#ifndef SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SET_HELPER_API_H__
#define SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SET_HELPER_API_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles/definitions.h"
    #include "sixtracklib/common/particles/particle_set.h"
    #include "sixtracklib/common/cobjects/definitions.h"

    #if defined( __cplusplus )
        #include "sixtracklib/common/internal/obj_c_api_traits.hpp"
    #endif /* defined( __cplusplus ) */
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <algorithm>
    #include <iterator>
    #include <memory>
    #include <vector>
    #include <type_traits>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        template< class PSetT >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN particle_addr_t
        ParticleSet_default_field_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC const
            PSetT *const SIXTRL_RESTRICT /* p */ ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            static_assert( st::ParticleSet_is_type< PSetT >(),
               "PSetT required to be a particle set class" );
            return st::particle_addr_t{ 0 };
        }

        template< class PSetT >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t
        ParticleSet_set_default_field_addr(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* SIXTRL_RESTRICT p,
            particle_addr_t& SIXTRL_RESTRICT_REF field_addr ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            static_assert( st::ParticleSet_is_type< PSetT >(),
                "PSetT required to be a particle set class" );

            field_addr = st::ParticleSet_default_field_addr< PSetT >( p );
            return st::ARCH_STATUS_SUCCESS;
        }

        template< class PSetT >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t
        ParticleSet_set_field_addr(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* SIXTRL_RESTRICT /*p*/,
            particle_addr_t& SIXTRL_RESTRICT_REF dest_field_addr,
            particle_addr_t const new_addr_value ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            static_assert( st::ParticleSet_is_type< PSetT >(),
                "Requires PSetT to be a particle set class" );

            dest_field_addr = new_addr_value;
            return st::ARCH_STATUS_SUCCESS;
        }

        /* ================================================================= */

        template< class PSetT >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
            !SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >(),
            SIXTRL_PARTICLE_SET_DATAPTR_DEC typename TypeMethodParamTraits<
                typename ParticleSetTraits< PSetT >::real_t
                    >::const_pointer >::type
        ParticleSet_const_real_begin_for_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC
                const PSetT *const SIXTRL_RESTRICT /*pset*/,
            particle_addr_t const /*addr*/ ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_NULLPTR;
        }

        template< class PSetT >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >(),
            SIXTRL_PARTICLE_SET_DATAPTR_DEC typename TypeMethodParamTraits<
                typename ParticleSetTraits< PSetT >::real_t
                    >::const_pointer >::type
        ParticleSet_const_real_begin_for_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC
                const PSetT *const SIXTRL_RESTRICT /*pset*/,
            particle_addr_t const addr ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            typedef typename st::ParticleSetTraits< PSetT >::real_t real_t;
            typedef SIXTRL_PARTICLE_SET_DATAPTR_DEC typename
                        TypeMethodParamTraits< real_t >::const_pointer ptr_t;
            typedef std::uintptr_t uint_t;

            return reinterpret_cast< ptr_t >( static_cast< uint_t >( addr ) );
        }

        template< class PSetT >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_PARTICLE_SET_DATAPTR_DEC
            typename TypeMethodParamTraits< typename ParticleSetTraits<
                PSetT >::real_t >::const_pointer
        ParticleSet_const_real_end_for_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC
                const PSetT *const SIXTRL_RESTRICT pset,
            particle_addr_t const addr,
            particle_num_elements_t const length ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            SIXTRL_ASSERT( length >= particle_num_elements_t{ 0 } );
            auto ptr = st::ParticleSet_const_real_begin_for_addr( pset, addr );

            if( ( ptr != SIXTRL_NULLPTR ) &&
                ( length >= particle_num_elements_t{ 0 } ) )
            {
                ptr = ptr + length;
            }

            return ptr;
        }

        template< class PSetT >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_PARTICLE_SET_DATAPTR_DEC
            typename TypeMethodParamTraits< typename ParticleSetTraits<
                PSetT >::real_t >::pointer
        ParticleSet_real_begin_for_addr(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* SIXTRL_RESTRICT pset,
            particle_addr_t const addr ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            typedef typename ParticleSetTraits< PSetT >::real_t real_t;
            typedef SIXTRL_PARTICLE_SET_DATAPTR_DEC typename
                    TypeMethodParamTraits< real_t >::pointer ptr_t;

            return const_cast< ptr_t >(
                st::ParticleSet_const_real_begin_for_addr< PSetT >(
                    pset, addr ) );
        }

        template< class PSetT >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_PARTICLE_SET_DATAPTR_DEC
            typename TypeMethodParamTraits< typename ParticleSetTraits<
                PSetT >::real_t >::pointer
        ParticleSet_real_end_for_addr(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* SIXTRL_RESTRICT pset,
            particle_addr_t const addr,
            particle_num_elements_t const length ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            typedef typename st::ParticleSetTraits< PSetT >::real_t real_t;
            typedef SIXTRL_PARTICLE_SET_DATAPTR_DEC typename
                    st::TypeMethodParamTraits< real_t >::pointer ptr_t;

            return const_cast< ptr_t >( st::ParticleSet_const_real_end_for_addr<
                PSetT >( pset, addr, length ) );
        }

        /* ----------------------------------------------------------------- */

        template< class PSetT >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
            !SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >(),
            typename ParticleSetTraits< PSetT >::real_t >::type
        ParticleSet_get_real_value_from_addr(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC const PSetT *const
                SIXTRL_RESTRICT /* pset */,
            particle_addr_t const /* addr */,
            particle_num_elements_t const /* length */,
            particle_num_elements_t const /* idx */ ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            static_assert( st::ParticleSet_is_type< PSetT >(),
                "PSetT required to be a particle set class" );
            return typename st::ParticleSetTraits< PSetT >::real_t{ 0 };
        }

        template< class PSetT >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
            SIXTRL_CXX_NAMESPACE::ParticleSet_impl_has_field_addr< PSetT >(),
            typename TypeMethodParamTraits< typename ParticleSetTraits<
                PSetT >::real_t >::const_existing_type >::type
        ParticleSet_get_real_value_from_addr(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC const PSetT *const
                SIXTRL_RESTRICT pset,
            particle_addr_t const addr, particle_num_elements_t const length,
            particle_num_elements_t const idx ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            auto ptr = st::ParticleSet_const_real_begin_for_addr( pset, addr );
            SIXTRL_ASSERT( ptr != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( idx < length );
            ( void )length;

            return ptr[ idx ];
        }

        /* ----------------------------------------------------------------- */

        template< class PSetT, typename RealArg >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
            !SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >(),
            arch_status_t >::type
        ParticleSet_set_real_value_for_addr(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* SIXTRL_RESTRICT /* pset */,
            particle_addr_t const /* addr */,
            particle_num_elements_t const /* length */,
            particle_num_elements_t const /* idx */,
            RealArg /* value */ ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
        }

        template< class PSetT, typename RealArg >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
            SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< RealArg,
                typename ParticleSetTraits< PSetT >::real_t >(),
                arch_status_t >::type
        ParticleSet_set_real_value_for_addr(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* SIXTRL_RESTRICT pset,
            particle_addr_t const addr, particle_num_elements_t const length,
            particle_num_elements_t const idx, RealArg value )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            auto ptr = st::ParticleSet_real_begin_for_addr( pset, addr );

            SIXTRL_ASSERT( ptr != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( idx < length );
            ( void )length;

            ptr[ idx ] = value;
            return st::ARCH_STATUS_SUCCESS;
        }

        template< class PSetT, typename RealArg >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
            !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< RealArg,
                typename ParticleSetTraits< PSetT >::real_t >() &&
            SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable< RealArg,
                typename ParticleSetTraits< PSetT >::real_t >(),
                arch_status_t >::type
        ParticleSet_set_real_value_for_addr(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* SIXTRL_RESTRICT pset,
            particle_addr_t const addr, particle_num_elements_t const length,
            particle_num_elements_t const idx, RealArg value )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            auto ptr = st::ParticleSet_real_begin_for_addr( pset, addr );

            SIXTRL_ASSERT( ptr != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( idx >= st::particle_num_elements_t{ 0 } );
            SIXTRL_ASSERT( idx < length );
            ( void )length;

            ptr[ idx ] = std::move( value );
            return st::ARCH_STATUS_SUCCESS;
        }

        template< class PSetT, typename RealArg >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
            !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< RealArg,
                typename ParticleSetTraits< PSetT >::real_t >() &&
            !SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable< RealArg,
                typename ParticleSetTraits< PSetT >::real_t >(),
            arch_status_t >::type
        ParticleSet_set_real_value_for_addr(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* SIXTRL_RESTRICT pset,
            particle_addr_t const addr, particle_num_elements_t const length,
            particle_num_elements_t const idx, RealArg value )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            auto ptr = st::ParticleSet_real_begin_for_addr( pset, addr );

            SIXTRL_ASSERT( ptr != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( idx >= st::particle_num_elements_t{ 0 } );
            SIXTRL_ASSERT( idx < length );
            ( void )length;

            return st::Types_perform_assignment< typename std::decay< RealArg
                >::type, typename ParticleSetTraits< PSetT >::real_t >(
                    ptr[ idx ], value );
        }

        /* ----------------------------------------------------------------- */

        template< class PSetT, typename RealArg >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
            !SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >(),
            arch_status_t >::type
        ParticleSet_set_all_real_values_for_addr(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* SIXTRL_RESTRICT /*pset*/,
            particle_addr_t const /* addr */,
            particle_num_elements_t const /* length */,
            RealArg /* value */ ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
        }

        template< class PSetT, typename RealArg >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
            ( SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< RealArg,
                typename ParticleSetTraits< PSetT >::real_t >() ||
              SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable< RealArg,
                typename ParticleSetTraits< PSetT >::real_t >() ),
            arch_status_t >::type
        ParticleSet_set_all_real_values_for_addr(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* SIXTRL_RESTRICT pset,
            particle_addr_t const addr,
            particle_num_elements_t const length, RealArg value )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            auto it = st::ParticleSet_real_begin_for_addr( pset, addr );
            auto end_ptr = st::ParticleSet_real_end_for_addr(
                pset, addr, length );

            st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

            if( ( it != SIXTRL_NULLPTR ) && ( end_ptr != SIXTRL_NULLPTR ) )
            {
                for( ; it != end_ptr ; ++it ) *it = value;
                status = st::ARCH_STATUS_SUCCESS;
            }

            return status;
        }

        template< class PSetT, typename RealArg >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
            !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< RealArg,
                typename ParticleSetTraits< PSetT >::real_t >() &&
            !SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable< RealArg,
                typename ParticleSetTraits< PSetT >::real_t >(),
            arch_status_t >::type
        ParticleSet_set_all_real_values_for_addr(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* SIXTRL_RESTRICT pset,
            particle_addr_t const addr,
            particle_num_elements_t const length, RealArg value )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            auto it = st::ParticleSet_real_begin_for_addr( pset, addr );
            auto end_ptr = st::ParticleSet_real_end_for_addr(
                pset, addr, length );

            st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

            if( ( it != SIXTRL_NULLPTR ) && ( end_ptr != SIXTRL_NULLPTR ) )
            {
                status = st::ARCH_STATUS_SUCCESS;
                for( ; it != end_ptr ; ++it )
                {
                    status |= st::Types_perform_assignment< typename std::decay<
                        RealArg >::type, typename ParticleSetTraits<
                            PSetT >::real_t >( *it, value );
                }
            }

            return status;
        }

        /* ----------------------------------------------------------------- */

        template< class PSetT, typename RealIter >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
            !SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >(),
            arch_status_t >::type
        ParticleSet_set_real_values_for_addr(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* SIXTRL_RESTRICT /*pset*/,
            particle_addr_t const /* addr */,
            particle_num_elements_t const /* length */,
            RealIter /* values_begin */ ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
        }

        template< class PSetT, typename RealIter >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
            SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
                typename std::iterator_traits< RealIter >::value_type,
                typename ParticleSetTraits< PSetT >::real_t >(),
            arch_status_t >::type
        ParticleSet_set_real_values_for_addr(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* SIXTRL_RESTRICT pset,
            particle_addr_t const addr, particle_num_elements_t const length,
            RealIter values_it )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            auto it = st::ParticleSet_real_begin_for_addr( pset, addr );
            auto end_ptr = st::ParticleSet_real_end_for_addr(
                pset, addr, length );

            st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

            if( ( it != SIXTRL_NULLPTR ) && ( end_ptr != SIXTRL_NULLPTR ) )
            {
                for( ; it != end_ptr ; ++it, ++values_it ) *it = *values_it;
                status = st::ARCH_STATUS_SUCCESS;
            }

            return status;
        }

        template< class PSetT, typename RealIter >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
            SIXTRL_CXX_NAMESPACE::ParticleSet_impl_has_field_addr< PSetT >() &&
            !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
                typename std::iterator_traits< RealIter >::value_type,
                typename ParticleSetTraits< PSetT >::real_t >(),
            arch_status_t >::type
        ParticleSet_set_real_values_for_addr(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* SIXTRL_RESTRICT pset,
            particle_addr_t const addr, particle_num_elements_t const length,
            RealIter values_it )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            auto it = st::ParticleSet_real_begin_for_addr( pset, addr );
            auto end_ptr = st::ParticleSet_real_end_for_addr(
                pset, addr, length );

            st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

            if( ( it != SIXTRL_NULLPTR ) && ( end_ptr != SIXTRL_NULLPTR ) )
            {
                typedef typename ParticleSetTraits< PSetT >::real_t real_t;
                typedef typename std::iterator_traits< RealIter >::value_type
                    src_real_t;

                status = st::ARCH_STATUS_SUCCESS;
                for( ; it != end_ptr ; ++it, ++values_it )
                {
                    status |= st::Types_perform_assignment<
                        src_real_t, real_t >( *it, *values_it );
                }
            }

            return status;
        }

        /* ================================================================= */

        template< class PSetT >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
            !SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >(),
            SIXTRL_PARTICLE_SET_DATAPTR_DEC typename TypeMethodParamTraits<
                typename ParticleSetTraits< PSetT >::index_t
                    >::const_pointer >::type
        ParticleSet_const_index_begin_for_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC
                const PSetT *const SIXTRL_RESTRICT /*pset*/,
            particle_addr_t const /*addr*/ ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_NULLPTR;
        }

        template< class PSetT >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >(),
            SIXTRL_PARTICLE_SET_DATAPTR_DEC typename TypeMethodParamTraits<
                typename ParticleSetTraits< PSetT >::index_t
                    >::const_pointer >::type
        ParticleSet_const_index_begin_for_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC
                const PSetT *const SIXTRL_RESTRICT /*pset*/,
            particle_addr_t const addr ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            typedef typename st::ParticleSetTraits< PSetT >::index_t index_t;
            typedef SIXTRL_PARTICLE_SET_DATAPTR_DEC typename
                        TypeMethodParamTraits< index_t >::const_pointer ptr_t;
            typedef std::uintptr_t uint_t;

            return reinterpret_cast< ptr_t >( static_cast< uint_t >( addr ) );
        }

        template< class PSetT >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_PARTICLE_SET_DATAPTR_DEC
            typename TypeMethodParamTraits< typename ParticleSetTraits<
                PSetT >::index_t >::const_pointer
        ParticleSet_const_index_end_for_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC
                const PSetT *const SIXTRL_RESTRICT pset,
            particle_addr_t const addr,
            particle_num_elements_t const length ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            SIXTRL_ASSERT( length >= particle_num_elements_t{ 0 } );

            auto ptr  = st::ParticleSet_const_index_begin_for_addr( pset, addr );
            if( ( ptr != SIXTRL_NULLPTR ) &&
                ( length >= st::particle_num_elements_t{ 0 } ) )
            {
                ptr = ptr + length;
            }

            return ptr;
        }

        template< class PSetT >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_PARTICLE_SET_DATAPTR_DEC
            typename TypeMethodParamTraits< typename ParticleSetTraits<
                PSetT >::index_t >::pointer
        ParticleSet_index_begin_for_addr(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* SIXTRL_RESTRICT pset,
            particle_addr_t const addr ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            typedef typename ParticleSetTraits< PSetT >::index_t index_t;
            typedef SIXTRL_PARTICLE_SET_DATAPTR_DEC typename
                    TypeMethodParamTraits< index_t >::pointer ptr_t;

            return const_cast< ptr_t >(
                st::ParticleSet_const_index_begin_for_addr< PSetT >(
                    pset, addr ) );
        }

        template< class PSetT >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_PARTICLE_SET_DATAPTR_DEC
            typename TypeMethodParamTraits< typename ParticleSetTraits<
                PSetT >::index_t >::pointer
        ParticleSet_index_end_for_addr(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* SIXTRL_RESTRICT pset,
            particle_addr_t const addr,
            particle_num_elements_t const length ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            typedef typename st::ParticleSetTraits< PSetT >::index_t index_t;
            typedef SIXTRL_PARTICLE_SET_DATAPTR_DEC typename
                    st::TypeMethodParamTraits< index_t >::pointer ptr_t;

            return const_cast< ptr_t >( st::ParticleSet_const_index_end_for_addr<
                PSetT >( pset, addr, length ) );
        }

        /* ----------------------------------------------------------------- */

        template< class PSetT >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
            !SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >(),
            typename ParticleSetTraits< PSetT >::index_t >::type
        ParticleSet_get_index_value_from_addr(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC const PSetT *const
                SIXTRL_RESTRICT /* pset */,
            particle_addr_t const /* addr */,
            particle_num_elements_t const /* length */,
            particle_num_elements_t const /* idx */ ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            static_assert( st::ParticleSet_is_type< PSetT >(),
                "PSetT required to be a particle set class" );
            return typename st::ParticleSetTraits< PSetT >::index_t{ 0 };
        }

        template< class PSetT >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
            SIXTRL_CXX_NAMESPACE::ParticleSet_impl_has_field_addr< PSetT >(),
            typename TypeMethodParamTraits< typename ParticleSetTraits<
                PSetT >::index_t >::const_existing_type >::type
        ParticleSet_get_index_value_from_addr(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC const PSetT *const
                SIXTRL_RESTRICT pset,
            particle_addr_t const addr, particle_num_elements_t const length,
            particle_num_elements_t const idx ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            auto ptr = st::ParticleSet_const_index_begin_for_addr( pset, addr );
            SIXTRL_ASSERT( ptr != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( idx >= st::particle_num_elements_t{ 0 } );
            SIXTRL_ASSERT( idx < length );
            ( void )length;

            return ptr[ idx ];
        }

        /* ----------------------------------------------------------------- */

        template< class PSetT, typename IndexArg >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
            !SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >(),
            arch_status_t >::type
        ParticleSet_set_index_value_for_addr(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* SIXTRL_RESTRICT /* pset */,
            particle_addr_t const /* addr */,
            particle_num_elements_t const /* length */,
            particle_num_elements_t const /* idx */,
            IndexArg /* value */ ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
        }

        template< class PSetT, typename IndexArg >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
            SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< IndexArg,
                typename ParticleSetTraits< PSetT >::index_t >(),
                arch_status_t >::type
        ParticleSet_set_index_value_for_addr(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* SIXTRL_RESTRICT pset,
            particle_addr_t const addr, particle_num_elements_t const length,
            particle_num_elements_t const idx, IndexArg value )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            auto ptr = st::ParticleSet_index_begin_for_addr( pset, addr );

            SIXTRL_ASSERT( ptr != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( idx >= st::particle_num_elements_t{ 0 } );
            SIXTRL_ASSERT( idx < length );
            ( void )length;

            ptr[ idx ] = value;
            return st::ARCH_STATUS_SUCCESS;
        }

        template< class PSetT, typename IndexArg >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
            !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< IndexArg,
                typename ParticleSetTraits< PSetT >::index_t >() &&
            SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable< IndexArg,
                typename ParticleSetTraits< PSetT >::index_t >(),
                arch_status_t >::type
        ParticleSet_set_index_value_for_addr(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* SIXTRL_RESTRICT pset,
            particle_addr_t const addr, particle_num_elements_t const length,
            particle_num_elements_t const idx, IndexArg value )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            auto ptr = st::ParticleSet_index_begin_for_addr( pset, addr );

            SIXTRL_ASSERT( ptr != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( idx >= st::particle_num_elements_t{ 0 } );
            SIXTRL_ASSERT( idx < length );
            ( void )length;

            ptr[ idx ] = std::move( value );
            return st::ARCH_STATUS_SUCCESS;
        }

        template< class PSetT, typename IndexArg >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
            !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< IndexArg,
                typename ParticleSetTraits< PSetT >::index_t >() &&
            !SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable< IndexArg,
                typename ParticleSetTraits< PSetT >::index_t >(),
            arch_status_t >::type
        ParticleSet_set_index_value_for_addr(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* SIXTRL_RESTRICT pset,
            particle_addr_t const addr, particle_num_elements_t const length,
            particle_num_elements_t const idx, IndexArg value )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            auto ptr = st::ParticleSet_index_begin_for_addr( pset, addr );

            SIXTRL_ASSERT( ptr != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( idx >= st::particle_num_elements_t{ 0 } );
            SIXTRL_ASSERT( idx < length );
            ( void )length;

            return st::Types_perform_assignment< typename std::decay< IndexArg
                >::type, typename ParticleSetTraits< PSetT >::index_t >(
                    ptr[ idx ], value );
        }

        /* ----------------------------------------------------------------- */

        template< class PSetT, typename IndexArg >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
            !SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >(),
            arch_status_t >::type
        ParticleSet_set_all_index_values_for_addr(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* SIXTRL_RESTRICT /*pset*/,
            particle_addr_t const /* addr */,
            particle_num_elements_t const /* length */,
            IndexArg /* value */ ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
        }

        template< class PSetT, typename IndexArg >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
            ( SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< IndexArg,
                typename ParticleSetTraits< PSetT >::index_t >() ||
              SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable< IndexArg,
                typename ParticleSetTraits< PSetT >::index_t >() ),
            arch_status_t >::type
        ParticleSet_set_all_index_values_for_addr(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* SIXTRL_RESTRICT pset,
            particle_addr_t const addr,
            particle_num_elements_t const length, IndexArg value )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            auto it = st::ParticleSet_index_begin_for_addr( pset, addr );
            auto end_ptr = st::ParticleSet_index_end_for_addr(
                pset, addr, length );

            st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

            if( ( it != SIXTRL_NULLPTR ) && ( end_ptr != SIXTRL_NULLPTR ) )
            {
                for( ; it != end_ptr ; ++it ) *it = value;
                status = st::ARCH_STATUS_SUCCESS;
            }

            return status;
        }

        template< class PSetT, typename IndexArg >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
            !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable< IndexArg,
                typename ParticleSetTraits< PSetT >::index_t >() &&
            !SIXTRL_CXX_NAMESPACE::Types_same_and_move_assignable< IndexArg,
                typename ParticleSetTraits< PSetT >::index_t >(),
            arch_status_t >::type
        ParticleSet_set_all_index_values_for_addr(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* SIXTRL_RESTRICT pset,
            particle_addr_t const addr,
            particle_num_elements_t const length, IndexArg value )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            auto it = st::ParticleSet_index_begin_for_addr( pset, addr );
            auto end_ptr = st::ParticleSet_index_end_for_addr(
                pset, addr, length );

            st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

            if( ( it != SIXTRL_NULLPTR ) && ( end_ptr != SIXTRL_NULLPTR ) )
            {
                typedef typename std::decay< IndexArg >::type src_index_t;
                typedef typename ParticleSetTraits< PSetT >::index_t index_t;

                status = st::ARCH_STATUS_SUCCESS;
                for( ; it != end_ptr ; ++it )
                {
                    status |= st::Types_perform_assignment<
                        src_index_t, index_t >( *it, value );
                }
            }

            return status;
        }

        /* ----------------------------------------------------------------- */

        template< class PSetT, typename IndexIter >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
            !SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >(),
            arch_status_t >::type
        ParticleSet_set_index_values_for_addr(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* SIXTRL_RESTRICT /*pset*/,
            particle_addr_t const /* addr */,
            particle_num_elements_t const /* length */,
            IndexIter /* values_begin */ ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
        }

        template< class PSetT, typename IndexIter >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
            SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
                typename std::iterator_traits< IndexIter >::value_type,
                typename ParticleSetTraits< PSetT >::index_t >(),
            arch_status_t >::type
        ParticleSet_set_index_values_for_addr(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* SIXTRL_RESTRICT pset,
            particle_addr_t const addr, particle_num_elements_t const length,
            IndexIter values_it )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            auto it = st::ParticleSet_index_begin_for_addr( pset, addr );
            auto end_ptr = st::ParticleSet_index_end_for_addr(
                pset, addr, length );
            st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

            if( ( it != SIXTRL_NULLPTR ) && ( end_ptr != SIXTRL_NULLPTR ) )
            {
                for( ; it != end_ptr ; ++it, ++values_it ) *it = *values_it;
                status = st::ARCH_STATUS_SUCCESS;
            }

            return status;
        }

        template< class PSetT, typename IndexIter >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
            SIXTRL_CXX_NAMESPACE::ParticleSet_impl_has_field_addr< PSetT >() &&
            !SIXTRL_CXX_NAMESPACE::Types_same_and_direct_assignable<
                typename std::iterator_traits< IndexIter >::value_type,
                typename ParticleSetTraits< PSetT >::index_t >(),
            arch_status_t >::type
        ParticleSet_set_index_values_for_addr(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* SIXTRL_RESTRICT pset,
            particle_addr_t const addr, particle_num_elements_t const length,
            IndexIter values_it )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            auto it = st::ParticleSet_index_begin_for_addr( pset, addr );
            auto end_ptr = st::ParticleSet_index_end_for_addr(
                pset, addr, length );

            st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

            if( ( it != SIXTRL_NULLPTR ) && ( end_ptr != SIXTRL_NULLPTR ) )
            {
                typedef typename ParticleSetTraits< PSetT >::index_t index_t;
                typedef typename std::iterator_traits< IndexIter >::value_type
                    src_index_t;

                status = st::ARCH_STATUS_SUCCESS;
                for( ; it != end_ptr ; ++it, ++values_it )
                {
                    status |= st::Types_perform_assignment<
                        src_index_t, index_t >( *it, *values_it );
                }
            }

            return status;
        }

        /* ================================================================= */

        template< class T, class Alloc >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t
        ParticleSet_vector_set_capacity(
            std::vector< T, Alloc >& SIXTRL_RESTRICT_REF vec,
            particle_num_elements_t const new_capacity,
            typename TypeMethodParamTraits< T >::const_argument_type
                default_value = T{} )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

            if( new_capacity >= st::particle_num_elements_t{ 0 } )
            {
                std::size_t const capacity =
                    static_cast< std::size_t >( new_capacity );

                if( vec.size() != capacity )
                {
                    std::vector< T, Alloc > new_vec( capacity );

                    if( vec.size() < capacity )
                    {
                        auto vec_begin = new_vec.begin();
                        auto vec_end = vec_begin;
                        std::advance( vec_end, capacity );

                        std::copy( vec.begin(), vec.end(), vec_begin );
                        std::fill( vec_end, new_vec.end(), default_value );
                    }
                    else
                    {
                        auto vec_begin = vec.begin();
                        auto vec_end = vec_begin;
                        std::advance( vec_end, capacity );
                        std::copy( vec_begin, vec_end, new_vec.begin() );
                    }

                    vec.swap( new_vec );
                }

                status = st::ARCH_STATUS_SUCCESS;
            }

            return status;
        }

        template< class T, class Alloc >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_PARTICLE_SET_DATAPTR_DEC
            typename TypeMethodParamTraits< T >::const_pointer
        ParticleSet_vector_const_begin( std::vector< T, Alloc > const&
            SIXTRL_RESTRICT_REF vec ) SIXTRL_NOEXCEPT
        {
            return vec.data();
        }

        template< class T, class Alloc >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_PARTICLE_SET_DATAPTR_DEC
            typename TypeMethodParamTraits< T >::const_pointer
        ParticleSet_vector_const_end(
            std::vector< T, Alloc > const& SIXTRL_RESTRICT_REF vec,
            particle_num_elements_t const num_particles ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            auto end_ptr = st::ParticleSet_vector_const_begin( vec );

            SIXTRL_ASSERT( num_particles >= st::particle_num_elements_t{ 0 } );
            SIXTRL_ASSERT( static_cast< std::size_t >( num_particles ) <=
                           vec.size() );

            if( end_ptr != SIXTRL_NULLPTR )
            {
                std::advance( end_ptr, num_particles );
            }

            return end_ptr;
        }
    }
}
#endif /* C++ */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC SIXTRL_FN
SIXTRL_PARTICLE_SET_DATAPTR_DEC NS(particle_real_t) const*
NS(ParticleSet_const_real_begin_for_addr)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const NS(ParticleSet) *const
        SIXTRL_RESTRICT pset,
    NS(particle_addr_t) const addr ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN
