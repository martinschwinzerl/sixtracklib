#ifndef SIXTRACKLIB_TESTLIB_COMMON_OBJS_DEFINITIONS_H__
#define SIXTRACKLIB_TESTLIB_COMMON_OBJS_DEFINITIONS_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stddef.h>
    #include <stdlib.h>
    #if defined( __cplusplus )
        #include <type_traits>
    #endif /* C++ */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/internal/buffer_main_defines.h"
    #include "sixtracklib/common/internal/obj_store_traits.hpp"
    #include "sixtracklib/common/internal/obj_c_api_traits.hpp"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

typedef SIXTRL_REAL_T   NS(test_objs_real_t);
typedef SIXTRL_INT64_T  NS(test_objs_int_t);
typedef SIXTRL_UINT8_T  NS(test_objs_uchar_t);
typedef SIXTRL_UINT64_T NS(test_objs_size_t);
typedef SIXTRL_UINT64_T NS(test_objs_addr_t);

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    typedef ::NS(test_objs_real_t)  objs_real_t;
    typedef ::NS(test_objs_int_t)   objs_int_t;
    typedef ::NS(test_objs_uchar_t) objs_uchar_t;
    typedef ::NS(test_objs_size_t)  objs_size_t;
    typedef ::NS(test_objs_addr_t)  objs_addr_t;

    /*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    typedef enum
    {
        OBJS_TYPE_NO_PTRS_IMPL_DEFAULT = 0
    }
    objs_type_no_ptrs_impl_t;

    template< class TypeNoPtrsT >
    struct ObjDataNoPtrTypeTraits
    {
        static constexpr bool is_type = false;
        static constexpr objs_type_no_ptrs_impl_t implementation =
            SIXTRL_CXX_NAMESPACE::tests::OBJS_TYPE_NO_PTRS_IMPL_DEFAULT;
    };

    template< class TypeNoPtrsT >
    constexpr bool ObjDataNoPtrTypeTraits< TypeNoPtrsT >::is_type;

    template< class TypeNoPtrsT >
    constexpr objs_type_no_ptrs_impl_t ObjDataNoPtrTypeTraits<
        TypeNoPtrsT >::implementation;

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class TypeNoPtrsT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN constexpr bool
    TypeNoPtrs_is_type( SIXTRL_BUFFER_DATAPTR_DEC const TypeNoPtrsT
        *const SIXTRL_RESTRICT /* obj */ = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return ObjDataNoPtrTypeTraits< TypeNoPtrsT >::is_type;
    }

    template< class TypeNoPtrsT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN constexpr bool
    TypeNoPtrs_impl_default( SIXTRL_BUFFER_DATAPTR_DEC const TypeNoPtrsT
        *const SIXTRL_RESTRICT /* obj */ = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return ObjDataNoPtrTypeTraits< TypeNoPtrsT >::implementation ==
            SIXTRL_CXX_NAMESPACE::tests::OBJS_TYPE_NO_PTRS_IMPL_DEFAULT;
    }

    /*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< class TypeNoPtrsT > struct TypeNoPtrsTraits
    {
    };

    /* --------------------------------------------------------------------- */

    typedef enum
    {
        OBJS_TYPE_CONST_NUM_PTRS_IMPL_DEFAULT = 0,
        OBJS_TYPE_CONST_NUM_PTRS_IMPL_STD_VECTOR = 1
    }
    objs_type_const_num_ptrs_impl_t;

    template< class TypeConstNumPtrsT >
    struct ObjDataTypeConstNumPtrsTraits
    {
        static constexpr bool is_type = false;
        static constexpr objs_type_const_num_ptrs_impl_t implementation =
            SIXTRL_CXX_NAMESPACE::tests::OBJS_TYPE_CONST_NUM_PTRS_IMPL_DEFAULT;
    };

    template< class TypeConstNumPtrsT >
    constexpr bool ObjDataTypeConstNumPtrsTraits< TypeConstNumPtrsT >::is_type;

    template< class TypeConstNumPtrsT >
    constexpr objs_type_const_num_ptrs_impl_t ObjDataTypeConstNumPtrsTraits<
        TypeConstNumPtrsT >::implementation;

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class TypeConstNumPtrsT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN constexpr bool
    TypeConstNumPtrs_is_type( SIXTRL_BUFFER_DATAPTR_DEC const
        TypeConstNumPtrsT *const SIXTRL_RESTRICT /* obj */ =
            SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return ObjDataTypeConstNumPtrsTraits< typename std::decay<
            TypeConstNumPtrsT >::type >::is_type;
    }

    template< class TypeConstNumPtrsT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN constexpr bool
    TypeConstNumPtrs_impl_default() SIXTRL_NOEXCEPT
    {
        return ObjDataTypeConstNumPtrsTraits< typename std::decay<
            TypeConstNumPtrsT >::type >::implementation ==
        SIXTRL_CXX_NAMESPACE::tests::OBJS_TYPE_CONST_NUM_PTRS_IMPL_DEFAULT;
    }

    template< class TypeConstNumPtrsT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN constexpr bool
    TypeConstNumPtrs_impl_std_vector() SIXTRL_NOEXCEPT
    {
        return ObjDataTypeConstNumPtrsTraits< typename std::decay<
            TypeConstNumPtrsT >::type >::implementation ==
        SIXTRL_CXX_NAMESPACE::tests::OBJS_TYPE_CONST_NUM_PTRS_IMPL_STD_VECTOR;
    }

    /*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< class TypeConstNumPtrsT > struct TypeConstNumPtrsTraits
    {
    };

} /* tests */
} /* SIXTRL_CXX_NAMESPACE */
#endif /* __cplusplus */

#endif /* SIXTRACKLIB_TESTLIB_COMMON_OBJS_DEFINITIONS_H__ */
