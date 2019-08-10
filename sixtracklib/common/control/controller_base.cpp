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
        ControllerBase::kernel_lock_t const& SIXTRL_RESTRICT_REF lock,
        ControllerBase::ptr_arg_base_t SIXTRL_RESTRICT arg,
        const void *const SIXTRL_RESTRICT src_begin,
        ControllerBase::size_type const src_size )
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

    ControllerBase::status_t ControllerBase::send(
        ControllerBase::kernel_lock_t const& SIXTRL_RESTRICT_REF lock,
        ControllerBase::ptr_arg_base_t SIXTRL_RESTRICT arg,
        const ControllerBase::c_buffer_t *const SIXTRL_RESTRICT source,
        ControllerBase::perform_remap_flag_t const perform_remap_flag )
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

    ControllerBase::status_t ControllerBase::send(
        ControllerBase::kernel_lock_t const& SIXTRL_RESTRICT_REF lock,
        ControllerBase::ptr_arg_base_t SIXTRL_RESTRICT arg,
        ControllerBase::buffer_t const& SIXTRL_RESTRICT_REF source,
        ControllerBase::perform_remap_flag_t const perform_remap_flag )
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

    ControllerBase::status_t ControllerBase::receive(
        ControllerBase::kernel_lock_t const& SIXTRL_RESTRICT_REF lock,
        void* SIXTRL_RESTRICT dest_begin,
        ControllerBase::size_type const dest_capacity,
        ControllerBase::ptr_arg_base_t SIXTRL_RESTRICT src_arg,
        ControllerBase::perform_remap_flag_t const perform_remap_flag )
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

    ControllerBase::status_t ControllerBase::receive(
        ControllerBase::kernel_lock_t const& SIXTRL_RESTRICT_REF lock,
        ControllerBase::c_buffer_t* SIXTRL_RESTRICT destination,
        ControllerBase::ptr_arg_base_t SIXTRL_RESTRICT src_arg,
        ControllerBase::perform_remap_flag_t const perform_remap_flag )
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

    ControllerBase::status_t ControllerBase::receive(
        ControllerBase::kernel_lock_t const& SIXTRL_RESTRICT_REF lock,
        ControllerBase::buffer_t& SIXTRL_RESTRICT_REF destination,
        ControllerBase::ptr_arg_base_t SIXTRL_RESTRICT src_arg,
        ControllerBase::perform_remap_flag_t const perform_remap_flag )
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

    ControllerBase::status_t ControllerBase::remap(
        ControllerBase::ptr_arg_base_t SIXTRL_RESTRICT ptr_arg )
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

    /* --------------------------------------------------------------------- */

    ControllerBase::status_t ControllerBase::doSyncWithKernelSetBaseImpl(
            ControllerBase::kernel_lock_t const& SIXTRL_RESTRICT_REF lock )
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
            lock, kernel_set_id ) == this->ptrKernelSetBase( lock ) );

            status = this->ptrKernelConfigStore()->updateKernelSet(
            lock, kernel_set_id );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                if( !this->ptrKernelSetBase()->isSyncWith(
                    this->m_expected_kernel_set_sync_id ) )
                {
                    status = this->doFetchOpFlagsAndSyncIdFromKernelSet(
                        lock, kernel_set_id );
                }

                SIXTRL_ASSERT( ( status != st::ARCH_STATUS_SUCCESS ) ||
                    ( this->ptrKernelSetBase( lock )->isSyncWith(
                    this->m_expected_kernel_set_sync_id ) ) );
            }
        }

        return status;
    }

    ControllerBase::status_t ControllerBase::doSyncWithKernelSet(
        ControllerBase::kernel_lock_t const& SIXTRL_RESTRICT_REF lock )
    {
        return this->doSyncWithKernelSetBaseImpl( lock );
    }

    bool ControllerBase::hasRemapBufferKernel( ControllerBase::kernel_lock_t
        const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
       return ( this->remapBufferKernelConfigId( lock ) !=
        _this_t::ILLEGAL_KERNEL_CONFIG_ID );
    }

    ControllerBase::kernel_id_t ControllerBase::remapBufferKernelConfigId(
        ControllerBase::kernel_lock_t const& SIXTRL_RESTRICT_REF
            lock ) const SIXTRL_NOEXCEPT
    {
        _this_t::kernel_id_t kernel_id = _this_t::ILLEGAL_KERNEL_CONFIG_ID;

        if( (  this->ptrKernelSetBase( lock ) != nullptr ) &&
            (  this->ptrKernelConfigStore() != nullptr ) &&
            (  this->ptrKernelConfigStore() ==
              &this->ptrKernelSetBase( lock )->kernelConfigStore() ) )
        {
            kernel_id = this->ptrKernelSetBase( lock )->kernelConfigId(
                lock, _this_t::PURPOSE_REMAP_BUFFER );
        }

        SIXTRL_ASSERT( ( kernel_id == _this_t::ILLEGAL_KERNEL_CONFIG_ID ) ||
            ( ( this->kernelSetId( lock ) != _this_t::ILLEGAL_KERNEL_SET_ID ) &&
              ( this->ptrKernelConfigStore()->checkLock( lock ) ) &&
              ( this->ptrKernelSetBase( lock ) ==
                this->ptrKernelConfigStore()->ptrKernelSetBase(
                    lock, this->kernelSetId( lock ) ) ) &&
              ( this->ptrKernelSetBase( lock )->ptrKernelConfigBase(
                lock, kernel_id ) != nullptr ) &&
              ( this->ptrKernelConfigStore()->ptrKernelConfigBase(
                    lock, kernel_id ) ==
                this->ptrKernelSetBase( lock )->ptrKernelConfigBase(
                    lock, kernel_id ) ) &&
              ( this->ptrKernelConfigStore()->ptrKernelConfigBase(
                    lock, kernel_id )->isAttachedToSet(
                        this->kernelSetId( lock ) ) ) ) );

        return kernel_id;
    }

    ControllerBase::kernel_config_key_t const&
    ControllerBase::remapBufferKernelConfigKey( ControllerBase::kernel_lock_t
        const& SIXTRL_RESTRICT_REF lock ) const
    {
        if( (  this->ptrKernelSetBase( lock ) != nullptr ) &&
            (  this->ptrKernelConfigStore() != nullptr ) &&
            (  this->ptrKernelConfigStore() ==
              &this->ptrKernelSetBase( lock )->kernelConfigStore() ) )
        {
            return this->ptrKernelSetBase( lock )->kernelConfigKey(
                lock, _this_t::PURPOSE_REMAP_BUFFER );
        }

        throw std::runtime_error(
            "unable to obtain remapBufferKernelConfigKey() from kernel set" );
    }

    /* --------------------------------------------------------------------- */

    ControllerBase::status_t ControllerBase::changeVariantFlags(
        ControllerBase::kernel_lock_t const& SIXTRL_RESTRICT_REF lock,
        ControllerBase::variant_t const new_variant_flags )
    {
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( this->checkKernelLock( lock ) )
        {
            status = this->doChangeVariantFlags( new_variant_flags );
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

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

    /* --------------------------------------------------------------------- */

    ControllerBase::ControllerBase(
        _this_t::arch_id_t const arch_id,
        _this_t::kernel_config_store_base_t* SIXTRL_RESTRICT ptr_store,
        _this_t::kernel_set_id_t const kernel_set_id,
        char const* SIXTRL_RESTRICT config_str ) :
        _this_t::_base_arch_obj_t( arch_id,
            _this_t::_base_arch_obj_t::DEFAULT_VARIANT, config_str ),
        m_default_key( arch_id ), m_name(),
        m_my_own_kernel_config_store( nullptr ),
        m_ptr_kernel_config_store( ptr_store ),
        m_op_flags( st::KERNEL_OP_FLAGS_NONE ),
        m_expected_kernel_set_sync_id( _this_t::ILLEGAL_SYNC_ID_VALUE ),
        m_kernel_set_id( _this_t::ILLEGAL_KERNEL_SET_ID ),
        m_uses_nodes( false )
    {
        if( ptr_store != nullptr )
        {
            _this_t::kernel_lock_t lock( *ptr_store->lockable() );
            _this_t::status_t status = this->doAssignPtrKernelConfigStore(
                lock, ptr_store );

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( kernel_set_id != _this_t::ILLEGAL_KERNEL_SET_ID ) )
            {
                status = this->doUpdateKernelSet( lock, kernel_set_id );
            }

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( this->ptrKernelSetBase( lock ) != nullptr ) )
            {
                status = this->doFetchOpFlagsAndSyncIdFromKernelSet(
                    lock, kernel_set_id );
            }
        }
    }

    ControllerBase::ControllerBase(
        _this_t::arch_id_t const arch_id,
        _this_t::ptr_kernel_config_store_t&& kernel_config_store,
        _this_t::kernel_set_id_t const kernel_set_id,
        char const* SIXTRL_RESTRICT config_str ) :
        _this_t::_base_arch_obj_t( arch_id,
            _this_t::_base_arch_obj_t::DEFAULT_VARIANT, config_str ),
        m_default_key( arch_id ), m_name(),
        m_my_own_kernel_config_store( nullptr ),
        m_ptr_kernel_config_store(),
        m_op_flags( st::KERNEL_OP_FLAGS_NONE ),
        m_expected_kernel_set_sync_id( _this_t::ILLEGAL_SYNC_ID_VALUE ),
        m_kernel_set_id( _this_t::ILLEGAL_KERNEL_SET_ID ),
        m_uses_nodes( false )
    {
        if( kernel_config_store.get() != nullptr )
        {
            _this_t::kernel_lock_t lock( *kernel_config_store->lockable() );
            _this_t::status_t status = this->doUpdateOwnKernelConfigStore(
                lock, std::move( kernel_config_store ) );

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( kernel_set_id != _this_t::ILLEGAL_KERNEL_SET_ID ) )
            {
                status = this->doUpdateKernelSet( lock, kernel_set_id );
            }

            if( ( status == st::ARCH_STATUS_SUCCESS ) &&
                ( this->ptrKernelSetBase( lock ) != nullptr ) )
            {
                status = this->doFetchOpFlagsAndSyncIdFromKernelSet(
                    lock, kernel_set_id );
            }
        }
    }

    void ControllerBase::doClear(
        ControllerBase::kernel_lock_t const& SIXTRL_RESTRICT_REF lock )
    {
        if( this->hasKernelSet( lock ) )
        {
            _this_t::kernel_set_t* ptr_kernel_set =
                this->ptrKernelSetBase( lock );

            if( ptr_kernel_set != nullptr )
            {
                ptr_kernel_set->reset( lock );
            }

            this->doResetOpFlagsAndSyncId();
        }

        return;
    }

    /* --------------------------------------------------------------------- */

    ControllerBase::status_t ControllerBase::doChangeVariantFlags(
        ControllerBase::variant_t const new_variant_flags )
    {
        using _this_t = st::ControllerBase;
        using _base_t = _this_t::_base_arch_obj_t;
        using kset_t  = _this_t::kernel_set_t;

        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( !this->hasKernelConfigStore() )
        {
            return status;
        }

        _this_t::kernel_lock_t const lock( *this->kernelLockable() );

        if( !this->hasKernelSet( lock ) )
        {
            return status;
        }

        if( ( !this->isSyncWithKernelSet() ) &&
            (  this->syncWithKernelSet( lock ) != st::ARCH_STATUS_SUCCESS ) )
        {
            return status;
        }

        SIXTRL_ASSERT( this->isSyncWithKernelSet() );

        kset_t& kernel_set = *this->ptrKernelSetBase( lock );
        kset_t const& const_kernel_set = kernel_set;

        bool const current_key_valid =
            const_kernel_set.currentKernelConfigKey( lock ).valid();

        if( ( current_key_valid ) &&
            ( const_kernel_set.currentKernelConfigKey( lock ).archId() !=
                this->archId() ) )
        {
            return status;
        }

        _this_t::kernel_config_key_t key;

        if( current_key_valid )
        {
            key = const_kernel_set.currentKernelConfigKey( lock );
        }
        else if( this->defaultKey().valid() )
        {
            key = this->defaultKey();
        }

        if( !key.valid() ) return status;

        if( ( current_key_valid ) &&
            ( key.variant() == new_variant_flags ) )
        {
            return st::ARCH_STATUS_SUCCESS;
        }

        /* ----------------------------------------------------------------- */
        /* if we are here, the "easy" cases are not applicable:
         * - key points to either current_key or default key
         * - key is valid
         * - key.variant() differs from the new_variant_flags */


        key.setVariant( new_variant_flags );
        SIXTRL_ASSERT( key.valid() );

        if( const_kernel_set.canSwitchKernels( lock, key ) )
        {
            status = kernel_set.switchKernels( lock, key );

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                status = _base_t::doChangeVariantFlags( new_variant_flags );
            }

            if( status == st::ARCH_STATUS_SUCCESS )
            {
                /* We save the send and receive flags as these would otherwise
                  * be overwritten by the update process.
                  * If a different behaviour is required, please
                  * explicitly set send/receive to false before calling
                  * this function and re-initilizae the flags afterwards */

                static constexpr _this_t::op_flags_t FLAGS_TO_SAVE =
                    st::KERNEL_OP_CTRL_READY_TO_SEND |
                    st::KERNEL_OP_CTRL_READY_TO_RECEIVE;

                status = this->doFetchOpFlagsAndSyncIdFromKernelSet(
                    lock, this->kernelSetId( lock ), FLAGS_TO_SAVE );
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

            output << "Debug mode      : "
                   << std::boolalpha << this->isInDebugMode()
                   << std::noboolalpha << "\r\n";

            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    /* --------------------------------------------------------------------- */

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

    _this_t::status_t ControllerBase::doUpdateOwnKernelConfigStore(
        _this_t::kernel_lock_t& SIXTRL_RESTRICT lock,
        _this_t::ptr_kernel_config_store_t&& kernel_conf_store )
    {
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        _this_t::ptr_kernel_config_store_t temp_store( nullptr );

        if( ( kernel_conf_store.get() != nullptr ) &&
            ( kernel_conf_store->checkLock( lock ) ) )
        {
            if( ( this->m_my_own_kernel_config_store.get() == nullptr ) &&
                ( this->m_ptr_kernel_config_store == nullptr ) &&
                ( this->m_kernel_set_id == _this_t::ILLEGAL_KERNEL_SET_ID ) &&
                ( this->m_ptr_kernel_set == nullptr ) )
            {
                this->m_ptr_kernel_config_store = kernel_conf_store.get();
                this->m_my_own_kernel_config_store = std::move(
                    kernel_conf_store );

                if( this->m_my_own_kernel_config_store.get() ==
                    this->m_ptr_kernel_config_store )
                {
                    status = st::ARCH_STATUS_SUCCESS;
                }
            }
            else if( this->m_ptr_kernel_config_store != nullptr )
            {
                if( ( kernel_conf_store.get() == this->m_ptr_kernel_config_store ) &&
                    ( this->m_my_own_kernel_config_store.get() == nullptr ) )
                {
                    this->m_my_own_kernel_config_store = std::move(
                        kernel_conf_store );
                }
                else if( ( this->m_ptr_kernel_set == nullptr ) &&
                    ( this->m_kernel_set_id == _this_t::ILLEGAL_KERNEL_SET_ID ) )
                {
                    this->m_ptr_kernel_config_store = kernel_conf_store.get();
                    this->m_my_own_kernel_config_store = std::move(
                        kernel_conf_store );
                }
                else
                {
                    this->m_kernel_set_id = _this_t::ILLEGAL_KERNEL_SET_ID;
                    this->m_ptr_kernel_set = nullptr;

                    this->doResetOpFlagsAndSyncId();

                    this->m_ptr_kernel_config_store = kernel_conf_store.get();
                    this->m_my_own_kernel_config_store = std::move(
                        kernel_conf_store );
                }

                if( ( kernel_conf_store.get() == nullptr ) &&
                    ( this->m_my_own_kernel_config_store.get() ==
                        this->m_ptr_kernel_config_store ) )
                {
                    status = st::ARCH_STATUS_SUCCESS;
                }
            }
        }
        else if( ( kernel_conf_store.get() == nullptr ) &&
                 ( this->m_ptr_kernel_config_store != nullptr ) &&
                 ( this->m_ptr_kernel_config_store->checkLock( lock ) ) )
        {
            if( this->m_my_own_kernel_config_store.get() != nullptr )
            {
                SIXTRL_ASSERT( this->m_my_own_kernel_config_store.get() ==
                               this->m_ptr_kernel_config_store );

                temp_store = std::move( this->m_my_own_kernel_config_store );
            }

            this->m_ptr_kernel_config_store = nullptr;
            this->m_kernel_set_id = _this_t::ILLEGAL_KERNEL_SET_ID;
            this->m_ptr_kernel_set = nullptr;

            status = st::ARCH_STATUS_SUCCESS;
        }

        if( ( status == st::ARCH_STATUS_SUCCESS ) &&
            ( temp_store.get() != nullptr ) )
        {
            lock.unlock();
        }

        return status;
    }

    _this_t::status_t ControllerBase::doAssignPtrKernelConfigStore(
        _this_t::kernel_lock_t& SIXTRL_RESTRICT_REF lock,
        _this_t::kernel_config_store_base_t* SIXTRL_RESTRICT ptr_store )
    {
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( ptr_store != nullptr ) && ( ptr_store->checkLock( lock ) ) )
        {
            if( ( this->m_ptr_kernel_config_store == nullptr ) &&
                ( this->m_kernel_set_id == _this_t::ILLEGAL_KERNEL_SET_ID ) &&
                ( this->m_ptr_kernel_set == nullptr ) )
            {
                SIXTRL_ASSERT( this->m_my_own_kernel_config_store.get()
                    == nullptr );

                this->m_ptr_kernel_config_store = ptr_store;
                status = st::ARCH_STATUS_SUCCESS;
            }
            else if( this->m_ptr_kernel_config_store == ptr_store )
            {
                status = st::ARCH_STATUS_SUCCESS;
            }
            else if( this->m_ptr_kernel_config_store != nullptr )
            {
                _this_t::ptr_kernel_config_store_t temp_store( nullptr );
                _this_t::kernel_config_store_base_t* ptr_temp = nullptr;

                _this_t::kernel_lock_t old_lock(
                    *this->m_ptr_kernel_config_store->lockable() );

                ptr_temp = this->m_ptr_kernel_config_store;

                if( this->m_my_own_kernel_config_store.get() != nullptr )
                {
                    temp_store = std::move( this->m_my_own_kernel_config_store );
                }

                SIXTRL_ASSERT( this->m_my_own_kernel_config_store.get()
                    == nullptr );

                if( ( this->m_kernel_set_id != _this_t::ILLEGAL_KERNEL_SET_ID ) ||
                    ( this->m_ptr_kernel_set == nullptr ) )
                {
                    this->m_kernel_set_id = _this_t::ILLEGAL_KERNEL_SET_ID;
                    this->m_ptr_kernel_set = nullptr;
                }

                this->doResetOpFlagsAndSyncId();

                this->m_ptr_kernel_config_store = ptr_store;

                if( ( ptr_temp != nullptr ) &&
                    ( ptr_temp->checkLock( old_lock ) ) )
                {
                    status = st::ARCH_STATUS_SUCCESS;
                    old_lock.unlock();
                }
            }
        }

        return status;
    }

    _this_t::status_t ControllerBase::doUpdateKernelSet(
        _this_t::kernel_lock_t const& SIXTRL_RESTRICT_REF lock,
        _this_t::kernel_set_id_t const kernel_set_id )
    {
        _this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( this->ptrKernelConfigStore() != nullptr ) &&
            ( this->ptrKernelConfigStore()->checkLock( lock ) ) )
        {
            if( this->kernelSetId( lock ) != kernel_set_id )
            {
                if( ( kernel_set_id != _this_t::ILLEGAL_KERNEL_SET_ID ) &&
                    ( this->ptrKernelConfigStore()->hasKernelSet(
                        lock, kernel_set_id ) ) )
                {
                    _this_t::kernel_set_id_t const saved_kernel_set_id =
                        this->kernelSetId( lock );

                    _this_t::kernel_set_t* ptr_saved_kernel_set =
                        this->ptrKernelSetBase( lock );

                    if( this->ptrKernelSetBase( lock ) != nullptr )
                    {
                        this->doResetOpFlagsAndSyncId();
                    }

                    this->m_kernel_set_id = kernel_set_id;
                    this->m_ptr_kernel_set = this->ptrKernelConfigStore(
                        )->ptrKernelSetBase( lock, kernel_set_id );

                    if( ( this->ptrKernelSetBase( lock ) != nullptr ) &&
                        ( this->kernelSetId( lock ) !=
                            _this_t::ILLEGAL_KERNEL_SET_ID ) )
                    {
                        status = this->syncWithKernelSet( lock );
                    }

                    if( status != st::ARCH_STATUS_SUCCESS )
                    {
                        this->m_kernel_set_id = saved_kernel_set_id;
                        this->m_ptr_kernel_set = ptr_saved_kernel_set;
                    }
                }
                else if( kernel_set_id == _this_t::ILLEGAL_KERNEL_SET_ID )
                {
                    this->m_kernel_set_id = kernel_set_id;
                    this->m_ptr_kernel_set = nullptr;
                    this->doResetOpFlagsAndSyncId();
                }
            }
            else if( this->ptrKernelConfigStore()->hasKernelSet(
                lock, kernel_set_id ) )
            {
                status = st::ARCH_STATUS_SUCCESS;
            }
        }

        return status;
    }
}

#endif /* C++, host */

/* end: sixtracklib/common/control/controller_base.cpp */
