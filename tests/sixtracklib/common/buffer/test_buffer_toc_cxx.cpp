#include "sixtracklib/common/buffer/buffer_toc.hpp"

#include <algorithm>
#include <map>
#include <numeric>
#include <vector>
#include <random>

#include <gtest/gtest.h>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/buffer/definitions.h"
#include "sixtracklib/common/particles/definitions.h"
#include "sixtracklib/common/buffer.hpp"
#include "sixtracklib/common/particles.hpp"
#include "sixtracklib/common/be_drift/be_drift.hpp"
#include "sixtracklib/common/be_multipole/be_multipole.hpp"
#include "sixtracklib/common/be_xyshift/be_xyshift.hpp"
#include "sixtracklib/common/be_srotation/be_srotation.hpp"
#include "sixtracklib/common/be_limit/be_limit_rect.hpp"
#include "sixtracklib/common/be_limit/be_limit_ellipse.hpp"
#include "sixtracklib/common/be_beam_monitor/be_beam_monitor.hpp"
#include "sixtracklib/common/internal/stl_buffer_helpers.hpp"
#include "sixtracklib/testlib.h"

namespace SIXTRL_CXX_NAMESPACE
{
    namespace tests
    {
        template< class Map, class Prng, class TypeContainer >
        void Buffer_setup_random_lattice(
            SIXTRL_CXX_NAMESPACE::Buffer& SIXTRL_RESTRICT_REF lattice,
            SIXTRL_CXX_NAMESPACE::buffer_size_t const lattice_length,
            TypeContainer const& SIXTRL_RESTRICT_REF type_list,
            Prng& SIXTRL_RESTRICT_REF prng,
            Map& SIXTRL_RESTRICT_REF lattice_type_map )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;

            using buffer_t   = st::Buffer;
            using buf_size_t = buffer_t::size_type;
            using type_id_t  = buffer_t::type_id_t;

            std::uniform_int_distribution< buf_size_t > type_dist(
                0, type_list.size() - buf_size_t{ 1 } );

            std::uniform_int_distribution< int64_t > multipole_dist( 0, 9 );
            std::uniform_int_distribution< int64_t > pset_num_dist( 1, 10 );

            while( lattice.getNumObjects() < lattice_length )
            {
                buf_size_t const type_id_idx = type_dist( prng );
                type_id_t const type_id = type_list.at( type_id_idx );
                buf_size_t const current_lattice_idx = lattice.getNumObjects();
                bool added = false;

                switch( type_id )
                {
                    case st::OBJECT_TYPE_DRIFT:
                    {
                        st::Drift* elem = lattice.createNew< st::Drift >();
                        added = ( elem != nullptr );
                        break;
                    }

                    case st::OBJECT_TYPE_DRIFT_EXACT:
                    {
                        st::DriftExact* elem =
                            lattice.createNew< st::DriftExact >();
                        added = ( elem != nullptr );
                        break;
                    }

                    case st::OBJECT_TYPE_XYSHIFT:
                    {
                        st::XYShift* elem = lattice.createNew< st::XYShift >();
                        added = ( elem != nullptr );
                        break;
                    }

                    case st::OBJECT_TYPE_SROTATION:
                    {
                        st::SRotation* elem = lattice.createNew< st::SRotation >();
                        added = ( elem != nullptr );
                        break;
                    }

                    case st::OBJECT_TYPE_LIMIT_RECT:
                    {
                        st::LimitRect* elem = lattice.createNew< st::LimitRect >();
                        added = ( elem != nullptr );
                        break;
                    }

                    case st::OBJECT_TYPE_LIMIT_ELLIPSE:
                    {
                        st::LimitEllipse* elem =
                            lattice.createNew< st::LimitEllipse >();
                        added = ( elem != nullptr );
                        break;
                    }

                    case st::OBJECT_TYPE_BEAM_MONITOR:
                    {
                        st::BeamMonitor* elem =
                            lattice.createNew< st::BeamMonitor >();
                        added = ( elem != nullptr );
                        break;
                    }

                    case st::OBJECT_TYPE_MULTIPOLE:
                    {
                        int64_t const order = multipole_dist( prng );
                        st::MultiPole* elem = lattice.createNew<
                            st::MultiPole >( order );

                        added = ( elem != nullptr );
                        break;
                    }

                    case st::OBJECT_TYPE_PARTICLE:
                    {
                        int64_t const num_particles = pset_num_dist( prng );
                        st::Particles* elem = lattice.createNew<
                            st::Particles >( num_particles );

                        added = ( elem != nullptr );
                        break;
                    }

                    default:
                    {
                        added = false;
                    }
                };

                if( added )
                {
                    if( st::ARCH_STATUS_SUCCESS !=
                        st::Map_ordered_vec_insert_value(
                            lattice_type_map, type_id, current_lattice_idx,
                                buf_size_t{ 0 }, true ) )
                    {
                        break;
                    }
                }
            }
        }
    }
}

