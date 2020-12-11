#ifndef SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_UNIT_COMPARE_H__
#define SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_UNIT_COMPARE_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <type_traits>
        #include <limits>
    #endif /* C++ */
#endif /* #if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles/particle_unit.h"
    #include "sixtracklib/common/particles/particle_unit.hpp"
    #include "sixtracklib/common/particles/particle_unit_api.h"
    #include "sixtracklib/common/particles/particle_unit_derived_api.h"
    #include "sixtracklib/common/particles/particle_unit_init.h"
    #include "sixtracklib/common/particles/particle_unit_convert.h"
    #include "sixtracklib/common/internal/compiler_attributes.h"
    #include "sixtracklib/common/internal/math_constants.h"
    #include "sixtracklib/common/internal/math_functions.h"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
    #include "sixtracklib/common/internal/type_comparison_helpers.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class LhsT, class RhsT, class DiffT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< RhsT >()  ||
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< LhsT >()  ||
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< DiffT >() ||
        !SIXTRL_CXX_NAMESPACE::Particle_allow_type_conversion< LhsT, DiffT >() ||
        !SIXTRL_CXX_NAMESPACE::Particle_allow_type_conversion< RhsT, DiffT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Particle_diff( SIXTRL_PARTICLE_ARGPTR_DEC DiffT*
        SIXTRL_RESTRICT SIXTRL_UNUSED( diff ),
        SIXTRL_PARTICLE_ARGPTR_DEC const LhsT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( lhs ),
        SIXTRL_PARTICLE_ARGPTR_DEC const RhsT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( rhs ) ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class LhsT, class RhsT, class DiffT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< RhsT >()  &&
        SIXTRL_CXX_NAMESPACE::Particle_is_type< LhsT >()  &&
        SIXTRL_CXX_NAMESPACE::Particle_is_type< DiffT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_allow_type_conversion< LhsT, DiffT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_allow_type_conversion< RhsT, DiffT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Particle_diff( SIXTRL_PARTICLE_ARGPTR_DEC DiffT* SIXTRL_RESTRICT diff,
        SIXTRL_PARTICLE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
        SIXTRL_PARTICLE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        typedef typename ParticleTraits< DiffT >::real_t  real_t;
        /* TODO: Implement "safe" arithmetic to prevent overflows */

        if( diff != SIXTRL_NULLPTR )
        {
            if( lhs != SIXTRL_NULLPTR )
            {
                if( st::Particle_allow_conversion( diff, lhs ) )
                {
                    status = st::Particle_convert( diff, lhs );
                }

                if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                    ( rhs != SIXTRL_NULLPTR ) )
                {
                    status  = st::Particle_subtract_from_x(
                        diff, st::Particle_x( rhs ) );

                    status |= st::Particle_subtract_from_px(
                        diff, st::Particle_px( rhs ) );

                    status |= st::Particle_subtract_from_y(
                        diff, st::Particle_y( rhs ) );

                    status |= st::Particle_subtract_from_py(
                        diff, st::Particle_py( rhs ) );

                    status |= st::Particle_subtract_from_zeta(
                        diff, st::Particle_zeta( rhs ) );

                    status |= st::Particle_subtract_from_delta(
                        diff, st::Particle_delta( rhs ) );

                    status |= st::Particle_subtract_from_state(
                        diff, st::Particle_state( rhs ) );

                    status |= st::Particle_subtract_from_at_element(
                        diff, st::Particle_at_element( rhs ) );

                    status |= st::Particle_subtract_from_at_turn(
                        diff, st::Particle_at_turn( rhs ) );

                    status |= st::Particle_subtract_from_id(
                        diff, st::Particle_id( rhs ) );

                    status |= st::Particle_subtract_from_psigma(
                        diff, st::Particle_psigma( rhs ) );

                    status |= st::Particle_subtract_from_rpp(
                        diff, st::Particle_rpp( rhs ) );

                    status |= st::Particle_subtract_from_rvv(
                        diff, st::Particle_rvv( rhs ) );

                    status |= st::Particle_subtract_from_psigma(
                        diff, st::Particle_psigma( rhs ) );

                    status |= st::Particle_subtract_from_chi(
                        diff, st::Particle_chi( rhs ) );

                    status |= st::Particle_subtract_from_charge_ratio(
                        diff, st::Particle_charge_ratio( rhs ) );

                    status |= st::Particle_subtract_from_charge0(
                        diff, st::Particle_charge0( rhs ) );

                    status |= st::Particle_subtract_from_mass0(
                        diff, st::Particle_mass0( rhs ) );

                    status |= st::Particle_subtract_from_beta0(
                        diff, st::Particle_beta0( rhs ) );

                    status |= st::Particle_subtract_from_gamma0(
                        diff, st::Particle_gamma0( rhs ) );

                    status |= st::Particle_subtract_from_pc0(
                        diff, st::Particle_pc0( rhs ) );

                    status |= st::Particle_subtract_from_s(
                        diff, st::Particle_s( rhs ) );
                }
            }
            else if( rhs != SIXTRL_NULLPTR )
            {
                if( st::Particle_allow_conversion( diff, rhs ) )
                {
                    status = st::Particle_convert( diff, rhs );
                }

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status  = st::Particle_scale_x( diff, real_t{ -1 } );
                    status |= st::Particle_scale_px( diff, real_t{ -1 } );
                    status |= st::Particle_scale_y( diff, real_t{ -1 } );
                    status |= st::Particle_scale_py( diff, real_t{ -1 } );
                    status |= st::Particle_scale_zeta( diff, real_t{ -1 } );
                    status |= st::Particle_scale_delta( diff, real_t{ -1 } );

                    status |= st::Particle_set_state(
                        diff, -( st::Particle_state( rhs ) ) );

                    status |= st::Particle_set_at_element(
                        diff, -( st::Particle_at_element( rhs ) ) );

                    status |= st::Particle_set_at_turn(
                        diff, -( st::Particle_at_turn( rhs ) ) );

                    status |= st::Particle_set_id(
                        diff, -( st::Particle_id( rhs ) ) );

                    status |= st::Particle_scale_psigma( diff, real_t{ -1 } );
                    status |= st::Particle_scale_rpp( diff, real_t{ -1 } );
                    status |= st::Particle_scale_rvv( diff, real_t{ -1 } );
                    status |= st::Particle_scale_chi( diff, real_t{ -1 } );
                    status |= st::Particle_scale_charge_ratio(
                        diff, real_t{ -1 } );

                    status |= st::Particle_scale_charge0( diff, real_t{ -1 } );
                    status |= st::Particle_scale_mass0( diff, real_t{ -1 } );
                    status |= st::Particle_scale_beta0( diff, real_t{ -1 } );
                    status |= st::Particle_scale_gamma0( diff, real_t{ -1 } );
                    status |= st::Particle_scale_pc0( diff, real_t{ -1 } );
                    status |= st::Particle_scale_s( diff, real_t{ -1 } );
                }
            }
        }

        return status;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class LhsT, class RhsT, typename cmp_result_t = typename
        SIXTRL_CXX_NAMESPACE::TypeCompLogicTypeTraits< typename
            SIXTRL_CXX_NAMESPACE::ParticleTraits< LhsT >::real_t
                >::cmp_result_t >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< RhsT >() ||
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< LhsT >(),
        cmp_result_t >::type
    Particle_compare(
        SIXTRL_PARTICLE_ARGPTR_DEC const LhsT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( lhs ),
        SIXTRL_PARTICLE_ARGPTR_DEC const RhsT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( rhs ) ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::TypeCompResultTraits<
            cmp_result_t >::CMP_LHS_SMALLER_RHS;
    }

    template< class LhsT, class RhsT, typename cmp_result_t =
         typename SIXTRL_CXX_NAMESPACE::TypeCompLogicTypeTraits< typename
             SIXTRL_CXX_NAMESPACE::ParticleTraits< LhsT >::real_t
                 >::cmp_result_t >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< RhsT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_is_type< LhsT >(),
        cmp_result_t >::type
    Particle_compare(
        SIXTRL_PARTICLE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
        SIXTRL_PARTICLE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        typedef typename ParticleTraits< LhsT >::real_t  lhs_real_t;
        typedef typename ParticleTraits< LhsT >::index_t lhs_index_t;
        typedef typename ParticleTraits< RhsT >::real_t  rhs_real_t;
        typedef typename ParticleTraits< RhsT >::index_t rhs_index_t;
        typedef st::TypeCompResultTraits< cmp_result_t > cmp_traits_t;

        cmp_result_t cmp_result = cmp_traits_t::CMP_LHS_SMALLER_RHS;

        if( ( rhs != SIXTRL_NULLPTR ) && ( lhs != SIXTRL_NULLPTR ) )
        {
            cmp_result = st::Type_value_comp_result< lhs_real_t,
                cmp_result_t, rhs_real_t >( st::Particle_x( rhs ),
                    st::Particle_x( lhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_real_t,
                    cmp_result_t, rhs_real_t >( st::Particle_px( rhs ),
                        st::Particle_px( lhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_real_t,
                    cmp_result_t, rhs_real_t >( st::Particle_y( rhs ),
                        st::Particle_y( lhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_real_t,
                    cmp_result_t, rhs_real_t >( st::Particle_py( rhs ),
                        st::Particle_py( lhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_real_t,
                    cmp_result_t, rhs_real_t >( st::Particle_zeta( rhs ),
                        st::Particle_zeta( lhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_real_t,
                    cmp_result_t, rhs_real_t >( st::Particle_delta( rhs ),
                        st::Particle_delta( lhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_index_t,
                    cmp_result_t, rhs_index_t >( st::Particle_state( rhs ),
                        st::Particle_state( lhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_index_t,
                    cmp_result_t, rhs_index_t >( st::Particle_at_element( rhs ),
                        st::Particle_at_element( lhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_index_t,
                    cmp_result_t, rhs_index_t >( st::Particle_at_turn( rhs ),
                        st::Particle_at_turn( lhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_index_t,
                    cmp_result_t, rhs_index_t >( st::Particle_id( rhs ),
                        st::Particle_id( lhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_real_t,
                    cmp_result_t, rhs_real_t >( st::Particle_psigma( rhs ),
                        st::Particle_psigma( lhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_real_t,
                    cmp_result_t, rhs_real_t >( st::Particle_rpp( rhs ),
                        st::Particle_rpp( lhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_real_t,
                    cmp_result_t, rhs_real_t >( st::Particle_rvv( rhs ),
                        st::Particle_rvv( lhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_real_t,
                    cmp_result_t, rhs_real_t >( st::Particle_chi( rhs ),
                        st::Particle_chi( lhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_real_t,
                    cmp_result_t, rhs_real_t >( st::Particle_charge_ratio( rhs ),
                        st::Particle_charge_ratio( lhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_real_t,
                    cmp_result_t, rhs_real_t >( st::Particle_charge0( rhs ),
                        st::Particle_charge0( lhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_real_t,
                    cmp_result_t, rhs_real_t >( st::Particle_mass0( rhs ),
                        st::Particle_mass0( lhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_real_t,
                    cmp_result_t, rhs_real_t >( st::Particle_beta0( rhs ),
                        st::Particle_beta0( lhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_real_t,
                    cmp_result_t, rhs_real_t >( st::Particle_gamma0( rhs ),
                        st::Particle_gamma0( lhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_real_t,
                    cmp_result_t, rhs_real_t >( st::Particle_pc0( rhs ),
                        st::Particle_pc0( lhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_real_t,
                    cmp_result_t, rhs_real_t >( st::Particle_s( rhs ),
                        st::Particle_s( lhs ) );
        }
        else if( lhs != SIXTRL_NULLPTR )
        {
            cmp_result = cmp_traits_t::CMP_LHS_LARGER_RHS;
        }

        return cmp_result;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class LhsT, class RhsT, typename cmp_result_t =
        typename SIXTRL_CXX_NAMESPACE::TypeCompLogicTypeTraits< typename
        SIXTRL_CXX_NAMESPACE::ParticleTraits< LhsT >::real_t >::cmp_result_t >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< RhsT >() ||
        !SIXTRL_CXX_NAMESPACE::Particle_is_type< LhsT >(),
        cmp_result_t >::type
    Particle_compare_with_tolerances(
        SIXTRL_PARTICLE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT /*lhs*/,
        SIXTRL_PARTICLE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT /*rhs*/,
        typename TypeMethodParamTraits< typename ParticleTraits< RhsT >::real_t
            >::const_argument_type /*rel_tol*/,
        typename TypeMethodParamTraits< typename ParticleTraits< RhsT >::real_t
            >::const_argument_type /*abs_tol*/ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::TypeCompResultTraits<
            cmp_result_t >::CMP_LHS_SMALLER_RHS;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class LhsT, class RhsT, typename cmp_result_t =
        typename SIXTRL_CXX_NAMESPACE::TypeCompLogicTypeTraits< typename
        SIXTRL_CXX_NAMESPACE::ParticleTraits< LhsT >::real_t >::cmp_result_t >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Particle_is_type< RhsT >() &&
        SIXTRL_CXX_NAMESPACE::Particle_is_type< LhsT >(),
        cmp_result_t >::type
    Particle_compare_with_tolerances(
        SIXTRL_PARTICLE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT lhs,
        SIXTRL_PARTICLE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs,
        typename TypeMethodParamTraits< typename ParticleTraits< RhsT >::real_t
            >::const_argument_type rel_tol,
        typename TypeMethodParamTraits< typename ParticleTraits< RhsT >::real_t
            >::const_argument_type abs_tol )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename st::ParticleTraits< LhsT >::real_t  lhs_real_t;
        typedef typename st::ParticleTraits< LhsT >::index_t lhs_index_t;
        typedef typename st::ParticleTraits< RhsT >::real_t  rhs_real_t;
        typedef typename st::ParticleTraits< RhsT >::index_t rhs_index_t;

        typedef st::TypeCompResultTraits< cmp_result_t > cmp_traits_t;

        SIXTRL_ASSERT( lhs != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( rhs != SIXTRL_NULLPTR );

        cmp_result_t cmp_result = cmp_traits_t::CMP_LHS_SMALLER_RHS;

        if( ( lhs != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) )
        {
            cmp_result = st::Type_value_comp_result< lhs_real_t,
                    cmp_result_t, rhs_real_t >( st::Particle_x( lhs ),
                        st::Particle_x( rhs ), rel_tol, abs_tol );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_real_t,
                    cmp_result_t, rhs_real_t >( st::Particle_px( lhs ),
                        st::Particle_px( rhs ), rel_tol, abs_tol );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_real_t,
                    cmp_result_t, rhs_real_t >( st::Particle_y( lhs ),
                        st::Particle_y( rhs ), rel_tol, abs_tol );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_real_t,
                    cmp_result_t, rhs_real_t >( st::Particle_py( lhs ),
                        st::Particle_py( rhs ), rel_tol, abs_tol );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_real_t,
                    cmp_result_t, rhs_real_t >( st::Particle_zeta( lhs ),
                        st::Particle_zeta( rhs ), rel_tol, abs_tol );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_real_t,
                    cmp_result_t, rhs_real_t >( st::Particle_delta( lhs ),
                        st::Particle_delta( rhs ), rel_tol, abs_tol );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_index_t,
                    cmp_result_t, rhs_index_t >( st::Particle_state( lhs ),
                         st::Particle_state( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_index_t,
                    cmp_result_t, rhs_index_t >( st::Particle_at_element( lhs ),
                        st::Particle_at_element( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_index_t,
                    cmp_result_t, rhs_index_t >( st::Particle_at_turn( lhs ),
                        st::Particle_at_turn( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_index_t,
                    cmp_result_t, rhs_index_t >( st::Particle_id( lhs ),
                        st::Particle_id( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_real_t,
                    cmp_result_t, rhs_real_t >( st::Particle_psigma( lhs ),
                        st::Particle_psigma( rhs ), rel_tol, abs_tol );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_real_t,
                    cmp_result_t, rhs_real_t >( st::Particle_rpp( lhs ),
                        st::Particle_rpp( rhs ), rel_tol, abs_tol );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_real_t,
                    cmp_result_t, rhs_real_t >( st::Particle_rvv( lhs ),
                        st::Particle_rvv( rhs ), rel_tol, abs_tol );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_real_t,
                    cmp_result_t, rhs_real_t >( st::Particle_chi( lhs ),
                        st::Particle_chi( rhs ), rel_tol, abs_tol );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_real_t,
                    cmp_result_t, rhs_real_t >( st::Particle_charge_ratio( lhs ),
                        st::Particle_charge_ratio( rhs ), rel_tol, abs_tol );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_real_t,
                    cmp_result_t, rhs_real_t >( st::Particle_charge0( lhs ),
                        st::Particle_charge0( rhs ), rel_tol, abs_tol );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_real_t,
                    cmp_result_t, rhs_real_t >( st::Particle_mass0( lhs ),
                        st::Particle_mass0( rhs ), rel_tol, abs_tol );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_real_t,
                    cmp_result_t, rhs_real_t >( st::Particle_beta0( lhs ),
                        st::Particle_beta0( rhs ), rel_tol, abs_tol );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_real_t,
                    cmp_result_t, rhs_real_t >( st::Particle_gamma0( lhs ),
                        st::Particle_gamma0( rhs ), rel_tol, abs_tol );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_real_t,
                    cmp_result_t, rhs_real_t >( st::Particle_pc0( lhs ),
                        st::Particle_pc0( rhs ), rel_tol, abs_tol );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
                cmp_result = st::Type_value_comp_result< lhs_real_t,
                    cmp_result_t, rhs_real_t >( st::Particle_s( lhs ),
                        st::Particle_s( rhs ), rel_tol, abs_tol );
        }
        else if( lhs != SIXTRL_NULLPTR )
        {
            cmp_result = cmp_traits_t::CMP_LHS_LARGER_RHS;
        }

        return cmp_result;
    }

    /* ********************************************************************* */
    /* LHS: NS(Particle) */

    template< class RhsT  >
    struct ObjDataComparisonHelper< ::NS(Particle), RhsT,
        typename ObjDataLogicTypeTraits< ::NS(Particle) >::cmp_result_t,
        typename std::enable_if< SIXTRL_CXX_NAMESPACE::Particle_is_type<
            RhsT >(), void >::type >
    {
        typedef ::NS(Particle) LhsT;
        typedef typename ObjDataLogicTypeTraits< ::NS(Particle) >::cmp_result_t
                cmp_result_t;

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN cmp_result_t compare(
            SIXTRL_PARTICLE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_PARTICLE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Particle_compare<
                LhsT, RhsT, cmp_result_t >( lhs, rhs );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        cmp_result_t compare_with_tolerances(
            SIXTRL_PARTICLE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_PARTICLE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs,
            Args&&... tolerances ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Particle_compare_with_tolerances<
                LhsT, RhsT, cmp_result_t >( lhs, rhs, std::forward< Args >(
                    tolerances )... );
        }
    };

    template< class RhsT, class DiffT >
    struct ObjDataDiffHelper< ::NS(Particle), RhsT, DiffT,
        typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::Particle_is_type< RhsT >() &&
            SIXTRL_CXX_NAMESPACE::Particle_is_type< DiffT >(), void >::type >
    {
        typedef ::NS(Particle) LhsT;

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
        calculate(
            SIXTRL_PARTICLE_ARGPTR_DEC DiffT* SIXTRL_RESTRICT diff,
            SIXTRL_PARTICLE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_PARTICLE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Particle_diff( diff, lhs, rhs );
        }
    };

    /* --------------------------------------------------------------------- */
    /*  LHS: TParticle< R, I, RAlign, IAlign > */

    template< class R, class I, SIXTRL_CXX_NAMESPACE::arch_size_t N,
              SIXTRL_CXX_NAMESPACE::arch_size_t RAlign,
              SIXTRL_CXX_NAMESPACE::arch_size_t IAlign, class RhsT >
    struct ObjDataComparisonHelper<
        SIXTRL_CXX_NAMESPACE::TParticle< R, I, N, RAlign, IAlign >, RhsT,
        typename ObjDataLogicTypeTraits< SIXTRL_CXX_NAMESPACE::TParticle<
            R, I, N, RAlign, IAlign > >::cmp_result_t,
        typename std::enable_if< SIXTRL_CXX_NAMESPACE::Particle_is_type<
            RhsT >(), void >::type >
    {
        typedef SIXTRL_CXX_NAMESPACE::TParticle<
                    R, I, N, RAlign, IAlign > LhsT;

        typedef typename ObjDataLogicTypeTraits< LhsT >::cmp_result_t
                cmp_result_t;

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN cmp_result_t compare(
            SIXTRL_PARTICLE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_PARTICLE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Particle_compare<
                LhsT, RhsT, cmp_result_t >( lhs, rhs );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        cmp_result_t compare_with_tolerances(
            SIXTRL_PARTICLE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_PARTICLE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs,
            Args&&... tolerances ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Particle_compare_with_tolerances<
                LhsT, RhsT, cmp_result_t >( lhs, rhs, std::forward< Args >(
                    tolerances )... );
        }
    };

    template< class R, class I, SIXTRL_CXX_NAMESPACE::arch_size_t N,
              SIXTRL_CXX_NAMESPACE::arch_size_t RAlign,
              SIXTRL_CXX_NAMESPACE::arch_size_t IAlign,
              class RhsT, class DiffT >
    struct ObjDataDiffHelper<
        SIXTRL_CXX_NAMESPACE::TParticle< R, I, N, RAlign, IAlign >, RhsT, DiffT,
        typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::Particle_is_type< RhsT >() &&
            SIXTRL_CXX_NAMESPACE::Particle_is_type< DiffT >(), void >::type >
    {
        typedef SIXTRL_CXX_NAMESPACE::TParticle< R, I, N, RAlign, IAlign > LhsT;

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
        calculate(
            SIXTRL_PARTICLE_ARGPTR_DEC DiffT* SIXTRL_RESTRICT diff,
            SIXTRL_PARTICLE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_PARTICLE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::Particle_diff( diff, lhs, rhs );
        }
    };
}

template< class LhsT, class RhsT, class DiffT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(Particle_diff)( SIXTRL_PARTICLE_ARGPTR_DEC DiffT* SIXTRL_RESTRICT diff,
    SIXTRL_PARTICLE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs )
{
    return SIXTRL_CXX_NAMESPACE::Particle_diff( diff, lhs, rhs );
}

template< class LhsT, class RhsT, typename cmp_result_t = typename
    SIXTRL_CXX_NAMESPACE::TypeCompLogicTypeTraits< typename
        SIXTRL_CXX_NAMESPACE::ParticleTraits< LhsT >::real_t >::cmp_result_t >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN cmp_result_t NS(Particle_compare)(
    SIXTRL_PARTICLE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs )
{
    return SIXTRL_CXX_NAMESPACE::Particle_compare<
        LhsT, RhsT, cmp_result_t >( lhs, rhs );
}

template< class LhsT, class RhsT, typename cmp_result_t = typename
     SIXTRL_CXX_NAMESPACE::TypeCompLogicTypeTraits< typename
         SIXTRL_CXX_NAMESPACE::ParticleTraits< LhsT >::real_t >::cmp_result_t >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN cmp_result_t
NS(Particle_compare_with_tolerances)(
    SIXTRL_PARTICLE_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLE_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs,
    typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
        SIXTRL_CXX_NAMESPACE::ParticleTraits< RhsT >::real_t
            >::const_argument_type rel_tol,
    typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
        SIXTRL_CXX_NAMESPACE::ParticleTraits< RhsT >::real_t
            >::const_argument_type abs_tol )
{
    return SIXTRL_CXX_NAMESPACE::Particle_compare_with_tolerances<
        LhsT, RhsT, cmp_result_t >( lhs, rhs, rel_tol, abs_tol );
}

#endif /* C++ */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(Particle_diff)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT diff,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN int NS(Particle_compare)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN int NS(Particle_compare_with_tolerances)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT rhs,
    NS(particle_real_t) const rel_tol, NS(particle_real_t) const abs_tol
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

SIXTRL_INLINE NS(arch_status_t) NS(Particle_diff)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particle)* SIXTRL_RESTRICT diff,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT
{
    typedef NS(particle_real_t) real_t;
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    if( diff != SIXTRL_NULLPTR )
    {
        if( lhs != SIXTRL_NULLPTR )
        {
            if( NS(Particle_allow_conversion)( diff, lhs,
                    SIXTRL_STORAGE_BE_DEFAULT, SIXTRL_STORAGE_BE_DEFAULT ) )
            {
                status = NS(Particle_convert)( diff, lhs,
                    SIXTRL_STORAGE_BE_DEFAULT, SIXTRL_STORAGE_BE_DEFAULT );
            }

            if( ( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS ) &&
                ( rhs != SIXTRL_NULLPTR ) )
            {
                status  = NS(Particle_subtract_from_x)(
                    diff, NS(Particle_x)( rhs ) );

                status |= NS(Particle_subtract_from_px)(
                    diff, NS(Particle_px)( rhs ) );

                status |= NS(Particle_subtract_from_y)(
                    diff, NS(Particle_y)( rhs ) );

                status |= NS(Particle_subtract_from_py)(
                    diff, NS(Particle_py)( rhs ) );

                status |= NS(Particle_subtract_from_zeta)(
                    diff, NS(Particle_zeta)( rhs ) );

                status |= NS(Particle_subtract_from_delta)(
                    diff, NS(Particle_delta)( rhs ) );

                status |= NS(Particle_subtract_from_state)(
                    diff, NS(Particle_state)( rhs ) );

                status |= NS(Particle_subtract_from_at_element)(
                    diff, NS(Particle_at_element)( rhs ) );

                status |= NS(Particle_subtract_from_at_turn)(
                    diff, NS(Particle_at_turn)( rhs ) );

                status |= NS(Particle_subtract_from_id)(
                    diff, NS(Particle_id)( rhs ) );

                status |= NS(Particle_subtract_from_psigma)(
                    diff, NS(Particle_psigma)( rhs ) );

                status |= NS(Particle_subtract_from_rpp)(
                    diff, NS(Particle_rpp)( rhs ) );

                status |= NS(Particle_subtract_from_psigma)(
                    diff, NS(Particle_psigma)( rhs ) );

                status |= NS(Particle_subtract_from_chi)(
                    diff, NS(Particle_chi)( rhs ) );

                status |= NS(Particle_subtract_from_charge_ratio)(
                    diff, NS(Particle_charge_ratio)( rhs ) );

                status |= NS(Particle_subtract_from_charge0)(
                    diff, NS(Particle_charge0)( rhs ) );

                status |= NS(Particle_subtract_from_mass0)(
                    diff, NS(Particle_mass0)( rhs ) );

                status |= NS(Particle_subtract_from_beta0)(
                    diff, NS(Particle_beta0)( rhs ) );

                status |= NS(Particle_subtract_from_gamma0)(
                    diff, NS(Particle_gamma0)( rhs ) );

                status |= NS(Particle_subtract_from_pc0)(
                    diff, NS(Particle_pc0)( rhs ) );

                status |= NS(Particle_subtract_from_s)(
                    diff, NS(Particle_s)( rhs ) );
            }
        }
        else if( rhs != SIXTRL_NULLPTR )
        {
            if( NS(Particle_allow_conversion)( diff, lhs,
                    SIXTRL_STORAGE_BE_DEFAULT, SIXTRL_STORAGE_BE_DEFAULT ) )
            {
                status = NS(Particle_convert)( diff, lhs,
                    SIXTRL_STORAGE_BE_DEFAULT, SIXTRL_STORAGE_BE_DEFAULT );
            }

            if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
            {
                status  = NS(Particle_scale_x)( diff, ( real_t )-1 );
                status |= NS(Particle_scale_px)( diff, ( real_t )-1 );
                status |= NS(Particle_scale_y)( diff, ( real_t )-1 );
                status |= NS(Particle_scale_py)( diff, ( real_t )-1 );
                status |= NS(Particle_scale_zeta)( diff, ( real_t )-1 );
                status |= NS(Particle_scale_delta)( diff, ( real_t )-1 );

                status |= NS(Particle_set_state)(
                    diff, -( NS(Particle_state)( rhs ) ) );

                status |= NS(Particle_set_at_element)(
                    diff, -( NS(Particle_at_element)( rhs ) ) );

                status |= NS(Particle_set_at_turn)(
                    diff, -( NS(Particle_at_turn)( rhs ) ) );

                status |= NS(Particle_set_id)(
                    diff, -( NS(Particle_id)( rhs ) ) );

                status |= NS(Particle_scale_psigma)( diff, ( real_t )-1 );
                status |= NS(Particle_scale_rpp)( diff, ( real_t )-1 );
                status |= NS(Particle_scale_rvv)( diff, ( real_t )-1 );
                status |= NS(Particle_scale_chi)( diff, ( real_t )-1 );
                status |= NS(Particle_scale_charge_ratio)(
                    diff, ( real_t )-1 );

                status |= NS(Particle_scale_charge0)( diff, ( real_t )-1 );
                status |= NS(Particle_scale_mass0)( diff, ( real_t )-1 );
                status |= NS(Particle_scale_beta0)( diff, ( real_t )-1 );
                status |= NS(Particle_scale_gamma0)( diff, ( real_t )-1 );
                status |= NS(Particle_scale_pc0)( diff, ( real_t )-1 );
                status |= NS(Particle_scale_s)( diff, ( real_t )-1 );
            }
        }
    }

    return status;
}

SIXTRL_INLINE int NS(Particle_compare)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( lhs != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( rhs != SIXTRL_NULLPTR );

    int cmp_result = NS(Type_value_comp_result)(
        NS(Particle_x)( lhs ), NS(Particle_x)( rhs ) );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result)(
            NS(Particle_px)( lhs ), NS(Particle_px)( rhs ) );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result)(
            NS(Particle_y)( lhs ), NS(Particle_y)( rhs ) );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result)(
            NS(Particle_py)( lhs ), NS(Particle_py)( rhs ) );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result)(
            NS(Particle_zeta)( lhs ), NS(Particle_zeta)( rhs ) );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result)(
            NS(Particle_delta)( lhs ), NS(Particle_delta)( rhs ) );

    if( ( cmp_result == 0 ) &&
        ( NS(Particle_state)( lhs ) != NS(Particle_state)( rhs ) ) )
    {
        cmp_result = ( NS(Particle_state)( lhs ) < NS(Particle_state)( rhs ) )
            ? -1 : +1;
    }

    if( ( cmp_result == 0 ) &&
        ( NS(Particle_at_element)( lhs ) != NS(Particle_at_element)( rhs ) ) )
    {
        cmp_result = ( NS(Particle_at_element)( lhs ) <
            NS(Particle_at_element)( rhs ) ) ? -1 : +1;
    }

    if( ( cmp_result == 0 ) &&
        ( NS(Particle_at_turn)( lhs ) != NS(Particle_at_turn)( rhs ) ) )
    {
        cmp_result = ( NS(Particle_at_turn)( lhs ) <
            NS(Particle_at_turn)( rhs ) ) ? -1 : +1;
    }

    if( ( cmp_result == 0 ) &&
        ( NS(Particle_id)( lhs ) != NS(Particle_id)( rhs ) ) )
    {
        cmp_result = ( NS(Particle_id)( lhs ) < NS(Particle_id)( rhs ) )
            ? -1 : +1;
    }

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result)(
            NS(Particle_psigma)( lhs ), NS(Particle_psigma)( rhs ) );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result)(
            NS(Particle_rpp)( lhs ), NS(Particle_rpp)( rhs ) );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result)(
            NS(Particle_rvv)( lhs ), NS(Particle_rvv)( rhs ) );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result)(
            NS(Particle_chi)( lhs ), NS(Particle_chi)( rhs ) );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result)(
            NS(Particle_charge_ratio)( lhs ),
            NS(Particle_charge_ratio)( rhs ) );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result)(
            NS(Particle_charge0)( lhs ), NS(Particle_charge0)( rhs ) );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result)(
            NS(Particle_mass0)( lhs ), NS(Particle_mass0)( rhs ) );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result)(
            NS(Particle_beta0)( lhs ), NS(Particle_beta0)( rhs ) );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result)(
            NS(Particle_gamma0)( lhs ), NS(Particle_gamma0)( rhs ) );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result)(
            NS(Particle_pc0)( lhs ), NS(Particle_pc0)( rhs ) );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result)(
            NS(Particle_s)( lhs ), NS(Particle_s)( rhs ) );

    return cmp_result;
}

SIXTRL_INLINE int NS(Particle_compare_with_tolerances)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particle) *const SIXTRL_RESTRICT rhs,
    NS(particle_real_t) const rel_tol, NS(particle_real_t) const abs_tol
) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( lhs != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( rhs != SIXTRL_NULLPTR );

    int cmp_result = NS(Type_value_comp_result_with_tolerances)(
        NS(Particle_x)( lhs ), NS(Particle_x)( rhs ), rel_tol, abs_tol );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_with_tolerances)(
            NS(Particle_px)( lhs ), NS(Particle_px)( rhs ), rel_tol, abs_tol );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_with_tolerances)(
            NS(Particle_y)( lhs ), NS(Particle_y)( rhs ), rel_tol, abs_tol );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_with_tolerances)(
            NS(Particle_py)( lhs ), NS(Particle_py)( rhs ), rel_tol, abs_tol );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_with_tolerances)(
            NS(Particle_zeta)( lhs ), NS(Particle_zeta)( rhs ),
                rel_tol, abs_tol );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_with_tolerances)(
            NS(Particle_delta)( lhs ), NS(Particle_delta)( rhs ),
                rel_tol, abs_tol );

    if( ( cmp_result == 0 ) &&
        ( NS(Particle_state)( lhs ) != NS(Particle_state)( rhs ) ) )
    {
        cmp_result = ( NS(Particle_state)( lhs ) < NS(Particle_state)( rhs ) )
            ? -1 : +1;
    }

    if( ( cmp_result == 0 ) &&
        ( NS(Particle_at_element)( lhs ) != NS(Particle_at_element)( rhs ) ) )
    {
        cmp_result = ( NS(Particle_at_element)( lhs ) <
            NS(Particle_at_element)( rhs ) ) ? -1 : +1;
    }

    if( ( cmp_result == 0 ) &&
        ( NS(Particle_at_turn)( lhs ) != NS(Particle_at_turn)( rhs ) ) )
    {
        cmp_result = ( NS(Particle_at_turn)( lhs ) <
            NS(Particle_at_turn)( rhs ) ) ? -1 : +1;
    }

    if( ( cmp_result == 0 ) &&
        ( NS(Particle_id)( lhs ) != NS(Particle_id)( rhs ) ) )
    {
        cmp_result = ( NS(Particle_id)( lhs ) < NS(Particle_id)( rhs ) )
            ? -1 : +1;
    }

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_with_tolerances)(
            NS(Particle_psigma)( lhs ), NS(Particle_psigma)( rhs ),
                rel_tol, abs_tol );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_with_tolerances)(
            NS(Particle_rpp)( lhs ), NS(Particle_rpp)( rhs ),
                rel_tol, abs_tol );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_with_tolerances)(
            NS(Particle_rvv)( lhs ), NS(Particle_rvv)( rhs ),
                rel_tol, abs_tol );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_with_tolerances)(
            NS(Particle_chi)( lhs ), NS(Particle_chi)( rhs ),
                rel_tol, abs_tol );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_with_tolerances)(
            NS(Particle_charge_ratio)( lhs ), NS(Particle_charge_ratio)( rhs ),
                rel_tol, abs_tol );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_with_tolerances)(
            NS(Particle_charge0)( lhs ), NS(Particle_charge0)( rhs ),
                rel_tol, abs_tol );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_with_tolerances)(
            NS(Particle_mass0)( lhs ), NS(Particle_mass0)( rhs ),
                rel_tol, abs_tol );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_with_tolerances)(
            NS(Particle_beta0)( lhs ), NS(Particle_beta0)( rhs ),
                rel_tol, abs_tol );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_with_tolerances)(
            NS(Particle_gamma0)( lhs ), NS(Particle_gamma0)( rhs ),
                rel_tol, abs_tol );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_with_tolerances)(
            NS(Particle_pc0)( lhs ), NS(Particle_pc0)( rhs ),
                rel_tol, abs_tol );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_with_tolerances)(
            NS(Particle_s)( lhs ), NS(Particle_s)( rhs ),
                rel_tol, abs_tol );

    return cmp_result;
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_UNIT_COMPARE_H__ */
