#ifndef SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_TRAITS_CXX_HPP__
#define SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_TRAITS_CXX_HPP__

namespace SIXTRL_CXX_NAMESPACE
{
    template< class ParticleObjData > struct TrackParticleDataTraits
    {
        typedef typename ParticleObjData::real_t    real_t;
        typedef typename ParticleObjData::int_t     int_t;
    };
}

#endif /* SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_TRAITS_CXX_HPP__ */
/* end: */
