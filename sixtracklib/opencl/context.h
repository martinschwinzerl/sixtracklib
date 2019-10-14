#ifndef SIXTRACKLIB_OPENCL_CONTEXT_H__
#define SIXTRACKLIB_OPENCL_CONTEXT_H__

#if !defined( __CUDACC__ )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdbool.h>
    #include <stddef.h>
    #include <stdint.h>
    #include <stdlib.h>
    #include <limits.h>

    #if defined( __cplusplus )
        #include <algorithm>
    #endif /* !defined( __cplusplus ) */

#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/particles/definitions.h"
    #include "sixtracklib/common/track/definitions.h"
    #include "sixtracklib/common/buffer.h"
    #include "sixtracklib/common/particles.h"

    #include "sixtracklib/opencl/cl.h"
    #include "sixtracklib/opencl/internal/base_context.h"
    #include "sixtracklib/opencl/argument.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )

namespace SIXTRL_CXX_NAMESPACE
{
    class ClContext : public ClContextBase
    {
        private:

        using _base_context_t   = ClContextBase;

        public:

        using  program_id_t     = _base_context_t::program_id_t;
        using  kernel_id_t      = _base_context_t::kernel_id_t;
        using  cl_buffer_t      = cl::Buffer;
        using  num_turns_t      = ::NS(particle_index_t);
        using  track_status_t   = SIXTRL_CXX_NAMESPACE::track_status_t;

        explicit ClContext(
            const char *const SIXTRL_RESTRICT config_str = nullptr );

        explicit ClContext( size_type const node_index,
            const char *const SIXTRL_RESTRICT config_str = nullptr );

        explicit ClContext( node_id_t const node_id,
            const char *const SIXTRL_RESTRICT config_str = nullptr );

        explicit ClContext( char const* node_id_str,
            const char *const SIXTRL_RESTRICT config_str = nullptr );

        ClContext( platform_id_t const platform_idx,
                   device_id_t const device_idx,
                   const char *const SIXTRL_RESTRICT config_str = nullptr );

        ClContext( ClContext const& other ) = delete;
        ClContext( ClContext&& other ) = delete;

        ClContext& operator=( ClContext const& other ) = delete;
        ClContext& operator=( ClContext&& other ) = delete;

        virtual ~ClContext() SIXTRL_NOEXCEPT;

        /* ================================================================= */

        bool set_particle_buffer_arg( ClArgument& SIXTRL_RESTRICT_REF arg );
        bool set_particle_set_index_arg( size_type const particle_set_index );
        bool set_beam_elements_buffer_arg( ClArgument& SIXTRL_RESTRICT_REF arg );
        bool set_output_buffer_arg( ClArgument& SIXTRL_RESTRICT_REF arg );
        bool set_particle_addr_buffer_arg( ClArgument& SIXTRL_RESTRICT_REF arg );

        bool set_elem_by_elem_config_arg(
            cl_buffer_t& SIXTRL_RESTRICT_REF config );

        bool set_be_monitors_out_index_offset_arg(
            size_type const out_index_offset );

        bool set_elem_by_elem_out_index_offset_arg(
            size_type const out_index_offset );

        bool set_cbuffer_slot_size_arg( size_type const slot_size );

        bool set_status_flag_buffer_arg(
            cl_buffer_t& SIXTRL_RESTRICT_REF cl_status_flag_buffer );

        /* ================================================================= */

        bool has_track_until_kernel() const SIXTRL_NOEXCEPT;
        kernel_id_t track_until_kernel_id() const SIXTRL_NOEXCEPT;
        bool set_track_until_kernel_id( kernel_id_t const kernel_id );

        track_status_t track_until(
            num_turns_t const until_turn );

        track_status_t track_until(
            num_turns_t const until_turn, kernel_id_t const track_kernel_id );

        track_status_t track_until(
            ClArgument& particles_arg, size_type const particle_set_index,
            ClArgument& beam_elements_arg,
            num_turns_t const until_turn, kernel_id_t const track_kernel_id );

        /* ----------------------------------------------------------------- */

