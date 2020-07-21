#ifndef SIXTRACKLIB_COMMON_CONTROL_PROGRAM_CODE_H__
#define SIXTRACKLIB_COMMON_CONTROL_PROGRAM_CODE_H__

#if !defined( SIXTRL_NO_DEFINES )
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/arch_base.hpp"
#endif /* !defined( SIXTRL_NO_DEFINES ) */

#if !defined( SIXTRL_NO_SYSTEM_DEFINES )
    #include <iterator>
    #include <map>
    #include <memory>
    #include <string>
    #include <type_traits>
    #include <vector>
#endif /* !defined( SIXTRL_NO_SYSTEM_DEFINES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    class ProgramCodeDefinitions
    {
        public:

        using arch_id_t = SIXTRL_CXX_NAMESPACE::arch_id_t;
        using size_type = SIXTRL_CXX_NAMESPACE::arch_size_t;
        using status_t  = SIXTRL_CXX_NAMESPACE::arch_status_t;

        private:

        using definitions_map_t = std::map< std::string, std::string >;
        using definitions_key_list_t = std::vector< std::string >;

        public:

        using const_iterator = definitions_map_t::const_iterator;
        using iterator = definitions_map_t::iterator;

        SIXTRL_HOST_FN ProgramCodeDefinitions();

        template< class PairIter >
        SIXTRL_HOST_FN ProgramCodeDefinitions( PairIter begin, PairIter end ) :
            m_definitions_map(), m_definition_keys()
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            status_t status = st::ARCH_STATUS_SUCCESS;

            using pair_t = typename std::iterator_traits< PairIter >::value_type;
            using key_t  = typename pair_t::first_type;
            using description_t = typename pair_t::second_type;

            static_assert(
                std::is_same< typename std::decay< key_t >::type,
                              std::string >::value &&
                std::is_same< typename std::decay< description_t >::type,
                              std::string >::value,
                "only implemented for std::string" );

            for( auto in_it = begin ; in_it != end ; ++in_it )
            {
                std::string const& key = in_it->first;
                std::string const& description = in_it->second;

                if( key.empty() ) continue;

                auto it = this->m_definitions_map.find( key );
                if( it == this->m_definitions_map.end() )
                {
                    status |= this->do_add_definition_base_impl(
                        key, description );
                }
                else
                {
                    it->second = description;
                }

                SIXTRL_ASSERT( this->has_definition_by_key( key ) );
                SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                    ( this->m_definitions_map.size() ==
                      this->m_definition_keys.size() ) );
            }

            SIXTRL_ASSERT( status == SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS );
            ( void )status;
        }

        template< class KeyIter, class ValueIter >
        SIXTRL_HOST_FN ProgramCodeDefinitions(
            KeyIter keys_it, KeyIter keys_end, ValueIter values_it )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            st::arch_status_t status = st::ARCH_STATUS_SUCCESS;

            static_assert( std::is_same< std::string, typename std::decay<
                typename std::iterator_traits< KeyIter >::value_type
                    >::type >::value, "only implemented for std::string keys" );

            static_assert( std::is_same< std::string, typename std::decay<
                typename std::iterator_traits< ValueIter >::value_type
                    >::type >::value, "only implemented for std::string values" );

            SIXTRL_ASSERT( std::distance( keys_it, keys_end ) >
                           std::ptrdiff_t{ 0 } );

            for( ; keys_it != keys_end; ++keys_it, ++values_it )
            {
                if( keys_it->empty() ) continue;
                auto it = this->m_definitions_map.find( *keys_it );

                if( it == this->m_definitions_map.end() )
                {
                    status |= this->do_add_definition_base_impl(
                        *keys_it, *values_it );
                }
                else
                {
                    it->second = *values_it;
                }

                SIXTRL_ASSERT( this->has_definition_by_key( *keys_it ) );
                SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                    ( this->m_definitions_map.size() ==
                      this->m_definition_keys.size() ) );
            }

            SIXTRL_ASSERT( this->m_definition_keys.size() ==
                           this->m_definitions_map.size() );
        }

        template< class KeyIter, class ValueIter,
            typename = typename std::enable_if<
            std::is_same< typename std::decay< typename std::iterator_traits<
                KeyIter >::value_type >::type, char const* >::value &&
            ( std::is_same< typename std::decay< typename std::iterator_traits<
                ValueIter >::value_type >::type, char const* >::value ||
              std::is_same< typename std::decay< typename std::iterator_traits<
                ValueIter >::value_type >::type, std::string >::value ),
            void >::type >
        SIXTRL_HOST_FN ProgramCodeDefinitions(
            KeyIter keys_it, KeyIter keys_end, ValueIter values_it )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            st::arch_status_t status = st::ARCH_STATUS_SUCCESS;

            SIXTRL_ASSERT( std::distance( keys_it, keys_end ) >
                           std::ptrdiff_t{ 0 } );

            for( ; keys_it != keys_end; ++keys_it, ++values_it )
            {
                if( *keys_it == nullptr ) continue;
                auto it = this->m_definitions_map.find( *keys_it );

                if( it == this->m_definitions_map.end() )
                {
                    status |= this->do_add_definition_base_impl(
                        *keys_it, *values_it );
                }
                else
                {
                    it->second = *values_it;
                }

                SIXTRL_ASSERT( this->has_definition_by_key( *keys_it ) );
                SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                    ( this->m_definitions_map.size() ==
                      this->m_definition_keys.size() ) );
            }

            SIXTRL_ASSERT( this->m_definition_keys.size() ==
                           this->m_definitions_map.size() );
        }

        SIXTRL_HOST_FN ProgramCodeDefinitions(
            std::string const* SIXTRL_RESTRICT keys_begin,
            std::string const* SIXTRL_RESTRICT values_begin,
            size_type const num_definions );

        SIXTRL_HOST_FN ProgramCodeDefinitions(
            char const* const* SIXTRL_RESTRICT keys,
            char const* const* SIXTRL_RESTRICT values,
            size_type const num_definions );

        SIXTRL_HOST_FN ProgramCodeDefinitions(
            ProgramCodeDefinitions const& SIXTRL_RESTRICT_REF orig ) = default;

        SIXTRL_HOST_FN ProgramCodeDefinitions(
            ProgramCodeDefinitions&& SIXTRL_RESTRICT_REF orig ) = default;

        SIXTRL_HOST_FN ProgramCodeDefinitions& operator=(
            ProgramCodeDefinitions const& SIXTRL_RESTRICT_REF rhs ) = default;

        SIXTRL_HOST_FN ProgramCodeDefinitions& operator=(
            ProgramCodeDefinitions&& SIXTRL_RESTRICT_REF rhs ) = default;

        SIXTRL_HOST_FN virtual ~ProgramCodeDefinitions() = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN size_type num_definions() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN std::string const& definition_key_str(
            size_type const idx ) const;

        SIXTRL_HOST_FN size_type definition_key_index(
            std::string const& SIXTRL_RESTRICT_REF key ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN char const* definition_key(
            size_type const idx ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool has_definition_by_key(
            std::string const& SIXTRL_RESTRICT_REF key ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN std::string const& definition_by_key_str(
            std::string const& SIXTRL_RESTRICT_REF key ) const;

        SIXTRL_HOST_FN char const* definition_by_key(
            std::string const& SIXTRL_RESTRICT_REF key ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN std::string const& definition_str(
            size_type const idx ) const;

        SIXTRL_HOST_FN char const* definition(
            size_type const idx ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void set_definition_by_key(
            std::string const& SIXTRL_RESTRICT_REF key,
            std::string const& SIXTRL_RESTRICT_REF definition );

        SIXTRL_HOST_FN void remove_definition_by_key(
            std::string const& SIXTRL_RESTRICT_REF key ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void remove_definition(
            size_type const idx ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN std::string const*
            definition_keys_begin() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN std::string const*
            definition_keys_end() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN const_iterator definitions_begin() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN const_iterator definitions_end() const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        template< class PairIter >
        SIXTRL_HOST_FN status_t update( PairIter def_it, PairIter def_end )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

            using pair_t  = typename std::iterator_traits< PairIter >::value_type;
            using key_t   = typename pair_t::first_type;
            using value_t = typename pair_t::second_type;

            static_assert( std::is_same< std::string,
                typename std::decay< key_t >::type >::value,
                "only implemented for std::string keys" );

            static_assert( std::is_same< std::string,
                typename std::decay< value_t >::type >::value,
                "only implemented for std::string keys" );

            for( ; def_it != def_end ; ++def_it )
            {
                if( def_it->first.empty() ) continue;
                auto it = this->m_definitions_map.find( def_it->first );

                if( it == this->m_definitions_map.end() )
                {
                    status |= this->do_add_definition(
                        def_it->first, def_it->second );
                }
                else
                {
                    it->second = *def_it->second;
                }

                SIXTRL_ASSERT( this->has_definition_by_key( def_it->first ) );
                SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                    ( this->m_definitions_map.size() ==
                      this->m_definition_keys.size() ) );
            }

            SIXTRL_ASSERT( this->m_definition_keys.size() ==
                           this->m_definitions_map.size() );

            return status;
        }

        template< class KeysIter, class ValuesIter >
        SIXTRL_HOST_FN typename std::enable_if<
            std::is_same< std::string, typename std::decay<
                typename std::iterator_traits< KeysIter >::value_type >::type
                    >::value &&
            std::is_same< std::string, typename std::decay<
                typename std::iterator_traits< ValuesIter >::value_type >::type
                    >::value, status_t >::type
        update( KeysIter keys_begin, KeysIter keys_end, ValuesIter values_it )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
            KeysIter keys_it = keys_begin;

            if( std::distance( keys_begin, keys_end ) > std::ptrdiff_t{ 0 } )
            {
                for( ; keys_it != keys_end ; ++keys_it, ++values_it )
                {
                    if( keys_it->empty() ) continue;
                    auto it = this->m_definitions_map.find( *keys_it );

                    if( it == this->m_definitions_map.end() )
                    {
                        status |= this->do_add_definition(
                            *keys_it, *values_it );
                    }
                    else
                    {
                        it->second = *values_it;
                    }

                    SIXTRL_ASSERT( this->has_definition_by_key( *keys_it ) );
                    SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                        ( this->m_definitions_map.size() ==
                          this->m_definition_keys.size() ) );
                }
            }

            SIXTRL_ASSERT( this->m_definition_keys.size() ==
                           this->m_definitions_map.size() );

            return status;
        }

        template< class KeysIter, class ValuesIter >
        SIXTRL_HOST_FN typename std::enable_if<
            std::is_same< char const*, typename std::decay<
                typename std::iterator_traits< KeysIter >::value_type >::type
                    >::value &&
            std::is_same< char const*, typename std::decay<
                typename std::iterator_traits< ValuesIter >::value_type >::type
                    >::value, status_t >::type
        update( KeysIter keys_begin, KeysIter keys_end, ValuesIter values_it )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
            KeysIter keys_it = keys_begin;

            if( std::distance( keys_begin, keys_end ) > std::ptrdiff_t{ 0 } )
            {
                for( ; keys_it != keys_end ; ++keys_it, ++values_it )
                {
                    if( ( *keys_it ) == nullptr ) continue;
                    std::string const key( *keys_it );
                    std::string value = std::string{};
                    if( ( ( *values_it ) != nullptr ) &&
                        ( std::strlen( *values_it ) > size_type{ 0 } ) )
                    {
                        value = *values_it;
                    }

                    auto it = this->m_definitions_map.find( key );
                    if( it == this->m_definitions_map.end() )
                    {
                        status |= this->do_add_definition( key, value );
                    }
                    else
                    {
                        it->second = value;
                    }

                    SIXTRL_ASSERT( this->has_definition_by_key( key ) );
                    SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                        ( this->m_definitions_map.size() ==
                          this->m_definition_keys.size() ) );
                }
            }

            SIXTRL_ASSERT( this->m_definition_keys.size() ==
                           this->m_definitions_map.size() );

            return status;
        }

        SIXTRL_HOST_FN status_t update(
            std::string const* SIXTRL_RESTRICT keys_begin,
            std::string const* SIXTRL_RESTRICT values_begin,
            size_type const num_definions );

        SIXTRL_HOST_FN status_t update(
            char const* const* SIXTRL_RESTRICT keys,
            char const* const* SIXTRL_RESTRICT values,
            size_type const num_definions );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN void clear();

        /* ----------------------------------------------------------------- */

        template< typename... Args >
        SIXTRL_HOST_FN status_t reset( Args&&... args )
        {
            this->do_clear();
            return this->update( std::forward< Args&& >( args )... );
        }

        protected:

        SIXTRL_HOST_FN virtual status_t do_add_definition(
            std::string const& SIXTRL_RESTRICT_REF key,
            std::string const& SIXTRL_RESTRICT_REF definition );

        SIXTRL_HOST_FN virtual status_t do_remove_definition(
            size_type const idx );

        SIXTRL_HOST_FN virtual void do_clear();

        private:

        SIXTRL_HOST_FN status_t do_add_definition_base_impl(
            std::string const& SIXTRL_RESTRICT key,
            std::string const& SIXTRL_RESTRICT definition );

        SIXTRL_HOST_FN status_t do_remove_definition_base_impl(
            size_type const idx ) SIXTRL_NOEXCEPT;

        definitions_map_t       m_definitions_map;
        definitions_key_list_t  m_definition_keys;
    };

    /* --------------------------------------------------------------------- */

    SIXTRL_HOST_FN SIXTRL_CXX_NAMESPACE::arch_status_t
    ProgramCodeDefinitions_to_c_code_block(
        std::ostream& SIXTRL_RESTRICT_REF ostr,
        ProgramCodeDefinitions const& SIXTRL_RESTRICT_REF program_code_defs,
        ProgramCodeDefinitions::size_type const ident_per_level = 4u,
        ProgramCodeDefinitions::size_type const level = 0u );

    /* --------------------------------------------------------------------- */

    class BaseProgramCode : public SIXTRL_CXX_NAMESPACE::BaseArchObj
    {
        public:

        using source_origin_t = uint64_t;
        using arch_id_t = SIXTRL_CXX_NAMESPACE::arch_id_t;
        using size_type = SIXTRL_CXX_NAMESPACE::arch_size_t;
        using status_t = SIXTRL_CXX_NAMESPACE::arch_status_t;

        using definitions_t = SIXTRL_CXX_NAMESPACE::ProgramCodeDefinitions;

        static constexpr source_origin_t FROM_SOURCE_FILE = uint64_t{ 0 };
        static constexpr source_origin_t FROM_STRING = uint64_t{ 1 };

        SIXTRL_HOST_FN explicit BaseProgramCode(
            std::string const& SIXTRL_RESTRICT_REF input_str,
            source_origin_t const source = FROM_STRING ) :
            SIXTRL_CXX_NAMESPACE::BaseArchObj(
                SIXTRL_CXX_NAMESPACE::ARCHITECTURE_NONE ),
            m_code(), m_full_path_to_file(), m_stored_definitions(
                new definitions_t )
            {
                status_t const status = this->set_code( input_str, source );
                SIXTRL_ASSERT( status ==
                    SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS );
                ( void )status;
            }

        template< typename PairIter >
        SIXTRL_HOST_FN BaseProgramCode(
            std::string const& SIXTRL_RESTRICT_REF input_str,
            PairIter definitions_begin, PairIter definitions_end,
            source_origin_t const source = FROM_STRING ) :
            SIXTRL_CXX_NAMESPACE::BaseArchObj(
                SIXTRL_CXX_NAMESPACE::ARCHITECTURE_NONE ),
            m_code(), m_full_path_to_file(), m_stored_definitions(
                new definitions_t )
        {
            status_t status = this->set_code( input_str, source );
            SIXTRL_ASSERT( this->definitions() != nullptr );
            status |= this->definitions()->update(
                definitions_begin, definitions_end );
            SIXTRL_ASSERT( status ==
                    SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS );
            ( void )status;
        }

        template< typename KeysIter, typename ValuesIter >
        SIXTRL_HOST_FN BaseProgramCode(
            std::string const& SIXTRL_RESTRICT_REF input_str,
            KeysIter keys_begin, KeysIter keys_end, ValuesIter values_begin,
            source_origin_t const source = FROM_STRING ) :
            SIXTRL_CXX_NAMESPACE::BaseArchObj(
                SIXTRL_CXX_NAMESPACE::ARCHITECTURE_NONE ),
            m_code(), m_full_path_to_file(), m_stored_definitions(
                new definitions_t )
        {
            status_t status = this->set_code( input_str, source );
            SIXTRL_ASSERT( this->definitions() != nullptr );
            status |= this->definitions()->update(
                keys_begin, keys_end, values_begin );
            SIXTRL_ASSERT( status ==
                    SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS );
            ( void )status;
        }

        SIXTRL_HOST_FN BaseProgramCode(
            std::string const& SIXTRL_RESTRICT_REF input_str,
            std::string const* SIXTRL_RESTRICT keys_begin,
            std::string const* SIXTRL_RESTRICT values_begin,
            size_type const num_definitions,
            source_origin_t const source = FROM_STRING ) :
            SIXTRL_CXX_NAMESPACE::BaseArchObj(
                SIXTRL_CXX_NAMESPACE::ARCHITECTURE_NONE ),
            m_code(), m_full_path_to_file(), m_stored_definitions(
                new definitions_t )
        {
            status_t status = this->set_code( input_str, source );
            SIXTRL_ASSERT( this->definitions() != nullptr );
            status |= this->definitions()->update(
                keys_begin, values_begin, num_definitions );
            SIXTRL_ASSERT( status ==
                    SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS );
            ( void )status;
        }

        SIXTRL_HOST_FN BaseProgramCode(
            char const* SIXTRL_RESTRICT input_str,
            char const* const* SIXTRL_RESTRICT keys_begin,
            char const* const* SIXTRL_RESTRICT values_begin,
            size_type const num_definitions,
            source_origin_t const source = FROM_STRING ) :
            SIXTRL_CXX_NAMESPACE::BaseArchObj(
                SIXTRL_CXX_NAMESPACE::ARCHITECTURE_NONE ),
            m_code(), m_full_path_to_file(), m_stored_definitions(
                new definitions_t )
        {
            status_t status = this->set_code( input_str, source );
            SIXTRL_ASSERT( this->definitions() != nullptr );
            status |= this->definitions()->update(
                keys_begin, values_begin, num_definitions );
            SIXTRL_ASSERT( status ==
                    SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS );
            ( void )status;
        }

        SIXTRL_HOST_FN BaseProgramCode( BaseProgramCode const& other );
        SIXTRL_HOST_FN BaseProgramCode& operator=( BaseProgramCode const& rhs );

        SIXTRL_HOST_FN BaseProgramCode( BaseProgramCode&& other ) = default;
        SIXTRL_HOST_FN BaseProgramCode& operator=( BaseProgramCode&& ) = default;

        SIXTRL_HOST_FN virtual ~BaseProgramCode() = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN definitions_t const*
            definitions() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN definitions_t* definitions() SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN std::string const& code_str() const;
        SIXTRL_HOST_FN char const* code() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t set_code(
            std::string const& SIXTRL_RESTRICT_REF input_str,
            source_origin_t const source = FROM_STRING );

        SIXTRL_HOST_FN status_t set_code_from_file(
            std::string const& SIXTRL_RESTRICT_REF full_path_to_file );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool is_from_file() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN std::string const&
            full_path_to_file_str() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN char const* full_path_to_file() const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN void clear();

        protected:

        using stored_definitions_t = std::unique_ptr< definitions_t >;

        SIXTRL_HOST_FN virtual void do_clear();
        SIXTRL_HOST_FN status_t update_stored_definitions(
            std::unique_ptr< definitions_t > defs_to_store ) SIXTRL_NOEXCEPT;

        private:

        std::string                         m_code;
        std::string                         m_full_path_to_file;
        std::unique_ptr< definitions_t >    m_stored_definitions;
    };

    class CudaProgramCode : public SIXTRL_CXX_NAMESPACE::BaseProgramCode
    {
        public:

        template< typename... Args >
        SIXTRL_HOST_FN explicit CudaProgramCode( Args&&... args ) :
            SIXTRL_CXX_NAMESPACE::BaseProgramCode(
                std::forward< Args >( args )... )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            this->set_arch_id( st::ARCHITECTURE_CUDA );
            this->set_arch_str( SIXTRL_ARCHITECTURE_CUDA_STR );
        }

        using SIXTRL_CXX_NAMESPACE::BaseProgramCode::operator=;
    };

} /* ns: SIXTRL_CXX_NAMESPACE */
#endif /* C++ */
#endif /* SIXTRACKLIB_COMMON_CONTROL_PROGRAM_CODE_H__ */
