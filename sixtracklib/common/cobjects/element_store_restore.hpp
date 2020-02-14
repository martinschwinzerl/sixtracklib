#ifndef SIXTRACKLIB_COMMON_COBJECTS_ELEMENT_STORE_RESTORE_CXX_HPP__
#define SIXTRACKLIB_COMMON_COBJECTS_ELEMENT_STORE_RESTORE_CXX_HPP__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <type_traits>
        #if !defined( _GPUCODE )
            #include <algorithm>
            #include <vector>
        #endif /* Host */
    #endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/cobjects/index_object.h"
    #include "sixtracklib/common/cobjects/flat_buffer.h"
    #include "sixtracklib/common/cobjects/element_pointers.hpp"
    #include "sixtracklib/common/cobjects/field_offsets.hpp"
    #include "sixtracklib/common/cobjects/field_sizes.hpp"
    #include "sixtracklib/common/cobjects/field_counts.hpp"
    #include "sixtracklib/common/internal/obj_base_class.hpp"
    #include "sixtracklib/common/internal/obj_store_traits.hpp"
    #if !defined( _GPUCODE )
        #include "sixtracklib/common/buffer.h"
    #endif /* !defined( _GPUCODE ) */
#endif /* SIXTRL_NO_INCLUDES */

#if defined( __cplusplus )

namespace SIXTRL_CXX_NAMESPACE
{
    template< class D >
    struct IsObjDataStorageInterfaceTraits<
        D, STORAGE_BE_COBJECTS, typename std::enable_if<
            std::is_base_of< ObjDataStorageInterfaceBase<
                typename D::obj_data_t, STORAGE_BE_COBJECTS, D >, D >::value &&
            std::is_base_of< typename D::obj_data_t, D >::value &&
           !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< D >()
        >::type >
    {
        static SIXTRL_FN constexpr bool is_interface() SIXTRL_NOEXCEPT
        {
            return true;
        }
    };

    template< class E >
    static SIXTRL_FN constexpr bool
    CObjElem_is_cobj_storage_interface() SIXTRL_NOEXCEPT
    {
        return IsObjDataStorageInterfaceTraits<
            E, STORAGE_BE_COBJECTS >::is_interface();
    }

    template< class D  >
    struct ObjDataDerivedStorageTraits< D, STORAGE_BE_COBJECTS,
        typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::CObjElem_is_cobj_storage_interface< D >() &&
            std::is_standard_layout< D >::value &&
            std::is_standard_layout< typename D::obj_data_t >::value &&
            ( sizeof( D ) == sizeof( typename D::obj_data_t ) ) &&
            SIXTRL_CXX_NAMESPACE::ObjData_can_be_memcopied<
                typename D::obj_data_t >() &&
            SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage<
                typename D::obj_data_t >() &&
            SIXTRL_CXX_NAMESPACE::CObjElemTypeId_is_legal<
                typename D::obj_data_t >() >::type >
    {
        static SIXTRL_FN constexpr bool allow_derived_storage() SIXTRL_NOEXCEPT
        {
            return true;
        }
    };

    template< class E >
    static SIXTRL_FN constexpr bool
    CObjElem_allow_derived_storage() SIXTRL_NOEXCEPT
    {
        return ObjDataDerivedStorageTraits<
            E, STORAGE_BE_COBJECTS >::allow_derived_storage();
    }

    /* ********************************************************************* */
    /* Define a set of cases, based on the different pointer - scenarios, to
     * provide differentiated implementations */

    template< class E >
    static SIXTRL_FN constexpr bool
    CObjElem_ptrs_case01_direct_no_ptrs() SIXTRL_NOEXCEPT
    {
        return (
            SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
            SIXTRL_CXX_NAMESPACE::CObjElem_definitely_has_no_ptrs< E >() );
    }

    template< class E >
    static SIXTRL_FN constexpr bool
    CObjElem_ptrs_case02_direct_fixed_few() SIXTRL_NOEXCEPT
    {
        return (
        SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
       !SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case01_direct_no_ptrs< E >() &&
        SIXTRL_CXX_NAMESPACE::CObjElem_has_field_offsets_begin_end_ptr< E >() &&
        SIXTRL_CXX_NAMESPACE::CObjElem_has_field_sizes_begin_end_ptr< E >() &&
        SIXTRL_CXX_NAMESPACE::CObjElem_few_enough_ptrs_for_static_array< E >()
        );
    }

    template< class E >
    static SIXTRL_FN constexpr bool
    CObjElem_ptrs_case03_direct_few() SIXTRL_NOEXCEPT
    {
        return (
        SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
       !SIXTRL_CXX_NAMESPACE::CObjElem_definitely_has_no_ptrs< E >() &&
        ( !SIXTRL_CXX_NAMESPACE::CObjElem_has_const_num_ptrs< E >() ||
          !SIXTRL_CXX_NAMESPACE::CObjElem_has_always_same_sizes< E >() ) &&
        SIXTRL_CXX_NAMESPACE::CObjElem_few_enough_ptrs_for_static_array<
            E >() );
    }

    template< class E >
    static SIXTRL_FN constexpr bool
    CObjElem_ptrs_case04_direct() SIXTRL_NOEXCEPT
    {
        #if !defined( _GPUCODE )

        return (
        SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
        SIXTRL_CXX_NAMESPACE::CObjElem_too_many_ptrs_for_static_array<
            E >() );

        #else

        return false;

        #endif /* !defined( _GPUCODE ) */
    }

    template< class E >
    static SIXTRL_FN constexpr bool
    CObjElem_ptrs_case99_undefined() SIXTRL_NOEXCEPT
    {
        return (
        !SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case01_direct_no_ptrs< E >() &&
        !SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case02_direct_fixed_few< E >() &&
        !SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case03_direct_few< E >() &&
        !SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case04_direct< E >() ) &&
        !SIXTRL_CXX_NAMESPACE::CObjElem_allow_derived_storage< E >();
    }

    /* ********************************************************************* */
    /* Provide template version of NS(CObjFlatBuffer_slot_based_size)() */

    /* First, implement specialized versions based on different pointer
     * scenarios */

    template< class E >
    static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case01_direct_no_ptrs< E >(),
        cobj_size_t >::type CObjElem_required_num_bytes(
        cobj_size_t const slot_size =
            SIXTRL_CXX_NAMESPACE::CBUFFER_DEFAULT_SLOT_SIZE,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
            /* ptr_elem */ = nullptr ) SIXTRL_NOEXCEPT
    {
        return ::NS(CObjFlatBuffer_slot_based_size)( sizeof( E ), slot_size );
    }

    template< class E >
    static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case02_direct_fixed_few< E >(),
        cobj_size_t >::type CObjElem_required_num_bytes(
        cobj_size_t const slot_size =
            SIXTRL_CXX_NAMESPACE::CBUFFER_DEFAULT_SLOT_SIZE,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT ptr_elem =
            nullptr ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef cobj_size_t _size_t;
        _size_t slot_based_size = _size_t{ 0 };

        _size_t constexpr MAX_NUM_PTRS = st::CObjElem_max_num_ptrs< E >();

        SIXTRL_BUFFER_ARGPTR_DEC _size_t counts[ MAX_NUM_PTRS ];

        if( st::CObjElemFieldCounts< E >::init_field_counts(
                &counts[ 0 ], MAX_NUM_PTRS, ptr_elem ) ==
                    st::COBJECTS_STATUS_SUCCESS )
        {
            slot_based_size = ::NS(CObjFlatBuffer_predict_required_num_slots)(
                sizeof( E ), MAX_NUM_PTRS,
                    st::CObjElem_field_sizes_ptr_constexpr_begin< E >(),
                        &counts[ 0 ], slot_size );
        }

        return slot_based_size;
    }

