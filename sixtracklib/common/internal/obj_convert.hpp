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
    #include "sixtracklib/common/internal/compiler_attributes.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template< class SrcT, class DstT, store_backend_t SrcStoreT,
              store_backend_t DstStoreT, typename SFINALE_Enabled = void >
    struct ObjDataAllowConversionTraits
    {
        SIXTRL_STATIC SIXTRL_FN constexpr bool allow() SIXTRL_NOEXCEPT
        {
            return false;
        }
    };

    template< class SrcT, class DstT,
              SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT >
    static SIXTRL_FN constexpr bool
    ObjData_allow_type_conversion() SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ObjDataAllowConversionTraits<
            SrcT, DstT, SrcStoreT, DstStoreT >::allow();
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class SrcT, class DstT,
              SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT,
              typename SFINAE_Enabled = void >
    struct ObjDataConversionTypesRequireNoPrepareTraits
    {
        static_assert( SIXTRL_CXX_NAMESPACE::ObjData_allow_type_conversion<
            SrcT, DstT, SrcStoreT, DstStoreT >(), "Illegal conversion" );

        static constexpr bool requires_no_prepare = true;
    };

    template< class SrcT, class DstT,
              SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT,
              typename SFINAE_Enabled >
    constexpr bool ObjDataConversionTypesRequireNoPrepareTraits< SrcT, DstT,
        SrcStoreT, DstStoreT, SFINAE_Enabled >::requires_no_prepare;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class SrcT, class DstT,
              SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT >
    static SIXTRL_FN constexpr bool
    ObjData_type_conversion_requ_no_prepare() SIXTRL_NOEXCEPT
    {
        return
        SIXTRL_CXX_NAMESPACE::ObjDataConversionTypesRequireNoPrepareTraits<
            SrcT, DstT, SrcStoreT, DstStoreT >::requires_no_prepare;
    }

    template< class SrcT, class DstT,
              SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT >
    static SIXTRL_FN constexpr bool
    ObjData_type_conversion_can_requ_prepare() SIXTRL_NOEXCEPT
    {
        return
        !SIXTRL_CXX_NAMESPACE::ObjDataConversionTypesRequireNoPrepareTraits<
            SrcT, DstT, SrcStoreT, DstStoreT >::requires_no_prepare;
    }

    /* ---------------------------------------------------------------------- */

    template< class SrcT, class DstT,
              SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT,
              typename SFINAE_Enabled = void >
    struct ObjDataConverter
    {
        static_assert( SIXTRL_CXX_NAMESPACE::ObjData_allow_type_conversion<
            SrcT, DstT, SrcStoreT, DstStoreT >(),
            "Only allowed for types that are allowed to be converted -> "
            "specialze ObjDataAllowConversionTraits<> first for this "
            "conversion!" );

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool requires_prepare(
            SIXTRL_ARGPTR_DEC const DstT *const
                SIXTRL_RESTRICT SIXTRL_UNUSED( dst ),
            SIXTRL_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT
                SIXTRL_UNUSED( src ) ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ObjData_type_conversion_can_requ_prepare<
                SrcT, DstT, SrcStoreT, DstStoreT >();
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
        prepare( SIXTRL_ARGPTR_DEC DstT* SIXTRL_RESTRICT SIXTRL_UNUSED( dst ),
                 SIXTRL_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT
                    SIXTRL_UNUSED( src ) ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
        }

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN bool
        allow( SIXTRL_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT
                    SIXTRL_UNUSED( dst ),
               SIXTRL_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT
                   SIXTRL_UNUSED( src ) ) SIXTRL_NOEXCEPT
        {
            return false;
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t attempt_conversion(
            SIXTRL_ARGPTR_DEC DstT* SIXTRL_RESTRICT SIXTRL_UNUSED( dst ),
            SIXTRL_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT
                SIXTRL_UNUSED( src ),
            Args&&... SIXTRL_UNUSED( additional_args ) ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
        }

        template< typename... Args >
        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
        SIXTRL_CXX_NAMESPACE::arch_status_t perform(
            SIXTRL_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
            SIXTRL_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
            Args&&... conv_paramters ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            using this_t = st::ObjDataConverter<
                SrcT, DstT, SrcStoreT, DstStoreT >;

            st::arch_status_t status = this_t::attempt_conversion(
                dst, src, std::forward< Args >( conv_paramters )... );

            if( ( status != st::ARCH_STATUS_SUCCESS ) &&
                ( this_t::requires_prepare( dst, src ) ) )
            {
                status = this_t::prepare( dst, src );

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    status = this_t::attempt_conversion(
                        dst, src, std::forward< Args >( conv_paramters )... );
                }
            }

            return status;
        }
    };

    /* --------------------------------------------------------------------- */

    template< class E,
              SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT =
                  SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT = SrcStoreT >
    SIXTRL_STATIC SIXTRL_FN constexpr
    bool ObjData_allow_type_copy() SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ObjData_allow_type_conversion<
            E, E, SrcStoreT, DstStoreT >();
    }

    template< class E,
              SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT =
                  SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT = SrcStoreT >
    SIXTRL_STATIC SIXTRL_FN constexpr
    bool ObjData_type_copy_requ_no_prepare() SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ObjData_type_conversion_requ_no_prepare<
            E, E, SrcStoreT, DstStoreT >();
    }

    template< class E,
              SIXTRL_CXX_NAMESPACE::store_backend_t SrcStoreT =
                  SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
              SIXTRL_CXX_NAMESPACE::store_backend_t DstStoreT = SrcStoreT >
    SIXTRL_STATIC SIXTRL_FN constexpr
    bool ObjData_type_copy_can_requ_prepare() SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ObjData_type_conversion_can_requ_prepare<
            E, E, SrcStoreT, DstStoreT >();
    }


}

#endif /* C++ */

#endif /* SIXTRACKLIB_COMMON_INTERNAL_OBJ_CONVERT_CXX_HPP__ */
