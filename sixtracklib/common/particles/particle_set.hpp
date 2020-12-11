#ifndef SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SET_CXX_HPP__
#define SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SET_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles/particle_set.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class R, class I >
    struct SIXTRL_ANNOTATE_COBJECT SIXTRL_ANNOTATE_ELEM_OBJ
    SIXTRL_ANNOTATE_ELEM_OBJ_DEC( "SIXTRL_PARTICLE_SET_ARGPTR_DEC" )
    SIXTRL_ANNOTATE_ELEM_OBJ_API_NAME( "ParticleSet" )
    TParticleSet
    {
        particle_num_elements_t num_particles SIXTRL_ALIGN( 8 )
                                SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

        particle_addr_t x_addr             /* [x] = 1 m */
                        SIXTRL_ALIGN( 8 )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( x )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( SIXTRL_PARTICLE_SET_DATAPTR_DEC )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( R )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( num_particles );

        particle_addr_t px_addr            /* px  = Px / P0 */
                        SIXTRL_ALIGN( 8 )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( px )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( SIXTRL_PARTICLE_SET_DATAPTR_DEC )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( R )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( num_particles );

        particle_addr_t y_addr             /* [y] = 1 m */
                        SIXTRL_ALIGN( 8 )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( y )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( SIXTRL_PARTICLE_SET_DATAPTR_DEC )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( R )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( num_particles );

        particle_addr_t py_addr            /* py  = Py / P0 */
                        SIXTRL_ALIGN( 8 )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( py )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( SIXTRL_PARTICLE_SET_DATAPTR_DEC )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( R )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( num_particles );

        particle_addr_t zeta_addr
                        SIXTRL_ALIGN( 8 )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( zeta )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( SIXTRL_PARTICLE_SET_DATAPTR_DEC )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( R )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( num_particles );

        particle_addr_t delta_addr         /* P/P0 - 1 = 1/rpp - 1 */
                        SIXTRL_ALIGN( 8 )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( delta )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( SIXTRL_PARTICLE_SET_DATAPTR_DEC )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( R )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( num_particles );

        particle_addr_t state_addr
                        SIXTRL_ALIGN( 8 )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( state )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( SIXTRL_PARTICLE_SET_DATAPTR_DEC )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( I )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( num_particles );

        particle_addr_t at_element_addr
                        SIXTRL_ALIGN( 8 )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( at_element_id )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( SIXTRL_PARTICLE_SET_DATAPTR_DEC )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( I )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( num_particles );

        particle_addr_t at_turn_addr
                        SIXTRL_ALIGN( 8 )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( at_turn )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( SIXTRL_PARTICLE_SET_DATAPTR_DEC )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( I )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( num_particles );

        particle_addr_t particle_id_addr
                        SIXTRL_ALIGN( 8 )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( particle_id )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( SIXTRL_PARTICLE_SET_DATAPTR_DEC )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( I )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( num_particles );

        particle_addr_t psigma_addr
                        SIXTRL_ALIGN( 8 )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( psigma )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( SIXTRL_PARTICLE_SET_DATAPTR_DEC )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( R )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( num_particles );

        particle_addr_t rpp_addr           /* P0 / P */
                        SIXTRL_ALIGN( 8 )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( rpp )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( SIXTRL_PARTICLE_SET_DATAPTR_DEC )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( R )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( num_particles );

        particle_addr_t rvv_addr           /* beta / beta0 */
                        SIXTRL_ALIGN( 8 )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( rvv )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( SIXTRL_PARTICLE_SET_DATAPTR_DEC )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( R )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( num_particles );

        particle_addr_t chi_addr           /* ( charge/charge0) / (m/mass0) */
                        SIXTRL_ALIGN( 8 )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( chi )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( SIXTRL_PARTICLE_SET_DATAPTR_DEC )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( R )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( num_particles );

        particle_addr_t charge_ratio_addr  /* (charge/charge0) */
                        SIXTRL_ALIGN( 8 )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( charge_ratio )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( SIXTRL_PARTICLE_SET_DATAPTR_DEC )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( R )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( num_particles );

        particle_addr_t charge0_addr        /* [charge0] = 1 e */
                        SIXTRL_ALIGN( 8 )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( charge0 )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( SIXTRL_PARTICLE_SET_DATAPTR_DEC )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( R )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( num_particles );

        particle_addr_t mass0_addr         /* [mass0]  = 1 eV/c² */
                        SIXTRL_ALIGN( 8 )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( mass0 )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( SIXTRL_PARTICLE_SET_DATAPTR_DEC )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( R )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( num_particles );

        particle_addr_t beta0_addr         /* [beta0]  = 1 */
                        SIXTRL_ALIGN( 8 )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( beta0 )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( SIXTRL_PARTICLE_SET_DATAPTR_DEC )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( R )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( num_particles );

        particle_addr_t gamma0_addr        /* [gamma0] = 1 */
                        SIXTRL_ALIGN( 8 )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( gamma0 )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( SIXTRL_PARTICLE_SET_DATAPTR_DEC )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( R )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( num_particles );

        particle_addr_t pc0_addr           /* [pc0]    = 1 eV */
                        SIXTRL_ALIGN( 8 )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( pc0 )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( SIXTRL_PARTICLE_SET_DATAPTR_DEC )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( R )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( num_particles );

        particle_addr_t s_addr             /* [s] = 1 m */
                        SIXTRL_ALIGN( 8 )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_IS_ARRAY
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_API_NAME( s )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_DEC( SIXTRL_PARTICLE_SET_DATAPTR_DEC )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_TYPE( R )
                        SIXTRL_ANNOTATE_ELEM_FIELD_POINTER_LENGTH( num_particles );

        particle_num_elements_t capacity SIXTRL_ALIGN( 8 )
                                SIXTRL_ANNOTATE_ELEM_FIELD_CONST
                                SIXTRL_ANNOTATE_ELEM_FIELD_REQU_INIT
                                SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );
    };

    /* ********************************************************************* */
    /* Specializations for TParticleSet: */
    /* ********************************************************************* */

    template< class R, class I >
    struct ObjDataParticleSetTraits< TParticleSet< R, I > >
    {
        static constexpr bool is_type = true;

        static constexpr particle_set_impl_t implementation =
            SIXTRL_CXX_NAMESPACE::PARTICLE_SET_IMPL_DEFAULT;
    };

    template< class R, class I >
    constexpr bool ObjDataParticleSetTraits< TParticleSet< R, I > >::is_type;

    template< class R, class I >
    constexpr particle_set_impl_t ObjDataParticleSetTraits< TParticleSet<
        R, I > >::implementation;

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    template< class R, class I >
    struct ParticleSetTraits< TParticleSet< R, I > >
    {
        typedef typename TypeMethodParamTraits< R >::value_type real_t;
        typedef typename TypeMethodParamTraits< I >::value_type index_t;

        static constexpr arch_size_t real_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< real_t >();

        static constexpr arch_size_t index_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< index_t >();

        static constexpr arch_size_t addr_alignment = arch_size_t{ 8 };
    };

    template< class R, class I >
    constexpr arch_size_t ParticleSetTraits< TParticleSet< R, I >
        >::real_alignment;

    template< class R, class I >
    constexpr arch_size_t ParticleSetTraits< TParticleSet< R, I >
        >::index_alignment;

    template< class R, class I >
    constexpr arch_size_t ParticleSetTraits< TParticleSet< R, I >
        >::addr_alignment;

    /* ********************************************************************* */
    /* Create an equivalency between the ::NS(ParticleSet) type and the
     * corresponding specialization of the ParticleSet template */
    /* ********************************************************************* */

    typedef TParticleSet<
                ParticleSetTraits< ::NS(ParticleSet) >::real_t,
                ParticleSetTraits< ::NS(ParticleSet) >::index_t > ParticleSet;

    template<> struct ObjDataCApiTypeTraits< ParticleSet >
    {
        static_assert(
            SIXTRL_CXX_NAMESPACE::ObjData_can_be_equivalent_to_c_api_type<
                ParticleSet, ::NS(ParticleSet) >(),
            "ParticleSet and ::NS(ParticleSet) are not equivalent C-Api types" );

        typedef ::NS(ParticleSet) c_api_t;
    };
}

#endif /* __cplusplus */

#endif /* SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SET_DATA_CXX_HPP__ */
