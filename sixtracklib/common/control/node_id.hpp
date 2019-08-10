#ifndef SIXTRACKLIB_COMMON_CONTROL_NODE_ID_HPP__
#define SIXTRACKLIB_COMMON_CONTROL_NODE_ID_HPP__

#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cstddef>
    #include <cstdlib>
    #include <cstdio>
    #include <cstring>
    #include <map>
    #include <string>
    #include <ostream>
    #include <vector>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */
#endif /* C++, Host */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/buffer.hpp"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/node_id.h"
    #include "sixtracklib/common/buffer/buffer_type.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

namespace SIXTRL_CXX_NAMESPACE
{
    class NodeId : public ::NS(NodeId)
    {
        public:

        using buffer_t      = SIXTRL_CXX_NAMESPACE::Buffer;
        using c_buffer_t    = buffer_t::c_api_t;
        using size_type     = buffer_t::size_type;
        using type_id_t     = buffer_t::type_id_t;
        using arch_id_t     = SIXTRL_CXX_NAMESPACE::arch_id_t;
        using status_t      = SIXTRL_CXX_NAMESPACE::arch_status_t;
        using platform_id_t = SIXTRL_CXX_NAMESPACE::node_platform_id_t;
        using device_id_t   = SIXTRL_CXX_NAMESPACE::node_device_id_t;
        using format_t      = SIXTRL_CXX_NAMESPACE::node_id_str_fmt_t;
        using c_api_t       = ::NS(NodeId);

        static SIXTRL_CONSTEXPR_OR_CONST platform_id_t ILLEGAL_PLATFORM_ID =
            SIXTRL_CXX_NAMESPACE::NODE_ILLEGAL_PLATFORM_ID;

        static SIXTRL_CONSTEXPR_OR_CONST device_id_t ILLEGAL_DEVICE_ID =
            SIXTRL_CXX_NAMESPACE::NODE_ILLEGAL_DEVICE_ID;

        static SIXTRL_CONSTEXPR_OR_CONST node_index_t UNDEFINED_INDEX =
            SIXTRL_CXX_NAMESPACE::NODE_UNDEFINED_INDEX;

        static SIXTRL_CONSTEXPR_OR_CONST arch_id_t ARCH_ILLEGAL =
            SIXTRL_CXX_NAMESPACE::ARCHITECTURE_ILLEGAL;

        static SIXTRL_CONSTEXPR_OR_CONST format_t DEFAULT_FORMAT =
            SIXTRL_CXX_NAMESPACE::NODE_ID_STR_FORMAT_DEFAULT;

        SIXTRL_FN explicit NodeId(
            arch_id_t const arch_id = ARCH_ILLEGAL,
            platform_id_t const platform_id = ILLEGAL_PLATFORM_ID,
            device_id_t const device_id = ILLEGAL_DEVICE_ID );

        SIXTRL_FN explicit NodeId(
            ::NS(NodeId) const& node_id ) SIXTRL_NOEXCEPT;

        SIXTRL_FN explicit NodeId(
            std::string const& SIXTRL_RESTRICT_REF id_str );

        SIXTRL_FN explicit NodeId( const char *const SIXTRL_RESTRICT id_str );

        SIXTRL_FN NodeId( NodeId const& other ) = default;
        SIXTRL_FN NodeId( NodeId&& other ) = default;

        SIXTRL_FN NodeId& operator=( NodeId const& rhs ) = default;
        SIXTRL_FN NodeId& operator=( NodeId&& rhs ) = default;

        SIXTRL_FN virtual ~NodeId() = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN c_api_t const* getCApiPtr() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN c_api_t* getCApiPtr() SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_FN type_id_t getTypeId() const SIXTRL_NOEXCEPT;

        SIXTRL_STATIC SIXTRL_FN size_type RequiredNumDataPtrs(
            buffer_t const& SIXTRL_RESTRICT_REF buffer ) SIXTRL_NOEXCEPT;

        SIXTRL_STATIC SIXTRL_FN size_type RequiredNumDataPtrs(
            SIXTRL_BUFFER_ARGPTR_DEC const c_buffer_t *const
                SIXTRL_RESTRICT ptr_buffer ) SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_STATIC SIXTRL_FN bool CanAddToBuffer(
            SIXTRL_BUFFER_ARGPTR_DEC buffer_t* SIXTRL_RESTRICT ptr_buffer,
            SIXTRL_ARGPTR_DEC size_type* SIXTRL_RESTRICT req_objects = nullptr,
            SIXTRL_ARGPTR_DEC size_type* SIXTRL_RESTRICT req_slots = nullptr,
            SIXTRL_ARGPTR_DEC size_type* SIXTRL_RESTRICT req_dataptrs = nullptr
        ) SIXTRL_NOEXCEPT;

