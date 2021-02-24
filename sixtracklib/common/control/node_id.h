#ifndef SIXTRACKLIB_COMMON_CONTROL_NODE_ID_HPP__
#define SIXTRACKLIB_COMMON_CONTROL_NODE_ID_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/internal/type_comparison_helpers.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cstddef>
    #include <cstdlib>
    #include <string>
    #include <ostream>
    #include <sstream>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

struct NS(NodeIdImpl)
{
    NS(node_platform_id_type) m_platform_id;
    NS(node_device_id_type)   m_device_id;
    NS(node_index_type)       m_node_index;
};

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    class NodeId : private ::NS(NodeIdImpl)
    {
        public:

        using size_type        = SIXTRL_CXX_NAMESPACE::size_type;
        using platform_id_type = SIXTRL_CXX_NAMESPACE::node_platform_id_type;
        using device_id_type   = SIXTRL_CXX_NAMESPACE::node_device_id_type;
        using index_type       = SIXTRL_CXX_NAMESPACE::node_index_type;
        using status_type      = SIXTRL_CXX_NAMESPACE::status_type;
        using str_format_type  = SIXTRL_CXX_NAMESPACE::node_id_str_fmt_type;
        using backend_id_type  = SIXTRL_CXX_NAMESPACE::backend_id_type;
        using cmp_result_type  = ::NS(cmp_result_type);

        static SIXTRL_HOST_FN str_format_type GET_STR_FORMAT_TYPE(
            std::string const& SIXTRL_RESTRICT_REF node_id_str,
            backend_id_type* SIXTRL_RESTRICT ptr_backend_id = nullptr );

        static SIXTRL_HOST_FN status_type DECODE_NODE_ID_STR(
            std::string const& SIXTRL_RESTRICT_REF node_id_str,
            str_format_type const format,
            platform_id_type* SIXTRL_RESTRICT ptr_platform_id,
            device_id_type*   SIXTRL_RESTRICT ptr_device_id,
            backend_id_type*  SIXTRL_RESTRICT ptr_backend_id = nullptr );


        static constexpr platform_id_type ILLEGAL_PLATFORM_ID =
            SIXTRL_CXX_NAMESPACE::NODE_PLATFORM_ID_ILLEGAL;

        static constexpr device_id_type ILLEGAL_DEVICE_ID =
            SIXTRL_CXX_NAMESPACE::NODE_DEVICE_ID_ILLEGAL;

        static constexpr index_type ILLEGAL_INDEX =
            SIXTRL_CXX_NAMESPACE::NODE_INDEX_ILLEGAL;

        static constexpr str_format_type DEFAULT_STR_FORMAT =
            SIXTRL_CXX_NAMESPACE::NODE_ID_STR_FORMAT_DEFAULT;

        SIXTRL_HOST_FN explicit NodeId(
            platform_id_type const platform_id = ILLEGAL_PLATFORM_ID,
            device_id_type const device_id = ILLEGAL_DEVICE_ID,
            node_index_type const node_index = ILLEGAL_INDEX ) SIXTRL_NOEXCEPT :
            ::NS(NodeIdImpl){ platform_id, device_id, node_index } {}

        SIXTRL_HOST_FN explicit NodeId( std::string const& id_str ):
            ::NS(NodeIdImpl){ ILLEGAL_PLATFORM_ID, ILLEGAL_DEVICE_ID,
                              ILLEGAL_INDEX }
        {
            this->from_string( id_str, ::NS(NODE_ID_STR_FORMAT_AUTO), nullptr );
        }

        SIXTRL_HOST_FN explicit NodeId( std::string const& id_str,
            str_format_type const str_format,
            backend_id_type* ptr_backend_id = nullptr ) :
            ::NS(NodeIdImpl){ ILLEGAL_PLATFORM_ID, ILLEGAL_DEVICE_ID,
                              ILLEGAL_INDEX }
        {
            this->from_string( id_str, str_format, ptr_backend_id );
        }

        SIXTRL_HOST_FN NodeId( NodeId const& other ) = default;
        SIXTRL_HOST_FN NodeId( NodeId&& other ) = default;

        SIXTRL_FN NodeId& operator=( NodeId const& rhs ) = default;
        SIXTRL_FN NodeId& operator=( NodeId&& rhs ) = default;

        SIXTRL_HOST_FN ~NodeId() = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN ::NS(NodeIdImpl)* as_c_api() SIXTRL_NOEXCEPT {
            return static_cast< ::NS(NodeIdImpl)* >( this ); }

        SIXTRL_HOST_FN ::NS(NodeIdImpl) const* as_const_c_api() SIXTRL_NOEXCEPT {
            return static_cast< NodeId const& >( *this ).as_c_api(); }

        SIXTRL_HOST_FN ::NS(NodeIdImpl) const* as_c_api() const SIXTRL_NOEXCEPT {
            return static_cast< ::NS(NodeIdImpl) const* >( this ); }

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool is_legal() const SIXTRL_NOEXCEPT {
            return ( ( this->m_platform_id != ILLEGAL_PLATFORM_ID ) &&
                     ( this->m_device_id   != ILLEGAL_DEVICE_ID   ) ); }

        SIXTRL_HOST_FN platform_id_type platform_id() const SIXTRL_NOEXCEPT {
            return this->m_platform_id; }

        SIXTRL_HOST_FN void set_platform_id( platform_id_type pid ) SIXTRL_NOEXCEPT {
            this->m_platform_id = pid; }

        SIXTRL_HOST_FN device_id_type device_id() const SIXTRL_NOEXCEPT {
            return this->m_device_id; }

        SIXTRL_HOST_FN void set_device_id( device_id_type pid ) SIXTRL_NOEXCEPT {
            this->m_device_id = pid; }

        SIXTRL_HOST_FN bool has_index() const SIXTRL_NOEXCEPT {
            return ( this->m_node_index != ILLEGAL_INDEX ); }

        SIXTRL_HOST_FN index_type index() const SIXTRL_NOEXCEPT {
            return this->m_node_index; }

        SIXTRL_HOST_FN void set_index( index_type const idx ) SIXTRL_NOEXCEPT {
            this->m_node_index = idx; }

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN cmp_result_type compare(
            NodeId const& SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool operator<( NodeId const& SIXTRL_RESTRICT_REF rhs
            ) const SIXTRL_NOEXCEPT {
                return ( this->compare( rhs ) < cmp_result_type{ 0 } ); }

        SIXTRL_HOST_FN void clear() SIXTRL_NOEXCEPT {
            this->m_platform_id = ILLEGAL_PLATFORM_ID;
            this->m_device_id = ILLEGAL_DEVICE_ID;
            this->m_node_index = ILLEGAL_INDEX;
        }

        SIXTRL_HOST_FN void reset(
            platform_id_type const platform_id,
            device_id_type const device_id,
            index_type const node_index = ILLEGAL_INDEX ) SIXTRL_NOEXCEPT {
            this->m_platform_id = platform_id;
            this->m_device_id = device_id;
            this->m_node_index = node_index;  }

        /* ------------------------------------------------------------------ */

        SIXTRL_HOST_FN status_type from_string(
            std::string const& SIXTRL_RESTRICT_REF node_id_str,
            str_format_type format =
                SIXTRL_CXX_NAMESPACE::NODE_ID_STR_FORMAT_AUTO,
            backend_id_type* ptr_backend_id = nullptr );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_type to_stream( std::ostream& ostr,
            str_format_type const format, backend_id_type const backend_id =
                SIXTRL_CXX_NAMESPACE::BACKEND_ID_NONE ) const;

        SIXTRL_HOST_FN friend std::ostream& operator<<(
            std::ostream& ostr, NodeId const& SIXTRL_RESTRICT_REF node_id ) {
            node_id.to_stream( ostr, ::NS(NODE_ID_STR_FORMAT_MINIMAL) );
            return ostr; }

        SIXTRL_HOST_FN std::string to_string( str_format_type const format,
            backend_id_type const backend_id =
                SIXTRL_CXX_NAMESPACE::BACKEND_ID_NONE ) const {
            namespace st = SIXTRL_CXX_NAMESPACE;
            if( this->is_legal() )
            {
                std::ostringstream a2str;
                if( st::STATUS_SUCCESS == this->to_stream(
                    a2str, format, backend_id ) ) { return a2str.str(); }
            }

            return std::string{};
        }

        SIXTRL_HOST_FN std::string to_string() const {
            return this->to_string( ::NS(NODE_ID_STR_FORMAT_MINIMAL) ); }

        SIXTRL_HOST_FN size_type required_string_capacity(
            str_format_type const format, backend_id_type const backend_id =
                SIXTRL_CXX_NAMESPACE::BACKEND_ID_NONE ) const {
            size_type str_capacity = size_type{ 0 };
            if( this->is_legal() )
            {
                std::ostringstream a2str;
                if( SIXTRL_CXX_NAMESPACE::STATUS_SUCCESS == this->to_stream(
                    a2str, format, backend_id ) ) {
                    str_capacity = a2str.str().size(); }
            }
            return str_capacity; }

        SIXTRL_HOST_FN status_type to_string( char* SIXTRL_RESTRICT node_id_str,
            size_type const str_capacity, str_format_type const format,
                backend_id_type const backend_id =
                    SIXTRL_CXX_NAMESPACE::BACKEND_ID_NONE )  const
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            status_type status = st::STATUS_GENERAL_FAILURE;
            if( ( this->is_legal() ) && ( node_id_str != nullptr ) &&
                ( str_capacity > size_type{ 0 } ) &&
                ( format != st::NODE_ID_STR_FORMAT_ILLEGAL ) )
            {
                std::ostringstream a2str;
                status = this->to_stream( a2str, format, backend_id );
                if( status == st::STATUS_SUCCESS ) {
                    std::string const temp = a2str.str();
                    if( temp.size() < str_capacity ) {
                        std::strncat( node_id_str, temp.c_str(),
                            str_capacity - size_type{ 1 } ); } }
            }

            return status;
        }
    };
}
#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* c++ */

