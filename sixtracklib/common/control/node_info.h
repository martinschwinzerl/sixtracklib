#ifndef SIXTRACKLIB_COMMON_CONTROL_NODE_INFO_BASE_HPP__
#define SIXTRACKLIB_COMMON_CONTROL_NODE_INFO_BASE_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/node_id.h"
    #include "sixtracklib/common/backends/backend_obj_base.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus )
    #include <cstdio>
    #include <cstring>
    #include <ostream>
    #include <sstream>
    #include <string>
#elif !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <string.h>
    #include <stdio.h>
    #include <stdbool.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES )  && defined( __cplusplus ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    class NodeInfoBase : public BackendObjBase
    {
        public:

        using node_id_type              = SIXTRL_CXX_NAMESPACE::NodeId;
        using platform_id_type          = node_id_type::platform_id_type;
        using device_id_type            = node_id_type::device_id_type;
        using node_index_type           = node_id_type::index_type;
        using size_type                 = node_id_type::size_type;
        using node_id_str_format_type   = node_id_type::str_format_type;

        static constexpr class_id_type BASE_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::NODE_INFO_BASE_CLASS_ID;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN virtual ~NodeInfoBase() = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN node_id_type const& node_id() const SIXTRL_NOEXCEPT {
            return this->m_node_id; }

        SIXTRL_HOST_FN node_id_type& node_id() SIXTRL_NOEXCEPT {
            return this->m_node_id; }

        SIXTRL_HOST_FN node_id_type const* ptr_node_id() const SIXTRL_NOEXCEPT {
            return &this->node_id(); }

        SIXTRL_HOST_FN node_id_type* ptr_node_id() SIXTRL_NOEXCEPT {
            return &this->node_id(); }

        SIXTRL_HOST_FN platform_id_type platform_id() const SIXTRL_NOEXCEPT {
            return this->node_id().platform_id(); }

        SIXTRL_HOST_FN void set_platform_id( platform_id_type const id
            ) SIXTRL_NOEXCEPT { this->node_id().set_platform_id( id ); }

        SIXTRL_HOST_FN device_id_type device_id() const SIXTRL_NOEXCEPT {
            return this->node_id().device_id(); }

        SIXTRL_HOST_FN void set_device_id( device_id_type const device_id
            ) SIXTRL_NOEXCEPT { this->node_id().set_device_id( device_id ); }

        SIXTRL_HOST_FN bool has_node_index() const SIXTRL_NOEXCEPT {
            return this->node_id().has_index(); }

        SIXTRL_HOST_FN node_index_type node_index() const SIXTRL_NOEXCEPT {
            return this->node_id().index(); }

        SIXTRL_HOST_FN void set_node_index( node_index_type const node_index
            ) SIXTRL_NOEXCEPT { this->node_id().set_index( node_index ); }

        SIXTRL_HOST_FN bool is_default_node(
            node_id_type const& default_node_id ) const SIXTRL_NOEXCEPT {
                return ( default_node_id.compare( this->node_id() ) == 0 ); }

        SIXTRL_HOST_FN bool is_selected_node(
            node_id_type const& selected_node_id ) const SIXTRL_NOEXCEPT {
                return ( selected_node_id.compare( this->node_id() ) == 0 ); }

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool has_platform_name() const SIXTRL_NOEXCEPT {
            return !this->m_platform_name.empty(); }

        SIXTRL_HOST_FN std::string const& platform_name_str(
            ) const SIXTRL_NOEXCEPT { return this->m_platform_name; }

        SIXTRL_HOST_FN char const* platform_name() const SIXTRL_NOEXCEPT {
            return this->m_platform_name.c_str(); }

        SIXTRL_HOST_FN void set_platform_name(
            std::string const& SIXTRL_RESTRICT_REF platform_name ) {
            this->m_platform_name = platform_name; }

        SIXTRL_HOST_FN bool has_device_name() const SIXTRL_NOEXCEPT {
            return !this->m_device_name.empty(); }

        SIXTRL_HOST_FN std::string const& device_name_str() const
            SIXTRL_NOEXCEPT { return this->m_device_name; }

        SIXTRL_HOST_FN char const* device_name() const SIXTRL_NOEXCEPT {
            return this->m_device_name.c_str(); }

        SIXTRL_HOST_FN void set_device_name(
            std::string const& SIXTRL_RESTRICT_REF device_name ) {
            this->m_device_name = device_name; }

        SIXTRL_HOST_FN bool has_description() const SIXTRL_NOEXCEPT {
            return !this->m_description.empty(); }

        SIXTRL_HOST_FN std::string const& description_str() const
            SIXTRL_NOEXCEPT { return this->m_description; }

        SIXTRL_HOST_FN char const* description() const SIXTRL_NOEXCEPT {
            return this->m_description.c_str(); }

        SIXTRL_HOST_FN void set_description(
            std::string const& SIXTRL_RESTRICT_REF description ) {
                this->m_description = description; }

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_type to_stream( std::ostream& ostr,
            node_id_str_format_type const node_id_str_format =
                node_id_type::DEFAULT_STR_FORMAT,
            node_id_type const* ptr_default_node_id = nullptr,
            node_id_type const* ptr_selected_node_id = nullptr ) const {
            return this->do_print_to_stream( ostr, node_id_str_format,
                ptr_default_node_id, ptr_selected_node_id ); }

        SIXTRL_HOST_FN friend std::ostream& operator<<(
            std::ostream& SIXTRL_RESTRICT_REF output,
            NodeInfoBase const& SIXTRL_RESTRICT_REF node_info ) {
            node_info.do_print_to_stream( output,
                node_id_type::DEFAULT_STR_FORMAT, nullptr, nullptr );
            return output; }

        SIXTRL_HOST_FN std::string to_string(
            node_id_str_format_type const node_id_str_format =
                node_id_type::DEFAULT_STR_FORMAT,
            node_id_type const* ptr_default_node_id = nullptr,
            node_id_type const* ptr_selected_node_id = nullptr ) const
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            std::ostringstream a2str;

            return ( st::STATUS_SUCCESS == this->do_print_to_stream( a2str,
                node_id_str_format, ptr_default_node_id, ptr_selected_node_id ) )
                ? a2str.str() : std::string{};
        }

        SIXTRL_HOST_FN size_type required_string_capacity(
            node_id_str_format_type const node_id_str_format =
                node_id_type::DEFAULT_STR_FORMAT,
            node_id_type const* ptr_default_node_id = nullptr,
            node_id_type const* ptr_selected_node_id = nullptr ) const {
            namespace st = SIXTRL_CXX_NAMESPACE;
            std::ostringstream a2str;

            return ( st::STATUS_SUCCESS == this->do_print_to_stream(
                a2str, node_id_str_format, ptr_default_node_id,
                    ptr_selected_node_id ) )
                ? a2str.str().size() + size_type{ 1 } : size_type{ 0 };
        }

        SIXTRL_HOST_FN status_type to_string(
            SIXTRL_ARGPTR_DEC char* SIXTRL_RESTRICT str,
            size_type const str_capacity,
            node_id_str_format_type const node_id_str_format =
                node_id_type::DEFAULT_STR_FORMAT,
            node_id_type const* ptr_default_node_id = nullptr,
            node_id_type const* ptr_selected_node_id = nullptr ) const
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            status_type status = st::STATUS_GENERAL_FAILURE;

            if( ( str != nullptr ) && ( str_capacity > size_type{ 0 } ) )
            {
                std::ostringstream a2str;
                status = this->do_print_to_stream( a2str, node_id_str_format,
                    ptr_default_node_id, ptr_selected_node_id );

                if( st::STATUS_SUCCESS == status ) {
                    std::string const temp = a2str.str();
                    if( str_capacity > temp.size() ) std::strncat(
                        str, temp.c_str(), str_capacity - size_type{ 1 } ); }
            }

            return status;
        }

        protected:

        SIXTRL_HOST_FN NodeInfoBase(
            backend_id_type const backend_id,
            class_id_type const derived_class_id,
            platform_id_type const platform_id = node_id_type::ILLEGAL_PLATFORM_ID,
            device_id_type const device_id = node_id_type::ILLEGAL_DEVICE_ID,
            std::string const& SIXTRL_RESTRICT_REF platform_str = std::string{},
            std::string const& SIXTRL_RESTRICT_REF device_str = std::string{},
            std::string const& SIXTRL_RESTRICT_REF descr_str = std::string{},
            node_index_type const node_index = node_id_type::ILLEGAL_INDEX ) :
            BackendObjBase( backend_id, NodeInfoBase::BASE_CLASS_ID,
                            derived_class_id ),
            m_node_id( platform_id, device_id, node_index ),
            m_platform_name( platform_str ), m_device_name( device_str ),
            m_description( descr_str )
        {

        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN NodeInfoBase( NodeInfoBase const& other ) = default;
        SIXTRL_HOST_FN NodeInfoBase( NodeInfoBase&& other ) = default;

        SIXTRL_HOST_FN NodeInfoBase& operator=(
            NodeInfoBase&& rhs ) = default;

        SIXTRL_HOST_FN NodeInfoBase& operator=(
            NodeInfoBase const& rhs ) = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN virtual status_type do_print_to_stream(
            std::ostream& SIXTRL_RESTRICT_REF output,
            node_id_str_fmt_type const node_id_str_format,
            const node_id_type *const ptr_default_node_id,
            const node_id_type *const ptr_selected_node_id ) const;

        private:

        node_id_type    m_node_id;

        std::string     m_platform_name;
        std::string     m_device_name;
        std::string     m_description;
    };

    template<> struct BackendObjTraits< SIXTRL_CXX_NAMESPACE::NodeInfoBase >
    {
        static constexpr backend_id_type BACKEND_ID =
            SIXTRL_CXX_NAMESPACE::BACKEND_ID_NONE;

        static constexpr derived_class_id_type BASE_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::NODE_INFO_BASE_CLASS_ID;

        static constexpr derived_class_id_type DERIVED_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::NODE_INFO_BASE_CLASS_ID;
    };

    template<> struct BackendObjInvTraits<
        SIXTRL_CXX_NAMESPACE::BACKEND_ID_NONE,
        SIXTRL_CXX_NAMESPACE::NODE_INFO_BASE_CLASS_ID >
    {
        typedef SIXTRL_CXX_NAMESPACE::NodeInfoBase backend_obj_type;
    };
}
#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
typedef SIXTRL_CXX_NAMESPACE::NodeInfoBase  NS(NodeInfoBase);
#else /* C++, Host */
typedef void NS(NodeInfoBase);
#endif /* C++, Host */

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN NS(backend_id_type) NS(NodeInfo_backend_id)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const
        SIXTRL_RESTRICT info ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN char const* NS(NodeInfo_backend_str)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const
        SIXTRL_RESTRICT info ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(derived_class_id_type)
