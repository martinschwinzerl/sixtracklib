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
    using _this_t = st::ControllerBase;

    constexpr _this_t::arch_id_t        _this_t::ARCH_ILLEGAL;
    constexpr _this_t::arch_id_t        _this_t::NO_ARCH_ID;
    constexpr _this_t::kernel_id_t      _this_t::ILLEGAL_KERNEL_CONFIG_ID;
    constexpr _this_t::kernel_set_id_t  _this_t::ILLEGAL_KERNEL_SET_ID;
    constexpr _this_t::sync_id_value_t  _this_t::ILLEGAL_SYNC_ID_VALUE;
    constexpr _this_t::kernel_purpose_t _this_t::UNSPECIFIED_PURPOSE;
    constexpr _this_t::kernel_purpose_t _this_t::PURPOSE_REMAP_BUFFER;

    /* ********************************************************************* */

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

    _this_t::status_t ControllerBase::send(
        _this_t::kernel_lock_t const& SIXTRL_RESTRICT_REF lock,
        _this_t::ptr_arg_base_t SIXTRL_RESTRICT arg,
        const void *const SIXTRL_RESTRICT src_begin,
        _this_t::size_type const src_size )
    {
        using size_t = _this_t::size_type;
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( arg != nullptr ) &&
            ( this->readyForSend( lock ) ) &&
            ( arg->usesRawArgument() ) &&
            ( arg->capacity() > size_t{ 0 } ) && ( src_begin != nullptr ) &&
            ( src_size > size_t{ 0 } ) && ( src_size <= arg->capacity() ) )
        {
            SIXTRL_ASSERT( this->checkKernelLock( lock ) );
            status = this->doSend( arg, src_begin, src_size );
        }

        return status;
    }

    _this_t::status_t ControllerBase::send(
        _this_t::kernel_lock_t const& SIXTRL_RESTRICT_REF lock,
        _this_t::ptr_arg_base_t SIXTRL_RESTRICT arg,
        const _this_t::c_buffer_t *const SIXTRL_RESTRICT source,
        _this_t::perform_remap_flag_t const perform_remap_flag )
    {
        using size_t     = _this_t::size_type;
        using data_ptr_t = void const*;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        static constexpr _this_t::op_flags_t REQU_FLAGS =
            st::KERNEL_OP_CTRL_READY_TO_SEND |
            st::KERNEL_OP_CTRL_KERNELS_AVAILABLE;

        data_ptr_t   src_begin = ::NS(Buffer_get_const_data_begin)( source );
        size_t const src_size  = ::NS(Buffer_get_size)( source );

        if( ( arg != nullptr ) &&
            ( this->doCheckOpFlagAndUpdateIfRequired( lock, REQU_FLAGS ) ) &&
            ( arg->usesCObjectsBuffer() ) &&
            ( arg->capacity() > size_t{ 0 } ) && ( src_begin != nullptr ) &&
            ( src_size > size_t{ 0 } ) && ( src_size <= arg->capacity() ) )
        {
            SIXTRL_ASSERT( this->checkKernelLock( lock ) );
            status = this->doSend( arg, src_begin, src_size );

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( perform_remap_flag == st::CTRL_PERFORM_REMAP ) )
            {
                status = this->doRemapCObjectsBufferArg( arg );
            }
        }

        return status;
    }

    _this_t::status_t ControllerBase::send(
        _this_t::kernel_lock_t const& SIXTRL_RESTRICT_REF lock,
        _this_t::ptr_arg_base_t SIXTRL_RESTRICT arg,
        _this_t::buffer_t const& SIXTRL_RESTRICT_REF source,
        _this_t::perform_remap_flag_t const perform_remap_flag )
    {
        using size_t     = _this_t::size_type;
        using data_ptr_t = void const*;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        static constexpr _this_t::op_flags_t REQU_FLAGS =
            st::KERNEL_OP_CTRL_READY_TO_SEND |
            st::KERNEL_OP_CTRL_KERNELS_AVAILABLE;

        data_ptr_t   src_begin = source.dataBegin< data_ptr_t >();
        size_t const src_size  = source.size();

        if( ( arg != nullptr ) &&
            ( this->doCheckOpFlagAndUpdateIfRequired( lock, REQU_FLAGS ) ) &&
            ( arg->usesCObjectsBuffer() ) &&
            ( arg->capacity() > size_t{ 0 } ) && ( src_begin != nullptr ) &&
            ( src_size > size_t{ 0 } ) && ( src_size <= arg->capacity() ) )
        {
            SIXTRL_ASSERT( this->checkKernelLock( lock ) );
            status = this->doSend( arg, src_begin, src_size );

            if( ( status == st::ARCH_STATUS_SUCCESS )&&
                ( perform_remap_flag == st::CTRL_PERFORM_REMAP ) )
            {
                status = this->doRemapCObjectsBufferArg( arg );
            }
        }

        return status;
    }

    _this_t::status_t ControllerBase::receive(
        _this_t::kernel_lock_t const& SIXTRL_RESTRICT_REF lock,
        void* SIXTRL_RESTRICT dest_begin,
        _this_t::size_type const dest_capacity,
        _this_t::ptr_arg_base_t SIXTRL_RESTRICT src_arg,
        _this_t::perform_remap_flag_t const perform_remap_flag )
    {
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( src_arg != nullptr ) && ( this->readyForReceive( lock ) ) &&
            ( src_arg->size() > size_t{ 0 } ) &&
            ( dest_capacity >= src_arg->size() ) && ( dest_begin != nullptr ) )
        {
            SIXTRL_ASSERT( this->checkKernelLock( lock ) );
            status = this->doReceive( dest_begin, dest_capacity, src_arg );

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( perform_remap_flag == st::CTRL_PERFORM_REMAP ) &&
                ( src_arg->usesCObjectsBuffer() ) )
            {
                status = ::NS(ManagedBuffer_remap)(
                    reinterpret_cast< unsigned char* >( dest_begin ),
                    st::BUFFER_DEFAULT_SLOT_SIZE );
            }
        }

        return status;

    }

    _this_t::status_t ControllerBase::receive(
        _this_t::kernel_lock_t const& SIXTRL_RESTRICT_REF lock,
        _this_t::c_buffer_t* SIXTRL_RESTRICT destination,
        _this_t::ptr_arg_base_t SIXTRL_RESTRICT src_arg,
        _this_t::perform_remap_flag_t const perform_remap_flag )
    {
        using size_t     = _this_t::size_type;
        using data_ptr_t = void*;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        data_ptr_t dest_begin = ::NS(Buffer_get_data_begin)( destination );
        size_t const dest_capacity = ::NS(Buffer_get_capacity)( destination );

        if( ( src_arg != nullptr ) && ( this->readyForReceive( lock ) ) &&
            ( src_arg->usesCObjectsBuffer() ) &&
            ( src_arg->size() > size_t{ 0 } ) &&
            ( dest_capacity >= src_arg->size() ) && ( dest_begin != nullptr ) )
        {
            SIXTRL_ASSERT( this->checkKernelLock( lock ) );
            status = this->doReceive( dest_begin, dest_capacity, src_arg );

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( perform_remap_flag == st::CTRL_PERFORM_REMAP ) )
            {
                status = ::NS(Buffer_remap)( destination );
            }
        }

        return status;
    }

    _this_t::status_t ControllerBase::receive(
        _this_t::kernel_lock_t const& SIXTRL_RESTRICT_REF lock,
        _this_t::buffer_t& SIXTRL_RESTRICT_REF destination,
        _this_t::ptr_arg_base_t SIXTRL_RESTRICT src_arg,
        _this_t::perform_remap_flag_t const perform_remap_flag )
    {
        using size_t  = _this_t::size_type;
        using data_ptr_t = void*;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( src_arg != nullptr ) && ( this->readyForReceive( lock ) ) &&
            ( src_arg->usesCObjectsBuffer() ) &&
            ( src_arg->size() > size_t{ 0 } ) &&
            ( destination.capacity() >= src_arg->size() ) &&
            ( destination.dataBegin< data_ptr_t >() != nullptr ) )
        {
            SIXTRL_ASSERT( this->checkKernelLock( lock ) );
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

    /* --------------------------------------------------------------------- */

    _this_t::status_t ControllerBase::remap(
        _this_t::ptr_arg_base_t SIXTRL_RESTRICT ptr_arg )
    {
        using _this_t = st::ControllerBase;
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( !this->hasKernelConfigStore() )
        {
            return status;
        }

        _this_t::kernel_lock_t const lock( *this->kernelLockable() );

        if( ( ptr_arg != nullptr ) && ( this->readyForRemap( lock ) ) )
        {
            status = this->doRemapCObjectsBufferArg( ptr_arg );
        }

        return status;
    }

    _this_t::status_t ControllerBase::remap(
        _this_t::arg_base_ref_t SIXTRL_RESTRICT_REF arg )
    {
        return this->remap( &arg );
    }

    bool ControllerBase::isRemapped(
        _this_t::ptr_arg_base_t SIXTRL_RESTRICT ptr_arg )
    {
        _this_t::status_t local_status = st::ARCH_STATUS_GENERAL_FAILURE;
        bool const is_remapped = this->doIsCObjectsBufferArgRemapped(
            ptr_arg, &local_status );

        if( local_status != st::ARCH_STATUS_SUCCESS )
        {
            throw std::runtime_error(
                "could not determine if cobject argument is remapped" );
        }

        return is_remapped;
    }

    /* --------------------------------------------------------------------- */

    bool ControllerBase::canChangeVariantFlags(
        _this_t::kernel_lock_t const& SIXTRL_RESTRICT_REF lock,
        _this_t::variant_t const new_variant_flags ) const
    {
        _this_t::kernel_config_key_t key( this->currentKey( lock ) );
        key.setVariant( new_variant_flags );
        return this->canChangeToKey( lock, key );
    }

    _this_t::status_t ControllerBase::changeVariantFlags(
        _this_t::kernel_lock_t const& SIXTRL_RESTRICT_REF lock,
        _this_t::variant_t const new_variant_flags )
    {
        _this_t::kernel_config_key_t key( this->currentKey( lock ) );
        key.setVariant( new_variant_flags );
        return this->changeToKey( lock, key );
    }

    /* --------------------------------------------------------------------- */

    bool ControllerBase::canChangeArgumentSet(
        _this_t::kernel_lock_t const& SIXTRL_RESTRICT_REF lock,
        _this_t::kernel_argument_set_t const arg_set ) const
    {
        _this_t::kernel_config_key_t key( this->currentKey( lock ) );
        key.setArgumentSet( arg_set );
        return this->canChangeToKey( lock, key );
    }

    _this_t::status_t ControllerBase::changeArgumentSet(
        _this_t::kernel_lock_t const& SIXTRL_RESTRICT_REF lock,
        _this_t::kernel_argument_set_t const arg_set )
    {
        _this_t::kernel_config_key_t key( this->currentKey( lock ) );
        key.setArgumentSet( arg_set );
        return this->changeToKey( lock, key );
    }

    /* --------------------------------------------------------------------- */

    bool ControllerBase::canChangeToKey(
        _this_t::kernel_lock_t const& SIXTRL_RESTRICT_REF lock,
        _this_t::kernel_config_key_t& SIXTRL_RESTRICT_REF new_key ) const
    {
        return ( ( new_key.isEqualExceptPurpose( this->currentKey( lock ) ) ) ||
            ( this->doCheckIfCanChangeAllKernelsWithKey( lock, new_key ) ) );
    }

    _this_t::status_t ControllerBase::changeToKey(
            _this_t::kernel_lock_t const& SIXTRL_RESTRICT_REF lock,
            _this_t::kernel_config_key_t& SIXTRL_RESTRICT_REF new_key )
    {
        if( ( this->ptrKernelConfigStore() == nullptr ) ||
            ( !this->checkKernelLock( lock ) ) )
                return st::ARCH_STATUS_GENERAL_FAILURE;

        return ( new_key.isEqualExceptPurpose( this->currentKey( lock ) ) )
            ? st::ARCH_STATUS_SUCCESS
            : this->doChangeAllKernelsWithKey( lock, new_key );
    }

    /* --------------------------------------------------------------------- */

    void ControllerBase::print( ::FILE* SIXTRL_RESTRICT output ) const
    {
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( output != nullptr )
        {
            std::ostringstream a2str;
            status = this->doPrintToOutputStream( a2str );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                std::string const temp_str = a2str.str();

                _this_t::size_type ret = std::fprintf(
                    output, "%s", temp_str.c_str() );

                SIXTRL_ASSERT( ret > ControllerBase::size_type{ 0 } );
                ( void )ret;
            }
        }
    }

    _this_t::size_type ControllerBase::requiredOutStringLength() const
    {
        _this_t::size_type capacity = ControllerBase::size_type{ 0 };

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

    _this_t::status_t ControllerBase::toString(
        _this_t::size_type const str_repr_capacity,
        char* SIXTRL_RESTRICT str_repr_begin ) const SIXTRL_NOEXCEPT
    {
        using size_t = _this_t::size_type;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

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

    /* --------------------------------------------------------------------- */

    ControllerBase::ControllerBase(
        _this_t::arch_id_t const arch_id,
        char const* SIXTRL_RESTRICT config_str ) :
        _this_t::_base_arch_obj_t( arch_id,
            _this_t::_base_arch_obj_t::DEFAULT_VARIANT, config_str ),
        m_default_key( arch_id ), m_name(),
        m_my_own_kernel_config_store( nullptr ),
        m_ptr_kernel_config_store( nullptr ),
        m_ptr_kernel_set( nullptr ),
        m_op_flags( st::KERNEL_OP_FLAGS_NONE ),
        m_expected_kernel_set_sync_id( _this_t::ILLEGAL_SYNC_ID_VALUE ),
        m_kernel_set_id( _this_t::ILLEGAL_KERNEL_SET_ID ),
        m_uses_nodes( false )
    {

    }

    void ControllerBase::doClear(
        _this_t::kernel_lock_t const& SIXTRL_RESTRICT_REF lock )
    {
        if( this->hasKernelSet( lock ) )
        {
            _this_t::kernel_set_t* ptr_kernel_set = this->ptrKernelSet( lock );
            if( ptr_kernel_set != nullptr )  ptr_kernel_set->reset( lock );
            this->doResetOpFlagsAndSyncId();
        }
    }

    /* --------------------------------------------------------------------- */

    _this_t::status_t ControllerBase::doSend(
        _this_t::ptr_arg_base_t SIXTRL_RESTRICT,
        const void *const SIXTRL_RESTRICT, size_type const )
    {
        return st::ARCH_STATUS_GENERAL_FAILURE;
    }

    _this_t::status_t ControllerBase::doReceive( void* SIXTRL_RESTRICT,
        _this_t::size_type const,
        _this_t::ptr_arg_base_t SIXTRL_RESTRICT )
    {
        return st::ARCH_STATUS_GENERAL_FAILURE;
    }

    _this_t::status_t ControllerBase::doRemapCObjectsBufferArg(
        _this_t::ptr_arg_base_t SIXTRL_RESTRICT )
    {
        return st::ARCH_STATUS_GENERAL_FAILURE;
    }

    bool ControllerBase::doIsCObjectsBufferArgRemapped(
        _this_t::ptr_arg_base_t SIXTRL_RESTRICT,
        ControllerBase::status_t* SIXTRL_RESTRICT ptr_status )
    {
        if( ptr_status != nullptr )
        {
            *ptr_status = st::ARCH_STATUS_GENERAL_FAILURE;
        }

        return false;
    }

    bool ControllerBase::doCheckIfCanChangeAllKernelsWithKey(
        _this_t::kernel_lock_t const& SIXTRL_RESTRICT_REF kernel_lock,
        _this_t::kernel_config_key_t& SIXTRL_RESTRICT_REF new_key ) const
    {
        bool can_switch_all_kernels = false;

        if( ( this->ptrKernelConfigStore() != nullptr ) &&
            ( this->checkKernelLock( kernel_lock ) ) )
        {
            _this_t::kernel_set_base_t const* kernel_set =
                this->ptrKernelConfigStore()->ptrKernelSetBase(
                    kernel_lock, this->m_kernel_set_id );

            can_switch_all_kernels = ( ( kernel_set != nullptr ) &&
                ( kernel_set->canSwitchKernels( kernel_lock, new_key ) ) );
        }

        return can_switch_all_kernels;
    }

    _this_t::status_t ControllerBase::doChangeAllKernelsWithKey(
        _this_t::kernel_lock_t const& SIXTRL_RESTRICT_REF kernel_lock,
        _this_t::kernel_config_key_t& SIXTRL_RESTRICT_REF new_key )
    {
        SIXTRL_ASSERT( this->ptrKernelConfigStore() != nullptr );
        SIXTRL_ASSERT( this->checkKernelLock( kernel_lock ) );
        SIXTRL_ASSERT( !new_key.isEqualExceptPurpose(
            this->currentKey( kernel_lock ) ) );

        SIXTRL_ASSERT( this->m_ptr_kernel_set != nullptr );
        SIXTRL_ASSERT( this->m_ptr_kernel_set ==
                       this->ptrKernelConfigStore()->ptrKernelSetBase(
                           kernel_lock, this->m_kernel_set_id ) );

        bool const changes_variant = ( new_key.variant() !=
            this->currentKey( kernel_lock ).variant() );

        _this_t::status_t status =
            this->m_ptr_kernel_set->switchKernels( kernel_lock, new_key );

        if( ( status == st::ARCH_STATUS_SUCCESS ) ||
            ( !this->isSyncWithKernelSet() ) )
        {
            status = this->syncWithKernelSet( kernel_lock );
        }

        if( ( status == st::ARCH_STATUS_SUCCESS ) && ( changes_variant ) )
        {
            status = this->doChangeVariantFlags( new_key.variant() );
        }

        return status;
    }

    _this_t::status_t ControllerBase::doPrintToOutputStream(
        std::ostream& SIXTRL_RESTRICT_REF output ) const
    {
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

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

            output << "Debug mode      : "
                   << std::boolalpha << this->isInDebugMode()
                   << std::noboolalpha << "\r\n";

            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

    _this_t::status_t ControllerBase::doSyncWithKernelSet(
        _this_t::kernel_lock_t const& SIXTRL_RESTRICT_REF lock )
    {
        return this->doSyncWithKernelSetBaseImpl( lock );
    }

    _this_t::kernel_config_store_base_t*
    ControllerBase::ptrKernelConfigStore() SIXTRL_NOEXCEPT
    {
        return const_cast< _this_t::kernel_config_store_base_t* >(
            static_cast< _this_t const& >( *this ).ptrKernelConfigStore() );
    }

    _this_t::kernel_config_store_base_t&
    ControllerBase::kernelConfigStore()
    {
        return const_cast< _this_t::kernel_config_store_base_t& >(
            static_cast< _this_t const& >( *this ).kernelConfigStore() );
    }

    /* --------------------------------------------------------------------- */

    _this_t::status_t ControllerBase::doSyncWithKernelSetBaseImpl(
            _this_t::kernel_lock_t const& SIXTRL_RESTRICT_REF lock )
    {
        using kernel_set_id_t = _this_t::kernel_set_id_t;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( this->hasKernelConfigStore() ) &&
            ( this->hasKernelSet( lock ) ) )
        {
            kernel_set_id_t const kernel_set_id = this->kernelSetId( lock );

            SIXTRL_ASSERT( this->checkKernelLock( lock ) );
            SIXTRL_ASSERT( kernel_set_id != _this_t::ILLEGAL_KERNEL_SET_ID );

            SIXTRL_ASSERT( this->ptrKernelConfigStore()->hasKernelSet(
            lock, kernel_set_id ) );

            SIXTRL_ASSERT( this->ptrKernelConfigStore()->ptrKernelSetBase(
            lock, kernel_set_id ) == this->ptrKernelSet( lock ) );

            status = this->ptrKernelConfigStore()->updateKernelSet(
            lock, kernel_set_id );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                if( !this->ptrKernelSet( lock )->isSyncWith(
                    this->m_expected_kernel_set_sync_id ) )
                {
                    status = this->doFetchOpFlagsAndSyncIdFromKernelSet(
                        lock, kernel_set_id );
                }

                SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                    ( this->ptrKernelSet( lock )->isSyncWith(
                    this->m_expected_kernel_set_sync_id ) ) );
            }
        }

        return status;
    }

    _this_t::status_t ControllerBase::doInitKernelConfigStore(
        _this_t::kernel_lock_t const& SIXTRL_RESTRICT kernel_lock,
        _this_t::kernel_config_store_base_t* SIXTRL_RESTRICT kernel_conf_store )
    {
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( kernel_conf_store != nullptr ) &&
            ( kernel_conf_store->checkLock( kernel_lock ) ) )
        {
            SIXTRL_ASSERT(
                ( this->m_my_own_kernel_config_store.get() == nullptr ) &&
                ( this->m_ptr_kernel_config_store == nullptr ) &&
                ( this->m_ptr_kernel_set == nullptr ) &&
                ( this->m_kernel_set_id == _this_t::ILLEGAL_KERNEL_SET_ID ) );

            this->m_ptr_kernel_config_store = kernel_conf_store;
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    _this_t::status_t ControllerBase::doInitKernelConfigStore(
        _this_t::kernel_lock_t const& SIXTRL_RESTRICT kernel_lock,
        _this_t::ptr_kernel_config_store_t&& kernel_conf_store )
    {
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( kernel_conf_store.get() != nullptr ) &&
            ( kernel_conf_store->checkLock( kernel_lock ) ) )
        {
            SIXTRL_ASSERT(
                ( this->m_my_own_kernel_config_store.get() == nullptr ) &&
                ( this->m_ptr_kernel_config_store == nullptr ) &&
                ( this->m_ptr_kernel_set == nullptr ) &&
                ( this->m_kernel_set_id == _this_t::ILLEGAL_KERNEL_SET_ID ) );

            this->m_ptr_kernel_config_store = kernel_conf_store.get();
            this->m_my_own_kernel_config_store = std::move( kernel_conf_store );
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    _this_t::status_t ControllerBase::doInitKernelSet(
        _this_t::kernel_lock_t const& SIXTRL_RESTRICT kernel_lock,
        _this_t::kernel_set_id_t const kernel_set_id )
    {
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( this->m_ptr_kernel_config_store != nullptr ) &&
            ( this->m_ptr_kernel_config_store->checkLock( kernel_lock ) ) &&
            ( this->m_ptr_kernel_set == nullptr ) &&
            ( this->m_kernel_set_id  == _this_t::ILLEGAL_KERNEL_SET_ID ) &&
            ( this->m_ptr_kernel_config_store->hasKernelSet(
                kernel_lock, kernel_set_id ) ) )
        {
            _this_t::kernel_set_base_t* ptr_kernel_set_base =
                this->m_ptr_kernel_config_store->ptrKernelSetBase(
                    kernel_lock, kernel_set_id );

            if( ( ptr_kernel_set_base != nullptr ) &&
                ( ptr_kernel_set_base->isForControllers() ) )
            {
                _this_t::kernel_set_t* ptr_kernel_set = static_cast<
                    _this_t::kernel_set_t* >( ptr_kernel_set_base );

                this->m_ptr_kernel_set = ptr_kernel_set;
                this->m_kernel_set_id  = kernel_set_id;
                status = st::ARCH_STATUS_SUCCESS;
            }
        }

        return status;
    }
}

#endif /* C++, host */

/* end: sixtracklib/common/control/controller_base.cpp */