SIXTRL_PARTICLE_SET_DATAPTR_DEC NS(particle_real_t) const*
NS(ParticleSet_const_real_end_for_addr)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const NS(ParticleSet) *const
        SIXTRL_RESTRICT pset,
    NS(particle_addr_t) const addr,
    NS(particle_num_elements_t) const length ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_PARTICLE_SET_DATAPTR_DEC NS(particle_real_t)*
NS(ParticleSet_real_begin_for_addr)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)* SIXTRL_RESTRICT pset,
    NS(particle_addr_t) const addr ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_PARTICLE_SET_DATAPTR_DEC NS(particle_real_t)*
NS(ParticleSet_real_end_for_addr)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)* SIXTRL_RESTRICT pset,
    NS(particle_addr_t) const addr,
    NS(particle_num_elements_t) const length ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_real_t)
NS(ParticleSet_get_real_value_from_addr)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const NS(ParticleSet) *const
        SIXTRL_RESTRICT pset,
    NS(particle_addr_t) const addr,
    NS(particle_num_elements_t) const length,
    NS(particle_num_elements_t) const idx ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(ParticleSet_set_real_value_for_addr)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)* SIXTRL_RESTRICT pset,
    NS(particle_addr_t) const addr,
    NS(particle_num_elements_t) const length,
    NS(particle_num_elements_t) const idx,
    NS(particle_real_t) const real_value ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(ParticleSet_set_real_values_for_addr)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)* SIXTRL_RESTRICT pset,
    NS(particle_addr_t) const addr,
    NS(particle_num_elements_t) const length,
    SIXTRL_PARTICLE_SET_DATAPTR_DEC NS(particle_real_t) const*
        SIXTRL_RESTRICT real_values_begin ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(ParticleSet_set_all_real_values_for_addr)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)* SIXTRL_RESTRICT pset,
    NS(particle_addr_t) const addr,
    NS(particle_num_elements_t) const length,
    NS(particle_real_t) const real_value ) SIXTRL_NOEXCEPT;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN
