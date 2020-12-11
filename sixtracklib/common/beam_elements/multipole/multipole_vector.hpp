#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_MULTIPOLE_VECTOR_CXX_HPP__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_MULTIPOLE_VECTOR_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/beam_elements/multipole/definitions.h"
    #include "sixtracklib/common/beam_elements/multipole/multipole.h"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
    #include "sixtracklib/common/internal/type_annotations.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <algorithm>
    #include <type_traits>
    #include <vector>
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template< class R, class O,
              SIXTRL_CXX_NAMESPACE::arch_size_t RAlign =
                    SIXTRL_CXX_NAMESPACE::Type_storage_align< R >(),
              SIXTRL_CXX_NAMESPACE::arch_size_t OAlign =
                    SIXTRL_CXX_NAMESPACE::Type_storage_align< O >(),
              class Alloc = std::allocator< R > >
    struct SIXTRL_ANNOTATE_COBJECT SIXTRL_ANNOTATE_ELEM_OBJ
    SIXTRL_ANNOTATE_ELEM_OBJ_DEC( "SIXTRL_BE_ARGPTR_DEC" )
    TVectorMultipole
    {
        O order  SIXTRL_ALIGN( OAlign )
                 SIXTRL_ANNOTATE_ELEM_FIELD_REQU_INIT
                 SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

        R length SIXTRL_ALIGN( RAlign )
                 SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

        R hxl    SIXTRL_ALIGN( RAlign )
                 SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

        R hyl    SIXTRL_ALIGN( RAlign )
                 SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

        std::vector< R, Alloc > bal_values;
    };

    /* ********************************************************************* */
    /* Specializations for TMultipole: */
    /* ********************************************************************* */

    template< class R, class O, arch_size_t RAlign, arch_size_t OAlign,
              class Alloc >
    struct ObjDataMultipoleTraits< TVectorMultipole<
        R, O, RAlign, OAlign, Alloc > >
    {
        static constexpr bool is_type = true;
        static constexpr be_multipole_impl_t implementation =
            SIXTRL_CXX_NAMESPACE::BE_MULTIPOLE_IMPL_STD_VECTOR;
    };

    template< class R, class O, arch_size_t RAlign, arch_size_t OAlign,
              class Alloc >
    constexpr bool ObjDataMultipoleTraits<
        TVectorMultipole< R, O, RAlign, OAlign, Alloc > >::is_type;

    template< class R, class O, arch_size_t RAlign, arch_size_t OAlign,
              class Alloc >
    constexpr be_multipole_impl_t ObjDataMultipoleTraits<
        TVectorMultipole< R, O, RAlign, OAlign, Alloc > >::implementation;

    typedef TVectorMultipole<
            MultipoleTraits< ::NS(Multipole) >::real_t,
            MultipoleTraits< ::NS(Multipole) >::order_t,
            MultipoleTraits< ::NS(Multipole) >::real_alignment,
            MultipoleTraits< ::NS(Multipole) >::order_alignment,
            std::allocator< MultipoleTraits< ::NS(Multipole) >::real_t > >
            VecMultipole;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class R, class O, arch_size_t RAlign, arch_size_t OAlign,
              class Alloc >
    struct MultipoleTraits< TVectorMultipole< R, O, RAlign, OAlign, Alloc > >
    {
        typedef typename TypeMethodParamTraits< R >::value_type real_t;
        typedef typename TypeMethodParamTraits< O >::value_type order_t;
        typedef std::vector< real_t, Alloc > bal_values_t;

        static constexpr arch_size_t real_alignment = RAlign;
        static constexpr arch_size_t order_alignment = OAlign;
    };

    template< class R, class O, arch_size_t RAlign, arch_size_t OAlign,
              class Alloc >
    constexpr arch_size_t MultipoleTraits< TVectorMultipole<
        R, O, RAlign, OAlign, Alloc > >::real_alignment;

    template< class R, class O, arch_size_t RAlign, arch_size_t OAlign,
              class Alloc >
    constexpr arch_size_t MultipoleTraits< TVectorMultipole<
        R, O, RAlign, OAlign, Alloc > >::order_alignment;

    /* ********************************************************************* */

    template< class MultipoleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Multipole_is_type< MultipoleT >() &&
        SIXTRL_CXX_NAMESPACE::Multipole_impl_std_vector< MultipoleT >(),
        typename MultipoleTraits< MultipoleT >::order_t >::type
    Multipole_bal_capacity( SIXTRL_BE_ARGPTR_DEC const MultipoleT *const
        SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
    {
        typedef typename MultipoleTraits< MultipoleT >::order_t order_t;
        SIXTRL_ASSERT(  elem != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( !elem->bal_values.empty() );
        SIXTRL_ASSERT(  elem->bal_values.size() % 2u == 0u );
        SIXTRL_ASSERT(  elem->order >= order_t{ 0 } );
        SIXTRL_ASSERT(  static_cast< order_t >( elem->bal_values.size() ) >=
                        ( 2 * elem->order + 2 ) );

        return static_cast< order_t >( elem->bal_values.size() );
    }

    template< class MultipoleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Multipole_is_type< MultipoleT >() &&
        SIXTRL_CXX_NAMESPACE::Multipole_impl_std_vector< MultipoleT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Multipole_set_bal_capacity(
        SIXTRL_BE_ARGPTR_DEC MultipoleT* SIXTRL_RESTRICT elem,
        typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
            SIXTRL_CXX_NAMESPACE::MultipoleTraits< MultipoleT >::order_t
                >::const_argument_type new_capacity )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename st::MultipoleTraits< MultipoleT >::order_t order_t;

        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( elem != SIXTRL_NULLPTR )
        {
            order_t current_capacity = elem->bal_values.size();

            if( new_capacity >= current_capacity )
            {
                typename MultipoleTraits< MultipoleT >::bal_values_t
                    new_bal_values( new_capacity, typename st::MultipoleTraits<
                        MultipoleT >::real_t{ 0 } );

                std::copy( elem->bal_values.begin(), elem->bal_values.end(),
                           new_bal_values.begin() );

                current_capacity = new_bal_values.size();
                elem->bal_values.swap( new_bal_values );
            }

            if( new_capacity <= current_capacity )
            {
                status = st::ARCH_STATUS_SUCCESS;
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

     template< class MultipoleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Multipole_is_type< MultipoleT >() &&
        SIXTRL_CXX_NAMESPACE::Multipole_impl_std_vector< MultipoleT >(),
        SIXTRL_CXX_NAMESPACE::be_address_t >::type
    Multipole_bal_addr( SIXTRL_BE_ARGPTR_DEC const MultipoleT *const
        SIXTRL_RESTRICT elem ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return ( elem != SIXTRL_NULLPTR )
            ? static_cast< st::be_address_t >( reinterpret_cast<
                std::uintptr_t >( elem->bal_values.data() ) )
            : st::be_address_t{ 0 };
    }

    template< class MultipoleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Multipole_is_type< MultipoleT >() &&
        SIXTRL_CXX_NAMESPACE::Multipole_impl_std_vector< MultipoleT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Multipole_set_bal_addr(
        SIXTRL_BE_ARGPTR_DEC MultipoleT* SIXTRL_RESTRICT /*elem*/,
        SIXTRL_CXX_NAMESPACE::be_address_t const bal_addr ) SIXTRL_NOEXCEPT
    {
        return ( bal_addr == SIXTRL_CXX_NAMESPACE::be_address_t{ 0 } )
            ? SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS
            : SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }
}

#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/multipole/multipole_api.h"
#endif /* C++, Host, !defined( SIXTRL_NO_INCLUDES ) */

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_MULTIPOLE_VECTOR_CXX_HPP__*/
