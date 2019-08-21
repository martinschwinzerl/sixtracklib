#ifndef SIXTRACKLIB_COMMON_CONTROL_NODE_INFO_BASE_HPP__
#define SIXTRACKLIB_COMMON_CONTROL_NODE_INFO_BASE_HPP__

#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

#if !defined( SIXTRKL_NO_SYSTEM_INCLUDES )
        #include <atomic>
        #include <cstddef>
        #include <cstdlib>
        #include <cstring>
        #include <cstdio>
        #include <map>
        #include <mutex>
        #include <string>
        #include <thread>
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
        using node_index_t      = SIXTRL_CXX_NAMESPACE::node_index_t;
        using arch_info_t       = SIXTRL_CXX_NAMESPACE::ArchInfo;
        using status_t          = SIXTRL_CXX_NAMESPACE::arch_status_t;
        using size_type         = SIXTRL_CXX_NAMESPACE::arch_size_t;
        using node_set_id_t     = SIXTRL_CXX_NAMESPACE::node_set_id_t;
        using arch_id_t         = arch_info_t::arch_id_t;
        using platform_id_t     = node_id_t::platform_id_t;
        using device_id_t       = node_id_t::device_id_t;
        using c_node_id_t       = node_id_t::c_api_t;

        using lockable_t        = std::mutex;
        using lock_t            = std::unique_lock< lockable_t >;

        static constexpr arch_id_t ARCH_ILLEGAL = node_id_t::ARCH_ILLEGAL;

        static constexpr platform_id_t ILLEGAL_PLATFORM_ID =
            node_id_t::ILLEGAL_PLATFORM_ID;

        static constexpr device_id_t ILLEGAL_DEVICE_ID =
            node_id_t::ILLEGAL_DEVICE_ID;

        static constexpr node_index_t UNDEFINED_INDEX =
            node_id_t::UNDEFINED_INDEX;

        static constexpr node_set_id_t ILLEGAL_NODE_SET_ID =
            SIXTRL_CXX_NAMESPACE::NODE_ILLEGAL_NODE_SET_ID;

        static constexpr size_type DEFAULT_MAX_SELECTION_COUNTER =
            size_type{ 1 };

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN explicit NodeInfoBase(
            arch_id_t const arch_id,
            const char *const SIXTRL_RESTRICT platform_name = nullptr,
            const char *const SIXTRL_RESTRICT device_name = nullptr,
            const char *const SIXTRL_RESTRICT description = nullptr,
            platform_id_t const platform_id = ILLEGAL_PLATFORM_ID,
            device_id_t const device_id = ILLEGAL_DEVICE_ID,
            NodeStore* SIXTRL_RESTRICT ptr_node_store = nullptr );

        SIXTRL_HOST_FN explicit NodeInfoBase(
            node_id_t const& SIXTRL_RESTRICT_REF node_id,
            const char *const SIXTRL_RESTRICT platform_name = nullptr,
            const char *const SIXTRL_RESTRICT device_name = nullptr,
            const char *const SIXTRL_RESTRICT description = nullptr,
            NodeStore* SIXTRL_RESTRICT ptr_node_store = nullptr );

        SIXTRL_HOST_FN explicit NodeInfoBase(
            const c_node_id_t *const SIXTRL_RESTRICT ptr_node_id,
            const char *const SIXTRL_RESTRICT platform_name = nullptr,
            const char *const SIXTRL_RESTRICT device_name = nullptr,
            const char *const SIXTRL_RESTRICT description = nullptr,
            NodeStore* SIXTRL_RESTRICT ptr_node_store = nullptr );

        SIXTRL_HOST_FN NodeInfoBase(
            arch_id_t const arch_id,
            std::string const& SIXTRL_RESTRICT_REF platform_name,
            std::string const& SIXTRL_RESTRICT_REF device_name,
            std::string const& SIXTRL_RESTRICT_REF description,
            platform_id_t const platform_id = ILLEGAL_PLATFORM_ID,
            device_id_t const device_id = ILLEGAL_DEVICE_ID,
            NodeStore* SIXTRL_RESTRICT ptr_node_store = nullptr );

        SIXTRL_HOST_FN NodeInfoBase(
            node_id_t const& SIXTRL_RESTRICT_REF node_id,
            std::string const& SIXTRL_RESTRICT_REF platform_name,
            std::string const& SIXTRL_RESTRICT_REF device_name,
            std::string const& SIXTRL_RESTRICT_REF description,
            NodeStore* SIXTRL_RESTRICT ptr_node_store = nullptr );

        SIXTRL_HOST_FN NodeInfoBase(
            const c_node_id_t *const SIXTRL_RESTRICT ptr_node_id,
            std::string const& SIXTRL_RESTRICT_REF platform_name,
            std::string const& SIXTRL_RESTRICT_REF device_name,
            std::string const& SIXTRL_RESTRICT_REF description,
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
            NodeStore& SIXTRL_RESTRICT_REF node_store );

        SIXTRL_HOST_FN status_t detachFromNodeStore();

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN status_t detachFromNodeStore(
            lock_t const& SIXTRL_RESTRICT_REF lock ) SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN node_id_t const& nodeId() const;
        SIXTRL_HOST_FN node_id_t const* ptrNodeId() const;
        SIXTRL_HOST_FN c_node_id_t const* ptrCNodeId() const;

        using SIXTRL_CXX_NAMESPACE::ArchInfo::archId;

        SIXTRL_HOST_FN arch_id_t archId(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN platform_id_t platformId() const;
        SIXTRL_HOST_FN device_id_t deviceId() const;

        SIXTRL_HOST_FN status_t setPlatformId( platform_id_t const );
        SIXTRL_HOST_FN status_t setDeviceId( device_id_t const );

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN node_id_t const& nodeId(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const;

        SIXTRL_HOST_FN node_id_t const* ptrNodeId(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN c_node_id_t const* ptrCNodeId(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN platform_id_t platformId(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN device_id_t deviceId(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t setPlatformId(
            lock_t const& SIXTRL_RESTRICT_REF lock, platform_id_t const );

        SIXTRL_HOST_FN status_t setDeviceId(
            lock_t const& SIXTRL_RESTRICT_REF lock, device_id_t const );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN node_index_t nodeIndex() const;

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN node_index_t nodeIndex(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t setNodeIndex(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_index_t const node_index );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool hasPlatformName() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN std::string const& platformName() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN char const* ptrPlatformNameStr() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t setPlatformName(
            std::string const& SIXTRL_RESTRICT_REF platform_name );

        SIXTRL_HOST_FN status_t setPlatformName(
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

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool hasUniqueIdStr() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN std::string const& uniqueIdStr() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN char const* ptrUniqueIdStr() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool mapsToSame( NodeInfoBase const&
            SIXTRL_RESTRICT node ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool mapsToSame( std::string const&
            SIXTRL_RESTRICT_REF node ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool mapsToSame( char const* SIXTRL_RESTRICT
            node ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN size_type maxAttachementCount() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isAttachedToAnySet() const;
        SIXTRL_HOST_FN size_type numAttachedSets() const;

        SIXTRL_HOST_FN bool isAttachedToSet(
            node_set_id_t const set_id ) const;

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN bool isAttachedToAnySet(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type numAttachedSets(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isAttachedToSet(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_set_id_t const node_set_id ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN size_type maxSelectionCount() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isSelectedByAnySet() const;

        SIXTRL_HOST_FN size_type numSelectionCount() const;

        SIXTRL_HOST_FN bool isSelectedBySet(
            node_set_id_t const node_set_id ) const;

        SIXTRL_HOST_FN bool isDefaultForSet(
            node_set_id_t const node_set_id ) const;

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN bool isSelectedByAnySet(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type numSelectionCount(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isSelectedBySet(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_set_id_t const node_set_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isDefaultForSet(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_set_id_t const node_set_id ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN size_type requiredOutStringLength(
            node_set_id_t const node_set_id = ILLEGAL_NODE_SET_ID ) const;

        SIXTRL_HOST_FN void print(
            std::ostream& SIXTRL_RESTRICT_REF output,
            node_set_id_t const node_set_id = ILLEGAL_NODE_SET_ID ) const;

        SIXTRL_HOST_FN void print( ::FILE* SIXTRL_RESTRICT output,
            node_set_id_t const node_set_id = ILLEGAL_NODE_SET_ID ) const;

        SIXTRL_HOST_FN void printOut(
            node_set_id_t const node_set_id = ILLEGAL_NODE_SET_ID ) const;

        SIXTRL_HOST_FN std::string toString(
            node_set_id_t const node_set_id = ILLEGAL_NODE_SET_ID ) const;

        SIXTRL_HOST_FN status_t toString( size_type const out_str_capacity,
            char* SIXTRL_RESTRICT out_str,
            node_set_id_t const node_set_id = ILLEGAL_NODE_SET_ID ) const;

        SIXTRL_HOST_FN friend std::ostream& operator<<(
            std::ostream& SIXTRL_RESTRICT_REF output,
            NodeInfoBase const& SIXTRL_RESTRICT_REF node_info );

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_HOST_FN size_type requiredOutStringLength(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_set_id_t const node_set_id ) const;

        SIXTRL_HOST_FN void print( lock_t const& SIXTRL_RESTRICT_REF lock,
            std::ostream& SIXTRL_RESTRICT_REF output,
            node_set_id_t const node_set_id ) const;

        SIXTRL_HOST_FN void print( lock_t const& SIXTRL_RESTRICT_REF lock,
            ::FILE* SIXTRL_RESTRICT output,
            node_set_id_t const node_set_id ) const;

        SIXTRL_HOST_FN void printOut( lock_t const& SIXTRL_RESTRICT_REF lock,
            node_set_id_t const node_set_id ) const;

        SIXTRL_HOST_FN std::string toString(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            node_set_id_t const node_set_id ) const;

        SIXTRL_HOST_FN status_t toString(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            size_type const out_str_capacity, char* SIXTRL_RESTRICT out_str,
            node_set_id_t const node_set_id ) const;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool checkLock(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void checkLockOrThrowOnError(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const;

        SIXTRL_HOST_FN lockable_t* lockable() const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        template< class Derived > SIXTRL_HOST_FN
        Derived const* asDerivedNodeInfo(
            arch_id_t const required_arch_id,
            bool requires_exact_match = false ) const SIXTRL_NOEXCEPT;

        template< class Derived > SIXTRL_HOST_FN Derived* asDerivedNodeInfo(
            arch_id_t const required_arch_id,
            bool requires_exact_match = false ) SIXTRL_NOEXCEPT;

        protected:

        SIXTRL_HOST_FN status_t doSetPlatformName(
            char const* SIXTRL_RESTRICT platform_name );

        SIXTRL_HOST_FN virtual status_t doPrintToOutputStream(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            std::ostream& SIXTRL_RESTRICT_REF output,
            node_set_id_t const node_set_id ) const;

        SIXTRL_HOST_FN void doSetUniqueIdStr(
            char const* SIXTRL_RESTRICT_REF unique_id_str );

        SIXTRL_HOST_FN void doSetMaxSelectionCount(
            size_type const max_selection_count ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doSetMaxAttachementCount(
            size_type const max_attachement_count ) SIXTRL_NOEXCEPT;

        private:

        node_id_t    m_node_id;

        std::string  m_platform_name;
        std::string  m_device_name;
        std::string  m_description;
        std::string  m_unique_id;

        NodeStore*   m_ptr_node_store;

        size_type    m_max_attachement_cnt;
        size_type    m_max_selection_cnt;
        node_index_t m_node_index_in_store;
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

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/node_store.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    /* --------------------------------------------------------------------- */

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

    SIXTRL_INLINE NodeInfoBase::status_t NodeInfoBase::detachFromNodeStore()
    {
        namespace  st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::NodeInfoBase;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->m_ptr_node_store != nullptr )
        {
            SIXTRL_ASSERT( this->m_ptr_node_store->lockable() != nullptr );
            _this_t::lock_t const lock( *this->m_ptr_node_store->lockable() );
            status = this->detachFromNodeStore( lock );
        }

        return status;
    }

    SIXTRL_INLINE NodeInfoBase::status_t NodeInfoBase::detachFromNodeStore(
        NodeInfoBase::lock_t const& SIXTRL_RESTRICT_REF lock ) SIXTRL_NOEXCEPT
    {
        namespace  st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::NodeInfoBase;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( this->m_ptr_node_store == nullptr ) ||
            ( this->checkLock( lock ) ) )
        {
            this->m_ptr_node_store = nullptr;
            this->m_node_index_in_store = _this_t::UNDEFINED_INDEX;
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    /* ----------------------------------------------------------------- */

    SIXTRL_INLINE NodeInfoBase::node_id_t const& NodeInfoBase::nodeId() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeInfoBase;
        if( this->ptrNodeStore() != nullptr )
        {
            _this_t::lock_t const lock( *this->lockable() );
            return this->nodeId( lock );
        }

        return this->nodeId( _this_t::lock_t{} );
    }

    SIXTRL_INLINE NodeInfoBase::node_id_t const* NodeInfoBase::ptrNodeId() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeInfoBase;
        if( this->ptrNodeStore() != nullptr )
        {
            _this_t::lock_t const lock( *this->lockable() );
            return this->ptrNodeId( lock );
        }

        return this->ptrNodeId( _this_t::lock_t{} );
    }

    SIXTRL_INLINE NodeInfoBase::c_node_id_t const*
    NodeInfoBase::ptrCNodeId() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeInfoBase;
        if( this->ptrNodeStore() != nullptr )
        {
            _this_t::lock_t const lock( *this->lockable() );
            return this->ptrCNodeId( lock );
        }

        return this->ptrCNodeId( _this_t::lock_t{} );
    }

    SIXTRL_INLINE NodeInfoBase::arch_id_t NodeInfoBase::archId(
            NodeInfoBase::lock_t const& SIXTRL_RESTRICT_REF lock
        ) const SIXTRL_NOEXCEPT
    {
        namespace  st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::NodeInfoBase;

        return ( ( this->ptrNodeStore() == nullptr ) ||
                 ( this->checkLock( lock ) ) )
            ? this->archId() : _this_t::ARCH_ILLEGAL;
    }

    SIXTRL_INLINE NodeInfoBase::platform_id_t NodeInfoBase::platformId() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeInfoBase;
        if( this->ptrNodeStore() != nullptr )
        {
            _this_t::lock_t const lock( *this->lockable() );
            return this->platformId( lock );
        }

        return this->platformId( _this_t::lock_t{} );
    }

    SIXTRL_INLINE NodeInfoBase::status_t NodeInfoBase::setPlatformId(
        NodeInfoBase::platform_id_t const platform_id )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeInfoBase;
        if( this->ptrNodeStore() != nullptr )
        {
            _this_t::lock_t const lock( *this->lockable() );
            return this->setPlatformId( lock, platform_id );
        }

        return this->setPlatformId( _this_t::lock_t{}, platform_id );
    }

    SIXTRL_INLINE NodeInfoBase::device_id_t NodeInfoBase::deviceId() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeInfoBase;
        if( this->ptrNodeStore() != nullptr )
        {
            _this_t::lock_t const lock( *this->lockable() );
            return this->deviceId( lock );
        }

        return this->deviceId( _this_t::lock_t{} );
    }

    SIXTRL_INLINE NodeInfoBase::status_t NodeInfoBase::setDeviceId(
        NodeInfoBase::device_id_t const device_id )
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeInfoBase;
        if( this->ptrNodeStore() != nullptr )
        {
            _this_t::lock_t const lock( *this->lockable() );
            return this->setDeviceId( lock, device_id );
        }

        return this->setDeviceId( _this_t::lock_t{}, device_id );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE NodeInfoBase::node_index_t NodeInfoBase::nodeIndex() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeInfoBase;

        if( ( this->ptrNodeStore() != nullptr ) &&
            ( this->lockable() != nullptr ) )
        {
            _this_t::lock_t const lock( *this->lockable() );
            return this->m_node_index_in_store;
        }
        else if( this->ptrNodeStore() == nullptr )
        {
            return this->m_node_index_in_store;
        }

        return _this_t::UNDEFINED_INDEX;
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

    SIXTRL_INLINE NodeInfoBase::status_t NodeInfoBase::setPlatformName(
        std::string const& SIXTRL_RESTRICT_REF platform_name )
    {
        return this->doSetPlatformName( platform_name.c_str() );
    }

    SIXTRL_INLINE NodeInfoBase::status_t NodeInfoBase::setPlatformName(
        char const* SIXTRL_RESTRICT platform_name )
    {
        return this->doSetPlatformName( platform_name );
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

    SIXTRL_INLINE NodeInfoBase::size_type
    NodeInfoBase::maxAttachementCount() const SIXTRL_NOEXCEPT
    {
        return this->m_max_attachement_cnt;
    }

    SIXTRL_INLINE bool NodeInfoBase::isAttachedToAnySet() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeInfoBase;
        bool is_attached_to_any = false;

        if( ( this->m_ptr_node_store != nullptr ) &&
            ( this->m_ptr_node_store->lockable() != nullptr ) )
        {
            _this_t::lock_t const lock( *this->m_ptr_node_store->lockable() );
            is_attached_to_any = this->isAttachedToAnySet( lock );
        }

        return is_attached_to_any;
    }

    SIXTRL_INLINE NodeInfoBase::size_type NodeInfoBase::numAttachedSets() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeInfoBase;
        _this_t::size_type num_attached_sets = _this_t::size_type{ 0 };

        if( ( this->m_ptr_node_store != nullptr ) &&
            ( this->m_ptr_node_store->lockable() != nullptr ) )
        {
            _this_t::lock_t const lock( *this->m_ptr_node_store->lockable() );
            num_attached_sets = this->numAttachedSets( lock );
        }

        return num_attached_sets;
    }

    SIXTRL_INLINE bool NodeInfoBase::isAttachedToSet(
        NodeInfoBase::node_set_id_t const set_id ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeInfoBase;
        bool is_attached_to_set = false;

        if( ( this->m_ptr_node_store != nullptr ) &&
            ( this->m_ptr_node_store->lockable() != nullptr ) )
        {
            _this_t::lock_t const lock( *this->m_ptr_node_store->lockable() );
            is_attached_to_set = this->isAttachedToSet( lock, set_id );
        }

        return is_attached_to_set;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE NodeInfoBase::size_type
    NodeInfoBase::maxSelectionCount() const SIXTRL_NOEXCEPT
    {
        return this->m_max_selection_cnt;
    }

    SIXTRL_INLINE bool NodeInfoBase::isSelectedByAnySet() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeInfoBase;
        bool is_selected_by_any = false;

        if( ( this->m_ptr_node_store != nullptr ) &&
            ( this->m_ptr_node_store->lockable() != nullptr ) )
        {
            _this_t::lock_t const lock( *this->m_ptr_node_store->lockable() );
            is_selected_by_any = this->isSelectedByAnySet( lock );

            SIXTRL_ASSERT( ( !is_selected_by_any ) ||
                ( this->isAttachedToAnySet( lock ) ) );
        }

        return is_selected_by_any;
    }

    SIXTRL_INLINE NodeInfoBase::size_type
    NodeInfoBase::numSelectionCount() const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeInfoBase;
        _this_t::size_type num_selected_nodes = _this_t::size_type{ 0 };

        if( ( this->m_ptr_node_store != nullptr ) &&
            ( this->m_ptr_node_store->lockable() != nullptr ) )
        {
            _this_t::lock_t const lock( *this->m_ptr_node_store->lockable() );
            num_selected_nodes = this->numSelectionCount( lock );

            SIXTRL_ASSERT( ( num_selected_nodes == _this_t::size_type{ 0 } ) ||
                ( ( num_selected_nodes < this->maxSelectionCount() ) &&
                  ( this->isSelectedByAnySet( lock ) ) ) );
        }

        return num_selected_nodes;
    }

    SIXTRL_INLINE bool NodeInfoBase::isSelectedBySet(
        NodeInfoBase::node_set_id_t const node_set_id ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeInfoBase;
        bool is_selected_by_set = false;

        if( ( this->m_ptr_node_store != nullptr ) &&
            ( this->m_ptr_node_store->lockable() != nullptr ) )
        {
            _this_t::lock_t const lock( *this->m_ptr_node_store->lockable() );
            is_selected_by_set = this->isSelectedBySet( lock, node_set_id );

            SIXTRL_ASSERT( ( !is_selected_by_set ) ||
                ( this->isAttachedToSet( lock, node_set_id ) ) );
        }

        return is_selected_by_set;
    }

    SIXTRL_INLINE bool NodeInfoBase::isDefaultForSet(
        NodeInfoBase::node_set_id_t const node_set_id ) const
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::NodeInfoBase;
        bool is_default_for_node = false;

        if( ( this->m_ptr_node_store != nullptr ) &&
            ( this->m_ptr_node_store->lockable() != nullptr ) )
        {
            _this_t::lock_t const lock( *this->m_ptr_node_store->lockable() );
            is_default_for_node = this->isDefaultForSet( lock, node_set_id );

            SIXTRL_ASSERT( ( !is_default_for_node ) ||
                ( this->isAttachedToSet( lock, node_set_id ) ) );
        }

        return is_default_for_node;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool NodeInfoBase::checkLock( NodeInfoBase::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( ( lock.owns_lock() ) && ( lock.mutex() != nullptr ) &&
                 ( this->m_ptr_node_store != nullptr ) &&
                 ( this->m_ptr_node_store->lockable() == lock.mutex() ) );
    }

    SIXTRL_INLINE void NodeInfoBase::checkLockOrThrowOnError(
        NodeInfoBase::lock_t const& SIXTRL_RESTRICT_REF lock ) const
    {
        if( !this->checkLock( lock ) )
        {
            throw std::runtime_error( "lock handle not properly locked" );
        }

        return;
    }

    SIXTRL_INLINE NodeInfoBase::lockable_t*
    NodeInfoBase::lockable() const SIXTRL_NOEXCEPT
    {
        return ( this->m_ptr_node_store != nullptr )
            ? this->m_ptr_node_store->lockable() : nullptr;
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
