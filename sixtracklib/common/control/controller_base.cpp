#include "sixtracklib/common/control/controller_base.hpp"

#if defined( __cplusplus ) && !defined( _GPUCODE ) && !defined( __CUDA_ARCH__ )

#include <cstddef>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <limits>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <memory>
#include <vector>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/generated/namespace.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/control/arch_info.hpp"
#include "sixtracklib/common/control/arch_base.hpp"
#include "sixtracklib/common/control/argument_base.hpp"
#include "sixtracklib/common/buffer/managed_buffer_remap.h"
#include "sixtracklib/common/buffer.hpp"
#include "sixtracklib/common/buffer.h"

namespace st = SIXTRL_CXX_NAMESPACE;

namespace SIXTRL_CXX_NAMESPACE
{
    bool ControllerBase::usesNodes() const SIXTRL_NOEXCEPT
    {
        return this->m_uses_nodes;
    }

    void ControllerBase::clear()
    {
        this->doClear();
    }

    /* --------------------------------------------------------------------- */

    bool ControllerBase::hasName() const SIXTRL_NOEXCEPT
    {
        return ( !this->m_name.empty() );
    }

    std::string const& ControllerBase::name() const SIXTRL_NOEXCEPT
    {
        return this->m_name;
    }

    char const* ControllerBase::ptrNameStr() const SIXTRL_NOEXCEPT
    {
        return ( this->hasName() ) ? this->m_name.c_str() : nullptr;
    }

    void ControllerBase::setName( std::string const& SIXTRL_RESTRICT_REF name )
    {
        this->setName( name.c_str() );
    }

    void ControllerBase::setName( char const* SIXTRL_RESTRICT name )
    {
        if( ( name != nullptr ) &&
            ( std::strlen( name) > ControllerBase::size_type{ 0 } ) )
        {
            this->m_name = name;
        }
        else
        {
            this->m_name.clear();
        }
    }

    /* --------------------------------------------------------------------- */

    bool ControllerBase::readyForSend() const SIXTRL_NOEXCEPT
    {
        return this->m_ready_for_send;
    }

    bool ControllerBase::readyForReceive() const SIXTRL_NOEXCEPT
    {
        return this->m_ready_for_receive;
    }

    bool ControllerBase::readyForRunningKernel() const SIXTRL_NOEXCEPT
    {
        return this->m_ready_for_running_kernels;
    }

    bool ControllerBase::readyForRemap() const SIXTRL_NOEXCEPT
    {
        return ( ( this->readyForRunningKernel() ) &&
                 ( ( ( !this->isInDebugMode() ) &&
                     ( this->hasRemapCObjectBufferKernel() ) ) ||
                   ( ( this->isInDebugMode() ) &&
                     ( this->hasRemapCObjectBufferDebugKernel() ) ) ) );
    }

    ControllerBase::status_t ControllerBase::send(
        ControllerBase::ptr_arg_base_t SIXTRL_RESTRICT arg,
        const void *const SIXTRL_RESTRICT src_begin,
        ControllerBase::size_type const src_size )
    {
        using size_t    = ControllerBase::size_type;
        using status_t  = ControllerBase::status_t;
        status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( arg != nullptr ) &&
            ( this->readyForSend() ) && ( this->readyForRemap() ) &&
            ( arg->usesRawArgument() ) &&
            ( arg->capacity() > size_t{ 0 } ) && ( src_begin != nullptr ) &&
            ( src_size > size_t{ 0 } ) && ( src_size <= arg->capacity() ) )
        {
            status = this->doSend( arg, src_begin, src_size );
        }