    template< class E >
    static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case03_direct_few< E >(),
        cobj_size_t >::type CObjElem_required_num_bytes(
        cobj_size_t const slot_size =
            SIXTRL_CXX_NAMESPACE::CBUFFER_DEFAULT_SLOT_SIZE,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT ptr_elem =
            nullptr ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        cobj_size_t slot_based_size = cobj_size_t{ 0 };

        cobj_size_t constexpr MAX_NUM_PTRS =
            st::CObjElem_max_num_ptrs< E >();

        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t sizes[ MAX_NUM_PTRS ];
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t counts[ MAX_NUM_PTRS ];

        cobj_size_t const num_ptrs =
            st::CObjElem_num_ptrs< E >( ptr_elem );

        SIXTRL_ASSERT( num_ptrs <= MAX_NUM_PTRS );

        if( ( st::CObjElem_field_sizes< E >( &sizes[ 0 ], MAX_NUM_PTRS,
                ptr_elem ) == st::COBJECTS_STATUS_SUCCESS ) &&
            ( st::CObjElem_field_counts< E >( &counts[ 0 ], MAX_NUM_PTRS,
                ptr_elem ) == st::COBJECTS_STATUS_SUCCESS ) )
        {
            slot_based_size = ::NS(CObjFlatBuffer_predict_required_num_slots)(
                sizeof( E ), num_ptrs, &sizes[ 0 ], &counts[ 0 ], slot_size );
        }

        return slot_based_size;
    }

    template< class E >
    static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case04_direct< E >(),
        cobj_size_t >::type CObjElem_required_num_bytes(
        cobj_size_t const slot_size =
            SIXTRL_CXX_NAMESPACE::CBUFFER_DEFAULT_SLOT_SIZE,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT ptr_elem =
            nullptr ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        cobj_size_t slot_based_size = cobj_size_t{ 0 };

        #if !defined( _GPUCODE )

        cobj_size_t constexpr MAX_NUM_PTRS =
            st::CObjElem_max_num_ptrs< E >();

        cobj_size_t const num_ptrs =
            st::CObjElem_num_ptrs< E >( ptr_elem );

        SIXTRL_ASSERT( num_ptrs <= MAX_NUM_PTRS );

        std::vector< cobj_size_t > sizes( MAX_NUM_PTRS );
        std::vector< cobj_size_t > counts( MAX_NUM_PTRS );

        SIXTRL_ASSERT( sizes.size()  >= MAX_NUM_PTRS );
        SIXTRL_ASSERT( counts.size() >= MAX_NUM_PTRS );

        if( ( st::CObjElem_field_sizes< E >( sizes.data(), sizes.size(),
                ptr_elem ) == st::COBJECTS_STATUS_SUCCESS ) &&
            ( st::CObjElem_field_counts< E >( counts.data(), counts.size(),
                ptr_elem ) == st::COBJECTS_STATUS_SUCCESS ) )
        {
            slot_based_size = ::NS(CObjFlatBuffer_predict_required_num_slots)(
                sizeof( E ), num_ptrs, sizes.data(), counts.data(), slot_size);
        }

        #else /* _GPUCODE */

        ( void )ptr_elem;
        ( void )slot_size;

        #endif /* _GPUCODE */

        return slot_based_size;
    }

    template< class Derived >
    static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_allow_derived_storage< Derived >(),
        cobj_size_t >::type
    CObjElem_required_num_bytes( cobj_size_t const slot_size =
            SIXTRL_CXX_NAMESPACE::CBUFFER_DEFAULT_SLOT_SIZE,
        SIXTRL_BUFFER_ARGPTR_DEC const Derived *const SIXTRL_RESTRICT ptr_elem
            = nullptr ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return st::CObjElem_required_num_bytes<
            typename Derived::obj_data_t >( slot_size,
            ( ( ptr_elem != nullptr ) ? ptr_elem->as_ptr_data() : nullptr ) );
    }

    template< class E >
    static SIXTRL_FN constexpr typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case99_undefined< E >(),
        cobj_size_t >::type CObjElem_required_num_bytes(
        cobj_size_t const /* slot_size */ =
            SIXTRL_CXX_NAMESPACE::CBUFFER_DEFAULT_SLOT_SIZE,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT /* ptr_elem */
            = nullptr ) SIXTRL_NOEXCEPT
    {
        return cobj_size_t{ 0 };
    }

    /* --------------------------------------------------------------------- */

    template< class E >
    static SIXTRL_FN cobj_size_t CObjElem_required_num_slots(
        cobj_size_t const slot_size =
            SIXTRL_CXX_NAMESPACE::CBUFFER_DEFAULT_SLOT_SIZE,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
            ptr_elem = nullptr ) SIXTRL_NOEXCEPT
    {
        return ( slot_size > cobj_size_t{ 0 } )
            ? SIXTRL_CXX_NAMESPACE::CObjElem_required_num_bytes< E >(
                slot_size, ptr_elem ) / slot_size
            : cobj_size_t{ 0 };
    }

    /* ********************************************************************* */
    /* Provide a helper predicate to check whether Derived and the base
     * E / ObjData class are compatible with storage in a CObjects buffer    */

    template< class Derived >
    static SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_OBJ_DATAPTR_DEC Derived const*
    CObjElem_const_derived_from_obj_index( SIXTRL_BUFFER_OBJ_ARGPTR_DEC const
            ::NS(CObjIndex) *const SIXTRL_RESTRICT index_obj,
        SIXTRL_CXX_NAMESPACE::cobj_size_t const slot_size =
            SIXTRL_CXX_NAMESPACE::CBUFFER_DEFAULT_SLOT_SIZE,
        SIXTRL_BUFFER_ARGPTR_DEC const Derived *const SIXTRL_RESTRICT
            /*ptr_cls_elem*/ = nullptr ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename Derived::obj_data_t Elem;
        typedef typename st::cobj_type_id_t _type_id_t;

        static_assert( st::CObjElem_is_cobj_storage_interface< Derived >(),
            "Type  has to be derived from the CObjects storage interface" );

        static_assert( st::CObjElem_allow_derived_storage< Derived >(),
            "Derived type and base type have to be compatible!" );

        /* TODO / HACK: Despite the plethora of static_assert's above which
         *              should limit the damage that is inflicted by what
         *              is about to happen, this runs afoul of type-aliasing
         *              rules and is very likely UB.
         *
         * Cross fingers until we get C++20 / std::bit_cast (or at least a
         * constexpr memcpy / memmove so we can implement our own) which
         * seems to be the only sensible option in the end */

        typedef SIXTRL_BUFFER_OBJ_DATAPTR_DEC Elem const* ptr_stored_elem_t;
        typedef SIXTRL_BUFFER_OBJ_DATAPTR_DEC Derived const* ptr_elem_t;

        _type_id_t constexpr type_id = st::CObjElem_type_id< Elem >();

        SIXTRL_ASSERT( sizeof( Elem ) <= ::NS(CObjIndex_size)( index_obj ) );
        SIXTRL_ASSERT( slot_size > st::cobj_size_t{ 0 } );
        SIXTRL_ASSERT( ( ::NS(CObjIndex_size)( index_obj ) % slot_size ) ==
                         st::cobj_size_t{ 0 } );

        /* NOTE: dynamic cast would be slightly more defined but without
         * sentinel also a lot slower!. Since typeid essentially acts as
         * a sentinel here (though on the level of E and not Derived), this
         * would not buy us anything in addition to what we are doing here.
         * Feedback to the contrary would be welcome! */

        ptr_elem_t ptr_elem =
            ( type_id == ::NS(CObjIndex_type_id)( index_obj ) )
            ? reinterpret_cast< ptr_elem_t >(
                /* NOTE: This is a downcast to Derived from the E instance! */
                reinterpret_cast< ptr_stored_elem_t >(
                    static_cast< uintptr_t >(
                        ::NS(CObjIndex_begin_addr)( index_obj ) ) ) )
            : nullptr;

        SIXTRL_ASSERT( ( ptr_elem == nullptr ) ||
            ( ( index_obj != nullptr ) &&
              ( st::cobj_size_t{ 0 } < ::NS(CObjIndex_size)( index_obj ) ) &&
              /* Derived has a is-a relationship with E -> this should work! */
              ( st::CObjElem_required_num_bytes< Elem >( slot_size, ptr_elem ) <=
                ::NS(CObjIndex_size)( index_obj ) ) ) );

        return ptr_elem;
    }

