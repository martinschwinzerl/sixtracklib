#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_MULTIPOLE_INIT_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_MULTIPOLE_INIT_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/multipole/multipole_api.h"
    #include "sixtracklib/common/internal/obj_addr_based_pointer_field.h"
    #include "sixtracklib/common/internal/obj_store_traits.hpp"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
    #include "sixtracklib/common/internal/type_comparison_helpers.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <type_traits>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template< class MultipoleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BE_ARGPTR_DEC MultipoleT*
    Multipole_preset( SIXTRL_BE_ARGPTR_DEC MultipoleT* SIXTRL_RESTRICT elem )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::Multipole_is_type< MultipoleT >(),
            "MultipoleT is required to be a multipole class" );

        if( elem != SIXTRL_NULLPTR )
        {
            st::arch_status_t status = st::ARCH_STATUS_SUCCESS;
            status |= st::Multipole_set_default_order( elem );
            status |= st::Multipole_set_default_length( elem );
            status |= st::Multipole_set_default_hxl( elem );
            status |= st::Multipole_set_default_hyl( elem );
            status |= st::Multipole_set_default_bal_addr( elem );
            status |= st::Multipole_set_default_bal_capacity( elem );

            SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
            ( void )status;
        }

        return elem;
    }

    template< class MultipoleT >
    SIXTRL_STATIC SIXTRL_FN arch_status_t Multipole_init(
        SIXTRL_BE_ARGPTR_DEC MultipoleT* SIXTRL_RESTRICT elem,
        typename TypeMethodParamTraits< typename MultipoleTraits<
            MultipoleT >::order_t >::const_argument_type order,
        typename MultipoleTraits< MultipoleT >::order_t bal_capacity =
            typename MultipoleTraits< MultipoleT >::order_t{ 2 } )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename st::MultipoleTraits< MultipoleT >::order_t order_t;

        static_assert( st::Multipole_is_type< MultipoleT >(),
                       "MultipoleT is required to be a multipole class" );

        SIXTRL_ASSERT( elem != SIXTRL_NULLPTR );
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( order >= order_t{ 0 } )
        {
            order_t const requ_capacity = order_t{ 2 }  * order + order_t{ 2 };
            if( bal_capacity < requ_capacity ) bal_capacity = requ_capacity;

            status  = st::Multipole_set_order( elem, order );
            status |= st::Multipole_set_bal_capacity( elem, bal_capacity );
            status |= st::Multipole_set_default_length( elem );
            status |= st::Multipole_set_default_hxl( elem );
            status |= st::Multipole_set_default_hyl( elem );
            status |= st::Multipole_set_default_bal_addr( elem );
        }

        return status;
    }

    template< class MultipoleT, typename LengthArg,
              typename HxlArg, typename HylArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t
    Multipole_init_detailed(
        SIXTRL_BE_ARGPTR_DEC MultipoleT* SIXTRL_RESTRICT elem,
        typename TypeMethodParamTraits< typename MultipoleTraits< MultipoleT
            >::order_t >::const_argument_type order,
        LengthArg length, HxlArg hxl, HylArg hyl,
        TypeMethodParamTraits< be_address_t >::const_argument_type bal_addr =
            be_address_t{ 0 },
        typename MultipoleTraits< MultipoleT >::order_t bal_capacity =
            typename MultipoleTraits< MultipoleT >::order_t{ 2 } )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename st::MultipoleTraits< MultipoleT >::order_t order_t;
        static_assert( st::Multipole_is_type< MultipoleT >(),
                       "MultipoleT is required to be a multipole class" );

        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( elem != SIXTRL_NULLPTR ) && ( order >= order_t{ 0 } ) )
        {
            order_t const requ_capacity = order_t{ 2 } * order + order_t{ 2 };
            if( requ_capacity > bal_capacity ) bal_capacity = requ_capacity;

            status  = st::Multipole_set_order( elem, order );
            status |= st::Multipole_set_bal_capacity( elem, bal_capacity );
            status |= st::Multipole_set_length( elem, length );
            status |= st::Multipole_set_hxl( elem, hxl );
            status |= st::Multipole_set_hyl( elem, hyl );
            status |= st::Multipole_set_bal_addr( elem, bal_addr );
        }

        return status;
    }

    template< class MultipoleT, typename LengthArg,
              typename HxlArg, typename HylArg >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t Multipole_init(
        SIXTRL_BE_ARGPTR_DEC MultipoleT* SIXTRL_RESTRICT elem,
        typename TypeMethodParamTraits< typename MultipoleTraits< MultipoleT
            >::order_t >::const_argument_type order,
        LengthArg length, HxlArg hxl, HylArg hyl,
        TypeMethodParamTraits< be_address_t >::const_argument_type bal_addr =
            be_address_t{ 0 },
        typename MultipoleTraits< MultipoleT >::order_t bal_capacity =
            typename MultipoleTraits< MultipoleT >::order_t{ 2 } )
    {
        return SIXTRL_CXX_NAMESPACE::Multipole_init_detailed(
            elem, order, length, hxl, hyl, bal_addr, bal_capacity );
    }

    /* ********************************************************************* */

    template< class MultipoleT, store_backend_t StoreT >
    struct ObjDataInitialiser< MultipoleT, StoreT, typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Multipole_is_type< MultipoleT >(), void >::type >
    {
        SIXTRL_STATIC SIXTRL_FN void preset( SIXTRL_BE_ARGPTR_DEC MultipoleT*
            SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
        {
            SIXTRL_CXX_NAMESPACE::Multipole_preset( obj );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t init(
            SIXTRL_BE_ARGPTR_DEC MultipoleT* SIXTRL_RESTRICT obj,
            Args&&... init_args )
        {
            return SIXTRL_CXX_NAMESPACE::Multipole_init(
                obj, std::forward< Args >( init_args )... );
        }
    };
}

/* init API: */

template< class MultipoleT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BE_ARGPTR_DEC MultipoleT*
NS(Multipole_preset)( SIXTRL_BE_ARGPTR_DEC MultipoleT* SIXTRL_RESTRICT elem )
{
    return SIXTRL_CXX_NAMESPACE::Multipole_preset( elem );
}

template< class MultipoleT, typename OrderArg >
SIXTRL_STATIC SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t NS(Multipole_init)(
    SIXTRL_BE_ARGPTR_DEC MultipoleT* SIXTRL_RESTRICT elem, OrderArg order )
{
    return SIXTRL_CXX_NAMESPACE::Multipole_init( elem, order );
}

template< class MultipoleT, typename OrderArg, typename LengthArg,
          typename HxlArg, typename HylArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Multipole_init_detailed)(
    SIXTRL_BE_ARGPTR_DEC MultipoleT* SIXTRL_RESTRICT elem,
    OrderArg order, LengthArg length, HxlArg hxl, HylArg hyl,
    SIXTRL_CXX_NAMESPACE::be_address_t bal_addr =
        SIXTRL_CXX_NAMESPACE::be_address_t{ 0 },
    typename SIXTRL_CXX_NAMESPACE::MultipoleTraits<
        MultipoleT >::order_t bal_capacity = typename
            SIXTRL_CXX_NAMESPACE::MultipoleTraits< MultipoleT >::order_t{ 2 } )
{
    return SIXTRL_CXX_NAMESPACE::Multipole_init_detailed(
        elem, order, length, hxl, hyl, bal_addr, bal_capacity );
}

