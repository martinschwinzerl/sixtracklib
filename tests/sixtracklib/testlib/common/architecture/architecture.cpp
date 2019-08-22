#include "sixtracklib/testlib/common/architecture/architecture.hpp"

#include <cstddef>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <sstream>

namespace SIXTRL_CXX_NAMESPACE
{
    namespace tests
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        st::arch_init_flags_t Arch_dummy_init_fn( st::arch_id_t const arch_id,
            st::ArchData* SIXTRL_RESTRICT ptr_arch_data )
        {
            st::arch_init_flags_t flags = st::ARCH_INIT_STATE_NONE;
            ( void )ptr_arch_data;

            if( ( arch_id != st::ARCHITECTURE_CPU ) &&
                ( arch_id != st::ARCHITECTURE_OPENCL ) &&
                ( arch_id != st::ARCHITECTURE_CUDA ) )
            {
                flags = st::ARCH_INIT_STATE_AVAILABLE;
            }

            return flags;
        }

        st::arch_status_t Architectures_setup(
            st::Architectures& SIXTRL_RESTRICT_REF archs,
            st::arch_size_t const num_architectures,
            st::arch_id_t const start_arch_id,
            st::arch_id_t* SIXTRL_RESTRICT arch_ids )
        {
            using size_t      = st::arch_size_t;
            using arch_id_t   = st::arch_id_t;
            using arch_data_t = st::ArchData;
            using ptr_arch_data_t = std::unique_ptr< arch_data_t >;

            st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

            if( ( num_architectures > size_t{ 0 } ) &&
                ( arch_ids != nullptr ) &&
                ( start_arch_id != st::ARCHITECTURE_ILLEGAL ) &&
                ( start_arch_id != st::ARCHITECTURE_NONE ) &&
                ( ( start_arch_id + num_architectures ) <
                    st::ARCHITECTURE_ILLEGAL ) )
            {
                arch_id_t arch_id = start_arch_id;
                std::ostringstream a2str;
                std::fill( arch_ids, arch_ids + num_architectures,
                           st::ARCHITECTURE_ILLEGAL );

                status = st::ARCH_STATUS_SUCCESS;

                for( size_t ii = size_t{ 0 } ; ii < num_architectures ;
                    ++ii, ++arch_id )
                {
                    if( !archs.hasArchitecture( arch_id ) )
                    {
                        a2str << "dummy arch "  << std::setfill( '0' )
                              << std::setw( 2 ) << ii;

                        std::string const arch_str( a2str.str() );
                        a2str.str( "" );

                        ptr_arch_data_t dummy_arch_data( new arch_data_t( arch_id,
                            arch_str, st::ARCH_INIT_STATE_ENABLED,
                                &st::tests::Arch_dummy_init_fn ) );

                        status = archs.addArchitecture(
                            std::move( dummy_arch_data ) );
                    }

                    if( ( st::ARCH_STATUS_SUCCESS == status ) &&
                        ( archs.hasArchitecture( arch_id ) ) )
                    {
                        arch_ids[ ii ] = arch_id;
                    }
                    else
                    {
                        status = st::ARCH_STATUS_GENERAL_FAILURE;
                        break;
                    }
                }
            }

            return status;
        }
    }
}

/* end: tests/sixtracklib/testlib/common/architecture/architecture.cpp */