    /* ********************************************************************* */
    /* Direct restore -> only works with Elements E that support that
     * mode, cf. the sixtrack::CObjElem_allow_direct_storage< E >() predicate*/

    template< class E >
    static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
        SIXTRL_CXX_NAMESPACE::CObjElemTypeId_is_legal< E >(),
        SIXTRL_BUFFER_OBJ_DATAPTR_DEC E const* >::type
    CObjElem_const_from_cobj_index( SIXTRL_BUFFER_OBJ_ARGPTR_DEC const
            ::NS(CObjIndex) *const SIXTRL_RESTRICT index_obj,
        cobj_size_t const slot_size =
            SIXTRL_CXX_NAMESPACE::CBUFFER_DEFAULT_SLOT_SIZE,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
            /*ptr_cls_elem*/ = nullptr ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef SIXTRL_BUFFER_OBJ_DATAPTR_DEC E const* ptr_elem_t;

        static_assert( st::ObjData_can_be_memcopied< E >(),
            "Can only restore entities from a CObjects buffer which are "
            "suitable for memcpy -> use delegates for other entities" );

        return reinterpret_cast< ptr_elem_t >( reinterpret_cast< uintptr_t >(
            ::NS(CObjIndex_begin_addr_filter_by_type_info)( index_obj,
                st::CObjElem_type_id< E >(), sizeof( E ), slot_size ) ) );
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    template< class E >
    static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_is_cobj_storage_interface< E >() &&
        SIXTRL_CXX_NAMESPACE::CObjElem_allow_derived_storage< E >(),
        SIXTRL_BUFFER_OBJ_DATAPTR_DEC E const* >::type
    CObjElem_const_from_cobj_index( SIXTRL_BUFFER_OBJ_ARGPTR_DEC const
            ::NS(CObjIndex) *const SIXTRL_RESTRICT index_obj,
        cobj_size_t const slot_size =
            SIXTRL_CXX_NAMESPACE::CBUFFER_DEFAULT_SLOT_SIZE,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
            ptr_cls_elem = nullptr ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_const_derived_from_obj_index<E >(
            index_obj, slot_size, ptr_cls_elem );
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    template< class E >
    static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
        ( !SIXTRL_CXX_NAMESPACE::CObjElem_is_cobj_storage_interface< E >() ||
          !SIXTRL_CXX_NAMESPACE::CObjElem_allow_derived_storage< E >() ),
        SIXTRL_BUFFER_OBJ_DATAPTR_DEC E const* >::type
    CObjElem_const_from_cobj_index( SIXTRL_BUFFER_OBJ_ARGPTR_DEC const
            ::NS(CObjIndex) *const SIXTRL_RESTRICT /*index_obj*/,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
            /* ptr_dummy_elem */ = nullptr ) SIXTRL_NOEXCEPT
    {
        return nullptr;
    }

    /* --------------------------------------------------------------------- */

    template< class E >
    static SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_OBJ_DATAPTR_DEC E*
    CObjElem_from_cobj_index(
        SIXTRL_BUFFER_OBJ_ARGPTR_DEC ::NS(CObjIndex)* SIXTRL_RESTRICT idx_obj,
        cobj_size_t const slot_size =
            SIXTRL_CXX_NAMESPACE::CBUFFER_DEFAULT_SLOT_SIZE,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
            ptr_dummy_elem = nullptr ) SIXTRL_NOEXCEPT
    {
        return const_cast< SIXTRL_BUFFER_OBJ_DATAPTR_DEC E* >(
            SIXTRL_CXX_NAMESPACE::CObjElem_const_from_cobj_index< E >(
                idx_obj, slot_size, ptr_dummy_elem ) );
    }

    /* ===================================================================== */
    /* "Load" Object from an instance stored at a buffer ->
     * we assume that the copy we are storing the data is itself not
     * stored in a CBuffer (For that we will provide a copy API) but
     * provides and manages any pointers itself
     *
     * For the moment, we will only provide implementations for the case where
     * the layout parameters of the source and target object are identical */

    template< class E >
    static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case01_direct_no_ptrs< E >(),
        cobj_status_t >::type
    CObjElem_load_from_flat_cbuffer_to_argptr(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t) const* SIXTRL_RESTRICT buffer,
        NS(cobj_size_t) const pos_in_buffer,
        NS(cobj_size_t) const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC E* SIXTRL_RESTRICT ptr_obj_to_update
    ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef st::cobj_size_t _size_t;

        return ::NS(CObjFlatBuffer_load_obj_same_layout_parameters_to_argptr)(
            buffer, pos_in_buffer, slot_size, st::CObjElem_type_id< E >(),
                ptr_obj_to_update, sizeof( E ), _size_t{ 0 },
                    nullptr, nullptr, nullptr, nullptr );
    }

    template< class E >
    static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case02_direct_fixed_few< E >(),
        cobj_status_t >::type
    CObjElem_load_from_flat_cbuffer_to_argptr(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t) const* SIXTRL_RESTRICT buffer,
        NS(cobj_size_t) const pos_in_buffer,
        NS(cobj_size_t) const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC E* SIXTRL_RESTRICT ptr_obj_to_update
    ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef st::cobj_size_t _size_t;

        st::cobj_status_t status = st::COBJECTS_STATUS_GENERAL_FAILURE;

        _size_t constexpr MAX_NUM_PTRS = st::CObjElem_max_num_ptrs< E >();
        _size_t counts[ MAX_NUM_PTRS ];
        _size_t save_ptrs[ MAX_NUM_PTRS ];

        if( st::CObjElem_field_counts< E >( &counts[ 0 ], MAX_NUM_PTRS,
                ptr_obj_to_update ) == st::COBJECTS_STATUS_SUCCESS )
        {
            status =
            ::NS(CObjFlatBuffer_load_obj_same_layout_parameters_to_argptr)(
                buffer, pos_in_buffer, slot_size, st::CObjElem_type_id< E >(),
                    ptr_obj_to_update, sizeof( E ), MAX_NUM_PTRS,
                        st::CObjElem_field_offsets_ptr_constexpr_begin< E >(),
                        st::CObjElem_field_sizes_ptr_constexpr_begin< E >(),
                        &counts[ 0 ], &save_ptrs[ 0 ] );
        }

        return status;
    }