        bool has_track_elem_by_elem_kernel() const SIXTRL_NOEXCEPT;
        kernel_id_t track_elem_by_elem_kernel_id() const SIXTRL_NOEXCEPT;
        bool set_track_elem_by_elem_kernel_id( kernel_id_t const kernel_id );

        int track_elem_by_elem(
            size_type until_turn,
            size_type out_index_offset = size_type{ 0 } );

        int track_elem_by_elem(
            size_type until_turn, size_type out_index_offset,
            kernel_id_t const kernel_id );

        int track_elem_by_elem(
            ClArgument& SIXTRL_RESTRICT_REF particles_arg,
            ClArgument& SIXTRL_RESTRICT_REF beam_elements_arg,
            ClArgument& SIXTRL_RESTRICT_REF elem_by_elem_buffer,
            size_type until_turn, size_type out_index_offset,
            kernel_id_t const kernel_id );

        /* ----------------------------------------------------------------- */

        bool has_track_line_kernel() const SIXTRL_NOEXCEPT;
        kernel_id_t track_line_kernel_id() const SIXTRL_NOEXCEPT;
        bool set_track_line_kernel_id( kernel_id_t const kernel_id );

        int track_line( size_type const line_begin_idx,
                        size_type const line_end_idx,
                        bool const finish_turn = false );

        int track_line( size_type const line_begin_idx,
                        size_type const line_end_idx,
                        bool const finish_turn,
                        kernel_id_t const kernel_id );

        int track_line( ClArgument& SIXTRL_RESTRICT_REF particles_arg,
                        size_type const particle_set_index,
                        ClArgument& SIXTRL_RESTRICT_REF beam_elements_arg,
                        size_type const line_begin_idx,
                        size_type const line_end_idx, bool const finish_turn,
                        kernel_id_t const track_kernel_id );

        /* ----------------------------------------------------------------- */

        bool has_assign_be_monitors_output_kernel() const SIXTRL_NOEXCEPT;
        kernel_id_t assign_be_monitors_output_kernel_id() const SIXTRL_NOEXCEPT;
        bool set_assign_be_monitors_output_kernel_id(
            kernel_id_t const kernel_id );

        int assign_be_monitors_output_kernel(
            ClArgument& SIXTRL_RESTRICT_REF beam_elements_arg,
            ClArgument& SIXTRL_RESTRICT_REF out_buffer_arg,
            size_type const min_turn_id = size_type{ 0 },
            size_type const out_index_offset = size_type{ 0 } );

        int assign_be_monitors_output_kernel(
            ClArgument& SIXTRL_RESTRICT_REF beam_elements_arg,
            ClArgument& SIXTRL_RESTRICT_REF out_buffer_arg,
            size_type const min_turn_id, size_type const out_index_offset,
            kernel_id_t const kernel_id );

        /* ----------------------------------------------------------------- */

        bool has_clear_be_monitors_output_kernel() const SIXTRL_NOEXCEPT;
        kernel_id_t clear_be_monitors_output_kernel_id() const SIXTRL_NOEXCEPT;
        bool set_clear_be_monitors_output_kernel_id(
            kernel_id_t const kernel_id );

        int clear_be_monitors_output(
            ClArgument& SIXTRL_RESTRICT_REF beam_elements_arg );

        int clear_be_monitors_output(
            ClArgument& SIXTRL_RESTRICT_REF beam_elements_arg,
            kernel_id_t const kernel_id );

        /* ----------------------------------------------------------------- */

        bool has_assign_elem_by_elem_output_kernel() const SIXTRL_NOEXCEPT;
        kernel_id_t assign_elem_by_elem_output_kernel_id() const SIXTRL_NOEXCEPT;
        bool set_assign_elem_by_elem_output_kernel_id(
            kernel_id_t const kernel_id );

        int assign_elem_by_elem_output(
            ClArgument& SIXTRL_RESTRICT_REF beam_elements_arg,
            ClArgument& SIXTRL_RESTRICT_REF out_buffer_arg,
            size_type const out_index_offset = size_type{ 0 } );

