#ifndef SIXTRACKLIB_BASE_NODE_DEFINTIONS_H__
#define SIXTRACKLIB_BASE_NODE_DEFINTIONS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/base/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

typedef SIXTRL_INT64_T  NS(node_platform_id_t);
typedef SIXTRL_INT64_T  NS(node_device_id_t);
typedef SIXTRL_INT16_T  NS(node_id_str_fmt_t);
typedef SIXTRL_INT16_T  NS(node_device_str_kind_t);
typedef SIXTRL_UINT64_T NS(node_print_flags_t);

/* ------------------------------------------------------------------------- */

#if !defined( SIXTRL_NODE_ILLEGAL_PLATFORM_ID )
    #define SIXTRL_NODE_ILLEGAL_PLATFORM_ID -1
#endif /* !defined( SIXTRL_NODE_ILLEGAL_PLATFORM_ID ) */

#if !defined( SIXTRL_NODE_ILLEGAL_DEVICE_ID )
    #define SIXTRL_NODE_ILLEGAL_DEVICE_ID -1
#endif /* !defined( SIXTRL_NODE_ILLEGAL_DEVICE_ID ) */

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if !defined( SIXTRL_NODE_ID_STR_FORMAT_NOARCH)
    #define SIXTRL_NODE_ID_STR_FORMAT_NOARCH 0
#endif /* !defined( SIXTRL_NODE_ID_STR_FORMAT_NOARCH) */

#if !defined( SIXTRL_NODE_ID_STR_FORMAT_ARCHID)
    #define SIXTRL_NODE_ID_STR_FORMAT_ARCHID 1
#endif /* !defined( SIXTRL_NODE_ID_STR_FORMAT_ARCHID) */

#if !defined( SIXTRL_NODE_ID_STR_FORMAT_ARCHSTR)
    #define SIXTRL_NODE_ID_STR_FORMAT_ARCHSTR 2
#endif /* !defined( SIXTRL_NODE_ID_STR_FORMAT_ARCHSTR) */

#if !defined( SIXTRL_NODE_ID_STR_FORMAT_DEFAULT)
    #define SIXTRL_NODE_ID_STR_FORMAT_DEFAULT 0
#endif /* !defined( SIXTRL_NODE_ID_STR_FORMAT_DEFAULT) */

#if !defined( SIXTRL_NODE_ID_STR_FORMAT_ILLEGAL)
    #define SIXTRL_NODE_ID_STR_FORMAT_ILLEGAL 0x7fff
#endif /* !defined( SIXTRL_NODE_ID_STR_FORMAT_ILLEGAL) */

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if !defined( SIXTRL_NODE_DEVICE_STRING_KIND_NOARCH )
    #define SIXTRL_NODE_DEVICE_STRING_KIND_NOARCH SIXTRL_NODE_ID_STR_FORMAT_NOARCH
#endif /* !defined( SIXTRL_NODE_DEVICE_STRING_KIND_NOARCH ) */

#if !defined( SIXTRL_NODE_DEVICE_STRING_KIND_ARCHID )
    #define SIXTRL_NODE_DEVICE_STRING_KIND_ARCHID SIXTRL_NODE_ID_STR_FORMAT_ARCHID
#endif /* !defined( SIXTRL_NODE_DEVICE_STRING_KIND_ARCHID ) */

#if !defined( SIXTRL_NODE_DEVICE_STRING_KIND_ARCHSTR )
    #define SIXTRL_NODE_DEVICE_STRING_KIND_ARCHSTR SIXTRL_NODE_ID_STR_FORMAT_ARCHSTR
#endif /* !defined( SIXTRL_NODE_DEVICE_STRING_KIND_ARCHSTR) */

#if !defined( SIXTRL_NODE_DEVICE_STRING_KIND_UUID )
    #define SIXTRL_NODE_DEVICE_STRING_KIND_UUID 4
#endif /* !defined( SIXTRL_NODE_DEVICE_STRING_KIND_UUID) */

#if !defined( SIXTRL_NODE_DEVICE_STRING_KIND_PCI_BUS_ID )
    #define SIXTRL_NODE_DEVICE_STRING_KIND_PCI_BUS_ID 5
#endif /* !defined( SIXTRL_NODE_DEVICE_STRING_KIND_PCI_BUS_ID ) */

#if !defined( SIXTRL_NODE_DEVICE_STRING_KIND_DEFAULT )
    #define SIXTRL_NODE_DEVICE_STRING_KIND_DEFAULT SIXTRL_NODE_ID_STR_FORMAT_ARCHSTR
#endif /* !defined( SIXTRL_NODE_DEVICE_STRING_KIND_DEFAULT ) */