        SIXTRL_STATIC SIXTRL_FN bool CanAddToBuffer(
            SIXTRL_BUFFER_ARGPTR_DEC c_buffer_t* SIXTRL_RESTRICT_REF buffer,
            SIXTRL_ARGPTR_DEC size_type* SIXTRL_RESTRICT req_objects = nullptr,
            SIXTRL_ARGPTR_DEC size_type* SIXTRL_RESTRICT req_slots = nullptr,
            SIXTRL_ARGPTR_DEC size_type* SIXTRL_RESTRICT req_dataptrs = nullptr
        ) SIXTRL_NOEXCEPT;


        SIXTRL_STATIC SIXTRL_FN SIXTRL_DATAPTR_DEC NodeId*
        CreateNewOnBuffer( buffer_t& SIXTRL_RESTRICT_REF buffer );

        SIXTRL_STATIC SIXTRL_FN SIXTRL_DATAPTR_DEC NodeId*
        CreateNewOnBuffer( c_buffer_t& SIXTRL_RESTRICT_REF buffer );

        SIXTRL_STATIC SIXTRL_FN SIXTRL_DATAPTR_DEC NodeId*
        AddToBuffer( buffer_t& SIXTRL_RESTRICT_REF buffer,
            arch_id_t const arch_id, platform_id_t const platform_id,
                device_id_t const device_id );

        SIXTRL_STATIC SIXTRL_FN SIXTRL_DATAPTR_DEC NodeId*
        AddToBuffer( c_buffer_t& SIXTRL_RESTRICT_REF buffer,
            arch_id_t const arch_id, platform_id_t const platform_id,
                device_id_t const device_id );

        SIXTRL_STATIC SIXTRL_FN SIXTRL_DATAPTR_DEC NodeId*
        AddCopyToBuffer( buffer_t& SIXTRL_RESTRICT_REF buffer,
                         NodeId const& SIXTRL_RESTRICT_REF orig );

        SIXTRL_STATIC SIXTRL_FN SIXTRL_DATAPTR_DEC NodeId*
        AddCopyToBuffer( c_buffer_t& SIXTRL_RESTRICT_REF buffer,
                         NodeId const& SIXTRL_RESTRICT_REF orig );

        /* ----------------------------------------------------------------- */

        SIXTRL_FN void preset() SIXTRL_NOEXCEPT;
        SIXTRL_FN void clear() SIXTRL_NOEXCEPT;

        SIXTRL_FN bool valid() const SIXTRL_NOEXCEPT;

        SIXTRL_FN arch_id_t archId() const SIXTRL_NOEXCEPT;
        SIXTRL_FN platform_id_t platformId() const SIXTRL_NOEXCEPT;
        SIXTRL_FN device_id_t   deviceId() const SIXTRL_NOEXCEPT;

        SIXTRL_FN status_t setArchId( arch_id_t const arch_id ) SIXTRL_NOEXCEPT;

        SIXTRL_FN status_t setPlatformId(
            platform_id_t const id ) SIXTRL_NOEXCEPT;

        SIXTRL_FN status_t setDeviceId(
            device_id_t const id ) SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_STATIC SIXTRL_FN format_t IdentifyFormat(
            std::string const& SIXTRL_RESTRICT_REF str ) SIXTRL_NOEXCEPT;

        SIXTRL_STATIC SIXTRL_FN format_t IdentifyFormat(
            char const* SIXTRL_RESTRICT node_id_str ) SIXTRL_NOEXCEPT;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_STATIC SIXTRL_HOST_FN status_t ExtractNodeIdStrFromConfigStr(
            std::string& SIXTRL_RESTRICT_REF node_id_str,
            std::string const& SIXTRL_RESTRICT_REF config_str );

        SIXTRL_STATIC SIXTRL_HOST_FN status_t ExtractNodeIdStrFromConfigStr(
            size_type const node_id_str_capacity,
            char* SIXTRL_RESTRICT node_id_str,
            char const* SIXTRL_RESTRICT configstr ) SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN size_type requiredStringCapacity(
            format_t const format = DEFAULT_FORMAT ) const;