        int assign_elem_by_elem_output(
            ClArgument& SIXTRL_RESTRICT_REF beam_elements_arg,
            ClArgument& SIXTRL_RESTRICT_REF out_buffer_arg,
            size_type const out_index_offset, kernel_id_t const kernel_id );

        /* ----------------------------------------------------------------- */

        bool has_fetch_particle_addr_kernel() const SIXTRL_NOEXCEPT;
        kernel_id_t fetch_particle_addr_kernel_id() const SIXTRL_NOEXCEPT;
        bool set_fetch_particle_addr_kernel_id( kernel_id_t const kernel_id );

        int fetch_particle_addr(
            ClArgument& SIXTRL_RESTRICT_REF particles_buffer_arg,
            ClArgument& SIXTRL_RESTRICT_REF paddresses_buffer_arg );

        int fetch_particle_addr(
            ClArgument& SIXTRL_RESTRICT_REF particles_buffer_arg,
            ClArgument& SIXTRL_RESTRICT_REF paddresses_buffer_arg,
            kernel_id_t const kernel_id );

        /* ================================================================= */

        bool use_optimized_tracking_by_default() const SIXTRL_NOEXCEPT;
        void enable_optimized_tracking_by_default();
        void disable_optimized_tracking_by_default();

        /* ----------------------------------------------------------------- */

        bool is_beam_beam_tracking_enabled() const SIXTRL_NOEXCEPT;
        void enable_beam_beam_tracking();
        void disable_beam_beam_tracking();

        protected:

        virtual void doClear() override;
        virtual bool doInitDefaultPrograms() override;
        virtual bool doInitDefaultKernels()  override;
        virtual bool doSelectNode( size_type const node_index ) override;

        template< typename Iter >
        bool doUpdateParticleSetIndices(
            Iter pset_indices_begin, Iter pset_indices_end,
            const ::NS(Buffer) *const SIXTRL_RESTRICT particles_buffer );

        void doResetParticleSetIndices(
            size_type const num_particles = size_type{ 0 } );

        private:

        bool doSelectNodePrivImpl( size_type const node_index );
        void doClearPrivImpl();

        bool doInitDefaultProgramsPrivImpl();
        bool doInitDefaultKernelsPrivImpl();

        cl::Buffer   m_elem_by_elem_config_buffer;

        std::vector< size_type > m_particle_set_indices;
        std::vector< size_type > m_particle_set_num_particles;
        std::vector< size_type > m_particle_set_index_begins;
        size_type m_total_num_particles;
        size_type m_total_num_particles_in_sets;

        program_id_t m_track_until_turn_program_id;
        program_id_t m_track_elem_by_elem_program_id;
        program_id_t m_track_line_program_id;
        program_id_t m_assign_be_mon_out_buffer_program_id;
        program_id_t m_clear_be_mon_program_id;
        program_id_t m_assign_elem_by_elem_out_buffer_program_id;
        program_id_t m_fetch_particle_addr_program_id;

        kernel_id_t  m_track_until_turn_kernel_id;
        kernel_id_t  m_track_elem_by_elem_kernel_id;
        kernel_id_t  m_track_line_kernel_id;
        kernel_id_t  m_assign_be_mon_out_buffer_kernel_id;
        kernel_id_t  m_clear_be_mon_kernel_id;
        kernel_id_t  m_assign_elem_by_elem_out_buffer_kernel_id;
        kernel_id_t  m_fetch_particle_addr_kernel_id;

        bool         m_use_optimized_tracking;
        bool         m_enable_beam_beam;
    };

    template< typename Iter >
        bool ClContext::doUpdateParticleSetIndices(
        Iter indices_begin, Iter indices_end,
        const ::NS(Buffer) *const SIXTRL_RESTRICT pbuffer )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        bool success = false;

        using diff_t = std::ptrdiff_t;
        using size_t = st::ClContext::size_type;

        diff_t const temp_len = std::distance( indices_begin, indices_end );

