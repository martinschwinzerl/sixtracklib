#ifndef SIXTRACKLIB_COMMON_INTERNAL_OBJ_STORE_TRAITS_CXX_HPP__
#define SIXTRACKLIB_COMMON_INTERNAL_OBJ_STORE_TRAITS_CXX_HPP__

#if defined( __cplusplus )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <algorithm>
    #include <cstdlib>
    #include <type_traits>

    #if !defined( _GPUCODE )
        #include <vector>
    #endif /* !defiend( _GPUCODE ) */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/buffer/buffer.h"
    #include "sixtracklib/common/buffer/buffer.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template< class ObjData >
    struct ObjDataTypeTraits
    {
        typedef SIXTRL_CXX_NAMESPACE::object_type_id_t type_id_t;

        static SIXTRL_FN constexpr type_id_t ObjTypeId() SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_ILLEGAL;
        }
    };

    /* --------------------------------------------------------------------- */

    template< class ObjData >
    struct ObjDataStoreCApiTraits { typedef void c_api_t; };

    template< class ObjData >
    SIXTRL_FN SIXTRL_INLINE constexpr bool
    ObjData_is_convertible_to_capi() SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename st::ObjDataStoreCApiTraits<
            ObjData >::c_api_t _c_api_t;

        return ( ( !std::is_void< _c_api_t >::value ) &&
                 (  std::is_standard_layout< _c_api_t > ) );
    }

    template< class ObjData > SIXTRL_FN constexpr bool
    ObjData_is_not_convertible_to_capi() SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return !st::ObjData_is_convertible_to_capi< ObjData >();
    }

    /* --------------------------------------------------------------------- */

    template< class ObjData >
    struct ObjDataStoreConstructTraits
    {
        static SIXTRL_FN constexpr bool CanBeMemCopied() SIXTRL_NOEXCEPT
        {
            return std::is_trivially_copyable< ObjData >::value;
        }
    };

    /* --------------------------------------------------------------------- */

    template< class ObjData >
    struct ObjDataStoreCObjectsTraits
    {
        typedef SIXTRL_CXX_NAMESPACE::buffer_size_t size_type;

        typedef SIXTRL_CXX_NAMESPACE::ObjDataStoreTraits< ObjData >
                _store_traits_t;

        typedef SIXTRL_CXX_NAMESPACE::ObjDataStoreConstructTraits< ObjData >
                _construct_traits_t;

        static SIXTRL_FN constexpr size_type StorageAlign() SIXTRL_NOEXCEPT
        {
            return static_cast< size_type >( SIXTRL_ALIGN_NUM );
        }

        static SIXTRL_FN constexpr bool CanBeStoredOnCBuffer() SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;

            return ( ( std::is_standard_layout< ObjData >::value ) &&
                ( _store_traits_t::ObjTypeId() != st::OBJECT_TYPE_ILLEGAL ) &&
                ( _construct_traits::CanBeMemCopied() ) );
        }
    };

    template< class ObjData > SIXTRL_FN constexpr bool
    ObjDataStore_can_be_stored_on_cobjects_buffer() SIXTRL_NOEXCEPT
    {
        typedef SIXTRL_CXX_NAMESPACE::ObjDataStoreCObjectsTraits< ObjData >
                _traits_t;

        return _traits_t::CanBeStoredOnCBuffer();
    }

    template< class ObjData >
    SIXTRL_FN bool ObjDataStore_can_be_stored_on_cobjects_buffer(
        const ::NS(Buffer) *const SIXTRL_RESTRICT buffer ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef st::ObjDataStoreCObjectsTraits< ObjData > _traits_t;
        typedef typename _traits_t::size_type _size_t;

        _size_t const slot_size = ::NS(Buffer_get_slot_size)( buffer );
        _size_t const alignment = _traits_t::StorageAlign();

        return ( ( slot_size > _size_t{ 0 } ) &&
                 ( _traits_t::CanBeStoredOnAnyCObjectsBuffer() ) &&
                 ( ( slot_size == _size_t{ 1 } ) ||
                   ( ( slot_size <= alignment ) &&
                   ( ( alignment % slot_size ) == _size_t{ 0 } ) ) ||
                   ( slot_size > alignment )
                 ) );
    }

    template< class ObjData >
    SIXTRL_FN bool ObjDataStore_can_be_stored_on_cobjects_buffer(
        SIXTRL_CXX_NAMESPACE::Buffer const&
            SIXTRL_RESTRICT_REF buffer ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return st::ObjDataStore_can_be_stored_on_cobjects_buffer< ObjData >(
            buffer.getCApiPtr() );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_FN SIXTRL_CXX_NAMESPACE::object_type_id_t
    ObjectTypeId_add_special_variant(
        SIXTRL_CXX_NAMESPACE::object_type_id_t const obj_type_id,
        SIXTRL_CXX_NAMESPACE::object_type_id_t const var_flag ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef st::object_type_id_t type_id_t;

        constexpr type_id_t VARIANT_FLAG_MASK =
            static_cast< type_id_t >( 0x0000ffff );

        constexpr type_id_t VARIANT_SHIFT_BITS =
            static_cast< type_id_t >( 4u );

        return ( obj_type_id & VARIANT_FLAG_MASK ) |
               ( ( var_flag & VARIANT_FLAG_MASK ) << VARIANT_SHIFT_BITS );
    }

    SIXTRL_FN bool ObjectTypeId_is_special_type_id(
        SIXTRL_CXX_NAMESPACE::object_type_id_t const obj_type_id )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef st::obj_type_id_t type_id_t;

        constexpr type_id_t SPECIAL_VARIANT_MASK =
            static_cast< type_id_t >( 0xffff0000 );

        constexpr type_id_t NOT_SPECIAL = static_cast< type_id_t >( 0 );
        return ( ( obj_type_id & SPECIAL_VARIANT_MASK ) != NOT_SPECIAL );
    }

    SIXTRL_FN SIXTRL_CXX_NAMESPACE::object_type_id_t
    ObjectTypeId_get_base_type_id(
        SIXTRL_CXX_NAMESPACE::object_type_id_t const obj_type_id )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef st::object_type_id_t type_id_t;

        constexpr type_id_t BASE_VARIANT_MASK =
            static_cast< type_id_t >( 0x0000ffff );

        return ( obj_type_id & BASE_VARIANT_MASK );
    }

    SIXTRL_FN SIXTRL_CXX_NAMESPACE::object_type_id_t
    ObjectTypeId_get_variant_flag(
        SIXTRL_FN SIXTRL_CXX_NAMESPACE::object_type_id_t const obj_type_id )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef st::object_type_id_t type_id_t;

        constexpr type_id_t VARIANT_FLAG_MASK =
            static_cast< type_id_t >( 0xffff0000 );

        constexpr type_id_t VARIANT_SHIFT_BITS =
            static_cast< type_id_t >( 4u );

        return ( obj_type_id & VARIANT_FLAG_MASK ) >> VARIANT_SHIFT_BITS;
    }

    /* --------------------------------------------------------------------- */

    template< class ObjData >
    struct ObjDataStoreDataPtrsTraits
    {
        typedef SIXTRL_CXX_NAMESPACE::buffer_size_t size_type;

        static SIXTRL_FN constexpr size_type MinNumDataPtrs() SIXTRL_NOEXCEPT
        {
            return static_cast< size_type >( 0 );
        }

        static SIXTRL_FN constexpr size_type MaxNumDataPtrs() SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            return st::ObjDataStoreDataPtrsTraits< ObjData >::MinNumDataPtrs();
        }
    };

    template< class ObjData >
    SIXTRL_FN constexpr bool ObjDataStore_has_dataptrs() SIXTRL_NOEXCEPT
    {
        typedef SIXTRL_CXX_NAMESPACE::ObjDataStoreDataPtrsTraits< ObjData >
                _traits_t;

        static_assert( _traits_t::MaxNumDataPtrs() >=
            _traits_t::MinNumDataPtrs(), "inconsistent num dataptrs" );

        return ( _traits_t::MaxNumDataPtrs() >
            static_cast< typename _traits_t::size_type >( 0 ) );
    }

    template< class ObjData >
    SIXTRL_FN constexpr bool ObjDataStore_has_no_dataptrs() SIXTRL_NOEXCEPT
    {
        typedef SIXTRL_CXX_NAMESPACE::ObjDataStoreDataPtrsTraits< ObjData >
                _traits_t;

        static_assert( _traits_t::MaxNumDataPtrs() >=
            _traits_t::MinNumDataPtrs(), "inconsistent num dataptrs" );

        return ( _traits_t::MaxNumDataPtrs() ==
            static_cast< typename _traits_t::size_type >( 0 ) );
    }

    template< class ObjData >
    SIXTRL_FN constexpr bool ObjDataStore_has_var_num_dataptrs() SIXTRL_NOEXCEPT
    {
        typedef SIXTRL_CXX_NAMESPACE::ObjDataStoreDataPtrsTraits< ObjData >
                _traits_t;

        static_assert( _traits_t::MaxNumDataPtrs() >=
            _traits_t::MinNumDataPtrs(), "inconsistent num dataptrs" );

        return ( _traits_t::MaxNumDataPtrs() != _traits_t::MinNumDataPtrs() );
    }

    template< class ObjData >
    SIXTRL_FN constexpr bool ObjDataStore_has_const_num_dataptrs() SIXTRL_NOEXCEPT
    {
        typedef SIXTRL_CXX_NAMESPACE::ObjDataStoreDataPtrsTraits< ObjData >
                _traits_t;

        static_assert( _traits_t::MaxNumDataPtrs() >=
            _traits_t::MinNumDataPtrs(), "inconsistent num dataptrs" );

        return ( _traits_t::MaxNumDataPtrs() == _traits_t::MinNumDataPtrs() );
    }

    /* --------------------------------------------------------------------- */

    template< class ObjData >
    static SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
    ObjDataStore_init_layout_param(
        SIXTRL_CXX_NAMESPACE::buffer_size_t* SIXTRL_RESTRICT param_begin,
        SIXTRL_CXX_NAMESPACE::buffer_size_t const num_param ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef st::buffer_size_t _size_t;
        typedef st::ObjDataStoreDataPtrsTraits< ObjData > _traits_t;

        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( param_begin != nullptr ) && ( num_param >= _size_t{ 0 } ) )
        {
            constexpr _size_t ZERO = _size_t{ 0 };
            SIXTRACKLIB_SET_VALUES( _size_t, param_begin, num_param, ZERO );

            std::fill( param_begin, param_begin + num_param, _size_t{ 0 } );

            if( num_param >= _traits_t::MaxNumDataPtrs() )
            {
                status = st::ARCH_STATUS_SUCCESS;
            }
        }

        return status;
    }

    template< class ObjData >
    struct ObjDataStoreLayoutTraits
    {
        typedef SIXTRL_CXX_NAMESPACE::buffer_size_t size_type;
        typedef SIXTRL_CXX_NAMESPACE::arch_status_t status_t;

        /* ----------------------------------------------------------------- */
        /* SFINAE: Provide default implementations for ObjData without
         *         dataptrs, or with const number of dataptrs (if possible).
         *         This should work out of the box for most DataObj and thus
         *         simplifies things considerably */

        static SIXTRL_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::ObjDataStore_has_const_num_dataptrs< ObjData >(),
                size_type >::type
        GetNumDataPtrs( const ObjData *const data = nullptr ) SIXTRL_NOEXCEPT
        {
            typedef SIXTRL_CXX_NAMESPACE::ObjDataStoreDataPtrsTraits< ObjData >
                    _traits_t;

            static_assert(
                _traits_t::MaxNumDataPtrs() == _traits_t::MinNumDataPtrs(),
                "inconsistent num dataptrs!!" );

            ( void )data;
            return _traits_t::MaxNumDataPtrs();
        }

        static SIXTRL_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::ObjDataStore_has_no_dataptrs< ObjData >(),
                status_t >::type
        GetDataPtrOffsets(
            size_type* SIXTRL_RESTRICT param_begin,
            size_type const max_num_param,
            const ObjData *const obj_data = nullptr ) SIXTRL_NOEXCEPT
        {
            SIXTRL_CXX_NAMESPACE::ObjDataStore_init_layout_param< ObjData >(
                param_begin, max_num_param );

            ( void )obj_data;
            return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
        }

        static SIXTRL_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::ObjDataStore_has_no_dataptrs< ObjData >(),
                status_t >::type
        GetDataPtrSizes(
            size_type* SIXTRL_RESTRICT param_begin,
            size_type const max_num_param,
            const ObjData *const obj_data = nullptr ) SIXTRL_NOEXCEPT
        {
            SIXTRL_CXX_NAMESPACE::ObjDataStore_init_layout_param< ObjData >(
                param_begin, max_num_param );

            ( void )obj_data;
            return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
        }

        static SIXTRL_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::ObjDataStore_has_no_dataptrs< ObjData >(),
                status_t >::type
        GetDataPtrCounts(
            size_type* SIXTRL_RESTRICT param_begin,
            size_type const max_num_param,
            const ObjData *const obj_data = nullptr ) SIXTRL_NOEXCEPT
        {
            SIXTRL_CXX_NAMESPACE::ObjDataStore_init_layout_param< ObjData >(
                param_begin, max_num_param );

            ( void )obj_data;
            return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
        }

        /* ----------------------------------------------------------------- */
        /* SFINAE: Implemenatons for the cases where explicit specialization of
         *         the traits is needed -> try to return an error, trigger an
         *         static assert or something nonsensical */

        static SIXTRL_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::ObjDataStore_has_var_num_dataptrs< ObjData >(),
                size_type >::type
        GetNumDataPtrs( const ObjData *const data = nullptr ) SIXTRL_NOEXCEPT
        {
            typedef SIXTRL_CXX_NAMESPACE::ObjDataStoreDataPtrsTraits< ObjData >
                    _traits_t;

            static_assert(
                _traits_t::MaxNumDataPtrs() == _traits_t::MinNumDataPtrs(),
                "Can not provide this number for a variable number of dataptrs type -> "
                "specialize ObjDataStoreLayoutTraits<> for this ObjData type!" );

            /* Should never get here */
            ( void )data;
            return _traits_t::MaxNumDataPtrs();
        }

        static SIXTRL_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::ObjDataStore_has_dataptrs< ObjData >(),
                status_t >::type
        GetDataPtrOffsets(
            size_type* SIXTRL_RESTRICT param_begin,
            size_type const max_num_param,
            const ObjData *const data = nullptr ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            typedef st::size_type _size_t;
            typedef st::ObjDataStoreDataPtrsTraits< ObjData > _traits_t;

            static_assert( _traits_t::MaxNumDataPtrs() == _size_t{ 0 },
                "Can't automatically deduce offsets for ObjData -> "
                "specialize ObjDataStoreLayoutTraits<> for this ObjData type!" )

            /* should never get here */
            st::ObjDataStore_init_layout_param< ObjData >(
                param_begin, max_num_param );

            ( void )data;
            return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
        }

        static SIXTRL_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::ObjDataStore_has_dataptrs< ObjData >(),
                status_t >::type
        GetDataPtrSizes(
            size_type* SIXTRL_RESTRICT param_begin,
            size_type const max_num_param,
            const ObjData *const obj_data = nullptr ) SIXTRL_NOEXCEPT
        {
            typedef SIXTRL_CXX_NAMESPACE::size_type _size_t;
            typedef SIXTRL_CXX_NAMESPACE::ObjDataStoreDataPtrsTraits< ObjData >
                    _traits_t;

            static_assert( _traits_t::MaxNumDataPtrs() == _size_t{ 0 },
                "Can't automatically deduce sizes for ObjData -> "
                "specialize ObjDataStoreLayoutTraits<> for this ObjData type!" )

            /* should never get here */
            st::ObjDataStore_init_layout_param< ObjData >(
                param_begin, max_num_param );

            ( void )data;
            return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
        }

        static SIXTRL_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::ObjDataStore_has_dataptrs< ObjData >(),
                status_t >::type
        GetDataPtrCounts(
            size_type* SIXTRL_RESTRICT param_begin,
            size_type const max_num_param,
            const ObjData *const obj_data = nullptr ) SIXTRL_NOEXCEPT
        {
            typedef SIXTRL_CXX_NAMESPACE::size_type _size_t;
            typedef SIXTRL_CXX_NAMESPACE::ObjDataStoreDataPtrsTraits< ObjData >
                    _traits_t;

            static_assert( _traits_t::MaxNumDataPtrs() == _size_t{ 0 },
                "Can't automatically deduce counts for ObjData -> "
                "specialize ObjDataStoreLayoutTraits<> for this ObjData type!" )

            /* should never get here */
            st::ObjDataStore_init_layout_param< ObjData >(
                param_begin, max_num_param );

            ( void )data;
            return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
        }
    };

    template< class ObjData >
    static SIXTRL_FN constexpr typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ObjDataStore_has_const_num_dataptrs< ObjData >(),
        SIXTRL_CXX_NAMESPACE::buffer_size_t >::type
    ObjDataStore_num_data_ptrs(
        const ObjData *const SIXTRL_RESRTRICT data ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef st::ObjDataStoreDataPtrsTraits< ObjData > _traits_t;

        static_assert(
            _traits_t::MaxNumDataPtrs() == _traits_t::MinNumDataPtrs(),
            "inconsistent num dataptrs" );

        ( void )data;
        return _traits_t::MaxNumDataPtrs();
    }

    template< class ObjData >
    static SIXTRL_FN constexpr typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ObjDataStore_has_const_num_dataptrs< ObjData >(),
        SIXTRL_CXX_NAMESPACE::buffer_size_t >::type
    ObjDataStore_num_data_ptrs(
        ObjData const& SIXTRL_RESRTRICT_REF data ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef st::ObjDataStoreDataPtrsTraits< ObjData > _traits_t;

        static_assert(
            _traits_t::MaxNumDataPtrs() == _traits_t::MinNumDataPtrs(),
            "inconsistent num dataptrs" );

        ( void )data;
        return _traits_t::MaxNumDataPtrs();
    }

    template< class ObjData >
    static SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ObjDataStore_has_var_num_dataptrs< ObjData >(),
        SIXTRL_CXX_NAMESPACE::buffer_size_t >::type
    ObjDataStore_num_data_ptrs(
        const ObjData *const SIXTRL_RESRTRICT data ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ObjDataStoreDataPtrsTraits<
            ObjData >::GetNumDataPtrs( data );
    }

    template< class ObjData >
    static SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ObjDataStore_has_var_num_dataptrs< ObjData >(),
        SIXTRL_CXX_NAMESPACE::buffer_size_t >::type
    ObjDataStore_num_data_ptrs(
        ObjData const& SIXTRL_RESRTRICT_REF data ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ObjDataStoreDataPtrsTraits<
            ObjData >::GetNumDataPtrs( &data );
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    template< class ObjData >
    static SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
    ObjDataStore_dataptr_offsets(
        SIXTRL_CXX_NAMESPACE::buffer_size_t* SIXTRL_RESTRICT param_begin,
        SIXTRL_CXX_NAMESPACE::buffer_size_t const max_num_param,
        const ObjData *const SIXTRL_RESTRICT data )
    {
        return SIXTRL_CXX_NAMESPACE::ObjDataStoreLayoutTraits<
            ObjData >::GetDataPtrOffsets( param_begin, max_num_param, data );
    }

    template< class ObjData >
    static SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
    ObjDataStore_dataptr_offsets(
        SIXTRL_CXX_NAMESPACE::buffer_size_t* SIXTRL_RESTRICT param_begin,
        SIXTRL_CXX_NAMESPACE::buffer_size_t const max_num_param,
        ObjData const& SIXTRL_RESTRICT data )
    {
        return SIXTRL_CXX_NAMESPACE::ObjDataStoreLayoutTraits<
            ObjData >::GetDataPtrOffsets( param_begin, max_num_param, &data );
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    template< class ObjData >
    static SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
    ObjDataStore_dataptr_sizes(
        SIXTRL_CXX_NAMESPACE::buffer_size_t* SIXTRL_RESTRICT param_begin,
        SIXTRL_CXX_NAMESPACE::buffer_size_t const max_num_param,
        const ObjData *const SIXTRL_RESTRICT data )
    {
        return SIXTRL_CXX_NAMESPACE::ObjDataStoreLayoutTraits<
            ObjData >::GetDataPtrSizes( param_begin, max_num_param, data );
    }

    template< class ObjData >
    static SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
    ObjDataStore_dataptr_sizes(
        SIXTRL_CXX_NAMESPACE::buffer_size_t* SIXTRL_RESTRICT param_begin,
        SIXTRL_CXX_NAMESPACE::buffer_size_t const max_num_param,
        ObjData const& SIXTRL_RESTRICT data )
    {
        return SIXTRL_CXX_NAMESPACE::ObjDataStoreLayoutTraits<
            ObjData >::GetDataPtrSizes( param_begin, max_num_param, &data );
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    template< class ObjData >
    static SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
    ObjDataStore_dataptr_counts(
        SIXTRL_CXX_NAMESPACE::buffer_size_t* SIXTRL_RESTRICT param_begin,
        SIXTRL_CXX_NAMESPACE::buffer_size_t const max_num_param,
        const ObjData *const SIXTRL_RESTRICT data )
    {
        return SIXTRL_CXX_NAMESPACE::ObjDataStoreLayoutTraits<
            ObjData >::GetDataPtrCounts( param_begin, max_num_param, data );
    }

    template< class ObjData >
    static SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
    ObjDataStore_dataptr_counts(
        SIXTRL_CXX_NAMESPACE::buffer_size_t* SIXTRL_RESTRICT param_begin,
        SIXTRL_CXX_NAMESPACE::buffer_size_t const max_num_param,
        ObjData const& SIXTRL_RESTRICT data )
    {
        return SIXTRL_CXX_NAMESPACE::ObjDataStoreLayoutTraits<
            ObjData >::GetDataPtrCounts( param_begin, max_num_param, &data );
    }

    # if !defined( _GPUCODE )
    /* --------------------------------------------------------------------- */
    /* ObjData_can_store_on_buffer: */

    template< class ObjData >
    static SIXTRL_HOST_FN std::enable_if<
        SIXTRL_CXX_NAMESPACE::ObjDataStore_has_no_dataptrs< ObjData >() &&
        SIXTRL_CXX_NAMESPACE::ObjDataStore_can_be_stored_on_cobjects_buffer<
            ObjData >(), bool >::type
    ObjData_can_store_on_buffer(
        const ::NS(Buffer) *const SIXTRL_RESTRICT buffer,
        ::NS(object_type_id_t) const expected_base_type_id =
            SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_ILLEGAL,
        const ObjData *const SIXTRL_RESTRICT ptr_obj_data = nullptr,
        ::NS(buffer_size_t) native_size = ::NS(buffer_size_t){ 0 },
        ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_objects = nullptr,
        ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_slots = nullptr,
        ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_dataptrs = nullptr
    ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        typedef st::object_type_id_t    _type_id_t;
        typedef st::buffer_size_t       _size_t;

        bool can_be_stored = false;

        /* Can only store objects which have a standard layout! */
        if( !std::is_standard_layout< ObjData >::value )
        {
            return can_be_stored;
        }

        constexpr _size_t num_dataptrs =
            st::ObjDataStoreDataPtrsTraits< ObjData >::MaxNumDataPtrs();

        static_assert( num_dataptrs == _size_t{ 0 },
                       "inconsistent num dataptrs" );

        _type_id_t const obj_type_id =
            st::ObjDataStoreTraits< ObjData >::ObjTypeId();

        _type_id_t const base_obj_type_id =
            st::ObjectTypeId_get_base_type_id( obj_type_id );

        if( ( obj_type_id != st::OBJECT_TYPE_ILLEGAL ) &&
            ( ( native_size >= sizeof( ObjData ) ) ||
              ( ptr_data_obj != nullptr ) ) &&
            ( ( expected_base_object_type_id == st::OBJECT_TYPE_ILLEGAL ) ||
              ( expected_base_object_type_id == base_obj_type_id ) ) &&
            ( st::ObjDataStore_can_be_stored_on_cobjects_buffer<
                ObjData >( buffer ) ) )
        {
            if( ( native_size == _size_t{ 0 } ) &&
                ( ptr_obj_data != nullptr ) )
            {
                native_size = sizeof( *ptr_obj_data );
            }

            can_be_stored = ::NS(Buffer_can_add_object)(
                buffer, native_size, num_dataptrs, nullptr, nullptr,
                    requ_num_objects, requ_num_slots, requ_num_dataptrs );
        }

        return can_be_stored;
    }

    template< class ObjData >
    static SIXTRL_HOST_FN std::enable_if<
        SIXTRL_CXX_NAMESPACE::ObjDataStore_has_dataptrs< ObjData >() &&
        SIXTRL_CXX_NAMESPACE::ObjDataStore_has_const_num_dataptrs< ObjData >() &&
        SIXTRL_CXX_NAMESPACE::ObjDataStore_can_be_stored_on_cobjects_buffer<
            ObjData >(), bool >::type
    ObjData_can_store_on_buffer(
        const ::NS(Buffer) *const SIXTRL_RESTRICT buffer,
        ::NS(object_type_id_t) const expected_base_type_id =
            SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_ILLEGAL,
        const ObjData *const SIXTRL_RESTRICT ptr_obj_data = nullptr,
        ::NS(buffer_size_t) native_size = ::NS(buffer_size_t){ 0 },
        ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_objects = nullptr,
        ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_slots = nullptr,
        ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_dataptrs = nullptr
    ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        typedef st::object_type_id_t    _type_id_t;
        typedef st::buffer_size_t       _size_t;

        bool can_be_stored = false;

        /* Can only store objects which have a standard layout! */
        if( !std::is_standard_layout< ObjData >::value )
        {
            return can_be_stored;
        }

        constexpr _size_t num_dataptrs =
            st::ObjDataStoreDataPtrsTraits< ObjData >::MaxNumDataPtrs();

        static_assert( num_dataptrs ==
            st::ObjDataStoreDataPtrsTraits< ObjData >::MinNumDataPtrs(),
            "min and max number of dataptrs disagreee -> inconsistent!" );

        static_assert( num_dataptrs > _size_t{ 0 },
            "max number of dataptrs required to be > 0" );

        _type_id_t const obj_type_id =
            st::ObjDataStoreTraits< ObjData >::ObjTypeId();

        _type_id_t const base_obj_type_id =
            st::ObjectTypeId_get_base_type_id( obj_type_id );

        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        _size_t sizes[ num_dataptrs ];
        _size_t counts[ num_dataptrs ];

        if( ( obj_type_id != st::OBJECT_TYPE_ILLEGAL ) &&
            ( ( native_size >= sizeof( ObjData ) ) ||
              ( ptr_data_obj != nullptr ) ) &&
            ( ( expected_base_object_type_id == st::OBJECT_TYPE_ILLEGAL ) ||
              ( expected_base_object_type_id == base_obj_type_id ) ) &&
            ( st::ObjDataStore_can_be_stored_on_cobjects_buffer<
                ObjData >( buffer ) ) )
        {
            status = st::ObjDataStoreLayoutTraits< ObjData >::GetDataPtrSizes(
                &sizes[ 0 ], num_dataptrs, ptr_data_obj );
        }

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            status = st::ObjDataStoreLayoutTraits< ObjData >::GetDataPtrCounts(
                &counts[ 0 ], num_dataptrs, ptr_data_obj );
        }

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            if( ( native_size == _size_t{ 0 } ) &&
                ( ptr_obj_data != nullptr ) )
            {
                native_size = sizeof( *ptr_obj_data );
            }

            can_be_stored = ::NS(Buffer_can_add_object)(
                buffer, native_size, num_dataptrs, &sizes[ 0 ], &counts[ 0 ],
                    requ_num_objects, requ_num_slots, requ_num_dataptrs );
        }

        return can_be_stored;
    }

    template< class ObjData >
    static SIXTRL_HOST_FN std::enable_if<
        SIXTRL_CXX_NAMESPACE::ObjDataStore_has_dataptrs< ObjData >() &&
        SIXTRL_CXX_NAMESPACE::ObjDataStore_has_var_num_dataptrs< ObjData >() &&
        SIXTRL_CXX_NAMESPACE::ObjDataStore_can_be_stored_on_cobjects_buffer<
            ObjData >(), bool >::type
    ObjData_can_store_on_buffer(
        const ::NS(Buffer) *const SIXTRL_RESTRICT buffer,
        SIXTRL_CXX_NAMESPACE::object_type_id_t const expected_base_type_id =
            SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_ILLEGAL,
        const ObjData *const SIXTRL_RESTRICT ptr_obj_data = nullptr,
        ::NS(buffer_size_t) native_size = ::NS(buffer_size_t){ 0 },
        ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_objects = nullptr,
        ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_slots = nullptr,
        ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_dataptrs = nullptr
    ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        typedef st::object_type_id_t    _type_id_t;
        typedef st::buffer_size_t       _size_t;

        bool can_be_stored = false;

        /* Can only store objects which have a standard layout! */
        if( !std::is_standard_layout< ObjData >::value )
        {
            return can_be_stored;
        }

        /* var num dataptrs ->
         * we need an instance to determine the paramters! */
        if( ptr_obj_data == nullptr )
        {
            return can_be_stored;
        }

        _size_t const num_dataptrs =
            st::ObjDataStore_num_data_ptrs( ptr_obj_data );

        SIXTRL_ASSERT( num_dataptrs >=
            st::ObjDataStoreDataPtrsTraits< ObjData >::MinNumDataPtrs() );

        SIXTRL_ASSERT( num_dataptrs <=
            st::ObjDataStoreDataPtrsTraits< ObjData >::MaxNumDataPtrs() );

        _type_id_t const obj_type_id =
            st::ObjDataStoreTraits< ObjData >::ObjTypeId();

        _type_id_t const base_obj_type_id =
            st::ObjectTypeId_get_base_type_id( obj_type_id );

        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        _size_t const dummy_num_dataptrs = ( num_dataptrs > _size_t{ 0 } )
            ? num_dataptrs : _size_t{ 1 };

        std::vector< _size_t > sizes( dummy_num_dataptrs );
        std::vector< _size_t > counts( dummy_num_dataptrs );

        if( ( obj_type_id != st::OBJECT_TYPE_ILLEGAL ) &&
            ( ( native_size >= sizeof( ObjData ) ) ||
              ( ptr_data_obj != nullptr ) ) &&
            ( ( expected_base_object_type_id == st::OBJECT_TYPE_ILLEGAL ) ||
              ( expected_base_object_type_id == base_obj_type_id ) ) &&
            ( st::ObjDataStore_can_be_stored_on_cobjects_buffer<
                ObjData >( buffer ) ) )
        {
            status = st::ObjDataStoreLayoutTraits< ObjData >::GetDataPtrSizes(
                sizes.data(), sizes.size(), ptr_data_obj );
        }

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            status = st::ObjDataStoreLayoutTraits< ObjData >::GetDataPtrCounts(
                counts.data(), counts.size(), ptr_data_obj );
        }

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            _size_t* ptr_sizes = ( num_dataptrs > _size_t{ 0 } )
                ? sizes.data() : nullptr;

            _size_t* ptr_counts = ( num_dataptrs > _size_t{ 0 } )
                ? counts.data() : nullptr;

            if( ( native_size == _size_t{ 0 } ) &&
                ( ptr_obj_data != nullptr ) )
            {
                native_size = sizeof( *ptr_obj_data );
            }

            can_be_stored = ::NS(Buffer_can_add_object)(
                buffer, native_size, num_dataptrs, ptr_sizes, ptr_counts,
                    requ_num_objects, requ_num_slots, requ_num_dataptrs );
        }

        return can_be_stored;
    }

    template< class ObjData >
    static SIXTRL_HOST_FN bool ObjData_can_store_on_buffer(
        SIXTRL_CXX_NAMESPACE::Buffer const& SIXTRL_RESTRICT_REF buffer,
        SIXTRL_CXX_NAMESPACE::object_type_id_t const expected_base_type_id =
            SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_ILLEGAL,
        const ObjData *const SIXTRL_RESTRICT ptr_obj_data = nullptr,
        SIXTRL_CXX_NAMESPACE::buffer_size_t native_size =
            SIXTRL_CXX_NAMESPACE::buffer_size_t{ 0 },
        SIXTRL_CXX_NAMESPACE::buffer_size_t* SIXTRL_RESTRICT
            requ_num_objects = nullptr,
        SIXTRL_CXX_NAMESPACE::buffer_size_t* SIXTRL_RESTRICT
            requ_num_slots = nullptr,
        SIXTRL_CXX_NAMESPACE::buffer_size_t* SIXTRL_RESTRICT
            requ_num_dataptrs = nullptr ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ObjData_can_store_on_buffer(
            buffer.getCApiPtr(), expected_base_type_id, ptr_obj_data,
                native_size, requ_num_objects, requ_num_slots,
                    requ_num_dataptrs );
    }

    template< class ObjData >
    static SIXTRL_HOST_FN bool ObjData_can_store_on_buffer(
        SIXTRL_CXX_NAMESPACE::Buffer const& SIXTRL_RESTRICT_REF buffer,
        ObjData const& SIXTRL_RESTRICT_REF obj_data,
        SIXTRL_CXX_NAMESPACE::object_type_id_t const expected_base_type_id =
            SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_ILLEGAL,
        SIXTRL_CXX_NAMESPACE::buffer_size_t* SIXTRL_RESTRICT
            requ_num_objects = nullptr,
        SIXTRL_CXX_NAMESPACE::buffer_size_t* SIXTRL_RESTRICT
            requ_num_slots = nullptr,
        SIXTRL_CXX_NAMESPACE::buffer_size_t* SIXTRL_RESTRICT
            requ_num_dataptrs = nullptr ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ObjData_can_store_on_buffer(
            buffer.getCApiPtr(), expected_base_type_id, &obj_data,
                sizeof( obj_data ), requ_num_objects, requ_num_slots,
                    requ_num_dataptrs );
    }

    /* --------------------------------------------------------------------- */
    /* ObjData_store_on_buffer */

    template< class ObjData >
    static SIXTRL_HOST_FN std::enable_if<
        SIXTRL_CXX_NAMESPACE::ObjDataStore_has_no_dataptrs< ObjData >() &&
        SIXTRL_CXX_NAMESPACE::ObjDataStore_can_be_stored_on_cobjects_buffer<
            ObjData >(), ::NS(Object)* >::type
    ObjData_store_on_buffer(
        ::NS(Buffer)* SIXTRL_RESTRICT buffer,
        ::NS(object_type_id_t) const expected_base_type_id =
            SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_ILLEGAL,
        const ObjData *const SIXTRL_RESTRICT ptr_obj_data = nullptr,
        ::NS(buffer_size_t) native_size = ::NS(buffer_size_t){ 0 } )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        typedef st::object_type_id_t    _type_id_t;
        typedef st::buffer_size_t       _size_t;

        ::NS(Object)* added_obj = nullptr;

        /* Can only store objects which have a standard layout! */
        if( !std::is_standard_layout< ObjData >::value )
        {
            return added_obj;
        }

        constexpr _size_t num_dataptrs =
            st::ObjDataStoreDataPtrsTraits< ObjData >::MaxNumDataPtrs();

        static_assert( num_dataptrs == _size_t{ 0 },
                       "inconsistent num dataptrs" );

        _type_id_t const obj_type_id =
            st::ObjDataStoreTraits< ObjData >::ObjTypeId();

        _type_id_t const base_obj_type_id =
            st::ObjectTypeId_get_base_type_id( obj_type_id );

        if( ( obj_type_id != st::OBJECT_TYPE_ILLEGAL ) &&
            ( ( native_size >= sizeof( ObjData ) ) ||
              ( ptr_data_obj != nullptr ) ) &&
            ( ( expected_base_object_type_id == st::OBJECT_TYPE_ILLEGAL ) ||
              ( expected_base_object_type_id == base_obj_type_id ) ) &&
            ( st::ObjDataStore_can_be_stored_on_cobjects_buffer<
                ObjData >( buffer ) ) )
        {
            if( ( native_size == _size_t{ 0 } ) &&
                ( ptr_obj_data != nullptr ) )
            {
                native_size = sizeof( *ptr_obj_data );
            }

            added_obj = ::NS(Buffer_add_object)( buffer, ptr_obj_data,
                native_size, obj_type_id, num_dataptrs, nullptr,
                    nullptr, nullptr );
        }

        return added_obj;
    }

    template< class ObjData >
    static SIXTRL_HOST_FN std::enable_if<
        SIXTRL_CXX_NAMESPACE::ObjDataStore_has_dataptrs< ObjData >() &&
        SIXTRL_CXX_NAMESPACE::ObjDataStore_has_const_num_dataptrs< ObjData >() &&
        SIXTRL_CXX_NAMESPACE::ObjDataStore_can_be_stored_on_cobjects_buffer<
            ObjData >(), ::NS(Object)* >::type
    ObjData_store_on_buffer(
        ::NS(Buffer)* SIXTRL_RESTRICT buffer,
        ::NS(object_type_id_t) const expected_base_type_id =
            SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_ILLEGAL,
        const ObjData *const SIXTRL_RESTRICT ptr_obj_data = nullptr,
        ::NS(buffer_size_t) native_size = ::NS(buffer_size_t){ 0 } )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        typedef st::object_type_id_t    _type_id_t;
        typedef st::buffer_size_t       _size_t;

        ::NS(Object)* added_obj = nullptr;

        /* Can only store objects which have a standard layout! */
        if( !std::is_standard_layout< ObjData >::value )
        {
            return added_obj;
        }

        constexpr _size_t num_dataptrs =
            st::ObjDataStoreDataPtrsTraits< ObjData >::MaxNumDataPtrs();

        static_assert( num_dataptrs ==
            st::ObjDataStoreDataPtrsTraits< ObjData >::MinNumDataPtrs(),
            "min and max number of dataptrs disagreee -> inconsistent!" );

        static_assert( num_dataptrs > _size_t{ 0 },
            "max number of dataptrs required to be > 0" );

        _type_id_t const obj_type_id =
            st::ObjDataStoreTraits< ObjData >::ObjTypeId();

        _type_id_t const base_obj_type_id =
            st::ObjectTypeId_get_base_type_id( obj_type_id );

        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        _size_t offsets[ num_dataptrs ];
        _size_t sizes[ num_dataptrs ];
        _size_t counts[ num_dataptrs ];

        if( ( obj_type_id != st::OBJECT_TYPE_ILLEGAL ) &&
            ( ( native_size >= sizeof( ObjData ) ) ||
              ( ptr_data_obj != nullptr ) ) &&
            ( ( expected_base_object_type_id == st::OBJECT_TYPE_ILLEGAL ) ||
              ( expected_base_object_type_id == base_obj_type_id ) ) &&
            ( st::ObjDataStore_can_be_stored_on_cobjects_buffer<
                ObjData >( buffer ) ) )
        {
            status = st::ObjDataStoreLayoutTraits< ObjData >::GetDataPtrOffsets(
                &offsets[ 0 ], num_dataptrs, ptr_data_obj );
        }

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            status = st::ObjDataStoreLayoutTraits< ObjData >::GetDataPtrSizes(
                &sizes[ 0 ], num_dataptrs, ptr_data_obj );
        }

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            status = st::ObjDataStoreLayoutTraits< ObjData >::GetDataPtrCounts(
                &counts[ 0 ], num_dataptrs, ptr_data_obj );
        }

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            if( ( native_size == _size_t{ 0 } ) &&
                ( ptr_obj_data != nullptr ) )
            {
                native_size = sizeof( *ptr_obj_data );
            }

            added_obj = ::NS(Buffer_add_object)(
                buffer, ptr_obj_data, native_size, obj_type_id, num_dataptrs,
                    &offset[ 0 ], &sizes[ 0 ], &counts[ 0 ] );
        }

        return added_obj;
    }

    template< class ObjData >
    static SIXTRL_HOST_FN std::enable_if<
        SIXTRL_CXX_NAMESPACE::ObjDataStore_has_dataptrs< ObjData >() &&
        SIXTRL_CXX_NAMESPACE::ObjDataStore_has_var_num_dataptrs< ObjData >() &&
        SIXTRL_CXX_NAMESPACE::ObjDataStore_can_be_stored_on_cobjects_buffer<
            ObjData >(), ::NS(Object)* >::type
    ObjData_store_on_buffer(
        ::NS(Buffer)* SIXTRL_RESTRICT buffer,
        ::NS(object_type_id_t) const expected_base_type_id =
            SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_ILLEGAL,
        const ObjData *const SIXTRL_RESTRICT ptr_obj_data = nullptr,
        ::NS(buffer_size_t) native_size = ::NS(buffer_size_t){ 0 } )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        typedef st::object_type_id_t    _type_id_t;
        typedef st::buffer_size_t       _size_t;

        ::NS(Object)* added_obj = nullptr;

        /* Can only store objects which have a standard layout! */
        if( !std::is_standard_layout< ObjData >::value )
        {
            return added_obj;
        }

        /* var num dataptrs ->
         * we need an instance to determine the paramters! */
        if( ptr_obj_data == nullptr )
        {
            return can_be_stored;
        }

        _size_t const num_dataptrs =
            st::ObjDataStore_num_data_ptrs( ptr_obj_data );

        SIXTRL_ASSERT( num_dataptrs >=
            st::ObjDataStoreDataPtrsTraits< ObjData >::MinNumDataPtrs() );

        SIXTRL_ASSERT( num_dataptrs <=
            st::ObjDataStoreDataPtrsTraits< ObjData >::MaxNumDataPtrs() );

        _type_id_t const obj_type_id =
            st::ObjDataStoreTraits< ObjData >::ObjTypeId();

        _type_id_t const base_obj_type_id =
            st::ObjectTypeId_get_base_type_id( obj_type_id );

        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        _size_t const dummy_num_dataptrs = ( num_dataptrs > _size_t{ 0 } )
            ? num_dataptrs : _size_t{ 1 };

        std::vector< _size_t > offsets( dummy_num_dataptrs );
        std::vector< _size_t > sizes( dummy_num_dataptrs );
        std::vector< _size_t > counts( dummy_num_dataptrs );

        if( ( obj_type_id != st::OBJECT_TYPE_ILLEGAL ) &&
            ( ( native_size >= sizeof( ObjData ) ) ||
              ( ptr_data_obj != nullptr ) ) &&
            ( ( expected_base_object_type_id == st::OBJECT_TYPE_ILLEGAL ) ||
              ( expected_base_object_type_id == base_obj_type_id ) ) &&
            ( st::ObjDataStore_can_be_stored_on_cobjects_buffer<
                ObjData >( buffer ) ) )
        {
            status = st::ObjDataStoreLayoutTraits< ObjData >::GetDataPtrOffsets(
                offsets.data(), offsets.size(), ptr_data_obj );
        }

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            status = st::ObjDataStoreLayoutTraits< ObjData >::GetDataPtrSizes(
                sizes.data(), sizes.size(), ptr_data_obj );
        }

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            status = st::ObjDataStoreLayoutTraits< ObjData >::GetDataPtrCounts(
                counts.data(), counts.size(), ptr_data_obj );
        }

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            _size_t* ptr_offsets = ( num_dataptrs > _size_t{ 0 } )
                ? offsets.data() : nullptr;

            _size_t* ptr_sizes = ( num_dataptrs > _size_t{ 0 } )
                ? sizes.data() : nullptr;

            _size_t* ptr_counts = ( num_dataptrs > _size_t{ 0 } )
                ? counts.data() : nullptr;

            if( ( native_size == _size_t{ 0 } ) &&
                ( ptr_obj_data != nullptr ) )
            {
                native_size = sizeof( *ptr_obj_data );
            }

            added_obj = ::NS(Buffer_add_object)(
                buffer, ptr_obj_data, native_size, obj_type_id, num_dataptrs,
                    ptr_offsets, ptr_sizes, ptr_counts );
        }

        return added_obj;
    }

    template< class ObjData >
    static SIXTRL_HOST_FN ::NS(Object)* ObjData_store_on_buffer(
        SIXTRL_CXX_NAMESPACE::Buffer const& SIXTRL_RESTRICT_REF buffer,
        SIXTRL_CXX_NAMESPACE::object_type_id_t const expected_base_type_id =
            SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_ILLEGAL,
        const ObjData *const SIXTRL_RESTRICT ptr_obj_data = nullptr,
        SIXTRL_CXX_NAMESPACE::buffer_size_t native_size =
            SIXTRL_CXX_NAMESPACE::buffer_size_t{ 0 } )
    {
        return SIXTRL_CXX_NAMESPACE::ObjData_can_store_on_buffer(
            buffer.getCApiPtr(), expected_base_type_id,
                ptr_obj_data, native_size );
    }

    template< class ObjData >
    static SIXTRL_HOST_FN ::NS(Object)* ObjData_store_on_buffer(
        SIXTRL_CXX_NAMESPACE::Buffer const& SIXTRL_RESTRICT_REF buffer,
        ObjData const& SIXTRL_RESTRICT_REF obj_data,
        SIXTRL_CXX_NAMESPACE::object_type_id_t const expected_base_type_id =
            SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_ILLEGAL )
    {
        return SIXTRL_CXX_NAMESPACE::ObjData_can_store_on_buffer(
            buffer.getCApiPtr(), expected_base_type_id, &obj_data,
                sizeof( obj_data ) );
    }

    /* -------------------------------------------------------------------- */

    template< class RestoreObj >
    static SIXTRL_HOST_FN RestoreObj const* ObjStore_ptr_const_from_obj_index(
        const ::NS(Object) *const SIXTRL_RESTRICT ptr_obj_index,
        SIXTRL_CXX_NAMESPACE::object_type_id_t) const
            expected_obj_type_id ) SIXTRL_NOEXCEPT
    {
        typedef SIXTRL_CXX_NAMESPACE::object_type_id_t _type_id_t;

        _type_id_t const obj_type_id = ::NS(Object_get_type_id)( obj_index );

        if( ( obj_index != nullptr ) &&
            ( obj_type_id == expected_obj_type_id ) &&
            ( obj_type_id != SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_ILLEGAL ) )
        {
            return reinterpret_cast< RestoreObj const* >(
                static_cast< uintptr_t >( ::NS(Object_get_begin_addr)(
                    obj_index ) ) );
        }

        return nullptr;
    }

    template< class RestoreObj >
    static SIXTRL_HOST_FN RestoreObj* ObjStore_ptr_from_obj_index(
        const ::NS(Object) *const SIXTRL_RESTRICT ptr_obj_index,
        SIXTRL_CXX_NAMESPACE::object_type_id_t) const
            expected_obj_type_id ) SIXTRL_NOEXCEPT
    {
        typedef SIXTRL_CXX_NAMESPACE::object_type_id_t _type_id_t;

        _type_id_t const obj_type_id = ::NS(Object_get_type_id)( obj_index );

        if( ( obj_index != nullptr ) &&
            ( obj_type_id == expected_obj_type_id ) &&
            ( obj_type_id != SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_ILLEGAL ) )
        {
            return reinterpret_cast< RestoreObj* >( static_cast< uintptr_t >(
                ::NS(Object_get_begin_addr)( obj_index ) ) );
        }

        return nullptr;
    }

    # endif /* _GPUCODE */

    /* --------------------------------------------------------------------- */

    template< class ObjData >
    class ObjConvertibleToCApiBase : public ObjData
    {
        public:

        typedef ObjData cxx_api_t;
        typedef typename ObjDataStoreCApiTraits< ObjData >::c_api_t c_api_t;
        typedef SIXTRL_CXX_NAMESPACE::buffer_size_t                 size_type;

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

        static SIXTRL_FN constexpr
        bool is_convertible_to_c_api() SIXTRL_NOEXCEPT
        {
            return st::ObjData_is_convertible_to_capi< ObjData >();
        }

        static SIXTRL_FN constexpr
        bool is_not_convertible_to_c_api() SIXTRL_NOEXCEPT
        {
            return st::ObjData_is_not_convertible_to_capi< ObjData >();
        }

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

        SIXTRL_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::ObjData_is_convertible_to_capi< ObjData >(),
                c_api_t const* >::type ptr_const_c_api() SIXTRL_NOEXCEPT
        {
            return static_cast< c_api_t const* >( this );
        }

        SIXTRL_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::ObjData_is_convertible_to_capi< ObjData >(),
                c_api_t const* >::type ptr_c_api() const SIXTRL_NOEXCEPT
        {
            return static_cast< c_api_t const* >( this );
        }

        SIXTRL_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::ObjData_is_convertible_to_capi< ObjData >(),
                c_api_t* >::type ptr_c_api() SIXTRL_NOEXCEPT
        {
            return static_cast< c_api_t* >( this );
        }

        /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

        SIXTRL_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::ObjData_is_not_convertible_to_capi< ObjData >(),
                c_api_t const* >::type ptr_const_c_api() SIXTRL_NOEXCEPT
        {
            return nullptr;
        }

        SIXTRL_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::ObjData_is_not_convertible_to_capi< ObjData >(),
                c_api_t const* >::type ptr_c_api() const SIXTRL_NOEXCEPT
        {
            return nullptr;
        }

        SIXTRL_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::ObjData_is_not_convertible_to_capi< ObjData >(),
                c_api_t* >::type ptr_c_api() SIXTRL_NOEXCEPT
        {
            return nullptr;
        }

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

        SIXTRL_FN cxx_api_t const& const_data() SIXTRL_NOEXCEPT
        {
            return static_cast< cxx_api_t const& >( *this );
        }

        SIXTRL_FN cxx_api_t const& data() const SIXTRL_NOEXCEPT
        {
            return static_cast< cxx_api_t const& >( *this );
        }

        SIXTRL_FN cxx_api_t& data() SIXTRL_NOEXCEPT
        {
            return static_cast< cxx_api_t& >( *this );
        }

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

        SIXTRL_FN cxx_api_t* ptr_data() SIXTRL_NOEXCEPT
        {
            return static_cast< cxx_api_t const* >( this );
        }

        SIXTRL_FN cxx_api_t const* ptr_data() const SIXTRL_NOEXCEPT
        {
            return static_cast< cxx_api_t const* >( this );
        }

        SIXTRL_FN cxx_api_t const* ptr_const_data() SIXTRL_NOEXCEPT
        {
            return static_cast< cxx_api_t const* >( this );
        }

        /* ----------------------------------------------------------------- */

        #if !defined( _GPUCODE )

        SIXTRL_FN bool can_store_on_buffer(
            const ::NS(Buffer) *const SIXTRL_RESTRICT buffer,
            size_type* SIXTRL_RESTRICT req_nobjects = nullptr,
            size_type* SIXTRL_RESTRICT req_nslots = nullptr,
            size_type* SIXTRL_RESTRICT req_ndataptrs = nullptr ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;

            return st::ObjData_can_store_on_buffer( buffer,
                st::ObjDataTypeTraits< ObjData >::ObjTypeId(), this,
                    st::buffer_size_t{ 0 }, req_nobjects, req_nslots,
                        req_ndataptrs );
        }

        SIXTRL_FN bool can_store_on_buffer(
            SIXTRL_CXX_NAMESPACE::Buffer const& SIXTRL_RESTRICT_REF buffer,
            size_type* SIXTRL_RESTRICT req_nobjects = nullptr,
            size_type* SIXTRL_RESTRICT req_nslots = nullptr,
            size_type* SIXTRL_RESTRICT req_ndataptrs = nullptr ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;

            return st::ObjData_can_store_on_buffer( buffer, *this,
                st::ObjDataTypeTraits< ObjData >::ObjTypeId(),
                    req_nobjects, req_nslots, req_ndataptrs );
        }

        #endif /* !defined( _GPUCODE ) */
    };
}

#endif /* defined( __cplusplus ) */

#endif /* SIXTRACKLIB_COMMON_INTERNAL_OBJ_STORE_TRAITS_CXX_HPP__ */
