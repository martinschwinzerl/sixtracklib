#ifndef SIXTRACKLIB_TESTLIB_COMMON_BEAM_ELEMENTS_XYSHIFT_CXX_HPP__
#define SIXTRACKLIB_TESTLIB_COMMON_BEAM_ELEMENTS_XYSHIFT_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/xy_shift.hpp"
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
    template< class XYShiftT >
    class XYShiftInitialiser : public CObjElemInitialiserBase
    {
        public:

        static_assert( SIXTRL_CXX_NAMESPACE::XYShift_is_type< XYShiftT >(),
           "Requires XYShiftT to be a multipole class" );

        typedef typename SIXTRL_CXX_NAMESPACE::XYShiftTraits< XYShiftT
            >::real_t real_t;

        private:

        typedef SIXTRL_CXX_NAMESPACE::TypeRandomTraits< real_t >
                real_random_traits_t;

        static_assert( real_random_traits_t::has_uniform_dist,
            "Requires a uniform distribution for the real_t" );

        public:

        typedef typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits<
                         real_t >::const_argument_type const_real_arg_t;

        typedef typename real_random_traits_t::uniform_dist_t  dx_dy_dist_t;
        typedef typename real_random_traits_t::default_prng_t  real_prng_t;
        typedef typename real_random_traits_t::default_prng_seed_t
                         real_prng_seed_t;

        typedef SIXTRL_CXX_NAMESPACE::CBufferView cbuffer_view_t;
        typedef SIXTRL_CXX_NAMESPACE::CBuffer cbuffer_t;

        SIXTRL_HOST_FN XYShiftInitialiser() :
            m_real_prng( real_prng_seed_t{ 2020519 } ),
            m_dx_dist( real_t{ -0.5 }, real_t{ +0.5 } ),
            m_dy_dist( real_t{ -0.5 }, real_t{ +0.5 } )
        {

        }

        SIXTRL_HOST_FN explicit XYShiftInitialiser(
            const_real_arg_t min_dx, const_real_arg_t max_dx,
            const_real_arg_t min_dy, const_real_arg_t max_dy ) :
            m_real_prng( real_prng_seed_t{ 2020519 } ),
            m_dx_dist( min_dx, max_dx ),
            m_dy_dist( min_dy, max_dy )
        {

        }

        SIXTRL_HOST_FN XYShiftInitialiser(
            XYShiftInitialiser< XYShiftT > const& ) = default;

        SIXTRL_HOST_FN XYShiftInitialiser(
            XYShiftInitialiser< XYShiftT >&& ) = default;

        SIXTRL_HOST_FN XYShiftInitialiser< XYShiftT >& operator=(
            XYShiftInitialiser< XYShiftT > const& ) = default;

        SIXTRL_HOST_FN XYShiftInitialiser< XYShiftT >& operator=(
            XYShiftInitialiser< XYShiftT >&& ) = default;

        SIXTRL_HOST_FN virtual ~XYShiftInitialiser() = default;

        template< typename... Args >
        SIXTRL_HOST_FN status_t operator()(
                SIXTRL_BE_ARGPTR_DEC XYShiftT* SIXTRL_RESTRICT elem,
                Args&&... init_parameters )
        {
            return SIXTRL_CXX_NAMESPACE::XYShift_init(
                elem, std::forward< Args >( init_parameters )... );
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        template< class OtherXYShiftT >
        SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
           !SIXTRL_CXX_NAMESPACE::XYShift_is_type< OtherXYShiftT >(),
            status_t >::type
        init_for_copy( SIXTRL_BE_ARGPTR_DEC XYShiftT* SIXTRL_RESTRICT
                SIXTRL_UNUSED( elem ),
            SIXTRL_BE_ARGPTR_DEC const OtherXYShiftT *const SIXTRL_RESTRICT
                SIXTRL_UNUSED( orig ) )
        {
            return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
        }

        template< class OtherXYShiftT >
        SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::XYShift_is_type< OtherXYShiftT >(),
            status_t >::type
        init_for_copy(
            SIXTRL_BE_ARGPTR_DEC XYShiftT* SIXTRL_RESTRICT elem,
            SIXTRL_BE_ARGPTR_DEC const OtherXYShiftT *const SIXTRL_RESTRICT
                SIXTRL_UNUSED( orig ) )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            return ( ( elem != SIXTRL_NULLPTR ) &&
                     ( elem == st::XYShift_preset( elem ) ) )
                ? st::ARCH_STATUS_SUCCESS : st::ARCH_STATUS_GENERAL_FAILURE;
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_INLINE SIXTRL_HOST_FN status_t randomise(
                SIXTRL_BE_ARGPTR_DEC XYShiftT* SIXTRL_RESTRICT elem )
        {
            return this->randomise_values( elem );
        }

        SIXTRL_INLINE SIXTRL_HOST_FN status_t randomise_values(
                SIXTRL_BE_ARGPTR_DEC XYShiftT* SIXTRL_RESTRICT elem )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            st::arch_status_t status = st::XYShift_set_dx(
                elem, this->random_dx_value( this->m_real_prng ) );

            status |= st::XYShift_set_dy(
                elem, this->random_dy_value( this->m_real_prng ) );

            return status;
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
        SIXTRL_BE_ARGPTR_DEC XYShiftT* create_new(
            cbuffer_view_t& SIXTRL_RESTRICT_REF view,
            SIXTRL_BE_ARGPTR_DEC XYShiftT const* SIXTRL_RESTRICT orig )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            SIXTRL_BE_ARGPTR_DEC XYShiftT* added_elem = nullptr;

            if( orig != nullptr )
            {
                added_elem = st::CBufferView_create_new_object<
                    XYShiftT >( view );

                if( st::XYShift_convert( added_elem, orig ) !=
                    st::ARCH_STATUS_SUCCESS )
                {
                    added_elem = SIXTRL_NULLPTR;
                }
            }

            return added_elem;
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
        SIXTRL_BE_ARGPTR_DEC XYShiftT* create_new(
            cbuffer_t& SIXTRL_RESTRICT_REF buffer,
            SIXTRL_BE_ARGPTR_DEC XYShiftT const* SIXTRL_RESTRICT orig )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            SIXTRL_BE_ARGPTR_DEC XYShiftT* added_elem = nullptr;

            if( orig != nullptr )
            {
                added_elem = buffer.create_new< XYShiftT >();

                if( st::XYShift_convert( added_elem, orig ) !=
                    st::ARCH_STATUS_SUCCESS )
                {
                    added_elem = nullptr;
                }
            }

            return added_elem;
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
        SIXTRL_BE_ARGPTR_DEC XYShiftT* add_new(
            cbuffer_view_t& SIXTRL_RESTRICT_REF view,
            SIXTRL_BE_ARGPTR_DEC XYShiftT const* SIXTRL_RESTRICT orig )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            SIXTRL_BE_ARGPTR_DEC XYShiftT* added_elem = nullptr;

            if( orig != nullptr )
            {
                added_elem = st::CBufferView_add_object< XYShiftT >( view,
                    st::XYShift_dx( orig ), st::XYShift_dy( orig ) );
            }

            return added_elem;
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
        SIXTRL_BE_ARGPTR_DEC XYShiftT* add_new(
            cbuffer_t& SIXTRL_RESTRICT_REF buffer,
            SIXTRL_BE_ARGPTR_DEC XYShiftT const* SIXTRL_RESTRICT orig )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            SIXTRL_BE_ARGPTR_DEC XYShiftT* added_elem = nullptr;

            if( orig != nullptr )
            {
                added_elem = buffer.template add< XYShiftT >(
                    st::XYShift_dx( orig ), st::XYShift_dy( orig ) );
            }

            return added_elem;
        }

        template< class PrngT >
        SIXTRL_INLINE SIXTRL_HOST_FN real_t
        random_dx_value( PrngT& SIXTRL_RESTRICT prng )
        {
            return this->m_dx_dist( prng );
        }

        SIXTRL_INLINE SIXTRL_HOST_FN real_t random_dx_value()
        {
            return this->m_dx_dist( this->m_real_prng );
        }

        template< class PrngT >
        SIXTRL_INLINE SIXTRL_HOST_FN real_t
        random_dy_value( PrngT& SIXTRL_RESTRICT prng )
        {
            return this->m_dy_dist( prng );
        }

        SIXTRL_INLINE SIXTRL_HOST_FN real_t random_dy_value()
        {
            return this->m_dy_dist( this->m_real_prng );
        }

        private:

        real_prng_t  m_real_prng;
        dx_dy_dist_t m_dx_dist;
        dx_dy_dist_t m_dy_dist;
    };

    /* ===================================================================== */

    template< class XYShiftT >
    struct ObjsRandomInitialiserTraits< XYShiftT, typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::XYShift_is_type< XYShiftT >(), void >::type >
    {
        typedef SIXTRL_CXX_NAMESPACE::tests::XYShiftInitialiser<
                    XYShiftT > initialiser_t;
    };

    template< class XYShiftT >
    struct CObjElemInitialiserTraits< XYShiftT, typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::XYShift_is_type< XYShiftT >() &&
        SIXTRL_CXX_NAMESPACE::CObjElem_type_id< XYShiftT >() !=
            SIXTRL_CXX_NAMESPACE::ObjTypeId_illegal_type_id<
                SIXTRL_CXX_NAMESPACE::cobj_type_id_t >(), void >::type >
    {
        typedef SIXTRL_CXX_NAMESPACE::tests::XYShiftInitialiser< XYShiftT >
                initialiser_t;
    };

    /* ===================================================================== */

    template< class XYShiftT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::XYShift_is_type< XYShiftT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    XYShift_tests_assignment(
        SIXTRL_CXX_NAMESPACE::arch_size_t const num_elems
            = SIXTRL_CXX_NAMESPACE::arch_size_t{ 1000 } ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename st::XYShiftTraits< XYShiftT >::real_t real_t;
        typedef typename st::tests::ObjsRandomInitialiserTraits<
                    XYShiftT >::initialiser_t obj_init_t;

        typedef st::arch_size_t st_size_t;
        obj_init_t obj_init;

        XYShiftT xy_shift;
        st::XYShift_preset( &xy_shift );

        st::arch_status_t status = obj_init.randomise( &xy_shift );
        if( status != st::ARCH_STATUS_SUCCESS ) return status;

        for( st_size_t ii = st_size_t{ 0 } ; ii < num_elems ; ++ii )
        {
            real_t const random_dx = obj_init.random_dx_value();
            real_t const saved_dx  = st::XYShift_dx( &xy_shift );

            real_t const random_dy = obj_init.random_dy_value();
            real_t const saved_dy  = st::XYShift_dy( &xy_shift );

            if( ( st::Type_comp_all_equal< real_t >( saved_dx, random_dx ) ) &&
                ( st::Type_comp_all_equal< real_t >( saved_dy, random_dy ) ) )
            {
                continue;
            }

            status = st::XYShift_set_dx( &xy_shift, random_dx );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            if( !st::Type_comp_all_equal< real_t >(
                    random_dx, st::XYShift_dx( &xy_shift ) ) )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }

            status = st::XYShift_set_dy( &xy_shift, random_dy );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            if( !st::Type_comp_all_equal< real_t >(
                    random_dy, st::XYShift_dy( &xy_shift ) ) )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }

            /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

            status = st::XYShift_set_dx( &xy_shift, saved_dx );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            if( !st::Type_comp_all_equal< real_t >(
                    saved_dx, st::XYShift_dx( &xy_shift ) ) )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }

            status = st::XYShift_set_dy( &xy_shift, saved_dy );
            if( status != st::ARCH_STATUS_SUCCESS ) break;

            if( !st::Type_comp_all_equal< real_t >(
                    saved_dy, st::XYShift_dy( &xy_shift ) ) )
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
#endif /* SIXTRACKLIB_TESTLIB_COMMON_BEAM_ELEMENTS_XYSHIFT_CXX_HPP__ */
