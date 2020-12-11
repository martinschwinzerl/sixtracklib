#ifndef SIXTRACKLIB_TESTLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_CXX_HPP__
#define SIXTRACKLIB_TESTLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/multipole.hpp"
    #include "sixtracklib/common/cobjects/cbuffer_view.hpp"
    #include "sixtracklib/common/cobjects/cbuffer.hpp"
    #include "sixtracklib/common/internal/obj_delegate.hpp"
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
    template< class MultipoleT >
    class MultipoleInitialiser : public CObjElemInitialiserBase
    {
        public:

        static_assert( SIXTRL_CXX_NAMESPACE::Multipole_is_type< MultipoleT >(),
           "Requires MultipoleT to be a multipole class" );

        typedef typename SIXTRL_CXX_NAMESPACE::MultipoleTraits< MultipoleT
                >::real_t real_t;

        typedef typename SIXTRL_CXX_NAMESPACE::MultipoleTraits< MultipoleT
                >::order_t order_t;

        private:

        typedef SIXTRL_CXX_NAMESPACE::TypeRandomTraits< real_t >
                real_random_traits_t;

        typedef SIXTRL_CXX_NAMESPACE::TypeRandomTraits< order_t >
                order_random_traits_t;

        static_assert( real_random_traits_t::has_uniform_dist,
            "Requires a uniform distribution for the real_t" );

        static_assert( order_random_traits_t::has_uniform_dist,
            "Requires a uniform distribution for the order_t" );

        public:

        typedef typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits<
                         order_t >::const_argument_type const_order_arg_t;

        typedef typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits<
                         real_t >::const_argument_type const_real_arg_t;

        typedef typename order_random_traits_t::uniform_dist_t order_dist_t;
        typedef typename order_random_traits_t::default_prng_t order_prng_t;
        typedef typename order_random_traits_t::default_prng_seed_t
                         order_prng_seed_t;

        typedef typename real_random_traits_t::uniform_dist_t  length_dist_t;
        typedef typename real_random_traits_t::uniform_dist_t  hxl_hyl_dist_t;
        typedef typename real_random_traits_t::uniform_dist_t  bal_dist_t;
        typedef typename real_random_traits_t::default_prng_t  real_prng_t;
        typedef typename real_random_traits_t::default_prng_seed_t
                         real_prng_seed_t;

        typedef SIXTRL_CXX_NAMESPACE::CBufferView cbuffer_view_t;
        typedef SIXTRL_CXX_NAMESPACE::CBuffer cbuffer_t;

        SIXTRL_HOST_FN MultipoleInitialiser() :
            m_order_prng( order_prng_seed_t{ 20205120 } ),
            m_real_prng( real_prng_seed_t{ 20205121 } ),
            m_order_dist( order_t{ 0 }, order_t{ 6 } ),
            m_length_dist( real_t{ 0 }, real_t{ 1 } ),
            m_hxl_dist( real_t{ -1e-2 }, real_t{ +1e-2 } ),
            m_hyl_dist( real_t{ -1e-2 }, real_t{ +1e-2 } ),
            m_bal_dist( real_t{ -1 }, real_t{ +1 } )
        {

        }

        SIXTRL_HOST_FN explicit MultipoleInitialiser(
            const_order_arg_t min_order, const_order_arg_t max_order,
            const_real_arg_t min_length, const_real_arg_t max_length,
            const_real_arg_t min_hxl, const_real_arg_t max_hxl,
            const_real_arg_t min_hyl, const_real_arg_t max_hyl,
            const_real_arg_t min_bal, const_real_arg_t max_bal ) :
            m_order_prng( order_prng_seed_t{ 20205120 } ),
            m_real_prng( real_prng_seed_t{ 20205121 } ),
            m_order_dist( min_order, max_order ),
            m_length_dist( min_length, max_length ),
            m_hxl_dist( min_hxl, max_hxl ),
            m_hyl_dist( min_hyl, max_hyl ),
            m_bal_dist( min_bal, max_bal )
        {

        }

        SIXTRL_HOST_FN MultipoleInitialiser(
            MultipoleInitialiser< MultipoleT > const& ) = default;

        SIXTRL_HOST_FN MultipoleInitialiser(
            MultipoleInitialiser< MultipoleT >&& ) = default;

        SIXTRL_HOST_FN MultipoleInitialiser< MultipoleT >& operator=(
            MultipoleInitialiser< MultipoleT > const& ) = default;

        SIXTRL_HOST_FN MultipoleInitialiser< MultipoleT >& operator=(
            MultipoleInitialiser< MultipoleT >&& ) = default;

        SIXTRL_HOST_FN virtual ~MultipoleInitialiser() = default;

        template< typename... Args >
        SIXTRL_HOST_FN status_t operator()(
                SIXTRL_BE_ARGPTR_DEC MultipoleT* SIXTRL_RESTRICT elem,
                Args&&... init_parameters )
        {
            return SIXTRL_CXX_NAMESPACE::Multipole_init(
                elem, std::forward< Args >( init_parameters )... );
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        template< class OtherMultipoleT >
        SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
           !SIXTRL_CXX_NAMESPACE::Multipole_is_type< OtherMultipoleT >(),
            status_t >::type
        init_for_copy(
            SIXTRL_BE_ARGPTR_DEC MultipoleT*
                SIXTRL_RESTRICT SIXTRL_UNUSED( elem ),
            SIXTRL_BE_ARGPTR_DEC const OtherMultipoleT *const
                SIXTRL_RESTRICT SIXTRL_UNUSED( orig ) ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
        }

        template< class OtherMultipoleT >
        SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
           SIXTRL_CXX_NAMESPACE::Multipole_is_type< OtherMultipoleT >(),
           status_t >::type
        init_for_copy(
            SIXTRL_BE_ARGPTR_DEC MultipoleT* SIXTRL_RESTRICT elem,
            SIXTRL_BE_ARGPTR_DEC const OtherMultipoleT *const
                SIXTRL_RESTRICT orig )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            st::arch_status_t status = st::Multipole_init( elem,
                st::Multipole_order( orig ) );

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( st::Multipole_impl_default< MultipoleT >() ) )
            {
                auto ret = this->add_ptr_field< real_t >(
                    st::Multipole_bal_length( elem ),
                    st::MultipoleTraits< MultipoleT >::real_alignment );

                status = ret.second;

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = st::Multipole_set_bal_addr( elem, ret.first );
                }
            }

            return status;
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_INLINE SIXTRL_HOST_FN status_t randomise(
                SIXTRL_BE_ARGPTR_DEC MultipoleT* SIXTRL_RESTRICT elem )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            using this_t = MultipoleInitialiser;

            st::arch_status_t status = this_t::operator()(
                elem, this->random_order_value( this->m_order_prng ) );

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( st::Multipole_impl_default< MultipoleT >() ) )
            {
                auto ret = this->add_ptr_field< real_t >(
                    st::Multipole_bal_length( elem ),
                    st::MultipoleTraits< MultipoleT >::real_alignment );

                status = ret.second;

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = st::Multipole_set_bal_addr( elem, ret.first );
                }
            }

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                status = this->randomise_values( elem );
            }

            return status;
        }

        SIXTRL_INLINE SIXTRL_HOST_FN status_t randomise_values(
                SIXTRL_BE_ARGPTR_DEC MultipoleT* SIXTRL_RESTRICT elem )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            st::arch_status_t status = st::Multipole_set_length(
                elem, this->random_length_value( this->m_real_prng ) );

            status |= st::Multipole_set_hxl(
                elem, this->random_hxl_value( this->m_real_prng ) );

            status |= st::Multipole_set_hyl(
                 elem, this->random_hyl_value( this->m_real_prng ) );

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( st::Multipole_const_bal_begin( elem ) != SIXTRL_NULLPTR ) )
            {
                auto bal_it  = st::Multipole_bal_begin( elem );
                auto bal_end = st::Multipole_bal_end( elem );

                SIXTRL_ASSERT( bal_it  != SIXTRL_NULLPTR );
                SIXTRL_ASSERT( bal_end != SIXTRL_NULLPTR );

                for( ; bal_it != bal_end ; ++bal_it )
                {
                    *bal_it = this->random_bal_value( this->m_real_prng );
                }
            }

            return status;
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
        SIXTRL_BE_ARGPTR_DEC MultipoleT* create_new(
            cbuffer_view_t& SIXTRL_RESTRICT_REF view,
            SIXTRL_BE_ARGPTR_DEC MultipoleT const* SIXTRL_RESTRICT orig )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            SIXTRL_BE_ARGPTR_DEC MultipoleT* added_elem = nullptr;

            if( orig != nullptr )
            {
                added_elem = st::CBufferView_create_new_object< MultipoleT >(
                    view, st::Multipole_order( orig ),
                    st::Multipole_bal_capacity( orig ) );

                if( st::Multipole_convert( added_elem, orig ) !=
                    st::ARCH_STATUS_SUCCESS )
                {
                    added_elem = SIXTRL_NULLPTR;
                }
            }

            return added_elem;
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
        SIXTRL_BE_ARGPTR_DEC MultipoleT* create_new(
            cbuffer_t& SIXTRL_RESTRICT_REF buffer,
            SIXTRL_BE_ARGPTR_DEC MultipoleT const* SIXTRL_RESTRICT orig )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            SIXTRL_BE_ARGPTR_DEC MultipoleT* added_elem = nullptr;

            if( orig != nullptr )
            {
                added_elem = buffer.create_new< MultipoleT >(
                    st::Multipole_order( orig ),
                    st::Multipole_bal_capacity( orig ) );

                if( st::Multipole_convert( added_elem, orig ) !=
                    st::ARCH_STATUS_SUCCESS )
                {
                    added_elem = nullptr;
                }
            }

            return added_elem;
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
        SIXTRL_BE_ARGPTR_DEC MultipoleT* add_new(
            cbuffer_view_t& SIXTRL_RESTRICT_REF view,
            SIXTRL_BE_ARGPTR_DEC MultipoleT const* SIXTRL_RESTRICT orig )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            SIXTRL_BE_ARGPTR_DEC MultipoleT* added_elem = nullptr;

            if( orig != nullptr )
            {
                added_elem = st::CBufferView_add_object< MultipoleT >( view,
                    st::Multipole_order( orig ),
                    st::Multipole_length( orig ),
                    st::Multipole_hxl( orig ), st::Multipole_hyl( orig ),
                    reinterpret_cast< std::uintptr_t >(
                        st::Multipole_const_bal_begin( orig ) ),
                    st::Multipole_bal_capacity( orig ) );
            }

            return added_elem;
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
        SIXTRL_BE_ARGPTR_DEC MultipoleT* add_new(
            cbuffer_t& SIXTRL_RESTRICT_REF buffer,
            SIXTRL_BE_ARGPTR_DEC MultipoleT const* SIXTRL_RESTRICT orig )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            SIXTRL_BE_ARGPTR_DEC MultipoleT* added_elem = nullptr;

            if( orig != nullptr )
            {
                added_elem = buffer.template add< MultipoleT >(
                    st::Multipole_order( orig ),
                    st::Multipole_length( orig ),
                    st::Multipole_hxl( orig ), st::Multipole_hyl( orig ),
                    reinterpret_cast< std::uintptr_t >(
                        st::Multipole_const_bal_begin( orig ) ),
                    st::Multipole_bal_capacity( orig ) );
            }

            return added_elem;
        }

        template< class PrngT >
        SIXTRL_INLINE SIXTRL_HOST_FN order_t
        random_order_value( PrngT& SIXTRL_RESTRICT prng )
        {
            return this->m_order_dist( prng );
        }

        SIXTRL_INLINE SIXTRL_HOST_FN order_t random_order_value()
        {
            return this->m_order_dist( this->m_order_prng );
        }

        template< class PrngT >
        SIXTRL_INLINE SIXTRL_HOST_FN real_t
        random_length_value( PrngT& SIXTRL_RESTRICT prng )
        {
            return this->m_length_dist( prng );
        }

        SIXTRL_INLINE SIXTRL_HOST_FN real_t random_length_value()
        {
            return this->m_length_dist( this->m_real_prng );
        }

        template< class PrngT >
        SIXTRL_INLINE SIXTRL_HOST_FN real_t
        random_hxl_value( PrngT& SIXTRL_RESTRICT prng )
        {
            return this->m_hxl_dist( prng );
        }

        SIXTRL_INLINE SIXTRL_HOST_FN real_t random_hxl_value()
        {
            return this->m_hxl_dist( this->m_real_prng );
        }

        template< class PrngT >
        SIXTRL_INLINE SIXTRL_HOST_FN real_t
        random_hyl_value( PrngT& SIXTRL_RESTRICT prng )
        {
            return this->m_hyl_dist( prng );
        }

        SIXTRL_INLINE SIXTRL_HOST_FN real_t random_hyl_value()
        {
            return this->m_hyl_dist( this->m_real_prng );
        }

        template< class PrngT >
        SIXTRL_INLINE SIXTRL_HOST_FN real_t
        random_bal_value( PrngT& SIXTRL_RESTRICT prng )
        {
            return this->m_bal_dist( prng );
        }

        SIXTRL_INLINE SIXTRL_HOST_FN real_t random_bal_value()
        {
            return this->m_bal_dist( this->m_real_prng );
        }

        private:

        order_prng_t    m_order_prng;
        real_prng_t     m_real_prng;

        order_dist_t    m_order_dist;
        length_dist_t   m_length_dist;
        hxl_hyl_dist_t  m_hxl_dist;
        hxl_hyl_dist_t  m_hyl_dist;
        bal_dist_t      m_bal_dist;
    };

    /* ===================================================================== */

    template< class MultipoleT >
    struct ObjsRandomInitialiserTraits< MultipoleT, typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Multipole_is_type< MultipoleT >(), void >::type >
    {
        typedef SIXTRL_CXX_NAMESPACE::tests::MultipoleInitialiser<
                    MultipoleT > initialiser_t;
    };

    template< class MultipoleT >
    struct CObjElemInitialiserTraits< MultipoleT, typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Multipole_is_type< MultipoleT >() &&
        SIXTRL_CXX_NAMESPACE::CObjElem_type_id< MultipoleT >() !=
            SIXTRL_CXX_NAMESPACE::ObjTypeId_illegal_type_id<
                SIXTRL_CXX_NAMESPACE::cobj_type_id_t >(), void >::type >
    {
        typedef SIXTRL_CXX_NAMESPACE::tests::MultipoleInitialiser< MultipoleT >
                initialiser_t;
    };

    /* ===================================================================== */

    template< class MultipoleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
       !SIXTRL_CXX_NAMESPACE::Multipole_is_type< MultipoleT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Multipole_tests_assignment(
        SIXTRL_CXX_NAMESPACE::arch_size_t const SIXTRL_UNUSED( num_elem ) =
            SIXTRL_CXX_NAMESPACE::arch_size_t{ 0 } ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class MultipoleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Multipole_is_type< MultipoleT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    Multipole_tests_assignment()
    {
        namespace st = sixtrack;
        typedef typename st::MultipoleTraits< MultipoleT >::real_t  real_t;
        typedef typename st::MultipoleTraits< MultipoleT >::order_t order_t;

        typedef st::be_address_t st_addr_t;
        typedef st::be_size_t st_size_t;

        typedef typename st::tests::ObjsRandomInitialiserTraits<
                    MultipoleT >::initialiser_t initialiser_t;

        typedef typename initialiser_t::real_prng_t         real_prng_t;
        typedef typename initialiser_t::real_prng_seed_t    real_prng_seed_t;
        typedef typename initialiser_t::bal_dist_t          bal_dist_t;

        const real_t EPS = std::numeric_limits< real_t >::epsilon();

        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        if( !st::Multipole_is_type< MultipoleT >() ) return status;

        initialiser_t initialiser;

        auto const random_length = initialiser.random_length_value();
        auto const random_hxl    = initialiser.random_hxl_value();
        auto const random_hyl    = initialiser.random_hyl_value();

        MultipoleT mp;
        status = initialiser.randomise( &mp );
        if( status != st::ARCH_STATUS_SUCCESS ) return status;

        if( st::Multipole_order( &mp ) <= order_t{ 0 } ) return status;
        if( st::Multipole_bal_length( &mp ) !=
            ( order_t{ 2 } * st::Multipole_order( &mp ) + order_t{ 2 } ) )
        {
            status |= st::ARCH_STATUS_GENERAL_FAILURE;
            return status;
        }

        if( st::Multipole_bal_capacity( &mp ) <
            st::Multipole_bal_length( &mp ) )
        {
            status |= st::ARCH_STATUS_GENERAL_FAILURE;
            return status;
        }

        if( st::Multipole_bal_addr( &mp ) == st_addr_t{ 0 } )
        {
            status |= st::ARCH_STATUS_GENERAL_FAILURE;
            return status;
        }

        if( st::Multipole_const_bal_begin( &mp ) == SIXTRL_NULLPTR )
        {
            status |= st::ARCH_STATUS_GENERAL_FAILURE;
            return status;
        }

        if( st::Multipole_const_bal_end( &mp ) == SIXTRL_NULLPTR )
        {
            status |= st::ARCH_STATUS_GENERAL_FAILURE;
            return status;
        }

        if( std::distance( st::Multipole_const_bal_begin( &mp ),
                st::Multipole_const_bal_end( &mp ) ) != static_cast<
                    std::ptrdiff_t >( st::Multipole_bal_length( &mp ) ) )
        {
            status |= st::ARCH_STATUS_GENERAL_FAILURE;
            return status;
        }

        if( st::Type_comp_all_not_equal< real_t >(
                st::Multipole_length( &mp ), random_length ) )
        {
            real_t const saved_length = st::Multipole_length( &mp );

            if( st::ARCH_STATUS_SUCCESS != st::Multipole_set_length(
                            &mp, random_length ) )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                return status;
            }

            if( !st::Type_comp_all_equal< real_t >(
                    st::Multipole_length( &mp ), random_length ) )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                return status;
            }

            if( st::ARCH_STATUS_SUCCESS != st::Multipole_set_length(
                    &mp, saved_length ) )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                return status;
            }

            if( !st::Type_comp_all_equal< real_t >(
                    st::Multipole_length( &mp ), saved_length ) )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                return status;
            }
        }

        if( st::Type_comp_all_not_equal< real_t >(
                st::Multipole_hxl( &mp ), random_hxl ) )
        {
            real_t const saved_hxl = st::Multipole_hxl( &mp );

            if( st::ARCH_STATUS_SUCCESS != st::Multipole_set_hxl(
                            &mp, random_hxl ) )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                return status;
            }

            if( !st::Type_comp_all_equal< real_t >(
                            st::Multipole_hxl( &mp ), random_hxl ) )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                return status;
            }

            if( st::ARCH_STATUS_SUCCESS != st::Multipole_set_hxl(
                            &mp, saved_hxl ) )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                return status;
            }

            if( !st::Type_comp_all_equal< real_t >(
                            st::Multipole_hxl( &mp ), saved_hxl ) )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                return status;
            }
        }

        if( st::Type_comp_all_not_equal< real_t >(
                st::Multipole_hyl( &mp ), random_hyl ) )
        {
            real_t const saved_hyl = st::Multipole_hyl( &mp );

            if( st::ARCH_STATUS_SUCCESS != st::Multipole_set_hyl(
                            &mp, random_hyl ) )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                return status;
            }

            if( !st::Type_comp_all_equal< real_t >(
                        st::Multipole_hyl( &mp ), random_hyl ) )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                return status;
            }

            if( st::ARCH_STATUS_SUCCESS != st::Multipole_set_hyl(
                            &mp, saved_hyl ) )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                return status;
            }

            if( !st::Type_comp_all_equal< real_t >(
                            st::Multipole_hyl( &mp ), saved_hyl ) )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                return status;
            }
        }

        real_prng_t real_prng( real_prng_seed_t{ 20200515 } );
        bal_dist_t cmp_values_dist( real_t{ -0.1 }, real_t{ 0.1 } );

        st_size_t const nn = st::Multipole_bal_length( &mp );
        std::vector< real_t > cmp_values( nn );
        std::generate( cmp_values.begin(), cmp_values.end(),
            [&cmp_values_dist, &real_prng]() -> real_t
            { return cmp_values_dist( real_prng ); } );

        for( st_size_t ii = st_size_t{ 0 } ; ii < nn ; ++ii )
        {
            status = st::Multipole_set_bal_value( &mp, ii, cmp_values[ ii ] );
            if( status != st::ARCH_STATUS_SUCCESS ) break;
        }

        if( !std::equal( cmp_values.begin(), cmp_values.end(),
                         st::Multipole_const_bal_begin( &mp ) ) )
        {
            status |= st::ARCH_STATUS_GENERAL_FAILURE;
            return status;
        }

        real_t cmp_factorial = real_t{ 1 };

        for( st_size_t ii = st_size_t{ 0 } ; ii < nn ; ii += 2u )
        {
            st_size_t jj = ii >> 1;
            if( jj != st_size_t{ 0 } ) cmp_factorial *= jj;

            if( !st::Type_comp_all_are_close< real_t >(
                    cmp_values[ ii ], st::Multipole_bal( &mp, ii ), EPS, EPS ) )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }

            if( !st::Type_comp_all_are_close< real_t >( cmp_values[ ii + 1u ],
                    st::Multipole_bal( &mp, ii + 1u ), EPS, EPS ) )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }

            if( !st::Type_comp_all_are_close< real_t >( cmp_factorial *
                    cmp_values[ ii ], st::Multipole_knl( &mp, jj ), EPS, EPS ) )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }

            if( !st::Type_comp_all_are_close< real_t >( cmp_factorial *
                    cmp_values[ ii + 1u ], st::Multipole_ksl(
                        &mp, jj ), EPS, EPS ) )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }
        }

        if( status != st::ARCH_STATUS_SUCCESS ) return status;

        status = st::Multipole_set_all_bal_values( &mp, real_t{ 0 } );
        if( status != st::ARCH_STATUS_SUCCESS ) return status;

        cmp_factorial = real_t{ 1 };

        for( st_size_t ii = st_size_t{ 0 } ; ii < nn ; ii += 2u )
        {
            st_size_t jj = ii >> 1;
            if( jj != st_size_t{ 0 } ) cmp_factorial *= jj;

            if( !st::Type_comp_all_equal< real_t >(
                st::Multipole_bal( &mp, ii ), real_t{ 0 } ) )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }

            status = st::Multipole_set_knl_value( &mp, jj, cmp_values[ ii ] );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            if( !st::Type_comp_all_are_close< real_t >( cmp_values[ ii ],
                    st::Multipole_knl( &mp, jj ), EPS, EPS ) )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }

            if( !st::Type_comp_all_are_close< real_t >( cmp_values[ ii ] /
                    cmp_factorial, st::Multipole_bal( &mp, ii ), EPS, EPS ) )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }

            if( !st::Type_comp_all_equal< real_t >(
                st::Multipole_bal( &mp, ii + 1u ), real_t{ 0 } ) )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }

            status = st::Multipole_set_ksl_value( &mp, jj,
                          cmp_values[ ii + 1u ] );

            if( status != st::ARCH_STATUS_SUCCESS ) break;

            if( !st::Type_comp_all_are_close< real_t >( cmp_values[ ii + 1u ],
                    st::Multipole_ksl( &mp, jj ), EPS, EPS ) )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }

            if( !st::Type_comp_all_are_close< real_t >( cmp_values[ ii + 1u ] /
                cmp_factorial, st::Multipole_bal( &mp, ii + 1u ), EPS, EPS ) )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }
        }

        if( status != st::ARCH_STATUS_SUCCESS ) return status;
        status = st::Multipole_set_all_knl_values( &mp, real_t{ 42 } );

        if( st::ARCH_STATUS_SUCCESS != status )
        {
            status |= st::ARCH_STATUS_GENERAL_FAILURE;
            return status;
        }

        status = st::Multipole_set_all_ksl_values( &mp, real_t{ 137 } );
        if( st::ARCH_STATUS_SUCCESS != status )
        {
            status |= st::ARCH_STATUS_GENERAL_FAILURE;
            return status;
        }

        for( st_size_t ii = st_size_t{ 0 } ; ii < nn ; ii += 2u )
        {
            st_size_t jj = ii >> 1;
            if( jj != st_size_t{ 0 } ) cmp_factorial *= jj;

            if( !st::Type_comp_all_are_close< real_t >( real_t{ 42 },
                 st::Multipole_knl( &mp, jj ), EPS, EPS ) )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }

            if( !st::Type_comp_all_are_close< real_t >( real_t{ 42 } /
                 st::Math_factorial< st_size_t, real_t >( jj ),
                 st::Multipole_bal( &mp, ii ), EPS, EPS ) )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }

            if( !st::Type_comp_all_are_close< real_t >( real_t{ 137 },
                 st::Multipole_ksl( &mp, jj ), EPS, EPS ) )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }

            if( !st::Type_comp_all_are_close< real_t >( real_t{ 137 } /
                 st::Math_factorial< st_size_t, real_t >( jj ),
                 st::Multipole_bal( &mp, ii + 1u ), EPS, EPS ) )
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
#endif /* SIXTRACKLIB_TESTLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_CXX_HPP__ */