        SIXTRL_HOST_FN status_t fromString(
            std::string const& SIXTRL_RESTRICT_REF id_str ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t fromString(
            const char *const SIXTRL_RESTRICT id_str ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN std::string toString(
            format_t const format = DEFAULT_FORMAT ) const;

        SIXTRL_HOST_FN status_t toString( char* SIXTRL_RESTRICT node_id_str,
            size_type const node_id_str_capacity,
            format_t const format = DEFAULT_FORMAT ) const;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN void print( std::ostream& SIXTRL_RESTRICT_REF os,
            format_t const format = DEFAULT_FORMAT ) const;

        SIXTRL_HOST_FN void print( ::FILE* SIXTRL_RESTRICT fp,
            format_t const format = DEFAULT_FORMAT ) const;

        SIXTRL_HOST_FN void printOut(
            format_t const format = DEFAULT_FORMAT) const;

        /* ----------------------------------------------------------------- */

        SIXTRL_FN bool operator<(
            NodeId const& SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT;

        SIXTRL_FN bool operator==(
            NodeId const& SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT;

        SIXTRL_FN int compare( ::NS(NodeId) const&
            SIXTRL_RESTRICT_REF node ) const SIXTRL_NOEXCEPT;

        SIXTRL_FN int compare( NodeId const&
            SIXTRL_RESTRICT_REF node ) const SIXTRL_NOEXCEPT;
    };

    template<> struct ObjectTypeTraits< NodeId >
    {
        SIXTRL_STATIC SIXTRL_INLINE object_type_id_t Type() SIXTRL_NOEXCEPT
        {
            return ::NS(OBJECT_TYPE_NODE_ID);
        }
    };

    template<> struct ObjectTypeTraits< ::NS(NodeId) >
    {
        SIXTRL_STATIC SIXTRL_INLINE object_type_id_t Type() SIXTRL_NOEXCEPT
        {
            return ::NS(OBJECT_TYPE_NODE_ID);
        }
    };

    SIXTRL_HOST_FN SIXTRL_DATAPTR_DEC NodeId* NodeId_new(
        NodeId::buffer_t& SIXTRL_RESTRICT_REF buffer );

    SIXTRL_HOST_FN SIXTRL_DATAPTR_DEC NodeId* NodeId_new(
        NodeId::c_buffer_t& SIXTRL_RESTRICT_REF buffer );

    SIXTRL_HOST_FN SIXTRL_DATAPTR_DEC NodeId* NodeId_add(
        NodeId::buffer_t& SIXTRL_RESTRICT_REF buffer,
        NodeId::arch_id_t const arch_id,
        NodeId::platform_id_t const platform_id,
        NodeId::device_id_t const device_id );

    SIXTRL_HOST_FN SIXTRL_DATAPTR_DEC NodeId* NodeId_add(
        NodeId::c_buffer_t& SIXTRL_RESTRICT_REF buffer,
        NodeId::arch_id_t const arch_id,
        NodeId::platform_id_t const platform_id,
        NodeId::device_id_t const device_id );

    SIXTRL_HOST_FN SIXTRL_DATAPTR_DEC NodeId* NodeId_add_copy(
        NodeId::buffer_t& SIXTRL_RESTRICT_REF buffer,
        NodeId const& SIXTRL_RESTRICT_REF orig );

    SIXTRL_HOST_FN SIXTRL_DATAPTR_DEC NodeId* NodeId_add_copy(
        NodeId::c_buffer_t& SIXTRL_RESTRICT_REF buffer,
        ::NS(NodeId) const& SIXTRL_RESTRICT_REF orig );

    SIXTRL_HOST_FN std::ostream& operator<<(
        std::ostream& SIXTRL_RESTRICT_REF output,
        SIXTRL_CXX_NAMESPACE::NodeId const& SIXTRL_RESTRICT_REF node_id );

    SIXTRL_HOST_FN int compareNodeIds(
        SIXTRL_CXX_NAMESPACE::NodeId const& SIXTRL_RESTRICT_REF lhs,
        SIXTRL_CXX_NAMESPACE::NodeId const& SIXTRL_RESTRICT_REF rhs );

    SIXTRL_STATIC SIXTRL_FN
    SIXTRL_DATAPTR_DEC SIXTRL_CXX_NAMESPACE::NodeId const*
    asCxxNodeId( const ::NS(NodeId) *const SIXTRL_RESTRICT ptr_node_id );

    SIXTRL_STATIC SIXTRL_FN
    SIXTRL_DATAPTR_DEC SIXTRL_CXX_NAMESPACE::NodeId*
    asCxxNodeId( ::NS(NodeId)* SIXTRL_RESTRICT ptr_node_id );

    SIXTRL_STATIC SIXTRL_HOST_FN std::string
    NodeId_extract_node_id_str_from_config_str(
        std::string const& SIXTRL_RESTRICT_REF config_str );

    SIXTRL_HOST_FN std::string NodeId_extract_node_id_str_from_config_str(
        char const* SIXTRL_RESTRICT config_str );
}
#endif /* C++, Host */

/* ************************************************************************* */
/* ******  Implementation of inline and template member functions    ******* */
/* ************************************************************************* */

#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <algorithm>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    SIXTRL_INLINE std::string NodeId_extract_node_id_str_from_config_str(
        std::string const& SIXTRL_RESTRICT_REF config_str )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using status_t = st::arch_status_t;

        std::string node_id_str = std::string{};

        status_t const status = st::NodeId::ExtractNodeIdStrFromConfigStr(
            node_id_str, config_str );

        if( status != st::ARCH_STATUS_SUCCESS )
        {
            node_id_str.clear();
        }

        return node_id_str;
    }

