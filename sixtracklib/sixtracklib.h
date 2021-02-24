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
#include "sixtracklib/common/control/node_id.h"
#include "sixtracklib/common/control/node_info.h"

#include "sixtracklib/common/generated/config.h"
#include "sixtracklib/common/generated/path.h"
#include "sixtracklib/common/generated/modules.h"

#include "sixtracklib/common/internal/file_tools.h"
#include "sixtracklib/common/internal/math_constants.h"
#include "sixtracklib/common/internal/math_factorial.h"
#include "sixtracklib/common/internal/math_functions.h"
#include "sixtracklib/common/internal/math_interpol.h"
#include "sixtracklib/common/internal/math_qgauss.h"
#include "sixtracklib/common/internal/physics_constants.h"
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

/*
#include "sixtracklib/common/buffer/mem_pool.h"
#include "sixtracklib/common/buffer/managed_buffer_minimal.h"
#include "sixtracklib/common/buffer/managed_buffer_remap.h"
#include "sixtracklib/common/buffer/managed_buffer.h"
#include "sixtracklib/common/buffer/buffer_type.h"
#include "sixtracklib/common/buffer/buffer_object.h"
#include "sixtracklib/common/buffer/buffer_garbage.h"
#include "sixtracklib/common/buffer/buffer_generic.h"
#include "sixtracklib/common/be_beamfields/be_beamfields.h"
#include "sixtracklib/common/be_beamfields/track.h"
#include "sixtracklib/common/be_beamfields/faddeeva_cern.h"
#include "sixtracklib/common/be_beamfields/gauss_fields.h"
#include "sixtracklib/common/be_cavity/be_cavity.h"
#include "sixtracklib/common/be_cavity/track.h"
#include "sixtracklib/common/be_drift/be_drift.h"
#include "sixtracklib/common/be_drift/track.h"
#include "sixtracklib/common/be_monitor/be_monitor.h"
#include "sixtracklib/common/be_monitor/output_buffer.h"
#include "sixtracklib/common/be_monitor/track.h"
#include "sixtracklib/common/be_multipole/be_multipole.h"
#include "sixtracklib/common/be_multipole/track.h"
#include "sixtracklib/common/be_srotation/be_srotation.h"
#include "sixtracklib/common/be_srotation/track.h"
#include "sixtracklib/common/be_xyshift/be_xyshift.h"
#include "sixtracklib/common/be_xyshift/track.h"
#include "sixtracklib/common/be_limit/be_limit_rect.h"
#include "sixtracklib/common/be_limit/be_limit_ellipse.h"
#include "sixtracklib/common/be_limit/be_limit_rect_ellipse.h"
#include "sixtracklib/common/be_limit/track.h"
#include "sixtracklib/common/be_dipedge/be_dipedge.h"
#include "sixtracklib/common/be_dipedge/track.h"
#include "sixtracklib/common/be_tricub/be_tricub.h"
#include "sixtracklib/common/be_tricub/track.h"
#include "sixtracklib/common/be_rfmultipole/be_rfmultipole.h"
#include "sixtracklib/common/be_rfmultipole/track.h"
#include "sixtracklib/common/context/compute_arch.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/control/argument_base.h"
#include "sixtracklib/common/control/controller_base.h"
#include "sixtracklib/common/control/node_controller_base.h"
#include "sixtracklib/common/controller.h"
#include "sixtracklib/common/internal/track_job_base.h"
#include "sixtracklib/common/output/elem_by_elem_config.h"
#include "sixtracklib/common/output/elem_by_elem_output_buffer.h"
#include "sixtracklib/common/output/output_buffer.h"
#include "sixtracklib/common/track/definitions.h"
#include "sixtracklib/common/track/track.h"
#include "sixtracklib/common/track/track_kernel_impl.h"
#include "sixtracklib/common/track/track_kernel_opt_impl.h"
#include "sixtracklib/common/beam_elements.h"
#include "sixtracklib/common/constants.h"
#include "sixtracklib/common/buffer.h"
#include "sixtracklib/common/particles.h"
#include "sixtracklib/common/track_job.h"
#include "sixtracklib/common/track_job_cpu.h"
*/

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if defined( SIXTRACKLIB_ENABLE_MODULE_OPENCL ) && \
           ( SIXTRACKLIB_ENABLE_MODULE_OPENCL == 1 )
/*
    #include "sixtracklib/opencl/opencl.h"
    #include "sixtracklib/opencl/argument.h"
    #include "sixtracklib/opencl/context.h"
    #include "sixtracklib/opencl/track_job_cl.h"
*/
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
