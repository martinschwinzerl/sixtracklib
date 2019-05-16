#ifndef SIXTRACKLIB_CUDA_INTERNAL_ARGUMENT_BASE_HPP__
#define SIXTRACKLIB_CUDA_INTERNAL_ARGUMENT_BASE_HPP__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus ) && !defined( _GPUCODE ) && \
       !defined( __CUDA_ARCH__ )
        #include <cstddef>
        #include <cstdlib>
        #include <memory>
        #include <string>
    #endif /* C++, Host */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/context/definitions.h"
    #include "sixtracklib/cuda/definitions.h"
    #include "sixtracklib/common/context/argument_base.hpp"
    #include "sixtracklib/common/context/context_base.hpp"
    #include "sixtracklib/common/context/context_base_with_nodes.hpp"
    #if defined( __cplusplus ) && !defined( _GPUCODE ) && \
       !defined( __CUDA_ARCH__ )
        #include "sixtracklib/common/buffer.hpp"
    #endif /* defined( __cplusplus ) */
    #include "sixtracklib/common/buffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE ) && !defined( __CUDA_ARCH__ )
namespace SIXTRL_CXX_NAMESPACE
{
    class CudaContextBase;

    class CudaArgumentBase : public SIXTRL_CXX_NAMESPACE::ArgumentBase
    {
        private:

        using _base_arg_t = SIXTRL_CXX_NAMESPACE::ArgumentBase;

        public:

        using type_id_t                = _base_arg_t::type_id_t;
        using status_t                 = _base_arg_t::status_t;
        using buffer_t                 = _base_arg_t::buffer_t;
        using c_buffer_t               = _base_arg_t::c_buffer_t;
        using size_type                = _base_arg_t::size_type;

        using ptr_base_context_t       = _base_arg_t::ptr_base_context_t;
        using ptr_const_base_context_t = _base_arg_t::ptr_const_base_context_t;
        using cuda_arg_buffer_t        = ::NS(cuda_arg_buffer_t);
        using cuda_const_arg_buffer_t  = ::NS(cuda_const_arg_buffer_t);

        SIXTRL_HOST_FN virtual ~CudaArgumentBase() SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool hasCudaArgBuffer() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN cuda_arg_buffer_t cudaArgBuffer() SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN cuda_const_arg_buffer_t cudaArgBuffer() const SIXTRL_NOEXCEPT;

        protected:

        using base_context_t = SIXTRL_CXX_NAMESPACE::CudaContextBase;
        using ptr_cuda_base_context_t       = base_context_t*;
        using ptr_cuda_base_const_context_t = base_context_t const*;

        SIXTRL_HOST_FN explicit CudaArgumentBase(
            ContextOnNodesBase* SIXTRL_RESTRICT ptr_context = nullptr );

        SIXTRL_HOST_FN explicit CudaArgumentBase(
            size_type const arg_buffer_capacity,
            ContextOnNodesBase* SIXTRL_RESTRICT ptr_context = nullptr );

        SIXTRL_HOST_FN CudaArgumentBase(
            CudaArgumentBase const& other ) = delete;

        SIXTRL_HOST_FN CudaArgumentBase( CudaArgumentBase&& other ) = delete;

        SIXTRL_HOST_FN CudaArgumentBase& operator=(
            CudaArgumentBase const& other ) = delete;

        SIXTRL_HOST_FN CudaArgumentBase& operator=(
            CudaArgumentBase&& other ) = delete;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN void doDeleteCudaArgumentBuffer() SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void doResetCudaArgumentBuffer(
            cuda_arg_buffer_t SIXTRL_RESTRICT new_arg_buffer,
            size_type const capacity );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN virtual bool doReserveArgumentBuffer(
            size_type const required_buffer_size ) override;

        private:

        SIXTRL_HOST_FN bool doReserveArgumentBufferCudaBaseImpl(
            size_type const required_buffer_size );

        cuda_arg_buffer_t m_arg_buffer;
    };
}

extern "C" {

typedef SIXTRL_CXX_NAMESPACE::CudaArgumentBase NS(CudaArgumentBase);

}

#else /* C++, Host */

typedef void  NS(CudaArgumentBase);

#endif /* C++, Host */

#endif /* SIXTRACKLIB_CUDA_INTERNAL_ARGUMENT_BASE_HPP__ */
/* end: sixtracklib/cuda/internal/argument_base.h */