/* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t initDefaultTrackJobKernels(
            kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key );

        SIXTRL_HOST_FN status_t configureDefaultTrackJobKernels(
            kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key,
            ArgumentBase& SIXTRL_RESTRICT_REF particles_arg,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin,
            ArgumentBase& SIXTRL_RESTRICT_REF beam_elements_buffer,
            size_type const until_turn_elem_by_elem );

        SIXTRL_HOST_FN status_t configureDefaultTrackJobKernels(
            kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key,
            buffer_t const& SIXTRL_RESTRICT_REF particles_buffer,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin,
            buffer_t const& SIXTRL_RESTRICT_REF beam_elements_buffer,
            size_type const until_turn_elem_by_elem );

        SIXTRL_HOST_FN status_t configureDefaultTrackJobKernels(
            kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key,
            const c_buffer_t *const SIXTRL_RESTRICT particles_buffer,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin,
            const c_buffer_t *const SIXTRL_RESTRICT beam_elements_buffer,
            size_type const until_turn_elem_by_elem );

        /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

        SIXTRL_HOST_FN status_t initDefaultTrackJobKernels(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key );

        SIXTRL_HOST_FN status_t configureDefaultTrackJobKernels(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key,
            ArgumentBase& SIXTRL_RESTRICT_REF particles_arg,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin,
            ArgumentBase& SIXTRL_RESTRICT_REF beam_elements_buffer,
            size_type const until_turn_elem_by_elem );

        SIXTRL_HOST_FN status_t configureDefaultTrackJobKernels(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key,
            buffer_t const& SIXTRL_RESTRICT_REF particles_buffer,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin,
            buffer_t const& SIXTRL_RESTRICT_REF beam_elements_buffer,
            size_type const until_turn_elem_by_elem );

        SIXTRL_HOST_FN status_t configureDefaultTrackJobKernels(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key,
            const c_buffer_t *const SIXTRL_RESTRICT particles_buffer,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin,
            const c_buffer_t *const SIXTRL_RESTRICT beam_elements_buffer,
            size_type const until_turn_elem_by_elem );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN kernel_config_id_t initTrackUntilKernelConfig(
            kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key );

        SIXTRL_HOST_FN kernel_config_id_t initTrackElemByElemKernelConfig(
            kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key );

        SIXTRL_HOST_FN kernel_config_id_t initTrackLineKernelConfig(
            kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key );

        SIXTRL_HOST_FN kernel_config_id_t initFetchParticlesAddrKernelConfig(
            kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key );

        SIXTRL_HOST_FN kernel_config_id_t
        initAssignBeamMonitorOutputKernelConfig(
            kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key );

        SIXTRL_HOST_FN kernel_config_id_t
        initAssignElemByElemOutputKernelConfig(
            kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key );

        /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

        SIXTRL_HOST_FN kernel_config_id_t initTrackUntilKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key );

        SIXTRL_HOST_FN kernel_config_id_t initTrackElemByElemKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key );

        SIXTRL_HOST_FN kernel_config_id_t initTrackLineKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key );

        SIXTRL_HOST_FN kernel_config_id_t initFetchParticlesAddrKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key );

        SIXTRL_HOST_FN kernel_config_id_t
        initAssignBeamMonitorOutputKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key );

        SIXTRL_HOST_FN kernel_config_id_t
        initAssignElemByElemOutputKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t configureTrackUntilKernelConfig(
            kernel_config_id_t const kernel_config_id,
            size_type const total_num_particles_in_sets );

        SIXTRL_HOST_FN status_t configureTrackUntilKernelConfig(
            kernel_config_id_t const kernel_config_id,
            ArgumentBase& SIXTRL_RESTRICT_REF particles_arg,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin );

        SIXTRL_HOST_FN status_t configureTrackUntilKernelConfig(
            kernel_config_id_t const kernel_config_id,
            buffer_t const& SIXTRL_RESTRICT_REF particles_buffer,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin );

        SIXTRL_HOST_FN status_t configureTrackUntilKernelConfig(
            kernel_config_id_t const kernel_config_id,
            const c_buffer_t *const SIXTRL_RESTRICT particles_buffer,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin );

        /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

        SIXTRL_HOST_FN status_t configureTrackUntilKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_id_t const kernel_config_id,
            size_type const total_num_particles_in_sets );

        SIXTRL_HOST_FN status_t configureTrackUntilKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_id_t const kernel_config_id,
            ArgumentBase& SIXTRL_RESTRICT_REF particles_arg,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin );

        SIXTRL_HOST_FN status_t configureTrackUntilKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_id_t const kernel_config_id,
            buffer_t const& SIXTRL_RESTRICT_REF particles_buffer,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin );

        SIXTRL_HOST_FN status_t configureTrackUntilKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_id_t const kernel_config_id,
            c_buffer_t const* SIXTRL_RESTRICT_REF particles_buffer,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t configureTrackElemByElemKernelConfig(
            kernel_config_id_t const kernel_config_id,
            size_type const total_num_particles_in_sets );

        SIXTRL_HOST_FN status_t configureTrackElemByElemKernelConfig(
            kernel_config_id_t const kernel_config_id,
            ArgumentBase& SIXTRL_RESTRICT_REF particles_arg,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin );

        SIXTRL_HOST_FN status_t configureTrackElemByElemKernelConfig(
            kernel_config_id_t const kernel_config_id,
            buffer_t const& SIXTRL_RESTRICT_REF particles_buffer,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin );

        SIXTRL_HOST_FN status_t configureTrackElemByElemKernelConfig(
            kernel_config_id_t const kernel_config_id,
            const c_buffer_t *const SIXTRL_RESTRICT particles_buffer,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin );

        /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

        SIXTRL_HOST_FN status_t configureTrackElemByElemKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_id_t const kernel_config_id,
            size_type const total_num_particles_in_sets );

        SIXTRL_HOST_FN status_t configureTrackElemByElemKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_id_t const kernel_config_id,
            ArgumentBase& SIXTRL_RESTRICT_REF particles_arg,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin );

        SIXTRL_HOST_FN status_t configureTrackElemByElemKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_id_t const kernel_config_id,
            buffer_t const& SIXTRL_RESTRICT_REF particles_buffer,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin );

        SIXTRL_HOST_FN status_t configureTrackElemByElemKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_id_t const kernel_config_id,
            const c_buffer_t *const SIXTRL_RESTRICT particles_buffer,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t configureTrackLineKernelConfig(
            kernel_config_id_t const kernel_config_id,
            size_type const total_num_particles_in_sets );

        SIXTRL_HOST_FN status_t configureTrackLineKernelConfig(
            kernel_config_id_t const kernel_config_id,
            ArgumentBase& SIXTRL_RESTRICT_REF particles_arg,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin );

        SIXTRL_HOST_FN status_t configureTrackLineKernelConfig(
            kernel_config_id_t const kernel_config_id,
            buffer_t const& SIXTRL_RESTRICT_REF particles_buffer,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin );

        SIXTRL_HOST_FN status_t configureTrackLineKernelConfig(
            kernel_config_id_t const kernel_config_id,
            const c_buffer_t *const SIXTRL_RESTRICT particles_buffer,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin );

        /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

        SIXTRL_HOST_FN status_t configureTrackLineKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_id_t const kernel_config_id,
            size_type const total_num_particles_in_sets );

        SIXTRL_HOST_FN status_t configureTrackLineKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_id_t const kernel_config_id,
            ArgumentBase& SIXTRL_RESTRICT_REF particles_arg,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin );

        SIXTRL_HOST_FN status_t configureTrackLineKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_id_t const kernel_config_id,
            buffer_t const& SIXTRL_RESTRICT_REF particles_buffer,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin );

        SIXTRL_HOST_FN status_t configureTrackLineKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_id_t const kernel_config_id,
            const c_buffer_t *const SIXTRL_RESTRICT particles_buffer,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t configureFetchParticlesAddrKernelConfig(
            kernel_config_id_t const kernel_config_id,
            size_type const num_objs_in_particle_buffer );

        SIXTRL_HOST_FN status_t configureFetchParticlesAddrKernelConfig(
            kernel_config_id_t const kernel_config_id,
            ArgumentBase& SIXTRL_RESTRICT_REF particles_arg );

        SIXTRL_HOST_FN status_t configureFetchParticlesAddrKernelConfig(
            kernel_config_id_t const kernel_config_id,
            buffer_t const& SIXTRL_RESTRICT_REF particles_buffer );

        SIXTRL_HOST_FN status_t configureFetchParticlesAddrKernelConfig(
            kernel_config_id_t const kernel_config_id,
            const c_buffer_t *const SIXTRL_RESTRICT particles_buffer );

        /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

        SIXTRL_HOST_FN status_t configureFetchParticlesAddrKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_id_t const kernel_config_id,
            size_type const num_objs_in_particle_buffer );

        SIXTRL_HOST_FN status_t configureFetchParticlesAddrKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_id_t const kernel_config_id,
            ArgumentBase& SIXTRL_RESTRICT_REF particles_arg );

        SIXTRL_HOST_FN status_t configureFetchParticlesAddrKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_id_t const kernel_config_id,
            buffer_t const& SIXTRL_RESTRICT_REF particles_buffer );

        SIXTRL_HOST_FN status_t configureFetchParticlesAddrKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_id_t const kernel_config_id,
            const c_buffer_t *const SIXTRL_RESTRICT particles_buffer );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t configureAssignOutputBeamMonitorKernelConfig(
            kernel_config_id_t const kernel_config_id,
            size_type const num_beam_monitors );

        SIXTRL_HOST_FN status_t configureAssignOutputBeamMonitorKernelConfig(
            kernel_config_id_t const kernel_config_id,
            ArgumentBase& SIXTRL_RESTRICT_REF beam_elements_arg );

        SIXTRL_HOST_FN status_t configureAssignOutputBeamMonitorKernelConfig(
            kernel_config_id_t const kernel_config_id,
            buffer_t const& SIXTRL_RESTRICT_REF beam_elements_arg );

        SIXTRL_HOST_FN status_t configureAssignOutputBeamMonitorKernelConfig(
            kernel_config_id_t const kernel_config_id,
            const c_buffer_t *const SIXTRL_RESTRICT beam_elements_arg );

        /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

        SIXTRL_HOST_FN status_t configureAssignOutputBeamMonitorKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_id_t const kernel_config_id,
            size_type const num_beam_monitors );

        SIXTRL_HOST_FN status_t configureAssignOutputBeamMonitorKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_id_t const kernel_config_id,
            ArgumentBase& SIXTRL_RESTRICT_REF particles_arg );

        SIXTRL_HOST_FN status_t configureAssignOutputBeamMonitorKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_id_t const kernel_config_id,
            buffer_t const& SIXTRL_RESTRICT_REF particles_buffer );

        SIXTRL_HOST_FN status_t configureAssignOutputBeamMonitorKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_id_t const kernel_config_id,
            const c_buffer_t *const SIXTRL_RESTRICT particles_buffer );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t configureAssignOutputElemByElemKernelConfig(
            kernel_config_id_t const kernel_config_id );

        /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

        SIXTRL_HOST_FN status_t configureAssignOutputElemByElemKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_id_t const kernel_config_id );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN virtual status_t doConfigureTrackKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_id_t const kernel_config_id,
            c_buffer_t const* SIXTRL_RESTRICT particles_buffer,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin,
            size_type const total_num_particles_in_sets );

        SIXTRL_HOST_FN virtual status_t
        doConfigureFetchParticlesAddrKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_id_t const kernel_config_id,
            size_type const num_objs_in_particle_buffer );

        SIXTRL_HOST_FN virtual status_t
        doConfigureAssignOutputBeamMonitorKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_id_t const kernel_config_id,
            size_type const num_beam_monitors );

        SIXTRL_HOST_FN virtual status_t
        doConfigureAssignOutputElemByElemKernelConfig(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            kernel_config_id_t const kernel_config_id );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t
        doGetParametersFromParticlesBufferAndBeamElements(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            const c_buffer_t *const SIXTRL_RESTRICT pbuffer,
            size_type const num_particle_sets,
            size_type const* SIXTRL_RESTRICT pset_begin,
            const c_buffer_t *const SIXTRL_RESTRICT beam_elements_buffer,
            size_type const until_turn_elem_by_elem,
            particle_index_t const at_elem_start_index,
            out_buffer_flags_t* ptr_output_buffer_flags,
            size_type* SIXTRL_RESTRICT ptr_total_num_particles_in_sets,
            size_type* SIXTRL_RESTRICT ptr_total_num_particle_sets,
            size_type* SIXTRL_RESTRICT ptr_num_objs_in_buffer,
            size_type* SIXTRL_RESTRICT ptr_num_elem_by_elem_objs,
            size_type* SIXTRL_RESTRICT ptr_num_beam_monitors );

        /* ----------------------------------------------------------------- */

         /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelConfigStore::kernel_config_id_t
    KernelConfigStore::initDefaultControllerKernels(
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->initDefaultControllerKernels( lock, input_key );
    }

    KernelConfigStore::status_t
    KernelConfigStore::configureRemapBufferKernelConfig(
        KernelConfigStore::kernel_config_id_t const kernel_config_id )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureRemapBufferKernelConfig( lock, kernel_config_id );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureDefaultTrackJobKernels(
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key,
        KernelConfigStore::buffer_t const& SIXTRL_RESTRICT_REF pbuffer,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin,
        KernelConfigStore::buffer_t const& SIXTRL_RESTRICT_REF belems_buffer,
        KernelConfigStore::size_type const until_turn_elem_by_elem )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureDefaultTrackJobKernels( lock, input_key,
            pbuffer.getCApiPtr(), num_particle_sets, pset_begin,
            belems_buffer.getCApiPtr(), until_turn_elem_by_elem );
    }

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureDefaultTrackJobKernels(
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key,
        const KernelConfigStore::c_buffer_t *const SIXTRL_RESTRICT pbuffer,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin,
        const KernelConfigStore::c_buffer_t *const SIXTRL_RESTRICT belems_buffer,
        KernelConfigStore::size_type const until_turn_elem_by_elem )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureDefaultTrackJobKernels( lock, input_key, pbuffer,
            num_particle_sets, pset_begin, belems_buffer,
                until_turn_elem_by_elem );
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureDefaultTrackJobKernels(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key,
        KernelConfigStore::buffer_t const& SIXTRL_RESTRICT_REF pbuffer,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin,
        KernelConfigStore::buffer_t const& SIXTRL_RESTRICT_REF belems_buffer,
        KernelConfigStore::size_type const until_turn_elem_by_elem )
    {
        return this->configureDefaultTrackJobKernels( lock, input_key,
            pbuffer.getCApiPtr(), num_particle_sets, pset_begin,
                belems_buffer.getCApiPtr(), until_turn_elem_by_elem );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelConfigStore::kernel_config_id_t
    KernelConfigStore::initTrackUntilKernelConfig(
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->initTrackUntilKernelConfig( lock, input_key );
    }

    SIXTRL_INLINE KernelConfigStore::kernel_config_id_t
    KernelConfigStore::initTrackElemByElemKernelConfig(
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->initTrackElemByElemKernelConfig( lock, input_key );
    }

    SIXTRL_INLINE KernelConfigStore::kernel_config_id_t
    KernelConfigStore::initTrackLineKernelConfig(
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->initTrackLineKernelConfig( lock, input_key );
    }

    SIXTRL_INLINE KernelConfigStore::kernel_config_id_t
    KernelConfigStore::initFetchParticlesAddrKernelConfig(
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->initFetchParticlesAddrKernelConfig( lock, input_key );
    }

    SIXTRL_INLINE KernelConfigStore::kernel_config_id_t
    KernelConfigStore::initAssignBeamMonitorOutputKernelConfig(
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->initAssignBeamMonitorOutputKernelConfig( lock, input_key );
    }

    SIXTRL_INLINE KernelConfigStore::kernel_config_id_t
    KernelConfigStore::initAssignElemByElemOutputKernelConfig(
        KernelConfigStore::kernel_config_key_t const& SIXTRL_RESTRICT_REF input_key )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->initAssignElemByElemOutputKernelConfig( lock, input_key );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureTrackUntilKernelConfig(
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        KernelConfigStore::size_type const total_num_particles_in_sets )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureTrackUntilKernelConfig(
            lock, kernel_config_id, total_num_particles_in_sets );
    }

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureTrackUntilKernelConfig(
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        KernelConfigStore::buffer_t const& SIXTRL_RESTRICT_REF pbuffer,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureTrackUntilKernelConfig( lock, kernel_config_id,
            pbuffer.getCApiPtr(), num_particle_sets, pset_begin );
    }

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureTrackUntilKernelConfig(
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        const KernelConfigStore::c_buffer_t *const SIXTRL_RESTRICT_REF pbuffer,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureTrackUntilKernelConfig( lock, kernel_config_id,
            pbuffer, num_particle_sets, pset_begin );
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureTrackUntilKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        KernelConfigStore::buffer_t const& SIXTRL_RESTRICT_REF pbuffer,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin )
    {
        return this->configureTrackUntilKernelConfig( lock, kernel_config_id,
            pbuffer.getCApiPtr(), num_particle_sets, pset_begin );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureTrackElemByElemKernelConfig(
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        KernelConfigStore::size_type const total_num_particles_in_sets )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureTrackElemByElemKernelConfig(
            lock, kernel_config_id, total_num_particles_in_sets );
    }

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureTrackElemByElemKernelConfig(
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        KernelConfigStore::buffer_t const& SIXTRL_RESTRICT_REF pbuffer,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureTrackElemByElemKernelConfig( lock,
            kernel_config_id, pbuffer.getCApiPtr(),
                num_particle_sets, pset_begin );
    }

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureTrackElemByElemKernelConfig(
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        const KernelConfigStore::c_buffer_t *const SIXTRL_RESTRICT_REF pbuffer,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureTrackElemByElemKernelConfig( lock,
            kernel_config_id, pbuffer, num_particle_sets, pset_begin );
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureTrackElemByElemKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        KernelConfigStore::buffer_t const& SIXTRL_RESTRICT_REF pbuffer,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin )
    {
        return this->configureTrackElemByElemKernelConfig( lock,
            kernel_config_id, pbuffer.getCApiPtr(),
                num_particle_sets, pset_begin );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureTrackLineKernelConfig(
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        KernelConfigStore::size_type const total_num_particles_in_sets )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureTrackLineKernelConfig(
            lock, kernel_config_id, total_num_particles_in_sets );
    }

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureTrackLineKernelConfig(
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        KernelConfigStore::buffer_t const& SIXTRL_RESTRICT_REF pbuffer,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureTrackLineKernelConfig( lock, kernel_config_id,
            pbuffer.getCApiPtr(), num_particle_sets, pset_begin );
    }

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureTrackLineKernelConfig(
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        const KernelConfigStore::c_buffer_t *const SIXTRL_RESTRICT pbuffer,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureTrackLineKernelConfig( lock, kernel_config_id,
            pbuffer, num_particle_sets, pset_begin );
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureTrackLineKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        KernelConfigStore::buffer_t const& SIXTRL_RESTRICT_REF pbuffer,
        KernelConfigStore::size_type const num_particle_sets,
        KernelConfigStore::size_type const* SIXTRL_RESTRICT pset_begin )
    {
        return this->configureTrackLineKernelConfig( lock, kernel_config_id,
            pbuffer.getCApiPtr(), num_particle_sets, pset_begin );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureFetchParticlesAddrKernelConfig(
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        KernelConfigStore::size_type const num_objs_in_particle_buffer )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureFetchParticlesAddrKernelConfig(
            lock, kernel_config_id, num_objs_in_particle_buffer );
    }

    SIXTRL_INLINE  KernelConfigStore::status_t
    KernelConfigStore::configureFetchParticlesAddrKernelConfig(
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        KernelConfigStore::buffer_t const& SIXTRL_RESTRICT_REF pbuffer )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureFetchParticlesAddrKernelConfig(
            lock, kernel_config_id, pbuffer.getCApiPtr() );
    }

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureFetchParticlesAddrKernelConfig(
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        const KernelConfigStore::c_buffer_t *const SIXTRL_RESTRICT_REF pbuffer )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureFetchParticlesAddrKernelConfig(
            lock, kernel_config_id, pbuffer );
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureFetchParticlesAddrKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        KernelConfigStore::buffer_t const& SIXTRL_RESTRICT_REF pbuffer )
    {
        return this->configureFetchParticlesAddrKernelConfig( lock,
            kernel_config_id, pbuffer.getCApiPtr() );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureAssignOutputBeamMonitorKernelConfig(
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        KernelConfigStore::size_type const num_beam_monitors )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureAssignOutputBeamMonitorKernelConfig(
            lock, kernel_config_id, num_beam_monitors );
    }

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureAssignOutputBeamMonitorKernelConfig(
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        KernelConfigStore::buffer_t const& SIXTRL_RESTRICT_REF beam_elements )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureAssignOutputBeamMonitorKernelConfig(
            lock, kernel_config_id, beam_elements.getCApiPtr() );
    }

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureAssignOutputBeamMonitorKernelConfig(
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        const KernelConfigStore::c_buffer_t *const
            SIXTRL_RESTRICT_REF beam_elements )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureAssignOutputBeamMonitorKernelConfig(
            lock, kernel_config_id, beam_elements );
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureAssignOutputBeamMonitorKernelConfig(
        KernelConfigStore::lock_t const& SIXTRL_RESTRICT_REF lock,
        KernelConfigStore::kernel_config_id_t const kernel_config_id,
        KernelConfigStore::buffer_t const& SIXTRL_RESTRICT_REF pbuffer )
    {
        return this->configureAssignOutputBeamMonitorKernelConfig(
            lock, kernel_config_id, pbuffer.getCApiPtr() );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE KernelConfigStore::status_t
    KernelConfigStore::configureAssignOutputElemByElemKernelConfig(
        KernelConfigStore::kernel_config_id_t const kernel_config_id )
    {
        KernelConfigStore::lock_t lock( *this->lockable() );
        return this->configureAssignOutputElemByElemKernelConfig( lock,
            kernel_config_id );
    }
