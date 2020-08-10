#ifndef SIXTRACKLIB_BASE_NODE_NODE_INFO_H__
#define SIXTRACKLIB_BASE_NODE_NODE_INFO_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/definitions.h"
    #include "sixtracklib_base/backend/definitions.h"
    #include "sixtracklib_base/backend/backend_obj.h"
    #include "sixtracklib_base/node/definitions.h"
    #include "sixtracklib_base/node/node_id.h"
    #include "sixtracklib_base/internal/class_id.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <algorithm>
        #include <cstddef>
        #include <cstdlib>
        #include <cstdio>
        #include <cstring>
        #include <map>
        #include <memory>
        #include <ostream>
        #include <stdexcept>
        #include <string>
        #include <sstream>
        #include <vector>
    #endif /* C++, Host */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    class SIXTRL_BASE_EXPORT_API BaseNodeInfo :
        public SIXTRL_CXX_NAMESPACE::BaseBackendObj
    {
        public:

        using c_node_id_t        = ::NS(NodeId);
        using size_type          = SIXTRL_CXX_NAMESPACE::size_t;
        using node_id_t          = SIXTRL_CXX_NAMESPACE::NodeId;
        using platform_id_t      = SIXTRL_CXX_NAMESPACE::node_platform_id_t;
        using device_id_t        = SIXTRL_CXX_NAMESPACE::node_device_id_t;
        using str_format_t       = SIXTRL_CXX_NAMESPACE::node_id_str_fmt_t;
        using device_str_kind_t  = SIXTRL_CXX_NAMESPACE::node_device_str_kind_t;
        using print_flags_t      = SIXTRL_CXX_NAMESPACE::node_print_flags_t;
        using status_t           = SIXTRL_CXX_NAMESPACE::status_t;
        using string_type        = node_id_t::string_type;
        using string_char_t      = node_id_t::string_char_t;
        using sstream_t          = node_id_t::sstream_t;

        static constexpr string_char_t DEVICE_ID_STR_UUID_REGEX_STR[] =
            "([0-9a-fA-F]{8})-([0-9a-fA-F]{4})-([1-5])([0-9a-fA-F]{3})-"
            "([0-9a-fA-F]{4})-([0-9a-fA-F]{12})";

        static constexpr string_char_t DEVICE_ID_STR_PCI_BUS_ID_REGEX_STR[] =
            "([0-9a-fA-F]{1,8})\\:([0-9a-fA-F]{2})"
            "\\:([0-9a-fA-F]{2})\\.([0-9]{1})";

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN static bool DEVICE_ID_STR_HAS_NOBACKEND_FORMAT(
            string_type const& SIXTRL_RESTRICT_REF device_id_str );

        SIXTRL_HOST_FN static bool DEVICE_ID_STR_HAS_BACKENDID_FORMAT(
            string_type const& SIXTRL_RESTRICT_REF device_id_str );

        SIXTRL_HOST_FN static bool
        DEVICE_ID_STR_HAS_BACKENDID_FORMAT_FOR_BACKEND(
            string_type const& SIXTRL_RESTRICT_REF device_id_str,
            backend_id_t const backend_id );

        SIXTRL_HOST_FN static bool DEVICE_ID_STR_HAS_BACKENDSTR_FORMAT(
            string_type const& SIXTRL_RESTRICT_REF device_id_str );

        SIXTRL_HOST_FN static bool
        DEVICE_ID_STR_HAS_BACKENDSTR_FORMAT_FOR_BACKEND(
            string_type const& SIXTRL_RESTRICT_REF device_id_str,
            backend_id_t const backend_id );

        SIXTRL_HOST_FN static bool DEVICE_ID_STR_HAS_UUID_FORMAT(
            string_type const& SIXTRL_RESTRICT_REF device_id_str );

        SIXTRL_HOST_FN static bool DEVICE_ID_STR_HAS_PCI_BUS_ID_FORMAT(
            string_type const& SIXTRL_RESTRICT_REF device_id_str );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN virtual ~BaseNodeInfo() = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN c_node_id_t node_id_data() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN node_id_t const* base_node_id() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN platform_id_t platform_id() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN device_id_t device_id() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t set_platform_id(
            platform_id_t const platform_id ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t set_device_id(
            device_id_t const device_id ) SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN string_type const&
        platform_name_str() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN string_type const&
        device_name_str() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN string_type const&
        description_str() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN string_char_t const*
        platform_name() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN string_char_t const*
        device_name() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN string_char_t const*
        description() const SIXTRL_NOEXCEPT;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN status_t set_platform_name(
            string_type const& SIXTRL_RESTRICT_REF platform_name );

        SIXTRL_HOST_FN status_t set_device_name(
            string_type const& SIXTRL_RESTRICT_REF device_name );

        SIXTRL_HOST_FN status_t set_description(
            string_type const& SIXTRL_RESTRICT_REF description );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN size_type num_device_strings() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN device_str_kind_t const*
            device_string_kinds_begin() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN device_str_kind_t const*
            device_string_kinds_end() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN device_str_kind_t device_string_kind(
            size_type const idx ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool has_device_string_by_kind(
            device_str_kind_t const kind ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN string_type const& device_string_str() const;

        SIXTRL_HOST_FN string_char_t const*
        device_string() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN string_type const& device_string_str_by_kind(
            device_str_kind_t const kind ) const;

        SIXTRL_HOST_FN string_char_t const* device_string_by_kind(
            device_str_kind_t const kind ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN device_str_kind_t find_device_str_kind(
            string_type const& SIXTRL_RESTRICT_REF device_id_str ) const;

        SIXTRL_HOST_FN bool check_device_str_format(
            string_type const& SIXTRL_RESTRICT_REF device_id_str,
            device_str_kind_t const kind ) const;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN status_t set_device_string(
            device_str_kind_t const device_str_kind,
            string_type const& SIXTRL_RESTRICT_REF device_str );

        SIXTRL_HOST_FN status_t remove_device_str(
            device_str_kind_t const device_str_kind );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN status_t update_default_device_strings();
        SIXTRL_HOST_FN void clear();
        SIXTRL_HOST_FN void print(
            std::ostream& SIXTRL_RESTRICT_REF ostr, print_flags_t const flags =
                SIXTRL_CXX_NAMESPACE::NODE_PRINT_FLAGS_NONE ) const;

        SIXTRL_HOST_FN string_type to_string( print_flags_t const flags =
                SIXTRL_CXX_NAMESPACE::NODE_PRINT_FLAGS_NONE ) const;

        SIXTRL_HOST_FN status_t to_string_detailed(
            char* SIXTRL_RESTRICT out_buffer, size_type const out_buf_capacity,
            node_print_flags_t const flags ) const;

        SIXTRL_HOST_FN status_t to_string( char* SIXTRL_RESTRICT out_buffer,
            size_type const out_buffer_capacity ) const;

        SIXTRL_HOST_FN size_type to_string_required_capacity(
            node_print_flags_t const flags ) const;

        SIXTRL_HOST_FN friend std::ostream& operator<<(
            std::ostream& SIXTRL_RESTRICT_REF ostr,
            BaseNodeInfo const& SIXTRL_RESTRICT_REF node_info )
        {
            node_info.print( ostr );
            return ostr;
        }

        SIXTRL_HOST_FN SIXTRL_INLINE bool operator<(
            BaseNodeInfo const& SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT
        {
            bool is_smaller = false;

            if( ( this->m_stored_node_id.get() != nullptr ) &&
                ( rhs.m_stored_node_id.get() != nullptr ) )
            {
                is_smaller = *this->m_stored_node_id < *rhs.m_stored_node_id;
            }
            else if( rhs.m_stored_node_id.get() != nullptr )
            {
                is_smaller = true;
            }

            return is_smaller;
        }

        protected:

        using device_str_map_t = std::map< device_str_kind_t, string_type >;
        using device_str_kinds_t = std::vector< device_str_kind_t >;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN explicit BaseNodeInfo( backend_id_t const backend_id );

        SIXTRL_HOST_FN BaseNodeInfo(
            BaseNodeInfo const& SIXTRL_RESTRICT_REF orig );

        SIXTRL_HOST_FN BaseNodeInfo( BaseNodeInfo&&
            SIXTRL_RESTRICT_REF orig ) = default;

        SIXTRL_HOST_FN BaseNodeInfo& operator=(
            BaseNodeInfo const& SIXTRL_RESTRICT_REF rhs );

        SIXTRL_HOST_FN BaseNodeInfo& operator=(
            BaseNodeInfo&& SIXTRL_RESTRICT_REF rhs ) = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN virtual void do_clear();

        SIXTRL_HOST_FN virtual status_t do_set_device_string(
            device_str_kind_t const kind, string_type const& device_str );

        SIXTRL_HOST_FN virtual status_t do_remove_device_string(
            device_str_kind_t const kind );

        SIXTRL_HOST_FN virtual status_t do_update_default_device_strings();

        SIXTRL_HOST_FN virtual device_str_kind_t
        do_find_device_str_kind_for_device_str(
            string_type const& SIXTRL_RESTRICT_REF device_id_str ) const;

        SIXTRL_HOST_FN virtual bool do_check_device_string_with_format(
            string_type const& SIXTRL_RESTRICT_REF device_str,
            device_str_kind_t const kind ) const;

        SIXTRL_HOST_FN virtual void do_print_device_str_section(
            std::ostream& SIXTRL_RESTRICT_REF ostr,
            print_flags_t const flags ) const;

        SIXTRL_HOST_FN virtual void do_print_base_section(
            std::ostream& SIXTRL_RESTRICT_REF ostr,
            print_flags_t const flags ) const;

        SIXTRL_HOST_FN virtual void do_print_extended_section(
            std::ostream& SIXTRL_RESTRICT_REF ostr,
            print_flags_t const flags ) const;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t update_stored_node_id(
            std::unique_ptr< node_id_t > node_id_to_store ) SIXTRL_NOEXCEPT;

        private:

        SIXTRL_HOST_FN status_t do_set_device_string_base_impl(
            device_str_kind_t const kind,
            string_type const& SIXTRL_RESTRICT_REF device_str );

        SIXTRL_HOST_FN status_t do_remove_device_string_base_impl(
            device_str_kind_t const kind ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t do_update_default_device_strings_base_impl();

        std::unique_ptr< node_id_t > m_stored_node_id;
        device_str_map_t m_device_str_map;
        device_str_kinds_t m_device_str_kinds;

        string_type m_platform_name;
        string_type m_device_name;
        string_type m_description;
    };

} /* ns: SIXTRL_CXX_NAMESPACE */

extern "C" { typedef SIXTRL_CXX_NAMESPACE::BaseNodeInfo NS(BaseNodeInfo); }

#else /* C++, Host */

struct NS(BaseNodeInfo);

#endif /* C++, Host */
#endif /* SIXTRACKLIB_BASE_NODE_NODE_INFO_H__ */
