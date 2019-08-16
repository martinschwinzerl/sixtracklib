#!/usr/bin/env python
# -*- coding: utf-8 -*-

import itertools
import importlib
from collections import namedtuple

import numpy as np
from cobjects import CBuffer, CObject, CField
from .mad_helper import madseq_to_line


class Drift(CObject):
    _typeid = 2
    length = CField(0, 'real', default=0.0, alignment=8)


class DriftExact(CObject):
    _typeid = 3
    length = CField(0, 'real', default=0.0, alignment=8)


class BeamMonitor(CObject):
    _typeid = 10
    num_stores = CField(0, 'int64', default=0, alignment=8)
    start = CField(1, 'int64', default=0, alignment=8)
    skip = CField(2, 'int64', default=1, alignment=8)
    out_address = CField(3, 'uint64', default=0, alignment=8)
    max_particle_id = CField(4, 'int64', default=0, alignment=8)
    min_particle_id = CField(5, 'int64', default=0, alignment=8)
    is_rolling = CField(6, 'int64', default=0, alignment=8)
    is_turn_ordered = CField(7, 'int64', default=1, alignment=8)


def append_beam_monitors_to_lattice(
        beam_elements_buffer, until_turn_elem_by_elem, until_turn_turn_by_turn,
        until_turn, skip_turns=1, min_particle_id=0, max_particle_id=0,
        initial_at_turn=0):
    num_beam_monitors_added = 0
    start_turn_by_turn = max(initial_at_turn, until_turn_elem_by_elem)

    if until_turn_turn_by_turn > start_turn_by_turn:
        bm_turn_by_turn = BeamMonitor(
            start=start_turn_by_turn,
            num_stores=(
                until_turn_turn_by_turn -
                start_turn_by_turn),
            skip=1,
            out_address=0,
            min_particle_id=min_particle_id,
            max_particle_id=max_particle_id,
            is_rolling=False,
            is_turn_ordered=True,
            cbuffer=beam_elements_buffer)
        num_beam_monitors_added += 1

    start_output_turn = max(start_turn_by_turn, until_turn_turn_by_turn)

    if until_turn > start_output_turn:
        if skip_turns <= 0:
            skip_turns = 1

        num_stores = until_turn - start_output_turn
        remainder = num_stores % skip_turns
        num_stores = num_stores // skip_turns

        if remainder > 0:
            num_stores += 1

        bm_output = BeamMonitor(
            start=start_output_turn,
            num_stores=num_stores,
            skip=skip_turns,
            out_address=0,
            min_particle_id=min_particle_id,
            max_particle_id=max_particle_id,
            is_rolling=True,
            is_turn_ordered=True,
            cbuffer=beam_elements_buffer)
        num_beam_monitors_added += 1

    return num_beam_monitors_added


