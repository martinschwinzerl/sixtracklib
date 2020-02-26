#ifndef SIXTRACKLIB_COMMON_INTERNAL_OBJ_CONVERT_CXX_HPP__
#define SIXTRACKLIB_COMMON_INTERNAL_OBJ_CONVERT_CXX_HPP__

#if defined( __cplusplus )
#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <type_traits>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/internal/obj_store_traits.hpp"
    #include "sixtracklib/common/internal/obj_illegal_type.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template< class Source, class Dest, store_backend_t SourceStoreT,
              store_backend_t DestStoreT = SourceStoreT >
    struct ObjDataAllowConversionTraits
    {
        static SIXTRL_FN constexpr bool allow() SIXTRL_NOEXCEPT
        {
            return false;
        }
    };

    template< class Source, class Dest,
              store_backend_t SourceStoreT, store_backend_t DestStoreT >
    static SIXTRL_FN constexpr bool ObjData_allow_conversion() SIXTRL_NOEXCEPT
    {
        return ObjDataAllowConversionTraits<
            Source, Dest, SourceStoreT, DestStoreT >::allow();
    }

    template< class Source, class Dest,
              store_backend_t SourceStoreT, store_backend_t DestStoreT >
    static SIXTRL_FN constexpr bool
    ObjData_not_allow_conversion() SIXTRL_NOEXCEPT
    {
        return !ObjDataAllowConversionTraits<
            Source, Dest, SourceStoreT, DestStoreT >::allow();
    }

    /* ---------------------------------------------------------------------- */

    template< class Source, class Dest,
              store_backend_t SrcStoreT, store_backend_t DstStoreT >
    struct ObjDataConversionPrepare
    {
        template< class S = Source, class D = Dest >
        static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
            !SIXTRL_CXX_NAMESPACE::ObjData_allow_conversion<
                S, D, SrcStoreT, DstStoreT >(),
            SIXTRL_CXX_NAMESPACE::arch_status_t >::type
        prepare(
            SIXTRL_ARGPTR_DEC D* SIXTRL_RESTRICT /* ptr_dest */,
            SIXTRL_ARGPTR_DEC const S *const SIXTRL_RESTRICT /* ptr_src */
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
        }

        template< class S = Source, class D = Dest >
        static SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::ObjData_allow_conversion<
                S, D, SrcStoreT, DstStoreT >(),
            SIXTRL_CXX_NAMESPACE::arch_status_t >::type
        prepare(
            SIXTRL_ARGPTR_DEC D* SIXTRL_RESTRICT /* ptr_dest */,
            SIXTRL_ARGPTR_DEC const S *const SIXTRL_RESTRICT /* ptr_src */
        ) SIXTRL_NOEXCEPT
        {
            /* Default: Nothing to prepare, return success */
            return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
        }
    };

    template< class Source, class Dest,
              store_backend_t SrcStoreT, store_backend_t DstStoreT >
    struct ObjDataConverter
    {
        static_assert( SIXTRL_CXX_NAMESPACE::ObjData_allow_conversion<
            Source, Dest, SrcStoreT, DstStoreT >(),
            "Only allowed for types that are allowed to be converted -> "
            "specialze ObjDataAllowConversionTraits<> first for this "
            "conversion!" );

        static SIXTRL_FN arch_status_t convert(
            SIXTRL_ARGPTR_DEC Dest* SIXTRL_RESTRICT /* ptr_dest */,
            SIXTRL_ARGPTR_DEC const Source *const SIXTRL_RESTRICT /* ptr_src */
        ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
        }
    };
}

#endif /* C++ */

#endif /* SIXTRACKLIB_COMMON_INTERNAL_OBJ_CONVERT_CXX_HPP__ */
