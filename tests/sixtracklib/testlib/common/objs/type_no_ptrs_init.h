#ifndef SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_TYPE_NO_PTRS_INIT_H__
#define SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_TYPE_NO_PTRS_INIT_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/testlib/common/objs/definitions.h"
    #include "sixtracklib/testlib/common/objs/objs_traits.hpp"
    #include "sixtracklib/testlib/common/objs/type_no_ptrs.h"
    #include "sixtracklib/testlib/common/objs/type_no_ptrs_api.h"
    #include "sixtracklib/testlib/common/cobjects/cobj_elem_traits.hpp"
    #include "sixtracklib/testlib/common/cobjects/cobjects_initialiser_base.hpp"
    #include "sixtracklib/common/internal/obj_store_traits.hpp"
    #include "sixtracklib/common/internal/type_random_traits.hpp"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
    #include "sixtracklib/common/internal/compiler_attributes.h"
    #include "sixtracklib/common/cobjects/cbuffer_view.hpp"
    #include "sixtracklib/common/cobjects/cbuffer.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    /* --------------------------------------------------------------------- */
    /* init API: */

    template< class TypeNoPtrsT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT*
    TypeNoPtrs_preset( SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT* SIXTRL_RESTRICT obj )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        if( obj != SIXTRL_NULLPTR )
        {
            st::arch_status_t status =
                st::tests::TypeNoPtrs_set_default_a( obj );

            status |= st::tests::TypeNoPtrs_set_default_b( obj );
            status |= st::tests::TypeNoPtrs_set_default_c( obj );

            SIXTRL_ASSERT( status == st::ARCH_STATUS_SUCCESS );
            ( void )status;
        }

        return obj;
    }

    template< class TypeNoPtrsT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
    TypeNoPtrs_init( SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT*
        SIXTRL_RESTRICT obj )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::arch_status_t status =
            st::tests::TypeNoPtrs_set_default_a( obj );
        status |= st::tests::TypeNoPtrs_set_default_b( obj );
        status |= st::tests::TypeNoPtrs_set_default_c( obj );

        return status;
    }

    template< class TypeNoPtrsT,
              typename RealArg, typename IntArg, typename UCharIter >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
    TypeNoPtrs_init_detailed(
        SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT* SIXTRL_RESTRICT obj,
        RealArg a, IntArg b, UCharIter c_values_begin )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::arch_status_t status = st::tests::TypeNoPtrs_set_a( obj, a );
        status |= st::tests::TypeNoPtrs_set_b( obj, b );
        status |= st::tests::TypeNoPtrs_set_c( obj, c_values_begin );
        return status;
    }

    template< class TypeNoPtrsT,
              typename RealArg, typename IntArg, typename UCharIter >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
    TypeNoPtrs_init( SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT*
        SIXTRL_RESTRICT obj, RealArg a, IntArg b, UCharIter c_values_begin )
    {
        return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_init_detailed(
            obj, a, b, c_values_begin );
    }

} /* namespace: tests */

template< class TypeNoPtrsT, store_backend_t StoreBeT >
struct ObjDataInitialiser< TypeNoPtrsT, StoreBeT, typename std::enable_if<
    SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< TypeNoPtrsT >(), void
        >::type >
{
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN void preset(
        SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT* SIXTRL_RESTRICT obj )
    {
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_preset( obj );
    }

    template< typename... Args >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN arch_status_t init(
        SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT* SIXTRL_RESTRICT obj,
        Args&&... args )
    {
        return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_init(
            obj, std::forward< Args >( args )... );
    }
};

namespace tests
{
    template< class TypeNoPtrsT >
    class TypeNoPtrsInitialiser : public CObjElemInitialiserBase
    {
        public:

        static_assert( SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type<
                TypeNoPtrsT >(),
            "TypeNoPtrsT is required to be a no-ptr test obj type" );

        typedef typename SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits<
                            TypeNoPtrsT >::real_t real_t;

        typedef typename SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits<
                            TypeNoPtrsT >::int_t int_t;

        typedef typename SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsTraits<
                            TypeNoPtrsT >::uchar_t uchar_t;

        private:

        typedef SIXTRL_CXX_NAMESPACE::TypeRandomTraits< real_t >
                real_random_traits_t;

        typedef SIXTRL_CXX_NAMESPACE::TypeRandomTraits< int_t >
                int_random_traits_t;

        typedef SIXTRL_CXX_NAMESPACE::TypeRandomTraits< uchar_t >
                uchar_random_traits_t;

        static_assert( real_random_traits_t::has_uniform_dist,
            "Requires a uniform distribution for the real_t" );

        static_assert( int_random_traits_t::has_uniform_dist,
            "Requires a uniform distribution for the int_t" );

        static_assert( uchar_random_traits_t::has_uniform_dist,
            "Requires a uniform distribution for the uchar_t" );

