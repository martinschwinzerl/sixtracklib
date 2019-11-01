#ifndef SIXTRACKLIB_ARCHITECTURE_ARCHITECTURES_CXX_HPP_
#define SIXTRACKLIB_ARCHITECTURE_ARCHITECTURES_CXX_HPP_

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cstddef>
    #include <cstdlib>
    #include <memory>
    #include <mutex>
    #include <string>
    #include <thread>
    #include <stdexcept>
    #include <unordered_map>
    #include <vector>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#endif /* C++, Host */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/architecture/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if  defined( __cplusplus ) && !defined( _GPUCODE ) && \
    !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

#if !defined( SIXTRL_NO_INCLUDES )
   #include "sixtracklib/common/architecture/arch_data.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    class Architectures
    {
        public:

        using arch_data_base_t     = SIXTRL_CXX_NAMESPACE::ArchData;
        using size_type            = ::NS(arch_size_t);
        using status_t             = ::NS(arch_status_t);
        using arch_id_t            = ::NS(arch_id_t);
        using init_flags_t         = ::NS(arch_init_flags_t);
        using ptr_arch_data_base_t = std::unique_ptr< arch_data_base_t >;
        using lib_handle_t         = ::NS(lib_handle_t);

        static SIXTRL_HOST_FN status_t init_default_architectures(
            Architectures& SIXTRL_RESTRICT_REF architectures );

        SIXTRL_HOST_FN Architectures();

        Architectures( Architectures const& ) = delete;
        Architectures( Architectures&& ) = delete;

        Architectures& operator=( Architectures const& ) = delete;
        Architectures& operator=( Architectures&& ) = delete;

        virtual ~Architectures() = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool has_arch(
            arch_id_t const arch_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool has_arch( std::string const&
            SIXTRL_RESTRICT_REF arch_str ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool has_arch(
            char const* SIXTRL_RESTRICT arch_str ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool has_arch_str(
            arch_id_t const arch_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN std::string const& architecture_str(
            arch_id_t const arch_id ) const;

        SIXTRL_HOST_FN char const* ptr_architecture_cstr(
            arch_id_t const arch_id ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN arch_id_t architecture_id( std::string const&
            SIXTRL_RESTRICT_REF arch_str ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN arch_id_t architecture_id( char const*
            SIXTRL_RESTRICT arch_str ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN arch_id_t architecture_id_by_index(
            size_type const index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN arch_id_t const*
        architecture_ids_begin() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN arch_id_t const*
        architecture_ids_end() const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN arch_data_base_t const* ptr_const_architecture_data_base(
            arch_id_t const arch_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN arch_data_base_t const* ptr_const_architecture_data_base(
            std::string const& SIXTRL_RESTRICT_REF arch_str
            ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN arch_data_base_t const* ptr_const_architecture_data_base(
            char const* SIXTRL_RESTRICT arch_str ) const SIXTRL_NOEXCEPT;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN arch_data_base_t* ptr_architecture_data_base(
            arch_id_t const arch_id ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN arch_data_base_t* ptr_architecture_data_base(
            std::string const& SIXTRL_RESTRICT_REF arch_str ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN arch_data_base_t* ptr_architecture_data_base(
            char const* SIXTRL_RESTRICT arch_str ) SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN size_type num_architectures() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t add_architecture(
            ptr_arch_data_base_t&& ptr_arch_data );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool has_handle(
            arch_id_t const arch_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN lib_handle_t lib_handle( arch_id_t const arch_id );

        SIXTRL_HOST_FN bool is_enabled(
            arch_id_t const arch_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool is_activated(
            arch_id_t const arch_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool is_available(
            arch_id_t const arch_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool is_shutdown(
            arch_id_t const arch_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN init_flags_t init_flags(
            arch_id_t const ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t initialize( arch_id_t const arch_id );
        SIXTRL_HOST_FN status_t shutdown( arch_id_t const arch_id );

        protected:

        using id_to_ptr_data_base_map_t =
            std::unordered_map< arch_id_t, ptr_arch_data_base_t >;

        using arch_str_to_id_map_t =
            std::unordered_map< std::string, arch_id_t >;

        using arch_id_list_t = std::vector< arch_id_t >;

        SIXTRL_HOST_FN virtual status_t doAddArchitecture(
            arch_id_t const arch_id,
            ptr_arch_data_base_t&& ptr_arch_data_base );

        private:

        SIXTRL_HOST_FN status_t doAddArchitectureBaseImpl(
            arch_id_t const arch_id,
            ptr_arch_data_base_t&& ptr_arch_data_base );

        id_to_ptr_data_base_map_t   m_id_to_ptr_data_base;
        arch_str_to_id_map_t        m_arch_str_to_id;
        arch_id_list_t              m_stored_arch_ids;
    };

    Architectures& Architectures_get();
    Architectures const& Architectures_get_const();

    Architectures* Architectures_get_ptr();
    Architectures const* Architectures_get_ptr_const();
}

typedef SIXTRL_CXX_NAMESPACE::Architectures NS(Architectures);

#else

struct NS(Architectures);
typedef struct NS(Architectures) NS(Architectures);

#endif /* C++, Host */

#if  defined( __cplusplus ) && !defined( _GPUCODE ) && \
    !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )
extern "C" {
#endif /* C++, Host */

NS(Architectures)* NS(Architectures_get_ptr)();
NS(Architectures) const* NS(Architectures_get_ptr_const)();

#if  defined( __cplusplus ) && !defined( _GPUCODE ) && \
    !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )
}
#endif /* C++, Host */

#if  defined( __cplusplus ) && !defined( _GPUCODE ) && \
    !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )

namespace SIXTRL_CXX_NAMESPACE
{
    SIXTRL_INLINE Architectures& Architectures_get()
    {
        static Architectures architectures;
        return architectures;
    }

    SIXTRL_INLINE Architectures const& Architectures_get_const()
    {
        return SIXTRL_CXX_NAMESPACE::Architectures_get();
    }

    SIXTRL_INLINE Architectures* Architectures_get_ptr()
    {
        return &Architectures_get();
    }

    SIXTRL_INLINE Architectures const* Architectures_get_ptr_const()
    {
        return &Architectures_get();
    }

    /* ********************************************************************* */

    SIXTRL_INLINE Architectures::Architectures() :
        m_id_to_ptr_data_base(),
        m_arch_str_to_id()
    {
        namespace  st = SIXTRL_CXX_NAMESPACE;
        using _this_t = st::Architectures;

        _this_t::status_t const status =
            _this_t::init_default_architectures( *this );

        if( status != st::ARCH_STATUS_SUCCESS )
        {
            throw std::runtime_error(
                "unable to initialize default architectures" );
        }
    }

    SIXTRL_INLINE bool Architectures::has_arch(
        std::string const& SIXTRL_RESTRICT_REF arch_str ) const SIXTRL_NOEXCEPT
    {
        return this->has_arch( this->architecture_id( arch_str ) );
    }

    SIXTRL_INLINE bool Architectures::has_arch(
        char const* SIXTRL_RESTRICT arch_str ) const SIXTRL_NOEXCEPT
    {
        return this->has_arch( this->architecture_id( arch_str ) );
    }

    SIXTRL_INLINE Architectures::arch_data_base_t const*
    Architectures::ptr_const_architecture_data_base(
        std::string const& SIXTRL_RESTRICT_REF arch_str ) const SIXTRL_NOEXCEPT
    {
        return this->ptr_const_architecture_data_base(
            this->architecture_id( arch_str ) );
    }

    SIXTRL_INLINE Architectures::arch_data_base_t const*
    Architectures::ptr_const_architecture_data_base(
        char const* SIXTRL_RESTRICT arch_str ) const SIXTRL_NOEXCEPT
    {
        return this->ptr_const_architecture_data_base(
            this->architecture_id( arch_str ) );
    }

    SIXTRL_INLINE Architectures::arch_data_base_t*
    Architectures::ptr_architecture_data_base(
        Architectures::arch_id_t const arch_id ) SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::Architectures;
        return const_cast< _this_t::arch_data_base_t* >(
            this->ptr_const_architecture_data_base( arch_id ) );
    }

    SIXTRL_INLINE Architectures::arch_data_base_t*
    Architectures::ptr_architecture_data_base(
        std::string const& SIXTRL_RESTRICT_REF arch_str ) SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::Architectures;
        return const_cast< _this_t::arch_data_base_t* >(
            this->ptr_const_architecture_data_base(arch_str ) );
    }

    SIXTRL_INLINE Architectures::arch_data_base_t*
    Architectures::ptr_architecture_data_base(
        char const* SIXTRL_RESTRICT arch_str ) SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::Architectures;
        return const_cast< _this_t::arch_data_base_t* >(
            this->ptr_const_architecture_data_base( arch_str ) );
    }
}

#endif /* C++, Host */

#endif /* SIXTRACKLIB_ARCHITECTURE_ARCHITECTURES_CXX_HPP_ */

/* end: sixtracklib/common/architecture/arch_state.hpp */
