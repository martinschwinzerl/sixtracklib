#ifndef SIXTRACKLIB_SIXTRACKLIB_COMMON_INTERNAL_TRACK_JOB_BASE_H__
#define SIXTRACKLIB_SIXTRACKLIB_COMMON_INTERNAL_TRACK_JOB_BASE_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <algorithm>
        #include <cstddef>
        #include <cstdint>
        #include <cstdlib>
        #include <map>
        #include <memory>
        #include <string>
        #include <vector>
    #else /* !defined( __cplusplus ) */
        #include <stdbool.h>
        #include <stddef.h>
        #include <stdint.h>
        #include <stdlib.h>
    #endif /* !defined( __cplusplus ) */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/buffer/definitions.h"
    #include "sixtracklib/common/particles/definitions.h"
    #include "sixtracklib/common/track/definitions.h"

    #if defined( __cplusplus )
        #include "sixtracklib/common/buffer.hpp"
    #endif /* defined( __cplusplus ) */

    #include "sixtracklib/common/buffer.h"
    #include "sixtracklib/common/buffer/assign_address_item.hpp"
    #include "sixtracklib/common/buffer/buffer_store.hpp"
    #include "sixtracklib/common/buffer/buffer_toc.hpp"
    #include "sixtracklib/common/particles.h"
    #include "sixtracklib/common/particles/particles_addr.h"
    #include "sixtracklib/common/particles/particle_set_state.h"
    #include "sixtracklib/common/output/output_buffer.h"
    #include "sixtracklib/common/output/elem_by_elem_config.h"
    #include "sixtracklib/common/track/track_config.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

typedef struct NS(TrackJobDestSrcBufferIds)
{
    NS(buffer_size_t)   dest_buffer_id;
    NS(buffer_size_t)   src_buffer_id;
}
NS(TrackJobDestSrcBufferIds);

#if defined( __cplusplus ) && !defined( _GPUCODE )
}

namespace SIXTRL_CXX_NAMESPACE
{
    struct TrackJobDestSrcBufferIdsLessCmp
    {
        bool operator()(
            ::NS(TrackJobDestSrcBufferIds) const& SIXTRL_RESTRICT_REF lhs,
            ::NS(TrackJobDestSrcBufferIds) const& SIXTRL_RESTRICT_REF rhs
        ) const SIXTRL_NOEXCEPT
        {
            return ( ( lhs.dest_buffer_id < rhs.dest_buffer_id ) ||
                     ( ( lhs.dest_buffer_id == rhs.dest_buffer_id ) &&
                       ( lhs.src_buffer_id < rhs.src_buffer_id ) ) );
        }
    };

    /* ********************************************************************* */

    class TrackJobBufferStoreBase
    {
        public:

        using buffer_t     = SIXTRL_CXX_NAMESPACE::Buffer;
        using c_buffer_t   = buffer_t::c_api_t;
        using size_type    = buffer_t::size_type;
        using flags_t      = buffer_t::flags_t;
        using buffer_toc_t = SIXTRL_CXX_NAMESPACE::BufferToc;
        using store_buffer_toc_t = std::unique_ptr< buffer_toc_t >;

        static size_type constexpr DEFAULT_BUFFER_CAPACITY =
            buffer_t::DEFAULT_BUFFER_CAPACITY;

        static flags_t constexpr DEFAULT_DATASTORE_FLAGS =
            buffer_t::DEFAULT_DATASTORE_FLAGS;

        SIXTRL_HOST_FN explicit TrackJobBufferStoreBase(
            size_type const buffer_capacity = DEFAULT_BUFFER_CAPACITY,
            flags_t const buffer_flags = DEFAULT_DATASTORE_FLAGS );

        SIXTRL_HOST_FN explicit TrackJobBufferStoreBase(
            buffer_t* SIXTRL_RESTRICT cxx_buffer,
            bool const take_ownership = false );

        SIXTRL_HOST_FN explicit TrackJobBufferStoreBase(
            c_buffer_t* SIXTRL_RESTRICT c99_buffer,
            bool const take_ownership = false,
            bool const delete_ptr_after_move = true );

        SIXTRL_HOST_FN explicit TrackJobBufferStoreBase(
            std::unique_ptr< buffer_t >&& stored_ptr_buffer );

        SIXTRL_HOST_FN explicit TrackJobBufferStoreBase(
            buffer_t&& cxx_buffer );

        SIXTRL_HOST_FN TrackJobBufferStoreBase(
            TrackJobBufferStoreBase const& other );