        public:

        typedef typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits<
                         real_t >::const_argument_type const_real_arg_t;

        typedef typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits<
                         int_t >::const_argument_type const_int_arg_t;

        typedef typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits<
                         uchar_t >::const_argument_type const_uchar_arg_t;


        typedef typename real_random_traits_t::uniform_dist_t a_dist_t;
        typedef typename real_random_traits_t::default_prng_t real_prng_t;
        typedef typename real_random_traits_t::default_prng_seed_t
                         real_prng_seed_t;

        typedef typename int_random_traits_t::uniform_dist_t b_dist_t;
        typedef typename int_random_traits_t::default_prng_t int_prng_t;
        typedef typename int_random_traits_t::default_prng_seed_t
                         int_prng_seed_t;

        typedef typename uchar_random_traits_t::uniform_dist_t c_dist_t;
        typedef typename uchar_random_traits_t::default_prng_t uchar_prng_t;
        typedef typename uchar_random_traits_t::default_prng_seed_t
                         uchar_prng_seed_t;

        static constexpr real_t  MIN_RANDOM_A = real_t{   -10 };
        static constexpr real_t  MAX_RANDOM_A = real_t{    10 };

        static constexpr int_t   MIN_RANDOM_B = int_t{    -42 };
        static constexpr int_t   MAX_RANDOM_B = int_t{     43 };

        static constexpr uchar_t MIN_RANDOM_C = uchar_t{  100 };
        static constexpr uchar_t MAX_RANDOM_C = uchar_t{  201 };

        SIXTRL_HOST_FN explicit TypeNoPtrsInitialiser(
            const_real_arg_t  min_a = MIN_RANDOM_A,
            const_real_arg_t  max_a = MAX_RANDOM_A,
            const_int_arg_t   min_b = MIN_RANDOM_B,
            const_int_arg_t   max_b = MAX_RANDOM_B,
            const_uchar_arg_t min_c = MIN_RANDOM_C,
            const_uchar_arg_t max_c = MAX_RANDOM_C ) :
            m_real_prng( real_prng_seed_t{ 202005130 } ),
            m_int_prng( int_prng_seed_t{ 202005131 } ),
            m_uchar_prng( uchar_prng_seed_t{ 202005131 } ),
            m_a_dist( min_a, max_a ), m_b_dist( min_b, max_b ),
            m_c_dist( min_c, max_c )
        {

        }

        SIXTRL_HOST_FN TypeNoPtrsInitialiser(
            TypeNoPtrsInitialiser< TypeNoPtrsT > const& ) = default;

        SIXTRL_HOST_FN TypeNoPtrsInitialiser(
            TypeNoPtrsInitialiser< TypeNoPtrsT >&& ) = default;

        SIXTRL_HOST_FN TypeNoPtrsInitialiser< TypeNoPtrsT >& operator=(
            TypeNoPtrsInitialiser< TypeNoPtrsT > const& ) = default;

        SIXTRL_HOST_FN TypeNoPtrsInitialiser< TypeNoPtrsT >& operator=(
            TypeNoPtrsInitialiser< TypeNoPtrsT >&& ) = default;

        SIXTRL_HOST_FN virtual ~TypeNoPtrsInitialiser() = default;

        template< typename... Args >
        SIXTRL_HOST_FN status_t operator()(
                SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT* SIXTRL_RESTRICT elem,
                Args&&... init_parameters )
        {
            return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_init(
                elem, std::forward< Args >( init_parameters )... );
        }

        template< class OtherT >
        SIXTRL_HOST_FN status_t init_for_copy(
            SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT* SIXTRL_RESTRICT elem,
            SIXTRL_BUFFER_DATAPTR_DEC const OtherT *const SIXTRL_RESTRICT orig )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

            static_assert( st::tests::TypeNoPtrs_is_type< OtherT >(),
               "OtherT required to be a TypeNoPtrs class" );

            if( ( elem != SIXTRL_NULLPTR ) && ( orig != SIXTRL_NULLPTR ) &&
                ( elem != orig ) )
            {
                st::tests::TypeNoPtrs_preset( elem );
                status = st::ARCH_STATUS_SUCCESS;
            }

            return status;
        }

        SIXTRL_HOST_FN status_t randomise(
                SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT* SIXTRL_RESTRICT elem )
        {
            return this->randomise_values( elem );
        }

        SIXTRL_HOST_FN status_t randomise_values(
                SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT* SIXTRL_RESTRICT elem )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;

            st::arch_status_t status = st::tests::TypeNoPtrs_set_a(
                elem, this->random_a_value() );

