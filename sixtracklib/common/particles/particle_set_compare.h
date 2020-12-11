#ifndef SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SET_COMPARE_H__
#define SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SET_COMPARE_H__


#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <type_traits>
        #include <limits>
    #endif /* C++ */
#endif /* #if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles/particle_set.h"
    #include "sixtracklib/common/particles/particle_set_api.h"
    #include "sixtracklib/common/particles/particle_set_init.h"
    #include "sixtracklib/common/particles/particle_set_convert.h"
    #include "sixtracklib/common/internal/compiler_attributes.h"
    #include "sixtracklib/common/internal/math_arithmetic.h"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
    #include "sixtracklib/common/internal/type_comparison_helpers.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class LhsT, class RhsT, class DiffT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< RhsT >()  ||
        !SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< LhsT >()  ||
        !SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< DiffT >() ||
        !SIXTRL_CXX_NAMESPACE::ParticleSet_allow_type_conversion< LhsT, DiffT >() ||
        !SIXTRL_CXX_NAMESPACE::ParticleSet_allow_type_conversion< RhsT, DiffT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_diff(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC DiffT*
            SIXTRL_RESTRICT SIXTRL_UNUSED( diff ),
        SIXTRL_PARTICLE_SET_ARGPTR_DEC const LhsT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( lhs ),
        SIXTRL_PARTICLE_SET_ARGPTR_DEC const RhsT *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( rhs ) ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class LhsT, class RhsT, class DiffT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< RhsT >()  &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< LhsT >()  &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< DiffT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_allow_type_conversion< LhsT, DiffT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_allow_type_conversion< RhsT, DiffT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_diff(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC DiffT* SIXTRL_RESTRICT diff,
        SIXTRL_PARTICLE_SET_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
        SIXTRL_PARTICLE_SET_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        /* TODO: Implement "safe" arithmetic to prevent overflows */

        if( diff != SIXTRL_NULLPTR )
        {
            if( lhs != SIXTRL_NULLPTR )
            {
                if( st::ParticleSet_allow_conversion( diff, lhs ) )
                {
                    status = st::ParticleSet_convert( diff, lhs );
                }

                if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                    ( rhs != SIXTRL_NULLPTR ) )
                {
                    SIXTRL_ASSERT( st::ParticleSet_x_length( diff ) ==
                                   st::ParticleSet_x_length( rhs ) );

                    status  = st::Math_arithmetic_subtract_from(
                        st::ParticleSet_x_begin( diff ),
                        st::ParticleSet_x_end( diff ),
                        st::ParticleSet_const_x_begin( rhs ) );

                    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - */

                    SIXTRL_ASSERT( st::ParticleSet_px_length( diff ) ==
                                   st::ParticleSet_px_length( rhs ) );

                    status  = st::Math_arithmetic_subtract_from(
                        st::ParticleSet_px_begin( diff ),
                        st::ParticleSet_px_end( diff ),
                        st::ParticleSet_const_px_begin( rhs ) );

                    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - */

                    SIXTRL_ASSERT( st::ParticleSet_px_length( diff ) ==
                                   st::ParticleSet_px_length( rhs ) );

                    status  = st::Math_arithmetic_subtract_from(
                        st::ParticleSet_px_begin( diff ),
                        st::ParticleSet_px_end( diff ),
                        st::ParticleSet_const_px_begin( rhs ) );

                    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - */

                    SIXTRL_ASSERT( st::ParticleSet_y_length( diff ) ==
                                   st::ParticleSet_y_length( rhs ) );

                    status  = st::Math_arithmetic_subtract_from(
                        st::ParticleSet_y_begin( diff ),
                        st::ParticleSet_y_end( diff ),
                        st::ParticleSet_const_y_begin( rhs ) );

                    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - */

                    SIXTRL_ASSERT( st::ParticleSet_py_length( diff ) ==
                                   st::ParticleSet_py_length( rhs ) );

                    status  = st::Math_arithmetic_subtract_from(
                        st::ParticleSet_py_begin( diff ),
                        st::ParticleSet_py_end( diff ),
                        st::ParticleSet_const_py_begin( rhs ) );

                    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - */

                    SIXTRL_ASSERT( st::ParticleSet_zeta_length( diff ) ==
                                   st::ParticleSet_zeta_length( rhs ) );

                    status  = st::Math_arithmetic_subtract_from(
                        st::ParticleSet_zeta_begin( diff ),
                        st::ParticleSet_zeta_end( diff ),
                        st::ParticleSet_const_zeta_begin( rhs ) );

                    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - */

                    SIXTRL_ASSERT( st::ParticleSet_delta_length( diff ) ==
                                   st::ParticleSet_delta_length( rhs ) );

                    status  = st::Math_arithmetic_subtract_from(
                        st::ParticleSet_delta_begin( diff ),
                        st::ParticleSet_delta_end( diff ),
                        st::ParticleSet_const_delta_begin( rhs ) );

                    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - */

                    SIXTRL_ASSERT( st::ParticleSet_state_length( diff ) ==
                                   st::ParticleSet_state_length( rhs ) );

                    status  = st::Math_arithmetic_subtract_from(
                        st::ParticleSet_state_begin( diff ),
                        st::ParticleSet_state_end( diff ),
                        st::ParticleSet_const_state_begin( rhs ) );

                    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - */

                    SIXTRL_ASSERT( st::ParticleSet_at_element_length( diff ) ==
                                   st::ParticleSet_at_element_length( rhs ) );

                    status  = st::Math_arithmetic_subtract_from(
                        st::ParticleSet_at_element_begin( diff ),
                        st::ParticleSet_at_element_end( diff ),
                        st::ParticleSet_const_at_element_begin( rhs ) );

                    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - */

                    SIXTRL_ASSERT( st::ParticleSet_at_turn_length( diff ) ==
                                   st::ParticleSet_at_turn_length( rhs ) );

                    status  = st::Math_arithmetic_subtract_from(
                        st::ParticleSet_at_turn_begin( diff ),
                        st::ParticleSet_at_turn_end( diff ),
                        st::ParticleSet_const_at_turn_begin( rhs ) );

                    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - */

                    SIXTRL_ASSERT( st::ParticleSet_particle_id_length( diff ) ==
                                   st::ParticleSet_particle_id_length( rhs ) );

                    status  = st::Math_arithmetic_subtract_from(
                        st::ParticleSet_particle_id_begin( diff ),
                        st::ParticleSet_particle_id_end( diff ),
                        st::ParticleSet_const_particle_id_begin( rhs ) );

                    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - */

                    SIXTRL_ASSERT( st::ParticleSet_psigma_length( diff ) ==
                                   st::ParticleSet_psigma_length( rhs ) );

                    status  = st::Math_arithmetic_subtract_from(
                        st::ParticleSet_psigma_begin( diff ),
                        st::ParticleSet_psigma_end( diff ),
                        st::ParticleSet_const_psigma_begin( rhs ) );

                    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - */

                    SIXTRL_ASSERT( st::ParticleSet_rpp_length( diff ) ==
                                   st::ParticleSet_rpp_length( rhs ) );

                    status  = st::Math_arithmetic_subtract_from(
                        st::ParticleSet_rpp_begin( diff ),
                        st::ParticleSet_rpp_end( diff ),
                        st::ParticleSet_const_rpp_begin( rhs ) );

                    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - */

                    SIXTRL_ASSERT( st::ParticleSet_rvv_length( diff ) ==
                                   st::ParticleSet_rvv_length( rhs ) );

                    status  = st::Math_arithmetic_subtract_from(
                        st::ParticleSet_rvv_begin( diff ),
                        st::ParticleSet_rvv_end( diff ),
                        st::ParticleSet_const_rvv_begin( rhs ) );

                    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - */

                    SIXTRL_ASSERT( st::ParticleSet_chi_length( diff ) ==
                                   st::ParticleSet_chi_length( rhs ) );

                    status  = st::Math_arithmetic_subtract_from(
                        st::ParticleSet_chi_begin( diff ),
                        st::ParticleSet_chi_end( diff ),
                        st::ParticleSet_const_chi_begin( rhs ) );

                    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - */

                    SIXTRL_ASSERT( st::ParticleSet_charge_ratio_length( diff ) ==
                                   st::ParticleSet_charge_ratio_length( rhs ) );

                    status  = st::Math_arithmetic_subtract_from(
                        st::ParticleSet_charge_ratio_begin( diff ),
                        st::ParticleSet_charge_ratio_end( diff ),
                        st::ParticleSet_const_charge_ratio_begin( rhs ) );

                    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - */

                    SIXTRL_ASSERT( st::ParticleSet_charge0_length( diff ) ==
                                   st::ParticleSet_charge0_length( rhs ) );

                    status  = st::Math_arithmetic_subtract_from(
                        st::ParticleSet_charge0_begin( diff ),
                        st::ParticleSet_charge0_end( diff ),
                        st::ParticleSet_const_charge0_begin( rhs ) );

                    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - */

                    SIXTRL_ASSERT( st::ParticleSet_mass0_length( diff ) ==
                                   st::ParticleSet_mass0_length( rhs ) );

                    status  = st::Math_arithmetic_subtract_from(
                        st::ParticleSet_mass0_begin( diff ),
                        st::ParticleSet_mass0_end( diff ),
                        st::ParticleSet_const_mass0_begin( rhs ) );

                    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - */

                    SIXTRL_ASSERT( st::ParticleSet_beta0_length( diff ) ==
                                   st::ParticleSet_beta0_length( rhs ) );

                    status  = st::Math_arithmetic_subtract_from(
                        st::ParticleSet_beta0_begin( diff ),
                        st::ParticleSet_beta0_end( diff ),
                        st::ParticleSet_const_beta0_begin( rhs ) );

                    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - */

                    SIXTRL_ASSERT( st::ParticleSet_gamma0_length( diff ) ==
                                   st::ParticleSet_gamma0_length( rhs ) );

                    status  = st::Math_arithmetic_subtract_from(
                        st::ParticleSet_gamma0_begin( diff ),
                        st::ParticleSet_gamma0_end( diff ),
                        st::ParticleSet_const_gamma0_begin( rhs ) );

                    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - */

                    SIXTRL_ASSERT( st::ParticleSet_pc0_length( diff ) ==
                                   st::ParticleSet_pc0_length( rhs ) );

                    status  = st::Math_arithmetic_subtract_from(
                        st::ParticleSet_pc0_begin( diff ),
                        st::ParticleSet_pc0_end( diff ),
                        st::ParticleSet_const_pc0_begin( rhs ) );

                    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - */

                    SIXTRL_ASSERT( st::ParticleSet_s_length( diff ) ==
                                   st::ParticleSet_s_length( rhs ) );

                    status  = st::Math_arithmetic_subtract_from(
                        st::ParticleSet_s_begin( diff ),
                        st::ParticleSet_s_end( diff ),
                        st::ParticleSet_const_s_begin( rhs ) );
                }
            }
            else if( rhs != SIXTRL_NULLPTR )
            {
                if( st::ParticleSet_allow_conversion( diff, rhs ) )
                {
                    status = st::ParticleSet_convert( diff, rhs );
                }

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status  = st::Math_arithmetic_change_sign(
                                st::ParticleSet_x_begin( diff ),
                                st::ParticleSet_x_end( diff ) );

                    status  = st::Math_arithmetic_change_sign(
                                st::ParticleSet_px_begin( diff ),
                                st::ParticleSet_px_end( diff ) );

                    status  = st::Math_arithmetic_change_sign(
                                st::ParticleSet_y_begin( diff ),
                                st::ParticleSet_y_end( diff ) );

                    status  = st::Math_arithmetic_change_sign(
                                st::ParticleSet_py_begin( diff ),
                                st::ParticleSet_py_end( diff ) );

                    status  = st::Math_arithmetic_change_sign(
                                st::ParticleSet_zeta_begin( diff ),
                                st::ParticleSet_zeta_end( diff ) );

                    status  = st::Math_arithmetic_change_sign(
                                st::ParticleSet_delta_begin( diff ),
                                st::ParticleSet_delta_end( diff ) );

                    status  = st::Math_arithmetic_change_sign(
                                st::ParticleSet_state_begin( diff ),
                                st::ParticleSet_state_end( diff ) );

                    status  = st::Math_arithmetic_change_sign(
                                st::ParticleSet_at_element_begin( diff ),
                                st::ParticleSet_at_element_end( diff ) );

                    status  = st::Math_arithmetic_change_sign(
                                st::ParticleSet_at_turn_begin( diff ),
                                st::ParticleSet_at_turn_end( diff ) );

                    status  = st::Math_arithmetic_change_sign(
                                st::ParticleSet_particle_id_begin( diff ),
                                st::ParticleSet_particle_id_end( diff ) );

                    status  = st::Math_arithmetic_change_sign(
                                st::ParticleSet_psigma_begin( diff ),
                                st::ParticleSet_psigma_end( diff ) );

                    status  = st::Math_arithmetic_change_sign(
                                st::ParticleSet_rpp_begin( diff ),
                                st::ParticleSet_rpp_end( diff ) );

                    status  = st::Math_arithmetic_change_sign(
                                st::ParticleSet_rvv_begin( diff ),
                                st::ParticleSet_rvv_end( diff ) );

                    status  = st::Math_arithmetic_change_sign(
                                st::ParticleSet_chi_begin( diff ),
                                st::ParticleSet_chi_end( diff ) );

                    status  = st::Math_arithmetic_change_sign(
                                st::ParticleSet_charge_ratio_begin( diff ),
                                st::ParticleSet_charge_ratio_end( diff ) );

                    status  = st::Math_arithmetic_change_sign(
                                st::ParticleSet_charge0_begin( diff ),
                                st::ParticleSet_charge0_end( diff ) );

                    status  = st::Math_arithmetic_change_sign(
                                st::ParticleSet_mass0_begin( diff ),
                                st::ParticleSet_mass0_end( diff ) );

                    status  = st::Math_arithmetic_change_sign(
                                st::ParticleSet_beta0_begin( diff ),
                                st::ParticleSet_beta0_end( diff ) );

                    status  = st::Math_arithmetic_change_sign(
                                st::ParticleSet_gamma0_begin( diff ),
                                st::ParticleSet_gamma0_end( diff ) );

                    status  = st::Math_arithmetic_change_sign(
                                st::ParticleSet_pc0_begin( diff ),
                                st::ParticleSet_pc0_end( diff ) );

                    status  = st::Math_arithmetic_change_sign(
                                st::ParticleSet_s_begin( diff ),
                                st::ParticleSet_s_end( diff ) );
                }
            }
        }

        return status;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class LhsT, class RhsT, typename cmp_result_t = typename
        SIXTRL_CXX_NAMESPACE::TypeCompLogicTypeTraits< typename
            SIXTRL_CXX_NAMESPACE::ParticleSetTraits< LhsT >::real_t
                >::cmp_result_t >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< RhsT >() ||
        !SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< LhsT >(),
        cmp_result_t >::type
    ParticleSet_compare(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT /* lhs */,
        SIXTRL_PARTICLE_SET_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT /* rhs */
    ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::TypeCompResultTraits<
            cmp_result_t >::CMP_LHS_SMALLER_RHS;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class LhsT, class RhsT, typename cmp_result_t =
         typename SIXTRL_CXX_NAMESPACE::TypeCompLogicTypeTraits< typename
             SIXTRL_CXX_NAMESPACE::ParticleSetTraits< LhsT >::real_t
                 >::cmp_result_t >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< RhsT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< LhsT >(),
        cmp_result_t >::type
    ParticleSet_compare(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
        SIXTRL_PARTICLE_SET_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        typedef SIXTRL_PARTICLE_SET_DATAPTR_DEC typename
            st::TypeMethodParamTraits< typename st::ParticleSetTraits< LhsT
                >::real_t >::const_pointer lhs_real_it_t;

        typedef SIXTRL_PARTICLE_SET_DATAPTR_DEC typename
            st::TypeMethodParamTraits< typename st::ParticleSetTraits< LhsT
                >::index_t >::const_pointer lhs_index_it_t;

        typedef SIXTRL_PARTICLE_SET_DATAPTR_DEC typename
            st::TypeMethodParamTraits< typename st::ParticleSetTraits< LhsT
                >::real_t >::const_pointer rhs_real_it_t;

        typedef SIXTRL_PARTICLE_SET_DATAPTR_DEC typename
            st::TypeMethodParamTraits< typename st::ParticleSetTraits< LhsT
                >::index_t >::const_pointer rhs_index_it_t;

        typedef st::TypeCompResultTraits< cmp_result_t > cmp_traits_t;

        cmp_result_t cmp_result = cmp_traits_t::CMP_LHS_SMALLER_RHS;

        if( ( rhs != SIXTRL_NULLPTR ) && ( lhs != SIXTRL_NULLPTR ) )
        {
            cmp_result = st::Type_value_comp_result<
                arch_size_t, cmp_result_t, arch_size_t >(
                    st::ParticleSet_x_length( lhs ),
                    st::ParticleSet_x_length( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result_for_range<
                lhs_real_it_t, cmp_result_t, rhs_real_it_t >(
                    st::ParticleSet_const_x_begin( lhs ),
                    st::ParticleSet_const_x_end( lhs ),
                    st::ParticleSet_const_x_begin( rhs ) );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result<
                arch_size_t, cmp_result_t, arch_size_t >(
                    st::ParticleSet_px_length( lhs ),
                    st::ParticleSet_px_length( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result_for_range<
                lhs_real_it_t, cmp_result_t, rhs_real_it_t >(
                    st::ParticleSet_const_px_begin( lhs ),
                    st::ParticleSet_const_px_end( lhs ),
                    st::ParticleSet_const_px_begin( rhs ) );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result<
                arch_size_t, cmp_result_t, arch_size_t >(
                    st::ParticleSet_y_length( lhs ),
                    st::ParticleSet_y_length( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result_for_range<
                lhs_real_it_t, cmp_result_t, rhs_real_it_t >(
                    st::ParticleSet_const_y_begin( lhs ),
                    st::ParticleSet_const_y_end( lhs ),
                    st::ParticleSet_const_y_begin( rhs ) );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result<
                arch_size_t, cmp_result_t, arch_size_t >(
                    st::ParticleSet_py_length( lhs ),
                    st::ParticleSet_py_length( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result_for_range<
                lhs_real_it_t, cmp_result_t, rhs_real_it_t >(
                    st::ParticleSet_const_py_begin( lhs ),
                    st::ParticleSet_const_py_end( lhs ),
                    st::ParticleSet_const_py_begin( rhs ) );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result<
                arch_size_t, cmp_result_t, arch_size_t >(
                    st::ParticleSet_zeta_length( lhs ),
                    st::ParticleSet_zeta_length( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result_for_range<
                lhs_real_it_t, cmp_result_t, rhs_real_it_t >(
                    st::ParticleSet_const_zeta_begin( lhs ),
                    st::ParticleSet_const_zeta_end( lhs ),
                    st::ParticleSet_const_zeta_begin( rhs ) );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result<
                arch_size_t, cmp_result_t, arch_size_t >(
                    st::ParticleSet_delta_length( lhs ),
                    st::ParticleSet_delta_length( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result_for_range<
                lhs_real_it_t, cmp_result_t, rhs_real_it_t >(
                    st::ParticleSet_const_delta_begin( lhs ),
                    st::ParticleSet_const_delta_end( lhs ),
                    st::ParticleSet_const_delta_begin( rhs ) );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result<
                arch_size_t, cmp_result_t, arch_size_t >(
                    st::ParticleSet_state_length( lhs ),
                    st::ParticleSet_state_length( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result_for_range<
                lhs_index_it_t, cmp_result_t, rhs_index_it_t >(
                    st::ParticleSet_const_state_begin( lhs ),
                    st::ParticleSet_const_state_end( lhs ),
                    st::ParticleSet_const_state_begin( rhs ) );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result<
                arch_size_t, cmp_result_t, arch_size_t >(
                    st::ParticleSet_at_element_length( lhs ),
                    st::ParticleSet_at_element_length( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result_for_range<
                lhs_index_it_t, cmp_result_t, rhs_index_it_t >(
                    st::ParticleSet_const_at_element_begin( lhs ),
                    st::ParticleSet_const_at_element_end( lhs ),
                    st::ParticleSet_const_at_element_begin( rhs ) );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result<
                arch_size_t, cmp_result_t, arch_size_t >(
                    st::ParticleSet_at_turn_length( lhs ),
                    st::ParticleSet_at_turn_length( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result_for_range<
                lhs_index_it_t, cmp_result_t, rhs_index_it_t >(
                    st::ParticleSet_const_at_turn_begin( lhs ),
                    st::ParticleSet_const_at_turn_end( lhs ),
                    st::ParticleSet_const_at_turn_begin( rhs ) );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result<
                arch_size_t, cmp_result_t, arch_size_t >(
                    st::ParticleSet_particle_id_length( lhs ),
                    st::ParticleSet_particle_id_length( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result_for_range<
                lhs_index_it_t, cmp_result_t, rhs_index_it_t >(
                    st::ParticleSet_const_particle_id_begin( lhs ),
                    st::ParticleSet_const_particle_id_end( lhs ),
                    st::ParticleSet_const_particle_id_begin( rhs ) );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result<
                arch_size_t, cmp_result_t, arch_size_t >(
                    st::ParticleSet_psigma_length( lhs ),
                    st::ParticleSet_psigma_length( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result_for_range<
                lhs_real_it_t, cmp_result_t, rhs_real_it_t >(
                    st::ParticleSet_const_psigma_begin( lhs ),
                    st::ParticleSet_const_psigma_end( lhs ),
                    st::ParticleSet_const_psigma_begin( rhs ) );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result<
                arch_size_t, cmp_result_t, arch_size_t >(
                    st::ParticleSet_rpp_length( lhs ),
                    st::ParticleSet_rpp_length( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result_for_range<
                lhs_real_it_t, cmp_result_t, rhs_real_it_t >(
                    st::ParticleSet_const_rpp_begin( lhs ),
                    st::ParticleSet_const_rpp_end( lhs ),
                    st::ParticleSet_const_rpp_begin( rhs ) );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result<
                arch_size_t, cmp_result_t, arch_size_t >(
                    st::ParticleSet_rvv_length( lhs ),
                    st::ParticleSet_rvv_length( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result_for_range<
                lhs_real_it_t, cmp_result_t, rhs_real_it_t >(
                    st::ParticleSet_const_rvv_begin( lhs ),
                    st::ParticleSet_const_rvv_end( lhs ),
                    st::ParticleSet_const_rvv_begin( rhs ) );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result<
                arch_size_t, cmp_result_t, arch_size_t >(
                    st::ParticleSet_chi_length( lhs ),
                    st::ParticleSet_chi_length( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result_for_range<
                lhs_real_it_t, cmp_result_t, rhs_real_it_t >(
                    st::ParticleSet_const_chi_begin( lhs ),
                    st::ParticleSet_const_chi_end( lhs ),
                    st::ParticleSet_const_chi_begin( rhs ) );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result<
                arch_size_t, cmp_result_t, arch_size_t >(
                    st::ParticleSet_charge_ratio_length( lhs ),
                    st::ParticleSet_charge_ratio_length( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result_for_range<
                lhs_real_it_t, cmp_result_t, rhs_real_it_t >(
                    st::ParticleSet_const_charge_ratio_begin( lhs ),
                    st::ParticleSet_const_charge_ratio_end( lhs ),
                    st::ParticleSet_const_charge_ratio_begin( rhs ) );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result<
                arch_size_t, cmp_result_t, arch_size_t >(
                    st::ParticleSet_charge0_length( lhs ),
                    st::ParticleSet_charge0_length( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result_for_range<
                lhs_real_it_t, cmp_result_t, rhs_real_it_t >(
                    st::ParticleSet_const_charge0_begin( lhs ),
                    st::ParticleSet_const_charge0_end( lhs ),
                    st::ParticleSet_const_charge0_begin( rhs ) );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result<
                arch_size_t, cmp_result_t, arch_size_t >(
                    st::ParticleSet_mass0_length( lhs ),
                    st::ParticleSet_mass0_length( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result_for_range<
                lhs_real_it_t, cmp_result_t, rhs_real_it_t >(
                    st::ParticleSet_const_mass0_begin( lhs ),
                    st::ParticleSet_const_mass0_end( lhs ),
                    st::ParticleSet_const_mass0_begin( rhs ) );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result<
                arch_size_t, cmp_result_t, arch_size_t >(
                    st::ParticleSet_beta0_length( lhs ),
                    st::ParticleSet_beta0_length( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result_for_range<
                lhs_real_it_t, cmp_result_t, rhs_real_it_t >(
                    st::ParticleSet_const_beta0_begin( lhs ),
                    st::ParticleSet_const_beta0_end( lhs ),
                    st::ParticleSet_const_beta0_begin( rhs ) );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result<
                arch_size_t, cmp_result_t, arch_size_t >(
                    st::ParticleSet_gamma0_length( lhs ),
                    st::ParticleSet_gamma0_length( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result_for_range<
                lhs_real_it_t, cmp_result_t, rhs_real_it_t >(
                    st::ParticleSet_const_gamma0_begin( lhs ),
                    st::ParticleSet_const_gamma0_end( lhs ),
                    st::ParticleSet_const_gamma0_begin( rhs ) );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result<
                arch_size_t, cmp_result_t, arch_size_t >(
                    st::ParticleSet_pc0_length( lhs ),
                    st::ParticleSet_pc0_length( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result_for_range<
                lhs_real_it_t, cmp_result_t, rhs_real_it_t >(
                    st::ParticleSet_const_pc0_begin( lhs ),
                    st::ParticleSet_const_pc0_end( lhs ),
                    st::ParticleSet_const_pc0_begin( rhs ) );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result<
                arch_size_t, cmp_result_t, arch_size_t >(
                    st::ParticleSet_s_length( lhs ),
                    st::ParticleSet_s_length( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result_for_range<
                lhs_real_it_t, cmp_result_t, rhs_real_it_t >(
                    st::ParticleSet_const_s_begin( lhs ),
                    st::ParticleSet_const_s_end( lhs ),
                    st::ParticleSet_const_s_begin( rhs ) );

        }
        else if( lhs != SIXTRL_NULLPTR )
        {
            cmp_result = cmp_traits_t::CMP_LHS_LARGER_RHS;
        }

        return cmp_result;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class LhsT, class RhsT, typename cmp_result_t = typename
        SIXTRL_CXX_NAMESPACE::TypeCompLogicTypeTraits< typename
            SIXTRL_CXX_NAMESPACE::ParticleSetTraits< LhsT >::real_t
                >::cmp_result_t >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< RhsT >() ||
        !SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< LhsT >(),
        cmp_result_t >::type
    ParticleSet_compare_with_tolerances(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT /* lhs */,
        SIXTRL_PARTICLE_SET_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT /* rhs */,
        typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
            SIXTRL_CXX_NAMESPACE::ParticleSetTraits< RhsT >::real_t
                >::const_argument_type /*rel_tol*/,
        typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
            SIXTRL_CXX_NAMESPACE::ParticleSetTraits< RhsT >::real_t
                >::const_argument_type /*abs_tol*/ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::TypeCompResultTraits<
            cmp_result_t >::CMP_LHS_SMALLER_RHS;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class LhsT, class RhsT, typename cmp_result_t =
        typename SIXTRL_CXX_NAMESPACE::TypeCompLogicTypeTraits< typename
        SIXTRL_CXX_NAMESPACE::ParticleSetTraits< LhsT >::real_t >::cmp_result_t >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< RhsT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< LhsT >(),
        cmp_result_t >::type
    ParticleSet_compare_with_tolerances(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT lhs,
        SIXTRL_PARTICLE_SET_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs,
        typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
            SIXTRL_CXX_NAMESPACE::ParticleSetTraits< RhsT >::real_t
                >::const_argument_type rel_tol,
        typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
            SIXTRL_CXX_NAMESPACE::ParticleSetTraits< RhsT >::real_t
                >::const_argument_type abs_tol )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        typedef SIXTRL_PARTICLE_SET_DATAPTR_DEC typename
            st::TypeMethodParamTraits< typename st::ParticleSetTraits< LhsT
                >::real_t >::const_pointer lhs_real_it_t;

        typedef SIXTRL_PARTICLE_SET_DATAPTR_DEC typename
            st::TypeMethodParamTraits< typename st::ParticleSetTraits< LhsT
                >::index_t >::const_pointer lhs_index_it_t;

        typedef SIXTRL_PARTICLE_SET_DATAPTR_DEC typename
            st::TypeMethodParamTraits< typename st::ParticleSetTraits< LhsT
                >::real_t >::const_pointer rhs_real_it_t;

        typedef SIXTRL_PARTICLE_SET_DATAPTR_DEC typename
            st::TypeMethodParamTraits< typename st::ParticleSetTraits< LhsT
                >::index_t >::const_pointer rhs_index_it_t;

        typedef st::TypeCompResultTraits< cmp_result_t > cmp_traits_t;
        cmp_result_t cmp_result = cmp_traits_t::CMP_LHS_SMALLER_RHS;

        if( ( rhs != SIXTRL_NULLPTR ) && ( lhs != SIXTRL_NULLPTR ) )
        {
            cmp_result = st::Type_value_comp_result<
                arch_size_t, cmp_result_t, arch_size_t >(
                    st::ParticleSet_x_length( lhs ),
                    st::ParticleSet_x_length( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result_for_range<
                lhs_real_it_t, cmp_result_t, rhs_real_it_t >(
                    st::ParticleSet_const_x_begin( lhs ),
                    st::ParticleSet_const_x_end( lhs ),
                    st::ParticleSet_const_x_begin( rhs ), rel_tol, abs_tol );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result<
                arch_size_t, cmp_result_t, arch_size_t >(
                    st::ParticleSet_px_length( lhs ),
                    st::ParticleSet_px_length( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result_for_range<
                lhs_real_it_t, cmp_result_t, rhs_real_it_t >(
                    st::ParticleSet_const_px_begin( lhs ),
                    st::ParticleSet_const_px_end( lhs ),
                    st::ParticleSet_const_px_begin( rhs ), rel_tol, abs_tol );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result<
                arch_size_t, cmp_result_t, arch_size_t >(
                    st::ParticleSet_y_length( lhs ),
                    st::ParticleSet_y_length( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result_for_range<
                lhs_real_it_t, cmp_result_t, rhs_real_it_t >(
                    st::ParticleSet_const_y_begin( lhs ),
                    st::ParticleSet_const_y_end( lhs ),
                    st::ParticleSet_const_y_begin( rhs ), rel_tol, abs_tol );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result<
                arch_size_t, cmp_result_t, arch_size_t >(
                    st::ParticleSet_py_length( lhs ),
                    st::ParticleSet_py_length( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result_for_range<
                lhs_real_it_t, cmp_result_t, rhs_real_it_t >(
                    st::ParticleSet_const_py_begin( lhs ),
                    st::ParticleSet_const_py_end( lhs ),
                    st::ParticleSet_const_py_begin( rhs ), rel_tol, abs_tol );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result<
                arch_size_t, cmp_result_t, arch_size_t >(
                    st::ParticleSet_zeta_length( lhs ),
                    st::ParticleSet_zeta_length( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result_for_range<
                lhs_real_it_t, cmp_result_t, rhs_real_it_t >(
                    st::ParticleSet_const_zeta_begin( lhs ),
                    st::ParticleSet_const_zeta_end( lhs ),
                    st::ParticleSet_const_zeta_begin( rhs ), rel_tol, abs_tol );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result<
                arch_size_t, cmp_result_t, arch_size_t >(
                    st::ParticleSet_delta_length( lhs ),
                    st::ParticleSet_delta_length( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result_for_range<
                lhs_real_it_t, cmp_result_t, rhs_real_it_t >(
                    st::ParticleSet_const_delta_begin( lhs ),
                    st::ParticleSet_const_delta_end( lhs ),
                    st::ParticleSet_const_delta_begin( rhs ), rel_tol, abs_tol );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result<
                arch_size_t, cmp_result_t, arch_size_t >(
                    st::ParticleSet_state_length( lhs ),
                    st::ParticleSet_state_length( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result_for_range<
                lhs_index_it_t, cmp_result_t, rhs_index_it_t >(
                    st::ParticleSet_const_state_begin( lhs ),
                    st::ParticleSet_const_state_end( lhs ),
                    st::ParticleSet_const_state_begin( rhs ) );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result<
                arch_size_t, cmp_result_t, arch_size_t >(
                    st::ParticleSet_at_element_length( lhs ),
                    st::ParticleSet_at_element_length( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result_for_range<
                lhs_index_it_t, cmp_result_t, rhs_index_it_t >(
                    st::ParticleSet_const_at_element_begin( lhs ),
                    st::ParticleSet_const_at_element_end( lhs ),
                    st::ParticleSet_const_at_element_begin( rhs ) );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result<
                arch_size_t, cmp_result_t, arch_size_t >(
                    st::ParticleSet_at_turn_length( lhs ),
                    st::ParticleSet_at_turn_length( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result_for_range<
                lhs_index_it_t, cmp_result_t, rhs_index_it_t >(
                    st::ParticleSet_const_at_turn_begin( lhs ),
                    st::ParticleSet_const_at_turn_end( lhs ),
                    st::ParticleSet_const_at_turn_begin( rhs ) );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result<
                arch_size_t, cmp_result_t, arch_size_t >(
                    st::ParticleSet_particle_id_length( lhs ),
                    st::ParticleSet_particle_id_length( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result_for_range<
                lhs_index_it_t, cmp_result_t, rhs_index_it_t >(
                    st::ParticleSet_const_particle_id_begin( lhs ),
                    st::ParticleSet_const_particle_id_end( lhs ),
                    st::ParticleSet_const_particle_id_begin( rhs ) );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result<
                arch_size_t, cmp_result_t, arch_size_t >(
                    st::ParticleSet_psigma_length( lhs ),
                    st::ParticleSet_psigma_length( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result_for_range<
                lhs_real_it_t, cmp_result_t, rhs_real_it_t >(
                    st::ParticleSet_const_psigma_begin( lhs ),
                    st::ParticleSet_const_psigma_end( lhs ),
                    st::ParticleSet_const_psigma_begin( rhs ),
                    rel_tol, abs_tol );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result<
                arch_size_t, cmp_result_t, arch_size_t >(
                    st::ParticleSet_rpp_length( lhs ),
                    st::ParticleSet_rpp_length( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result_for_range<
                lhs_real_it_t, cmp_result_t, rhs_real_it_t >(
                    st::ParticleSet_const_rpp_begin( lhs ),
                    st::ParticleSet_const_rpp_end( lhs ),
                    st::ParticleSet_const_rpp_begin( rhs ), rel_tol, abs_tol );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result<
                arch_size_t, cmp_result_t, arch_size_t >(
                    st::ParticleSet_rvv_length( lhs ),
                    st::ParticleSet_rvv_length( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result_for_range<
                lhs_real_it_t, cmp_result_t, rhs_real_it_t >(
                    st::ParticleSet_const_rvv_begin( lhs ),
                    st::ParticleSet_const_rvv_end( lhs ),
                    st::ParticleSet_const_rvv_begin( rhs ), rel_tol, abs_tol );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result<
                arch_size_t, cmp_result_t, arch_size_t >(
                    st::ParticleSet_chi_length( lhs ),
                    st::ParticleSet_chi_length( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result_for_range<
                lhs_real_it_t, cmp_result_t, rhs_real_it_t >(
                    st::ParticleSet_const_chi_begin( lhs ),
                    st::ParticleSet_const_chi_end( lhs ),
                    st::ParticleSet_const_chi_begin( rhs ), rel_tol, abs_tol );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result<
                arch_size_t, cmp_result_t, arch_size_t >(
                    st::ParticleSet_charge_ratio_length( lhs ),
                    st::ParticleSet_charge_ratio_length( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result_for_range<
                lhs_real_it_t, cmp_result_t, rhs_real_it_t >(
                    st::ParticleSet_const_charge_ratio_begin( lhs ),
                    st::ParticleSet_const_charge_ratio_end( lhs ),
                    st::ParticleSet_const_charge_ratio_begin( rhs ),
                    rel_tol, abs_tol );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result<
                arch_size_t, cmp_result_t, arch_size_t >(
                    st::ParticleSet_charge0_length( lhs ),
                    st::ParticleSet_charge0_length( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result_for_range<
                lhs_real_it_t, cmp_result_t, rhs_real_it_t >(
                    st::ParticleSet_const_charge0_begin( lhs ),
                    st::ParticleSet_const_charge0_end( lhs ),
                    st::ParticleSet_const_charge0_begin( rhs ),
                    rel_tol, abs_tol );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result<
                arch_size_t, cmp_result_t, arch_size_t >(
                    st::ParticleSet_mass0_length( lhs ),
                    st::ParticleSet_mass0_length( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result_for_range<
                lhs_real_it_t, cmp_result_t, rhs_real_it_t >(
                    st::ParticleSet_const_mass0_begin( lhs ),
                    st::ParticleSet_const_mass0_end( lhs ),
                    st::ParticleSet_const_mass0_begin( rhs ), rel_tol, abs_tol );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result<
                arch_size_t, cmp_result_t, arch_size_t >(
                    st::ParticleSet_beta0_length( lhs ),
                    st::ParticleSet_beta0_length( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result_for_range<
                lhs_real_it_t, cmp_result_t, rhs_real_it_t >(
                    st::ParticleSet_const_beta0_begin( lhs ),
                    st::ParticleSet_const_beta0_end( lhs ),
                    st::ParticleSet_const_beta0_begin( rhs ),
                    rel_tol, abs_tol );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result<
                arch_size_t, cmp_result_t, arch_size_t >(
                    st::ParticleSet_gamma0_length( lhs ),
                    st::ParticleSet_gamma0_length( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result_for_range<
                lhs_real_it_t, cmp_result_t, rhs_real_it_t >(
                    st::ParticleSet_const_gamma0_begin( lhs ),
                    st::ParticleSet_const_gamma0_end( lhs ),
                    st::ParticleSet_const_gamma0_begin( rhs ),
                    rel_tol, abs_tol );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result<
                arch_size_t, cmp_result_t, arch_size_t >(
                    st::ParticleSet_pc0_length( lhs ),
                    st::ParticleSet_pc0_length( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result_for_range<
                lhs_real_it_t, cmp_result_t, rhs_real_it_t >(
                    st::ParticleSet_const_pc0_begin( lhs ),
                    st::ParticleSet_const_pc0_end( lhs ),
                    st::ParticleSet_const_pc0_begin( rhs ),
                    rel_tol, abs_tol );

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result<
                arch_size_t, cmp_result_t, arch_size_t >(
                    st::ParticleSet_s_length( lhs ),
                    st::ParticleSet_s_length( rhs ) );

            if( cmp_result == cmp_traits_t::CMP_LHS_EQUAL_RHS )
            cmp_result = st::Type_value_comp_result_for_range<
                lhs_real_it_t, cmp_result_t, rhs_real_it_t >(
                    st::ParticleSet_const_s_begin( lhs ),
                    st::ParticleSet_const_s_end( lhs ),
                    st::ParticleSet_const_s_begin( rhs ),
                    rel_tol, abs_tol );
        }
        else if( lhs != SIXTRL_NULLPTR )
        {
            cmp_result = cmp_traits_t::CMP_LHS_LARGER_RHS;
        }

        return cmp_result;
    }
}

#endif /* C++ */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles/particle_set.hpp"
    #include "sixtracklib/common/particles/particle_set_vector.hpp"
#endif /* C++ */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    /* ********************************************************************* */
    /* LHS: NS(ParticleSet) */

    template< class RhsT >
    struct ObjDataComparisonHelper< ::NS(ParticleSet), RhsT,
        typename SIXTRL_CXX_NAMESPACE::ObjDataLogicTypeTraits<
            ::NS(ParticleSet) >::cmp_result_t, typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< RhsT >(), void >::type >
    {
        typedef ::NS(ParticleSet) LhsT;
        typedef typename SIXTRL_CXX_NAMESPACE::ObjDataLogicTypeTraits<
                    LhsT >::cmp_result_t cmp_result_t;

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN cmp_result_t compare(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC  const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_PARTICLE_SET_ARGPTR_DEC  const RhsT *const SIXTRL_RESTRICT rhs
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ParticleSet_compare<
                LhsT, RhsT, cmp_result_t >( lhs, rhs );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        cmp_result_t compare_with_tolerances(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC  const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_PARTICLE_SET_ARGPTR_DEC  const RhsT *const SIXTRL_RESTRICT rhs,
            Args&&... tolerances ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ParticleSet_compare_with_tolerances<
                LhsT, RhsT, cmp_result_t >( lhs, rhs, std::forward< Args >(
                    tolerances )... );
        }
    };

    template< class RhsT, class DiffT >
    struct ObjDataDiffHelper< ::NS(ParticleSet), RhsT, DiffT,
        typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< RhsT >() &&
            SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< DiffT >(), void >::type >
    {
        typedef ::NS(ParticleSet) LhsT;

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
        calculate(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC DiffT* SIXTRL_RESTRICT diff,
            SIXTRL_PARTICLE_SET_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_PARTICLE_SET_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ParticleSet_diff( diff, lhs, rhs );
        }
    };

    /* --------------------------------------------------------------------- */
    /*  LHS: TParticleSet< R, I, RAlign, IAlign > */

    template< class R, class I, class RhsT >
    struct ObjDataComparisonHelper< SIXTRL_CXX_NAMESPACE::TParticleSet< R, I >,
        RhsT, typename SIXTRL_CXX_NAMESPACE::ObjDataLogicTypeTraits<
            SIXTRL_CXX_NAMESPACE::TParticleSet< R, I > >::cmp_result_t,
        typename std::enable_if< SIXTRL_CXX_NAMESPACE::ParticleSet_is_type<
            RhsT >(), void >::type >
    {
        typedef SIXTRL_CXX_NAMESPACE::TParticleSet< R, I > LhsT;
        typedef typename SIXTRL_CXX_NAMESPACE::ObjDataLogicTypeTraits<
                    LhsT >::cmp_result_t cmp_result_t;

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN cmp_result_t compare(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_PARTICLE_SET_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ParticleSet_compare<
                LhsT, RhsT, cmp_result_t >( lhs, rhs );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        cmp_result_t compare_with_tolerances(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_PARTICLE_SET_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs,
            Args&&... tolerances ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ParticleSet_compare_with_tolerances<
                LhsT, RhsT, cmp_result_t >( lhs, rhs, std::forward< Args >(
                    tolerances )... );
        }
    };

    template< class R, class I, class RhsT, class DiffT >
    struct ObjDataDiffHelper< SIXTRL_CXX_NAMESPACE::TParticleSet< R, I >, RhsT,
        DiffT, typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< RhsT >() &&
            SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< DiffT >(), void >::type >
    {
        typedef SIXTRL_CXX_NAMESPACE::TParticleSet< R, I > LhsT;

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
        calculate(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC DiffT* SIXTRL_RESTRICT diff,
            SIXTRL_PARTICLE_SET_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_PARTICLE_SET_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ParticleSet_diff( diff, lhs, rhs );
        }
    };

    /* --------------------------------------------------------------------- */
    /*  LHS: TParticleSet< R, I, RAlign, IAlign > */

    template< class R, class I, class RAlloc, class IAlloc, class RhsT >
    struct ObjDataComparisonHelper<
        SIXTRL_CXX_NAMESPACE::TVectorParticleSet< R, I, RAlloc, IAlloc >, RhsT,
        typename SIXTRL_CXX_NAMESPACE::ObjDataLogicTypeTraits<
            SIXTRL_CXX_NAMESPACE::TVectorParticleSet< R, I, RAlloc, IAlloc >
                >::cmp_result_t,
        typename std::enable_if< SIXTRL_CXX_NAMESPACE::ParticleSet_is_type<
            SIXTRL_CXX_NAMESPACE::TVectorParticleSet<
                R, I, RAlloc, IAlloc > >(), void >::type >
    {
        typedef SIXTRL_CXX_NAMESPACE::TVectorParticleSet<
                    R, I, RAlloc, IAlloc > LhsT;

        typedef typename SIXTRL_CXX_NAMESPACE::ObjDataLogicTypeTraits<
                    LhsT >::cmp_result_t cmp_result_t;

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN cmp_result_t compare(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC  const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_PARTICLE_SET_ARGPTR_DEC  const RhsT *const SIXTRL_RESTRICT rhs
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ParticleSet_compare<
                LhsT, RhsT, cmp_result_t >( lhs, rhs );
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        cmp_result_t compare_with_tolerances(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC  const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_PARTICLE_SET_ARGPTR_DEC  const RhsT *const SIXTRL_RESTRICT rhs,
            Args&&... tolerances ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ParticleSet_compare_with_tolerances<
                LhsT, RhsT, cmp_result_t >( lhs, rhs, std::forward< Args >(
                    tolerances )... );
        }
    };

    template< class R, class I, class RAlloc, class IAlloc,
              class RhsT, class DiffT >
    struct ObjDataDiffHelper< SIXTRL_CXX_NAMESPACE::TVectorParticleSet<
            R, I, RAlloc, IAlloc >, RhsT, DiffT, typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< RhsT >() &&
            SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< DiffT >(), void >::type >
    {
        typedef SIXTRL_CXX_NAMESPACE::TVectorParticleSet<
            R, I, RAlloc, IAlloc > LhsT;

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
        calculate(
            SIXTRL_PARTICLE_SET_ARGPTR_DEC DiffT* SIXTRL_RESTRICT diff,
            SIXTRL_PARTICLE_SET_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
            SIXTRL_PARTICLE_SET_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ParticleSet_diff( diff, lhs, rhs );
        }
    };
}

template< class LhsT, class RhsT, class DiffT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(ParticleSet_diff)( SIXTRL_PARTICLE_SET_ARGPTR_DEC DiffT* SIXTRL_RESTRICT diff,
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs )
{
    return SIXTRL_CXX_NAMESPACE::ParticleSet_diff( diff, lhs, rhs );
}

template< class LhsT, class RhsT, typename cmp_result_t = typename
    SIXTRL_CXX_NAMESPACE::TypeCompLogicTypeTraits< typename
        SIXTRL_CXX_NAMESPACE::ParticleSetTraits< LhsT >::real_t >::cmp_result_t >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN cmp_result_t NS(ParticleSet_compare)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs )
{
    return SIXTRL_CXX_NAMESPACE::ParticleSet_compare<
        LhsT, RhsT, cmp_result_t >( lhs, rhs );
}

template< class LhsT, class RhsT, typename cmp_result_t = typename
     SIXTRL_CXX_NAMESPACE::TypeCompLogicTypeTraits< typename
         SIXTRL_CXX_NAMESPACE::ParticleSetTraits< LhsT >::real_t >::cmp_result_t >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN cmp_result_t
NS(ParticleSet_compare_with_tolerances)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const LhsT *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const RhsT *const SIXTRL_RESTRICT rhs,
    typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
        SIXTRL_CXX_NAMESPACE::ParticleSetTraits< RhsT >::real_t
            >::const_argument_type rel_tol,
    typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
        SIXTRL_CXX_NAMESPACE::ParticleSetTraits< RhsT >::real_t
            >::const_argument_type abs_tol )
{
    return SIXTRL_CXX_NAMESPACE::ParticleSet_compare_with_tolerances<
        LhsT, RhsT, cmp_result_t >( lhs, rhs, rel_tol, abs_tol );
}

#endif /* C++ */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(ParticleSet_diff)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)* SIXTRL_RESTRICT diff,
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const NS(ParticleSet) *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const NS(ParticleSet) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN int NS(ParticleSet_compare)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const NS(ParticleSet) *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const NS(ParticleSet) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN int NS(ParticleSet_compare_with_tolerances)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const NS(ParticleSet) *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const NS(ParticleSet) *const SIXTRL_RESTRICT rhs,
    NS(particle_real_t) const rel_tol, NS(particle_real_t) const abs_tol
) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_INLINE NS(arch_status_t) NS(ParticleSet_diff)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)* SIXTRL_RESTRICT diff,
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const NS(ParticleSet) *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const NS(ParticleSet) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = ( NS(arch_status_t)
        )SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    if( diff != SIXTRL_NULLPTR )
    {
        if( lhs != SIXTRL_NULLPTR )
        {
            if( NS(ParticleSet_allow_conversion)( diff, lhs,
                    SIXTRL_STORAGE_BE_DEFAULT, SIXTRL_STORAGE_BE_DEFAULT ) )
            {
                status = NS(ParticleSet_convert)( diff, lhs,
                    SIXTRL_STORAGE_BE_DEFAULT, SIXTRL_STORAGE_BE_DEFAULT );
            }

            if( ( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS ) &&
                ( rhs != SIXTRL_NULLPTR ) )
            {
                SIXTRL_ASSERT( NS(ParticleSet_x_length)( diff ) ==
                               NS(ParticleSet_x_length)( rhs ) );

                status  = NS(Math_arithmetic_subtract_from_real_ranges)(
                    NS(ParticleSet_x_begin)( diff ),
                    NS(ParticleSet_x_end)( diff ),
                    NS(ParticleSet_const_x_begin)( rhs ) );

                SIXTRL_ASSERT( NS(ParticleSet_px_length)( diff ) ==
                               NS(ParticleSet_px_length)( rhs ) );

                status |= NS(Math_arithmetic_subtract_from_real_ranges)(
                    NS(ParticleSet_px_begin)( diff ),
                    NS(ParticleSet_px_end)( diff ),
                    NS(ParticleSet_const_px_begin)( rhs ) );

                SIXTRL_ASSERT( NS(ParticleSet_y_length)( diff ) ==
                               NS(ParticleSet_y_length)( rhs ) );

                status |= NS(Math_arithmetic_subtract_from_real_ranges)(
                    NS(ParticleSet_y_begin)( diff ),
                    NS(ParticleSet_y_end)( diff ),
                    NS(ParticleSet_const_y_begin)( rhs ) );

                SIXTRL_ASSERT( NS(ParticleSet_py_length)( diff ) ==
                               NS(ParticleSet_py_length)( rhs ) );

                status |= NS(Math_arithmetic_subtract_from_real_ranges)(
                    NS(ParticleSet_py_begin)( diff ),
                    NS(ParticleSet_py_end)( diff ),
                    NS(ParticleSet_const_py_begin)( rhs ) );

                SIXTRL_ASSERT( NS(ParticleSet_zeta_length)( diff ) ==
                               NS(ParticleSet_zeta_length)( rhs ) );

                status |= NS(Math_arithmetic_subtract_from_real_ranges)(
                    NS(ParticleSet_zeta_begin)( diff ),
                    NS(ParticleSet_zeta_end)( diff ),
                    NS(ParticleSet_const_zeta_begin)( rhs ) );

                SIXTRL_ASSERT( NS(ParticleSet_delta_length)( diff ) ==
                               NS(ParticleSet_delta_length)( rhs ) );

                status |= NS(Math_arithmetic_subtract_from_real_ranges)(
                    NS(ParticleSet_delta_begin)( diff ),
                    NS(ParticleSet_delta_end)( diff ),
                    NS(ParticleSet_const_delta_begin)( rhs ) );

                SIXTRL_ASSERT( NS(ParticleSet_state_length)( diff ) ==
                               NS(ParticleSet_state_length)( rhs ) );

                status |= NS(Math_arithmetic_subtract_from_int64_ranges)(
                    NS(ParticleSet_state_begin)( diff ),
                    NS(ParticleSet_state_end)( diff ),
                    NS(ParticleSet_const_state_begin)( rhs ) );

                SIXTRL_ASSERT( NS(ParticleSet_at_element_length)( diff ) ==
                               NS(ParticleSet_at_element_length)( rhs ) );

                status |= NS(Math_arithmetic_subtract_from_int64_ranges)(
                    NS(ParticleSet_at_element_begin)( diff ),
                    NS(ParticleSet_at_element_end)( diff ),
                    NS(ParticleSet_const_at_element_begin)( rhs ) );

                SIXTRL_ASSERT( NS(ParticleSet_at_turn_length)( diff ) ==
                               NS(ParticleSet_at_turn_length)( rhs ) );

                status |= NS(Math_arithmetic_subtract_from_int64_ranges)(
                    NS(ParticleSet_at_turn_begin)( diff ),
                    NS(ParticleSet_at_turn_end)( diff ),
                    NS(ParticleSet_const_at_turn_begin)( rhs ) );

                SIXTRL_ASSERT( NS(ParticleSet_particle_id_length)( diff ) ==
                               NS(ParticleSet_particle_id_length)( rhs ) );

                status |= NS(Math_arithmetic_subtract_from_int64_ranges)(
                    NS(ParticleSet_particle_id_begin)( diff ),
                    NS(ParticleSet_particle_id_end)( diff ),
                    NS(ParticleSet_const_particle_id_begin)( rhs ) );

                SIXTRL_ASSERT( NS(ParticleSet_psigma_length)( diff ) ==
                               NS(ParticleSet_psigma_length)( rhs ) );

                status |= NS(Math_arithmetic_subtract_from_real_ranges)(
                    NS(ParticleSet_psigma_begin)( diff ),
                    NS(ParticleSet_psigma_end)( diff ),
                    NS(ParticleSet_const_psigma_begin)( rhs ) );

                SIXTRL_ASSERT( NS(ParticleSet_rpp_length)( diff ) ==
                               NS(ParticleSet_rpp_length)( rhs ) );

                status |= NS(Math_arithmetic_subtract_from_real_ranges)(
                    NS(ParticleSet_rpp_begin)( diff ),
                    NS(ParticleSet_rpp_end)( diff ),
                    NS(ParticleSet_const_rpp_begin)( rhs ) );

                SIXTRL_ASSERT( NS(ParticleSet_rvv_length)( diff ) ==
                               NS(ParticleSet_rvv_length)( rhs ) );

                status |= NS(Math_arithmetic_subtract_from_real_ranges)(
                    NS(ParticleSet_rvv_begin)( diff ),
                    NS(ParticleSet_rvv_end)( diff ),
                    NS(ParticleSet_const_rvv_begin)( rhs ) );

                SIXTRL_ASSERT( NS(ParticleSet_chi_length)( diff ) ==
                               NS(ParticleSet_chi_length)( rhs ) );

                status |= NS(Math_arithmetic_subtract_from_real_ranges)(
                    NS(ParticleSet_chi_begin)( diff ),
                    NS(ParticleSet_chi_end)( diff ),
                    NS(ParticleSet_const_chi_begin)( rhs ) );

                SIXTRL_ASSERT( NS(ParticleSet_charge_ratio_length)( diff ) ==
                               NS(ParticleSet_charge_ratio_length)( rhs ) );

                status |= NS(Math_arithmetic_subtract_from_real_ranges)(
                    NS(ParticleSet_charge_ratio_begin)( diff ),
                    NS(ParticleSet_charge_ratio_end)( diff ),
                    NS(ParticleSet_const_charge_ratio_begin)( rhs ) );

                SIXTRL_ASSERT( NS(ParticleSet_charge0_length)( diff ) ==
                               NS(ParticleSet_charge0_length)( rhs ) );

                status |= NS(Math_arithmetic_subtract_from_real_ranges)(
                    NS(ParticleSet_charge0_begin)( diff ),
                    NS(ParticleSet_charge0_end)( diff ),
                    NS(ParticleSet_const_charge0_begin)( rhs ) );

                SIXTRL_ASSERT( NS(ParticleSet_mass0_length)( diff ) ==
                               NS(ParticleSet_mass0_length)( rhs ) );

                status |= NS(Math_arithmetic_subtract_from_real_ranges)(
                    NS(ParticleSet_mass0_begin)( diff ),
                    NS(ParticleSet_mass0_end)( diff ),
                    NS(ParticleSet_const_mass0_begin)( rhs ) );


                SIXTRL_ASSERT( NS(ParticleSet_beta0_length)( diff ) ==
                               NS(ParticleSet_beta0_length)( rhs ) );

                status |= NS(Math_arithmetic_subtract_from_real_ranges)(
                    NS(ParticleSet_beta0_begin)( diff ),
                    NS(ParticleSet_beta0_end)( diff ),
                    NS(ParticleSet_const_beta0_begin)( rhs ) );

                SIXTRL_ASSERT( NS(ParticleSet_gamma0_length)( diff ) ==
                               NS(ParticleSet_gamma0_length)( rhs ) );

                status |= NS(Math_arithmetic_subtract_from_real_ranges)(
                    NS(ParticleSet_gamma0_begin)( diff ),
                    NS(ParticleSet_gamma0_end)( diff ),
                    NS(ParticleSet_const_gamma0_begin)( rhs ) );

                SIXTRL_ASSERT( NS(ParticleSet_pc0_length)( diff ) ==
                               NS(ParticleSet_pc0_length)( rhs ) );

                status |= NS(Math_arithmetic_subtract_from_real_ranges)(
                    NS(ParticleSet_pc0_begin)( diff ),
                    NS(ParticleSet_pc0_end)( diff ),
                    NS(ParticleSet_const_pc0_begin)( rhs ) );

                SIXTRL_ASSERT( NS(ParticleSet_s_length)( diff ) ==
                               NS(ParticleSet_s_length)( rhs ) );

                status |= NS(Math_arithmetic_subtract_from_real_ranges)(
                    NS(ParticleSet_s_begin)( diff ),
                    NS(ParticleSet_s_end)( diff ),
                    NS(ParticleSet_const_s_begin)( rhs ) );
            }
        }
        else if( rhs != SIXTRL_NULLPTR )
        {
            if( NS(ParticleSet_allow_conversion)( diff, lhs,
                    SIXTRL_STORAGE_BE_DEFAULT, SIXTRL_STORAGE_BE_DEFAULT ) )
            {
                status = NS(ParticleSet_convert)( diff, lhs,
                    SIXTRL_STORAGE_BE_DEFAULT, SIXTRL_STORAGE_BE_DEFAULT );
            }

            if( status == ( NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS )
            {
                status  = NS(Math_arithmetic_change_sign_for_real_ranges)(
                    NS(ParticleSet_x_begin)( diff ),
                    NS(ParticleSet_x_end)( diff ) );

                status |= NS(Math_arithmetic_change_sign_for_real_ranges)(
                    NS(ParticleSet_px_begin)( diff ),
                    NS(ParticleSet_px_end)( diff ) );

                status |= NS(Math_arithmetic_change_sign_for_real_ranges)(
                    NS(ParticleSet_y_begin)( diff ),
                    NS(ParticleSet_y_end)( diff ) );

                status |= NS(Math_arithmetic_change_sign_for_real_ranges)(
                    NS(ParticleSet_py_begin)( diff ),
                    NS(ParticleSet_py_end)( diff ) );

                status |= NS(Math_arithmetic_change_sign_for_real_ranges)(
                    NS(ParticleSet_zeta_begin)( diff ),
                    NS(ParticleSet_zeta_end)( diff ) );

                status |= NS(Math_arithmetic_change_sign_for_real_ranges)(
                    NS(ParticleSet_delta_begin)( diff ),
                    NS(ParticleSet_delta_end)( diff ) );

                status |= NS(Math_arithmetic_change_sign_for_int64_ranges)(
                    NS(ParticleSet_state_begin)( diff ),
                    NS(ParticleSet_state_end)( diff ) );

                status |= NS(Math_arithmetic_change_sign_for_int64_ranges)(
                    NS(ParticleSet_at_element_begin)( diff ),
                    NS(ParticleSet_at_element_end)( diff ) );

                status |= NS(Math_arithmetic_change_sign_for_int64_ranges)(
                    NS(ParticleSet_at_turn_begin)( diff ),
                    NS(ParticleSet_at_turn_end)( diff ) );

                status |= NS(Math_arithmetic_change_sign_for_int64_ranges)(
                    NS(ParticleSet_particle_id_begin)( diff ),
                    NS(ParticleSet_particle_id_end)( diff ) );

                status |= NS(Math_arithmetic_change_sign_for_real_ranges)(
                    NS(ParticleSet_psigma_begin)( diff ),
                    NS(ParticleSet_psigma_end)( diff ) );

                status |= NS(Math_arithmetic_change_sign_for_real_ranges)(
                    NS(ParticleSet_rpp_begin)( diff ),
                    NS(ParticleSet_rpp_end)( diff ) );

                status |= NS(Math_arithmetic_change_sign_for_real_ranges)(
                    NS(ParticleSet_rvv_begin)( diff ),
                    NS(ParticleSet_rvv_end)( diff ) );

                status |= NS(Math_arithmetic_change_sign_for_real_ranges)(
                    NS(ParticleSet_chi_begin)( diff ),
                    NS(ParticleSet_chi_end)( diff ) );

                status |= NS(Math_arithmetic_change_sign_for_real_ranges)(
                    NS(ParticleSet_charge_ratio_begin)( diff ),
                    NS(ParticleSet_charge_ratio_end)( diff ) );

                status |= NS(Math_arithmetic_change_sign_for_real_ranges)(
                    NS(ParticleSet_charge0_begin)( diff ),
                    NS(ParticleSet_charge0_end)( diff ) );

                status |= NS(Math_arithmetic_change_sign_for_real_ranges)(
                    NS(ParticleSet_mass0_begin)( diff ),
                    NS(ParticleSet_mass0_end)( diff ) );

                status |= NS(Math_arithmetic_change_sign_for_real_ranges)(
                    NS(ParticleSet_beta0_begin)( diff ),
                    NS(ParticleSet_beta0_end)( diff ) );

                status |= NS(Math_arithmetic_change_sign_for_real_ranges)(
                    NS(ParticleSet_gamma0_begin)( diff ),
                    NS(ParticleSet_gamma0_end)( diff ) );

                status |= NS(Math_arithmetic_change_sign_for_real_ranges)(
                    NS(ParticleSet_pc0_begin)( diff ),
                    NS(ParticleSet_pc0_end)( diff ) );

                status |= NS(Math_arithmetic_change_sign_for_real_ranges)(
                    NS(ParticleSet_s_begin)( diff ),
                    NS(ParticleSet_s_end)( diff ) );
            }
        }
    }

    return status;
}

SIXTRL_INLINE int NS(ParticleSet_compare)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const NS(ParticleSet) *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const NS(ParticleSet) *const SIXTRL_RESTRICT rhs
) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( lhs != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( rhs != SIXTRL_NULLPTR );

    int cmp_result = ( NS(ParticleSet_num_particles)( lhs ) ==
                       NS(ParticleSet_num_particles)( rhs ) )
        ? 0 : ( NS(ParticleSet_num_particles)( lhs ) >
                NS(ParticleSet_num_particles)( rhs ) ) ? +1 : -1;

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_for_range)(
            NS(ParticleSet_const_x_begin)( lhs ),
            NS(ParticleSet_const_x_end)( lhs ),
            NS(ParticleSet_const_x_begin)( rhs ) );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_for_range)(
            NS(ParticleSet_const_px_begin)( lhs ),
            NS(ParticleSet_const_px_end)( lhs ),
            NS(ParticleSet_const_px_begin)( rhs ) );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_for_range)(
            NS(ParticleSet_const_y_begin)( lhs ),
            NS(ParticleSet_const_y_end)( lhs ),
            NS(ParticleSet_const_y_begin)( rhs ) );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_for_range)(
            NS(ParticleSet_const_py_begin)( lhs ),
            NS(ParticleSet_const_py_end)( lhs ),
            NS(ParticleSet_const_py_begin)( rhs ) );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_for_range)(
            NS(ParticleSet_const_zeta_begin)( lhs ),
            NS(ParticleSet_const_zeta_end)( lhs ),
            NS(ParticleSet_const_zeta_begin)( rhs ) );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_for_range)(
            NS(ParticleSet_const_delta_begin)( lhs ),
            NS(ParticleSet_const_delta_end)( lhs ),
            NS(ParticleSet_const_delta_begin)( rhs ) );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_int64_for_range)(
            NS(ParticleSet_const_state_begin)( lhs ),
            NS(ParticleSet_const_state_end)( lhs ),
            NS(ParticleSet_const_state_begin)( rhs ) );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_int64_for_range)(
            NS(ParticleSet_const_at_element_begin)( lhs ),
            NS(ParticleSet_const_at_element_end)( lhs ),
            NS(ParticleSet_const_at_element_begin)( rhs ) );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_int64_for_range)(
            NS(ParticleSet_const_at_turn_begin)( lhs ),
            NS(ParticleSet_const_at_turn_end)( lhs ),
            NS(ParticleSet_const_at_turn_begin)( rhs ) );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_int64_for_range)(
            NS(ParticleSet_const_particle_id_begin)( lhs ),
            NS(ParticleSet_const_particle_id_end)( lhs ),
            NS(ParticleSet_const_particle_id_begin)( rhs ) );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_for_range)(
            NS(ParticleSet_const_psigma_begin)( lhs ),
            NS(ParticleSet_const_psigma_end)( lhs ),
            NS(ParticleSet_const_psigma_begin)( rhs ) );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_for_range)(
            NS(ParticleSet_const_rpp_begin)( lhs ),
            NS(ParticleSet_const_rpp_end)( lhs ),
            NS(ParticleSet_const_rpp_begin)( rhs ) );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_for_range)(
            NS(ParticleSet_const_rvv_begin)( lhs ),
            NS(ParticleSet_const_rvv_end)( lhs ),
            NS(ParticleSet_const_rvv_begin)( rhs ) );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_for_range)(
            NS(ParticleSet_const_chi_begin)( lhs ),
            NS(ParticleSet_const_chi_end)( lhs ),
            NS(ParticleSet_const_chi_begin)( rhs ) );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_for_range)(
            NS(ParticleSet_const_charge_ratio_begin)( lhs ),
            NS(ParticleSet_const_charge_ratio_end)( lhs ),
            NS(ParticleSet_const_charge_ratio_begin)( rhs ) );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_for_range)(
            NS(ParticleSet_const_charge0_begin)( lhs ),
            NS(ParticleSet_const_charge0_end)( lhs ),
            NS(ParticleSet_const_charge0_begin)( rhs ) );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_for_range)(
            NS(ParticleSet_const_mass0_begin)( lhs ),
            NS(ParticleSet_const_mass0_end)( lhs ),
            NS(ParticleSet_const_mass0_begin)( rhs ) );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_for_range)(
            NS(ParticleSet_const_beta0_begin)( lhs ),
            NS(ParticleSet_const_beta0_end)( lhs ),
            NS(ParticleSet_const_beta0_begin)( rhs ) );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_for_range)(
            NS(ParticleSet_const_gamma0_begin)( lhs ),
            NS(ParticleSet_const_gamma0_end)( lhs ),
            NS(ParticleSet_const_gamma0_begin)( rhs ) );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_for_range)(
            NS(ParticleSet_const_pc0_begin)( lhs ),
            NS(ParticleSet_const_pc0_end)( lhs ),
            NS(ParticleSet_const_pc0_begin)( rhs ) );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_for_range)(
            NS(ParticleSet_const_s_begin)( lhs ),
            NS(ParticleSet_const_s_end)( lhs ),
            NS(ParticleSet_const_s_begin)( rhs ) );

    return cmp_result;
}

SIXTRL_INLINE int NS(ParticleSet_compare_with_tolerances)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const
        NS(ParticleSet) *const SIXTRL_RESTRICT lhs,
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const
        NS(ParticleSet) *const SIXTRL_RESTRICT rhs,
    NS(particle_real_t) const rel_tol, NS(particle_real_t) const abs_tol
) SIXTRL_NOEXCEPT
{
    SIXTRL_ASSERT( lhs != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( rhs != SIXTRL_NULLPTR );

    int cmp_result = ( NS(ParticleSet_num_particles)( lhs ) ==
                       NS(ParticleSet_num_particles)( rhs ) )
        ? 0 : ( NS(ParticleSet_num_particles)( lhs ) >
                NS(ParticleSet_num_particles)( rhs ) ) ? +1 : -1;

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_with_tolerances_for_range)(
            NS(ParticleSet_const_x_begin)( lhs ),
            NS(ParticleSet_const_x_end)( lhs ),
            NS(ParticleSet_const_x_begin)( rhs ), rel_tol, abs_tol );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_with_tolerances_for_range)(
            NS(ParticleSet_const_px_begin)( lhs ),
            NS(ParticleSet_const_px_end)( lhs ),
            NS(ParticleSet_const_px_begin)( rhs ), rel_tol, abs_tol );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_with_tolerances_for_range)(
            NS(ParticleSet_const_y_begin)( lhs ),
            NS(ParticleSet_const_y_end)( lhs ),
            NS(ParticleSet_const_y_begin)( rhs ), rel_tol, abs_tol );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_with_tolerances_for_range)(
            NS(ParticleSet_const_py_begin)( lhs ),
            NS(ParticleSet_const_py_end)( lhs ),
            NS(ParticleSet_const_py_begin)( rhs ), rel_tol, abs_tol );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_with_tolerances_for_range)(
            NS(ParticleSet_const_zeta_begin)( lhs ),
            NS(ParticleSet_const_zeta_end)( lhs ),
            NS(ParticleSet_const_zeta_begin)( rhs ), rel_tol, abs_tol );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_with_tolerances_for_range)(
            NS(ParticleSet_const_delta_begin)( lhs ),
            NS(ParticleSet_const_delta_end)( lhs ),
            NS(ParticleSet_const_delta_begin)( rhs ), rel_tol, abs_tol );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_int64_for_range)(
            NS(ParticleSet_const_state_begin)( lhs ),
            NS(ParticleSet_const_state_end)( lhs ),
            NS(ParticleSet_const_state_begin)( rhs ) );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_int64_for_range)(
            NS(ParticleSet_const_at_element_begin)( lhs ),
            NS(ParticleSet_const_at_element_end)( lhs ),
            NS(ParticleSet_const_at_element_begin)( rhs ) );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_int64_for_range)(
            NS(ParticleSet_const_at_turn_begin)( lhs ),
            NS(ParticleSet_const_at_turn_end)( lhs ),
            NS(ParticleSet_const_at_turn_begin)( rhs ) );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_int64_for_range)(
            NS(ParticleSet_const_particle_id_begin)( lhs ),
            NS(ParticleSet_const_particle_id_end)( lhs ),
            NS(ParticleSet_const_particle_id_begin)( rhs ) );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_with_tolerances_for_range)(
            NS(ParticleSet_const_psigma_begin)( lhs ),
            NS(ParticleSet_const_psigma_end)( lhs ),
            NS(ParticleSet_const_psigma_begin)( rhs ), rel_tol, abs_tol );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_with_tolerances_for_range)(
            NS(ParticleSet_const_rpp_begin)( lhs ),
            NS(ParticleSet_const_rpp_end)( lhs ),
            NS(ParticleSet_const_rpp_begin)( rhs ), rel_tol, abs_tol );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_with_tolerances_for_range)(
            NS(ParticleSet_const_rvv_begin)( lhs ),
            NS(ParticleSet_const_rvv_end)( lhs ),
            NS(ParticleSet_const_rvv_begin)( rhs ), rel_tol, abs_tol );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_with_tolerances_for_range)(
            NS(ParticleSet_const_chi_begin)( lhs ),
            NS(ParticleSet_const_chi_end)( lhs ),
            NS(ParticleSet_const_chi_begin)( rhs ), rel_tol, abs_tol );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_with_tolerances_for_range)(
            NS(ParticleSet_const_charge_ratio_begin)( lhs ),
            NS(ParticleSet_const_charge_ratio_end)( lhs ),
            NS(ParticleSet_const_charge_ratio_begin)( rhs ), rel_tol, abs_tol );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_with_tolerances_for_range)(
            NS(ParticleSet_const_charge0_begin)( lhs ),
            NS(ParticleSet_const_charge0_end)( lhs ),
            NS(ParticleSet_const_charge0_begin)( rhs ), rel_tol, abs_tol );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_with_tolerances_for_range)(
            NS(ParticleSet_const_mass0_begin)( lhs ),
            NS(ParticleSet_const_mass0_end)( lhs ),
            NS(ParticleSet_const_mass0_begin)( rhs ), rel_tol, abs_tol );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_with_tolerances_for_range)(
            NS(ParticleSet_const_beta0_begin)( lhs ),
            NS(ParticleSet_const_beta0_end)( lhs ),
            NS(ParticleSet_const_beta0_begin)( rhs ), rel_tol, abs_tol );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_with_tolerances_for_range)(
            NS(ParticleSet_const_gamma0_begin)( lhs ),
            NS(ParticleSet_const_gamma0_end)( lhs ),
            NS(ParticleSet_const_gamma0_begin)( rhs ), rel_tol, abs_tol );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_with_tolerances_for_range)(
            NS(ParticleSet_const_pc0_begin)( lhs ),
            NS(ParticleSet_const_pc0_end)( lhs ),
            NS(ParticleSet_const_pc0_begin)( rhs ), rel_tol, abs_tol );

    if( cmp_result == 0 )
        cmp_result = NS(Type_value_comp_result_with_tolerances_for_range)(
            NS(ParticleSet_const_s_begin)( lhs ),
            NS(ParticleSet_const_s_end)( lhs ),
            NS(ParticleSet_const_s_begin)( rhs ), rel_tol, abs_tol );

    return cmp_result;
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SET_COMPARE_H__ */
