#ifndef SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_COBJECTS_GTEST_DIRECT_BASE_CXX_HPP__
#define SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_COBJECTS_GTEST_DIRECT_BASE_CXX_HPP__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <algorithm>
        #include <cstddef>
        #include <cstdlib>
        #include <iostream>
        #include <type_traits>
        #include <memory>
        #include <vector>
    #endif /* C++ */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/cobjects/cbuffer_view.hpp"
    #include "sixtracklib/testlib/common/cobjects/cobj_elem_traits.hpp"
    #include "sixtracklib/testlib/common/objs.hpp"
    #include "sixtracklib/testlib/common/config.h"
    #include "sixtracklib/testlib/common/cobjects.hpp"
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/cobjects/cbuffer.hpp"
    #include "sixtracklib/common/cobjects/cbuffer_view.hpp"
    #include "sixtracklib/common/internal/type_comparison_helpers.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    template< class E, class ElemAloc = std::allocator< E >, class SizeAlloc =
                std::allocator< SIXTRL_CXX_NAMESPACE::arch_size_t > >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
    CObjElem_test_impl_create_orig_elems(
        std::vector< E, ElemAloc >& SIXTRL_RESTRICT_REF orig_elems,
        typename SIXTRL_CXX_NAMESPACE::tests::ObjsRandomInitialiserTraits<
            E >::initialiser_t& obj_init,
        std::vector< SIXTRL_CXX_NAMESPACE::arch_size_t, SizeAlloc >&
            SIXTRL_RESTRICT_REF requ_num_slots,
        std::vector< SIXTRL_CXX_NAMESPACE::arch_size_t, SizeAlloc >&
            SIXTRL_RESTRICT_REF requ_num_objs,
        std::vector< SIXTRL_CXX_NAMESPACE::arch_size_t, SizeAlloc >&
            SIXTRL_RESTRICT_REF requ_num_ptrs,
        SIXTRL_CXX_NAMESPACE::arch_size_t const slot_size =
                SIXTRL_CXX_NAMESPACE::CBufferView::DEFAULT_SLOT_SIZE )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef st::arch_size_t st_size_t;
        typedef st::arch_status_t st_status_t;

        st_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        st_size_t const NUM_ELEM = orig_elems.size();

        if( NUM_ELEM > st_size_t{ 0 } )
        {
            requ_num_slots.clear();
            requ_num_slots.resize( NUM_ELEM, st_size_t{ 0 } );

            requ_num_objs.clear();
            requ_num_objs.resize( NUM_ELEM, st_size_t{ 0 } );

            requ_num_ptrs.clear();
            requ_num_ptrs.resize( NUM_ELEM, st_size_t{ 0 } );

            status = st::ARCH_STATUS_SUCCESS;

            for( st_size_t ii = st_size_t{ 0 } ; ii < NUM_ELEM ; ++ii )
            {
                E* orig = std::addressof( orig_elems[ ii ] );
                SIXTRL_ASSERT( orig != nullptr );

                status = obj_init.randomise( orig );
                if( status != st::ARCH_STATUS_SUCCESS ) break;

                requ_num_objs[ ii ] = st::CObjElem_required_num_objects( orig );

                if( requ_num_objs[ ii ] == st_size_t{ 0 } )
                {
                    status = st::ARCH_STATUS_GENERAL_FAILURE;
                    break;
                }

                requ_num_slots[ ii ] = st::CObjElem_required_num_slots(
                    slot_size, orig );

                if( requ_num_slots[ ii ] == st_size_t{ 0 } )
                {
                    status = st::ARCH_STATUS_GENERAL_FAILURE;
                    break;
                }

                requ_num_ptrs[ ii ] = st::CObjElem_num_ptrs< E >();
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    template< class E, class SizeAlloc = std::allocator<
                SIXTRL_CXX_NAMESPACE::arch_size_t > >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() ||
         SIXTRL_CXX_NAMESPACE::CObjElem_allow_delegate_storage< E >(),
         SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    CObjElem_test_impl_direct_create_view_buffer(
        SIXTRL_BUFFER_ARGPTR_DEC const E *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( orig ),
        SIXTRL_CXX_NAMESPACE::arch_size_t const SIXTRL_UNUSED( idx ),
        typename SIXTRL_CXX_NAMESPACE::tests::CObjElemInitialiserTraits<
            E >::initialiser_t& SIXTRL_UNUSED( obj_init ),
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBufferView&
            SIXTRL_RESTRICT_REF SIXTRL_UNUSED( view ),
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBuffer&
            SIXTRL_RESTRICT_REF SIXTRL_UNUSED( buffer ),
        std::vector< SIXTRL_CXX_NAMESPACE::arch_size_t, SizeAlloc > const&
            SIXTRL_RESTRICT_REF SIXTRL_UNUSED( requ_num_slots ),
        std::vector< SIXTRL_CXX_NAMESPACE::arch_size_t, SizeAlloc > const&
            SIXTRL_RESTRICT_REF SIXTRL_UNUSED( requ_num_objs ),
        std::vector< SIXTRL_CXX_NAMESPACE::arch_size_t, SizeAlloc > const&
            SIXTRL_RESTRICT_REF SIXTRL_UNUSED( requ_num_ptrs ) )
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class E, class SizeAlloc = std::allocator<
                SIXTRL_CXX_NAMESPACE::arch_size_t > >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
       !SIXTRL_CXX_NAMESPACE::CObjElem_allow_delegate_storage< E >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    CObjElem_test_impl_direct_create_view_buffer(
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT orig,
        SIXTRL_CXX_NAMESPACE::arch_size_t const idx,
        typename SIXTRL_CXX_NAMESPACE::tests::CObjElemInitialiserTraits<
            E >::initialiser_t& obj_init,
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBufferView&
            SIXTRL_RESTRICT_REF view,
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBuffer&
            SIXTRL_RESTRICT_REF buffer,
        std::vector< SIXTRL_CXX_NAMESPACE::arch_size_t, SizeAlloc > const&
            SIXTRL_RESTRICT_REF requ_num_slots,
        std::vector< SIXTRL_CXX_NAMESPACE::arch_size_t, SizeAlloc > const&
            SIXTRL_RESTRICT_REF requ_num_objs,
        std::vector< SIXTRL_CXX_NAMESPACE::arch_size_t, SizeAlloc > const&
            SIXTRL_RESTRICT_REF requ_num_ptrs )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef st::arch_size_t   st_size_t;
        typedef st::arch_status_t status_t;

        status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        st_size_t const jj = idx % st_size_t{ 3 };

        if( buffer.slot_size() != view.slot_size() ) return status;
        if( std::addressof( buffer ) == std::addressof( view ) ) return status;

        SIXTRL_ASSERT( orig != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( idx < requ_num_objs.size()  );
        SIXTRL_ASSERT( idx < requ_num_slots.size() );
        SIXTRL_ASSERT( idx < requ_num_ptrs.size()  );

        SIXTRL_BUFFER_DATAPTR_DEC E* added_elem_v = nullptr;
        SIXTRL_BUFFER_DATAPTR_DEC E* added_elem_b = nullptr;

        switch( jj )
        {
            case 0:
            {
                added_elem_v = obj_init.create_new( view, orig );
                added_elem_b = obj_init.create_new( buffer, orig );
                break;
            }

            case 1:
            {
                added_elem_v = obj_init.add_new( view,   orig );
                added_elem_b = obj_init.add_new( buffer, orig );
                break;
            }

            case 2:
            {
                added_elem_v = st::CBufferView_add_copy_of_object_detail(
                    view, orig, nullptr, nullptr, nullptr, nullptr );
                added_elem_b = buffer.add_copy( orig );
                break;
            }

            default:
            {
                added_elem_v = nullptr;
                added_elem_b = nullptr;
            }
        };

        if( ( added_elem_v == nullptr ) || ( added_elem_v == orig ) ) return status;
        if( ( added_elem_b == nullptr ) || ( added_elem_b == orig ) ) return status;
        if( added_elem_b == added_elem_v ) return status;

        if( view.n_objects()   != st_size_t{ 1 } + idx ) return status;
        if( buffer.n_objects() != st_size_t{ 1 } + idx ) return status;

        if( requ_num_objs[ idx ] != st::CObjElem_required_num_objects(
                added_elem_v ) ) return status;

        if( requ_num_slots[ idx ] != st::CObjElem_required_num_slots(
                view.slot_size(), added_elem_v ) ) return status;

        if( requ_num_ptrs[ idx ] != st::CObjElem_num_ptrs(
                added_elem_v ) ) return status;

        if( requ_num_objs[ idx ] != st::CObjElem_required_num_objects(
                added_elem_b ) ) return status;

        if( requ_num_slots[ idx ] != st::CObjElem_required_num_slots(
                buffer.slot_size(), added_elem_b ) ) return status;

        if( requ_num_ptrs[ idx ] != st::CObjElem_num_ptrs(
                added_elem_b ) ) return status;

        /* ----------------------------------------------------------------- */
        /* initial : elem_v == A, elem_b == A, orig == A */

        auto cmp_result = st::ObjDataComparisonHelper< E, E >::compare(
            added_elem_v, orig );

        if( cmp_result != st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS ) return status;

        cmp_result = st::ObjDataComparisonHelper< E, E >::compare(
            added_elem_b, orig );

        if( cmp_result != st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS ) return status;

        cmp_result = st::ObjDataComparisonHelper< E, E >::compare(
            added_elem_b, added_elem_v );

        if( cmp_result != st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS ) return status;

        /* ----------------------------------------------------------------- */
        /* randomise elem_v: elem_v == B, elem_b == A, orig == A */

        if( obj_init.randomise_values( added_elem_v ) !=
            st::ARCH_STATUS_SUCCESS ) return status;

        cmp_result = st::ObjDataComparisonHelper< E, E >::compare(
            added_elem_v, orig );

        if( cmp_result == st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS ) return status;

        cmp_result = st::ObjDataComparisonHelper< E, E >::compare(
            added_elem_b, orig );

        if( cmp_result != st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS ) return status;

        cmp_result = st::ObjDataComparisonHelper< E, E >::compare(
            added_elem_b, added_elem_v );

        if( cmp_result == st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS ) return status;

        /* ----------------------------------------------------------------- */
        /* view.load( elem_b ) : elem_v == B, elem_b == B, orig == A */

        if( st::ARCH_STATUS_SUCCESS != view.load_object(
                idx, added_elem_b ) ) return status;

        cmp_result = st::ObjDataComparisonHelper< E, E >::compare(
            added_elem_v, added_elem_b );

        if( cmp_result != st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS ) return status;

        cmp_result = st::ObjDataComparisonHelper< E, E >::compare(
            added_elem_v, orig );

        if( cmp_result == st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS ) return status;

        cmp_result = st::ObjDataComparisonHelper< E, E >::compare(
            added_elem_b, orig );

        if( cmp_result == st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS ) return status;

        /* ----------------------------------------------------------------- */
        /* view.store( orig ) : elem_v == B, elem_b == A, orig == A */

        if( st::ARCH_STATUS_SUCCESS != buffer.store_object(
                idx, orig ) ) return status;

        cmp_result = st::ObjDataComparisonHelper< E, E >::compare(
            added_elem_b, orig );

        if( cmp_result != st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS ) return status;

        cmp_result = st::ObjDataComparisonHelper< E, E >::compare(
            added_elem_v, orig );

        if( cmp_result == st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS ) return status;

        cmp_result = st::ObjDataComparisonHelper< E, E >::compare(
            added_elem_v, added_elem_b );

        if( cmp_result == st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS ) return status;

        /* ----------------------------------------------------------------- */
        /* buffer.load( orig ) : elem_v == A, elem_b == A, orig == A */

        if( st::ARCH_STATUS_SUCCESS != view.store_object(
                idx, orig ) ) return status;

        cmp_result = st::ObjDataComparisonHelper< E, E >::compare(
            added_elem_v, orig );

        if( cmp_result != st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS ) return status;

        cmp_result = st::ObjDataComparisonHelper< E, E >::compare(
            added_elem_b, orig );

        if( cmp_result != st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS ) return status;

        cmp_result = st::ObjDataComparisonHelper< E, E >::compare(
            added_elem_v, added_elem_b );

        if( cmp_result != st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS ) return status;

        /* ================================================================= */
        /* randomise elem_b: elem_v == C, elem_b == A, orig == A */

        if( obj_init.randomise_values( added_elem_v ) !=
            st::ARCH_STATUS_SUCCESS ) return status;

        cmp_result = st::ObjDataComparisonHelper< E, E >::compare(
            added_elem_v, orig );

        if( cmp_result == st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS ) return status;

        cmp_result = st::ObjDataComparisonHelper< E, E >::compare(
            added_elem_b, orig );

        if( cmp_result != st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS ) return status;

        cmp_result = st::ObjDataComparisonHelper< E, E >::compare(
            added_elem_b, added_elem_v );

        if( cmp_result == st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS ) return status;

        /* ----------------------------------------------------------------- */
        /* buffer.store( elem_v ) : elem_v == C, elem_b == C, orig == A */

        if( st::ARCH_STATUS_SUCCESS != view.load_object(
                idx, added_elem_b ) ) return status;

        cmp_result = st::ObjDataComparisonHelper< E, E >::compare(
            added_elem_v, added_elem_b );

        if( cmp_result != st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS ) return status;

        cmp_result = st::ObjDataComparisonHelper< E, E >::compare(
            added_elem_v, orig );

        if( cmp_result == st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS ) return status;

        cmp_result = st::ObjDataComparisonHelper< E, E >::compare(
            added_elem_b, orig );

        if( cmp_result == st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS ) return status;

        /* ----------------------------------------------------------------- */
        /* view.store( orig ) : elem_v == A, elem_b == C, orig == A */

        if( st::ARCH_STATUS_SUCCESS != view.store_object(
                idx, orig ) ) return status;

        cmp_result = st::ObjDataComparisonHelper< E, E >::compare(
            added_elem_v, orig );

        if( cmp_result != st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS ) return status;

        cmp_result = st::ObjDataComparisonHelper< E, E >::compare(
            added_elem_b, orig );

        if( cmp_result == st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS ) return status;

        cmp_result = st::ObjDataComparisonHelper< E, E >::compare(
            added_elem_v, added_elem_b );

        if( cmp_result == st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS ) return status;

        /* ----------------------------------------------------------------- */
        /* view.load( orig ) : elem_v == A, elem_b == A, orig == A */

        if( st::ARCH_STATUS_SUCCESS != buffer.store_object(
                idx, orig ) ) return status;

        cmp_result = st::ObjDataComparisonHelper< E, E >::compare(
            added_elem_v, orig );

        if( cmp_result != st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS ) return status;

        cmp_result = st::ObjDataComparisonHelper< E, E >::compare(
            added_elem_b, orig );

        if( cmp_result != st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS ) return status;

        cmp_result = st::ObjDataComparisonHelper< E, E >::compare(
            added_elem_v, added_elem_b );

        if( cmp_result != st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS ) return status;

        status = st::ARCH_STATUS_SUCCESS;
        return status;
    }

    /* --------------------------------------------------------------------- */

    template< class E >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
       !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() ||
        SIXTRL_CXX_NAMESPACE::CObjElem_allow_delegate_storage< E >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    CObjElem_test_impl_compare_view_and_buffer_direct(
        SIXTRL_BUFFER_ARGPTR_DEC const E *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( orig ),
        SIXTRL_CXX_NAMESPACE::arch_size_t const
            SIXTRL_UNUSED( idx ),
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBufferView const&
            SIXTRL_RESTRICT_REF SIXTRL_UNUSED( view ),
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBuffer const&
            SIXTRL_RESTRICT_REF SIXTRL_UNUSED( buffer ) ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class E >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
       !SIXTRL_CXX_NAMESPACE::CObjElem_allow_delegate_storage< E >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    CObjElem_test_impl_compare_view_and_buffer_direct(
        SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT orig,
        SIXTRL_CXX_NAMESPACE::arch_size_t const idx,
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBufferView const&
            SIXTRL_RESTRICT_REF view,
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBuffer const&
            SIXTRL_RESTRICT_REF buffer )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        if( orig == nullptr ) return status;
        if( buffer.slot_size() != view.slot_size() ) return status;
        if( std::addressof( buffer ) == std::addressof( view ) ) return status;
        if( buffer.n_objects() != view.n_objects() ) return status;
        if( buffer.n_objects() <= idx ) return status;

        static_assert( st::CObjElem_allow_direct_storage< E >(),
                       "Direct storage required" );

        SIXTRL_BUFFER_DATAPTR_DEC E const* added_elem_v =
            buffer.get_object< E >( idx );

        SIXTRL_BUFFER_DATAPTR_DEC E const* added_elem_b =
            view.get_object< E >( idx );

        if( added_elem_v == nullptr ) return status;
        if( added_elem_b == nullptr ) return status;
        if( added_elem_v == added_elem_b ) return status;
        if( added_elem_v == orig ) return status;
        if( added_elem_b == orig ) return status;

        auto cmp_result = st::ObjDataComparisonHelper< E, E >::compare(
            added_elem_v, orig );

        if( cmp_result != st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS ) return status;

        cmp_result = st::ObjDataComparisonHelper< E, E >::compare(
            added_elem_b, orig );

        if( cmp_result != st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS ) return status;

        cmp_result = st::ObjDataComparisonHelper< E, E >::compare(
            added_elem_v, added_elem_b );

        if( cmp_result != st::TypeCompResultTraits<
            decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS ) return status;

        status = st::ARCH_STATUS_SUCCESS;
        return status;
    }

    /* --------------------------------------------------------------------- */

    template< class E >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
       !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() ||
        SIXTRL_CXX_NAMESPACE::CObjElem_allow_delegate_storage< E >(),
        SIXTRL_CXX_NAMESPACE::arch_size_t >::type
    CObjElem_test_direct_storage_view_buffer(
        SIXTRL_CXX_NAMESPACE::arch_size_t const
            SIXTRL_UNUSED( num_elem ) ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class E >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
       !SIXTRL_CXX_NAMESPACE::CObjElem_allow_delegate_storage< E >(),
        SIXTRL_CXX_NAMESPACE::arch_size_t >::type
    CObjElem_test_direct_storage_view_buffer(
        SIXTRL_CXX_NAMESPACE::arch_size_t const num_elem )
    {
        namespace st = sixtrack;
        typedef st::arch_size_t st_size_t;
        typedef typename st::tests::CObjElemInitialiserTraits<
                    E >::initialiser_t obj_init_t;

        static_assert( st::CObjElem_allow_direct_storage< E >(),
                       "Direct storage to cobjects buffer required" );

        typedef st::CBufferView cbuffer_view_t;
        typedef cbuffer_view_t::address_t st_addr_t;
        typedef st::CBuffer cbuffer_t;
        typedef cbuffer_view_t::raw_t st_raw_data_t;

        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        if( num_elem == st_size_t{ 0 } ) return status;

        std::vector< st_size_t > requ_num_objs(  num_elem, st_size_t{ 0 } );
        std::vector< st_size_t > requ_num_slots( num_elem, st_size_t{ 0 } );
        std::vector< st_size_t > requ_num_ptrs(  num_elem, st_size_t{ 0 } );

        /* Create orig elements in vector: */

        obj_init_t obj_init;
        std::vector< E > cmp_obj( num_elem, E{} );

        cbuffer_t buffer;

        status = st::tests::CObjElem_test_impl_create_orig_elems< E >( cmp_obj, obj_init,
            requ_num_slots, requ_num_objs, requ_num_ptrs, buffer.slot_size() );

        if( status != st::ARCH_STATUS_SUCCESS ) return status;

        /* Calculate buffer / view layout parameters */

        st_size_t const max_num_objs = std::accumulate(
            requ_num_objs.begin(), requ_num_objs.end(), st_size_t{ 0 } );

        st_size_t const max_num_slots = std::accumulate(
            requ_num_slots.begin(), requ_num_slots.end(), st_size_t{ 0 } );

        st_size_t const max_num_ptrs = std::accumulate(
            requ_num_ptrs.begin(), requ_num_ptrs.end(), st_size_t{ 0 } );

        st_size_t const requ_buffer_size =
            cbuffer_view_t::required_buffer_length( max_num_slots,
                max_num_objs, max_num_ptrs, st_size_t{ 0 },
                    buffer.slot_size() );

        SIXTRL_ASSERT( max_num_objs >= num_elem );
        SIXTRL_ASSERT( max_num_slots > st_size_t{ 0 } );
        SIXTRL_ASSERT( requ_buffer_size > st_size_t{ 0 } );

        /* prepare view */

        std::vector< st_raw_data_t > view_raw_buffer(
            requ_buffer_size + buffer.slot_size() );

        st_size_t view_capacity = st_size_t{ 0 };
        st_addr_t const view_begin_addr = cbuffer_view_t::aligned_base_addr(
            reinterpret_cast< std::uintptr_t >( view_raw_buffer.data() ),
            view_raw_buffer.size(), st::Type_storage_align< E >(),
                &view_capacity, buffer.slot_size() );

        SIXTRL_ASSERT( view_begin_addr != cbuffer_view_t::NULL_ADDRESS );
        SIXTRL_ASSERT( view_capacity >= requ_buffer_size );

        cbuffer_view_t view( view_begin_addr, buffer.slot_size(),
                             view_capacity );

        SIXTRL_ASSERT( view.capacity() >= requ_buffer_size );
        SIXTRL_ASSERT( view.can_allocate(
            max_num_slots, max_num_objs, max_num_ptrs, st_size_t{ 0 } ) );

        status = st::CObjStatus_to_status( view.allocate(
            max_num_slots, max_num_objs, max_num_ptrs, st_size_t{ 0 } ) );
        if( status != st::ARCH_STATUS_SUCCESS ) return status;

        SIXTRL_ASSERT( view.max_slots()    >= max_num_slots );
        SIXTRL_ASSERT( view.max_objects()  >= max_num_objs );
        SIXTRL_ASSERT( view.max_pointers() >= max_num_ptrs );

        /* prepare buffer */

        for( st_size_t ii = st_size_t{ 0 } ; ii < num_elem ; ++ii )
        {
            E const* orig = std::addressof( cmp_obj[ ii ] );
            status = st::tests::CObjElem_test_impl_direct_create_view_buffer<
                E >( orig, ii, obj_init, view, buffer, requ_num_slots,
                    requ_num_objs, requ_num_ptrs );
            if( status != st::ARCH_STATUS_SUCCESS ) break;
        }

        if( ( status != st::ARCH_STATUS_SUCCESS ) ||
            ( view.n_objects()   != num_elem ) ||
            ( buffer.n_objects() != num_elem ) )
        {
            return status | st::ARCH_STATUS_GENERAL_FAILURE;
        }

        /* compare all buffer/view elems with the orig elements in one go */

        for( st_size_t ii = st_size_t{ 0 } ; ii < num_elem ; ++ii )
        {
            E const* orig = std::addressof( cmp_obj[ ii ] );
            status = st::tests::CObjElem_test_impl_compare_view_and_buffer_direct(
                orig, ii, view, buffer );

            if( status != st::ARCH_STATUS_SUCCESS ) break;
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    template< class E >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() ||
       !SIXTRL_CXX_NAMESPACE::CObjElem_allow_delegate_storage< E >(),
        SIXTRL_CXX_NAMESPACE::arch_size_t >::type
    CObjElem_test_delegate_storage_view_buffer(
        SIXTRL_CXX_NAMESPACE::arch_size_t const
            SIXTRL_UNUSED( num_elem ) ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class E >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
       !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
        SIXTRL_CXX_NAMESPACE::CObjElem_allow_delegate_storage< E >(),
        SIXTRL_CXX_NAMESPACE::arch_size_t >::type
    CObjElem_test_delegate_storage_view_buffer(
        SIXTRL_CXX_NAMESPACE::arch_size_t const num_elem )
    {
        namespace st = sixtrack;
        typedef st::arch_size_t st_size_t;

        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        typedef typename st::tests::ObjsRandomInitialiserTraits<
                    E >::initialiser_t obj_init_t;

        typedef typename st::ObjDataDelegateTraits<
            E, st::STORAGE_BE_COBJECTS >::delegate_t delegate_t;

        typedef typename st::tests::CObjElemInitialiserTraits<
            delegate_t >::initialiser_t delegate_init_t;

        typedef st::CBufferView cbuffer_view_t;
        typedef cbuffer_view_t::address_t st_addr_t;
        typedef st::CBuffer cbuffer_t;
        typedef cbuffer_view_t::raw_t st_raw_data_t;

        if( num_elem == st_size_t{ 0 } ) return status;

        std::vector< st_size_t > requ_num_objs(  num_elem, st_size_t{ 0 } );
        std::vector< st_size_t > requ_num_slots( num_elem, st_size_t{ 0 } );
        std::vector< st_size_t > requ_num_ptrs(  num_elem, st_size_t{ 0 } );

        /* Create orig elements in vector: */

        delegate_init_t delegate_init;
        std::vector< delegate_t > orig_elems( num_elem, delegate_t{} );

        cbuffer_t buffer;

        status = st::tests::CObjElem_test_impl_create_orig_elems< delegate_t >(
            orig_elems, delegate_init, requ_num_slots, requ_num_objs,
                requ_num_ptrs, buffer.slot_size() );

        if( status != st::ARCH_STATUS_SUCCESS )
        {
            std::cout << "exit point 01" << std::endl;
            return status;
        }

        /* Calculate buffer / view layout parameters */

        st_size_t const max_num_objs = std::accumulate(
            requ_num_objs.begin(), requ_num_objs.end(), st_size_t{ 0 } );

        st_size_t const max_num_slots = std::accumulate(
            requ_num_slots.begin(), requ_num_slots.end(), st_size_t{ 0 } );

        st_size_t const max_num_ptrs = std::accumulate(
            requ_num_ptrs.begin(), requ_num_ptrs.end(), st_size_t{ 0 } );

        st_size_t const requ_buffer_size =
            cbuffer_view_t::required_buffer_length( max_num_slots,
                max_num_objs, max_num_ptrs, st_size_t{ 0 },
                    buffer.slot_size() );

        SIXTRL_ASSERT( max_num_objs >= num_elem );
        SIXTRL_ASSERT( max_num_slots > st_size_t{ 0 } );
        SIXTRL_ASSERT( requ_buffer_size > st_size_t{ 0 } );

        /* prepare view */

        std::vector< st_raw_data_t > view_raw_buffer(
            requ_buffer_size + buffer.slot_size() );

        st_size_t view_capacity = st_size_t{ 0 };
        st_addr_t const view_begin_addr = cbuffer_view_t::aligned_base_addr(
            reinterpret_cast< std::uintptr_t >( view_raw_buffer.data() ),
            view_raw_buffer.size(), st::Type_storage_align< E >(),
                &view_capacity, buffer.slot_size() );

        SIXTRL_ASSERT( view_begin_addr != cbuffer_view_t::NULL_ADDRESS );
        SIXTRL_ASSERT( view_capacity >= requ_buffer_size );

        cbuffer_view_t view( view_begin_addr, buffer.slot_size(),
                             view_capacity );

        SIXTRL_ASSERT( view.capacity() >= requ_buffer_size );
        SIXTRL_ASSERT( view.can_allocate(
            max_num_slots, max_num_objs, max_num_ptrs, st_size_t{ 0 } ) );

        status = st::CObjStatus_to_status( view.allocate(
            max_num_slots, max_num_objs, max_num_ptrs, st_size_t{ 0 } ) );
        if( status != st::ARCH_STATUS_SUCCESS )
        {
            std::cout << "exit point 02" << std::endl;
            return status;
        }

        SIXTRL_ASSERT( view.max_slots()    >= max_num_slots );
        SIXTRL_ASSERT( view.max_objects()  >= max_num_objs );
        SIXTRL_ASSERT( view.max_pointers() >= max_num_ptrs );

        /* prepare buffer */

        for( st_size_t ii = st_size_t{ 0 } ; ii < num_elem ; ++ii )
        {
            delegate_t const* orig = std::addressof( orig_elems[ ii ] );
            status = st::tests::CObjElem_test_impl_direct_create_view_buffer<
                delegate_t >( orig, ii, delegate_init, view, buffer,
                    requ_num_slots, requ_num_objs, requ_num_ptrs );
            if( status != st::ARCH_STATUS_SUCCESS )
            {
                std::cout << "exit point 03" << std::endl;
                break;
            }
        }

        if( ( status != st::ARCH_STATUS_SUCCESS ) ||
            ( view.n_objects()   != num_elem ) ||
            ( buffer.n_objects() != num_elem ) )
        {
            status |= st::ARCH_STATUS_GENERAL_FAILURE;
            std::cout << "exit point 04" << std::endl;
            return status;
        }

        /* compare all buffer/view elems with the orig elements in one go */

        for( st_size_t ii = st_size_t{ 0 } ; ii < num_elem ; ++ii )
        {
            delegate_t const* orig = std::addressof( orig_elems[ ii ] );
            status = st::tests::CObjElem_test_impl_compare_view_and_buffer_direct(
                orig, ii, view, buffer );

            if( status != st::ARCH_STATUS_SUCCESS )
            {
                std::cout << "exit point 05" << std::endl;
                break;
            }
        }

        obj_init_t obj_init;
        std::vector< E > obj_elems( num_elem, E{} );
        std::vector< E > obj_diffs( num_elem, E{} );
        std::vector< E > cmp_obj_diffs( num_elem, E{} );
        std::vector< delegate_t > delegate_diffs( num_elem, delegate_t{} );
        std::vector< delegate_t > cmp_result_diffs( num_elem, delegate_t{} );

        /* perform the store / load tests with the objects via the delegates */
        for( st_size_t ii = st_size_t{ 0 } ; ii < num_elem ; ++ii )
        {
            delegate_t const* orig = std::addressof( orig_elems[ ii ] );

            SIXTRL_BUFFER_DATAPTR_DEC delegate_t* elem_v =
                view.get_object< delegate_t >( ii );

            SIXTRL_BUFFER_DATAPTR_DEC delegate_t* elem_b =
                buffer.get_object< delegate_t >( ii );

            if( ( orig   == nullptr ) || ( elem_v == nullptr ) ||
                ( elem_b == nullptr ) || ( elem_v == elem_b  ) ||
                ( elem_b == orig    ) || ( elem_v == orig    ) )
            {
                status = st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }

            E* obj = std::addressof( obj_elems[ ii ] );
            status = obj_init.init_for_copy( obj, orig );
            if( status != st::ARCH_STATUS_SUCCESS )
            {
                std::cout << "exit point 06" << std::endl;
                break;
            }

            /* ------------------------------------------------------------- */
            /* verify initial state -> buffer, view and orig elem should
             * compare equal */

            auto cmp_result = st::ObjDataComparisonHelper<
                delegate_t, delegate_t >::compare( elem_v, orig );

            if( cmp_result != st::TypeCompResultTraits<
                decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                std::cout << "exit point 07" << std::endl;
                break;
            }

            cmp_result = st::ObjDataComparisonHelper<
                delegate_t, delegate_t >::compare( elem_b, orig );

            if( cmp_result != st::TypeCompResultTraits<
                decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                std::cout << "exit point 08" << std::endl;
                break;
            }

            cmp_result = st::ObjDataComparisonHelper<
                delegate_t, delegate_t >::compare( elem_v, elem_b );

            if( cmp_result != st::TypeCompResultTraits<
                decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                std::cout << "exit point 09" << std::endl;
                break;
            }

            /* ------------------------------------------------------------- */
            /* Create diffs */
            /* elem_v == A, elem_b == A, orig == A */

            status = delegate_init.randomise_values( elem_v );
            if( status != st::ARCH_STATUS_SUCCESS )
            {
                std::cout << "exit point 10" << std::endl;
                break;
            }

            /* elem_v == B, elem_b == A, orig == A */

            status = st::ObjDataConverter< delegate_t, E,
                st::STORAGE_BE_COBJECTS, st::STORAGE_BE_DEFAULT >::perform(
                    obj, elem_v );
            if( status != st::ARCH_STATUS_SUCCESS )
            {
                std::cout << "exit point 11" << std::endl;
                break;
            }

            /* elem_v == B, elem_b == A, orig == A, obj ~ B */

            E* obj_load_diff = std::addressof( obj_diffs[ ii ] );
            status = obj_init.init_for_copy( obj_load_diff, orig );
            if( status != st::ARCH_STATUS_SUCCESS )
            {
                std::cout << "exit point 12" << std::endl;
                break;
            }

            E* cmp_obj_diff = std::addressof( cmp_obj_diffs[ ii ] );
            status = obj_init.init_for_copy( cmp_obj_diff, orig );
            if( status != st::ARCH_STATUS_SUCCESS )
            {
                std::cout << "exit point 13" << std::endl;
                break;
            }

            status = st::ObjDataDiffHelper< E, delegate_t, E >::calculate(
                        obj_load_diff, obj, elem_v );
            if( status != st::ARCH_STATUS_SUCCESS )
            {
                std::cout << "exit point 14" << std::endl;
                break;
            }

            status = st::ObjDataConverter< E, delegate_t, st::STORAGE_BE_DEFAULT
                , st::STORAGE_BE_COBJECTS >::perform( elem_v, obj );
            if( status != st::ARCH_STATUS_SUCCESS )
            {
                std::cout << "exit point 15" << std::endl;
                break;
            }

            /* elem_v ~= B, elem_b == A, orig == A, obj ~ B */

            delegate_t* obj_store_diff = std::addressof( delegate_diffs[ ii ] );
            status = delegate_init.init_for_copy( obj_store_diff, orig );
            if( status != st::ARCH_STATUS_SUCCESS )
            {
                std::cout << "exit point 16" << std::endl;
                break;
            }

            status = st::ObjDataDiffHelper< delegate_t, E, delegate_t
                >::calculate( obj_store_diff, elem_v, obj );
            if( status != st::ARCH_STATUS_SUCCESS )
            {
                std::cout << "exit point 17" << std::endl;
                break;
            }

            delegate_t* cmp_result_diff = std::addressof(
                cmp_result_diffs[ ii ] );

            status = delegate_init.init_for_copy( cmp_result_diff, orig );
            if( status != st::ARCH_STATUS_SUCCESS )
            {
                std::cout << "exit point 18" << std::endl;
                break;
            }

            status = buffer.load_object( ii, elem_v );
            if( status != st::ARCH_STATUS_SUCCESS )
            {
                std::cout << "exit point 19" << std::endl;
                break;
            }

            /* elem_v == A, elem_b == A, orig == A, obj ~ B */

            /* ------------------------------------------------------------- */
            /* Again, verify initial state -> buffer, view and orig elem should
             * compare equal even after making the diffs
             *
             * orig == A, elem_v == A, elem_b == A, obj ~ B */

            cmp_result = st::ObjDataComparisonHelper<
                delegate_t, delegate_t >::compare( elem_v, orig );

            if( cmp_result != st::TypeCompResultTraits<
                decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                std::cout << "exit point 20" << std::endl;
                break;
            }

            cmp_result = st::ObjDataComparisonHelper<
                delegate_t, delegate_t >::compare( elem_b, orig );

            if( cmp_result != st::TypeCompResultTraits<
                decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                std::cout << "exit point 21" << std::endl;
                break;
            }

            cmp_result = st::ObjDataComparisonHelper<
                delegate_t, delegate_t >::compare( elem_v, elem_b );

            if( cmp_result != st::TypeCompResultTraits<
                decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                std::cout << "exit point 22" << std::endl;
                break;
            }

            /* ------------------------------------------------------------- */
            /* store obj -> elem_v */
            /* elem_v == A, elem_b == A, orig == A, obj ~ B */

            status = buffer.store_object( ii, obj );
            if( status != st::ARCH_STATUS_SUCCESS )
            {
                std::cout << "exit point 23" << std::endl;
                break;
            }

            /* elem_v == A, elem_b == B, orig == A, obj ~ B */

            cmp_result = st::ObjDataComparisonHelper<
                delegate_t, delegate_t >::compare( elem_v, orig );

            if( cmp_result != st::TypeCompResultTraits<
                decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                std::cout << "exit point 24" << std::endl;
                break;
            }

            cmp_result = st::ObjDataComparisonHelper<
                delegate_t, delegate_t >::compare( elem_b, orig );

            if( cmp_result == st::TypeCompResultTraits<
                decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                std::cout << "exit point 25" << std::endl;
                break;
            }

            cmp_result = st::ObjDataComparisonHelper<
                delegate_t, delegate_t >::compare( elem_v, elem_b );

            if( cmp_result == st::TypeCompResultTraits<
                decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                std::cout << "exit point 26" << std::endl;
                break;
            }

            status = st::ObjDataDiffHelper< delegate_t, E, delegate_t
                >::calculate( cmp_result_diff, elem_b, obj );
            if( status != st::ARCH_STATUS_SUCCESS )
            {
                std::cout << "exit point 27" << std::endl;
                break;
            }

            cmp_result = st::ObjDataComparisonHelper<
                delegate_t, delegate_t >::compare(
                    cmp_result_diff, obj_store_diff );

            if( cmp_result != st::TypeCompResultTraits<
                decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                std::cout << "exit point 28" << std::endl;
                break;
            }

            /* ------------------------------------------------------------- */
            /* store obj -> elem_b */
            /* elem_v == B, elem_b == B, orig == A, obj ~ B */

            status = view.store_object( ii, obj );
            if( status != st::ARCH_STATUS_SUCCESS )
            {
                std::cout << "exit point 29" << std::endl;
                break;
            }

            cmp_result = st::ObjDataComparisonHelper<
                delegate_t, delegate_t >::compare( elem_v, orig );

            if( cmp_result == st::TypeCompResultTraits<
                decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                std::cout << "exit point 30" << std::endl;
                break;
            }

            cmp_result = st::ObjDataComparisonHelper<
                delegate_t, delegate_t >::compare( elem_b, orig );

            if( cmp_result == st::TypeCompResultTraits<
                decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                std::cout << "exit point 31" << std::endl;
                break;
            }

            cmp_result = st::ObjDataComparisonHelper<
                delegate_t, delegate_t >::compare( elem_v, elem_b );

            if( cmp_result != st::TypeCompResultTraits<
                decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                std::cout << "exit point 32" << std::endl;
                break;
            }

            status = st::ObjDataDiffHelper< delegate_t, E, delegate_t
                >::calculate( cmp_result_diff, elem_v, obj );
            if( status != st::ARCH_STATUS_SUCCESS )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                std::cout << "exit point 33" << std::endl;
                break;
            }

            cmp_result = st::ObjDataComparisonHelper<
                delegate_t, delegate_t >::compare(
                    cmp_result_diff, obj_store_diff );

            if( cmp_result != st::TypeCompResultTraits<
                decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                std::cout << "exit point 34" << std::endl;
                break;
            }

            /* ------------------------------------------------------------- */
            /* elem_v == B, elem_b == B, orig == A, obj ~ A */

            status = st::ObjDataConverter< delegate_t, E,
                st::STORAGE_BE_DEFAULT, st::STORAGE_BE_DEFAULT >::perform(
                    obj, orig );
            if( status != st::ARCH_STATUS_SUCCESS )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                std::cout << "exit point 35" << std::endl;
                break;
            }

            status = view.load_object( ii, obj );
            if( status != st::ARCH_STATUS_SUCCESS )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                std::cout << "exit point 36" << std::endl;
                break;
            }

            status = st::ObjDataDiffHelper< E, delegate_t, E >::calculate(
                cmp_obj_diff, obj, elem_v );
            if( status != st::ARCH_STATUS_SUCCESS )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                std::cout << "exit point 37" << std::endl;
                break;
            }

             cmp_result = st::ObjDataComparisonHelper< E, E >::compare(
                 cmp_obj_diff, obj_load_diff );

            if( cmp_result != st::TypeCompResultTraits<
                decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                std::cout << "exit point 38" << std::endl;
                break;
            }

            status = st::ObjDataConverter< delegate_t, E,
                st::STORAGE_BE_DEFAULT, st::STORAGE_BE_DEFAULT >::perform(
                    obj, orig );
            if( status != st::ARCH_STATUS_SUCCESS )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                std::cout << "exit point 39" << std::endl;
                break;
            }

            status = buffer.load_object( ii, obj );
            if( status != st::ARCH_STATUS_SUCCESS )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                std::cout << "exit point 40" << std::endl;
                break;
            }

            status = st::ObjDataDiffHelper< E, delegate_t, E >::calculate(
                cmp_obj_diff, obj, elem_b );
            if( status != st::ARCH_STATUS_SUCCESS )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                std::cout << "exit point 41" << std::endl;
                break;
            }

             cmp_result = st::ObjDataComparisonHelper< E, E >::compare(
                 cmp_obj_diff, obj_load_diff );

            if( cmp_result != st::TypeCompResultTraits<
                decltype( cmp_result ) >::CMP_LHS_EQUAL_RHS )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                std::cout << "exit point 42" << std::endl;
                break;
            }

            /* ------------------------------------------------------------- */

            status = view.store_object( ii, orig );
            if( status != st::ARCH_STATUS_SUCCESS )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                std::cout << "exit point 43" << std::endl;
                break;
            }

            status = buffer.store_object( ii, orig );
            if( status != st::ARCH_STATUS_SUCCESS )
            {
                status |= st::ARCH_STATUS_GENERAL_FAILURE;
                std::cout << "exit point 44" << std::endl;
                break;
            }
        }

        if( status != st::ARCH_STATUS_SUCCESS )
        {
            std::cout << "exit point 45" << std::endl;
        }

        return status;
    }

} /* namespace: tests */
} /* namespace: SIXTRL_CXX_NAMESPACE */

#endif /* C++ */
#endif /* SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_COBJECTS_GTEST_DIRECT_BASE_CXX_HPP__ */