        SIXTRL_HOST_FN TrackJobBufferStoreBase(
            TrackJobBufferStoreBase&& other ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN TrackJobBufferStoreBase& operator=(
            TrackJobBufferStoreBase const& rhs );

        SIXTRL_HOST_FN TrackJobBufferStoreBase& operator=(
            TrackJobBufferStoreBase&& other ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN ~TrackJobBufferStoreBase() = default;

        SIXTRL_HOST_FN bool active() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool owns_buffer() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN c_buffer_t const* ptr_buffer() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN c_buffer_t* ptr_buffer() SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN buffer_t const* ptr_cxx_buffer() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN buffer_t* ptr_cxx_buffer() SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void clear() SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void reset(
            buffer_t::size_type const buffer_capacity,
            buffer_t::flags_t const buffer_flags = DEFAULT_DATASTORE_FLAGS );

        SIXTRL_HOST_FN void reset(
            buffer_t* SIXTRL_RESTRICT cxx_buffer,
            bool const take_ownership = false );

        SIXTRL_HOST_FN void reset(
            c_buffer_t* SIXTRL_RESTRICT c99_buffer,
            bool const take_ownership = false,
            bool const delete_ptr_after_move = true );

        SIXTRL_HOST_FN void reset(
            std::unique_ptr< buffer_t >&& stored_ptr_buffer );

        SIXTRL_HOST_FN void reset( buffer_t&& cxx_buffer );

        SIXTRL_HOST_FN bool has_buffer_toc() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN buffer_toc_t const& table_of_contents() const;

        SIXTRL_HOST_FN buffer_toc_t const*
            ptr_table_of_contents() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t replace_table_of_contents(
            store_buffer_toc_t&& table_of_contents_to_store );

        private:

        buffer_t*                   m_ptr_cxx_buffer;
        c_buffer_t*                 m_ptr_c99_buffer;
        std::unique_ptr< buffer_t > m_own_buffer;
        store_buffer_toc_t          m_stored_buffer_toc;
    };

    class TrackJobBase
    {
        public:

        using buffer_t               = SIXTRL_CXX_NAMESPACE::Buffer;
        using buffer_toc_t           = SIXTRL_CXX_NAMESPACE::BufferToc;
        using c_buffer_t             = buffer_t::c_api_t;
        using elem_by_elem_config_t  = ::NS(ElemByElemConfig);
        using elem_by_elem_order_t   = ::NS(elem_by_elem_order_t);
        using particle_index_t       = ::NS(particle_index_t);
        using size_type              = SIXTRL_CXX_NAMESPACE::track_job_size_t;
        using arch_id_t              = SIXTRL_CXX_NAMESPACE::arch_id_t;
        using track_status_t         = SIXTRL_CXX_NAMESPACE::track_status_t;
        using status_t               = SIXTRL_CXX_NAMESPACE::arch_status_t;
        using assign_item_t          = SIXTRL_CXX_NAMESPACE::AssignAddressItem;
        using assign_item_key_t      = ::NS(TrackJobDestSrcBufferIds);
        using output_buffer_flag_t   = ::NS(output_buffer_flag_t);
        using object_type_id_t       = ::NS(object_type_id_t);
        using particles_addr_t       = ::NS(ParticlesAddr);
        using particle_set_state_t   = ::NS(ParticleSetState);

        using collect_flag_t = SIXTRL_CXX_NAMESPACE::track_job_collect_flag_t;
        using push_flag_t    = SIXTRL_CXX_NAMESPACE::track_job_push_flag_t;

        using config_id_t            = uint32_t;
        using track_kernel_config_t  = ::NS(TrackConfig);

        /* ----------------------------------------------------------------- */

        static constexpr size_type ILLEGAL_BUFFER_ID =
            SIXTRL_CXX_NAMESPACE::ARCH_ILLEGAL_BUFFER_ID;

        static constexpr config_id_t ILLEGAL_CONFIG_ID =
            config_id_t{ 0xffffffff };

        static constexpr size_type ILLEGAL_OUTPUT_BUFFER_OFFSET =
            size_type{ 0xffffffffffffffff };

        static constexpr particle_index_t ILLEGAL_UNTIL_TURN =
            particle_index_t{ -9223372036854775808 };

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN static bool IsCollectFlagSet(
            collect_flag_t const haystack,
            collect_flag_t const needle ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN static size_type
        DefaultNumParticleSetIndices() SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN static size_type const*
        DefaultParticleSetIndicesBegin() SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN static size_type const*
        DefaultParticleSetIndicesEnd() SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN void clear();

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN void collect();
        SIXTRL_HOST_FN void collect( collect_flag_t const flags );

        SIXTRL_HOST_FN void collect_particles();
        SIXTRL_HOST_FN void collect_beam_elements();
        SIXTRL_HOST_FN void collect_output();

        SIXTRL_HOST_FN void enable_collect_particles()  SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN void disable_collect_patricles() SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool is_collecting_particles() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void enable_collect_beam_elements()  SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN void disable_collect_beam_elements() SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool is_collecting_beam_elements() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void enable_collect_output()  SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN void disable_collect_output() SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool is_collecting_output() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN collect_flag_t collect_flags() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN void set_collect_flags(
            collect_flag_t const flag ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool requires_collecting() const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN void push( push_flag_t const flags );
        SIXTRL_HOST_FN void push_particles();
        SIXTRL_HOST_FN void push_beam_elements();
        SIXTRL_HOST_FN void push_output();

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN track_status_t track_until(
            size_type const until_turn );

        SIXTRL_HOST_FN track_status_t track_elem_by_elem(
            size_type const until_turn_elem_by_elem );

        SIXTRL_HOST_FN track_status_t track_line(
            size_type const beam_elements_begin_index,
            size_type const beam_elements_end_index,
            bool const finish_turn = false );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN virtual ~TrackJobBase() = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool reset(
            buffer_t& SIXTRL_RESTRICT_REF particles_buffer,
            buffer_t& SIXTRL_RESTRICT_REF beam_elements_buffer,
            buffer_t* SIXTRL_RESTRICT ptr_output_buffer   = nullptr,
            size_type const until_turn_elem_by_elem = size_type{ 0 } );

        SIXTRL_HOST_FN bool reset(
            buffer_t& SIXTRL_RESTRICT_REF particles_buffer,
            size_type const particle_set_index,
            buffer_t& SIXTRL_RESTRICT_REF beam_elements_buffer,
            buffer_t* SIXTRL_RESTRICT ptr_output_buffer = nullptr,
            size_type const until_turn_elem_by_elem = size_type{ 0 } );

        template< typename ParSetIndexIter  >
        SIXTRL_HOST_FN bool reset(
            buffer_t& SIXTRL_RESTRICT_REF particles_buffer,
            ParSetIndexIter  particle_set_indices_begin,
            ParSetIndexIter  particle_set_indices_end,
            buffer_t& SIXTRL_RESTRICT_REF beam_elements_buffer,
            buffer_t* SIXTRL_RESTRICT ptr_output_buffer = nullptr,
            size_type const until_turn_elem_by_elem = size_type{ 0 } );

        SIXTRL_HOST_FN bool reset(
            c_buffer_t* SIXTRL_RESTRICT particles_buffer,
            c_buffer_t* SIXTRL_RESTRICT beam_elements_buffer,
            c_buffer_t* SIXTRL_RESTRICT ptr_output_buffer = nullptr,
            size_type const until_turn_elem_by_elem = size_type{ 0 } );

        SIXTRL_HOST_FN bool reset(
            c_buffer_t* SIXTRL_RESTRICT particles_buffer,
            size_type const particle_set_index,
            c_buffer_t* SIXTRL_RESTRICT beam_elements_buffer,
            c_buffer_t* SIXTRL_RESTRICT ptr_output_buffer = nullptr,
            size_type const until_turn_elem_by_elem = size_type{ 0 } );

        SIXTRL_HOST_FN bool reset(
            c_buffer_t* SIXTRL_RESTRICT particles_buffer,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT particle_set_indices_begin,
            c_buffer_t* SIXTRL_RESTRICT beam_elements_buffer,
            c_buffer_t* SIXTRL_RESTRICT ptr_output_buffer = nullptr,
            size_type const until_turn_elem_by_elem = size_type{ 0 } );

        template< typename ParSetIndexIter  >
        SIXTRL_HOST_FN bool reset(
            c_buffer_t* SIXTRL_RESTRICT particles_buffer,
            ParSetIndexIter  particle_set_indices_begin,
            ParSetIndexIter  particle_set_indices_end,
            c_buffer_t* SIXTRL_RESTRICT beam_elements_buffer,
            c_buffer_t* SIXTRL_RESTRICT ptr_output_buffer = nullptr,
            size_type const until_turn_elem_by_elem = size_type{ 0 } );

        SIXTRL_HOST_FN bool select_particle_set(
            size_type const particle_set_index );

        SIXTRL_HOST_FN bool assign_output_buffer(
            buffer_t& SIXTRL_RESTRICT_REF output_buffer );

        SIXTRL_HOST_FN bool assign_output_buffer(
            c_buffer_t* SIXTRL_RESTRICT ptr_output_buffer );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN arch_id_t arch_id()              const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN std::string const& arch_str()    const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN char const* arch_cstr()          const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool has_node_id_str()           const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN std::string const& node_id_str() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN char const* node_id_cstr()       const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool has_config_str()            const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN std::string const& config_str()  const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN char const* config_cstr()        const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN size_type num_particle_sets() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type const*
        particle_set_indices_begin() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type const*
        particle_set_indices_end() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type particle_set_index( size_type const n ) const;

        SIXTRL_HOST_FN size_type const*
        num_particles_in_sets_begin() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type const*
        num_particles_in_sets_end() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type
        num_particles_in_set( size_type const n ) const;

        SIXTRL_HOST_FN size_type
        total_num_particles_in_sets() const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN particle_index_t min_particle_id() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN particle_index_t max_particle_id() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN particle_index_t min_element_id()  const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN particle_index_t max_element_id()  const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN particle_index_t
        min_initial_turn_id() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN particle_index_t
        max_initial_turn_id() const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN buffer_t& particles_cxx_buffer();
        SIXTRL_HOST_FN buffer_t const& particles_cxx_buffer() const;

        SIXTRL_HOST_FN buffer_t* ptr_particles_cxx_buffer() SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN buffer_t const*
            ptr_particles_cxx_buffer() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN c_buffer_t* particles_buffer() SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN c_buffer_t const*
            particles_buffer() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN buffer_toc_t const&
        particles_buffer_toc() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN buffer_toc_t const*
        ptr_particles_buffer_toc() const SIXTRL_NOEXCEPT;

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN buffer_t& beam_elements_cxx_buffer();
        SIXTRL_HOST_FN buffer_t const& beam_elements_cxx_buffer() const;

        SIXTRL_HOST_FN buffer_t*
            ptr_beam_elements_cxx_buffer() SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN buffer_t const*
            ptr_beam_elements_cxx_buffer() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN c_buffer_t* beam_elements_buffer() SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN c_buffer_t const*
            beam_elements_buffer() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN buffer_toc_t const&
        beam_elements_buffer_toc() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN buffer_toc_t const*
        ptr_beam_elements_buffer_toc() const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool can_fetch_particles_addr() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool has_particles_addr() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t fetch_particles_addr();
        SIXTRL_HOST_FN status_t clear_all_particles_addr();
        SIXTRL_HOST_FN status_t clear_particles_addr(
            size_type const index = size_type{ 0 } );

        SIXTRL_HOST_FN particles_addr_t const* particles_addr(
            size_type const index = size_type{ 0 } ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN buffer_t const*
        ptr_particles_addr_buffer() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN c_buffer_t const*
        ptr_particles_addr_cbuffer() const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN assign_item_t* add_assign_address_item(
            assign_item_t const& SIXTRL_RESTRICT_REF assign_item_to_add );

        SIXTRL_HOST_FN assign_item_t* add_assign_address_item(
            object_type_id_t const dest_type_id,
            size_type const dest_buffer_id,
            size_type const dest_elem_index,
            size_type const dest_pointer_offset,
            object_type_id_t const src_type_id,
            size_type const src_buffer_id,
            size_type const src_elem_index,
            size_type const src_pointer_offset );

        SIXTRL_HOST_FN status_t remove_assign_address_item(
            assign_item_key_t const& SIXTRL_RESTRICT_REF key,
            size_type const index_of_item_to_remove );

        SIXTRL_HOST_FN status_t remove_assign_address_item(
            assign_item_t const& SIXTRL_RESTRICT_REF item_to_remove );

        SIXTRL_HOST_FN bool has_assign_address_item( assign_item_t const&
            SIXTRL_RESTRICT_REF assign_item ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool has_assign_address_item(
            object_type_id_t const dest_type_id,
            size_type const dest_buffer_id,
            size_type const dest_elem_index,
            size_type const dest_pointer_offset,
            object_type_id_t const src_type_id,
            size_type const src_buffer_id,
            size_type const src_elem_index,
            size_type const src_pointer_offset ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type index_of_assign_address_item(
            object_type_id_t const dest_type_id,
            size_type const dest_buffer_id,
            size_type const dest_elem_index,
            size_type const dest_pointer_offset,
            object_type_id_t const src_type_id,
            size_type const src_buffer_id,
            size_type const src_elem_index,
            size_type const src_pointer_offset ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type index_of_assign_address_item(
            assign_item_t const& SIXTRL_RESTRICT_REF
                assign_item ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool has_assign_items(
            size_type const dest_buffer_id,
            size_type const src_buffer_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type num_assign_items(
            size_type const dest_buffer_id,
            size_type const src_buffer_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type total_num_assign_items() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN assign_item_t const* ptr_assign_address_item(
            assign_item_t const& SIXTRL_RESTRICT_REF
                assign_address_item ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN assign_item_t const* ptr_assign_address_item(
            size_type const dest_buffer_id,  size_type const src_buffer_id,
            size_type const assign_item_index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN assign_item_t const* ptr_assign_address_item(
            object_type_id_t const dest_type_id,
            size_type const dest_buffer_id,
            size_type const dest_elem_index,
            size_type const dest_pointer_offset,
            object_type_id_t const src_type_id,
            size_type const src_buffer_id,
            size_type const src_elem_index,
            size_type const src_pointer_offset ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type
            num_distinct_available_assign_address_items_dest_src_pairs() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type available_assign_address_items_dest_src_pairs(
            size_type const max_num_pairs,
            assign_item_key_t* pairs_begin ) const SIXTRL_NOEXCEPT;

        template< typename PairIter >
        SIXTRL_HOST_FN size_type available_assign_address_items_dest_src_pairs(
            PairIter pairs_begin, PairIter pairs_end ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN c_buffer_t* buffer_by_buffer_id(
            size_type const buffer_id ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN c_buffer_t const* buffer_by_buffer_id(
            size_type const buffer_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool is_buffer_by_buffer_id(
            size_type const buffer_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool is_raw_memory_by_buffer_id(
            size_type const buffer_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const*
        assign_items_begin( size_type const dest_buffer_id,
            size_type const src_buffer_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const*
        assign_items_end( size_type const dest_buffer_id,
            size_type const src_buffer_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN assign_item_key_t const*
        assign_item_dest_src_begin() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN assign_item_key_t const*
        assign_item_dest_src_end() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t commit_address_assignments();

        SIXTRL_HOST_FN status_t assign_all_addresses();
        SIXTRL_HOST_FN status_t assign_addresses(
            size_type const dest_buffer_id, size_type const src_buffer_id );

        /* ---------------------------------------------------------------- */

        SIXTRL_HOST_FN size_type
        stored_buffers_capacity() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t reserve_stored_buffers_capacity(
            size_type const capacity );

        SIXTRL_HOST_FN bool has_stored_buffers() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type
            num_stored_buffers() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type
            min_stored_buffer_id() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type
            max_stored_buffer_id() const SIXTRL_NOEXCEPT;

        template< typename... Args >
        SIXTRL_HOST_FN size_type add_stored_buffer( Args&&... args );

        SIXTRL_HOST_FN bool owns_stored_buffer(
            size_type const buffer_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t remove_stored_buffer(
            size_type const buffer_index );

        SIXTRL_HOST_FN buffer_t& stored_cxx_buffer(
            size_type const buffer_id );

        SIXTRL_HOST_FN buffer_t const& stored_cxx_buffer(
            size_type const buffer_id ) const;

        SIXTRL_HOST_FN buffer_t* ptr_stored_cxx_buffer(
            size_type const buffer_id ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN buffer_t const* ptr_stored_cxx_buffer(
            size_type const buffer_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN c_buffer_t* ptr_stored_buffer(
            size_type const buffer_id ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN c_buffer_t const* ptr_stored_buffer(
            size_type const buffer_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t push_stored_buffer(
            size_type const buffer_id );

        SIXTRL_HOST_FN status_t collect_stored_buffer(
            size_type const buffer_id );

        /* ---------------------------------------------------------------- */

        SIXTRL_HOST_FN bool has_output_buffer()       const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool owns_output_buffer()      const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN c_buffer_t* output_buffer() SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN c_buffer_t const* output_buffer() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN buffer_t* ptr_output_cxx_buffer() SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN buffer_t* ptr_output_cxx_buffer() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN buffer_t const& output_cxx_buffer() const;
        SIXTRL_HOST_FN buffer_t& output_cxx_buffer();

        SIXTRL_HOST_FN buffer_toc_t const&
            output_buffer_toc() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN buffer_toc_t const*
            ptr_output_buffer_toc() const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool has_config_buffer() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool has_config_entry(
            config_id_t const entry_idx ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN c_buffer_t const* config_buffer() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN c_buffer_t* config_buffer() SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN buffer_t const*
            ptr_config_cxx_buffer() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN buffer_t* ptr_config_cxx_buffer() SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN buffer_t const& config_cxx_buffer() const;
        SIXTRL_HOST_FN buffer_t& config_cxx_buffer();

        SIXTRL_HOST_FN buffer_toc_t const&
            config_buffer_toc() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN buffer_toc_t const*
            ptr_config_buffer_toc() const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool has_beam_monitors()       const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool has_beam_monitor_output() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN size_type num_beam_monitors()  const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type const*
            beam_monitor_indices_begin() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type const*
            beam_monitor_indices_end() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type const*
            beam_monitor_output_offsets_begin() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type const*
            beam_monitor_output_offsets_end() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type beam_monitor_index(
            size_type const idx ) const;

        SIXTRL_HOST_FN size_type min_beam_monitor_output_offset() const;
        SIXTRL_HOST_FN size_type max_beam_monitor_output_offset() const;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool has_elem_by_elem_configs() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool has_elem_by_elem_output() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type
            num_elem_by_elem_configs() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN config_id_t const*
            elem_by_elem_config_ids_begin() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN config_id_t const*
            elem_by_elem_config_ids_end() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type const*
            elem_by_elem_output_offsets_begin() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type const*
            elem_by_elem_output_offsets_end() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN config_id_t elem_by_elem_config_id(
            size_type const idx ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN elem_by_elem_config_t const* elem_by_elem_config_by_id(
            config_id_t const elem_by_elem_conf_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN elem_by_elem_config_t* elem_by_elem_config_by_id(
            config_id_t const elem_by_elem_conf_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN particle_index_t until_turn_elem_by_elem_by_id(
            config_id_t const elem_by_elem_conf_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type num_elem_by_elem_turns_by_id(
            config_id_t const elem_by_elem_conf_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type elem_by_elem_output_offset_by_id(
            config_id_t const elem_by_elem_conf_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool
            default_is_elem_by_elem_config_rolling() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void set_default_elem_by_elem_rolling(
            bool is_rolling ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN elem_by_elem_order_t
            default_elem_by_elem_config_order() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void set_default_elem_by_elem_config_order(
            elem_by_elem_order_t const elem_by_elem_order ) SIXTRL_NOEXCEPT;

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN elem_by_elem_config_t const*
            elem_by_elem_config() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN elem_by_elem_config_t*
            elem_by_elem_config() SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type
            elem_by_elem_output_offset() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN particle_index_t
            until_turn_elem_by_elem() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type num_elem_by_elem_turns() const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool debugMode() const SIXTRL_NOEXCEPT;

        protected:

        using base_buffer_store_t = SIXTRL_CXX_NAMESPACE::BufferStoreBase;
        using ptr_buffer_t        = std::unique_ptr< buffer_t >;
        using ptr_buffer_store_t  = std::unique_ptr< base_buffer_store_t >;
        using ptr_buffer_toc_t    = std::unique_ptr< buffer_toc_t >;

        using out_offset_buffer_toc_t =
            SIXTRL_CXX_NAMESPACE::OutputOffsetBufferToc;

        using particle_sets_buffer_toc_t =
            SIXTRL_CXX_NAMESPACE::ParticleSetsBufferToc;

        /* ----------------------------------------------------------------- */

        SIXTRL_STATIC SIXTRL_HOST_FN void COPY_PTR_BUFFER(
            ptr_buffer_t& SIXTRL_RESTRICT_REF dest_ptr_buffer,
            ptr_buffer_t const& SIXTRL_RESTRICT_REF src_ptr_buffer );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN static collect_flag_t UnsetCollectFlag(
            collect_flag_t const haystack,
            collect_flag_t const needle ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN TrackJobBase(
            const char *const SIXTRL_RESTRICT type_str,
            arch_id_t const type_id );

        SIXTRL_HOST_FN TrackJobBase( TrackJobBase const& other );
        SIXTRL_HOST_FN TrackJobBase( TrackJobBase&& other ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN TrackJobBase& operator=(
            TrackJobBase const& rhs );

        SIXTRL_HOST_FN TrackJobBase& operator=(
            TrackJobBase&& rhs ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN virtual void doClear();

        SIXTRL_HOST_FN virtual void doCollect( collect_flag_t const flags );
        SIXTRL_HOST_FN virtual void doPush( push_flag_t const flags );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN virtual status_t doPrepareConfigStructures();

        SIXTRL_HOST_FN virtual bool doPrepareParticlesStructures(
            c_buffer_t* SIXTRL_RESTRICT ptr_particles_buffer );

        SIXTRL_HOST_FN virtual bool doPrepareBeamElementsStructures(
            c_buffer_t* SIXTRL_RESTRICT ptr_beam_elem_buffer );

        SIXTRL_HOST_FN virtual bool doPrepareOutputStructures(
            c_buffer_t* SIXTRL_RESTRICT particles_buffer,
            c_buffer_t* SIXTRL_RESTRICT beam_elem_buffer,
            c_buffer_t* SIXTRL_RESTRICT ptr_output_buffer,
            size_type const until_turn_elem_by_elem );

        SIXTRL_HOST_FN virtual bool doAssignOutputBufferToBeamMonitors(
            c_buffer_t* SIXTRL_RESTRICT beam_elem_buffer,
            c_buffer_t* SIXTRL_RESTRICT output_buffer,
            particle_index_t const min_turn_id,
            size_type const output_buffer_offset_index );

        SIXTRL_HOST_FN virtual bool doAssignOutputBufferToElemByElemConfig(
            elem_by_elem_config_t* SIXTRL_RESTRICT elem_by_elem_config,
            c_buffer_t* SIXTRL_RESTRICT output_buffer,
            size_type const output_buffer_offset_index );

        SIXTRL_HOST_FN virtual bool doReset(
            c_buffer_t* SIXTRL_RESTRICT particles_buffer,
            c_buffer_t* SIXTRL_RESTRICT beam_elem_buffer,
            c_buffer_t* SIXTRL_RESTRICT ptr_output_buffer,
            size_type const until_turn_elem_by_elem );

        SIXTRL_HOST_FN virtual bool doAssignNewOutputBuffer(
            c_buffer_t* SIXTRL_RESTRICT ptr_output_buffer );

        SIXTRL_HOST_FN virtual size_type doAddStoredBuffer(
            buffer_store_t&& assigned_buffer_handle );

        SIXTRL_HOST_FN virtual status_t doRemoveStoredBuffer(
            size_type const buffer_id );

        SIXTRL_HOST_FN virtual status_t doPushStoredBuffer(
            size_type const buffer_id );

        SIXTRL_HOST_FN virtual status_t doCollectStoredBuffer(
            size_type const buffer_id );

        SIXTRL_HOST_FN virtual status_t doAddAssignAddressItem(
            assign_item_t const& SIXTRL_RESTRICT_REF assign_item,
            size_type* SIXTRL_RESTRICT ptr_item_index );

        SIXTRL_HOST_FN virtual status_t doRemoveAssignAddressItem(
            assign_item_key_t const& SIXTRL_RESTRICT_REF assign_item_key,
            size_type const index_of_item_to_remove );

        SIXTRL_HOST_FN virtual status_t doPerformAddressAssignments(
            assign_item_key_t const& SIXTRL_RESTRICT_REF assign_item_key );

        SIXTRL_HOST_FN virtual status_t doCommitAddressAssignments();

        SIXTRL_HOST_FN virtual status_t doRebuildAssignItemsBufferArg();

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN virtual track_status_t doTrackUntilTurn(
            size_type const until_turn );

        SIXTRL_HOST_FN virtual track_status_t doTrackElemByElem(
            size_type const until_turn_elem_by_elem );

        SIXTRL_HOST_FN virtual track_status_t doTrackLine(
            size_type const beam_elements_begin_index,
            size_type const beam_elements_end_index, bool const finish_turn );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN virtual void doParseConfigStr(
            const char *const SIXTRL_RESTRICT config_str );

        SIXTRL_HOST_FN void doSetDeviceIdStr(
            const char *const SIXTRL_RESTRICT device_id_str );

        SIXTRL_HOST_FN void doSetConfigStr(
            const char *const SIXTRL_RESTRICT config_str );

        SIXTRL_HOST_FN void doSetPtrParticleBuffer(
            buffer_t* SIXTRL_RESTRICT ptr_buffer ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doSetPtrBeamElementsBuffer(
            buffer_t* SIXTRL_RESTRICT ptr_buffer ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doSetPtrOutputBuffer(
            buffer_t* SIXTRL_RESTRICT ptr_buffer ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doSetPtrCParticleBuffer(
            c_buffer_t* SIXTRL_RESTRICT ptr_buffer ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doSetPtrCBeamElementsBuffer(
            c_buffer_t* SIXTRL_RESTRICT ptr_buffer ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doSetPtrCOutputBuffer(
            c_buffer_t* SIXTRL_RESTRICT ptr_buffer ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doSetBeamMonitorOutputBufferOffset(
            size_type const output_buffer_offset ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doSetElemByElemOutputIndexOffset(
            size_type const target_num_output_turns ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doSetUntilTurnElemByElem(
            particle_index_t const until_turn_elem_by_elem ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doSetRequiresCollectFlag(
            bool const requires_collect_flag ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doSetBeamMonitorOutputEnabledFlag(
            bool const beam_monitor_flag ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doSetElemByElemOutputEnabledFlag(
            bool const elem_by_elem_flag ) SIXTRL_NOEXCEPT;

        template< typename Iter >
        SIXTRL_HOST_FN void doSetParticleSetIndices( Iter begin, Iter end,
            const c_buffer_t *const SIXTRL_RESTRICT pbuffer = nullptr );

        SIXTRL_HOST_FN void doInitDefaultParticleSetIndices();

        template< typename BeMonitorIndexIter >
        SIXTRL_HOST_FN void doSetBeamMonitorIndices(
            BeMonitorIndexIter begin, BeMonitorIndexIter end );

        SIXTRL_HOST_FN void doInitDefaultBeamMonitorIndices();

        SIXTRL_HOST_FN void doSetMinParticleId(
            particle_index_t const min_particle_id ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doSetMaxParticleId(
            particle_index_t const max_particle_id ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doSetMinElementId(
            particle_index_t const min_element_id ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doSetMaxElementId(
            particle_index_t const max_element_id ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doSetMinInitialTurnId(
            particle_index_t const min_initial_turn_id ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doSetMaxInitialTurnId(
            particle_index_t const max_initial_turn_id ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doUpdateStoredOutputBuffer(
            ptr_buffer_t&& ptr_output_buffer ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doUpdateStoredParticlesAddrBuffer(
            ptr_buffer_t&& ptr_particles_addr_buffer ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN buffer_store_t* doGetPtrBufferStore(
            size_type const buffer_id ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN buffer_store_t const* doGetPtrBufferStore(
            size_type const buffer_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type doGetStoredBufferSize() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type doFindAssingAddressItem( assign_item_t const&
            SIXTRL_RESTRICT_REF item_to_search ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN assign_item_t const* doGetAssignAddressItem(
            assign_item_key_t const& SIXTRL_RESTRICT_REF key,
            size_type const item_index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN assign_item_t* doGetAssignAddressItem(
            assign_item_key_t const& SIXTRL_RESTRICT_REF key,
            size_type const item_index ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN c_buffer_t* doGetPtrAssignAddressItemsBuffer(
            assign_item_key_t const& SIXTRL_RESTRICT_REF key ) SIXTRL_NOEXCEPT;


        private:

        using assing_item_map_t = std::map< assign_item_key_t, buffer_t,
            SIXTRL_CXX_NAMESPACE::TrackJobDestSrcBufferIdsLessCmp >;
        using assign_item_keys_list_t = std::vector< assign_item_key_t >;

        SIXTRL_HOST_FN void doClearBaseImpl() SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doParseConfigStrBaseImpl(
            const char *const SIXTRL_RESTRICT config_str );

        SIXTRL_HOST_FN status_t doPrepareConfigStructuresBaseImpl();

        SIXTRL_HOST_FN void doUpdateStoredConfigBuffer(
            ptr_buffer_t&& ptr_config_buffer ) SIXTRL_NOEXCEPT;

        particle_set_state_t              m_initial_particle_set_state;
        particle_set_state_t              m_particle_set_state;

        assing_item_map_t                 m_assign_address_items;
        assign_item_keys_list_t           m_assign_item_keys;

        std::vector< ptr_buffer_store_t > m_stored_buffers;
        std::vector< ptr_buffer_toc_t >   m_stored_buffer_tocs;
        std::vector< size_type >          m_selected_pset_indices;

        std::string                       m_arch_str;
        std::string                       m_node_id_str;
        std::string                       m_config_str;

        size_type                         m_beam_elements_buffer_id;
        size_type                         m_particle_sets_buffer_id;
        size_type                         m_output_buffer_id;
        size_type                         m_config_buffer_id;
        size_type                         m_assign_address_items_buffer_id;
        size_type                         m_particle_sets_addr_buffer_id;
        size_type                         m_particle_sets_state_buffer_id;
        size_type                         m_particle_sets_statistics_buffer_id;

        size_type                         m_total_num_particles_in_sets;
        size_type                         m_num_stored_buffers;

        type_t                            m_arch_id;
        elem_by_elem_order_t              m_default_elem_by_elem_order;

        collect_flag_t                    m_collect_flags;
        bool                              m_requires_collect;
        bool                              m_default_elem_by_elem_rolling;
    };
}

typedef SIXTRL_CXX_NAMESPACE::TrackJobBase NS(TrackJobBase);

#else /* defined( __cplusplus ) && !defined( _GPUCODE ) */

typedef void NS(TrackJobBase);

#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if !defined( _GPUCODE )
#if defined( __cplusplus )

/* ------------------------------------------------------------------------- */
/* ---- implementation of inline and template C++ methods/functions     ---- */
/* ------------------------------------------------------------------------- */

namespace SIXTRL_CXX_NAMESPACE
{
    template< typename ParSetIndexIter  >
    SIXTRL_HOST_FN bool TrackJobBase::reset(
        TrackJobBase::buffer_t& SIXTRL_RESTRICT_REF particles_buffer,
        ParSetIndexIter  particle_set_indices_begin,
        ParSetIndexIter  particle_set_indices_end,
        TrackJobBase::buffer_t& SIXTRL_RESTRICT_REF beam_elements_buffer,
        buffer_t* SIXTRL_RESTRICT ptr_output_buffer,
        size_type const until_turn_elem_by_elem )
    {
        using c_buffer_t = TrackJobBase::c_buffer_t;

        bool success = false;

        this->doClear();

        c_buffer_t* ptr_pb  = particles_buffer.getCApiPtr();
        c_buffer_t* ptr_eb  = beam_elements_buffer.getCApiPtr();
        c_buffer_t* ptr_out = ( ptr_output_buffer != nullptr )
            ? ptr_output_buffer->getCApiPtr() : nullptr;

        if( ( particle_set_indices_begin !=
              particle_set_indices_end ) &&
            ( std::distance( particle_set_indices_begin,
                particle_set_indices_end ) > std::ptrdiff_t{ 0 } ) )
        {
            this->doSetParticleSetIndices(
                particle_set_indices_begin, particle_set_indices_end, ptr_pb );
        }
        else
        {
            this->doInitDefaultBeamMonitorIndices();
        }

        success = this->doReset(
            ptr_pb, ptr_eb, ptr_out, until_turn_elem_by_elem );

        if( success )
        {
            this->doSetPtrParticleBuffer( &particles_buffer );
            this->doSetPtrBeamElementsBuffer( &beam_elements_buffer );

            if( ( ptr_out != nullptr ) && ( this->has_output_buffer() ) )
            {
                this->doSetPtrOutputBuffer( ptr_output_buffer );
            }
        }

        return success;
    }

    template< typename ParSetIndexIter  >
    SIXTRL_HOST_FN bool TrackJobBase::reset(
        TrackJobBase::c_buffer_t* SIXTRL_RESTRICT particles_buffer,
        ParSetIndexIter  particle_set_indices_begin,
        ParSetIndexIter  particle_set_indices_end,
        TrackJobBase::c_buffer_t* SIXTRL_RESTRICT beam_elements_buffer,
        TrackJobBase::c_buffer_t* SIXTRL_RESTRICT ptr_output_buffer,
        TrackJobBase::size_type const until_turn_elem_by_elem )
    {
        this->doClear();

        if( ( particle_set_indices_begin !=
              particle_set_indices_end ) &&
            ( std::distance( particle_set_indices_begin,
                particle_set_indices_end ) > std::ptrdiff_t{ 0 } ) )
        {
            this->doSetParticleSetIndices( particle_set_indices_begin,
                particle_set_indices_end, particles_buffer );
        }
        else
        {
            this->doInitDefaultBeamMonitorIndices();
        }

        bool success = this->doReset( particles_buffer, beam_elements_buffer,
            ptr_output_buffer, until_turn_elem_by_elem );

        /*
        if( success )
        {
            this->doSetPtrCParticleBuffer( particles_buffer );
            this->doSetPtrCBeamElementsBuffer( beam_elements_buffer );
        }
        */

        return success;
    }

    template< typename... Args >
    TrackJobBase::size_type TrackJobBase::add_stored_buffer( Args&&... args )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::TrackJobBase;

        _this_t::buffer_store_t temp_buffer_store(
            std::forward< Args >( args )... );

        _this_t::size_type const buffer_id =
            this->doAddStoredBuffer( std::move( temp_buffer_store ) );

        return buffer_id;
    }

    template< typename PairIter >
    SIXTRL_HOST_FN TrackJobBase::size_type
    TrackJobBase::available_assign_address_items_dest_src_pairs(
        PairIter out_it, PairIter out_end ) const SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::TrackJobBase;
        using size_t = _this_t::size_type;
        size_t num_pairs = size_t{ 0 };

        if( !this->m_assign_address_items.empty() )
        {
            SIXTRL_ASSERT( this->m_assign_address_items.size() ==
                           this->m_assign_item_keys.size() );

            auto it = this->m_assign_item_keys.begin();
            auto end = this->m_assign_item_keys.end();

            while( ( out_it != out_end ) && ( it != end ) )
            {
                *out_it = *it;
                ++num_pairs;
                ++out_it;
                ++it;
            }
        }

        std::fill( out_it, out_end, _this_t::assign_item_key_t{
            _this_t::ILLEGAL_BUFFER_ID, _this_t::ILLEGAL_BUFFER_ID } );

        return num_pairs;
    }

    template< typename ParSetIndexIter >
    SIXTRL_HOST_FN void TrackJobBase::doSetParticleSetIndices(
        ParSetIndexIter begin, ParSetIndexIter end,
        const TrackJobBase::c_buffer_t *const SIXTRL_RESTRICT pbuffer )
    {
        using diff_t   = std::ptrdiff_t;
        using size_t   = TrackJobBase::size_type;
        using obj_it_t = SIXTRL_BUFFER_DATAPTR_DEC ::NS(Object) const*;
        using nparticles_t = ::NS(particle_num_elements_t);

        diff_t const temp_len = std::distance( begin, end );

        if( temp_len >= diff_t{ 0 } )
        {
            size_t total_num_particles_in_sets = size_t{ 0 };
            this->m_particle_set_indices.clear();
            this->m_num_particles_in_sets.clear();

            if( temp_len > diff_t{ 0 } )
            {
                this->m_particle_set_indices.clear();
                this->m_particle_set_indices.reserve(
                    static_cast< size_t >( temp_len ) );

                if( pbuffer == nullptr )
                {
                    this->m_particle_set_indices.assign( begin, end );
                }
                else
                {
                    size_t const SETS_IN_BUFFER =
                        ::NS(Buffer_get_num_of_objects)( pbuffer );

                    obj_it_t obj = nullptr;

                    for( ParSetIndexIter it = begin ; it != end ; ++it )
                    {
                        obj = ::NS(Buffer_get_const_object)( pbuffer, *it );

                        if( ( *it < SETS_IN_BUFFER ) && ( obj != nullptr ) &&
                            ( ::NS(Object_get_type_id)( obj ) ==
                                ::NS(OBJECT_TYPE_PARTICLE) ) )
                        {
                            this->m_particle_set_indices.push_back( *it );
                        }
                    }
                }

                std::sort( this->m_particle_set_indices.begin(),
                           this->m_particle_set_indices.end() );

                this->m_particle_set_indices.erase( std::unique(
                    this->m_particle_set_indices.begin(),
                    this->m_particle_set_indices.end() ),
                    this->m_particle_set_indices.end() );

                if( !this->m_particle_set_indices.empty() )
                {
                    for( auto const pset_idx : this->m_particle_set_indices )
                    {
                        auto pset = ::NS(Particles_buffer_get_const_particles)(
                            pbuffer, pset_idx );

                        SIXTRL_ASSERT( pset != nullptr );

                        nparticles_t const nparticles =
                            ::NS(Particles_get_num_of_particles)( pset );

                        SIXTRL_ASSERT( nparticles >= nparticles_t{ 0 } );

                        this->m_num_particles_in_sets.push_back( nparticles );
                        total_num_particles_in_sets += nparticles;
                    }

                    SIXTRL_ASSERT( this->m_num_particles_in_sets.size() ==
                                   this->m_particle_set_indices.size() );

                    this->m_total_num_particles_in_sets =
                        total_num_particles_in_sets;
                }
            }
        }

        return;
    }

    template< typename BeMonitorIndexIter >
    SIXTRL_HOST_FN void TrackJobBase::doSetBeamMonitorIndices(
        BeMonitorIndexIter begin, BeMonitorIndexIter end )
    {
        using diff_t = std::ptrdiff_t;
        using size_t = TrackJobBase::size_type;

        diff_t const temp_len = std::distance( begin, end );

        if( temp_len >= diff_t{ 0 } )
        {
            this->m_beam_monitor_indices.clear();

            if( temp_len > diff_t{ 0 } )
            {
                this->m_beam_monitor_indices.reserve(
                    static_cast< size_t >( temp_len ) );

                this->m_beam_monitor_indices.assign( begin, end );

                std::sort( this->m_beam_monitor_indices.begin(),
                           this->m_beam_monitor_indices.end() );

                this->m_beam_monitor_indices.erase( std::unique(
                    this->m_beam_monitor_indices.begin(),
                    this->m_beam_monitor_indices.end() ),
                    this->m_beam_monitor_indices.end() );
            }
        }

        return;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool TrackJobBase::IsCollectFlagSet(
        TrackJobBase::collect_flag_t const flag_set,
        TrackJobBase::collect_flag_t const flag ) SIXTRL_NOEXCEPT
    {
        return ( ( flag_set & flag ) == flag );
    }

    SIXTRL_INLINE TrackJobBase::collect_flag_t
    TrackJobBase::UnsetCollectFlag(
        TrackJobBase::collect_flag_t const flag_set,
        TrackJobBase::collect_flag_t const flag ) SIXTRL_NOEXCEPT
    {
        return flag_set & ~flag;
    }
}

#endif /* defined( __cplusplus ) */


#endif /* !defined( _GPUCODE ) */

#endif /* SIXTRACKLIB_SIXTRACKLIB_COMMON_INTERNAL_TRACK_JOB_BASE_H__ */
/*end: sixtracklib/common/internal/track_job_base.h */
