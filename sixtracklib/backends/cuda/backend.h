#ifndef SIXTRACKLIB_BACKENDS_CUDA_BACKEND_BACKEND_H__
#define SIXTRACKLIB_BACKENDS_CUDA_BACKEND_BACKEND_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/backends/cuda/definitions.h"
    #include "sixtracklib_base/backend/node_backend.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    class SIXTRL_EXPORT_API CudaBackend :
        public SIXTRL_CXX_NAMESPACE::BaseNodeBackend
    {
        public:

        SIXTRL_HOST_FN CudaBackend();
        SIXTRL_HOST_FN CudaBackend( CudaBackend const& ) = delete;
        SIXTRL_HOST_FN CudaBackend( CudaBackend&& ) = default;
        SIXTRL_HOST_FN CudaBackend& operator=( CudaBackend const& ) = delete;
        SIXTRL_HOST_FN CudaBackend& operator=( CudaBackend&& ) = default;
        SIXTRL_HOST_FN virtual ~CudaBackend() = default;

        protected:

        SIXTRL_HOST_FN status_t do_make_ready() override;
    };

    SIXTRL_EXPORT_API SIXTRL_HOST_FN CudaBackend* Cuda_init_backend();

    SIXTRL_EXPORT_API SIXTRL_HOST_FN
    CudaBackend* Cuda_init_backend_with_config_file(
        CudaBackend::fs_string_type const& SIXTRL_RESTRICT_REF path_to_conf );

    SIXTRL_EXPORT_API SIXTRL_HOST_FN CudaBackend*
    Cuda_init_backend_with_config_string(
        CudaBackend::string_type const& SIXTRL_RESTRICT_REF config_string );

} /* ns: SIXTRL_CXX_NAMESPACE */

extern "C" { typedef SIXTRL_CXX_NAMESPACE::CudaBackend NS(CudaBackend); }

#else /* C++, Host */

struct NS(CudaBackend);

#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_EXPORT_API SIXTRL_HOST_FN
NS(CudaBackend)* NS(Cuda_init_backend)( void );

SIXTRL_EXPORT_API SIXTRL_HOST_FN
NS(CudaBackend)* NS(Cuda_init_backend_with_config_file)(
    char const* SIXTRL_RESTRICT path_to_conf );

SIXTRL_EXPORT_API SIXTRL_HOST_FN
NS(CudaBackend)* NS(Cuda_init_backend_with_config_string)(
    char const* SIXTRL_RESTRICT config_string );

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_BACKENDS_CUDA_BACKEND_BACKEND_H__ */