NS(NodeInfo_base_class_id)( SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const
    SIXTRL_RESTRICT info ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(derived_class_id_type)
NS(NodeInfo_required_class_id)( SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const
    SIXTRL_RESTRICT info ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeInfo_delete)(
    NS(NodeInfoBase)* SIXTRL_RESTRICT node_info ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(NodeId) const*
NS(NodeInfo_const_node_id)( SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const
    SIXTRL_RESTRICT info ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(NodeId)* NS(NodeInfo_node_id)(
    SIXTRL_ARGPTR_DEC NS(NodeInfoBase)* SIXTRL_RESTRICT info ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_platform_id_type)
NS(NodeInfo_platform_id)( SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const
    SIXTRL_RESTRICT info ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeInfo_set_platform_id)(
    SIXTRL_ARGPTR_DEC NS(NodeInfoBase)* SIXTRL_RESTRICT info,
    NS(node_platform_id_type) const platform_id ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_device_id_type) NS(NodeInfo_device_id)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const
        SIXTRL_RESTRICT info ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeInfo_set_device_id)(
    SIXTRL_ARGPTR_DEC NS(NodeInfoBase)* SIXTRL_RESTRICT info,
    NS(node_device_id_type) const device_id ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeInfo_has_node_index)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const
        SIXTRL_RESTRICT info ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_index_type) NS(NodeInfo_node_index)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const
        SIXTRL_RESTRICT info ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeInfo_set_node_index)(
    SIXTRL_ARGPTR_DEC NS(NodeInfoBase)* SIXTRL_RESTRICT info,
    NS(node_index_type) node_index ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeInfo_is_default_node)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT default_node_id
) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeInfo_is_selected_node)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT selected_node_id
) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeInfo_has_platform_name)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const
        SIXTRL_RESTRICT info ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN char const* NS(NodeInfo_platform_name)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const
        SIXTRL_RESTRICT info ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeInfo_set_platform_name)(
    SIXTRL_ARGPTR_DEC NS(NodeInfoBase)* SIXTRL_RESTRICT info,
    SIXTRL_ARGPTR_DEC const char *const SIXTRL_RESTRICT platform_name );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeInfo_has_device_name)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const
        SIXTRL_RESTRICT info ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN char const* NS(NodeInfo_device_name)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const
        SIXTRL_RESTRICT info ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeInfo_set_device_name)(
    SIXTRL_ARGPTR_DEC NS(NodeInfoBase)* SIXTRL_RESTRICT info,
    SIXTRL_ARGPTR_DEC const char *const SIXTRL_RESTRICT device_name );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeInfo_has_description)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const
        SIXTRL_RESTRICT info ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN char const* NS(NodeInfo_description)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const
        SIXTRL_RESTRICT info ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeInfo_set_description)(
    SIXTRL_ARGPTR_DEC NS(NodeInfoBase)* SIXTRL_RESTRICT info,
    SIXTRL_ARGPTR_DEC const char *const SIXTRL_RESTRICT description );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(size_type)
