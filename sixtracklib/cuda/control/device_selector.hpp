#ifndef SIXTRACKLIB_CUDA_CONTROL_DEVICE_SELECTOR_CXX_HPP__
#define SIXTRACKLIB_CUDA_CONTROL_DEVICE_SELECTOR_CXX_HPP__

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cstddef>
    #include <cstdlib>
    #include <memory>
    #include <mutex>
    #include <thread>
    #include <utility>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/node_store.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#endif /* C++, Host */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/cuda/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

namespace SIXTRL_CXX_NAMESPACE
{
    class CudaDeviceSelector
    {
        public:

        using node_store_t     = SIXTRL_CXX_NAMESPACE::NodeStore;
        using lockable_t       = node_store_t::lockable_t;
        using lock_t           = node_store_t::lock_t;
        using cuda_dev_index_t = SIXTRL_CXX_NAMESPACE::cuda_dev_index_t;
        using status_t         = SIXTRL_CXX_NAMESPACE::arch_status_t;
        using size_type        = SIXTRL_CXX_NAMESPACE::arch_size_t;

        static constexpr cuda_dev_index_t
            ILLEGAL_CUDA_DEVICE_INDEX = cuda_dev_index_t{ -1 };

        SIXTRL_HOST_FN CudaDeviceSelector();
        SIXTRL_HOST_FN explicit CudaDeviceSelector(
            node_store_t& SIXTRL_RESTRICT_REF node_store );

        SIXTRL_HOST_FN CudaDeviceSelector(
            CudaDeviceSelector const& other ) = delete;

        SIXTRL_HOST_FN CudaDeviceSelector(
            CudaDeviceSelector&& other ) = delete;

        SIXTRL_HOST_FN CudaDeviceSelector& CudaDeviceSelector=(
            CudaDeviceSelector const& rhs ) = delete;

        SIXTRL_HOST_FN CudaDeviceSelector& CudaDeviceSelector=(
            CudaDeviceSelector&& rhs ) = delete;

