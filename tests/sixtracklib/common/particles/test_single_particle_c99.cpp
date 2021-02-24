#include <algorithm>
#include <cstdint>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

#include <gtest/gtest.h>

#include "sixtracklib/common/cobjects/definitions.h"
#include "sixtracklib/common/particles/definitions.h"
#include "sixtracklib/common/particles/particle.h"

#include "sixtracklib/common/cobjects/cobj_type_traits.h"
#include "sixtracklib/common/cobjects/cbuffer.h"
#include "sixtracklib/common/cobjects/cbuffer.hpp"

#include "sixtracklib/testlib.h"

TEST( C99CommonParticlesSingleParticle, CobjectsStoreAndRestore )
{
    #if !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) || \
                ( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER != 1 )

    namespace st = SIXTRL_CXX_NAMESPACE;

    using size_type      = ::NS(cobj_size_type);
    using particle_type  = ::NS(Particle);
    using raw_type       = ::NS(cobj_raw_type);
    using real_type      = ::NS(particle_real_type);
    using index_type     = ::NS(particle_index_type);

    static constexpr real_type ACTIVE_TRESHOLD = real_type{ 0.1 };
    static constexpr size_type NUM_BELEMENTS = size_type{ 1000 };

    ASSERT_TRUE( st::CObjects_has_legal_id< particle_type >() );
    ASSERT_TRUE( st::CObjects_num_pointers< particle_type >() ==
                 size_type{ 0 } );

    ASSERT_TRUE( st::CObjects_type_id< particle_type >() ==
                 st::COBJECTS_TYPE_ID_SINGLE_PARTICLE );

    #if defined( SIXTRL_PARTICLE_USE_PSIGMA_FIELD ) && \
               ( SIXTRL_PARTICLE_USE_PSIGMA_FIELD == 1 ) && \
        defined( SIXTRL_PARTICLE_USE_S_FIELD ) && \
               ( SIXTRL_PARTICLE_USE_S_FIELD == 1 )

    ASSERT_TRUE( st::CObjects_has_trivial_handle_size< particle_type >() );
    ASSERT_TRUE( st::CObjects_is_trivial_type< particle_type >() );

    #else /* SIXTRL_PARTICLE_USE_PSIGMA_FIELD && SIXTRL_PARTICLE_USE_S_FIELD */

    ASSERT_FALSE( st::CObjects_has_trivial_handle_size< particle_type >() );
    ASSERT_FALSE( st::CObjects_is_trivial_type< particle_type >() );

    #endif /* SIXTRL_PARTICLE_USE_PSIGMA_FIELD && SIXTRL_PARTICLE_USE_S_FIELD */



    ASSERT_TRUE( ::NS(Particle_cobj_num_dataptrs)() == size_type{ 0 } );
    ASSERT_TRUE( ::NS(Particle_cobj_type_id)() ==
                 ::NS(COBJECTS_TYPE_ID_SINGLE_PARTICLE) );

    /* --------------------------------------------------------------------- */
    /* prepare comparison data */

    std::mt19937_64 prng( std::mt19937_64::result_type{ 20210212 } );

    std::uniform_real_distribution< real_type > x_dist(
        real_type{ -1e-5 }, real_type{ 1e-5 } );

    std::uniform_real_distribution< real_type > y_dist(
        real_type{ -1e-5 }, real_type{ 1e-5 } );

    std::uniform_real_distribution< real_type > px_dist(
        real_type{ -1e-6 }, real_type{ 1e-6 } );

    std::uniform_real_distribution< real_type > py_dist(
        real_type{ -1e-6 }, real_type{ 1e-6 } );

    std::uniform_real_distribution< real_type > zeta_dist(
        real_type{ -1e-2 }, real_type{ 1e-2 } );

    std::uniform_real_distribution< real_type > delta_dist(
        real_type{ -1e-6 }, real_type{ 1e-6 } );

    std::uniform_int_distribution< index_type > id_dist(
        index_type{ SIXTRL_PARTICLE_MIN_LEGAL_ID },
        index_type{ SIXTRL_PARTICLE_MAX_LEGAL_ID } );

    std::uniform_int_distribution< index_type > at_elem_dist(
        index_type{ SIXTRL_PARTICLE_MIN_LEGAL_AT_ELEMENT },
        index_type{ SIXTRL_PARTICLE_MAX_LEGAL_AT_ELEMENT } );

    std::uniform_int_distribution< index_type > at_turn_dist(
        index_type{ SIXTRL_PARTICLE_MIN_LEGAL_AT_TURN },
        index_type{ SIXTRL_PARTICLE_MAX_LEGAL_AT_TURN } );

    std::uniform_real_distribution< real_type > state_dist(
        real_type{ 0.0 }, real_type{ 1.0 } );

    std::uniform_int_distribution< size_type > num_mass0_dist(
        size_type{ 1 }, size_type{ 238 } );

    std::uniform_int_distribution< index_type > num_charge0_dist(
        index_type{ -20 }, index_type{ 20 } );

    std::uniform_real_distribution< real_type > charge_ratio_dist(
        real_type{ -1.0 }, real_type{ 1.0 } );

    std::uniform_real_distribution< real_type > mass_ratio_dist(
        real_type{ 0.8 }, real_type{ 1.0 } );

    std::uniform_real_distribution< real_type > s_dist(
        real_type{ 0.0 }, real_type{ 10000.0 } );

    std::uniform_real_distribution< real_type > beta0_dist(
        real_type{ 1e-3 }, real_type{ 1.0 } );

    std::uniform_real_distribution< real_type > gamma0_dist(
        real_type{ 1.0 }, real_type{ 1.0e5 } );

    std::uniform_real_distribution< real_type > p0c_dist(
        real_type{ 0.1 }, real_type{ 7.0e12 } );

    /* gather information to prepare a cobj flat buffer */

    size_type const slot_size = st::CBUFFER_DEFAULT_SLOT_SIZE;
    size_type n_slots = size_type{ 0 };
    size_type const n_objs = NUM_BELEMENTS;
    size_type const n_ptrs = ::NS(Particle_cobj_num_dataptrs)() * NUM_BELEMENTS;

    std::vector< ::NS(SingleParticle) > CMP_ELEMENTS(
        NUM_BELEMENTS, ::NS(SingleParticle){} );

    for( size_type ii = 0u ; ii < NUM_BELEMENTS ; ++ii )
    {
        auto& p = CMP_ELEMENTS[ ii ];

        real_type third_param_value = real_type{ 0. };
        ::NS(ParticleInitModeEnum) init_mode = ::NS(PARTICLE_INIT_MODE_DEFAULT);

        if( ( ii % size_type{ 3 } ) == size_type{ 0 } )
        {
            init_mode = ::NS(PARTICLE_INIT_MODE_CHARGE0_MASS0_BETA0);
            third_param_value = beta0_dist( prng );
        }
        else if( ( ii % size_type{ 3 } ) == size_type{ 1 } )
        {
            init_mode = ::NS(PARTICLE_INIT_MODE_CHARGE0_MASS0_GAMMA0);
            third_param_value = gamma0_dist( prng );
        }
        else
        {
            init_mode = ::NS(PARTICLE_INIT_MODE_CHARGE0_MASS0_P0C);
            third_param_value = p0c_dist( prng );
        }

        auto const ret = st::testlib::Particle_init_random( &p, prng, x_dist,
            y_dist, px_dist, py_dist, zeta_dist, delta_dist, state_dist,
                ACTIVE_TRESHOLD, at_elem_dist, at_turn_dist, id_dist,
                    charge_ratio_dist, mass_ratio_dist, num_charge0_dist,
                        num_mass0_dist, s_dist, third_param_value, init_mode );

        ASSERT_TRUE( st::STATUS_SUCCESS == ret );

        n_slots += ::NS(Particle_cobj_required_num_bytes)( &p, slot_size )
                 / slot_size;
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
        SIXTRL_PARTICLE_ARGPTR_DEC particle_type* flat_buffer_obj = nullptr;
        SIXTRL_PARTICLE_ARGPTR_DEC particle_type* c99_buffer_obj  = nullptr;
        SIXTRL_PARTICLE_ARGPTR_DEC particle_type* cxx_buffer_obj  = nullptr;

        SIXTRL_PARTICLE_ARGPTR_DEC particle_type const* cmp_obj = &CMP_ELEMENTS[ ii ];

        size_type constexpr TEMP_NN = size_type{ 25 };
        SIXTRL_ASSERT( ::NS(Particle_cobj_num_dataptrs)() < TEMP_NN );

        SIXTRL_ARGPTR_DEC size_type OFFSETS[ TEMP_NN ];
        SIXTRL_ARGPTR_DEC size_type SIZES[ TEMP_NN ];
        SIXTRL_ARGPTR_DEC size_type COUNTS[ TEMP_NN ];

        ASSERT_TRUE( st::STATUS_SUCCESS == st::CObjects_attribute_offsets<
            particle_type >( &OFFSETS[ 0 ], TEMP_NN, cmp_obj, slot_size ) );

        ASSERT_TRUE( st::STATUS_SUCCESS == st::CObjects_attribute_sizes<
            particle_type >( &SIZES[ 0 ], TEMP_NN, cmp_obj, slot_size ) );

        ASSERT_TRUE( st::STATUS_SUCCESS == st::CObjects_attribute_counts<
            particle_type >( &COUNTS[ 0 ], TEMP_NN, cmp_obj, slot_size ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* Flat Buffer: */

        size_type const flat_buffer_mode = ii % size_type{ 7 };

        switch( flat_buffer_mode )
        {
            case 0:
            {
                SIXTRL_PARTICLE_ARGPTR_DEC ::NS(Particle)* obj =
                    ::NS(Particle_cobj_flat_buffer_new)( flat_buffer, slot_size );

                ASSERT_TRUE( obj != nullptr );

                ::NS(Particle_set_x)( obj,  ::NS(Particle_x)(  cmp_obj ) );
                ::NS(Particle_set_y)( obj,  ::NS(Particle_y)(  cmp_obj ) );
                ::NS(Particle_set_px)( obj, ::NS(Particle_px)( cmp_obj ) );
                ::NS(Particle_set_py)( obj, ::NS(Particle_py)( cmp_obj ) );

                ::NS(Particle_set_zeta)( obj, ::NS(Particle_zeta)( cmp_obj ) );
                ::NS(Particle_set_delta)( obj, ::NS(Particle_delta)( cmp_obj ) );
                ::NS(Particle_set_state)( obj, ::NS(Particle_state)( cmp_obj ) );

                ::NS(Particle_set_at_element)( obj,
                    ::NS(Particle_at_element)( cmp_obj ) );

                ::NS(Particle_set_at_turn)( obj,
                    ::NS(Particle_at_turn)( cmp_obj ) );

                ::NS(Particle_set_id)( obj, ::NS(Particle_id)( cmp_obj ) );
                ::NS(Particle_set_psigma)( obj,
                    ::NS(Particle_psigma)( cmp_obj ) );

                ::NS(Particle_set_rpp)( obj, ::NS(Particle_rpp)( cmp_obj ) );
                ::NS(Particle_set_rvv)( obj, ::NS(Particle_rvv)( cmp_obj ) );
                ::NS(Particle_set_chi)( obj, ::NS(Particle_chi)( cmp_obj ) );
                ::NS(Particle_set_charge_ratio)( obj,
                    ::NS(Particle_charge_ratio)( cmp_obj ) );

                ::NS(Particle_set_charge0)( obj,
                    ::NS(Particle_charge0)( cmp_obj ) );

                ::NS(Particle_set_mass0)( obj, ::NS(Particle_mass0)( cmp_obj ) );
                ::NS(Particle_set_beta0)( obj, ::NS(Particle_beta0)( cmp_obj ) );
                ::NS(Particle_set_gamma0)( obj,
                    ::NS(Particle_gamma0)( cmp_obj ) );

                ::NS(Particle_set_p0c)( obj, ::NS(Particle_p0c)( cmp_obj ) );
                ::NS(Particle_set_s)( obj, ::NS(Particle_s)( cmp_obj ) );

                flat_buffer_obj = obj;
                break;
            }

            case 1:
            {
                flat_buffer_obj = ::NS(Particle_cobj_flat_buffer_new)(
                    flat_buffer, slot_size );

                ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(Particle_copy)(
                    flat_buffer_obj, cmp_obj ) );

                break;
            }

            case 2:
            {
                flat_buffer_obj = ::NS(Particle_cobj_flat_buffer_add)(
                    flat_buffer, slot_size,
                    ::NS(Particle_x)( cmp_obj ),
                    ::NS(Particle_y)( cmp_obj ),
                    ::NS(Particle_px)( cmp_obj ),
                    ::NS(Particle_py)( cmp_obj ),
                    ::NS(Particle_zeta)( cmp_obj ),
                    ::NS(Particle_delta)( cmp_obj ),
                    ::NS(Particle_state)( cmp_obj ),
                    ::NS(Particle_at_element)( cmp_obj ),
                    ::NS(Particle_at_turn)( cmp_obj ),
                    ::NS(Particle_id)( cmp_obj ),
                    ::NS(Particle_psigma)( cmp_obj ),
                    ::NS(Particle_rpp)( cmp_obj ),
                    ::NS(Particle_rvv)( cmp_obj ),
                    ::NS(Particle_chi)( cmp_obj ),
                    ::NS(Particle_charge_ratio)( cmp_obj ),
                    ::NS(Particle_charge0)( cmp_obj ),
                    ::NS(Particle_mass0)( cmp_obj ),
                    ::NS(Particle_beta0)( cmp_obj ),
                    ::NS(Particle_gamma0)( cmp_obj ),
                    ::NS(Particle_p0c)( cmp_obj ),
                    ::NS(Particle_s)( cmp_obj ) );

                break;
            }

            case 3:
            {
                flat_buffer_obj = ::NS(Particle_cobj_flat_buffer_add_copy)(
                    flat_buffer, slot_size, cmp_obj );

                break;
            }

            case 4:
            {
                flat_buffer_obj = ::NS(Particle_from_cobj_index)(
                    ::NS(CObjFlatBuffer_add_copy_of_trivial_object)(
                        flat_buffer, slot_size, cmp_obj,
                        ::NS(Particle_cobj_reserved_handle_size)( slot_size ),
                        ::NS(Particle_cobj_type_id)(), true ) );

                break;
            }

            case 5:
            {
                flat_buffer_obj = ::NS(Particle_from_cobj_index)(
                    ::NS(CObjFlatBuffer_add_copy_of_object)(
                        flat_buffer, slot_size, cmp_obj,
                        ::NS(Particle_cobj_reserved_handle_size)( slot_size ),
                        ::NS(Particle_cobj_type_id)(),
                        ::NS(Particle_cobj_num_dataptrs)(),
                        &OFFSETS[ 0 ], &SIZES[ 0 ], &COUNTS[ 0 ], true ) );

                break;
            }

            case 6:
            {
                flat_buffer_obj = ::NS(Particle_from_cobj_index)(
                    ::NS(CObjFlatBuffer_add_copy_of_object_detailed)(
                        flat_buffer, slot_size, cmp_obj,
                        ::NS(Particle_cobj_reserved_handle_size)( slot_size ),
                        ::NS(Particle_cobj_actual_handle_size)( slot_size ),
                        ::NS(Particle_cobj_type_id)(),
                        ::NS(Particle_cobj_num_dataptrs)(),
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
        ASSERT_TRUE( 0 == ::NS(Particle_compare)( cmp_obj, flat_buffer_obj ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* c99_buffer: */

        size_type const c99_buffer_mode = ii % size_type{ 7 };

        switch( c99_buffer_mode )
        {
            case 0:
            {
                SIXTRL_PARTICLE_ARGPTR_DEC ::NS(Particle)* obj =
                    ::NS(Particle_cbuffer_new)( c99_buffer );

                ASSERT_TRUE( obj != nullptr );

                ::NS(Particle_set_x)( obj,  ::NS(Particle_x)(  cmp_obj ) );
                ::NS(Particle_set_y)( obj,  ::NS(Particle_y)(  cmp_obj ) );
                ::NS(Particle_set_px)( obj, ::NS(Particle_px)( cmp_obj ) );
                ::NS(Particle_set_py)( obj, ::NS(Particle_py)( cmp_obj ) );

                ::NS(Particle_set_zeta)( obj, ::NS(Particle_zeta)( cmp_obj ) );
                ::NS(Particle_set_delta)( obj, ::NS(Particle_delta)( cmp_obj ) );
                ::NS(Particle_set_state)( obj, ::NS(Particle_state)( cmp_obj ) );

                ::NS(Particle_set_at_element)( obj,
                    ::NS(Particle_at_element)( cmp_obj ) );

                ::NS(Particle_set_at_turn)( obj,
                    ::NS(Particle_at_turn)( cmp_obj ) );

                ::NS(Particle_set_id)( obj, ::NS(Particle_id)( cmp_obj ) );
                ::NS(Particle_set_psigma)( obj,
                    ::NS(Particle_psigma)( cmp_obj ) );

                ::NS(Particle_set_rpp)( obj, ::NS(Particle_rpp)( cmp_obj ) );
                ::NS(Particle_set_rvv)( obj, ::NS(Particle_rvv)( cmp_obj ) );
                ::NS(Particle_set_chi)( obj, ::NS(Particle_chi)( cmp_obj ) );
                ::NS(Particle_set_charge_ratio)( obj,
                    ::NS(Particle_charge_ratio)( cmp_obj ) );

                ::NS(Particle_set_charge0)( obj,
                    ::NS(Particle_charge0)( cmp_obj ) );

                ::NS(Particle_set_mass0)( obj, ::NS(Particle_mass0)( cmp_obj ) );
                ::NS(Particle_set_beta0)( obj, ::NS(Particle_beta0)( cmp_obj ) );
                ::NS(Particle_set_gamma0)( obj,
                    ::NS(Particle_gamma0)( cmp_obj ) );

                ::NS(Particle_set_p0c)( obj, ::NS(Particle_p0c)( cmp_obj ) );
                ::NS(Particle_set_s)( obj, ::NS(Particle_s)( cmp_obj ) );

                c99_buffer_obj = obj;

                break;
            }

            case 1:
            {
                c99_buffer_obj = ::NS(Particle_cbuffer_new)( c99_buffer );
                ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(Particle_copy)(
                    c99_buffer_obj, cmp_obj ) );
                break;
            }

            case 2:
            {
                c99_buffer_obj = ::NS(Particle_cbuffer_add)( c99_buffer,
                    ::NS(Particle_x)( cmp_obj ),
                    ::NS(Particle_y)( cmp_obj ),
                    ::NS(Particle_px)( cmp_obj ),
                    ::NS(Particle_py)( cmp_obj ),
                    ::NS(Particle_zeta)( cmp_obj ),
                    ::NS(Particle_delta)( cmp_obj ),
                    ::NS(Particle_state)( cmp_obj ),
                    ::NS(Particle_at_element)( cmp_obj ),
                    ::NS(Particle_at_turn)( cmp_obj ),
                    ::NS(Particle_id)( cmp_obj ),
                    ::NS(Particle_psigma)( cmp_obj ),
                    ::NS(Particle_rpp)( cmp_obj ),
                    ::NS(Particle_rvv)( cmp_obj ),
                    ::NS(Particle_chi)( cmp_obj ),
                    ::NS(Particle_charge_ratio)( cmp_obj ),
                    ::NS(Particle_charge0)( cmp_obj ),
                    ::NS(Particle_mass0)( cmp_obj ),
                    ::NS(Particle_beta0)( cmp_obj ),
                    ::NS(Particle_gamma0)( cmp_obj ),
                    ::NS(Particle_p0c)( cmp_obj ),
                    ::NS(Particle_s)( cmp_obj ) );
                break;
            }

            case 3:
            {
                c99_buffer_obj = ::NS(Particle_cbuffer_add_copy)(
                    c99_buffer, cmp_obj );
                break;
            }

            case 4:
            {
                c99_buffer_obj = ::NS(Particle_from_cobj_index)(
                    ::NS(CBuffer_add_copy_of_trivial_object)(
                        c99_buffer, cmp_obj,
                        ::NS(Particle_cobj_reserved_handle_size)( slot_size ),
                        ::NS(Particle_cobj_type_id)(), true ) );

                break;
            }

            case 5:
            {
                c99_buffer_obj = ::NS(Particle_from_cobj_index)(
                    ::NS(CBuffer_add_copy_of_object)(
                        c99_buffer, cmp_obj,
                        ::NS(Particle_cobj_reserved_handle_size)( slot_size ),
                        ::NS(Particle_cobj_type_id)(),
                        ::NS(Particle_cobj_num_dataptrs)(),
                        &OFFSETS[ 0 ], &SIZES[ 0 ], &COUNTS[ 0 ], true ) );

                break;
            }

            case 6:
            {
                c99_buffer_obj = ::NS(Particle_from_cobj_index)(
                    ::NS(CBuffer_add_copy_of_object_detailed)(
                        c99_buffer, cmp_obj,
                        ::NS(Particle_cobj_reserved_handle_size)( slot_size ),
                        ::NS(Particle_cobj_actual_handle_size)( slot_size ),
                        ::NS(Particle_cobj_type_id)(),
                        ::NS(Particle_cobj_num_dataptrs)(),
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
        ASSERT_TRUE( 0 == ::NS(Particle_compare)( cmp_obj, c99_buffer_obj ) );
        ASSERT_TRUE( 0 == ::NS(Particle_compare)(
                        flat_buffer_obj, c99_buffer_obj ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* cxx_buffer: */

        size_type cxx_buffer_mode = ii % size_type{ 8 };

        switch( cxx_buffer_mode )
        {
            case 0:
            {
                SIXTRL_PARTICLE_ARGPTR_DEC ::NS(Particle)* obj =
                    ::NS(Particle_cbuffer_new)( cxx_buffer.as_c_api() );

                ASSERT_TRUE( obj != nullptr );

                ::NS(Particle_set_x)( obj,  ::NS(Particle_x)(  cmp_obj ) );
                ::NS(Particle_set_y)( obj,  ::NS(Particle_y)(  cmp_obj ) );
                ::NS(Particle_set_px)( obj, ::NS(Particle_px)( cmp_obj ) );
                ::NS(Particle_set_py)( obj, ::NS(Particle_py)( cmp_obj ) );

                ::NS(Particle_set_zeta)( obj, ::NS(Particle_zeta)( cmp_obj ) );
                ::NS(Particle_set_delta)( obj, ::NS(Particle_delta)( cmp_obj ) );
                ::NS(Particle_set_state)( obj, ::NS(Particle_state)( cmp_obj ) );

                ::NS(Particle_set_at_element)( obj,
                    ::NS(Particle_at_element)( cmp_obj ) );

                ::NS(Particle_set_at_turn)( obj,
                    ::NS(Particle_at_turn)( cmp_obj ) );

                ::NS(Particle_set_id)( obj, ::NS(Particle_id)( cmp_obj ) );
                ::NS(Particle_set_psigma)( obj,
                    ::NS(Particle_psigma)( cmp_obj ) );

                ::NS(Particle_set_rpp)( obj, ::NS(Particle_rpp)( cmp_obj ) );
                ::NS(Particle_set_rvv)( obj, ::NS(Particle_rvv)( cmp_obj ) );
                ::NS(Particle_set_chi)( obj, ::NS(Particle_chi)( cmp_obj ) );
                ::NS(Particle_set_charge_ratio)( obj,
                    ::NS(Particle_charge_ratio)( cmp_obj ) );

                ::NS(Particle_set_charge0)( obj,
                    ::NS(Particle_charge0)( cmp_obj ) );

                ::NS(Particle_set_mass0)( obj, ::NS(Particle_mass0)( cmp_obj ) );
                ::NS(Particle_set_beta0)( obj, ::NS(Particle_beta0)( cmp_obj ) );
                ::NS(Particle_set_gamma0)( obj,
                    ::NS(Particle_gamma0)( cmp_obj ) );

                ::NS(Particle_set_p0c)( obj, ::NS(Particle_p0c)( cmp_obj ) );
                ::NS(Particle_set_s)( obj, ::NS(Particle_s)( cmp_obj ) );

                cxx_buffer_obj = obj;

                break;
            }

            case 1:
            {
                cxx_buffer_obj = ::NS(Particle_cbuffer_new)( cxx_buffer.as_c_api() );
                ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(Particle_copy)(
                    cxx_buffer_obj, cmp_obj ) );
                break;
            }

            case 2:
            {
                cxx_buffer_obj = ::NS(Particle_cbuffer_add)(
                    cxx_buffer.as_c_api(),
                    ::NS(Particle_x)( cmp_obj ),
                    ::NS(Particle_y)( cmp_obj ),
                    ::NS(Particle_px)( cmp_obj ),
                    ::NS(Particle_py)( cmp_obj ),
                    ::NS(Particle_zeta)( cmp_obj ),
                    ::NS(Particle_delta)( cmp_obj ),
                    ::NS(Particle_state)( cmp_obj ),
                    ::NS(Particle_at_element)( cmp_obj ),
                    ::NS(Particle_at_turn)( cmp_obj ),
                    ::NS(Particle_id)( cmp_obj ),
                    ::NS(Particle_psigma)( cmp_obj ),
                    ::NS(Particle_rpp)( cmp_obj ),
                    ::NS(Particle_rvv)( cmp_obj ),
                    ::NS(Particle_chi)( cmp_obj ),
                    ::NS(Particle_charge_ratio)( cmp_obj ),
                    ::NS(Particle_charge0)( cmp_obj ),
                    ::NS(Particle_mass0)( cmp_obj ),
                    ::NS(Particle_beta0)( cmp_obj ),
                    ::NS(Particle_gamma0)( cmp_obj ),
                    ::NS(Particle_p0c)( cmp_obj ),
                    ::NS(Particle_s)( cmp_obj ) );
                break;
            }

            case 3:
            {
                cxx_buffer_obj = ::NS(Particle_cbuffer_add_copy)(
                    cxx_buffer.as_c_api(), cmp_obj );
                break;
            }

            case 4:
            {
                cxx_buffer_obj = ::NS(Particle_from_cobj_index)(
                    cxx_buffer.add_copy_of_trivial_object( cmp_obj,
                        ::NS(Particle_cobj_reserved_handle_size)( slot_size ),
                        ::NS(Particle_cobj_type_id)() ) );

                break;
            }

            case 5:
            {
                cxx_buffer_obj = ::NS(Particle_from_cobj_index)(
                    cxx_buffer.add_copy_of_object( cmp_obj,
                        ::NS(Particle_cobj_reserved_handle_size)( slot_size ),
                        ::NS(Particle_cobj_type_id)(),
                        ::NS(Particle_cobj_num_dataptrs)(),
                        &OFFSETS[ 0 ], &SIZES[ 0 ], &COUNTS[ 0 ] ) );

                break;
            }

            case 6:
            {
                cxx_buffer_obj = ::NS(Particle_from_cobj_index)(
                    cxx_buffer.add_copy_of_object_detailed( cmp_obj,
                        ::NS(Particle_cobj_reserved_handle_size)( slot_size ),
                        ::NS(Particle_cobj_actual_handle_size)( slot_size ),
                        ::NS(Particle_cobj_type_id)(),
                        ::NS(Particle_cobj_num_dataptrs)(),
                        &OFFSETS[ 0 ], &SIZES[ 0 ], &COUNTS[ 0 ] ) );

                break;
            }

            case 7:
            {
                cxx_buffer_obj = cxx_buffer.add_copy< particle_type >( cmp_obj );
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
        ASSERT_TRUE( 0 == ::NS(Particle_compare)( cmp_obj, cxx_buffer_obj ) );
        ASSERT_TRUE( 0 == ::NS(Particle_compare)(
                        flat_buffer_obj, cxx_buffer_obj ) );
        ASSERT_TRUE( 0 == ::NS(Particle_compare)(
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
        auto c99_buffer_obj = ::NS(Particle_const_from_cbuffer)( c99_buffer, ii );
        auto cxx_buffer_obj = cxx_buffer.get_object< particle_type >( ii );
        auto flat_buffer_obj = ::NS(Particle_const_from_cobj_flat_buffer)(
            flat_buffer, ii, slot_size );

        ASSERT_TRUE( flat_buffer_obj != nullptr );
        ASSERT_TRUE( c99_buffer_obj  != nullptr );
        ASSERT_TRUE( cxx_buffer_obj  != nullptr );
        ASSERT_TRUE( cxx_buffer_obj  != c99_buffer_obj );
        ASSERT_TRUE( cxx_buffer_obj  != flat_buffer_obj );
        ASSERT_TRUE( c99_buffer_obj  != flat_buffer_obj );

        ASSERT_TRUE( cxx_buffer_obj  == ::NS(Particle_const_from_cbuffer)(
            cxx_buffer.as_c_api(), ii ) );

        auto cmp_obj = &CMP_ELEMENTS[ ii ];

        ASSERT_TRUE( cmp_obj != flat_buffer_obj );
        ASSERT_TRUE( 0 == ::NS(Particle_compare)( cmp_obj, flat_buffer_obj ) );
        ASSERT_TRUE( 0 == ::NS(Particle_compare)( cmp_obj, c99_buffer_obj ) );
        ASSERT_TRUE( 0 == ::NS(Particle_compare)( cmp_obj, cxx_buffer_obj ) );
    }

    auto flat_buffer_obj = ::NS(Particle_const_from_cobj_flat_buffer)(
        flat_buffer, 0u, slot_size );

    real_type const saved_x = ::NS(Particle_x)( flat_buffer_obj );

    do
    {
        ::NS(Particle_set_x)( ::NS(Particle_from_cobj_flat_buffer)(
            flat_buffer, 0, slot_size ), x_dist( prng ) );
    }
    while( 0 == ::NS(Type_value_comp_result)( saved_x,
           ::NS(Particle_x)( flat_buffer_obj ) ) );

    ASSERT_TRUE( 0 != ::NS(Particle_compare)(
        &CMP_ELEMENTS[ 0 ], flat_buffer_obj ) );

    ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(Particle_copy)(
        ::NS(Particle_from_cobj_flat_buffer)( flat_buffer, 0u, slot_size ),
            &CMP_ELEMENTS[ 0 ] ) );

    ASSERT_TRUE( 0 == ::NS(Particle_compare)(
        &CMP_ELEMENTS[ 0 ], flat_buffer_obj ) );

    /* --------------------------------------------------------------------- */
    /* cleanup */

    NS(CBuffer_delete)( c99_buffer );

    #else /* defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */

    std::cout << "Skipping this test for the "
              << "NS(SingleParticleView) implementation" << std::endl;

    return;

    #endif /* !defined( SIXTRL_USE_SINGLE_PARTICLE_ADAPTER ) */
}