    SIXTRL_INLINE std::string NodeId_extract_node_id_str_from_config_str(
        char const* SIXTRL_RESTRICT config_str )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using status_t = st::arch_status_t;

        std::string node_id_str = std::string{};

        if( config_str != nullptr )
        {
            status_t const status = st::NodeId::ExtractNodeIdStrFromConfigStr(
                node_id_str, config_str );

            if( status != st::ARCH_STATUS_SUCCESS )
            {
                node_id_str.clear();
            }
        }

        return node_id_str;
    }

    /* ********************************************************************* */
    SIXTRL_INLINE NodeId::NodeId(
        NodeId::arch_id_t const arch_id,
        NodeId::platform_id_t const platform_id,
        NodeId::device_id_t const device_id ) : ::NS(NodeId)()
    {
        NodeId::status_t const status = ::NS(NodeId_init)(
            ::NS(NodeId_preset)( this->getCApiPtr() ),
                arch_id, platform_id, device_id );

        SIXTRL_ASSERT( status == SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS );
        ( void )status;
    }

    SIXTRL_INLINE NodeId::NodeId(
        ::NS(NodeId) const& node_id ) SIXTRL_NOEXCEPT : ::NS(NodeId)( node_id )
    {

    }

    SIXTRL_INLINE NodeId::NodeId(
        std::string const& SIXTRL_RESTRICT_REF id_str ) : ::NS(NodeId)()
    {
        NodeId::status_t const status = ::NS(NodeId_from_node_id_str)(
            ::NS(NodeId_preset)( this->getCApiPtr() ), id_str.c_str() );

        SIXTRL_ASSERT( status == SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS );
        ( void )status;
    }

