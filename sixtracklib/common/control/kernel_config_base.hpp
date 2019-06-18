#ifndef SIXTRACKLIB_COMMON_CONTROL_KERNEL_CONFIG_BASE_HPP_
#define SIXTRACKLIB_COMMON_CONTROL_KERNEL_CONFIG_BASE_HPP_

#if defined( __cplusplus  ) && !defined( _GPUCODE ) && \
  !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#if !defined( SIXTRKL_NO_SYSTEM_INCLUDES )
    #include <cstddef>
    #include <cstdlib>
    #include <cstring>
    #include <cstdio>
    #include <ostream>
    #include <string>
    #include <vector>
#endif /* !defined( SIXTRKL_NO_SYSTEM_INCLUDES ) */

#endif /* C++, Host */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/arch_base.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/arch_base.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    class KernelConfigBase : public SIXTRL_CXX_NAMESPACE::ArchBase
    {
        private:

        using _arch_base_t = SIXTRL_CXX_NAMESPACE::ArchBase;

        public:

        using arch_id_t     = _arch_base_t::arch_id_t;
        using size_type     = _arch_base_t::size_type;
        using kernel_id_t   = SIXTRL_CXX_NAMESPACE::arch_kernel_id_t;
        using node_id_t     = SIXTRL_CXX_NAMESPACE::node_id_t;
        using platform_id_t = node_id_t::platform_id_t;
        using device_id_t   = node_id_t::device_id_t;
        using variant_t     = SIXTRL_CXX_NAMESPACE::kernel_config_variant_t;

        static constexpr platform_id_t ILLEGAL_PLATFORM_ID =
            SIXTRL_CXX_NAMESPACE::NODE_ILLEGAL_PATFORM_ID;

        static constexpr platform_id_t ILLEGAL_DEVICE_ID =
            SIXTRL_CXX_NAMESPACE::NODE_ILLEGAL_DEVICE_ID;

        static constexpr kernel_id_t ILLEGAL_KERNEL_ID =
            SIXTRL_CXX_NAMESPACE::ARCH_ILLEGAL_KERNEL_ID;

        SIXTRL_HOST_FN KernelConfigBase( arch_id_t const arch_id,
            char const* SIXTRL_RESTRICT arch_str,
            size_type const num_kernel_args = size_type{ 0 },
            char const* SIXTRL_RESTRICT kernel_name_str = nullptr,
            variant_t const variant_flags =
                SIXTRL_CXX_NAMESPACE::KERNEL_CONFIG_VARIANT_DEBUG_MODE,
            char const* SIXTRL_RESTRICT config_str = nullptr );

        SIXTRL_HOST_FN KernelConfigBase( arch_id_t const arch_id,
            std::string const& SIXTRL_RESTRICT_REF arch_str,
            size_type const num_kernel_args = size_type{ 0 },
            std::string const& SIXTRL_RESTRICT_REF kernel_name = std::string{},
            variant_t const variant_flags =
                SIXTRL_CXX_NAMESPACE::KERNEL_CONFIG_VARIANT_DEBUG_MODE,
            std::string const& SIXTRL_RESTRICT_REF config_str = std::string{} );

        SIXTRL_HOST_FN KernelConfigBase(
            KernelConfigBase const& other ) = default;

        SIXTRL_HOST_FN KernelConfigBase( KernelConfigBase&& other ) = default;

        SIXTRL_HOST_FN KernelConfigBase& operator=(
            KernelConfigBase const& rhs ) = default;

        SIXTRL_HOST_FN KernelConfigBase& operator=(
            KernelConfigBase&& rhs ) = default;

        SIXTRL_HOST_FN virtual ~KernelConfigBase() = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool hasKernelId() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN kernel_id_t kernelId() const SIXTRL_NOEXCEPT;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN void setKernelId(
            kernel_id_t const kernel_id ) SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool hasName() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN std::string const& name() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN char const* ptrNameStr() const SIXTRL_NOEXCEPT;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN void setName(
            std::string const& SIXTRL_RESTRICT_REF kernel_name );

        SIXTRL_HOST_FN void setName(
            char const* SIXTRL_RESTRICT kernel_name );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN size_type numArguments() const SIXTRL_NOEXCEPT;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN void setNumArguments(
            size_type const num_kernel_args ) SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN variant_t variantFlags() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool areVariantFlagsSet(
            variant_t const var_flags ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool variantDebugMode() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool variantReleaseMode() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void setVariantFlags(
            variant_t const variant_flags ) SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool hasNodes() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN size_type numNodes() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_id_t const* nodesBegin() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN node_id_t const* nodesEnd()   const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_id_t const* ptrNode(
            size_type const num_node_in_list ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_id_t* nodesBegin() SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN node_id_t* nodesEnd()   SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_id_t* ptrNode(
            size_type const num_node_in_list ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t assignToNode( node_id_t const& node );

        SIXTRL_HOST_FN bool isAssignedToNode(
            node_id_t const& node_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isAssignedToNode( platform_id_t const platform_id,
                device_id_t const device_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t detachFromNode( node_id_t const& node );
        SIXTRL_HOST_FN status_t detachFromNode(
            platform_id_t const platform_id, device_id_t const device_id );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN void clear();

        SIXTRL_HOST_FN bool needsUpdate() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN status_t update();

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN void print(
            std::ostream& SIXTRL_RESTRICT_REF output ) const;

        SIXTRL_HOST_FN void print( ::FILE* SIXTRL_RESTRICT output ) const;
        SIXTRL_HOST_FN void printOut() const;

        /* ----------------------------------------------------------------- */

        template< class Derived >
        SIXTRL_HOST_FN Derived const* asDerivedKernelConfig(
            arch_id_t const required_arch_id,
            bool const requires_exact_match = false ) const SIXTRL_NOEXCEPT;

        template< class Derived >
        SIXTRL_HOST_FN Derived* asDerivedKernelConfig(
            arch_id_t const required_arch_id,
            bool const requires_exact_match = false ) SIXTRL_NOEXCEPT;

        protected:

        SIXTRL_HOST_FN virtual void doPrintToOutputStream(
            std::ostream& SIXTRL_RESTRICT_REF output ) const;

        SIXTRL_HOST_FN virtual status_t doUpdate();

        SIXTRL_HOST_FN virtual status_t doAssignToNode(
            node_id_t const& SIXTRL_RESTRICT_REF node );

        SIXTRL_HOST_FN virtual status_t doDetachFromNode(
            platform_id_t const platform_id,
            device_id_t const device_id );

        SIXTRL_HOST_FN virtual void doClear();

        SIXTRL_HOST_FN node_id_t const* doFindNodeByPlatformIdAndDeviceId(
            platform_id_t const plartform_id,
            device_id_t const device_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_id_t* doFindNodeByPlatformIdAndDeviceId(
            platform_id_t const plartform_id,
            device_id_t const device_id ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doSetNeedsUpdateFlag(
            bool const needs_update ) SIXTRL_NOEXCEPT;

        private:

        SIXTRL_HOST_FN void doClearBaseImpl() SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t doAssignToNodeBaseImpl(
            node_id_t const& SIXTRL_RESTRICT_REF node );

        SIXTRL_HOST_FN status_t doDetachFromNodeBaseImpl(
            platform_id_t const platform_id, device_id_t const device_id );

        std::vector< node_id_t > m_nodes;
        std::string m_name;

        size_type   m_num_kernel_args;
        kernel_id_t m_kernel_id;
        variant_t   m_variant_flags;

        bool        m_needs_update;
    };

    /* ----------------------------------------------------------------- */

    std::ostream& operator<<( std::ostream& SIXTRL_RESTRICT_REF output,
        KernelConfigBase const& SIXTRL_RESTRICT_REF kernel_config );
}
#endif/* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++ */

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

typedef SIXTRL_CXX_NAMESPACE::KernelConfigBase NS(KernelConfigBase);

#else /* C++, Host */

typedef void NS(KernelConfigBase);

#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++ */

/* ************************************************************************* */
/* ********     Inline and template function implementation     ************ */
/* ************************************************************************* */

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <type_traits>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template< class Derived >
    Derived const* KernelConfigBase::asDerivedKernelConfig(
        KernelConfigBase::arch_id_t const required_arch_id,
        bool requires_exact_match ) const SIXTRL_NOEXCEPT
    {
        Derived const* ptr_derived = nullptr;

        static_assert( std::is_base_of< KernelConfigBase, Derived >::value,
            "asDerivedKernelConfig< Derived > requires Derived to "
            "be derived from SIXTRL_CXX_NAMESPACE::KernelConfigBase" );

        if( ( ( !requires_exact_match ) &&
              ( this->isArchCompatibleWith( required_arch_id ) ) ) ||
            ( this->isArchIdenticalTo( required_arch_id ) ) )
        {
            ptr_derived = static_cast< Derived const* >( this );
        }

        return ptr_derived;
    }

    template< class Derived > Derived* KernelConfigBase::asDerivedKernelConfig(
        KernelConfigBase::arch_id_t const required_arch_id,
        bool requires_exact_match ) SIXTRL_NOEXCEPT
    {
        return const_cast< Derived* >( static_cast< KernelConfigBase const& >(
            *this ).asDerivedKernelConfig< Derived >(
                required_arch_id, requires_exact_match ) );
    }
}

#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_CONTROL_KERNEL_CONFIG_BASE_HPP_ */

/* end: sixtracklib/common/control/kernel_config_base.hpp */