TEST( CxxCommonBufferBufferTocTests, BufferTocTest )
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    using buffer_toc_t       = st::BufferToc;
    using buffer_t           = st::Buffer;
    using buf_size_t         = buffer_t::size_type;
    using type_id_t          = buffer_t::type_id_t;
    using prng_t             = std::mt19937_64;
    using prng_seed_t        = prng_t::result_type;

    /* Init the prng to scramble the lattices enough to be somewhat
     * representative of "real" world lattices */

    prng_t prng( prng_seed_t{ 20191211 } );

    std::vector< type_id_t > available_types = {
        st::OBJECT_TYPE_DRIFT, st::OBJECT_TYPE_DRIFT_EXACT,
        st::OBJECT_TYPE_MULTIPOLE, st::OBJECT_TYPE_XYSHIFT,
        st::OBJECT_TYPE_SROTATION, st::OBJECT_TYPE_LIMIT_RECT,
        st::OBJECT_TYPE_LIMIT_ELLIPSE, st::OBJECT_TYPE_BEAM_MONITOR };

    std::sort( available_types.begin(), available_types.end() );

    /* --------------------------------------------------------------------- */
    /* Setup lattice buffer */

    buffer_t lattice;
    std::map< type_id_t, std::vector< buf_size_t > > cmp_type_map;

    constexpr buf_size_t LATTICE_LENGTH = buf_size_t{ 1000 };

    st::tests::Buffer_setup_random_lattice( lattice, LATTICE_LENGTH,
        available_types, prng, cmp_type_map );

    ASSERT_TRUE( lattice.getNumObjects() == LATTICE_LENGTH );
    ASSERT_TRUE( st::Map_ordered_vec_total_num_values(
                    cmp_type_map ) == LATTICE_LENGTH );

    /* create generic buffer toc */

    buffer_toc_t buffer_toc( lattice );

    ASSERT_TRUE( buffer_toc.has_types() );
    ASSERT_TRUE( buffer_toc.num_types() == cmp_type_map.size() );
    ASSERT_TRUE( buffer_toc.total_num_elements() == LATTICE_LENGTH );

    ASSERT_TRUE( std::distance( buffer_toc.types_begin(),
                                buffer_toc.types_end() ) ==
                 std::distance( cmp_type_map.begin(), cmp_type_map.end() ) );

    auto type_it  = buffer_toc.types_begin();
    auto type_end = buffer_toc.types_end();

    for( ; type_it != type_end ; ++type_it )
    {
        ASSERT_TRUE( std::binary_search( available_types.begin(),
            available_types.end(), *type_it ) );

        ASSERT_TRUE( buffer_toc.has_type_elements( *type_it ) );
        ASSERT_TRUE( cmp_type_map.find( *type_id ) != cmp_type_map.end() );

        ASSERT_TRUE( st::Map_ordered_vec_size( cmp_type_map, *type_it ) ==
            buffer_toc.num_type_elements( *type_it ) );

        ASSERT_TRUE( buffer_toc.type_elements_indices_begin(
            *type_it ) != nullptr );

        ASSERT_TRUE( buffer_toc.type_elements_indices_end(
            *type_it ) != nullptr );

        ASSERT_TRUE( std::is_sorted(
            buffer_toc.type_elements_indices_begin( *type_it ),
            buffer_toc.type_elements_indices_end( *type_it ) ) );

        ASSERT_TRUE( std::equal(
            st::Map_ordered_vec_begin( cmp_type_map, *type_it ),
            st::Map_ordered_vec_end( cmp_type_map, *type_it ),
            buffer_toc.type_elements_indices_begin( *type_it ) ) );
    }

    ASSERT_TRUE( buffer_toc.is_compatible_with( lattice ) );
    ASSERT_TRUE( buffer_toc.is_compatible_with( lattice.getCApiPtr() ) );

    /* create a second empty buffer toc */

    buffer_toc_t buffer_toc_copy;

    ASSERT_TRUE( st::ARCH_STATUS_SUCCESS ==
                 buffer_toc_copy.reset( lattice ) );

    ASSERT_TRUE( buffer_toc_copy == buffer_toc );
    ASSERT_TRUE( buffer_toc_copy.is_compatible_with( lattice ) );
    ASSERT_TRUE( buffer_toc_copy.is_compatible_with( lattice.getCApiPtr() ) );

    /* append an element to the lattice and create a third toc */

    buf_size_t const old_num_drifts = buffer_toc.num_type_elements(
        st::OBJECT_TYPE_DRIFT );

    st::Drift* drift = lattice.createNew< st::Drift >();

    buffer_toc_t buffer_toc_updated( lattice.getCApiPtr() );

    ASSERT_TRUE(  buffer_toc_updated != buffer_toc );
    ASSERT_TRUE(  buffer_toc_updated != buffer_toc_copy );

    ASSERT_TRUE( !buffer_toc.is_compatible_with( lattice ) );
    ASSERT_TRUE( !buffer_toc.is_compatible_with( lattice.getCApiPtr() ) );

    ASSERT_TRUE( !buffer_toc_copy.is_compatible_with( lattice ) );
    ASSERT_TRUE( !buffer_toc_copy.is_compatible_with( lattice.getCApiPtr() ) );

    /* bring buffer_toc_copy in line with the updated lattice */

    buffer_toc_copy.clear();

    ASSERT_TRUE( buffer_toc_copy.reset( lattice ) ==
        st::ARCH_STATUS_SUCCESS );

    ASSERT_TRUE( buffer_toc_copy.total_num_elements() ==
        ( LATTICE_LENGTH + buf_size_t{ 1 } ) );

    ASSERT_TRUE( buffer_toc_copy.num_type_elements(
        st::OBJECT_TYPE_DRIFT ) == ( old_num_drifts + buf_size_t{ 1 } ) );

    ASSERT_TRUE( buffer_toc_copy != buffer_toc );
    ASSERT_TRUE( buffer_toc_copy == buffer_toc_updated );
    ASSERT_TRUE( buffer_toc_copy.is_compatible_with( lattice ) );
    ASSERT_TRUE( buffer_toc_copy.is_compatible_with( lattice.getCApiPtr() ) );

    /* bring the buffer_toc in line with the updated lattice */

    ASSERT_TRUE( buffer_toc.reset( lattice ) == st::ARCH_STATUS_SUCCESS );
    ASSERT_TRUE( buffer_toc == buffer_toc_copy );
    ASSERT_TRUE( buffer_toc == buffer_toc_updated );

    ASSERT_TRUE( buffer_toc.is_compatible_with( lattice ) );
    ASSERT_TRUE( buffer_toc.is_compatible_with( lattice.getCApiPtr() ) );

    auto type_it  = buffer_toc.types_begin();
    auto type_end = buffer_toc.types_end();

    for( ; type_it != type_end ; ++type_it )
    {
        ASSERT_TRUE( std::binary_search( available_types.begin(),
                available_types.end(), *type_it ) );

        ASSERT_TRUE( buffer_toc.has_type_elements( *type_it ) );
        ASSERT_TRUE( cmp_type_map.find( *type_id ) != cmp_type_map.end() );

        ASSERT_TRUE( buffer_toc.type_elements_indices_begin(
            *type_it ) != nullptr );

        ASSERT_TRUE( buffer_toc.type_elements_indices_end(
            *type_it ) != nullptr );

        ASSERT_TRUE( std::is_sorted(
            buffer_toc.type_elements_indices_begin( *type_it ),
            buffer_toc.type_elements_indices_end( *type_it ) ) );

        if( *type_it != st::OBJECT_TYPE_DRIFT )
        {
            ASSERT_TRUE( st::Map_ordered_vec_size( cmp_type_map, *type_it ) ==
                buffer_toc.num_type_elements( *type_it ) );

            ASSERT_TRUE( std::equal(
                st::Map_ordered_vec_begin( cmp_type_map, *type_it ),
                st::Map_ordered_vec_end( cmp_type_map, *type_it ),
                buffer_toc.type_elements_indices_begin( *type_it ) ) );
        }
        else
        {
            ASSERT_TRUE( ( buf_size_t{ 1 } + st::Map_ordered_vec_size(
                cmp_type_map, *type_it ) ==
                    buffer_toc.num_type_elements( *type_it ) );

            /* All drifts up until the last one should still be the same */

            ASSERT_TRUE( std::equal(
                st::Map_ordered_vec_begin( cmp_type_map, *type_it ),
                st::Map_ordered_vec_end( cmp_type_map, *type_it ),
                buffer_toc.type_elements_indices_begin( *type_it ) ) );
        }
    }
}


