#ifndef SIXTRACKLIB_BASE_NODE_TOOLS_H__
#define SIXTRACKLIB_BASE_NODE_TOOLS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/base/definitions.h"
    #include "sixtracklib/base/architecture/definitions.h"
    #include "sixtracklib/base/node/definitions.h"
    #include "sixtracklib/base/node/node_id.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <string>
    #else
        #include <stdbool.h>
    #endif /* C++ */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    SIXTRL_BASE_EXPORT_API SIXTRL_EXTERN SIXTRL_HOST_FN bool
    Node_is_device_str_kind_a_node_id_format(
        node_device_str_kind_t const kind ) SIXTRL_NOEXCEPT;

    SIXTRL_BASE_EXPORT_API SIXTRL_EXTERN SIXTRL_HOST_FN bool
    Node_is_node_id_format_device_str_kind(
        node_id_str_fmt_t const format ) SIXTRL_NOEXCEPT;

    SIXTRL_BASE_EXPORT_API SIXTRL_EXTERN SIXTRL_HOST_FN node_id_str_fmt_t
    Node_convert_device_str_kind_to_node_id_format(
        node_device_str_kind_t const kind ) SIXTRL_NOEXCEPT;

    SIXTRL_BASE_EXPORT_API SIXTRL_EXTERN SIXTRL_HOST_FN node_device_str_kind_t
    Node_convert_node_id_format_to_device_str_kind(
        node_id_str_fmt_t const format ) SIXTRL_NOEXCEPT;

    /* --------------------------------------------------------------------- */

    SIXTRL_BASE_EXPORT_API SIXTRL_EXTERN SIXTRL_HOST_FN
    bool Node_id_format_is_noarch(
        std::string const& SIXTRL_RESTRICT_REF node_id_str );

    SIXTRL_BASE_EXPORT_API SIXTRL_EXTERN SIXTRL_HOST_FN
    bool Node_id_format_is_archid(
        std::string const& SIXTRL_RESTRICT_REF node_id_str );

    SIXTRL_BASE_EXPORT_API SIXTRL_EXTERN SIXTRL_HOST_FN
    bool Node_id_format_is_archstr(
        std::string const& SIXTRL_RESTRICT_REF node_id_str );

    SIXTRL_BASE_EXPORT_API SIXTRL_EXTERN SIXTRL_HOST_FN
    node_id_str_fmt_t Node_find_node_id_format(
        std::string const& SIXTRL_RESTRICT_REF node_id_str );

    /* --------------------------------------------------------------------- */

    SIXTRL_BASE_EXPORT_API SIXTRL_EXTERN SIXTRL_HOST_FN status_t
    NodeId_parse( ::NS(NodeId)& SIXTRL_RESTRICT_REF node_id,
        std::string const& SIXTRL_RESTRICT_REF node_id_str );

    SIXTRL_BASE_EXPORT_API SIXTRL_EXTERN SIXTRL_HOST_FN status_t
    NodeId_parse_using_format( ::NS(NodeId)& SIXTRL_RESTRICT_REF node_id,
        std::string const& SIXTRL_RESTRICT_REF node_id_str,
        node_id_str_fmt_t const format );

    /* --------------------------------------------------------------------- */

    SIXTRL_BASE_EXPORT_API SIXTRL_EXTERN SIXTRL_HOST_FN
    bool Node_device_str_is_noarch(
        std::string const& SIXTRL_RESTRICT_REF device_str );

    SIXTRL_BASE_EXPORT_API SIXTRL_EXTERN SIXTRL_HOST_FN
    bool Node_device_str_is_archid(
        std::string const& SIXTRL_RESTRICT_REF device_str );

    SIXTRL_BASE_EXPORT_API SIXTRL_EXTERN SIXTRL_HOST_FN
    bool Node_device_str_is_archstr(
        std::string const& SIXTRL_RESTRICT_REF device_str );

    SIXTRL_BASE_EXPORT_API SIXTRL_EXTERN SIXTRL_HOST_FN
    bool Node_device_str_is_uuid(
        std::string const& SIXTRL_RESTRICT_REF device_str );

    SIXTRL_BASE_EXPORT_API SIXTRL_EXTERN SIXTRL_HOST_FN
    bool Node_device_str_is_pci_bus_id(
        std::string const& SIXTRL_RESTRICT_REF device_str );

    SIXTRL_BASE_EXPORT_API SIXTRL_EXTERN SIXTRL_HOST_FN
    node_device_str_kind_t Node_find_device_str_kind_from_device_str(
        std::string const& SIXTRL_RESTRICT_REF device_str );
}
#endif /* C++ */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_BASE_EXPORT_API SIXTRL_EXTERN SIXTRL_HOST_FN bool
NS(Node_is_device_str_kind_a_node_id_format)(
    NS(node_device_str_kind_t) const kind ) SIXTRL_NOEXCEPT;

