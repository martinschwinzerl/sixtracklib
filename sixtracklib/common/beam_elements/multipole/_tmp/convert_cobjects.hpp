#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_CONVERT_COBJECTS_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_CONVERT_COBJECTS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/beam_elements/multipole/multipole_api.h"
    #include "sixtracklib/common/beam_elements/multipole/multipole_data_api.hpp"
    #include "sixtracklib/common/internal/obj_convert.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )

#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    /* ---------------------------------------------------------------------- */
    /* Allow Conversion from NS(Multipole) to general MultipoleData<>
     * on the CObjects storage be */

    /* NS(Multipole) -> Source
     * MultipoleData< R, RAlign > -> Destination */

    template< class R, class O, arch_size_t RAlign, arch_size_t OAlign,
              store_backend_t SrcStoreT >
    struct ObjDataAllowConversionTraits< ::NS(Multipole),
        MultipoleData< R, O, RAlign, OAlign >, SrcStoreT, STORAGE_BE_COBJECTS >
    {
        static SIXTRL_FN constexpr bool allow() SIXTRL_NOEXCEPT
        {
            return ( SrcStoreT != STORAGE_BE_ILLEGAL ) &&
                SIXTRL_CXX_NAMESPACE::Types_can_perform_assignment<
                    MultipoleTraits< ::NS(Multipole) >::real_t,
                    typename MultipoleTraits< MultipoleData< R, O, RAlign, OAlign >
                >::real_t >() &&
                SIXTRL_CXX_NAMESPACE::Types_can_perform_assignment<
                    MultipoleTraits< ::NS(Multipole) >::order_t,
                    typename MultipoleTraits< MultipoleData< R, O, RAlign, OAlign >
                >::order_t >();
        }
    };

    template< class R, class O, arch_size_t RAlign, arch_size_t OAlign,
              store_backend_t SrcStoreT >
    struct ObjDataConversionPrepare< ::NS(Multipole),
        MultipoleData< R, O, RAlign, OAlign >, SrcStoreT, STORAGE_BE_COBJECTS >
    {
        static SIXTRL_INLINE SIXTRL_FN arch_status_t prepare(
            SIXTRL_BE_ARGPTR_DEC MultipoleData< R, O, RAlign, OAlign >*
                SIXTRL_RESTRICT dest,
            SIXTRL_BE_ARGPTR_DEC const ::NS(Multipole) *const
                SIXTRL_RESTRICT src ) SIXTRL_NOEXCEPT
        {
            SIXTRL_CXX_NAMESPACE::arch_status_t success =
                SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;

            if( ( src != nullptr ) && ( dest != nullptr ) )
            {
                SIXTRL_CXX_NAMESPACE::Multipole_init( dest, src->order );
                success = SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
            }

            return success;
        }
    };

    template< class R, class O, arch_size_t RAlign, arch_size_t OAlign,
              store_backend_t SrcStoreT >
    struct ObjDataConverter< ::NS(Multipole),
        MultipoleData< R, O, RAlign, OAlign >, SrcStoreT, STORAGE_BE_COBJECTS >
    {
        typedef ::NS(Multipole) source_t;
        typedef MultipoleData< R, O, RAlign, OAlign > destination_t;

        static_assert( SIXTRL_CXX_NAMESPACE::ObjData_allow_conversion<
            source_t, destination_t, SrcStoreT, STORAGE_BE_COBJECTS >(),
           "Conversion from NS(Multipole) to "
           "MultipoleData< R, O, RAlign, OAlign > not allowed" );

        static SIXTRL_INLINE SIXTRL_FN arch_status_t convert(
            SIXTRL_BE_ARGPTR_DEC destination_t* SIXTRL_RESTRICT dest,
            SIXTRL_BE_ARGPTR_DEC const source_t *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            SIXTRL_CXX_NAMESPACE::arch_status_t success =
                SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;

            if( SIXTRL_CXX_NAMESPACE::Multipole_bal_length( dest ) ==
                SIXTRL_CXX_NAMESPACE::Multipole_bal_length( src ) )
            {
                SIXTRL_CXX_NAMESPACE::Multipole_set_length( dest,
                    SIXTRL_CXX_NAMESPACE::Multipole_length( src ) );

                SIXTRL_CXX_NAMESPACE::Multipole_set_hxl( dest,
                    SIXTRL_CXX_NAMESPACE::Multipole_hxl( src ) );

                SIXTRL_CXX_NAMESPACE::Multipole_set_hyl( dest,
                    SIXTRL_CXX_NAMESPACE::Multipole_hyl( src ) );

                SIXTRL_CXX_NAMESPACE::Multipole_set_bal( dest,
                    SIXTRL_CXX_NAMESPACE::Multipole_bal_const_begin( src ) );

                success = SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
            }

            return success;
        }
    };

    /* ---------------------------------------------------------------------- */
    /* Allow Conversion from general MultipoleData<> to NS(Multipole)
     * on the CObjects storage be */

    template< class R, class O, arch_size_t RAlign, arch_size_t OAlign,
              store_backend_t DstStoreT >
    struct ObjDataAllowConversionTraits< MultipoleData< R, O, RAlign, OAlign >,
        ::NS(Multipole), STORAGE_BE_COBJECTS, DstStoreT >
    {
        static SIXTRL_FN constexpr bool allow() SIXTRL_NOEXCEPT
        {
            return ( DstStoreT != STORAGE_BE_ILLEGAL ) &&
                SIXTRL_CXX_NAMESPACE::Types_can_perform_assignment<
                    typename MultipoleTraits< MultipoleData<
                        R, O, RAlign, OAlign > >::real_t,
                    MultipoleTraits< ::NS(Multipole) >::real_t >() &&
                SIXTRL_CXX_NAMESPACE::Types_can_perform_assignment<
                    typename MultipoleTraits< MultipoleData<
                        R, O, RAlign, OAlign > >::order_t,
                    MultipoleTraits< ::NS(Multipole) >::order_t >();
        }
    };

    template< class R, class O, arch_size_t RAlign, arch_size_t OAlign,
              store_backend_t DstStoreT >
    struct ObjDataConversionPrepare< MultipoleData< R, O, RAlign, OAlign >,
        ::NS(Multipole), STORAGE_BE_COBJECTS, DstStoreT >
    {
        static SIXTRL_INLINE SIXTRL_FN arch_status_t prepare(
            SIXTRL_BE_ARGPTR_DEC const ::NS(Multipole) *const
                SIXTRL_RESTRICT dest,
            SIXTRL_BE_ARGPTR_DEC const MultipoleData< R, O, RAlign, OAlign >
                *const SIXTRL_RESTRICT src ) SIXTRL_NOEXCEPT
        {
            SIXTRL_CXX_NAMESPACE::arch_status_t success =
                SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;

            if( ( src != nullptr ) && ( dest != nullptr ) )
            {
                SIXTRL_CXX_NAMESPACE::Multipole_init( dest, src->order );
                success = SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
            }

            return success;
        }
    };

    template< class R, class O, arch_size_t RAlign, arch_size_t OAlign,
              store_backend_t DstStoreT >
    struct ObjDataConverter< MultipoleData< R, O, RAlign, OAlign >,
        ::NS(Multipole), STORAGE_BE_COBJECTS, DstStoreT >
    {
        typedef ::NS(Multipole) destination_t;
        typedef MultipoleData< R, O, RAlign, OAlign > src_t;

        static_assert( SIXTRL_CXX_NAMESPACE::ObjData_allow_conversion<
            src_t, destination_t, STORAGE_BE_COBJECTS, DstStoreT >(),
           "Conversion from MultipoleData< R, O, RAlign, OAlign > to "
           "NS(Multipole) not allowed" );

        static SIXTRL_INLINE SIXTRL_FN arch_status_t convert(
            SIXTRL_BE_ARGPTR_DEC destination_t* SIXTRL_RESTRICT dest,
            SIXTRL_BE_ARGPTR_DEC const src_t *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            SIXTRL_CXX_NAMESPACE::arch_status_t success =
                SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;

            if( SIXTRL_CXX_NAMESPACE::Multipole_bal_length( dest ) ==
                SIXTRL_CXX_NAMESPACE::Multipole_bal_length( src ) )
            {
                SIXTRL_CXX_NAMESPACE::Multipole_set_length( dest,
                    SIXTRL_CXX_NAMESPACE::Multipole_length( src ) );

                SIXTRL_CXX_NAMESPACE::Multipole_set_hxl( dest,
                    SIXTRL_CXX_NAMESPACE::Multipole_hxl( src ) );

                SIXTRL_CXX_NAMESPACE::Multipole_set_hyl( dest,
                    SIXTRL_CXX_NAMESPACE::Multipole_hyl( src ) );

                SIXTRL_CXX_NAMESPACE::Multipole_set_bal( dest,
                    SIXTRL_CXX_NAMESPACE::Multipole_bal_const_begin( src ) );

                success = SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
            }

            return success;
        }
    };

    /* ---------------------------------------------------------------------- */
    /* Allow General MultipoleData<> -> MultipoleData<> for the Cobjects storage be */

    template<
        class SrcR, class SrcO, arch_size_t SrcRAlign, arch_size_t SrcOAlign,
        class DstR, class DstO, arch_size_t DstRAlign, arch_size_t DstOAlign,
        store_backend_t SrcStoreT, store_backend_t DstStoreT >
    struct ObjDataAllowConversionTraits<
        MultipoleData< SrcR, SrcO, SrcRAlign, SrcOAlign >,
        MultipoleData< DstR, DstO, DstRAlign, DstOAlign >, SrcStoreT, DstStoreT >
    {
        static SIXTRL_FN constexpr bool allow() SIXTRL_NOEXCEPT
        {
            return
                ( SrcStoreT != STORAGE_BE_ILLEGAL ) &&
                ( DstStoreT != STORAGE_BE_ILLEGAL ) &&
                SIXTRL_CXX_NAMESPACE::Types_can_perform_assignment<
                    typename MultipoleTraits< MultipoleData<
                        SrcR, SrcO, SrcRAlign, SrcOAlign > >::real_t,
                    typename MultipoleTraits< MultipoleData<
                        DstR, DstO, DstRAlign, DstOAlign > >::real_t >() &&
                SIXTRL_CXX_NAMESPACE::Types_can_perform_assignment<
                    typename MultipoleTraits< MultipoleData<
                        SrcR, SrcO, SrcRAlign, SrcOAlign > >::order_t,
                    typename MultipoleTraits< MultipoleData<
                        DstR, DstO, DstRAlign, DstOAlign > >::order_t >();
        }
    };

    template<
        class SrcR, class SrcO, arch_size_t SrcRAlign, arch_size_t SrcOAlign,
        class DstR, class DstO, arch_size_t DstRAlign, arch_size_t DstOAlign,
        store_backend_t SrcStoreT, store_backend_t DstStoreT >
    struct ObjDataConversionPrepare<
        MultipoleData< SrcR, SrcO, SrcRAlign, SrcOAlign >,
        MultipoleData< DstR, DstO, DstRAlign, DstOAlign >,
        SrcStoreT, DstStoreT >
    {
        static SIXTRL_INLINE SIXTRL_FN arch_status_t prepare(
            SIXTRL_BE_ARGPTR_DEC const MultipoleData<
                DstR, DstO, DstRAlign, DstOAlign > *const SIXTRL_RESTRICT dest,
            SIXTRL_BE_ARGPTR_DEC const MultipoleData<
                SrcR, SrcO, SrcRAlign, SrcOAlign > *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            SIXTRL_CXX_NAMESPACE::arch_status_t success =
                SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;

            if( ( src != nullptr ) && ( dest != nullptr ) )
            {
                SIXTRL_CXX_NAMESPACE::Multipole_init( dest, src->order );
                success = SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
            }

            return success;
        }
    };

    template<
        class SrcR, class SrcO, arch_size_t SrcRAlign, arch_size_t SrcOAlign,
        class DstR, class DstO, arch_size_t DstRAlign, arch_size_t DstOAlign,
        store_backend_t SrcStoreT, store_backend_t DstStoreT >
    struct ObjDataConverter<
        MultipoleData< SrcR, SrcO, SrcRAlign, SrcOAlign >,
        MultipoleData< DstR, DstO, DstRAlign, DstOAlign >,
        SrcStoreT, DstStoreT >
    {
        typedef MultipoleData< SrcR, SrcO, SrcRAlign, SrcOAlign > src_t;
        typedef MultipoleData< DstR, DstO, DstRAlign, DstOAlign > dest_t;

        static_assert( SIXTRL_CXX_NAMESPACE::ObjData_allow_conversion<
            src_t, dest_t, STORAGE_BE_COBJECTS, DstStoreT >(),
           "Conversion from MultipoleData< SrcR, SrcO, SrcRAlign, SrcOAlign > "
           "to MultipoleData< DstR, DstO, DstRAlign, DstOAlign > not allowed"
        );

        static SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
        convert( SIXTRL_ARGPTR_DEC dest_t* SIXTRL_RESTRICT dest,
            SIXTRL_ARGPTR_DEC const src_t *const SIXTRL_RESTRICT src
        ) SIXTRL_NOEXCEPT
        {
            SIXTRL_CXX_NAMESPACE::arch_status_t success =
                SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;

            if( SIXTRL_CXX_NAMESPACE::Multipole_bal_length( dest ) ==
                SIXTRL_CXX_NAMESPACE::Multipole_bal_length( src ) )
            {
                SIXTRL_CXX_NAMESPACE::Multipole_set_length( dest,
                    SIXTRL_CXX_NAMESPACE::Multipole_length( src ) );

                SIXTRL_CXX_NAMESPACE::Multipole_set_hxl( dest,
                    SIXTRL_CXX_NAMESPACE::Multipole_hxl( src ) );

                SIXTRL_CXX_NAMESPACE::Multipole_set_hyl( dest,
                    SIXTRL_CXX_NAMESPACE::Multipole_hyl( src ) );

                SIXTRL_CXX_NAMESPACE::Multipole_set_bal( dest,
                    SIXTRL_CXX_NAMESPACE::Multipole_bal_const_begin( src ) );

                success = SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
            }

            return success;
        }
    };
}

#endif /* defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_CONVERT_COBJECTS_H__ */