TEST( CxxCommonBufferBufferTocTests, OutputOffsetBufferTocTest )
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    using buffer_toc_t       = st::OutputOffsetBufferToc;
    using buffer_t           = st::Buffer;
    using buf_size_t         = buffer_t::size_type;
    using type_id_t          = buffer_t::type_id_t;
    using prng_t             = std::mt19937_64;
    using prng_seed_t        = prng_t::result_type;

    /* Init the prng to scramble the lattices enough to be somewhat
     * representative of "real" world lattices */

    prng_t prng( prng_seed_t{ 20191211 } );

    std::vector< type_id_t > available_types = {
        st::OBJECT_TYPE_DRIFT, st::OBJECT_TYPE_DRIFT_EXACT,
        st::OBJECT_TYPE_MULTIPOLE, st::OBJECT_TYPE_XYSHIFT,
        st::OBJECT_TYPE_SROTATION, st::OBJECT_TYPE_LIMIT_RECT,
        st::OBJECT_TYPE_LIMIT_ELLIPSE, st::OBJECT_TYPE_BEAM_MONITOR };

    std::sort( available_types.begin(), available_types.end() );

    /* --------------------------------------------------------------------- */
    /* Setup lattice buffer */

    buffer_t lattice;
    std::map< type_id_t, std::vector< buf_size_t > > cmp_type_map;

    constexpr buf_size_t LATTICE_LENGTH = buf_size_t{ 1000 };

    st::tests::Buffer_setup_random_lattice( lattice, LATTICE_LENGTH,
        available_types, prng, cmp_type_map );

    ASSERT_TRUE( lattice.getNumObjects() == LATTICE_LENGTH );
    ASSERT_TRUE( st::Map_ordered_vec_total_num_values(
                    cmp_type_map ) == LATTICE_LENGTH );

    /* create buffer toc with output offsets */

    buffer_toc_t buffer_toc( lattice );
    type_id_t const be_monitor_type = st::OBJECT_TYPE_BEAM_MONITOR;

    ASSERT_TRUE( buffer_toc.is_compatible_with( lattice ) );
    ASSERT_TRUE( buffer_toc.is_compatible_with( lattice.getCApiPtr() ) );

    ASSERT_TRUE( !buffer_toc.has_output_offset( be_monitor_type ) );
    ASSERT_TRUE(  buffer_toc.enable_output_offset( be_monitor_type ) ==
                  st::ARCH_STATUS_SUCCESS );

    ASSERT_TRUE( buffer_toc.is_compatible_with( lattice ) );
    ASSERT_TRUE( buffer_toc.is_compatible_with( lattice.getCApiPtr() ) );

    for( auto const test_type : available_types )
    {
        buf_size_t const num_elements =
            buffer_toc.num_type_elements( test_type );

        if( test_type != be_monitor_type )
        {
            ASSERT_TRUE( !buffer_toc.has_output_offset( test_type ) );

            ASSERT_TRUE( buffer_toc.num_output_offset(
                test_type ) == buf_size_t{ 0 } );

            ASSERT_TRUE( buffer_toc.output_offsets_begin(
                test_type ) == nullptr );

            ASSERT_TRUE( buffer_toc.output_offsets_end(
                test_type ) == nullptr );

            for( buf_size_t ii = buf_size_t{ 0 } ; ii < num_elements ; ++ii )
            {
                buf_size_t const elem_idx =
                    buffer_toc.type_element_index( test_type, ii );

                ASSERT_TRUE( elem_idx < LATTICE_LENGTH );
                ASSERT_TRUE( buffer_toc.type_element_index_no_check(
                    test_type, ii ) == elem_idx );

                ASSERT_TRUE( buffer_toc.output_offset( test_type, ii ) ==
                    buffer_toc_t::ILLEGAL_OUTPUT_OFFSET );

                ASSERT_TRUE( buffer_toc.output_offset_by_buffer_index(
                    test_type, elem_idx ) ==
                        buffer_toc_t::ILLEGAL_OUTPUT_OFFSET );

                ASSERT_TRUE( buffer_toc.set_output_offset(
                    test_type, ii, elem_idx ) != st::ARCH_STATUS_SUCCESS );

                ASSERT_TRUE( buffer_toc.output_offset(
                    test_type, ii ) == buffer_toc_t::ILLEGAL_OUTPUT_OFFSET );

                ASSERT_TRUE( buffer_toc.output_offset_by_buffer_index(
                    test_type, elem_idx ) ==
                        buffer_toc_t::ILLEGAL_OUTPUT_OFFSET );

                ASSERT_TRUE( buffer_toc.set_output_offset_by_buffer_index(
                    test_type, elem_idx, ii ) != st::ARCH_STATUS_SUCCESS );

                ASSERT_TRUE( buffer_toc.output_offset( test_type, ii ) ==
                    buffer_toc_t::ILLEGAL_OUTPUT_OFFSET );

                ASSERT_TRUE( buffer_toc.output_offset_by_buffer_index(
                    test_type, elem_idx ) ==
                        buffer_toc_t::ILLEGAL_OUTPUT_OFFSET );
            }
        }
        else
        {
            ASSERT_TRUE( buffer_toc.has_output_offset( test_type ) );

            buf_size_t const nn = buffer_toc.num_output_offset( test_type );
            ASSERT_TRUE( nn == num_elements );

            ASSERT_TRUE( buffer_toc.output_offsets_begin(
                test_type ) != nullptr );

            ASSERT_TRUE( buffer_toc.output_offsets_end(
                test_type ) != nullptr );

            ASSERT_TRUE( std::distance(
                buffer_toc.output_offsets_begin( test_type ),
                buffer_toc.output_offsets_end( test_type ) ) ==
                    static_cast< std::ptrdiff_t >( num_elements ) );

            ASSERT_TRUE( std::all_of(
                buffer_toc.output_offsets_begin( test_type ),
                buffer_toc.output_offsets_end( test_type ),
                []( buf_size_t const offset ) -> bool
                { return ( offset == buffer_toc_t::ILLEGAL_OUTPUT_OFFSET ); } )
            );

            for( buf_size_t ii = buf_size_t{ 0 } ; ii < nn ; ++ii )
            {
                buf_size_t const elem_idx =
                    buffer_toc.type_element_index( test_type, ii );

                ASSERT_TRUE( elem_idx < LATTICE_LENGTH );
                ASSERT_TRUE( buffer_toc.type_element_index_no_check(
                    test_type, ii ) == elem_idx );

                ASSERT_TRUE( buffer_toc.output_offset( test_type, ii ) ==
                    buffer_toc_t::ILLEGAL_OUTPUT_OFFSET );

                ASSERT_TRUE( buffer_toc.output_offset_by_buffer_index(
                    test_type, elem_idx ) ==
                        buffer_toc_t::ILLEGAL_OUTPUT_OFFSET );

                ASSERT_TRUE( buffer_toc.set_output_offset(
                    test_type, ii, elem_idx ) == st::ARCH_STATUS_SUCCESS );

                ASSERT_TRUE( buffer_toc.output_offset(
                    test_type, ii ) == elem_idx );

                ASSERT_TRUE( buffer_toc.output_offset_by_buffer_index(
                    test_type, elem_idx ) == elem_idx );

                ASSERT_TRUE( buffer_toc.set_output_offset_by_buffer_index(
                    test_type, elem_idx, ii ) == st::ARCH_STATUS_SUCCESS );

                ASSERT_TRUE( buffer_toc.output_offset( test_type, ii ) == ii );
                ASSERT_TRUE( buffer_toc.output_offset_by_buffer_index(
                    test_type, elem_idx ) == ii );
            }
        }
    }

    ASSERT_TRUE( buffer_toc.is_compatible_with( lattice ) );
    ASSERT_TRUE( buffer_toc.is_compatible_with( lattice.getCApiPtr() ) );
}


