#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_XY_SHIFT_XY_SHIFT_INIT_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_XY_SHIFT_XY_SHIFT_INIT_H__


#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/xy_shift/xy_shift_api.h"
    #include "sixtracklib/common/internal/obj_store_traits.hpp"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
    #include "sixtracklib/common/internal/type_comparison_helpers.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class XYShiftT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BE_ARGPTR_DEC XYShiftT*
    XYShift_preset( SIXTRL_BE_ARGPTR_DEC XYShiftT* SIXTRL_RESTRICT elem )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::XYShift_is_type< XYShiftT >(),
            "XYShiftT required to be a xy-shift class" );

        if( elem != SIXTRL_NULLPTR )
        {
            st::arch_status_t status = st::XYShift_set_default_dx( elem );
            status |= st::XYShift_set_default_dy( elem );

            SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
            ( void )status;
        }

        return elem;
    }

    template< class XYShiftT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
    XYShift_init( SIXTRL_BE_ARGPTR_DEC XYShiftT* SIXTRL_RESTRICT elem )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return st::XYShift_set_default_dx( elem ) |
               st::XYShift_set_default_dy( elem );
    }

    template< class XYShiftT, typename DxArg, typename DyArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
    XYShift_init_detailed(
        SIXTRL_BE_ARGPTR_DEC XYShiftT* SIXTRL_RESTRICT elem,
        DxArg dx_value, DyArg dy_value )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return st::XYShift_set_dx( elem, dx_value ) |
               st::XYShift_set_dy( elem, dy_value );
    }

    template< class XYShiftT, typename DxArg, typename DyArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
    XYShift_init( SIXTRL_BE_ARGPTR_DEC XYShiftT* SIXTRL_RESTRICT elem,
        DxArg dx_value, DyArg dy_value )
    {
        return SIXTRL_CXX_NAMESPACE::XYShift_init_detailed(
            elem, dx_value, dy_value );
    }

    /* ********************************************************************* */

    template< class XYShiftT, store_backend_t StoreT >
    struct ObjDataInitialiser< XYShiftT, StoreT, typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::XYShift_is_type< XYShiftT >(), void >::type >
    {
        SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC XYShiftT* preset(
            SIXTRL_BE_ARGPTR_DEC XYShiftT* SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::XYShift_preset( obj );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t init(
            SIXTRL_BE_ARGPTR_DEC XYShiftT* SIXTRL_RESTRICT obj,
            Args&&... init_args )
        {
            return SIXTRL_CXX_NAMESPACE::XYShift_init(
                obj, std::forward< Args >( init_args )... );
        }
    };
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(XYShift)* NS(XYShift_preset)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(XYShift_init)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(XYShift_init_detailed)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const dx_value, NS(be_real_t) const dy_value
) SIXTRL_NOEXCEPT;

 #if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!!!        Inline Methods and Functions Implementations       !!!!!!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(XYShift)* NS(XYShift_preset)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    if( elem != SIXTRL_NULLPTR )
    {
        NS(arch_status_t) status  = NS(XYShift_set_default_dx)( elem );
        status |= NS(XYShift_set_default_dx)( elem );

        SIXTRL_ASSERT( status == ( NS(arch_status_t)
            )SIXTRL_ARCH_STATUS_SUCCESS );
    }

    return elem;
}

SIXTRL_INLINE NS(arch_status_t) NS(XYShift_init)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    return NS(XYShift_set_default_dx)( elem ) |
           NS(XYShift_set_default_dy)( elem );
}

SIXTRL_INLINE NS(arch_status_t) NS(XYShift_init_detailed)(
    SIXTRL_BE_ARGPTR_DEC NS(XYShift)* SIXTRL_RESTRICT elem,
    NS(be_real_t) const dx_value, NS(be_real_t) const dy_value ) SIXTRL_NOEXCEPT
{
    return NS(XYShift_set_dx)( elem, dx_value ) |
           NS(XYShift_set_dy)( elem, dy_value );
}

 #if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#endif /* C++ */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_XY_SHIFT_XY_SHIFT_INIT_H__ */