#if !defined( SIXTRL_NODE_DEVICE_STRING_KIND_ILLEGAL)
    #define SIXTRL_NODE_DEVICE_STRING_KIND_ILLEGAL SIXTRL_NODE_ID_STR_FORMAT_ILLEGAL
#endif /* !defined( SIXTRL_NODE_DEVICE_STRING_KIND_ILLEGAL) */

#if !defined( _GPUCODE )
#if defined( __cplusplus )
extern "C" {
#endif /* C++ */

SIXTRL_STATIC_VAR const NS(node_platform_id_t) NS(NODE_ILLEGAL_PLATFORM_ID) =
    ( NS(node_platform_id_t) )SIXTRL_NODE_ILLEGAL_PLATFORM_ID;

SIXTRL_STATIC_VAR const NS(node_device_id_t) NS(NODE_ILLEGAL_DEVICE_ID) =
    ( NS(node_device_id_t) )SIXTRL_NODE_ILLEGAL_DEVICE_ID;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC_VAR const NS(node_id_str_fmt_t) NS(NODE_ID_STR_FORMAT_NOARCH) =
    ( NS(node_id_str_fmt_t) )SIXTRL_NODE_ID_STR_FORMAT_NOARCH;

SIXTRL_STATIC_VAR const NS(node_id_str_fmt_t) NS(NODE_ID_STR_FORMAT_ARCHID) =
    ( NS(node_id_str_fmt_t) )SIXTRL_NODE_ID_STR_FORMAT_ARCHID;

SIXTRL_STATIC_VAR const NS(node_id_str_fmt_t) NS(NODE_ID_STR_FORMAT_ARCHSTR) =
    ( NS(node_id_str_fmt_t) )SIXTRL_NODE_ID_STR_FORMAT_ARCHSTR;

SIXTRL_STATIC_VAR const NS(node_id_str_fmt_t) NS(NODE_ID_STR_FORMAT_DEFAULT) =
    ( NS(node_id_str_fmt_t) )SIXTRL_NODE_ID_STR_FORMAT_DEFAULT;

SIXTRL_STATIC_VAR const NS(node_id_str_fmt_t) NS(NODE_ID_STR_FORMAT_ILLEGAL) =
    ( NS(node_id_str_fmt_t) )SIXTRL_NODE_ID_STR_FORMAT_ILLEGAL;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC_VAR const NS(node_device_str_kind_t)
    NS(NODE_DEVICE_STRING_KIND_NOARCH) = ( NS(node_device_str_kind_t)
        )SIXTRL_NODE_DEVICE_STRING_KIND_NOARCH;

SIXTRL_STATIC_VAR const NS(node_device_str_kind_t)
    NS(NODE_DEVICE_STRING_KIND_ARCHID) = ( NS(node_device_str_kind_t)
        )SIXTRL_NODE_DEVICE_STRING_KIND_ARCHID;

SIXTRL_STATIC_VAR const NS(node_device_str_kind_t)
    NS(NODE_DEVICE_STRING_KIND_ARCHSTR) = ( NS(node_device_str_kind_t)
        )SIXTRL_NODE_DEVICE_STRING_KIND_ARCHSTR;

SIXTRL_STATIC_VAR const NS(node_device_str_kind_t)
    NS(NODE_DEVICE_STRING_KIND_UUID) = ( NS(node_device_str_kind_t)
        )SIXTRL_NODE_DEVICE_STRING_KIND_UUID;

SIXTRL_STATIC_VAR const NS(node_device_str_kind_t)
    NS(NODE_DEVICE_STRING_KIND_PCI_BUS_ID) = ( NS(node_device_str_kind_t)
        )SIXTRL_NODE_DEVICE_STRING_KIND_PCI_BUS_ID;

SIXTRL_STATIC_VAR const NS(node_device_str_kind_t)
    NS(NODE_DEVICE_STRING_KIND_DEFAULT) = ( NS(node_device_str_kind_t)
        )SIXTRL_NODE_DEVICE_STRING_KIND_DEFAULT;

SIXTRL_STATIC_VAR const NS(node_device_str_kind_t)
    NS(NODE_DEVICE_STRING_KIND_ILLEGAL) = ( NS(node_device_str_kind_t)
        )SIXTRL_NODE_DEVICE_STRING_KIND_ILLEGAL;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC_VAR const NS(node_print_flags_t)
    NS(NODE_PRINT_FLAGS_NONE) = ( NS(node_print_flags_t) )0x00;

SIXTRL_STATIC_VAR const NS(node_print_flags_t)
    NS(NODE_PRINT_FLAGS_SELECTED_NODE) = ( NS(node_print_flags_t) )0x01;

SIXTRL_STATIC_VAR const NS(node_print_flags_t)
    NS(NODE_PRINT_FLAGS_DEFAULT_NODE) = ( NS(node_print_flags_t) )0x02;

#if defined( __cplusplus )
}
#endif /* C++ */
#endif /* Host */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    typedef ::NS(node_platform_id_t)        node_platform_id_t;
    typedef ::NS(node_device_id_t)          node_device_id_t;
    typedef ::NS(node_id_str_fmt_t)         node_id_str_fmt_t;
    typedef ::NS(node_device_str_kind_t)    node_device_str_kind_t;
    typedef ::NS(node_print_flags_t)        node_print_flags_t;

    static constexpr node_platform_id_t NODE_ILLEGAL_PLATFORM_ID =
        static_cast< node_platform_id_t >( SIXTRL_NODE_ILLEGAL_PLATFORM_ID );

    static constexpr node_device_id_t NODE_ILLEGAL_DEVICE_ID =
        static_cast< node_device_id_t >( SIXTRL_NODE_ILLEGAL_DEVICE_ID );

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    static constexpr node_id_str_fmt_t NODE_ID_STR_FORMAT_NOARCH =
        static_cast< node_id_str_fmt_t >( SIXTRL_NODE_ID_STR_FORMAT_NOARCH );

    static constexpr node_id_str_fmt_t NODE_ID_STR_FORMAT_ARCHID =
        static_cast< node_id_str_fmt_t >( SIXTRL_NODE_ID_STR_FORMAT_ARCHID );

    static constexpr node_id_str_fmt_t NODE_ID_STR_FORMAT_ARCHSTR =
        static_cast< node_id_str_fmt_t >( SIXTRL_NODE_ID_STR_FORMAT_ARCHSTR );

    static constexpr node_id_str_fmt_t NODE_ID_STR_FORMAT_DEFAULT =
        static_cast< node_id_str_fmt_t >( SIXTRL_NODE_ID_STR_FORMAT_DEFAULT );

    static constexpr node_id_str_fmt_t NODE_ID_STR_FORMAT_ILLEGAL =
        static_cast< node_id_str_fmt_t >( SIXTRL_NODE_ID_STR_FORMAT_ILLEGAL );

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    static constexpr const node_device_str_kind_t
        NODE_DEVICE_STRING_KIND_NOARCH = static_cast< node_device_str_kind_t >(
            SIXTRL_NODE_DEVICE_STRING_KIND_NOARCH );

    static constexpr const node_device_str_kind_t
        NODE_DEVICE_STRING_KIND_ARCHID = static_cast< node_device_str_kind_t >(
            SIXTRL_NODE_DEVICE_STRING_KIND_ARCHID );

    static constexpr const node_device_str_kind_t
        NODE_DEVICE_STRING_KIND_ARCHSTR = static_cast< node_device_str_kind_t >(
            SIXTRL_NODE_DEVICE_STRING_KIND_ARCHSTR );

    static constexpr const node_device_str_kind_t
        NODE_DEVICE_STRING_KIND_UUID = static_cast< node_device_str_kind_t >(
            SIXTRL_NODE_DEVICE_STRING_KIND_UUID );

    static constexpr const node_device_str_kind_t
        NODE_DEVICE_STRING_KIND_PCI_BUS_ID = static_cast<
            node_device_str_kind_t >(
                SIXTRL_NODE_DEVICE_STRING_KIND_PCI_BUS_ID );

    static constexpr const node_device_str_kind_t
        NODE_DEVICE_STRING_KIND_DEFAULT = static_cast< node_device_str_kind_t >(
            SIXTRL_NODE_DEVICE_STRING_KIND_DEFAULT );

    static constexpr const node_device_str_kind_t
        NODE_DEVICE_STRING_KIND_ILLEGAL = static_cast< node_device_str_kind_t >(
            SIXTRL_NODE_DEVICE_STRING_KIND_ILLEGAL );

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    static constexpr node_print_flags_t NODE_PRINT_FLAGS_NONE =
        static_cast< node_print_flags_t >( 0x00 );

    static constexpr node_print_flags_t NODE_PRINT_FLAGS_SELECTED_NODE =
        static_cast< node_print_flags_t >( 0x01 );

    static constexpr node_print_flags_t NODE_PRINT_FLAGS_DEFAULT_NODE =
        static_cast< node_print_flags_t >( 0x02 );

} /* ns: SIXTRL_CXX_NAMESPACE */
#endif /* C++ */
#endif /* SIXTRACKLIB_BASE_NODE_DEFINTIONS_H__ */
