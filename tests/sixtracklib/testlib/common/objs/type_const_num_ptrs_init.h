#ifndef SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_TYPE_CONST_NUM_PTRS_INIT_H__
#define SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_TYPE_CONST_NUM_PTRS_INIT_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/testlib/common/objs/definitions.h"
    #include "sixtracklib/testlib/common/objs/objs_traits.hpp"
    #include "sixtracklib/testlib/common/objs/objs_initialiser_base.hpp"
    #include "sixtracklib/testlib/common/objs/type_const_num_ptrs.h"
    #include "sixtracklib/testlib/common/objs/type_const_num_ptrs_api.h"
    #include "sixtracklib/testlib/common/cobjects/cobj_elem_traits.hpp"
    #include "sixtracklib/testlib/common/cobjects/cobjects_initialiser_base.hpp"
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/cobjects/cbuffer_view.hpp"
    #include "sixtracklib/common/cobjects/cbuffer.hpp"
    #include "sixtracklib/common/internal/compiler_attributes.h"
    #include "sixtracklib/common/internal/obj_store_traits.hpp"
    #include "sixtracklib/common/internal/type_random_traits.hpp"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    /* --------------------------------------------------------------------- */
    /* init API: */

    template< class TypeT >
    SIXTRL_STATIC constexpr SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type< TypeT >(),
         SIXTRL_BUFFER_DATAPTR_DEC TypeT* >::type
    TypeConstNumPtrs_preset( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT /*obj*/ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_NULLPTR;
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type< TypeT >() &&
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_default< TypeT >(),
        SIXTRL_BUFFER_DATAPTR_DEC TypeT* >::type
    TypeConstNumPtrs_preset( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        if( obj != SIXTRL_NULLPTR )
        {
            st::arch_status_t status =
                st::tests::TypeConstNumPtrs_set_default_a( obj );
            status |= st::tests::TypeConstNumPtrs_set_default_num_b_values( obj );
            status |= st::tests::TypeConstNumPtrs_set_default_num_c_values( obj );
            status |= st::tests::TypeConstNumPtrs_set_default_b_addr( obj );
            status |= st::tests::TypeConstNumPtrs_set_default_c_addr( obj );

            SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
            ( void )status;
        }

        return obj;
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    template< class TypeT >
    SIXTRL_STATIC constexpr SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >(), SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_init(
        SIXTRL_BUFFER_ARGPTR_DEC TypeT* SIXTRL_RESTRICT /*obj*/,
        SIXTRL_CXX_NAMESPACE::tests::objs_size_t const /*num_b_values*/,
        SIXTRL_CXX_NAMESPACE::tests::objs_size_t const /*num_c_values*/
    ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class TypeT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >() &&
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_default< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_init(
        SIXTRL_BUFFER_ARGPTR_DEC TypeT* SIXTRL_RESTRICT obj,
        SIXTRL_CXX_NAMESPACE::tests::objs_size_t const num_b_values,
        SIXTRL_CXX_NAMESPACE::tests::objs_size_t const num_c_values
    ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_ASSERT( obj != SIXTRL_NULLPTR );
        st::arch_status_t status =
            st::tests::TypeConstNumPtrs_set_default_a( obj );

        status |= st::tests::TypeConstNumPtrs_set_num_b_values(
            obj, num_b_values );

        status |= st::tests::TypeConstNumPtrs_set_default_b_addr( obj );

        status |= st::tests::TypeConstNumPtrs_set_num_c_values(
            obj, num_c_values );

        status |= st::tests::TypeConstNumPtrs_set_default_c_addr( obj );

        return status;
    }

    /*  -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

    template< class TypeT, typename RealArg  >
    SIXTRL_STATIC constexpr SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >(), SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_init_detailed(
        SIXTRL_BUFFER_ARGPTR_DEC TypeT* SIXTRL_RESTRICT /*obj*/,
        RealArg /*a_value*/,
        SIXTRL_CXX_NAMESPACE::tests::objs_size_t const /*num_b_values*/,
        SIXTRL_CXX_NAMESPACE::tests::objs_size_t const /*num_c_values*/,
        SIXTRL_CXX_NAMESPACE::tests::objs_addr_t const /*b_addr*/,
        SIXTRL_CXX_NAMESPACE::tests::objs_addr_t const /*c_addr */
    ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class TypeT, typename RealArg  >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >() &&
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_default< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_init_detailed(
        SIXTRL_BUFFER_ARGPTR_DEC TypeT* SIXTRL_RESTRICT obj, RealArg a_value,
        SIXTRL_CXX_NAMESPACE::tests::objs_size_t const num_b_values,
        SIXTRL_CXX_NAMESPACE::tests::objs_size_t const num_c_values,
        SIXTRL_CXX_NAMESPACE::tests::objs_addr_t const b_addr,
        SIXTRL_CXX_NAMESPACE::tests::objs_addr_t const c_addr ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        st::arch_status_t status =
            st::tests::TypeConstNumPtrs_set_a( obj, a_value );

        status |= st::tests::TypeConstNumPtrs_set_num_b_values(
            obj, num_b_values );

        status |= st::tests::TypeConstNumPtrs_set_b_addr( obj, b_addr );

        status |= st::tests::TypeConstNumPtrs_set_num_c_values(
            obj, num_c_values );

        status |= st::tests::TypeConstNumPtrs_set_c_addr( obj, c_addr );

        return status;
    }

    /*  -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

    template< class TypeT, typename RealArg  >
    SIXTRL_STATIC constexpr SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >(), SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_init(
        SIXTRL_BUFFER_ARGPTR_DEC TypeT* SIXTRL_RESTRICT /*obj*/,
        RealArg /*a_value*/,
        SIXTRL_CXX_NAMESPACE::tests::objs_size_t const /*num_b_values*/,
        SIXTRL_CXX_NAMESPACE::tests::objs_size_t const /*num_c_values*/,
        SIXTRL_CXX_NAMESPACE::tests::objs_addr_t const /*b_addr*/,
        SIXTRL_CXX_NAMESPACE::tests::objs_addr_t const /*c_addr */
    ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class TypeT, typename RealArg  >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
            TypeT >() &&
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_impl_default< TypeT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    TypeConstNumPtrs_init(
        SIXTRL_BUFFER_ARGPTR_DEC TypeT* SIXTRL_RESTRICT obj,
        RealArg a_value,
        SIXTRL_CXX_NAMESPACE::tests::objs_size_t const num_b_values,
        SIXTRL_CXX_NAMESPACE::tests::objs_size_t const num_c_values,
        SIXTRL_CXX_NAMESPACE::tests::objs_addr_t const b_addr,
        SIXTRL_CXX_NAMESPACE::tests::objs_addr_t const c_addr
    ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_init_detailed(
            obj, a_value, num_b_values, num_c_values, b_addr, c_addr );
    }

} /* namespace: tests */

template< class TypeT, store_backend_t StoreBeT >
struct ObjDataInitialiser< TypeT, StoreBeT, typename std::enable_if<
    SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
        TypeT >(), void >::type >
{
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN void preset(
        SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj )
    {
        SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_preset( obj );
    }

    template< typename... Args >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t init(
        SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj,
        Args&&... args )
    {
        return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_init(
            obj, std::forward< Args >( args )... );
    }
};

namespace tests
{
    template< class TypeConstNumPtrsT >
    class TypeConstNumPtrsInitialiser : public CObjElemInitialiserBase
    {
        public:

        static_assert( SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
                TypeConstNumPtrsT >(),
            "TypeConstNumPtrsT is required to be a const-num-ptrs test type" );

        typedef SIXTRL_CXX_NAMESPACE::tests::objs_size_t size_type;

        typedef typename SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsTraits<
                            TypeConstNumPtrsT >::real_t real_t;

        private:

        typedef SIXTRL_CXX_NAMESPACE::TypeRandomTraits< real_t >
                real_random_traits_t;

        typedef SIXTRL_CXX_NAMESPACE::TypeRandomTraits< size_type >
                size_type_random_traits_t;

        static_assert( real_random_traits_t::has_uniform_dist,
            "Requires a uniform distribution for the real_t" );

        static_assert( size_type_random_traits_t::has_uniform_dist,
            "Requires a uniform distribution for the size_type" );

        public:

        typedef typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits<
                         real_t >::const_argument_type const_real_arg_t;

        typedef typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits<
                         size_type >::const_argument_type const_size_arg_t;

        typedef typename real_random_traits_t::uniform_dist_t real_dist_t;
        typedef typename real_random_traits_t::default_prng_t real_prng_t;
        typedef typename real_random_traits_t::default_prng_seed_t
                         real_prng_seed_t;

        typedef typename size_type_random_traits_t::uniform_dist_t size_dist_t;
        typedef typename size_type_random_traits_t::default_prng_t size_prng_t;
        typedef typename size_type_random_traits_t::default_prng_seed_t
                         size_type_prng_seed_t;

        static constexpr real_t    MIN_RANDOM_A = real_t{   -12 };
        static constexpr real_t    MAX_RANDOM_A = real_t{   +12 };

        static constexpr size_type MIN_RANDOM_NUM_B_VALUES = size_type{   0 };
        static constexpr size_type MAX_RANDOM_NUM_B_VALUES = size_type{ 100 };

        static constexpr real_t    MIN_RANDOM_B = real_t{ -100 };
        static constexpr real_t    MAX_RANDOM_B = real_t{ +100 };

        static constexpr size_type MIN_RANDOM_NUM_C_VALUES = size_type{  16 };
        static constexpr size_type MAX_RANDOM_NUM_C_VALUES = size_type{  64 };

        static constexpr real_t    MIN_RANDOM_C = real_t{ -42 };
        static constexpr real_t    MAX_RANDOM_C = real_t{ +42 };

        SIXTRL_HOST_FN explicit TypeConstNumPtrsInitialiser(
            const_size_arg_t  min_num_b_values = MIN_RANDOM_NUM_B_VALUES,
            const_size_arg_t  max_num_b_values = MAX_RANDOM_NUM_B_VALUES,
            const_size_arg_t  min_num_c_values = MIN_RANDOM_NUM_C_VALUES,
            const_size_arg_t  max_num_c_values = MAX_RANDOM_NUM_C_VALUES,
            const_real_arg_t  min_a = MIN_RANDOM_A,
            const_real_arg_t  max_a = MAX_RANDOM_A,
            const_real_arg_t  min_b = MIN_RANDOM_B,
            const_real_arg_t  max_b = MAX_RANDOM_B,
            const_real_arg_t  min_c = MIN_RANDOM_C,
            const_real_arg_t  max_c = MAX_RANDOM_C ) :
            m_real_prng( real_prng_seed_t{ 202005130 } ),
            m_size_prng( size_type_prng_seed_t{ 202005131 } ),
            m_num_b_values_dist( min_num_b_values, max_num_b_values ),
            m_num_c_values_dist( min_num_c_values, max_num_c_values ),
            m_a_dist( min_a, max_a ), m_b_dist( min_b, max_b ),
            m_c_dist( min_c, max_c )
        {

        }

        SIXTRL_HOST_FN TypeConstNumPtrsInitialiser(
            TypeConstNumPtrsInitialiser< TypeConstNumPtrsT > const& ) = default;

        SIXTRL_HOST_FN TypeConstNumPtrsInitialiser(
            TypeConstNumPtrsInitialiser< TypeConstNumPtrsT >&& ) = default;

        SIXTRL_HOST_FN TypeConstNumPtrsInitialiser< TypeConstNumPtrsT >&
        operator=( TypeConstNumPtrsInitialiser<
            TypeConstNumPtrsT > const& ) = default;

        SIXTRL_HOST_FN TypeConstNumPtrsInitialiser< TypeConstNumPtrsT >&
        operator=( TypeConstNumPtrsInitialiser<
            TypeConstNumPtrsT >&& ) = default;

        SIXTRL_HOST_FN virtual ~TypeConstNumPtrsInitialiser() = default;

        template< typename... Args >
        SIXTRL_HOST_FN status_t operator()(
                SIXTRL_BUFFER_DATAPTR_DEC TypeConstNumPtrsT* SIXTRL_RESTRICT elem,
                Args&&... init_parameters )
        {
            return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_init(
                elem, std::forward< Args >( init_parameters )... );
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        template< class OtherT >
        SIXTRL_HOST_FN typename std::enable_if<
            !SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type< OtherT >(),
            status_t >::type
        init_for_copy(
            SIXTRL_BUFFER_DATAPTR_DEC TypeConstNumPtrsT*
                SIXTRL_RESTRICT SIXTRL_UNUSED( elem ),
            SIXTRL_BUFFER_DATAPTR_DEC const OtherT *const
                SIXTRL_RESTRICT SIXTRL_UNUSED( orig ) ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
        }


        template< class OtherT >
        SIXTRL_HOST_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type< OtherT >(),
            status_t >::type
        init_for_copy(
            SIXTRL_BUFFER_DATAPTR_DEC TypeConstNumPtrsT* SIXTRL_RESTRICT elem,
            SIXTRL_BUFFER_DATAPTR_DEC const OtherT *const SIXTRL_RESTRICT orig )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

            static_assert( st::tests::TypeConstNumPtrs_is_type< OtherT >(),
               "OtherT required to be a TypeConstNumPtrs class" );

            if( ( elem != SIXTRL_NULLPTR ) && ( orig != SIXTRL_NULLPTR ) &&
                ( elem != orig ) )
            {
                st::tests::objs_size_t const num_b_values =
                    st::tests::TypeConstNumPtrs_b_length( orig );

                st::tests::objs_size_t const num_c_values =
                    st::tests::TypeConstNumPtrs_c_length( orig );

                status = st::tests::TypeConstNumPtrs_init(
                    elem, num_b_values, num_c_values );

                if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                    ( st::tests::TypeConstNumPtrs_impl_default<
                        TypeConstNumPtrsT >() ) )
                {
                    auto b_ret = this->add_ptr_field< real_t >( num_b_values,
                        st::tests::TypeConstNumPtrsTraits< TypeConstNumPtrsT
                            >::real_alignment );

                    status = b_ret.second;

                    if( status == st::ARCH_STATUS_SUCCESS )
                    {
                        status = st::tests::TypeConstNumPtrs_set_b_addr(
                            elem, b_ret.first );
                    }

                    auto c_ret = this->add_ptr_field< real_t >( num_c_values,
                        st::tests::TypeConstNumPtrsTraits< TypeConstNumPtrsT
                            >::real_alignment );

                    status = c_ret.second;

                    if( status == st::ARCH_STATUS_SUCCESS )
                    {
                        status = st::tests::TypeConstNumPtrs_set_c_addr(
                            elem, c_ret.first );
                    }
                }
            }

            return status;
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN status_t randomise_values(
            SIXTRL_BUFFER_DATAPTR_DEC TypeConstNumPtrsT* SIXTRL_RESTRICT elem )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

            if( elem != SIXTRL_NULLPTR )
            {
                status = st::tests::TypeConstNumPtrs_set_a(
                    elem, this->random_a_value() );

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    auto b_it  = st::tests::TypeConstNumPtrs_b_begin( elem );
                    auto b_end = st::tests::TypeConstNumPtrs_b_end( elem );

                    SIXTRL_ASSERT( b_it  != SIXTRL_NULLPTR );
                    SIXTRL_ASSERT( b_end != SIXTRL_NULLPTR );

                    for( ; b_it != b_end ; ++b_it )
                    {
                        *b_it = this->random_b_value();
                    }

                    auto c_it  = st::tests::TypeConstNumPtrs_c_begin( elem );
                    auto c_end = st::tests::TypeConstNumPtrs_c_end( elem );

                    SIXTRL_ASSERT( c_it  != SIXTRL_NULLPTR );
                    SIXTRL_ASSERT( c_end != SIXTRL_NULLPTR );

                    for( ; c_it != c_end ; ++c_it )
                    {
                        *c_it = this->random_c_value();
                    }
                }
            }

            return status;
        }

        SIXTRL_HOST_FN status_t randomise(
            SIXTRL_BUFFER_DATAPTR_DEC TypeConstNumPtrsT* SIXTRL_RESTRICT elem )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;

            st::arch_status_t status = st::tests::TypeConstNumPtrs_init( elem,
                    this->random_num_b_values_value(),
                    this->random_num_c_values_value() );

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( st::tests::TypeConstNumPtrs_impl_default<
                    TypeConstNumPtrsT >() ) )
            {
                auto b_ret = this->add_ptr_field< real_t >(
                    st::tests::TypeConstNumPtrs_b_length( elem ),
                    st::tests::TypeConstNumPtrsTraits< TypeConstNumPtrsT
                        >::real_alignment );

                status = b_ret.second;

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = st::tests::TypeConstNumPtrs_set_b_addr(
                        elem, b_ret.first );
                }

                auto c_ret = this->add_ptr_field< real_t >(
                    st::tests::TypeConstNumPtrs_c_length( elem ),
                    st::tests::TypeConstNumPtrsTraits< TypeConstNumPtrsT
                        >::real_alignment );

                status = c_ret.second;

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = st::tests::TypeConstNumPtrs_set_c_addr(
                        elem, c_ret.first );
                }
            }

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                status = this->randomise_values( elem );
            }

            return status;
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
        SIXTRL_BUFFER_DATAPTR_DEC TypeConstNumPtrsT* create_new(
            SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBufferView&
                SIXTRL_RESTRICT_REF view,
            SIXTRL_BUFFER_DATAPTR_DEC TypeConstNumPtrsT const* SIXTRL_RESTRICT orig )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            using this_t = st::tests::TypeConstNumPtrsInitialiser<
                TypeConstNumPtrsT >;

            SIXTRL_BUFFER_DATAPTR_DEC TypeConstNumPtrsT* added_elem =
                st::CBufferView_create_new_object< TypeConstNumPtrsT >( view,
                    st::tests::TypeConstNumPtrs_b_length( orig ),
                    st::tests::TypeConstNumPtrs_c_length( orig ) );

            if( ( added_elem != SIXTRL_NULLPTR ) &&
                ( st::ARCH_STATUS_SUCCESS != this_t::do_perform_copy(
                    added_elem, orig ) ) )
            {
                added_elem = SIXTRL_NULLPTR;
            }

            return added_elem;
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
        SIXTRL_BUFFER_DATAPTR_DEC TypeConstNumPtrsT* add_new(
            SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBufferView&
                SIXTRL_RESTRICT_REF view,
            SIXTRL_BUFFER_DATAPTR_DEC TypeConstNumPtrsT const* SIXTRL_RESTRICT orig )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            return st::CBufferView_add_object< TypeConstNumPtrsT >( view,
                    st::tests::TypeConstNumPtrs_a( orig ),
                    st::tests::TypeConstNumPtrs_b_length( orig ),
                    st::tests::TypeConstNumPtrs_c_length( orig ),
                    reinterpret_cast< std::uintptr_t >(
                        st::tests::TypeConstNumPtrs_const_b_begin( orig ) ),
                    reinterpret_cast< std::uintptr_t >(
                        st::tests::TypeConstNumPtrs_const_c_begin( orig ) ) );
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
        SIXTRL_BUFFER_DATAPTR_DEC TypeConstNumPtrsT* create_new(
            SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBuffer&
                SIXTRL_RESTRICT_REF buffer,
            SIXTRL_BUFFER_DATAPTR_DEC TypeConstNumPtrsT const* SIXTRL_RESTRICT orig )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            using this_t = st::tests::TypeConstNumPtrsInitialiser<
                TypeConstNumPtrsT >;

            SIXTRL_BUFFER_DATAPTR_DEC TypeConstNumPtrsT* added_elem =
                buffer.create_new< TypeConstNumPtrsT >(
                    st::tests::TypeConstNumPtrs_b_length( orig ),
                    st::tests::TypeConstNumPtrs_c_length( orig ) );

            if( ( added_elem != SIXTRL_NULLPTR ) &&
                ( st::ARCH_STATUS_SUCCESS != this_t::do_perform_copy(
                    added_elem, orig ) ) )
            {
                added_elem = SIXTRL_NULLPTR;
            }

            return added_elem;
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
        SIXTRL_BUFFER_DATAPTR_DEC TypeConstNumPtrsT* add_new(
            SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBuffer&
                SIXTRL_RESTRICT_REF buffer,
            SIXTRL_BUFFER_DATAPTR_DEC TypeConstNumPtrsT const* SIXTRL_RESTRICT orig )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            return buffer.add< TypeConstNumPtrsT >(
                st::tests::TypeConstNumPtrs_a( orig ),
                st::tests::TypeConstNumPtrs_b_length( orig ),
                st::tests::TypeConstNumPtrs_c_length( orig ),
                reinterpret_cast< std::uintptr_t >(
                    st::tests::TypeConstNumPtrs_const_b_begin( orig ) ),
                reinterpret_cast< std::uintptr_t >(
                    st::tests::TypeConstNumPtrs_const_c_begin( orig ) ) );
        }

        template< class PrngT >
        SIXTRL_INLINE SIXTRL_HOST_FN size_type
        random_num_b_values_value( PrngT& SIXTRL_RESTRICT prng )
        {
            return this->m_num_b_values_dist( prng );
        }

        SIXTRL_INLINE SIXTRL_HOST_FN size_type random_num_b_values_value()
        {
            return this->m_num_b_values_dist( this->m_size_prng );
        }

        template< class PrngT >
        SIXTRL_INLINE SIXTRL_HOST_FN size_type
        random_num_c_values_value( PrngT& SIXTRL_RESTRICT prng )
        {
            return this->m_num_c_values_dist( prng );
        }

        SIXTRL_INLINE SIXTRL_HOST_FN size_type random_num_c_values_value()
        {
            return this->m_num_c_values_dist( this->m_size_prng );
        }

        template< class PrngT >
        SIXTRL_INLINE SIXTRL_HOST_FN real_t
        random_a_value( PrngT& SIXTRL_RESTRICT prng )
        {
            return this->m_a_dist( prng );
        }

        SIXTRL_INLINE SIXTRL_HOST_FN real_t random_a_value()
        {
            return this->m_a_dist( this->m_real_prng );
        }

        template< class PrngT >
        SIXTRL_INLINE SIXTRL_HOST_FN real_t random_b_value(
            PrngT& SIXTRL_RESTRICT prng )
        {
            return this->m_b_dist( prng );
        }

        SIXTRL_INLINE SIXTRL_HOST_FN real_t random_b_value()
        {
            return this->m_b_dist( this->m_real_prng );
        }

        template< class PrngT >
        SIXTRL_INLINE SIXTRL_HOST_FN real_t random_c_value(
            PrngT& SIXTRL_RESTRICT prng )
        {
            return this->m_c_dist( prng );
        }

        SIXTRL_INLINE SIXTRL_HOST_FN real_t random_c_value()
        {
            return this->m_c_dist( this->m_real_prng );
        }

        private:

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN status_t do_perform_copy(
            SIXTRL_BUFFER_DATAPTR_DEC TypeConstNumPtrsT* SIXTRL_RESTRICT elem,
            SIXTRL_BUFFER_DATAPTR_DEC const TypeConstNumPtrsT *const orig )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

            if( ( elem != SIXTRL_NULLPTR ) && ( orig != SIXTRL_NULLPTR ) &&
                ( elem != orig ) &&
                ( st::tests::TypeConstNumPtrs_b_length( orig ) ==
                  st::tests::TypeConstNumPtrs_b_length( elem ) ) &&
                ( st::tests::TypeConstNumPtrs_c_length( orig ) ==
                  st::tests::TypeConstNumPtrs_c_length( elem ) ) )
            {
                status = st::tests::TypeConstNumPtrs_set_a( elem,
                    st::tests::TypeConstNumPtrs_a( orig ) );

                if( st::tests::TypeConstNumPtrs_const_b_begin( orig ) !=
                    SIXTRL_NULLPTR )
                {
                    status |= st::tests::TypeConstNumPtrs_set_b( elem,
                        st::tests::TypeConstNumPtrs_const_b_begin( orig ) );
                }

                if( st::tests::TypeConstNumPtrs_const_c_begin( orig ) !=
                    SIXTRL_NULLPTR )
                {
                    status |= st::tests::TypeConstNumPtrs_set_c( elem,
                        st::tests::TypeConstNumPtrs_const_c_begin( orig ) );
                }
            }

            return status;
        }

        real_prng_t  m_real_prng;
        size_prng_t  m_size_prng;

        size_dist_t  m_num_b_values_dist;
        size_dist_t  m_num_c_values_dist;
        real_dist_t  m_a_dist;
        real_dist_t  m_b_dist;
        real_dist_t  m_c_dist;
    };

    template< class TypeConstNumPtrsT >
    constexpr typename TypeConstNumPtrsInitialiser< TypeConstNumPtrsT >::real_t
    TypeConstNumPtrsInitialiser< TypeConstNumPtrsT >::MIN_RANDOM_A;

    template< class TypeConstNumPtrsT >
    constexpr typename TypeConstNumPtrsInitialiser< TypeConstNumPtrsT >::real_t
    TypeConstNumPtrsInitialiser< TypeConstNumPtrsT >::MAX_RANDOM_A;

    template< class TypeConstNumPtrsT >
    constexpr typename TypeConstNumPtrsInitialiser<
        TypeConstNumPtrsT >::size_type
    TypeConstNumPtrsInitialiser< TypeConstNumPtrsT >::MIN_RANDOM_NUM_B_VALUES;

    template< class TypeConstNumPtrsT >
    constexpr typename TypeConstNumPtrsInitialiser<
        TypeConstNumPtrsT >::size_type
    TypeConstNumPtrsInitialiser< TypeConstNumPtrsT >::MAX_RANDOM_NUM_B_VALUES;

    template< class TypeConstNumPtrsT >
    constexpr typename TypeConstNumPtrsInitialiser< TypeConstNumPtrsT >::real_t
    TypeConstNumPtrsInitialiser< TypeConstNumPtrsT >::MIN_RANDOM_B;

    template< class TypeConstNumPtrsT >
    constexpr typename TypeConstNumPtrsInitialiser< TypeConstNumPtrsT >::real_t
    TypeConstNumPtrsInitialiser< TypeConstNumPtrsT >::MAX_RANDOM_B;

    template< class TypeConstNumPtrsT >
    constexpr typename TypeConstNumPtrsInitialiser<
        TypeConstNumPtrsT >::size_type
    TypeConstNumPtrsInitialiser< TypeConstNumPtrsT >::MIN_RANDOM_NUM_C_VALUES;

    template< class TypeConstNumPtrsT >
    constexpr typename TypeConstNumPtrsInitialiser<
        TypeConstNumPtrsT >::size_type
    TypeConstNumPtrsInitialiser< TypeConstNumPtrsT >::MAX_RANDOM_NUM_C_VALUES;

    template< class TypeConstNumPtrsT >
    constexpr typename TypeConstNumPtrsInitialiser< TypeConstNumPtrsT >::real_t
    TypeConstNumPtrsInitialiser< TypeConstNumPtrsT >::MIN_RANDOM_C;

    template< class TypeConstNumPtrsT >
    constexpr typename TypeConstNumPtrsInitialiser< TypeConstNumPtrsT >::real_t
    TypeConstNumPtrsInitialiser< TypeConstNumPtrsT >::MAX_RANDOM_C;

    /* --------------------------------------------------------------------- */

    template< class TypeConstNumPtrsT >
    struct ObjsRandomInitialiserTraits<
        TypeConstNumPtrsT, typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_is_type<
                TypeConstNumPtrsT >(), void >::type >
    {
        typedef SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrsInitialiser<
            TypeConstNumPtrsT > initialiser_t;
    };

} /* namespace: tests */
} /* namespace: SIXTRL_CXX_NAMESPACE */

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC TypeT*
NS(TypeConstNumPtrs_preset)( SIXTRL_BUFFER_DATAPTR_DEC TypeT*
    SIXTRL_RESTRICT obj )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_preset( obj );
}

