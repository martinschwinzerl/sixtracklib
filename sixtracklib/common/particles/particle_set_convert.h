#ifndef SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SET_CONVERT_CXX_HPP__
#define SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SET_CONVERT_CXX_HPP__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <type_traits>
    #endif /* C++ */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/particles/particle_set.h"
    #include "sixtracklib/common/particles/particle_set.hpp"
    #include "sixtracklib/common/particles/particle_set_vector.hpp"
    #include "sixtracklib/common/particles/particle_set_api.h"
    #include "sixtracklib/common/internal/obj_convert.hpp"
    #include "sixtracklib/common/internal/compiler_attributes.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class SrcT, class DstT >
    SIXTRL_STATIC SIXTRL_FN constexpr bool ParticleSet_allow_type_conversion(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( dst ) = SIXTRL_NULLPTR,
        SIXTRL_PARTICLE_SET_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( src ) = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return ( ( SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< SrcT >() ) &&
                 ( SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< DstT >() ) &&
                 ( SIXTRL_CXX_NAMESPACE::Types_can_perform_assignment<
                     typename ParticleTraits< SrcT >::real_t,
                     typename ParticleTraits< DstT >::real_t >() ) &&
                 ( SIXTRL_CXX_NAMESPACE::Types_can_perform_assignment<
                     typename ParticleTraits< SrcT >::index_t,
                     typename ParticleTraits< DstT >::index_t >() ) );
    }

    template< class SrcT, class DstT >
    SIXTRL_STATIC SIXTRL_FN constexpr bool
    ParticleSet_type_conv_can_requ_prepare(
        SIXTRL_BUFFER_DATAPTR_DEC const DstT *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( dest ) = SIXTRL_NULLPTR,
        SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( src ) = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return true;
    }

    template< class SrcT, class DstT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool
    ParticleSet_requ_prepare_conversion(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
        SIXTRL_PARTICLE_SET_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
        SIXTRL_CXX_NAMESPACE::store_backend_t const src_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
        SIXTRL_CXX_NAMESPACE::store_backend_t const dst_store_be =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::ParticleSet_allow_type_conversion< SrcT, DstT >(),
                       "Illegal conversion" );

        SIXTRL_ASSERT( src_store_be != st::STORAGE_BE_ILLEGAL );
        SIXTRL_ASSERT( dst_store_be != st::STORAGE_BE_ILLEGAL );

        SIXTRL_ASSERT( dst != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( src != SIXTRL_NULLPTR );

        ( void )src_store_be;
        ( void )dst_store_be;

        return ( ( !std::is_same< SrcT, DstT >::value ) &&
                 ( reinterpret_cast< std::uintptr_t >( dst ) !=
                   reinterpret_cast< std::uintptr_t >( src ) ) &&
                 ( st::ParticleSet_capacity( dst ) <
                   st::ParticleSet_num_particles( src ) ) );
    }

    template< class SrcT, class DstT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t
    ParticleSet_prepare_conversion(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
        SIXTRL_PARTICLE_SET_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
        store_backend_t src_store_be = STORAGE_BE_DEFAULT,
        store_backend_t dst_store_be = STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::ParticleSet_allow_type_conversion< SrcT, DstT >(),
            "conversion from SrcT to DstT is not allowed" );

        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( src != SIXTRL_NULLPTR ) && ( dst != SIXTRL_NULLPTR ) &&
            ( src_store_be != st::STORAGE_BE_ILLEGAL ) &&
            ( dst_store_be != st::STORAGE_BE_ILLEGAL ) )
        {
            status = st::ParticleSet_set_capacity(
                dst, st::ParticleSet_num_particles( src ) );
        }

        return status;
    }


    template< class SrcT, class DstT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool ParticleSet_allow_conversion(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
        SIXTRL_PARTICLE_SET_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
        store_backend_t const src_store_be = STORAGE_BE_DEFAULT,
        store_backend_t const dst_store_be = STORAGE_BE_DEFAULT
    ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return (
        ( st::ParticleSet_allow_type_conversion< SrcT, DstT >( dst, src ) ) &&
        ( src_store_be != st::STORAGE_BE_ILLEGAL ) &&
        ( dst_store_be != st::STORAGE_BE_ILLEGAL ) &&
        ( src != SIXTRL_NULLPTR ) && ( dst != SIXTRL_NULLPTR ) &&
        ( st::ParticleSet_capacity( dst ) >=
          st::ParticleSet_num_particles( src ) ) );
    }

    template< class SrcT, class DstT >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::ParticleSet_allow_type_conversion< SrcT, DstT >(),
        arch_status_t >::type
    ParticleSet_convert(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC DstT*
            SIXTRL_RESTRICT SIXTRL_UNUSED( dst ),
        SIXTRL_PARTICLE_SET_ARGPTR_DEC const SrcT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( src ),
        SIXTRL_CXX_NAMESPACE::store_backend_t const SIXTRL_UNUSED(
            src_store_be ) = SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
        SIXTRL_CXX_NAMESPACE::store_backend_t const SIXTRL_UNUSED(
            dst_store_be ) = SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class SrcT, class DstT, typename... Args >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_allow_type_conversion< SrcT, DstT >(),
        arch_status_t >::type
    ParticleSet_convert(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
        SIXTRL_PARTICLE_SET_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
        store_backend_t const src_store_be = STORAGE_BE_DEFAULT,
        store_backend_t const dst_store_be = STORAGE_BE_DEFAULT,
        Args&&... SIXTRL_UNUSED( conv_parameters ) )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( st::ParticleSet_allow_conversion(
                dst, src, src_store_be, dst_store_be ) )
        {
            status = st::ParticleSet_set_num_particles(
                    dst, st::ParticleSet_num_particles( src ) );

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( st::ParticleSet_const_x_begin( src ) != SIXTRL_NULLPTR ) )
            {
                status = ( st::ParticleSet_const_x_begin( dst
                                ) != SIXTRL_NULLPTR )
                    ? st::ParticleSet_set_x( dst,
                        st::ParticleSet_const_x_begin( src ) )
                    : st::ARCH_STATUS_GENERAL_FAILURE;
            }

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( st::ParticleSet_const_px_begin( src ) != SIXTRL_NULLPTR ) )
            {
                status = ( st::ParticleSet_const_px_begin( dst
                                ) != SIXTRL_NULLPTR )
                    ? st::ParticleSet_set_px( dst,
                        st::ParticleSet_const_px_begin( src ) )
                    : st::ARCH_STATUS_GENERAL_FAILURE;
            }

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( st::ParticleSet_const_y_begin( src ) != SIXTRL_NULLPTR ) )
            {
                status = ( st::ParticleSet_const_y_begin( dst
                                ) != SIXTRL_NULLPTR )
                    ? st::ParticleSet_set_y( dst,
                        st::ParticleSet_const_y_begin( src ) )
                    : st::ARCH_STATUS_GENERAL_FAILURE;
            }

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( st::ParticleSet_const_py_begin( src ) != SIXTRL_NULLPTR ) )
            {
                status = ( st::ParticleSet_const_py_begin( dst
                                ) != SIXTRL_NULLPTR )
                    ? st::ParticleSet_set_py( dst,
                        st::ParticleSet_const_py_begin( src ) )
                    : st::ARCH_STATUS_GENERAL_FAILURE;
            }

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( st::ParticleSet_const_zeta_begin( src ) != SIXTRL_NULLPTR ) )
            {
                status = ( st::ParticleSet_const_zeta_begin( dst
                                ) != SIXTRL_NULLPTR )
                    ? st::ParticleSet_set_zeta( dst,
                        st::ParticleSet_const_zeta_begin( src ) )
                    : st::ARCH_STATUS_GENERAL_FAILURE;
            }

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( st::ParticleSet_const_delta_begin( src ) != SIXTRL_NULLPTR ) )
            {
                status = ( st::ParticleSet_const_delta_begin( dst
                                ) != SIXTRL_NULLPTR )
                    ? st::ParticleSet_set_delta( dst,
                        st::ParticleSet_const_delta_begin( src ) )
                    : st::ARCH_STATUS_GENERAL_FAILURE;
            }

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( st::ParticleSet_const_state_begin( src ) != SIXTRL_NULLPTR ) )
            {
                status = ( st::ParticleSet_const_state_begin( dst
                                ) != SIXTRL_NULLPTR )
                    ? st::ParticleSet_set_state( dst,
                        st::ParticleSet_const_state_begin( src ) )
                    : st::ARCH_STATUS_GENERAL_FAILURE;
            }

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( st::ParticleSet_const_at_element_begin( src ) !=
                    SIXTRL_NULLPTR ) )
            {
                status = ( st::ParticleSet_const_at_element_begin(
                               dst ) != SIXTRL_NULLPTR )
                    ? st::ParticleSet_set_at_element( dst,
                        st::ParticleSet_const_at_element_begin( src ) )
                    : st::ARCH_STATUS_GENERAL_FAILURE;
            }

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( st::ParticleSet_const_at_turn_begin(
                                src ) != SIXTRL_NULLPTR ) )
            {
                status = ( st::ParticleSet_const_at_turn_begin( dst
                                ) != SIXTRL_NULLPTR )
                    ? st::ParticleSet_set_at_turn( dst,
                        st::ParticleSet_const_at_turn_begin( src ) )
                    : st::ARCH_STATUS_GENERAL_FAILURE;
            }

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( st::ParticleSet_const_particle_id_begin(
                    src ) != SIXTRL_NULLPTR ) )
            {
                status = ( st::ParticleSet_const_particle_id_begin( dst
                                ) != SIXTRL_NULLPTR )
                    ? st::ParticleSet_set_particle_id( dst,
                        st::ParticleSet_const_particle_id_begin( src ) )
                    : st::ARCH_STATUS_GENERAL_FAILURE;
            }

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( st::ParticleSet_const_psigma_begin(
                            src ) != SIXTRL_NULLPTR ) )
            {
                status = ( st::ParticleSet_const_psigma_begin(
                            dst ) != SIXTRL_NULLPTR )
                    ? st::ParticleSet_set_psigma( dst,
                        st::ParticleSet_const_psigma_begin( src ) )
                    : st::ARCH_STATUS_GENERAL_FAILURE;
            }

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( st::ParticleSet_const_rpp_begin( src ) != SIXTRL_NULLPTR ) )
            {
                status = ( st::ParticleSet_const_rpp_begin( dst
                                ) != SIXTRL_NULLPTR )
                    ? st::ParticleSet_set_rpp( dst,
                        st::ParticleSet_const_rpp_begin( src ) )
                    : st::ARCH_STATUS_GENERAL_FAILURE;
            }

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( st::ParticleSet_const_rvv_begin( src ) != SIXTRL_NULLPTR ) )
            {
                status = ( st::ParticleSet_const_rvv_begin( dst
                                ) != SIXTRL_NULLPTR )
                    ? st::ParticleSet_set_rvv( dst,
                        st::ParticleSet_const_rvv_begin( src ) )
                    : st::ARCH_STATUS_GENERAL_FAILURE;
            }

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( st::ParticleSet_const_chi_begin( src ) != SIXTRL_NULLPTR ) )
            {
                status = ( st::ParticleSet_const_chi_begin( dst
                                ) != SIXTRL_NULLPTR )
                    ? st::ParticleSet_set_chi( dst,
                        st::ParticleSet_const_chi_begin( src ) )
                    : st::ARCH_STATUS_GENERAL_FAILURE;
            }

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( st::ParticleSet_const_charge_ratio_begin(
                            src ) != SIXTRL_NULLPTR ) )
            {
                status = ( st::ParticleSet_const_charge_ratio_begin( dst
                                ) != SIXTRL_NULLPTR )
                    ? st::ParticleSet_set_charge_ratio( dst,
                        st::ParticleSet_const_charge_ratio_begin( src ) )
                    : st::ARCH_STATUS_GENERAL_FAILURE;
            }

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( st::ParticleSet_const_charge0_begin(
                            src ) != SIXTRL_NULLPTR ) )
            {
                status = ( st::ParticleSet_const_charge0_begin( src
                                ) != SIXTRL_NULLPTR )
                    ? st::ParticleSet_set_charge0( dst,
                        st::ParticleSet_const_charge0_begin( src ) )
                    : st::ARCH_STATUS_GENERAL_FAILURE;
            }

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( st::ParticleSet_const_mass0_begin( src ) != SIXTRL_NULLPTR ) )
            {
                status = ( st::ParticleSet_const_mass0_begin( dst
                                ) != SIXTRL_NULLPTR )
                    ? st::ParticleSet_set_mass0( dst,
                        st::ParticleSet_const_mass0_begin( src ) )
                    : st::ARCH_STATUS_GENERAL_FAILURE;
            }

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( st::ParticleSet_const_beta0_begin( src ) != SIXTRL_NULLPTR ) )
            {
                status = ( st::ParticleSet_const_beta0_begin( dst
                                ) != SIXTRL_NULLPTR )
                    ? st::ParticleSet_set_beta0( dst,
                        st::ParticleSet_const_beta0_begin( src ) )
                    : st::ARCH_STATUS_GENERAL_FAILURE;
            }

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( st::ParticleSet_const_gamma0_begin( src ) != SIXTRL_NULLPTR ) )
            {
                status = ( st::ParticleSet_const_gamma0_begin( dst
                                ) != SIXTRL_NULLPTR )
                    ? st::ParticleSet_set_gamma0( dst,
                        st::ParticleSet_const_gamma0_begin( src ) )
                    : st::ARCH_STATUS_GENERAL_FAILURE;
            }

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( st::ParticleSet_const_pc0_begin( src ) != SIXTRL_NULLPTR ) )
            {
                status = ( st::ParticleSet_const_pc0_begin( dst
                                ) != SIXTRL_NULLPTR )
                    ? st::ParticleSet_set_pc0( dst,
                        st::ParticleSet_const_pc0_begin( src ) )
                    : st::ARCH_STATUS_GENERAL_FAILURE;
            }

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( st::ParticleSet_const_s_begin( src ) != SIXTRL_NULLPTR ) )
            {
                status = ( st::ParticleSet_const_s_begin( dst
                                ) != SIXTRL_NULLPTR )
                    ? st::ParticleSet_set_s( dst,
                        st::ParticleSet_const_s_begin( src ) )
                    : st::ARCH_STATUS_GENERAL_FAILURE;
            }
        }

        return status;
    }

    /* ********************************************************************* */
    /* NS(ParticleSet) */

    template< class DstT, SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT >
    struct ObjDataAllowConversionTraits<
        ::NS(ParticleSet), DstT, SrcStoreT, DstStoreT >
    {
        typedef ::NS(ParticleSet) SrcT;

        SIXTRL_STATIC SIXTRL_FN constexpr bool allow() SIXTRL_NOEXCEPT
        {
            return ( SIXTRL_CXX_NAMESPACE::ParticleSet_allow_type_conversion<
                        SrcT, DstT >() ) &&
                   ( SrcStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL ) &&
                   ( DstStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL );
        }
    };

    template< class DstT, SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT >
    struct ObjDataConversionTypesRequireNoPrepareTraits<
        ::NS(ParticleSet), DstT, SrcStoreT, DstStoreT >
    {
        typedef ::NS(ParticleSet) SrcT;

        static_assert( SIXTRL_CXX_NAMESPACE::ObjData_allow_type_conversion<
            SrcT, DstT, SrcStoreT, DstStoreT >(), "Illegal conversion" );

        constexpr static bool requires_no_prepare = false;
    };

    template< class DstT, SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT >
    struct ObjDataConverter< ::NS(ParticleSet), DstT, SrcStoreT, DstStoreT >
    {
        typedef ::NS(ParticleSet) SrcT;

        static_assert( SIXTRL_CXX_NAMESPACE::ObjData_allow_type_conversion<
            SrcT, DstT, SrcStoreT, DstStoreT >(), "Illegal conversion" );

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool requires_prepare(
            SIXTRL_BUFFER_DATAPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
            SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ParticleSet_requ_prepare_conversion(
                dst, src, SrcStoreT, DstStoreT );
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
        prepare( SIXTRL_BUFFER_DATAPTR_DEC DstT* SIXTRL_RESTRICT dst,
                 SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ParticleSet_prepare_conversion(
                dst, src, SrcStoreT, DstStoreT );
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool allow(
            SIXTRL_BUFFER_DATAPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
            SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ParticleSet_allow_conversion(
                dst, src, SrcStoreT, DstStoreT );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t attempt_conversion(
            SIXTRL_BUFFER_DATAPTR_DEC DstT* SIXTRL_RESTRICT dst,
            SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
            Args&&... conv_params ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ParticleSet_convert( dst, src,
                SrcStoreT, DstStoreT, std::forward< Args >( conv_params )... );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t perform(
            SIXTRL_BUFFER_DATAPTR_DEC DstT* SIXTRL_RESTRICT dst,
            SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
            Args&&... conv_params ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;

            st::arch_status_t status = st::ParticleSet_convert( dst, src,
                SrcStoreT, DstStoreT, std::forward< Args >( conv_params )... );

            if( ( status != st::ARCH_STATUS_SUCCESS ) &&
                ( st::ParticleSet_requ_prepare_conversion(
                    dst, src, SrcStoreT, DstStoreT ) ) )
            {
                status = st::ParticleSet_prepare_conversion(
                    dst, src, SrcStoreT, DstStoreT );

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = st::ParticleSet_convert( dst, src, SrcStoreT,
                        DstStoreT, std::forward< Args >( conv_params )... );
                }
            }

            return status;
        }
    };

    /* ********************************************************************* */
    /* TParticleSet< R, I > */

    template< class R, class I, class DstT,
              SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT >
    struct ObjDataAllowConversionTraits< SIXTRL_CXX_NAMESPACE::TParticleSet<
        R, I >, DstT, SrcStoreT, DstStoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::TParticleSet< R, I > SrcT;

        SIXTRL_STATIC SIXTRL_FN constexpr bool allow() SIXTRL_NOEXCEPT
        {
            return ( SIXTRL_CXX_NAMESPACE::ParticleSet_allow_type_conversion<
                        SrcT, DstT >() ) &&
                   ( SrcStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL ) &&
                   ( DstStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL );
        }
    };

    template< class R, class I, class DstT,
              SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT >
    struct ObjDataConversionTypesRequireNoPrepareTraits<
        SIXTRL_CXX_NAMESPACE::TParticleSet< R, I >, DstT, SrcStoreT, DstStoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::TParticleSet< R, I > SrcT;
        static_assert( SIXTRL_CXX_NAMESPACE::ObjData_allow_type_conversion<
            SrcT, DstT, SrcStoreT, DstStoreT >(), "Illegal conversion" );

        constexpr static bool requires_no_prepare = false;
    };

    template< class R, class I, class DstT,
              SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT >
    struct ObjDataConverter< SIXTRL_CXX_NAMESPACE::TParticleSet< R, I >,
        DstT, SrcStoreT, DstStoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::TParticleSet< R, I > SrcT;
        static_assert( SIXTRL_CXX_NAMESPACE::ObjData_allow_type_conversion<
            SrcT, DstT, SrcStoreT, DstStoreT >(), "Illegal conversion" );

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool requires_prepare(
            SIXTRL_BUFFER_DATAPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
            SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ParticleSet_requ_prepare_conversion(
                dst, src, SrcStoreT, DstStoreT );
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
        prepare( SIXTRL_BUFFER_DATAPTR_DEC DstT* SIXTRL_RESTRICT dst,
                 SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ParticleSet_prepare_conversion(
                dst, src, SrcStoreT, DstStoreT );
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool allow(
            SIXTRL_BUFFER_DATAPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
            SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ParticleSet_allow_conversion(
                dst, src, SrcStoreT, DstStoreT );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t attempt_conversion(
            SIXTRL_BUFFER_DATAPTR_DEC DstT* SIXTRL_RESTRICT dst,
            SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
            Args&&... conv_params ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ParticleSet_convert( dst, src,
                SrcStoreT, DstStoreT, std::forward< Args >( conv_params )... );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t perform(
            SIXTRL_BUFFER_DATAPTR_DEC DstT* SIXTRL_RESTRICT dst,
            SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
            Args&&... conv_params ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            st::arch_status_t status = st::ParticleSet_convert( dst, src,
                SrcStoreT, DstStoreT, std::forward< Args >( conv_params )... );

            if( ( status != st::ARCH_STATUS_SUCCESS ) &&
                ( st::ParticleSet_requ_prepare_conversion(
                    dst, src, SrcStoreT, DstStoreT ) ) )
            {
                status = st::ParticleSet_prepare_conversion(
                    dst, src, SrcStoreT, DstStoreT );

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = st::ParticleSet_convert( dst, src, SrcStoreT,
                        DstStoreT, std::forward< Args >( conv_params )... );
                }
            }

            return status;
        }
    };

    /* ********************************************************************* */
    /* TVectorParticleSet< R, I, RAlloc, IAlloc > */

    template< class R, class I, class RAlloc, class IAlloc, class DstT,
              SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT >
    struct ObjDataAllowConversionTraits<
        SIXTRL_CXX_NAMESPACE::TVectorParticleSet< R, I, RAlloc, IAlloc >, DstT,
        SrcStoreT, DstStoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::TVectorParticleSet<
                    R, I, RAlloc, IAlloc > SrcT;

        SIXTRL_STATIC SIXTRL_FN constexpr bool allow() SIXTRL_NOEXCEPT
        {
            return ( SIXTRL_CXX_NAMESPACE::ParticleSet_allow_type_conversion<
                        SrcT, DstT >() ) &&
                   ( SrcStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL ) &&
                   ( DstStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL );
        }
    };

    template< class R, class I, class RAlloc, class IAlloc, class DstT,
              SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT >
    struct ObjDataConversionTypesRequireNoPrepareTraits<
        SIXTRL_CXX_NAMESPACE::TVectorParticleSet< R, I, RAlloc, IAlloc >, DstT,
        SrcStoreT, DstStoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::TVectorParticleSet<
            R, I, RAlloc, IAlloc > SrcT;

        static_assert( SIXTRL_CXX_NAMESPACE::ObjData_allow_type_conversion<
            SrcT, DstT, SrcStoreT, DstStoreT >(), "Illegal conversion" );

        constexpr static bool requires_no_prepare = false;
    };

    template< class R, class I, class RAlloc, class IAlloc, class DstT,
              SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT >
    struct ObjDataConverter< SIXTRL_CXX_NAMESPACE::TVectorParticleSet< R, I,
        RAlloc, IAlloc >, DstT, SrcStoreT, DstStoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::TVectorParticleSet<
                    R, I, RAlloc, IAlloc > SrcT;

        static_assert( SIXTRL_CXX_NAMESPACE::ObjData_allow_type_conversion<
            SrcT, DstT, SrcStoreT, DstStoreT >(), "Illegal conversion" );

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool requires_prepare(
            SIXTRL_BUFFER_DATAPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
            SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ParticleSet_requ_prepare_conversion(
                dst, src, SrcStoreT, DstStoreT );
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
        prepare( SIXTRL_BUFFER_DATAPTR_DEC DstT* SIXTRL_RESTRICT dst,
                 SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ParticleSet_prepare_conversion(
                dst, src, SrcStoreT, DstStoreT );
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool allow(
            SIXTRL_BUFFER_DATAPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
            SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ParticleSet_allow_conversion(
                dst, src, SrcStoreT, DstStoreT );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t attempt_conversion(
            SIXTRL_BUFFER_DATAPTR_DEC DstT* SIXTRL_RESTRICT dst,
            SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
            Args&&... conv_params ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ParticleSet_convert( dst, src,
                SrcStoreT, DstStoreT, std::forward< Args >( conv_params )... );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t perform(
            SIXTRL_BUFFER_DATAPTR_DEC DstT* SIXTRL_RESTRICT dst,
            SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
            Args&&... conv_params ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            st::arch_status_t status = st::ParticleSet_convert( dst, src,
                SrcStoreT, DstStoreT, std::forward< Args >( conv_params )... );

            if( ( status != st::ARCH_STATUS_SUCCESS ) &&
                ( st::ParticleSet_requ_prepare_conversion(
                    dst, src, SrcStoreT, DstStoreT ) ) )
            {
                status = st::ParticleSet_prepare_conversion(
                    dst, src, SrcStoreT, DstStoreT );

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = st::ParticleSet_convert( dst, src, SrcStoreT,
                        DstStoreT, std::forward< Args >( conv_params )... );
                }
            }

            return status;
        }
    };
}

template< class SrcT, class DstT >
SIXTRL_STATIC SIXTRL_FN constexpr bool NS(ParticleSet_allow_type_conversion)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT
        SIXTRL_UNUSED( dst ) = SIXTRL_NULLPTR,
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT
        SIXTRL_UNUSED( src ) = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::ParticleSet_allow_type_conversion<
        SrcT, DstT >();
}

template< class SrcT, class DstT >
SIXTRL_STATIC SIXTRL_FN constexpr bool
NS(ParticleSet_type_conv_can_requ_prepare)(
    SIXTRL_BUFFER_DATAPTR_DEC const DstT *const SIXTRL_RESTRICT
        SIXTRL_UNUSED( dest ) = SIXTRL_NULLPTR,
    SIXTRL_BUFFER_DATAPTR_DEC const SrcT *const SIXTRL_RESTRICT
        SIXTRL_UNUSED( src ) = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::ParticleSet_type_conv_can_requ_prepare<
        SrcT, DstT >();
}

template< class SrcT, class DstT,
          SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT =
              SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
          SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT =
              SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT >
SIXTRL_STATIC SIXTRL_FN constexpr bool NS(ParticleSet_requ_prepare_conversion)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const DstT *const
        SIXTRL_RESTRICT /* dst */,
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const SrcT *const
        SIXTRL_RESTRICT /* src */ ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::ParticleSet_requ_prepare_conversion<
        SrcT, DstT, SrcStoreT, DstStoreT >();
}

