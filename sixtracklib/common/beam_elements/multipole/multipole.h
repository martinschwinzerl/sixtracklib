#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_C99_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_C99_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #if defined( __cplusplus )
        #include <cmath>
    #endif /* defined( __cplusplus ) */
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/beam_elements/multipole/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( __GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( __GPUCODE ) && defined( __cplusplus ) */

typedef struct NS(Multipole)
{
    NS(be_order_t)   order    SIXTRL_ALIGN( 8 );
    NS(be_real_t)    length   SIXTRL_ALIGN( 8 );
    NS(be_real_t)    hxl      SIXTRL_ALIGN( 8 );
    NS(be_real_t)    hyl      SIXTRL_ALIGN( 8 );
    NS(be_address_t) bal_addr SIXTRL_ALIGN( 8 );
}
NS(Multipole);

SIXTRL_STATIC SIXTRL_FN NS(be_order_t) NS(Multipole_order)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const
        SIXTRL_RESTRICT multipole ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_order_t) NS(Multipole_bal_length)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const
        SIXTRL_RESTRICT multipole ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_t) NS(Multipole_length)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const
        SIXTRL_RESTRICT multipole ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_t) NS(Multipole_hxl)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const
        SIXTRL_RESTRICT multipole ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(be_real_t) NS(Multipole_hyl)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const
        SIXTRL_RESTRICT multipole ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(buffer_addr_t) NS(Multipole_bal_addr)(
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const
        SIXTRL_RESTRICT multipole ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_DATAPTR_DEC NS(be_real_t) const*
NS(Multipole_const_bal)( SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const
    SIXTRL_RESTRICT multipole ) SIXTRL_NOEXCEPT;

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

SIXTRL_STATIC SIXTRL_FN void NS(Multipole_set_order)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT multipole,
    NS(be_order_t) const order ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Multipole_set_bal_length)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT multipole,
    NS(be_order_t) const bal_length ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Multipole_set_length)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT multipole,
    NS(be_real_t) const length ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Multipole_set_hxl)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT multipole,
    NS(be_real_t) const hxl ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Multipole_set_hyl)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT multipole,
    NS(be_real_t) const hyl ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN void NS(Multipole_set_bal_addr)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT multipole,
    NS(buffer_addr_t) const bal_addr ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_DATAPTR_DEC
NS(be_real_t)* NS(Multipole_bal)( SIXTRL_BE_ARGPTR_DEC NS(Multipole)*
    SIXTRL_RESTRICT multipole) SIXTRL_NOEXCEPT;

#if !defined( __GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( __GPUCODE ) && defined( __cplusplus ) */

#if defined( __cplusplus )

namespace SIXTRL_CXX_NAMESPACE
{
    template<> struct MultipoleTraits< ::NS(Multipole) >
    {
        typedef ::NS(be_real_t)     real_t;
        typedef ::NS(be_order_t)    order_t;
        typedef ::NS(be_address_t)  address_t;

        static constexpr arch_size_t real_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< real_t >();

        static constexpr arch_size_t order_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< order_t >();

        static constexpr arch_size_t address_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< order_t >();
    };

    constexpr arch_size_t MultipoleTraits< ::NS(Multipole) >::real_alignment;
    constexpr arch_size_t MultipoleTraits< ::NS(Multipole) >::order_alignment;
    constexpr arch_size_t MultipoleTraits< ::NS(Multipole)>::address_alignment;
}

#endif /* defined( __cplusplus ) */

/* ------------------------------------------------------------------------- */

#if !defined( __GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( __GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE NS(be_order_t) NS(Multipole_order)( SIXTRL_BE_ARGPTR_DEC const
    NS(Multipole) *const SIXTRL_RESTRICT multipole ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( multipole != SIXTRL_NULLPTR );
    return multipole->order;
}

