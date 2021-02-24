#ifndef SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_COBJ_TEST_DATAPTRS_CXX_HPP__
#define SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_COBJ_TEST_DATAPTRS_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/testlib/common/cobjects/definitions.h"
    #include "sixtracklib/testlib/common/cobjects/cobj_dataptrs.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus )
    #include <algorithm>
    #include <random>
    #include <vector>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
namespace testlib
{
    template< class PrngT, class ElemAlloc, class PtrAlloc >
    SIXTRL_STATIC SIXTRL_HOST_FN ::NS(status_type)
    CObjTestDataptrs_prepare_cmp_elements(
        std::vector< ::NS(CObjTestDataptrs), ElemAlloc >& SIXTRL_RESTRICT_REF cmp,
        std::vector< ::NS(cobj_test_real_type), PtrAlloc >&
            SIXTRL_RESTRICT_REF cmp_ptr_data,
        ::NS(cobj_size_type) const num_elements,
        ::NS(cobj_size_type) const min_b_capacity,
        ::NS(cobj_size_type) const max_b_capacity,
        ::NS(cobj_size_type) const min_c_capacity,
        ::NS(cobj_size_type) const max_c_capacity,
        PrngT& SIXTRL_RESTRICT_REF prng,
        ::NS(cobj_size_type) const slot_size = ::NS(CBUFFER_DEFAULT_SLOT_SIZE),
        ::NS(cobj_size_type) const copies_per_elem = ::NS(cobj_size_type){ 1 },
        ::NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_n_slots = nullptr,
        ::NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_n_objs  = nullptr,
        ::NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_n_ptrs  = nullptr );


    /* ********************************************************************* */