SIXTRL_PARTICLE_SET_DATAPTR_DEC NS(particle_index_t) const*
NS(ParticleSet_const_index_begin_for_addr)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const NS(ParticleSet) *const
        SIXTRL_RESTRICT pset,
    NS(particle_addr_t) const addr ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN
SIXTRL_PARTICLE_SET_DATAPTR_DEC NS(particle_index_t) const*
NS(ParticleSet_const_index_end_for_addr)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const NS(ParticleSet) *const
        SIXTRL_RESTRICT pset,
    NS(particle_addr_t) const addr,
    NS(particle_num_elements_t) const length ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_PARTICLE_SET_DATAPTR_DEC NS(particle_index_t)*
NS(ParticleSet_index_begin_for_addr)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)* SIXTRL_RESTRICT pset,
    NS(particle_addr_t) const addr ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_PARTICLE_SET_DATAPTR_DEC NS(particle_index_t)*
NS(ParticleSet_index_end_for_addr)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)* SIXTRL_RESTRICT pset,
    NS(particle_addr_t) const addr,
    NS(particle_num_elements_t) const length ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(particle_index_t)
NS(ParticleSet_get_index_value_from_addr)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const NS(ParticleSet) *const
        SIXTRL_RESTRICT pset,
    NS(particle_addr_t) const addr,
    NS(particle_num_elements_t) const length,
    NS(particle_num_elements_t) const idx ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(ParticleSet_set_index_value_for_addr)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)* SIXTRL_RESTRICT pset,
    NS(particle_addr_t) const addr,
    NS(particle_num_elements_t) const length,
    NS(particle_num_elements_t) const idx,
    NS(particle_index_t) const index_value ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(ParticleSet_set_index_values_for_addr)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)* SIXTRL_RESTRICT pset,
    NS(particle_addr_t) const addr,
    NS(particle_num_elements_t) const length,
    SIXTRL_PARTICLE_SET_DATAPTR_DEC NS(particle_index_t) const*
        SIXTRL_RESTRICT index_values_begin ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t)