template< class SrcT, class DstT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(ParticleSet_prepare_conversion)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
    SIXTRL_CXX_NAMESPACE::store_backend_t src_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
    SIXTRL_CXX_NAMESPACE::store_backend_t dst_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::ParticleSet_prepare_conversion(
        dst, src, src_store_be, dst_store_be );
}

template< class SrcT, class DstT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool NS(ParticleSet_allow_conversion)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT dst,
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
    SIXTRL_CXX_NAMESPACE::store_backend_t const src_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
    SIXTRL_CXX_NAMESPACE::store_backend_t const dst_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::ParticleSet_allow_conversion(
        dst, src, src_store_be, dst_store_be );
}

template< class SrcT, class DstT, typename... Args >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(ParticleSet_convert)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
    SIXTRL_CXX_NAMESPACE::store_backend_t const src_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
    SIXTRL_CXX_NAMESPACE::store_backend_t const dst_store_be =
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
    Args&&... conv_parameters )
{
    return SIXTRL_CXX_NAMESPACE::ParticleSet_convert( dst, src, src_store_be,
        dst_store_be, std::forward< Args >( conv_parameters )... );
}

#endif /* defined( __cplusplus ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC SIXTRL_FN bool NS(ParticleSet_allow_type_conversion)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(ParticleSet_type_conv_can_requ_prepare)(
    void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(ParticleSet_requ_prepare_conversion)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const NS(ParticleSet) *const
        SIXTRL_RESTRICT dst,
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const NS(ParticleSet) *const
        SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(ParticleSet_prepare_conversion)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)* SIXTRL_RESTRICT dst,
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const NS(ParticleSet) *const
        SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(ParticleSet_allow_conversion)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const NS(ParticleSet) *const
        SIXTRL_RESTRICT dst,
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const NS(ParticleSet) *const
        SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be  ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(ParticleSet_convert)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)* SIXTRL_RESTRICT dst,
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const NS(ParticleSet) *const
        SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!!!        Inline Methods and Functions Implementations       !!!!!!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_INLINE bool NS(ParticleSet_allow_type_conversion)(
    void ) SIXTRL_NOEXCEPT
{
    return true;
}