TEST( CxxCommonBufferBufferTocTests, ParticleSetsBufferTocTest )
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    using base_buffer_toc_t  = st::BufferToc;
    using buffer_toc_t       = st::ParticleSetsBufferToc;
    using buffer_t           = st::Buffer;
    using particle_set_t     = st::Particles;
    using buf_size_t         = buffer_t::size_type;
    using type_id_t          = buffer_t::type_id_t;
    using prng_t             = std::mt19937_64;
    using prng_seed_t        = prng_t::result_type;

    /* Init the prng to scramble the mixed buffer enough to be somewhat
     * representative of "real" world lattices */

    prng_t prng( prng_seed_t{ 20191211 } );

    std::vector< type_id_t > available_types = {
        st::OBJECT_TYPE_PARTICLE, st::OBJECT_TYPE_DRIFT,
        st::OBJECT_TYPE_DRIFT_EXACT, st::OBJECT_TYPE_MULTIPOLE,
        st::OBJECT_TYPE_XYSHIFT, st::OBJECT_TYPE_SROTATION,
        st::OBJECT_TYPE_LIMIT_RECT, st::OBJECT_TYPE_LIMIT_ELLIPSE,
        st::OBJECT_TYPE_BEAM_MONITOR, st::OBJECT_TYPE_MULTIPOLE };

    std::sort( available_types.begin(), available_types.end() );

    /* --------------------------------------------------------------------- */
    /* Setup "mixed" buffer -> this one should not work with a
     * ParticleSetsBufferToc instance but with a regular BufferToc */

    buffer_t mixed_buffer;
    std::map< type_id_t, std::vector< buf_size_t > > cmp_type_map;

    constexpr buf_size_t MIXED_BUFFER_LEN = buf_size_t{ 1000 };

    st::tests::Buffer_setup_random_lattice( mixed_buffer, MIXED_BUFFER_LEN,
        available_types, prng, cmp_type_map );

    ASSERT_TRUE( mixed_buffer.getNumObjects() == MIXED_BUFFER_LEN );
    ASSERT_TRUE( st::Map_ordered_vec_total_num_values(
                    cmp_type_map ) == MIXED_BUFFER_LEN );

    ASSERT_TRUE( !st::Buffer_is_particles_buffer( pset_buffer ) );

    /* Create the "regular" mixed_buffer toc */

    base_buffer_toc_t mixed_buffer_toc( mixed_buffer );

    ASSERT_TRUE( mixed_buffer_toc.has_types() );
    ASSERT_TRUE( mixed_buffer_toc.num_types() == cmp_type_map.size() );
    ASSERT_TRUE( mixed_buffer_toc.total_num_elements() == MIXED_BUFFER_LEN );

    ASSERT_TRUE( std::distance( mixed_buffer_toc.types_begin(),
                                mixed_buffer_toc.types_end() ) ==
                 std::distance( cmp_type_map.begin(), cmp_type_map.end() ) );

    auto type_it  = mixed_buffer_toc.types_begin();
    auto type_end = mixed_buffer_toc.types_end();

    ASSERT_TRUE( type_it  != nullptr );
    ASSERT_TRUE( type_end != nullptr );

    for( ; type_it != type_end ; ++type_it )
    {
        ASSERT_TRUE( std::binary_search( available_types.begin(),
            available_types.end(), *type_it ) );

        ASSERT_TRUE( mixed_buffer_toc.has_type_elements( *type_it ) );
        ASSERT_TRUE( cmp_type_map.find( *type_id ) != cmp_type_map.end() );

        ASSERT_TRUE( st::Map_ordered_vec_size( cmp_type_map, *type_it ) ==
            mixed_buffer_toc.num_type_elements( *type_it ) );

        ASSERT_TRUE( mixed_buffer_toc.type_elements_indices_begin(
            *type_it ) != nullptr );

        ASSERT_TRUE( mixed_buffer_toc.type_elements_indices_end(
            *type_it ) != nullptr );

        ASSERT_TRUE( std::is_sorted(
            mixed_buffer_toc.type_elements_indices_begin( *type_it ),
            mixed_buffer_toc.type_elements_indices_end( *type_it ) ) );

        ASSERT_TRUE( std::equal(
            st::Map_ordered_vec_begin( cmp_type_map, *type_it ),
            st::Map_ordered_vec_end( cmp_type_map, *type_it ),
            mixed_buffer_toc.type_elements_indices_begin( *type_it ) ) );
    }

    ASSERT_TRUE( mixed_buffer_toc.is_compatible_with( mixed_buffer ) );
    ASSERT_TRUE( mixed_buffer_toc.is_compatible_with(
                  mixed_buffer.getCApiPtr() ) );

    /* Attempt to create a ParticleSetsBufferToc on the mixed_buffer ->
     * this should not work as the buffer contains not only particle sets */

    st::ParticleSetsBufferToc mixed_pset_toc( mixed_buffer );

    ASSERT_TRUE( !mixed_pset_toc.has_types() );
    ASSERT_TRUE(  mixed_pset_toc.num_types() == buf_size_t{ 0 } );
    ASSERT_TRUE(  mixed_pset_toc.total_num_elements() == buf_size_t{ 0 } );
    ASSERT_TRUE(  mixed_pset_toc.types_begin() == nullptr );
    ASSERT_TRUE(  mixed_pset_toc.types_end() == nullptr );
    ASSERT_TRUE( !mixed_pset_toc.has_type_elements( st::OBJECT_TYPE_PARTICLE ) );
    ASSERT_TRUE(  mixed_pset_toc.num_type_elements( st::OBJECT_TYPE_PARTICLE )
                  == buf_size_t{ 0 } );

    ASSERT_TRUE( !mixed_pset_toc.is_compatible_with( mixed_buffer ) );
    ASSERT_TRUE( !mixed_pset_toc.is_compatible_with(
                  mixed_buffer.getCApiPtr() ) );

    ASSERT_TRUE( mixed_pset_toc.reset(
        mixed_buffer ) != st::ARCH_STATUS_SUCCESS );

    ASSERT_TRUE(  mixed_pset_toc.num_types() == buf_size_t{ 0 } );
    ASSERT_TRUE(  mixed_pset_toc.total_num_elements() == buf_size_t{ 0 } );
    ASSERT_TRUE(  mixed_pset_toc.types_begin() == nullptr );
    ASSERT_TRUE(  mixed_pset_toc.types_end() == nullptr );
    ASSERT_TRUE( !mixed_pset_toc.has_type_elements( st::OBJECT_TYPE_PARTICLE ) );
    ASSERT_TRUE(  mixed_pset_toc.num_type_elements( st::OBJECT_TYPE_PARTICLE )
                  == buf_size_t{ 0 } );

    ASSERT_TRUE( !mixed_pset_toc.is_compatible_with( mixed_buffer ) );
    ASSERT_TRUE( !mixed_pset_toc.is_compatible_with(
                  mixed_buffer.getCApiPtr() ) );

    ASSERT_TRUE(  mixed_pset_toc != mixed_buffer_toc );

    /* Create a particle set buffer containing only particle sets: */

    constexpr buf_size_t NUM_PSETS = 100;

    buf_size_t cmp_total_num_particles = buf_size_t{ 0 };
    std::vector< buf_size_t > cmp_begin_indices( NUM_PSETS, buf_size_t{ 0 } );
    std::vector< buf_size_t > cmp_end_indices( NUM_PSETS, buf_size_t{ 0 } );
    std::vector< buf_size_t > cmp_num_particles( NUM_PSETS, buf_size_t{ 0 } );

    cmp_begin_indices.clear();
    cmp_end_indices.clear();
    cmp_num_particles.clear();

    buffer_t pset_buffer;

    std::uniform_int_distribution< buf_size_t > pset_num_dist( 1, 64 );

    for( buf_size_t ii = buf_size_t{ 0 } ; ii < NUM_PSETS ; ++ii )
    {
        buf_size_t const npart = pset_num_dist( prng );
        particle_set_t* pset = pset_buffer.createNew< particle_set_t >( npart );
        SIXTRL_ASSERT( pset != nullptr );

        cmp_begin_indices.push_back( cmp_total_num_particles );
        cmp_num_particles.push_back( pset->getNumParticles() );
        cmp_total_num_particles += pset->getNumParticles();
        cmp_end_indices.push_back( cmp_total_num_particles );
    }

    ASSERT_TRUE( pset_buffer.getNumObjects() == NUM_PSETS );
    ASSERT_TRUE( st::Buffer_is_particles_buffer( pset_buffer ) );
    ASSERT_TRUE( st::Particles_buffer_get_total_num_of_particles( pset_buffer )
                 == cmp_total_num_particles );

    ASSERT_TRUE( st::Particles_buffer_get_num_of_particle_blocks( pset_buffer )
                 == NUM_PSETS );

    /* create a "general" buffer toc on the pset buffer -> should always work */

    base_buffer_toc_t general_pset_buffer_toc( pset_buffer );

    ASSERT_TRUE( general_pset_buffer_toc.has_types() );
    ASSERT_TRUE( general_pset_buffer_toc.num_types() == buf_size_t{ 1 } );
    ASSERT_TRUE( general_pset_buffer_toc.total_num_elements() == NUM_PSETS );

    ASSERT_TRUE( std::distance( general_pset_buffer_toc.types_begin(),
        general_pset_buffer_toc.types_end() ) == std::ptridff_t{ 1 } );

    type_it  = general_pset_buffer_toc.types_begin();
    type_end = general_pset_buffer_toc.types_end();

    ASSERT_TRUE( type_end != nullptr );
    ASSERT_TRUE(  type_it != nullptr );
    ASSERT_TRUE( *type_it == st::OBJECT_TYPE_PARTICLE );

    ASSERT_TRUE( general_pset_buffer_toc.has_type_elements( *type_it ) );

    ASSERT_TRUE( general_pset_buffer_toc.type_elements_indices_begin(
        *type_it ) != nullptr );

    ASSERT_TRUE( general_pset_buffer_toc.type_elements_indices_end(
        *type_it ) != nullptr );

    ASSERT_TRUE( std::is_sorted(
        general_pset_buffer_toc.type_elements_indices_begin( *type_it ),
        general_pset_buffer_toc.type_elements_indices_end( *type_it ) ) );

    std::vector< buf_size_t > cmp_element_indices( NUM_PSETS, buf_size_t{ 0 } );

    std::iota( cmp_element_indices.begin(), cmp_element_indices.end(),
               buf_size_t{ 0 } );

    ASSERT_TRUE( std::equal(
        general_pset_buffer_toc.type_elements_indices_begin( *type_it ),
        general_pset_buffer_toc.type_elements_indices_end( *type_it ),
        cmp_element_indices.begin() ) );

    ASSERT_TRUE( general_pset_buffer_toc.is_compatible_with( pset_buffer ) );
    ASSERT_TRUE( general_pset_buffer_toc.is_compatible_with(
        pset_buffer.getCApiPtr() ) );

    /* create a dedicated particle sets buffer toc on the pset buffer */

    st::ParticleSetsBufferToc pset_toc( pset_buffer );

    ASSERT_TRUE( pset_toc.has_types() );
    ASSERT_TRUE( pset_toc.num_types() == buf_size_t{ 1 } );
    ASSERT_TRUE( pset_toc.total_num_elements() == NUM_PSETS );

    ASSERT_TRUE( std::distance( pset_toc.types_begin(),
        pset_toc.types_end() ) == std::ptridff_t{ 1 } );

    type_it  = pset_toc.types_begin();
    type_end = pset_toc.types_end();

    ASSERT_TRUE( type_end != nullptr );
    ASSERT_TRUE(  type_it != nullptr );
    ASSERT_TRUE( *type_it == st::OBJECT_TYPE_PARTICLE );

    ASSERT_TRUE( pset_toc.has_type_elements( *type_it ) );
    ASSERT_TRUE( pset_toc.type_elements_indices_begin( *type_it ) != nullptr );
    ASSERT_TRUE( pset_toc.type_elements_indices_end( *type_it ) != nullptr );

    ASSERT_TRUE( std::is_sorted(
        pset_toc.type_elements_indices_begin( *type_it ),
        pset_toc.type_elements_indices_end( *type_it ) ) );

    ASSERT_TRUE( std::equal(
        pset_toc.type_elements_indices_begin( *type_it ),
        pset_toc.type_elements_indices_end( *type_it ),
        general_pset_buffer_toc.type_elements_indices_begin( *type_it ) );

    ASSERT_TRUE( pset_toc.total_num_particles() == cmp_total_num_particles );

    ASSERT_TRUE( pset_toc.num_particle_sets() == NUM_PSETS );
    ASSERT_TRUE( pset_toc.num_particles_in_sets_begin() != nullptr );
    ASSERT_TRUE( pset_toc.num_particles_in_sets_end() != nullptr );
    ASSERT_TRUE( std::distance( pset_toc.num_particles_in_sets_begin(),
                                pset_toc.num_particles_in_sets_end() ) ==
        static_cast< std::ptrdiff_t >( NUM_PSETS ) );

    ASSERT_TRUE( std::equal( cmp_num_particles.begin(),
        cmp_num_particles.end(), pset_toc.num_particles_in_sets_begin() ) );


    ASSERT_TRUE( pset_toc.particle_set_begin_index_begin() != nullptr );
    ASSERT_TRUE( pset_toc.particle_set_begin_index_end() != nullptr );
    ASSERT_TRUE( std::distance( pset_toc.particle_set_begin_index_begin(),
                                pset_toc.particle_set_begin_index_end() ) ==
        static_cast< std::ptrdiff_t >( NUM_PSETS ) );

    ASSERT_TRUE( std::equal( cmp_begin_indices.begin(),
        cmp_begin_indices.end(), pset_toc.particle_set_begin_index_begin() ) );


    ASSERT_TRUE( pset_toc.particle_set_end_index_begin() != nullptr );
    ASSERT_TRUE( pset_toc.particle_set_end_index_end() != nullptr );
    ASSERT_TRUE( std::distance( pset_toc.particle_set_end_index_begin(),
                                pset_toc.particle_set_end_index_end() ) ==
        static_cast< std::ptrdiff_t >( NUM_PSETS ) );

    ASSERT_TRUE( std::equal( cmp_end_indices.begin(),
        cmp_end_indices.end(), pset_toc.particle_set_end_index_begin() ) );

    ASSERT_TRUE( pset_toc.is_compatible_with( pset_buffer ) );
    ASSERT_TRUE( pset_toc.is_compatible_with( pset_buffer.getCApiPtr() ) );
    ASSERT_TRUE( general_pset_buffer_toc == pset_toc );
}