NS(ParticleSet_set_all_index_values_for_addr)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)* SIXTRL_RESTRICT pset,
    NS(particle_addr_t) const addr,
    NS(particle_num_elements_t) const length,
    NS(particle_index_t) const index_value ) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!         Implementation of inline methods and functions         !!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_INLINE SIXTRL_PARTICLE_SET_DATAPTR_DEC NS(particle_real_t) const*
NS(ParticleSet_const_real_begin_for_addr)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const NS(ParticleSet) *const
        SIXTRL_RESTRICT /*pset*/,
    NS(particle_addr_t) const addr ) SIXTRL_NOEXCEPT
{
    return ( SIXTRL_PARTICLE_SET_DATAPTR_DEC NS(particle_real_t) const* )(
        uintptr_t )addr;
}

SIXTRL_INLINE SIXTRL_PARTICLE_SET_DATAPTR_DEC NS(particle_real_t) const*
NS(ParticleSet_const_real_end_for_addr)( SIXTRL_PARTICLE_SET_ARGPTR_DEC const
        NS(ParticleSet) *const SIXTRL_RESTRICT pset,
    NS(particle_addr_t) const addr,
    NS(particle_num_elements_t) const length ) SIXTRL_NOEXCEPT
{
    SIXTRL_PARTICLE_SET_DATAPTR_DEC NS(particle_real_t) const* ptr =
        NS(ParticleSet_const_real_begin_for_addr)( pset, addr );

    if( ( ptr != SIXTRL_NULLPTR ) &&
        ( length >= ( NS(particle_num_elements_t) )0 ) )
    {
        ptr = ptr + length;
    }

    return ptr;
}