SIXTRL_BASE_EXPORT_API SIXTRL_EXTERN SIXTRL_HOST_FN bool
NS(Node_is_node_id_format_device_str_kind)(
    NS(node_id_str_fmt_t) const format ) SIXTRL_NOEXCEPT;

SIXTRL_BASE_EXPORT_API SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_id_str_fmt_t)
NS(Node_convert_device_str_kind_to_node_id_format)(
    NS(node_device_str_kind_t) const kind ) SIXTRL_NOEXCEPT;

SIXTRL_BASE_EXPORT_API SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_device_str_kind_t)
NS(Node_convert_node_id_format_to_device_str_kind)(
    NS(node_id_str_fmt_t) const format ) SIXTRL_NOEXCEPT;

/* ------------------------------------------------------------------------- */

SIXTRL_BASE_EXPORT_API SIXTRL_EXTERN SIXTRL_HOST_FN
bool NS(Node_id_format_is_noarch)( char const* SIXTRL_RESTRICT node_id_str );

SIXTRL_BASE_EXPORT_API SIXTRL_EXTERN SIXTRL_HOST_FN
bool NS(Node_id_format_is_archid)( char const* SIXTRL_RESTRICT node_id_str );

SIXTRL_BASE_EXPORT_API SIXTRL_EXTERN SIXTRL_HOST_FN
bool NS(Node_id_format_is_archstr)( char const* SIXTRL_RESTRICT node_id_str );

SIXTRL_BASE_EXPORT_API SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_id_str_fmt_t)
NS(Node_find_node_id_format)( char const* SIXTRL_RESTRICT node_id_str );

/* ------------------------------------------------------------------------- */

SIXTRL_BASE_EXPORT_API SIXTRL_EXTERN SIXTRL_HOST_FN NS(status_t)
NS(NodeId_parse)( NS(NodeId)* SIXTRL_RESTRICT node_id,
    char const* SIXTRL_RESTRICT node_id_str );

SIXTRL_BASE_EXPORT_API SIXTRL_EXTERN SIXTRL_HOST_FN NS(status_t)
NS(NodeId_parse_using_format)( NS(NodeId)* SIXTRL_RESTRICT node_id,
    char const* SIXTRL_RESTRICT node_id_str,
    NS(node_id_str_fmt_t) const format );

/* ------------------------------------------------------------------------- */

SIXTRL_BASE_EXPORT_API SIXTRL_EXTERN SIXTRL_HOST_FN
bool NS(Node_device_str_is_noarch)( char const* SIXTRL_RESTRICT device_str );

SIXTRL_BASE_EXPORT_API SIXTRL_EXTERN SIXTRL_HOST_FN
bool NS(Node_device_str_is_archid)(char const* SIXTRL_RESTRICT device_str );

SIXTRL_BASE_EXPORT_API SIXTRL_EXTERN SIXTRL_HOST_FN
bool NS(Node_device_str_is_archstr)( char const* SIXTRL_RESTRICT device_str );

SIXTRL_BASE_EXPORT_API SIXTRL_EXTERN SIXTRL_HOST_FN
bool NS(Node_device_str_is_uuid)( char const* SIXTRL_RESTRICT device_str );

SIXTRL_BASE_EXPORT_API SIXTRL_EXTERN SIXTRL_HOST_FN
bool NS(Node_device_str_is_pci_bus_id)(
    char const* SIXTRL_RESTRICT device_str );

SIXTRL_BASE_EXPORT_API SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_device_str_kind_t)
NS(Node_find_device_str_kind_from_device_str)(
    char const* SIXTRL_RESTRICT device_str );

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#endif /* SIXTRACKLIB_BASE_NODE_TOOLS_H__ */
