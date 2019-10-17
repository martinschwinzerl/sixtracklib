import pickle
import pysixtrack
import numpy as np
import helpers as hp
import matplotlib.pyplot as plt

n_turns = 100

with open('line.pkl', 'rb') as fid:
    line = pysixtrack.Line.from_dict(pickle.load(fid))

with open('particle_on_CO.pkl', 'rb') as fid:
    partCO = pickle.load(fid)

Dx_m = 1e-4
Dpx_rad = 1e-6
Dy_m = 2e-4
Dpy_rad = 3e-6
Dsigma_m = 2e-3
Ddelta = 2e-5

part = pysixtrack.Particles(**partCO)

dict_tbt = {}

print('Tracking ST')
x_tbt_ST, px_tbt_ST, y_tbt_ST, py_tbt_ST, sigma_tbt_ST, delta_tbt_ST = hp.track_particle_sixtrack(
    partCO=partCO, Dx_wrt_CO_m=np.array([Dx_m, Dx_m]), Dpx_wrt_CO_rad=Dpx_rad,
    Dy_wrt_CO_m=Dy_m, Dpy_wrt_CO_rad=Dpy_rad,
    Dsigma_wrt_CO_m=Dsigma_m, Ddelta_wrt_CO=Ddelta, n_turns=n_turns)
dict_tbt['ST'] = {
    kk: vv for kk, vv in zip(
        'x y px py sigma delta'.split(), [
            x_tbt_ST, px_tbt_ST, y_tbt_ST, py_tbt_ST, sigma_tbt_ST, delta_tbt_ST])}
print('Tracking STlib')
x_tbt_STl, px_tbt_STl, y_tbt_STl, py_tbt_STl, sigma_tbt_STl, delta_tbt_STl = hp.track_particle_sixtracklib(
    line, partCO=partCO, Dx_wrt_CO_m=np.array([Dx_m, Dx_m]), Dpx_wrt_CO_rad=Dpx_rad,
    Dy_wrt_CO_m=Dy_m, Dpy_wrt_CO_rad=Dpy_rad,
    Dsigma_wrt_CO_m=Dsigma_m, Ddelta_wrt_CO=Ddelta, n_turns=n_turns)
dict_tbt['STlib'] = {
    kk: vv for kk, vv in zip(
        'x y px py sigma delta'.split(), [
            x_tbt_STl, px_tbt_STl, y_tbt_STl, py_tbt_STl, sigma_tbt_STl, delta_tbt_STl])}
print('Tracking PyST')
x_tbt_pyST, px_tbt_pyST, y_tbt_pyST, py_tbt_pyST, sigma_tbt_pyST, delta_tbt_pyST = hp.track_particle_pysixtrack(
    line, part=part, Dx_wrt_CO_m=Dx_m, Dpx_wrt_CO_rad=Dpx_rad,
    Dy_wrt_CO_m=Dy_m, Dpy_wrt_CO_rad=Dpy_rad,
    Dsigma_wrt_CO_m=Dsigma_m, Ddelta_wrt_CO=Ddelta, n_turns=n_turns, verbose=True)
dict_tbt['PyST'] = {
    kk: vv for kk, vv in zip(
        'x y px py sigma delta'.split(), [
            x_tbt_pyST, px_tbt_pyST, y_tbt_pyST, py_tbt_pyST, sigma_tbt_pyST, delta_tbt_pyST])}

plt.close('all')
fig1 = plt.figure(1, figsize=(8 * 1.5, 6 * 1.2))
axx = fig1.add_subplot(3, 2, 1)
axx.plot(x_tbt_pyST[:, 0], label='PyST')
axx.plot(x_tbt_ST[:, 0], label='ST')
axx.plot(x_tbt_STl[:, 0], label='STl')
axx.set_ylabel('x [m]')

axy = fig1.add_subplot(3, 2, 2, sharex=axx)
axy.plot(y_tbt_pyST, label='PyST')
axy.plot(y_tbt_ST[:, 0], label='ST')
axy.plot(y_tbt_STl[:, 0], label='STl')
axy.set_ylabel('y [m]')


axpx = fig1.add_subplot(3, 2, 3, sharex=axx)
axpx.plot(px_tbt_pyST, label='PyST')
axpx.plot(px_tbt_ST[:, 0], label='ST')
axpx.plot(px_tbt_STl[:, 0], label='STl')
axpx.set_ylabel('px')


axpy = fig1.add_subplot(3, 2, 4, sharex=axx)
axpy.plot(py_tbt_pyST, label='PyST')
axpy.plot(py_tbt_ST[:, 0], label='ST')
axpy.plot(py_tbt_STl[:, 0], label='STl')
axpy.set_ylabel('py')


axsigma = fig1.add_subplot(3, 2, 5, sharex=axx)
axsigma.plot(sigma_tbt_pyST, label='PyST')
axsigma.plot(sigma_tbt_ST[:, 0], label='ST')
axsigma.plot(sigma_tbt_STl[:, 0], label='STl')
axsigma.set_ylabel('$\sigma$ [m]')
axsigma.set_xlabel('Turn number')

axdelta = fig1.add_subplot(3, 2, 6, sharex=axx)
axdelta.plot(delta_tbt_pyST, label='PyST')
axdelta.plot(delta_tbt_ST[:, 0], label='ST')
axdelta.plot(delta_tbt_STl[:, 0], label='STl')
axdelta.set_ylabel('$\delta$')
axdelta.set_xlabel('Turn number')
axdelta.legend()  # .draggable()

for ax in [axx, axy, axpx, axpy, axsigma, axdelta]:
    ax.ticklabel_format(style='sci', scilimits=(0, 0), axis='y')
    ax.grid(True)

fig2 = plt.figure(2, figsize=(8 * 1.5, 6 * 1.2))
axerrx = fig2.add_subplot(3, 2, 1, sharex=axx)
axerry = fig2.add_subplot(3, 2, 2, sharex=axerrx)
axerrpx = fig2.add_subplot(3, 2, 3, sharex=axerrx)
axerrpy = fig2.add_subplot(3, 2, 4, sharex=axerrx)
axerrsigma = fig2.add_subplot(3, 2, 5, sharex=axerrx)
axerrdelta = fig2.add_subplot(3, 2, 6, sharex=axerrx)

# Compute errors, choose implementations to comapare

ref = 'ST'
test = 'STlib'

for ax, coord in zip([axerrx, axerry, axerrpx, axerrpy, axerrsigma,
                      axerrdelta], 'x y px py sigma delta'.split()):
    ax.plot(np.abs(dict_tbt[test][coord] - dict_tbt[ref][coord])[:, 0])
    ax.set_ylabel(coord)
    ax.grid('on')

fig2.suptitle('Comparing %s against %s' % (test, ref))


plt.show()
