#ifndef SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_TYPE_NO_PTRS_H__
#define SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_TYPE_NO_PTRS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/cobjects/obj_base_class.hpp"
    #include "sixtracklib/common/internal/obj_data_type_traits.hpp"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

typedef enum { NS(TESTS_OBJECT_TYPE_NO_PTRS) = 10000 } NS(TypeNoPtrsTypeId);

typedef struct NS(TypeNoPtrs)
{
    SIXTRL_REAL_T   a         SIXTRL_ALIGN( 8 );
    SIXTRL_INT64_T  b         SIXTRL_ALIGN( 8 );
    SIXTRL_UINT8_T  c[ 6 ]    SIXTRL_ALIGN( 8 );
}
NS(TypeNoPtrs);

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#if defined( __cplusplus )

namespace SIXTRL_CXX_NAMESPACE
{
    static constexpr cobj_type_id_t TESTS_OBJECT_TYPE_NO_PTRS =
        static_cast< cobj_type_id_t >( NS(TESTS_OBJECT_TYPE_NO_PTRS) );

    template<>
    struct ObjTypeIdDataTypeMap< cobj_type_id_t, TESTS_OBJECT_TYPE_NO_PTRS >
    {
        typedef ::NS(TypeNoPtrs) value_type;
    };

    template<>
    struct ObjDataTypeIdTraits< ::NS(TypeNoPtrs), cobj_type_id_t >
    {
        static SIXTRL_FN constexpr cobj_type_id_t TypeId() SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::TESTS_OBJECT_TYPE_NO_PTRS;
        }
    };

    namespace tests
    {
        template<
            typename A, typename B, typename C,
            arch_size_t AlignA = SIXTRL_CXX_NAMESPACE::Type_storage_align< A >(),
            arch_size_t AlignB = SIXTRL_CXX_NAMESPACE::Type_storage_align< B >(),
            arch_size_t AlignC = SIXTRL_CXX_NAMESPACE::Type_storage_align< C >() >
        struct TypeNoPtrsData
        {
            A a         SIXTRL_ALIGN( AlignA );
            B b         SIXTRL_ALIGN( AlignB );
            C c[ 6 ]    SIXTRL_ALIGN( AlignC );
        };

        typedef TypeNoPtrsData< SIXTRL_REAL_T, SIXTRL_INT64_T, SIXTRL_UINT8_T,
                                8u, 8u, 8u >
                CTypeNoPtrsEquivData;

        template< class E, SIXTRL_CXX_NAMESPACE::store_backend_t StoreT >
        class TTypeNoPtrsImpl :
            public SIXTRL_CXX_NAMESPACE::ObjDataStorageInterfaceBase<
                E, StoreT, TTypeNoPtrsImpl< E, StoreT > > {};

        template< typename A, typename B, typename C,
            arch_size_t AlignA = SIXTRL_CXX_NAMESPACE::Type_storage_align< A >(),
            arch_size_t AlignB = SIXTRL_CXX_NAMESPACE::Type_storage_align< B >(),
            arch_size_t AlignC = SIXTRL_CXX_NAMESPACE::Type_storage_align< C >() >
        using TTypeNoPtrs =
            TTypeNoPtrsImpl< TypeNoPtrsData< A, B, C, AlignA, AlignB, AlignC >,
                             SIXTRL_CXX_NAMESPACE::STORAGE_BE_COBJECTS >;

        typedef TTypeNoPtrsImpl< CTypeNoPtrsEquivData,
                                 SIXTRL_CXX_NAMESPACE::STORAGE_BE_COBJECTS >
                TypeNoPtrs;

        typedef TTypeNoPtrsImpl< ::NS(TypeNoPtrs),
                                 SIXTRL_CXX_NAMESPACE::STORAGE_BE_COBJECTS >
                CTypeNoPtrs;
    }

    template<> struct ObjDataCApiTypeTraits<
        SIXTRL_CXX_NAMESPACE::tests::CTypeNoPtrsEquivData >
    {
        typedef ::NS(TypeNoPtrs) c_api_t;
    };
}

#endif /* __cplusplus */
#endif /* SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_TYPE_NO_PTRS_H__ */