template< class TypeT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeConstNumPtrs_init)(
    SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj,
    SIXTRL_CXX_NAMESPACE::tests::objs_size_t const num_b_values,
    SIXTRL_CXX_NAMESPACE::tests::objs_size_t const num_c_values )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_init(
        obj, num_b_values, num_c_values );
}

template< class TypeT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeConstNumPtrs_init_detailed)(
    SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj, RealArg a,
    SIXTRL_CXX_NAMESPACE::tests::objs_size_t const num_b_values,
    SIXTRL_CXX_NAMESPACE::tests::objs_size_t const num_c_values,
    SIXTRL_CXX_NAMESPACE::tests::objs_addr_t const b_addr,
    SIXTRL_CXX_NAMESPACE::tests::objs_addr_t const c_addr )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_init_detailed(
        obj, a, num_b_values, num_c_values, b_addr, c_addr );
}

template< class TypeT, typename RealArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeConstNumPtrs_init)(
    SIXTRL_BUFFER_DATAPTR_DEC TypeT* SIXTRL_RESTRICT obj, RealArg a,
    SIXTRL_CXX_NAMESPACE::tests::objs_size_t const num_b_values,
    SIXTRL_CXX_NAMESPACE::tests::objs_size_t const num_c_values,
    SIXTRL_CXX_NAMESPACE::tests::objs_addr_t const b_addr,
    SIXTRL_CXX_NAMESPACE::tests::objs_addr_t const c_addr )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeConstNumPtrs_init_detailed(
        obj, a, num_b_values, num_c_values, b_addr, c_addr );
}
#endif /* C++ */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)*
NS(TypeConstNumPtrs_preset)( SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)*
    SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeConstNumPtrs_init)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_size_t) const num_b_values,
    NS(test_objs_size_t) const num_c_values ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeConstNumPtrs_init_detailed)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_real_t) const a,
    NS(test_objs_size_t) const num_b_values,
    NS(test_objs_size_t) const num_c_values,
    NS(test_objs_addr_t) const b_addr,
    NS(test_objs_addr_t) const c_addr ) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!!!        Inline Methods and Functions Implementations       !!!!!!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)*