SIXTRL_INLINE SIXTRL_PARTICLE_SET_DATAPTR_DEC NS(particle_real_t)*
NS(ParticleSet_real_begin_for_addr)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)* SIXTRL_RESTRICT /*pset*/,
    NS(particle_addr_t) const addr ) SIXTRL_NOEXCEPT
{
    return ( SIXTRL_PARTICLE_SET_DATAPTR_DEC NS(particle_real_t)* )(
        uintptr_t )addr;
}

SIXTRL_INLINE SIXTRL_PARTICLE_SET_DATAPTR_DEC NS(particle_real_t)*
NS(ParticleSet_real_end_for_addr)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)* SIXTRL_RESTRICT pset,
    NS(particle_addr_t) const addr,
    NS(particle_num_elements_t) const length ) SIXTRL_NOEXCEPT
{
    return ( SIXTRL_PARTICLE_SET_DATAPTR_DEC NS(particle_real_t)*
        )NS(ParticleSet_const_real_end_for_addr)( pset, addr, length );
}

SIXTRL_INLINE NS(particle_real_t) NS(ParticleSet_get_real_value_from_addr)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const
        NS(ParticleSet) *const SIXTRL_RESTRICT pset,
    NS(particle_addr_t) const addr, NS(particle_num_elements_t) const length,
    NS(particle_num_elements_t) const idx ) SIXTRL_NOEXCEPT
{
    SIXTRL_PARTICLE_SET_DATAPTR_DEC NS(particle_real_t) const* ptr =
        NS(ParticleSet_const_real_begin_for_addr)( pset, addr );

    SIXTRL_ASSERT( idx >= ( NS(particle_num_elements_t) )0 );

    return ( ( ptr != SIXTRL_NULLPTR ) && ( idx < length ) )
        ? ptr[ idx ] : ( NS(particle_real_t) )0;
}