        return status;
    }

    ControllerBase::status_t ControllerBase::send(
        ControllerBase::ptr_arg_base_t SIXTRL_RESTRICT arg,
        const ControllerBase::c_buffer_t *const SIXTRL_RESTRICT source,
        ControllerBase::perform_remap_flag_t const perform_remap_flag )
    {
        using size_t         = ControllerBase::size_type;
        using status_t       = ControllerBase::status_t;
        using data_ptr_t     = void const*;

        status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        data_ptr_t   src_begin = ::NS(Buffer_get_const_data_begin)( source );
        size_t const src_size  = ::NS(Buffer_get_size)( source );

        if( ( arg != nullptr ) &&
            ( this->readyForSend() ) && ( this->readyForRemap() ) &&
            ( arg->usesCObjectsBuffer() ) &&
            ( arg->capacity() > size_t{ 0 } ) && ( src_begin != nullptr ) &&
            ( src_size > size_t{ 0 } ) && ( src_size <= arg->capacity() ) )
        {
            status = this->doSend( arg, src_begin, src_size );

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( perform_remap_flag == st::CTRL_PERFORM_REMAP ) )
            {
                status = this->doRemapCObjectsBufferArg( arg );
            }
        }

        return status;
    }

    ControllerBase::status_t ControllerBase::send(
        ControllerBase::ptr_arg_base_t SIXTRL_RESTRICT arg,
        ControllerBase::buffer_t const& SIXTRL_RESTRICT_REF source,
        ControllerBase::perform_remap_flag_t const perform_remap_flag )
    {
        using size_t     = ControllerBase::size_type;
        using status_t   = ControllerBase::status_t;
        using data_ptr_t = void const*;

        status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        data_ptr_t   src_begin = source.dataBegin< data_ptr_t >();
        size_t const src_size  = source.size();

        if( ( arg != nullptr ) &&
            ( this->readyForSend() ) && ( this->readyForRemap() ) &&
            ( arg->usesCObjectsBuffer() ) &&
            ( arg->capacity() > size_t{ 0 } ) && ( src_begin != nullptr ) &&
            ( src_size > size_t{ 0 } ) && ( src_size <= arg->capacity() ) )
        {
            status = this->doSend( arg, src_begin, src_size );

            if( ( status == st::ARCH_STATUS_SUCCESS )&&
                ( perform_remap_flag == st::CTRL_PERFORM_REMAP ) )
            {
                status = this->doRemapCObjectsBufferArg( arg );
            }
        }

        return status;
    }

    ControllerBase::status_t ControllerBase::receive(
        void* SIXTRL_RESTRICT dest_begin,
        ControllerBase::size_type const dest_capacity,
        ControllerBase::ptr_arg_base_t SIXTRL_RESTRICT src_arg )
    {
        using size_t     = ControllerBase::size_type;
        using status_t   = ControllerBase::status_t;

        status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( src_arg != nullptr ) && ( this->readyForReceive() ) &&
            ( src_arg->size() > size_t{ 0 } ) &&
            ( dest_capacity >= src_arg->size() ) && ( dest_begin != nullptr ) )
        {
            status = this->doReceive( dest_begin, dest_capacity, src_arg );

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( src_arg->usesCObjectsBuffer() ) )
            {
                unsigned char* managed_buffer_begin =
                    reinterpret_cast< unsigned char* >( dest_begin );

                size_t const slot_size = SIXTRL_BUFFER_DEFAULT_SLOT_SIZE;
                if( ::NS(ManagedBuffer_remap)( managed_buffer_begin,
                        slot_size ) != 0 )
                {
                    status = st::ARCH_STATUS_GENERAL_FAILURE;
                }
            }
        }

        return status;

    }

    ControllerBase::status_t ControllerBase::receive(
        ControllerBase::c_buffer_t* SIXTRL_RESTRICT destination,
        ControllerBase::ptr_arg_base_t SIXTRL_RESTRICT src_arg,
        ControllerBase::perform_remap_flag_t const perform_remap_flag )
    {
        using size_t     = ControllerBase::size_type;
        using status_t   = ControllerBase::status_t;
        using data_ptr_t = void*;

        status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        data_ptr_t dest_begin = ::NS(Buffer_get_data_begin)( destination );
        size_t const dest_capacity = ::NS(Buffer_get_capacity)( destination );

        if( ( src_arg != nullptr ) && ( this->readyForReceive() ) &&
            ( src_arg->usesCObjectsBuffer() ) &&
            ( src_arg->size() > size_t{ 0 } ) &&
            ( dest_capacity >= src_arg->size() ) && ( dest_begin != nullptr ) )
        {
            status = this->doReceive( dest_begin, dest_capacity, src_arg );

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( perform_remap_flag == st::CTRL_PERFORM_REMAP ) )
            {
                status = ::NS(Buffer_remap)( destination );
            }
        }

        return status;
    }

    ControllerBase::status_t ControllerBase::receive(
        ControllerBase::buffer_t& SIXTRL_RESTRICT_REF destination,
        ControllerBase::ptr_arg_base_t SIXTRL_RESTRICT src_arg,
        ControllerBase::perform_remap_flag_t const perform_remap_flag )
    {
        using size_t     = ControllerBase::size_type;
        using status_t   = ControllerBase::status_t;
        using data_ptr_t = void*;

        status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( src_arg != nullptr ) && ( this->readyForReceive() ) &&
            ( src_arg->usesCObjectsBuffer() ) &&
            ( src_arg->size() > size_t{ 0 } ) &&
            ( destination.capacity() >= src_arg->size() ) &&
            ( destination.dataBegin< data_ptr_t >() != nullptr ) )
        {
            status = this->doReceive( destination.dataBegin< data_ptr_t >(),
                                      destination.capacity(), src_arg );

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( perform_remap_flag == st::CTRL_PERFORM_REMAP ) )
            {
                status = ( destination.remap() )
                    ? st::ARCH_STATUS_SUCCESS
                    : st::ARCH_STATUS_GENERAL_FAILURE;
            }
        }

        return status;
    }

    /* ===================================================================== */

    ControllerBase::size_type
    ControllerBase::numKernels() const SIXTRL_NOEXCEPT
    {
        return this->m_num_kernels;
    }

    /* --------------------------------------------------------------------- */

    bool ControllerBase::hasRemapCObjectBufferKernel() const SIXTRL_NOEXCEPT
    {
        return this->hasKernel( this->m_remap_kernel_id );
    }

    ControllerBase::kernel_id_t
    ControllerBase::remapCObjectBufferKernelId() const SIXTRL_NOEXCEPT
    {
        return this->m_remap_kernel_id;
    }

    void ControllerBase::setRemapCObjectBufferKernelId(
        ControllerBase::kernel_id_t const kernel_id ) SIXTRL_NOEXCEPT
    {
        this->m_remap_kernel_id = kernel_id;
    }



    bool
    ControllerBase::hasRemapCObjectBufferDebugKernel() const SIXTRL_NOEXCEPT
    {
        return this->hasKernel( this->m_remap_debug_kernel_id );
    }

    ControllerBase::kernel_id_t
    ControllerBase::remapCObjectBufferDebugKernelId() const SIXTRL_NOEXCEPT
    {
        return this->m_remap_debug_kernel_id;
    }

    void ControllerBase::setRemapCObjectBufferDebugKernelId(
        ControllerBase::kernel_id_t const kernel_id ) SIXTRL_NOEXCEPT
    {
        this->m_remap_debug_kernel_id = kernel_id;
    }

    /* --------------------------------------------------------------------- */

    ControllerBase::size_type
    ControllerBase::kernelWorkItemsDim(
        kernel_id_t const kernel_id ) const SIXTRL_NOEXCEPT
    {
        ControllerBase::kernel_config_base_t const* ptr_kernel_conf_base =
            this->ptrKernelConfigBase( kernel_id );

        return ( ptr_kernel_conf_base != nullptr )
            ? ptr_kernel_conf_base->workItemsDim()
            : ControllerBase::size_type{ 0 };
    }

    ControllerBase::size_type
    ControllerBase::kernelWorkGroupsDim(
        kernel_id_t const kernel_id ) const SIXTRL_NOEXCEPT
    {
        ControllerBase::kernel_config_base_t const* ptr_kernel_conf_base =
            this->ptrKernelConfigBase( kernel_id );

        return ( ptr_kernel_conf_base != nullptr )
            ? ptr_kernel_conf_base->workGroupsDim()
            : ControllerBase::size_type{ 0 };
    }

    ControllerBase::size_type ControllerBase::kernelNumArguments(
        ControllerBase::kernel_id_t const kernel_id ) const SIXTRL_NOEXCEPT
    {
        ControllerBase::kernel_config_base_t const* ptr_kernel_conf_base =
            this->ptrKernelConfigBase( kernel_id );

        return ( ptr_kernel_conf_base != nullptr )
            ? ptr_kernel_conf_base->numArguments()
            : ControllerBase::size_type{ 0 };
    }

    /* --------------------------------------------------------------------- */

    bool ControllerBase::kernelHasName(
        ControllerBase::kernel_id_t const kernel_id ) const SIXTRL_NOEXCEPT
    {
        ControllerBase::kernel_config_base_t const* ptr_kernel_conf_base =
            this->ptrKernelConfigBase( kernel_id );

        return ( ( ptr_kernel_conf_base != nullptr ) &&
                 ( ptr_kernel_conf_base->hasName() ) );
    }

    std::string const& ControllerBase::kernelName(
        ControllerBase::kernel_id_t const kernel_id ) const
    {
        ControllerBase::kernel_config_base_t const* ptr_kernel_conf_base =
            this->ptrKernelConfigBase( kernel_id );

        if( ptr_kernel_conf_base == nullptr )
        {
            throw std::runtime_error( "no kernel found for kernel_id" );
        }

        return ptr_kernel_conf_base->name();
    }

    char const* ControllerBase::ptrKernelNameStr(
        ControllerBase::kernel_id_t const kernel_id ) const SIXTRL_NOEXCEPT
    {
        ControllerBase::kernel_config_base_t const* ptr_kernel_conf_base =
            this->ptrKernelConfigBase( kernel_id );

        return ( ptr_kernel_conf_base != nullptr )
            ? ptr_kernel_conf_base->ptrNameStr() : nullptr;
    }

    /* --------------------------------------------------------------------- */

    bool ControllerBase::hasKernel(
        ControllerBase::kernel_id_t const kernel_id ) const SIXTRL_NOEXCEPT
    {
        return ( this->ptrKernelConfigBase( kernel_id ) != nullptr );
    }

    bool ControllerBase::hasKernel( std::string const& SIXTRL_RESTRICT_REF
        kernel_name ) const SIXTRL_NOEXCEPT
    {
        return ( this->ptrKernelConfigBase( this->doFindKernelConfigByName(
            kernel_name.c_str() ) ) != nullptr );
    }

    bool ControllerBase::hasKernel(
        char const* SIXTRL_RESTRICT kernel_name ) const SIXTRL_NOEXCEPT
    {
        return ( this->ptrKernelConfigBase( this->doFindKernelConfigByName(
            kernel_name ) ) != nullptr );
    }

    /* --------------------------------------------------------------------- */

    ControllerBase::kernel_config_base_t const*
    ControllerBase::ptrKernelConfigBase(
        ControllerBase::kernel_id_t const kernel_id ) const SIXTRL_NOEXCEPT
    {
        using _this_t = ControllerBase;

        _this_t::kernel_config_base_t const* ptr_kernel_conf_base = nullptr;

        if( ( kernel_id != _this_t::ILLEGAL_KERNEL_ID ) &&
            ( static_cast< _this_t::size_type >( kernel_id ) <
                this->m_kernel_configs.size() ) )
        {
            ptr_kernel_conf_base = this->m_kernel_configs[ kernel_id ].get();
        }

        return ptr_kernel_conf_base;
    }

    ControllerBase::kernel_config_base_t const*
    ControllerBase::ptrKernelConfigBase( std::string const& SIXTRL_RESTRICT_REF
        kernel_name ) const SIXTRL_NOEXCEPT
    {
        return this->ptrKernelConfigBase( this->doFindKernelConfigByName(
            kernel_name.c_str() ) );
    }

    ControllerBase::kernel_config_base_t const*
    ControllerBase::ptrKernelConfigBase(
        char const* SIXTRL_RESTRICT kernel_name ) const SIXTRL_NOEXCEPT
    {
        return this->ptrKernelConfigBase( this->doFindKernelConfigByName(
            kernel_name ) );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    ControllerBase::kernel_config_base_t* ControllerBase::ptrKernelConfigBase(
        ControllerBase::kernel_id_t const kernel_id ) SIXTRL_NOEXCEPT
    {
        using _this_t = ControllerBase;
        using ptr_t = _this_t::kernel_config_base_t*;

        return const_cast< ptr_t >( static_cast< _this_t const& >(
            *this ).ptrKernelConfigBase( kernel_id ) );
    }

    ControllerBase::kernel_config_base_t* ControllerBase::ptrKernelConfigBase(
        std::string const& SIXTRL_RESTRICT_REF kernel_name ) SIXTRL_NOEXCEPT
    {
        using _this_t = ControllerBase;
        using ptr_t = _this_t::kernel_config_base_t*;

        return const_cast< ptr_t >( static_cast< _this_t const& >(
            *this ).ptrKernelConfigBase( kernel_name ) );
    }

    ControllerBase::kernel_config_base_t* ControllerBase::ptrKernelConfigBase(
        char const* SIXTRL_RESTRICT kernel_name ) SIXTRL_NOEXCEPT
    {
        using _this_t = ControllerBase;
        using ptr_t = _this_t::kernel_config_base_t*;

        return const_cast< ptr_t >( static_cast< _this_t const& >(
            *this ).ptrKernelConfigBase( kernel_name ) );
    }

    /* ===================================================================== */

    ControllerBase::status_t ControllerBase::remap(
        ControllerBase::ptr_arg_base_t SIXTRL_RESTRICT ptr_arg )
    {
        ControllerBase::status_t status =
            st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( ptr_arg != nullptr ) && ( this->readyForRemap() ) )
        {
            status = this->doRemapCObjectsBufferArg( ptr_arg );
        }

        return status;
    }

    ControllerBase::status_t ControllerBase::remap(
        ControllerBase::arg_base_ref_t SIXTRL_RESTRICT_REF arg )
    {
        return this->remap( &arg );
    }

    bool ControllerBase::isRemapped(
        ControllerBase::ptr_arg_base_t SIXTRL_RESTRICT ptr_arg )
    {
        ControllerBase::status_t local_status =
            st::ARCH_STATUS_GENERAL_FAILURE;

        bool const is_remapped = this->doIsCObjectsBufferArgRemapped(
            ptr_arg, &local_status );

        if( local_status != st::ARCH_STATUS_SUCCESS )
        {
            throw std::runtime_error(
                "could not determine if cobject argument is remapped" );
        }

        return is_remapped;
    }

    bool ControllerBase::isRemapped(
        ControllerBase::arg_base_ref_t SIXTRL_RESTRICT_REF arg )
    {
        return this->isRemapped( &arg );
    }

    ControllerBase::~ControllerBase() SIXTRL_NOEXCEPT
    {

    }

    /* ===================================================================== */

    void ControllerBase::print(
        std::ostream& SIXTRL_RESTRICT_REF output ) const
    {
        this->doPrintToOutputStream( output );
    }

    void ControllerBase::print( ::FILE* SIXTRL_RESTRICT output ) const
    {
        ControllerBase::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( output != nullptr )
        {
            std::ostringstream a2str;
            status = this->doPrintToOutputStream( a2str );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                std::string const temp_str = a2str.str();

                ControllerBase::size_type ret = std::fprintf(
                    output, "%s", temp_str.c_str() );

                SIXTRL_ASSERT( ret > ControllerBase::size_type{ 0 } );
                ( void )ret;
            }
        }

        return std::string{};
    }

    void ControllerBase::printOut()
    {
        this->print( std::cout );
    }

    std::ostream& ControllerBase::operator<<(
        std::ostream& SIXTRL_RESTRICT_REF output,
        st::ControllerBase const& SIXTRL_RESTRICT_REF controller )
    {
        controller.print( output );
        return output;
    }

    ControllerBase::size_type ControllerBase::requiredOutStringLength() const
    {
        ControllerBase::size_type capacity = ControllerBase::size_type{ 0 };

        std::ostringstream a2str;
        if( st::ARCH_STATUS_SUCCESS == this->doPrintToOutputStream( a2str ) )
        {
            capacity = a2str.str().size();
        }

        return capacity;
    }

    std::string ControllerBase::toString() const
    {
        std::ostringstream a2str;

        if( st::ARCH_STATUS_SUCCESS != this->doPrintToOutputStream( a2str ) )
        {
            a2str.str( "" );
        }

        return a2str.str();
    }

    ControllerBase::status_t ControllerBase::toString(
        ControllerBase::size_type const str_repr_capacity,
        char* SIXTRL_RESTRICT str_repr_begin ) const SIXTRL_NOEXCEPT
    {
        using size_t = ControllerBase::size_type;

        ControllerBase::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( str_repr_capacity > size_t{ 0 } ) &&
            ( str_repr_begin != nullptr ) )
        {
            std::memset( str_repr_begin, static_cast< int >( '\0' ),
                         str_repr_capacity );

            std::ostringstream a2str;
            status = this->doPrintToOutputStream( a2str );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                std::string const temp_str = a2str.str();

                if( temp_str.size() < str_repr_capacity )
                {
                    std::strncpy( str_repr_begin, temp_str.c_str(),
                                  str_repr_capacity - size_t{ 1 } );
                }
                else
                {
                    status = st::ARCH_STATUS_GENERAL_FAILURE;
                }
            }
        }

        return status;
    }

    /* ===================================================================== */

    ControllerBase::ControllerBase(
        ControllerBase::arch_id_t const arch_id,
        const char *const SIXTRL_RESTRICT arch_str,
        const char *const SIXTRL_RESTRICT config_str ) :
        ArchDebugBase( arch_id, arch_str, config_str ),
            m_kernel_configs(), m_name(),
            m_num_kernels( ControllerBase::size_type{ 0 } ),
            m_remap_kernel_id( ControllerBase::ILLEGAL_KERNEL_ID ),
            m_uses_nodes( false ),
            m_ready_for_running_kernels( false ),
            m_ready_for_send( false ),
            m_ready_for_receive( false )
    {

    }

    void ControllerBase::doClear()
    {
        this->m_remap_kernel_id = ControllerBase::ILLEGAL_KERNEL_ID;

        this->m_ready_for_receive = false;
        this->m_ready_for_send = false;
        this->m_ready_for_running_kernels = false;

        return;
    }

    ControllerBase::status_t ControllerBase::doSend(
        ControllerBase::ptr_arg_base_t SIXTRL_RESTRICT,
        const void *const SIXTRL_RESTRICT, size_type const )
    {
        return st::ARCH_STATUS_GENERAL_FAILURE;
    }

    ControllerBase::status_t ControllerBase::doReceive( void* SIXTRL_RESTRICT,
        ControllerBase::size_type const,
        ControllerBase::ptr_arg_base_t SIXTRL_RESTRICT )
    {
        return st::ARCH_STATUS_GENERAL_FAILURE;
    }

    ControllerBase::status_t ControllerBase::doRemapCObjectsBufferArg(
        ControllerBase::ptr_arg_base_t SIXTRL_RESTRICT )
    {
        return st::ARCH_STATUS_GENERAL_FAILURE;
    }

    bool ControllerBase::doIsCObjectsBufferArgRemapped(
        ControllerBase::ptr_arg_base_t SIXTRL_RESTRICT,
        ControllerBase::status_t* SIXTRL_RESTRICT ptr_status )
    {
        if( ptr_status != nullptr )
        {
            *ptr_status = st::ARCH_STATUS_GENERAL_FAILURE;
        }

        return false;
    }

    ControllerBase::status_t
    ControllerBase::doSwitchDebugMode( bool const is_in_debug_mode )
    {
        if( ( ( is_in_debug_mode ) &&
              ( this->hasRemapCObjectBufferDebugKernel() ) ) ||
            ( ( !is_in_debug_mode ) &&
              ( this->hasRemapCObjectBufferKernel() ) ) )
        {
            return ControllerBase::_base_arch_obj_t::doSwitchDebugMode(
                is_in_debug_mode );
        }

        return st::ARCH_STATUS_GENERAL_FAILURE;
    }


    ControllerBase::status_t ControllerBase::doPrintToOutputStream(
        std::ostream& SIXTRL_RESTRICT_REF output ) const
    {
        ControllerBase::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->archId() != st::ARCHITECTURE_ILLEGAL )
        {
            if( this->hasName() )
            {
                output << "Controller      : " << this->name() << "\r\n";
            }

            output << "Architecture    : " << this->archId();

            if( this->hasArchStr() )
            {
                output << "( " << this->archStr() << " )\r\n";
            }

            if( this->isInDebugMode() )
            {
                output << "Debug mode      : true\r\n";
            }

            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    void ControllerBase::doSetUsesNodesFlag( bool const flag ) SIXTRL_NOEXCEPT
    {
        this->m_uses_nodes = flag;
    }

    void ControllerBase::doSetReadyForSendFlag(
        bool const flag ) SIXTRL_NOEXCEPT
    {
        this->m_ready_for_send = flag;
    }

    void ControllerBase::doSetReadyForReceiveFlag(
        bool const flag ) SIXTRL_NOEXCEPT
    {
        this->m_ready_for_receive = flag;
    }

    void ControllerBase::doSetReadyForRunningKernelsFlag(
            bool const flag ) SIXTRL_NOEXCEPT
    {
        this->m_ready_for_running_kernels = flag;
    }

    /* -------------------------------------------------------------------- */

    void ControllerBase::doReserveForNumKernelConfigs(
        ControllerBase::size_type const kernel_configs_capacity )
    {
        this->m_kernel_configs.reserve( kernel_configs_capacity );
    }

    ControllerBase::kernel_id_t ControllerBase::doFindKernelConfigByName(
        char const* SIXTRL_RESTRICT kernel_name ) const SIXTRL_NOEXCEPT
    {
        using _this_t = ControllerBase;
        _this_t::kernel_id_t kernel_id = ControllerBase::ILLEGAL_KERNEL_ID;

        if( ( kernel_name != nullptr ) &&
            ( std::strlen( kernel_name ) > _this_t::size_type{ 0 } ) )
        {
            _this_t::size_type ii = _this_t::size_type{ 0 };
            _this_t::size_type const nkernels = this->m_kernel_configs.size();

            for( ; ii < nkernels ; ++ii )
            {
                _this_t::kernel_config_base_t const* ptr_kernel_conf_base =
                    this->m_kernel_configs[ ii ].get();

                if( ( ptr_kernel_conf_base != nullptr ) &&
                    ( ptr_kernel_conf_base->hasName() ) &&
                    ( 0 == ptr_kernel_conf_base->name().compare(
                        kernel_name ) ) )
                {
                    kernel_id = static_cast< _this_t::kernel_id_t >( ii );
                    break;
                }
            }
        }

        return kernel_id;
    }

    ControllerBase::kernel_id_t ControllerBase::doAppendKernelConfig(
        ControllerBase::ptr_kernel_conf_base_t&&
            ptr_kernel_conf_base ) SIXTRL_NOEXCEPT
    {
        using _this_t = ControllerBase;
        _this_t::kernel_id_t kernel_id = _this_t::ILLEGAL_KERNEL_ID;

        if( ptr_kernel_conf_base.get() != nullptr )
        {
            SIXTRL_ASSERT( this->m_kernel_configs.size() < static_cast<
                _this_t::size_type >( _this_t::ILLEGAL_KERNEL_ID ) );

            kernel_id = static_cast< kernel_id_t >(
                this->m_kernel_configs.size() );


            this->m_kernel_configs.push_back(
                std::move( ptr_kernel_conf_base ) );

            if( this->ptrKernelConfigBase( kernel_id ) != nullptr )
            {
                ++this->m_num_kernels;
            }
        }

        return kernel_id;
    }

    void ControllerBase::doRemoveKernelConfig(
        ControllerBase::kernel_id_t const kernel_id ) SIXTRL_NOEXCEPT
    {
        using kernel_conf_base_t = ControllerBase::kernel_config_base_t;

        kernel_conf_base_t* ptr_kernel_conf_base =
            this->ptrKernelConfigBase( kernel_id );

        if( ptr_kernel_conf_base != nullptr )
        {
            SIXTRL_ASSERT( kernel_id < this->m_kernel_configs.size() );
            SIXTRL_ASSERT( this->m_num_kernels >
                           ControllerBase::size_type{ 0 } );

            this->m_kernel_configs[ kernel_id ].reset( nullptr );
            --this->m_num_kernels;
        }

        return;
    }
}

#endif /* C++, host */

/* end: sixtracklib/common/control/controller_base.cpp */
