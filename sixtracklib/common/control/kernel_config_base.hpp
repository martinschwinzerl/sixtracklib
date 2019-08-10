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
    #include "sixtracklib/common/control/arch_variant_mixin.hpp"
    #include "sixtracklib/common/control/kernel_config_key.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    class KernelConfigBase : public SIXTRL_CXX_NAMESPACE::ArchVariantMixin<
        SIXTRL_CXX_NAMESPACE::ArchBase >
    {
        private:

        using _arch_base_t = SIXTRL_CXX_NAMESPACE::ArchVariantMixin<
            SIXTRL_CXX_NAMESPACE::ArchBase >;

        public:

        using arch_id_t       = _arch_base_t::arch_id_t;
        using size_type       = _arch_base_t::size_type;
        using key_t           = SIXTRL_CXX_NAMESPACE::KernelConfigKey;
        using node_id_t       = SIXTRL_CXX_NAMESPACE::NodeId;
        using kernel_set_id_t = SIXTRL_CXX_NAMESPACE::kernel_set_id_t;
        using argument_set_t  = SIXTRL_CXX_NAMESPACE::kernel_argument_set_t;
        using platform_id_t   = node_id_t::platform_id_t;
        using device_id_t     = node_id_t::device_id_t;
        using purpose_t       = SIXTRL_CXX_NAMESPACE::kernel_purpose_t;

        static constexpr size_type
            DEFAULT_NUM_KERNEL_ARGUMENTS = size_type{ 0 };

        static constexpr purpose_t DEFAULT_KERNEL_PURPOSE =
            SIXTRL_CXX_NAMESPACE::KERNEL_CONFIG_PURPOSE_UNSPECIFIED;

        static constexpr variant_t DEFAULT_KERNEL_VARIANT =
            _arch_base_t::DEFAULT_VARIANT;

        static constexpr argument_set_t DEFAULT_ARGUMENT_SET =
            SIXTRL_CXX_NAMESPACE::DEFAULT_KERNEL_ARGUMENT_SET;

        static constexpr kernel_set_id_t ILLEGAL_KERNEL_SET_ID =
            SIXTRL_CXX_NAMESPACE::ILLEGAL_KERNEL_SET_ID;

        static constexpr size_type
            DEFAULT_MAX_NUM_ATTACHED_KERNEL_SETS = size_type{ 1 };

        SIXTRL_HOST_FN explicit KernelConfigBase(
            arch_id_t const arch_id,
            size_type const num_kernel_args = DEFAULT_NUM_KERNEL_ARGUMENTS,
            purpose_t const purpose = DEFAULT_KERNEL_PURPOSE,
            variant_t const variant_flags = DEFAULT_KERNEL_VARIANT,
            char const* SIXTRL_RESTRICT kernel_name_str = nullptr,
            char const* SIXTRL_RESTRICT config_str = nullptr );

        SIXTRL_HOST_FN explicit KernelConfigBase(
            key_t const& SIXTRL_RESTRICT_REF key,
            size_type const num_kernel_args = DEFAULT_NUM_KERNEL_ARGUMENTS,
            char const* SIXTRL_RESTRICT kernel_name_str = nullptr );

        SIXTRL_HOST_FN KernelConfigBase(
            arch_id_t const arch_id,
            size_type const num_kernel_args,
            purpose_t const purpose,
            variant_t const variant_flags,
            std::string const& SIXTRL_RESTRICT_REF kernel_name,
            std::string const& SIXTRL_RESTRICT_REF config_str = std::string{} );

        SIXTRL_HOST_FN KernelConfigBase(
            key_t const& SIXTRL_RESTRICT_REF key,
            size_type const num_kernel_args,
            std::string const& SIXTRL_RESTRICT_REF kernel_name_str );

        SIXTRL_HOST_FN KernelConfigBase(
            KernelConfigBase const& other ) = default;

        SIXTRL_HOST_FN KernelConfigBase( KernelConfigBase&& other ) = default;

        SIXTRL_HOST_FN KernelConfigBase& operator=(
            KernelConfigBase const& rhs ) = default;

        SIXTRL_HOST_FN KernelConfigBase& operator=(
            KernelConfigBase&& rhs ) = default;

        SIXTRL_HOST_FN virtual ~KernelConfigBase() = default;

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

        SIXTRL_HOST_FN status_t setNumArguments(
            size_type const num_kernel_args );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool isAttachedToAnySets() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isAttachedToSet(
            kernel_set_id_t const kernel_set_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool canAttachToSet(
            kernel_set_id_t const kernel_set_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type maxNumAttachedSets() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN size_type numAttachedSets() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_set_id_t const*
        attachedSetsBegin() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_set_id_t const*
        attachedSetsEnd() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t attachToSet(
            kernel_set_id_t const kernel_set_id );

        SIXTRL_HOST_FN status_t detachFromSet(
            kernel_set_id_t const kernel_set_id );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t setVariant( variant_t const variant );

        SIXTRL_HOST_FN status_t addVariantFlags(
            variant_t const add_these_flags ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t removeVariantFlags(
            variant_t const remove_these_flags )  SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN void setArgumentSet(
            argument_set_t const argument_set ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN argument_set_t argumentSet() const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool hasSpecifiedPurpose() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool hasPredefinedPurpose() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool hasUserdefinedPurpose() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN purpose_t purpose() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void setPurpose(
            purpose_t const purpose ) SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t updateConfigStr(
            std::string const& SIXTRL_RESTRICT_REF config_str );

        SIXTRL_HOST_FN status_t updateConfigStr(
            char const* SIXTRL_RESTRICT config_str );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN void clear();

        SIXTRL_HOST_FN bool needsUpdate() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool performsAutoUpdate() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t update();

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN size_type requiredOutStringLength() const;

        SIXTRL_HOST_FN std::string toString() const;

        SIXTRL_HOST_FN status_t toString( size_type const out_str_capacity,
            char* SIXTRL_RESTRICT out_str ) const;


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

        using kernel_set_ids_list_t = std::vector< kernel_set_id_t >;

        SIXTRL_HOST_FN virtual status_t doPrintToOutputStream(
            std::ostream& SIXTRL_RESTRICT_REF output ) const;

        SIXTRL_HOST_FN virtual status_t doUpdate();

        SIXTRL_HOST_FN virtual status_t doSetNeedsUpdate();

        SIXTRL_HOST_FN virtual void doClear();

        SIXTRL_HOST_FN void doSetPurpose(
            purpose_t const purpose ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doSetNeedsUpdateFlag(
            bool const needs_update ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doSetPerformsAutoUpdatesFlag(
            bool const performs_auto_updates ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doSetMaxNumAttachedKernelSets(
            size_type const max_num_attached_kernel_sets );

        private:

        SIXTRL_HOST_FN void doClearBaseImpl() SIXTRL_NOEXCEPT;

        std::string             m_name;
        kernel_set_ids_list_t   m_kernel_set_ids;

        size_type               m_num_kernel_args;
        size_type               m_max_attached_kernel_ids;
        purpose_t               m_purpose;
        argument_set_t          m_argument_set;

        bool                    m_needs_update;
        bool                    m_perform_auto_update;
    };

    SIXTRL_HOST_FN std::ostream& operator<<(
            std::ostream& SIXTRL_RESTRICT_REF output,
            KernelConfigBase const& SIXTRL_RESTRICT_REF node_info );
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
    SIXTRL_INLINE bool KernelConfigBase::hasName() const SIXTRL_NOEXCEPT
    {
        return !this->m_name.empty();
    }

    SIXTRL_INLINE std::string const&
    KernelConfigBase::name() const SIXTRL_NOEXCEPT
    {
        return this->m_name;
    }

    SIXTRL_INLINE char const*
    KernelConfigBase::ptrNameStr() const SIXTRL_NOEXCEPT
    {
        return this->m_name.c_str();
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelConfigBase::size_type
    KernelConfigBase::numArguments() const SIXTRL_NOEXCEPT
    {
        return this->m_num_kernel_args;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool
    KernelConfigBase::isAttachedToAnySets() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->maxNumAttachedSets() >= this->numAttachedSets() );
        return !this->m_kernel_set_ids.empty();
    }

    SIXTRL_INLINE bool KernelConfigBase::isAttachedToSet(
        KernelConfigBase::kernel_set_id_t const
            kernel_set_id ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelConfigBase;

        SIXTRL_ASSERT( this->maxNumAttachedSets() >= this->numAttachedSets() );

        SIXTRL_ASSERT( ( this->m_kernel_set_ids.empty() ) ||
            ( std::is_sorted( this->m_kernel_set_ids.begin(),
                              this->m_kernel_set_ids.end() ) ) );

        bool const is_attached = (
            ( kernel_set_id != _this_t::ILLEGAL_KERNEL_SET_ID ) &&
            ( !this->m_kernel_set_ids.empty() ) &&
            ( std::binary_search( this->m_kernel_set_ids.begin(),
                    this->m_kernel_set_ids.end(), kernel_set_id ) ) );

        return is_attached;
    }

    SIXTRL_INLINE bool KernelConfigBase::canAttachToSet(
            KernelConfigBase::kernel_set_id_t const kernel_set_id
        ) const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelConfigBase;

        return ( ( kernel_set_id != _this_t::ILLEGAL_KERNEL_SET_ID ) &&
                 ( this->maxNumAttachedSets() < this->numAttachedSets() ) );
    }

    SIXTRL_INLINE KernelConfigBase::size_type
    KernelConfigBase::maxNumAttachedSets() const SIXTRL_NOEXCEPT
    {
        return this->m_max_attached_kernel_ids;
    }

    SIXTRL_INLINE KernelConfigBase::size_type
    KernelConfigBase::numAttachedSets() const SIXTRL_NOEXCEPT
    {
        return this->m_kernel_set_ids.size();
    }

    SIXTRL_INLINE KernelConfigBase::kernel_set_id_t const*
    KernelConfigBase::attachedSetsBegin() const SIXTRL_NOEXCEPT
    {
        return ( !this->m_kernel_set_ids.empty() )
            ? this->m_kernel_set_ids.data() : nullptr;
    }

    SIXTRL_INLINE KernelConfigBase::kernel_set_id_t const*
    KernelConfigBase::attachedSetsEnd() const SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::KernelConfigBase;
        _this_t::kernel_set_id_t const* end_ptr = this->attachedSetsBegin();

        if( ( end_ptr != nullptr ) && ( !this->m_kernel_set_ids.empty() ) )
        {
            std::advance( end_ptr, this->m_kernel_set_ids.size() );
        }

        return end_ptr;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE void KernelConfigBase::setArgumentSet(
        KernelConfigBase::argument_set_t const argument_set ) SIXTRL_NOEXCEPT
    {
        this->m_argument_set = argument_set;
    }

    SIXTRL_INLINE KernelConfigBase::argument_set_t
    KernelConfigBase::argumentSet() const SIXTRL_NOEXCEPT
    {
        return this->m_argument_set;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelConfigBase::status_t KernelConfigBase::setVariant(
        KernelConfigBase::variant_t const variant_flags )
    {
        KernelConfigBase::status_t status = ::NS(ARCH_STATUS_GENERAL_FAILURE);

        if( ( variant_flags != this->variant() ) &&
            ( ( variant_flags == SIXTRL_CXX_NAMESPACE::ARCH_VARIANT_NONE ) ||
              ( !this->areVariantFlagsSet( variant_flags ) ) ) )
        {
            this->doSetVariantFlags( variant_flags );
            status = SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    SIXTRL_INLINE KernelConfigBase::status_t
    KernelConfigBase::addVariantFlags(
        KernelConfigBase::variant_t const add_these_flags ) SIXTRL_NOEXCEPT
    {
        return this->doAddVariantFlags( add_these_flags );
    }

    SIXTRL_INLINE KernelConfigBase::status_t
    KernelConfigBase::removeVariantFlags(
        KernelConfigBase::variant_t const remove_these_flags ) SIXTRL_NOEXCEPT
    {
        return this->doRemoveVariantFlags( remove_these_flags );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool
    KernelConfigBase::hasSpecifiedPurpose() const SIXTRL_NOEXCEPT
    {
        return ( ( this->hasPredefinedPurpose() ) ||
                 ( this->hasUserdefinedPurpose() ) );
    }

    SIXTRL_INLINE bool
    KernelConfigBase::hasPredefinedPurpose() const SIXTRL_NOEXCEPT
    {
        return ( this->purpose() <=
            SIXTRL_CXX_NAMESPACE::KERNEL_CONFIG_PURPOSE_MAX_PREDEFINED_ID );
    }

    SIXTRL_INLINE bool
    KernelConfigBase::hasUserdefinedPurpose() const SIXTRL_NOEXCEPT
    {
        return ( this->purpose() >=
            SIXTRL_CXX_NAMESPACE::KERNEL_CONFIG_PURPOSE_MIN_USERDEFINED_ID );
    }

    SIXTRL_INLINE KernelConfigBase::purpose_t
    KernelConfigBase::purpose() const SIXTRL_NOEXCEPT
    {
        return this->m_purpose;
    }

    SIXTRL_INLINE void KernelConfigBase::setPurpose(
        KernelConfigBase::purpose_t const purpose ) SIXTRL_NOEXCEPT
    {
        this->m_purpose = purpose;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelConfigBase::status_t KernelConfigBase::updateConfigStr(
        std::string const& SIXTRL_RESTRICT_REF config_str )
    {
        return this->updateConfigStr( config_str.c_str() );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE void KernelConfigBase::clear()
    {
        this->doClear();
    }

    SIXTRL_INLINE bool KernelConfigBase::needsUpdate() const SIXTRL_NOEXCEPT
    {
        return this->m_needs_update;
    }

    SIXTRL_INLINE bool
    KernelConfigBase::performsAutoUpdate() const SIXTRL_NOEXCEPT
    {
        return this->m_perform_auto_update;
    }

    /* --------------------------------------------------------------------- */

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