template< typename MultipoleT, typename OrderArg, typename LengthArg,
          typename HxlArg, typename HylArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Multipole_init)(
    SIXTRL_BE_ARGPTR_DEC MultipoleT* SIXTRL_RESTRICT elem,
    OrderArg order, LengthArg length, HxlArg hxl, HylArg hyl,
    SIXTRL_CXX_NAMESPACE::be_address_t const bal_addr =
        SIXTRL_CXX_NAMESPACE::be_address_t{ 0 },
    typename SIXTRL_CXX_NAMESPACE::MultipoleTraits<
        MultipoleT >::order_t bal_capacity = typename
            SIXTRL_CXX_NAMESPACE::MultipoleTraits< MultipoleT >::order_t{ 2 } )
{
    return SIXTRL_CXX_NAMESPACE::Multipole_init_detailed(
        elem, order, length, hxl, hyl, bal_addr, bal_capacity );
}

#endif /* C++ */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(Multipole)*
NS(Multipole_preset)( SIXTRL_BE_ARGPTR_DEC NS(Multipole)*
    SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Multipole_init)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT elem,
    NS(be_order_t) const order ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Multipole_init_detailed)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT elem,
    NS(be_order_t) const order, NS(be_real_t) const length,
    NS(be_real_t) const hxl, NS(be_real_t) const hyl,
    NS(be_address_t) const bal_addr,
    NS(be_order_t) bal_capacity ) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!        Implementation of inline methods / functions            !!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(Multipole)*
