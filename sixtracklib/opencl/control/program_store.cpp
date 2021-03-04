#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/opencl/control/program_store.h"
    #include "sixtracklib/opencl/control/program_item.h"
#endif /* !defined( SIXTRL_NO_INCLUDES )  */

#if !defined( _GPUCODE ) && defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using store_type             = st::OclProgramStore;
        using base_store_type        = st::ProgramStoreBase;
        using st_status_t            = store_type::status_type;
        using st_guard_t             = store_type::guard_type;
        using st_key_t               = store_type::key_type;
        using st_prog_id_t           = store_type::program_id_type;
        using base_prg_item_type     = store_type::item_base_type;
        using ocl_base_prg_item_type = store_type::ocl_program_item_type;
        using ocl_rtc_prg_item_type  = st::OclRtcProgramItem;
    }

    constexpr store_type::class_id_type store_type::CLASS_ID;

    constexpr store_type::backend_id_type
    st::BackendObjTraits< store_type >::BACKEND_ID;

    constexpr store_type::class_id_type
    st::BackendObjTraits< store_type >::BASE_CLASS_ID;

    constexpr store_type::class_id_type
    st::BackendObjTraits< store_type >::DERIVED_CLASS_ID;

    /* --------------------------------------------------------------------- */

    store_type::~OclProgramStore()
    {
        auto const lock = this->create_lock();
        this->m_key_to_id_map.clear();
    }

    st_prog_id_t store_type::program_id(
        st_key_t const& SIXTRL_RESTRICT_REF key,
        st_guard_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        st_prog_id_t found_prog_id = store_type::ILLEGAL_PROGRAM_ID;

        if( ( this->is_locked( lock ) ) && ( key.is_legal() ) )
        {
            auto it = this->m_key_to_id_map.find( key );

            if( it != this->m_key_to_id_map.end() )
            {
                SIXTRL_ASSERT( this->_items_vector_size( lock ) <=
                               this->m_key_to_id_map.size() );

                if( static_cast< size_type >( it->second ) <
                    this->_items_vector_size( lock ) )
                {
                    found_prog_id = it->second;
                }
            }
        }

        return found_prog_id;
    }

    bool store_type::is_stored( st_key_t const& key,
        st_guard_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT {
        SIXTRL_ASSERT( this->_items_vector_size( lock ) <=
                       this->m_key_to_id_map.size() );
        SIXTRL_ASSERT( this->num_stored_items( lock ) <=
                       this->m_key_to_id_map.size() );

        bool is_stored = false;
        st_prog_id_t const prog_id = this->program_id( key, lock );

        if( prog_id != base_store_type::ILLEGAL_PROGRAM_ID )
        {
            SIXTRL_ASSERT( this->is_locked( lock ) );
            SIXTRL_ASSERT( key.is_legal() );

            is_stored = ( base_store_type::program_item(
                prog_id, lock ) != nullptr );
        }

        return is_stored;
    }

    std::unique_ptr< base_prg_item_type > store_type::remove(
        st_key_t const& SIXTRL_RESTRICT_REF key,
        st_guard_t const& SIXTRL_RESTRICT_REF lock ) {
        if( ( this->is_locked( lock ) ) && ( key.is_legal() ) &&
            ( this->is_stored( key, lock ) ) )
        {
            auto it = this->m_key_to_id_map.find( key );
            st_prog_id_t const stored_prog_id = this->program_id( key, lock );

            SIXTRL_ASSERT( stored_prog_id != store_type::ILLEGAL_PROGRAM_ID );
            SIXTRL_ASSERT( it != this->m_key_to_id_map.end() );

            this->m_key_to_id_map.erase( it );
            return this->remove( stored_prog_id, lock );
        }

        return std::unique_ptr< base_prg_item_type >( nullptr );
    }

    st_prog_id_t store_type::store( st_key_t const& key,
        std::unique_ptr< ocl_base_prg_item_type >&& prg_item_to_store,
        st_guard_t const& SIXTRL_RESTRICT_REF lock )
    {
        st_prog_id_t stored_prog_id = base_store_type::ILLEGAL_PROGRAM_ID;

        if( ( this->is_locked( lock ) ) && ( key.is_legal() ) )
        {
            stored_prog_id = this->program_id( key, lock );

            if( ( stored_prog_id != base_store_type::ILLEGAL_PROGRAM_ID ) &&
                ( prg_item_to_store.get() == nullptr ) &&
                ( this->program_item( stored_prog_id, lock ) != nullptr ) )
            {
                auto it = this->m_key_to_id_map.find( key );
                SIXTRL_ASSERT( it != this->m_key_to_id_map.end() );
                SIXTRL_ASSERT( it->second == stored_prog_id );
                this->remove( stored_prog_id );
                stored_prog_id = base_store_type::ILLEGAL_PROGRAM_ID;
            }
            else if( ( stored_prog_id == base_store_type::ILLEGAL_PROGRAM_ID ) &&
                     ( prg_item_to_store.get() != nullptr ) )
            {
                st_prog_id_t const try_prog_id = this->_store_new_item(
                    std::move( prg_item_to_store ), lock );

                if( try_prog_id != base_store_type::ILLEGAL_PROGRAM_ID )
                {
                    SIXTRL_ASSERT( this->m_key_to_id_map.find( key ) ==
                                   this->m_key_to_id_map.end() );

                    auto ret = this->m_key_to_id_map.emplace(
                        std::make_pair( key, try_prog_id ) );

                    if( ret.second )
                    {
                        stored_prog_id = try_prog_id;
                    }
                }
            }
        }

        return stored_prog_id;
    }

    ocl_base_prg_item_type const* store_type::program_item( st_prog_id_t const id,
        st_guard_t const& SIXTRL_RESTRICT_REF lock ) const {
        ocl_base_prg_item_type const* derived = nullptr;

        base_prg_item_type const* ptr = base_store_type::program_item( id, lock );
        if( ptr == nullptr ) return derived;

        if( st::BackendObjBase_is_derived<
                item_base_type, ocl_rtc_prg_item_type >( *ptr ) )
        {
            derived = st::BackendObjBase_cast_to_derived< item_base_type,
                ocl_rtc_prg_item_type >( ptr );
        }

        return derived;
    }

    ocl_base_prg_item_type const* store_type::program_item(
        st_prog_id_t const id,
        st_guard_t const& SIXTRL_RESTRICT_REF lock ) {
        return static_cast< store_type const& >(
            *this ).program_item( id, lock ); }

    ocl_base_prg_item_type const* store_type::program_item( st_key_t const& key,
        st_guard_t const& SIXTRL_RESTRICT_REF lock ) const {
        return this->program_item( this->program_id( key, lock ), lock ); }

    ocl_base_prg_item_type* store_type::do_get_program_item(
        st_key_t const& key, st_guard_t const& SIXTRL_RESTRICT_REF lock ) {
        return this->do_get_program_item( this->program_id( key, lock ), lock );
    }

    ocl_base_prg_item_type* store_type::do_get_program_item(
        program_id_type const id,
        guard_type const& SIXTRL_RESTRICT_REF lock ) {
        ocl_base_prg_item_type* derived = nullptr;
        base_prg_item_type* ptr =
            base_store_type::do_get_program_item( id, lock );

        if( ptr != nullptr ) return derived;
        if( st::BackendObjBase_is_derived<
                item_base_type, ocl_rtc_prg_item_type >( *ptr ) )
        {
            derived = st::BackendObjBase_cast_to_derived<
                base_prg_item_type, ocl_rtc_prg_item_type >( ptr );
        }

        return derived;
    }

} /* end: namespace SIXTRL_CXX_NAMESPACE */
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */
