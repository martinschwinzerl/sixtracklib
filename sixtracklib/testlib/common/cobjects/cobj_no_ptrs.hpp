#ifndef SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_COBJ_TEST_NO_PTRS_CXX_HPP__
#define SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_COBJ_TEST_NO_PTRS_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/testlib/common/cobjects/definitions.h"
    #include "sixtracklib/testlib/common/cobjects/cobj_no_ptrs.h"
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
    template< class PrngT, class ElemAlloc >
    SIXTRL_STATIC SIXTRL_HOST_FN ::NS(status_type)
    CObjTestNoPtrs_prepare_cmp_elements(
        std::vector< ::NS(CObjTestNoPtrs), ElemAlloc >& SIXTRL_RESTRICT_REF cmp,
        ::NS(cobj_size_type) const num_elements,
        PrngT& SIXTRL_RESTRICT_REF prng,
        ::NS(cobj_size_type) const slot_size = ::NS(CBUFFER_DEFAULT_SLOT_SIZE),
        ::NS(cobj_size_type) const copies_per_elem = ::NS(cobj_size_type){ 1 },
        ::NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_n_slots = nullptr,
        ::NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_n_objs  = nullptr,
        ::NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_n_ptrs  = nullptr );

    /* ********************************************************************* */

    template< class PrngT, class ElemAlloc >
    SIXTRL_INLINE ::NS(status_type) CObjTestNoPtrs_prepare_cmp_elements(
        std::vector< ::NS(CObjTestNoPtrs), ElemAlloc >& SIXTRL_RESTRICT_REF cmp,
        ::NS(cobj_size_type) const num_elements,
        PrngT& SIXTRL_RESTRICT_REF prng,
        ::NS(cobj_size_type) const slot_size,
        ::NS(cobj_size_type) const num_copies_per_elem,
        ::NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_n_slots,
        ::NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_n_objs,
        ::NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_n_ptrs ) {

        namespace st = SIXTRL_CXX_NAMESPACE;
        using real_type = ::NS(cobj_test_real_type);
        using uint_type = ::NS(cobj_test_uint64_type);
        using int_type  = ::NS(cobj_test_int64_type);
        using st_size_t = ::NS(cobj_size_type);
        st::status_type status = st::STATUS_GENERAL_FAILURE;

        if( ( num_elements == st_size_t{ 0 } ) ||
            ( num_copies_per_elem == st_size_t{ 0 } ) ) return status;

        status = st::STATUS_SUCCESS;

        std::uniform_real_distribution< real_type > a_dist( -5.0, 5.0 );
        std::uniform_int_distribution<  uint_type > b_dist( 0, 20 );
        std::uniform_real_distribution< real_type > vec_dist( -42.0, 42.0 );
        std::uniform_int_distribution<  int_type  > d_dist( -100, -1 );

        st_size_t requ_n_slots = st_size_t{ 0 };
        st_size_t requ_n_objs  = st_size_t{ 0 };
        st_size_t requ_n_ptrs  = st_size_t{ 0 };

        cmp.clear();
        cmp.resize( num_elements, ::NS(CObjTestNoPtrs){} );

        for( auto& elem : cmp )
        {
            st_size_t const c_length = ::NS(CObjTestNoPtrs_c_length)( &elem );

            status |= ::NS(CObjTestNoPtrs_set_a)( &elem, a_dist( prng ) );
            status |= ::NS(CObjTestNoPtrs_set_b)( &elem, b_dist( prng ) );

            for( st::size_type ii = 0u ; ii < c_length ; ++ii ) {
                status |= ::NS(CObjTestNoPtrs_set_c)(
                    &elem, ii, vec_dist( prng ) ); }

            status |= ::NS(CObjTestNoPtrs_set_d)( &elem, d_dist( prng ) );

            st_size_t const n_bytes =
                ::NS(CObjTestNoPtrs_cobj_required_num_bytes)( &elem, slot_size );
            st_size_t n_slots = n_bytes / slot_size;
            if( n_slots * slot_size < n_bytes ) ++n_slots;
            requ_n_slots += num_copies_per_elem * n_slots;
            requ_n_objs  += num_copies_per_elem;
            requ_n_ptrs  += num_copies_per_elem *
                            ::NS(CObjTestNoPtrs_cobj_num_dataptrs)();
        }

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

#endif /* SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_COBJ_TEST_NO_PTRS_CXX_HPP__*/
