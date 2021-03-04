#ifndef SIXTRACKLIB_OPENCL_CONTROL_KERNEL_ITEM_H__
#define SIXTRACKLIB_OPENCL_CONTROL_KERNEL_ITEM_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/opencl/definitions.h"
    #include "sixtracklib/opencl/control/program_item.h"
    #include "sixtracklib/opencl/control/program_store.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES ) && defined( __cplusplus )
    #include "sixtracklib/opencl/opencl.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) && defined( __cplusplus ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus )
    #include <string>
    #include <vector>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    struct OclKernelKey
    {
        using program_id_type = SIXTRL_CXX_NAMESPACE::ctrl_program_id_type;
        using cmp_result_type = ::NS(cmp_result_type);

        static constexpr program_id_type ILLEGAL_PROGRAM_ID =
            SIXTRL_CXX_NAMESPACE::OclProgramStore::ILLEGAL_PROGRAM_ID;

        SIXTRL_HOST_FN bool is_legal() const SIXTRL_NOEXCEPT {
            return ( ( this->program_id != ILLEGAL_PROGRAM_ID ) &&
                     ( !this->name.empty() ) );
        }

        SIXTRL_HOST_FN cmp_result_type compare(
            OclKernelKey const& SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT
        {
            cmp_result_type ret = ( this->program_id == rhs.program_id )
                ? cmp_result_type{ 0 }
                : ( ( this->program_id > rhs.program_id )
                    ? cmp_result_type{ 1 } : cmp_result_type{ -1 } );

            if( ret == 0 )
            {
                if( !this->name.empty() )
                {
                    if( this->name.size() == rhs.name.size() )
                    {
                        ret = this->name.compare( rhs.name );
                    }
                    else
                    {
                        ret = ( this->name.size() > rhs.name.size() )
                            ? cmp_result_type{ 1 } : cmp_result_type{ -1 };
                    }
                }
                else if( !rhs.name.empty() )
                {
                    ret = cmp_result_type{ -1 };
                }
            }

            if( ret == 0 )
            {
                if( !this->options.empty() )
                {
                    if( this->options.size() == rhs.options.size() )
                    {
                        ret = this->options.compare( rhs.options );
                    }
                    else
                    {
                        ret = ( this->options.size() > rhs.options.size() )
                            ? cmp_result_type{ 1 } : cmp_result_type{ -1 };
                    }
                }
                else if( !rhs.options.empty() )
                {
                    ret = cmp_result_type{ -1 };
                }
            }

            return ret;
        }

        SIXTRL_HOST_FN bool operator<(
            OclKernelKey const& SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT
        {
            return ( this->compare( rhs ) < cmp_result_type{ 0 } );
        }

        SIXTRL_HOST_FN bool operator==(
            OclKernelKey const& SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT
        {
            return ( this->compare( rhs ) == cmp_result_type{ 0 } );
        }

        SIXTRL_HOST_FN bool operator!=(
            OclKernelKey const& SIXTRL_RESTRICT_REF rhs ) const SIXTRL_NOEXCEPT
        {
            return ( this->compare( rhs ) != cmp_result_type{ 0 } );
        }

        std::string name = std::string{};
        std::string options = std::string{};
        program_id_type program_id = ILLEGAL_PROGRAM_ID;
    };

    class OclKernelItem : public SIXTRL_CXX_NAMESPACE::BackendObjBase
    {
        public:

        using key_type           = SIXTRL_CXX_NAMESPACE::OclKernelKey;
        using program_id_type    = key_type::program_id_type;
        using program_key_type   = SIXTRL_CXX_NAMESPACE::OclProgramKey;
        using program_store_type = SIXTRL_CXX_NAMESPACE::OclProgramStore;
        using program_item_type  = SIXTRL_CXX_NAMESPACE::OclProgramItemBase;

        static constexpr class_id_type BASE_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::OPENCL_KERNEL_ITEM_CLASS_ID;

        static constexpr class_id_type CLASS_ID =
            SIXTRL_CXX_NAMESPACE::OPENCL_KERNEL_ITEM_CLASS_ID;

        SIXTRL_HOST_FN OclKernelItem() :
            BackendObjBase( SIXTRL_CXX_NAMESPACE::BACKEND_ID_OPENCL,
                BASE_CLASS_ID, CLASS_ID ),
            m_kernel_key(), m_cl_kernel()
        {
        }

        SIXTRL_HOST_FN OclKernelItem(
            program_store_type const& SIXTRL_RESTRICT_REF program_store,
            program_id_type const prog_id,
            std::string const& SIXTRL_RESTRICT_REF kernel_name,
            std::string const& SIXTRL_RESTRICT_REF kernel_options = std::string{} ) :
            BackendObjBase( SIXTRL_CXX_NAMESPACE::BACKEND_ID_OPENCL,
                BASE_CLASS_ID, CLASS_ID ),
            m_kernel_key(), m_cl_kernel()
        {
            status_type const status = this->init( program_store, prog_id,
                kernel_name, kernel_options );

            if( status != SIXTRL_CXX_NAMESPACE::STATUS_SUCCESS )
            {
                throw std::runtime_error( "Unable to create kernel item from "
                    "supplied prog_id and kernel name" );
            }
        }

        SIXTRL_HOST_FN OclKernelItem(
            program_store_type const& SIXTRL_RESTRICT_REF program_store,
            program_key_type const& SIXTRL_RESTRICT_REF prog_key,
            std::string const& SIXTRL_RESTRICT_REF kernel_name,
            std::string const& SIXTRL_RESTRICT_REF kernel_options = std::string{} ) :
            BackendObjBase( SIXTRL_CXX_NAMESPACE::BACKEND_ID_OPENCL,
                BASE_CLASS_ID, CLASS_ID ),
            m_kernel_key(), m_cl_kernel()
        {
            status_type const status = this->init( program_store, prog_key,
                kernel_name, kernel_options );

            if( status != SIXTRL_CXX_NAMESPACE::STATUS_SUCCESS )
            {
                throw std::runtime_error( "Unable to create kernel item from "
                    "supplied prog_key and kernel name" );
            }
        }

        SIXTRL_HOST_FN OclKernelItem(
            program_item_type const& SIXTRL_RESTRICT_REF program_item,
            program_id_type const prog_id,
            std::string const& SIXTRL_RESTRICT_REF kernel_name,
            std::string const& SIXTRL_RESTRICT_REF kernel_options = std::string{} ) :
            BackendObjBase( SIXTRL_CXX_NAMESPACE::BACKEND_ID_OPENCL,
                BASE_CLASS_ID, CLASS_ID ),
            m_kernel_key(), m_cl_kernel()
        {
            status_type const status = this->init(
                program_item, prog_id, kernel_name, kernel_options );

            if( status != SIXTRL_CXX_NAMESPACE::STATUS_SUCCESS )
            {
                throw std::runtime_error( "Unable to create kernel item from "
                    "supplied program item and kernel name" );
            }
        }

        SIXTRL_HOST_FN OclKernelItem( OclKernelItem const& ) = default;
        SIXTRL_HOST_FN OclKernelItem( OclKernelItem&& ) = default;

        SIXTRL_HOST_FN OclKernelItem& operator=( OclKernelItem const& ) = default;
        SIXTRL_HOST_FN OclKernelItem& operator=( OclKernelItem&& ) = default;

        SIXTRL_HOST_FN virtual ~OclKernelItem() = default;

        SIXTRL_HOST_FN status_type init(
            program_store_type const& SIXTRL_RESTRICT_REF program_store,
            program_id_type const prog_id,
            std::string const& SIXTRL_RESTRICT_REF kernel_name,
            std::string const& SIXTRL_RESTRICT_REF kernel_options =
                std::string{} );

        SIXTRL_HOST_FN status_type init(
            program_store_type const& SIXTRL_RESTRICT_REF program_store,
            program_key_type const& prog_key,
            std::string const& SIXTRL_RESTRICT_REF kernel_name,
            std::string const& SIXTRL_RESTRICT_REF kernel_options =
                std::string{} )
        {
            return this->init( program_store,
                program_store.program_id( prog_key ), kernel_name,
                    kernel_options );
        }

        SIXTRL_HOST_FN status_type init(
            program_item_type const& SIXTRL_RESTRICT_REF program_item,
            program_id_type const prog_id,
            std::string const& SIXTRL_RESTRICT_REF kernel_name,
            std::string const& SIXTRL_RESTRICT_REF kernel_options =
                std::string{} );

        SIXTRL_HOST_FN key_type const& key() const SIXTRL_NOEXCEPT {
            return this->m_kernel_key; }

        SIXTRL_HOST_FN cl::Kernel& cl_kernel() SIXTRL_NOEXCEPT {
            return this->m_cl_kernel; }

        SIXTRL_HOST_FN cl::Kernel const& cl_kernel() const SIXTRL_NOEXCEPT {
            return this->m_cl_kernel; }

        SIXTRL_HOST_FN size_type num_kernel_args() const SIXTRL_NOEXCEPT {
            return this->m_num_kernel_args; }

        private:

        SIXTRL_HOST_FN void _update_kernel_key(
            program_id_type const program_id,
            std::string const& SIXTRL_RESTRICT_REF kernel_name,
            std::string const& SIXTRL_RESTRICT_REF kernel_options )
        {
            this->m_kernel_key.program_id = program_id;
            this->m_kernel_key.name = kernel_name;
            this->m_kernel_key.options = kernel_options;
        }

        OclKernelKey m_kernel_key;
        cl::Kernel   m_cl_kernel;
        size_type    m_num_kernel_args = size_type{ 0 };
    };

    template<> struct BackendObjTraits< SIXTRL_CXX_NAMESPACE::OclKernelItem >
    {
        static constexpr backend_id_type BACKEND_ID =
            SIXTRL_CXX_NAMESPACE::BACKEND_ID_OPENCL;

        static constexpr derived_class_id_type BASE_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::OclKernelItem::BASE_CLASS_ID;

        static constexpr derived_class_id_type DERIVED_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::OclKernelItem::CLASS_ID;
    };

    template<> struct BackendObjInvTraits<
        SIXTRL_CXX_NAMESPACE::BACKEND_ID_OPENCL,
        SIXTRL_CXX_NAMESPACE::OPENCL_KERNEL_ITEM_CLASS_ID >
    {
        typedef SIXTRL_CXX_NAMESPACE::OclKernelItem backend_obj_type;
    };
}
#endif /* C++, Host */

#endif /* SIXTRACKLIB_OPENCL_CONTROL_KERNEL_ITEM_H__ */
