#ifndef SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SET_H__
#define SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SET_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles/definitions.h"

    #if defined( __cplusplus )
        #include "sixtracklib/common/internal/obj_c_api_traits.hpp"
        #include "sixtracklib/common/internal/type_annotations.h"
        #endif /* defined( __cplusplus ) */
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( __GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( __GPUCODE ) && defined( __cplusplus ) */

typedef struct
SIXTRL_ANNOTATE_COBJECT SIXTRL_ANNOTATE_ELEM_OBJ
SIXTRL_ANNOTATE_ELEM_OBJ_DEC( "SIXTRL_PARTICLE_SET_ARGPTR_DEC" )
NS(ParticleSet)
{
    NS(particle_num_elements_t) num_particles SIXTRL_ALIGN( 8 )
                                SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

    NS(particle_addr_t)         x_addr             /* [x] = 1 m */
                                SIXTRL_ALIGN( 8 )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( x )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( SIXTRL_PARTICLE_SET_DATAPTR_DEC )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( NS(particle_real_t) )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( num_particles );

    NS(particle_addr_t)         px_addr            /* px  = Px / P0 */
                                SIXTRL_ALIGN( 8 )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( px )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( SIXTRL_PARTICLE_SET_DATAPTR_DEC )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( NS(particle_real_t) )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( num_particles );

    NS(particle_addr_t)         y_addr             /* [y] = 1 m */
                                SIXTRL_ALIGN( 8 )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( y )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( SIXTRL_PARTICLE_SET_DATAPTR_DEC )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( NS(particle_real_t) )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( num_particles );

    NS(particle_addr_t)         py_addr            /* py  = Py / P0 */
                                SIXTRL_ALIGN( 8 )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( py )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( SIXTRL_PARTICLE_SET_DATAPTR_DEC )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( NS(particle_real_t) )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( num_particles );

    NS(particle_addr_t)         zeta_addr
                                SIXTRL_ALIGN( 8 )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( zeta )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( SIXTRL_PARTICLE_SET_DATAPTR_DEC )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( NS(particle_real_t) )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( num_particles );

    NS(particle_addr_t)         delta_addr         /* P/P0 - 1 = 1/rpp - 1 */
                                SIXTRL_ALIGN( 8 )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( delta )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( SIXTRL_PARTICLE_SET_DATAPTR_DEC )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( NS(particle_real_t) )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( num_particles );

    NS(particle_addr_t)         state_addr
                                SIXTRL_ALIGN( 8 )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( state )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( SIXTRL_PARTICLE_SET_DATAPTR_DEC )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( NS(particle_index_t) )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( num_particles );

    NS(particle_addr_t)         at_element_addr
                                SIXTRL_ALIGN( 8 )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( at_element_id )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( SIXTRL_PARTICLE_SET_DATAPTR_DEC )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( NS(particle_index_t) )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( num_particles );

    NS(particle_addr_t)         at_turn_addr
                                SIXTRL_ALIGN( 8 )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( at_turn )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( SIXTRL_PARTICLE_SET_DATAPTR_DEC )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( NS(particle_index_t) )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( num_particles );

    NS(particle_addr_t)         particle_id_addr
                                SIXTRL_ALIGN( 8 )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( particle_id )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( SIXTRL_PARTICLE_SET_DATAPTR_DEC )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( NS(particle_index_t) )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( num_particles );

    NS(particle_addr_t)         psigma_addr
                                SIXTRL_ALIGN( 8 )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( psigma )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( SIXTRL_PARTICLE_SET_DATAPTR_DEC )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( NS(particle_real_t) )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( num_particles );

    NS(particle_addr_t)         rpp_addr           /* P0 / P */
                                SIXTRL_ALIGN( 8 )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( rpp )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( SIXTRL_PARTICLE_SET_DATAPTR_DEC )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( NS(particle_real_t) )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( num_particles );

    NS(particle_addr_t)         rvv_addr           /* beta / beta0 */
                                SIXTRL_ALIGN( 8 )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( rvv )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( SIXTRL_PARTICLE_SET_DATAPTR_DEC )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( NS(particle_real_t) )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( num_particles );

    NS(particle_addr_t)         chi_addr           /* ( charge/charge0) / (m/mass0) */
                                SIXTRL_ALIGN( 8 )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( chi )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( SIXTRL_PARTICLE_SET_DATAPTR_DEC )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( NS(particle_real_t) )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( num_particles );

    NS(particle_addr_t)         charge_ratio_addr  /* (charge/charge0) */
                                SIXTRL_ALIGN( 8 )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( charge_ratio )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( SIXTRL_PARTICLE_SET_DATAPTR_DEC )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( NS(particle_real_t) )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( num_particles );

    NS(particle_addr_t)         charge0_addr        /* [charge0] = 1 e */
                                SIXTRL_ALIGN( 8 )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( charge0 )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( SIXTRL_PARTICLE_SET_DATAPTR_DEC )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( NS(particle_real_t) )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( num_particles );

    NS(particle_addr_t)         mass0_addr         /* [mass0]  = 1 eV/c² */
                                SIXTRL_ALIGN( 8 )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( mass0 )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( SIXTRL_PARTICLE_SET_DATAPTR_DEC )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( NS(particle_real_t) )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( num_particles );

    NS(particle_addr_t)         beta0_addr         /* [beta0]  = 1 */
                                SIXTRL_ALIGN( 8 )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( beta0 )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( SIXTRL_PARTICLE_SET_DATAPTR_DEC )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( NS(particle_real_t) )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( num_particles );

    NS(particle_addr_t)         gamma0_addr        /* [gamma0] = 1 */
                                SIXTRL_ALIGN( 8 )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( gamma0 )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( SIXTRL_PARTICLE_SET_DATAPTR_DEC )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( NS(particle_real_t) )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( num_particles );

    NS(particle_addr_t)         pc0_addr           /* [pc0]    = 1 eV */
                                SIXTRL_ALIGN( 8 )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( pc0 )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( SIXTRL_PARTICLE_SET_DATAPTR_DEC )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( NS(particle_real_t) )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( num_particles );

    NS(particle_addr_t)         s_addr             /* [s] = 1 m */
                                SIXTRL_ALIGN( 8 )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( s )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( SIXTRL_PARTICLE_SET_DATAPTR_DEC )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( NS(particle_real_t) )
                                SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( num_particles );

    NS(particle_num_elements_t) capacity SIXTRL_ALIGN( 8 )
                                SIXTRL_ANNOTATE_ELEM_FIELD_CONST
                                SIXTRL_ANNOTATE_ELEM_FIELD_REQU_INIT
                                SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );
}
NS(ParticleSet);

#if !defined( __GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( __GPUCODE ) && defined( __cplusplus ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template<> struct ObjDataParticleSetTraits< ::NS(ParticleSet) >
    {
        static constexpr bool is_type = true;
        static constexpr particle_set_impl_t implementation =
            SIXTRL_CXX_NAMESPACE::PARTICLE_SET_IMPL_DEFAULT;
    };

    template<> struct ParticleSetTraits< ::NS(ParticleSet) >
    {
        typedef ::NS(particle_real_t)  real_t;
        typedef ::NS(particle_index_t) index_t;

        static constexpr arch_size_t real_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< real_t >();

        static constexpr arch_size_t index_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< index_t >();

        static constexpr arch_size_t addr_alignment = arch_size_t{ 8 };
    };

    template<> struct ObjDataCApiTypeTraits< ::NS(ParticleSet) >
    {
        typedef ::NS(ParticleSet) c_api_t;
    };

    typedef ::NS(ParticleSet) CParticleSet;
}
#endif /* C++ */

#endif /* SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SET_H__ */