            status |= st::tests::TypeNoPtrs_set_b(
                elem, this->random_b_value() );

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( st::tests::TypeNoPtrs_const_c_begin( elem ) != SIXTRL_NULLPTR ) )
            {
                auto c_it  = st::tests::TypeNoPtrs_c_begin( elem );
                auto c_end = st::tests::TypeNoPtrs_c_end( elem );

                SIXTRL_ASSERT( c_it  != SIXTRL_NULLPTR );
                SIXTRL_ASSERT( c_end != SIXTRL_NULLPTR );

                for( ; c_it != c_end ; ++c_it )
                {
                    *c_it = this->random_c_value();
                }
            }

            return status;
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
        SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT* create_new(
            SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBufferView&
                SIXTRL_RESTRICT_REF view,
            SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT const* SIXTRL_RESTRICT orig )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;

            SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT* added_elem =
                st::CBufferView_create_new_object< TypeNoPtrsT >( view );

            if( added_elem != SIXTRL_NULLPTR )
            {
                st::arch_status_t status  = st::tests::TypeNoPtrs_set_a(
                    added_elem, st::tests::TypeNoPtrs_a( orig ) );

                status |= st::tests::TypeNoPtrs_set_b( added_elem,
                    st::tests::TypeNoPtrs_b( orig ) );

                status |= st::tests::TypeNoPtrs_set_c( added_elem,
                    st::tests::TypeNoPtrs_const_c_begin( orig ) );

                if( status != st::ARCH_STATUS_SUCCESS )
                {
                    added_elem = SIXTRL_NULLPTR;
                }
            }

            return added_elem;
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
        SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT* add_new(
            SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBufferView&
                SIXTRL_RESTRICT_REF view,
            SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT const* SIXTRL_RESTRICT orig )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            return st::CBufferView_add_object< TypeNoPtrsT >( view,
                    st::tests::TypeNoPtrs_a( orig ),
                    st::tests::TypeNoPtrs_b( orig ),
                    st::tests::TypeNoPtrs_const_c_begin( orig ) );
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
        SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT* create_new(
            SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBuffer&
                SIXTRL_RESTRICT_REF buffer,
            SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT const* SIXTRL_RESTRICT orig )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;

            SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT* added_elem =
                buffer.create_new< TypeNoPtrsT >();

            if( added_elem != SIXTRL_NULLPTR )
            {
                st::arch_status_t status  = st::tests::TypeNoPtrs_set_a(
                    added_elem, st::tests::TypeNoPtrs_a( orig ) );

                status |= st::tests::TypeNoPtrs_set_b( added_elem,
                    st::tests::TypeNoPtrs_b( orig ) );

                status |= st::tests::TypeNoPtrs_set_c( added_elem,
                    st::tests::TypeNoPtrs_const_c_begin( orig ) );

                if( status != st::ARCH_STATUS_SUCCESS )
                {
                    added_elem = SIXTRL_NULLPTR;
                }
            }

            return added_elem;
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
        SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT* add_new(
            SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBuffer&
                SIXTRL_RESTRICT_REF buffer,
            SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT const* SIXTRL_RESTRICT orig )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            static_assert( st::CObjElem_allow_direct_storage< TypeNoPtrsT >(),
                           "HERE1" );

            return buffer.add< TypeNoPtrsT >(
                st::tests::TypeNoPtrs_a( orig ),
                st::tests::TypeNoPtrs_b( orig ),
                st::tests::TypeNoPtrs_const_c_begin( orig ) );
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
        SIXTRL_INLINE SIXTRL_HOST_FN int_t
        random_b_value( PrngT& SIXTRL_RESTRICT prng )
        {
            return this->m_b_dist( prng );
        }

        SIXTRL_INLINE SIXTRL_HOST_FN int_t random_b_value()
        {
            return this->m_b_dist( this->m_int_prng );
        }

        template< class PrngT >
        SIXTRL_INLINE SIXTRL_HOST_FN uchar_t
        random_c_value( PrngT& SIXTRL_RESTRICT prng )
        {
            return this->m_c_dist( prng );
        }

        SIXTRL_INLINE SIXTRL_HOST_FN uchar_t random_c_value()
        {
            return this->m_c_dist( this->m_uchar_prng );
        }

        private:

        real_prng_t  m_real_prng;
        int_prng_t   m_int_prng;
        uchar_prng_t m_uchar_prng;

        a_dist_t     m_a_dist;
        b_dist_t     m_b_dist;
        c_dist_t     m_c_dist;
    };

    template< class TypeNoPtrsT >
    constexpr typename TypeNoPtrsInitialiser< TypeNoPtrsT >::real_t
    TypeNoPtrsInitialiser< TypeNoPtrsT >::MIN_RANDOM_A;

    template< class TypeNoPtrsT >
    constexpr typename TypeNoPtrsInitialiser< TypeNoPtrsT >::real_t
    TypeNoPtrsInitialiser< TypeNoPtrsT >::MAX_RANDOM_A;

    template< class TypeNoPtrsT >
    constexpr typename TypeNoPtrsInitialiser< TypeNoPtrsT >::int_t
    TypeNoPtrsInitialiser< TypeNoPtrsT >::MIN_RANDOM_B;

    template< class TypeNoPtrsT >
    constexpr typename TypeNoPtrsInitialiser< TypeNoPtrsT >::int_t
    TypeNoPtrsInitialiser< TypeNoPtrsT >::MAX_RANDOM_B;

    template< class TypeNoPtrsT >
    constexpr typename TypeNoPtrsInitialiser< TypeNoPtrsT >::uchar_t
    TypeNoPtrsInitialiser< TypeNoPtrsT >::MIN_RANDOM_C;

    template< class TypeNoPtrsT >
    constexpr typename TypeNoPtrsInitialiser< TypeNoPtrsT >::uchar_t
    TypeNoPtrsInitialiser< TypeNoPtrsT >::MAX_RANDOM_C;

    /* --------------------------------------------------------------------- */

    template< class TypeNoPtrsT >
    struct ObjsRandomInitialiserTraits< TypeNoPtrsT, typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_is_type< TypeNoPtrsT >(),
        void >::type >
    {
        typedef SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrsInitialiser<
            TypeNoPtrsT > initialiser_t;
    };

} /* namespace: tests */
} /* namespace: SIXTRL_CXX_NAMESPACE */

