#ifndef SIXTRACKLIB_COMMON_BUFFER_BUFFER_TOC_CXX_HPP__
#define SIXTRACKLIB_COMMON_BUFFER_BUFFER_TOC_CXX_HPP__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <algorithm>
        #include <map>
        #include <vector>
        #include <unordered_map>
    #endif /* defined( __cplusplus ) */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/buffer.h"
    #include "sixtracklib/common/internal/objects_type_id.h"
    #if defined( __cplusplus )
        #include "sixtracklib/common/buffer.hpp"
    #endif /* defined( __cplusplus ) */
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )

namespace SIXTRL_CXX_NAMESPACE
{
    class BufferTableOfContents
    {
        public:

        using buffer_t   = SIXTRL_CXX_NAMESPACE::Buffer;
        using type_id_t  = SIXTRL_CXX_NAMESPACE::object_type_id_t;
        using status_t   = SIXTRL_CXX_NAMESPACE::arch_status_t;
        using c_buffer_t = buffer_t::c_api_t;
        using size_type  = buffer_t::size_type;
        using offset_t   = uint64_t;

        static constexpr size_type ILLEGAL_ENTRY_INDEX =
            static_cast< size_type >( 0xffffffffffffffff );

        static constexpr offset_t ILLEGAL_ENTRY_OFFSET =
            static_cast< offset_t >( 0xffffffffffffffff );

        static constexpr size_type ILLEGAL_ENTRY_SIZE =
            static_cast< size_type >( 0xffffffffffffffff );

        static constexpr size_type ILLEGAL_NUM_DATAPTRS =
            static_cast< size_type >( 0xffffffffffffffff );

        SIXTRL_HOST_FN explicit BufferTableOfContents(
            const c_buffer_t *const SIXTRL_RESTRICT buffer = nullptr );

        SIXTRL_HOST_FN explicit BufferTableOfContents(
            buffer_t const& SIXTRL_RESTRICT_REF buffer );

        SIXTRL_HOST_FN BufferTableOfContents(
            BufferTableOfContents const& ) = default;

        SIXTRL_HOST_FN BufferTableOfContents(
            BufferTableOfContents&& ) = default;

        SIXTRL_HOST_FN BufferTableOfContents& operator=(
            BufferTableOfContents const& ) = default;

        SIXTRL_HOST_FN BufferTableOfContents& operator=(
            BufferTableOfContents&& ) = default;

        SIXTRL_HOST_FN virtual ~BufferTableOfContents() = default;

        friend void swap(
            BufferTableOfContents& SIXTRL_RESTRICT_REF lhs,
            BufferTableOfContents& SIXTRL_RESTRICT_REF rhs ) SIXTRL_NOEXCEPT
        {
            using std::swap;

            swap( lhs.m_type_indices_map,  rhs.m_type_indices_map  );
            swap( lhs.m_entry_list,        rhs.m_entry_list        );
            swap( lhs.m_type_id_list,      rhs.m_type_id_list      );
        }

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN size_type total_num_entries() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type num_entry_types() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN type_id_t const*
            entry_types_begin() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN type_id_t const*
            entry_types_end() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool has_entries(
            type_id_t const type_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type num_entries(
            type_id_t const type_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type const* entry_indices_begin(
            type_id_t const type_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type const* entry_indices_end(
            type_id_t const type_id ) const SIXTRL_NOEXCEPT;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN size_type entry_type_index(
            size_type const nn ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN type_id_t entry_type_id(
            size_type const nn ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN offset_t  entry_offset(
            size_type const nn ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type entry_size(
            size_type const nn ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type entry_num_dataptrs(
            size_type const nn ) const SIXTRL_NOEXCEPT;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN size_type entry_index( type_id_t const type_id,
            size_type const nn ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN offset_t entry_offset( type_id_t const type_id,
            size_type const nn ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type entry_size( type_id_t const type_id,
            size_type const nn ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type entry_num_dataptrs(
            type_id_t const type_id, size_type const nn ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN void clear();

        SIXTRL_HOST_FN status_t reset(
            buffer_t const& SIXTRL_RESTRICT_REF buffer );

        SIXTRL_HOST_FN status_t reset(
            const c_buffer_t *const SIXTRL_RESTRICT buffer );

        SIXTRL_HOST_FN status_t append(
            buffer_t const& SIXTRL_RESTRICT_REF buffer,
            size_type const num_entries_to_append = size_type{ 0 } );

        SIXTRL_HOST_FN status_t append(
            const c_buffer_t *const SIXTRL_RESTRICT buffer,
            size_type const num_entries_to_append = size_type{ 0 } );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool has_same_layout(
            buffer_t const& SIXTRL_RESTRICT_REF buffer );

        SIXTRL_HOST_FN bool has_same_layout(
            const c_buffer_t *const SIXTRL_RESTRICT buffer );

        protected:

        using entry_t = struct Entry
        {
            offset_t    m_offset;
            size_type   m_size;
            size_type   m_num_dataptrs;
            size_type   m_type_index;
            type_id_t   m_type_id;
        };

        using indices_list_t = std::vector< size_type >;
        using entry_list_t   = std::vector< entry_t >;
        using type_id_list_t = std::vector< type_id_t >;

        using type_indices_map_t =
            std::unordered_map< type_id_t, indices_list_t >;

        using name_index_map_t = std::map< std::string, size_type >;

        SIXTRL_HOST_FN virtual void doClear();

        SIXTRL_HOST_FN virtual status_t doAppendEntries(
            const c_buffer_t *const SIXTRL_RESTRICT buffer,
            size_type const num_entries_to_append );

        SIXTRL_HOST_FN virtual bool doCheckHasBufferIdenticalLayout(
            const c_buffer_t *const SIXTRL_RESTRICT buffer,
            size_type const begin_index, size_type const end_index );

        private:

        SIXTRL_HOST_FN status_t doAppendEntriesBaseImpl(
            const c_buffer_t *const SIXTRL_RESTRICT buffer,
            size_type const num_entries_to_append );


        type_indices_map_t      m_type_indices_map;
        entry_list_t            m_entry_list;
        type_id_list_t          m_type_id_list;
    };
}

extern "C" {

    typedef SIXTRL_CXX_NAMESPACE::BufferTableOfContents
            NS(BufferTableOfContents);
}

#else /*  defined( __cplusplus ) && !defined( _GPUCODE ) */

typedef void NS(BufferTableOfContents);

#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */
#endif /* SIXTRACKLIB_COMMON_BUFFER_BUFFER_TOC_CXX_HPP__ */

/* end: sixtracklib/common/buffer/buffer_index.hpp */