NS(NodeInfo_required_string_capacity)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const SIXTRL_RESTRICT node_info );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(size_type)
NS(NodeInfo_required_string_capacity_detailed)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const SIXTRL_RESTRICT node_info,
    NS(node_id_str_fmt_type) const node_id_str_format,
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT default_node_id,
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT selected_node_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(status_type) NS(NodeInfo_to_string)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const SIXTRL_RESTRICT node_info,
    char* SIXTRL_RESTRICT node_info_str,
    NS(size_type) const node_info_str_capacity );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(status_type) NS(NodeInfo_to_string_detailed)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const SIXTRL_RESTRICT node_info,
    char* SIXTRL_RESTRICT node_info_str,
    NS(size_type) const node_info_str_capacity,
    NS(node_id_str_fmt_type) const node_id_str_format,
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT default_node_id,
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT selected_node_id );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeInfo_print)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    FILE* SIXTRL_RESTRICT output );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeInfo_print_detailed)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    FILE* SIXTRL_RESTRICT output,
    NS(node_id_str_fmt_type) const node_id_str_format,
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT default_node_id,
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT selected_node_id );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeInfo_print_out)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const SIXTRL_RESTRICT info );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeInfo_print_out_detailed)(
    SIXTRL_ARGPTR_DEC const NS(NodeInfoBase) *const SIXTRL_RESTRICT info,
    NS(node_id_str_fmt_type) const node_id_str_format,
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT default_node_id,
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT selected_node_id );

#endif /* !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_COMMON_CONTROL_NODE_INFO_BASE_HPP__ */
