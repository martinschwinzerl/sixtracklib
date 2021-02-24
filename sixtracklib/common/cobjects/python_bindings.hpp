#ifndef SIXTRACKLIB_COMMON_COBJECTS_PYTHON_BINDINGS_CXX_HPP__
#define SIXTRACKLIB_COMMON_COBJECTS_PYTHON_BINDINGS_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/definitions.h"
//     #include "sixtracklib/common/cobjects/cbuffer.h"
//     #include "sixtracklib/common/cobjects/cbuffer_view.hpp"
//     #include "sixtracklib/common/cobjects/cbuffer.hpp"
    #include "sixtracklib/common/cobjects/index_object.h"
    #include "sixtracklib/common/cobjects/garbage_range.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus )
    #include <pybind11/pybind11.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && C++ */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE {
namespace python {

struct SixTrackLibModuleVars;

struct SixTrackLibCommonCObjectsSubVars
{
    SIXTRL_HOST_FN explicit SixTrackLibCommonCObjectsSubVars(
        SixTrackLibModuleVars& vars );

    SIXTRL_HOST_FN SixTrackLibCommonCObjectsSubVars(
        SixTrackLibCommonCObjectsSubVars const& ) = delete;

    SIXTRL_HOST_FN SixTrackLibCommonCObjectsSubVars(
        SixTrackLibCommonCObjectsSubVars&& ) = delete;

    SIXTRL_HOST_FN SixTrackLibCommonCObjectsSubVars& operator=(
        SixTrackLibCommonCObjectsSubVars const& ) = delete;

    SIXTRL_HOST_FN SixTrackLibCommonCObjectsSubVars& operator=(
        SixTrackLibCommonCObjectsSubVars&& ) = delete;

    SIXTRL_HOST_FN virtual ~SixTrackLibCommonCObjectsSubVars() = default;

    /* --------------------------------------------------------------------- */

    SIXTRL_HOST_FN void init( SixTrackLibModuleVars& SIXTRL_RESTRICT_REF vars );

    SIXTRL_HOST_FN void init_cobj_index_type(
        SixTrackLibModuleVars& SIXTRL_RESTRICT_REF vars );

    SIXTRL_HOST_FN void init_cobj_garbage_range_type(
        SixTrackLibModuleVars& SIXTRL_RESTRICT_REF vars );

    /* --------------------------------------------------------------------- */

//     pybind11::class_< ::NS(CBuffer)          > c99_cbuffer_type;
    pybind11::class_< ::NS(CObjIndex)        > cobj_index_type;
    pybind11::class_< ::NS(CObjGarbageRange) > cobj_garbage_range_type;

//     pybind11::class_< SIXTRL_CXX_NAMESPACE::CBufferView > cbuffer_view_type;
//     pybind11::class_< SIXTRL_CXX_NAMESPACE::CBuffer >     cbuffer_type;
};

} /* end: namespace python */
} /* end: namespace SIXTRL_CXX_NAMESPACE */

#endif /* C++, Host */
#endif /* SIXTRACKLIB_COMMON_COBJECTS_PYTHON_BINDINGS_CXX_HPP__ */
