#include "python/sixtracklib/_wrapper/init_helper.h"
#include "python/sixtracklib/_wrapper/buffer_protocol.h"
#include "python/sixtracklib/_wrapper/common.h"
#include "python/sixtracklib/_wrapper/testlib.h"
#include "python/sixtracklib/_wrapper/demotrack.h"

#include "sixtracklib/sixtracklib.h"

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace SIXTRL_CXX_NAMESPACE
{
namespace python
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        namespace stpy = SIXTRL_CXX_NAMESPACE::python;
        namespace py = pybind11;
    }

    std::string Add_c99_ns( char const* SIXTRL_RESTRICT raw_str ) {
        if( ( raw_str == nullptr ) || ( std::strlen( raw_str ) == 0 ) )
        {
            throw std::runtime_error( "raw_str is empty / null!" );
        }

        return std::string{ SIXTRL_C99_NAMESPACE_PREFIX_STR } +
               std::string{ raw_str };
    }

    std::string Add_c99_ns(
        std::string const& SIXTRL_RESTRICT_REF raw_str )
    {
        if( raw_str.empty() )
        {
            throw std::runtime_error( "raw_str is empty / null!" );
        }

        return std::string{ SIXTRL_C99_NAMESPACE_PREFIX_STR } + raw_str;
    }



    InitHelper::InitHelper( pybind11::module& ext_m ) :
        real_adapter_type( ext_m,
            "RealBufferAdapter", pybind11::buffer_protocol() ),
        int64_adapter_type( ext_m,
            "Int64BufferAdapter", pybind11::buffer_protocol() ),
        be_sc_coasting_type( ext_m, stpy::Add_c99_ns( "SCCoasting" ).c_str() ),
        be_sc_qgauss_type( ext_m, stpy::Add_c99_ns( "SCQGaussProfile" ).c_str() ),
        be_cavity_type( ext_m, stpy::Add_c99_ns( "Cavity" ).c_str() ),
        be_dipedge_type( ext_m, stpy::Add_c99_ns( "DipoleEdge" ).c_str() ),
        be_drift_type( ext_m, stpy::Add_c99_ns( "Drift" ).c_str() ),
        be_drift_exact_type( ext_m, stpy::Add_c99_ns( "DriftExact" ).c_str() ),
        be_end_tracking_type( ext_m, stpy::Add_c99_ns( "EndTracking" ).c_str() ),
        be_limit_rect_type( ext_m, stpy::Add_c99_ns( "LimitRect" ).c_str() ),
        be_limit_ellipse_type( ext_m, stpy::Add_c99_ns( "LimitEllipse" ).c_str() ),
        be_limit_rect_ellipse_type( ext_m, stpy::Add_c99_ns(
            "LimitRectEllipse" ).c_str() ),
        be_monitor_type( ext_m, stpy::Add_c99_ns( "Monitor" ).c_str() ),
        be_multipole_type( ext_m, stpy::Add_c99_ns( "Multipole" ).c_str() ),
        be_rf_multipole_type( ext_m, stpy::Add_c99_ns( "RFMultipole" ).c_str() ),
        be_srotation_type( ext_m, stpy::Add_c99_ns( "SRotation" ).c_str() ),
        be_xyshift_type( ext_m, stpy::Add_c99_ns( "XYShift" ).c_str() ),
        cobj_index_type( ext_m, stpy::Add_c99_ns( "CObjIndex" ).c_str() ),
        cobj_garbage_range_type( ext_m,stpy::Add_c99_ns(
            "ObjGarbageRange" ).c_str() ),
        cbuffer_view_type( ext_m, "CBufferView" ),
        cbuffer_type( ext_m, "CBuffer" ),
        single_particle_type( ext_m, stpy::Add_c99_ns(
            "SingleParticle" ).c_str() ),
        particles_type( ext_m, stpy::Add_c99_ns( "Particles" ).c_str() ),
        particles_addr_type( ext_m, stpy::Add_c99_ns(
            "ParticlesAddr" ).c_str() ),
        #if defined( SIXTRL_TESTLIB_ENABLED ) && \
                   ( SIXTRL_TESTLIB_ENABLED == 1 )
        cobj_test_no_ptrs_type( ext_m, stpy::Add_c99_ns(
            "CObjTestNoPtrs" ).c_str() ),
        cobj_test_dataptrs_type( ext_m, stpy::Add_c99_ns(
            "CObjTestDataptrs" ).c_str() ),
        #endif /* defined( SIXTRL_TESTLIB_ENABLED ) */

        #if defined( SIXTRL_DEMOTRACK_ENABLED ) && \
                   ( SIXTRL_DEMOTRACK_ENABLED == 1 )
        demotrack_particle_type( ext_m, stpy::Add_c99_ns(
            "DemotrackParticle" ).c_str() ),
        #endif/* defined( SIXTRL_DEMOTRACK_ENABLED ) */
        m( ext_m )
    {

    }

    void InitHelper::init()
    {
        stpy::InitHelper_buffer_protocol( *this );
        stpy::InitHelper_common( *this );
        stpy::InitHelper_testlib( *this );
        stpy::InitHelper_demotrack( *this );
    }
}
}
