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

    ControllerBase::kernel_id_t ControllerBase::addKernelConfig(
        ControllerBase::key_t const& SIXTRL_RESTRICT_REF key,
        ControllerBase::ptr_kernel_conf_base_t&& ptr_kernel_config )
    {
        return this->kernelConfigStore().addKernelConfig(
            key, std::move( ptr_kernel_config ) );
    }

    ControllerBase::status_t ControllerBase::addKernelConfig(
        ControllerBase::key_t const& SIXTRL_RESTRICT_REF key,
        ControllerBase::kernel_id_t const kernel_config_id )
    {
        return this->kernelConfigStore().addKernelConfig(
            key, kernel_config_id );
    }

    /* ===================================================================== */

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

    /* ===================================================================== */

    void ControllerBase::setDefaultKernelConfigStr(
        char const* SIXTRL_RESTRICT kernel_config_str )
    {
        using _this_t = st::ControllerBase;

        if( ( kernel_config_str != nullptr ) &&
            ( std::strlen( kernel_config_str ) > _this_t::size_type{ 0 } ) )
        {
            this->m_default_kernel_config_str =
                std::string{ kernel_config_str };
        }
        else
        {
            this->m_default_kernel_config_str.clear();
        }
    }

    /* ===================================================================== */

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
        ControllerBase::kernel_config_store_base_t&
            SIXTRL_RESTRICT_REF kernel_config_store,
        const char *const SIXTRL_RESTRICT config_str ) :
        ArchDebugBase( arch_id, arch_str, config_str ),
            m_remap_kernel_key(),
            m_kernel_config_store( kernel_config_store ),
            m_name(),
            m_default_kernel_config_str(),
            m_remap_kernel_id( ControllerBase::ILLEGAL_KERNEL_ID ),
            m_uses_nodes( false ),
            m_ready_for_running_kernels( false ),
            m_ready_for_send( false ),
            m_ready_for_receive( false )
    {

    }

    ControllerBase::kernel_config_store_base_t&
    ControllerBase::kernelConfigStore() SIXTRL_NOEXCEPT
    {
        return this->m_kernel_config_store;
    }

    void ControllerBase::doClear()
    {
        this->m_remap_kernel_key = st::ControllerBase::key_t{};
        this->m_remap_kernel_id = ControllerBase::ILLEGAL_KERNEL_ID;
        this->m_ready_for_receive = false;
        this->m_ready_for_send = false;
        this->m_ready_for_running_kernels = false;

        return;
    }

    /* --------------------------------------------------------------------- */

    ControllerBase::status_t ControllerBase::doChangeVariantFlags(
        ControllerBase::variant_t const new_variant_flags )
    {
        using _this_t = st::ControllerBase;
        using _base_t = _this_t::_base_arch_obj_t;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
        bool has_fatal_error = false;

        if( !this->hasRemapBufferKernel() )
        {
            SIXTRL_ASSERT( !this->remapBufferKernelConfigKey.valid() );
            SIXTRL_ASSERT( this->remapBufferKernelConfigId() ==
                _this_t::ILLEGAL_KERNEL_ID );

            status = _base_t::doChangeVariantFlags( new_variant_flags );
            return status;
        }

        SIXTRL_ASSERT( new_key.archId() == _this_t::ARCH_ILLEGAL );

        _this_t::kernel_config_key_t key = this->remapBufferKernelConfigKey();

        SIXTRL_ASSERT( ( key.valid() ) &&
            ( key.purpose() == st::KERNEL_CONFIG_PURPOSE_REMAP_BUFFER ) &&
            ( this->remapBufferKernelConfigId() !=
                _this_t::ILLEGAL_KERNEL_ID ) );


        _this_t::variant_t const current_variant = this->variant();

        key.setVariant( new_variant_flags );

        if( this->doPreflightCheckSelectKernelConfigByKey( key ) )
        {
            status = _base_t::doChangeVariantFlags( new_variant_flags );
        }

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            status = this->doSelectRemapBufferKernelConfig( key );

            if( status != st::ARCH_STATUS_SUCCESS )
            {
                /* Attempt to roll-back and register fatal error if
                * this does not work either: */

                _this_t::status_t rollback_status =
                    _base_t::doChangeVariantFlags( current_variant );

                key.setVariant( current_variant );

                if( st::ARCH_STATUS_SUCCESS !=
                        this->doSelectRemapBufferKernelConfig( key ) )
                {
                    rollback_status = st::ARCH_STATUS_GENERAL_FAILURE;
                }

                if( rollback_status != st::ARCH_STATUS_SUCCESS )
                {
                    has_fatal_error = true;
                }
            }
        }
        else if( st::ARCH_STATUS_SUCCESS !=
                _base_t::doChangeVariantFlags( cur_variant );
        {
            /* Unable to roll-back to previous variant flags ->
            * throw a runtime error */

            has_fatal_error = true;
        }

        if( has_fatal_error )
        {
            throw std::runtime_error(
                "unable to rollback failed variant flags change" );
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    ControllerBase::status_t ControllerBase::doSelectKernelConfigByKey(
        ControllerBase::kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
        ControllerBase::kernel_id_t* SIXTRL_RESTRICT ptr_kernel_id_to_change,
        ControllerBase::kernel_config_key_t* SIXTRL_RESTRICT ptr_key_to_change )
    {
        using _this_t = st::ControllerBase;
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( key.archId() != _this_t::ARCH_ILLEGAL ) &&
            ( ( ptr_kernel_id_to_change != nullptr ) ||
              ( ptr_key_to_change != nullptr ) ) )
        {
            _this_t::kernel_id_t kernel_config_id =
                this->kernelConfigStore().kernelId( key );

            _this_t::kernel_config_base_t const* ptr_conf =
                this->kernelConfigStore().ptrKernelConfigBase(
                    kernel_config_id );

            if( this->doCheckSelectKernelConfigByKeyOk( key, ptr_conf ) )
            {
                if( ptr_kernel_id_to_change != nullptr )
                {
                    *ptr_kernel_id_to_change = kernel_config_id;
                }

                if( ptr_key_to_change != nullptr )
                {
                    *ptr_key_to_change = key;
                }

                status = st::ARCH_STATUS_SUCCESS;
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    ControllerBase::status_t ControllerBase::doUnselectKernelConfig(
        ControllerBase::kernel_id_t& SIXTRL_RESTRICT_REF kernel_id_to_unselect,
        ControllerBase::kernel_config_key_t*
            SIXTRL_RESTRICT ptr_key_to_unselect )
    {
        using _this_t = st::ControllerBase;
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( kernel_id_to_unselect != _this_t::ILLEGAL_KERNEL_ID )
        {
            kernel_id_to_unselect = _this_t::ILLEGAL_KERNEL_ID;

            if( ptr_key_to_unselect != nullptr )
            {
                *ptr_key_to_unselect = _this_t::kernel_config_key_t{};
            }

            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    bool ControllerBase::doCheckAreKernelConfigsInitialized(
        ControllerBase::kernel_config_key_t& SIXTRL_RESTRICT_REF key ) const
    {
        bool initialized = false;

        using _this_t = st::ControllerBase;

        if( input_key.archId() != _this_t::ARCH_ILLEGAL )
        {
            _this_t::kernel_purpose_t const initial_purpose = key.purpose();

            if( initial_purpose != st::KERNEL_CONFIG_PURPOSE_REMAP_BUFFER )
            {
                key.setPurpose( st::KERNEL_CONFIG_PURPOSE_REMAP_BUFFER );
            }

            initialized = ( this->kernelConfigStore().kernelId( key ) !=
                _this_t::ILLEGAL_KERNEL_ID );

            if( initial_purpose != st::KERNEL_CONFIG_PURPOSE_REMAP_BUFFER )
            {
                key.setPurpose( initial_purpose );
            }
        }

        return initialized;
    }

    ControllerBase::status_t ControllerBase::doInitializeKernelConfigs(
        ControllerBase::kernel_config_key_t& SIXTRL_RESTRICT_REF key )
    {
        using _this_t = st::NodeControllerBase;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( input_key.archId() != _this_t::ARCH_ILLEGAL ) &&
            ( this->nodeStore().checkLock( lock ) ) )
        {
            _this_t::kernel_purpose_t const initial_purpose = key.purpose();

            if( initial_purpose != st::KERNEL_CONFIG_PURPOSE_REMAP_BUFFER )
            {
                key.setPurpose( st::KERNEL_CONFIG_PURPOSE_REMAP_BUFFER );
            }

            _this_t::kernel_id_t const kernel_config_id =
                this->kernelConfigStore().kernelId( key );

            if( kernel_config_id != _this_t::ILLEGAL_KERNEL_ID )
            {
                status = st::ARCH_STATUS_SUCCESS;
            }
            else
            {
                status = this->kernelConfigStore().initKernelConfig( key );
            }

            if( initial_purpose != st::KERNEL_CONFIG_PURPOSE_REMAP_BUFFER )
            {
                key.setPurpose( initial_purpose );
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

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

    ControllerBase::kernel_id_t ControllerBase::doInitKernelConfig(
        ControllerBase::kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
        ControllerBase::size_type num_kernel_args,
        char const* SIXTRL_RESTRICT name )
    {
        using _this_t = st::ControllerBase;
        _this_t::kernel_id_t kernel_config_id = _this_t::ILLEGAL_KERNEL_ID;

        if(

        return kernel_config_id;
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

            output << "Variant Flags   : " << std::hex << this->variant()
                   << std::dec << "\r\n";

            output << output << "Debug mode      : "
                   << std::boolalpha << this->isInDebugMode()
                   << std::noboolalpha << "\r\n";

            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    bool ControllerBase::doPreflightCheckSelectKernelConfigByKey(
        ControllerBase::kernel_config_key_t const& SIXTRL_RESTRICT_REF key ) const
    {
        bool select_op_should_work = false;

        if( key.archId() != _this_t::ARCH_ILLEGAL )
        {
            _this_t::kernel_id_t kernel_config_id =
                this->kernelConfigStore().kernelId( key );

            select_op_should_work = this->doCheckSelectKernelConfigByKeyOk(
                key, this->kernelConfigStore().ptrKernelConfigBase(
                    kernel_config_id ) );
        }

        return select_op_should_work;
    }

    bool ControllerBase::doCheckSelectKernelConfigByKeyOk(
        ControllerBase::kernel_config_key_t const& SIXTRL_RESTRICT_REF key,
        ControllerBase::kernel_config_base_t const* SIXTRL_RESTRICT ptr_conf ) const
    {
        return ( ( ptr_conf != nullptr ) &&
                 ( key.archId() != _this_t::ARCH_ILLEGAL ) &&
                 ( ptr_conf->archId() == key.archId() ) &&
                 ( ptr_conf->purpose() == key.purpose() ) &&
                 ( ( key.variant() == st::ARCH_VARIANT_NONE ) ||
                   ( ptr_conf->areVariantFlagsSet( key.variant() ) ) ) );
    }

    ControllerBase::status_t ControllerBase::doSetRemapBufferKernelConfigKey(
        ControllerBase::kernel_config_key_t const& SIXTRL_RESTRICT_REF key );
    {
        this->m_remap_kernel_key = key;
    }

    ControllerBase::status_t ControllerBase::doSetRemapBufferKernelConfigId(
        ControllerBase::kernel_id_t const kernel_config_id )
    {
        this->m_remap_kernel_id = kernel_config_id;
    }

    /* --------------------------------------------------------------------- */

    ControllerBase::status_t ControllerBase::doUpdateKernelConfigStore(
        ControllerBase::kernel_config_store_base_t& SIXTRL_RESTRICT_REF store )
    {
        using _this_t = ControllerBase;
        using store_t = _this_t::kernel_config_store_base_t;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;


        if( this->ptrKernelConfigStore() == &store )
        {
            status = st::ARCH_STATUS_SUCCESS;
        }
        else if( ( !this->readyForRunningKernel() ) &&
                 ( !this->readyForSend() ) && ( !this->readyForReceive() ) &&
                 ( !this->kernelConfigStore().lockable() != store.lockable() ) )
        {
            store_t::lock_t old_store_lock(
                *this->kernelConfigStore().lockable() );
            store_t::lock_t new_store_lock( *store.lockable() );

            this->m_kernel_config_store = store;
            old_store_lock.unlock();
            new_store_lock.unlock();

            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

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
}

#endif /* C++, host */

/* end: sixtracklib/common/control/controller_base.cpp */