        SIXTRL_HOST_FN CudaDeviceSelector~() = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool hasDevices() const;
        SIXTRL_HOST_FN bool hasDevices(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool hasSelectedDevice() const;
        SIXTRL_HOST_FN bool hasSelectedDevice(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN cuda_dev_index_t minDeviceIndex() const;
        SIXTRL_HOST_FN cuda_dev_index_t minDeviceIndex(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN cuda_dev_index_t maxDeviceIndex() const;
        SIXTRL_HOST_FN cuda_dev_index_t maxDeviceIndex(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type numAvailableDevices() const;
        SIXTRL_HOST_FN size_type numAvailableDevices(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_t reset();

        SIXTRL_HOST_FN status_t reset(
            lock_t const& SIXTRL_RESTRICT_REF lock );

        SIXTRL_HOST_FN status_t reset(
            node_store_t& SIXTRL_RESTRICT_REF node_store );

        SIXTRL_HOST_FN status_t reset(
            lock_t& SIXTRL_RESTRICT_REF old_store_lock,
            node_store_t& SIXTRL_RESTRICT_REF node_store,
            lock_t const& SIXTRL_RESTRICT_REF new_store_lock );

        SIXTRL_HOST_FN status_t resetIfDifferentNodeStore(
            node_store_t& SIXTRL_RESTRICT_REF node_store );

        SIXTRL_HOST_FN status_t resetIfDifferentNodeStore(
            lock_t& SIXTRL_RESTRICT_REF old_store_lock,
            node_store_t& SIXTRL_RESTRICT_REF node_store,
            lock_t const& SIXTRL_RESTRICT_REF new_store_lock );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN cuda_dev_index_t deviceIndex() const;
        SIXTRL_HOST_FN cuda_dev_index_t deviceIndex(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t setDeviceIndex(
            cuda_dev_index_t const device_idx );

        SIXTRL_HOST_FN status_t setDeviceIndex(
            lock_t const& SIXTRL_RESTRICT_REF lock,
            cuda_dev_index_t const device_idx );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN node_store_t const& nodeStore() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN node_store_t const* ptrNodeStore() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_store_t& nodeStore() SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN node_store_t* ptrNodeStore() SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN lockable_t* lockable() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool checkLock(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void checkLockAndThrowOnError(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const;

        private:

        node_store_t&       m_node_store;
        size_type           m_num_available_devices;

        cuda_dev_index_t    m_selected_device;
        cuda_dev_index_t    m_min_device_index;
        cuda_dev_index_t    m_max_device_index;
    };

    SIXTRL_HOST_FN CudaDeviceSelector& CudaDeviceSelector_get();
    SIXTRL_HOST_FN CudaDeviceSelector const& CudaDeviceSelector_get_const();

    SIXTRL_HOST_FN CudaDeviceSelector* CudaDeviceSelector_get_ptr();
    SIXTRL_HOST_FN CudaDeviceSelector const* CudaDeviceSelector_get_const_ptr();
}

#endif /* C++, Host */

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

namespace SIXTRL_CXX_NAMESPACE
{
    SIXTRL_INLINE CudaDeviceSelector& CudaDeviceSelector_get()
    {
        static SIXTRL_CXX_NAMESPACE::CudaDeviceSelector cuda_dev_selector;
        return cuda_dev_selector;
    }

    SIXTRL_INLINE CudaDeviceSelector const& CudaDeviceSelector_get_const()
    {
        return SIXTRL_CXX_NAMESPACE::CudaDeviceSelector_get();
    }

    SIXTRL_INLINE CudaDeviceSelector* CudaDeviceSelector_get_ptr()
    {
        return &SIXTRL_CXX_NAMESPACE::CudaDeviceSelector_get();
    }

    SIXTRL_INLINE CudaDeviceSelector const* CudaDeviceSelector_get_const_ptr()
    {
        return &SIXTRL_CXX_NAMESPACE::CudaDeviceSelector_get();
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool CudaDeviceSelector::hasDevices() const
    {
        using size_t = CudaDeviceSelector::size_type;

        st::CudaDeviceSelector::lock_t lock( *this->nodeStore().lockable() );
        return this->hasDevices( lock );
    }

    SIXTRL_INLINE bool CudaDeviceSelector::hasDevices(
            CudaDeviceSelector::lock_t const& SIXTRL_RESTRICT_REF lock
        ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->checkLock( lock ) ) &&
                 ( this->m_num_available_devices > size_t{ 0 } ) );
    }

    SIXTRL_INLINE bool CudaDeviceSelector::hasSelectedDevice() const
    {
        st::CudaDeviceSelector::lock_t lock( *this->nodeStore().lockable() );
        return this->hasSelectedDevice( lock );
    }

    SIXTRL_INLINE bool CudaDeviceSelector::hasSelectedDevice(
            CudaDeviceSelector::lock_t const& SIXTRL_RESTRICT_REF lock
        ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->checkLock( lock ) ) &&
            ( this->m_selected_device !=
                st::CudaDeviceSelector::ILLEGAL_CUDA_DEVICE_INDEX ) );
    }

    SIXTRL_INLINE CudaDeviceSelector::cuda_dev_index_t
    CudaDeviceSelector::minDeviceIndex() const
    {
        st::CudaDeviceSelector::lock_t lock( *this->nodeStore().lockable() );
        return this->minDeviceIndex( lock );
    }

    SIXTRL_INLINE CudaDeviceSelector::cuda_dev_index_t
    CudaDeviceSelector::minDeviceIndex( CudaDeviceSelector::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( this->checkLock( lock ) )
            ? this->m_min_device_index
            : st::CudaDeviceSelector::ILLEGAL_CUDA_DEVICE_INDEX;
    }

    SIXTRL_INLINE CudaDeviceSelector::cuda_dev_index_t
    CudaDeviceSelector::maxDeviceIndex() const
    {
        st::CudaDeviceSelector::lock_t lock( *this->nodeStore().lockable() );
        return this->maxDeviceIndex( lock );
    }

    SIXTRL_INLINE CudaDeviceSelector::cuda_dev_index_t
    CudaDeviceSelector::maxDeviceIndex( CudaDeviceSelector::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( this->checkLock( lock ) )
            ? this->m_max_device_index
            : st::CudaDeviceSelector::ILLEGAL_CUDA_DEVICE_INDEX;
    }

    SIXTRL_INLINE CudaDeviceSelector::size_type
    CudaDeviceSelector::numAvailableDevices() const
    {
        st::CudaDeviceSelector::lock_t lock( *this->nodeStore().lockable() );
        return this->numAvailableDevices( lock );
    }

    SIXTRL_INLINE CudaDeviceSelector::size_type
    CudaDeviceSelector::numAvailableDevices( CudaDeviceSelector::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( this->checkLock( lock ) )
            ? this->m_num_available_devices
            : st::CudaDeviceSelector::size_type{ 0 };
    }

    SIXTRL_INLINE CudaDeviceSelector::status_t CudaDeviceSelector::reset()
    {
        st::CudaDeviceSelector::lock_t lock( *this->nodeStore().lockable() );
        SIXTRL_ASSERT( this->checkLockAndThrowOnError( lock ) );
        return this->reset( lock );
    }

    SIXTRL_INLINE CudaDeviceSelector::cuda_dev_index_t
    CudaDeviceSelector::deviceIndex() const
    {
        st::CudaDeviceSelector::lock_t lock( *this->nodeStore().lockable() );
        SIXTRL_ASSERT( this->checkLockAndThrowOnError( lock ) );
        return this->m_selected_device;
    }

    SIXTRL_INLINE CudaDeviceSelector::cuda_dev_index_t
    CudaDeviceSelector::deviceIndex( CudaDeviceSelector::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( this->checkLock( lock ) )
            ? this->m_selected_device
            : st::CudaDeviceSelector::ILLEGAL_CUDA_DEVICE_INDEX;
    }

    SIXTRL_INLINE CudaDeviceSelector::status_t
    CudaDeviceSelector::setDeviceIndex( CudaDeviceSelector::cuda_dev_index_t
        const device_idx )
    {
        st::CudaDeviceSelector::lock_t lock( *this->nodeStore().lockable() );
        SIXTRL_ASSERT( this->checkLockAndThrowOnError( lock ) );
        return this->setDeviceIndex( lock, device_idx );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE CudaDeviceSelector::node_store_t const&
    CudaDeviceSelector::nodeStore() const SIXTRL_NOEXCEPT
    {
        return this->m_node_store;
    }

    SIXTRL_INLINE CudaDeviceSelector::node_store_t const*
    CudaDeviceSelector::ptrNodeStore() const SIXTRL_NOEXCEPT
    {
        return &this->m_node_store;
    }

    SIXTRL_INLINE CudaDeviceSelector::node_store_t&
    CudaDeviceSelector::nodeStore() SIXTRL_NOEXCEPT
    {
        return this->m_node_store;
    }

    SIXTRL_INLINE CudaDeviceSelector::node_store_t*
    CudaDeviceSelector::ptrNodeStore() SIXTRL_NOEXCEPT
    {
        return &this->m_node_store;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE CudaDeviceSelector::lockable_t*
    CudaDeviceSelector::lockable() const SIXTRL_NOEXCEPT
    {
        return this->nodeStore().lockable();
    }

    SIXTRL_INLINE bool CudaDeviceSelector::checkLock(
            CudaDeviceSelector::lock_t const& SIXTRL_RESTRICT_REF lock
        ) const SIXTRL_NOEXCEPT
    {
        return this->nodeStore().checkLock( lock );
    }

    SIXTRL_INLINE void CudaDeviceSelector::checkLockAndThrowOnError(
        CudaDeviceSelector::lock_t const& SIXTRL_RESTRICT_REF lock ) const
    {
        this->nodeStore().checkLockAndThrowOnError( lock );
    }
}

#endif /* C++, Host */

#endif /* SIXTRACKLIB_CUDA_CONTROL_DEVICE_SELECTOR_CXX_HPP__ */

/* end: sixtracklib/cuda/control/device_selector.hpp */