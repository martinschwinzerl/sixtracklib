#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/base/architecture/architectures_store.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <algorithm>
    #include <utility>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using store_t = st::ArchitecturesStore;
        using arch_t = st::Architecture;
        using st_arch_id_t = store_t::arch_id_t;
        using st_status_t = store_t::status_t;
    }

    constexpr st_arch_id_t store_t::MIN_USERDEFINED_ARCH_ID;
    constexpr st_arch_id_t store_t::MAX_USERDEFINED_ARCH_ID;

    /* --------------------------------------------------------------------- */

    st_status_t store_t::INIT_PREDEFINED_ARCHITECTURES(
        store_t& SIXTRL_RESTRICT_REF arch_store )
    {
        return st::STATUS_GENERAL_FAILURE;
    }

    /* --------------------------------------------------------------------- */

    store_t::ArchitecturesStore() :
        m_id_to_architectures(), m_arch_str_to_arch_id(), m_stored_arch_ids(),
        m_next_userdefined_arch_id( store_t::MIN_USERDEFINED_ARCH_ID )
    {

    }

    bool store_t::has_architecture(
        st_arch_id_t const arch_id ) const SIXTRL_NOEXCEPT
    {
        return ( ( arch_id != st::ARCHITECTURE_ILLEGAL ) &&
                 ( arch_id != st::ARCHITECTURE_UNDEFINED ) &&
                 ( this->m_id_to_architectures.find( arch_id ) !=
                   this->m_id_to_architectures.end() ) );
    }

    bool store_t::has_arch_string(
        st_arch_id_t const arch_id ) const SIXTRL_NOEXCEPT
    {
        bool has_arch_str = false;

        SIXTRL_ASSERT( this->m_id_to_architectures.size() ==
                       this->m_stored_arch_ids.size() );

        SIXTRL_ASSERT( this->m_stored_arch_ids.size() >=
                       this->m_arch_str_to_arch_id.size() );

        if( ( arch_id != st::ARCHITECTURE_ILLEGAL ) &&
            ( arch_id != st::ARCHITECTURE_UNDEFINED ) )
        {
            auto it = this->m_id_to_architectures.find( arch_id );

            if( ( it != this->m_id_to_architectures.end() ) &&
                ( it->second.get() != nullptr ) )
            {
                has_arch_str = it->second->has_arch_string();

                SIXTRL_ASSERT( ( !has_arch_str ) ||
                    ( ( !it->second->arch_string_str().empty() ) &&
                      ( this->m_arch_str_to_arch_id.find(
                        it->second->arch_string_str() ) !=
                        this->m_arch_str_to_arch_id.end() ) &&
                      ( this->m_arch_str_to_arch_id.find(
                        it->second->arch_string_str() )->second == arch_id ) ) );
            }
        }

        return has_arch_str;
    }

    std::string const& store_t::arch_string_str(
        st_arch_id_t const arch_id ) const
    {
        SIXTRL_ASSERT( this->m_id_to_architectures.size() ==
                       this->m_stored_arch_ids.size() );

        SIXTRL_ASSERT( this->m_stored_arch_ids.size() >=
                       this->m_arch_str_to_arch_id.size() );

        if( ( arch_id == st::ARCHITECTURE_ILLEGAL ) ||
            ( arch_id == st::ARCHITECTURE_UNDEFINED ) )
        {
            throw std::runtime_error( "illegal/undefined arch_id" );
        }

        auto it = this->m_id_to_architectures.find( arch_id );

        if( it == this->m_id_to_architectures.end() )
        {
            throw std::runtime_error( "arch_id not stored" );
        }

        if( it->second.get() == nullptr )
        {
            throw std::runtime_error( "empty / null architecture stored" );
        }

        if( !it->second->has_arch_string() )
        {
            throw std::runtime_error( "stored architecture has no arch_string" );
        }

        return it->second->arch_string_str();
    }

    char const* store_t::arch_string(
        st_arch_id_t const arch_id ) const SIXTRL_NOEXCEPT
    {
        char const* arch_cstring = nullptr;

        SIXTRL_ASSERT( this->m_id_to_architectures.size() ==
                       this->m_stored_arch_ids.size() );

        SIXTRL_ASSERT( this->m_stored_arch_ids.size() >=
                       this->m_arch_str_to_arch_id.size() );

        if( ( arch_id != st::ARCHITECTURE_ILLEGAL ) &&
            ( arch_id != st::ARCHITECTURE_UNDEFINED ) )
        {
            auto it = this->m_id_to_architectures.find( arch_id );

            if( ( it != this->m_id_to_architectures.end() ) &&
                ( it->second.get() != nullptr ) )
            {
                if( it->second->has_arch_string() )
                {
                    arch_cstring = it->second->arch_string();
                }
            }
        }

        return arch_cstring;
    }

    st_arch_id_t store_t::arch_id_by_str( std::string const&
        SIXTRL_RESTRICT_REF arch_str ) const SIXTRL_NOEXCEPT
    {
        st_arch_id_t arch_id = st::ARCHITECTURE_ILLEGAL;

        SIXTRL_ASSERT( this->m_id_to_architectures.size() ==
                       this->m_stored_arch_ids.size() );

        SIXTRL_ASSERT( this->m_stored_arch_ids.size() >=
                       this->m_arch_str_to_arch_id.size() );

        if( !arch_str.empty() )
        {
            auto it = this->m_arch_str_to_arch_id.find( arch_str );

            if( it != this->m_arch_str_to_arch_id.end() )
            {
                SIXTRL_ASSERT(
                    ( it->second != st::ARCHITECTURE_ILLEGAL ) &&
                    ( it->second != st::ARCHITECTURE_UNDEFINED ) &&
                    ( this->has_architecture( it->second ) ) );

                arch_id = it->second;
            }
        }

        return arch_id;
    }

    st_size_t store_t::num_architectures() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_id_to_architectures.size() ==
                       this->m_stored_arch_ids.size() );

        SIXTRL_ASSERT( this->m_stored_arch_ids.size() >=
                       this->m_arch_str_to_arch_id.size() );

        return this->m_stored_arch_ids.size();
    }

    st_arch_id_t store_t::arch_id_by_idx(
        st_size_t const idx ) const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_id_to_architectures.size() ==
                       this->m_stored_arch_ids.size() );

        SIXTRL_ASSERT( this->m_stored_arch_ids.size() >=
                       this->m_arch_str_to_arch_id.size() );

        return ( this->m_stored_arch_ids.size() > idx )
            ? this->m_stored_arch_ids[ idx ]
            : st::ARCHITECTURE_ILLEGAL;
    }

    st_arch_id_t const* store_t::arch_ids_begin() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( this->m_id_to_architectures.size() ==
                       this->m_stored_arch_ids.size() );

        SIXTRL_ASSERT( this->m_stored_arch_ids.size() >=
                       this->m_arch_str_to_arch_id.size() );

        return ( !this->m_stored_arch_ids.empty() )
            ? this->m_stored_arch_ids.data() : nullptr;
    }

    st_arch_id_t const* store_t::arch_ids_end() const SIXTRL_NOEXCEPT
    {
        auto ptr_end = this->arch_ids_begin();

        if( ptr_end != nullptr )
        {
            SIXTRL_ASSERT( this->m_id_to_architectures.size() ==
                        this->m_stored_arch_ids.size() );

            SIXTRL_ASSERT( this->m_stored_arch_ids.size() >=
                        this->m_arch_str_to_arch_id.size() );

            std::advance( ptr_end, this->m_stored_arch_ids.size() );
        }

        return ptr_end;
    }

    arch_t const* store_t::architecture(
        st_arch_id_t const arch_id ) const SIXTRL_NOEXCEPT
    {
        arch_t const* ptr_architecture = nullptr;

        if( ( arch_id != st::ARCHITECTURE_ILLEGAL ) &&
            ( arch_id != st::ARCHITECTURE_UNDEFINED ) )
        {
            auto it = this->m_id_to_architectures.find( arch_id );

            if( it != this->m_id_to_architectures.end() )
            {
                ptr_architecture = it->second.get();
            }
        }

        return ptr_architecture;
    }

    arch_t* store_t::architecture( st_arch_id_t const arch_id ) SIXTRL_NOEXCEPT
    {
        return const_cast< arch_t* >( static_cast< store_t const& >(
            *this ).architecture( arch_id ) );
    }

    arch_t const* store_t::architecture_by_str( std::string
        const& SIXTRL_RESTRICT_REF arch_str ) const SIXTRL_NOEXCEPT
    {
        return this->architecture( this->arch_id_by_str( arch_str ) );
    }

    arch_t* store_t::architecture_by_str( std::string const&
        SIXTRL_RESTRICT_REF arch_str ) SIXTRL_NOEXCEPT
    {
        return this->architecture( this->arch_id_by_str( arch_str ) );
    }

    arch_t const* store_t::architecture_by_idx(
        st_size_t const idx ) const SIXTRL_NOEXCEPT
    {
        return this->architecture( this->arch_id_by_idx( idx ) );
    }

    arch_t* store_t::architecture_by_idx( st_size_t const idx ) SIXTRL_NOEXCEPT
    {
        return this->architecture( this->arch_id_by_idx( idx ) );
    }

    /* --------------------------------------------------------------------- */

    st_status_t store_t::add_architecture(
        std::unique_ptr< architecture_t > architecture_to_store )
    {
        return this->do_add_architecture( std::move( architecture_to_store ) );
    }

    st_status_t store_t::remove_architecture( st_arch_id_t const arch_id )
    {
        return this->do_remove_architecture( arch_id );
    }

    st_status_t store_t::remove_architecture_by_str(
        std::string const& SIXTRL_RESTRICT_REF arch_str )
    {
        return this->do_remove_architecture( this->arch_id_by_str( arch_str ) );
    }

    /* --------------------------------------------------------------------- */

    st_status_t store_t::do_add_architecture(
        std::unique_ptr< arch_t >&& architecture_to_store )
    {
        return this->do_add_architecture_base_impl(
            std::move( architecture_to_store ) );
    }

    st_status_t store_t::do_remove_architecture( st_arch_id_t const arch_id )
    {
        return this->do_remove_architecture_base_impl( arch_id );
    }

    /* --------------------------------------------------------------------- */

    st_status_t store_t::do_add_architecture_base_impl(
        std::unique_ptr< arch_t >&& architecture_to_store )
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( architecture_to_store.get() == nullptr )
        {
            return status;
        }

        st_arch_id_t arch_id = architecture_to_store->arch_id();

        if( ( arch_id != st::ARCHITECTURE_ILLEGAL ) &&
            ( arch_t::IS_PREDEFINED_ARCHITECTURE( arch_id ) ) )
        {
            status = st::STATUS_SUCCESS;
        }
        else if( ( arch_id == st::ARCHITECTURE_UNDEFINED ) &&
                 ( this->m_next_userdefined_arch_id <
                   store_t::MAX_USERDEFINED_ARCH_ID ) )
        {
            auto max_it = std::max_element( this->m_stored_arch_ids.begin(),
                this->m_stored_arch_ids.end() );

            if( (  max_it != this->m_stored_arch_ids.end() ) &&
                ( *max_it >= this->m_next_userdefined_arch_id ) )
            {
                return st::STATUS_GENERAL_FAILURE;
            }

            status = architecture_to_store->update_undefined_arch_id(
                this->m_next_userdefined_arch_id++ );
        }

        if( status == st::STATUS_SUCCESS )
        {
            SIXTRL_ASSERT( this->m_arch_str_to_arch_id.size() <=
                           this->m_stored_arch_ids.size() );

            SIXTRL_ASSERT( this->m_id_to_architectures.size() ==
                           this->m_stored_arch_ids.size() );

            auto it = this->m_id_to_architectures.find( arch_id );
            if( it != this->m_id_to_architectures.end() )
            {
                SIXTRL_ASSERT( ( !architecture_to_store->has_arch_string() ) ||
                    ( ( ( this->m_arch_str_to_arch_id.find(
                            architecture_to_store->arch_string_str() ) !=
                          this->m_arch_str_to_arch_id.end() ) &&
                        ( this->m_arch_str_to_arch_id.find(
                            architecture_to_store->arch_string_str() )->second
                                == arch_id ) ) ) );

                SIXTRL_ASSERT( std::find( this->m_stored_arch_ids.begin(),
                    this->m_stored_arch_ids.end(), arch_id ) !=
                        this->m_stored_arch_ids.end() );

                return st::STATUS_GENERAL_FAILURE;
            }

            if( status == st::STATUS_SUCCESS )
            {
                auto res = this->m_id_to_architectures.emplace(
                    std::make_pair( arch_id, std::move(
                        architecture_to_store ) ) );

                if( res.second )
                {
                    SIXTRL_ASSERT(
                        ( !architecture_to_store->has_arch_string() ) ||
                        ( this->m_arch_str_to_arch_id.find(
                            architecture_to_store->arch_string_str() ) ==
                                this->m_arch_str_to_arch_id.end() ) );

                    if( architecture_to_store->has_arch_string() )
                    {
                        auto res2 = this->m_arch_str_to_arch_id.emplace(
                            std::make_pair(
                                architecture_to_store->arch_string_str(),
                                arch_id ) );

                        if( !res2.second )
                        {
                            this->m_id_to_architectures.erase( res.first );
                            status = st::STATUS_GENERAL_FAILURE;
                        }
                    }

                    if( status == st::STATUS_SUCCESS )
                    {
                        this->m_stored_arch_ids.push_back( arch_id );
                    }
                }
                else
                {
                    status = st::STATUS_GENERAL_FAILURE;
                }
            }

            SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                ( ( this->m_id_to_ptr_data_base.size() ==
                    this->m_stored_arch_ids.size() ) &&
                  ( this->m_id_to_ptr_data_base.find( arch_id ) !=
                    this->m_id_to_ptr_data_base.end() ) &&
                  ( this->m_id_to_ptr_data_base.find(
                    arch_id )->second.get() != nullptr ) &&
                  ( std::is_sorted( this->m_stored_arch_ids.begin(),
                                    this->m_stored_arch_ids.end() ) ) ) );
        }

        return status;
    }

    st_status_t store_t::do_remove_architecture_base_impl(
        st_arch_id_t const arch_id ) SIXTRL_NOEXCEPT
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( arch_id != st::ARCHITECTURE_ILLEGAL ) &&
            ( arch_id != st::ARCHITECTURE_UNDEFINED ) )
        {
            SIXTRL_ASSERT( this->m_id_to_architectures.size() ==
                           this->m_stored_arch_ids.size() );

            SIXTRL_ASSERT( this->m_arch_str_to_arch_id.size() <=
                           this->m_stored_arch_ids.size() );

            auto map_it = this->m_id_to_architectures.find( arch_id );
            auto list_it = std::find( this->m_stored_arch_ids.begin(),
                this->m_stored_arch_ids.end(), arch_id );

            auto str_found = this->m_arch_str_to_arch_id.end();
            auto str_it = this->m_arch_str_to_arch_id.begin();

            for( ; str_it != this->m_arch_str_to_arch_id.end() ; ++str_it )
            {
                if( str_it->second == arch_id )
                {
                    str_found = str_it;
                    break;
                }
            }

            if( ( map_it != this->m_id_to_architectures.end() ) &&
                ( map_it->second.get() != nullptr ) &&
                ( list_it != this->m_stored_arch_ids.end() ) &&
                ( ( !map_it->second->has_arch_string() ) ||
                  ( ( str_it != this->m_arch_str_to_arch_id.end() ) &&
                    ( str_it->first.compare(
                        map_it->second->arch_string() ) == 0 ) ) ) )
            {
                this->m_id_to_architectures.erase( map_it );
                this->m_stored_arch_ids.erase( list_it );

                if( str_it != this->m_arch_str_to_arch_id.end() )
                {
                    this->m_arch_str_to_arch_id.erase( str_it );
                }

                status = st::STATUS_SUCCESS;
            }
            else if( ( map_it == this->m_id_to_architectures.end() ) &&
                  ( list_it == this->m_stored_arch_ids.end() ) &&
                  ( str_it == this->m_arch_str_to_arch_id.end() ) )
            {
                status = st::STATUS_SUCCESS;
            }
        }

        return status;
    }

    store_t const& ArchitecturesStore_const_global() {
        static store_t const global_store;
        return global_store;
    }

    store_t& ArchitecturesStore_global() {
        return const_cast< store_t& >( st::ArchitecturesStore_const_global() );
    }

    store_t const* ArchitecturesStore_ptr_const_global() {
        return std::addressof( st::ArchitecturesStore_const_global() );
    }

    store_t* ArchitecturesStore_ptr_global() {
        return std::addressof( st::ArchitecturesStore_global() );
    }
}

::NS(ArchitecturesStore) const* NS(ArchitecturesStore_ptr_const_global)()
{
    return SIXTRL_CXX_NAMESPACE::ArchitecturesStore_ptr_const_global();
}

::NS(ArchitecturesStore)* NS(ArchitecturesStore_ptr_global)()
{
    return SIXTRL_CXX_NAMESPACE::ArchitecturesStore_ptr_global();
}

#endif /* C++, Host */
