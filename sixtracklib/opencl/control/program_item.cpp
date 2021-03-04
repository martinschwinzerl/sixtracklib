#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/opencl/control/node_info.h"
    #include "sixtracklib/opencl/control/controller.h"
    #include "sixtracklib/opencl/internal/helpers.h"
#endif /* !defined( SIXTRL_NO_INCLUDES )  */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <fstream>
    #include <iostream>
    #include <regex>
    #include <string>
    #include <stdexcept>
    #include <sstream>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES )  */

#if !defined( _GPUCODE ) && defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using rtc_prog_type  = st::OclRtcProgramItem;
        using base_prog_type = st::OclProgramItemBase;
        using st_status_t    = rtc_prog_type::status_type;
        using st_size_t      = rtc_prog_type::size_type;
    }

    constexpr rtc_prog_type::class_id_type rtc_prog_type::CLASS_ID;

    constexpr rtc_prog_type::backend_id_type
    st::BackendObjTraits< rtc_prog_type >::BACKEND_ID;

    constexpr rtc_prog_type::class_id_type
    st::BackendObjTraits< rtc_prog_type >::BASE_CLASS_ID;

    constexpr rtc_prog_type::class_id_type
    st::BackendObjTraits< rtc_prog_type >::DERIVED_CLASS_ID;

    /* --------------------------------------------------------------------- */

    void base_prog_type::do_clear()
    {
        cl::Program dummy;
        this->m_cl_program = std::move( dummy );
        this->m_kernel_names.clear();
        this->m_program_key.clear();
    }

    st_status_t base_prog_type::do_update_program_key(
        base_prog_type::context_type const& SIXTRL_RESTRICT_REF context,
        std::string const& SIXTRL_RESTRICT_REF name,
        std::string const& SIXTRL_RESTRICT_REF options )
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( context.key().is_legal() )
        {
            this->m_program_key.ctx_key = context.key();
            this->m_program_key.name    = name;
            this->m_program_key.options = options;
            status = st::STATUS_SUCCESS;
        }

        return status;
    }

    st_status_t base_prog_type::do_parse_kernel_names()
    {
        st_status_t status = st::STATUS_SUCCESS;

        ::size_t temp_num_kernels = ::size_t{ 0 };
        std::string temp_kernel_names;

        ::cl_int ret = this->m_cl_program.getInfo(
            CL_PROGRAM_NUM_KERNELS, &temp_num_kernels );

        if( ( ret == CL_SUCCESS ) && ( temp_num_kernels > st_size_t{ 0 } ) )
        {
            ret = this->m_cl_program.getInfo(
                CL_PROGRAM_KERNEL_NAMES, &temp_kernel_names );
        }

        if( ( ret == CL_SUCCESS ) && ( !temp_kernel_names.empty() ) )
        {
            std::regex const regex_str( "\\s*;\\s*" );
            this->m_kernel_names.assign(
                std::sregex_token_iterator(
                    temp_kernel_names.begin(), temp_kernel_names.end(),
                        regex_str, -1 ),
                std::sregex_token_iterator() );
        }

        if( ret != CL_SUCCESS ) status = st::STATUS_GENERAL_FAILURE;

        return status;
    }

    /* --------------------------------------------------------------------- */

    void rtc_prog_type::do_clear()
    {
        base_prog_type::do_clear();
        this->m_source_code.clear();
        this->m_path_to_file.clear();
        this->m_compile_flags.clear();

        this->m_build_log.clear();
        this->m_is_compiled = false;
    }

    st_status_t rtc_prog_type::create_from_source(
        st::OclContext const& SIXTRL_RESTRICT_REF ctx,
        std::string const& SIXTRL_RESTRICT_REF source_code )
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( !source_code.empty() )
        {
            ::cl_int ret = CL_SUCCESS;
            cl::Program prog( ctx.cl_context(), source_code, false, &ret );

            if( ret == CL_SUCCESS )
            {
                this->cl_program() = std::move( prog );
                this->m_source_code = source_code;
                status = st::STATUS_SUCCESS;
            }
            else
            {
                st::OpenCL_ret_value_to_exception< std::runtime_error >(
                    ret, "OclRtcProgramItem", "create_from_source" );
            }
        }

        return status;
    }

    st_status_t rtc_prog_type::create_from_source_file(
        st::OclContext const& SIXTRL_RESTRICT_REF ctx,
        std::string const& SIXTRL_RESTRICT_REF path_to_file )
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( !path_to_file.empty() )
        {
            this->m_path_to_file = path_to_file;

            std::ifstream in_file( path_to_file.c_str() );
            if( !in_file.is_open() ) return status;
            std::ostringstream a2str;
            a2str << in_file.rdbuf();
            status = this->create_from_source( ctx, a2str.str() );
        }

        return status;
    }

    void rtc_prog_type::set_compile_flags(
        std::string const& SIXTRL_RESTRICT_REF compile_flags )
    {
        this->m_compile_flags = compile_flags;
    }

    st_status_t rtc_prog_type::build(
        st::OclContext const& SIXTRL_RESTRICT_REF ctx,
        std::string const& SIXTRL_RESTRICT_REF program_name,
        std::string const& SIXTRL_RESTRICT_REF program_option )
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( !this->m_source_code.empty() ) && ( ctx.key().is_legal() ) )
        {
            ::cl_int ret = CL_SUCCESS;
            this->m_build_log.clear();

            #if defined( SIXTRL_OPENCL_ENABLES_EXCEPTION_FLAG ) && \
                         SIXTRL_OPENCL_ENABLES_EXCEPTION_FLAG == 1
            try
            {
            #endif /* OpenCL 1.x C++ Host Exceptions enabled */

                ret = this->cl_program().build( this->m_compile_flags.c_str() );

            #if defined( SIXTRL_OPENCL_ENABLES_EXCEPTION_FLAG ) && \
                         SIXTRL_OPENCL_ENABLES_EXCEPTION_FLAG == 1
            }
            catch( cl::Error& e )
            {
                std::ostringstream a2str;
                auto const& key = ctx.key();
                st_size_t const num_devices = key.num_devices;

                for( st_size_t ii = st_size_t{ 0 } ; ii < num_devices ; ++ii )
                {
                    status |= this->_build_report_to_stream(
                        a2str, key.platform_id, key.device_ids[ ii ],
                            ctx.cl_devices()[ ii ] );
                    this->m_build_log.push_back( a2str.str() );
                    a2str.str( "" );
                }

                #if defined( SIXTRL_OPENCL_PRINT_BUILD_REPORT ) && \
                           ( SIXTRL_OPENCL_PRINT_BUILD_REPORT == 1 )
                for( auto const& log : this->m_build_log )
                {
                    std::cerr << log << std::endl;
                }
                #endif /* SIXTRL_OPENCL_PRINT_BUILD_REPORT */

                throw e;
            }
            #endif /* OpenCL 1.x C++ Host Exceptions enabled */

            if( ret == CL_SUCCESS ) status = st::STATUS_SUCCESS;

            auto const& key = ctx.key();
            st_size_t const num_devices = key.num_devices;

            std::ostringstream a2str;

            for( st_size_t ii = st_size_t{ 0 } ; ii < num_devices ; ++ii )
            {
                status |= this->_build_report_to_stream(
                    a2str, key.platform_id, key.device_ids[ ii ],
                        ctx.cl_devices()[ ii ] );
                this->m_build_log.push_back( a2str.str() );
                a2str.str( "" );
            }
            #if defined( SIXTRL_OPENCL_PRINT_BUILD_REPORT ) && \
                        ( SIXTRL_OPENCL_PRINT_BUILD_REPORT == 1 )
            if( status != st::STATUS_SUCCESS )
            {
                for( auto const& log : this->m_build_log )
                {
                    std::cerr << log << std::endl;
                }
            }
            #endif /* SIXTRL_OPENCL_PRINT_BUILD_REPORT */

            if( status == st::STATUS_SUCCESS )
            {
                status = this->do_parse_kernel_names();
            }

            if( status == st::STATUS_SUCCESS )
            {
                if( !program_name.empty() )
                {
                    status = this->do_update_program_key(
                        ctx, program_name, program_option );
                }
                else if( !this->m_path_to_file.empty() )
                {
                    status = this->do_update_program_key(
                        ctx, this->m_path_to_file, program_option );
                }
                else
                {
                    status = st::STATUS_GENERAL_FAILURE;
                }
            }

            this->m_is_compiled = ( status == st::STATUS_SUCCESS );
        }

        return status;
    }

    st_size_type rtc_prog_type::num_devices() const {
        st_size_t num_devices = st_size_t{ 0 };
        ::cl_uint temp_num_devices = ::cl_uint{ 0 };

        ::cl_int ret = this->cl_program().getInfo(
            CL_PROGRAM_NUM_DEVICES, &temp_num_devices );

        if( ret == CL_SUCCESS )
        {
            num_devices = temp_num_devices;
        }
        else
        {
            if( ret == CL_INVALID_VALUE )
            {
                throw std::runtime_error( "OclRtcProgramItem::num_devices: "
                    "CL_INVALID_VALUE" );
            }
            else if( ret == CL_INVALID_PROGRAM )
            {
                throw std::runtime_error( "OclRtcProgramItem::num_devices: "
                    "CL_INVALID_PROGRAM" );
            }
            else if( ret == CL_INVALID_PROGRAM_EXECUTABLE )
            {
                throw std::runtime_error( "OclRtcProgramItem::num_devices: "
                    "CL_INVALID_PROGRAM_EXECUTABLE" );
            }
            else if( ret == CL_OUT_OF_RESOURCES )
            {
                throw std::runtime_error( "OclRtcProgramItem::num_devices: "
                    "CL_OUT_OF_RESOURCES" );
            }
            else
            {
                SIXTRL_ASSERT( ret == CL_OUT_OF_HOST_MEMORY );
                throw std::runtime_error( "OclRtcProgramItem::num_devices: "
                    "CL_OUT_OF_HOST_MEMORY" );
            }
        }

        return num_devices;
    }

    std::string rtc_prog_type::build_log() const {
        std::ostringstream a2str;
        for( auto const& log : this->m_build_log )
        {
            a2str << log << "\r\n" << "\r\n";
        }

        return a2str.str();
    }

    std::string const& rtc_prog_type::build_log(
        st_size_t const device_idx ) const
    {
        if( device_idx >= this->m_build_log.size() )
        {
            throw std::runtime_error( "OclRtcProgramItem::build_log: "
                "device_idx > build_log.size()" );
        }

        return this->m_build_log[ device_idx ];
    }

    st_status_t rtc_prog_type::_build_report_to_stream(
        std::ostream& SIXTRL_RESTRICT_REF ostr,
        rtc_prog_type::platform_id_type const platform_id,
        rtc_prog_type::device_id_type const device_id,
        cl::Device const& SIXTRL_RESTRICT_REF build_device )
    {
        rtc_prog_type::node_id_type node_id( platform_id, device_id );
        ostr << "build device      : ";
        st::status_type status = node_id.to_stream( ostr,
            st::NODE_ID_STR_FORMAT_BACKEND_STR, st::BACKEND_ID_OPENCL );
        ostr << "\r\n";

        ::cl_build_status build_status = CL_BUILD_NONE;
        ::cl_int ret = this->cl_program().getBuildInfo(
            build_device, CL_PROGRAM_BUILD_STATUS, &build_status );

        if( CL_SUCCESS == ret )
        {
            ostr << "build_status      : ";
            switch( build_status )
            {
                case CL_BUILD_SUCCESS: { ostr << "SUCCESS\r\n"; break; }
                case CL_BUILD_ERROR:   { ostr << "ERROR\r\n"; break; }
                case CL_BUILD_IN_PROGRESS: { ostr << "IN PROGRESS\r\n"; break; }
                default: { ostr << "NONE\r\n"; }
            };
        }
        else
        {
           status = st::STATUS_GENERAL_FAILURE;
        }

        if( CL_SUCCESS == ret )
        {
            std::string build_log_str;
            ret = this->cl_program().getBuildInfo(
                build_device, CL_PROGRAM_BUILD_LOG, &build_log_str );

            if( ( ret == CL_SUCCESS ) && ( !build_log_str.empty() ) )
            {
                ostr << "build log         :\r\n" << build_log_str << "\r\n";
            }
        }
        else
        {
            status = st::STATUS_GENERAL_FAILURE;
        }

        return status;
    }

    /* ********************************************************************* */

} /* end: namespace SIXTRL_CXX_NAMESPACE */
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */
