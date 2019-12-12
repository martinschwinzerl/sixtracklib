#include "sixtracklib/common/buffer/buffer_toc.h"

#include <algorithm>
#include <map>
#include <numeric>
#include <vector>
#include <random>

#include <gtest/gtest.h>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/buffer/definitions.h"
#include "sixtracklib/common/particles/definitions.h"
#include "sixtracklib/common/buffer.h"
#include "sixtracklib/common/particles.h"
#include "sixtracklib/common/be_drift/be_drift.h"
#include "sixtracklib/common/be_multipole/be_multipole.h"
#include "sixtracklib/common/be_xyshift/be_xyshift.h"
#include "sixtracklib/common/be_srotation/be_srotation.h"
#include "sixtracklib/common/be_limit/be_limit_rect.h"
#include "sixtracklib/common/be_limit/be_limit_ellipse.h"
#include "sixtracklib/common/be_beam_monitor/be_beam_monitor.h"
#include "sixtracklib/common/internal/stl_buffer_helpers.h"
#include "sixtracklib/testlib.h"

namespace SIXTRL_CXX_NAMESPACE
{
    namespace tests
    {
        template< class Map, class Prng, class TypeContainer >
        void Buffer_setup_random_lattice( ::NS(Buffer)* SIXTRL_RESTRICT lattice,
            ::NS(buffer_size_t) const lattice_length,
            TypeContainer const& SIXTRL_RESTRICT_REF type_list,
            Prng& SIXTRL_RESTRICT_REF prng,
            Map& SIXTRL_RESTRICT_REF lattice_type_map )
        {
            using buf_size_t = ::NS(buffer_size_t);
            using type_id_t  = ::NS(object_type_id_t);

            std::uniform_int_distribution< buf_size_t > type_dist(
                0, type_list.size() - buf_size_t{ 1 } );

            std::uniform_int_distribution< int64_t > multipole_dist( 0, 9 );
            std::uniform_int_distribution< int64_t > pset_num_dist( 1, 10 );

            while( ::NS(Buffer_get_num_of_objects)( lattice ) < lattice_length )
            {
                buf_size_t const type_id_idx = type_dist( prng );
                type_id_t const type_id = type_list.at( type_id_idx );
                buf_size_t const current_lattice_idx =
                    ::NS(Buffer_get_num_of_objects)( lattice );

                bool added = false;

                switch( type_id )
                {
                    case ::NS(OBJECT_TYPE_DRIFT):
                    {
                        ::NS(Drift)* elem = ::NS(Drift_new)( lattice );
                        added = ( elem != nullptr );
                        break;
                    }

                    case ::NS(OBJECT_TYPE_DRIFT_EXACT):
                    {
                        ::NS(DriftExact)* elem =
                            ::NS(DriftExact_new)( lattice );
                        added = ( elem != nullptr );
                        break;
                    }

                    case ::NS(OBJECT_TYPE_XYSHIFT):
                    {
                        ::NS(XYShift)* elem = ::NS(XYShift_new)( lattice );
                        added = ( elem != nullptr );
                        break;
                    }

                    case ::NS(OBJECT_TYPE_SROTATION):
                    {
                        ::NS(SRotation)* elem = ::NS(SRotation_new)( lattice );
                        added = ( elem != nullptr );
                        break;
                    }

                    case ::NS(OBJECT_TYPE_LIMIT_RECT):
                    {
                        ::NS(LimitRect)* elem = ::NS(LimitRect_new)( lattice );
                        added = ( elem != nullptr );
                        break;
                    }

                    case ::NS(OBJECT_TYPE_LIMIT_ELLIPSE):
                    {
                        ::NS(LimitEllipse)* elem =
                            ::NS(LimitEllipse_new)( lattice );
                        added = ( elem != nullptr );
                        break;
                    }

                    case ::NS(OBJECT_TYPE_BEAM_MONITOR):
                    {
                        ::NS(BeamMonitor)* elem =
                            ::NS(BeamMonitor_new)( lattice );
                        added = ( elem != nullptr );
                        break;
                    }

                    case ::NS(OBJECT_TYPE_MULTIPOLE):
                    {
                        int64_t const order = multipole_dist( prng );
                        ::NS(MultiPole)* elem =
                            ::NS(MultiPole_new)( lattice, order );

                        added = ( elem != nullptr );
                        break;
                    }

                    case ::NS(OBJECT_TYPE_PARTICLE):
                    {
                        int64_t const num_particles = pset_num_dist( prng );
                        ::NS(Particles)* elem =
                            ::NS(Particles_new)( lattice, num_particles );

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
                    if( ::NS(ARCH_STATUS_SUCCESS) !=
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

TEST( C99CommonBufferBufferTocTests, BufferTocTest )
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    using buffer_toc_t       = ::NS(BufferToc);
    using buffer_t           = ::NS(Buffer);
    using buf_size_t         = ::NS(buffer_size_t);
    using type_id_t          = ::NS(object_type_id_t);
    using prng_t             = std::mt19937_64;
    using prng_seed_t        = prng_t::result_type;

    /* Init the prng to scramble the lattices enough to be somewhat
     * representative of "real" world lattices */

    prng_t prng( prng_seed_t{ 20191211 } );

    std::vector< type_id_t > available_types = {
        ::NS(OBJECT_TYPE_DRIFT), ::NS(OBJECT_TYPE_DRIFT_EXACT),
        ::NS(OBJECT_TYPE_MULTIPOLE), ::NS(OBJECT_TYPE_XYSHIFT),
        ::NS(OBJECT_TYPE_SROTATION), ::NS(OBJECT_TYPE_LIMIT_RECT),
        ::NS(OBJECT_TYPE_LIMIT_ELLIPSE), ::NS(OBJECT_TYPE_BEAM_MONITOR) };

    std::sort( available_types.begin(), available_types.end() );

    /* --------------------------------------------------------------------- */
    /* Setup lattice buffer */

    buffer_t* lattice = ::NS(Buffer_new)( buf_size_t{ 0 } );
    SIXTRL_ASSERT( lattice != nullptr );

    std::map< type_id_t, std::vector< buf_size_t > > cmp_type_map;

    constexpr buf_size_t LATTICE_LENGTH = buf_size_t{ 1000 };

    st::tests::Buffer_setup_random_lattice(
        lattice, LATTICE_LENGTH, available_types, prng, cmp_type_map );

    ASSERT_TRUE( ::NS(Buffer_get_num_of_objects)( lattice ) == LATTICE_LENGTH );
    ASSERT_TRUE( st::Map_ordered_vec_total_num_values(
                    cmp_type_map ) == LATTICE_LENGTH );

    /* create generic buffer toc */

    buffer_toc_t* buffer_toc = ::NS(BufferToc_new)( lattice );

    ASSERT_TRUE( buffer_toc != nullptr );
    ASSERT_TRUE( ::NS(BufferToc_has_types)( buffer_toc ) );
    ASSERT_TRUE( ::NS(BufferToc_num_types)( buffer_toc ) ==
                 cmp_type_map.size() );

    ASSERT_TRUE( ::NS(BufferToc_total_num_elements)( buffer_toc ) ==
                 LATTICE_LENGTH );

    ASSERT_TRUE( std::distance( ::NS(BufferToc_types_begin)( buffer_toc ),
                                ::NS(BufferToc_types_end)( buffer_toc ) ) ==
                 std::distance( cmp_type_map.begin(), cmp_type_map.end() ) );

    auto type_it  = ::NS(BufferToc_types_begin)( buffer_toc );
    auto type_end = ::NS(BufferToc_types_end)( buffer_toc );

    for( ; type_it != type_end ; ++type_it )
    {
        ASSERT_TRUE( std::binary_search( available_types.begin(),
            available_types.end(), *type_it ) );

        ASSERT_TRUE( ::NS(BufferToc_has_type_elements)( buffer_toc, *type_it ) );
        ASSERT_TRUE( cmp_type_map.find( *type_id ) != cmp_type_map.end() );

        ASSERT_TRUE( st::Map_ordered_vec_size( cmp_type_map, *type_it ) ==
            ::NS(BufferToc_num_type_elements)( buffer_toc, *type_it ) );

        ASSERT_TRUE( ::NS(BufferToc_type_elements_indices_begin)( buffer_toc, *type_it ) != nullptr );
        ASSERT_TRUE( ::NS(BufferToc_type_elements_indices_end)( buffer_toc, *type_it ) != nullptr );

        ASSERT_TRUE( std::is_sorted(
            ::NS(BufferToc_type_elements_indices_begin)( buffer_toc, *type_it ),
            ::NS(BufferToc_type_elements_indices_end)( buffer_toc, *type_it ) ) );

        ASSERT_TRUE( std::equal(
            st::Map_ordered_vec_begin( cmp_type_map, *type_it ),
            st::Map_ordered_vec_end( cmp_type_map, *type_it ),
            ::NS(BufferToc_type_elements_indices_begin)( buffer_toc, *type_it ) ) );
    }

    ASSERT_TRUE( ::NS(BufferToc_is_compatible_with)( buffer_toc, lattice ) );

    /* create a second empty buffer toc */

    buffer_toc_t* buffer_toc_copy = ::NS(BufferToc_create)();

    ASSERT_TRUE( buffer_toc_copy != nullptr );
    ASSERT_TRUE( ::NS(ARCH_STATUS_SUCCESS) ==
                 ::NS(BufferToc_reset)( buffer_toc_copy, lattice ) );

    ASSERT_TRUE( buffer_toc_copy == buffer_toc );
    ASSERT_TRUE( ::NS(BufferToc_is_compatible_with)( buffer_toc_copy, lattice ) );

    /* append an element to the lattice and create a third toc */

    buf_size_t const old_num_drifts = ::NS(BufferToc_num_type_elements)(
        buffer_toc, ::NS(OBJECT_TYPE_DRIFT) );

    ::NS(Drift)* drift = ::NS(Drift_new)( lattice );
    buffer_toc_t* buffer_toc_updated ::NS(BufferToc_new)( lattice );

    ASSERT_TRUE( buffer_toc_updated != nullptr );
    ASSERT_TRUE(  ::NS(BufferToc_are_not_equal)(
        buffer_toc_updated, buffer_toc ) );

    ASSERT_TRUE(  ::NS(BufferToc_are_not_equal)(
        buffer_toc_updated, buffer_toc_copy ) );

    ASSERT_TRUE( !::NS(BufferToc_is_compatible_with)( buffer_toc, lattice ) );
    ASSERT_TRUE( !::NS(BufferToc_is_compatible_with)(
        buffer_toc_copy, lattice ) );

    /* bring buffer_toc_copy in line with the updated lattice */

    ::NS(BufferToc_clear)( buffer_toc_copy );

    ASSERT_TRUE( ::NS(BufferToc_reset)( buffer_toc_copy, lattice ) ==
        ::NS(ARCH_STATUS_SUCCESS) );

    ASSERT_TRUE( ::NS(BufferToc_total_num_elements)( buffer_toc_copy ) ==
        ( LATTICE_LENGTH + buf_size_t{ 1 } ) );

    ASSERT_TRUE( ::NS(BufferToc_num_type_elements)( buffer_toc_copy,
        ::NS(OBJECT_TYPE_DRIFT) ) == ( old_num_drifts + buf_size_t{ 1 } ) );

    ASSERT_TRUE( buffer_toc_copy != buffer_toc );
    ASSERT_TRUE( buffer_toc_copy == buffer_toc_updated );
    ASSERT_TRUE( ::NS(BufferToc_is_compatible_with)( buffer_toc_copy, lattice ) );

    /* bring the buffer_toc in line with the updated lattice */

    ASSERT_TRUE( ::NS(BufferToc_reset)( buffer_toc, lattice ) == ::NS(ARCH_STATUS_SUCCESS) );
    ASSERT_TRUE( ::NS(BufferToc_are_equal)( buffer_toc, buffer_toc_copy ) );
    ASSERT_TRUE( ::NS(BufferToc_are_equal)( buffer_toc, buffer_toc_updated ) );
    ASSERT_TRUE( ::NS(BufferToc_is_compatible_with)( buffer_toc, lattice ) );

    auto type_it  = ::NS(BufferToc_types_begin)( buffer_toc );
    auto type_end = ::NS(BufferToc_types_end)( buffer_toc );

    for( ; type_it != type_end ; ++type_it )
    {
        ASSERT_TRUE( std::binary_search( available_types.begin(),
                available_types.end(), *type_it ) );

        ASSERT_TRUE( ::NS(BufferToc_has_type_elements)( buffer_toc, *type_it ) );
        ASSERT_TRUE( cmp_type_map.find( *type_id ) != cmp_type_map.end() );

        ASSERT_TRUE( ::NS(BufferToc_type_elements_indices_begin)(
            buffer_toc, *type_it ) != nullptr );

        ASSERT_TRUE( ::NS(BufferToc_type_elements_indices_end)(
            buffer_toc, *type_it ) != nullptr );

        ASSERT_TRUE( std::is_sorted(
            ::NS(BufferToc_type_elements_indices_begin)( buffer_toc, *type_it ),
            ::NS(BufferToc_type_elements_indices_end)( buffer_toc, *type_it ) ) );

        if( *type_it != ::NS(OBJECT_TYPE_DRIFT) )
        {
            ASSERT_TRUE( st::Map_ordered_vec_size( cmp_type_map, *type_it ) ==
                ::NS(BufferToc_num_type_elements)( buffer_toc, *type_it ) );

            ASSERT_TRUE( std::equal(
                st::Map_ordered_vec_begin( cmp_type_map, *type_it ),
                st::Map_ordered_vec_end( cmp_type_map, *type_it ),
                ::NS(BufferToc_type_elements_indices_begin)( buffer_toc, *type_it ) ) );
        }
        else
        {
            ASSERT_TRUE( ( buf_size_t{ 1 } + st::Map_ordered_vec_size(
                cmp_type_map, *type_it ) ==
                    ::NS(BufferToc_num_type_elements)( buffer_toc, *type_it ) );

            /* All drifts up until the last one should still be the same */

            ASSERT_TRUE( std::equal(
                st::Map_ordered_vec_begin( cmp_type_map, *type_it ),
                st::Map_ordered_vec_end( cmp_type_map, *type_it ),
                ::NS(BufferToc_type_elements_indices_begin)( buffer_toc, *type_it ) ) );
        }
    }

    ::NS(BufferToc_delete)( buffer_toc );
    ::NS(BufferToc_delete)( buffer_toc_copy );
    ::NS(BufferToc_delete)( buffer_toc_updated );
    ::NS(Buffer_delete)( lattice );
}


TEST( C99CommonBufferBufferTocTests, OutputOffsetBufferTocTest )
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    using buffer_toc_t       = ::NS(OutputOffsetBufferToc);
    using buffer_t           = ::NS(Buffer);
    using buf_size_t         = ::NS(buffer_size_t);
    using type_id_t          = ::NS(object_type_id_t);
    using prng_t             = std::mt19937_64;
    using prng_seed_t        = prng_t::result_type;

    /* Init the prng to scramble the lattices enough to be somewhat
     * representative of "real" world lattices */

    prng_t prng( prng_seed_t{ 20191211 } );

    std::vector< type_id_t > available_types = {
        ::NS(OBJECT_TYPE_DRIFT), ::NS(OBJECT_TYPE_DRIFT_EXACT),
        ::NS(OBJECT_TYPE_MULTIPOLE), ::NS(OBJECT_TYPE_XYSHIFT),
        ::NS(OBJECT_TYPE_SROTATION), ::NS(OBJECT_TYPE_LIMIT_RECT),
        ::NS(OBJECT_TYPE_LIMIT_ELLIPSE), ::NS(OBJECT_TYPE_BEAM_MONITOR) };

    std::sort( available_types.begin(), available_types.end() );

    /* --------------------------------------------------------------------- */
    /* Setup lattice buffer */

    buffer_t* lattice = ::NS(Buffer_new)( buf_size_t{ 0 } );
    SIXTRL_ASSERT( lattice != nullptr );

    std::map< type_id_t, std::vector< buf_size_t > > cmp_type_map;
    constexpr buf_size_t LATTICE_LENGTH = buf_size_t{ 1000 };

    st::tests::Buffer_setup_random_lattice(
        lattice, LATTICE_LENGTH, available_types, prng, cmp_type_map );

    ASSERT_TRUE( ::NS(Buffer_get_num_of_objects)( lattice ) == LATTICE_LENGTH );
    ASSERT_TRUE( st::Map_ordered_vec_total_num_values(
                    cmp_type_map ) == LATTICE_LENGTH );

    /* create buffer toc with output offsets */

    buffer_toc_t* buffer_toc = ::NS(BufferToc_new)( lattice );
    ASSERT_TRUE( buffer_toc != nullptr );

    type_id_t const be_monitor_type = ::NS(OBJECT_TYPE_BEAM_MONITOR);

    ASSERT_TRUE( ::NS(BufferToc_is_compatible_with)( buffer_toc, lattice ) );
    ASSERT_TRUE( !::NS(OutputOffsetBufferToc_has_output_offset)( buffer_toc, be_monitor_type ) );
    ASSERT_TRUE(  ::NS(OutputOffsetBufferToc_enable_output_offset)( buffer_toc, be_monitor_type ) ==
                  ::NS(ARCH_STATUS_SUCCESS) );

    ASSERT_TRUE( ::NS(BufferToc_is_compatible_with)( buffer_toc, lattice ) );

    for( auto const test_type : available_types )
    {
        buf_size_t const num_elements =
            ::NS(BufferToc_num_type_elements)( buffer_toc, test_type );

        if( test_type != be_monitor_type )
        {
            ASSERT_TRUE( !::NS(OutputOffsetBufferToc_has_output_offset)( buffer_toc, test_type ) );

            ASSERT_TRUE( ::NS(OutputOffsetBufferToc_num_output_offset)( buffer_toc, test_type ) == buf_size_t{ 0 } );
            ASSERT_TRUE( ::NS(OutputOffsetBufferToc_output_offsets_begin)( buffer_toc, test_type ) == nullptr );
            ASSERT_TRUE( ::NS(OutputOffsetBufferToc_output_offsets_end)( buffer_toc, test_type ) == nullptr );

            for( buf_size_t ii = buf_size_t{ 0 } ; ii < num_elements ; ++ii )
            {
                buf_size_t const elem_idx = ::NS(OutputOffsetBufferToc_type_element_index)( buffer_toc, test_type, ii );

                ASSERT_TRUE( elem_idx < LATTICE_LENGTH );
                ASSERT_TRUE( ::NS(OutputOffsetBufferToc_type_element_index_no_check)( buffer_toc, test_type, ii ) == elem_idx );

                ASSERT_TRUE( ::NS(OutputOffsetBufferToc_output_offset)( buffer_toc, test_type, ii ) ==
                    buffer_toc_t::ILLEGAL_OUTPUT_OFFSET );

                ASSERT_TRUE( ::NS(OutputOffsetBufferToc_output_offset_by_buffer_index)( buffer_toc, test_type, elem_idx ) ==
                        buffer_toc_t::ILLEGAL_OUTPUT_OFFSET );

                ASSERT_TRUE( buffer_toc.set_output_offset( test_type, ii, elem_idx ) != ::NS(ARCH_STATUS_SUCCESS) );

                ASSERT_TRUE( ::NS(OutputOffsetBufferToc_output_offset)( buffer_toc, test_type, ii ) == buffer_toc_t::ILLEGAL_OUTPUT_OFFSET );

                ASSERT_TRUE( ::NS(OutputOffsetBufferToc_output_offset_by_buffer_index)( buffer_toc, test_type, elem_idx ) ==
                        buffer_toc_t::ILLEGAL_OUTPUT_OFFSET );

                ASSERT_TRUE( ::NS(OutputOffsetBufferToc_set_output_offset_by_buffer_index)( buffer_toc, test_type, elem_idx, ii ) != ::NS(ARCH_STATUS_SUCCESS) );

                ASSERT_TRUE( ::NS(OutputOffsetBufferToc_output_offset)( buffer_toc, test_type, ii ) ==
                    buffer_toc_t::ILLEGAL_OUTPUT_OFFSET );

                ASSERT_TRUE( ::NS(OutputOffsetBufferToc_output_offset_by_buffer_index)( buffer_toc, test_type, elem_idx ) ==
                        buffer_toc_t::ILLEGAL_OUTPUT_OFFSET );
            }
        }
        else
        {
            ASSERT_TRUE( ::NS(OutputOffsetBufferToc_has_output_offset)( buffer_toc, test_type ) );

            buf_size_t const nn = ::NS(OutputOffsetBufferToc_num_output_offset)( buffer_toc, test_type );
            ASSERT_TRUE( nn == num_elements );

            ASSERT_TRUE( ::NS(OutputOffsetBufferToc_output_offsets_begin)( buffer_toc, test_type ) != nullptr );
            ASSERT_TRUE( ::NS(OutputOffsetBufferToc_output_offsets_end)( buffer_toc, test_type ) != nullptr );

            ASSERT_TRUE( std::distance(
                ::NS(OutputOffsetBufferToc_output_offsets_begin)( buffer_toc, test_type ),
                ::NS(OutputOffsetBufferToc_output_offsets_end)( buffer_toc, test_type ) ) ==
                    static_cast< std::ptrdiff_t >( num_elements ) );

            ASSERT_TRUE( std::all_of(
                ::NS(OutputOffsetBufferToc_output_offsets_begin)( buffer_toc, test_type ),
                ::NS(OutputOffsetBufferToc_output_offsets_end)( buffer_toc, test_type ),
                []( buf_size_t const offset ) -> bool
                { return ( offset == buffer_toc_t::ILLEGAL_OUTPUT_OFFSET ); } )
            );

            for( buf_size_t ii = buf_size_t{ 0 } ; ii < nn ; ++ii )
            {
                buf_size_t const elem_idx =
                    ::NS(OutputOffsetBufferToc_type_element_index)( buffer_toc, test_type, ii );

                ASSERT_TRUE( elem_idx < LATTICE_LENGTH );
                ASSERT_TRUE( ::NS(OutputOffsetBufferToc_type_element_index_no_check)( buffer_toc, test_type, ii ) == elem_idx );

                ASSERT_TRUE( ::NS(OutputOffsetBufferToc_output_offset)( buffer_toc, test_type, ii ) ==
                    buffer_toc_t::ILLEGAL_OUTPUT_OFFSET );

                ASSERT_TRUE( ::NS(OutputOffsetBufferToc_output_offset_by_buffer_index)( buffer_toc, test_type, elem_idx ) ==
                        buffer_toc_t::ILLEGAL_OUTPUT_OFFSET );

                ASSERT_TRUE( buffer_toc.set_output_offset( test_type, ii, elem_idx ) == ::NS(ARCH_STATUS_SUCCESS) );

                ASSERT_TRUE( ::NS(OutputOffsetBufferToc_output_offset)( buffer_toc, test_type, ii ) == elem_idx );

                ASSERT_TRUE( ::NS(OutputOffsetBufferToc_output_offset_by_buffer_index)( buffer_toc, test_type, elem_idx ) == elem_idx );

                ASSERT_TRUE( ::NS(OutputOffsetBufferToc_set_output_offset_by_buffer_index)( buffer_toc, test_type, elem_idx, ii ) == ::NS(ARCH_STATUS_SUCCESS) );

                ASSERT_TRUE( ::NS(OutputOffsetBufferToc_output_offset)( buffer_toc, test_type, ii ) == ii );
                ASSERT_TRUE( ::NS(OutputOffsetBufferToc_output_offset_by_buffer_index)( buffer_toc, test_type, elem_idx ) == ii );
            }
        }
    }

    ASSERT_TRUE( ::NS(BufferToc_is_compatible_with)( buffer_toc, lattice ) );

    ::NS(BufferToc_delete)( buffer_toc );
    ::NS(Buffer_delete)( lattice );
}


TEST( C99CommonBufferBufferTocTests, ParticleSetsBufferTocTest )
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    using base_buffer_toc_t  = ::NS(BufferToc);
    using buffer_toc_t       = ::NS(ParticleSetsBufferToc);
    using buffer_t           = ::NS(Buffer);
    using particle_set_t     = ::NS(Particles);
    using buf_size_t         = ::NS(buffer_size_t);
    using type_id_t          = ::NS(object_type_id_t);
    using prng_t             = std::mt19937_64;
    using prng_seed_t        = prng_t::result_type;

    /* Init the prng to scramble the mixed buffer enough to be somewhat
     * representative of "real" world lattices */

    prng_t prng( prng_seed_t{ 20191211 } );

    std::vector< type_id_t > available_types = {
        ::NS(OBJECT_TYPE_PARTICLE), ::NS(OBJECT_TYPE_DRIFT),
        ::NS(OBJECT_TYPE_DRIFT_EXACT), ::NS(OBJECT_TYPE_MULTIPOLE),
        ::NS(OBJECT_TYPE_XYSHIFT), ::NS(OBJECT_TYPE_SROTATION),
        ::NS(OBJECT_TYPE_LIMIT_RECT), ::NS(OBJECT_TYPE_LIMIT_ELLIPSE),
        ::NS(OBJECT_TYPE_BEAM_MONITOR), ::NS(OBJECT_TYPE_MULTIPOLE) };

    std::sort( available_types.begin(), available_types.end() );

    /* --------------------------------------------------------------------- */
    /* Setup "mixed" buffer -> this one should not work with a
     * ParticleSetsBufferToc instance but with a regular BufferToc */

    buffer_t* mixed_buffer = ::NS(Buffer_new)( buf_size_t{ 0 } );
    SIXTRL_ASSERT( mixed_buffer != nullptr );

    constexpr buf_size_t MIXED_BUFFER_LEN = buf_size_t{ 1000 };
    std::map< type_id_t, std::vector< buf_size_t > > cmp_type_map;

    st::tests::Buffer_setup_random_lattice(
        mixed_buffer, MIXED_BUFFER_LEN, available_types, prng, cmp_type_map );

    ASSERT_TRUE( ::NS(Buffer_get_num_of_objects)( mixed_buffer) ==
                 MIXED_BUFFER_LEN );

    ASSERT_TRUE( st::Map_ordered_vec_total_num_values(
                    cmp_type_map ) == MIXED_BUFFER_LEN );

    ASSERT_TRUE( !::NS(Buffer_is_particles_buffer)( pset_buffer ) );

    /* Create the "regular" mixed_buffer toc */

    base_buffer_toc_t* mixed_buffer_toc =
        ::NS(ParticleSetsBufferToc_new)( mixed_buffer );

    ASSERT_TRUE( ::NS(BufferToc_has_types)( mixed_buffer_toc ) );
    ASSERT_TRUE( ::NS(BufferToc_num_types)( mixed_buffer_toc ) == cmp_type_map.size() );
    ASSERT_TRUE( ::NS(BufferToc_total_num_elements)( mixed_buffer_toc ) == MIXED_BUFFER_LEN );

    ASSERT_TRUE( std::distance( ::NS(BufferToc_types_begin)( mixed_buffer_toc ),
                                ::NS(BufferToc_types_end)( mixed_buffer_toc ) ) ==
                 std::distance( cmp_type_map.begin(), cmp_type_map.end() ) );

    auto type_it  = ::NS(BufferToc_types_begin)( mixed_buffer_toc );
    auto type_end = ::NS(BufferToc_types_end)( mixed_buffer_toc );

    ASSERT_TRUE( type_it  != nullptr );
    ASSERT_TRUE( type_end != nullptr );

    for( ; type_it != type_end ; ++type_it )
    {
        ASSERT_TRUE( std::binary_search( available_types.begin(),
            available_types.end(), *type_it ) );

        ASSERT_TRUE( ::NS(BufferToc_has_type_elements)( mixed_buffer_toc, *type_it ) );
        ASSERT_TRUE( cmp_type_map.find( *type_id ) != cmp_type_map.end() );

        ASSERT_TRUE( st::Map_ordered_vec_size( cmp_type_map, *type_it ) ==
            ::NS(BufferToc_num_type_elements)( mixed_buffer_toc, *type_it ) );

        ASSERT_TRUE( ::NS(BufferToc_type_elements_indices_begin)( mixed_buffer_toc, *type_it ) != nullptr );
        ASSERT_TRUE( ::NS(BufferToc_type_elements_indices_end)( mixed_buffer_toc, *type_it ) != nullptr );

        ASSERT_TRUE( std::is_sorted(
            ::NS(BufferToc_type_elements_indices_begin)( mixed_buffer_toc, *type_it ),
            ::NS(BufferToc_type_elements_indices_end)( mixed_buffer_toc, *type_it ) ) );

        ASSERT_TRUE( std::equal(
            st::Map_ordered_vec_begin( cmp_type_map, *type_it ),
            st::Map_ordered_vec_end( cmp_type_map, *type_it ),
            ::NS(BufferToc_type_elements_indices_begin)( mixed_buffer_toc, *type_it ) ) );
    }

    ASSERT_TRUE( ::NS(BufferToc_is_compatible_with)( mixed_buffer_toc, mixed_buffer ) );

    /* Attempt to create a ParticleSetsBufferToc on the mixed_buffer ->
     * this should not work as the buffer contains not only particle sets */

    ::NS(ParticleSetsBufferToc)* mixed_pset_toc =
        ::NS(ParticleSetsBufferToc_new)( mixed_buffer );

    ASSERT_TRUE( mixed_pset_toc != nullptr );
    ASSERT_TRUE( !::NS(BufferToc_has_types)( mixed_pset_toc ) );
    ASSERT_TRUE(  ::NS(BufferToc_num_types)( mixed_pset_toc ) == buf_size_t{ 0 } );
    ASSERT_TRUE(  ::NS(BufferToc_total_num_elements)( mixed_pset_toc ) == buf_size_t{ 0 } );
    ASSERT_TRUE(  ::NS(BufferToc_types_begin)( mixed_pset_toc ) == nullptr );
    ASSERT_TRUE(  ::NS(BufferToc_types_end)( mixed_pset_toc ) == nullptr );
    ASSERT_TRUE( !::NS(BufferToc_has_type_elements)( mixed_pset_toc, ::NS(OBJECT_TYPE_PARTICLE) ) );
    ASSERT_TRUE(  ::NS(BufferToc_num_type_elements)( mixed_pset_toc, ::NS(OBJECT_TYPE_PARTICLE) )
                  == buf_size_t{ 0 } );

    ASSERT_TRUE( !::NS(BufferToc_is_compatible_with)( mixed_pset_toc, mixed_buffer ) );
    ASSERT_TRUE( ::NS(BufferToc_reset)( mixed_pset_toc, mixed_buffer ) != ::NS(ARCH_STATUS_SUCCESS) );

    ASSERT_TRUE(  ::NS(BufferToc_num_types)( mixed_pset_toc ) == buf_size_t{ 0 } );
    ASSERT_TRUE(  ::NS(BufferToc_total_num_elements)( mixed_pset_toc ) == buf_size_t{ 0 } );
    ASSERT_TRUE(  ::NS(BufferToc_types_begin)( mixed_pset_toc ) == nullptr );
    ASSERT_TRUE(  ::NS(BufferToc_types_end)( mixed_pset_toc ) == nullptr );
    ASSERT_TRUE( !::NS(BufferToc_has_type_elements)( mixed_pset_toc, ::NS(OBJECT_TYPE_PARTICLE) ) );
    ASSERT_TRUE(  ::NS(BufferToc_num_type_elements)( mixed_pset_toc, ::NS(OBJECT_TYPE_PARTICLE) )
                  == buf_size_t{ 0 } );

    ASSERT_TRUE( !::NS(BufferToc_is_compatible_with)( mixed_pset_toc, mixed_buffer ) );
    ASSERT_TRUE(  ::NS(BufferToc_are_not_equal)( mixed_pset_toc, mixed_buffer_toc ) );

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
        particle_set_t* pset = ::NS(Particles_new)( pset_buffer, npart );
        SIXTRL_ASSERT( pset != nullptr );

        cmp_begin_indices.push_back( cmp_total_num_particles );
        cmp_num_particles.push_back(
            ::NS(Particles_get_num_of_particles)( pset ) );

        cmp_total_num_particles += ::NS(Particles_get_num_of_particles)( pset );
        cmp_end_indices.push_back( cmp_total_num_particles );
    }

    ASSERT_TRUE( ::NS(Buffer_get_num_of_objects)( pset_buffer ) == NUM_PSETS );
    ASSERT_TRUE( ::NS(Buffer_is_particles_buffer)( pset_buffer ) );
    ASSERT_TRUE( ::NS(Particles_buffer_get_total_num_of_particles)( pset_buffer )
                 == cmp_total_num_particles );

    ASSERT_TRUE( ::NS(Particles_buffer_get_num_of_particle_blocks)( pset_buffer )
                 == NUM_PSETS );

    /* create a "general" buffer toc on the pset buffer -> should always work */

    base_buffer_toc_t* general_pset_buffer_toc =
        ::NS(BufferToc_new)( pset_buffer );

    ASSERT_TRUE( general_pset_buffer_toc != nullptr );
    ASSERT_TRUE( ::NS(BufferToc_has_types)( general_pset_buffer_toc ) );
    ASSERT_TRUE( ::NS(BufferToc_num_types)( general_pset_buffer_toc ) == buf_size_t{ 1 } );
    ASSERT_TRUE( ::NS(BufferToc_total_num_elements)( general_pset_buffer_toc ) == NUM_PSETS );

    ASSERT_TRUE( std::distance( ::NS(BufferToc_types_begin)( general_pset_buffer_toc ),
        ::NS(BufferToc_types_end)( general_pset_buffer_toc ) ) == std::ptridff_t{ 1 } );

    type_it  = ::NS(BufferToc_types_begin)( general_pset_buffer_toc );
    type_end = ::NS(BufferToc_types_end)( general_pset_buffer_toc );

    ASSERT_TRUE( type_end != nullptr );
    ASSERT_TRUE(  type_it != nullptr );
    ASSERT_TRUE( *type_it == ::NS(OBJECT_TYPE_PARTICLE) );

    ASSERT_TRUE( ::NS(BufferToc_has_type_elements)( general_pset_buffer_toc, *type_it ) );

    ASSERT_TRUE( ::NS(BufferToc_type_elements_indices_begin)( general_pset_buffer_toc, *type_it ) != nullptr );
    ASSERT_TRUE( ::NS(BufferToc_type_elements_indices_end)( general_pset_buffer_toc, *type_it ) != nullptr );

    ASSERT_TRUE( std::is_sorted(
        ::NS(BufferToc_type_elements_indices_begin)( general_pset_buffer_toc, *type_it ),
        ::NS(BufferToc_type_elements_indices_end)( general_pset_buffer_toc, *type_it ) ) );

    std::vector< buf_size_t > cmp_element_indices( NUM_PSETS, buf_size_t{ 0 } );

    std::iota( cmp_element_indices.begin(), cmp_element_indices.end(),
               buf_size_t{ 0 } );

    ASSERT_TRUE( std::equal(
        ::NS(BufferToc_type_elements_indices_begin)( general_pset_buffer_toc, *type_it ),
        ::NS(BufferToc_type_elements_indices_end)( general_pset_buffer_toc, *type_it ),
        cmp_element_indices.begin() ) );

    ASSERT_TRUE( ::NS(BufferToc_is_compatible_with)( general_pset_buffer_toc, pset_buffer ) );

    /* create a dedicated particle sets buffer toc on the pset buffer */

    ::NS(ParticleSetsBufferToc)* pset_toc =
        ::NS(ParticleSetsBufferToc_new)( pset_buffer );

    ASSERT_TRUE( pset_toc != nullptr );
    ASSERT_TRUE( ::NS(BufferToc_has_types)( pset_toc ) );
    ASSERT_TRUE( ::NS(BufferToc_num_types)( pset_toc ) == buf_size_t{ 1 } );
    ASSERT_TRUE( ::NS(BufferToc_total_num_elements)( pset_toc ) == NUM_PSETS );

    ASSERT_TRUE( std::distance( ::NS(BufferToc_types_begin)( pset_toc ),
        ::NS(BufferToc_types_end)( pset_toc ) ) == std::ptridff_t{ 1 } );

    type_it  = ::NS(BufferToc_types_begin)( pset_toc );
    type_end = ::NS(BufferToc_types_end)( pset_toc );

    ASSERT_TRUE( type_end != nullptr );
    ASSERT_TRUE(  type_it != nullptr );
    ASSERT_TRUE( *type_it == ::NS(OBJECT_TYPE_PARTICLE) );

    ASSERT_TRUE( ::NS(BufferToc_has_type_elements)( pset_toc, *type_it ) );
    ASSERT_TRUE( ::NS(BufferToc_type_elements_indices_begin)( pset_toc, *type_it ) != nullptr );
    ASSERT_TRUE( ::NS(BufferToc_type_elements_indices_end)( pset_toc, *type_it ) != nullptr );

    ASSERT_TRUE( std::is_sorted(
        ::NS(BufferToc_type_elements_indices_begin)( pset_toc, *type_it ),
        ::NS(BufferToc_type_elements_indices_end)( pset_toc, *type_it ) ) );

    ASSERT_TRUE( std::equal(
        ::NS(BufferToc_type_elements_indices_begin)( pset_toc, *type_it ),
        ::NS(BufferToc_type_elements_indices_end)( pset_toc, *type_it ),
        ::NS(BufferToc_type_elements_indices_begin)( general_pset_buffer_toc, *type_it ) );

    ASSERT_TRUE( ::NS(ParticleSetsBufferToc_total_num_particles)( pset_toc ) == cmp_total_num_particles );

    ASSERT_TRUE( ::NS(ParticleSetsBufferToc_num_particle_sets)( pset_toc ) == NUM_PSETS );
    ASSERT_TRUE( ::NS(ParticleSetsBufferToc_num_particles_in_sets_begin)( pset_toc ) != nullptr );
    ASSERT_TRUE( ::NS(ParticleSetsBufferToc_num_particles_in_sets_end)( pset_toc ) != nullptr );
    ASSERT_TRUE( std::distance( ::NS(ParticleSetsBufferToc_num_particles_in_sets_begin)( pset_toc ),
                                ::NS(ParticleSetsBufferToc_num_particles_in_sets_end)( pset_toc ) ) ==
        static_cast< std::ptrdiff_t >( NUM_PSETS ) );

    ASSERT_TRUE( std::equal( cmp_num_particles.begin(),
        cmp_num_particles.end(), ::NS(ParticleSetsBufferToc_num_particles_in_sets_begin)( pset_toc ) ) );


    ASSERT_TRUE( ::NS(ParticleSetsBufferToc_particle_set_begin_index_begin)( pset_toc ) != nullptr );
    ASSERT_TRUE( ::NS(ParticleSetsBufferToc_particle_set_begin_index_end)( pset_toc ) != nullptr );
    ASSERT_TRUE( std::distance( ::NS(ParticleSetsBufferToc_particle_set_begin_index_begin)( pset_toc ),
                                ::NS(ParticleSetsBufferToc_particle_set_begin_index_end)( pset_toc ) ) ==
        static_cast< std::ptrdiff_t >( NUM_PSETS ) );

    ASSERT_TRUE( std::equal( cmp_begin_indices.begin(),
        cmp_begin_indices.end(), ::NS(ParticleSetsBufferToc_particle_set_begin_index_begin)( pset_toc ) ) );


    ASSERT_TRUE( ::NS(ParticleSetsBufferToc_particle_set_end_index_begin)( pset_toc ) != nullptr );
    ASSERT_TRUE( ::NS(ParticleSetsBufferToc_particle_set_end_index_end)( pset_toc ) != nullptr );
    ASSERT_TRUE( std::distance( ::NS(ParticleSetsBufferToc_particle_set_end_index_begin)( pset_toc ),
                                ::NS(ParticleSetsBufferToc_particle_set_end_index_end)( pset_toc ) ) ==
        static_cast< std::ptrdiff_t >( NUM_PSETS ) );

    ASSERT_TRUE( std::equal( cmp_end_indices.begin(),
        cmp_end_indices.end(), ::NS(ParticleSetsBufferToc_particle_set_end_index_begin)( pset_toc ) ) );

    ASSERT_TRUE( ::NS(BufferToc_is_compatible_with)( pset_toc, pset_buffer ) );
    ASSERT_TRUE( ::NS(BufferToc_are_equal)( general_pset_buffer_toc, pset_toc ) );

    ::NS(BufferToc_delete)( mixed_buffer_toc );
    ::NS(BufferToc_delete)( general_pset_buffer_toc );

    ::NS(ParticleSetsBufferToc_delete)( mixed_pset_toc );
    ::NS(ParticleSetsBufferToc_deletE)( pset_toc );

    ::NS(Buffer_delete)( mixed_buffer );
    ::NS(Buffer_delete)( pset_buffer );
}