NS(Multipole_preset)( SIXTRL_BE_ARGPTR_DEC NS(Multipole)*
    SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
{
    if( elem != SIXTRL_NULLPTR )
    {
        NS(arch_status_t) status = ( NS(arch_status_t)
            )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

        status  = NS(Multipole_set_default_order)( elem );
        status |= NS(Multipole_set_default_bal_capacity)( elem );
        status |= NS(Multipole_set_default_length)( elem );
        status |= NS(Multipole_set_default_hxl)( elem );
        status |= NS(Multipole_set_default_hyl)( elem );
        status |= NS(Multipole_set_default_bal_addr)( elem );

        SIXTRL_ASSERT( status == (
            NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS );
        ( void )status;
    }

    return elem;
}

SIXTRL_INLINE NS(arch_status_t) NS(Multipole_init)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT elem,
    NS(be_order_t) const order ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = (
        NS(arch_status_t) )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    if( ( elem != SIXTRL_NULLPTR ) && ( order >= ( NS(be_order_t) )0 ) )
    {
        NS(be_order_t) const requ_capacity =
            ( NS(be_order_t) )2 * order + ( NS(be_order_t) )2;

        status  = NS(Multipole_set_order)( elem, order );
        status |= NS(Multipole_set_bal_capacity)( elem, requ_capacity );
        status |= NS(Multipole_set_default_length)( elem );
        status |= NS(Multipole_set_default_hxl)( elem );
        status |= NS(Multipole_set_default_hyl)( elem );
        status |= NS(Multipole_set_default_bal_addr)( elem );
    }

    return status;
}

SIXTRL_INLINE  NS(arch_status_t) NS(Multipole_init_detailed)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT elem,
    NS(be_order_t) const order, NS(be_real_t) const length,
    NS(be_real_t) const hxl, NS(be_real_t) const hyl,
    NS(be_address_t) const bal_addr,
    NS(be_order_t) bal_capacity ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = (
        NS(arch_status_t) )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    if( ( elem != SIXTRL_NULLPTR ) && ( order >= ( NS(be_order_t) )0 ) )
    {
        NS(be_order_t) const requ_capacity =
            ( NS(be_order_t) )2 * order + ( NS(be_order_t) )2;

        if( requ_capacity > bal_capacity ) bal_capacity = requ_capacity;
        status  = NS(Multipole_set_order)( elem, order );
        status |= NS(Multipole_set_bal_capacity)( elem, bal_capacity );
        status |= NS(Multipole_set_length)( elem, length );
        status |= NS(Multipole_set_hxl)( elem, hxl );
        status |= NS(Multipole_set_hyl)( elem, hyl );
        status |= NS(Multipole_set_bal_addr)( elem, bal_addr );
    }

    return status;
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_MULTIPOLE_INIT_H__ */
