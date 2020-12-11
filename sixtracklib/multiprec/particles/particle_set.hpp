#ifndef SIXTRACKLIB_MULTIPREC_PARTICLES_PARTICLE_SET_CXX_HPP__
#define SIXTRACKLIB_MULTIPREC_PARTICLES_PARTICLE_SET_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/multiprec/definitions.h"
    #include "sixtracklib/common/particle.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    template< unsigned N, class I,
            boost::multiprecision::backends::digit_base_type base=
                boost::multiprecision::backends::digit_base_2,
            class Alloc = void, class E = int, E ExpMin = E{ 0 },
            E ExpMax = E{ 0 }, multiprec_et_option_t et = DEFAULT_MULTIPREC_ET >
    using TMultiPrecParticleSet = TVectorParticleSet<
        MultiPrecReal< N, base, Alloc, E, ExpMin, ExpMax, et >, I >;

    /* Specialisations for important parameter sets */

    template< class I, SIXTRL_CXX_NAMESPACE::multiprec_et_option_t et >
    using TSinglePrecParticleSet= TVectorParticleSet< MultiPrecRealSingle< et >, I >;

    using SinglePrecParticleSet = TSinglePrecParticleSet<
        SIXTRL_CXX_NAMESPACE::particle_index_t, DEFAULT_MULTIPREC_ET >;

    template< class I, SIXTRL_CXX_NAMESPACE::store_backend_t StoreT,
              SIXTRL_CXX_NAMESPACE::multiprec_et_option_t et >
    struct ObjDataDelegateTraits< TSinglePrecParticleSet< I, et >, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::ParticleSet delegate_t;
    };

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< class I, SIXTRL_CXX_NAMESPACE::multiprec_et_option_t et >
    using TDoublePrecParticleSet= TVectorParticleSet<
        MultiPrecRealDouble< et >, I >;

    using DoublePrecParticleSet = TDoublePrecParticleSet<
        SIXTRL_CXX_NAMESPACE::particle_index_t, DEFAULT_MULTIPREC_ET >;

    template< class I, SIXTRL_CXX_NAMESPACE::store_backend_t StoreT,
              SIXTRL_CXX_NAMESPACE::multiprec_et_option_t et >
    struct ObjDataDelegateTraits< TDoublePrecParticleSet< I, et >, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::ParticleSet delegate_t;
    };

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< class I, SIXTRL_CXX_NAMESPACE::multiprec_et_option_t et >
    using TExtDoublePrecParticleSet= TVectorParticleSet<
        MultiPrecRealExtDouble< et >, I >;

    using ExtDoublePrecParticleSet = TExtDoublePrecParticleSet<
        SIXTRL_CXX_NAMESPACE::particle_index_t, DEFAULT_MULTIPREC_ET >;

    template< class I, SIXTRL_CXX_NAMESPACE::store_backend_t StoreT,
              SIXTRL_CXX_NAMESPACE::multiprec_et_option_t et >
    struct ObjDataDelegateTraits< TExtDoublePrecParticleSet< I, et >, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::ParticleSet delegate_t;
    };

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

   template< class I, SIXTRL_CXX_NAMESPACE::multiprec_et_option_t et >
    using TQuadPrecParticleSet= TVectorParticleSet<
        MultiPrecRealQuad< et >, I >;

    using QuadPrecParticleSet = TQuadPrecParticleSet<
        SIXTRL_CXX_NAMESPACE::particle_index_t, DEFAULT_MULTIPREC_ET >;

    template< class I, SIXTRL_CXX_NAMESPACE::store_backend_t StoreT,
              SIXTRL_CXX_NAMESPACE::multiprec_et_option_t et >
    struct ObjDataDelegateTraits< TQuadPrecParticleSet< I, et >, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::ParticleSet delegate_t;
    };

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< class I, SIXTRL_CXX_NAMESPACE::multiprec_et_option_t et >
    using TOctPrecParticleSet= TVectorParticleSet<
        MultiPrecRealOct< et >, I >;

    using OctPrecParticleSet = TOctPrecParticleSet<
        SIXTRL_CXX_NAMESPACE::particle_index_t, DEFAULT_MULTIPREC_ET >;

    template< class I, SIXTRL_CXX_NAMESPACE::store_backend_t StoreT,
              SIXTRL_CXX_NAMESPACE::multiprec_et_option_t et >
    struct ObjDataDelegateTraits< TOctPrecParticleSet< I, et >, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::ParticleSet delegate_t;
    };
}
#endif /* C++, HOST */
#endif /* SIXTRACKLIB_MULTIPREC_PARTICLES_PARTICLE_SET_CXX_HPP__ */

