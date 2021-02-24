#include <algorithm>
#include <cstdint>
#include <cmath>
#include <random>
#include <vector>

#include <gtest/gtest.h>

#include "sixtracklib/common/beam_elements/cavity/cavity.h"
#include "sixtracklib/common/cobjects/cobj_type_traits.h"
#include "sixtracklib/common/cobjects/cbuffer.h"
#include "sixtracklib/common/cobjects/cbuffer.hpp"

#include "sixtracklib/testlib.h"

TEST( C99CommonBeamElementsLimitRect, CobjectsStoreAndRestore )
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    using size_type   = ::NS(cobj_size_type);
    using elem_type   = ::NS(LimitRect);
    using raw_type    = ::NS(cobj_raw_type);
    using real_type   = ::NS(be_real_type);

    static size_type constexpr NUM_BELEMENTS = size_type{ 1000 };

    ASSERT_TRUE( st::CObjects_type_id< elem_type >() ==
                 st::COBJECTS_TYPE_ID_LIMIT_RECT );
    ASSERT_TRUE( st::CObjects_is_trivial_type< elem_type >() );
    ASSERT_TRUE( st::CObjects_num_pointers< elem_type >() == size_type{ 0 } );

    ASSERT_TRUE( ::NS(LimitRect_cobj_num_dataptrs)() == size_type{ 0 } );
    ASSERT_TRUE( ::NS(LimitRect_cobj_type_id)() ==
                 ::NS(COBJECTS_TYPE_ID_LIMIT_RECT) );

    /* --------------------------------------------------------------------- */
    /* prepare comparison data */

    std::mt19937_64 prng( std::mt19937_64::result_type{ 20210212 } );

    std::uniform_real_distribution< real_type > x_min_dist(
        real_type{ -1.0 }, real_type{ +0.0 } );

    std::uniform_real_distribution< real_type > x_max_dist(
        real_type{ +0.0 }, real_type{ +1.0 } );

    std::uniform_real_distribution< real_type > y_min_dist(
        real_type{ -1.0 }, real_type{ +0.0 } );

    std::uniform_real_distribution< real_type > y_max_dist(
        real_type{ +0.0 }, real_type{ +1.0 } );

    /* gather information to prepare a cobj flat buffer */

    size_type const slot_size = st::CBUFFER_DEFAULT_SLOT_SIZE;
    size_type n_slots = size_type{ 0 };
    size_type const n_objs = NUM_BELEMENTS;
    size_type const n_ptrs = ::NS(LimitRect_cobj_num_dataptrs)() * NUM_BELEMENTS;

    std::vector< elem_type > CMP_ELEMENTS( NUM_BELEMENTS, elem_type{} );
    for( auto& e : CMP_ELEMENTS )
    {
        ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(LimitRect_init)( &e,
            x_min_dist( prng ), x_max_dist( prng ), y_min_dist( prng ),
                y_max_dist( prng ) ) );

        n_slots += ::NS(LimitRect_cobj_required_num_bytes)(
            &e, slot_size ) / slot_size;
    }

    /* --------------------------------------------------------------------- */
    /* prepare a flat buffer, a ::NS(Cbuffer) and a c++ CBufffer */

    ASSERT_TRUE( n_ptrs  == size_type{ 0 } );
    ASSERT_TRUE( n_slots  > size_type{ 0 } );
    size_type flat_buffer_capacity =
        ::NS(CObjFlatBuffer_predict_required_buffer_size)(
            n_slots, n_objs, n_ptrs, size_type{ 0 }, slot_size );

    ASSERT_TRUE( flat_buffer_capacity >
        ::NS(CBuffer_min_buffer_size)( slot_size ) );

    std::vector< raw_type > stored_flat_buffer(
        flat_buffer_capacity + slot_size, raw_type{ 0 } );

    SIXTRL_CBUFFER_DATAPTR_DEC raw_type* flat_buffer = reinterpret_cast<
        SIXTRL_CBUFFER_DATAPTR_DEC raw_type* >( static_cast< uintptr_t >(
            ::NS(CObjFlatBuffer_aligned_base_addr)(
                reinterpret_cast< uintptr_t >( stored_flat_buffer.data() ),
                flat_buffer_capacity, slot_size, &flat_buffer_capacity,
                    slot_size ) ) );

    ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(CObjFlatBuffer_init_empty_detailed)(
        flat_buffer, flat_buffer_capacity, slot_size, n_slots, n_objs, n_ptrs,
            size_type{ 0 }, SIXTRL_NULLPTR ) );

    SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer)* c99_buffer = ::NS(CBuffer_new)();
    ASSERT_TRUE( c99_buffer != nullptr );
    ASSERT_TRUE( ::NS(CBuffer_p_const_base_begin)( c99_buffer ) != nullptr );
    ASSERT_TRUE( ::NS(CBuffer_slot_size)( c99_buffer ) == slot_size );
    ASSERT_TRUE( ::NS(CBuffer_size)( c99_buffer ) >=
                 ::NS(CBuffer_min_buffer_size)( slot_size ) );

    st::CBuffer cxx_buffer;
    ASSERT_TRUE( cxx_buffer.p_const_base_begin() != nullptr );
    ASSERT_TRUE( cxx_buffer.slot_size() == slot_size );
    ASSERT_TRUE( cxx_buffer.size() >= st::CBuffer::MIN_BUFFER_SIZE( slot_size ) );

    /* --------------------------------------------------------------------- */
    /* Add all elements from the compare data set to each buffer */

    for( size_type ii = 0u ; ii < NUM_BELEMENTS ; ++ii )
    {
        SIXTRL_BE_ARGPTR_DEC elem_type* flat_buffer_obj = nullptr;
        SIXTRL_BE_ARGPTR_DEC elem_type* c99_buffer_obj  = nullptr;
        SIXTRL_BE_ARGPTR_DEC elem_type* cxx_buffer_obj  = nullptr;

        SIXTRL_BE_ARGPTR_DEC elem_type const* cmp_obj = &CMP_ELEMENTS[ ii ];

        size_type constexpr TEMP_NN = size_type{ 25 };
        SIXTRL_ASSERT( ::NS(LimitRect_cobj_num_dataptrs)() < TEMP_NN );

        SIXTRL_ARGPTR_DEC size_type OFFSETS[ TEMP_NN ];
        SIXTRL_ARGPTR_DEC size_type SIZES[ TEMP_NN ];
        SIXTRL_ARGPTR_DEC size_type COUNTS[ TEMP_NN ];

        ASSERT_TRUE( st::STATUS_SUCCESS == st::CObjects_attribute_offsets<
            elem_type >( &OFFSETS[ 0 ], TEMP_NN, cmp_obj, slot_size ) );

        ASSERT_TRUE( st::STATUS_SUCCESS == st::CObjects_attribute_sizes<
            elem_type >( &SIZES[ 0 ], TEMP_NN, cmp_obj, slot_size ) );

        ASSERT_TRUE( st::STATUS_SUCCESS == st::CObjects_attribute_counts<
            elem_type >( &COUNTS[ 0 ], TEMP_NN, cmp_obj, slot_size ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* Flat Buffer: */

        size_type const flat_buffer_mode = ii % size_type{ 7 };

        switch( flat_buffer_mode )
        {
            case 0:
            {
                flat_buffer_obj = ::NS(LimitRect_cobj_flat_buffer_new)(
                    flat_buffer, slot_size );

                ASSERT_TRUE( flat_buffer_obj != nullptr );

                ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(LimitRect_set_x_min)(
                    flat_buffer_obj, ::NS(LimitRect_x_min)( cmp_obj ) ) );

                ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(LimitRect_set_x_max)(
                    flat_buffer_obj, ::NS(LimitRect_x_max)( cmp_obj ) ) );

                ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(LimitRect_set_y_min)(
                    flat_buffer_obj, ::NS(LimitRect_y_min)( cmp_obj ) ) );

                ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(LimitRect_set_y_max)(
                    flat_buffer_obj, ::NS(LimitRect_y_max)( cmp_obj ) ) );

                break;
            }

            case 1:
            {
                flat_buffer_obj = ::NS(LimitRect_cobj_flat_buffer_new)(
                    flat_buffer, slot_size );

                ASSERT_TRUE( flat_buffer_obj != nullptr );

                ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(LimitRect_copy)(
                    flat_buffer_obj, cmp_obj ) );

                break;
            }

            case 2:
            {
                flat_buffer_obj = ::NS(LimitRect_cobj_flat_buffer_add)(
                    flat_buffer, slot_size,
                        ::NS(LimitRect_x_min)( cmp_obj ),
                        ::NS(LimitRect_x_max)( cmp_obj ),
                        ::NS(LimitRect_y_min)( cmp_obj ),
                        ::NS(LimitRect_y_max)( cmp_obj ) );

                break;
            }

            case 3:
            {
                flat_buffer_obj = ::NS(LimitRect_cobj_flat_buffer_add_copy)(
                    flat_buffer, slot_size, cmp_obj );

                break;
            }

            case 4:
            {
                flat_buffer_obj = ::NS(LimitRect_from_cobj_index)(
                    ::NS(CObjFlatBuffer_add_copy_of_trivial_object)(
                        flat_buffer, slot_size, cmp_obj,
                        ::NS(LimitRect_cobj_reserved_handle_size)( slot_size ),
                        ::NS(LimitRect_cobj_type_id)(), true ) );

                break;
            }

            case 5:
            {
                flat_buffer_obj = ::NS(LimitRect_from_cobj_index)(
                    ::NS(CObjFlatBuffer_add_copy_of_object)(
                        flat_buffer, slot_size, cmp_obj,
                        ::NS(LimitRect_cobj_reserved_handle_size)( slot_size ),
                        ::NS(LimitRect_cobj_type_id)(),
                        ::NS(LimitRect_cobj_num_dataptrs)(),
                        &OFFSETS[ 0 ], &SIZES[ 0 ], &COUNTS[ 0 ], true ) );

                break;
            }

            case 6:
            {
                flat_buffer_obj = ::NS(LimitRect_from_cobj_index)(
                    ::NS(CObjFlatBuffer_add_copy_of_object_detailed)(
                        flat_buffer, slot_size, cmp_obj,
                        ::NS(LimitRect_cobj_reserved_handle_size)( slot_size ),
                        ::NS(LimitRect_cobj_actual_handle_size)( slot_size ),
                        ::NS(LimitRect_cobj_type_id)(),
                        ::NS(LimitRect_cobj_num_dataptrs)(),
                        &OFFSETS[ 0 ], &SIZES[ 0 ], &COUNTS[ 0 ], true ) );

                break;
            }

            default:
            {
                flat_buffer_obj = nullptr;
            }
        };

        ASSERT_TRUE( flat_buffer_obj != nullptr );
        ASSERT_TRUE( flat_buffer_obj != cmp_obj );
        ASSERT_TRUE( 0 == ::NS(LimitRect_compare)( cmp_obj, flat_buffer_obj ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* c99_buffer: */

        size_type const c99_buffer_mode = ii % size_type{ 7 };

        switch( c99_buffer_mode )
        {
            case 0:
            {
                c99_buffer_obj = ::NS(LimitRect_cbuffer_new)( c99_buffer );

                ASSERT_TRUE( c99_buffer_obj != nullptr );

                ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(LimitRect_set_x_min)(
                    c99_buffer_obj, ::NS(LimitRect_x_min)( cmp_obj ) ) );

                ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(LimitRect_set_x_max)(
                    c99_buffer_obj, ::NS(LimitRect_x_max)( cmp_obj ) ) );

                ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(LimitRect_set_y_min)(
                    c99_buffer_obj, ::NS(LimitRect_y_min)( cmp_obj ) ) );

                ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(LimitRect_set_y_max)(
                    c99_buffer_obj, ::NS(LimitRect_y_max)( cmp_obj ) ) );

                break;
            }

            case 1:
            {
                c99_buffer_obj = ::NS(LimitRect_cbuffer_new)( c99_buffer );
                ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(LimitRect_copy)(
                    c99_buffer_obj, cmp_obj ) );
                break;
            }

            case 2:
            {
                c99_buffer_obj = ::NS(LimitRect_cbuffer_add)( c99_buffer,
                    ::NS(LimitRect_x_min)( cmp_obj ),
                    ::NS(LimitRect_x_max)( cmp_obj ),
                    ::NS(LimitRect_y_min)( cmp_obj ),
                    ::NS(LimitRect_y_max)( cmp_obj ) );
                break;
            }

            case 3:
            {
                c99_buffer_obj = ::NS(LimitRect_cbuffer_add_copy)(
                    c99_buffer, cmp_obj );
                break;
            }

            case 4:
            {
                c99_buffer_obj = ::NS(LimitRect_from_cobj_index)(
                    ::NS(CBuffer_add_copy_of_trivial_object)(
                        c99_buffer, cmp_obj,
                        ::NS(LimitRect_cobj_reserved_handle_size)( slot_size ),
                        ::NS(LimitRect_cobj_type_id)(), true ) );

                break;
            }

            case 5:
            {
                c99_buffer_obj = ::NS(LimitRect_from_cobj_index)(
                    ::NS(CBuffer_add_copy_of_object)(
                        c99_buffer, cmp_obj,
                        ::NS(LimitRect_cobj_reserved_handle_size)( slot_size ),
                        ::NS(LimitRect_cobj_type_id)(),
                        ::NS(LimitRect_cobj_num_dataptrs)(),
                        &OFFSETS[ 0 ], &SIZES[ 0 ], &COUNTS[ 0 ], true ) );

                break;
            }

            case 6:
            {
                c99_buffer_obj = ::NS(LimitRect_from_cobj_index)(
                    ::NS(CBuffer_add_copy_of_object_detailed)(
                        c99_buffer, cmp_obj,
                        ::NS(LimitRect_cobj_reserved_handle_size)( slot_size ),
                        ::NS(LimitRect_cobj_actual_handle_size)( slot_size ),
                        ::NS(LimitRect_cobj_type_id)(),
                        ::NS(LimitRect_cobj_num_dataptrs)(),
                        &OFFSETS[ 0 ], &SIZES[ 0 ], &COUNTS[ 0 ], true ) );

                break;
            }

            default:
            {
                c99_buffer_obj = nullptr;
            }
        };

        ASSERT_TRUE( c99_buffer_obj != nullptr );
        ASSERT_TRUE( c99_buffer_obj != cmp_obj );
        ASSERT_TRUE( c99_buffer_obj != flat_buffer_obj );
        ASSERT_TRUE( 0 == ::NS(LimitRect_compare)( cmp_obj, c99_buffer_obj ) );
        ASSERT_TRUE( 0 == ::NS(LimitRect_compare)(
                        flat_buffer_obj, c99_buffer_obj ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* cxx_buffer: */

        size_type cxx_buffer_mode = ii % size_type{ 8 };

        switch( cxx_buffer_mode )
        {
            case 0:
            {
                cxx_buffer_obj = ::NS(LimitRect_cbuffer_new)(
                    cxx_buffer.as_c_api() );

                ASSERT_TRUE( cxx_buffer_obj != nullptr );

                ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(LimitRect_set_x_min)(
                    cxx_buffer_obj, ::NS(LimitRect_x_min)( cmp_obj ) ) );

                ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(LimitRect_set_x_max)(
                    cxx_buffer_obj, ::NS(LimitRect_x_max)( cmp_obj ) ) );

                ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(LimitRect_set_y_min)(
                    cxx_buffer_obj, ::NS(LimitRect_y_min)( cmp_obj ) ) );

                ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(LimitRect_set_y_max)(
                    cxx_buffer_obj, ::NS(LimitRect_y_max)( cmp_obj ) ) );

                break;
            }

            case 1:
            {
                cxx_buffer_obj = ::NS(LimitRect_cbuffer_new)(
                    cxx_buffer.as_c_api() );

                ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(LimitRect_copy)(
                    cxx_buffer_obj, cmp_obj ) );
                break;
            }

            case 2:
            {
                cxx_buffer_obj = ::NS(LimitRect_cbuffer_add)(
                    cxx_buffer.as_c_api(),
                    ::NS(LimitRect_x_min)( cmp_obj ),
                    ::NS(LimitRect_x_max)( cmp_obj ),
                    ::NS(LimitRect_y_min)( cmp_obj ),
                    ::NS(LimitRect_y_max)( cmp_obj ) );
                break;
            }

            case 3:
            {
                cxx_buffer_obj = ::NS(LimitRect_cbuffer_add_copy)(
                    cxx_buffer.as_c_api(), cmp_obj );
                break;
            }

            case 4:
            {
                cxx_buffer_obj = ::NS(LimitRect_from_cobj_index)(
                    cxx_buffer.add_copy_of_trivial_object( cmp_obj,
                        ::NS(LimitRect_cobj_reserved_handle_size)( slot_size ),
                        ::NS(LimitRect_cobj_type_id)() ) );

                break;
            }

            case 5:
            {
                cxx_buffer_obj = ::NS(LimitRect_from_cobj_index)(
                    cxx_buffer.add_copy_of_object( cmp_obj,
                        ::NS(LimitRect_cobj_reserved_handle_size)( slot_size ),
                        ::NS(LimitRect_cobj_type_id)(),
                        ::NS(LimitRect_cobj_num_dataptrs)(),
                        &OFFSETS[ 0 ], &SIZES[ 0 ], &COUNTS[ 0 ] ) );

                break;
            }

            case 6:
            {
                cxx_buffer_obj = ::NS(LimitRect_from_cobj_index)(
                    cxx_buffer.add_copy_of_object_detailed( cmp_obj,
                        ::NS(LimitRect_cobj_reserved_handle_size)( slot_size ),
                        ::NS(LimitRect_cobj_actual_handle_size)( slot_size ),
                        ::NS(LimitRect_cobj_type_id)(),
                        ::NS(LimitRect_cobj_num_dataptrs)(),
                        &OFFSETS[ 0 ], &SIZES[ 0 ], &COUNTS[ 0 ] ) );

                break;
            }

            case 7:
            {
                cxx_buffer_obj = cxx_buffer.add_copy< elem_type >( cmp_obj );
                break;
            }

            default:
            {
                c99_buffer_obj = nullptr;
            }
        };

        ASSERT_TRUE( cxx_buffer_obj != nullptr );
        ASSERT_TRUE( cxx_buffer_obj != cmp_obj );
        ASSERT_TRUE( cxx_buffer_obj != flat_buffer_obj );
        ASSERT_TRUE( cxx_buffer_obj != c99_buffer_obj );
        ASSERT_TRUE( 0 == ::NS(LimitRect_compare)( cmp_obj, cxx_buffer_obj ) );
        ASSERT_TRUE( 0 == ::NS(LimitRect_compare)(
                        flat_buffer_obj, cxx_buffer_obj ) );
        ASSERT_TRUE( 0 == ::NS(LimitRect_compare)(
                        c99_buffer_obj, cxx_buffer_obj ) );
    }

    ASSERT_TRUE( cxx_buffer.num_objects() == NUM_BELEMENTS );
    ASSERT_TRUE( ::NS(CBuffer_num_objects)( c99_buffer ) == NUM_BELEMENTS );
    ASSERT_TRUE( ::NS(CObjFlatBuffer_num_objects)( flat_buffer, slot_size ) ==
                  NUM_BELEMENTS );

    /* --------------------------------------------------------------------- */
    /* Add all elements from the compare data set to each buffer */

    for( size_type ii = 0u ; ii < NUM_BELEMENTS ; ++ii )
    {
        auto c99_buffer_obj = ::NS(LimitRect_const_from_cbuffer)( c99_buffer, ii );
        auto cxx_buffer_obj = cxx_buffer.get_object< elem_type >( ii );
        auto flat_buffer_obj = ::NS(LimitRect_const_from_cobj_flat_buffer)(
            flat_buffer, ii, slot_size );

        ASSERT_TRUE( flat_buffer_obj != nullptr );
        ASSERT_TRUE( c99_buffer_obj  != nullptr );
        ASSERT_TRUE( cxx_buffer_obj  != nullptr );
        ASSERT_TRUE( cxx_buffer_obj  != c99_buffer_obj );
        ASSERT_TRUE( cxx_buffer_obj  != flat_buffer_obj );
        ASSERT_TRUE( c99_buffer_obj  != flat_buffer_obj );

        ASSERT_TRUE( cxx_buffer_obj  == ::NS(LimitRect_const_from_cbuffer)(
            cxx_buffer.as_c_api(), ii ) );

        auto cmp_obj = &CMP_ELEMENTS[ ii ];

        ASSERT_TRUE( cmp_obj != flat_buffer_obj );
        ASSERT_TRUE( 0 == ::NS(LimitRect_compare)( cmp_obj, flat_buffer_obj ) );
        ASSERT_TRUE( 0 == ::NS(LimitRect_compare)( cmp_obj, c99_buffer_obj ) );
        ASSERT_TRUE( 0 == ::NS(LimitRect_compare)( cmp_obj, cxx_buffer_obj ) );
    }

    auto flat_buffer_obj = ::NS(LimitRect_const_from_cobj_flat_buffer)(
        flat_buffer, 0u, slot_size );

    real_type const saved_x_min = ::NS(LimitRect_x_min)( flat_buffer_obj );

    do
    {
        ASSERT_TRUE( ::NS(LimitRect_set_x_min)(
            ::NS(LimitRect_from_cobj_flat_buffer)( flat_buffer, 0, slot_size ),
                x_min_dist( prng ) ) == st::STATUS_SUCCESS );
    }
    while( 0 == ::NS(Type_value_comp_result)( saved_x_min,
           ::NS(LimitRect_x_min)( flat_buffer_obj ) ) );

    if( !::NS(LimitRect_is_consistent)( flat_buffer_obj ) )
    {
        ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(LimitRect_update)(
            NS(LimitRect_from_cobj_flat_buffer)( flat_buffer, 0, slot_size ) ) );
    }

    ASSERT_TRUE( ::NS(LimitRect_is_consistent)( flat_buffer_obj ) );

    ASSERT_TRUE( 0 != ::NS(LimitRect_compare)(
        &CMP_ELEMENTS[ 0 ], flat_buffer_obj ) );

    ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(LimitRect_copy)(
        ::NS(LimitRect_from_cobj_flat_buffer)( flat_buffer, 0u, slot_size ),
            &CMP_ELEMENTS[ 0 ] ) );

    ASSERT_TRUE( ::NS(LimitRect_is_consistent)( flat_buffer_obj ) );

    ASSERT_TRUE( 0 == ::NS(LimitRect_compare)(
        &CMP_ELEMENTS[ 0 ], flat_buffer_obj ) );

    /* --------------------------------------------------------------------- */
    /* cleanup */

    NS(CBuffer_delete)( c99_buffer );
}
