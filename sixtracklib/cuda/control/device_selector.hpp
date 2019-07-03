#ifndef SIXTRACKLIB_CUDA_CONTROL_DEVICE_SELECTOR_CXX_HPP__
#define SIXTRACKLIB_CUDA_CONTROL_DEVICE_SELECTOR_CXX_HPP__

#if defined( __cplusplus   ) && !defined( _GPUCODE ) && \
   !defined( __CUDA_ARCH__ ) && !defined( __CUDACC__ )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cstddef>
    #include <cstdlib>
    #include <mutex>
    #include <thread>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

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

        using lockable_t     = std::mutex;
        using lock_t         = std::unique_lock< lockable_t >;
        using device_index_t = SIXTRL_CXX_NAMESPACE::cuda_dev_index_t;
        using status_t       = SIXTRL_CXX_NAMESPACE::arch_status_t;
        using size_type      = SIXTRL_CXX_NAMESPACE::arch_size_t;

        static constexpr device_index_t
            ILLEGAL_CUDA_DEVICE_INDEX = device_index_t{ -1 };

        SIXTRL_HOST_FN CudaDeviceSelector();

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

        SIXTRL_HOST_FN device_index_t minDeviceIndex() const;
        SIXTRL_HOST_FN device_index_t minDeviceIndex(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN device_index_t maxDeviceIndex() const;
        SIXTRL_HOST_FN device_index_t maxDeviceIndex(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type numAvailableDevices() const;
        SIXTRL_HOST_FN size_type numAvailableDevices(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t reset();
        SIXTRL_HOST_FN status_t reset(
            lock_t const& SIXTRL_RESTRICT_REF lock );

        SIXTRL_HOST_FN device_index_t deviceIndex() const;
        SIXTRL_HOST_FN device_index_t deviceIndex(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_t setDeviceIndex(
            device_index_t const device_idx );

        SIXTRL_HOST_FN status_t setDeviceIndex(
            device_index_t const device_idx,
            lock_t const& SIXTRL_RESTRICT_REF lock );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN lockable_t* lockable() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool checkLock(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool checkLockAndThrowOnError(
            lock_t const& SIXTRL_RESTRICT_REF lock ) const;

        private:

        mutable lockable_t  m_lockable;
        size_type           m_num_available_devices;

        device_index_t      m_selected_device;
        device_index_t      m_min_device_index;
        device_index_t      m_max_device_index;
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
        using CudaDeviceSelector::

        st::CudaDeviceSelector::lock_t lock( *this->lockable() );
        return ( ( this->checkLock( lock ) ) &&
                 ( this->m_num_available_devices >
    }

    SIXTRL_INLINE bool CudaDeviceSelector::hasDevices(
            CudaDeviceSelector::lock_t const& SIXTRL_RESTRICT_REF lock
        ) const SIXTRL_NOEXCEPT
    {

    }

    SIXTRL_INLINE bool CudaDeviceSelector::hasSelectedDevice() const
    {

    }

    SIXTRL_INLINE bool CudaDeviceSelector::hasSelectedDevice(
            CudaDeviceSelector::lock_t const& SIXTRL_RESTRICT_REF lock
        ) const SIXTRL_NOEXCEPT
    {

    }

    SIXTRL_INLINE CudaDeviceSelector::device_index_t
    CudaDeviceSelector::minDeviceIndex() const
    {

    }

    SIXTRL_INLINE CudaDeviceSelector::device_index_t
    CudaDeviceSelector::minDeviceIndex( CudaDeviceSelector::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {

    }

    SIXTRL_INLINE CudaDeviceSelector::device_index_t
    CudaDeviceSelector::maxDeviceIndex() const
    {

    }

    SIXTRL_INLINE CudaDeviceSelector::device_index_t
    CudaDeviceSelector::maxDeviceIndex( CudaDeviceSelector::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {

    }

    SIXTRL_INLINE CudaDeviceSelector::size_type
    CudaDeviceSelector::numAvailableDevices() const
    {

    }

    SIXTRL_INLINE CudaDeviceSelector::size_type
    CudaDeviceSelector::numAvailableDevices( CudaDeviceSelector::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {

    }

    SIXTRL_INLINE CudaDeviceSelector::status_t CudaDeviceSelector::reset()
    {
        st::CudaDeviceSelector::lock_t lock( *this->lockable() );
        SIXTRL_ASSERT( this->checkLockAndThrowOnError( lock ) );
        return this->reset( lock );
    }

    SIXTRL_INLINE CudaDeviceSelector::device_index_t
    CudaDeviceSelector::deviceIndex() const
    {
        st::CudaDeviceSelector::lock_t lock( *this->lockable() );
        SIXTRL_ASSERT( this->checkLockAndThrowOnError( lock ) );
        return this->m_selected_device;
    }

    SIXTRL_INLINE CudaDeviceSelector::device_index_t
    CudaDeviceSelector::deviceIndex( CudaDeviceSelector::lock_t const&
        SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT
    {
        return ( this->checkLock( lock ) )
            ? this->m_selected_device
            : st::CudaDeviceSelector::ILLEGAL_CUDA_DEVICE_INDEX;
    }

    SIXTRL_INLINE CudaDeviceSelector::status_t
    CudaDeviceSelector::setDeviceIndex( CudaDeviceSelector::device_index_t
        const device_idx )
    {
        st::CudaDeviceSelector::lock_t lock( *this->lockable() );
        SIXTRL_ASSERT( this->checkLockAndThrowOnError( lock ) );
        return this->setDeviceIndex( lock, device_idx );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE CudaDeviceSelector::lockable_t*
    CudaDeviceSelector::lockable() const SIXTRL_NOEXCEPT
    {
        return &this->m_lockable;
    }

    SIXTRL_INLINE bool CudaDeviceSelector::checkLock(
            CudaDeviceSelector::lock_t const& SIXTRL_RESTRICT_REF lock
        ) const SIXTRL_NOEXCEPT
    {
        return ( ( lock.owns_lock() ) &&
                 ( lock.mutex() == this->lockable() ) );
    }
}

#endif /* C++, Host */

#endif /* SIXTRACKLIB_CUDA_CONTROL_DEVICE_SELECTOR_CXX_HPP__ */

/* end: sixtracklib/cuda/control/device_selector.hpp */
