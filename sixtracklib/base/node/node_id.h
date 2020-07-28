#ifndef SIXTRACKLIB_BASE_NODE_NODE_ID_H__
#define SIXTRACKLIB_BASE_NODE_NODE_ID_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/base/definitions.h"
    #include "sixtracklib/base/architecture/definitions.h"
    #include "sixtracklib/base/node/definitions.h"
    #include "sixtracklib/base/internal/class_id.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <cstddef>
        #include <cstdlib>
        #include <cstdio>
        #include <cstring>
        #include <string>
        #include <stdexcept>
        #include <ostream>
    #endif /* C++, Host */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* C++, Host */

struct SIXTRL_BASE_EXPORT_API NS(NodeId)
{
    NS(arch_id_t)            m_arch_id        SIXTRL_ALIGN( 8 );
    NS(node_platform_id_t)   m_platform_id    SIXTRL_ALIGN( 8 );
    NS(node_device_id_t)     m_device_id      SIXTRL_ALIGN( 8 );
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

        using size_type     = SIXTRL_CXX_NAMESPACE::size_t;
        using platform_id_t = SIXTRL_CXX_NAMESPACE::node_platform_id_t;
        using device_id_t   = SIXTRL_CXX_NAMESPACE::node_device_id_t;
        using str_format_t  = SIXTRL_CXX_NAMESPACE::node_id_str_fmt_t;
        using status_t      = SIXTRL_CXX_NAMESPACE::status_t;
        using arch_id_t     = SIXTRL_CXX_NAMESPACE::arch_id_t;

        static constexpr platform_id_t ILLEGAL_PLATFORM_ID =
            SIXTRL_CXX_NAMESPACE::NODE_ILLEGAL_PLATFORM_ID;

        static constexpr device_id_t ILLEGAL_DEVICE_ID =
            SIXTRL_CXX_NAMESPACE::NODE_ILLEGAL_DEVICE_ID;

        static constexpr str_format_t DEFAULT_STR_FORMAT =
            SIXTRL_CXX_NAMESPACE::NODE_ID_STR_FORMAT_DEFAULT;

