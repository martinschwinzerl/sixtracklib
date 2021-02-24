#ifndef SIXTRACKLIB_PYTHON_WRAPPER_INIT_HELPER_H__
#define SIXTRACKLIB_PYTHON_WRAPPER_INIT_HELPER_H__

#include "sixtracklib/sixtracklib.h"
#include "python/sixtracklib/_wrapper/buffer_protocol.h"

#if defined( SIXTRL_TESTLIB_ENABLED ) && ( SIXTRL_TESTLIB_ENABLED == 1 )
#include "sixtracklib/testlib.h"
#endif /* defined( SIXTRL_TESTLIB_ENABLED ) */


#include <memory>
#include <string>
#include <utility>

#include <pybind11/pybind11.h>

namespace SIXTRL_CXX_NAMESPACE
{
namespace python
{
    SIXTRL_HOST_FN std::string Add_c99_ns( char const* SIXTRL_RESTRICT raw_str );

    SIXTRL_HOST_FN std::string Add_c99_ns(
        std::string const& SIXTRL_RESTRICT_REF raw_str );


    struct InitHelper
    {
        using real_buffer_adapter =
            SIXTRL_CXX_NAMESPACE::python::RealBufferAdapter;

        using int64_buffer_adapter =
            SIXTRL_CXX_NAMESPACE::python::Int64BufferAdapter;

        SIXTRL_HOST_FN explicit InitHelper( pybind11::module& ext_m );

        SIXTRL_HOST_FN InitHelper( InitHelper const& ) = delete;
        SIXTRL_HOST_FN InitHelper( InitHelper&& ) = delete;
        SIXTRL_HOST_FN InitHelper& operator=( InitHelper const& ) = delete;
        SIXTRL_HOST_FN InitHelper& operator=( InitHelper&& ) = delete;
        SIXTRL_HOST_FN virtual ~InitHelper() = default;

        SIXTRL_HOST_FN void init();

        /* ----------------------------------------------------------------- */
        /* common: */

        pybind11::class_< real_buffer_adapter  > real_adapter_type;
        pybind11::class_< int64_buffer_adapter > int64_adapter_type;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* belements: */

        pybind11::class_< ::NS(SCCoasting),
            std::unique_ptr< ::NS(SCCoasting), pybind11::nodelete >
            > be_sc_coasting_type;

        pybind11::class_< ::NS(SCQGaussProfile),
            std::unique_ptr< ::NS(SCQGaussProfile), pybind11::nodelete >
            > be_sc_qgauss_type;

        pybind11::class_< ::NS(Cavity),
            std::unique_ptr< ::NS(Cavity), pybind11::nodelete >
            > be_cavity_type;

        pybind11::class_< ::NS(DipoleEdge),
            std::unique_ptr< ::NS(DipoleEdge), pybind11::nodelete >
            > be_dipedge_type;

        pybind11::class_< ::NS(Drift),
            std::unique_ptr< ::NS(Drift), pybind11::nodelete >
            > be_drift_type;

        pybind11::class_< ::NS(DriftExact),
            std::unique_ptr< ::NS(DriftExact), pybind11::nodelete >
            > be_drift_exact_type;

        pybind11::class_< ::NS(EndTracking),
            std::unique_ptr< ::NS(EndTracking), pybind11::nodelete >
            > be_end_tracking_type;

        pybind11::class_< ::NS(LimitRect),
            std::unique_ptr< ::NS(LimitRect), pybind11::nodelete >
            > be_limit_rect_type;

        pybind11::class_< ::NS(LimitEllipse),
            std::unique_ptr< ::NS(LimitEllipse), pybind11::nodelete >
            > be_limit_ellipse_type;

        pybind11::class_< ::NS(LimitRectEllipse),
            std::unique_ptr< ::NS(LimitRectEllipse), pybind11::nodelete >
            > be_limit_rect_ellipse_type;

        pybind11::class_< ::NS(Monitor),
            std::unique_ptr< ::NS(Monitor), pybind11::nodelete >
            > be_monitor_type;

        pybind11::class_< ::NS(Multipole),
            std::unique_ptr< ::NS(Multipole), pybind11::nodelete >
            > be_multipole_type;

        pybind11::class_< ::NS(RFMultipole),
            std::unique_ptr< ::NS(RFMultipole), pybind11::nodelete >
            > be_rf_multipole_type;

        pybind11::class_< ::NS(SRotation),
            std::unique_ptr< ::NS(SRotation), pybind11::nodelete >
            > be_srotation_type;

        pybind11::class_< ::NS(XYShift),
            std::unique_ptr< ::NS(XYShift), pybind11::nodelete >
            > be_xyshift_type;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* cobjects: */

        pybind11::class_< ::NS(CObjIndex) > cobj_index_type;
        pybind11::class_< ::NS(CObjGarbageRange) > cobj_garbage_range_type;
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBufferView > cbuffer_view_type;
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBuffer,
                          SIXTRL_CXX_NAMESPACE::CBufferView > cbuffer_type;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* particles: */

        pybind11::class_< ::NS(SingleParticle),
            std::unique_ptr< ::NS(SingleParticle), pybind11::nodelete >
            > single_particle_type;

        pybind11::class_< ::NS(Particles),
            std::unique_ptr< ::NS(Particles), pybind11::nodelete >
            > particles_type;

        pybind11::class_< ::NS(ParticlesAddr),
            std::unique_ptr< ::NS(ParticlesAddr), pybind11::nodelete >
            >  particles_addr_type;

        /* ----------------------------------------------------------------- */
        /* testlib: */

        #if defined( SIXTRL_TESTLIB_ENABLED ) && ( SIXTRL_TESTLIB_ENABLED == 1 )

        pybind11::class_< ::NS(CObjTestNoPtrs),
            std::unique_ptr< ::NS(CObjTestNoPtrs), pybind11::nodelete >
            > cobj_test_no_ptrs_type;

        pybind11::class_< ::NS(CObjTestDataptrs),
            std::unique_ptr< ::NS(CObjTestDataptrs), pybind11::nodelete >
            > cobj_test_dataptrs_type;

        #endif /* defined( SIXTRL_TESTLIB_ENABLED ) */

        /* ----------------------------------------------------------------- */
        /* demolib: */

        #if defined( SIXTRL_DEMOTRACK_ENABLED ) && \
                   ( SIXTRL_DEMOTRACK_ENABLED == 1 )

        pybind11::class_< ::NS(DemotrackParticle) > demotrack_particle_type;

        #endif /* defined( SIXTRL_DEMOTRACK_ENABLED ) */

        pybind11::module& m;
    };
}
}


#endif /* SIXTRACKLIB_PYTHON_WRAPPER_INIT_HELPER_H__ */
