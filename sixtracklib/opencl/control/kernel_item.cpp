#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/opencl/control/kernel_item.h"
    #include "sixtracklib/opencl/control/program_store.h"
    #include "sixtracklib/opencl/control/program_item.h"
    #include "sixtracklib/opencl/internal/helpers.h"
#endif /* !defined( SIXTRL_NO_INCLUDES )  */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
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
        using prog_store_type        = st::OclProgramStore;
        using key_type               = st::OclKernelKey;
        using item_type              = st::OclKernelItem;
        using prog_key_type          = st::OclProgramKey;
        using st_status_t            = item_type::status_type;
        using st_size_t              = item_type::size_type;
        using st_prog_id_t           = item_type::program_id_type;
        using ocl_base_prg_item_type = prog_store_type::ocl_program_item_type;
    }

    constexpr key_type::program_id_type key_type::ILLEGAL_PROGRAM_ID;

    constexpr item_type::class_id_type item_type::BASE_CLASS_ID;
    constexpr item_type::class_id_type item_type::CLASS_ID;

    constexpr item_type::backend_id_type
    st::BackendObjTraits< item_type >::BACKEND_ID;

    constexpr item_type::class_id_type
    st::BackendObjTraits< item_type >::BASE_CLASS_ID;

    constexpr item_type::class_id_type
    st::BackendObjTraits< item_type >::DERIVED_CLASS_ID;

    /* --------------------------------------------------------------------- */

    st_status_t item_type::init(
        prog_store_type const& SIXTRL_RESTRICT_REF program_store,
        st_prog_id_t const prog_id,
        std::string const& SIXTRL_RESTRICT_REF kernel_name,
        std::string const& SIXTRL_RESTRICT_REF kernel_options )
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( kernel_name.empty() ) ||
            ( prog_id == key_type::ILLEGAL_PROGRAM_ID ) )
        {
            return status;
        }

        if( ( program_store.num_stored_items() > st_size_t{ 0 } ) &&
            ( program_store.is_stored( prog_id ) ) )
        {
            auto prog_item = program_store.program_item( prog_id );
            if( prog_item != nullptr )
            {
                status = this->init(
                    *prog_item, prog_id, kernel_name, kernel_options );
            }
        }

        return status;
    }

    st_status_t item_type::init(
        ocl_base_prg_item_type const& SIXTRL_RESTRICT_REF program_item,
        st_prog_id_t const prog_id,
        std::string const& SIXTRL_RESTRICT_REF kernel_name,
        std::string const& SIXTRL_RESTRICT_REF kernel_options )
    {
        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( !kernel_name.empty() ) &&
            ( prog_id != key_type::ILLEGAL_PROGRAM_ID ) &&
            ( program_item.key().is_legal() ) )
        {
            bool has_kernel = false;

            st_size_t const n_kernels = program_item.num_kernels();
            for( st_size_t ii = st_size_t{ 0 } ;  ii < n_kernels ; ++ii )
            {
                if( kernel_name.compare( program_item.kernel_name( ii ) ) == 0 )
                {
                    has_kernel = true;
                    break;
                }
            }

            if( !has_kernel ) return status;
            ::cl_int ret = CL_SUCCESS;

            #if defined( CL_HPP_ENABLE_EXCEPTIONS )
            try
            #endif /* defined( CL_HPP_ENABLE_EXCEPTIONS ) */
            {
                cl::Kernel k( program_item.cl_program(), kernel_name.c_str(),
                                &ret );
                if( ret == CL_SUCCESS ) this->m_cl_kernel = std::move( k );
            }
            #if defined( CL_HPP_ENABLE_EXCEPTIONS )
            catch( cl::Error& e )
            {
                st::OpenCL_ret_value_to_exception< std::runtime_error >(
                    e.err(), "OclKernelItem", "init", e.what(),
                        st_size_t{ __LINE__ } );
            }
            #else  /* !defined( CL_HPP_ENABLE_EXCEPTIONS ) */
            if( ret != CL_SUCCESS )
            {
                st::OpenCL_ret_value_to_exception< std::runtime_error >(
                    ret, "OclKernelItem", "init",
                        "unable to create cl::Kernel from program",
                            st_size_t{ __LINE__ } );
                return status;
            }
            #endif /* defined( CL_HPP_ENABLE_EXCEPTIONS ) */

            SIXTRL_ASSERT( ret == CL_SUCCESS );
            st_size_t num_kernel_args = st_size_t{ 0 };

            #if defined( CL_HPP_ENABLE_EXCEPTIONS )
            try
            #endif /* defined( CL_HPP_ENABLE_EXCEPTIONS ) */
            {
                ::cl_uint temp_num_kernel_args = ::cl_uint{ 0 };
                ret = this->m_cl_kernel.getInfo( CL_KERNEL_NUM_ARGS,
                    &temp_num_kernel_args );

                if( ret == CL_SUCCESS )
                {
                    num_kernel_args = temp_num_kernel_args;
                    status = st::STATUS_SUCCESS;
                }
            }
            #if defined( CL_HPP_ENABLE_EXCEPTIONS )
            catch( cl::Error& e )
            {
                st::OpenCL_ret_value_to_exception< std::runtime_error >(
                    e.err(), "OclKernelItem", "init", e.what(),
                        st_size_t{ __LINE__ } );
            }
            #else  /* !defined( CL_HPP_ENABLE_EXCEPTIONS ) */
            if( ret != CL_SUCCESS )
            {
                st::OpenCL_ret_value_to_exception< std::runtime_error >(
                    ret, "OclKernelItem", "init",
                    "Unable to retrieve number of kernel args "
                        "from kernel object", st_size_t{ __LINE__ } );

                return status;
            }
            #endif /* OpenCL 1.x C++ Host Exceptions enabled */

            if( status == st::STATUS_SUCCESS )
            {
                this->m_num_kernel_args = num_kernel_args;
                this->_update_kernel_key(
                    prog_id, kernel_name, kernel_options );
            }
        }

        return status;
    }
}
#endif /* C++, Host */