SIXTRL_INLINE bool NS(ParticleSet_type_conv_can_requ_prepare)(
    void ) SIXTRL_NOEXCEPT
{
    return true;
}

SIXTRL_INLINE bool NS(ParticleSet_requ_prepare_conversion)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const NS(ParticleSet) *const
        SIXTRL_RESTRICT dst,
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const NS(ParticleSet) *const
        SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( NS(ParticleSet_allow_type_conversion)() );

    SIXTRL_ASSERT( src_store_be != (
        NS(store_backend_t ) )SIXTRL_STORAGE_BE_ILLEGAL );

    SIXTRL_ASSERT( dst_store_be != (
        NS(store_backend_t ) )SIXTRL_STORAGE_BE_ILLEGAL );

    SIXTRL_ASSERT( dst != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( src != SIXTRL_NULLPTR );

    ( void )src_store_be;
    ( void )dst_store_be;

    return ( ( src != dst ) && ( NS(ParticleSet_capacity)( dst ) <
               NS(ParticleSet_num_particles)( src ) ) );
}

SIXTRL_INLINE NS(arch_status_t) NS(ParticleSet_prepare_conversion)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)* SIXTRL_RESTRICT dst,
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const NS(ParticleSet) *const
        SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    if( ( src != SIXTRL_NULLPTR ) && ( dst != SIXTRL_NULLPTR ) &&
        ( src_store_be != ( NS(store_backend_t) )SIXTRL_STORAGE_BE_ILLEGAL ) &&
        ( dst_store_be != ( NS(store_backend_t) )SIXTRL_STORAGE_BE_ILLEGAL ) )
    {
        status = NS(ParticleSet_set_capacity)(
            dst, NS(ParticleSet_capacity)( src ) );
    }

    return status;
}