class Multipole(CObject):
    _typeid = 4
    order = CField(0, 'int64', default=0, const=True, alignment=8)
    length = CField(1, 'real', default=0.0, alignment=8)
    hxl = CField(2, 'real', default=0.0, alignment=8)
    hyl = CField(3, 'real', default=0.0, alignment=8)
    bal = CField(4, 'real', default=0.0, alignment=8, pointer=True,
                    length='2 * order + 2')

    @staticmethod
    def _factorial(x):
        if not isinstance(x, int):
            return 0
        return (x > 0) and (x * Multipole._factorial(x - 1)) or 1

    def __init__(self, order=None, knl=None, ksl=None, bal=None, **kwargs):
        if bal is None and \
                (knl is not None or ksl is not None or order is not None):
            if knl is None:
                knl = []
            if ksl is None:
                ksl = []
            if order is None:
                order = 0

            n = max((order + 1), max(len(knl), len(ksl)))
            assert(n > 0)

            _knl = np.array(knl)
            nknl = np.zeros(n, dtype=_knl.dtype)
            nknl[:len(knl)] = knl
            knl = nknl
            del(_knl)
            assert(len(knl) == n)

            _ksl = np.array(ksl)
            nksl = np.zeros(n, dtype=_ksl.dtype)
            nksl[:len(ksl)] = ksl
            ksl = nksl
            del(_ksl)
            assert(len(ksl) == n)

            order = n - 1
            bal = np.zeros(2 * order + 2)

            for ii in range(0, len(knl)):
                inv_factorial = 1.0 / float(Multipole._factorial(ii))
                jj = 2 * ii
                bal[jj] = knl[ii] * inv_factorial
                bal[jj + 1] = ksl[ii] * inv_factorial

            kwargs["bal"] = bal
            kwargs["order"] = order

        elif bal is not None and bal and len(bal) > 2 and ((len(bal) % 2) == 0):
            kwargs["bal"] = bal
            kwargs["order"] = (len(bal) - 2) / 2

        CObject.__init__(self, **kwargs)

    @property
    def knl(self):
        return [self.bal[ii] * Multipole._factorial(ii // 2)
                for ii in range(0, len(self.bal), 2)]

    @property
    def ksl(self):
        return [self.bal[ii + 1] * Multipole._factorial(ii // 2 + 1)
                for ii in range(0, len(self.bal), 2)]


class Cavity(CObject):
    _typeid = 5
    voltage = CField(0, 'real', default=0.0, alignment=8)
    frequency = CField(1, 'real', default=0.0, alignment=8)
    lag = CField(2, 'real', default=0.0, alignment=8)


class XYShift(CObject):
    _typeid = 6
    dx = CField(0, 'real', default=0.0, alignment=8)
    dy = CField(1, 'real', default=0.0, alignment=8)


class SRotation(CObject):
    _typeid = 7
    cos_z = CField(0, 'real', default=1.0, alignment=8)
    sin_z = CField(1, 'real', default=0.0, alignment=8)

    def __init__(self, angle=0, **nargs):
        anglerad = angle / 180 * np.pi
        cos_z = np.cos(anglerad)
        sin_z = np.sin(anglerad)
        CObject.__init__(self,
                         cos_z=cos_z, sin_z=sin_z, **nargs)

    @property
    def angle(self):
        return np.arctan2(self.sin_z, self.cos_z)

    @property
    def angle_deg(self):
        return self.angle * (180.0 / np.pi)


class BeamBeam4D(CObject):
    _typeid = 8
    size = CField(0, 'uint64', const=True, default=0)
    data = CField(1, 'float64', default=0.0,
                  length='size', pointer=True)

    def __init__(self, **kwargs):
        if 'q_part' in kwargs:
            slots = (
                'q_part',
                'N_part',
                'sigma_x',
                'sigma_y',
                'beta_s',
                'min_sigma_diff',
                'Delta_x',
                'Delta_y',
                'Dpx_sub',
                'Dpy_sub',
                'enabled')
            data = [kwargs[ss] for ss in slots]
            CObject.__init__(self, size=len(data), data=data, **kwargs)
        else:
            CObject.__init__(self, **kwargs)


class BeamBeam6D(CObject):
    _typeid = 9
    size = CField(0, 'uint64', const=True, default=0)
    data = CField(1, 'float64', default=0.0,
                  length='size', pointer=True)

    def __init__(self, **kwargs):
        if 'q_part' in kwargs:
            import pysixtrack
            data = pysixtrack.BB6Ddata.BB6D_init(
                **{kk: kwargs[kk] for kk in kwargs.keys() if kk != 'cbuffer'}).tobuffer()
            CObject.__init__(self, size=len(data), data=data, **kwargs)
        else:
            CObject.__init__(self, **kwargs)


class LimitRect(CObject):
    _typeid = 11
    min_x = CField(0, 'float64', default=-1.0, alignment=8)
    max_x = CField(1, 'float64', default=+1.0, alignment=8)
    min_y = CField(2, 'float64', default=-1.0, alignment=8)
    max_y = CField(3, 'float64', default=+1.0, alignment=8)


class LimitEllipse(CObject):
    _typeid = 12
    a_squ = CField(0, 'float64', default=+1.0, alignment=8)
    b_squ = CField(1, 'float64', default=+1.0, alignment=8)
    a_b_squ = CField(2, 'float64', alignment=8)

    def __init__(self, a_squ=None, b_squ=None, **kwargs):
        if a_squ is None:
            a = kwargs.get( 'a', 1.0 )
            a_squ = a * a

        if b_squ is None:
            b = kwargs.get( 'b', 1.0 )
            b_squ = b * b

        kwargs[ 'a_squ' ] = a_squ
        kwargs[ 'b_squ' ] = b_squ
        a_b_squ = a_squ * b_squ

        if not 'a_b_squ' in kwargs:
            kwargs[ 'a_b_squ' ] = a_b_squ

        if abs( kwargs.get( 'a_b_squ' ) - a_b_squ ) <= \
                np.finfo('float64').resolution:
            CObject.__init__( self, **kwargs )
        else:
            raise ValueError( "a_squ, b_squ and a_b_squ do not agree" )

    def set_half_axes(self, a, b):
        return self.set_half_axes_squ(a * a, b * b)

    def set_half_axes_squ(self, a_squ, b_squ):
        self.a_squ = a_squ
        self.b_squ = b_squ
        self.a_b_squ = a_squ * b_squ
        return self


class DipoleEdge(CObject):
    _typeid = 24
    r21 = CField(0, 'float64', default=0.0, alignment=8)
    r43 = CField(1, 'float64', default=0.0, alignment=8)

    def __init__(self, **kwargs):
        # TODO: Implement conversion schemes, if required
        CObject.__init__(self, *kwargs)


class Elements(object):
    element_types = {'Cavity': Cavity,
                     'Drift': Drift,
                     'DriftExact': DriftExact,
                     'Multipole': Multipole,
                     #                     'RFMultipole': RFMultipole,
                     'SRotation': SRotation,
                     'XYShift': XYShift,
                     'BeamBeam6D': BeamBeam6D,
                     'BeamBeam4D': BeamBeam4D,
                     'LimitRect': LimitRect,
                     'LimitEllipse': LimitEllipse,
                     'DipoleEdge': DipoleEdge,
                     #                     'Line': Line,
                     'BeamMonitor': BeamMonitor,
                     }

    def _mk_fun(self, buff, cls):
        def fun(*args, **nargs):
            # print(cls.__name__,nargs)
            return cls(cbuffer=buff, **nargs)
        return fun

    @classmethod
    def fromfile(cls, filename):
        cbuffer = CBuffer.fromfile(filename)
        return cls(cbuffer=cbuffer)

    @classmethod
    def fromline(cls, line, exact_drift=False):
        return cls().append_line(line, exact_drift)

    def append_line(self, line, exact_drift=False):
        for label, element_name, element in line:
            if exact_drift and element_name == 'Drift':
                element_name = 'DriftExact'
            getattr(self, element_name)(**element._asdict())
        return self

    def tofile(self, filename):
        self.cbuffer.tofile(filename)

    def __init__(self, cbuffer=None):
        if cbuffer is None:
            self.cbuffer = CBuffer()
        else:
            self.cbuffer = cbuffer
        for name, cls in self.element_types.items():
            setattr(self, name, self._mk_fun(self.cbuffer, cls))
            self.cbuffer.typeids[cls._typeid] = cls
        self._builder = self.gen_builder()

    def gen_builder(self):
        out = {}
        for name, cls in self.element_types.items():
            out[name] = getattr(self, name)
        return out

    def get_elements(self):
        n = self.cbuffer.n_objects
        return [self.cbuffer.get_object(i) for i in range(n)]

    def get(self, objid):
        return self.cbuffer.get_object(objid)

    @classmethod
    def from_mad(cls, seq, exact_drift=False):
        line = madseq_to_line(seq)
        return cls.fromline(line, exact_drift=exact_drift)

    # @classmethod
    # def from_mad2(cls, seq):
    #    self=cls()
    #    list(madseq_to_line(seq,self._builder))
    #    return self
