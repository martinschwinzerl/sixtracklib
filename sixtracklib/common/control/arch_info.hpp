#ifndef SIXTRACKLIB_COMMON_CONTROL_ARCH_INFO_HPP__
#define SIXTRACKLIB_COMMON_CONTROL_ARCH_INFO_HPP__

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cstddef>
    #include <cstdlib>
    #include <string>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */
#endif /* C++, Host */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/architecture/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/buffer/buffer_type.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */


#if  defined( __cplusplus ) && !defined( _GPUCODE ) && \
    !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

namespace SIXTRL_CXX_NAMESPACE
{
    class ArchInfo
    {
        public:

        using arch_id_t    = SIXTRL_CXX_NAMESPACE::arch_id_t;
        using size_type    = SIXTRL_CXX_NAMESPACE::arch_size_t;
        using status_t     = SIXTRL_CXX_NAMESPACE::arch_status_t;

        static constexpr arch_id_t ILLEGAL_ARCH =
            SIXTRL_CXX_NAMESPACE::ARCHITECTURE_ILLEGAL;

        /* ----------------------------------------------------------------- */

        SIXTRL_STATIC SIXTRL_HOST_FN status_t SanitizeArchStr(
            std::string& SIXTRL_RESTRICT_REF arch_str );

        SIXTRL_STATIC SIXTRL_HOST_FN status_t SanitizeArchStr(
            char* SIXTRL_RESTRICT arch_str,
            size_type const arch_str_capacity );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN explicit ArchInfo(
            arch_id_t const arch_id = ILLEGAL_ARCH );

        SIXTRL_HOST_FN ArchInfo( ArchInfo const& other ) = default;
        SIXTRL_HOST_FN ArchInfo( ArchInfo&& other ) = default;

        SIXTRL_HOST_FN ArchInfo& operator=( ArchInfo const& rhs ) = default;
        SIXTRL_HOST_FN ArchInfo& operator=( ArchInfo&& rhs ) = default;
        SIXTRL_HOST_FN virtual ~ArchInfo() = default;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN arch_id_t archId() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool hasArchStr() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN std::string const& archStr() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN char const* ptrArchStr() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isArchCompatibleWith(
            arch_id_t const arch_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isArchCompatibleWith(
            ArchInfo const& SIXTRL_RESTRICT other ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isArchIdenticalTo(
            arch_id_t const arch_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isArchIdenticalTo(
            ArchInfo const& SIXTRL_RESTRICT rhs ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t reset( arch_id_t const arch_id );
        SIXTRL_HOST_FN status_t reset();

        protected:

        SIXTRL_HOST_FN status_t doSetArchId( arch_id_t const arch_id );

        private:

        std::string m_arch_str;
        arch_id_t   m_arch_id;
    };

    SIXTRL_CXX_NAMESPACE::arch_status_t ArchInfo_sanitize_arch_str(
        std::string& SIXTRL_RESTRICT_REF arch_str );

    SIXTRL_CXX_NAMESPACE::arch_status_t ArchInfo_sanitize_arch_str(
        char* SIXTRL_RESTRICT arch_str,
        SIXTRL_CXX_NAMESPACE::arch_size_t const arch_str_capacity );
}
#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++ */

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

typedef SIXTRL_CXX_NAMESPACE::ArchInfo NS(ArchInfo);

#else /* C++, Host */

typedef void NS(ArchInfo);

#endif /* C++, Host */

NS(arch_status_t) NS(ArchInfo_sanitize_arch_str)(
    char* SIXTRL_RESTRICT arch_str,
    NS(arch_size_t) const arch_str_capacity );

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++ */

/* ************************************************************************* */
/* ********     Inline and template function implementation     ************ */
/* ************************************************************************* */

#if  defined( __cplusplus ) && !defined( _GPUCODE ) && \
    !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <algorithm>
    #include <cstring>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    SIXTRL_INLINE ArchInfo::status_t ArchInfo::SanitizeArchStr(
        std::string& SIXTRL_RESTRICT_REF arch_str )
    {
        return SIXTRL_CXX_NAMESPACE::ArchInfo_sanitize_arch_str( arch_str );
    }

    SIXTRL_INLINE ArchInfo::status_t ArchInfo::SanitizeArchStr(
        char* SIXTRL_RESTRICT arch_str,
        ArchInfo::size_type const arch_str_capacity )
    {
        return SIXTRL_CXX_NAMESPACE::ArchInfo_sanitize_arch_str(
            arch_str, arch_str_capacity );
    }

    /* --------------------------------------------------------------------- */

}

#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_CONTROL_ARCH_INFO_HPP__ */

/* end: sixtracklib/common/control/arch_info.hpp */