SIXTRL_INLINE NS(arch_status_t) NS(ParticleSet_set_real_value_for_addr)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)* SIXTRL_RESTRICT pset,
    NS(particle_addr_t) const addr,
    NS(particle_num_elements_t) const length,
    NS(particle_num_elements_t) const idx,
    NS(particle_real_t) const real_value ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    SIXTRL_PARTICLE_SET_DATAPTR_DEC NS(particle_real_t)* ptr =
        NS(ParticleSet_real_begin_for_addr)( pset, addr );

    if( ( ptr != SIXTRL_NULLPTR ) && ( idx < length ) )
    {
        SIXTRL_ASSERT( idx >= ( NS(particle_num_elements_t) )0 );
        ptr[ idx ] = real_value;
        status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

SIXTRL_INLINE NS(arch_status_t) NS(ParticleSet_set_real_values_for_addr)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)* SIXTRL_RESTRICT pset,
    NS(particle_addr_t) const addr,
    NS(particle_num_elements_t) const length,
    SIXTRL_PARTICLE_SET_DATAPTR_DEC NS(particle_real_t) const*
        SIXTRL_RESTRICT real_values_begin ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    SIXTRL_PARTICLE_SET_DATAPTR_DEC NS(particle_real_t)* ptr =
        NS(ParticleSet_real_begin_for_addr)( pset, addr );

    if( ( ptr != SIXTRL_NULLPTR ) &&
        ( length > ( NS(particle_num_elements_t) )0 ) &&
        ( real_values_begin != SIXTRL_NULLPTR ) )
    {
        NS(particle_num_elements_t) idx = ( NS(particle_num_elements_t) )0;

        for( ; idx < length ; ++idx )
        {
            ptr[ idx ] = real_values_begin[ idx ];
        }

        status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

SIXTRL_INLINE NS(arch_status_t) NS(ParticleSet_set_all_real_values_for_addr)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)* SIXTRL_RESTRICT pset,
    NS(particle_addr_t) const addr,
    NS(particle_num_elements_t) const length,
    NS(particle_real_t) const real_value ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    SIXTRL_PARTICLE_SET_DATAPTR_DEC NS(particle_real_t)* ptr =
        NS(ParticleSet_real_begin_for_addr)( pset, addr );

    if( ( ptr != SIXTRL_NULLPTR ) &&
        ( length > ( NS(particle_num_elements_t) )0 ) )
    {
        NS(particle_num_elements_t) idx = ( NS(particle_num_elements_t) )0;

        for( ; idx < length ; ++idx )
        {
            ptr[ idx ] = real_value;
        }

        status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE SIXTRL_PARTICLE_SET_DATAPTR_DEC NS(particle_index_t) const*
NS(ParticleSet_const_index_begin_for_addr)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const NS(ParticleSet) *const
        SIXTRL_RESTRICT /*pset*/,
    NS(particle_addr_t) const addr ) SIXTRL_NOEXCEPT
{
    return ( SIXTRL_PARTICLE_SET_DATAPTR_DEC NS(particle_index_t) const* )(
        uintptr_t )addr;
}

