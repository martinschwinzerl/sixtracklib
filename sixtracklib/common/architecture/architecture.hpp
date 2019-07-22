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
    #include <unordered_map>
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
        using size_type            = SIXTRL_CXX_NAMESPACE::arch_size_t;
        using status_t             = SIXTRL_CXX_NAMESPACE::arch_status_t;
        using ptr_arch_data_base_t = std::unique_ptr< arch_data_base_t >;
        using arch_id_t            = arch_data_base_t::arch_id_t;
        using lib_handle_t         = arch_data_base_t::lib_handle_t;
        using init_flags_t         = arch_data_base_t::init_flags_t;

        using lockable_t           = std::mutex;
        using lock_t               = std::unique_lock< lockable_t >;


        SIXTRL_HOST_FN Architectures();

        Architectures( Architectures const& ) = delete;
        Architectures( Architectures&& ) = delete;

        Architectures& operator=( Architectures const& ) = delete;
        Architectures& operator=( Architectures&& ) = delete;

        virtual ~Architectures() = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool hasArchitecture( arch_id_t const arch_id ) const;

        SIXTRL_HOST_FN bool hasArchitecture( std::string const&
            SIXTRL_RESTRICT_REF arch_str ) const;

        SIXTRL_HOST_FN bool hasArchitecture(
            char const* SIXTRL_RESTRICT arch_str ) const;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN bool hasArchitecture(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            arch_id_t const arch_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool hasArchitecture(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            std::string const& SIXTRL_RESTRICT_REF ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool hasArchitecture(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            char const* SIXTRL_RESTRICT arch_str ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool hasArchStr( arch_id_t const arch_id ) const;
        SIXTRL_HOST_FN std::string const& archStr(
            arch_id_t const arch_id ) const;

        SIXTRL_HOST_FN char const* ptrArchStr( arch_id_t const arch_id ) const;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN bool hasArchStr(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            arch_id_t const arch_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN std::string const& archStr(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            arch_id_t const arch_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN char const* ptrArchStr(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            arch_id_t const arch_id ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN arch_id_t archId(
            std::string const& SIXTRL_RESTRICT_REF arch_str ) const;

        SIXTRL_HOST_FN arch_id_t archId(
            char const* SIXTRL_RESTRICT arch_str ) const;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN arch_id_t archId(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            std::string const& SIXTRL_RESTRICT_REF arch_str ) const;

        SIXTRL_HOST_FN arch_id_t archId(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            char const* SIXTRL_RESTRICT arch_str ) const;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN arch_data_base_t const* ptrArchDataBase(
            arch_id_t const arch_id ) const;

        SIXTRL_HOST_FN arch_data_base_t const* ptrArchDataBase(
            std::string const& SIXTRL_RESTRICT_REF arch_str ) const;

        SIXTRL_HOST_FN arch_data_base_t const* ptrArchDataBase(
            char const* SIXTRL_RESTRICT arch_str ) const;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN arch_data_base_t const* ptrArchDataBase(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            arch_id_t const arch_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN arch_data_base_t const* ptrArchDataBase(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            std::string const& SIXTRL_RESTRICT_REF
                arch_str ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN arch_data_base_t const* ptrArchDataBase(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            char const* SIXTRL_RESTRICT arch_str ) const SIXTRL_NOEXCEPT;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN arch_data_base_t* ptrArchDataBase(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            arch_id_t const arch_id ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN arch_data_base_t* ptrArchDataBase(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            std::string const& SIXTRL_RESTRICT_REF arch_str ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN arch_data_base_t* ptrArchDataBase(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            char const* SIXTRL_RESTRICT arch_str ) SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN size_type numArchitectures() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type numArchitectures(
            lock_t const& lock ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t addArchitecture(
            ptr_arch_data_base_t&& ptr_arch_data );

        SIXTRL_HOST_FN status_t addArchitecture(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            ptr_arch_data_base_t&& ptr_arch_data );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool hasHandle( arch_id_t const arch_id ) const;

        SIXTRL_HOST_FN bool isEnabled( arch_id_t const arch_id ) const;
        SIXTRL_HOST_FN bool isActivated( arch_id_t const arch_id ) const;
        SIXTRL_HOST_FN bool isAvailable( arch_id_t const arch_id ) const;
        SIXTRL_HOST_FN bool isShutdown( arch_id_t const arch_id ) const;

        SIXTRL_HOST_FN init_flags_t initFlags( arch_id_t const ) const;


        SIXTRL_HOST_FN bool hasHandle( lock_t const& SIXTRL_RESTRICT_REF lock,
            arch_id_t const arch_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN lib_handle_t libHandle(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            arch_id_t const arch_id ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isEnabled( lock_t const& SIXTRL_RESTRICT_REF lock,
            arch_id_t const arch_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isActivated( lock_t const& SIXTRL_RESTRICT_REF lock,
            arch_id_t const arch_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isAvailable( lock_t const& SIXTRL_RESTRICT_REF lock,
            arch_id_t const arch_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool isShutdown( lock_t const& SIXTRL_RESTRICT_REF lock,
            arch_id_t const arch_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN init_flags_t initFlags(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            arch_id_t const ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t initialize(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            arch_id_t const arch_id );

        SIXTRL_HOST_FN status_t shutdown(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            arch_id_t const arch_id );

        /* ----------------------------------------------------------------- */

        lockable_t* lockable() const SIXTRL_NOEXCEPT;

        bool checkLock(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        protected:

        using id_to_ptr_data_base_map_t =
            std::unordered_map< arch_id_t, ptr_arch_data_base_t >;

        using arch_str_to_id_map_t =
            std::unordered_map< arch_id_t, std::string >;

        SIXTRL_HOST_FN virtual status_t doAddArchitecture(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            arch_id_t const arch_id,
            ptr_arch_data_base_t&& ptr_arch_data_base );

        private:

        SIXTRL_HOST_FN status_t doAddArchitectureBaseImpl(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            arch_id_t const arch_id,
            ptr_arch_data_base_t&& ptr_arch_data_base );

        id_to_ptr_data_base_map_t   m_id_to_ptr_data_base;
        arch_str_to_id_map_t        m_arch_str_to_id;
        mutable lockable_t          m_lockable;
    };

    Architectures& Architectures_get();
    Architectures const& Architectures_get_const();

    Architectures* Architectures_get_ptr();
    Architectures const* Architectures_get_const_ptr();
}

typedef SIXTRL_CXX_NAMESPACE::Architectures NS(Architectures);

#else

typedef void NS(Architectures);

#endif /* C++, Host */

#if  defined( __cplusplus ) && !defined( _GPUCODE ) && \
    !defined( __CUDACC__  ) && !defined( __CUDA_ARCH__ )
extern "C" {
#endif /* C++, Host */

NS(Architectures)* NS(Architectures_get_ptr)();
NS(Architectures) const* NS(Architectures_get_const_ptr)();

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

    SIXTRL_INLINE Architectures const* Architectures_get_const_ptr()
    {
        return &Architectures_get();
    }

    /* ********************************************************************* */

    SIXTRL_INLINE bool Architectures::hasArchitecture(
        Architectures::arch_id_t const arch_id ) const
    {
        SIXTRL_CXX_NAMESPACE::Architectures::lock_t lock( *this->lockable() );
        return this->hasArchitecture( lock, arch_id );
    }

    SIXTRL_INLINE bool Architectures::hasArchitecture(
        std::string const& SIXTRL_RESTRICT_REF arch_str ) const
    {
        SIXTRL_CXX_NAMESPACE::Architectures::lock_t lock( *this->lockable() );
        return this->hasArchitecture( lock, arch_str.c_str() );
    }

    SIXTRL_INLINE bool Architectures::hasArchitecture(
        char const* SIXTRL_RESTRICT arch_str ) const
    {
        SIXTRL_CXX_NAMESPACE::Architectures::lock_t lock( *this->lockable() );
        return this->hasArchitecture( lock, arch_str );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE bool Architectures::hasArchitecture(
        Architectures::lock_t const& SIXTRL_RESTRICT_REF lock,
        std::string const& SIXTRL_RESTRICT_REF arch_str ) const SIXTRL_NOEXCEPT
    {
        return this->hasArchitecture( lock, this->archId(
            lock, arch_str.c_str() ) );
    }

    SIXTRL_INLINE bool Architectures::hasArchitecture(
        Architectures::lock_t const& SIXTRL_RESTRICT_REF lock,
        char const* SIXTRL_RESTRICT arch_str ) const SIXTRL_NOEXCEPT
    {
        return this->hasArchitecture( lock, this->archId( lock, arch_str ) );
    }

    /* ----------------------------------------------------------------- */

    SIXTRL_INLINE bool Architectures::hasArchStr(
        Architectures::arch_id_t const arch_id ) const
    {
        SIXTRL_CXX_NAMESPACE::Architectures::lock_t lock( *this->lockable() );
        return this->hasArchStr( lock, arch_id );
    }

    SIXTRL_INLINE std::string const& Architectures::archStr(
        Architectures::arch_id_t const arch_id ) const
    {
        SIXTRL_CXX_NAMESPACE::Architectures::lock_t lock( *this->lockable() );
        return this->archStr( lock, arch_id );
    }

    SIXTRL_INLINE char const* Architectures::ptrArchStr(
        Architectures::arch_id_t const arch_id ) const
    {
        SIXTRL_CXX_NAMESPACE::Architectures::lock_t lock( *this->lockable() );
        return this->ptrArchStr( lock, arch_id );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE Architectures::arch_id_t Architectures::archId(
        std::string const& SIXTRL_RESTRICT_REF arch_str ) const
    {
        SIXTRL_CXX_NAMESPACE::Architectures::lock_t lock( *this->lockable() );
        return this->archId( lock, arch_str.c_str() );
    }

    SIXTRL_INLINE Architectures::arch_id_t Architectures::archId(
        char const* SIXTRL_RESTRICT arch_str ) const
    {
        SIXTRL_CXX_NAMESPACE::Architectures::lock_t lock( *this->lockable() );
        return this->archId( lock, arch_str );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE Architectures::arch_id_t Architectures::archId(
        Architectures::lock_t const& SIXTRL_RESTRICT_REF lock,
        std::string const& SIXTRL_RESTRICT_REF arch_str ) const
    {
        return this->archId( lock, arch_str.c_str() );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE Architectures::arch_data_base_t const*
    Architectures::ptrArchDataBase(
        Architectures::arch_id_t const arch_id ) const
    {
        SIXTRL_CXX_NAMESPACE::Architectures::lock_t lock( *this->lockable() );
        return this->ptrArchDataBase( lock, arch_id );
    }

    SIXTRL_INLINE Architectures::arch_data_base_t const*
    Architectures::ptrArchDataBase(
        std::string const& SIXTRL_RESTRICT_REF arch_str ) const
    {
        SIXTRL_CXX_NAMESPACE::Architectures::lock_t lock( *this->lockable() );
        return this->ptrArchDataBase( lock, this->archId( lock, arch_str ) );
    }

    SIXTRL_INLINE Architectures::arch_data_base_t const*
    Architectures::ptrArchDataBase(
        char const* SIXTRL_RESTRICT arch_str ) const
    {
        SIXTRL_CXX_NAMESPACE::Architectures::lock_t lock( *this->lockable() );
        return this->ptrArchDataBase( lock, this->archId( lock, arch_str ) );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE Architectures::arch_data_base_t const*
    Architectures::ptrArchDataBase(
        Architectures::lock_t const& SIXTRL_RESTRICT_REF lock,
        std::string const& SIXTRL_RESTRICT_REF arch_str ) const SIXTRL_NOEXCEPT
    {
        return this->ptrArchDataBase( lock, this->archId( lock, arch_str ) );
    }

    SIXTRL_INLINE Architectures::arch_data_base_t const*
    Architectures::ptrArchDataBase(
        Architectures::lock_t const& SIXTRL_RESTRICT_REF lock,
        char const* SIXTRL_RESTRICT arch_str ) const SIXTRL_NOEXCEPT
    {
        return this->ptrArchDataBase( lock, this->archId( lock, arch_str ) );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE Architectures::arch_data_base_t*
    Architectures::ptrArchDataBase(
        Architectures::lock_t const& SIXTRL_RESTRICT_REF lock,
        Architectures::arch_id_t const arch_id ) SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::Architectures;

        return const_cast< _this_t::arch_data_base_t* >( static_cast<
            _this_t const& >( *this ).ptrArchDataBase( lock, arch_id ) );

    }

    SIXTRL_INLINE Architectures::arch_data_base_t*
    Architectures::ptrArchDataBase(
        Architectures::lock_t const& SIXTRL_RESTRICT_REF lock,
        std::string const& SIXTRL_RESTRICT_REF arch_str ) SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::Architectures;
        return const_cast< _this_t::arch_data_base_t* >( static_cast<
            _this_t const& >( *this ).ptrArchDataBase( lock,
                this->archId( lock, arch_str.c_str() ) ) );
    }

    SIXTRL_INLINE Architectures::arch_data_base_t*
    Architectures::ptrArchDataBase(
        Architectures::lock_t const& SIXTRL_RESTRICT_REF lock,
        char const* SIXTRL_RESTRICT arch_str ) SIXTRL_NOEXCEPT
    {
        using _this_t = SIXTRL_CXX_NAMESPACE::Architectures;
        return const_cast< _this_t::arch_data_base_t* >( static_cast<
            _this_t const& >( *this ).ptrArchDataBase( lock,
                this->archId( lock, arch_str ) ) );
    }

    /* ----------------------------------------------------------------- */

    SIXTRL_INLINE Architectures::size_type
    Architectures::numArchitectures() const SIXTRL_NOEXCEPT
    {
        SIXTRL_CXX_NAMESPACE::Architectures::lock_t lock( *this->lockable() );
        return this->numArchitectures( lock );
    }

    SIXTRL_INLINE Architectures::size_type Architectures::numArchitectures(
        Architectures::lock_t const& lock ) const SIXTRL_NOEXCEPT
    {
        return ( this->checkLock( lock ) )
            ? this->m_id_to_ptr_data_base.size()
            : SIXTRL_CXX_NAMESPACE::Architectures::size_type{ 0 };
    }

    /* ----------------------------------------------------------------- */

    SIXTRL_INLINE Architectures::status_t
    Architectures::addArchitecture(
        Architectures::ptr_arch_data_base_t&& ptr_arch_data )
    {
        SIXTRL_CXX_NAMESPACE::Architectures::lock_t lock( *this->lockable() );
        return this->addArchitecture( lock, std::move( ptr_arch_data ) );
    }

    SIXTRL_INLINE Architectures::status_t Architectures::addArchitecture(
        Architectures::lock_t const& SIXTRL_RESTRICT_REF lock,
        Architectures::ptr_arch_data_base_t&& ptr_arch_data )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        st::Architectures::arch_id_t const aid =
            ( ptr_arch_data.get() != nullptr )
                ? ptr_arch_data->archId() : st::ARCHITECTURE_ILLEGAL;

        return ( ( ptr_arch_data.get() != nullptr ) &&
                 ( aid != st::ARCHITECTURE_ILLEGAL ) &&
                 ( aid != st::ARCHITECTURE_NONE ) &&
                 ( this->checkLock( lock ) ) )
            ? this->doAddArchitecture( lock, aid, std::move( ptr_arch_data ) )
            : st::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* ----------------------------------------------------------------- */

    SIXTRL_INLINE bool Architectures::hasHandle(
        Architectures::arch_id_t const arch_id ) const
    {
        SIXTRL_CXX_NAMESPACE::Architectures::lock_t lock( *this->lockable() );
        return this->hasHandle( lock, arch_id );
    }

    SIXTRL_INLINE bool Architectures::isEnabled(
        Architectures::arch_id_t const arch_id ) const
    {
        SIXTRL_CXX_NAMESPACE::Architectures::lock_t lock( *this->lockable() );
        return this->isEnabled( lock, arch_id );
    }

    SIXTRL_INLINE bool Architectures::isActivated(
        Architectures::arch_id_t const arch_id ) const
    {
        SIXTRL_CXX_NAMESPACE::Architectures::lock_t lock( *this->lockable() );
        return this->isActivated( lock, arch_id );
    }

    SIXTRL_INLINE bool Architectures::isAvailable(
        Architectures::arch_id_t const arch_id ) const
    {
        SIXTRL_CXX_NAMESPACE::Architectures::lock_t lock( *this->lockable() );
        return this->isAvailable( lock, arch_id );
    }

    SIXTRL_INLINE bool Architectures::isShutdown(
        Architectures::arch_id_t const arch_id ) const
    {
        SIXTRL_CXX_NAMESPACE::Architectures::lock_t lock( *this->lockable() );
        return this->isShutdown( lock, arch_id );
    }

    SIXTRL_INLINE Architectures::init_flags_t Architectures::initFlags(
        Architectures::arch_id_t const arch_id ) const
    {
        SIXTRL_CXX_NAMESPACE::Architectures::lock_t lock( *this->lockable() );
        return this->initFlags( lock, arch_id );
    }

    /* ----------------------------------------------------------------- */

    SIXTRL_INLINE bool Architectures::hasHandle(
        Architectures::lock_t const& SIXTRL_RESTRICT_REF lock,
        arch_id_t const arch_id ) const SIXTRL_NOEXCEPT
    {
        auto ptr = this->ptrArchDataBase( lock, arch_id );
        return ( ( ptr != nullptr ) && ( ptr->hasHandle() ) );
    }

    SIXTRL_INLINE Architectures::lib_handle_t Architectures::libHandle(
        Architectures::lock_t const& SIXTRL_RESTRICT_REF lock,
        Architectures::arch_id_t const arch_id ) SIXTRL_NOEXCEPT
    {
        auto ptr = this->ptrArchDataBase( lock, arch_id );
        return ( ptr != nullptr ) ? ptr->libHandle() : nullptr;
    }

    SIXTRL_INLINE bool Architectures::isEnabled(
        Architectures::lock_t const& SIXTRL_RESTRICT_REF lock,
        Architectures::arch_id_t const arch_id ) const SIXTRL_NOEXCEPT
    {
        auto ptr = this->ptrArchDataBase( lock, arch_id );
        return ( ( ptr != nullptr ) && ( ptr->isEnabled() ) );
    }

    SIXTRL_INLINE bool Architectures::isActivated(
        Architectures::lock_t const& SIXTRL_RESTRICT_REF lock,
        Architectures::arch_id_t const arch_id ) const SIXTRL_NOEXCEPT
    {
        auto ptr = this->ptrArchDataBase( lock, arch_id );
        return ( ( ptr != nullptr ) && ( ptr->isActivated() ) );
    }

    SIXTRL_INLINE bool Architectures::isAvailable(
        Architectures::lock_t const& SIXTRL_RESTRICT_REF lock,
        Architectures::arch_id_t const arch_id ) const SIXTRL_NOEXCEPT
    {
        auto ptr = this->ptrArchDataBase( lock, arch_id );
        return ( ( ptr != nullptr ) && ( ptr->isAvailable() ) );
    }

    SIXTRL_INLINE bool Architectures::isShutdown(
        Architectures::lock_t const& SIXTRL_RESTRICT_REF lock,
        Architectures::arch_id_t const arch_id ) const SIXTRL_NOEXCEPT
    {
        auto ptr = this->ptrArchDataBase( lock, arch_id );
        return ( ( ptr != nullptr ) && ( ptr->isShutdown() ) );
    }

    SIXTRL_INLINE Architectures::init_flags_t Architectures::initFlags(
        Architectures::lock_t const& SIXTRL_RESTRICT_REF lock,
        Architectures::arch_id_t const arch_id ) const SIXTRL_NOEXCEPT
    {
        auto ptr = this->ptrArchDataBase( lock, arch_id );
        return ( ptr != nullptr )
            ? ptr->initFlags() : SIXTRL_CXX_NAMESPACE::ARCH_INIT_STATE_NONE;
    }

    SIXTRL_INLINE Architectures::status_t Architectures::initialize(
        Architectures::lock_t const& SIXTRL_RESTRICT_REF lock,
        Architectures::arch_id_t const arch_id )
    {
        auto ptr = this->ptrArchDataBase( lock, arch_id );
        return ( ptr != nullptr ) ? ptr->initialize()
            : SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    SIXTRL_INLINE Architectures::status_t Architectures::shutdown(
        Architectures::lock_t const& SIXTRL_RESTRICT_REF lock,
        Architectures::arch_id_t const arch_id )
    {
        auto ptr = this->ptrArchDataBase( lock, arch_id );
        return ( ptr != nullptr ) ? ptr->shutdown()
            : SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE Architectures::lockable_t*
    Architectures::lockable() const SIXTRL_NOEXCEPT
    {
        return &this->m_lockable;
    }

    SIXTRL_INLINE bool Architectures::checkLock( Architectures::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( ( lock.owns_lock() ) && ( lock.mutex() == this->lockable() ) );
    }
}

#endif /* C++, Host */

#endif /* SIXTRACKLIB_ARCHITECTURE_ARCHITECTURES_CXX_HPP_ */

/* end: sixtracklib/common/architecture/arch_state.hpp */