        if( ( temp_len > diff_t{ 0 } ) &&
            ( !::NS(Buffer_needs_remapping)( pbuffer ) ) &&
            ( std::is_sorted( indices_begin, indices_end ) ) )
        {
            size_t const num_psets = static_cast< size_t >( temp_len );
            size_t const nobjects  = ::NS(Buffer_get_num_of_objects)( pbuffer );

            SIXTRL_ASSERT( num_psets > size_t{ 0 } );
            SIXTRL_ASSERT( nobjects >= num_psets );

            Iter it = indices_begin;
            std::advance( it, num_psets - size_t{ 1 } );

            SIXTRL_ASSERT( ( ( num_psets > size_t{ 1 } ) &&
                ( *it > *indices_begin ) ) || ( num_psets == size_t{ 1 } ) );

            if( *it >= nobjects )
            {
                return success;
            }

            std::vector< size_t > temp_num_particles( nobjects, size_t{ 0 } );
            temp_num_particles.clear();

            std::vector< size_t > temp_pset_offsets( num_psets, size_t{ 0 } );
            temp_pset_offsets.clear();

            ::NS(Particles) const* p = nullptr;

            success = true;
            it = indices_begin;

            size_t total_num_particles = size_t{ 0 };
            size_t total_num_particles_in_sets = size_t{ 0 };

            for( size_t ii = size_t{ 0 } ; ii < nobjects ; ++ii )
            {
                p = ::NS(Particles_buffer_get_const_particles)( pbuffer, ii );
                size_t const num_particles = ( p != nullptr )
                    ? ::NS(Particles_get_num_of_particles)( p ) : size_t{ 0 };

                temp_num_particles.push_back( num_particles );

                if( it != indices_end )
                {
                    SIXTRL_ASSERT( *it >= ii );

                    if( ii == *it )
                    {
                        if( num_particles == size_t{ 0 } )
                        {
                            success = false;
                            break;
                        }

                        temp_pset_offsets.push_back( total_num_particles_in_sets );
                        total_num_particles_in_sets += num_particles;

                        ++it;
                        SIXTRL_ASSERT( ( it == indices_end ) || ( *it > ii ) );
                    }
                }

                total_num_particles += num_particles;
            }

            if( success )
            {
                SIXTRL_ASSERT( temp_pset_offsets.size()  == num_psets );
                SIXTRL_ASSERT( temp_num_particles.size() == nobjects );
                SIXTRL_ASSERT( total_num_particles > size_t{ 0 } );
                SIXTRL_ASSERT( total_num_particles >=
                               total_num_particles_in_sets );

                this->m_particle_set_indices.clear();
                this->m_particle_set_indices.reserve( num_psets );

                this->m_particle_set_num_particles.clear();
                this->m_particle_set_num_particles.reserve( num_psets );

                this->m_particle_set_index_begins.clear();
                this->m_particle_set_index_begins.reserve( num_psets );

                size_t ii = size_t{ 0 };
                it = indices_begin;

                for( ; it != indices_end ; ++it, ++ii )
                {
                    this->m_particle_set_index_begins.push_back(
                        temp_pset_offsets[ ii ] );

                    this->m_particle_set_num_particles.push_back(
                        temp_num_particles[ *it ] );

                    this->m_particle_set_indices.push_back( *it );
                }

                this->m_total_num_particles_in_sets =
                    total_num_particles_in_sets;

                this->m_total_num_particles = total_num_particles;
            }
        }

        return success;
    }
}

#if !defined( _GPUCODE )
extern "C" {
#endif /* !defined( _GPUCODE ) */

typedef SIXTRL_CXX_NAMESPACE::ClContext              NS(ClContext);
typedef SIXTRL_CXX_NAMESPACE::ClContext::num_turns_t NS(context_num_turns_t);

#if !defined( _GPUCODE )
}
#endif /* !defined( _GPUCODE ) */

#else /* !defined( __cplusplus ) */

typedef void NS(ClContext);
typedef SIXTRL_INT64_T NS(context_num_turns_t);

#endif /* defined( __cplusplus ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(ClContext)* NS(ClContext_create)();

SIXTRL_EXTERN SIXTRL_HOST_FN NS(ClContext)* NS(ClContext_new)(
    const char* node_id_str );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(ClContext_delete)(
    NS(ClContext)* SIXTRL_RESTRICT ctx );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(ClContext_clear)(
    NS(ClContext)* SIXTRL_RESTRICT ctx );

