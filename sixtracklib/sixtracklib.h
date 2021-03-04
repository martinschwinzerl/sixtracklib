#ifndef SIXTRACKLIB_SIXTRACKLIB_H__
#define SIXTRACKLIB_SIXTRACKLIB_H__

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/generated/namespace.h"

#include "sixtracklib/common/backends/definitions.h"
#include "sixtracklib/common/backends/definitions_cuda.h"
#include "sixtracklib/common/backends/definitions_opencl.h"
#include "sixtracklib/common/backends/helper_methods.h"
#include "sixtracklib/common/backends/backends.h"

#include "sixtracklib/common/beam_elements/definitions.h"
#include "sixtracklib/common/beam_elements/cobj_type_ids.h"
#include "sixtracklib/common/beam_elements/all_beam_elements.h"
#include "sixtracklib/common/beam_elements/all_tracking_maps.h"

#if defined( SIXTRL_DEMOTRACK_ENABLED ) && ( SIXTRL_DEMOTRACK_ENABLED == 1 )
#include "sixtracklib/common/beam_elements/demotrack.h"
#endif /* defined( SIXTRL_DEMOTRACK_ENABLED )  */

#include "sixtracklib/common/cobjects/definitions.h"
#include "sixtracklib/common/cobjects/address_manipulations.h"
#include "sixtracklib/common/cobjects/cbuffer.h"
#include "sixtracklib/common/cobjects/cbuffer_view.hpp"
#include "sixtracklib/common/cobjects/cbuffer.hpp"
#include "sixtracklib/common/cobjects/cobj_illegal_type.h"
#include "sixtracklib/common/cobjects/cobj_type_traits.h"
#include "sixtracklib/common/cobjects/flat_buffer.h"
#include "sixtracklib/common/cobjects/garbage_range.h"
#include "sixtracklib/common/cobjects/index_object.h"

#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/control/argument.h"
#include "sixtracklib/common/control/controller.h"
#include "sixtracklib/common/control/node_id.h"
#include "sixtracklib/common/control/node_info.h"
#include "sixtracklib/common/control/program_item.h"
#include "sixtracklib/common/control/program_store.h"

#include "sixtracklib/common/generated/config.h"
#include "sixtracklib/common/generated/path.h"
#include "sixtracklib/common/generated/modules.h"
#include "sixtracklib/common/generated/helpers.h"

#include "sixtracklib/common/internal/file_tools.h"
#include "sixtracklib/common/internal/math_constants.h"
#include "sixtracklib/common/internal/math_factorial.h"
#include "sixtracklib/common/internal/math_functions.h"
#include "sixtracklib/common/internal/math_interpol.h"
#include "sixtracklib/common/internal/math_qgauss.h"
#include "sixtracklib/common/internal/physics_constants.h"
#include "sixtracklib/common/internal/thread_lock.h"
#include "sixtracklib/common/internal/thread_id.h"
#include "sixtracklib/common/internal/type_arithmetic_helpers.h"
#include "sixtracklib/common/internal/type_comparison_helpers.h"
#include "sixtracklib/common/internal/tools.h"

#include "sixtracklib/common/particles/definitions.h"
#include "sixtracklib/common/particles/cobj_type_ids.h"
#include "sixtracklib/common/particles/particle.h"
#include "sixtracklib/common/particles/particles.h"
#include "sixtracklib/common/particles/particles_addr.h"
#include "sixtracklib/common/particles/particle_helper.h"

#if defined( SIXTRL_DEMOTRACK_ENABLED ) && ( SIXTRL_DEMOTRACK_ENABLED == 1 )
#include "sixtracklib/common/particles/demotrack.h"
#endif /* defined( SIXTRL_DEMOTRACK_ENABLED )  */

#include "sixtracklib/common/track/definitions.h"
#include "sixtracklib/common/track/track_config.h"
#include "sixtracklib/common/track/track.h"

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if defined( SIXTRACKLIB_ENABLE_MODULE_OPENCL ) && \
           ( SIXTRACKLIB_ENABLE_MODULE_OPENCL == 1 )
    #include "sixtracklib/opencl/opencl.h"
    #include "sixtracklib/opencl/definitions.h"
    #include "sixtracklib/opencl/internal/helpers.h"
    #include "sixtracklib/opencl/control/argument.h"
    #include "sixtracklib/opencl/control/cmd_queue.h"
    #include "sixtracklib/opencl/control/context.h"
    #include "sixtracklib/opencl/control/controller.h"
    #include "sixtracklib/opencl/control/kernel_item.h"
    #include "sixtracklib/opencl/control/node_info.h"
    #include "sixtracklib/opencl/control/program_item.h"
    #include "sixtracklib/opencl/control/program_store.h"
#endif /* defined( SIXTRACKLIB_ENABLE_MODULE_OPENCL ) */

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if defined( SIXTRACKLIB_ENABLE_MODULE_CUDA ) && \
           ( SIXTRACKLIB_ENABLE_MODULE_CUDA == 1 )
/*
    #include "sixtracklib/cuda/definitions.h"
    #include "sixtracklib/cuda/control/kernel_config.h"
    #include "sixtracklib/cuda/argument.h"
    #include "sixtracklib/cuda/controller.h"
    #include "sixtracklib/cuda/track_particles_kernel_c_wrapper.h"
*/
#endif /* defined( SIXTRACKLIB_ENABLE_MODULE_OPENCL ) */
#endif /* SIXTRACKLIB_SIXTRACKLIB_H__ */