SIXTRL_INLINE NS(be_order_t) NS(Multipole_bal_length)( SIXTRL_BE_ARGPTR_DEC
    const NS(Multipole) *const SIXTRL_RESTRICT multipole ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( multipole != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( multipole->order >= 0 );
    return 2 * ( multipole->order + 1 );
}

SIXTRL_INLINE NS(be_real_t) NS(Multipole_length)( SIXTRL_BE_ARGPTR_DEC const
    NS(Multipole) *const SIXTRL_RESTRICT multipole ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( multipole != SIXTRL_NULLPTR );
    return multipole->length;
}

SIXTRL_INLINE NS(be_real_t) NS(Multipole_hxl)( SIXTRL_BE_ARGPTR_DEC const
    NS(Multipole) *const SIXTRL_RESTRICT multipole ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( multipole != SIXTRL_NULLPTR );
    return multipole->hxl;
}

SIXTRL_INLINE NS(be_real_t) NS(Multipole_hyl)( SIXTRL_BE_ARGPTR_DEC const
    NS(Multipole) *const SIXTRL_RESTRICT multipole ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( multipole != SIXTRL_NULLPTR );
    return multipole->hyl;
}

SIXTRL_INLINE NS(buffer_addr_t) NS(Multipole_bal_addr)( SIXTRL_BE_ARGPTR_DEC
    const NS(Multipole) *const SIXTRL_RESTRICT multipole ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( multipole != SIXTRL_NULLPTR );
    return multipole->bal_addr;
}

SIXTRL_INLINE SIXTRL_BE_DATAPTR_DEC NS(be_real_t) const*
NS(Multipole_const_bal)( SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const
    SIXTRL_RESTRICT multipole ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( multipole != SIXTRL_NULLPTR );
    return ( SIXTRL_BE_DATAPTR_DEC NS(be_real_t) const* )( uintptr_t
        )NS(Multipole_bal_addr)( multipole );
}

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

SIXTRL_INLINE void NS(Multipole_set_order)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT multipole,
    NS(be_order_t) const order ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( multipole != SIXTRL_NULLPTR );
    multipole->order = order;
}

SIXTRL_INLINE void NS(Multipole_set_bal_length)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT multipole,
    NS(be_order_t) const bal_length ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( multipole != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( ( bal_length > 0 ) && ( ( bal_length % 2 ) == 0 ) );
    multipole->order = ( bal_length / 2 ) - 1;
}

SIXTRL_INLINE void NS(Multipole_set_length)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT multipole,
    NS(be_real_t) const length ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( multipole != SIXTRL_NULLPTR );
    multipole->length = length;
}

SIXTRL_INLINE void NS(Multipole_set_hxl)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT multipole,
    NS(be_real_t) const hxl ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( multipole != SIXTRL_NULLPTR );
    multipole->hxl = hxl;
}

SIXTRL_INLINE void NS(Multipole_set_hyl)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT multipole,
    NS(be_real_t) const hyl ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( multipole != SIXTRL_NULLPTR );
    multipole->hyl = hyl;
}

SIXTRL_INLINE void NS(Multipole_set_bal_addr)(
    SIXTRL_BE_ARGPTR_DEC NS(Multipole)* SIXTRL_RESTRICT multipole,
    NS(buffer_addr_t) const bal_addr ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( multipole != SIXTRL_NULLPTR );
    multipole->bal_addr = bal_addr;
}

SIXTRL_INLINE SIXTRL_BE_DATAPTR_DEC
NS(be_real_t)* NS(Multipole_bal)( SIXTRL_BE_ARGPTR_DEC NS(Multipole)*
    SIXTRL_RESTRICT multipole) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( multipole != SIXTRL_NULLPTR );
    return ( SIXTRL_BE_DATAPTR_DEC NS(be_real_t)* )( uintptr_t
        )multipole->bal_addr;
}

#if !defined( __GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( __GPUCODE ) && defined( __cplusplus ) */

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_C99_H__ */
