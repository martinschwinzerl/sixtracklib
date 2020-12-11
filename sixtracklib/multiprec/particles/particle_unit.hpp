#ifndef SIXTRACKLIB_MULTIPREC_PARTICLES_PARTICLE_UNIT_CXX_HPP__
#define SIXTRACKLIB_MULTIPREC_PARTICLES_PARTICLE_UNIT_CXX_HPP__

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
    using TMultiPrecParticle = TParticle<
        MultiPrecReal< N, base, Alloc, E, ExpMin, ExpMax, et >,
        I, arch_size_t{ 1 },
        SIXTRL_CXX_NAMESPACE::Type_storage_align<
            MultiPrecReal< N, base, Alloc, E, ExpMin, ExpMax, et > >(),
        SIXTRL_CXX_NAMESPACE::Type_storage_align< I >() >;

    /* Specialisations for important parameter sets */

    template< class I, multiprec_et_option_t et >
    using TSinglePrecParticle = TParticle<
        MultiPrecRealSingle< et >, I, SIXTRL_CXX_NAMESPACE::arch_size_t{ 1 },
        SIXTRL_CXX_NAMESPACE::Type_storage_align< MultiPrecRealSingle< et > >(),
        SIXTRL_CXX_NAMESPACE::Type_storage_align< I >() >;

    using SinglePrecParticle = TSinglePrecParticle<
        SIXTRL_CXX_NAMESPACE::particle_index_t, DEFAULT_MULTIPREC_ET >;

    template< class I, SIXTRL_CXX_NAMESPACE::store_backend_t StoreT,
              SIXTRL_CXX_NAMESPACE::multiprec_et_option_t et >
    struct ObjDataDelegateTraits< TSinglePrecParticle< I, et >, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::Particle delegate_t;
    };

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< class I, multiprec_et_option_t et >
    using TDoublePrecParticle = TParticle<
        MultiPrecRealDouble< et >, I, SIXTRL_CXX_NAMESPACE::arch_size_t{ 1 },
        SIXTRL_CXX_NAMESPACE::Type_storage_align< MultiPrecRealDouble< et > >(),
        SIXTRL_CXX_NAMESPACE::Type_storage_align< I >() >;

    using DoublePrecParticle = TDoublePrecParticle<
        SIXTRL_CXX_NAMESPACE::particle_index_t, DEFAULT_MULTIPREC_ET >;

    template< class I, SIXTRL_CXX_NAMESPACE::store_backend_t StoreT,
              SIXTRL_CXX_NAMESPACE::multiprec_et_option_t et >
    struct ObjDataDelegateTraits< TDoublePrecParticle< I, et >, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::Particle delegate_t;
    };

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< class I, SIXTRL_CXX_NAMESPACE::multiprec_et_option_t et >
    using TExtDoublePrecParticle = TParticle<
        MultiPrecRealExtDouble< et >, I, SIXTRL_CXX_NAMESPACE::arch_size_t{ 1 },
        SIXTRL_CXX_NAMESPACE::Type_storage_align<
            MultiPrecRealExtDouble< et > >(),
        SIXTRL_CXX_NAMESPACE::Type_storage_align< I >() >;

    using ExtDoublePrecParticle = TExtDoublePrecParticle<
        SIXTRL_CXX_NAMESPACE::particle_index_t, DEFAULT_MULTIPREC_ET >;

    template< class I, SIXTRL_CXX_NAMESPACE::multiprec_et_option_t et,
              SIXTRL_CXX_NAMESPACE::store_backend_t StoreT >
    struct ObjDataDelegateTraits< TExtDoublePrecParticle< I, et >, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::Particle delegate_t;
    };

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< class I, SIXTRL_CXX_NAMESPACE::multiprec_et_option_t et >
    using TQuadPrecParticle = TParticle<
        MultiPrecRealQuad< et >, I, SIXTRL_CXX_NAMESPACE::arch_size_t{ 1 },
        SIXTRL_CXX_NAMESPACE::Type_storage_align< MultiPrecRealQuad< et > >(),
        SIXTRL_CXX_NAMESPACE::Type_storage_align< I >() >;

    using QuadPrecParticle = TQuadPrecParticle<
        SIXTRL_CXX_NAMESPACE::particle_index_t, DEFAULT_MULTIPREC_ET >;

    template< class I, SIXTRL_CXX_NAMESPACE::multiprec_et_option_t et,
              SIXTRL_CXX_NAMESPACE::store_backend_t StoreT >
    struct ObjDataDelegateTraits< TQuadPrecParticle< I, et >, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::Particle delegate_t;
    };

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    template< class I, multiprec_et_option_t et >
    using TOctPrecParticle = TParticle<
        MultiPrecRealOct< et >, I, arch_size_t{ 1 },
        SIXTRL_CXX_NAMESPACE::Type_storage_align< MultiPrecRealOct< et > >(),
        SIXTRL_CXX_NAMESPACE::Type_storage_align< I >() >;

    using OctPrecParticle = TOctPrecParticle<
        SIXTRL_CXX_NAMESPACE::particle_index_t, DEFAULT_MULTIPREC_ET >;

    template< class I, SIXTRL_CXX_NAMESPACE::multiprec_et_option_t et,
              SIXTRL_CXX_NAMESPACE::store_backend_t StoreT >
    struct ObjDataDelegateTraits< TOctPrecParticle< I, et >, StoreT >
    {
        typedef SIXTRL_CXX_NAMESPACE::Particle delegate_t;
    };
}
#endif /* C++, Host */

#endif /* SIXTRACKLIB_MULTIPREC_PARTICLES_PARTICLE_UNIT_CXX_HPP__ */