    SIXTRL_INLINE NodeId::NodeId(
        const char *const SIXTRL_RESTRICT id_str ) : ::NS(NodeId)()
    {
        NodeId::status_t const status = ::NS(NodeId_from_node_id_str)(
            ::NS(NodeId_preset)( this->getCApiPtr() ), id_str );

        SIXTRL_ASSERT( status == SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS );
        ( void )status;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE NodeId::c_api_t const*
    NodeId::getCApiPtr() const SIXTRL_NOEXCEPT
    {
        return static_cast< NodeId::c_api_t const* >( this );
    }

    SIXTRL_INLINE NodeId::c_api_t* NodeId::getCApiPtr() SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeId;

        return const_cast< _this_t::c_api_t* >( static_cast<
            _this_t const& >( *this ).getCApiPtr() );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE NodeId::type_id_t NodeId::getTypeId() const SIXTRL_NOEXCEPT
    {
        return ObjectTypeTraits< NodeId >::Type();
    }

    SIXTRL_INLINE NodeId::size_type NodeId::RequiredNumDataPtrs(
        NodeId::buffer_t const& SIXTRL_RESTRICT_REF buffer ) SIXTRL_NOEXCEPT
    {
        return ::NS(NodeId_get_required_num_dataptrs)( buffer.getCApiPtr() );
    }

    SIXTRL_INLINE NodeId::size_type NodeId::RequiredNumDataPtrs(
        SIXTRL_BUFFER_ARGPTR_DEC const NodeId::c_buffer_t *const
            SIXTRL_RESTRICT ptr_buffer ) SIXTRL_NOEXCEPT
    {
        return ::NS(NodeId_get_required_num_dataptrs)( ptr_buffer );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool NodeId::CanAddToBuffer(
        SIXTRL_BUFFER_ARGPTR_DEC NodeId::buffer_t* SIXTRL_RESTRICT ptr_buffer,
        SIXTRL_ARGPTR_DEC NodeId::size_type* SIXTRL_RESTRICT req_objects,
        SIXTRL_ARGPTR_DEC NodeId::size_type* SIXTRL_RESTRICT req_slots,
        SIXTRL_ARGPTR_DEC NodeId::size_type* SIXTRL_RESTRICT req_dataptrs
        ) SIXTRL_NOEXCEPT
    {
        return ::NS(NodeId_can_be_added)(
            ( ptr_buffer != nullptr ) ? ptr_buffer->getCApiPtr() : nullptr,
            req_objects, req_slots, req_dataptrs );
    }

    SIXTRL_INLINE bool NodeId::CanAddToBuffer(
        SIXTRL_BUFFER_ARGPTR_DEC NodeId::c_buffer_t* SIXTRL_RESTRICT_REF buffer,
        SIXTRL_ARGPTR_DEC NodeId::size_type* SIXTRL_RESTRICT req_objects,
        SIXTRL_ARGPTR_DEC NodeId::size_type* SIXTRL_RESTRICT req_slots,
        SIXTRL_ARGPTR_DEC NodeId::size_type* SIXTRL_RESTRICT req_dataptrs
        ) SIXTRL_NOEXCEPT
    {
        return ::NS(NodeId_can_be_added)(
            buffer, req_objects, req_slots, req_dataptrs );
    }

    SIXTRL_INLINE SIXTRL_DATAPTR_DEC NodeId* NodeId::CreateNewOnBuffer(
        NodeId::buffer_t& SIXTRL_RESTRICT_REF buffer )
    {
        return SIXTRL_CXX_NAMESPACE::asCxxNodeId(
            ::NS(NodeId_new)( buffer.getCApiPtr() ) );
    }

    SIXTRL_INLINE SIXTRL_DATAPTR_DEC NodeId* NodeId::CreateNewOnBuffer(
        NodeId::c_buffer_t& SIXTRL_RESTRICT_REF buffer )
    {
        return SIXTRL_CXX_NAMESPACE::asCxxNodeId( ::NS(NodeId_new)( &buffer ) );
    }

    SIXTRL_INLINE SIXTRL_DATAPTR_DEC NodeId* NodeId::AddToBuffer(
        NodeId::buffer_t& SIXTRL_RESTRICT_REF buffer,
        NodeId::arch_id_t const arch_id,
        NodeId::platform_id_t const platform_id,
        NodeId::device_id_t const device_id )
    {
        return SIXTRL_CXX_NAMESPACE::asCxxNodeId( ::NS(NodeId_add)(
            buffer.getCApiPtr(), arch_id, platform_id, device_id ) );
    }

    SIXTRL_INLINE SIXTRL_DATAPTR_DEC NodeId* NodeId::AddToBuffer(
        NodeId::c_buffer_t& SIXTRL_RESTRICT_REF buffer,
        NodeId::arch_id_t const arch_id,
        NodeId::platform_id_t const platform_id,
        NodeId::device_id_t const device_id )
    {
        return SIXTRL_CXX_NAMESPACE::asCxxNodeId(
            ::NS(NodeId_add)( &buffer, arch_id, platform_id, device_id ) );

    }

    SIXTRL_INLINE SIXTRL_DATAPTR_DEC NodeId* NodeId::AddCopyToBuffer(
        NodeId::buffer_t& SIXTRL_RESTRICT_REF buffer,
        NodeId const& SIXTRL_RESTRICT_REF orig )
    {
        return SIXTRL_CXX_NAMESPACE::asCxxNodeId( ::NS(NodeId_add)(
            buffer.getCApiPtr(), orig.archId(), orig.platformId(),
                orig.deviceId() ) );
    }

    SIXTRL_INLINE SIXTRL_DATAPTR_DEC NodeId*
    NodeId::AddCopyToBuffer(
        NodeId::c_buffer_t& SIXTRL_RESTRICT_REF buffer,
        NodeId const& SIXTRL_RESTRICT_REF orig )
    {
        return SIXTRL_CXX_NAMESPACE::asCxxNodeId( ::NS(NodeId_add)(
            &buffer, orig.archId(), orig.platformId(), orig.deviceId() ) );
    }

    /* ----------------------------------------------------------------- */

    SIXTRL_INLINE void NodeId::preset() SIXTRL_NOEXCEPT
    {
        ::NS(NodeId_preset)( this->getCApiPtr() );
    }

    SIXTRL_INLINE void NodeId::clear() SIXTRL_NOEXCEPT
    {
        ::NS(NodeId_clear)( this->getCApiPtr() );
    }

    SIXTRL_INLINE bool NodeId::valid() const SIXTRL_NOEXCEPT
    {
        return ::NS(NodeId_is_valid)( this->getCApiPtr() );
    }

    SIXTRL_INLINE NodeId::arch_id_t NodeId::archId() const SIXTRL_NOEXCEPT
    {
        return ::NS(NodeId_get_arch_id)( this->getCApiPtr() );
    }

    SIXTRL_INLINE NodeId::platform_id_t
    NodeId::platformId() const SIXTRL_NOEXCEPT
    {
        return ::NS(NodeId_get_platform_id)( this->getCApiPtr() );
    }

    SIXTRL_INLINE NodeId::device_id_t NodeId::deviceId() const SIXTRL_NOEXCEPT
    {
        return ::NS(NodeId_get_device_id)( this->getCApiPtr() );
    }

    SIXTRL_INLINE NodeId::status_t NodeId::setArchId(
        NodeId::arch_id_t const arch_id ) SIXTRL_NOEXCEPT
    {
        return ::NS(NodeId_set_arch_id)( this->getCApiPtr(), arch_id );
    }

    SIXTRL_INLINE NodeId::status_t NodeId::setPlatformId(
        NodeId::platform_id_t const id ) SIXTRL_NOEXCEPT
    {
        return ::NS(NodeId_set_platform_id)( this->getCApiPtr(), id );
    }

    SIXTRL_INLINE NodeId::status_t NodeId::setDeviceId(
        NodeId::device_id_t const id ) SIXTRL_NOEXCEPT
    {
        return ::NS(NodeId_set_device_id)( this->getCApiPtr(), id );
    }

    /* ----------------------------------------------------------------- */

    SIXTRL_INLINE NodeId::size_type NodeId::requiredStringCapacity(
        NodeId::format_t const format ) const
    {
        return ::NS(NodeId_required_str_capacity_for_format)(
            this->getCApiPtr(), format );
    }

    SIXTRL_INLINE NodeId::status_t NodeId::fromString(
        std::string const& SIXTRL_RESTRICT_REF id_str ) SIXTRL_NOEXCEPT
    {
        return ::NS(NodeId_from_node_id_str)(
            this->getCApiPtr(), id_str.c_str() );
    }

    SIXTRL_INLINE NodeId::status_t NodeId::fromString(
        const char *const SIXTRL_RESTRICT id_str ) SIXTRL_NOEXCEPT
    {
        return ::NS(NodeId_from_node_id_str)( this->getCApiPtr(), id_str );
    }

    SIXTRL_INLINE std::string NodeId::toString(
        NodeId::format_t const format ) const
    {
        char temp_node_id_str[ 16 ] =
        {
            '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
            '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'
        };

        if( SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS !=
            ::NS(NodeId_to_node_id_str_with_format)( this->getCApiPtr(),
                16, &temp_node_id_str[ 0 ], format ) )
        {
            std::memset( temp_node_id_str, static_cast< int >( '\0' ), 16 );
        }

        return std::string{ &temp_node_id_str[ 0 ] };
    }

    SIXTRL_INLINE NodeId::status_t NodeId::toString(
        char* SIXTRL_RESTRICT node_id_str,
        NodeId::size_type const node_id_str_capacity,
        NodeId::format_t const format ) const
    {
        return ::NS(NodeId_to_node_id_str_with_format)(
            this->getCApiPtr(), node_id_str_capacity, node_id_str, format );
    }

    /* ----------------------------------------------------------------- */

    SIXTRL_INLINE void NodeId::print( std::ostream& SIXTRL_RESTRICT_REF os,
        NodeId::format_t const format ) const
    {
        if( this->valid() )
        {
            char temp_node_id_str[ 16 ] =
            {
                '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
                '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'
            };

            if( SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS ==
                ::NS(NodeId_to_node_id_str_with_format)( this->getCApiPtr(),
                     16, &temp_node_id_str[ 0 ], format ) )
            {
                os << &temp_node_id_str[ 0 ];
            }
        }
    }

    SIXTRL_INLINE void NodeId::print( ::FILE* SIXTRL_RESTRICT fp,
        NodeId::format_t const format ) const
    {
        ::NS(NodeId_print_with_format)( this->getCApiPtr(), fp, format );
    }

    SIXTRL_INLINE void NodeId::printOut( NodeId::format_t const format ) const
    {
        ::NS(NodeId_print_out_with_format)( this->getCApiPtr(), format );
    }

    /* ----------------------------------------------------------------- */

    SIXTRL_INLINE bool NodeId::operator<(
        NodeId const& SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT
    {
        bool const has_same_arch =
            ( this->archId() == rhs.archId() );

        bool const has_same_platform =
            ( this->platformId() == rhs.platformId() );

        return ( ( this->archId() < rhs.archId() ) ||
            ( ( has_same_arch ) &&
              ( this->platformId() < rhs.platformId() ) ) ||
            ( ( has_same_arch ) && ( has_same_platform ) &&
              ( this->deviceId() < rhs.deviceId() ) ) );

        return ( ::NS(NodeId_compare)(
            this->getCApiPtr(), rhs.getCApiPtr() ) < 0 );
    }

    SIXTRL_INLINE bool NodeId::operator==(
            NodeId const& SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->archId() == rhs.archId() ) &&
                 ( this->platformId() == rhs.platformId() ) &&
                 ( this->deviceId() == rhs.deviceId() ) );
    }

    SIXTRL_INLINE int NodeId::compare( ::NS(NodeId) const&
        SIXTRL_RESTRICT_REF node ) const SIXTRL_NOEXCEPT
    {
        return ::NS(NodeId_compare)( this->getCApiPtr(), &node);
    }

    SIXTRL_INLINE int NodeId::compare( NodeId const&
        SIXTRL_RESTRICT_REF node ) const SIXTRL_NOEXCEPT
    {
        return this->compare( *node.getCApiPtr() );
    }

    /* ===================================================================== */

    SIXTRL_INLINE SIXTRL_DATAPTR_DEC NodeId* NodeId_new(
        NodeId::buffer_t& SIXTRL_RESTRICT_REF buffer )
    {
        return SIXTRL_CXX_NAMESPACE::NodeId::CreateNewOnBuffer( buffer );
    }

    SIXTRL_INLINE SIXTRL_DATAPTR_DEC NodeId* NodeId_new(
        NodeId::c_buffer_t& SIXTRL_RESTRICT_REF buffer )
    {
        return SIXTRL_CXX_NAMESPACE::NodeId::CreateNewOnBuffer( buffer );
    }

    SIXTRL_INLINE SIXTRL_DATAPTR_DEC NodeId* NodeId_add(
        NodeId::buffer_t& SIXTRL_RESTRICT_REF buffer,
        NodeId::arch_id_t const arch_id,
        NodeId::platform_id_t const platform_id,
        NodeId::device_id_t const device_id )
    {
        return SIXTRL_CXX_NAMESPACE::NodeId::AddToBuffer(
            buffer, arch_id, platform_id, device_id );
    }

    SIXTRL_INLINE SIXTRL_DATAPTR_DEC NodeId* NodeId_add(
        NodeId::c_buffer_t& SIXTRL_RESTRICT_REF buffer,
        NodeId::arch_id_t const arch_id,
        NodeId::platform_id_t const platform_id,
        NodeId::device_id_t const device_id )
    {
        return SIXTRL_CXX_NAMESPACE::NodeId::AddToBuffer(
            buffer, arch_id, platform_id, device_id );
    }

    SIXTRL_INLINE SIXTRL_DATAPTR_DEC NodeId* NodeId_add_copy(
        NodeId::buffer_t& SIXTRL_RESTRICT_REF buffer,
        NodeId const& SIXTRL_RESTRICT_REF orig )
    {
        return SIXTRL_CXX_NAMESPACE::NodeId::AddToBuffer(
            buffer, orig.archId(), orig.platformId(), orig.deviceId() );
    }

    SIXTRL_INLINE SIXTRL_DATAPTR_DEC NodeId* NodeId_add_copy(
        NodeId::c_buffer_t& SIXTRL_RESTRICT_REF buffer,
        ::NS(NodeId) const& SIXTRL_RESTRICT_REF orig )
    {
        return SIXTRL_CXX_NAMESPACE::NodeId::AddToBuffer(
            buffer, ::NS(NodeId_get_arch_id)( &orig ),
            ::NS(NodeId_get_platform_id)( &orig ),
            ::NS(NodeId_get_device_id)( &orig ) );
    }

    SIXTRL_INLINE std::ostream& operator<<(
        std::ostream& SIXTRL_RESTRICT_REF output,
        SIXTRL_CXX_NAMESPACE::NodeId const& SIXTRL_RESTRICT_REF node_id )
    {
        node_id.print( output );
        return output;
    }

    SIXTRL_INLINE int compareNodeIds(
        SIXTRL_CXX_NAMESPACE::NodeId const& SIXTRL_RESTRICT_REF lhs,
        SIXTRL_CXX_NAMESPACE::NodeId const& SIXTRL_RESTRICT_REF rhs )
    {
        return lhs.compare( rhs );
    }

    /* ===================================================================== */

    SIXTRL_INLINE SIXTRL_DATAPTR_DEC SIXTRL_CXX_NAMESPACE::NodeId const*
    asCxxNodeId( SIXTRL_DATAPTR_DEC const ::NS(NodeId) *const
        SIXTRL_RESTRICT ptr_node_id )
    {
        using cxx_node_id_t = SIXTRL_CXX_NAMESPACE::NodeId;
        using ptr_cxx_node_id_t = SIXTRL_DATAPTR_DEC cxx_node_id_t const*;

        return static_cast< ptr_cxx_node_id_t >( ptr_node_id );
    }

    SIXTRL_INLINE SIXTRL_DATAPTR_DEC SIXTRL_CXX_NAMESPACE::NodeId*
    asCxxNodeId( SIXTRL_DATAPTR_DEC ::NS(NodeId)* SIXTRL_RESTRICT ptr_node_id )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        using ptr_const_c_node_id_t = SIXTRL_DATAPTR_DEC ::NS(NodeId) const*;
        using cxx_node_id_t = st::NodeId;
        using ptr_cxx_node_id_t = SIXTRL_DATAPTR_DEC cxx_node_id_t*;

        ptr_const_c_node_id_t cptr = ptr_node_id;
        return const_cast< ptr_cxx_node_id_t >( st::asCxxNodeId( cptr ) );
    }