/* ========================================================================= */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(ClContext_has_tracking_kernel)(
    const NS(ClContext) *const SIXTRL_RESTRICT ctx );

SIXTRL_EXTERN SIXTRL_HOST_FN int NS(ClContext_get_tracking_kernel_id)(
    const NS(ClContext) *const SIXTRL_RESTRICT ctx );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(ClContext_set_tracking_kernel_id)(
    NS(ClContext)* SIXTRL_RESTRICT ctx, int const kernel_id );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXTERN SIXTRL_HOST_FN int NS(ClContext_continue_tracking)(
    NS(ClContext)* SIXTRL_RESTRICT ctx, NS(context_num_turns_t) const turn );

SIXTRL_EXTERN SIXTRL_HOST_FN int
NS(ClContext_continue_tracking_with_kernel_id)(
    NS(ClContext)* SIXTRL_RESTRICT ctx, int const track_kernel_id,
    NS(context_num_turns_t) const turn );

SIXTRL_EXTERN SIXTRL_HOST_FN int NS(ClContext_track)(
    NS(ClContext)* SIXTRL_RESTRICT ctx,
    NS(ClArgument)* SIXTRL_RESTRICT ptr_particles_arg,
    NS(ClArgument)* SIXTRL_RESTRICT ptr_beam_elements_arg,
    NS(context_num_turns_t) const turn );

SIXTRL_EXTERN SIXTRL_HOST_FN int NS(ClContext_track_with_kernel_id)(
    NS(ClContext)* SIXTRL_RESTRICT ctx,
    NS(ClArgument)* SIXTRL_RESTRICT ptr_particles_arg,
    NS(ClArgument)* SIXTRL_RESTRICT ptr_beam_elements_arg,
    NS(context_num_turns_t) const turn, int const tracking_kernel_id );

/* ------------------------------------------------------------------------- */


SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(ClContext_has_line_tracking_kernel)(
    const NS(ClContext) *const SIXTRL_RESTRICT ctx );

SIXTRL_EXTERN SIXTRL_HOST_FN int NS(ClContext_get_line_tracking_kernel_id)(
    const NS(ClContext) *const SIXTRL_RESTRICT ctx );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(ClContext_set_line_tracking_kernel_id)(
    NS(ClContext)* SIXTRL_RESTRICT ctx, int const kernel_id );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXTERN SIXTRL_HOST_FN int
NS(ClContext_continue_line_tracking)( NS(ClContext)* SIXTRL_RESTRICT ctx,
    NS(buffer_size_t) const line_begin_idx,
    NS(buffer_size_t) const line_end_idx, bool const finish_turn );

SIXTRL_EXTERN SIXTRL_HOST_FN int
NS(ClContext_continue_line_tracking_with_kernel_id)(
    NS(ClContext)* SIXTRL_RESTRICT ctx,
    NS(buffer_size_t) const line_begin_idx,
    NS(buffer_size_t) const line_end_idx,
    bool const finish_turn, int const line_tracking_kernel_id );

SIXTRL_EXTERN SIXTRL_HOST_FN int NS(ClContext_track_line)(
    NS(ClContext)* SIXTRL_RESTRICT ctx,
    NS(ClArgument)* SIXTRL_RESTRICT ptr_particles_arg,
    NS(buffer_size_t) const particle_set_index,
    NS(ClArgument)* SIXTRL_RESTRICT ptr_beam_elements_arg,
    NS(buffer_size_t) const line_begin_idx,
    NS(buffer_size_t) const line_end_idx, bool const finish_turn );

SIXTRL_EXTERN SIXTRL_HOST_FN int NS(ClContext_track_line_with_kernel_id)(
    NS(ClContext)* SIXTRL_RESTRICT ctx,
    NS(ClArgument)* SIXTRL_RESTRICT ptr_particles_arg,
    NS(buffer_size_t) const particle_set_index,
    NS(ClArgument)* SIXTRL_RESTRICT ptr_beam_elements_arg,
    NS(buffer_size_t) const line_begin_idx,
    NS(buffer_size_t) const line_end_idx, bool const finish_turn,
    int const line_tracking_kernel_id );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool
