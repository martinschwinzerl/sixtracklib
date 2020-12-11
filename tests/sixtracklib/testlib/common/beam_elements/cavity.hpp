#ifndef SIXTRACKLIB_TESTLIB_COMMON_BEAM_ELEMENTS_CAVITY_CXX_HPP__
#define SIXTRACKLIB_TESTLIB_COMMON_BEAM_ELEMENTS_CAVITY_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/cavity.hpp"
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
    template< class CavityT >
    class CavityInitialiser : public CObjElemInitialiserBase
    {
        public:

        static_assert( SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(),
           "Requires CavityT to be a multipole class" );

        typedef typename SIXTRL_CXX_NAMESPACE::CavityTraits< CavityT
            >::real_t real_t;

        private:

        typedef SIXTRL_CXX_NAMESPACE::TypeRandomTraits< real_t >
                real_random_traits_t;

        static_assert( real_random_traits_t::has_uniform_dist,
            "Requires a uniform distribution for the real_t" );

        public:

        typedef typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits<
                         real_t >::const_argument_type const_real_arg_t;

        typedef typename real_random_traits_t::uniform_dist_t  voltage_dist_t;
        typedef typename real_random_traits_t::uniform_dist_t  frequency_dist_t;
        typedef typename real_random_traits_t::uniform_dist_t  lag_dist_t;
        typedef typename real_random_traits_t::default_prng_t  real_prng_t;
        typedef typename real_random_traits_t::default_prng_seed_t
                         real_prng_seed_t;

        typedef SIXTRL_CXX_NAMESPACE::CBufferView cbuffer_view_t;
        typedef SIXTRL_CXX_NAMESPACE::CBuffer cbuffer_t;

        SIXTRL_HOST_FN CavityInitialiser() :
            m_real_prng( real_prng_seed_t{ 2020519 } ),
            m_voltage_dist( real_t{ 0 }, real_t{ 1e7 } ),
            m_frequency_dist( real_t{ 1 }, real_t{ 1e6 } ),
            m_lag_dist( -SIXTRL_CXX_NAMESPACE::MathConst_pi< real_t >(),
                        +SIXTRL_CXX_NAMESPACE::MathConst_pi< real_t >() )
        {

        }

        SIXTRL_HOST_FN explicit CavityInitialiser(
            const_real_arg_t  min_voltage,
            const_real_arg_t  max_voltage,
            const_real_arg_t  min_frequency,
            const_real_arg_t  max_frequency,
            const_real_arg_t  min_lag,
            const_real_arg_t  max_lag ) :
            m_real_prng( real_prng_seed_t{ 2020519 } ),
            m_voltage_dist( min_voltage, max_voltage ),
            m_frequency_dist( min_frequency, max_frequency ),
            m_lag_dist( min_lag, max_lag )
        {

        }

        SIXTRL_HOST_FN CavityInitialiser(
            CavityInitialiser< CavityT > const& ) = default;

        SIXTRL_HOST_FN CavityInitialiser(
            CavityInitialiser< CavityT >&& ) = default;

        SIXTRL_HOST_FN CavityInitialiser< CavityT >& operator=(
            CavityInitialiser< CavityT > const& ) = default;

        SIXTRL_HOST_FN CavityInitialiser< CavityT >& operator=(
            CavityInitialiser< CavityT >&& ) = default;

        SIXTRL_HOST_FN virtual ~CavityInitialiser() = default;

        template< typename... Args >
        SIXTRL_HOST_FN status_t operator()(
                SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem,
                Args&&... init_parameters )
        {
            return SIXTRL_CXX_NAMESPACE::Cavity_init(
                elem, std::forward< Args >( init_parameters )... );
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        template< class OtherCavityT >
        SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
            !SIXTRL_CXX_NAMESPACE::Cavity_is_type< OtherCavityT >(),
            status_t >::type
        init_for_copy(
            SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT SIXTRL_UNUSED( elem ),
            SIXTRL_BE_ARGPTR_DEC const OtherCavityT *const SIXTRL_RESTRICT
                SIXTRL_UNUSED( orig ) ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
        }

        template< class OtherCavityT >
        SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::Cavity_is_type< OtherCavityT >(),
            status_t >::type
        init_for_copy(
            SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem,
            SIXTRL_BE_ARGPTR_DEC const OtherCavityT *const SIXTRL_RESTRICT
                SIXTRL_UNUSED( orig ) )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            return ( ( elem != SIXTRL_NULLPTR ) &&
                     ( elem == st::Cavity_preset( elem ) ) )
                ? st::ARCH_STATUS_SUCCESS : st::ARCH_STATUS_GENERAL_FAILURE;
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_INLINE SIXTRL_HOST_FN status_t randomise(
                SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem )
        {
            return this->randomise_values( elem );
        }

        SIXTRL_INLINE SIXTRL_HOST_FN status_t randomise_values(
                SIXTRL_BE_ARGPTR_DEC CavityT* SIXTRL_RESTRICT elem )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            st::arch_status_t status = st::Cavity_set_voltage(
                elem, this->random_voltage_value( this->m_real_prng ) );

            status |= st::Cavity_set_frequency(
                elem, this->random_frequency_value( this->m_real_prng ) );

            status |= st::Cavity_set_lag(
                 elem, this->random_lag_value( this->m_real_prng ) );

            return status;
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
        SIXTRL_BE_ARGPTR_DEC CavityT* create_new(
            cbuffer_view_t& SIXTRL_RESTRICT_REF view,
            SIXTRL_BE_ARGPTR_DEC CavityT const* SIXTRL_RESTRICT orig )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            SIXTRL_BE_ARGPTR_DEC CavityT* added_elem = nullptr;

            if( orig != nullptr )
            {
                added_elem = st::CBufferView_create_new_object<
                    CavityT >( view );

                if( st::Cavity_convert( added_elem, orig ) !=
                    st::ARCH_STATUS_SUCCESS )
                {
                    added_elem = SIXTRL_NULLPTR;
                }
            }

            return added_elem;
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
        SIXTRL_BE_ARGPTR_DEC CavityT* create_new(
            cbuffer_t& SIXTRL_RESTRICT_REF buffer,
            SIXTRL_BE_ARGPTR_DEC CavityT const* SIXTRL_RESTRICT orig )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            SIXTRL_BE_ARGPTR_DEC CavityT* added_elem = nullptr;

            if( orig != nullptr )
            {
                added_elem = buffer.create_new< CavityT >();

                if( st::Cavity_convert( added_elem, orig ) !=
                    st::ARCH_STATUS_SUCCESS )
                {
                    added_elem = nullptr;
                }
            }

            return added_elem;
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
        SIXTRL_BE_ARGPTR_DEC CavityT* add_new(
            cbuffer_view_t& SIXTRL_RESTRICT_REF view,
            SIXTRL_BE_ARGPTR_DEC CavityT const* SIXTRL_RESTRICT orig )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            SIXTRL_BE_ARGPTR_DEC CavityT* added_elem = nullptr;

            if( orig != nullptr )
            {
                added_elem = st::CBufferView_add_object< CavityT >( view,
                    st::Cavity_voltage( orig ),
                    st::Cavity_frequency( orig ),
                    st::Cavity_lag( orig ) );
            }

            return added_elem;
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
        SIXTRL_BE_ARGPTR_DEC CavityT* add_new(
            cbuffer_t& SIXTRL_RESTRICT_REF buffer,
            SIXTRL_BE_ARGPTR_DEC CavityT const* SIXTRL_RESTRICT orig )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            SIXTRL_BE_ARGPTR_DEC CavityT* added_elem = nullptr;

            if( orig != nullptr )
            {
                added_elem = buffer.template add< CavityT >(
                    st::Cavity_voltage( orig ),
                    st::Cavity_frequency( orig ),
                    st::Cavity_lag( orig ) );
            }

            return added_elem;
        }

        template< class PrngT >
        SIXTRL_INLINE SIXTRL_HOST_FN real_t
        random_voltage_value( PrngT& SIXTRL_RESTRICT prng )
        {
            return this->m_voltage_dist( prng );
        }

        SIXTRL_INLINE SIXTRL_HOST_FN real_t random_voltage_value()
        {
            return this->m_voltage_dist( this->m_real_prng );
        }

        template< class PrngT >
        SIXTRL_INLINE SIXTRL_HOST_FN real_t
        random_frequency_value( PrngT& SIXTRL_RESTRICT prng )
        {
            return this->m_frequency_dist( prng );
        }

        SIXTRL_INLINE SIXTRL_HOST_FN real_t random_frequency_value()
        {
            return this->m_frequency_dist( this->m_real_prng );
        }

        template< class PrngT >
        SIXTRL_INLINE SIXTRL_HOST_FN real_t
        random_lag_value( PrngT& SIXTRL_RESTRICT prng )
        {
            return this->m_lag_dist( prng );
        }

        SIXTRL_INLINE SIXTRL_HOST_FN real_t random_lag_value()
        {
            return this->m_lag_dist( this->m_real_prng );
        }

        private:

        real_prng_t      m_real_prng;
        voltage_dist_t   m_voltage_dist;
        frequency_dist_t m_frequency_dist;
        lag_dist_t       m_lag_dist;
    };

    /* ===================================================================== */

    template< class CavityT >
    struct ObjsRandomInitialiserTraits< CavityT, typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(), void >::type >
    {
        typedef SIXTRL_CXX_NAMESPACE::tests::CavityInitialiser<
                    CavityT > initialiser_t;
    };

    template< class CavityT >
    struct CObjElemInitialiserTraits< CavityT, typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >() &&
        SIXTRL_CXX_NAMESPACE::CObjElem_type_id< CavityT >() !=
            SIXTRL_CXX_NAMESPACE::ObjTypeId_illegal_type_id<
                SIXTRL_CXX_NAMESPACE::cobj_type_id_t >(), void >::type >
    {
        typedef SIXTRL_CXX_NAMESPACE::tests::CavityInitialiser< CavityT >
                initialiser_t;
    };

    /* ===================================================================== */

    template< class CavityT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Cavity_is_type< CavityT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Cavity_tests_assignment(
        SIXTRL_CXX_NAMESPACE::arch_size_t const num_elems
            = SIXTRL_CXX_NAMESPACE::arch_size_t{ 1000 } ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename st::CavityTraits< CavityT >::real_t real_t;
        typedef typename st::tests::ObjsRandomInitialiserTraits<
                    CavityT >::initialiser_t obj_init_t;

        typedef st::arch_size_t st_size_t;
        obj_init_t obj_init;

        CavityT cavity;
        st::Cavity_preset( &cavity );

        st::arch_status_t status = obj_init.randomise( &cavity );
        if( status != st::ARCH_STATUS_SUCCESS ) return status;

        for( st_size_t ii = st_size_t{ 0 } ; ii < num_elems ; ++ii )
        {
            real_t const random_voltage = obj_init.random_voltage_value();
            real_t const saved_voltage  = st::Cavity_voltage( &cavity );

            real_t const random_frequency = obj_init.random_frequency_value();
            real_t const saved_frequency  = st::Cavity_frequency( &cavity );

            real_t const random_lag = obj_init.random_lag_value();
            real_t const saved_lag  = st::Cavity_lag( &cavity );

            if( ( st::Type_comp_all_equal< real_t >(
                    saved_voltage, random_voltage ) ) &&
                ( st::Type_comp_all_equal< real_t >(
                    saved_frequency, random_frequency ) ) &&
                ( st::Type_comp_all_equal< real_t >( saved_lag, random_lag ) ) )
            {
                continue;
            }

            status = st::Cavity_set_voltage( &cavity, random_voltage );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            if( !st::Type_comp_all_equal< real_t >(
                    random_voltage, st::Cavity_voltage( &cavity ) ) )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }

            status = st::Cavity_set_frequency( &cavity, random_frequency );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            if( !st::Type_comp_all_equal< real_t >(
                    random_frequency, st::Cavity_frequency( &cavity ) ) )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }

            status = st::Cavity_set_lag( &cavity, random_lag );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            if( !st::Type_comp_all_equal< real_t >(
                    random_lag, st::Cavity_lag( &cavity ) ) )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            status = st::Cavity_set_voltage( &cavity, saved_voltage );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            if( !st::Type_comp_all_equal< real_t >(
                    saved_voltage, st::Cavity_voltage( &cavity ) ) )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }

            status = st::Cavity_set_frequency( &cavity, saved_frequency );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            if( !st::Type_comp_all_equal< real_t >(
                    saved_frequency, st::Cavity_frequency( &cavity ) ) )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }

            status = st::Cavity_set_lag( &cavity, saved_lag );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            if( !st::Type_comp_all_equal< real_t >(
                    saved_lag, st::Cavity_lag( &cavity ) ) )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }
        }

        return status;
    }



} /* namespace: tests */
} /* namespace: SIXTRL_CXX_NAMESPACE */

#endif /* C++, Host */
#endif /* SIXTRACKLIB_TESTLIB_COMMON_BEAM_ELEMENTS_CAVITY_CXX_HPP__ */
