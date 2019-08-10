
    KernelConfigStore::kernel_config_id_t
    KernelConfigStore::initTrackUntilKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key )
    {
        return this->doInitPredefinedKernel( lock, input_key,
            st::KERNEL_CONFIG_PURPOSE_TRACK_UNTIL_TURN );

    }

    KernelConfigStore::kernel_config_id_t
    KernelConfigStore::initTrackElemByElemKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key )
    {
        return this->doInitPredefinedKernel( lock, input_key,
            st::KERNEL_CONFIG_PURPOSE_TRACK_ELEM_BY_ELEM );
    }

    KernelConfigStore::kernel_config_id_t KernelConfigStore::initTrackLineKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key )
    {
        return this->doInitPredefinedKernel( lock, input_key,
            st::KERNEL_CONFIG_PURPOSE_TRACK_LINE );
    }

    KernelConfigStore::kernel_config_id_t
    KernelConfigStore::initFetchParticlesAddrKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key )
    {
        return this->doInitPredefinedKernel( lock, input_key,
            st::KERNEL_CONFIG_PURPOSE_FETCH_PARTICLE_ADDRESSES );
    }

    KernelConfigStore::kernel_config_id_t
    KernelConfigStore::initAssignBeamMonitorOutputKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key )
    {
        return this->doInitPredefinedKernel( lock, input_key,
            st::KERNEL_CONFIG_PURPOSE_ASSIGN_BEAM_MONITOR_OUTPUT );
    }

    KernelConfigStore::kernel_config_id_t
    KernelConfigStore::initAssignElemByElemOutputKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key )
    {
        return this->doInitPredefinedKernel( lock, input_key,
            st::KERNEL_CONFIG_PURPOSE_ASSIGN_ELEM_BY_ELEM_OUTPUT );
    }

    /* --------------------------------------------------------------------- */

    KernelConfigStore::status_t
    KernelConfigStore::configureTrackUntilKernelConfig(
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        st::ArgumentBase& SIXTRL_RESTRICT_REF particles_arg,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureTrackUntilKernelConfig( lock, kernel_config_id,
            particles_arg.ptrCObjectsBuffer(), num_particle_sets, pset_begin );
    }

    KernelConfigStore::status_t
    KernelConfigStore::configureTrackUntilKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        st::ArgumentBase& SIXTRL_RESTRICT_REF particles_arg,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin )
    {
        return this->configureTrackUntilKernelConfig( lock, kernel_config_id,
            particles_arg.ptrCObjectsBuffer(), num_particle_sets, pset_begin );
    }

    KernelConfigStore::status_t
    KernelConfigStore::configureTrackUntilKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        KernelConfigStore::size_type const total_num_particles_in_sets )
    {
        using _this_t = st::KernelConfigStore;
        using status_t = _this_t::status_t;
        using ptr_config_t = _this_t::kernel_config_base_t*;

        status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( kernel_config_id != _this_t::ILLEGAL_KERNEL_CONFIG_ID ) &&
            ( total_num_particles_in_sets > _this_t::size_type{ 0 } ) &&
            ( this->checkLock( lock ) ) )
        {
            ptr_config_t conf = nullptr;

            status = this->doConfigureTrackKernelConfig(
                lock, kernel_config_id, nullptr, size_t{ 0 }, nullptr,
                    total_num_particles_in_sets );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                conf = this->ptrKernelConfigBase( lock, kernel_config_id );
            }

            if( conf != nullptr )
            {
                if( conf->needsUpdate() )
                {
                    status = conf->update();
                }
            }
            else
            {
                status = st::ARCH_STATUS_GENERAL_FAILURE;
            }

            SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                ( (  conf != nullptr ) && ( !conf->needsUpdate() ) ) );
        }

        return status;
    }

    KernelConfigStore::status_t
    KernelConfigStore::configureTrackUntilKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        const KernelConfigStore::c_buffer_t *const SIXTRL_RESTRICT_REF pbuffer,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin )
    {
        return this->configureTrackUntilKernelConfig( lock, kernel_config_id,
            ::NS(Particles_buffer_get_total_num_of_particles_on_particle_sets)(
                pbuffer, num_particle_sets, pset_begin ) );
    }

    /* --------------------------------------------------------------------- */

    KernelConfigStore::status_t
    KernelConfigStore::configureTrackElemByElemKernelConfig(
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        st::ArgumentBase& SIXTRL_RESTRICT_REF particles_arg,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin )
    {
        using _this_t = st::KernelConfigStore;
        _this_t::lock_t lock( *this->lockable() );
        return this->configureTrackElemByElemKernelConfig(
            lock, kernel_config_id, particles_arg.ptrCObjectsBuffer(),
                num_particle_sets, pset_begin );
    }

    KernelConfigStore::status_t
    KernelConfigStore::configureTrackElemByElemKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        KernelConfigStore::size_type const total_num_particles_in_sets )
    {
        using _this_t = st::KernelConfigStore;
        using status_t = _this_t::status_t;
        using ptr_config_t = _this_t::kernel_config_base_t*;

        status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( kernel_config_id != _this_t::ILLEGAL_KERNEL_CONFIG_ID ) &&
            ( total_num_particles_in_sets > _this_t::size_type{ 0 } ) &&
            ( this->checkLock( lock ) ) )
        {
            ptr_config_t conf = nullptr;

            status = this->doConfigureTrackKernelConfig(
                lock, kernel_config_id, nullptr, size_t{ 0 }, nullptr,
                    total_num_particles_in_sets );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                conf = this->ptrKernelConfigBase( lock, kernel_config_id );
            }

            if( conf != nullptr )
            {
                if( conf->needsUpdate() )
                {
                    status = conf->update();
                }
            }
            else
            {
                status = st::ARCH_STATUS_GENERAL_FAILURE;
            }

            SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                ( (  conf != nullptr ) && ( !conf->needsUpdate() ) ) );
        }

        return status;
    }

    KernelConfigStore::status_t
    KernelConfigStore::configureTrackElemByElemKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        st::ArgumentBase& SIXTRL_RESTRICT_REF particles_arg,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin )
    {
        return this->configureTrackElemByElemKernelConfig( lock,
            kernel_config_id, particles_arg.ptrCObjectsBuffer(),
                num_particle_sets, pset_begin );
    }

    KernelConfigStore::status_t
    KernelConfigStore::configureTrackElemByElemKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        const KernelConfigStore::c_buffer_t *const SIXTRL_RESTRICT_REF pbuffer,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin )
    {
        return this->configureTrackElemByElemKernelConfig( lock, kernel_config_id,
            ::NS(Particles_buffer_get_total_num_of_particles_on_particle_sets)(
                pbuffer, num_particle_sets, pset_begin ) );
    }

    /* --------------------------------------------------------------------- */

    KernelConfigStore::status_t
    KernelConfigStore::configureTrackLineKernelConfig(
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        st::ArgumentBase& SIXTRL_RESTRICT_REF particles_arg,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin )
    {
        using _this_t = st::KernelConfigStore;
        _this_t::lock_t lock( *this->lockable() );
        return this->configureTrackLineKernelConfig( lock, kernel_config_id,
            particles_arg.ptrCObjectsBuffer(), num_particle_sets, pset_begin );
    }

    KernelConfigStore::status_t
    KernelConfigStore::configureTrackLineKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        KernelConfigStore::size_type const total_num_particles_in_sets )
    {
        using _this_t = st::KernelConfigStore;
        using status_t = _this_t::status_t;
        using ptr_config_t = _this_t::kernel_config_base_t*;

        status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( kernel_config_id != _this_t::ILLEGAL_KERNEL_CONFIG_ID ) &&
            ( total_num_particles_in_sets > _this_t::size_type{ 0 } ) &&
            ( this->checkLock( lock ) ) )
        {
            ptr_config_t conf = nullptr;

            status = this->doConfigureTrackKernelConfig(
                lock, kernel_config_id, nullptr, size_t{ 0 }, nullptr,
                    total_num_particles_in_sets );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                conf = this->ptrKernelConfigBase( lock, kernel_config_id );
            }

            if( conf != nullptr )
            {
                if( conf->needsUpdate() )
                {
                    status = conf->update();
                }
            }
            else
            {
                status = st::ARCH_STATUS_GENERAL_FAILURE;
            }

            SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                ( (  conf != nullptr ) && ( !conf->needsUpdate() ) ) );
        }

        return status;
    }

    KernelConfigStore::status_t KernelConfigStore::configureTrackLineKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        st::ArgumentBase& SIXTRL_RESTRICT_REF particles_arg,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin )
    {
        return this->configureTrackLineKernelConfig( lock, kernel_config_id,
            particles_arg.ptrCObjectsBuffer(), num_particle_sets, pset_begin );
    }

    KernelConfigStore::status_t KernelConfigStore::configureTrackLineKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        const KernelConfigStore::c_buffer_t *const SIXTRL_RESTRICT_REF pbuffer,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin )
    {
        return this->configureTrackLineKernelConfig( lock, kernel_config_id,
            ::NS(Particles_buffer_get_total_num_of_particles_on_particle_sets)(
                pbuffer, num_particle_sets, pset_begin ) );
    }

    /* --------------------------------------------------------------------- */

    KernelConfigStore::status_t
    KernelConfigStore::configureFetchParticlesAddrKernelConfig(
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        st::ArgumentBase& SIXTRL_RESTRICT_REF particles_arg )
    {
        st::KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureFetchParticlesAddrKernelConfig( lock,
            kernel_config_id, particles_arg.ptrCObjectsBuffer() );
    }

    KernelConfigStore::status_t
    KernelConfigStore::configureFetchParticlesAddrKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        KernelConfigStore::size_type const num_objs_in_particle_buffer )
    {
        using _this_t = st::KernelConfigStore;
        using status_t = _this_t::status_t;
        using ptr_config_t = _this_t::kernel_config_base_t*;

        status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( kernel_config_id != _this_t::ILLEGAL_KERNEL_CONFIG_ID ) &&
            ( num_objs_in_particle_buffer > _this_t::size_type{ 0 } ) &&
            ( this->checkLock( lock ) ) )
        {
            ptr_config_t conf = nullptr;

            status = this->doConfigureFetchParticlesAddrKernelConfig(
                lock, kernel_config_id, num_objs_in_particle_buffer );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                conf = this->ptrKernelConfigBase( lock, kernel_config_id );
            }

            if( conf != nullptr )
            {
                if( conf->needsUpdate() )
                {
                    status = conf->update();
                }
            }
            else
            {
                status = st::ARCH_STATUS_GENERAL_FAILURE;
            }

            SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                ( (  conf != nullptr ) && ( !conf->needsUpdate() ) ) );
        }

        return status;
    }

    KernelConfigStore::status_t
    KernelConfigStore::configureFetchParticlesAddrKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        st::ArgumentBase& SIXTRL_RESTRICT_REF particles_arg )
    {
        return this->configureFetchParticlesAddrKernelConfig( lock,
            kernel_config_id, particles_arg.ptrCObjectsBuffer() );
    }

    KernelConfigStore::status_t
    KernelConfigStore::configureFetchParticlesAddrKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        const KernelConfigStore::c_buffer_t *const SIXTRL_RESTRICT_REF pbuffer )
    {
        return this->configureFetchParticlesAddrKernelConfig(
            lock, kernel_config_id, ::NS(Buffer_get_num_of_objects)( pbuffer ) );
    }

    /* --------------------------------------------------------------------- */

    KernelConfigStore::status_t
    KernelConfigStore::configureAssignOutputBeamMonitorKernelConfig(
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        st::ArgumentBase& SIXTRL_RESTRICT_REF beam_elements_arg )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureAssignOutputBeamMonitorKernelConfig( lock,
            kernel_config_id, beam_elements_arg.ptrCObjectsBuffer() );
    }

    KernelConfigStore::status_t
    KernelConfigStore::configureAssignOutputBeamMonitorKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        KernelConfigStore::size_type const num_beam_monitors )
    {
        using _this_t = st::KernelConfigStore;
        using status_t = _this_t::status_t;
        using ptr_config_t = _this_t::kernel_config_base_t*;

        status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( kernel_config_id != _this_t::ILLEGAL_KERNEL_CONFIG_ID ) &&
            ( num_beam_monitors > _this_t::size_type{ 0 } ) &&
            ( this->checkLock( lock ) ) )
        {
            ptr_config_t conf = nullptr;

            status = this->doConfigureAssignOutputBeamMonitorKernelConfig(
                lock, kernel_config_id, num_beam_monitors );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                conf = this->ptrKernelConfigBase( lock, kernel_config_id );
            }

            if( conf != nullptr )
            {
                if( conf->needsUpdate() )
                {
                    status = conf->update();
                }
            }
            else
            {
                status = st::ARCH_STATUS_GENERAL_FAILURE;
            }

            SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                ( (  conf != nullptr ) && ( !conf->needsUpdate() ) ) );
        }

        return status;
    }

    KernelConfigStore::status_t
    KernelConfigStore::configureAssignOutputBeamMonitorKernelConfig(
        lock_t const& SIXTRL_RESTRICT_REF lock,
        kernel_config_id_t const kernel_config_id,
        st::ArgumentBase& SIXTRL_RESTRICT_REF beam_elements_arg )
    {
        return this->configureAssignOutputBeamMonitorKernelConfig( lock,
            kernel_config_id, beam_elements_arg.ptrCObjectsBuffer() );
    }

    KernelConfigStore::status_t
    KernelConfigStore::configureAssignOutputBeamMonitorKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        const KernelConfigStore::c_buffer_t *const
            SIXTRL_RESTRICT_REF belems_buffer )
    {
        return this->configureAssignOutputBeamMonitorKernelConfig( lock,
            kernel_config_id, ::NS(BeamMonitor_get_num_of_beam_monitor_objects)(
                belems_buffer ) );
    }

    /* --------------------------------------------------------------------- */

    KernelConfigStore::status_t
    KernelConfigStore::configureAssignOutputElemByElemKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_id_t const kernel_config_id )
    {
        using _this_t = st::KernelConfigStore;
        using status_t = _this_t::status_t;
        using ptr_config_t = _this_t::kernel_config_base_t*;

        status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( kernel_config_id != _this_t::ILLEGAL_KERNEL_CONFIG_ID ) &&
            ( this->checkLock( lock ) ) )
        {
            ptr_config_t conf = nullptr;

            status = this->doConfigureAssignOutputElemByElemKernelConfig(
                lock, kernel_config_id );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                conf = this->ptrKernelConfigBase( lock, kernel_config_id );
            }

            if( conf != nullptr )
            {
                if( conf->needsUpdate() )
                {
                    status = conf->update();
                }
            }
            else
            {
                status = st::ARCH_STATUS_GENERAL_FAILURE;
            }

            SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                ( (  conf != nullptr ) && ( !conf->needsUpdate() ) ) );
        }

        return status;
    }

    /* -------------------------------------------------------------------- */

    /* --------------------------------------------------------------------- */

    KernelConfigStore::status_t
    KernelConfigStore::doConfigureRemapBufferKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_id_t const kernel_config_id )
    {
        ( void )lock;
        ( void )kernel_config_id;

        return st::ARCH_STATUS_GENERAL_FAILURE;
    }

    KernelConfigStore::status_t
    KernelConfigStore::doConfigureTrackKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        const KernelConfigStore::c_buffer_t *const SIXTRL_RESTRICT pbuffer,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin,
        size_type const total_num_particles_in_sets )
    {
        ( void )lock;
        ( void )kernel_config_id;
        ( void )pbuffer;
        ( void )num_particle_sets;
        ( void )pset_begin;
        ( void )total_num_particles_in_sets;

        return st::ARCH_STATUS_GENERAL_FAILURE;
    }

    KernelConfigStore::status_t
    KernelConfigStore::doConfigureFetchParticlesAddrKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        KernelConfigStore::size_type const num_objs_in_particle_buffer )
    {
        ( void )lock;
        ( void )kernel_config_id;
        ( void )num_objs_in_particle_buffer;

        return st::ARCH_STATUS_GENERAL_FAILURE;
    }

    KernelConfigStore::status_t
    KernelConfigStore::doConfigureAssignOutputBeamMonitorKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        KernelConfigStore::size_type const num_beam_monitors )
    {
        ( void )lock;
        ( void )kernel_config_id;
        ( void )num_beam_monitors;

        return st::ARCH_STATUS_GENERAL_FAILURE;
    }

    KernelConfigStore::status_t
    KernelConfigStore::doConfigureAssignOutputElemByElemKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_id_t const kernel_config_id )
    {
        ( void )lock;
        ( void )kernel_config_id;

        return st::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* ----------------------------------------------------------------- */

    KernelConfigStore::status_t
    KernelConfigStore::doGetParametersFromParticlesBufferAndBeamElements(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        const KernelConfigStore::c_buffer_t *const SIXTRL_RESTRICT pbuffer,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin,
        const KernelConfigStore::c_buffer_t *const SIXTRL_RESTRICT belems_buffer,
        KernelConfigStore::size_type const until_turn_elem_by_elem,
        KernelConfigStore::particle_index_t const at_elem_start_index,
        KernelConfigStore::out_buffer_flags_t* SIXTRL_RESTRICT ptr_out_flags,
        KernelConfigStore::size_type* SIXTRL_RESTRICT ptr_num_particles_in_sets,
        KernelConfigStore::size_type* SIXTRL_RESTRICT ptr_num_particle_sets,
        KernelConfigStore::size_type* SIXTRL_RESTRICT ptr_num_objs_in_buffer,
        KernelConfigStore::size_type* SIXTRL_RESTRICT ptr_num_elem_by_elem_objs,
        KernelConfigStore::size_type* SIXTRL_RESTRICT ptr_num_beam_monitors )
    {
        using _this_t = st::KernelConfigStore;
        using out_buffer_flags_t = _this_t::out_buffer_flags_t;
        using status_t           = _this_t::status_t;
        using pindex_t           = _this_t::particle_index_t;

        status_t ret = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( this->checkLock( lock ) ) &&
            ( pbuffer != nullptr ) && ( num_particle_sets > size_t{ 0 } ) &&
            ( pset_begin != nullptr ) && ( belems_buffer != nullptr ) )
        {
            size_t num_elem_by_elem_objects = size_t{ 0 };

            pindex_t min_particle_id, max_particle_id, min_at_element,
                     max_at_element, min_at_turn, max_at_turn;

            ret = ::NS(OutputBuffer_get_min_max_attributes_on_particle_sets)(
                pbuffer, num_particle_sets, pset_begin, belems_buffer,
                    &min_particle_id, &max_particle_id, &min_at_element,
                    &max_at_element, &min_at_turn, &max_at_turn,
                        &num_elem_by_elem_objects, at_elem_start_index );

            if( ret == st::ARCH_STATUS_SUCCESS )
            {
                if( ptr_num_elem_by_elem_objs != nullptr )
                {
                    *ptr_num_elem_by_elem_objs = num_elem_by_elem_objects;
                }

                if( ptr_num_particles_in_sets != nullptr )
                {
                    size_t total_num_particles = size_t{ 0 };
                    size_t const* pset_it  = pset_begin;
                    size_t const* pset_end = pset_begin;
                    std::advance( pset_end, num_particle_sets );

                    for( ; pset_it != pset_end ; ++pset_it )
                    {
                        total_num_particles += *pset_it;
                    }

                    *ptr_num_particles_in_sets = total_num_particles;
                }

                if( ( ptr_out_flags != nullptr ) ||
                    ( ptr_num_beam_monitors != nullptr ) )
                {
                    size_t num_beam_monitors = size_t{ 0 };

                    out_buffer_flags_t const out_flags =
                    ::NS(OutputBuffer_required_for_tracking_detailed)(
                        belems_buffer, min_particle_id, max_particle_id,
                        min_at_element, max_at_element, min_at_turn,
                        max_at_turn, until_turn_elem_by_elem,
                        &num_beam_monitors );

                    if( ptr_out_flags != nullptr )
                    {
                        *ptr_out_flags = out_flags;
                    }

                    if( ptr_num_beam_monitors != nullptr )
                    {
                        *ptr_num_beam_monitors = num_beam_monitors;
                    }
                }

                if( ptr_num_particle_sets != nullptr )
                {
                    *ptr_num_particle_sets =
                    ::NS(Particles_buffer_get_num_of_particle_blocks)( pbuffer );
                }

                if( ptr_num_objs_in_buffer != nullptr )
                {
                    *ptr_num_objs_in_buffer =
                        ::NS(Buffer_get_num_of_objects)( pbuffer );
                }
            }
        }

        return ret;
    }

    _store_t::status_t KernelConfigStore::initDefaultTrackJobKernels(
        _store_t::lock_t const& SIXTRL_RESTRICT_REF lock,
        _store_t::kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key )
    {
        using _this_t = st::KernelConfigStore;
        using kernel_config_id_t = _this_t::kernel_config_id_t;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( input_key.archId() != _this_t::ARCH_ILLEGAL ) &&
            ( this->checkLock( lock ) ) )
        {
            _this_t::kernel_config_key_t key( input_key );

            bool added_kernels = false;

            key.setPurpose( st::KERNEL_CONFIG_PURPOSE_TRACK_UNTIL_TURN );
            kernel_config_id_t track_until_kernel_id = this->kernelId( lock, key );

            if( track_until_kernel_id == _this_t::ILLEGAL_KERNEL_CONFIG_ID )
            {
                track_until_kernel_id =
                    this->initTrackUntilKernelConfig( lock, key );

                if( track_until_kernel_id != _this_t::ILLEGAL_KERNEL_CONFIG_ID )
                {
                    added_kernels = true;
                }
            }

            key.setPurpose( st::KERNEL_CONFIG_PURPOSE_TRACK_ELEM_BY_ELEM );
            kernel_config_id_t track_elem_by_elem_kernel_id = this->kernelId( lock, key );

            if( track_elem_by_elem_kernel_id == _this_t::ILLEGAL_KERNEL_CONFIG_ID )
            {
                track_elem_by_elem_kernel_id =
                    this->initTrackElemByElemKernelConfig( lock, key );

                if( track_elem_by_elem_kernel_id != _this_t::ILLEGAL_KERNEL_CONFIG_ID )
                {
                    added_kernels = true;
                }
            }

            key.setPurpose( st::KERNEL_CONFIG_PURPOSE_TRACK_LINE );
            kernel_config_id_t track_line_kernel_id = this->kernelId( lock, key );

            if( track_line_kernel_id == _this_t::ILLEGAL_KERNEL_CONFIG_ID )
            {
                track_line_kernel_id =
                    this->initTrackLineKernelConfig( lock, key );

                if( track_line_kernel_id != _this_t::ILLEGAL_KERNEL_CONFIG_ID )
                {
                    added_kernels = true;
                }
            }

            key.setPurpose( st::KERNEL_CONFIG_PURPOSE_FETCH_PARTICLE_ADDRESSES );
            kernel_config_id_t fetch_particles_kernel_id = this->kernelId( lock, key );

            if( fetch_particles_kernel_id == _this_t::ILLEGAL_KERNEL_CONFIG_ID )
            {
                fetch_particles_kernel_id =
                    this->initFetchParticlesAddrKernelConfig( lock, key );

                if( fetch_particles_kernel_id != _this_t::ILLEGAL_KERNEL_CONFIG_ID )
                {
                    added_kernels = true;
                }
            }

            key.setPurpose( st::KERNEL_CONFIG_PURPOSE_ASSIGN_BEAM_MONITOR_OUTPUT );
            kernel_config_id_t assign_be_mon_kernel_id = this->kernelId( lock, key );

            if( assign_be_mon_kernel_id == _this_t::ILLEGAL_KERNEL_CONFIG_ID )
            {
                assign_be_mon_kernel_id =
                    this->initAssignBeamMonitorOutputKernelConfig( lock, key );

                if( assign_be_mon_kernel_id != _this_t::ILLEGAL_KERNEL_CONFIG_ID )
                {
                    added_kernels = true;
                }
            }

            key.setPurpose( st::KERNEL_CONFIG_PURPOSE_ASSIGN_ELEM_BY_ELEM_OUTPUT );
            kernel_config_id_t assign_elem_kernel_id = this->kernelId( lock, key );

            if( assign_elem_kernel_id == _this_t::ILLEGAL_KERNEL_CONFIG_ID )
            {
                assign_elem_kernel_id =
                    this->initAssignElemByElemOutputKernelConfig( lock, key );

                if( assign_elem_kernel_id != _this_t::ILLEGAL_KERNEL_CONFIG_ID )
                {
                    added_kernels = true;
                }
            }

            if( ( track_until_kernel_id        != _this_t::ILLEGAL_KERNEL_CONFIG_ID ) &&
                ( track_elem_by_elem_kernel_id != _this_t::ILLEGAL_KERNEL_CONFIG_ID ) &&
                ( track_line_kernel_id         != _this_t::ILLEGAL_KERNEL_CONFIG_ID ) &&
                ( fetch_particles_kernel_id    != _this_t::ILLEGAL_KERNEL_CONFIG_ID ) &&
                ( assign_be_mon_kernel_id      != _this_t::ILLEGAL_KERNEL_CONFIG_ID ) &&
                ( assign_elem_kernel_id        != _this_t::ILLEGAL_KERNEL_CONFIG_ID ) )
            {
                status = st::ARCH_STATUS_SUCCESS;
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    KernelConfigStore::status_t
    KernelConfigStore::configureDefaultTrackJobKernels(
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key,
        st::ArgumentBase& SIXTRL_RESTRICT_REF particles_arg,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin,
        st::ArgumentBase& SIXTRL_RESTRICT_REF beam_elements_arg,
        KernelConfigStore::size_type const until_turn_elem_by_elem )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureDefaultTrackJobKernels( lock, input_key,
            particles_arg.ptrCObjectsBuffer(), num_particle_sets, pset_begin,
                beam_elements_arg.ptrCObjectsBuffer(),
                    until_turn_elem_by_elem );
    }

    KernelConfigStore::status_t
    KernelConfigStore::configureDefaultTrackJobKernels(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key,
        st::ArgumentBase& SIXTRL_RESTRICT_REF particles_arg,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin,
        st::ArgumentBase& SIXTRL_RESTRICT_REF beam_elements_arg,
        KernelConfigStore::size_type const until_turn_elem_by_elem )
    {
        return this->configureDefaultTrackJobKernels( lock, input_key,
            particles_arg.ptrCObjectsBuffer(), num_particle_sets, pset_begin,
                beam_elements_arg.ptrCObjectsBuffer(),
                    until_turn_elem_by_elem );
    }

    KernelConfigStore::status_t
    KernelConfigStore::configureDefaultTrackJobKernels(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key,
        const KernelConfigStore::c_buffer_t *const SIXTRL_RESTRICT pbuffer,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin,
        const KernelConfigStore::c_buffer_t *const SIXTRL_RESTRICT belems_buffer,
        KernelConfigStore::size_type const until_turn_elem_by_elem )
    {
        using _this_t = st::KernelConfigStore;
        using  size_t = _this_t::size_type;
        using  out_buffer_flags_t = _this_t::out_buffer_flags_t;
        using  pindex_t = _this_t::particle_index_t;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( input_key.archId() != _this_t::ARCH_ILLEGAL ) &&
            ( pbuffer != nullptr ) && ( num_particle_sets > size_t{ 0 } ) &&
            ( pset_begin != nullptr ) && ( belems_buffer != nullptr ) )
        {
            _this_t::kernel_config_key_t key( input_key );

            out_buffer_flags_t out_flags = ::NS(OUTPUT_BUFFER_NONE);
            size_t total_num_particles = size_t{ 0 };
            size_t num_objs_in_particle_buffer = size_t{ 0 };
            size_t num_beam_monitors = size_t{ 0 };

            status = this->doGetParametersFromParticlesBufferAndBeamElements(
                lock, pbuffer, num_particle_sets, pset_begin, belems_buffer,
                until_turn_elem_by_elem, pindex_t{ 0 }, &out_flags,
                &total_num_particles, nullptr, &num_objs_in_particle_buffer,
                nullptr, &num_beam_monitors );

            if( total_num_particles > size_t{ 0 } )
            {
                key.setPurpose( st::KERNEL_CONFIG_PURPOSE_TRACK_UNTIL_TURN );
                status = this->configureTrackUntilKernelConfig(
                    lock, this->kernelId( lock, key ), total_num_particles );

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    key.setPurpose( st::KERNEL_CONFIG_PURPOSE_TRACK_ELEM_BY_ELEM );
                    status = this->configureTrackElemByElemKernelConfig( lock,
                        this->kernelId( lock, key ), total_num_particles );
                }

                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    key.setPurpose( st::KERNEL_CONFIG_PURPOSE_TRACK_LINE );
                    status = this->configureTrackLineKernelConfig( lock,
                        this->kernelId( lock, key ), total_num_particles );
                }
            }

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( num_objs_in_particle_buffer > size_t{ 0 } ) )
            {
                key.setPurpose( st::KERNEL_CONFIG_PURPOSE_FETCH_PARTICLE_ADDRESSES );
                status = this->configureFetchParticlesAddrKernelConfig( lock,
                    this->kernelId( lock, key ), num_objs_in_particle_buffer );
            }

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( ::NS(OutputBuffer_requires_beam_monitor_output)( out_flags ) ) &&
                ( num_beam_monitors > size_t{ 0 } ) )
            {
                key.setPurpose( st::KERNEL_CONFIG_PURPOSE_ASSIGN_BEAM_MONITOR_OUTPUT );
                status = this->configureAssignOutputBeamMonitorKernelConfig(
                    lock, this->kernelId( lock, key ), num_beam_monitors );
            }

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( ::NS(OutputBuffer_requires_elem_by_elem_output)( out_flags ) ) )
            {
                key.setPurpose( st::KERNEL_CONFIG_PURPOSE_ASSIGN_ELEM_BY_ELEM_OUTPUT );
                status = this->configureAssignOutputElemByElemKernelConfig(
                    lock, this->kernelId( lock, key ) );
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    KernelConfigStore::kernel_config_id_t
    KernelConfigStore::initDefaultControllerKernels(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key )
    {
        using _this_t = st::KernelConfigStore;
        _this_t::kernel_config_id_t kernel_config_id = _this_t::ILLEGAL_KERNEL_CONFIG_ID;

        if( ( input_key.archId() != _this_t::ARCH_ILLEGAL ) &&
            ( this->checkLock( lock ) ) )
        {
            _this_t::kernel_config_key_t key( input_key );
            key.setPurpose( st::KERNEL_CONFIG_PURPOSE_REMAP_BUFFER );

            kernel_config_id = this->kernelId( key );

            if( kernel_config_id == _this_t::ILLEGAL_KERNEL_CONFIG_ID )
            {
                kernel_config_id = this->initKernelConfig( lock, key );
            }
        }

        return kernel_config_id;
    }

    KernelConfigStore::status_t
    KernelConfigStore::configureRemapBufferKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_id_t const kernel_config_id )
    {
        using _this_t = st::KernelConfigStore;
        using status_t = _this_t::status_t;
        using ptr_config_t = _this_t::kernel_config_base_t*;

        status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( kernel_config_id != _this_t::ILLEGAL_KERNEL_CONFIG_ID ) &&
            ( this->checkLock( lock ) ) )
        {
            ptr_config_t conf = nullptr;

            status = this->doConfigureRemapBufferKernelConfig(
                lock, kernel_config_id );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                conf = this->ptrKernelConfigBase( lock, kernel_config_id );
            }

            if( conf != nullptr )
            {
                if( conf->needsUpdate() )
                {
                    status = conf->update();
                }
            }
            else
            {
                status = st::ARCH_STATUS_GENERAL_FAILURE;
            }

            SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                ( (  conf != nullptr ) && ( !conf->needsUpdate() ) ) );
        }

        return status;
    }
