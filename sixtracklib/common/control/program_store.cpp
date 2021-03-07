#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/program_store.h"
    #include "sixtracklib/common/control/program_item.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using store_type   = st::ProgramStoreBase;
        using st_size_t    = store_type::size_type;
        using st_prog_id_t = store_type::program_id_type;
    }

    constexpr store_type::class_id_type store_type::BASE_CLASS_ID;
    constexpr store_type::program_id_type store_type::ILLEGAL_PROGRAM_ID;

    constexpr store_type::backend_id_type
    st::BackendObjTraits< store_type >::BACKEND_ID;

    constexpr store_type::class_id_type
    st::BackendObjTraits< store_type >::BASE_CLASS_ID;

    constexpr store_type::class_id_type
    st::BackendObjTraits< store_type >::DERIVED_CLASS_ID;

    /* --------------------------------------------------------------------- */

    store_type::~ProgramStoreBase()
    {
        this->m_num_stored_items = st_size_t{ 0 };
        this->m_items.clear();
    }

    st_size_t store_type::num_stored_items() const SIXTRL_NOEXCEPT {
        SIXTRL_ASSERT( this->_count_non_null_items() ==
                       this->m_num_stored_items );
        SIXTRL_ASSERT( this->_items_vector_size() >= this->m_num_stored_items );
        return this->m_num_stored_items;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    st_prog_id_t store_type::program_id( store_type::item_base_type const&
        SIXTRL_RESTRICT_REF stored_program ) const SIXTRL_NOEXCEPT {
        st_prog_id_t prog_id = store_type::ILLEGAL_PROGRAM_ID;
        if( this->m_num_stored_items <= this->m_items.size() )
        {
            st_prog_id_t const NN = static_cast<
                st_prog_id_t >( this->m_items.size() );

            for( st_prog_id_t ii = st_prog_id_t{ 0 } ; ii < NN ; ++ii )
            {
                if( this->m_items[ ii ].get() == &stored_program )
                {
                    prog_id = ii;
                    break;
                }
            }
        }

        return prog_id;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    store_type::item_base_type const* store_type::program_item(
        st_prog_id_t const id ) const {
        return ( ( id >= st_prog_id_t{ 0 } ) &&
                 ( static_cast< st_size_t >( id ) < this->m_items.size() ) )
            ? this->m_items[ id ].get() : nullptr; }

    store_type::item_base_type const* store_type::program_item(
        st_prog_id_t const id ) {
        return static_cast< store_type const& >( *this ).program_item( id ); }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    bool store_type::is_stored( st_prog_id_t const id ) const SIXTRL_NOEXCEPT {
        return ( ( id >= st_prog_id_t{ 0 } ) &&
                 ( this->m_items.size() > static_cast< st_size_t >( id ) ) ); }

    std::unique_ptr< store_type::item_base_type >
    store_type::remove( st_prog_id_t const id ) SIXTRL_NOEXCEPT {
        return this->is_stored( id )
            ? std::move( this->m_items[ id ] )
            : std::unique_ptr< store_type::item_base_type >( nullptr ); }


    store_type::item_base_type*
    store_type::do_get_program_item( st_prog_id_t const id ) {
        return ( this->is_stored( id ) ) ? this->m_items[ id ].get() : nullptr; }

    st_prog_id_t store_type::_store_new_item(
        std::unique_ptr< store_type::item_base_type >&& item_to_store )
    {
        st_prog_id_t stored_prog_id = store_type::ILLEGAL_PROGRAM_ID;
        st_prog_id_t const try_id = static_cast< st_prog_id_t >(
            this->m_items.size() );

        if( item_to_store.get() != nullptr )
        {
            this->m_items.push_back( std::move( item_to_store ) );
            ++this->m_num_stored_items;
            stored_prog_id = try_id;
        }
        else
        {
            this->m_items.emplace_back( nullptr );
            stored_prog_id = try_id;
        }

        SIXTRL_ASSERT( this->_count_non_null_items() ==
                       this->m_num_stored_items );
        SIXTRL_ASSERT( this->_items_vector_size() >= this->m_num_stored_items );

        return stored_prog_id;
    }

    st_size_t store_type::_count_non_null_items() const SIXTRL_NOEXCEPT {

        st_size_t num_non_null_items = st_size_t{ 0 };

        if( !this->m_items.empty() )
        {
            for( auto& item : this->m_items )
            {
                if( item.get() != nullptr ) ++num_non_null_items;
            }
        }

        return num_non_null_items;
    }

} /* end: namespace SIXTRL_CXX_NAMESPACE */
#endif /* C++, Host */