        SIXTRL_HOST_FN explicit NodeId(
            arch_id_t const arch_id = SIXTRL_CXX_NAMESPACE::ARCHITECTURE_ILLEGAL,
            platform_id_t const platform_id = ILLEGAL_PLATFORM_ID,
            device_id_t const device_id = ILLEGAL_DEVICE_ID ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN explicit NodeId(
            std::string const& SIXTRL_RESTRICT_REF device_str );

        SIXTRL_HOST_FN explicit NodeId(
            std::string const& SIXTRL_RESTRICT_REF device_str,
            str_format_t const device_str_format );

        SIXTRL_HOST_FN NodeId( NodeId const& other ) = default;
        SIXTRL_HOST_FN NodeId( NodeId&& other ) = default;

        SIXTRL_HOST_FN NodeId& operator=( NodeId const& rhs ) = default;
        SIXTRL_HOST_FN NodeId& operator=( NodeId&& rhs ) = default;

        SIXTRL_HOST_FN virtual ~NodeId() = default;

        SIXTRL_BASE_EXPORT_API SIXTRL_HOST_FN SIXTRL_INLINE
        bool is_legal() const SIXTRL_NOEXCEPT { return
            ( this->m_arch_id != SIXTRL_CXX_NAMESPACE::ARCHITECTURE_ILLEGAL ) &&
            ( this->m_platform_id != ILLEGAL_PLATFORM_ID ) &&
            ( this->m_device_id != ILLEGAL_DEVICE_ID );
        }

        SIXTRL_BASE_EXPORT_API SIXTRL_HOST_FN SIXTRL_INLINE arch_id_t arch_id()
            const SIXTRL_NOEXCEPT { return this->m_arch_id; }

        SIXTRL_BASE_EXPORT_API SIXTRL_HOST_FN SIXTRL_INLINE platform_id_t
            platform_id() const SIXTRL_NOEXCEPT { return this->m_platform_id; }

        SIXTRL_BASE_EXPORT_API SIXTRL_HOST_FN SIXTRL_INLINE device_id_t
            device_id() const SIXTRL_NOEXCEPT { return this->m_device_id; }

        SIXTRL_BASE_EXPORT_API SIXTRL_HOST_FN SIXTRL_INLINE status_t
        set_arch_id( arch_id_t const arch_id ) SIXTRL_NOEXCEPT {
            this->m_arch_id = arch_id;
            return SIXTRL_CXX_NAMESPACE::STATUS_SUCCESS;
        }

        SIXTRL_BASE_EXPORT_API SIXTRL_HOST_FN SIXTRL_INLINE status_t
        set_platform_id( platform_id_t const platform_id ) SIXTRL_NOEXCEPT
        {
            this->m_platform_id = platform_id;
            return SIXTRL_CXX_NAMESPACE::STATUS_SUCCESS;
        }

        SIXTRL_BASE_EXPORT_API SIXTRL_HOST_FN SIXTRL_INLINE status_t
        set_device_id( device_id_t const device_id ) SIXTRL_NOEXCEPT
        {
            this->m_device_id = device_id;
            return SIXTRL_CXX_NAMESPACE::STATUS_SUCCESS;
        }

        SIXTRL_BASE_EXPORT_API SIXTRL_HOST_FN str_format_t
        find_device_string_format( std::string const&
            SIXTRL_RESTRICT_REF device_str ) {
            return this->do_find_device_string_format( device_str ); }

        SIXTRL_HOST_FN status_t from_string_using_format(
            std::string const& SIXTRL_RESTRICT_REF device_str,
            str_format_t const format ) SIXTRL_NOEXCEPT {
            return this->do_parse_device_str( device_str, format );
        }

        SIXTRL_BASE_EXPORT_API SIXTRL_HOST_FN SIXTRL_INLINE status_t
        from_string( std::string const& SIXTRL_RESTRICT_REF device_string ) {
            return this->from_string_using_format( device_string,
                this->find_device_string_format( device_string ) );
        }

        SIXTRL_HOST_FN std::string to_string_using_format(
            str_format_t const str_format ) const;

        SIXTRL_BASE_EXPORT_API SIXTRL_HOST_FN SIXTRL_INLINE
        std::string to_string() const {
            return this->to_string_using_format( DEFAULT_STR_FORMAT );
        }

        SIXTRL_BASE_EXPORT_API SIXTRL_HOST_FN SIXTRL_INLINE size_type
        required_device_string_capacity(
            str_format_t const str_format = DEFAULT_STR_FORMAT ) const
        {
            std::string const temp_device_str(
                this->to_string_using_format( str_format ) );
            return temp_device_str.size() + size_type{ 1 };
        }

        SIXTRL_HOST_FN status_t to_string_using_format(
            char* SIXTRL_RESTRICT device_str,
            size_type const device_str_capacity,
            str_format_t const format ) const;

        SIXTRL_BASE_EXPORT_API SIXTRL_HOST_FN SIXTRL_INLINE status_t to_string(
            char* SIXTRL_RESTRICT device_str,
            size_type const device_str_capacity ) const {
            return this->to_string_using_format( device_str,
                device_str_capacity, DEFAULT_STR_FORMAT );
        }

        SIXTRL_BASE_EXPORT_API SIXTRL_HOST_FN SIXTRL_INLINE bool operator<(
            NodeId const& SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT {

            bool is_smaller = ( this->m_arch_id < rhs.m_arch_id );

            if( ( !is_smaller ) && ( this->m_arch_id == rhs.m_arch_id ) )
            {
                is_smaller = ( this->m_platform_id < rhs.m_platform_id );

                if( ( !is_smaller ) &&
                    ( this->m_platform_id == rhs.m_platform_id ) )
                {
                    is_smaller = ( this->m_device_id < rhs.m_device_id );
                }
            }

            return is_smaller;
        }

        SIXTRL_BASE_EXPORT_API SIXTRL_HOST_FN SIXTRL_INLINE
        void clear() SIXTRL_NOEXCEPT { this->do_clear(); }

        /* ----------------------------------------------------------------- */

        SIXTRL_BASE_EXPORT_API SIXTRL_HOST_FN SIXTRL_INLINE void print(
            std::ostream& SIXTRL_RESTRICT_REF ostr ) const {
            this->do_print( ostr, DEFAULT_STR_FORMAT ); }

        SIXTRL_BASE_EXPORT_API SIXTRL_HOST_FN SIXTRL_INLINE
        void print_using_format( std::ostream& SIXTRL_RESTRICT_REF ostr,
            str_format_t const format ) const {
            this->do_print( ostr, format ); }

        SIXTRL_BASE_EXPORT_API SIXTRL_HOST_FN SIXTRL_INLINE friend std::ostream&
        operator<<( std::ostream& SIXTRL_RESTRICT_REF ostr,
                    NodeId const& SIXTRL_RESTRICT_REF node_id )
        {
            node_id.do_print( ostr, DEFAULT_STR_FORMAT );
            return ostr;
        }

        protected:

        SIXTRL_HOST_FN virtual void do_clear();

        SIXTRL_HOST_FN virtual str_format_t do_find_device_string_format(
            std::string const& device_id_str ) const;

        SIXTRL_HOST_FN virtual status_t do_print(
            std::ostream& SIXTRL_RESTRICT_REF ostr,
            str_format_t const device_str_format ) const;

        SIXTRL_HOST_FN virtual status_t do_parse_device_str(
            std::string const& SIXTRL_RESTRICT_REF device_str,
            str_format_t const device_str_format );

        private:

        SIXTRL_HOST_FN str_format_t do_find_device_string_format_base_impl(
            std::string const& device_id_str ) const;

        SIXTRL_HOST_FN status_t do_parse_device_str_base_impl(
            std::string const& SIXTRL_RESTRICT_REF device_str,
            str_format_t const device_str_format ) SIXTRL_NOEXCEPT;
    };
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_BASE_NODE_NODE_ID_H__ */