#if defined( __cplusplus )
typedef SIXTRL_CXX_NAMESPACE::NodeId  NS(NodeId);
#else /* defined( __cplusplus ) */
typedef NS(NodeIdImpl) NS(NodeId);
#endif /* C++, Host */

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_ARGPTR_DEC NS(NodeId)*
NS(NodeId_create)( void );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeId_delete)(
    SIXTRL_ARGPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node_id );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_ARGPTR_DEC NS(NodeId)*
NS(NodeId_new)( NS(node_platform_id_type) const platform_id,
                NS(node_device_id_type) const device_id );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_ARGPTR_DEC NS(NodeId)*
NS(NodeId_new_from_string)( char const* SIXTRL_RESTRICT node_id_str );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_ARGPTR_DEC NS(NodeId)*
NS(NodeId_new_detailed)( NS(node_platform_id_type) const platform_id,
    NS(node_device_id_type) const device_id,
    NS(node_index_type) const node_index );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_ARGPTR_DEC NS(NodeId)*
NS(NodeId_preset)( SIXTRL_ARGPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node_id );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeId_is_legal)(
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_platform_id_type) NS(NodeId_platform_id)(
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_device_id_type) NS(NodeId_device_id)(
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeId_has_index)(
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(node_index_type) NS(NodeId_node_index)(
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeId_clear)(
    SIXTRL_ARGPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeId_reset)(
    SIXTRL_ARGPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node,
    NS(node_platform_id_type) const platform_id,
    NS(node_device_id_type) const device_id,
    NS(node_index_type) const node_index );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeId_set_platform_id)(
    SIXTRL_ARGPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node,
    NS(node_platform_id_type) const platform_id );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeId_set_device_id)(
    SIXTRL_ARGPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node,
    NS(node_device_id_type) const device_id );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeId_set_index)(
    SIXTRL_ARGPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node,
    NS(node_index_type) const node_index );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(status_type) NS(NodeId_to_string)(
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node_id,
    SIXTRL_ARGPTR_DEC char* SIXTRL_RESTRICT node_id_str,
    NS(size_type) const node_id_str_capacity );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(status_type) NS(NodeId_to_string_detailed)(
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node_id,
    SIXTRL_ARGPTR_DEC char* SIXTRL_RESTRICT node_id_str,
    NS(size_type) const node_id_str_capacity,
    NS(backend_id_type) const backend_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(status_type) NS(NodeId_from_string)(
    SIXTRL_ARGPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node_id,
    SIXTRL_ARGPTR_DEC const char *const SIXTRL_RESTRICT node_id_str );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(status_type) NS(NodeId_from_string_detailed)(
    SIXTRL_ARGPTR_DEC NS(NodeId)* SIXTRL_RESTRICT node_id,
    SIXTRL_ARGPTR_DEC const char *const SIXTRL_RESTRICT node_id_str,
    SIXTRL_ARGPTR_DEC NS(backend_id_type)* ptr_backend_id );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cmp_result_type) NS(NodeId_compare)(
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT lhs,
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT rhs );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(NodeId_are_equal)(
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT lhs,
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT rhs );

/* ------------------------------------------------------------------------- */

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeId_print_out)(
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node_id );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(NodeId_print)(
    FILE* SIXTRL_RESTRICT output,
    SIXTRL_ARGPTR_DEC const NS(NodeId) *const SIXTRL_RESTRICT node_id );

#endif /* !defined( _GPUCODE ) */
#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* c++ */
#endif /* SIXTRACKLIB_COMMON_CONTROL_NODE_ID_HPP__ */
