#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_CONVERT_COBJECTS_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_CONVERT_COBJECTS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/beam_elements/drift/definitions.h"
    #include "sixtracklib/common/beam_elements/drift/drift.h"
    #include "sixtracklib/common/beam_elements/drift/drift_data.hpp"
    #include "sixtracklib/common/internal/obj_convert.hpp"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )

#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    /* ---------------------------------------------------------------------- */
    /* Allow Conversion from NS(Drift) to general DriftData<>
     * on the CObjects storage be */

    /* NS(Drift) -> Source
     * DriftData< R, RAlign > -> Destination */

    template< class R, arch_size_t RAlign, store_backend_t SrcStoreT >
    struct ObjDataAllowConversionTraits< ::NS(Drift), DriftData< R, RAlign >,
        SrcStoreT, STORAGE_BE_COBJECTS >
    {
        static SIXTRL_FN constexpr bool allow() SIXTRL_NOEXCEPT
        {
            return ( SrcStoreT != STORAGE_BE_ILLEGAL ) &&
                SIXTRL_CXX_NAMESPACE::Types_are_assignable_or_convertible<
                    DriftTraits< ::NS(Drift) >::real_t,
                    typename DriftTraits< DriftData< R, RAlign > >::real_t >();
        }
    };

    /* No prepare necessary -> we can use the default implementation */

    template< class R, arch_size_t RAlign, store_backend_t SrcStoreT >
    struct ObjDataConverter<
        ::NS(Drift), DriftData< R, RAlign >, SrcStoreT, STORAGE_BE_COBJECTS >
    {
        typedef DriftData< R, RAlign > destination_t;

        static_assert( SIXTRL_CXX_NAMESPACE::ObjData_allow_conversion<
            ::NS(Drift), destination_t, SrcStoreT, STORAGE_BE_COBJECTS >(),
           "Conversion from NS(Drift) to DriftData< R, RAlign > not allowed" );

        static SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
        convert( SIXTRL_ARGPTR_DEC DriftData< R, RAlign >*
                SIXTRL_RESTRICT ptr_dest,
            SIXTRL_ARGPTR_DEC const ::NS(Drift) *const SIXTRL_RESTRICT ptr_src
        ) SIXTRL_NOEXCEPT
        {
            typedef typename DriftTraits< destination_t >::real_t dest_real_t;
            typedef DriftTraits< ::NS(Drift) >::real_t src_real_t;

            SIXTRL_ASSERT( ptr_dest != nullptr );
            SIXTRL_ASSERT( ptr_src  != nullptr );
            SIXTRL_ASSERT( reinterpret_cast< uintptr_t >( ptr_dest ) !=
                           reinterpret_cast< uintptr_t >( ptr_src ) );

            SIXTRL_CXX_NAMESPACE::Type_perform_assignment<
                src_real_t, dest_real_t >( ptr_dest->length, ptr_src->length );

            return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
        }
    };

    /* ---------------------------------------------------------------------- */
    /* Allow Conversion from general DriftData<> to NS(Drift)
     * on the CObjects storage be */

    template< class R, arch_size_t RAlign, store_backend_t DstStoreT >
    struct ObjDataAllowConversionTraits< DriftData< R, RAlign >, ::NS(Drift),
        STORAGE_BE_COBJECTS, DstStoreT >
    {
        static SIXTRL_FN constexpr bool allow() SIXTRL_NOEXCEPT
        {
            return ( DstStoreT != STORAGE_BE_ILLEGAL ) &&
                SIXTRL_CXX_NAMESPACE::Types_are_assignable_or_convertible<
                    typename DriftTraits< DriftData< R, RAlign > >::real_t,
                    DriftTraits< ::NS(Drift) >::real_t >();
        }
    };

    /* No prepare necessary -> we can use the default implementation */

    template< class R, arch_size_t RAlign, store_backend_t DstStoreT >
    struct ObjDataConverter<
        DriftData< R, RAlign >, ::NS(Drift), STORAGE_BE_COBJECTS, DstStoreT >
    {
        typedef DriftData< R, RAlign >  source_t;

        static_assert( SIXTRL_CXX_NAMESPACE::ObjData_allow_conversion<
            source_t, ::NS(Drift), STORAGE_BE_COBJECTS, DstStoreT >(),
           "Conversion from DriftData< R, RAlign > to NS(Drift) not allowed" );

        static SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
        convert( SIXTRL_ARGPTR_DEC ::NS(Drift)* SIXTRL_RESTRICT ptr_dest,
            SIXTRL_ARGPTR_DEC const DriftData< R, RAlign > *const
                SIXTRL_RESTRICT ptr_src ) SIXTRL_NOEXCEPT
        {
            typedef typename DriftTraits< source_t >::real_t src_real_t;
            typedef DriftTraits< ::NS(Drift) >::real_t dest_real_t;

            SIXTRL_ASSERT( ptr_dest != nullptr );
            SIXTRL_ASSERT( ptr_src  != nullptr );
            SIXTRL_ASSERT( reinterpret_cast< uintptr_t >( ptr_dest ) !=
                           reinterpret_cast< uintptr_t >( ptr_src ) );

            SIXTRL_CXX_NAMESPACE::Type_perform_assignment<
                src_real_t, dest_real_t >( ptr_dest->length, ptr_src->length );

            return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
        }
    };

    /* ---------------------------------------------------------------------- */
    /* Allow General DriftData<> -> DriftData<> for the Cobjects storage be */

    template<
        class SrcReal, arch_size_t SrcRealAlign, store_backend_t SrcStoreT,
        class DstReal, arch_size_t DstRealAlign, store_backend_t DstStoreT >
    struct ObjDataAllowConversionTraits<
        DriftData< SrcReal, SrcRealAlign >,
        DriftData< DstReal, DstRealAlign >, SrcStoreT, DstStoreT >
    {
        static SIXTRL_FN constexpr bool allow() SIXTRL_NOEXCEPT
        {
            return  ( SrcStoreT != STORAGE_BE_ILLEGAL ) &&
                    ( DstStoreT != STORAGE_BE_ILLEGAL ) &&
                    ( SIXTRL_CXX_NAMESPACE::Types_are_assignable_or_convertible<
                        typename DriftTraits< DriftData<
                            SrcReal, SrcRealAlign > >::real_t,
                        typename DriftTraits< DriftData<
                            DstReal, DstRealAlign > >::real_t >() );
        }
    };

    /* No prepare necessary -> we can use the default implementation */

    template<
        class SrcReal, arch_size_t SrcRealAlign, store_backend_t SrcStoreT,
        class DstReal, arch_size_t DstRealAlign, store_backend_t DstStoreT >
    struct ObjDataConverter<
        DriftData< SrcReal, SrcRealAlign >, DriftData< DstReal, DstRealAlign >,
        SrcStoreT, DstStoreT >
    {
        typedef DriftData< SrcReal, SrcRealAlign >  source_t;
        typedef DriftData< DstReal, DstRealAlign >  destination_t;

        static_assert( SIXTRL_CXX_NAMESPACE::ObjData_allow_conversion<
            source_t, destination_t, STORAGE_BE_COBJECTS, DstStoreT >(),
           "Conversion from DriftData< SrcReal, SrcRealAlign > to "
           "DriftData< DstReal, DstRealAlign > not allowed" );

        static SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
        convert( SIXTRL_ARGPTR_DEC DriftData< DstReal, DstRealAlign >*
                SIXTRL_RESTRICT ptr_dest,
            SIXTRL_ARGPTR_DEC const DriftData< SrcReal, SrcRealAlign > *const
                SIXTRL_RESTRICT ptr_src ) SIXTRL_NOEXCEPT
        {
            typedef typename DriftTraits< destination_t >::real_t dest_real_t;
            typedef typename DriftTraits< source_t >::real_t src_real_t;

            SIXTRL_ASSERT( ptr_dest != nullptr );
            SIXTRL_ASSERT( ptr_src  != nullptr );
            SIXTRL_ASSERT( reinterpret_cast< uintptr_t >( ptr_dest ) !=
                           reinterpret_cast< uintptr_t >( ptr_src ) );

            SIXTRL_CXX_NAMESPACE::Type_perform_assignment<
                src_real_t, dest_real_t >( ptr_dest->length, ptr_src->length );

            return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
        }
    };
}

#endif /* defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_CONVERT_COBJECTS_H__ */
