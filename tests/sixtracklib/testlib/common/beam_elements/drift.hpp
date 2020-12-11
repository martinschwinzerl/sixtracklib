#ifndef SIXTRACKLIB_TESTLIB_COMMON_BEAM_ELEMENTS_DRIFT_CXX_HPP__
#define SIXTRACKLIB_TESTLIB_COMMON_BEAM_ELEMENTS_DRIFT_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/drift.hpp"
    #include "sixtracklib/common/cobjects/cbuffer_view.hpp"
    #include "sixtracklib/common/cobjects/cbuffer.hpp"
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
    template< class DriftT >
    class DriftInitialiser : public CObjElemInitialiserBase
    {
        public:

        static_assert( SIXTRL_CXX_NAMESPACE::Drift_is_type< DriftT >(),
            "DriftT is required to be a drift beam-element type" );

        typedef typename SIXTRL_CXX_NAMESPACE::DriftTraits<
                         DriftT >::real_t real_t;

        typedef SIXTRL_CXX_NAMESPACE::be_drift_track_type_t track_type_t;

        private:

        typedef SIXTRL_CXX_NAMESPACE::TypeRandomTraits< real_t >
                real_random_traits_t;

        static_assert( real_random_traits_t::has_uniform_dist,
            "Requires a uniform distribution for the real_t" );

        typedef SIXTRL_CXX_NAMESPACE::TypeRandomTraits< track_type_t >
                track_type_random_traits_t;

        public:

        typedef typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits<
                         real_t >::const_argument_type const_real_arg_t;

        typedef typename real_random_traits_t::uniform_dist_t  length_dist_t;
        typedef typename real_random_traits_t::default_prng_t  real_prng_t;
        typedef typename real_random_traits_t::default_prng_seed_t
                         real_prng_seed_t;

        typedef typename track_type_random_traits_t::uniform_dist_t
                track_type_dist_t;

        typedef typename track_type_random_traits_t::default_prng_t
                track_type_prng_t;

        typedef typename track_type_random_traits_t::default_prng_seed_t
                track_type_prng_seed_t;

        typedef SIXTRL_CXX_NAMESPACE::CBufferView cbuffer_view_t;
        typedef SIXTRL_CXX_NAMESPACE::CBuffer cbuffer_t;

        SIXTRL_HOST_FN DriftInitialiser() :
            m_prng( real_prng_seed_t{ 202005130 } ),
            m_track_type_prng( track_type_prng_seed_t{ 202005131 } ),
            m_length_dist( real_t{ 0 }, real_t{ 1 } ),
            m_track_type_dist(
                SIXTRL_CXX_NAMESPACE::BE_DRIFT_TRACK_TYPE_SIMPLE,
                SIXTRL_CXX_NAMESPACE::BE_DRIFT_TRACK_TYPE_EXACT )
        {

        }

        SIXTRL_HOST_FN explicit DriftInitialiser(
            const_real_arg_t min_length, const_real_arg_t max_length ) :
            m_prng( real_prng_seed_t{ 202005130 } ),
            m_track_type_prng( track_type_prng_seed_t{ 202005131 } ),
            m_length_dist( min_length, max_length ),
            m_track_type_dist(
                SIXTRL_CXX_NAMESPACE::BE_DRIFT_TRACK_TYPE_SIMPLE,
                SIXTRL_CXX_NAMESPACE::BE_DRIFT_TRACK_TYPE_EXACT )
        {

        }

        SIXTRL_HOST_FN DriftInitialiser(
            DriftInitialiser< DriftT > const& ) = default;

        SIXTRL_HOST_FN DriftInitialiser(
            DriftInitialiser< DriftT >&& ) = default;

        SIXTRL_HOST_FN DriftInitialiser< DriftT >& operator=(
            DriftInitialiser< DriftT > const& ) = default;

        SIXTRL_HOST_FN DriftInitialiser< DriftT >& operator=(
            DriftInitialiser< DriftT >&& ) = default;

        SIXTRL_HOST_FN virtual ~DriftInitialiser() = default;

        template< typename... Args >
        SIXTRL_HOST_FN status_t operator()(
                SIXTRL_BE_ARGPTR_DEC DriftT* SIXTRL_RESTRICT elem,
                Args&&... init_parameters )
        {
            return SIXTRL_CXX_NAMESPACE::Drift_init(
                elem, std::forward< Args >( init_parameters )... );
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        template< class OtherDriftT >
        SIXTRL_HOST_FN typename std::enable_if<
           !SIXTRL_CXX_NAMESPACE::Drift_is_type< OtherDriftT >(),
            status_t >::type
        init_for_copy(
            SIXTRL_BE_ARGPTR_DEC DriftT* SIXTRL_RESTRICT SIXTRL_UNUSED( elem ),
            SIXTRL_BE_ARGPTR_DEC const OtherDriftT *const SIXTRL_RESTRICT
                SIXTRL_UNUSED( orig ) )
        {
            return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
        }


        template< class OtherDriftT >
        SIXTRL_HOST_FN typename std::enable_if<
           SIXTRL_CXX_NAMESPACE::Drift_is_type< OtherDriftT >(),
           status_t >::type
        init_for_copy(
            SIXTRL_BE_ARGPTR_DEC DriftT* SIXTRL_RESTRICT elem,
            SIXTRL_BE_ARGPTR_DEC const OtherDriftT *const
                SIXTRL_RESTRICT SIXTRL_UNUSED( orig ) )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            return ( ( elem != SIXTRL_NULLPTR ) &&
                     ( elem == st::Drift_preset( elem ) ) )
                ? st::ARCH_STATUS_SUCCESS : st::ARCH_STATUS_GENERAL_FAILURE;
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN status_t randomise_values(
            SIXTRL_BE_ARGPTR_DEC DriftT* SIXTRL_RESTRICT elem )
        {
            return SIXTRL_CXX_NAMESPACE::Drift_set_length(
                elem, this->random_length_value( this->m_prng ) );
        }

        SIXTRL_HOST_FN status_t randomise(
            SIXTRL_BE_ARGPTR_DEC DriftT* SIXTRL_RESTRICT elem )
        {
            return this->randomise_values( elem );
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
        SIXTRL_BE_ARGPTR_DEC DriftT* create_new(
            SIXTRL_BUFFER_ARGPTR_DEC cbuffer_view_t& SIXTRL_RESTRICT_REF view,
            SIXTRL_BE_ARGPTR_DEC DriftT const* SIXTRL_RESTRICT orig )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            SIXTRL_BE_ARGPTR_DEC DriftT* added_elem = nullptr;

            if( orig != SIXTRL_NULLPTR )
            {
                added_elem = st::CBufferView_create_new_object< DriftT >( view );

                if( st::Drift_convert( added_elem, orig ) !=
                    st::ARCH_STATUS_SUCCESS )
                {
                    added_elem = SIXTRL_NULLPTR;
                }
            }

            return added_elem;
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
        SIXTRL_BE_ARGPTR_DEC DriftT* add_new(
            SIXTRL_BUFFER_ARGPTR_DEC cbuffer_view_t& SIXTRL_RESTRICT_REF view,
            SIXTRL_BE_ARGPTR_DEC DriftT const* SIXTRL_RESTRICT orig )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            SIXTRL_BE_ARGPTR_DEC DriftT* added_elem = nullptr;

            if( orig != nullptr )
            {
                added_elem = st::CBufferView_add_object< DriftT >(
                    view, st::Drift_length( orig ) );
            }

            return added_elem;
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
        SIXTRL_BE_ARGPTR_DEC DriftT* create_new(
            SIXTRL_BUFFER_ARGPTR_DEC cbuffer_t& SIXTRL_RESTRICT_REF buffer,
            SIXTRL_BE_ARGPTR_DEC DriftT const* SIXTRL_RESTRICT orig )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            SIXTRL_BE_ARGPTR_DEC DriftT* added_elem = nullptr;

            if( orig != SIXTRL_NULLPTR )
            {
                added_elem = buffer.create_new< DriftT >();

                if( st::Drift_convert( added_elem, orig ) !=
                    st::ARCH_STATUS_SUCCESS )
                {
                    added_elem = SIXTRL_NULLPTR;
                }
            }

            return added_elem;
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
        SIXTRL_BE_ARGPTR_DEC DriftT* add_new(
            SIXTRL_BUFFER_ARGPTR_DEC cbuffer_t& SIXTRL_RESTRICT_REF buffer,
            SIXTRL_BE_ARGPTR_DEC DriftT const* SIXTRL_RESTRICT orig )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            SIXTRL_BE_ARGPTR_DEC DriftT* added_elem = nullptr;

            if( orig != nullptr )
            {
                added_elem = buffer.add< DriftT >( st::Drift_length( orig ) );
            }

            return added_elem;
        }

        template< class PrngT >
        SIXTRL_INLINE SIXTRL_HOST_FN real_t
        random_length_value( PrngT& SIXTRL_RESTRICT prng )
        {
            return this->m_length_dist( prng );
        }

        SIXTRL_INLINE SIXTRL_HOST_FN real_t random_length_value()
        {
            return this->m_length_dist( this->m_prng );
        }

        template< class PrngT >
        SIXTRL_INLINE SIXTRL_HOST_FN track_type_t
        random_track_type_value( PrngT& SIXTRL_RESTRICT prng )
        {
            return this->m_track_type_dist( prng );
        }

        SIXTRL_INLINE SIXTRL_HOST_FN track_type_t random_track_type_value()
        {
            return this->m_track_type_dist( this->m_track_type_prng );
        }

        private:

        real_prng_t         m_prng;
        track_type_prng_t   m_track_type_prng;
        length_dist_t       m_length_dist;
        track_type_dist_t   m_track_type_dist;
    };

    /* ===================================================================== */

    template< class DriftT >
    struct ObjsRandomInitialiserTraits< DriftT, typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Drift_is_type< DriftT >(), void >::type >
    {
        typedef SIXTRL_CXX_NAMESPACE::tests::DriftInitialiser< DriftT >
                initialiser_t;
    };

    template< class DriftT >
    struct CObjElemInitialiserTraits< DriftT, typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Drift_is_type< DriftT >() &&
        SIXTRL_CXX_NAMESPACE::CObjElem_type_id< DriftT >() !=
            SIXTRL_CXX_NAMESPACE::ObjTypeId_illegal_type_id<
                SIXTRL_CXX_NAMESPACE::cobj_type_id_t >(), void >::type >
    {
        typedef SIXTRL_CXX_NAMESPACE::tests::DriftInitialiser< DriftT >
                initialiser_t;
    };

    /* ===================================================================== */

    template< class DriftT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::Drift_is_type< DriftT >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Drift_tests_assignment(
        SIXTRL_CXX_NAMESPACE::arch_size_t const SIXTRL_UNUSED( num_elems )
            = SIXTRL_CXX_NAMESPACE::arch_size_t{ 0 } ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class DriftT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Drift_is_type< DriftT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Drift_tests_assignment(
        SIXTRL_CXX_NAMESPACE::arch_size_t const num_elems
            = SIXTRL_CXX_NAMESPACE::arch_size_t{ 1000 } ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename st::DriftTraits< DriftT >::real_t real_t;
        typedef st::be_drift_track_type_t track_type_t;
        typedef typename st::tests::ObjsRandomInitialiserTraits<
                    DriftT >::initialiser_t obj_init_t;

        typedef st::arch_size_t st_size_t;
        obj_init_t obj_init;

        DriftT drift;
        st::Drift_preset( &drift );

        st::arch_status_t status = obj_init.randomise( &drift );
        if( status != st::ARCH_STATUS_SUCCESS ) return status;

        for( st_size_t ii = st_size_t{ 0 } ; ii < num_elems ; ++ii )
        {
            real_t const length = obj_init.random_length_value();
            real_t const saved_length = st::Drift_length( &drift );

            track_type_t const track_type =
                obj_init.random_track_type_value();

            track_type_t const saved_track_type =
                st::Drift_track_type( &drift );

            if( ( st::Type_comp_all_not_equal< real_t >(
                    saved_length, length ) ) ||
                ( st::Type_comp_all_not_equal< track_type_t >(
                    saved_track_type, track_type ) ) )
            {
                status = st::Drift_set_length( &drift, length );
                if( status != st::ARCH_STATUS_SUCCESS ) break;

                if( !st::Type_comp_all_equal< real_t >(
                        length, st::Drift_length( &drift ) ) )
                {
                    status |= st::ARCH_STATUS_GENERAL_FAILURE;
                    break;
                }

                status = st::Drift_set_track_type( &drift, track_type );
                if( status != st::ARCH_STATUS_SUCCESS ) break;

                if( !st::Type_comp_all_equal< track_type_t >(
                        track_type, st::Drift_track_type( &drift ) ) )
                {
                    status |= st::ARCH_STATUS_GENERAL_FAILURE;
                    break;
                }

                /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

                status = st::Drift_set_length( &drift, saved_length );
                if( status != st::ARCH_STATUS_SUCCESS ) break;

                if( !st::Type_comp_all_equal< real_t >(
                        saved_length, st::Drift_length( &drift ) ) )
                {
                    status |= st::ARCH_STATUS_GENERAL_FAILURE;
                    break;
                }

                status = st::Drift_set_track_type( &drift, saved_track_type );
                if( status != st::ARCH_STATUS_SUCCESS ) break;

                if( !st::Type_comp_all_equal< track_type_t >(
                        saved_track_type, st::Drift_track_type( &drift ) ) )
                {
                    status |= st::ARCH_STATUS_GENERAL_FAILURE;
                    break;
                }
            }
        }

        return status;
    }


} /* namespace: tests */
} /* namespace: SIXTRL_CXX_NAMESPACE */


#endif /* C++, Host */

#endif /* SIXTRACKLIB_TESTLIB_COMMON_BEAM_ELEMENTS_DRIFT_CXX_HPP__ */