    template< class E >
    static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case03_direct_few< E >(),
        cobj_status_t >::type
    CObjElem_load_from_flat_cbuffer_to_argptr(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t) const* SIXTRL_RESTRICT buffer,
        NS(cobj_size_t) const pos_in_buffer,
        NS(cobj_size_t) const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC E* SIXTRL_RESTRICT ptr_obj_to_update
    ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef st::cobj_size_t _size_t;

        st::cobj_status_t status = st::COBJECTS_STATUS_GENERAL_FAILURE;

        _size_t constexpr MAX_NUM_PTRS =
            st::CObjElem_max_num_ptrs< E >();

        static_assert( MAX_NUM_PTRS > _size_t{ 0 },
                       "Expected to have dataptrs here" );

        SIXTRL_BUFFER_OBJ_DATAPTR_DEC E const* src =
            st::CObjElem_const_from_cobj_index< E >(
                ::NS(CObjFlatBuffer_const_index)(
                    buffer, pos_in_buffer, slot_size ), slot_size );

        _size_t const num_pointers =
            st::CObjElem_num_ptrs< E >( ptr_obj_to_update );

        SIXTRL_ASSERT( num_pointers <= MAX_NUM_PTRS );

        _size_t target_offsets[ MAX_NUM_PTRS ];
        _size_t target_counts[ MAX_NUM_PTRS ];
        _size_t target_sizes[ MAX_NUM_PTRS ];

        if( ( src != nullptr ) &&
            ( num_pointers == st::CObjElem_num_ptrs< E >( src ) ) )
        {
            SIXTRL_BUFFER_ARGPTR_DEC E* SIXTRL_RESTRICT target =
                ptr_obj_to_update;

            _size_t src_offsets[ MAX_NUM_PTRS ];
            _size_t src_counts[ MAX_NUM_PTRS ];
            _size_t src_sizes[ MAX_NUM_PTRS ];

            if( ( st::CObjElem_field_offsets< E >( &target_offsets[ 0 ],
                    MAX_NUM_PTRS, target ) == st::COBJECTS_STATUS_SUCCESS ) &&
                ( st::CObjElem_field_sizes< E >( &target_sizes[ 0 ],
                    MAX_NUM_PTRS, target ) == st::COBJECTS_STATUS_SUCCESS ) &&
                ( st::CObjElem_field_counts< E >( &target_counts[ 0 ],
                    MAX_NUM_PTRS, target ) == st::COBJECTS_STATUS_SUCCESS ) &&
                ( st::CObjElem_field_offsets< E >( &src_offsets[ 0 ],
                    MAX_NUM_PTRS, src ) == st::COBJECTS_STATUS_SUCCESS ) &&
                ( st::CObjElem_field_sizes< E >( &src_sizes[ 0 ],
                    MAX_NUM_PTRS, src ) == st::COBJECTS_STATUS_SUCCESS ) &&
                ( st::CObjElem_field_counts< E >( &src_counts[ 0 ],
                    MAX_NUM_PTRS, src ) == st::COBJECTS_STATUS_SUCCESS ) )
            {
                status = st::COBJECTS_STATUS_SUCCESS;

                for( _size_t ii = _size_t{ 0 } ; ii < num_pointers ; ++ii )
                {
                    if( ( src_offsets[ ii ] != target_offsets[ ii ] ) ||
                        ( src_sizes[ ii ]   != target_sizes[ ii ]   ) ||
                        ( src_counts[ ii ]  != target_counts[ ii ]  ) )
                    {
                        status = st::COBJECTS_STATUS_GENERAL_FAILURE;
                        break;
                    }
                }
            }
        }

        if( status == st::COBJECTS_STATUS_SUCCESS )
        {
            _size_t save_ptrs[ MAX_NUM_PTRS ];

            status =
            ::NS(CObjFlatBuffer_load_obj_same_layout_parameters_to_argptr)(
                buffer, pos_in_buffer, slot_size, st::CObjElem_type_id< E >(),
                    ptr_obj_to_update, sizeof( E ), num_pointers,
                        &target_offsets[ 0 ], &target_sizes[ 0 ],
                            &target_counts[ 0 ], &save_ptrs[ 0 ] );
        }