    /* ===================================================================== */

    SIXTRL_INLINE NodeId::format_t NodeId::IdentifyFormat(
        std::string const& SIXTRL_RESTRICT_REF str ) SIXTRL_NOEXCEPT
    {
        return NodeId::IdentifyFormat( str.c_str() );
    }

    SIXTRL_INLINE NodeId::format_t NodeId::IdentifyFormat(
        char const* SIXTRL_RESTRICT node_id_str ) SIXTRL_NOEXCEPT
    {
        return ::NS(NodeId_identify_format_from_node_id_str)( node_id_str );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE NodeId::status_t NodeId::ExtractNodeIdStrFromConfigStr(
        std::string& SIXTRL_RESTRICT_REF node_id_str,
        std::string const& SIXTRL_RESTRICT_REF config_str )
    {
        std::vector< char > temp_node_id_str( 64, '\0' );

        NodeId::status_t const status =
            ::NS(NodeId_extract_node_id_str_from_config_str)(
                temp_node_id_str.size(), temp_node_id_str.data(),
                    config_str.c_str() );

        if( status == SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS )
        {
            if( temp_node_id_str.back() != '\0' )
            {
                temp_node_id_str.push_back( '\0' );
            }

            node_id_str = temp_node_id_str.data();
        }

        return status;
    }

    SIXTRL_INLINE NodeId::status_t NodeId::ExtractNodeIdStrFromConfigStr(
        NodeId::size_type const node_id_str_capacity,
        char* SIXTRL_RESTRICT node_id_str,
        char const* SIXTRL_RESTRICT config_str ) SIXTRL_NOEXCEPT
    {
        return ::NS(NodeId_extract_node_id_str_from_config_str)(
            node_id_str_capacity, node_id_str, config_str );
    }
}

#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_CONTROL_NODE_ID_HPP__ */

/* end: sixtracklib/common/control/node_id.hpp */