SIXTRL_INLINE bool NS(ParticleSet_allow_conversion)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const NS(ParticleSet) *const
        SIXTRL_RESTRICT dst,
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const NS(ParticleSet) *const
        SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be  ) SIXTRL_NOEXCEPT
{
    return (
        ( src_store_be != ( NS(store_backend_t) )SIXTRL_STORAGE_BE_ILLEGAL ) &&
        ( dst_store_be != ( NS(store_backend_t) )SIXTRL_STORAGE_BE_ILLEGAL ) &&
        ( src != SIXTRL_NULLPTR ) && ( dst != SIXTRL_NULLPTR ) &&
        ( NS(ParticleSet_capacity)( dst ) >=
          NS(ParticleSet_num_particles)( src ) ) );
}

SIXTRL_INLINE NS(arch_status_t) NS(ParticleSet_convert)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)* SIXTRL_RESTRICT dst,
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const NS(ParticleSet) *const
        SIXTRL_RESTRICT src,
    NS(store_backend_t) const src_store_be,
    NS(store_backend_t) const dst_store_be ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    if( NS(ParticleSet_allow_conversion)(
            dst, src, src_store_be, dst_store_be ) )
    {
        status = NS(ParticleSet_set_num_particles)(
            dst, NS(ParticleSet_num_particles)( src ) );

        status |= NS(ParticleSet_set_x)(
            dst, NS(ParticleSet_const_x_begin)( src ) );

        status |= NS(ParticleSet_set_px)(
            dst, NS(ParticleSet_const_px_begin)( src ) );

        status |= NS(ParticleSet_set_y)(
            dst, NS(ParticleSet_const_y_begin)( src ) );

        status |= NS(ParticleSet_set_py)(
            dst, NS(ParticleSet_const_py_begin)( src ) );

        status |= NS(ParticleSet_set_zeta)(
            dst, NS(ParticleSet_const_zeta_begin)( src ) );

        status |= NS(ParticleSet_set_delta)(
            dst, NS(ParticleSet_const_delta_begin)( src ) );

        status |= NS(ParticleSet_set_state)(
            dst, NS(ParticleSet_const_state_begin)( src ) );

        status |= NS(ParticleSet_set_at_element)(
            dst, NS(ParticleSet_const_at_element_begin)( src ) );

        status |= NS(ParticleSet_set_at_turn)(
            dst, NS(ParticleSet_const_at_turn_begin)( src ) );

        status |= NS(ParticleSet_set_particle_id)(
            dst, NS(ParticleSet_const_particle_id_begin)( src ) );

        status |= NS(ParticleSet_set_psigma)(
            dst, NS(ParticleSet_const_psigma_begin)( src ) );

        status |= NS(ParticleSet_set_rpp)(
            dst, NS(ParticleSet_const_rpp_begin)( src ) );

        status |= NS(ParticleSet_set_rvv)(
            dst, NS(ParticleSet_const_rvv_begin)( src ) );

        status |= NS(ParticleSet_set_chi)(
            dst, NS(ParticleSet_const_chi_begin)( src ) );

        status |= NS(ParticleSet_set_charge_ratio)(
            dst, NS(ParticleSet_const_charge_ratio_begin)( src ) );

        status |= NS(ParticleSet_set_charge0)(
            dst, NS(ParticleSet_const_charge0_begin)( src ) );

        status |= NS(ParticleSet_set_mass0)(
            dst, NS(ParticleSet_const_mass0_begin)( src ) );

        status |= NS(ParticleSet_set_beta0)(
            dst, NS(ParticleSet_const_beta0_begin)( src ) );

        status |= NS(ParticleSet_set_gamma0)(
            dst, NS(ParticleSet_const_gamma0_begin)( src ) );

        status |= NS(ParticleSet_set_pc0)(
            dst, NS(ParticleSet_const_pc0_begin)( src ) );

        status |= NS(ParticleSet_set_s)(
            dst, NS(ParticleSet_const_s_begin)( src ) );
    }

    return status;
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SET_CONVERT_CXX_HPP__ */
