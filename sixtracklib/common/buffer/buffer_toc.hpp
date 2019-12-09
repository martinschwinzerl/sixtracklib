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
    #include "sixtracklib/common/internal/beam_elements_defines.h"
    #include "sixtracklib/common/internal/objects_type_id.h"
    #include "sixtracklib/common/buffer.hpp"
    #include "sixtracklib/common/buffer.h"
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

        friend bool operator==( BufferToc const& SIXTRL_RESTRICT_REF lhs,
            BufferToc const& SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT;

        friend bool operator!=( BufferToc const& SIXTRL_RESTRICT_REF lhs,
            BufferToc const& SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT;

        protected:

        using indices_list_t  = std::vector< size_type >;
        using type_ids_list_t = std::vector< type_id_t >;
        using type_id_to_indices_map_t = std::map< type_id_t, indices_list_t >;

        SIXTRL_HOST_FN virtual void doClear();

        SIXTRL_HOST_FN virtual status_t doReset(
            const c_buffer_t *const SIXTRL_RESTRICT buffer );

        private:

        SIXTRL_HOST_FN void doClearBaseImpl() SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t doResetBaseImpl(
            const c_buffer_t *const SIXTRL_RESTRICT buffer );

        type_id_to_indices_map_t        m_type_ids_to_indices_map;
        type_ids_list_t                 m_stored_type_ids;
    };
}

#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )

extern "C" {

typedef SIXTRL_CXX_NAMESPACE::BufferToc NS(BufferToc);

}

#else

struct NS(BufferToc);

#endif /* SIXTRACKLIB_COMMON_BUFFER_BUFFER_TOC_CXX_HPP__ */
