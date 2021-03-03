#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/backends/backends.h"
    #include "sixtracklib/common/generated/modules.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <sstream>
    #include <ostream>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
    }

    bool Backends_is_enabled( st::backend_id_type const id ) SIXTRL_NOEXCEPT {
        bool is_enabled = false;

        switch( id )
        {
            case st::BACKEND_ID_CPU:
            {
                is_enabled = true;
                break;
            }

            case st::BACKEND_ID_OPENMP: { break; }

            case st::BACKEND_ID_OPENCL:
            {
                #if defined( SIXTRACKLIB_ENABLE_MODULE_OPENCL ) && \
                           ( SIXTRACKLIB_ENABLE_MODULE_OPENCL == 1 )

                is_enabled = true;
                #endif /* defined( SIXTRACKLIB_ENABLE_MODULE_OPENCL ) */
                break;
            }

            case st::BACKEND_ID_CUDA:
            {
                #if defined( SIXTRACKLIB_ENABLE_MODULE_CUDA ) && \
                           ( SIXTRACKLIB_ENABLE_MODULE_CUDA == 1 )

                is_enabled = true;
                #endif /* defined( SIXTRACKLIB_ENABLE_MODULE_CUDA ) */
                break;
            }

            case st::BACKEND_ID_HIP: { break; }
            case st::BACKEND_ID_DPCPP: { break; }
            default: { is_enabled = false; }
        };

        return is_enabled;
    }

    bool Backends_is_enabled( std::string const& SIXTRL_RESTRICT_REF bend_str )
    {
        return st::Backends_is_enabled( st::Backends_id_by_string( bend_str ) );
    }

    std::ostream& Backends_string_to_stream( std::ostream& ostr,
        SIXTRL_CXX_NAMESPACE::backend_id_type const id )
    {
        ostr << st::Backends_string_by_id( id );
        return ostr;
    }

    std::string Backends_string_by_id(
        SIXTRL_CXX_NAMESPACE::backend_id_type const id )
    {
        std::string backends_str = std::string{};

        switch( id )
        {
            case st::BACKEND_ID_CPU:
            {
                backends_str = std::string{ "cpu" };
                break;
            }

            case st::BACKEND_ID_OPENMP:
            {
                backends_str = std::string{ "openmp" };
                break;
            }

            case st::BACKEND_ID_OPENCL:
            {
                backends_str = std::string{ "opencl" };
                break;
            }

            case st::BACKEND_ID_CUDA:
            {
                backends_str = std::string{ "cuda" };
                break;
            }

            case st::BACKEND_ID_HIP:
            {
                backends_str = std::string{ "hip" };
                break;
            }

            case st::BACKEND_ID_DPCPP:
            {
                backends_str = std::string{ "dpcpp" };
                break;
            }

            default: { backends_str = std::string{}; }
        };

        return backends_str;
    }


    SIXTRL_CXX_NAMESPACE::backend_id_type Backends_id_by_string(
        std::string const& SIXTRL_RESTRICT_REF backend_str ) SIXTRL_NOEXCEPT {
        st::backend_id_type backend_id = st::BACKEND_ID_NONE;

        if( !backend_str.empty() )
        {
            if( backend_str.compare( "cpu" ) == 0 )
            {
                backend_id = st::BACKEND_ID_CPU;
            }
            else if( backend_str.compare( "openmp" ) == 0 )
            {
                backend_id = st::BACKEND_ID_OPENMP;
            }
            else if( backend_str.compare( "opencl" ) == 0 )
            {
                backend_id = st::BACKEND_ID_OPENCL;
            }
            else if( backend_str.compare( "cuda" ) == 0 )
            {
                backend_id = st::BACKEND_ID_CUDA;
            }
            else if( backend_str.compare( "hip" ) == 0 )
            {
                backend_id = st::BACKEND_ID_HIP;
            }
            else if( backend_str.compare( "dpcpp" ) == 0 )
            {
                backend_id = st::BACKEND_ID_DPCPP;
            }
        }

        return backend_id;
    }

    std::string Backends_backend_id_regex( bool const only_enabled )
    {
        std::ostringstream a2str;
        st::size_type num_used_backends = st::size_type{ 0 };
        a2str << "(";

        if( ( !only_enabled ) ||
            ( st::Backends_is_enabled( st::BACKEND_ID_CPU ) ) )
        {
            a2str << st::BACKEND_ID_CPU;
            ++num_used_backends;
        }

        if( ( !only_enabled ) ||
            ( st::Backends_is_enabled( st::BACKEND_ID_OPENMP ) ) )
        {
            if( num_used_backends > st::size_type{ 0 } ) a2str << "|";
            a2str << st::BACKEND_ID_OPENMP;
            ++num_used_backends;
        }

        if( ( !only_enabled ) ||
            ( st::Backends_is_enabled( st::BACKEND_ID_OPENCL ) ) )
        {
            if( num_used_backends > st::size_type{ 0 } ) a2str << "|";
            a2str << st::BACKEND_ID_OPENCL;
            ++num_used_backends;
        }

        if( ( !only_enabled ) ||
            ( st::Backends_is_enabled( st::BACKEND_ID_CUDA ) ) )
        {
            if( num_used_backends > st::size_type{ 0 } ) a2str << "|";
            a2str << st::BACKEND_ID_CUDA;
            ++num_used_backends;
        }

        if( ( !only_enabled ) ||
            ( st::Backends_is_enabled( st::BACKEND_ID_HIP ) ) )
        {
            if( num_used_backends > st::size_type{ 0 } ) a2str << "|";
            a2str << st::BACKEND_ID_HIP;
            ++num_used_backends;
        }

        if( ( !only_enabled ) ||
            ( st::Backends_is_enabled( st::BACKEND_ID_DPCPP ) ) )
        {
            if( num_used_backends > st::size_type{ 0 } ) a2str << "|";
            a2str << st::BACKEND_ID_DPCPP;
            ++num_used_backends;
        }

        if( num_used_backends > st::size_type{ 0 } )
        {
            a2str << ")";
        }
        else
        {
            a2str.str( "" );
        }

        return a2str.str();
    }

    std::string Backends_backend_str_regex( bool const only_enabled )
    {
        std::ostringstream a2str;
        st::size_type num_used_backends = st::size_type{ 0 };
        std::string temp;
        temp.reserve( 64 );

        a2str << "(";

        if( ( !only_enabled ) ||
            ( st::Backends_is_enabled( st::BACKEND_ID_CPU ) ) )
        {
            temp = st::Backends_string_by_id( st::BACKEND_ID_CPU );
            if( !temp.empty() ) { a2str << temp; ++num_used_backends; }
        }

        if( ( !only_enabled ) ||
            ( st::Backends_is_enabled( st::BACKEND_ID_OPENMP ) ) )
        {
            if( num_used_backends > st::size_type{ 0 } ) a2str << "|";
            temp = st::Backends_string_by_id( st::BACKEND_ID_OPENMP );
            if( !temp.empty() ) { a2str << temp; ++num_used_backends; }
        }

        if( ( !only_enabled ) ||
            ( st::Backends_is_enabled( st::BACKEND_ID_OPENCL ) ) )
        {
            if( num_used_backends > st::size_type{ 0 } ) a2str << "|";
            temp = st::Backends_string_by_id( st::BACKEND_ID_OPENCL );
            if( !temp.empty() ) { a2str << temp; ++num_used_backends; }
        }

        if( ( !only_enabled ) ||
            ( st::Backends_is_enabled( st::BACKEND_ID_CUDA ) ) )
        {
            if( num_used_backends > st::size_type{ 0 } ) a2str << "|";
            temp = st::Backends_string_by_id( st::BACKEND_ID_CUDA );
            if( !temp.empty() ) { a2str << temp; ++num_used_backends; }
        }

        if( ( !only_enabled ) ||
            ( st::Backends_is_enabled( st::BACKEND_ID_HIP ) ) )
        {
            if( num_used_backends > st::size_type{ 0 } ) a2str << "|";
            temp = st::Backends_string_by_id( st::BACKEND_ID_HIP );
            if( !temp.empty() ) { a2str << temp; ++num_used_backends; }
        }

        if( ( !only_enabled ) ||
            ( st::Backends_is_enabled( st::BACKEND_ID_DPCPP ) ) )
        {
            if( num_used_backends > st::size_type{ 0 } ) a2str << "|";
            temp = st::Backends_string_by_id( st::BACKEND_ID_DPCPP );
            if( !temp.empty() ) { a2str << temp; ++num_used_backends; }
        }

        if( num_used_backends > st::size_type{ 0 } )
        {
            a2str << ")";
        }
        else
        {
            a2str.str( "" );
        }

        return a2str.str();
    }

} /* end: namespace SIXTRL_CXX_NAMESPACE */

