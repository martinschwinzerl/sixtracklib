#ifndef SIXTRACKLIB_BASE_NODE_NODE_ID_H__
#define SIXTRACKLIB_BASE_NODE_NODE_ID_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/definitions.h"
    #include "sixtracklib_base/backend/definitions.h"
    #include "sixtracklib_base/node/definitions.h"
    #include "sixtracklib_base/internal/class_id.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <cstddef>
        #include <cstdlib>
        #include <cstdio>
        #include <cstring>
        #include <ostream>
        #include <sstream>
        #include <stdexcept>
        #include <string>
    #endif /* C++, Host */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* C++, Host */

struct SIXTRL_BASE_EXPORT_API NS(NodeId)
{
    NS(backend_id_t)            m_backend_id        SIXTRL_ALIGN( 8 );
    NS(node_platform_id_t)   m_platform_id    SIXTRL_ALIGN( 8 );
    NS(node_device_id_t)     m_device_id      SIXTRL_ALIGN( 8 );

    #if defined( __cplusplus )
    friend SIXTRL_HOST_FN bool operator<(
        ::NS(NodeId) const& SIXTRL_RESTRICT_REF lhs,
        ::NS(NodeId) const& SIXTRL_RESTRICT_REF rhs ) SIXTRL_NOEXCEPT
    {
        bool is_smaller = ( lhs.m_backend_id < rhs.m_backend_id );

        if( ( !is_smaller ) && ( lhs.m_backend_id == rhs.m_backend_id ) )
        {
            is_smaller = ( lhs.m_platform_id < rhs.m_platform_id );

            if( ( !is_smaller ) && ( lhs.m_platform_id == rhs.m_platform_id ) )
            {
                is_smaller = ( lhs.m_device_id < rhs.m_device_id );
            }
        }

        return is_smaller;
    }

    friend SIXTRL_HOST_FN bool operator==(
        ::NS(NodeId) const& SIXTRL_RESTRICT_REF lhs,
        ::NS(NodeId) const& SIXTRL_RESTRICT_REF rhs ) SIXTRL_NOEXCEPT
    {
        return ( ( lhs.m_backend_id == rhs.m_backend_id ) &&
                 ( lhs.m_platform_id == rhs.m_platform_id ) &&
                 ( lhs.m_device_id == rhs.m_device_id ) );
    }

    friend SIXTRL_HOST_FN bool operator!=(
        ::NS(NodeId) const& SIXTRL_RESTRICT_REF lhs,
        ::NS(NodeId) const& SIXTRL_RESTRICT_REF rhs ) SIXTRL_NOEXCEPT
    {
        return !( lhs == rhs );
    }

    friend SIXTRL_HOST_FN bool operator>=(
        ::NS(NodeId) const& SIXTRL_RESTRICT_REF lhs,
        ::NS(NodeId) const& SIXTRL_RESTRICT_REF rhs ) SIXTRL_NOEXCEPT
    {
        return !( lhs < rhs );
    }

    friend SIXTRL_HOST_FN bool operator>(
        ::NS(NodeId) const& SIXTRL_RESTRICT_REF lhs,
        ::NS(NodeId) const& SIXTRL_RESTRICT_REF rhs ) SIXTRL_NOEXCEPT
    {
        return !( rhs < lhs );
    }

    friend SIXTRL_HOST_FN bool operator<=(
        ::NS(NodeId) const& SIXTRL_RESTRICT_REF lhs,
        ::NS(NodeId) const& SIXTRL_RESTRICT_REF rhs ) SIXTRL_NOEXCEPT
    {
        return !( rhs < lhs );
    }
    #endif /* C++ ++ */
};

