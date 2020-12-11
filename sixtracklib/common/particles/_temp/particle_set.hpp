#ifndef SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SET_CXX_HPP__
#define SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SET_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/particles/particle_set.h"
    #include "sixtracklib/common/particles/particle_set_data.hpp"
    #include "sixtracklib/common/particles/particle_set_api.h"
    #include "sixtracklib/common/particles/particle_set_derived_api.h"
    #include "sixtracklib/common/particles/particle_set_particle_api.h"
    #include "sixtracklib/common/internal/math_factorial.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/internal/obj_base_class.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template< class ObjData, SIXTRL_CXX_NAMESPACE::store_backend_t StoreT >
    class TParticleSetImpl : public ObjDataStorageInterfaceBase<
        ObjData, StoreT, SIXTRL_CXX_NAMESPACE::TParticleSetImpl<
            ObjData, StoreT > >
    {
        public:

        typedef typename ParticleSetTraits< ObjData >::real_t  real_t;
        typedef typename ParticleSetTraits< ObjData >::index_t index_t;
        typedef typename ::NS(be_address_t) address_t;
        typedef typename ::NS(particle_num_elements_t) num_elements_t;

        typedef typename TypeMethodParamTraits< real_t >::const_argument_type
                real_arg_t;

        typedef typename TypeMethodParamTraits< real_t >::const_existing_type
                real_const_existing_t;

        typedef typename TypeMethodParamTraits< real_t >::const_pointer
                real_const_pointer;

        typedef typename TypeMethodParamTraits< real_t >::pointer real_pointer;

        typedef typename TypeMethodParamTraits< index_t >::const_argument_type
                index_arg_t;

        typedef typename TypeMethodParamTraits< index_t >::const_existing_type
                index_const_existing_t;

        typedef typename TypeMethodParamTraits< index_t >::const_pointer
                index_const_pointer;

        typedef typename TypeMethodParamTraits< index_t >::pointer
                index_pointer;

        typedef typename TypeMethodParamTraits< address_t >::const_argument_type
                address_arg_t;

        typedef typename TypeMethodParamTraits< address_t>::const_existing_type
                address_const_existing_t;

        typedef SIXTRL_BE_DATAPTR_DEC real_t const* ptr_const_bal_t;
        typedef SIXTRL_BE_DATAPTR_DEC real_t*       ptr_bal_t;

        template< typename... Args >
        SIXTRL_FN arch_status_t init( Args&&... args )
        {
            return SIXTRL_CXX_NAMESPACE::ParticleSet_init(
                this->as_ptr_data(), std::forward< Args >( args )... );
        }

        template< class ParticleT >
        SIXTRL_FN arch_status_t to_particle(
            SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
            particle_num_elements_t const idx )
        {
            return SIXTRL_CXX_NAMESPACE::ParticleSet_store_to_particle(
                this->as_ptr_data(), p, idx );
        }

        template< class ParticleT >
        SIXTRL_FN arch_status_t from_particle(
            SIXTRL_PARTICLE_ARGPTR_DEC ParticleT* SIXTRL_RESTRICT p,
            particle_num_elements_t const idx )
        {
            return SIXTRL_CXX_NAMESPACE::ParticleSet_load_from_particle(
                this->as_ptr_data(), p, idx );
        }
    };
}

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/obj_base_class.hpp"
    #include "sixtracklib/common/particles/particle_set_cobjects_api.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template< class R, class I, arch_size_t N,
        arch_size_t RAlign = SIXTRL_CXX_NAMESPACE::Type_storage_align< R >(),
        arch_size_t IAlign = SIXTRL_CXX_NAMESPACE::Type_storage_align< I >() >
    using TParticleSet = TParticleSetImpl<
        ParticleSetData< R, I, N, RAlign, IAlign >, STORAGE_BE_COBJECTS >;

    typedef TParticleSetImpl< CParticleSetEquivData, STORAGE_BE_COBJECTS >
            ParticleSet;

    typedef TParticleSetImpl< ::NS(ParticleSet), STORAGE_BE_COBJECTS >
            CParticleSet;
}

#endif /* __cplusplus */
#endif /* SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SET_CXX_HPP__ */