SIXTRL_INLINE SIXTRL_PARTICLE_SET_DATAPTR_DEC NS(particle_index_t) const*
NS(ParticleSet_const_index_end_for_addr)( SIXTRL_PARTICLE_SET_ARGPTR_DEC const
        NS(ParticleSet) *const SIXTRL_RESTRICT pset,
    NS(particle_addr_t) const addr,
    NS(particle_num_elements_t) const length ) SIXTRL_NOEXCEPT
{
    SIXTRL_PARTICLE_SET_DATAPTR_DEC NS(particle_index_t) const* ptr =
        NS(ParticleSet_const_index_begin_for_addr)( pset, addr );

    if( ( ptr != SIXTRL_NULLPTR ) &&
        ( length >= ( NS(particle_num_elements_t) )0 ) )
    {
        ptr = ptr + length;
    }

    return ptr;
}

SIXTRL_INLINE SIXTRL_PARTICLE_SET_DATAPTR_DEC NS(particle_index_t)*
NS(ParticleSet_index_begin_for_addr)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)* SIXTRL_RESTRICT /*pset*/,
    NS(particle_addr_t) const addr ) SIXTRL_NOEXCEPT
{
    return ( SIXTRL_PARTICLE_SET_DATAPTR_DEC NS(particle_index_t)* )(
        uintptr_t )addr;
}

