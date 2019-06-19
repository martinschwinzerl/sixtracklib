#ifndef SIXTRACKLIB_COMMON_CONTROL_NODE_INFO_BASE_HPP__
#define SIXTRACKLIB_COMMON_CONTROL_NODE_INFO_BASE_HPP__

#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )
#if !defined( SIXTRKL_NO_SYSTEM_INCLUDES )
        #include <cstddef>
        #include <cstdlib>
        #include <cstring>
        #include <cstdio>
#endif /* !defined( SIXTRKL_NO_SYSTEM_INCLUDES ) */
#endif /* C++, Host */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/node_id.h"
    #include "sixtracklib/common/control/arch_info.h"
    #include "sixtracklib/common/control/controller_base.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/node_id.hpp"
    #include "sixtracklib/common/control/arch_info.hpp"
    #include "sixtracklib/common/control/controller_base.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    class NodeInfoBase : public SIXTRL_CXX_NAMESPACE::ArchInfo
    {
        public:

        using node_id_t     = SIXTRL_CXX_NAMESPACE::NodeId;
        using platform_id_t = node_id_t::platform_id_t;
        using device_id_t   = node_id_t::device_id_t;
        using node_index_t  = node_id_t::index_t;
        using size_type     = node_id_t::size_type;

        using platform_device_pair_t = node_id_t:platform_device_pair_t;
        using controller_base_t      = node_id_t::controller_base_t;

        using arch_info_t   = SIXTRL_CXX_NAMESPACE::ArchInfo;
        using arch_id_t     = arch_info_t::arch_id_t;
        using status_t      = SIXTRL_CXX_NAMESPACE::arch_status_t;

        static constexpr ILLEGAL_PLATFORM_ID = node_id_t::ILLEGAL_PLATFORM_ID;
        static constexpr ILLEGAL_DEVICE_ID   = node_id_t::ILLEGAL_DEVICE_ID;
        static constexpr UNDEFINED_INDEX     = node_id_t::UNDEFINED_INDEX;

        SIXTRL_HOST_FN explicit NodeInfoBase(
            arch_id_t const arch_id,
            const char *const SIXTRL_RESTRICT arch_str,
            platform_id_t const platform_id = ILLEGAL_PATFORM_ID,
            device_id_t const device_id = ILLEGAL_DEVICE_ID,
            const char *const SIXTRL_RESTRICT platform_name = nullptr,
            const char *const SIXTRL_RESTRICT device_name = nullptr,
            const char *const SIXTRL_RESTRICT description = nullptr );

        SIXTRL_HOST_FN explicit NodeInfoBase(
            arch_info_t const* SIXTRL_RESTRICT ptr_arch_info,
            node_id_t* SIXTRL_RESTRICT ptr_node_id = nullptr,
            const char *const SIXTRL_RESTRICT platform_name = nullptr,
            const char *const SIXTRL_RESTRICT device_name = nullptr,
            const char *const SIXTRL_RESTRICT description = nullptr );

        SIXTRL_HOST_FN NodeInfoBase(
            arch_id_t const arch_id,
            std::string const& SIXTRL_RESTRICT_REF arch_str,
            platform_id_t const platform_id,
            device_id_t const device_id,
            std::string const& SIXTRL_RESTRICT_REF platform_name,
            std::string const& SIXTRL_RESTRICT_REF device_name,
            std::string const& SIXTRL_RESTRICT_REF description );

        SIXTRL_HOST_FN explicit NodeInfoBase(
            arch_info_t const& SIXTRL_RESTRICT_REF arch_info,
            node_id_t* SIXTRL_RESTRICT ptr_node_id,
            std::string const& SIXTRL_RESTRICT_REF platform_name,
            std::string const& SIXTRL_RESTRICT_REF device_name,
            std::string const& SIXTRL_RESTRICT_REF description );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN NodeInfoBase( NodeInfoBase const& other ) = default;
        SIXTRL_HOST_FN NodeInfoBase( NodeInfoBase&& other ) = default;

        SIXTRL_HOST_FN NodeInfoBase& operator=( NodeInfoBase&& rhs ) = default;

        SIXTRL_HOST_FN NodeInfoBase&
        operator=( NodeInfoBase const& rhs ) = default;

        SIXTRL_HOST_FN virtual ~NodeInfoBase() = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool ownsNodeId() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool hasNodeId()  const SIXTRL_NOEXCEPT;

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

        SIXTRL_HOST_FN platform_device_pair_t const&
        platformDeviceIdPair() const;

        SIXTRL_HOST_FN platform_device_pair_t&
        platformDeviceIdPair();

        SIXTRL_HOST_FN platform_device_pair_t const*
        ptrPlatformDeviceIdPair() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN platform_device_pair_t&
        ptrPlatformDeviceIdPair() SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool hasControllers() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN size_type numControllers() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isAttachedToController( controller_base_t const&
            SIXTRL_RESTRICT_REF ctrl ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool hasNodeIndex( controller_base_t const&
            SIXTRL_RESTRICT_REF ctrl ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t nodeIndex( controller_base_t const&
            SIXTRL_RESTRICT_REF ctrl ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t setNodeIndex(
            controller_base_t const& SIXTRL_RESTRICT_REF ctrl,
            node_index_t const node_index ) SIXTRL_RESTRICT;

        SIXTRL_HOST_FN bool isSelected() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isSelectedByController( controller_base_t const&
            SIXTRL_RESTRICT_REF ctrl ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isDefault() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isDefaultForController( controller_base_t const&
            SIXTRL_RESTRICT_REF ctrl ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN controller_base_t const*
        ptrSelectingController() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t setPtrSelectedController(
            controller_base_t const* SIXTRL_RESTRICT ptr_ctrl ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t setSelectedController(
            controller_base_t const& SIXTRL_RESTRICT_REF ctrl ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void resetSelectingController() SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t attachToController(
            controller_base_t const& SIXTRL_RESTRICT_REF ctrl,
            node_index_t const node_index = UNDEFINED_INDEX );

        SIXTRL_HOST_FN status_t detachFromController( controller_base_t const&
            SIXTRL_RESTRICT_REF ctrl ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN controller_base_t const*
        controllersBegin() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN controller_base_t const*
        controllersEnd() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN controller_base_t const* ptrController(
            size_type const num_of_controller_in_list ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool hasPlatformName() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN std::string const& platformName() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN char const* ptrPlatformNameStr() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void setPlatformName(
            std::string const& SIXTRL_RESTRICT_REF device_name );

        SIXTRL_HOST_FN void setPlatformName(
            const char *const SIXTRL_RESTRICT device_name );

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

        SIXTRL_HOST_FN friend std::ostream& operator<<(
            std::ostream& SIXTRL_RESTRICT_REF output,
            NodeInfoBase const& SIXTRL_RESTRICT_REF node_info );

        SIXTRL_HOST_FN void print( ::FILE* SIXTRL_RESTRICT output,
            controller_base_t const* SIXTRL_RESTRICT
                ptr_controller = nullptr ) const;

        SIXTRL_HOST_FN void printOut( controller_base_t const* SIXTRL_RESTRICT
                ptr_controller = nullptr ) const;

        SIXTRL_HOST_FN size_type requiredOutStringLength(
            controller_base_t const* SIXTRL_RESTRICT
                ptr_controller = nullptr ) const;

        SIXTRL_HOST_FN std::string toString(
            controller_base_t const* SIXTRL_RESTRICT
                ptr_controller = nullptr ) const;

        SIXTRL_HOST_FN status_t toString(
            size_type const out_str_capacity, char* SIXTRL_RESTRICT out_str,
            controller_base_t const* SIXTRL_RESTRICT ptr_controller = nullptr
        ) const;

        /* ----------------------------------------------------------------- */

        template< class Derived > SIXTRL_HOST_FN
        Derived const* asDerivedNodeInfo(
            arch_id_t const required_arch_id,
            bool requires_exact_match = false ) const SIXTRL_NOEXCEPT;

        template< class Derived > SIXTRL_HOST_FN Derived* asDerivedNodeInfo(
            arch_id_t const required_arch_id,
            bool requires_exact_match = false ) SIXTRL_NOEXCEPT;

        protected:

        using stored_node_id_t = std::unique_ptr< node_id_t >;

        SIXTRL_HOST_FN virtual void doPrintToOutputStream(
            std::ostream& SIXTRL_RESTRICT_REF output
            controller_base_t const* SIXTRL_RESTRICT ptr_ctrl ) const;

        SIXTRL_HOST_FN void doUpdateStoredNodeId(
            stored_node_id_t&& ptr_node_id ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t doSetPtrNodeId(
            node_id_t* SIXTRL_RESTRICT ptr_node_id ) SIXTRL_NOEXCEPT;

        private:

        std::string      m_platform_name;
        std::string      m_device_name;
        std::string      m_description;
        node_id_t*       m_ptr_node_id;
        stored_node_id_t m_ptr_stored_node_id;
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
