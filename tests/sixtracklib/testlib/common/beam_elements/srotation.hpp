#ifndef SIXTRACKLIB_TESTLIB_COMMON_BEAM_ELEMENTS_SROTATION_CXX_HPP__
#define SIXTRACKLIB_TESTLIB_COMMON_BEAM_ELEMENTS_SROTATION_CXX_HPP__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <iostream>
    #endif /* defined( __cplusplus ) */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/srotation.hpp"
    #include "sixtracklib/common/cobjects/cbuffer_view.hpp"
    #include "sixtracklib/common/cobjects/cbuffer.hpp"
    #include "sixtracklib/common/internal/compiler_attributes.h"
    #include "sixtracklib/common/internal/math_constants.h"
    #include "sixtracklib/common/internal/type_random_traits.hpp"
    #include "sixtracklib/testlib/common/objs/objs_traits.hpp"
    #include "sixtracklib/testlib/common/cobjects/cobj_elem_traits.hpp"
    #include "sixtracklib/testlib/common/cobjects/cobjects_initialiser_base.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    template< class SRotationT >
    class SRotationInitialiser : public CObjElemInitialiserBase
    {
        public:

        static_assert( SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >(),
           "Requires SRotationT to be a multipole class" );

        typedef typename SIXTRL_CXX_NAMESPACE::SRotationTraits< SRotationT
            >::real_t real_t;

        private:

        typedef SIXTRL_CXX_NAMESPACE::TypeRandomTraits< real_t >
                real_random_traits_t;

        static_assert( real_random_traits_t::has_uniform_dist,
            "Requires a uniform distribution for the real_t" );

        public:

        typedef typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits<
                         real_t >::const_argument_type const_real_arg_t;

        typedef typename real_random_traits_t::uniform_dist_t  angle_dist_t;
        typedef typename real_random_traits_t::default_prng_t  real_prng_t;
        typedef typename real_random_traits_t::default_prng_seed_t
                         real_prng_seed_t;

        typedef SIXTRL_CXX_NAMESPACE::CBufferView cbuffer_view_t;
        typedef SIXTRL_CXX_NAMESPACE::CBuffer cbuffer_t;

        SIXTRL_HOST_FN SRotationInitialiser() :
            m_real_prng( real_prng_seed_t{ 2020519 } ),
            m_angle_deg_dist( real_t{ -45 }, real_t{ +45 } )
        {

        }

        SIXTRL_HOST_FN explicit SRotationInitialiser(
            const_real_arg_t min_angle_deg,
            const_real_arg_t max_angle_deg ) :
            m_real_prng( real_prng_seed_t{ 2020519 } ),
            m_angle_deg_dist( min_angle_deg, max_angle_deg )
        {

        }

        SIXTRL_HOST_FN SRotationInitialiser(
            SRotationInitialiser< SRotationT > const& ) = default;

        SIXTRL_HOST_FN SRotationInitialiser(
            SRotationInitialiser< SRotationT >&& ) = default;

        SIXTRL_HOST_FN SRotationInitialiser< SRotationT >& operator=(
            SRotationInitialiser< SRotationT > const& ) = default;

        SIXTRL_HOST_FN SRotationInitialiser< SRotationT >& operator=(
            SRotationInitialiser< SRotationT >&& ) = default;

        SIXTRL_HOST_FN virtual ~SRotationInitialiser() = default;

        template< typename... Args >
        SIXTRL_HOST_FN status_t operator()(
                SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem,
                Args&&... init_parameters )
        {
            return SIXTRL_CXX_NAMESPACE::SRotation_init(
                elem, std::forward< Args >( init_parameters )... );
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        template< class OtherSRotationT >
        SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
           !SIXTRL_CXX_NAMESPACE::SRotation_is_type< OtherSRotationT >(),
            status_t >::type
        init_for_copy(
            SIXTRL_BE_ARGPTR_DEC SRotationT*
                SIXTRL_RESTRICT SIXTRL_UNUSED( elem ),
            SIXTRL_BE_ARGPTR_DEC const OtherSRotationT *const SIXTRL_RESTRICT
                SIXTRL_UNUSED( orig ) )
        {
            return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
        }

        template< class OtherSRotationT >
        SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
           SIXTRL_CXX_NAMESPACE::SRotation_is_type< OtherSRotationT >(),
           status_t >::type
        init_for_copy(
            SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem,
            SIXTRL_BE_ARGPTR_DEC const OtherSRotationT *const SIXTRL_RESTRICT
                SIXTRL_UNUSED( orig ) )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;

            return ( ( elem != SIXTRL_NULLPTR ) &&
                     ( elem == st::SRotation_preset( elem ) ) )
                ? st::ARCH_STATUS_SUCCESS : st::ARCH_STATUS_GENERAL_FAILURE;
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_INLINE SIXTRL_HOST_FN status_t randomise(
                SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem )
        {
            return this->randomise_values( elem );
        }

        SIXTRL_INLINE SIXTRL_HOST_FN status_t randomise_values(
                SIXTRL_BE_ARGPTR_DEC SRotationT* SIXTRL_RESTRICT elem )
        {
            return SIXTRL_CXX_NAMESPACE::SRotation_update_angle_deg(
                elem, this->random_angle_deg_value( this->m_real_prng ) );
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
        SIXTRL_BE_ARGPTR_DEC SRotationT* create_new(
            cbuffer_view_t& SIXTRL_RESTRICT_REF view,
            SIXTRL_BE_ARGPTR_DEC SRotationT const* SIXTRL_RESTRICT orig )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            SIXTRL_BE_ARGPTR_DEC SRotationT* added_elem = nullptr;

            if( orig != nullptr )
            {
                added_elem = st::CBufferView_create_new_object<
                    SRotationT >( view );

                if( st::SRotation_convert( added_elem, orig ) !=
                    st::ARCH_STATUS_SUCCESS )
                {
                    added_elem = SIXTRL_NULLPTR;
                }
            }

            return added_elem;
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
        SIXTRL_BE_ARGPTR_DEC SRotationT* create_new(
            cbuffer_t& SIXTRL_RESTRICT_REF buffer,
            SIXTRL_BE_ARGPTR_DEC SRotationT const* SIXTRL_RESTRICT orig )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            SIXTRL_BE_ARGPTR_DEC SRotationT* added_elem = nullptr;

            if( orig != nullptr )
            {
                added_elem = buffer.create_new< SRotationT >();

                if( st::SRotation_convert( added_elem, orig ) !=
                    st::ARCH_STATUS_SUCCESS )
                {
                    added_elem = nullptr;
                }
            }

            return added_elem;
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
        SIXTRL_BE_ARGPTR_DEC SRotationT* add_new(
            cbuffer_view_t& SIXTRL_RESTRICT_REF view,
            SIXTRL_BE_ARGPTR_DEC SRotationT const* SIXTRL_RESTRICT orig )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            SIXTRL_BE_ARGPTR_DEC SRotationT* added_elem = nullptr;

            if( orig != nullptr )
            {
                added_elem = st::CBufferView_add_object< SRotationT >( view,
                    st::SRotation_cos_z( orig ), st::SRotation_sin_z( orig ) );
            }

            return added_elem;
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
        SIXTRL_BE_ARGPTR_DEC SRotationT* add_new(
            cbuffer_t& SIXTRL_RESTRICT_REF buffer,
            SIXTRL_BE_ARGPTR_DEC SRotationT const* SIXTRL_RESTRICT orig )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            SIXTRL_BE_ARGPTR_DEC SRotationT* added_elem = nullptr;

            if( orig != nullptr )
            {
                added_elem = buffer.template add< SRotationT >(
                    st::SRotation_cos_z( orig ), st::SRotation_sin_z( orig ) );
            }

            return added_elem;
        }

        template< class PrngT >
        SIXTRL_INLINE SIXTRL_HOST_FN real_t
        random_angle_deg_value( PrngT& SIXTRL_RESTRICT prng )
        {
            return this->m_angle_deg_dist( prng );
        }

        SIXTRL_INLINE SIXTRL_HOST_FN real_t random_angle_deg_value()
        {
            return this->m_angle_deg_dist( this->m_real_prng );
        }

        private:

        real_prng_t  m_real_prng;
        angle_dist_t m_angle_deg_dist;
    };

    /* ===================================================================== */

    template< class SRotationT >
    struct ObjsRandomInitialiserTraits< SRotationT, typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >(), void >::type >
    {
        typedef SIXTRL_CXX_NAMESPACE::tests::SRotationInitialiser<
                    SRotationT > initialiser_t;
    };

    template< class SRotationT >
    struct CObjElemInitialiserTraits< SRotationT, typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >() &&
        SIXTRL_CXX_NAMESPACE::CObjElem_type_id< SRotationT >() !=
            SIXTRL_CXX_NAMESPACE::ObjTypeId_illegal_type_id<
                SIXTRL_CXX_NAMESPACE::cobj_type_id_t >(), void >::type >
    {
        typedef SIXTRL_CXX_NAMESPACE::tests::SRotationInitialiser< SRotationT >
                initialiser_t;
    };

    /* ===================================================================== */

    template< class SRotationT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::SRotation_is_type< SRotationT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    SRotation_tests_assignment(
        SIXTRL_CXX_NAMESPACE::arch_size_t const num_elems
            = SIXTRL_CXX_NAMESPACE::arch_size_t{ 100 } ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename st::SRotationTraits< SRotationT >::real_t real_t;
        typedef typename st::tests::ObjsRandomInitialiserTraits<
                    SRotationT >::initialiser_t obj_init_t;

        real_t const ABS_TOL = real_t{ 1000 } *
            std::numeric_limits< real_t >::epsilon();

        real_t const REL_TOL = real_t{ 1000 } *
            std::numeric_limits< real_t >::epsilon();

        std::cout << "ABS_TOL = " << ABS_TOL << "\r\n"
                  << "REL_TOL = " << REL_TOL << "\r\n"
                  << std::endl;

        typedef st::arch_size_t st_size_t;
        obj_init_t obj_init;

        SRotationT srot;
        st::SRotation_preset( &srot );

        st::arch_status_t status = obj_init.randomise( &srot );
        if( status != st::ARCH_STATUS_SUCCESS ) return status;

        for( st_size_t ii = st_size_t{ 0 } ; ii < num_elems ; ++ii )
        {
            real_t const random_angle_deg = obj_init.random_angle_deg_value();
            real_t const random_angle_rad = st::MathConst_deg2rad<
                real_t >() * random_angle_deg;

            real_t const random_cos_z = st::cos< real_t >( random_angle_rad );
            real_t const random_sin_z = st::sin< real_t >( random_angle_rad );

            real_t const saved_cos_z = st::SRotation_cos_z( &srot );
            real_t const saved_sin_z = st::SRotation_sin_z( &srot );

            if( ( st::Type_comp_all_equal< real_t >( random_cos_z, saved_cos_z ) ) &&
                ( st::Type_comp_all_equal< real_t >( random_sin_z, saved_sin_z ) ) )
            {
                continue;
            }

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            status = st::SRotation_update_angle_rad( &srot, random_angle_rad );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            if( !st::Type_comp_all_are_close< real_t >( random_cos_z,
                    st::SRotation_cos_z( &srot ), REL_TOL, ABS_TOL ) )
            {
                real_t const diff = random_cos_z - st::SRotation_cos_z( &srot );
                std::cout << "update angle_rad :: diff cos_z = \r\n"
                          << random_cos_z << " - \r\n"
                          << st::SRotation_cos_z( &srot ) << " = \r\n"
                          << diff << std::endl;

                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }

            if( !st::Type_comp_all_are_close< real_t >( random_sin_z,
                    st::SRotation_sin_z( &srot ), REL_TOL, ABS_TOL ) )
            {
                real_t const diff = random_sin_z - st::SRotation_sin_z( &srot );
                std::cout << "update angle_rad :: diff sin_z = \r\n"
                          << random_sin_z << " - \r\n"
                          << st::SRotation_sin_z( &srot ) << " = \r\n"
                          << diff << std::endl;

                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }

            if( !st::Type_comp_all_are_close< real_t >( random_angle_rad,
                    st::SRotation_angle_rad( &srot ), REL_TOL, ABS_TOL ) )
            {
                real_t const diff = random_angle_rad -
                    st::SRotation_angle_rad( &srot );

                std::cout << "update angle_rad :: diff angle_rad = \r\n"
                          << random_angle_rad << " - \r\n"
                          << st::SRotation_angle_rad( &srot ) << " = \r\n"
                          << diff << std::endl;

                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }

            if( !st::Type_comp_all_are_close< real_t >( random_angle_deg,
                    st::SRotation_angle_deg( &srot ), REL_TOL, ABS_TOL ) )
            {
                real_t const diff = random_angle_deg -
                    st::SRotation_angle_deg( &srot );

                std::cout << "update angle_rad :: diff angle_deg = \r\n"
                          << random_angle_deg << " - \r\n"
                          << st::SRotation_angle_deg( &srot ) << " = \r\n"
                          << diff << std::endl;

                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            status = st::SRotation_update_angle_deg( &srot, random_angle_deg );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            if( !st::Type_comp_all_are_close< real_t >( random_cos_z,
                    st::SRotation_cos_z( &srot ), REL_TOL, ABS_TOL ) )
            {
                real_t const diff = random_cos_z - st::SRotation_cos_z( &srot );
                std::cout << "update angle_deg :: diff cos_z = \r\n"
                          << random_cos_z << " - \r\n"
                          << st::SRotation_cos_z( &srot ) << " = \r\n"
                          << diff << std::endl;

                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }

            if( !st::Type_comp_all_are_close< real_t >( random_sin_z,
                    st::SRotation_sin_z( &srot ), REL_TOL, ABS_TOL ) )
            {
                real_t const diff = random_sin_z - st::SRotation_sin_z( &srot );
                std::cout << "update angle_deg :: diff sin_z = \r\n"
                          << random_sin_z << " - \r\n"
                          << st::SRotation_sin_z( &srot ) << " = \r\n"
                          << diff << std::endl;

                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }

            if( !st::Type_comp_all_are_close< real_t >( random_angle_rad,
                    st::SRotation_angle_rad( &srot ), REL_TOL, ABS_TOL ) )
            {
                real_t const diff = random_angle_rad -
                                    st::SRotation_angle_rad( &srot );

                std::cout << "update angle_deg :: diff angle_rad = \r\n"
                          << random_angle_rad << " - \r\n"
                          << st::SRotation_angle_rad( &srot ) << " = \r\n"
                          << diff << std::endl;

                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }

            if( !st::Type_comp_all_are_close< real_t >( random_angle_deg,
                    st::SRotation_angle_deg( &srot ), REL_TOL, ABS_TOL ) )
            {
                real_t const diff = random_angle_deg -
                                    st::SRotation_angle_deg( &srot );

                std::cout << "update angle_deg :: diff angle_deg = \r\n"
                          << random_angle_deg << " - \r\n"
                          << st::SRotation_angle_deg( &srot ) << " = \r\n"
                          << diff << std::endl;

                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            status = st::SRotation_set_cos_z( &srot, random_cos_z );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            status = st::SRotation_set_sin_z( &srot, random_sin_z );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            if( !st::Type_comp_all_equal< real_t >( random_cos_z,
                    st::SRotation_cos_z( &srot ) ) )
            {
                real_t const diff = random_cos_z - st::SRotation_cos_z( &srot );
                std::cout << "update cos_z / sin_z :: diff cos_z = \r\n"
                          << random_cos_z << " - \r\n"
                          << st::SRotation_cos_z( &srot ) << " = \r\n"
                          << diff << std::endl;

                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }

            if( !st::Type_comp_all_equal< real_t >( random_sin_z,
                    st::SRotation_sin_z( &srot ) ) )
            {
                real_t const diff = random_sin_z - st::SRotation_sin_z( &srot );
                std::cout << "update cos_z / sin_z :: diff sin_z = \r\n"
                          << random_sin_z << " - \r\n"
                          << st::SRotation_sin_z( &srot ) << " = \r\n"
                          << diff << std::endl;

                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }

            if( !st::Type_comp_all_are_close< real_t >( random_angle_rad,
                    st::SRotation_angle_rad( &srot ), REL_TOL, ABS_TOL ) )
            {
                real_t const diff = random_angle_rad -
                                    st::SRotation_angle_rad( &srot );

                std::cout << "update cos_z / sin_z :: diff angle_rad = \r\n"
                          << random_angle_rad << " - \r\n"
                          << st::SRotation_angle_rad( &srot ) << " = \r\n"
                          << diff << std::endl;

                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }

            if( !st::Type_comp_all_are_close< real_t >( random_angle_deg,
                    st::SRotation_angle_deg( &srot ), REL_TOL, ABS_TOL ) )
            {
                real_t const diff = random_angle_deg -
                                    st::SRotation_angle_deg( &srot );

                std::cout << "update cos_z / sin_z :: diff angle_deg = \r\n"
                          << random_angle_deg << " - \r\n"
                          << st::SRotation_angle_deg( &srot ) << " = \r\n"
                          << diff << std::endl;

                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            status = st::SRotation_set_cos_z( &srot, saved_cos_z );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            status = st::SRotation_set_sin_z( &srot, saved_sin_z );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            if( !st::Type_comp_all_equal< real_t >(
                saved_cos_z, st::SRotation_cos_z( &srot ) ) )
            {
                real_t const diff = saved_cos_z - st::SRotation_cos_z( &srot );

                std::cout << "restore cos_z / sin_z :: diff cos_z = \r\n"
                          << saved_cos_z << " - \r\n"
                          << st::SRotation_angle_rad( &srot ) << " = \r\n"
                          << diff << std::endl;

                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }

            if( !st::Type_comp_all_equal< real_t >(
                saved_sin_z, st::SRotation_sin_z( &srot ) ) )
            {
                real_t const diff = saved_sin_z - st::SRotation_sin_z( &srot );

                std::cout << "restore cos_z / sin_z :: diff sin_z = \r\n"
                          << saved_sin_z << " - \r\n"
                          << st::SRotation_angle_rad( &srot ) << " = \r\n"
                          << diff << std::endl;

                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }
        }

        return status;
    }

} /* namespace: tests */
} /* namespace: SIXTRL_CXX_NAMESPACE */

#endif /* C++, Host */
#endif /* SIXTRACKLIB_TESTLIB_COMMON_BEAM_ELEMENTS_SROTATION_CXX_HPP__ */