template< class TypeNoPtrsT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT*
NS(TypeNoPtrs_preset)( SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT*
    SIXTRL_RESTRICT obj )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_preset( obj );
}

template< class TypeNoPtrsT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeNoPtrs_init)( SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT*
    SIXTRL_RESTRICT obj )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_init( obj );
}

template< class TypeNoPtrsT, typename RealArg, typename IntArg,
          typename UCharArg >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeNoPtrs_init_detailed)(
    SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT* SIXTRL_RESTRICT obj,
    RealArg a, IntArg b, UCharArg c )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_init_detailed(
        obj, a, b, c );
}

template< class TypeNoPtrsT, typename RealArg, typename IntArg,
          typename UCharIter >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
NS(TypeNoPtrs_init)( SIXTRL_BUFFER_DATAPTR_DEC TypeNoPtrsT* SIXTRL_RESTRICT obj,
    RealArg a, IntArg b, UCharIter c_values_begin )
{
    return SIXTRL_CXX_NAMESPACE::tests::TypeNoPtrs_init(
        obj, a, b, c_values_begin );
}
#endif /* C++ */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)*
NS(TypeNoPtrs_preset)( SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)*
    SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeNoPtrs_init)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT;


SIXTRL_STATIC SIXTRL_FN NS(arch_status_t) NS(TypeNoPtrs_init_detailed)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_real_t) const a, NS(test_objs_int_t) const b,
    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_uchar_t) const* SIXTRL_RESTRICT
        c_values_begin ) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!!!        Inline Methods and Functions Implementations       !!!!!!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_INLINE SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)*
NS(TypeNoPtrs_preset)( SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)*
    SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    if( obj != SIXTRL_NULLPTR )
    {
        NS(arch_status_t) status = NS(TypeNoPtrs_set_default_a)( obj );
        status |= NS(TypeNoPtrs_set_default_b)( obj );
        status |= NS(TypeNoPtrs_set_default_c)( obj );

        SIXTRL_ASSERT( status == (
            NS(arch_status_t) )SIXTRL_ARCH_STATUS_SUCCESS );
        ( void )status;
    }

    return obj;
}

SIXTRL_INLINE NS(arch_status_t) NS(TypeNoPtrs_init)( SIXTRL_BUFFER_DATAPTR_DEC
    NS(TypeNoPtrs)* SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = NS(TypeNoPtrs_set_default_a)( obj );
    status |= NS(TypeNoPtrs_set_default_b)( obj );
    status |= NS(TypeNoPtrs_set_default_c)( obj );

    return status;
}

SIXTRL_INLINE NS(arch_status_t) NS(TypeNoPtrs_init_detailed)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TypeNoPtrs)* SIXTRL_RESTRICT obj,
    NS(test_objs_real_t) const a, NS(test_objs_int_t) const b,
    SIXTRL_BUFFER_DATAPTR_DEC NS(test_objs_uchar_t) const* SIXTRL_RESTRICT
        c_values_begin ) SIXTRL_NOEXCEPT
{
    NS(arch_status_t) status = NS(TypeNoPtrs_set_a)( obj, a );
    status |= NS(TypeNoPtrs_set_b)( obj, b );
    status |= NS(TypeNoPtrs_set_c)( obj, c_values_begin );
    return status;
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#endif /* SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_TYPE_NO_PTRS_INIT_H__ */
