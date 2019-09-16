#ifndef SIXTRACKLIB_COMMON_INTERNAL_OBJ_STORE_TRAITS_CXX_HPP__
#define SIXTRACKLIB_COMMON_INTERNAL_OBJ_STORE_TRAITS_CXX_HPP__

#include <algorithm>
#include <cstdlib>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/buffer.h"
#include "sixtracklib/common/internal/objects_type_id.h"

namespace SIXTRL_CXX_NAMESPACE
{
    template< typename T >
    struct TypeStoreTraits
    {
        static SIXTRL_FN constexpr std::size_t StorageAlign()
        {
            return alignof( T ) > static_cast< std::size_t >( 8u )
                 ? alignof( T ) : static_cast< std::size_t >( 8u );
        }

        static SIXTRL_FN constexpr bool Scalar()
        {
            return true;
        }
    };

    /* --------------------------------------------------------------------- */

    template< class ObjData >
    struct ObjDataStoreTraits
    {
        static SIXTRL_FN constexpr
        SIXTRL_CXX_NAMESPACE::object_type_id_t ObjTypeId()
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_INVALID;
        }

        static SIXTRL_FN constexpr bool HasCApiLayout()
        {
            return false;
        }
    };

    template< class ObjData >
    struct ObjDataStoreConstructionTraits
    {
        static SIXTRL_FN constexpr bool CanBeMemCopied()
        {
            return std::is_trivially_copyable< ObjData >::value;
        };
    };

    template< class ObjData >
    SIXTRL_FN constexpr bool
    ObjData_can_be_stored_on_cobjects_buffer() SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef st::ObjDataStoreTraits< ObjData > _store_traits_t;
        typedef st::ObjDataStoreConstructionTraits< ObjData >
                _construction_traits_t;

        return ( ( std::is_standard_layout< ObjData >::value ) &&
                 ( _store_traits_t::ObjTypeId() !=
                     SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_INVALID ) &&
                 ( _construction_traits_t::CanBeMemCopied() ) );
    }

    template< class ObjData >
    SIXTRL_FN bool ObjData_can_be_stored_on_cobjects_buffer(
        const ::NS(Buffer) *const SIXTRL_RESTRICT buffer )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef ::NS(buffer_size_t) size_type;

        size_type const slot_size = ::NS(Buffer_get_slot_size)( buffer );

        return ( ( st::ObjData_can_be_stored_on_cobjects_buffer< ObjData >() ) &&
                 ( buffer != nullptr ) && ( slot_size > size_type{ 0 } ) &&
                 ( ( slot_size == size_type { 1 } ) ||
                   ( ( slot_size <= alignof( ObjData ) ) &&
                     ( alignof( ObjData ) % slot_size == size_type{ 0 } ) ) ||
                   ( slot_size > alignof( ObjData ) ) ) );
    }

    template< class ObjData >
    SIXTRL_FN constexpr bool ObjData_has_same_layout_as_c_api() SIXTRL_NOEXCEPT
    {
        return ObjDataStoreTraits< ObjData >::HasCApiLayout();
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_FN SIXTRL_CXX_NAMESPACE::object_type_id_t
    ObjectTypeId_add_special_variant(
        SIXTRL_FN SIXTRL_CXX_NAMESPACE::object_type_id_t const obj_type_id,
        SIXTRL_FN SIXTRL_CXX_NAMESPACE::object_type_id_t const variant_flag )
    {
        using obj_type_id_t = SIXTRL_CXX_NAMESPACE::object_type_id_t;
        obj_type_id_t const VARIANT_FLAG_MASK = ( obj_type_id_t )0x0000ffff;

        return ( obj_type_id & VARIANT_FLAG_MASK ) |
            ( ( variant_flag & VARIANT_FLAG_MASK ) << 4u );
    }

    SIXTRL_FN bool ObjectTypeId_is_special_type_id(
        SIXTRL_CXX_NAMESPACE::object_type_id_t const obj_type_id )
    {
        using obj_type_id_t = SIXTRL_CXX_NAMESPACE::object_type_id_t;
        obj_type_id_t const SPECIAL_VARIANT = ( obj_type_id_t )0x0000ffff;

        return ( obj_type_id > SPECIAL_VARIANT );
    }

    SIXTRL_FN SIXTRL_CXX_NAMESPACE::object_type_id_t
    ObjectTypeId_get_base_type_id(
        SIXTRL_FN SIXTRL_CXX_NAMESPACE::object_type_id_t const obj_type_id )
    {
        using obj_type_id_t = SIXTRL_CXX_NAMESPACE::object_type_id_t;
        obj_type_id_t const MASK = ( obj_type_id_t )0x0000ffff;

        return obj_type_id & MASK;
    }

    SIXTRL_FN SIXTRL_CXX_NAMESPACE::object_type_id_t
    ObjectTypeId_get_variant_flag(
        SIXTRL_FN SIXTRL_CXX_NAMESPACE::object_type_id_t const obj_type_id )
    {
        using obj_type_id_t = SIXTRL_CXX_NAMESPACE::object_type_id_t;
        obj_type_id_t const MASK = ( obj_type_id_t )0x0000ffff;

        return ( obj_type_id >> 4u ) & MASK;
    }

    /* --------------------------------------------------------------------- */

    template< class ObjData >
    struct ObjDataStoreLayoutTraits
    {
        typedef ::NS(buffer_size_t) size_type;
        typedef ::NS(arch_status_t) status_t;

        static SIXTRL_FN constexpr size_type NumDataPtrs() { return 0u; }
        static SIXTRL_FN constexpr bool VarNumDataPtrCounts() { return false; }

        static SIXTRL_FN status_t GetDataPtrTypeOffsets( size_type* )
        {
            return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
        }

        static SIXTRL_FN status_t GetDataPtrTypeSizes( size_type* )
        {
            return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
        }

        static SIXTRL_FN status_t GetDataPtrTypeCounts(
            const ObjData *const, size_type* )
        {
            return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
        }
    };

    template< class ObjData > static SIXTRL_FN constexpr ::NS(buffer_size_t)
    ObjData_get_num_data_ptrs()
    {
        return ObjDataStoreLayoutTraits< ObjData >::NumDataPtrs();
    }

    template< class ObjData > static SIXTRL_FN constexpr ::NS(buffer_size_t)
    ObjData_get_num_data_ptrs( ObjData const& )
    {
        return ObjDataStoreLayoutTraits< ObjData >::NumDataPtrs();
    }

    template< class ObjData > static SIXTRL_FN constexpr bool
    ObjData_has_data_ptrs()
    {
        return ( ObjDataStoreLayoutTraits<
            ObjData >::NumDataPtrs() != ::NS(buffer_size_t){ 0 } );
    }

    template< class ObjData > static SIXTRL_FN constexpr bool
    ObjData_has_data_ptrs( ObjData const& )
    {
        return ( ObjDataStoreLayoutTraits<
            ObjData >::NumDataPtrs() != ::NS(buffer_size_t){ 0 } );
    }

    template< class ObjData > static SIXTRL_FN constexpr bool
    ObjData_dataptr_type_count_can_vary()
    {
        return ObjDataStoreLayoutTraits< ObjData >::VarNumDataPtrCounts();
    }

    template< class ObjData > static SIXTRL_FN constexpr bool
    ObjData_dataptr_type_count_can_vary( ObjData const& )
    {
        return ObjDataStoreLayoutTraits< ObjData >::VarNumDataPtrCounts();
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    template< class ObjData > static SIXTRL_FN ::NS(arch_status_t)
    ObjDataStore_get_dataptr_type_offsets(
        ObjData const& SIXTRL_RESTRICT_REF,
        ::NS(buffer_size_t)* SIXTRL_RESTRICT offsets_begin )
    {
        return ObjDataStoreLayoutTraits<
            ObjData >::GetDataPtrTypeOffsets( offsets_begin );
    }

    template< class ObjData > static SIXTRL_FN ::NS(arch_status_t)
    ObjDataStore_get_dataptr_type_sizes(
        ObjData const& SIXTRL_RESTRICT_REF,
        ::NS(buffer_size_t)* SIXTRL_RESTRICT sizes_begin )
    {
        return ObjDataStoreLayoutTraits<
            ObjData >::GetDataPtrTypeSizes( sizes_begin );
    }

    template< class ObjData > static SIXTRL_FN ::NS(arch_status_t)
    ObjDataStore_get_dataptr_type_counts(
        ObjData const& SIXTRL_RESTRICT_REF obj_data,
        ::NS(buffer_size_t)* SIXTRL_RESTRICT counts_begin )
    {
        return ObjDataStoreLayoutTraits<
            ObjData >::GetDataPtrTypeCounts( &obj_data, counts_begin );
    }

    template< class ObjData > static SIXTRL_FN
    typename std::enable_if< !SIXTRL_CXX_NAMESPACE::ObjData_has_data_ptrs<
        ObjData >(), bool >::type Obj_can_store_on_buffer(
        const ::NS(Buffer) *const SIXTRL_RESTRICT_REF buffer,
        ::NS(object_type_id_t) const expected_base_object_type_id
            = SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_INVALID,
        const ObjData *const SIXTRL_RESTRICT_REF ptr_obj_data = nullptr,
        ::NS(buffer_size_t) native_size = ::NS(buffer_size_t){ 0 },
        ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_objects  = nullptr,
        ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_slots    = nullptr,
        ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_dataptrs = nullptr )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        bool can_be_stored = false;

        typedef ::NS(buffer_size_t) size_t;
        typedef ::NS(arch_status_t) status_t;
        typedef ::NS(object_type_id_t) obj_type_id_t;
        typedef st::ObjDataStoreTraits< ObjData > obj_type_traits_t;
        typedef st::ObjDataStoreLayoutTraits< ObjData > obj_traits_t;

        status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        obj_type_id_t obj_type_id = st::OBJECT_TYPE_INVALID;
        constexpr size_t num_dataptrs = obj_traits_t::NumDataPtrs();

        if( ( num_dataptrs == size_t{ 0 } ) &&
            ( ( ptr_obj_data != nullptr ) ||
              ( native_size >= sizeof( ObjData ) ) ) &&
            ( st::ObjData_can_be_stored_on_cobjects_buffer<
                ObjData >( buffer ) ) )
        {
            status = st::ARCH_STATUS_SUCCESS;
            obj_type_id = obj_type_traits_t::ObjTypeId();

            if( ( native_size == size_t{ 0 } ) &&
                ( ptr_obj_data != nullptr ) )
            {
                native_size = sizeof( *ptr_obj_data );
            }
        }

        if( ( status == st::ARCH_STATUS_SUCCESS ) &&
            ( obj_type_id != st::OBJECT_TYPE_INVALID ) &&
            ( native_size > size_t{ 0 } ) &&
            ( ( expected_base_object_type_id == st::OBJECT_TYPE_INVALID ) ||
              ( expected_base_object_type_id ==
                st::ObjectTypeId_get_base_type_id( obj_type_id ) ) ) )
        {
            static_assert( std::is_standard_layout< ObjData >::value,
                "Can only store ObjData classes which satisfy the "
                "std::is_standard_layout<> type trait; "
                "this type does not conform" );

            can_be_stored = ::NS(Buffer_can_add_object)( buffer, native_size,
                num_dataptrs, nullptr, nullptr, requ_num_objects,
                    requ_num_slots, requ_num_dataptrs );
        }

        return can_be_stored;
    }

    template< class ObjData >
    typename std::enable_if< SIXTRL_CXX_NAMESPACE::ObjData_has_data_ptrs<
        ObjData >(),
        bool >::type Obj_can_store_on_buffer(
        const ::NS(Buffer) *const SIXTRL_RESTRICT_REF buffer,
        ::NS(object_type_id_t) const expected_base_object_type_id
            = SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_INVALID,
        const ObjData *const SIXTRL_RESTRICT_REF ptr_obj_data = nullptr,
        ::NS(buffer_size_t) native_size = ::NS(buffer_size_t){ 0 },
        ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_objects  = nullptr,
        ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_slots    = nullptr,
        ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_dataptrs = nullptr )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        bool can_be_stored = false;

        typedef ::NS(buffer_size_t) size_t;
        typedef ::NS(arch_status_t) status_t;
        typedef ::NS(object_type_id_t) obj_type_id_t;
        typedef st::ObjDataStoreTraits< ObjData > obj_type_traits_t;
        typedef st::ObjDataStoreLayoutTraits< ObjData > obj_traits_t;

        status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        obj_type_id_t obj_type_id = st::OBJECT_TYPE_INVALID;
        constexpr size_t num_dataptrs = obj_traits_t::NumDataPtrs();

        size_t SIZES[  obj_traits_t::NumDataPtrs() ];
        size_t COUNTS[ obj_traits_t::NumDataPtrs() ];

        std::fill( &SIZES[ 0 ],  &SIZES[ num_dataptrs ],  size_t{ 0 } );
        std::fill( &COUNTS[ 0 ], &COUNTS[ num_dataptrs ], size_t{ 0 } );

        if( ( num_dataptrs == size_t{ 0 } ) &&
            ( ( ptr_obj_data != nullptr ) ||
              ( native_size >= sizeof( ObjData ) ) ) &&
            ( st::ObjData_can_be_stored_on_cobjects_buffer< ObjData >(
                buffer ) ) )
        {
            status = obj_traits_t::GetDataPtrTypeSizes( &SIZES[ 0 ] );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                status= obj_traits_t::GetDataPtrTypeOffsets( &COUNTS[ 0 ] );
            }

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                obj_type_id = obj_type_traits_t::ObjTypeId();
            }

            if( ( native_size == size_t{ 0 } ) &&
                ( ptr_obj_data != nullptr ) )
            {
                native_size = sizeof( *ptr_obj_data );
            }
        }

        if( ( status == st::ARCH_STATUS_SUCCESS ) &&
            ( obj_type_id != st::OBJECT_TYPE_INVALID ) &&
            ( native_size > size_t{ 0 } ) &&
            ( ( expected_base_object_type_id == st::OBJECT_TYPE_INVALID ) ||
              ( expected_base_object_type_id ==
                st::ObjectTypeId_get_base_type_id( obj_type_id ) ) ) )
        {
            static_assert( std::is_standard_layout< ObjData >::value,
                "Can only store ObjData classes which satisfy the "
                "std::is_standard_layout<> type trait; "
                "this type does not conform" );

            can_be_stored = ::NS(Buffer_can_add_object)( buffer, native_size,
                num_dataptrs, &SIZES[ 0 ], &COUNTS[ 0 ], requ_num_objects,
                    requ_num_slots, requ_num_dataptrs );
        }

        return can_be_stored;
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    template< class ObjData >
    static SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::ObjData_has_data_ptrs< ObjData >(),
        ::NS(Object)* >::type
    Obj_store_on_buffer(
        ::NS(Buffer)* SIXTRL_RESTRICT buffer,
        ::NS(object_type_id_t) const expected_base_object_type_id
            = SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_INVALID,
        const ObjData *const SIXTRL_RESTRICT_REF ptr_obj_data = nullptr,
        ::NS(buffer_size_t) native_size = ::NS(buffer_size_t){ 0 } )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        ::NS(Object)* ptr_obj_info = nullptr;

        typedef ::NS(buffer_size_t) size_t;
        typedef ::NS(arch_status_t) status_t;
        typedef ::NS(object_type_id_t) obj_type_id_t;
        typedef st::ObjDataStoreTraits< ObjData > obj_type_traits_t;
        typedef st::ObjDataStoreLayoutTraits< ObjData > obj_traits_t;

        status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        obj_type_id_t obj_type_id = st::OBJECT_TYPE_INVALID;
        constexpr size_t num_dataptrs = obj_traits_t::NumDataPtrs();

        if( ( ptr_obj_data != nullptr ) && ( num_dataptrs == size_t{ 0 } ) &&
            ( ( native_size == size_t{ 0 } ) ||
              ( native_size >= sizeof( *ptr_obj_data ) ) ) &&
            ( st::ObjData_can_be_stored_on_cobjects_buffer< ObjData >(
                buffer ) ) )
        {
            status = st::ARCH_STATUS_SUCCESS;
            obj_type_id = obj_type_traits_t::ObjTypeId();

            if( native_size == size_t{ 0 } )
                native_size = sizeof( *ptr_obj_data );
        }

        if( ( status == st::ARCH_STATUS_SUCCESS ) &&
            ( obj_type_id != st::OBJECT_TYPE_INVALID ) &&
            ( native_size > size_t{ 0 } ) &&
            ( ( expected_base_object_type_id == st::OBJECT_TYPE_INVALID ) ||
              ( expected_base_object_type_id ==
                st::ObjectTypeId_get_base_type_id( obj_type_id ) ) ) )
        {
            static_assert( std::is_standard_layout< ObjData >::value,
                "Can only store ObjData classes which satisfy the "
                "std::is_standard_layout<> type trait; "
                "this type does not conform" );

            ptr_obj_info = ::NS(Buffer_add_object)( buffer, ptr_obj_data,
                native_size, obj_type_id, num_dataptrs,
                    nullptr, nullptr, nullptr );
        }

        return ptr_obj_info;
    }

    template< class ObjData >
    static SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ObjData_has_data_ptrs< ObjData >(),
        ::NS(Object)* >::type
    Obj_store_on_buffer(
        ::NS(Buffer)* SIXTRL_RESTRICT buffer,
        ::NS(object_type_id_t) const expected_base_object_type_id
            = SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_INVALID,
        const ObjData *const SIXTRL_RESTRICT_REF ptr_obj_data = nullptr,
        ::NS(buffer_size_t) native_size = ::NS(buffer_size_t){ 0 } )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        ::NS(Object)* ptr_obj_info = nullptr;

        typedef ::NS(buffer_size_t) size_t;
        typedef ::NS(arch_status_t) status_t;
        typedef ::NS(object_type_id_t) obj_type_id_t;
        typedef st::ObjDataStoreTraits< ObjData > obj_type_traits_t;
        typedef st::ObjDataStoreLayoutTraits< ObjData > obj_traits_t;

        status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        obj_type_id_t obj_type_id = st::OBJECT_TYPE_INVALID;
        constexpr size_t num_dataptrs = obj_traits_t::NumDataPtrs();

        size_t OFFSETS[ obj_traits_t::NumDataPtrs() ];
        size_t SIZES[   obj_traits_t::NumDataPtrs() ];
        size_t COUNTS[  obj_traits_t::NumDataPtrs() ];

        std::fill( &OFFSETS[ 0 ], &OFFSETS[ num_dataptrs ], size_t{ 0 } );
        std::fill( &SIZES[ 0 ],   &SIZES[   num_dataptrs ], size_t{ 0 } );
        std::fill( &COUNTS[ 0 ],  &COUNTS[  num_dataptrs ], size_t{ 0 } );

        if( ( ptr_obj_data != nullptr ) && ( num_dataptrs > size_t{ 0 } ) &&
            ( ( native_size == size_t{ 0 } ) ||
              ( native_size >= sizeof( *ptr_obj_data ) ) ) &&
            ( st::ObjData_can_be_stored_on_cobjects_buffer<
                ObjData >( buffer ) ) )
        {
            status = obj_traits_t::GetDataPtrTypeOffsets( &OFFSETS[ 0 ] );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                status = obj_traits_t::GetDataPtrTypeSizes( &SIZES[ 0 ] );
            }

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                status = obj_traits_t::GetDataPtrTypeCounts(
                    ptr_obj_data, &COUNTS[ 0 ] );
            }

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                obj_type_id = obj_type_traits_t::ObjTypeId();
            }

            if( native_size == size_t{ 0 } )
            {
                native_size = sizeof( *ptr_obj_data );
            }
        }

        if( ( status == st::ARCH_STATUS_SUCCESS ) &&
            ( obj_type_id != st::OBJECT_TYPE_INVALID ) &&
            ( native_size > size_t{ 0 } ) &&
            ( ( expected_base_object_type_id == st::OBJECT_TYPE_INVALID ) ||
              ( expected_base_object_type_id ==
                st::ObjectTypeId_get_base_type_id( obj_type_id ) ) ) )
        {
            static_assert( std::is_standard_layout< ObjData >::value,
                "Can only store ObjData classes which satisfy the "
                "std::is_standard_layout<> type trait; "
                "this type does not conform" );

            ptr_obj_info = ::NS(Buffer_add_object)( buffer, ptr_obj_data,
                native_size, obj_type_id, num_dataptrs, &OFFSETS[ 0 ],
                    &SIZES[ 0 ], &COUNTS[ 0 ] );
        }

        return ptr_obj_info;
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    template< class RestoreObj >
    SIXTRL_FN RestoreObj const* ObjStore_get_ptr_const_obj_from_info(
        const ::NS(Object) *const SIXTRL_RESTRICT ptr_obj_info,
        ::NS(object_type_id_t) const expected_obj_type_id )
    {
        ::NS(object_type_id_t) const obj_type_id =
            ::NS(Object_get_type_id)( ptr_obj_info );

        if( ( obj_type_id == expected_obj_type_id ) &&
            ( obj_type_id != SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_INVALID ) )
        {
            return reinterpret_cast< RestoreObj const* >(
                ::NS(Object_get_begin_addr)( ptr_obj_info ) );
        }

        return nullptr;
    }

    template< class RestoreObj >
    SIXTRL_FN RestoreObj* ObjStore_get_ptr_obj_from_info(
        ::NS(Object)* SIXTRL_RESTRICT ptr_obj_info,
        ::NS(object_type_id_t) const expected_obj_type_id )
    {
        return const_cast< RestoreObj* >(
            ObjStore_get_ptr_const_obj_from_info< RestoreObj >(
                ptr_obj_info, expected_obj_type_id ) );
    }
}

#endif /* SIXTRACKLIB_COMMON_INTERNAL_OBJ_STORE_TRAITS_CXX_HPP__ */
/* end: cxx/common/internal/obj_store_traits.hpp */
