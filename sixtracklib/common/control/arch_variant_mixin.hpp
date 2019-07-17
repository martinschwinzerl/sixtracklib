#ifndef SIXTRACKLIB_COMMON_CONTROL_ARCH_VARIANT_MIXIN_CXX_HPP__
#define SIXTRACKLIB_COMMON_CONTROL_ARCH_VARIANT_MIXIN_CXX_HPP__

#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/arch_info.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cstddef>
    #include <cstdlib>
    #include <string>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#endif /* C++, Host */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/buffer/buffer_type.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE ) && \
   !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

namespace SIXTRL_CXX_NAMESPACE
{
    template< class Base >
    class ArchVariantMixin : public Base
    {
        public:

        using variant_t  = SIXTRL_CXX_NAMESPACE::arch_variant_flags_t;
        using status_t   = SIXTRL_CXX_NAMESPACE::arch_status_t;

        static SIXTRL_CONSTEXPR_OR_CONST variant_t DEFAULT_VARIANT =
            SIXTRL_CXX_NAMESPACE::ARCH_VARIANT_NONE;

        static SIXTRL_CONSTEXPR_OR_CONST variant_t VARIANT_DEBUG =
            SIXTRL_CXX_NAMESPACE::ARCH_VARIANT_DEBUG;

        template< typename Args... >
        SIXTRL_HOST_FN explicit ArchVariantMixin( Args&&... args ) :
            Base( std::forward< Args >( args )... ),
            m_variant_flags( DEFAULT_VARIANT )
        {

        }

        template< typename Args... >
        SIXTRL_HOST_FN explicit ArchVariantMixin(
            variant_t const variant_flags, Args&&... args ) :
            Base( std::forward< Args >( args )... ),
            m_variant_flags( variant_flags )
        {

        }

        SIXTRL_HOST_FN ArchVariantMixin(
            ArchVariantMixin< Base > const& other ) = default;

        SIXTRL_HOST_FN ArchVariantMixin(
            ArchVariantMixin< Base >&& other ) = default;

        SIXTRL_HOST_FN ArchVariantMixin< Base >& operator=(
            ArchVariantMixin< Base > const& rhs ) = default;

        SIXTRL_HOST_FN ArchVariantMixin< Base >& operator=(
            ArchVariantMixin< Base >&& rhs ) = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN variant_t variant() const SIXTRL_NOEXCEPT
        {
            return this->m_variant_flags;
        }

        SIXTRL_HOST_FN variant_t variantFlags() const SIXTRL_NOEXCEPT
        {
            return this->m_variant_flags;
        }

        SIXTRL_HOST_FN bool areVariantFlagsSet(
            variant_t const var_flags ) const SIXTRL_NOEXCEPT
        {
            using _this_t = SIXTRL_CXX_NAMESPACE::ArchVariantMixin< Base >;
            return _this_t::AreVariantFlagsSet(
                this->m_variant_flags, var_flags );
        }

        SIXTRL_HOST_FN bool variantDebugMode() const SIXTRL_NOEXCEPT
        {
            return this->areVariantFlagsSet( VARIANT_DEBUG );
        }

        SIXTRL_HOST_FN bool variantReleaseMode() const SIXTRL_NOEXCEPT
        {
            return !this->variantDebugMode();
        }

        /* ----------------------------------------------------------------- */

        protected:

        static SIXTRL_HOST_FN bool AreVariantFlagsSet(
            variant_t const haystack, variant_t const needle ) SIXTRL_NOEXCEPT
        {
            return ( ( needle != SIXTRL_CXX_NAMESPACE::ARCH_VARIANT_NONE ) &&
                     ( needle == ( haystack & needle ) ) );
        }

        static SIXTRL_HOST_FN variant_t AddVariantFlags(
            variant_t const variants,
            variant_t const add_these_flags ) SIXTRL_NOEXCEPT
        {
            return ( variants | add_these_flags );
        }

        static SIXTRL_HOST_FN variant_t RemoveVariantFlags(
            variant_t const variants,
            variant_t const remove_these_flags ) SIXTRL_NOEXCEPT
        {
            return ( variants & ~( remove_these_flags ) );
        }

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN void doSetVariantFlags(
            variant_t const variant_flags ) SIXTRL_NOEXCEPT
        {
            this->m_variant_flags = variant_flags;
        }

        SIXTRL_HOST_FN status_t doAddVariantFlags(
            variant_t const add_these_flags ) SIXTRL_NOEXCEPT
        {
            using _this_t = SIXTRL_CXX_NAMESPACE::ArchVariantMixin< Base >;
            status_t status = SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
            variant_t const current_variant = this->m_variant_flags;

            this->m_variant_flags = _this_t::AddVariantFlags(
                this->m_variant_flags, add_these_flags );

            return ( this->m_variant_flags != current_variant )
                ? SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS
                : SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
        }

        SIXTRL_HOST_FN status_t doRemoveVariantFlags(
            variant_t const remove_these_flags ) SIXTRL_NOEXCEPT
        {
            using _this_t = SIXTRL_CXX_NAMESPACE::ArchVariantMixin< Base >;
            status_t status = SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
            variant_t const current_variant = this->m_variant_flags;

            this->m_variant_flags = _this_t::RemoveVariantFlags(
                this->m_variant_flags, remove_these_flags );

            return ( this->m_variant_flags != current_variant )
                ? SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS
                : SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
        }

        private:

        variant_t m_variant_flags;
    };
}

#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_CONTROL_ARCH_VARIANT_MIXIN_CXX_HPP__ */

/* end: sixtracklib/common/control/arch_variant_mixin.hpp */