NS(TypeConstNumPtrs_preset)( SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)*
    SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    if( obj != SIXTRL_NULLPTR )
    {
        NS(arch_status_t) status = NS(TypeConstNumPtrs_set_default_a)( obj );
        status |= NS(TypeConstNumPtrs_set_default_num_b_values)( obj );
        status |= NS(TypeConstNumPtrs_set_default_num_c_values)( obj );
        status |= NS(TypeConstNumPtrs_set_default_b_addr)( obj );
        status |= NS(TypeConstNumPtrs_set_default_c_addr)( obj );

        SIXTRL_ASSERT( status == (
            NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS );

        ( void )status;
    }

    return obj;
}

SIXTRL_INLINE NS(arch_status_t) NS(TypeConstNumPtrs_init)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_size_t) const num_b_values,
    NS(test_objs_size_t) const num_c_values ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = NS(TypeConstNumPtrs_set_default_a)( obj );
    status |= NS(TypeConstNumPtrs_set_num_b_values)( obj, num_b_values );
    status |= NS(TypeConstNumPtrs_set_default_b_addr)( obj );
    status |= NS(TypeConstNumPtrs_set_num_c_values)( obj, num_c_values );
    status |= NS(TypeConstNumPtrs_set_default_c_addr)( obj );

    return status;
}

SIXTRL_INLINE NS(arch_status_t) NS(TypeConstNumPtrs_init_detailed)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeConstNumPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_real_t) const a,
    NS(test_objs_size_t) const num_b_values,
    NS(test_objs_size_t) const num_c_values,
    NS(test_objs_addr_t) const b_addr,
    NS(test_objs_addr_t) const c_addr ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = NS(TypeConstNumPtrs_set_a)( obj, a );
    status |= NS(TypeConstNumPtrs_set_num_b_values)( obj, num_b_values );
    status |= NS(TypeConstNumPtrs_set_b_addr)( obj, b_addr );
    status |= NS(TypeConstNumPtrs_set_num_c_values)( obj, num_c_values );
    status |= NS(TypeConstNumPtrs_set_c_addr)( obj, c_addr );

    return status;
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#endif /* SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_TYPE_CONST_NUM_PTRS_INIT_H__ */
