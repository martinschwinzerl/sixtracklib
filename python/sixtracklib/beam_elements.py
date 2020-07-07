#!/usr/bin/env python
# -*- coding: utf-8 -*-

import itertools
import importlib
from collections import namedtuple

import numpy as np
from scipy.special import factorial
from scipy.constants import e as qe
from cobjects import CBuffer, CObject, CField
from .mad_helper import madseq_to_generator

from .stcommon import st_BeamBeam4D_type_id, st_BeamBeam4D_data_addr_offset, \
    st_BeamBeam6D_type_id, st_BeamBeam6D_data_addr_offset, \
    st_BeamMonitor_type_id, st_Cavity_type_id, st_DipoleEedge_type_id, \
    st_Drift_type_id, st_DriftExact_type_id, \
    st_LimitRect_type_id, st_LimitEllipse_type_id, \
    st_LimitRectEllipse_type_id, st_Multipole_type_id, st_RFMultipole_type_id, \
    st_SpaceChargeCoasting_type_id, \
    st_SpaceChargeQGaussianProfile_type_id, st_LineDensityProfileData_type_id, \
    st_NullSpaceChargeInterpolatedProfile, \
    st_SpaceChargeInterpolatedProfile_type_id, \
    st_SpaceChargeInterpolatedProfile_interpol_data_addr_offset, \
    st_SRotation_type_id, st_XYShift_type_id

class Drift(CObject):
    _typeid = st_Drift_type_id()
    length = CField(0, "real", default=0.0)


class DriftExact(CObject):
    _typeid = st_DriftExact_type_id()
    length = CField(0, "real", default=0.0)


