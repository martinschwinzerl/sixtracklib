#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_BEAM_MONITOR_CXX_HPP__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_BEAM_MONITOR_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/beam_elements/beam_monitor/definitions.h"
    #include "sixtracklib/common/beam_elements/beam_monitor/beam_monitor.h"
    #include "sixtracklib/common/beam_elements/beam_monitor/beam_monitor_api.h"
    #include "sixtracklib/common/beam_elements/beam_monitor/beam_monitor_data.hpp"
    #include "sixtracklib/common/beam_elements/beam_monitor/beam_monitor_data_api.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/internal/obj_base_class.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template< class ObjData, SIXTRL_CXX_NAMESPACE::store_backend_t StoreT >
    class TBeamMonitorImpl : public ObjDataStorageInterfaceBase< ObjData,
        StoreT, SIXTRL_CXX_NAMESPACE::TBeamMonitorImpl< ObjData, StoreT > >
    {
        public:

        typedef typename BeamMonitorTraits< ObjData >::particle_set_t
                particle_set_t;

        typedef typename BeamMonitorTraits< ObjData >::particle_real_t
                particle_real_t;

        typedef typename BeamMonitorTraits< ObjData >::particle_index_t
                particle_index_t;

        typedef typename TypeMethodParamTraits< particle_set_t >::const_pointer
                particle_set_const_pointer_t;

        typedef typename TypeMethodParamTraits< particle_set_t >::pointer
                particle_set_pointer_t;

        typedef SIXTRL_CXX_NAMESPACE::arch_status_t status_t;
        typedef SIXTRL_CXX_NAMESPACE::be_monitor_flag_t monitor_flag_t;

        template< typename... Args >
        SIXTRL_FN void init( Args&&... args )
        {
            SIXTRL_CXX_NAMESPACE::BeamMonitor_init(
                this->as_ptr_data(), std::forward< Args >( args )... );
        }

        SIXTRL_FN SIXTRL_PARTICLE_SET_ARGPTR_DEC particle_set_const_pointer_t
        particle_set() const SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::BeamMonitor_const_particle_set(
                this->as_ptr_data() );
        }

        SIXTRL_FN SIXTRL_PARTICLE_SET_ARGPTR_DEC particle_set_pointer_t
        const_particle_set() SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::BeamMonitor_const_particle_set(
                this->as_ptr_data() );
        }

        SIXTRL_FN SIXTRL_PARTICLE_SET_ARGPTR_DEC particle_set_const_pointer_t
        particle_set() SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::BeamMonitor_particle_set(
                this->as_ptr_data() );
        }

        template< typename NumStoresArg >
        SIXTRL_FN status_t set_num_stores(
            NumStoresArg num_stores ) const SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::BeamMonitor_set_num_stores(
                this->as_ptr_data(), num_stores );
        }

        template< typename StartTurnArg >
        SIXTRL_FN status_t set_start_turn(
            StartTurnArg start_turn ) const SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::BeamMonitor_set_start_turn(
                this->as_ptr_data(), start_turn );
        }

        template< typename SkipTurnsArg >
        SIXTRL_FN status_t set_skip_turns(
            SkipTurnsArg skip_turns ) const SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::BeamMonitor_set_skip_turns(
                this->as_ptr_data(), skip_turns );
        }

        template< typename OutAddressArg >
        SIXTRL_FN status_t set_out_address(
            OutAddressArg out_address ) const SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::BeamMonitor_set_out_address(
                this->as_ptr_data(), out_address );
        }

        template< typename ParticleIdArg >
        SIXTRL_FN status_t set_min_particle_id(
            ParticleIdArg min_particle_id ) const SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::BeamMonitor_set_min_particle_id(
                this->as_ptr_data(), min_particle_id );
        }

        template< typename ParticleIdArg >
        SIXTRL_FN status_t set_max_particle_id(
            ParticleIdArg max_particle_id ) const SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::BeamMonitor_set_max_particle_id(
                this->as_ptr_data(), max_particle_id );
        }

        SIXTRL_FN status_t set_is_rolling_flag(
            monitor_flag_t const is_rolling_flag ) const SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::BeamMonitor_set_is_rolling_flag(
                this->as_ptr_data(), is_rolling_flag );
        }

        SIXTRL_FN status_t set_is_turn_ordered_flag(
            monitor_flag_t const is_turn_ordered_flag ) const SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::BeamMonitor_set_is_turn_ordered_flag(
                this->as_ptr_data(), is_turn_ordered_flag );
        }

        SIXTRL_FN status_t set_is_rolling_flag(
            monitor_flag_t const is_rolling_flag ) const SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::BeamMonitor_set_is_rolling_flag(
                this->as_ptr_data(), is_rolling_flag );
        }

        SIXTRL_FN status_t set_is_turn_ordered_flag(
            monitor_flag_t const is_turn_ordered_flag ) const SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::BeamMonitor_set_is_turn_ordered_flag(
                this->as_ptr_data(), is_turn_ordered_flag );
        }
    };
}

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/obj_base_class.hpp"
    #include "sixtracklib/common/beam_elements/beam_monitor/beam_monitor_cobjects_api.h"
    #include "sixtracklib/common/beam_elements/beam_monitor/beam_monitor_data_cobjects_api.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template< class R, class I, arch_size_t IAlign =
        SIXTRL_CXX_NAMESPACE::Type_storage_align< I >() >
    using TBeamMonitor = TBeamMonitorImpl< BeamMonitorData< R, I, IAlign >,
        STORAGE_BE_COBJECTS >;

    typedef TBeamMonitorImpl< CBeamMonitorEquivData, STORAGE_BE_COBJECTS > BeamMonitor;
    typedef TBeamMonitorImpl< ::NS(BeamMonitor),     STORAGE_BE_COBJECTS > CBeamMonitor;
}

#endif /* __cplusplus */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_BEAM_MONITOR_CXX_HPP__ */