bool NS(Backends_is_enabled_by_string)(
    char const* SIXTRL_RESTRICT backend_str ) SIXTRL_NOEXCEPT {
    return SIXTRL_CXX_NAMESPACE::Backends_is_enabled( backend_str ); }

bool NS(Backends_is_enabled)( ::NS(backend_id_type) const id ) SIXTRL_NOEXCEPT {
    return SIXTRL_CXX_NAMESPACE::Backends_is_enabled( id ); }

::NS(status_type) NS(Backends_string_by_id)(
    char* SIXTRL_RESTRICT backend_str,
    ::NS(size_type) const backend_str_capacity,
    ::NS(backend_id_type) const id ) SIXTRL_NOEXCEPT
{
    typedef ::NS(status_type) st_status_t;
    st_status_t status = ::NS(STATUS_GENERAL_FAILURE);
    std::string const temp = SIXTRL_CXX_NAMESPACE::Backends_string_by_id( id );
    if( ( backend_str != nullptr ) && ( !temp.empty() ) &&
        ( backend_str_capacity > temp.size() ) )
    {
        std::strncat( backend_str, temp.c_str(), backend_str_capacity );
        status = ::NS(STATUS_SUCCESS);
    }

    return status;
}

::NS(backend_id_type) NS(Backends_id_by_string)(
    char const* SIXTRL_RESTRICT backend_str ) SIXTRL_NOEXCEPT {
    return ( ( backend_str != nullptr ) && ( std::strlen( backend_str ) > 0u ) )
        ? SIXTRL_CXX_NAMESPACE::Backends_id_by_string(
            std::string{ backend_str } )
        : SIXTRL_CXX_NAMESPACE::BACKEND_ID_NONE;
}

#endif /* C++, Host */
