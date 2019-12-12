#ifndef SIXTRACKLIB_COMMON_BUFFER_BUFFER_TOC_CXX_HPP__
#define SIXTRACKLIB_COMMON_BUFFER_BUFFER_TOC_CXX_HPP__

#if defined( __cplusplus ) && !defined( _GPUCODE )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cstddef>
    #include <cstdint>
    #include <cstdlib>
    #include <map>
    #include <type_traits>
    #include <unordered_map>
    #include <utility>
    #include <vector>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/particles/definitions.h"
    #include "sixtracklib/common/internal/beam_elements_defines.h"
    #include "sixtracklib/common/internal/objects_type_id.h"
    #include "sixtracklib/common/buffer.hpp"
    #include "sixtracklib/common/buffer.h"
    #include "sixtracklib/common/particles/particle_set_state.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    class BufferToc
    {
        public:

        using buffer_t   = SIXTRL_CXX_NAMESPACE::Buffer;
        using c_buffer_t = buffer_t::c_api_t;
        using size_type  = buffer_t::size_type;
        using type_id_t  = buffer_t::type_id_t;
        using status_t   = SIXTRL_CXX_NAMESPACE::arch_status_t;

        constexpr size_type ILLEGAL_ELEMENT_ID =
            size_type{ 0xffffffffffffffff };

        SIXTRL_HOST_FN BufferToc() = default;

        SIXTRL_HOST_FN explicit BufferToc(
            buffer_t const SIXTRL_RESTRICT_REF buffer );

        SIXTRL_HOST_FN explicit BufferToc(
            const c_buffer_t *const SIXTRL_RESTRICT buffer );

        SIXTRL_HOST_FN BufferToc( BufferToc&& toc ) = default;

        SIXTRL_HOST_FN BufferToc(
            BufferToc const& SIXTRL_RESTRICT_REF toc ) = default;

        SIXTRL_HOST_FN BufferToc& operator=(
            BufferToc const& SIXTRL_RESTRICT_REF toc ) = default;

        SIXTRL_HOST_FN BufferToc& operator=( BufferToc&& toc ) = default;

        SIXTRL_HOST_FN virtual ~BufferToc() = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool has_types() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN size_type num_types() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN type_id_t const* types_begin() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN type_id_t const* types_end() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type total_num_elements() const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool has_type_elements(
            type_id_t const type_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type num_type_elements(
            type_id_t const type_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type const* type_elements_indices_begin(
            type_id_t const type_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type const* type_elements_indices_end(
            type_id_t const type_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type type_element_index(
            type_id_t const type_id, size_type const id ) const;

        SIXTRL_HOST_FN size_type type_element_index_no_check(
            type_id_t const type_id, size_type const id ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t reset(
            buffer_t const& SIXTRL_RESTRICT_REF buffer );

        SIXTRL_HOST_FN status_t reset(
            const c_buffer_t *const SIXTRL_RESTRICT buffer );

        SIXTRL_HOST_FN void clear();

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool is_compatible_with(
            buffer_t const& SIXTRL_RESTRICT_REF buffer ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool is_compatible_with( const c_buffer_t *const
            SIXTRL_RESTRICT buffer ) const SIXTRL_NOEXCEPT;


        SIXTRL_HOST_FN friend bool operator==(
            BufferToc const& SIXTRL_RESTRICT_REF lhs,
            BufferToc const& SIXTRL_RESTRICT_REF rhs ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN friend bool operator!=(
            BufferToc const& SIXTRL_RESTRICT_REF lhs,
            BufferToc const& SIXTRL_RESTRICT_REF rhs ) SIXTRL_NOEXCEPT;

        protected:

        using indices_list_t  = std::vector< size_type >;
        using output_offset_list_t = std::vector< size_type >;
        using type_ids_list_t = std::vector< type_id_t >;
        using type_id_to_indices_map_t = std::map< type_id_t, indices_list_t >;
        using type_id_to_output_offset_map_t =
            std::map< type_id_t, output_offset_list_t >;

        SIXTRL_HOST_FN virtual void doClear();

        SIXTRL_HOST_FN virtual status_t doReset(
            const c_buffer_t *const SIXTRL_RESTRICT buffer );

        SIXTRL_HOST_FN virtual bool doCheckIsCompatibleWithBuffer(
            const c_buffer_t *const SIXTRL_RESTRICT buffer );

        private:

        SIXTRL_HOST_FN void doClearBaseImpl() SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t doResetBaseImpl(
            const c_buffer_t *const SIXTRL_RESTRICT buffer );

        type_id_to_indices_map_t        m_type_ids_to_indices_map;
        type_id_to_output_offset_map_t  m_type_ids_with_output_offset;
        type_ids_list_t                 m_stored_type_ids;
    };


    class OutputOffsetBufferToc : public SIXTRL_CXX_NAMESPACE::BufferToc
    {
        public:

        constexpr size_type ILLEGAL_OUTPUT_OFFSET =
            size_type{ 0xffffffffffffffff };

        SIXTRL_HOST_FN OutputOffsetBufferToc() = default;

        SIXTRL_HOST_FN explicit OutputOffsetBufferToc(
            buffer_t const SIXTRL_RESTRICT_REF buffer );

        SIXTRL_HOST_FN explicit OutputOffsetBufferToc(
            const c_buffer_t *const SIXTRL_RESTRICT buffer );

        SIXTRL_HOST_FN OutputOffsetBufferToc(
            OutputOffsetBufferToc&& toc ) = default;

        SIXTRL_HOST_FN OutputOffsetBufferToc(
            OutputOffsetBufferToc const& SIXTRL_RESTRICT_REF toc ) = default;

        SIXTRL_HOST_FN OutputOffsetBufferToc& operator=(
            BufferToc const& SIXTRL_RESTRICT_REF toc ) = default;

        SIXTRL_HOST_FN OutputOffsetBufferToc& operator=(
            OutputOffsetBufferToc&& toc ) = default;

        SIXTRL_HOST_FN virtual ~OutputOffsetBufferToc() = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool has_output_offset(
            type_id_t const type_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t enable_output_offset(
            type_id_t const type_id ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t disable_output_offset(
            type_id_t const type_id ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type num_output_offsets(
            type_id_t const type_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type const* output_offsets_begin(
            type_id_t const type_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type const* output_offsets_end(
            type_id_t const type_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type output_offset( type_id_t const type_id,
            size_type const index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type output_offset_by_buffer_index(
            type_id_t const type_id,
            size_type const buffer_index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t set_output_offset(
            type_id_t const type_id, size_type const index,
            size_type const output_offset ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t set_output_offset_by_buffer_index(
            type_id_t const type_id, size_type const buffer_index,
            size_type const output_offset ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN friend bool operator==(
            OutputOffsetBufferToc const& SIXTRL_RESTRICT_REF lhs,
            OutputOffsetBufferToc const& SIXTRL_RESTRICT_REF rhs
            ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN friend bool operator!=(
            OutputOffsetBufferToc const& SIXTRL_RESTRICT_REF lhs,
            OutputOffsetBufferToc const& SIXTRL_RESTRICT_REF rhs
            ) SIXTRL_NOEXCEPT;

        protected:

        using output_offset_list_t = std::vector< size_type >;
        using type_id_to_output_offset_map_t =
            std::map< type_id_t, output_offset_list_t >;

        SIXTRL_HOST_FN status_t doReset(
            const c_buffer_t *const SIXTRL_RESTRICT buffer ) override;

        SIXTRL_HOST_FN void doClear() override;

        private:

        SIXTRL_HOST_FN status_t doResetOutputOffset(
            const c_buffer_t *const SIXTRL_RESTRICT buffer );

        type_id_to_output_offset_map_t  m_type_ids_with_output_offset;
    };

    class ParticleSetsBufferToc : SIXTRL_CXX_NAMESPACE::BufferToc
    {
        public:

        using particle_set_state_t = ::NS(ParticleSetState);

        SIXTRL_HOST_FN ParticleSetsBufferToc() = default;

        SIXTRL_HOST_FN explicit ParticleSetsBufferToc(
            buffer_t const& SIXTRL_RESTRICT_REF buffer );

        SIXTRL_HOST_FN explicit ParticleSetsBufferToc(
            const c_buffer_t *const SIXTRL_RESTRICT buffer );

        SIXTRL_HOST_FN ParticleSetsBufferToc( ParticleSetsBufferToc&& toc ) = default;

        SIXTRL_HOST_FN ParticleSetsBufferToc(
            ParticleSetsBufferToc const& SIXTRL_RESTRICT_REF toc ) = default;

        SIXTRL_HOST_FN ParticleSetsBufferToc& operator=(
            ParticleSetsBufferToc const& SIXTRL_RESTRICT_REF toc ) = default;

        SIXTRL_HOST_FN ParticleSetsBufferToc& operator=(
            ParticleSetsBufferToc&& toc ) = default;

        SIXTRL_HOST_FN virtual ~ParticleSetsBufferToc() = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN size_type num_particle_sets() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type const*
            num_particles_in_sets_begin() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type const*
            num_particles_in_sets_end() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type const*
            particle_set_begin_index_begin() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type const*
            particle_set_begin_index_end() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type const*
            particle_set_end_index_begin() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type const*
            particle_set_end_index_end() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type particle_set_begin_index(
            size_type const pset_index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type particle_set_end_index(
            size_type const pset_index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type num_particles(
            size_type const pset_index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type total_num_particles() const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN friend bool operator==(
            ParticleSetsBufferToc const& SIXTRL_RESTRICT_REF lhs,
            ParticleSetsBufferToc const& SIXTRL_RESTRICT_REF rhs
        ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN friend bool operator!=(
            ParticleSetsBufferToc const& SIXTRL_RESTRICT_REF lhs,
            ParticleSetsBufferToc const& SIXTRL_RESTRICT_REF rhs
        ) SIXTRL_NOEXCEPT;

        protected:

        SIXTRL_HOST_FN status_t doReset(
            const c_buffer_t *const SIXTRL_RESTRICT buffer ) override;

        SIXTRL_HOST_FN void doClear() override;

        SIXTRL_HOST_FN bool doCheckIsCompatibleWithBuffer(
            const c_buffer_t *const SIXTRL_RESTRICT buffer ) override;

        private:

        SIXTRL_HOST_FN void doClearParticleSetsImpl() SIXTRL_NOEXCEPT;

        std::vector< size_type > m_num_particles_in_set;
        std::vector< size_type > m_begin_indices;
        std::vector< size_type > m_end_indices;

        size_type m_total_num_particles;
    };
}

#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )

extern "C" {

typedef SIXTRL_CXX_NAMESPACE::BufferToc NS(BufferToc);
typedef SIXTRL_CXX_NAMESPACE::OutputOffsetBufferToc NS(OutputOffsetBufferToc);
typedef SIXTRL_CXX_NAMESPACE::ParticleSetsBufferToc;

}

#else

struct NS(BufferToc);
struct NS(OutputOffsetBufferToc);
struct NS(ParticleSetsBufferToc);

#endif /* SIXTRACKLIB_COMMON_BUFFER_BUFFER_TOC_CXX_HPP__ */
