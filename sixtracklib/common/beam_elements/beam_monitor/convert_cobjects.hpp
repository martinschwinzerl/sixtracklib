#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_BEAM_MONITOR_CONVERT_COBJECTS_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_BEAM_MONITOR_CONVERT_COBJECTS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/beam_elements/beam_monitor/beam_monitor_api.h"
    #include "sixtracklib/common/beam_elements/beam_monitor/beam_monitor_data_api.hpp"
    #include "sixtracklib/common/internal/obj_convert.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )

#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        template< class SrcBeamMonitorT, class DestBeamMonitorT >
        SIXTRL_STATIC SIXTRL_FN arch_status_t BeamMonitor_convert_generic(
            SIXTRL_BE_ARGPTR_DEC DestBeamMonitorT* SIXTRL_RESTRICT dest,
            SIXTRL_BE_ARGPTR_DEC const SrcBeamMonitorT *const SIXTRL_RESTRICT src
        )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;

            st::arch_status_t status = st::BeamMonitor_set_num_stores( dest,
                st::BeamMonitor_num_stores( dest ) );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                status = st::BeamMonitor_set_start_turn( dest,
                st::BeamMonitor_start_turn( dest ) );
            }

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                status = st::BeamMonitor_set_skip_turns( dest,
                    st::BeamMonitor_skip_turns( src ) );
            }

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                status = st::BeamMonitor_set_out_address( dest,
                    st::BeamMonitor_out_address( src ) );
            }

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                status = st::BeamMonitor_set_min_particle_id( dest,
                    st::BeamMonitor_min_particle_id( src ) );
            }

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                status = st::BeamMonitor_set_max_particle_id( dest,
                    st::BeamMonitor_max_particle_id( src ) );
            }

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                status = st::BeamMonitor_set_is_rolling_flag( dest,
                    st::BeamMonitor_is_rolling_flag( src ) );
            }

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                status = st::BeamMonitor_set_is_turn_ordered_flag( dest,
                    st::BeamMonitor_is_turn_ordered_flag( src ) );
            }

            return status;
        }
    }

    /* ---------------------------------------------------------------------- */
    /* Allow Conversion from NS(BeamMonitor) to general BeamMonitorData<>
     * on the CObjects storage be */

    /* NS(BeamMonitor) -> Source
     * BeamMonitorData< R, RAlign > -> Destination */

    template< class R, class I, arch_size_t IAlign, store_backend_t SrcStoreT >
    struct ObjDataAllowConversionTraits< ::NS(BeamMonitor),
        BeamMonitorData< R, I, IAlign >, SrcStoreT, STORAGE_BE_COBJECTS >
    {
        typedef ::NS(BeamMonitor) src_t;
        typedef BeamMonitorTraits< src_t >::particle_real_t  src_real_t;
        typedef BeamMonitorTraits< src_t >::particle_index_t src_index_t;

        typedef BeamMonitorData< R, I, IAlign > dest_t;
        typedef typename BeamMonitorTraits< dest_t >::particle_real_t
                dest_real_t;

        typedef typename BeamMonitorTraits< dest_t >::particle_ndex_t
                dest_index_t;

        static SIXTRL_FN constexpr bool allow() SIXTRL_NOEXCEPT
        {
            return (
                ( SrcStoreT != STORAGE_BE_ILLEGAL ) &&
                ( SIXTRL_CXX_NAMESPACE::Types_can_perform_assignment<
                    src_real_t, dest_real_t >() ) &&
                ( SIXTRL_CXX_NAMESPACE::Types_can_perform_assignment<
                    src_index_t, dest_index_t >() ) );
        }
    };

    /* No prepare necessary -> we can use the default implementation */

    template< class R, class I, arch_size_t IAlign, store_backend_t SrcStoreT >
    struct ObjDataConverter< ::NS(BeamMonitor), BeamMonitorData< R, I, IAlign >,
        SrcStoreT, STORAGE_BE_COBJECTS >
    {
        typedef ::NS(BeamMonitor) src_t;
        typedef BeamMonitorData< R, I, IAlign > dest_t;

        static_assert( SIXTRL_CXX_NAMESPACE::ObjData_allow_conversion<
            src_t, dest_t, SrcStoreT, STORAGE_BE_COBJECTS >(),
           "Conversion from NS(BeamMonitor) to "
           "BeamMonitorData< R, I, IAlign > not allowed" );

        SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
        convert( SIXTRL_ARGPTR_DEC dest_t* SIXTRL_RESTRICT dest,
                 SIXTRL_ARGPTR_DEC const src_t *const SIXTRL_RESTRICT src )
        {
            return SIXTRL_CXX_NAMESPACE::BeamMonitor_convert_generic( dest, src );
        }
    };

    /* ---------------------------------------------------------------------- */
    /* Allow Conversion from general BeamMonitorData<> to NS(BeamMonitor)
     * on the CObjects storage be */

    template< class R, class I, arch_size_t IAlign, store_backend_t DstStoreT >
    struct ObjDataAllowConversionTraits< BeamMonitorData< R, I, IAlign >,
        ::NS(BeamMonitor), STORAGE_BE_COBJECTS, DstStoreT >
    {
        typedef BeamMonitorData< R, I, IAlign > src_t;
        typedef typename BeamMonitorTraits< src_t >::particle_real_t
                src_real_t;

        typedef typename BeamMonitorTraits< src_t >::particle_index_t
                src_index_t;

        typedef ::NS(BeamMonitor) dest_t;
        typedef typename BeamMonitorTraits< dest_t >::particle_real_t
                dest_real_t;

        typedef typename BeamMonitorTraits< dest_t >::particle_index_t
                dest_index_t;

        static SIXTRL_FN constexpr bool allow() SIXTRL_NOEXCEPT
        {
            return (
                ( DstStoreT != STORAGE_BE_ILLEGAL ) &&
                ( SIXTRL_CXX_NAMESPACE::Types_can_perform_assignment<
                        src_real_t, dest_real_t >() ) &&
                ( SIXTRL_CXX_NAMESPACE::Types_can_perform_assignment<
                        src_index_t, dest_index_t >() ) );
        }
    };

    /* No prepare necessary -> we can use the default implementation */

    template< class R, class I, arch_size_t IAlign, store_backend_t DstStoreT >
    struct ObjDataConverter< BeamMonitorData< R, I, IAlign >,
        ::NS(BeamMonitor), STORAGE_BE_COBJECTS, DstStoreT >
    {
        typedef BeamMonitorData< R, I, IAlign > src_t;
        typedef ::NS(BeamMonitor) dest_t;

        static_assert( SIXTRL_CXX_NAMESPACE::ObjData_allow_conversion<
            src_t, dest_t, STORAGE_BE_COBJECTS, DstStoreT >(),
           "Conversion from BeamMonitorData< R, I, IAlign > "
           "to NS(BeamMonitor) not allowed" );

        static SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
        convert( SIXTRL_ARGPTR_DEC dest_t* SIXTRL_RESTRICT dest,
                 SIXTRL_ARGPTR_DEC const src_t *const SIXTRL_RESTRICT src )
        {
            return SIXTRL_CXX_NAMESPACE::BeamMonitor_convert_generic( dest, src );
        }
    };

    /* ---------------------------------------------------------------------- */
    /* Allow General BeamMonitorData<> -> BeamMonitorData<> for the Cobjects storage be */

    template< class SrcR, class SrcI, arch_size_t SrcIAlign,
              class DstR, class DstI, arch_size_t DstIAlign,
              store_backend_t SrcStoreT, store_backend_t DstStoreT >
    struct ObjDataAllowConversionTraits<
        BeamMonitorData< SrcR, SrcI, SrcIAlign >,
        BeamMonitorData< DstR, DstI, DstIAlign >, SrcStoreT, DstStoreT >
    {
        typedef BeamMonitorData< SrcR, SrcI, SrcIAlign > src_t;
        typedef typename BeamMonitorTraits< src_t >::particle_real_t
                src_real_t;

        typedef typename BeamMonitorTraits< src_t >::particle_index_t
                src_index_t;

        typedef BeamMonitorData< DstR, DstI, DstIAlign > dest_t;
        typedef typename BeamMonitorTraits< dest_t >::particle_real_t
                dest_real_t;

        typedef typename BeamMonitorTraits< dest_t >::particle_index_t
                dest_index_t;

        static SIXTRL_FN constexpr bool allow() SIXTRL_NOEXCEPT
        {
            return (
                ( DstStoreT != STORAGE_BE_ILLEGAL ) &&
                ( SIXTRL_CXX_NAMESPACE::Types_can_perform_assignment<
                        src_real_t, dest_real_t >() ) &&
                ( SIXTRL_CXX_NAMESPACE::Types_can_perform_assignment<
                        src_index_t, dest_index_t >() ) );
        }
    };

    /* No prepare necessary -> we can use the default implementation */

    template< class SrcR, class SrcI, arch_size_t SrcIAlign,
              class DstR, class DstI, arch_size_t DstIAlign,
              store_backend_t SrcStoreT, store_backend_t DstStoreT >
    struct ObjDataConverter< BeamMonitorData< SrcR, SrcI, SrcIAlign >,
        BeamMonitorData< DstR, DstI, DstIAlign >, SrcStoreT, DstStoreT >
    {
        typedef BeamMonitorData< SrcR, SrcI, SrcIAlign > src_t;
        typedef BeamMonitorData< DstR, DstI, DstIAlign > dest_t;

        static_assert( SIXTRL_CXX_NAMESPACE::ObjData_allow_conversion<
            src_t, dest_t, STORAGE_BE_COBJECTS, DstStoreT >(),
           "Conversion from BeamMonitorData< SrcR, SrcI, SrcIAlign > to "
           "BeamMonitorData< DstR, DstI, DstIAlign > not allowed" );

        static SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::arch_status_t
        convert( SIXTRL_ARGPTR_DEC dest_t* SIXTRL_RESTRICT dest,
                 SIXTRL_ARGPTR_DEC const src_t *const SIXTRL_RESTRICT src )
        {
            return SIXTRL_CXX_NAMESPACE::BeamMonitor_convert_generic(
                dest, src );
        }
    };
}

#endif /* defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_BEAM_MONITOR_CONVERT_COBJECTS_H__ */