        return status;
    }

    template< class E >
    static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case04_direct< E >(),
        cobj_status_t >::type
    CObjElem_load_from_flat_cbuffer_to_argptr(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t) const* SIXTRL_RESTRICT buffer,
        NS(cobj_size_t) const pos_in_buffer, NS(cobj_size_t) const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC E* SIXTRL_RESTRICT ptr_obj_to_update )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::cobj_status_t status = st::COBJECTS_STATUS_GENERAL_FAILURE;

        #if !defined( _GPUCODE )

        typedef st::cobj_size_t _size_t;
        _size_t constexpr MAX_NUM_PTRS =
            st::CObjElem_max_num_ptrs< E >();

        static_assert( MAX_NUM_PTRS > _size_t{ 0 },
                       "Expected to have dataptrs here" );

        SIXTRL_BUFFER_OBJ_DATAPTR_DEC E const* src =
            st::CObjElem_const_from_cobj_index< E >(
                ::NS(CObjFlatBuffer_const_index)(
                    buffer, pos_in_buffer, slot_size ), slot_size );

        _size_t const num_pointers =
            st::CObjElem_num_ptrs< E >( ptr_obj_to_update );

        SIXTRL_ASSERT( num_pointers <= MAX_NUM_PTRS );

        std::vector< _size_t > target_offsets( MAX_NUM_PTRS );
        std::vector< _size_t > target_counts( MAX_NUM_PTRS );
        std::vector< _size_t > target_sizes( MAX_NUM_PTRS );

        if( ( src != nullptr ) &&
            ( num_pointers == st::CObjElem_num_ptrs< E >( src ) ) )
        {
            std::vector< _size_t > src_offsets( MAX_NUM_PTRS );
            std::vector< _size_t > src_counts( MAX_NUM_PTRS );
            std::vector< _size_t > src_sizes( MAX_NUM_PTRS );

            SIXTRL_BUFFER_ARGPTR_DEC E* target = ptr_obj_to_update;

            if( ( st::CObjElem_field_offsets< E >( target_offsets.data(),
                    MAX_NUM_PTRS, target ) == st::COBJECTS_STATUS_SUCCESS ) &&
                ( st::CObjElem_field_sizes< E >( target_sizes.data(),
                    MAX_NUM_PTRS, target ) == st::COBJECTS_STATUS_SUCCESS ) &&
                ( st::CObjElem_field_counts< E >( target_counts.data(),
                    MAX_NUM_PTRS, target ) == st::COBJECTS_STATUS_SUCCESS ) &&
                ( st::CObjElem_field_offsets< E >( src_offsets.data(),
                    MAX_NUM_PTRS, src ) == st::COBJECTS_STATUS_SUCCESS ) &&
                ( st::CObjElem_field_sizes< E >( src_sizes.data(),
                    MAX_NUM_PTRS, src ) == st::COBJECTS_STATUS_SUCCESS ) &&
                ( st::CObjElem_field_counts< E >( src_counts.data(),
                    MAX_NUM_PTRS, src ) == st::COBJECTS_STATUS_SUCCESS ) )
            {
                if( ( std::equal( target_offsets.data(),
                                  target_offsets.data() + num_pointers,
                                  src_offsets.data() ) ) &&
                    ( std::equal( target_sizes.data(),
                                  target_sizes.data() + num_pointers,
                                  src_sizes.data() ) ) &&
                    ( std::equal( target_counts.data(),
                                  target_counts.data() + num_pointers,
                                  src_counts.data() ) ) )
                {
                    status = st::COBJECTS_STATUS_SUCCESS;
                }
            }
        }

        if( status == st::COBJECTS_STATUS_SUCCESS )
        {
            std::vector< _size_t > save_ptrs( MAX_NUM_PTRS );

            status =
            ::NS(CObjFlatBuffer_load_obj_same_layout_parameters_to_argptr)(
                buffer, pos_in_buffer, slot_size, st::CObjElem_type_id< E >(),
                    ptr_obj_to_update, sizeof( E ), num_pointers,
                        target_offsets.data(), target_sizes.data(),
                            target_counts.data(), save_ptrs.data() );
        }

        #else /* _GPUCODE */

        ( void )buffer;
        ( void )slot_size;
        ( void )pos_in_buffer;
        ( void )ptr_obj_to_update;

        #endif /* _GPUCODE */

        return status;
    }

    template< class Derived >
    static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
       !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< Derived >() &&
        SIXTRL_CXX_NAMESPACE::CObjElem_is_cobj_storage_interface< Derived >(),
        cobj_status_t >::type
    CObjElem_load_from_flat_cbuffer_to_argptr(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t) const* SIXTRL_RESTRICT buffer,
        NS(cobj_size_t) const pos_in_buffer, NS(cobj_size_t) const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC Derived* SIXTRL_RESTRICT ptr_obj_to_update )
    {
        typedef typename Derived::obj_data_t E;
        SIXTRL_BUFFER_ARGPTR_DEC E* _ptr = ( ptr_obj_to_update != nullptr )
            ? ptr_obj_to_update->as_ptr_data() : nullptr;

        return SIXTRL_CXX_NAMESPACE::CObjElem_load_from_flat_cbuffer_to_argptr<
            E >( buffer, pos_in_buffer, slot_size, _ptr );
    }

    template< class E >
    static SIXTRL_FN constexpr typename std::enable_if<
       !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
       !SIXTRL_CXX_NAMESPACE::CObjElem_is_cobj_storage_interface< E >(),
        cobj_status_t >::type
    CObjElem_load_from_flat_cbuffer_to_argptr(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t) const*
            SIXTRL_RESTRICT /*buffer*/,
        NS(cobj_size_t) const /*pos_in_buffer*/,
        NS(cobj_size_t) const /*slot_size*/,
        SIXTRL_BUFFER_ARGPTR_DEC E* SIXTRL_RESTRICT
            /*ptr_to_source*/ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::COBJECTS_STATUS_GENERAL_FAILURE;
    }

    /* ===================================================================== */
    /* "Store" (i.e.: update) an object stored in the buffer from an instance
     * not stored on the buffer.
     *
     * For the moment, we will only provide implementations for the case where
     * the layout parameters of the source and target object are identical */

    template< class E >
    static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case01_direct_no_ptrs< E >(),
        cobj_status_t >::type
    CObjElem_store_to_flat_cbuffer_from_argptr(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t)* SIXTRL_RESTRICT buffer,
        NS(cobj_size_t) const pos_in_buffer, NS(cobj_size_t) const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT ptr_to_source
    ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef st::cobj_size_t _size_t;

        return ::NS(CObjFlatBuffer_store_obj_same_layout_parameters_from_argptr)(
            buffer, pos_in_buffer, slot_size, st::CObjElem_type_id< E >(),
                ptr_to_source, sizeof( E ), _size_t{ 0 },
                    nullptr, nullptr, nullptr, nullptr );
    }

    template< class E >
    static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case02_direct_fixed_few< E >(),
        cobj_status_t >::type
    CObjElem_store_to_flat_cbuffer_from_argptr(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t)* SIXTRL_RESTRICT buffer,
        NS(cobj_size_t) const pos_in_buffer,
        NS(cobj_size_t) const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT ptr_to_source
    ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef st::cobj_size_t _size_t;

        cobj_status_t status = st::COBJECTS_STATUS_GENERAL_FAILURE;

        _size_t constexpr MAX_NUM_PTRS = st::CObjElem_max_num_ptrs< E >();
        _size_t counts[ MAX_NUM_PTRS ];
        _size_t save_ptrs[ MAX_NUM_PTRS ];

        if( st::CObjElem_field_counts< E >( &counts[ 0 ], MAX_NUM_PTRS,
                ptr_to_source ) == st::COBJECTS_STATUS_SUCCESS )
        {
            status =
            ::NS(CObjFlatBuffer_store_obj_same_layout_parameters_from_argptr)(
                buffer, pos_in_buffer, slot_size, st::CObjElem_type_id< E >(),
                ptr_to_source, sizeof( E ), MAX_NUM_PTRS,
                st::CObjElem_field_offsets_ptr_constexpr_begin< E >(),
                st::CObjElem_field_sizes_ptr_constexpr_begin< E >(),
                &counts[ 0 ], &save_ptrs[ 0 ] );
        }

        return status;
    }

    template< class E >
    static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case03_direct_few< E >(),
        cobj_status_t >::type
    CObjElem_store_to_flat_cbuffer_from_argptr(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t)* SIXTRL_RESTRICT buffer,
        NS(cobj_size_t) const pos_in_buffer,
        NS(cobj_size_t) const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT ptr_to_source
    ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef st::cobj_size_t _size_t;

        cobj_status_t status = st::COBJECTS_STATUS_GENERAL_FAILURE;

        _size_t constexpr MAX_NUM_PTRS = st::CObjElem_max_num_ptrs< E >();
        static_assert( MAX_NUM_PTRS > _size_t{ 0 },
            "Expected to have dataptrs here" );

        SIXTRL_BUFFER_OBJ_DATAPTR_DEC E* target =
            st::CObjElem_from_cobj_index< E >( ::NS(CObjFlatBuffer_index)(
                buffer, pos_in_buffer, slot_size ), slot_size );

        _size_t const num_pointers = st::CObjElem_num_ptrs<
            E >( ptr_to_source );

        SIXTRL_ASSERT( num_pointers <= MAX_NUM_PTRS );

        _size_t src_offsets[ MAX_NUM_PTRS ];
        _size_t src_counts[ MAX_NUM_PTRS ];
        _size_t src_sizes[ MAX_NUM_PTRS ];

        if( ( target != nullptr ) &&
            ( num_pointers == st::CObjElem_num_ptrs< E >( target ) ) )
        {
            _size_t target_offsets[ MAX_NUM_PTRS ];
            _size_t target_counts[ MAX_NUM_PTRS ];
            _size_t target_sizes[ MAX_NUM_PTRS ];

            SIXTRL_BUFFER_ARGPTR_DEC const E *const src = ptr_to_source;

            if( ( st::CObjElem_field_offsets< E >( &target_offsets[ 0 ],
                    MAX_NUM_PTRS, src ) == st::COBJECTS_STATUS_SUCCESS ) &&
                ( st::CObjElem_field_sizes< E >( &target_sizes[ 0 ],
                    MAX_NUM_PTRS, src ) == st::COBJECTS_STATUS_SUCCESS ) &&
                ( st::CObjElem_field_counts< E >( &target_counts[ 0 ],
                    MAX_NUM_PTRS, src ) == st::COBJECTS_STATUS_SUCCESS ) &&
                ( st::CObjElem_field_offsets< E >( &src_offsets[ 0 ],
                    MAX_NUM_PTRS, target ) == st::COBJECTS_STATUS_SUCCESS ) &&
                ( st::CObjElem_field_sizes< E >( &src_sizes[ 0 ],
                    MAX_NUM_PTRS, target ) == st::COBJECTS_STATUS_SUCCESS ) &&
                ( st::CObjElem_field_counts< E >( &src_counts[ 0 ],
                    MAX_NUM_PTRS, target ) == st::COBJECTS_STATUS_SUCCESS ) )
            {
                status = st::COBJECTS_STATUS_SUCCESS;

                for( _size_t ii = _size_t{ 0 } ; ii < num_pointers ; ++ii )
                {
                    if( ( src_offsets[ ii ] != target_offsets[ ii ] ) ||
                        ( src_sizes[ ii ]   != target_sizes[ ii ]   ) ||
                        ( src_counts[ ii ]  != target_counts[ ii ]  ) )
                    {
                        status = st::COBJECTS_STATUS_GENERAL_FAILURE;
                        break;
                    }
                }
            }
        }

        if( status == st::COBJECTS_STATUS_SUCCESS )
        {
            _size_t save_ptrs[ MAX_NUM_PTRS ];

            status =
            ::NS(CObjFlatBuffer_store_obj_same_layout_parameters_from_argptr)(
                buffer, pos_in_buffer, slot_size, st::CObjElem_type_id< E >(),
                    ptr_to_source, sizeof( E ), num_pointers, &src_offsets[ 0 ],
                        &src_sizes[ 0 ], &src_counts[ 0 ], &save_ptrs[ 0 ] );
        }

        return status;
    }

    template< class E >
    static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case04_direct< E >(),
        cobj_status_t >::type
    CObjElem_load_from_flat_cbuffer_to_argptr(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t) const* SIXTRL_RESTRICT buffer,
        NS(cobj_size_t) const pos_in_buffer, NS(cobj_size_t) const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT ptr_to_source )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::cobj_status_t status = st::COBJECTS_STATUS_GENERAL_FAILURE;

        #if !defined( _GPUCODE )

        typedef st::cobj_size_t _size_t;
        _size_t constexpr MAX_NUM_PTRS = st::CObjElem_max_num_ptrs< E >();

        static_assert( MAX_NUM_PTRS > _size_t{ 0 },
            "Expected to have dataptrs here" );

        SIXTRL_BUFFER_OBJ_DATAPTR_DEC E* target =
            st::CObjElem_from_cobj_index< E >( ::NS(CObjFlatBuffer_const_index)(
                buffer, pos_in_buffer, slot_size ), slot_size );

        _size_t const num_ptrs = st::CObjElem_num_ptrs< E >( ptr_to_source );

        SIXTRL_ASSERT( num_ptrs <= MAX_NUM_PTRS );

        std::vector< _size_t > src_offsets( MAX_NUM_PTRS );
        std::vector< _size_t > src_counts( MAX_NUM_PTRS );
        std::vector< _size_t > src_sizes( MAX_NUM_PTRS );

        if( ( target != nullptr ) &&
            ( num_ptrs == st::CObjElem_num_ptrs< E >( target ) ) )
        {
            std::vector< _size_t > target_offsets( MAX_NUM_PTRS );
            std::vector< _size_t > target_counts( MAX_NUM_PTRS );
            std::vector< _size_t > target_sizes( MAX_NUM_PTRS );

            SIXTRL_BUFFER_ARGPTR_DEC const E *const src = ptr_to_source;

            if( ( st::CObjElem_field_offsets< E >( target_offsets.data(),
                    MAX_NUM_PTRS, target ) == st::COBJECTS_STATUS_SUCCESS ) &&
                ( st::CObjElem_field_sizes< E >( target_sizes.data(),
                    MAX_NUM_PTRS, target ) == st::COBJECTS_STATUS_SUCCESS ) &&
                ( st::CObjElem_field_counts< E >( target_counts.data(),
                    MAX_NUM_PTRS, target ) ==
                        st::COBJECTS_STATUS_SUCCESS ) &&
                ( st::CObjElem_field_offsets< E >( src_offsets.data(),
                    MAX_NUM_PTRS, src ) == st::COBJECTS_STATUS_SUCCESS ) &&
                ( st::CObjElem_field_sizes< E >( src_sizes.data(),
                    MAX_NUM_PTRS, src ) == st::COBJECTS_STATUS_SUCCESS ) &&
                ( st::CObjElem_field_counts< E >( src_counts.data(),
                    MAX_NUM_PTRS, src ) == st::COBJECTS_STATUS_SUCCESS ) )
            {
                if( ( std::equal( target_offsets.data(),
                        target_offsets.data() + num_ptrs,
                        src_offsets.data() ) ) &&
                    ( std::equal( target_sizes.data(),
                        target_sizes.data() + num_ptrs, src_sizes.data() ) ) &&
                    ( std::equal( target_counts.data(),
                        target_counts.data() + num_ptrs, src_counts.data() ) ))
                {
                    status = st::COBJECTS_STATUS_SUCCESS;
                }
            }
        }

        if( status == st::COBJECTS_STATUS_SUCCESS )
        {
            std::vector< _size_t > save_ptrs( MAX_NUM_PTRS );

            status =
            ::NS(CObjFlatBuffer_load_obj_same_layout_parameters_to_argptr)(
                buffer, pos_in_buffer, slot_size, st::CObjElem_type_id< E >(),
                    ptr_to_source, sizeof( E ), num_ptrs, src_offsets.data(),
                        src_sizes.data(), src_counts.data(), save_ptrs.data());
        }

        #else /* _GPUCODE */

        ( void )buffer;
        ( void )slot_size;
        ( void )pos_in_buffer;
        ( void )ptr_to_source;

        #endif /* _GPUCODE */

        return status;
    }

    template< class Derived >
    static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
       !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< Derived >() &&
        SIXTRL_CXX_NAMESPACE::CObjElem_is_cobj_storage_interface< Derived >(),
        cobj_status_t >::type
    CObjElem_store_to_flat_cbuffer_from_argptr(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t)* SIXTRL_RESTRICT buffer,
        NS(cobj_size_t) const pos_in_buffer, NS(cobj_size_t) const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC const Derived *const
            SIXTRL_RESTRICT ptr_to_source )
    {
        typedef typename Derived::obj_data_t E;
        SIXTRL_BUFFER_ARGPTR_DEC E* _ptr = ( ptr_to_source != nullptr )
            ? ptr_to_source->as_ptr_data() : nullptr;

        return SIXTRL_CXX_NAMESPACE::CObjElem_load_from_flat_cbuffer_to_argptr<
            E >( buffer, pos_in_buffer, slot_size, _ptr );
    }


    template< class E >
    static SIXTRL_FN constexpr typename std::enable_if<
       !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
       !SIXTRL_CXX_NAMESPACE::CObjElem_is_cobj_storage_interface< E >(),
        cobj_status_t >::type
    CObjElem_store_to_flat_cbuffer_from_argptr(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t)* SIXTRL_RESTRICT /*buffer*/,
        NS(cobj_size_t) const /*pos_in_buffer*/,
        NS(cobj_size_t) const /*slot_size*/,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const
            SIXTRL_RESTRICT /*ptr_to_source*/ ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::COBJECTS_STATUS_GENERAL_FAILURE;
    }

    /* ********************************************************************* */
    /* Support for checking whether a copy of an object can be added:        */

    template< class E >
    static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case01_direct_no_ptrs< E >(),
        bool >::type
    CObjElem_can_add_copy_of_object(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t) const* SIXTRL_RESTRICT buffer,
        cobj_size_t const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT /* ptr_elem */,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT requ_buffer_size,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT requ_num_slots,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT requ_num_objs,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT requ_num_ptrs
    ) SIXTRL_NOEXCEPT
    {
        return ::NS(CObjFlatBuffer_can_add_copy_of_object)(
            buffer, slot_size, sizeof( E ), cobj_size_t{ 0 }, nullptr, nullptr,
                requ_buffer_size, requ_num_slots,
                    requ_num_objs, requ_num_ptrs );
    }

    template< class E >
    static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case02_direct_fixed_few< E >(),
        bool >::type
    CObjElem_can_add_copy_of_object(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t) const* SIXTRL_RESTRICT buffer,
        cobj_size_t const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT ptr_elem,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT requ_buffer_size,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT requ_num_slots,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT requ_num_objs,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT requ_num_ptrs
    ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef st::cobj_size_t _size_t;

        _size_t constexpr MAX_NUM_PTRS = st::CObjElem_max_num_ptrs< E >();
        _size_t counts[ MAX_NUM_PTRS ];

        return (
            ( st::CObjElemFieldCounts< E >::init_field_counts( &counts[ 0 ],
                MAX_NUM_PTRS, ptr_elem ) == st::COBJECTS_STATUS_SUCCESS ) &&
            ( ::NS(CObjFlatBuffer_can_add_copy_of_object)( buffer, slot_size,
                sizeof( E ), MAX_NUM_PTRS,
                    st::CObjElem_field_sizes_ptr_constexpr_begin< E >(),
                    &counts[ 0 ], requ_buffer_size, requ_num_slots,
                        requ_num_objs, requ_num_ptrs ) ) );
    }

    template< class E >
    static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case03_direct_few< E >(),
        bool >::type
    CObjElem_can_add_copy_of_object(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t) const* SIXTRL_RESTRICT buffer,
        cobj_size_t const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT ptr_elem,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT requ_buffer_size,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT requ_num_slots,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT requ_num_objs,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT requ_num_ptrs
    ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef st::cobj_size_t _size_t;

        _size_t constexpr MAX_NUM_PTRS = st::CObjElem_max_num_ptrs< E >();
        _size_t const num_pointers =
            st::CObjElem_num_ptrs< E >( ptr_elem );

        SIXTRL_ASSERT( num_pointers <= MAX_NUM_PTRS );

        _size_t sizes[ MAX_NUM_PTRS ];
        _size_t counts[ MAX_NUM_PTRS ];

        return (
            ( st::COBJECTS_STATUS_SUCCESS == st::CObjElem_field_sizes< E >(
                &sizes[ 0 ], MAX_NUM_PTRS, ptr_elem ) ) &&
            ( st::CObjElemFieldCounts< E >::init_field_counts( &counts[ 0 ],
                MAX_NUM_PTRS, ptr_elem ) == st::COBJECTS_STATUS_SUCCESS ) &&
            ( ::NS(CObjFlatBuffer_can_add_copy_of_object)( buffer, slot_size,
                sizeof( E ), num_pointers, &sizes[ 0 ], &counts[ 0 ],
                    requ_buffer_size, requ_num_slots, requ_num_objs,
                        requ_num_ptrs ) ) );
    }

    template< class E >
    static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case04_direct< E >(), bool >::type
    CObjElem_can_add_copy_of_object(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t) const* SIXTRL_RESTRICT buffer,
        cobj_size_t const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT ptr_elem,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT requ_buffer_size,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT requ_num_slots,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT requ_num_objs,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT requ_num_ptrs )
    {
        #if !defined( _GPUCODE )

        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef st::cobj_size_t _size_t;

        _size_t constexpr MAX_NUM_PTRS = st::CObjElem_max_num_ptrs< E >();
        _size_t const num_pointers =
            st::CObjElem_num_ptrs< E >( ptr_elem );

        SIXTRL_ASSERT( num_pointers <= MAX_NUM_PTRS );

        std::vector< _size_t > sizes( MAX_NUM_PTRS );
        std::vector< _size_t > counts( MAX_NUM_PTRS );

        return (
            ( st::COBJECTS_STATUS_SUCCESS == st::CObjElem_field_sizes< E >(
                sizes.data(), MAX_NUM_PTRS, ptr_elem ) ) &&
            ( st::CObjElemFieldCounts< E >::init_field_counts( counts.data(),
                MAX_NUM_PTRS, ptr_elem ) == st::COBJECTS_STATUS_SUCCESS ) &&
            ( ::NS(CObjFlatBuffer_can_add_copy_of_object)( buffer, slot_size,
                sizeof( E ), num_pointers, sizes.data(), counts.data(),
                    requ_buffer_size, requ_num_slots, requ_num_objs,
                        requ_num_ptrs ) ) );

        #else /* _GPUCODE */
        ( void )buffer;
        ( void )slot_size;
        ( void )ptr_elem;
        ( void )requ_buffer_size;
        ( void )requ_num_slots;
        ( void )requ_num_objs;
        ( void )requ_num_ptrs;

        return false;

        #endif /* _GPUCODE */
    }

    template< class Derived >
    static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_allow_derived_storage< Derived >(),
        bool >::type
    CObjElem_can_add_copy_of_object(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t) const* SIXTRL_RESTRICT buffer,
        cobj_size_t const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC const Derived *const SIXTRL_RESTRICT ptr_elem,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT requ_buffer_size,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT requ_num_slots,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT requ_num_objs,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT requ_num_ptrs )
    {
        typedef typename Derived::obj_data_t E;
        SIXTRL_BUFFER_DATAPTR_DEC E const* _ptr = ( ptr_elem != nullptr )
            ? ptr_elem->as_ptr_data() : nullptr;

        return SIXTRL_CXX_NAMESPACE::CObjElem_can_add_copy_of_object< E >(
            buffer, slot_size, _ptr, requ_buffer_size, requ_num_slots,
                requ_num_objs, requ_num_ptrs );
    }

    template< class E >
    static SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
        !SIXTRL_CXX_NAMESPACE::CObjElem_allow_derived_storage< E >(),
        bool >::type
    CObjElem_can_add_copy_of_object(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t) const*
            SIXTRL_RESTRICT /*buffer*/,
        cobj_size_t const /*slot_size*/,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT /*ptr_elem*/,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT
            /*requ_buffer_size*/,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT
            /*requ_num_slots*/,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT
            /*requ_num_objs*/,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT
            /*requ_num_ptrs*/ ) SIXTRL_NOEXCEPT
    {
        return false;
    }

    /* ********************************************************************* */
    /* Support for adding copies of elements:                                */

    template< class E >
    static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case01_direct_no_ptrs< E >(),
        SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* >::type
    CObjElem_add_copy_of_object_impl(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t)* SIXTRL_RESTRICT buffer,
        cobj_size_t const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT ptr_elem,
        bool const init_with_zeros = false ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef cobj_size_t _size_t;
        _size_t constexpr obj_size = sizeof( E );

        return ::NS(CObjFlatBuffer_add_copy_of_object)( buffer, slot_size,
            ptr_elem, obj_size, st::CObjElem_type_id< E >(), _size_t{ 0 },
                nullptr, nullptr, nullptr, init_with_zeros );
    }

    template< class E >
    static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case02_direct_fixed_few< E >(),
        SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* >::type
    CObjElem_add_copy_of_object_impl(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t)* SIXTRL_RESTRICT buffer,
        cobj_size_t const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT elem,
        bool const init_with_zeros = false ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        NS(ptr_cobj_index_t) index_added_obj = nullptr;

        st::cobj_size_t constexpr MAX_NUM_PTRS =
            st::CObjElem_max_num_ptrs< E >();
        st::cobj_size_t counts[ MAX_NUM_PTRS ];

        if( st::CObjElemFieldCounts< E >::init_field_counts( &counts[ 0 ],
                MAX_NUM_PTRS, elem ) == st::COBJECTS_STATUS_SUCCESS )
        {
            index_added_obj = ::NS(CObjFlatBuffer_add_copy_of_object)(
                buffer, slot_size, elem, sizeof( E ),
                    st::CObjElem_type_id< E >(), MAX_NUM_PTRS,
                    st::CObjElem_field_offsets_ptr_constexpr_begin< E >(),
                        st::CObjElem_field_sizes_ptr_constexpr_begin< E >(),
                            &counts[ 0 ], init_with_zeros );
        }

        return index_added_obj;
    }

    template< class E >
    static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case03_direct_few< E >(),
        SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* >::type
    CObjElem_add_copy_of_object_impl(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t)* SIXTRL_RESTRICT buffer,
        cobj_size_t const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT elem,
        bool const init_with_zeros = false ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        NS(ptr_cobj_index_t) index_added_obj = nullptr;

        st::cobj_size_t constexpr MAX_NUM_PTRS =
            st::CObjElem_max_num_ptrs< E >();

        st::cobj_size_t offsets[ MAX_NUM_PTRS ];
        st::cobj_size_t sizes[ MAX_NUM_PTRS ];
        st::cobj_size_t counts[ MAX_NUM_PTRS ];

        st::cobj_size_t const num_pointers =
            st::CObjElem_num_ptrs< E >( elem );

        SIXTRL_ASSERT( num_pointers <= MAX_NUM_PTRS );

        if( ( st::CObjElem_field_offsets< E >( &offsets[ 0 ], MAX_NUM_PTRS,
                elem ) == st::COBJECTS_STATUS_SUCCESS ) &&
            ( st::CObjElem_field_sizes< E >( &sizes[ 0 ], MAX_NUM_PTRS,
                elem ) == st::COBJECTS_STATUS_SUCCESS ) &&
            ( st::CObjElem_field_counts< E >( &counts[ 0 ], MAX_NUM_PTRS,
                elem ) == st::COBJECTS_STATUS_SUCCESS ) )
        {
            index_added_obj = ::NS(CObjFlatBuffer_add_copy_of_object)( buffer,
                slot_size, elem, sizeof( E ), st::CObjElem_type_id< E >(),
                    num_pointers, &offsets[ 0 ], &sizes[ 0 ], &counts[ 0 ],
                        init_with_zeros);
        }

        return index_added_obj;
    }

    template< class E >
    static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case04_direct< E >(),
        SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* >::type
    CObjElem_add_copy_of_object_impl(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t)* SIXTRL_RESTRICT buffer,
        cobj_size_t const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT elem,
        bool const init_with_zeros = false )
    {
        NS(ptr_cobj_index_t) index_added_obj = nullptr;

        #if !defined( _GPUCODE )
        namespace st = SIXTRL_CXX_NAMESPACE;

        st::cobj_size_t constexpr MAX_NUM_PTRS =
            st::CObjElem_max_num_ptrs< E >();

        std::vector< cobj_size_t > offsets( MAX_NUM_PTRS );
        std::vector< cobj_size_t > sizes( MAX_NUM_PTRS );
        std::vector< cobj_size_t > counts( MAX_NUM_PTRS );

        st::cobj_size_t const num_pointers =
            st::CObjElem_num_ptrs< E >( elem );

        SIXTRL_ASSERT( num_pointers <= MAX_NUM_PTRS );

        if( ( st::CObjElem_field_offsets< E >( offsets.data(), MAX_NUM_PTRS,
                elem ) == st::COBJECTS_STATUS_SUCCESS ) &&
            ( st::CObjElem_field_sizes< E >( sizes.data(), MAX_NUM_PTRS,
                elem ) == st::COBJECTS_STATUS_SUCCESS ) &&
            ( st::CObjElem_field_counts< E >( counts.data(), MAX_NUM_PTRS,
                elem ) == st::COBJECTS_STATUS_SUCCESS ) )
        {
            index_added_obj = ::NS(CObjFlatBuffer_add_copy_of_object)( buffer,
                slot_size, elem, sizeof( E ), st::CObjElem_type_id< E >(),
                    num_pointers, offsets.data(), sizes.data(), counts.data(),
                        init_with_zeros );
        }

        #else /* _GPUCODE */
        ( void )buffer;
        ( void )slot_size;
        ( void )elem;
        ( void )init_with_zeros;

        #endif /* _GPUCODE */

        return index_added_obj;
    }

    template< class Derived >
    static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_allow_derived_storage< Derived >(),
        SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* >::type
    CObjElem_add_copy_of_object_impl(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t)* SIXTRL_RESTRICT buffer,
        cobj_size_t const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC const Derived *const SIXTRL_RESTRICT elem,
        bool const init_with_zeros = false )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename Derived::obj_data_t E;
        SIXTRL_BUFFER_DATAPTR_DEC E const* _ptr = ( elem != nullptr )
            ? elem->as_ptr_data() : nullptr;

        return st::CObjElem_add_copy_of_object_impl(
            buffer, slot_size, _ptr, init_with_zeros );
    }

    template< class E >
    static SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
        !SIXTRL_CXX_NAMESPACE::CObjElem_allow_derived_storage< E >(),
        SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* >::type
    CObjElem_add_copy_of_object_impl(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t)* SIXTRL_RESTRICT /*buffer*/,
        cobj_size_t const /*slot_size*/,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT /*ptr_elem*/,
        bool const /* init_with_zeros */ ) SIXTRL_NOEXCEPT
    {
        return false;
    }

    /* --------------------------------------------------------------------- */

    template< class E >
    static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() ||
        SIXTRL_CXX_NAMESPACE::CObjElem_allow_derived_storage< E >(),
        SIXTRL_BUFFER_OBJ_DATAPTR_DEC E* >::type
    CObjElem_add_copy_of_object(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t)* SIXTRL_RESTRICT buffer,
        cobj_size_t const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT ptr_elem,
        bool const init_with_zeros = false )
    {
        return reinterpret_cast< SIXTRL_BUFFER_OBJ_DATAPTR_DEC E* >(
            static_cast< uintptr_t >( ::NS(CObjIndex_begin_addr)(
                SIXTRL_CXX_NAMESPACE::CObjElem_add_copy_of_object_impl(
                    buffer, slot_size, ptr_elem, init_with_zeros ) ) ) );
    }
}

#endif /* _cplusplus */
#endif /* SIXTRACKLIB_COMMON_COBJECTS_ELEMENT_STORE_RESTORE_CXX_HPP__ */
