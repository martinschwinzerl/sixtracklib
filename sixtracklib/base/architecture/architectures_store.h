#ifndef SIXTRACKLIB_BASE_ARCHITECTURE_ARCHITECTURE_STORE_H__
#define SIXTRACKLIB_BASE_ARCHITECTURE_ARCHITECTURE_STORE_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/base/architecture/definitions.h"
    #include "sixtracklib/base/architecture/architecture.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <cstddef>
        #include <cstdlib>
        #include <memory>
        #include <string>
        #include <unordered_map>
        #include <vector>
    #endif /* C++ */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    class SIXTRL_BASE_EXPORT_API ArchitecturesStore
    {
        public:

        using architecture_t       = SIXTRL_CXX_NAMESPACE::Architecture;
        using size_type            = SIXTRL_CXX_NAMESPACE::size_t;
        using status_t             = SIXTRL_CXX_NAMESPACE::status_t;
        using ptr_architecture_t   = std::unique_ptr< architecture_t >;
        using arch_id_t            = architecture_t::arch_id_t;
        using plugin_handle_t      = architecture_t::plugin_handle_t;
        using state_flags_t        = architecture_t::state_flags_t;

        static SIXTRL_HOST_FN status_t INIT_PREDEFINED_ARCHITECTURES(
            ArchitecturesStore& SIXTRL_RESTRICT_REF arch_store );

        static constexpr arch_id_t
            MIN_USERDEFINED_ARCH_ID = arch_id_t{ 256 };

        static constexpr arch_id_t
            MAX_USERDEFINED_ARCH_ID = arch_id_t{ 0x7fffffff };

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN ArchitecturesStore();

        ArchitecturesStore( ArchitecturesStore const& ) = delete;
        ArchitecturesStore( ArchitecturesStore&& ) = delete;

        ArchitecturesStore& operator=( ArchitecturesStore const& ) = delete;
        ArchitecturesStore& operator=( ArchitecturesStore&& ) = delete;

        virtual ~ArchitecturesStore() = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool has_architecture(
            arch_id_t const arch_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_BASE_EXPORT_API SIXTRL_HOST_FN SIXTRL_INLINE bool
        has_architecture_by_str( std::string const&
            SIXTRL_RESTRICT_REF arch_str ) const SIXTRL_NOEXCEPT
        {
            return this->has_architecture( this->arch_id_by_str( arch_str ) );
        }

        SIXTRL_HOST_FN bool has_arch_string(
            arch_id_t const arch_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN std::string const& arch_string_str(
            arch_id_t const arch_id ) const;

        SIXTRL_HOST_FN char const* arch_string(
            arch_id_t const arch_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN arch_id_t arch_id_by_str( std::string const&
            SIXTRL_RESTRICT_REF arch_str ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type num_architectures() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN arch_id_t arch_id_by_idx(
            size_type const idx ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN arch_id_t const* arch_ids_begin() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN arch_id_t const* arch_ids_end() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN architecture_t const* architecture(
            arch_id_t const arch_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN architecture_t* architecture(
            arch_id_t const arch_id ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN architecture_t const* architecture_by_str( std::string
            const& SIXTRL_RESTRICT_REF arch_str ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN architecture_t* architecture_by_str(
            std::string const& SIXTRL_RESTRICT_REF arch_str ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN architecture_t const* architecture_by_idx(
            size_type const idx ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN architecture_t* architecture_by_idx(
            size_type const idx ) SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_BASE_EXPORT_API SIXTRL_HOST_FN SIXTRL_INLINE bool
        has_architectures_with_nodes() const SIXTRL_NOEXCEPT {
            return !this->m_archs_with_nodes.empty(); }

        SIXTRL_BASE_EXPORT_API SIXTRL_HOST_FN SIXTRL_INLINE arch_id_t const*
        architectures_with_nodes_begin() const SIXTRL_NOEXCEPT {
            return ( !this->m_archs_with_nodes.empty() )
                ? this->m_archs_with_nodes.data() : nullptr; }

        SIXTRL_BASE_EXPORT_API SIXTRL_HOST_FN SIXTRL_INLINE arch_id_t const*
        architectures_with_nodes_end() const SIXTRL_NOEXCEPT {
            auto end_ptr = this->architectures_with_nodes_begin();
            if( end_ptr != nullptr )
                std::advance( end_ptr, this->m_archs_with_nodes.size() );
            return end_ptr;
        }

        template< typename ArchStrIter >
        SIXTRL_HOST_FN size_type arch_string_for_archs_with_nodes(
            ArchStrIter arch_str_begin, ArchStrIter arch_str_end ) const
        {
            size_type num_arch_strings = size_type{ 0 };

            auto out_capacity = std::distance( arch_str_begin, arch_str_end );
            auto it = arch_str_begin;
            auto arch_id_it = this->m_archs_with_nodes.begin();
            auto arch_id_end = this->m_archs_with_nodes.end();

            while( ( it != arch_str_end ) && ( arch_id_it != arch_id_end ) )
            {
                auto architecture = this->architecture( *arch_id_it );
                if( architecture == nullptr ) continue;

                *it++ = architecture->arch_string_str();
                ++num_arch_strings;
                ++arch_id_it;
            }

            while( it != arch_str_end )
            {
                it->clear();
                ++it;
            }

            return num_arch_strings;
        }

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t add_architecture(
            std::unique_ptr< architecture_t > architecture_to_store );

        SIXTRL_HOST_FN status_t remove_architecture( arch_id_t const arch_id );

        SIXTRL_HOST_FN status_t remove_architecture_by_str(
            std::string const& SIXTRL_RESTRICT_REF arch_str );

        protected:

        using arch_id_list_t = std::vector< arch_id_t >;
        using id_to_architecture_map_t =
            std::unordered_map< arch_id_t, std::unique_ptr< architecture_t > >;

        using arch_str_to_arch_id_map_t =
            std::unordered_map< std::string, arch_id_t >;

        SIXTRL_HOST_FN virtual status_t do_add_architecture(
            std::unique_ptr< architecture_t >&& architecture_to_store );

        SIXTRL_HOST_FN virtual status_t do_remove_architecture(
            arch_id_t const arch_id );

        private:

        SIXTRL_HOST_FN status_t do_add_architecture_base_impl(
            std::unique_ptr< architecture_t >&& architecture_to_store );

        SIXTRL_HOST_FN status_t do_remove_architecture_base_impl(
            arch_id_t const arch_id ) SIXTRL_NOEXCEPT;

        id_to_architecture_map_t m_id_to_architectures;
        arch_str_to_arch_id_map_t m_arch_str_to_arch_id;
        arch_id_list_t m_stored_arch_ids;
        arch_id_list_t m_archs_with_nodes;
        arch_id_t m_next_userdefined_arch_id;
    };

    SIXTRL_BASE_EXPORT_API SIXTRL_EXTERN SIXTRL_HOST_FN
    ArchitecturesStore const& ArchitecturesStore_const_global();

    SIXTRL_BASE_EXPORT_API SIXTRL_EXTERN SIXTRL_HOST_FN
    ArchitecturesStore& ArchitecturesStore_global();

    SIXTRL_BASE_EXPORT_API SIXTRL_EXTERN SIXTRL_HOST_FN
    ArchitecturesStore const* ArchitecturesStore_ptr_const_global();

    SIXTRL_BASE_EXPORT_API SIXTRL_EXTERN SIXTRL_HOST_FN
    ArchitecturesStore* ArchitecturesStore_ptr_global();

} /* ns: SIXTRL_CXX_NAMESPACE */

extern "C" {
    typedef SIXTRL_CXX_NAMESPACE::ArchitecturesStore NS(ArchitecturesStore);
}

#else /* C++, Host */

struct NS(ArchitecturesStore);

#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_BASE_EXPORT_API SIXTRL_EXTERN SIXTRL_HOST_FN
NS(ArchitecturesStore) const* NS(ArchitecturesStore_ptr_const_global)( void );

SIXTRL_BASE_EXPORT_API SIXTRL_EXTERN SIXTRL_HOST_FN
NS(ArchitecturesStore)* NS(ArchitecturesStore_ptr_global)( void );

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_BASE_ARCHITECTURE_ARCHITECTURE_STORE_H__ */