NS(ClContext_has_element_by_element_tracking_kernel)(
    const NS(ClContext) *const SIXTRL_RESTRICT ctx );

SIXTRL_EXTERN SIXTRL_HOST_FN int
NS(ClContext_get_element_by_element_tracking_kernel_id)(
    const NS(ClContext) *const SIXTRL_RESTRICT ctx );

SIXTRL_EXTERN SIXTRL_HOST_FN bool
NS(ClContext_set_element_by_element_tracking_kernel_id)(
    NS(ClContext)* SIXTRL_RESTRICT ctx, int const tracking_kernel_id );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXTERN SIXTRL_HOST_FN int
NS(ClContext_continue_tracking_element_by_element)(
    NS(ClContext)* SIXTRL_RESTRICT ctx, NS(buffer_size_t) const until_turn,
    NS(buffer_size_t) const out_particle_block_offset );

SIXTRL_EXTERN SIXTRL_HOST_FN int
NS(ClContext_continue_tracking_element_by_element_with_kernel_id)(
    NS(ClContext)* SIXTRL_RESTRICT ctx, NS(buffer_size_t) const until_turn,
    NS(buffer_size_t) const out_particle_block_offset,
    int const kernel_id );

SIXTRL_EXTERN SIXTRL_HOST_FN int NS(ClContext_track_element_by_element)(
    NS(ClContext)* SIXTRL_RESTRICT ctx,
    NS(ClArgument)* SIXTRL_RESTRICT ptr_particles_arg,
    NS(ClArgument)* SIXTRL_RESTRICT ptr_beam_elements_arg,
    NS(ClArgument)* SIXTRL_RESTRICT ptr_elem_by_elem_buffer_arg,
    NS(buffer_size_t) const until_turn,
    NS(buffer_size_t) const out_particle_block_offset );

SIXTRL_EXTERN SIXTRL_HOST_FN int
NS(ClContext_track_element_by_element_with_kernel_id)(
    NS(ClContext)* SIXTRL_RESTRICT ctx,
    NS(ClArgument)* SIXTRL_RESTRICT ptr_particles_arg,
    NS(ClArgument)* SIXTRL_RESTRICT ptr_beam_elements_arg,
    NS(ClArgument)* SIXTRL_RESTRICT ptr_elem_by_elem_buffer_arg,
    NS(buffer_size_t) const until_turn,
    NS(buffer_size_t) const out_particle_block_offset,
    int const tracking_kernel_id );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool
NS(ClContext_has_assign_beam_monitor_out_buffer_kernel)(
    const NS(ClContext) *const SIXTRL_RESTRICT ctx );

SIXTRL_EXTERN SIXTRL_HOST_FN int
NS(ClContext_get_assign_beam_monitor_out_buffer_kernel_id)(
    const NS(ClContext) *const SIXTRL_RESTRICT ctx );

SIXTRL_EXTERN SIXTRL_HOST_FN bool
NS(ClContext_set_assign_beam_monitor_out_buffer_kernel_id)(
    NS(ClContext)* SIXTRL_RESTRICT ctx, int const assign_kernel_id );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXTERN SIXTRL_HOST_FN int NS(ClContext_assign_beam_monitor_out_buffer)(
    NS(ClContext)*  SIXTRL_RESTRICT ctx,
    NS(ClArgument)* SIXTRL_RESTRICT beam_elements_arg,
    NS(ClArgument)* SIXTRL_RESTRICT out_buffer,
    NS(buffer_size_t) const min_turn_id,
    NS(buffer_size_t) const out_particle_block_offset );

SIXTRL_EXTERN SIXTRL_HOST_FN int
NS(ClContext_assign_beam_monitor_out_buffer_with_kernel_id)(
    NS(ClContext)*  SIXTRL_RESTRICT ctx,
    NS(ClArgument)* SIXTRL_RESTRICT beam_elements_arg,
    NS(ClArgument)* SIXTRL_RESTRICT out_buffer,
    NS(buffer_size_t) const min_turn_id,
    NS(buffer_size_t) const out_particle_block_offset,
    int const assign_kernel_id );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXTERN SIXTRL_HOST_FN bool
