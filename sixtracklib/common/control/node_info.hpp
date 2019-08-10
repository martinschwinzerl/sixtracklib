#ifndef SIXTRACKLIB_COMMON_CONTROL_NODE_INFO_BASE_HPP__
#define SIXTRACKLIB_COMMON_CONTROL_NODE_INFO_BASE_HPP__

#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

#if !defined( SIXTRKL_NO_SYSTEM_INCLUDES )
        #include <cstddef>
        #include <cstdlib>
        #include <cstring>
        #include <cstdio>
        #include <map>
        #include <string>
        #include <vector>
#endif /* !defined( SIXTRKL_NO_SYSTEM_INCLUDES ) */

#endif /* C++, Host */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/arch_info.hpp"
    #include "sixtracklib/common/control/arch_info.h"
    #include "sixtracklib/common/control/controller_base.hpp"
    #include "sixtracklib/common/control/controller_base.h"
    #include "sixtracklib/common/control/node_id.hpp"
    #include "sixtracklib/common/control/node_id.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    class NodeStore;

    class NodeInfoBase : public SIXTRL_CXX_NAMESPACE::ArchInfo
    {
        public:

        using node_id_t         = SIXTRL_CXX_NAMESPACE::NodeId;
        using controller_base_t = SIXTRL_CXX_NAMESPACE::ControllerBase;
        using node_index_t      = SIXTRL_CXX_NAMESPACE::node_index_t;
        using arch_info_t       = SIXTRL_CXX_NAMESPACE::ArchInfo;
        using status_t          = SIXTRL_CXX_NAMESPACE::arch_status_t;
        using size_type         = SIXTRL_CXX_NAMESPACE::arch_size_t;
        using arch_id_t         = arch_info_t::arch_id_t;
        using platform_id_t     = node_id_t::platform_id_t;
        using device_id_t       = node_id_t::device_id_t;

        static constexpr arch_id_t ARCH_ILLEGAL = node_id_t::ARCH_ILLEGAL;

        static constexpr platform_id_t ILLEGAL_PLATFORM_ID =
            node_id_t::ILLEGAL_PLATFORM_ID;

        static constexpr device_id_t ILLEGAL_DEVICE_ID =
            node_id_t::ILLEGAL_DEVICE_ID;

        static constexpr node_index_t UNDEFINED_INDEX =
            node_id_t::UNDEFINED_INDEX;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN explicit NodeInfoBase(
            arch_id_t const arch_id,
            const char *const SIXTRL_RESTRICT platform_name = nullptr,
            const char *const SIXTRL_RESTRICT device_name = nullptr,
            const char *const SIXTRL_RESTRICT description = nullptr,
            platform_id_t const platform_id = ILLEGAL_PLATFORM_ID,
            device_id_t const device_id = ILLEGAL_DEVICE_ID,
            NodeStore* SIXTRL_RESTRICT ptr_node_store = nullptr );

        SIXTRL_HOST_FN NodeInfoBase(
            arch_id_t const arch_id,
            std::string const& SIXTRL_RESTRICT_REF platform_name,
            std::string const& SIXTRL_RESTRICT_REF device_name,
            std::string const& SIXTRL_RESTRICT_REF description,
            platform_id_t const platform_id = ILLEGAL_PLATFORM_ID,
            device_id_t const device_id = ILLEGAL_DEVICE_ID,
            NodeStore* SIXTRL_RESTRICT ptr_node_store = nullptr );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN NodeInfoBase( NodeInfoBase const& other ) = default;
        SIXTRL_HOST_FN NodeInfoBase( NodeInfoBase&& other ) = default;

        SIXTRL_HOST_FN NodeInfoBase& operator=( NodeInfoBase&& rhs ) = default;

        SIXTRL_HOST_FN NodeInfoBase&
        operator=( NodeInfoBase const& rhs ) = default;

        SIXTRL_HOST_FN virtual ~NodeInfoBase() = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool hasNodeStore() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN NodeStore const* ptrNodeStore() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN NodeStore* ptrNodeStore() SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN NodeStore const& nodeStore() const;
        SIXTRL_HOST_FN NodeStore& nodeStore();

        SIXTRL_HOST_FN status_t assignToNodeStore(
            NodeStore& SIXTRL_RESTRICT_REF node_store ) SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN node_id_t const& nodeId() const;
        SIXTRL_HOST_FN node_id_t& nodeId();

        SIXTRL_HOST_FN node_id_t const* ptrNodeId() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN node_id_t* ptrNodeId() SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_platform_id_t platformId() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t setPlatformId(
            node_platform_id_t const platform_id ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_device_id_t deviceId() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t setDeviceId(
            node_device_id_t const device_id ) SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool hasPlatformName() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN std::string const& platformName() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN char const* ptrPlatformNameStr() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void setPlatformName(
            std::string const& SIXTRL_RESTRICT_REF platform_name );

        SIXTRL_HOST_FN void setPlatformName(
            const char *const SIXTRL_RESTRICT platform_name );

        SIXTRL_HOST_FN bool hasDeviceName() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN std::string const& deviceName() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN char const* ptrDeviceNameStr() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void setDeviceName(
            std::string const& SIXTRL_RESTRICT_REF device_name );

        SIXTRL_HOST_FN void setDeviceName(
            const char *const SIXTRL_RESTRICT device_name );

        SIXTRL_HOST_FN bool hasDescription() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN std::string const& description() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN char const* ptrDescriptionStr() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void setDescription(
            std::string const& SIXTRL_RESTRICT_REF description );

        SIXTRL_HOST_FN void setDescription(
            const char *const SIXTRL_RESTRICT description_str );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN bool hasUniqueIdStr() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN std::string const& uniqueIdStr() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN char const* ptrUniqueIdStr() const SIXTRL_NOEXCEPT;

        bool mapsToSame( NodeInfoBase const&
            SIXTRL_RESTRICT node ) const SIXTRL_NOEXCEPT;

        bool mapsToSame( std::string const&
            SIXTRL_RESTRICT_REF node ) const SIXTRL_NOEXCEPT;

        bool mapsToSame( char const* SIXTRL_RESTRICT
            node ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN size_type requiredOutStringLength(
            controller_base_t const* SIXTRL_RESTRICT ctrl = nullptr ) const;

        SIXTRL_HOST_FN void print( ::FILE* SIXTRL_RESTRICT output,
            controller_base_t const* SIXTRL_RESTRICT ctrl = nullptr ) const;

        SIXTRL_HOST_FN void printOut(
            controller_base_t const* SIXTRL_RESTRICT ctrl = nullptr ) const;

        SIXTRL_HOST_FN std::string toString(
            controller_base_t const* SIXTRL_RESTRICT ctrl = nullptr ) const;

        SIXTRL_HOST_FN status_t toString( size_type const out_str_capacity,
            char* SIXTRL_RESTRICT out_str,
            controller_base_t const* SIXTRL_RESTRICT ctrl = nullptr ) const;

        SIXTRL_HOST_FN friend std::ostream& operator<<(
            std::ostream& SIXTRL_RESTRICT_REF output,
            NodeInfoBase const& SIXTRL_RESTRICT_REF node_info );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN size_type maxSelectionCount() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isAttachedToAnyController() const;

        SIXTRL_HOST_FN size_type numAttachedControllers() const;

        SIXTRL_HOST_FN bool isAttachedToController(
            controller_base_t const& SIXTRL_RESTRICT controller ) const;

        SIXTRL_HOST_FN bool isSelectedByAnyController() const;

        SIXTRL_HOST_FN bool isSelectedByController(
            controller_base_t const& SIXTRL_RESTRICT controller ) const;

        SIXTRL_HOST_FN size_type numSelectingControllers() const;

        /* ----------------------------------------------------------------- */

        template< class Derived > SIXTRL_HOST_FN
        Derived const* asDerivedNodeInfo(
            arch_id_t const required_arch_id,
            bool requires_exact_match = false ) const SIXTRL_NOEXCEPT;

        template< class Derived > SIXTRL_HOST_FN Derived* asDerivedNodeInfo(
            arch_id_t const required_arch_id,
            bool requires_exact_match = false ) SIXTRL_NOEXCEPT;

        protected:

        static constexpr size_type
            DEFAULT_MAX_SELECTION_COUNTER = size_type{ 1 };

        SIXTRL_HOST_FN virtual status_t doPrintToOutputStream(
            std::ostream& SIXTRL_RESTRICT_REF output,
            controller_base_t const* SIXTRL_RESTRICT ptr_ctrl ) const;

        SIXTRL_HOST_FN void doSetUniqueIdStr(
            char const* SIXTRL_RESTRICT_REF unique_id_str );

        SIXTRL_HOST_FN void doSetMaxSelectionCount(
            size_type const max_selection_count ) SIXTRL_NOEXCEPT;

        private:

        using ptr_ctrl_to_node_index_map_t =
            std::map< controller_base_t const*, node_index_t >;

        using ptr_ctrl_list_t = std::vector< controller_base_t const* >;

        std::string  m_platform_name;
        std::string  m_device_name;
        std::string  m_description;
        std::string  m_unique_id;
        NodeStore*   m_ptr_node_store;
        size_type    m_max_selection_cnt;
        node_id_t    m_node_id;
    };
}

#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++ */

#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

typedef SIXTRL_CXX_NAMESPACE::NodeInfoBase  NS(NodeInfoBase);

#else /* C++, Host */

typedef void NS(NodeInfoBase);

#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++ */

/* ************************************************************************* */
/* ********     Inline and template function implementation     ************ */
/* ************************************************************************* */

#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <type_traits>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    /* ----------------------------------------------------------------- */

    SIXTRL_INLINE bool NodeInfoBase::hasNodeStore() const SIXTRL_NOEXCEPT
    {
        return ( this->m_ptr_node_store != nullptr );
    }

    SIXTRL_INLINE NodeStore const*
    NodeInfoBase::ptrNodeStore() const SIXTRL_NOEXCEPT
    {
        return this->m_ptr_node_store;
    }

    SIXTRL_INLINE NodeStore* NodeInfoBase::ptrNodeStore() SIXTRL_NOEXCEPT
    {
        return this->m_ptr_node_store;
    }

    SIXTRL_INLINE NodeStore& NodeInfoBase::nodeStore()
    {
        return const_cast< NodeStore& >( static_cast< NodeInfoBase const& >(
            *this ).nodeStore() );
    }

    /* ----------------------------------------------------------------- */

    SIXTRL_INLINE NodeInfoBase::node_id_t const& NodeInfoBase::nodeId() const
    {
        return this->m_node_id;
    }

    SIXTRL_INLINE NodeInfoBase::node_id_t& NodeInfoBase::nodeId()
    {
        return this->m_node_id;
    }

    SIXTRL_INLINE NodeInfoBase::node_id_t const*
    NodeInfoBase::ptrNodeId() const SIXTRL_NOEXCEPT
    {
        return &this->m_node_id;
    }

    SIXTRL_INLINE NodeInfoBase::node_id_t*
    NodeInfoBase::ptrNodeId() SIXTRL_NOEXCEPT
    {
        return &this->m_node_id;
    }

    SIXTRL_INLINE NodeInfoBase::platform_id_t
    NodeInfoBase::platformId() const SIXTRL_NOEXCEPT
    {
        return this->m_node_id.platformId();
    }

    SIXTRL_INLINE NodeInfoBase::status_t NodeInfoBase::setPlatformId(
        NodeInfoBase::platform_id_t const platform_id ) SIXTRL_NOEXCEPT
    {
        return this->m_node_id.setPlatformId( platform_id );
    }

    SIXTRL_INLINE NodeInfoBase::device_id_t
    NodeInfoBase::deviceId() const SIXTRL_NOEXCEPT
    {
        return this->m_node_id.deviceId();
    }

    SIXTRL_INLINE NodeInfoBase::status_t NodeInfoBase::setDeviceId(
        NodeInfoBase::device_id_t const device_id ) SIXTRL_NOEXCEPT
    {
        return this->m_node_id.setDeviceId( device_id );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE NodeInfoBase::size_type
    NodeInfoBase::maxSelectionCount() const SIXTRL_NOEXCEPT
    {
        return this->m_max_selection_cnt;
    }

    SIXTRL_INLINE void NodeInfoBase::doSetMaxSelectionCount(
        NodeInfoBase::size_type const max_selection_count ) SIXTRL_NOEXCEPT
    {
        this->m_max_selection_cnt = max_selection_count;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool NodeInfoBase::hasPlatformName() const SIXTRL_NOEXCEPT
    {
        return !this->m_platform_name.empty();
    }

    SIXTRL_INLINE std::string const&
    NodeInfoBase::platformName() const SIXTRL_NOEXCEPT
    {
        return this->m_platform_name;
    }

    SIXTRL_INLINE char const*
    NodeInfoBase::ptrPlatformNameStr() const SIXTRL_NOEXCEPT
    {
        return this->m_platform_name.c_str();
    }

    SIXTRL_INLINE void NodeInfoBase::setPlatformName(
        std::string const& SIXTRL_RESTRICT_REF platform_name )
    {
        this->setPlatformName( platform_name.c_str() );
    }

    SIXTRL_INLINE bool NodeInfoBase::hasDeviceName() const SIXTRL_NOEXCEPT
    {
        return !this->m_device_name.empty();
    }

    SIXTRL_INLINE std::string const&
    NodeInfoBase::deviceName() const SIXTRL_NOEXCEPT
    {
        return this->m_device_name;
    }

    SIXTRL_INLINE char const*
    NodeInfoBase::ptrDeviceNameStr() const SIXTRL_NOEXCEPT
    {
        return this->m_device_name.c_str();
    }

    SIXTRL_INLINE void NodeInfoBase::setDeviceName(
        std::string const& SIXTRL_RESTRICT_REF device_name )
    {
        this->setDeviceName( device_name.c_str() );
    }

    SIXTRL_INLINE bool NodeInfoBase::hasDescription() const SIXTRL_NOEXCEPT
    {
        return !this->m_description.empty();
    }

    SIXTRL_INLINE std::string const&
    NodeInfoBase::description() const SIXTRL_NOEXCEPT
    {
        return this->m_description;
    }

    SIXTRL_INLINE char const*
    NodeInfoBase::ptrDescriptionStr() const SIXTRL_NOEXCEPT
    {
        return this->m_description.c_str();
    }

    SIXTRL_INLINE void NodeInfoBase::setDescription(
        std::string const& SIXTRL_RESTRICT_REF description )
    {
        this->setDescription( description.c_str() );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool NodeInfoBase::hasUniqueIdStr() const SIXTRL_NOEXCEPT
    {
        return ( !this->m_unique_id.empty() );
    }

    SIXTRL_INLINE std::string const&
    NodeInfoBase::uniqueIdStr() const SIXTRL_NOEXCEPT
    {
        return this->m_unique_id;
    }

    SIXTRL_INLINE char const*
    NodeInfoBase::ptrUniqueIdStr() const SIXTRL_NOEXCEPT
    {
        return ( this->hasUniqueIdStr() )
            ? this->m_unique_id.c_str() : nullptr;
    }

    SIXTRL_INLINE bool NodeInfoBase::mapsToSame(
        NodeInfoBase const& SIXTRL_RESTRICT_REF info ) const SIXTRL_NOEXCEPT
    {
        bool maps_to_same = ( this == &info );

        if( ( !maps_to_same ) && (info.hasUniqueIdStr() ) )
        {
            maps_to_same = this->mapsToSame( info.ptrUniqueIdStr() );
        }

        return maps_to_same;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool NodeInfoBase::mapsToSame(
        std::string const& SIXTRL_RESTRICT_REF hwid_str ) const SIXTRL_NOEXCEPT
    {
        return this->mapsToSame( hwid_str.c_str() );
    }

    SIXTRL_INLINE bool NodeInfoBase::mapsToSame(
        char const* SIXTRL_RESTRICT unique_id_str ) const SIXTRL_NOEXCEPT
    {
        bool const maps_to_same = ( ( unique_id_str != nullptr ) &&
            ( std::strlen( unique_id_str ) > NodeInfoBase::size_type{ 0 } ) &&
            ( this->hasUniqueIdStr() ) &&
            ( this->uniqueIdStr().compare( unique_id_str ) == 0 ) );

        return maps_to_same;
    }

    /* --------------------------------------------------------------------- */

    template< class Derived > Derived const* NodeInfoBase::asDerivedNodeInfo(
        NodeInfoBase::arch_id_t const required_arch_id,
        bool requires_exact_match ) const SIXTRL_NOEXCEPT
    {
        Derived const* ptr_derived = nullptr;

        static_assert( std::is_base_of< NodeInfoBase, Derived >::value,
                       "asDerivedNodeInfo< Derived > requires Dervied to be "
                       "derived from SIXTRL_CXX_NAMESPACE::NodeInfoBase" );

        if( ( ( !requires_exact_match ) &&
              ( this->isArchCompatibleWith( required_arch_id ) ) ) ||
            ( this->isArchIdenticalTo( required_arch_id ) ) )
        {
            ptr_derived = static_cast< Derived const* >( this );
        }

        return ptr_derived;
    }

    template< class Derived > Derived* NodeInfoBase::asDerivedNodeInfo(
        NodeInfoBase::arch_id_t const required_arch_id,
        bool requires_exact_match ) SIXTRL_NOEXCEPT
    {
        return const_cast< Derived* >( static_cast< NodeInfoBase const& >(
            *this ).asDerivedNodeInfo< Derived >(
                required_arch_id, requires_exact_match ) );
    }
}

#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_CONTROL_NODE_INFO_BASE_HPP__ */
/* end: sixtracklib/common/control/node_info.hpp */