typedef struct NS(NodeId) NS(NodeId);

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    class SIXTRL_BASE_EXPORT_API NodeId : private ::NS(NodeId)
    {
        public:

        using c_node_id_t   = ::NS(NodeId);
        using size_type     = SIXTRL_CXX_NAMESPACE::size_t;
        using platform_id_t = SIXTRL_CXX_NAMESPACE::node_platform_id_t;
        using device_id_t   = SIXTRL_CXX_NAMESPACE::node_device_id_t;
        using str_format_t  = SIXTRL_CXX_NAMESPACE::node_id_str_fmt_t;
        using status_t      = SIXTRL_CXX_NAMESPACE::status_t;
        using backend_id_t  = SIXTRL_CXX_NAMESPACE::backend_id_t;
        using string_type   = std::string;
        using sstream_t     = std::ostringstream;
        using string_char_t = string_type::value_type;

        /* ----------------------------------------------------------------- */

        static constexpr string_char_t
        NODE_ID_STR_NOBACKEND_FORMAT_REGEX_STR[] =
            "([0-9]{1,3})\\.([0-9]{1,3})";

        static constexpr platform_id_t ILLEGAL_PLATFORM_ID =
            SIXTRL_CXX_NAMESPACE::NODE_ILLEGAL_PLATFORM_ID;

        static constexpr device_id_t ILLEGAL_DEVICE_ID =
            SIXTRL_CXX_NAMESPACE::NODE_ILLEGAL_DEVICE_ID;

        static constexpr str_format_t DEFAULT_STR_FORMAT =
            SIXTRL_CXX_NAMESPACE::NODE_ID_STR_FORMAT_DEFAULT;

        /* ----------------------------------------------------------------- */

        static bool NODE_ID_STR_HAS_NOBACKEND_FORMAT(
            string_type const& SIXTRL_RESTRICT_REF node_id_str );

        static bool NODE_ID_STR_HAS_BACKENDID_FORMAT(
            string_type const& SIXTRL_RESTRICT_REF node_id_str );

        static
        bool NODE_ID_STR_HAS_BACKENDID_FORMAT_FOR_BACKEND(
            string_type const& SIXTRL_RESTRICT_REF node_id_str,
            backend_id_t const backend_id );

        static bool NODE_ID_STR_HAS_BACKENDSTR_FORMAT(
            string_type const& SIXTRL_RESTRICT_REF node_id_str );

        static
        bool NODE_ID_STR_HAS_BACKENDSTR_FORMAT_FOR_BACKEND(
            string_type const& SIXTRL_RESTRICT_REF node_id_str,
            backend_id_t const backend_id );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN explicit NodeId(
            backend_id_t const backend_id = SIXTRL_CXX_NAMESPACE::BACKEND_ILLEGAL,
            platform_id_t const platform_id = ILLEGAL_PLATFORM_ID,
            device_id_t const device_id = ILLEGAL_DEVICE_ID ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN explicit NodeId(
            ::NS(NodeId) const& SIXTRL_RESTRICT_REF
                base_node_id ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN explicit NodeId(
            string_type const& SIXTRL_RESTRICT_REF device_str );

        SIXTRL_HOST_FN explicit NodeId(
            string_type const& SIXTRL_RESTRICT_REF device_str,
            str_format_t const device_str_format );

        SIXTRL_HOST_FN NodeId( NodeId const& other ) = default;
        SIXTRL_HOST_FN NodeId( NodeId&& other ) = default;
        SIXTRL_HOST_FN NodeId& operator=( NodeId const& rhs ) = default;
        SIXTRL_HOST_FN NodeId& operator=( NodeId&& rhs ) = default;
        SIXTRL_HOST_FN NodeId& operator=(
            ::NS(NodeId) const& SIXTRL_RESTRICT_REF rhs ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN virtual ~NodeId() = default;

        SIXTRL_HOST_FN bool is_legal() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN backend_id_t backend_id() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN platform_id_t platform_id() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN device_id_t device_id() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t
        set_backend_id( backend_id_t const backend_id ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t
        set_platform_id( platform_id_t const platform_id ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t set_device_id(
            device_id_t const device_id ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN str_format_t find_device_string_format(
            string_type const& SIXTRL_RESTRICT_REF device_str );

        SIXTRL_HOST_FN status_t from_string_using_format(
            string_type const& SIXTRL_RESTRICT_REF device_str,
            str_format_t const format ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t from_string(
            string_type const& SIXTRL_RESTRICT_REF device_string );

        SIXTRL_HOST_FN string_type to_string_using_format(
            str_format_t const str_format ) const;

        SIXTRL_HOST_FN string_type to_string() const;

        SIXTRL_HOST_FN size_type required_device_string_capacity(
            str_format_t const str_format = DEFAULT_STR_FORMAT ) const;

        SIXTRL_HOST_FN status_t to_string_using_format(
            string_char_t* SIXTRL_RESTRICT device_str,
            size_type const device_str_capacity,
            str_format_t const format ) const;

        SIXTRL_HOST_FN status_t to_string(
            string_char_t* SIXTRL_RESTRICT device_str,
            size_type const device_str_capacity ) const;

        SIXTRL_HOST_FN SIXTRL_INLINE bool operator==(
            NodeId const& SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT {
                return ( static_cast< ::NS(NodeId) const& >( *this ) ==
                         static_cast< ::NS(NodeId) const& >( rhs ) ); }

        SIXTRL_HOST_FN SIXTRL_INLINE bool operator!=(
            NodeId const& SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT {
                return ( static_cast< ::NS(NodeId) const& >( *this ) !=
                         static_cast< ::NS(NodeId) const& >( rhs ) ); }

        SIXTRL_HOST_FN SIXTRL_INLINE bool operator>(
            NodeId const& SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT {
                return ( static_cast< ::NS(NodeId) const& >( *this ) >
                         static_cast< ::NS(NodeId) const& >( rhs ) ); }

        SIXTRL_HOST_FN SIXTRL_INLINE bool operator>=(
            NodeId const& SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT {
                return ( static_cast< ::NS(NodeId) const& >( *this ) >=
                         static_cast< ::NS(NodeId) const& >( rhs ) ); }

        SIXTRL_HOST_FN SIXTRL_INLINE bool operator<(
            NodeId const& SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT {
            return ( static_cast< ::NS(NodeId) const& >( *this ) <
                     static_cast< ::NS(NodeId) const& >( rhs ) ); }

        SIXTRL_HOST_FN SIXTRL_INLINE bool operator<=(
            NodeId const& SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT {
                return ( static_cast< ::NS(NodeId) const& >( *this ) >
                         static_cast< ::NS(NodeId) const& >( rhs ) ); }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - */

        SIXTRL_HOST_FN SIXTRL_INLINE bool operator==(
            ::NS(NodeId) const& SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT
        {
            return ( static_cast< ::NS(NodeId) const& >( *this ) == rhs );
        }

        SIXTRL_HOST_FN SIXTRL_INLINE bool operator!=(
            ::NS(NodeId) const& SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT
        {
            return ( static_cast< ::NS(NodeId) const& >( *this ) != rhs );
        }

        SIXTRL_HOST_FN SIXTRL_INLINE bool operator<(
            ::NS(NodeId) const& SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT
        {
            return ( static_cast< ::NS(NodeId) const& >( *this ) < rhs );
        }

        SIXTRL_HOST_FN SIXTRL_INLINE bool operator<=(
            ::NS(NodeId) const& SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT
        {
            return ( static_cast< ::NS(NodeId) const& >( *this ) <= rhs );
        }

        SIXTRL_HOST_FN SIXTRL_INLINE bool operator>(
            ::NS(NodeId) const& SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT
        {
            return ( static_cast< ::NS(NodeId) const& >( *this ) > rhs );
        }

        SIXTRL_HOST_FN SIXTRL_INLINE bool operator>=(
            ::NS(NodeId) const& SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT
        {
            return ( static_cast< ::NS(NodeId) const& >( *this ) >= rhs );
        }

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN void clear() SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN void print(
            std::ostream& SIXTRL_RESTRICT_REF ostr ) const;

        SIXTRL_HOST_FN void print_using_format(
            std::ostream& SIXTRL_RESTRICT_REF ostr,
            str_format_t const format ) const;

        friend SIXTRL_HOST_FN std::ostream& operator<<(
            std::ostream& SIXTRL_RESTRICT_REF ostr,
            NodeId const& SIXTRL_RESTRICT_REF node_id );

        protected:

        SIXTRL_HOST_FN virtual void do_clear();
        SIXTRL_HOST_FN virtual str_format_t do_find_device_string_format(
            string_type const& device_id_str ) const;

        SIXTRL_HOST_FN virtual status_t do_print(
            std::ostream& SIXTRL_RESTRICT_REF ostr,
            str_format_t const device_str_format ) const;

        SIXTRL_HOST_FN virtual status_t do_parse_device_str(
            string_type const& SIXTRL_RESTRICT_REF device_str,
            str_format_t const device_str_format );

        SIXTRL_HOST_FN ::NS(NodeId) const& as_c_node_id() const SIXTRL_NOEXCEPT
        {
            return static_cast< ::NS(NodeId) const& >( *this );
        }

        SIXTRL_HOST_FN ::NS(NodeId)& as_c_node_id() SIXTRL_NOEXCEPT
        {
            return static_cast< ::NS(NodeId)& >( *this );
        }

        private:

        SIXTRL_HOST_FN str_format_t do_find_device_string_format_base_impl(
            string_type const& device_id_str ) const;

        SIXTRL_HOST_FN status_t do_parse_device_str_base_impl(
            string_type const& SIXTRL_RESTRICT_REF device_str,
            str_format_t const device_str_format ) SIXTRL_NOEXCEPT;
    };
}

#endif /* C++, Host */
#endif /* SIXTRACKLIB_BASE_NODE_NODE_ID_H__ */