NS(ClContext_has_clear_beam_monitor_out_assignment_kernel)(
    const NS(ClContext) *const SIXTRL_RESTRICT ctx );

SIXTRL_EXTERN SIXTRL_HOST_FN int
NS(ClContext_get_clear_beam_monitor_out_assignment_kernel_id)(
    const NS(ClContext) *const SIXTRL_RESTRICT ctx );

SIXTRL_EXTERN SIXTRL_HOST_FN bool
NS(ClContext_set_clear_beam_monitor_out_assignment_kernel_id)(
    NS(ClContext)* SIXTRL_RESTRICT ctx, int const kernel_id );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXTERN SIXTRL_HOST_FN int
NS(ClContext_clear_beam_monitor_out_assignment)(
    NS(ClContext)*  SIXTRL_RESTRICT context,
    NS(ClArgument)* SIXTRL_RESTRICT beam_elements_arg );

SIXTRL_EXTERN SIXTRL_HOST_FN int
NS(ClContext_clear_beam_monitor_out_assignment_with_kernel)(
    NS(ClContext)*  SIXTRL_RESTRICT context,
    NS(ClArgument)* SIXTRL_RESTRICT beam_elements_arg, int const kernel_id );

/* ------------------------------------------------------------------------- */


SIXTRL_EXTERN SIXTRL_HOST_FN bool
NS(ClContext_has_assign_elem_by_elem_output_kernel)(
    const NS(ClContext) *const SIXTRL_RESTRICT ctx );

SIXTRL_EXTERN SIXTRL_HOST_FN int
NS(ClContext_get_assign_elem_by_elem_output_kernel_id)(
    const NS(ClContext) *const SIXTRL_RESTRICT ctx );

SIXTRL_EXTERN SIXTRL_HOST_FN bool
NS(ClContext_set_assign_elem_by_elem_output_kernel_id)(
    NS(ClContext)* SIXTRL_RESTRICT ctx, int const kernel_id );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXTERN SIXTRL_HOST_FN int
NS(ClContext_assign_elem_by_elem_output_kernel)(
    NS(ClContext)*  SIXTRL_RESTRICT context,
    NS(ClArgument)* SIXTRL_RESTRICT beam_elements_arg,
    NS(ClArgument)* SIXTRL_RESTRICT output_buffer_arg,

SIXTRL_EXTERN SIXTRL_HOST_FN int
NS(ClContext_clear_beam_monitor_out_assignment_with_kernel)(
    NS(ClContext)*  SIXTRL_RESTRICT context,
    NS(ClArgument)* SIXTRL_RESTRICT beam_elements_arg, int const kernel_id );

/* ------------------------------------------------------------------------- */


/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool
NS(ClContext_uses_optimized_tracking_by_default)(
    const NS(ClContext) *const SIXTRL_RESTRICT ctx );

SIXTRL_EXTERN SIXTRL_HOST_FN void
NS(ClContext_enable_optimized_tracking_by_default)(
    NS(ClContext)* SIXTRL_RESTRICT ctx );

SIXTRL_EXTERN SIXTRL_HOST_FN void
NS(ClContext_disable_optimized_tracking_by_default)(
    NS(ClContext)* SIXTRL_RESTRICT ctx );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(ClContext_is_beam_beam_tracking_enabled)(
    const NS(ClContext) *const SIXTRL_RESTRICT ctx );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(ClContext_enable_beam_beam_tracking)(
    NS(ClContext)* SIXTRL_RESTRICT ctx );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(ClContext_disable_beam_beam_tracking)(
    NS(ClContext)* SIXTRL_RESTRICT ctx );


#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#endif /* !defined( __CUDACC__ ) */

#endif /* SIXTRACKLIB_OPENCL_CONTEXT_H__ */

/* end: sixtracklib/opencl/context.h */
