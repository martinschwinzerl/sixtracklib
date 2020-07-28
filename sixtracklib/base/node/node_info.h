#ifndef SIXTRACKLIB_BASE_NODE_NODE_INFO_H__
#define SIXTRACKLIB_BASE_NODE_NODE_INFO_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/base/definitions.h"
    #include "sixtracklib/base/architecture/definitions.h"
    #include "sixtracklib/base/architecture/arch_obj.h"
    #include "sixtracklib/base/node/definitions.h"
    #include "sixtracklib/base/node/node_id.h"
    #include "sixtracklib/base/internal/class_id.h"
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
        public SIXTRL_CXX_NAMESPACE::BaseArchObj
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

        SIXTRL_HOST_FN virtual ~BaseNodeInfo() = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN c_node_id_t node_id_data() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_id_t const* base_node_id() const SIXTRL_NOEXCEPT {
            return this->m_stored_node_id.get(); }

        SIXTRL_HOST_FN platform_id_t platform_id() const SIXTRL_NOEXCEPT {
            SIXTRL_ASSERT( this->m_stored_node_id.get() != nullptr );
            return this->m_stored_node_id->platform_id(); }

        SIXTRL_HOST_FN device_id_t device_id() const SIXTRL_NOEXCEPT {
            SIXTRL_ASSERT( this->m_stored_node_id.get() != nullptr );
            return this->m_stored_node_id->device_id(); }

        SIXTRL_HOST_FN status_t set_platform_id(
            platform_id_t const platform_id ) SIXTRL_NOEXCEPT {
            SIXTRL_ASSERT( this->m_stored_node_id.get() != nullptr );
            return this->m_stored_node_id->set_platform_id( platform_id );
        }

        SIXTRL_HOST_FN status_t set_device_id(
            device_id_t const device_id ) SIXTRL_NOEXCEPT {
            SIXTRL_ASSERT( this->m_stored_node_id.get() != nullptr );
            return this->m_stored_node_id->set_device_id( device_id );
        }

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN std::string const&
        platform_name_str() const SIXTRL_NOEXCEPT {
            return this->m_platform_name; }

        SIXTRL_HOST_FN std::string const&
        device_name_str() const SIXTRL_NOEXCEPT {
            return this->m_device_name; }

        SIXTRL_HOST_FN std::string const&
            description_str() const SIXTRL_NOEXCEPT {
            return this->m_description; }

        SIXTRL_HOST_FN char const* platform_name() const SIXTRL_NOEXCEPT {
            return this->m_platform_name.c_str(); }

        SIXTRL_HOST_FN char const* device_name() const SIXTRL_NOEXCEPT {
            return this->m_device_name.c_str(); }

        SIXTRL_HOST_FN char const* description() const SIXTRL_NOEXCEPT {
            return this->m_description.c_str(); }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN status_t set_platform_name(
            std::string const& SIXTRL_RESTRICT_REF platform_name ) {
            namespace st = SIXTRL_CXX_NAMESPACE;
            this->m_platform_name = platform_name;
            return st::STATUS_SUCCESS;
        }

        SIXTRL_HOST_FN status_t set_device_name(
            std::string const& SIXTRL_RESTRICT_REF device_name ) {
            namespace st = SIXTRL_CXX_NAMESPACE;
            this->m_device_name = device_name;
            return st::STATUS_SUCCESS;
        }

        SIXTRL_HOST_FN status_t set_description(
            std::string const& SIXTRL_RESTRICT_REF description ) {
            namespace st = SIXTRL_CXX_NAMESPACE;
            this->m_description = description;
            return st::STATUS_SUCCESS;
        }

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN size_type num_device_strings() const SIXTRL_NOEXCEPT {
            SIXTRL_ASSERT( this->m_device_str_kinds.size() ==
                           this->m_device_str_map.size() );
            return this->m_device_str_kinds.size();
        }

        SIXTRL_HOST_FN device_str_kind_t const*
            device_string_kinds_begin() const SIXTRL_NOEXCEPT {
            SIXTRL_ASSERT( this->m_device_str_kinds.size() ==
                           this->m_device_str_map.size() );
            return ( !this->m_device_str_kinds.empty() )
                ? this->m_device_str_kinds.data() : nullptr;
        }

        SIXTRL_HOST_FN device_str_kind_t const*
            device_string_kinds_end() const SIXTRL_NOEXCEPT {
            SIXTRL_ASSERT( this->m_device_str_kinds.size() ==
                           this->m_device_str_map.size() );
            return ( !this->m_device_str_kinds.empty() )
                ? this->m_device_str_kinds.data() : nullptr;
        }

        SIXTRL_HOST_FN device_str_kind_t device_string_kind(
            size_type const idx ) const SIXTRL_NOEXCEPT {
            SIXTRL_ASSERT( this->m_device_str_kinds.size() ==
                           this->m_device_str_map.size() );

            return ( idx < this->m_device_str_kinds.size() )
                ? this->m_device_str_kinds[ idx ]
                : SIXTRL_CXX_NAMESPACE::NODE_DEVICE_STRING_KIND_ILLEGAL;
        }

        SIXTRL_HOST_FN bool has_device_string_by_kind( device_str_kind_t const
            kind ) const SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            SIXTRL_ASSERT( this->m_device_str_kinds.size() ==
                           this->m_device_str_map.size() );

            return ( ( kind != st::NODE_DEVICE_STRING_KIND_ILLEGAL ) &&
                     ( std::find( this->m_device_str_kinds.begin(),
                                  this->m_device_str_kinds.end(), kind ) !=
                        this->m_device_str_kinds.end() ) );
        }

        SIXTRL_HOST_FN std::string const& device_string_str() const {
            return this->device_string_str_by_kind(
                SIXTRL_CXX_NAMESPACE::NODE_DEVICE_STRING_KIND_DEFAULT );
        }

        SIXTRL_HOST_FN char const* device_string() const SIXTRL_NOEXCEPT {
            return this->device_string_by_kind(
                SIXTRL_CXX_NAMESPACE::NODE_DEVICE_STRING_KIND_DEFAULT );
        }

        SIXTRL_HOST_FN std::string const& device_string_str_by_kind(
            device_str_kind_t const kind ) const;

        SIXTRL_HOST_FN char const* device_string_by_kind(
            device_str_kind_t const kind ) const SIXTRL_NOEXCEPT;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN status_t set_device_string(
            device_str_kind_t const device_str_kind,
            std::string const& SIXTRL_RESTRICT_REF device_str ) {
            return this->do_set_device_string( device_str_kind, device_str );
        }

        SIXTRL_HOST_FN status_t remove_device_str(
            device_str_kind_t const device_str_kind ) {
            return this->do_remove_device_string( device_str_kind );
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN status_t update_default_device_strings() {
            return this->do_update_default_device_strings();
        }

        SIXTRL_HOST_FN void clear() { this->do_clear(); }

        SIXTRL_HOST_FN void print(
            std::ostream& SIXTRL_RESTRICT_REF ostr,
            node_print_flags_t const flags =
                SIXTRL_CXX_NAMESPACE::NODE_PRINT_FLAGS_NONE ) const
        {
            this->do_print_device_str_section( ostr, flags );
            this->do_print_base_section( ostr, flags );
            this->do_print_extended_section( ostr, flags );
        }

        SIXTRL_HOST_FN std::string to_string(
            node_print_flags_t const flags =
                SIXTRL_CXX_NAMESPACE::NODE_PRINT_FLAGS_NONE ) const
        {
            std::ostringstream a2str;
            this->print( a2str, flags );
            return a2str.str();
        }

        SIXTRL_HOST_FN status_t to_string_detailed(
            char* SIXTRL_RESTRICT out_buffer, size_type const out_buf_capacity,
            node_print_flags_t const flags ) const;

        SIXTRL_HOST_FN status_t to_string(
            char* SIXTRL_RESTRICT out_buffer,
            size_type const out_buffer_capacity ) const
        {
            return this->to_string_detailed( out_buffer, out_buffer_capacity,
                SIXTRL_CXX_NAMESPACE::NODE_PRINT_FLAGS_NONE );
        }

        SIXTRL_HOST_FN size_type to_string_required_capacity(
            node_print_flags_t const flags ) const
        {
            std::string const temp_str( this->to_string( flags ) );
            return temp_str.size() + size_type{ 1 };
        }

        SIXTRL_HOST_FN friend std::ostream& operator<<(
            std::ostream& SIXTRL_RESTRICT_REF ostr,
            BaseNodeInfo const& SIXTRL_RESTRICT_REF node_info )
        {
            node_info.print( ostr );
            return ostr;
        }

        protected:

        using device_str_map_t = std::map< device_str_kind_t, std::string >;
        using device_str_kinds_t = std::vector< device_str_kind_t >;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN explicit BaseNodeInfo( arch_id_t const arch_id,
            std::string const& SIXTRL_RESTRICT_REF arch_str = std::string{} );

        SIXTRL_HOST_FN BaseNodeInfo( BaseNodeInfo const&
            SIXTRL_RESTRICT_REF orig ) = default;

        SIXTRL_HOST_FN BaseNodeInfo( BaseNodeInfo&&
            SIXTRL_RESTRICT_REF orig ) = default;

        SIXTRL_HOST_FN BaseNodeInfo& operator=(
            BaseNodeInfo const& SIXTRL_RESTRICT_REF rhs ) = default;

        SIXTRL_HOST_FN BaseNodeInfo& operator=(
            BaseNodeInfo&& SIXTRL_RESTRICT_REF rhs ) = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN virtual void do_clear();

        SIXTRL_HOST_FN virtual status_t do_set_device_string(
            device_str_kind_t const kind, std::string const& device_str );

        SIXTRL_HOST_FN virtual status_t do_remove_device_string(
            device_str_kind_t const kind );

        SIXTRL_HOST_FN virtual status_t do_update_default_device_strings();

        SIXTRL_HOST_FN virtual void do_print_device_str_section(
            std::ostream& SIXTRL_RESTRICT_REF ostr,
            node_print_flags_t const flags ) const;

        SIXTRL_HOST_FN virtual void do_print_base_section(
            std::ostream& SIXTRL_RESTRICT_REF ostr,
            node_print_flags_t const flags ) const;

        SIXTRL_HOST_FN virtual void do_print_extended_section(
            std::ostream& SIXTRL_RESTRICT_REF ostr,
            node_print_flags_t const flags ) const;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t update_stored_node_id(
            std::unique_ptr< node_id_t > node_id_to_store ) SIXTRL_NOEXCEPT;

        private:

        SIXTRL_HOST_FN status_t do_set_device_string_base_impl(
            device_str_kind_t const kind,
            std::string const& SIXTRL_RESTRICT_REF device_str );

        SIXTRL_HOST_FN status_t do_remove_device_string_base_impl(
            device_str_kind_t const kind ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t do_update_default_device_strings_base_impl();

        std::unique_ptr< node_id_t > m_stored_node_id;
        device_str_map_t m_device_str_map;
        device_str_kinds_t m_device_str_kinds;

        std::string m_platform_name;
        std::string m_device_name;
        std::string m_description;
    };

} /* ns: SIXTRL_CXX_NAMESPACE */

extern "C" { typedef SIXTRL_CXX_NAMESPACE::BaseNodeInfo NS(BaseNodeInfo); }

#else /* C++, Host */

struct NS(BaseNodeInfo);

#endif /* C++, Host */
#endif /* SIXTRACKLIB_BASE_NODE_NODE_INFO_H__ */