    template< class PrngT, class ElemAlloc, class PtrAlloc >
    SIXTRL_INLINE ::NS(status_type) CObjTestDataptrs_prepare_cmp_elements(
        std::vector< ::NS(CObjTestDataptrs), ElemAlloc >& SIXTRL_RESTRICT_REF cmp,
        std::vector< ::NS(cobj_test_real_type), PtrAlloc >&
            SIXTRL_RESTRICT_REF cmp_ptr_data,
        ::NS(cobj_size_type) const num_elements,
        ::NS(cobj_size_type) const min_b_capacity,
        ::NS(cobj_size_type) const max_b_capacity,
        ::NS(cobj_size_type) const min_c_capacity,
        ::NS(cobj_size_type) const max_c_capacity,
        PrngT& SIXTRL_RESTRICT_REF prng,
        ::NS(cobj_size_type) const slot_size,
        ::NS(cobj_size_type) const num_copies_per_elem,
        ::NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_n_slots,
        ::NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_n_objs,
        ::NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_n_ptrs ) {

        namespace st = SIXTRL_CXX_NAMESPACE;
        using real_type = ::NS(cobj_test_real_type);
        using uint_type = ::NS(cobj_test_uint64_type);
        using st_size_t = ::NS(cobj_size_type);

        st::status_type status = st::STATUS_GENERAL_FAILURE;

        if( ( num_elements == st_size_t{ 0 } ) ||
            ( num_copies_per_elem == st_size_t{ 0 } ) ||
            ( max_b_capacity == st_size_t{ 0 } ) ||
            ( min_b_capacity > max_b_capacity ) ||
            ( max_c_capacity == st_size_t{ 0 } ) ||
            ( min_c_capacity > max_c_capacity ) ) return status;

        status = st::STATUS_SUCCESS;

        std::uniform_real_distribution< real_type > a_dist( -5.0, 5.0 );
        std::uniform_real_distribution< real_type > vec_dist( -42.0, 42.0 );
        std::uniform_int_distribution<  uint_type > b_capacity_dist(
            min_b_capacity, max_b_capacity );
        std::uniform_int_distribution<  uint_type > c_capacity_dist(
            min_c_capacity, max_c_capacity );

        st_size_t requ_n_slots = st_size_t{ 0 };
        st_size_t requ_n_objs  = st_size_t{ 0 };
        st_size_t requ_n_ptrs  = st_size_t{ 0 };

        st_size_t num_b_values = st_size_t{ 0 };
        st_size_t num_c_values = st_size_t{ 0 };

        cmp.clear();
        cmp.resize( num_elements, ::NS(CObjTestDataptrs){} );

        cmp_ptr_data.clear();
        cmp_ptr_data.reserve( ( max_b_capacity + max_c_capacity ) *
            num_elements );

        for( auto& elem : cmp )
        {
            status |= ::NS(CObjTestDataptrs_clear)( &elem );
            status |= ::NS(CObjTestDataptrs_set_a)( &elem, a_dist( prng ) );

            uint_type const b_capacity = b_capacity_dist( prng );
            uint_type b_length = b_capacity_dist( prng );
            if( b_length > b_capacity ) b_length = b_capacity;

            status |= ::NS(CObjTestDataptrs_set_b_capacity)( &elem, b_capacity );
            status |= ::NS(CObjTestDataptrs_set_b_length)( &elem, b_length );
            if( status != st::STATUS_SUCCESS ) break;
            num_b_values += b_capacity;

            uint_type const c_capacity = c_capacity_dist( prng );
            uint_type c_length = c_capacity_dist( prng );
            if( c_length > c_capacity ) c_length = c_capacity;

            status |= ::NS(CObjTestDataptrs_set_c_capacity)( &elem, c_capacity );
            status |= ::NS(CObjTestDataptrs_set_c_length)( &elem, c_length );
            if( status != st::STATUS_SUCCESS ) break;
            num_c_values += c_capacity;
        }

        if( status != st::STATUS_SUCCESS ) return status;
        cmp_ptr_data.resize( num_b_values + num_c_values, real_type{ 0 } );
        for( auto& val : cmp_ptr_data ) val = vec_dist( prng );

        st_size_t ptr_data_offset = st_size_t{ 0 };

        for( auto& elem : cmp )
        {
            status |= ::NS(CObjTestDataptrs_set_b_addr)( &elem, reinterpret_cast<
                uintptr_t >( &cmp_ptr_data[ ptr_data_offset ] ) );
            ptr_data_offset += ::NS(CObjTestDataptrs_b_capacity)( &elem );

            status |= ::NS(CObjTestDataptrs_set_c_addr)( &elem, reinterpret_cast<
                uintptr_t >( &cmp_ptr_data[ ptr_data_offset ] ) );
            ptr_data_offset += ::NS(CObjTestDataptrs_c_capacity)( &elem );

            st_size_t const n_bytes =
                ::NS(CObjTestDataptrs_cobj_required_num_bytes)(
                    &elem, slot_size );
            st_size_t n_slots = n_bytes / slot_size;
            if( n_slots * slot_size < n_bytes ) ++n_slots;

            requ_n_slots += num_copies_per_elem * n_slots;
            requ_n_objs  += num_copies_per_elem;
            requ_n_ptrs  += num_copies_per_elem *
                            ::NS(CObjTestDataptrs_cobj_num_dataptrs)();
        }

        if( ( status == st::STATUS_SUCCESS ) &&
            ( ptr_data_offset != cmp_ptr_data.size() ) ) {
            status = st::STATUS_GENERAL_FAILURE; }

        if( status == st::STATUS_SUCCESS )
        {
            if(  ptr_requ_n_slots != nullptr )
                *ptr_requ_n_slots += requ_n_slots;

            if(  ptr_requ_n_objs != nullptr )
                *ptr_requ_n_objs += requ_n_objs;

            if(  ptr_requ_n_ptrs != nullptr )
                *ptr_requ_n_ptrs += requ_n_ptrs;
        }

        return status;
    }

} /* ns: testlib */
} /* ns: SIXTRL_CXX_NAMESPACE */
#endif /* C++ */

#endif /* SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_COBJ_TEST_DATAPTRS_CXX_HPP__*/
