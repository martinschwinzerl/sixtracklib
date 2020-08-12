#ifndef SIXTRACKLIB_BASE_COBJECTS_ELEMENT_STORE_RESTORE_H__
#define SIXTRACKLIB_BASE_COBJECTS_ELEMENT_STORE_RESTORE_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/cobjects/definitions.h"
    #include "sixtracklib_base/cobjects/index_object.h"
    #include "sixtracklib_base/cobjects/flat_buffer.h"
    #include "sixtracklib_base/cobjects/element_pointers.h"
    #include "sixtracklib_base/cobjects/field_offsets.h"
    #include "sixtracklib_base/cobjects/field_sizes.h"
    #include "sixtracklib_base/cobjects/field_counts.h"
    #include "sixtracklib_base/internal/compiler_attributes.h"
    #include "sixtracklib_base/internal/obj_store_traits.h"
#endif /* SIXTRL_NO_INCLUDES */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <algorithm>
        #include <type_traits>
        #include <vector>
    #endif /* defined( __cplusplus ) */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    /* ********************************************************************* */
    /* Define a set of cases, based on the different pointer - scenarios, to
     * provide differentiated implementations */

    template< class E > static SIXTRL_FN constexpr bool
    CObjElem_ptrs_case01_direct_no_ptrs() SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
               SIXTRL_CXX_NAMESPACE::CObjElem_definitely_has_no_ptrs< E >();
    }

    template< class E > static SIXTRL_FN constexpr bool
    CObjElem_ptrs_case02_direct_fixed_few() SIXTRL_NOEXCEPT
    {
        return
        SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
       !SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case01_direct_no_ptrs< E >() &&
        SIXTRL_CXX_NAMESPACE::CObjElem_few_enough_ptrs_for_static_array< E >();
    }

    template< class E > static SIXTRL_FN constexpr bool
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

    template< class E > static SIXTRL_FN constexpr bool
    CObjElem_ptrs_case04_direct() SIXTRL_NOEXCEPT
    {
        #if !defined( _GPUCODE )
        return
        SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
        SIXTRL_CXX_NAMESPACE::CObjElem_too_many_ptrs_for_static_array< E >();

        #else
        return false;

        #endif /* !defined( _GPUCODE ) */
    }

    template< class E > static SIXTRL_FN constexpr bool
    CObjElem_ptrs_case99_undefined() SIXTRL_NOEXCEPT
    {
        return (
        !SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case01_direct_no_ptrs< E >() &&
        !SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case02_direct_fixed_few< E >() &&
        !SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case03_direct_few< E >() &&
        !SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case04_direct< E >() );
    }

    /* ********************************************************************* */
    /* Provide CObjElem_required_num_objects: */

    template< class E > static SIXTRL_FN constexpr typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElemTypeId_is_illegal< E >(),
        SIXTRL_CXX_NAMESPACE::size_t >::type
    CObjElem_required_num_objects(
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( ptr_elem ) = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::size_t{ 0 };
    }

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElemTypeId_is_legal< E >(),
        SIXTRL_CXX_NAMESPACE::size_t >::type
    CObjElem_required_num_objects(
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( ptr_elem ) = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::size_t{ 1 };
    }


    /* ********************************************************************* */
    /* Provide template version of NS(CObjFlatBuffer_slot_based_size)() */

    /* First, implement specialized versions based on different pointer
     * scenarios */

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case01_direct_no_ptrs< E >() &&
       !SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< E >(),
        SIXTRL_CXX_NAMESPACE::size_t >::type CObjElem_required_num_bytes(
        SIXTRL_CXX_NAMESPACE::size_t const slot_size =
            SIXTRL_CXX_NAMESPACE::CBUFFER_DEFAULT_SLOT_SIZE,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( ptr_elem ) = nullptr ) SIXTRL_NOEXCEPT
    {
        return ::NS(CObjFlatBuffer_slot_based_size)( sizeof( E ), slot_size );
    }

    /*  -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case02_direct_fixed_few< E >() &&
       !SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< E >(),
        SIXTRL_CXX_NAMESPACE::size_t >::type CObjElem_required_num_bytes(
        SIXTRL_CXX_NAMESPACE::size_t const slot_size =
            SIXTRL_CXX_NAMESPACE::CBUFFER_DEFAULT_SLOT_SIZE,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT ptr_elem =
            nullptr ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::size_t slot_based_size = st::size_t{ 0 };

        st::size_t constexpr MAX_NUM_PTRS = st::CObjElem_max_num_ptrs< E >();
        SIXTRL_BUFFER_ARGPTR_DEC st::size_t counts[ MAX_NUM_PTRS ];

        if( st::CObjElemFieldCounts< E >::init_field_counts(
                &counts[ 0 ], MAX_NUM_PTRS, ptr_elem ) ==
                    st::STATUS_SUCCESS )
        {
            slot_based_size = ::NS(CObjFlatBuffer_predict_required_num_bytes)(
                sizeof( E ), MAX_NUM_PTRS, &CObjElemFieldSizes< E >::sizes[ 0 ],
                    &counts[ 0 ], slot_size );
        }

        return slot_based_size;
    }

    /*  -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case03_direct_few< E >() &&
       !SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< E >() ,
        SIXTRL_CXX_NAMESPACE::size_t >::type CObjElem_required_num_bytes(
        SIXTRL_CXX_NAMESPACE::size_t const slot_size =
            SIXTRL_CXX_NAMESPACE::CBUFFER_DEFAULT_SLOT_SIZE,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT ptr_elem =
            nullptr ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::size_t slot_based_size = st::size_t{ 0 };
        st::size_t constexpr MAX_NUM_PTRS = st::CObjElem_max_num_ptrs< E >();

        SIXTRL_BUFFER_ARGPTR_DEC st::size_t sizes[ MAX_NUM_PTRS ];
        SIXTRL_BUFFER_ARGPTR_DEC st::size_t counts[ MAX_NUM_PTRS ];
        st::size_t const num_ptrs = st::CObjElem_num_ptrs< E >( ptr_elem );
        SIXTRL_ASSERT( num_ptrs <= MAX_NUM_PTRS );

        if( ( st::CObjElem_field_sizes< E >( &sizes[ 0 ], MAX_NUM_PTRS,
                ptr_elem ) == st::STATUS_SUCCESS ) &&
            ( CObjElemFieldCounts< E >::init_field_counts( &counts[ 0 ],
                MAX_NUM_PTRS, ptr_elem ) == st::STATUS_SUCCESS ) )
        {
            slot_based_size = ::NS(CObjFlatBuffer_predict_required_num_bytes)(
                sizeof( E ), num_ptrs, &sizes[ 0 ], &counts[ 0 ], slot_size );
        }

        return slot_based_size;
    }

    /*  -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case04_direct< E >() &&
       !SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< E >() ,
        SIXTRL_CXX_NAMESPACE::size_t >::type CObjElem_required_num_bytes(
        SIXTRL_CXX_NAMESPACE::size_t const slot_size =
            SIXTRL_CXX_NAMESPACE::CBUFFER_DEFAULT_SLOT_SIZE,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT ptr_elem =
            nullptr ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::size_t slot_based_size = st::size_t{ 0 };

        #if !defined( _GPUCODE )

        st::size_t constexpr MAX_NUM_PTRS = st::CObjElem_max_num_ptrs< E >();
        st::size_t const num_ptrs = st::CObjElem_num_ptrs< E >( ptr_elem );
        SIXTRL_ASSERT( num_ptrs <= MAX_NUM_PTRS );

        std::vector< st::size_t > sizes( MAX_NUM_PTRS );
        std::vector< st::size_t > counts( MAX_NUM_PTRS );

        SIXTRL_ASSERT( sizes.size()  >= MAX_NUM_PTRS );
        SIXTRL_ASSERT( counts.size() >= MAX_NUM_PTRS );

        if( ( st::CObjElem_field_sizes< E >( sizes.data(), sizes.size(),
                ptr_elem ) == st::STATUS_SUCCESS ) &&
            ( st::CObjElem_field_counts< E >( counts.data(), counts.size(),
                ptr_elem ) == st::STATUS_SUCCESS ) )
        {
            slot_based_size = ::NS(CObjFlatBuffer_predict_required_num_bytes)(
                sizeof( E ), num_ptrs, sizes.data(), counts.data(), slot_size);
        }

        #else /* _GPUCODE */

        ( void )ptr_elem;
        ( void )slot_size;

        #endif /* _GPUCODE */

        return slot_based_size;
    }

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
        SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< E >(),
        SIXTRL_CXX_NAMESPACE::size_t >::type
    CObjElem_required_num_bytes( SIXTRL_CXX_NAMESPACE::size_t const slot_size =
            SIXTRL_CXX_NAMESPACE::CBUFFER_DEFAULT_SLOT_SIZE,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
            ptr_elem = nullptr ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_required_num_bytes<
            typename ObjDataCApiTypeTraits< E >::c_api_t >( slot_size,
                ObjData_bitcast_to_const_c_api< E >( ptr_elem ) );
    }

    template< class E > static SIXTRL_FN constexpr typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case99_undefined< E >(),
        SIXTRL_CXX_NAMESPACE::size_t >::type CObjElem_required_num_bytes(
        SIXTRL_CXX_NAMESPACE::size_t const SIXTRL_UNUSED( slot_size ) =
            SIXTRL_CXX_NAMESPACE::CBUFFER_DEFAULT_SLOT_SIZE,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( ptr_elem ) = nullptr ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::size_t{ 0 };
    }

    /* --------------------------------------------------------------------- */

    template< class E > static SIXTRL_FN SIXTRL_CXX_NAMESPACE::size_t
    CObjElem_required_num_slots( SIXTRL_CXX_NAMESPACE::size_t const slot_size =
            SIXTRL_CXX_NAMESPACE::CBUFFER_DEFAULT_SLOT_SIZE,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT ptr_elem =
            nullptr ) SIXTRL_NOEXCEPT
    {
        return ( slot_size > SIXTRL_CXX_NAMESPACE::size_t{ 0 } )
            ? SIXTRL_CXX_NAMESPACE::CObjElem_required_num_bytes< E >(
                slot_size, ptr_elem ) / slot_size
            : SIXTRL_CXX_NAMESPACE::size_t{ 0 };
    }

    /* ********************************************************************* */
    /* Direct restore -> only works with Elements E that support that
     * mode, cf. the sixtrack::CObjElem_allow_direct_storage< E >() predicate*/

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
        SIXTRL_CXX_NAMESPACE::CObjElemTypeId_is_legal< E >(),
        SIXTRL_BUFFER_OBJ_DATAPTR_DEC E const* >::type
    CObjElem_const_from_cobj_index( SIXTRL_BUFFER_OBJ_ARGPTR_DEC const
            ::NS(CObjIndex) *const SIXTRL_RESTRICT index_obj,
        SIXTRL_CXX_NAMESPACE::size_t const slot_size =
            SIXTRL_CXX_NAMESPACE::CBUFFER_DEFAULT_SLOT_SIZE,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( ptr_cls_elem ) = nullptr ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef SIXTRL_BUFFER_OBJ_DATAPTR_DEC E const* ptr_elem_t;

        static_assert( st::ObjData_can_be_memcopied< E >(),
            "Can only restore entities from a CObjects buffer which are "
            "suitable for memcpy -> use conversion for other entities" );

        return reinterpret_cast< ptr_elem_t >( reinterpret_cast< uintptr_t >(
            ::NS(CObjIndex_begin_addr_filter_by_type_info)( index_obj,
                st::CObjElem_type_id< E >(), sizeof( E ), slot_size ) ) );
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() ||
        !SIXTRL_CXX_NAMESPACE::CObjElemTypeId_is_legal< E >(),
        SIXTRL_BUFFER_OBJ_DATAPTR_DEC E const* >::type
    CObjElem_const_from_cobj_index( SIXTRL_BUFFER_OBJ_ARGPTR_DEC const
            ::NS(CObjIndex) *const SIXTRL_RESTRICT SIXTRL_UNUSED( index_obj ),
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( ptr_dummy_elem ) = nullptr ) SIXTRL_NOEXCEPT
    {
        return nullptr;
    }

    /* --------------------------------------------------------------------- */

    template< class E >
    static SIXTRL_INLINE SIXTRL_FN SIXTRL_BUFFER_OBJ_DATAPTR_DEC E*
    CObjElem_from_cobj_index(
        SIXTRL_BUFFER_OBJ_ARGPTR_DEC ::NS(CObjIndex)* SIXTRL_RESTRICT idx_obj,
        SIXTRL_CXX_NAMESPACE::size_t const slot_size =
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

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case01_direct_no_ptrs< E >() &&
       !SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< E >(),
        SIXTRL_CXX_NAMESPACE::status_t >::type
    CObjElem_load_from_flat_cbuffer_to_argptr(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t) const* SIXTRL_RESTRICT buffer,
        NS(size_t) const pos_in_buffer, NS(size_t) const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC E* SIXTRL_RESTRICT ptr_obj_to_update
    ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return ::NS(CObjFlatBuffer_load_obj_same_layout_parameters_to_argptr)(
            buffer, pos_in_buffer, slot_size, st::CObjElem_type_id< E >(),
                ptr_obj_to_update, sizeof( E ), st::size_t{ 0 },
                    nullptr, nullptr, nullptr, nullptr );
    }

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case01_direct_no_ptrs< E >() &&
        SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< E >(),
        SIXTRL_CXX_NAMESPACE::status_t >::type
    CObjElem_load_from_flat_cbuffer_to_argptr(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t) const* SIXTRL_RESTRICT buffer,
        NS(size_t) const pos_in_buffer, NS(size_t) const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC E* SIXTRL_RESTRICT ptr_obj_to_update
    ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename ObjDataCApiTypeTraits< E >::c_api_t c_api_t;

        return ::NS(CObjFlatBuffer_load_obj_same_layout_parameters_to_argptr)(
            buffer, pos_in_buffer, slot_size, st::CObjElem_type_id< c_api_t >(),
                st::ObjData_bitcast_to_c_api< E >( ptr_obj_to_update ),
                    sizeof( c_api_t ), st::size_t{ 0 }, nullptr, nullptr,
                        nullptr, nullptr );
    }

    /*  -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case02_direct_fixed_few< E >() &&
       !SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< E >(),
        SIXTRL_CXX_NAMESPACE::status_t >::type
    CObjElem_load_from_flat_cbuffer_to_argptr(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t) const* SIXTRL_RESTRICT buffer,
        NS(size_t) const pos_in_buffer, NS(size_t) const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC E* SIXTRL_RESTRICT ptr_obj_to_update
    ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::status_t status = st::STATUS_GENERAL_FAILURE;

        SIXTRL_BUFFER_OBJ_DATAPTR_DEC E const* src =
            st::CObjElem_const_from_cobj_index< E >(
                ::NS(CObjFlatBuffer_const_index)(
                    buffer, pos_in_buffer, slot_size ), slot_size );

        if( src == ptr_obj_to_update ) return st::STATUS_SUCCESS;

        st::size_t constexpr MAX_NUM_PTRS = st::CObjElem_max_num_ptrs< E >();
        st::size_t dest_counts[ MAX_NUM_PTRS ];
        st::size_t const num_pointers = st::CObjElem_num_ptrs< E >( src );

        if( ( src != nullptr ) && ( num_pointers ==
                st::CObjElem_num_ptrs< E >( ptr_obj_to_update) ) )
        {
            status = st::CObjElemFieldCounts< E >::init_field_counts(
                &dest_counts[ 0 ], MAX_NUM_PTRS, ptr_obj_to_update );
        }

        if( status == st::STATUS_SUCCESS )
        {
            st::size_t src_counts[ MAX_NUM_PTRS ];

            status = st::CObjElemFieldCounts< E >::init_field_counts(
                &src_counts[ 0 ], MAX_NUM_PTRS, src );

            if( status == st::STATUS_SUCCESS )
            {
                for( st::size_t ii = st::size_t{ 0 } ; ii < num_pointers ; ++ii )
                {
                    if( dest_counts[ ii ] != src_counts[ ii ] )
                    {
                        status = st::STATUS_GENERAL_FAILURE;
                        break;
                    }
                }
            }
        }

        if( status == st::STATUS_SUCCESS )
        {
            st::size_t save_ptrs[ MAX_NUM_PTRS ];

            status =
            ::NS(CObjFlatBuffer_load_obj_same_layout_parameters_to_argptr)(
                buffer, pos_in_buffer, slot_size, st::CObjElem_type_id< E >(),
                    ptr_obj_to_update, sizeof( E ), MAX_NUM_PTRS,
                        &CObjElemFieldOffsets< E >::offsets[ 0 ],
                        &CObjElemFieldSizes< E >::sizes[ 0 ],
                        &dest_counts[ 0 ], &save_ptrs[ 0 ] );
        }

        return status;
    }

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case02_direct_fixed_few< E >() &&
        SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< E >(),
        SIXTRL_CXX_NAMESPACE::status_t >::type
    CObjElem_load_from_flat_cbuffer_to_argptr(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t) const* SIXTRL_RESTRICT buffer,
        NS(size_t) const pos_in_buffer,
        NS(size_t) const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC E* SIXTRL_RESTRICT ptr_obj_to_update
    ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename ObjDataCApiTypeTraits< E >::c_api_t c_api_t;

        return st::CObjElem_load_from_flat_cbuffer_to_argptr< c_api_t >(
            buffer, pos_in_buffer, slot_size,
                st::ObjData_bitcast_to_c_api< E >( ptr_obj_to_update ) );
    }

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case03_direct_few< E >() &&
       !SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< E >(),
        SIXTRL_CXX_NAMESPACE::status_t >::type
    CObjElem_load_from_flat_cbuffer_to_argptr(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t) const* SIXTRL_RESTRICT buffer,
        NS(size_t) const pos_in_buffer,
        NS(size_t) const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC E* SIXTRL_RESTRICT ptr_obj_to_update
    ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::status_t status = st::STATUS_GENERAL_FAILURE;
        st::size_t constexpr MAX_NUM_PTRS = st::CObjElem_max_num_ptrs< E >();

        static_assert( MAX_NUM_PTRS > st::size_t{ 0 },
           "Expected to have dataptrs here" );

        SIXTRL_BUFFER_OBJ_DATAPTR_DEC E const* src =
            st::CObjElem_const_from_cobj_index< E >(
                ::NS(CObjFlatBuffer_const_index)(
                    buffer, pos_in_buffer, slot_size ), slot_size );

        st::size_t const num_pointers =
            st::CObjElem_num_ptrs< E >( ptr_obj_to_update );

        SIXTRL_ASSERT( num_pointers <= MAX_NUM_PTRS );

        st::size_t dest_offsets[ MAX_NUM_PTRS ];
        st::size_t dest_counts[ MAX_NUM_PTRS ];
        st::size_t dest_sizes[ MAX_NUM_PTRS ];

        if( ( src != nullptr ) &&
            ( num_pointers == st::CObjElem_num_ptrs< E >( src ) ) )
        {
            SIXTRL_BUFFER_ARGPTR_DEC E* SIXTRL_RESTRICT target =
                ptr_obj_to_update;

            st::size_t src_offsets[ MAX_NUM_PTRS ];
            st::size_t src_counts[ MAX_NUM_PTRS ];
            st::size_t src_sizes[ MAX_NUM_PTRS ];

            if( ( st::CObjElem_field_offsets< E >( &dest_offsets[ 0 ],
                    MAX_NUM_PTRS, target ) == st::STATUS_SUCCESS ) &&
                ( st::CObjElem_field_sizes< E >( &dest_sizes[ 0 ],
                    MAX_NUM_PTRS, target ) == st::STATUS_SUCCESS ) &&
                ( CObjElemFieldCounts< E >::init_field_counts(
                    &dest_counts[ 0 ], MAX_NUM_PTRS, target ) ==
                        st::STATUS_SUCCESS ) &&
                ( st::CObjElem_field_offsets< E >( &src_offsets[ 0 ],
                    MAX_NUM_PTRS, src ) == st::STATUS_SUCCESS ) &&
                ( st::CObjElem_field_sizes< E >( &src_sizes[ 0 ],
                    MAX_NUM_PTRS, src ) == st::STATUS_SUCCESS ) &&
                ( CObjElemFieldCounts< E >::init_field_counts( &src_counts[ 0],
                    MAX_NUM_PTRS, src ) == st::STATUS_SUCCESS ) )
            {
                status = st::STATUS_SUCCESS;

                for( st::size_t ii = st::size_t{ 0 } ; ii < num_pointers ; ++ii )
                {
                    if( ( src_offsets[ ii ] != dest_offsets[ ii ] ) ||
                        ( src_sizes[ ii ]   != dest_sizes[ ii ]   ) ||
                        ( src_counts[ ii ]  != dest_counts[ ii ]  ) )
                    {
                        status = st::STATUS_GENERAL_FAILURE;
                        break;
                    }
                }
            }
        }

        if( status == st::STATUS_SUCCESS )
        {
            st::size_t save_ptrs[ MAX_NUM_PTRS ];

            status =
            ::NS(CObjFlatBuffer_load_obj_same_layout_parameters_to_argptr)(
                buffer, pos_in_buffer, slot_size, st::CObjElem_type_id< E >(),
                    ptr_obj_to_update, sizeof( E ), num_pointers,
                        &dest_offsets[ 0 ], &dest_sizes[ 0 ],
                            &dest_counts[ 0 ], &save_ptrs[ 0 ] );
        }

        return status;
    }

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case03_direct_few< E >() &&
        SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< E >(),
        SIXTRL_CXX_NAMESPACE::status_t >::type
    CObjElem_load_from_flat_cbuffer_to_argptr(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t) const* SIXTRL_RESTRICT buffer,
        NS(size_t) const pos_in_buffer,
        NS(size_t) const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC E* SIXTRL_RESTRICT ptr_obj_to_update
    ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename ObjDataCApiTypeTraits< E >::c_api_t c_api_t;
        return st::CObjElem_load_from_flat_cbuffer_to_argptr< c_api_t >(
            buffer, pos_in_buffer, slot_size, st::ObjData_bitcast_to_c_api<
                E >( ptr_obj_to_update ) );
    }

    /*  -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case04_direct< E >() &&
       !SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< E >() ,
        SIXTRL_CXX_NAMESPACE::status_t >::type
    CObjElem_load_from_flat_cbuffer_to_argptr(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t) const* SIXTRL_RESTRICT buffer,
        NS(size_t) const pos_in_buffer, NS(size_t) const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC E* SIXTRL_RESTRICT ptr_obj_to_update )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::status_t status = st::STATUS_GENERAL_FAILURE;

        #if !defined( _GPUCODE )
        st::size_t constexpr MAX_NUM_PTRS = st::CObjElem_max_num_ptrs< E >();
        static_assert( MAX_NUM_PTRS > st::size_t{ 0 },
            "Expected to have dataptrs here" );

        SIXTRL_BUFFER_OBJ_DATAPTR_DEC E const* src =
            st::CObjElem_const_from_cobj_index< E >(
                ::NS(CObjFlatBuffer_const_index)(
                    buffer, pos_in_buffer, slot_size ), slot_size );

        st::size_t const num_pointers =
            st::CObjElem_num_ptrs< E >( ptr_obj_to_update );

        SIXTRL_ASSERT( num_pointers <= MAX_NUM_PTRS );

        std::vector< st::size_t > dest_offsets( MAX_NUM_PTRS );
        std::vector< st::size_t > dest_counts( MAX_NUM_PTRS );
        std::vector< st::size_t > dest_sizes( MAX_NUM_PTRS );

        if( ( src != nullptr ) &&
            ( num_pointers == st::CObjElem_num_ptrs< E >( src ) ) )
        {
            std::vector< st::size_t > src_offsets( MAX_NUM_PTRS );
            std::vector< st::size_t > src_counts( MAX_NUM_PTRS );
            std::vector< st::size_t > src_sizes( MAX_NUM_PTRS );

            SIXTRL_BUFFER_ARGPTR_DEC E* target = ptr_obj_to_update;

            if( ( st::CObjElem_field_offsets< E >( dest_offsets.data(),
                    MAX_NUM_PTRS, target ) == st::STATUS_SUCCESS ) &&
                ( st::CObjElem_field_sizes< E >( dest_sizes.data(),
                    MAX_NUM_PTRS, target ) == st::STATUS_SUCCESS ) &&
                ( CObjElemFieldCounts< E >::init_field_counts(
                    dest_counts.data(), MAX_NUM_PTRS, target ) ==
                        st::STATUS_SUCCESS ) &&
                ( st::CObjElem_field_offsets< E >( src_offsets.data(),
                    MAX_NUM_PTRS, src ) == st::STATUS_SUCCESS ) &&
                ( st::CObjElem_field_sizes< E >( src_sizes.data(),
                    MAX_NUM_PTRS, src ) == st::STATUS_SUCCESS ) &&
                ( CObjElemFieldCounts< E >::init_field_counts(
                    src_counts.data(), MAX_NUM_PTRS, target ) ==
                        st::STATUS_SUCCESS ) )
            {
                if( ( std::equal( dest_offsets.data(),
                                  dest_offsets.data() + num_pointers,
                                  src_offsets.data() ) ) &&
                    ( std::equal( dest_sizes.data(),
                                  dest_sizes.data() + num_pointers,
                                  src_sizes.data() ) ) &&
                    ( std::equal( dest_counts.data(),
                                  dest_counts.data() + num_pointers,
                                  src_counts.data() ) ) )
                {
                    status = st::STATUS_SUCCESS;
                }
            }
        }

        if( status == st::STATUS_SUCCESS )
        {
            std::vector< st::size_t > save_ptrs( MAX_NUM_PTRS );

            status =
            ::NS(CObjFlatBuffer_load_obj_same_layout_parameters_to_argptr)(
                buffer, pos_in_buffer, slot_size, st::CObjElem_type_id< E >(),
                    ptr_obj_to_update, sizeof( E ), num_pointers,
                        dest_offsets.data(), dest_sizes.data(),
                            dest_counts.data(), save_ptrs.data() );
        }

        #else /* _GPUCODE */

        ( void )buffer;
        ( void )slot_size;
        ( void )pos_in_buffer;
        ( void )ptr_obj_to_update;

        #endif /* _GPUCODE */

        return status;
    }

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case04_direct< E >() &&
        SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< E >(),
        SIXTRL_CXX_NAMESPACE::status_t >::type
    CObjElem_load_from_flat_cbuffer_to_argptr(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t) const* SIXTRL_RESTRICT buffer,
        NS(size_t) const pos_in_buffer, NS(size_t) const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC E* SIXTRL_RESTRICT ptr_obj_to_update )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename ObjDataCApiTypeTraits< E >::c_api_t c_api_t;
        return st::CObjElem_load_from_flat_cbuffer_to_argptr< c_api_t >(
            buffer, pos_in_buffer, slot_size, st::ObjData_bitcast_to_c_api<
                E >( ptr_obj_to_update ) );
    }

    template< class E > static SIXTRL_FN constexpr typename std::enable_if<
       !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >(),
        SIXTRL_CXX_NAMESPACE::status_t >::type
    CObjElem_load_from_flat_cbuffer_to_argptr(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t) const*
            SIXTRL_RESTRICT SIXTRL_UNUSED( buffer ),
        NS(size_t) const SIXTRL_UNUSED( pos_in_buffer ),
        NS(size_t) const SIXTRL_UNUSED( slot_size ),
        SIXTRL_BUFFER_ARGPTR_DEC E* SIXTRL_RESTRICT
            SIXTRL_UNUSED( ptr_to_source ) ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::STATUS_GENERAL_FAILURE;
    }

    /* ===================================================================== */
    /* "Store" (i.e.: update) an object stored in the buffer from an instance
     * not stored on the buffer.
     *
     * For the moment, we will only provide implementations for the case where
     * the layout parameters of the source and target object are identical */

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case01_direct_no_ptrs< E >() &&
       !SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< E >(),
        SIXTRL_CXX_NAMESPACE::status_t >::type
    CObjElem_store_to_flat_cbuffer_from_argptr(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t)* SIXTRL_RESTRICT buffer,
        NS(size_t) const pos_in_buffer, NS(size_t) const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT ptr_to_source
    ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return ::NS(CObjFlatBuffer_store_obj_same_layout_parameters_from_argptr)(
            buffer, pos_in_buffer, slot_size, st::CObjElem_type_id< E >(),
                ptr_to_source, sizeof( E ), st::size_t{ 0 },
                    nullptr, nullptr, nullptr, nullptr );
    }

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case01_direct_no_ptrs< E >() &&
        SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< E >(),
        SIXTRL_CXX_NAMESPACE::status_t >::type
    CObjElem_store_to_flat_cbuffer_from_argptr(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t)* SIXTRL_RESTRICT buffer,
        NS(size_t) const pos_in_buffer, NS(size_t) const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT ptr_to_source
    ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_store_to_flat_cbuffer_from_argptr<
            typename ObjDataCApiTypeTraits< E >::c_api_t >( buffer,
                pos_in_buffer, slot_size,
                    SIXTRL_CXX_NAMESPACE::ObjData_bitcast_to_const_c_api< E >(
                        ptr_to_source ) );
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case02_direct_fixed_few< E >() &&
       !SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< E >(),
        SIXTRL_CXX_NAMESPACE::status_t >::type
    CObjElem_store_to_flat_cbuffer_from_argptr(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t)* SIXTRL_RESTRICT buffer,
        NS(size_t) const pos_in_buffer,
        NS(size_t) const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT ptr_to_source
    ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::status_t status = st::STATUS_GENERAL_FAILURE;

        st::size_t constexpr MAX_NUM_PTRS = st::CObjElem_max_num_ptrs< E >();
        st::size_t dest_counts[ MAX_NUM_PTRS ];

        SIXTRL_BUFFER_OBJ_DATAPTR_DEC E* dest =
            st::CObjElem_from_cobj_index< E >( ::NS(CObjFlatBuffer_index)(
                buffer, pos_in_buffer, slot_size ), slot_size );

        if( dest == ptr_to_source ) return st::STATUS_SUCCESS;
        st::size_t const num_ptrs = st::CObjElem_num_ptrs< E >( dest );

        if( ( dest != nullptr ) && ( ptr_to_source != nullptr ) &&
            ( st::CObjElem_num_ptrs< E >( ptr_to_source ) == num_ptrs ) )
        {
            status = st::CObjElemFieldCounts< E >::init_field_counts(
                &dest_counts[ 0 ], MAX_NUM_PTRS, dest );

            if( status == st::STATUS_SUCCESS )
            {
                st::size_t src_counts[ MAX_NUM_PTRS ];

                if( st::CObjElemFieldCounts< E >::init_field_counts(
                    &src_counts[ 0 ], MAX_NUM_PTRS, ptr_to_source ) ==
                        st::STATUS_SUCCESS )
                {
                    for( st::size_t ii = st::size_t{ 0 } ; ii < num_ptrs ; ++ii )
                    {
                        if( dest_counts[ ii ] != src_counts[ ii ] )
                        {
                            status = st::STATUS_GENERAL_FAILURE;
                            break;
                        }
                    }
                }
            }
        }

        if( status == st::STATUS_SUCCESS )
        {
            st::size_t save_ptrs[ MAX_NUM_PTRS ];
            status =
            ::NS(CObjFlatBuffer_store_obj_same_layout_parameters_from_argptr)(
                buffer, pos_in_buffer, slot_size, st::CObjElem_type_id< E >(),
                ptr_to_source, sizeof( E ), MAX_NUM_PTRS,
                &CObjElemFieldOffsets< E >::offsets[ 0 ],
                &CObjElemFieldSizes< E >::sizes[ 0 ], &dest_counts[ 0 ],
                &save_ptrs[ 0 ] );
        }

        return status;
    }

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case02_direct_fixed_few< E >() &&
        SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< E >(),
        SIXTRL_CXX_NAMESPACE::status_t >::type
    CObjElem_store_to_flat_cbuffer_from_argptr(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t)* SIXTRL_RESTRICT buffer,
        NS(size_t) const pos_in_buffer,
        NS(size_t) const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT ptr_to_source
    ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef typename ObjDataCApiTypeTraits< E >::c_api_t c_api_t;
        return st::CObjElem_store_to_flat_cbuffer_from_argptr< c_api_t >(
            buffer, pos_in_buffer, slot_size,
                st::ObjData_bitcast_to_const_c_api< E >( ptr_to_source ) );
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case03_direct_few< E >() &&
       !SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< E >() ,
        SIXTRL_CXX_NAMESPACE::status_t >::type
    CObjElem_store_to_flat_cbuffer_from_argptr(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t)* SIXTRL_RESTRICT buffer,
        NS(size_t) const pos_in_buffer,
        NS(size_t) const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT ptr_to_source
    ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::status_t status = st::STATUS_GENERAL_FAILURE;

        st::size_t constexpr MAX_NUM_PTRS = st::CObjElem_max_num_ptrs< E >();
        static_assert( MAX_NUM_PTRS > st::size_t{ 0 },
            "Expected to have dataptrs here" );

        SIXTRL_BUFFER_OBJ_DATAPTR_DEC E* dest =
            st::CObjElem_from_cobj_index< E >( ::NS(CObjFlatBuffer_index)(
                buffer, pos_in_buffer, slot_size ), slot_size );

        st::size_t const num_pointers = st::CObjElem_num_ptrs< E >( dest );
        SIXTRL_ASSERT( num_pointers <= MAX_NUM_PTRS );

        st::size_t dest_counts[ MAX_NUM_PTRS ];
            st::size_t dest_sizes[ MAX_NUM_PTRS ];
            st::size_t dest_offsets[ MAX_NUM_PTRS ];

        if( ( dest != nullptr ) && ( ptr_to_source != nullptr ) &&
            ( num_pointers == st::CObjElem_num_ptrs< E >( dest ) ) )
        {
            st::size_t src_offsets[ MAX_NUM_PTRS ];
            st::size_t src_counts[ MAX_NUM_PTRS ];
            st::size_t src_sizes[ MAX_NUM_PTRS ];

            SIXTRL_BUFFER_ARGPTR_DEC const E *const src = ptr_to_source;

            if( ( st::CObjElem_field_offsets< E >( &dest_offsets[ 0 ],
                    MAX_NUM_PTRS, dest ) == st::STATUS_SUCCESS ) &&
                ( st::CObjElem_field_sizes< E >( &dest_sizes[ 0 ],
                    MAX_NUM_PTRS, dest ) == st::STATUS_SUCCESS ) &&
                ( CObjElemFieldCounts< E >::init_field_counts( &dest_counts[ 0 ],
                    MAX_NUM_PTRS, dest ) == st::STATUS_SUCCESS ) &&
                ( st::CObjElem_field_offsets< E >( &src_offsets[ 0 ],
                    MAX_NUM_PTRS, src ) == st::STATUS_SUCCESS ) &&
                ( st::CObjElem_field_sizes< E >( &src_sizes[ 0 ],
                    MAX_NUM_PTRS, src ) == st::STATUS_SUCCESS ) &&
                ( CObjElemFieldCounts< E >::init_field_counts( &src_counts[ 0 ],
                    MAX_NUM_PTRS, src ) == st::STATUS_SUCCESS ) )
            {
                status = st::STATUS_SUCCESS;

                for( st::size_t ii = st::size_t{ 0 } ; ii < num_pointers ; ++ii )
                {
                    if( ( src_offsets[ ii ] != dest_offsets[ ii ] ) ||
                        ( src_sizes[ ii ]   != dest_sizes[ ii ]   ) ||
                        ( src_counts[ ii ]  != dest_counts[ ii ]  ) )
                    {
                        status = st::STATUS_GENERAL_FAILURE;
                        break;
                    }
                }
            }
        }

        if( status == st::STATUS_SUCCESS )
        {
            st::size_t save_ptrs[ MAX_NUM_PTRS ];

            status =
            ::NS(CObjFlatBuffer_store_obj_same_layout_parameters_from_argptr)(
                buffer, pos_in_buffer, slot_size, st::CObjElem_type_id< E >(),
                    ptr_to_source, sizeof( E ), num_pointers,
                        &dest_offsets[ 0 ], &dest_sizes[ 0 ], &dest_counts[ 0 ]
                            , &save_ptrs[ 0 ] );
        }

        return status;
    }

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case03_direct_few< E >() &&
        SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< E >(),
        SIXTRL_CXX_NAMESPACE::status_t >::type
    CObjElem_store_to_flat_cbuffer_from_argptr(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t)* SIXTRL_RESTRICT buffer,
        NS(size_t) const pos_in_buffer,
        NS(size_t) const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT ptr_to_source
    ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return st::CObjElem_store_to_flat_cbuffer_from_argptr< typename
            ObjDataCApiTypeTraits< E >::c_api_t >( buffer, pos_in_buffer,
                slot_size, st::ObjData_bitcast_to_const_c_api< E >(
                    ptr_to_source ) );
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case04_direct< E >() &&
       !SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< E >(),
        SIXTRL_CXX_NAMESPACE::status_t >::type
    CObjElem_store_to_flat_cbuffer_from_argptr(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t) const* SIXTRL_RESTRICT buffer,
        NS(size_t) const pos_in_buffer, NS(size_t) const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT ptr_to_source )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::status_t status = st::STATUS_GENERAL_FAILURE;

        #if !defined( _GPUCODE )
        st::size_t constexpr MAX_NUM_PTRS = st::CObjElem_max_num_ptrs< E >();

        static_assert( MAX_NUM_PTRS > st::size_t{ 0 },
            "Expected to have dataptrs here" );

        SIXTRL_BUFFER_OBJ_DATAPTR_DEC E* dest =
            st::CObjElem_from_cobj_index< E >( ::NS(CObjFlatBuffer_const_index)(
                buffer, pos_in_buffer, slot_size ), slot_size );

        if( ( dest == ptr_to_source ) && ( ptr_to_source != nullptr ) )
        {
            return st::STATUS_SUCCESS;
        }

        st::size_t const num_ptrs = st::CObjElem_num_ptrs< E >( dest );

        SIXTRL_ASSERT( num_ptrs <= MAX_NUM_PTRS );

        std::vector< st::size_t > dest_offsets( MAX_NUM_PTRS );
        std::vector< st::size_t > dest_counts( MAX_NUM_PTRS );
        std::vector< st::size_t > dest_sizes( MAX_NUM_PTRS );

        if( ( dest != nullptr ) && ( ptr_to_source != nullptr ) &&
            ( num_ptrs == st::CObjElem_num_ptrs< E >( dest ) ) )
        {
            std::vector< st::size_t > src_offsets( MAX_NUM_PTRS );
            std::vector< st::size_t > src_counts( MAX_NUM_PTRS );
            std::vector< st::size_t > src_sizes( MAX_NUM_PTRS );

            SIXTRL_BUFFER_ARGPTR_DEC const E *const src = ptr_to_source;

            if( ( st::CObjElem_field_offsets< E >( dest_offsets.data(),
                    MAX_NUM_PTRS, dest ) == st::STATUS_SUCCESS ) &&
                ( st::CObjElem_field_sizes< E >( dest_sizes.data(),
                    MAX_NUM_PTRS, dest ) == st::STATUS_SUCCESS ) &&
                ( CObjElemFieldCounts< E >::init_field_counts(
                    dest_counts.data(), MAX_NUM_PTRS, dest ) ==
                        st::STATUS_SUCCESS ) &&
                ( st::CObjElem_field_offsets< E >( src_offsets.data(),
                    MAX_NUM_PTRS, src ) == st::STATUS_SUCCESS ) &&
                ( st::CObjElem_field_sizes< E >( src_sizes.data(),
                    MAX_NUM_PTRS, src ) == st::STATUS_SUCCESS ) &&
                ( CObjElemFieldCounts< E >::init_field_counts(
                    src_counts.data(), MAX_NUM_PTRS, src ) ==
                        st::STATUS_SUCCESS ) )
            {
                if( ( std::equal( dest_offsets.data(),
                        dest_offsets.data() + num_ptrs, src_offsets.data() ))&&
                    ( std::equal( dest_sizes.data(),
                        dest_sizes.data() + num_ptrs, src_sizes.data() ) ) &&
                    ( std::equal( dest_counts.data(),
                        dest_counts.data() + num_ptrs, src_counts.data() ) ))
                {
                    status = st::STATUS_SUCCESS;
                }
            }
        }

        if( status == st::STATUS_SUCCESS )
        {
            std::vector< st::size_t > save_ptrs( MAX_NUM_PTRS );

            status =
            ::NS(CObjFlatBuffer_load_obj_same_layout_parameters_to_argptr)(
                buffer, pos_in_buffer, slot_size, st::CObjElem_type_id< E >(),
                    ptr_to_source, sizeof( E ), num_ptrs, dest_offsets.data(),
                        dest_sizes.data(), dest_counts.data(),
                            save_ptrs.data() );
        }

        #else /* _GPUCODE */

        ( void )buffer;
        ( void )slot_size;
        ( void )pos_in_buffer;
        ( void )ptr_to_source;

        #endif /* _GPUCODE */

        return status;
    }

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case04_direct< E >() &&
        SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< E >(),
        SIXTRL_CXX_NAMESPACE::status_t >::type
    CObjElem_store_to_flat_cbuffer_from_argptr(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t) const* SIXTRL_RESTRICT buffer,
        NS(size_t) const pos_in_buffer, NS(size_t) const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT ptr_to_source )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return st::CObjElem_store_to_flat_cbuffer_from_argptr< typename
            ObjDataCApiTypeTraits< E >::c_api_t >( buffer, pos_in_buffer,
                slot_size, st::ObjData_bitcast_to_const_c_api< E >(
                    ptr_to_source ) );
    }

    template< class E > static SIXTRL_FN constexpr typename std::enable_if<
       !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >(),
        SIXTRL_CXX_NAMESPACE::status_t >::type
    CObjElem_store_to_flat_cbuffer_from_argptr(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t)* SIXTRL_RESTRICT
            SIXTRL_UNUSED( buffer ),
        NS(size_t) const SIXTRL_UNUSED( pos_in_buffer ),
        NS(size_t) const SIXTRL_UNUSED( slot_size ),
        SIXTRL_BUFFER_ARGPTR_DEC const E *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( ptr_to_source ) ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::STATUS_GENERAL_FAILURE;
    }

    /* ********************************************************************* */
    /* Support for checking whether a copy of an object can be added:        */

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case01_direct_no_ptrs< E >() &&
       !SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< E >(),
        bool >::type
    CObjElem_can_add_copy_of_object(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t) const* SIXTRL_RESTRICT buffer,
        SIXTRL_CXX_NAMESPACE::size_t const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( ptr_elem ),
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t*
            SIXTRL_RESTRICT requ_buffer_size,
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t*
            SIXTRL_RESTRICT requ_num_slots,
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t*
            SIXTRL_RESTRICT requ_num_objs,
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t*
            SIXTRL_RESTRICT requ_num_ptrs ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return ::NS(CObjFlatBuffer_can_add_copy_of_object)(
            buffer, slot_size, sizeof( E ), st::size_t{ 0 }, nullptr, nullptr,
            requ_buffer_size, requ_num_slots, requ_num_objs, requ_num_ptrs );
    }

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case02_direct_fixed_few< E >() &&
       !SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< E >(),
        bool >::type
    CObjElem_can_add_copy_of_object(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t) const* SIXTRL_RESTRICT buffer,
        SIXTRL_CXX_NAMESPACE::size_t const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT ptr_elem,
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t*
            SIXTRL_RESTRICT requ_buffer_size,
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t*
            SIXTRL_RESTRICT requ_num_slots,
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t*
            SIXTRL_RESTRICT requ_num_objs,
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t*
            SIXTRL_RESTRICT requ_num_ptrs ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::size_t constexpr MAX_NUM_PTRS = st::CObjElem_max_num_ptrs< E >();
        st::size_t counts[ MAX_NUM_PTRS ];

        return (
            ( st::CObjElemFieldCounts< E >::init_field_counts( &counts[ 0 ],
                MAX_NUM_PTRS, ptr_elem ) == st::STATUS_SUCCESS ) &&
            ( ::NS(CObjFlatBuffer_can_add_copy_of_object)( buffer, slot_size,
                sizeof( E ), MAX_NUM_PTRS, &CObjElemFieldSizes< E >::sizes[ 0 ],
                &counts[ 0 ], requ_buffer_size, requ_num_slots, requ_num_objs,
                requ_num_ptrs )
            ) );
    }

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case03_direct_few< E >() &&
       !SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< E >(),
        bool >::type
    CObjElem_can_add_copy_of_object(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t) const* SIXTRL_RESTRICT buffer,
        SIXTRL_CXX_NAMESPACE::size_t const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT ptr_elem,
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t*
            SIXTRL_RESTRICT requ_buffer_size,
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t*
            SIXTRL_RESTRICT requ_num_slots,
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t*
            SIXTRL_RESTRICT requ_num_objs,
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t*
            SIXTRL_RESTRICT requ_num_ptrs ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::size_t constexpr MAX_NUM_PTRS = st::CObjElem_max_num_ptrs< E >();
        st::size_t const num_pointers = st::CObjElem_num_ptrs< E >( ptr_elem );

        SIXTRL_ASSERT( num_pointers <= MAX_NUM_PTRS );

        st::size_t sizes[ MAX_NUM_PTRS ];
        st::size_t counts[ MAX_NUM_PTRS ];

        return (
            ( st::STATUS_SUCCESS == st::CObjElem_field_sizes< E >(
                &sizes[ 0 ], MAX_NUM_PTRS, ptr_elem ) ) &&
            ( st::CObjElemFieldCounts< E >::init_field_counts( &counts[ 0 ],
                MAX_NUM_PTRS, ptr_elem ) == st::STATUS_SUCCESS ) &&
            ( ::NS(CObjFlatBuffer_can_add_copy_of_object)( buffer, slot_size,
                sizeof( E ), num_pointers, &sizes[ 0 ], &counts[ 0 ],
                    requ_buffer_size, requ_num_slots, requ_num_objs,
                        requ_num_ptrs ) ) );
    }

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case04_direct< E >() &&
       !SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< E >(),
        bool >::type
    CObjElem_can_add_copy_of_object(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t) const* SIXTRL_RESTRICT buffer,
        SIXTRL_CXX_NAMESPACE::size_t const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT ptr_elem,
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t*
            SIXTRL_RESTRICT requ_buffer_size,
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t*
            SIXTRL_RESTRICT requ_num_slots,
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t*
            SIXTRL_RESTRICT requ_num_objs,
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t*
            SIXTRL_RESTRICT requ_num_ptrs )
    {
        #if !defined( _GPUCODE )

        namespace st = SIXTRL_CXX_NAMESPACE;


        st::size_t constexpr MAX_NUM_PTRS = st::CObjElem_max_num_ptrs< E >();
        st::size_t const num_pointers =
            st::CObjElem_num_ptrs< E >( ptr_elem );

        SIXTRL_ASSERT( num_pointers <= MAX_NUM_PTRS );

        std::vector< st::size_t > sizes( MAX_NUM_PTRS );
        std::vector< st::size_t > counts( MAX_NUM_PTRS );

        return (
            ( st::STATUS_SUCCESS == st::CObjElem_field_sizes< E >(
                sizes.data(), MAX_NUM_PTRS, ptr_elem ) ) &&
            ( st::CObjElemFieldCounts< E >::init_field_counts( counts.data(),
                MAX_NUM_PTRS, ptr_elem ) == st::STATUS_SUCCESS ) &&
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

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
        SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< E >(),
        bool >::type
    CObjElem_can_add_copy_of_object(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t) const* SIXTRL_RESTRICT buffer,
        SIXTRL_CXX_NAMESPACE::size_t const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT ptr_elem,
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t* SIXTRL_RESTRICT requ_buffer_size,
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t* SIXTRL_RESTRICT requ_num_slots,
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t* SIXTRL_RESTRICT requ_num_objs,
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t* SIXTRL_RESTRICT requ_num_ptrs )
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_can_add_copy_of_object<
            typename ObjDataCApiTypeTraits< E >::c_api_t >( buffer, slot_size,
                SIXTRL_CXX_NAMESPACE::ObjData_bitcast_to_const_c_api< E >(
                    ptr_elem ), requ_buffer_size, requ_num_slots,
                        requ_num_objs, requ_num_ptrs );
    }

    template< class E > static SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() ||
        !SIXTRL_CXX_NAMESPACE::CObjElemTypeId_is_legal< E >(), bool >::type
    CObjElem_can_add_copy_of_object(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t) const*
            SIXTRL_RESTRICT SIXTRL_UNUSED( buffer ),
        SIXTRL_CXX_NAMESPACE::size_t const SIXTRL_UNUSED( slot_size ),
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT SIXTRL_UNUSED( ptr_elem ),
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t* SIXTRL_RESTRICT
            SIXTRL_UNUSED( requ_buffer_size ),
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t* SIXTRL_RESTRICT
            SIXTRL_UNUSED( requ_num_slots ),
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t* SIXTRL_RESTRICT
            SIXTRL_UNUSED( requ_num_objs ),
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t* SIXTRL_RESTRICT
            SIXTRL_UNUSED( requ_num_ptrs ) ) SIXTRL_NOEXCEPT
    {
        return false;
    }

    /* ********************************************************************* */
    /* Support for adding copies of elements:                                */

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case01_direct_no_ptrs< E >() &&
       !SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< E >(),
        SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* >::type
    CObjElem_add_copy_of_object_impl(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t)* SIXTRL_RESTRICT buffer,
        SIXTRL_CXX_NAMESPACE::size_t const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT ptr_elem,
        bool const init_with_zeros = false ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::size_t constexpr obj_size = sizeof( E );
        return ::NS(CObjFlatBuffer_add_copy_of_object)( buffer, slot_size,
            ptr_elem, obj_size, st::CObjElem_type_id< E >(), st::size_t{ 0 },
                nullptr, nullptr, nullptr, init_with_zeros );
    }

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case02_direct_fixed_few< E >() &&
       !SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< E >(),
        SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* >::type
    CObjElem_add_copy_of_object_impl(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t)* SIXTRL_RESTRICT buffer,
        SIXTRL_CXX_NAMESPACE::size_t const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT elem,
        bool const init_with_zeros = false ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        NS(ptr_cobj_index_t) index_added_obj = nullptr;
        st::size_t constexpr MAX_NUM_PTRS = st::CObjElem_max_num_ptrs< E >();
        st::size_t counts[ MAX_NUM_PTRS ];

        if( st::CObjElemFieldCounts< E >::init_field_counts( &counts[ 0 ],
                MAX_NUM_PTRS, elem ) == st::STATUS_SUCCESS )
        {
            index_added_obj = ::NS(CObjFlatBuffer_add_copy_of_object)( buffer,
                slot_size, elem, sizeof( E ), st::CObjElem_type_id< E >(),
                MAX_NUM_PTRS, &CObjElemFieldOffsets< E >::offsets[ 0 ],
                &CObjElemFieldSizes< E >::sizes[ 0 ], &counts[ 0 ],
                init_with_zeros );
        }

        return index_added_obj;
    }

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case03_direct_few< E >() &&
       !SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< E >(),
        SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* >::type
    CObjElem_add_copy_of_object_impl(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t)* SIXTRL_RESTRICT buffer,
        SIXTRL_CXX_NAMESPACE::size_t const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT elem,
        bool const init_with_zeros = false ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        NS(ptr_cobj_index_t) index_added_obj = nullptr;
        st::size_t constexpr MAX_NUM_PTRS = st::CObjElem_max_num_ptrs< E >();
        st::size_t offsets[ MAX_NUM_PTRS ];
        st::size_t sizes[ MAX_NUM_PTRS ];
        st::size_t counts[ MAX_NUM_PTRS ];

        st::size_t const num_pointers = st::CObjElem_num_ptrs< E >( elem );
        SIXTRL_ASSERT( num_pointers <= MAX_NUM_PTRS );

        if( ( st::CObjElem_field_offsets< E >( &offsets[ 0 ], MAX_NUM_PTRS,
                elem ) == st::STATUS_SUCCESS ) &&
            ( st::CObjElem_field_sizes< E >( &sizes[ 0 ], MAX_NUM_PTRS,
                elem ) == st::STATUS_SUCCESS ) &&
            ( CObjElemFieldCounts< E >::init_field_counts( &counts[ 0 ],
                MAX_NUM_PTRS, elem ) == st::STATUS_SUCCESS ) )
        {
            index_added_obj = ::NS(CObjFlatBuffer_add_copy_of_object)( buffer,
                slot_size, elem, sizeof( E ), st::CObjElem_type_id< E >(),
                    num_pointers, &offsets[ 0 ], &sizes[ 0 ], &counts[ 0 ],
                        init_with_zeros);
        }

        return index_added_obj;
    }

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_ptrs_case04_direct< E >() &&
       !SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< E >(),
        SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* >::type
    CObjElem_add_copy_of_object_impl(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t)* SIXTRL_RESTRICT buffer,
        SIXTRL_CXX_NAMESPACE::size_t const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT elem,
        bool const init_with_zeros = false )
    {
        NS(ptr_cobj_index_t) index_added_obj = nullptr;

        #if !defined( _GPUCODE )
        namespace st = SIXTRL_CXX_NAMESPACE;

        st::size_t constexpr MAX_NUM_PTRS = st::CObjElem_max_num_ptrs< E >();
        std::vector< SIXTRL_CXX_NAMESPACE::size_t > offsets( MAX_NUM_PTRS );
        std::vector< SIXTRL_CXX_NAMESPACE::size_t > sizes( MAX_NUM_PTRS );
        std::vector< SIXTRL_CXX_NAMESPACE::size_t > counts( MAX_NUM_PTRS );
        st::size_t const num_pointers = st::CObjElem_num_ptrs< E >( elem );
        SIXTRL_ASSERT( num_pointers <= MAX_NUM_PTRS );

        if( ( st::CObjElem_field_offsets< E >( offsets.data(), MAX_NUM_PTRS,
                elem ) == st::STATUS_SUCCESS ) &&
            ( st::CObjElem_field_sizes< E >( sizes.data(), MAX_NUM_PTRS,
                elem ) == st::STATUS_SUCCESS ) &&
            ( CObjElemFieldCounts< E >::init_field_counts( counts.data(),
                MAX_NUM_PTRS, elem ) == st::STATUS_SUCCESS ) )
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

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >()  &&
        SIXTRL_CXX_NAMESPACE::ObjData_has_equivalent_c_api_type< E >(),
        SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* >::type
    CObjElem_add_copy_of_object_impl(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t)* SIXTRL_RESTRICT buffer,
        SIXTRL_CXX_NAMESPACE::size_t const slot_size,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT elem,
        bool const init_with_zeros = false )
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_add_copy_of_object_impl<
            typename ObjDataCApiTypeTraits< E >::c_api_t >( buffer, slot_size,
                SIXTRL_CXX_NAMESPACE::ObjData_bitcast_to_const_c_api< E >(
                    elem ), init_with_zeros );
    }

    template< class E > static SIXTRL_FN constexpr typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >(),
        SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* >::type
    CObjElem_add_copy_of_object_impl(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t)* SIXTRL_RESTRICT SIXTRL_UNUSED( buffer ),
        SIXTRL_CXX_NAMESPACE::size_t const SIXTRL_UNUSED( slot_size ),
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT SIXTRL_UNUSED( ptr_elem ),
        bool const SIXTRL_UNUSED( init_with_zeros ) ) SIXTRL_NOEXCEPT
    {
        return false;
    }

    /* --------------------------------------------------------------------- */

    template< class E > static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >(),
        SIXTRL_BUFFER_OBJ_DATAPTR_DEC E* >::type
    CObjElem_add_copy_of_object(
        SIXTRL_BUFFER_DATAPTR_DEC NS(cobj_raw_t)* SIXTRL_RESTRICT buffer,
        SIXTRL_CXX_NAMESPACE::size_t const slot_size,
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
#endif /* SIXTRACKLIB_BASE_COBJECTS_ELEMENT_STORE_RESTORE_H__ */