SIXTRL_INLINE SIXTRL_PARTICLE_SET_DATAPTR_DEC NS(particle_index_t)*
NS(ParticleSet_index_end_for_addr)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)* SIXTRL_RESTRICT pset,
    NS(particle_addr_t) const addr,
    NS(particle_num_elements_t) const length ) SIXTRL_NOEXCEPT
{
    return ( SIXTRL_PARTICLE_SET_DATAPTR_DEC NS(particle_index_t)*
        )NS(ParticleSet_const_index_end_for_addr)( pset, addr, length );
}

SIXTRL_INLINE NS(particle_index_t) NS(ParticleSet_get_index_value_from_addr)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const NS(ParticleSet) *const
        SIXTRL_RESTRICT pset,
    NS(particle_addr_t) const addr,
    NS(particle_num_elements_t) const length,
    NS(particle_num_elements_t) const idx ) SIXTRL_NOEXCEPT
{
    SIXTRL_PARTICLE_SET_DATAPTR_DEC NS(particle_index_t) const* ptr =
        NS(ParticleSet_const_index_begin_for_addr)( pset, addr );
    SIXTRL_ASSERT( idx >= ( NS(particle_num_elements_t) )0 );

    return ( ( ptr != SIXTRL_NULLPTR ) && ( idx < length ) )
        ? ptr[ idx ] : ( NS(particle_index_t) )0;
}

SIXTRL_INLINE NS(arch_status_t) NS(ParticleSet_set_index_value_for_addr)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)* SIXTRL_RESTRICT pset,
    NS(particle_addr_t) const addr,
    NS(particle_num_elements_t) const length,
    NS(particle_num_elements_t) const idx,
    NS(particle_index_t) const index_value ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    SIXTRL_PARTICLE_SET_DATAPTR_DEC NS(particle_index_t)* ptr =
        NS(ParticleSet_index_begin_for_addr)( pset, addr );

    if( ( ptr != SIXTRL_NULLPTR ) && ( idx < length ) )
    {
        SIXTRL_ASSERT( idx >= ( NS(particle_num_elements_t) )0 );
        ptr[ idx ] = index_value;
        status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

SIXTRL_INLINE NS(arch_status_t) NS(ParticleSet_set_index_values_for_addr)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)* SIXTRL_RESTRICT pset,
    NS(particle_addr_t) const addr,
    NS(particle_num_elements_t) const length,
    SIXTRL_PARTICLE_SET_DATAPTR_DEC NS(particle_index_t) const*
        SIXTRL_RESTRICT index_values_begin ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    SIXTRL_PARTICLE_SET_DATAPTR_DEC NS(particle_index_t)* ptr =
        NS(ParticleSet_index_begin_for_addr)( pset, addr );

    if( ( ptr != SIXTRL_NULLPTR ) &&
        ( length > ( NS(particle_num_elements_t) )0 ) &&
        ( index_values_begin != SIXTRL_NULLPTR ) )
    {
        NS(particle_num_elements_t) idx = ( NS(particle_num_elements_t) )0;

        for( ; idx < length ; ++idx )
        {
            ptr[ idx ] = index_values_begin[ idx ];
        }

        status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

SIXTRL_INLINE NS(arch_status_t) NS(ParticleSet_set_all_index_values_for_addr)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)* SIXTRL_RESTRICT pset,
    NS(particle_addr_t) const addr,
    NS(particle_num_elements_t) const length,
    NS(particle_index_t) const index_value ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    SIXTRL_PARTICLE_SET_DATAPTR_DEC NS(particle_index_t)* ptr =
        NS(ParticleSet_index_begin_for_addr)( pset, addr );

    if( ( ptr != SIXTRL_NULLPTR ) &&
        ( length > ( NS(particle_num_elements_t) )0 ) )
    {
        NS(particle_num_elements_t) idx = ( NS(particle_num_elements_t) )0;

        for( ; idx < length ; ++idx )
        {
            ptr[ idx ] = index_value;
        }

        status = ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS;
    }

    return status;
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SET_HELPER_API_H__ */