class Multipole(CObject):
    _typeid = st_Multipole_type_id()
    order = CField(0, "int64", default=0, const=True)
    length = CField(1, "real", default=0.0)
    hxl = CField(2, "real", default=0.0)
    hyl = CField(3, "real", default=0.0)
    bal = CField(
        4,
        "real",
        default=0.0,
        alignment=8,
        pointer=True,
        length="2 * order + 2",
    )

    def __init__(self, order=None, knl=None, ksl=None, bal=None, **kwargs):
        if bal is None and (
            knl is not None or ksl is not None or order is not None
        ):
            if knl is None:
                knl = []
            if ksl is None:
                ksl = []
            if order is None:
                order = 0

            n = max((order + 1), max(len(knl), len(ksl)))
            assert n > 0

            _knl = np.array(knl)
            nknl = np.zeros(n, dtype=_knl.dtype)
            nknl[: len(knl)] = knl
            knl = nknl
            del _knl
            assert len(knl) == n

            _ksl = np.array(ksl)
            nksl = np.zeros(n, dtype=_ksl.dtype)
            nksl[: len(ksl)] = ksl
            ksl = nksl
            del _ksl
            assert len(ksl) == n

            order = n - 1
            bal = np.zeros(2 * order + 2)

            idx = np.array([ii for ii in range(0, len(knl))])
            inv_factorial = 1.0 / factorial(idx, exact=True)
            bal[0::2] = knl * inv_factorial
            bal[1::2] = ksl * inv_factorial

            kwargs["bal"] = bal
            kwargs["order"] = order

        elif (
            bal is not None and bal and len(bal) > 2 and ((len(bal) % 2) == 0)
        ):
            kwargs["bal"] = bal
            kwargs["order"] = (len(bal) - 2) / 2

        super().__init__(**kwargs)

    @property
    def knl(self):
        idx = np.array([ii for ii in range(0, len(self.bal), 2)])
        return self.bal[idx] * factorial(idx // 2, exact=True)

    @property
    def ksl(self):
        idx = np.array([ii for ii in range(0, len(self.bal), 2)])
        return self.bal[idx + 1] * factorial(idx // 2, exact=True)

    def set_knl(self, value, order):
        assert order <= self.order
        self.bal[order * 2] = value / factorial(order, exact=True)

    def set_ksl(self, value, order):
        assert order <= self.order
        self.bal[order * 2 + 1] = value / factorial(order, exact=True)


class RFMultipole(CObject):
    _typeid = st_RFMultipole_type_id()
    order = CField(0, "int64", default=0, const=True)
    voltage = CField(1, "real", default=0.0)
    frequency = CField(2, "real", default=0.0)
    lag = CField(3, "real", default=0.0)
    bal = CField( 4, "real", pointer=True, length="2*order+2", default=0.0)
    phase = CField(5, "real", pointer=True, length="2*order+2", default=0.0)

    def __init__(
        self,
        order=None,
        knl=None,
        ksl=None,
        pn=None,
        ps=None,
        bal=None,
        p=None,
        **kwargs
    ):
        if bal is None and (
            knl is not None
            or ksl is not None
            or pn is not None
            or ps is not None
            or order is not None
        ):
            if knl is None:
                knl = []
            if ksl is None:
                ksl = []
            if pn is None:
                pn = []
            if ps is None:
                ps = []
            if order is None:
                order = 0

            n = max((order + 1), max(len(knl), len(ksl), len(pn), len(ps)))
            assert n > 0

            _knl = np.array(knl)
            nknl = np.zeros(n, dtype=_knl.dtype)
            nknl[: len(knl)] = knl
            knl = nknl
            del _knl
            assert len(knl) == n

            _ksl = np.array(ksl)
            nksl = np.zeros(n, dtype=_ksl.dtype)
            nksl[: len(ksl)] = ksl
            ksl = nksl
            del _ksl
            assert len(ksl) == n

            _pn = np.array(pn)
            npn = np.zeros(n, dtype=_pn.dtype)
            npn[: len(pn)] = pn
            pn = npn
            del _pn
            assert len(pn) == n

            _ps = np.array(ps)
            nps = np.zeros(n, dtype=_ps.dtype)
            nps[: len(ps)] = ps
            ps = nps
            del _ps
            assert len(ps) == n

            order = n - 1
            bal = np.zeros(2 * order + 2)
            p = np.zeros(2 * order + 2)

            idx = np.array([ii for ii in range(0, len(knl))])
            inv_factorial = 1.0 / factorial(idx, exact=True)
            bal[0::2] = knl * inv_factorial
            bal[1::2] = ksl * inv_factorial

            p[0::2] = pn
            p[1::2] = ps

            kwargs["bal"] = bal
            kwargs["phase"] = p
            kwargs["order"] = order

        elif (
            bal is not None
            and bal
            and len(bal) > 2
            and ((len(bal) % 2) == 0)
            and p is not None
            and p
            and len(p) > 2
            and ((len(p) % 2) == 0)
        ):
            kwargs["bal"] = bal
            kwargs["phase"] = p
            kwargs["order"] = (len(bal) - 2) / 2

        super().__init__(**kwargs)

    @property
    def knl(self):
        idx = np.array([ii for ii in range(0, len(self.bal), 2)])
        return self.bal[idx] * factorial(idx // 2, exact=True)

    @property
    def ksl(self):
        idx = np.array([ii for ii in range(0, len(self.bal), 2)])
        return self.bal[idx + 1] * factorial(idx // 2, exact=True)

    def set_knl(self, value, order):
        assert order <= self.order
        self.bal[order * 2] = value / factorial(order, exact=True)

    def set_ksl(self, value, order):
        assert order <= self.order
        self.bal[order * 2 + 1] = value / factorial(order, exact=True)

    @property
    def pn(self):
        idx = np.array([ii for ii in range(0, len(self.p), 2)])
        return self.phase[idx]

    @property
    def ps(self):
        idx = np.array([ii for ii in range(0, len(self.p), 2)])
        return self.phase[idx + 1]

    def set_pn(self, value, order):
        assert order <= self.order
        self.phase[order * 2] = value

    def set_ps(self, value, order):
        assert order <= self.order
        self.phase[order * 2 + 1] = value


class Cavity(CObject):
    _typeid = st_Cavity_type_id()
    voltage = CField(0, "real", default=0.0)
    frequency = CField(1, "real", default=0.0)
    lag = CField(2, "real", default=0.0)


class XYShift(CObject):
    _typeid = st_XYShift_type_id()
    dx = CField(0, "real", default=0.0)
    dy = CField(1, "real", default=0.0)


class SRotation(CObject):
    _typeid = st_SRotation_type_id()
    cos_z = CField(0, "real", default=1.0)
    sin_z = CField(1, "real", default=0.0)

    def __init__(self, angle=0, **nargs):
        anglerad = angle / 180 * np.pi
        cos_z = np.cos(anglerad)
        sin_z = np.sin(anglerad)
        super().__init__(cos_z=cos_z, sin_z=sin_z, **nargs)

    @property
    def angle(self):
        return np.arctan2(self.sin_z, self.cos_z)

    @property
    def angle_deg(self):
        return self.angle * (180.0 / np.pi)


class BeamMonitor(CObject):
    _typeid = st_BeamMonitor_type_id()
    num_stores = CField(0, "int64", default=0)
    start = CField(1, "int64", default=0)
    skip = CField(2, "int64", default=1)
    out_address = CField(3, "uint64", default=0)
    max_particle_id = CField(4, "int64", default=0)
    min_particle_id = CField(5, "int64", default=0)
    is_rolling = CField(6, "int64", default=0)
    is_turn_ordered = CField(7, "int64", default=1)


def append_beam_monitors_to_lattice(
    beam_elements_buffer,
    until_turn_elem_by_elem,
    until_turn_turn_by_turn,
    until_turn,
    skip_turns=1,
    min_particle_id=0,
    max_particle_id=0,
    initial_at_turn=0,
):
    num_beam_monitors_added = 0
    start_turn_by_turn = max(initial_at_turn, until_turn_elem_by_elem)

    if until_turn_turn_by_turn > start_turn_by_turn:
        bm_turn_by_turn = BeamMonitor(
            start=start_turn_by_turn,
            num_stores=(until_turn_turn_by_turn - start_turn_by_turn),
            skip=1,
            out_address=0,
            min_particle_id=min_particle_id,
            max_particle_id=max_particle_id,
            is_rolling=False,
            is_turn_ordered=True,
            cbuffer=beam_elements_buffer,
        )
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
            cbuffer=beam_elements_buffer,
        )
        num_beam_monitors_added += 1

    return num_beam_monitors_added


class LimitRect(CObject):
    _typeid = st_LimitRect_type_id()
    min_x = CField(0, "float64", default=-1.0)
    max_x = CField(1, "float64", default=+1.0)
    min_y = CField(2, "float64", default=-1.0)
    max_y = CField(3, "float64", default=+1.0)

    def __init__(
        self,
        min_x=None,
        max_x=None,
        min_y=None,
        max_y=None,
        min_coord=-1.0,
        max_coord=1.0,
        **kwargs
    ):
        if min_x is None and min_coord is not None:
            min_x = min_coord
        if min_y is None and min_coord is not None:
            min_y = min_coord
        if max_x is None and max_coord is not None:
            max_x = max_coord
        if max_y is None and max_coord is not None:
            max_y = max_coord

        if min_x is None:
            min_x = -1.0
        if max_x is None:
            max_x = 1.0
        if min_y is None:
            min_y = -1.0
        if max_y is None:
            max_y = 1.0

        delta_x = 0.0
        delta_y = 0.0

        if min_x is not None and max_x is not None:
            if min_x > max_x:
                min_x, max_x = max_x, min_x
            delta_x = max_x - min_x

        if min_y is not None and max_y is not None:
            if min_y > max_y:
                min_y, max_y = max_y, min_y
            delta_y = max_y - min_y

        if delta_x * delta_y > 0.0:
            super().__init__(
                min_x=min_x, max_x=max_x, min_y=min_y, max_y=max_y, **kwargs
            )
        else:
            raise ValueError(
                "min_x, max_x, min_y, max_y have to delimit "
                + "a non-vanishing rectangle; values = [{0},{1},{2},{3}]".format(
                    min_x, max_x, min_y, max_x
                )
            )


class LimitEllipse(CObject):
    _typeid = st_LimitEllipse_type_id()
    a_squ = CField(0, "float64", default=+1.0)
    b_squ = CField(1, "float64", default=+1.0)
    a_b_squ = CField(2, "float64")

    def __init__(self, a_squ=None, b_squ=None, **kwargs):
        if a_squ is None and "a" in kwargs:
            a = kwargs.get("a")
            if a is not None and a > 0.0:
                a_squ = a * a
        if a_squ is None:
            a_squ = 1.0

        if b_squ is None and "b" in kwargs:
            b = kwargs.get("b")
            if b is not None and b > 0.0:
                b_squ = b * b
        if b_squ is None:
            b_squ = 1.0

        if a_squ > 0.0 and b_squ > 0.0:
            a_b_squ = a_squ * b_squ
            super().__init__(
                a_squ=a_squ, b_squ=b_squ, a_b_squ=a_squ * b_squ, **kwargs
            )
        else:
            raise ValueError("a_squ and b_squ have to be positive definite")

    def set_half_axes(self, a, b):
        return self.set_half_axes_squ(a * a, b * b)

    def set_half_axes_squ(self, a_squ, b_squ):
        self.a_squ = a_squ
        self.b_squ = b_squ
        self.a_b_squ = a_squ * b_squ
        return self

class BeamBeam4D(CObject):
    _typeid = st_BeamBeam4D_type_id()
    size = CField(0, "uint64", const=True, default=0)
    data = CField(1, "float64", default=0.0, length="size", pointer=True)

    def __init__(self, **kwargs):
        if "x_bb" in kwargs:
            slots = (
                "charge",
                "sigma_x",
                "sigma_y",
                "beta_r",
                "min_sigma_diff",
                "x_bb",
                "y_bb",
                "d_px",
                "d_py",
                "enabled",
            )

            data = [qe] + [kwargs[ss] for ss in slots]
            super().__init__(size=len(data), data=data, **kwargs)
        else:
            super().__init__(**kwargs)


class BeamBeam6D(CObject):
    _typeid = st_BeamBeam6D_type_id()
    size = CField(0, "uint64", const=True, default=0)
    data = CField(1, "float64", default=0.0, length="size", pointer=True)

    def __init__(self, **kwargs):
        if "x_bb_co" in kwargs:

            import pysixtrack

            params = kwargs

            data = pysixtrack.BB6Ddata.BB6D_init(
                q_part=qe,
                phi=params["phi"],
                alpha=params["alpha"],
                delta_x=params["x_bb_co"],
                delta_y=params["y_bb_co"],
                N_part_per_slice=params["charge_slices"],
                z_slices=params["zeta_slices"],
                Sig_11_0=params["sigma_11"],
                Sig_12_0=params["sigma_12"],
                Sig_13_0=params["sigma_13"],
                Sig_14_0=params["sigma_14"],
                Sig_22_0=params["sigma_22"],
                Sig_23_0=params["sigma_23"],
                Sig_24_0=params["sigma_24"],
                Sig_33_0=params["sigma_33"],
                Sig_34_0=params["sigma_34"],
                Sig_44_0=params["sigma_44"],
                x_CO=params["x_co"],
                px_CO=params["px_co"],
                y_CO=params["y_co"],
                py_CO=params["py_co"],
                sigma_CO=params["zeta_co"],
                delta_CO=params["delta_co"],
                min_sigma_diff=params["min_sigma_diff"],
                threshold_singular=params["threshold_singular"],
                Dx_sub=params["d_x"],
                Dpx_sub=params["d_px"],
                Dy_sub=params["d_y"],
                Dpy_sub=params["d_py"],
                Dsigma_sub=params["d_zeta"],
                Ddelta_sub=params["d_delta"],
                enabled=params["enabled"],
            ).tobuffer()
            super().__init__(size=len(data), data=data, **kwargs)
        else:
            super().__init__(**kwargs)


class SpaceChargeCoasting(CObject):
    _typeid = st_SpaceChargeCoasting_type_id()
    number_of_particles = CField(0, "float64", default=0.0)
    circumference = CField(1, "float64", default=1.0)
    sigma_x = CField(2, "float64", default=1.0)
    sigma_y = CField(3, "float64", default=1.0)
    length = CField(4, "float64", default=0.0)
    x_co = CField(5, "float64", default=0.0)
    y_co = CField(6, "float64", default=0.0)
    min_sigma_diff = CField(7, "float64", default=1e-10)
    enabled = CField(8, "uint64", default=1)

    def __init__(self, **kwargs):
        super().__init__(**kwargs)


class SpaceChargeQGaussianProfile(CObject):
    _typeid = st_SpaceChargeQGaussianProfile_type_id()
    number_of_particles = CField(0, "float64", default=0.0)
    bunchlength_rms = CField(1, "float64", default=1.0)
    sigma_x = CField(2, "float64", default=1.0)
    sigma_y = CField(3, "float64", default=1.0)
    length = CField(4, "float64", default=0.0)
    x_co = CField(5, "float64", default=0.0 )
    y_co = CField(6, "float64", default=0.0)
    min_sigma_diff = CField(7, "float64", default=1e-10)
    q_param = CField(8, "float64", default=1.0)
    b_param = CField(9, "float64", default=1.0)
    enabled = CField(10, "uint64", default=1)

    def __init__(self, **kwargs):
        super().__init__(**kwargs)

class SpaceChargeInterpolatedProfile(CObject):
    _typeid = st_SpaceChargeInterpolatedProfile_type_id()
    number_of_particles = CField(0, "float64", default=0.0)
    sigma_x = CField(1, "float64", default=1.0)
    sigma_y = CField(2, "float64", default=1.0)
    length = CField(3, "float64", default=0.0)
    x_co = CField(4, "float64", default=0.0)
    y_co = CField(5, "float64", default=0.0)
    interpol_data_addr = CField(6, "uint64", default=0)
    line_density_prof_fallback = CField(7, "float64", default=1.0)
    min_sigma_diff = CField(8, "float64", default=1e-10)
    enabled = CField(9, "uint64", default=1)

    def __init__(self, **kwargs):
        super().__init__(**kwargs)


class LimitRectEllipse(CObject):
    _typeid = st_LimitRectEllipse_type_id()
    max_x = CField(0, "float64", default=+1.0)
    max_y = CField(1, "float64", default=+1.0)
    a_squ = CField(2, "float64", default=+1.0)
    b_squ = CField(3, "float64", default=+1.0)
    a_b_squ = CField(4, "float64")

    def __init__(
        self, max_x=None, max_y=None, a_squ=None, b_squ=None, **kwargs
    ):
        if max_x is None:
            max_x = 1.0
        if max_y is None:
            max_y = 1.0
        if a_squ is None and "a" in kwargs:
            a = kwargs.get("a")
            if a is not None and a > 0.0:
                a_squ = a * a
        if a_squ is None:
            a_squ = 1.0

        if b_squ is None and "b" in kwargs:
            b = kwargs.get("b")
            if b is not None and b > 0.0:
                b_squ = b * b
        if b_squ is None:
            b_squ = 1.0

        if max_x < 0.0:
            raise ValueError("max_x has to be positive definite")

        if max_y < 0.0:
            raise ValueError("max_y has to be_positive definite")

        if a_squ < 0.0 or b_squ < 0.0:
            raise ValueError("a_squ and b_squ have to be positive definite")

        super().__init__(
            max_x=max_x,
            max_y=max_y,
            a_squ=a_squ,
            b_squ=b_squ,
            a_b_squ=a_squ * b_squ,
            **kwargs
        )

    def set_half_axes(self, a, b):
        return self.set_half_axes_squ(a * a, b * b)

    def set_half_axes_squ(self, a_squ, b_squ):
        self.a_squ = a_squ
        self.b_squ = b_squ
        self.a_b_squ = a_squ * b_squ
        return self


class DipoleEdge(CObject):
    _typeid = st_DipoleEedge_type_id()
    r21 = CField(0, "float64", default=0.0)
    r43 = CField(1, "float64", default=0.0)

    def __init__(
        self,
        r21=None,
        r43=None,
        h=None,
        e1=None,
        hgap=None,
        fint=None,
        **kwargs
    ):
        if r21 is None and r43 is None:
            ZERO = np.float64(0.0)
            if hgap is None:
                hgap = ZERO
            if h is None:
                h = ZERO
            if e1 is None:
                e1 = ZERO
            if fint is None:
                fint = ZERO

            # Check that the argument e1 is not too close to ( 2k + 1 ) * pi/2
            # so that the cos in the denominator of the r43 calculation and
            # the tan in the r21 calculations blow up
            assert not np.isclose(np.absolute(np.cos(e1)), ZERO)

            corr = np.float64(2.0) * h * hgap * fint
            r21 = h * np.tan(e1)
            temp = (
                corr / np.cos(e1) * (np.float64(1) + np.sin(e1) * np.sin(e1))
            )

            # again, the argument to the tan calculation should be limited
            assert not np.isclose(np.absolute(np.cos(e1 - temp)), ZERO)
            r43 = -h * np.tan(e1 - temp)

        if r21 is not None and r43 is not None:
            super().__init__(r21=r21, r43=r43, **kwargs)
        else:
            raise ValueError(
                "DipoleEdge needs either coefficiants r21 and r43"
                " or suitable values for h, e1, hgap, and fint provided"
            )


class Elements(object):
    element_types = {
        "Cavity": Cavity,
        "Drift": Drift,
        "DriftExact": DriftExact,
        "Multipole": Multipole,
        "RFMultipole": RFMultipole,
        "SRotation": SRotation,
        "XYShift": XYShift,
        "BeamMonitor": BeamMonitor,
        "LimitRect": LimitRect,
        "LimitEllipse": LimitEllipse,
        "LimitRectEllipse": LimitRectEllipse,
        "BeamBeam4D": BeamBeam4D,
        "BeamBeam6D": BeamBeam6D,
        "SpaceChargeCoasting": SpaceChargeCoasting,
        "SpaceChargeQGaussianProfile": SpaceChargeQGaussianProfile,
        "SpaceChargeInterpolatedProfile": SpaceChargeInterpolatedProfile,
        "LimitRect": LimitRect,
        "LimitEllipse": LimitEllipse,
        "LimitRectEllipse": LimitRectEllipse,
        "DipoleEdge": DipoleEdge,
        #                     'Line': Line,
        # 'Solenoid': Solenoid,
        # 'Wire': Wire,
    }

    @staticmethod
    def add_element_type(cls, cls_name):
        Elements.element_types.update({cls_name: cls})

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
    def from_line(cls, line):
        self = cls()
        return self.append_line(line)

    def append_line(self, line):
        for element in line.elements:
            element_name = element.__class__.__name__
            getattr(self, element_name)(**element.to_dict(keepextra=True))
        return self

    def to_file(self, filename):
        self.cbuffer.tofile(filename)
        return self

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
        # temporary
        self = cls()
        for label, element_name, element in madseq_to_generator(seq):
            if exact_drift and element_name == "Drift":
                element_name = "DriftExact"
            getattr(self, element_name)(**element._asdict())
        return self

    # @classmethod
    # def from_mad2(cls, seq):
    #    self=cls()
    #    list(madseq_to_line(seq,self._builder))
    #    return self
