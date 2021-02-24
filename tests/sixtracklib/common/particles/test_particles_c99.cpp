#include <algorithm>
#include <cstdint>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

#include <gtest/gtest.h>

#include "sixtracklib/common/cobjects/definitions.h"
#include "sixtracklib/common/particles/definitions.h"
#include "sixtracklib/common/particles/particles.h"
#include "sixtracklib/common/particles/particle.h"

#include "sixtracklib/common/cobjects/cobj_type_traits.h"
#include "sixtracklib/common/cobjects/cbuffer.h"
#include "sixtracklib/common/cobjects/cbuffer.hpp"

#include "sixtracklib/testlib.h"

TEST( C99CommonParticlesParticles, CObjectsStoreAndRestoreMinimal )
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    using particle_set_t  = ::NS(Particles);
    using npart_type      = ::NS(particles_num_type);
    using real_type       = ::NS(particle_real_type);
    using index_type      = ::NS(particle_index_type);
    using size_type       = ::NS(size_type);
    using raw_type        = ::NS(cobj_raw_type);

    ASSERT_TRUE( st::CObjects_has_legal_id< particle_set_t >() );
    ASSERT_TRUE( st::CObjects_num_pointers< particle_set_t >() ==
                 size_type{ 21 } );

    ASSERT_TRUE( st::CObjects_type_id< particle_set_t >() ==
                 st::COBJECTS_TYPE_ID_PARTICLES_COLLECTION );

    ASSERT_TRUE(  st::CObjects_has_trivial_handle_size< particle_set_t >() );
    ASSERT_FALSE( st::CObjects_is_trivial_type< particle_set_t >() );

    /* --------------------------------------------------------------------- */

    static constexpr npart_type NUM_PARTICLE_SETS = npart_type{ 30 };
    static constexpr npart_type MIN_NUM_PARTICLES = npart_type{ 10 };
    static constexpr npart_type MAX_NUM_PARTICLES = npart_type{ 100 };

    static constexpr size_type slot_size = st::CBuffer::DEFAULT_SLOT_SIZE;

    std::mt19937_64 prng( std::mt19937_64::result_type{ 20210212 } );

    std::uniform_real_distribution< real_type > real_dist(
        real_type{ 0.0 }, real_type{ 1.0 } );

    std::uniform_int_distribution< index_type > index_dist(
        index_type{ 0 }, index_type{ 2 } );

    std::uniform_int_distribution< npart_type > num_particles_dist(
        MIN_NUM_PARTICLES, MAX_NUM_PARTICLES );

    std::vector< real_type > real_values(
        17 * NUM_PARTICLE_SETS * MAX_NUM_PARTICLES, real_type{ 0.0 } );

    for( auto& v : real_values ) v = real_dist( prng );

    std::vector< index_type > index_values(
        4 * NUM_PARTICLE_SETS * MAX_NUM_PARTICLES, index_type{ 0 } );

    for( auto& v : index_values ) v = index_dist( prng );

    npart_type real_offsets = npart_type{ 0 };
    npart_type index_offsets = npart_type{ 0 };

    size_type const n_objs = NUM_PARTICLE_SETS;
    size_type const n_ptrs = NUM_PARTICLE_SETS * size_type{ 21 };
    size_type n_slots = size_type{ 0 };

    std::vector< particle_set_t > CMP_PARTICLES(
        NUM_PARTICLE_SETS, particle_set_t{} );

    for( auto& pset : CMP_PARTICLES )
    {
        npart_type const max_num_particles = num_particles_dist( prng );
        npart_type num_particles = num_particles_dist( prng );

        if( num_particles > max_num_particles )
            num_particles = max_num_particles;

        ASSERT_TRUE( ::NS(Particles_clear)( &pset ) == st::STATUS_SUCCESS );

        ::NS(Particles_init_with_pointers)(
            &pset, max_num_particles, num_particles,
            &real_values[  real_offsets  +  0 * max_num_particles ],
            &real_values[  real_offsets  +  1 * max_num_particles ],
            &real_values[  real_offsets  +  2 * max_num_particles ],
            &real_values[  real_offsets  +  3 * max_num_particles ],
            &real_values[  real_offsets  +  4 * max_num_particles ],
            &real_values[  real_offsets  +  5 * max_num_particles ],
            &real_values[  real_offsets  +  6 * max_num_particles ],
            &real_values[  real_offsets  +  7 * max_num_particles ],
            &real_values[  real_offsets  +  8 * max_num_particles ],
            &real_values[  real_offsets  +  9 * max_num_particles ],
            &real_values[  real_offsets  + 10 * max_num_particles ],
            &real_values[  real_offsets  + 11 * max_num_particles ],
            &real_values[  real_offsets  + 12 * max_num_particles ],
            &real_values[  real_offsets  + 13 * max_num_particles ],
            &real_values[  real_offsets  + 14 * max_num_particles ],
            &real_values[  real_offsets  + 15 * max_num_particles ],
            &real_values[  real_offsets  + 16 * max_num_particles ],
            &index_values[ index_offsets +  0 * max_num_particles ],
            &index_values[ index_offsets +  1 * max_num_particles ],
            &index_values[ index_offsets +  2 * max_num_particles ],
            &index_values[ index_offsets +  3 * max_num_particles ] );

        real_offsets  += npart_type{ 17 } * max_num_particles;
        index_offsets += npart_type{  4 } * max_num_particles;

         n_slots += ::NS(Particles_cobj_required_num_bytes)(
            &pset, slot_size ) / slot_size;
    }

    /* --------------------------------------------------------------------- */
    /* prepare a flat buffer, a ::NS(Cbuffer) and a c++ CBufffer */

    ASSERT_TRUE( n_ptrs  == NUM_PARTICLE_SETS * size_type{ 21 } );
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

    for( npart_type ii = 0 ; ii < NUM_PARTICLE_SETS ; ++ii )
    {
        SIXTRL_PARTICLES_ARGPTR_DEC particle_set_t* flat_buffer_obj = nullptr;
        SIXTRL_PARTICLES_ARGPTR_DEC particle_set_t* c99_buffer_obj  = nullptr;
        SIXTRL_PARTICLES_ARGPTR_DEC particle_set_t* cxx_buffer_obj  = nullptr;

        SIXTRL_PARTICLES_ARGPTR_DEC particle_set_t const* cmp_obj =
            &CMP_PARTICLES[ ii ];

        size_type constexpr TEMP_NN = st::CObjects_num_pointers<
            particle_set_t >();

        SIXTRL_ASSERT( ::NS(Particles_cobj_num_dataptrs)() == TEMP_NN );

        SIXTRL_ARGPTR_DEC size_type OFFSETS[ TEMP_NN ];
        SIXTRL_ARGPTR_DEC size_type SIZES[ TEMP_NN ];
        SIXTRL_ARGPTR_DEC size_type COUNTS[ TEMP_NN ];

        ASSERT_TRUE( st::STATUS_SUCCESS == st::CObjects_attribute_offsets<
            particle_set_t >( &OFFSETS[ 0 ], TEMP_NN, cmp_obj, slot_size ) );

        ASSERT_TRUE( st::STATUS_SUCCESS == st::CObjects_attribute_sizes<
            particle_set_t >( &SIZES[ 0 ], TEMP_NN, cmp_obj, slot_size ) );

        ASSERT_TRUE( st::STATUS_SUCCESS == st::CObjects_attribute_counts<
            particle_set_t >( &COUNTS[ 0 ], TEMP_NN, cmp_obj, slot_size ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* Flat Buffer: */

        size_type const flat_buffer_mode = ii % size_type{ 6 };

        switch( flat_buffer_mode )
        {
            case 0:
            {
                flat_buffer_obj = ::NS(Particles_cobj_flat_buffer_new)(
                    flat_buffer, slot_size, ::NS(Particles_max_num_particles)(
                        cmp_obj ) );

                ASSERT_TRUE( flat_buffer_obj != nullptr );

                ::NS(Particles_set_num_particles)( flat_buffer_obj,
                    ::NS(Particles_num_particles)( cmp_obj ) );

                std::copy( ::NS(Particles_charge0_const_begin)( cmp_obj ),
                           ::NS(Particles_charge0_const_end)( cmp_obj ),
                           ::NS(Particles_charge0_begin)( flat_buffer_obj ) );

                std::copy( ::NS(Particles_mass0_const_begin)( cmp_obj ),
                           ::NS(Particles_mass0_const_end)( cmp_obj ),
                           ::NS(Particles_mass0_begin)( flat_buffer_obj ) );

                std::copy( ::NS(Particles_beta0_const_begin)( cmp_obj ),
                           ::NS(Particles_beta0_const_end)( cmp_obj ),
                           ::NS(Particles_beta0_begin)( flat_buffer_obj ) );

                std::copy( ::NS(Particles_gamma0_const_begin)( cmp_obj ),
                           ::NS(Particles_gamma0_const_end)( cmp_obj ),
                           ::NS(Particles_gamma0_begin)( flat_buffer_obj ) );

                std::copy( ::NS(Particles_p0c_const_begin)( cmp_obj ),
                           ::NS(Particles_p0c_const_end)( cmp_obj ),
                           ::NS(Particles_p0c_begin)( flat_buffer_obj ) );

                std::copy( ::NS(Particles_s_const_begin)( cmp_obj ),
                           ::NS(Particles_s_const_end)( cmp_obj ),
                           ::NS(Particles_s_begin)( flat_buffer_obj ) );

                std::copy( ::NS(Particles_x_const_begin)( cmp_obj ),
                           ::NS(Particles_x_const_end)( cmp_obj ),
                           ::NS(Particles_x_begin)( flat_buffer_obj ) );

                std::copy( ::NS(Particles_y_const_begin)( cmp_obj ),
                           ::NS(Particles_y_const_end)( cmp_obj ),
                           ::NS(Particles_y_begin)( flat_buffer_obj ) );

                std::copy( ::NS(Particles_px_const_begin)( cmp_obj ),
                           ::NS(Particles_px_const_end)( cmp_obj ),
                           ::NS(Particles_px_begin)( flat_buffer_obj ) );

                std::copy( ::NS(Particles_py_const_begin)( cmp_obj ),
                           ::NS(Particles_py_const_end)( cmp_obj ),
                           ::NS(Particles_py_begin)( flat_buffer_obj ) );

                std::copy( ::NS(Particles_zeta_const_begin)( cmp_obj ),
                           ::NS(Particles_zeta_const_end)( cmp_obj ),
                           ::NS(Particles_zeta_begin)( flat_buffer_obj ) );

                std::copy( ::NS(Particles_psigma_const_begin)( cmp_obj ),
                           ::NS(Particles_psigma_const_end)( cmp_obj ),
                           ::NS(Particles_psigma_begin)( flat_buffer_obj ) );

                std::copy( ::NS(Particles_delta_const_begin)( cmp_obj ),
                           ::NS(Particles_delta_const_end)( cmp_obj ),
                           ::NS(Particles_delta_begin)( flat_buffer_obj ) );

                std::copy( ::NS(Particles_rpp_const_begin)( cmp_obj ),
                           ::NS(Particles_rpp_const_end)( cmp_obj ),
                           ::NS(Particles_rpp_begin)( flat_buffer_obj ) );

                std::copy( ::NS(Particles_rvv_const_begin)( cmp_obj ),
                           ::NS(Particles_rvv_const_end)( cmp_obj ),
                           ::NS(Particles_rvv_begin)( flat_buffer_obj ) );

                std::copy( ::NS(Particles_chi_const_begin)( cmp_obj ),
                           ::NS(Particles_chi_const_end)( cmp_obj ),
                           ::NS(Particles_chi_begin)( flat_buffer_obj ) );

                std::copy( ::NS(Particles_charge_ratio_const_begin)( cmp_obj ),
                           ::NS(Particles_charge_ratio_const_end)( cmp_obj ),
                           ::NS(Particles_charge_ratio_begin)( flat_buffer_obj ) );

                std::copy( ::NS(Particles_id_const_begin)( cmp_obj ),
                           ::NS(Particles_id_const_end)( cmp_obj ),
                           ::NS(Particles_id_begin)( flat_buffer_obj ) );

                std::copy( ::NS(Particles_at_element_const_begin)( cmp_obj ),
                           ::NS(Particles_at_element_const_end)( cmp_obj ),
                           ::NS(Particles_at_element_begin)( flat_buffer_obj ) );

                std::copy( ::NS(Particles_at_turn_const_begin)( cmp_obj ),
                           ::NS(Particles_at_turn_const_end)( cmp_obj ),
                           ::NS(Particles_at_turn_begin)( flat_buffer_obj ) );

                std::copy( ::NS(Particles_state_const_begin)( cmp_obj ),
                           ::NS(Particles_state_const_end)( cmp_obj ),
                           ::NS(Particles_state_begin)( flat_buffer_obj ) );

                break;
            }

            case 1:
            {
                flat_buffer_obj = ::NS(Particles_cobj_flat_buffer_new)(
                    flat_buffer, slot_size, ::NS(Particles_max_num_particles)(
                        cmp_obj ) );

                ASSERT_TRUE( flat_buffer_obj != nullptr );

                ::NS(Particles_set_num_particles)( flat_buffer_obj,
                    ::NS(Particles_num_particles)( cmp_obj ) );

                ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(Particles_copy)(
                    flat_buffer_obj, cmp_obj ) );

                break;
            }

            case 2:
            {
                flat_buffer_obj = ::NS(Particles_cobj_flat_buffer_add)(
                    flat_buffer, slot_size,
                    ::NS(Particles_max_num_particles)( cmp_obj ),
                    ::NS(Particles_num_particles)( cmp_obj ),
                    ::NS(Particles_charge0_const_begin)( cmp_obj ),
                    ::NS(Particles_mass0_const_begin)( cmp_obj ),
                    ::NS(Particles_beta0_const_begin)( cmp_obj ),
                    ::NS(Particles_gamma0_const_begin)( cmp_obj ),
                    ::NS(Particles_p0c_const_begin)( cmp_obj ),
                    ::NS(Particles_s_const_begin)( cmp_obj ),
                    ::NS(Particles_x_const_begin)( cmp_obj ),
                    ::NS(Particles_y_const_begin)( cmp_obj ),
                    ::NS(Particles_px_const_begin)( cmp_obj ),
                    ::NS(Particles_py_const_begin)( cmp_obj ),
                    ::NS(Particles_zeta_const_begin)( cmp_obj ),
                    ::NS(Particles_psigma_const_begin)( cmp_obj ),
                    ::NS(Particles_delta_const_begin)( cmp_obj ),
                    ::NS(Particles_rpp_const_begin)( cmp_obj ),
                    ::NS(Particles_rvv_const_begin)( cmp_obj ),
                    ::NS(Particles_chi_const_begin)( cmp_obj ),
                    ::NS(Particles_charge_ratio_const_begin)( cmp_obj ),
                    ::NS(Particles_id_const_begin)( cmp_obj ),
                    ::NS(Particles_at_element_const_begin)( cmp_obj ),
                    ::NS(Particles_at_turn_const_begin)( cmp_obj ),
                    ::NS(Particles_state_const_begin)( cmp_obj ) );

                ASSERT_TRUE( flat_buffer_obj != nullptr );

                break;
            }

            case 3:
            {
                flat_buffer_obj = ::NS(Particles_cobj_flat_buffer_add_copy)(
                    flat_buffer, slot_size, cmp_obj );

                ASSERT_TRUE( flat_buffer_obj != nullptr );

                break;
            }

            case 4:
            {
                flat_buffer_obj = ::NS(Particles_from_cobj_index)(
                    ::NS(CObjFlatBuffer_add_copy_of_object)(
                        flat_buffer, slot_size, cmp_obj,
                        ::NS(Particles_cobj_reserved_handle_size)( slot_size ),
                        ::NS(Particles_cobj_type_id)(),
                        ::NS(Particles_cobj_num_dataptrs)(),
                        &OFFSETS[ 0 ], &SIZES[ 0 ], &COUNTS[ 0 ], true ) );

                ASSERT_TRUE( flat_buffer_obj != nullptr );

                break;
            }

            case 5:
            {
                flat_buffer_obj = ::NS(Particles_from_cobj_index)(
                    ::NS(CObjFlatBuffer_add_copy_of_object_detailed)(
                        flat_buffer, slot_size, cmp_obj,
                        ::NS(Particles_cobj_reserved_handle_size)( slot_size ),
                        ::NS(Particles_cobj_actual_handle_size)( slot_size ),
                        ::NS(Particles_cobj_type_id)(),
                        ::NS(Particles_cobj_num_dataptrs)(),
                        &OFFSETS[ 0 ], &SIZES[ 0 ], &COUNTS[ 0 ], true ) );

                ASSERT_TRUE( flat_buffer_obj != nullptr );

                break;
            }

            default:
            {
                flat_buffer_obj = nullptr;
            }
        };

        ASSERT_TRUE( flat_buffer_obj != nullptr );
        ASSERT_TRUE( flat_buffer_obj != cmp_obj );

        if( 0 != ::NS(Particles_compare)( cmp_obj, flat_buffer_obj ) )
        {
            std::cout << "ii = " << ii << std::endl;
        }

        ASSERT_TRUE( 0 == ::NS(Particles_compare)( cmp_obj, flat_buffer_obj ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* c99_buffer: */

        size_type const c99_buffer_mode = ii % size_type{ 6 };

        switch( c99_buffer_mode )
        {
            case 0:
            {
                c99_buffer_obj = ::NS(Particles_cbuffer_new)( c99_buffer,
                    ::NS(Particles_max_num_particles)( cmp_obj ) );

                ASSERT_TRUE( c99_buffer_obj != nullptr );

                ::NS(Particles_set_num_particles)( c99_buffer_obj,
                    ::NS(Particles_num_particles)( cmp_obj ) );

                std::copy( ::NS(Particles_charge0_const_begin)( cmp_obj ),
                           ::NS(Particles_charge0_const_end)( cmp_obj ),
                           ::NS(Particles_charge0_begin)( c99_buffer_obj ) );

                std::copy( ::NS(Particles_mass0_const_begin)( cmp_obj ),
                           ::NS(Particles_mass0_const_end)( cmp_obj ),
                           ::NS(Particles_mass0_begin)( c99_buffer_obj ) );

                std::copy( ::NS(Particles_beta0_const_begin)( cmp_obj ),
                           ::NS(Particles_beta0_const_end)( cmp_obj ),
                           ::NS(Particles_beta0_begin)( c99_buffer_obj ) );

                std::copy( ::NS(Particles_gamma0_const_begin)( cmp_obj ),
                           ::NS(Particles_gamma0_const_end)( cmp_obj ),
                           ::NS(Particles_gamma0_begin)( c99_buffer_obj ) );

                std::copy( ::NS(Particles_p0c_const_begin)( cmp_obj ),
                           ::NS(Particles_p0c_const_end)( cmp_obj ),
                           ::NS(Particles_p0c_begin)( c99_buffer_obj ) );

                std::copy( ::NS(Particles_s_const_begin)( cmp_obj ),
                           ::NS(Particles_s_const_end)( cmp_obj ),
                           ::NS(Particles_s_begin)( c99_buffer_obj ) );

                std::copy( ::NS(Particles_x_const_begin)( cmp_obj ),
                           ::NS(Particles_x_const_end)( cmp_obj ),
                           ::NS(Particles_x_begin)( c99_buffer_obj ) );

                std::copy( ::NS(Particles_y_const_begin)( cmp_obj ),
                           ::NS(Particles_y_const_end)( cmp_obj ),
                           ::NS(Particles_y_begin)( c99_buffer_obj ) );

                std::copy( ::NS(Particles_px_const_begin)( cmp_obj ),
                           ::NS(Particles_px_const_end)( cmp_obj ),
                           ::NS(Particles_px_begin)( c99_buffer_obj ) );

                std::copy( ::NS(Particles_py_const_begin)( cmp_obj ),
                           ::NS(Particles_py_const_end)( cmp_obj ),
                           ::NS(Particles_py_begin)( c99_buffer_obj ) );

                std::copy( ::NS(Particles_zeta_const_begin)( cmp_obj ),
                           ::NS(Particles_zeta_const_end)( cmp_obj ),
                           ::NS(Particles_zeta_begin)( c99_buffer_obj ) );

                std::copy( ::NS(Particles_psigma_const_begin)( cmp_obj ),
                           ::NS(Particles_psigma_const_end)( cmp_obj ),
                           ::NS(Particles_psigma_begin)( c99_buffer_obj ) );

                std::copy( ::NS(Particles_delta_const_begin)( cmp_obj ),
                           ::NS(Particles_delta_const_end)( cmp_obj ),
                           ::NS(Particles_delta_begin)( c99_buffer_obj ) );

                std::copy( ::NS(Particles_rpp_const_begin)( cmp_obj ),
                           ::NS(Particles_rpp_const_end)( cmp_obj ),
                           ::NS(Particles_rpp_begin)( c99_buffer_obj ) );

                std::copy( ::NS(Particles_rvv_const_begin)( cmp_obj ),
                           ::NS(Particles_rvv_const_end)( cmp_obj ),
                           ::NS(Particles_rvv_begin)( c99_buffer_obj ) );

                std::copy( ::NS(Particles_chi_const_begin)( cmp_obj ),
                           ::NS(Particles_chi_const_end)( cmp_obj ),
                           ::NS(Particles_chi_begin)( c99_buffer_obj ) );

                std::copy( ::NS(Particles_charge_ratio_const_begin)( cmp_obj ),
                           ::NS(Particles_charge_ratio_const_end)( cmp_obj ),
                           ::NS(Particles_charge_ratio_begin)( c99_buffer_obj ) );

                std::copy( ::NS(Particles_id_const_begin)( cmp_obj ),
                           ::NS(Particles_id_const_end)( cmp_obj ),
                           ::NS(Particles_id_begin)( c99_buffer_obj ) );

                std::copy( ::NS(Particles_at_element_const_begin)( cmp_obj ),
                           ::NS(Particles_at_element_const_end)( cmp_obj ),
                           ::NS(Particles_at_element_begin)( c99_buffer_obj ) );

                std::copy( ::NS(Particles_at_turn_const_begin)( cmp_obj ),
                           ::NS(Particles_at_turn_const_end)( cmp_obj ),
                           ::NS(Particles_at_turn_begin)( c99_buffer_obj ) );

                std::copy( ::NS(Particles_state_const_begin)( cmp_obj ),
                           ::NS(Particles_state_const_end)( cmp_obj ),
                           ::NS(Particles_state_begin)( c99_buffer_obj ) );

                break;
            }

            case 1:
            {
                c99_buffer_obj = ::NS(Particles_cbuffer_new)( c99_buffer,
                    ::NS(Particles_max_num_particles)( cmp_obj ) );

                ASSERT_TRUE( c99_buffer_obj != nullptr );

                ::NS(Particles_set_num_particles)( c99_buffer_obj,
                    ::NS(Particles_num_particles)( cmp_obj ) );

                ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(Particles_copy)(
                    c99_buffer_obj, cmp_obj ) );
                break;
            }

            case 2:
            {
                c99_buffer_obj = ::NS(Particles_cbuffer_add)( c99_buffer,
                    ::NS(Particles_max_num_particles)( cmp_obj ),
                    ::NS(Particles_num_particles)( cmp_obj ),
                    ::NS(Particles_charge0_const_begin)( cmp_obj ),
                    ::NS(Particles_mass0_const_begin)( cmp_obj ),
                    ::NS(Particles_beta0_const_begin)( cmp_obj ),
                    ::NS(Particles_gamma0_const_begin)( cmp_obj ),
                    ::NS(Particles_p0c_const_begin)( cmp_obj ),
                    ::NS(Particles_s_const_begin)( cmp_obj ),
                    ::NS(Particles_x_const_begin)( cmp_obj ),
                    ::NS(Particles_y_const_begin)( cmp_obj ),
                    ::NS(Particles_px_const_begin)( cmp_obj ),
                    ::NS(Particles_py_const_begin)( cmp_obj ),
                    ::NS(Particles_zeta_const_begin)( cmp_obj ),
                    ::NS(Particles_psigma_const_begin)( cmp_obj ),
                    ::NS(Particles_delta_const_begin)( cmp_obj ),
                    ::NS(Particles_rpp_const_begin)( cmp_obj ),
                    ::NS(Particles_rvv_const_begin)( cmp_obj ),
                    ::NS(Particles_chi_const_begin)( cmp_obj ),
                    ::NS(Particles_charge_ratio_const_begin)( cmp_obj ),
                    ::NS(Particles_id_const_begin)( cmp_obj ),
                    ::NS(Particles_at_element_const_begin)( cmp_obj ),
                    ::NS(Particles_at_turn_const_begin)( cmp_obj ),
                    ::NS(Particles_state_const_begin)( cmp_obj ) );
                break;
            }

            case 3:
            {
                c99_buffer_obj = ::NS(Particles_cbuffer_add_copy)(
                    c99_buffer, cmp_obj );
                break;
            }

            case 4:
            {
                c99_buffer_obj = ::NS(Particles_from_cobj_index)(
                    ::NS(CBuffer_add_copy_of_object)(
                        c99_buffer, cmp_obj,
                        ::NS(Particles_cobj_reserved_handle_size)( slot_size ),
                        ::NS(Particles_cobj_type_id)(),
                        ::NS(Particles_cobj_num_dataptrs)(),
                        &OFFSETS[ 0 ], &SIZES[ 0 ], &COUNTS[ 0 ], true ) );

                break;
            }

            case 5:
            {
                c99_buffer_obj = ::NS(Particles_from_cobj_index)(
                    ::NS(CBuffer_add_copy_of_object_detailed)(
                        c99_buffer, cmp_obj,
                        ::NS(Particles_cobj_reserved_handle_size)( slot_size ),
                        ::NS(Particles_cobj_actual_handle_size)( slot_size ),
                        ::NS(Particles_cobj_type_id)(),
                        ::NS(Particles_cobj_num_dataptrs)(),
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
        ASSERT_TRUE( 0 == ::NS(Particles_compare)( cmp_obj, c99_buffer_obj ) );
        ASSERT_TRUE( 0 == ::NS(Particles_compare)(
                        flat_buffer_obj, c99_buffer_obj ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* cxx_buffer: */

        size_type cxx_buffer_mode = ii % size_type{ 7 };

        switch( cxx_buffer_mode )
        {
            case 0:
            {
                cxx_buffer_obj = ::NS(Particles_cbuffer_new)(
                    cxx_buffer.as_c_api(), ::NS(Particles_max_num_particles)(
                        cmp_obj ) );

                ASSERT_TRUE( cxx_buffer_obj != nullptr );

                ::NS(Particles_set_num_particles)( cxx_buffer_obj,
                    ::NS(Particles_num_particles)( cmp_obj ) );

                std::copy( ::NS(Particles_charge0_const_begin)( cmp_obj ),
                           ::NS(Particles_charge0_const_end)( cmp_obj ),
                           ::NS(Particles_charge0_begin)( cxx_buffer_obj ) );

                std::copy( ::NS(Particles_mass0_const_begin)( cmp_obj ),
                           ::NS(Particles_mass0_const_end)( cmp_obj ),
                           ::NS(Particles_mass0_begin)( cxx_buffer_obj ) );

                std::copy( ::NS(Particles_beta0_const_begin)( cmp_obj ),
                           ::NS(Particles_beta0_const_end)( cmp_obj ),
                           ::NS(Particles_beta0_begin)( cxx_buffer_obj ) );

                std::copy( ::NS(Particles_gamma0_const_begin)( cmp_obj ),
                           ::NS(Particles_gamma0_const_end)( cmp_obj ),
                           ::NS(Particles_gamma0_begin)( cxx_buffer_obj ) );

                std::copy( ::NS(Particles_p0c_const_begin)( cmp_obj ),
                           ::NS(Particles_p0c_const_end)( cmp_obj ),
                           ::NS(Particles_p0c_begin)( cxx_buffer_obj ) );

                std::copy( ::NS(Particles_s_const_begin)( cmp_obj ),
                           ::NS(Particles_s_const_end)( cmp_obj ),
                           ::NS(Particles_s_begin)( cxx_buffer_obj ) );

                std::copy( ::NS(Particles_x_const_begin)( cmp_obj ),
                           ::NS(Particles_x_const_end)( cmp_obj ),
                           ::NS(Particles_x_begin)( cxx_buffer_obj ) );

                std::copy( ::NS(Particles_y_const_begin)( cmp_obj ),
                           ::NS(Particles_y_const_end)( cmp_obj ),
                           ::NS(Particles_y_begin)( cxx_buffer_obj ) );

                std::copy( ::NS(Particles_px_const_begin)( cmp_obj ),
                           ::NS(Particles_px_const_end)( cmp_obj ),
                           ::NS(Particles_px_begin)( cxx_buffer_obj ) );

                std::copy( ::NS(Particles_py_const_begin)( cmp_obj ),
                           ::NS(Particles_py_const_end)( cmp_obj ),
                           ::NS(Particles_py_begin)( cxx_buffer_obj ) );

                std::copy( ::NS(Particles_zeta_const_begin)( cmp_obj ),
                           ::NS(Particles_zeta_const_end)( cmp_obj ),
                           ::NS(Particles_zeta_begin)( cxx_buffer_obj ) );

                std::copy( ::NS(Particles_psigma_const_begin)( cmp_obj ),
                           ::NS(Particles_psigma_const_end)( cmp_obj ),
                           ::NS(Particles_psigma_begin)( cxx_buffer_obj ) );

                std::copy( ::NS(Particles_delta_const_begin)( cmp_obj ),
                           ::NS(Particles_delta_const_end)( cmp_obj ),
                           ::NS(Particles_delta_begin)( cxx_buffer_obj ) );

                std::copy( ::NS(Particles_rpp_const_begin)( cmp_obj ),
                           ::NS(Particles_rpp_const_end)( cmp_obj ),
                           ::NS(Particles_rpp_begin)( cxx_buffer_obj ) );

                std::copy( ::NS(Particles_rvv_const_begin)( cmp_obj ),
                           ::NS(Particles_rvv_const_end)( cmp_obj ),
                           ::NS(Particles_rvv_begin)( cxx_buffer_obj ) );

                std::copy( ::NS(Particles_chi_const_begin)( cmp_obj ),
                           ::NS(Particles_chi_const_end)( cmp_obj ),
                           ::NS(Particles_chi_begin)( cxx_buffer_obj ) );

                std::copy( ::NS(Particles_charge_ratio_const_begin)( cmp_obj ),
                           ::NS(Particles_charge_ratio_const_end)( cmp_obj ),
                           ::NS(Particles_charge_ratio_begin)( cxx_buffer_obj ) );

                std::copy( ::NS(Particles_id_const_begin)( cmp_obj ),
                           ::NS(Particles_id_const_end)( cmp_obj ),
                           ::NS(Particles_id_begin)( cxx_buffer_obj ) );

                std::copy( ::NS(Particles_at_element_const_begin)( cmp_obj ),
                           ::NS(Particles_at_element_const_end)( cmp_obj ),
                           ::NS(Particles_at_element_begin)( cxx_buffer_obj ) );

                std::copy( ::NS(Particles_at_turn_const_begin)( cmp_obj ),
                           ::NS(Particles_at_turn_const_end)( cmp_obj ),
                           ::NS(Particles_at_turn_begin)( cxx_buffer_obj ) );

                std::copy( ::NS(Particles_state_const_begin)( cmp_obj ),
                           ::NS(Particles_state_const_end)( cmp_obj ),
                           ::NS(Particles_state_begin)( cxx_buffer_obj ) );

                break;
            }

            case 1:
            {
                cxx_buffer_obj = ::NS(Particles_cbuffer_new)(
                    cxx_buffer.as_c_api(), ::NS(Particles_max_num_particles)(
                        cmp_obj ) );

                ASSERT_TRUE( cxx_buffer_obj != nullptr );

                ::NS(Particles_set_num_particles)( cxx_buffer_obj,
                    ::NS(Particles_num_particles)( cmp_obj ) );

                ASSERT_TRUE( st::STATUS_SUCCESS == ::NS(Particles_copy)(
                    cxx_buffer_obj, cmp_obj ) );
                break;
            }

            case 2:
            {
                cxx_buffer_obj = ::NS(Particles_cbuffer_add)(
                    cxx_buffer.as_c_api(),
                    ::NS(Particles_max_num_particles)( cmp_obj ),
                    ::NS(Particles_num_particles)( cmp_obj ),
                    ::NS(Particles_charge0_const_begin)( cmp_obj ),
                    ::NS(Particles_mass0_const_begin)( cmp_obj ),
                    ::NS(Particles_beta0_const_begin)( cmp_obj ),
                    ::NS(Particles_gamma0_const_begin)( cmp_obj ),
                    ::NS(Particles_p0c_const_begin)( cmp_obj ),
                    ::NS(Particles_s_const_begin)( cmp_obj ),
                    ::NS(Particles_x_const_begin)( cmp_obj ),
                    ::NS(Particles_y_const_begin)( cmp_obj ),
                    ::NS(Particles_px_const_begin)( cmp_obj ),
                    ::NS(Particles_py_const_begin)( cmp_obj ),
                    ::NS(Particles_zeta_const_begin)( cmp_obj ),
                    ::NS(Particles_psigma_const_begin)( cmp_obj ),
                    ::NS(Particles_delta_const_begin)( cmp_obj ),
                    ::NS(Particles_rpp_const_begin)( cmp_obj ),
                    ::NS(Particles_rvv_const_begin)( cmp_obj ),
                    ::NS(Particles_chi_const_begin)( cmp_obj ),
                    ::NS(Particles_charge_ratio_const_begin)( cmp_obj ),
                    ::NS(Particles_id_const_begin)( cmp_obj ),
                    ::NS(Particles_at_element_const_begin)( cmp_obj ),
                    ::NS(Particles_at_turn_const_begin)( cmp_obj ),
                    ::NS(Particles_state_const_begin)( cmp_obj ) );
                break;
            }

            case 3:
            {
                cxx_buffer_obj = ::NS(Particles_cbuffer_add_copy)(
                    cxx_buffer.as_c_api(), cmp_obj );
                break;
            }

            case 4:
            {
                cxx_buffer_obj = ::NS(Particles_from_cobj_index)(
                    cxx_buffer.add_copy_of_object( cmp_obj,
                        ::NS(Particles_cobj_reserved_handle_size)( slot_size ),
                        ::NS(Particles_cobj_type_id)(),
                        ::NS(Particles_cobj_num_dataptrs)(),
                        &OFFSETS[ 0 ], &SIZES[ 0 ], &COUNTS[ 0 ] ) );

                break;
            }

            case 5:
            {
                cxx_buffer_obj = ::NS(Particles_from_cobj_index)(
                    cxx_buffer.add_copy_of_object_detailed( cmp_obj,
                        ::NS(Particles_cobj_reserved_handle_size)( slot_size ),
                        ::NS(Particles_cobj_actual_handle_size)( slot_size ),
                        ::NS(Particles_cobj_type_id)(),
                        ::NS(Particles_cobj_num_dataptrs)(),
                        &OFFSETS[ 0 ], &SIZES[ 0 ], &COUNTS[ 0 ] ) );

                break;
            }

            case 6:
            {
                cxx_buffer_obj = cxx_buffer.add_copy< particle_set_t >( cmp_obj );
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
        ASSERT_TRUE( 0 == ::NS(Particles_compare)( cmp_obj, cxx_buffer_obj ) );
        ASSERT_TRUE( 0 == ::NS(Particles_compare)(
                        flat_buffer_obj, cxx_buffer_obj ) );
        ASSERT_TRUE( 0 == ::NS(Particles_compare)(
                        c99_buffer_obj, cxx_buffer_obj ) );
    }

    ASSERT_TRUE( cxx_buffer.num_objects() == NUM_PARTICLE_SETS );
    ASSERT_TRUE( ::NS(CBuffer_num_objects)( c99_buffer ) == NUM_PARTICLE_SETS );
    ASSERT_TRUE( ::NS(CObjFlatBuffer_num_objects)( flat_buffer, slot_size ) ==
                  NUM_PARTICLE_SETS );

    /* --------------------------------------------------------------------- */
    /* Add all elements from the compare data set to each buffer */

    for( size_type ii = 0u ; ii < NUM_PARTICLE_SETS ; ++ii )
    {
        auto c99_buffer_obj = ::NS(Particles_const_from_cbuffer)( c99_buffer, ii );
        auto cxx_buffer_obj = cxx_buffer.get_object< particle_set_t >( ii );
        auto flat_buffer_obj = ::NS(Particles_const_from_cobj_flat_buffer)(
            flat_buffer, ii, slot_size );

        ASSERT_TRUE( flat_buffer_obj != nullptr );
        ASSERT_TRUE( c99_buffer_obj  != nullptr );
        ASSERT_TRUE( cxx_buffer_obj  != nullptr );
        ASSERT_TRUE( cxx_buffer_obj  != c99_buffer_obj );
        ASSERT_TRUE( cxx_buffer_obj  != flat_buffer_obj );
        ASSERT_TRUE( c99_buffer_obj  != flat_buffer_obj );

        ASSERT_TRUE( cxx_buffer_obj  == ::NS(Particles_const_from_cbuffer)(
            cxx_buffer.as_c_api(), ii ) );

        auto cmp_obj = &CMP_PARTICLES[ ii ];

        ASSERT_TRUE( cmp_obj != flat_buffer_obj );
        ASSERT_TRUE( 0 == ::NS(Particles_compare)( cmp_obj, flat_buffer_obj ) );
        ASSERT_TRUE( 0 == ::NS(Particles_compare)( cmp_obj, c99_buffer_obj ) );
        ASSERT_TRUE( 0 == ::NS(Particles_compare)( cmp_obj, cxx_buffer_obj ) );
    }

    /* --------------------------------------------------------------------- */
    /* cleanup */

    NS(CBuffer_delete)( c99_buffer );
}


