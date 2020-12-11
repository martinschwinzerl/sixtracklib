#ifndef SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SET_VECTOR_CXX_HPP__
#define SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SET_VECTOR_CXX_HPP__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <vector>
        #include <memory>
        #include <utility>
    #endif /* C++ */
#endif /* C++ */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles/definitions.h"
    #include "sixtracklib/common/internal/physics_constants.h"
    #include "sixtracklib/common/internal/compiler_attributes.h"
    #include "sixtracklib/common/internal/compiler_compability.h"
    #include "sixtracklib/common/particles/particle_set_helper_api.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class R, class I, class RAlloc = std::allocator< R >,
              class IAlloc = std::allocator< I > >
    struct SIXTRL_ANNOTATE_COBJECT SIXTRL_ANNOTATE_ELEM_OBJ
    SIXTRL_ANNOTATE_ELEM_OBJ_DEC( "SIXTRL_PARTICLE_SET_ARGPTR_DEC" )
    SIXTRL_ANNOTATE_ELEM_OBJ_API_NAME( "ParticleSet" )
    TVectorParticleSet
    {
        particle_num_elements_t num_particles SIXTRL_ALIGN( 8 )
                                SIXTRL_ANNOTATE_ELEM_FIELD_DEFAULT_VALUE( 0 );

        std::vector< R, RAlloc >    m_x;
        std::vector< R, RAlloc >    m_px;
        std::vector< R, RAlloc >    m_y;
        std::vector< R, RAlloc >    m_py;
        std::vector< R, RAlloc >    m_zeta;
        std::vector< R, RAlloc >    m_delta;

        std::vector< I, IAlloc >    m_state;
        std::vector< I, IAlloc >    m_at_element;
        std::vector< I, IAlloc >    m_at_turn;
        std::vector< I, IAlloc >    m_particle_id;

        std::vector< R, RAlloc >    m_psigma;
        std::vector< R, RAlloc >    m_rpp;
        std::vector< R, RAlloc >    m_rvv;
        std::vector< R, RAlloc >    m_chi;
        std::vector< R, RAlloc >    m_charge_ratio;

        std::vector< R, RAlloc >    m_charge0;
        std::vector< R, RAlloc >    m_mass0;
        std::vector< R, RAlloc >    m_beta0;
        std::vector< R, RAlloc >    m_gamma0;
        std::vector< R, RAlloc >    m_pc0;

        std::vector< R, RAlloc >    m_s;
    };

    /* ********************************************************************* */
    /* Specializations for TVectorParticleSet: */
    /* ********************************************************************* */

    template< class R, class I, class RAlloc, class IAlloc >
    struct ObjDataParticleSetTraits<
        TVectorParticleSet< R, I, RAlloc, IAlloc > >
    {
        static constexpr bool is_type = true;

        static constexpr particle_set_impl_t implementation =
            SIXTRL_CXX_NAMESPACE::PARTICLE_SET_IMPL_STD_VECTOR;
    };

    template< class R, class I, class RAlloc, class IAlloc >
    constexpr bool ObjDataParticleSetTraits< TVectorParticleSet<
        R, I, RAlloc, IAlloc > >::is_type;

    template< class R, class I, class RAlloc, class IAlloc >
    constexpr particle_set_impl_t ObjDataParticleSetTraits< TVectorParticleSet<
        R, I, RAlloc, IAlloc > >::implementation;

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    template< class R, class I, class RAlloc, class IAlloc >
    struct ParticleSetTraits< TVectorParticleSet< R, I, RAlloc, IAlloc > >
    {
        typedef typename TypeMethodParamTraits< R >::value_type real_t;
        typedef typename TypeMethodParamTraits< I >::value_type index_t;

        static constexpr arch_size_t real_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< real_t >();

        static constexpr arch_size_t index_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< index_t >();

        static constexpr arch_size_t addr_alignment = arch_size_t{ 8 };
    };

    template< class R, class I, class RAlloc, class IAlloc >
    constexpr arch_size_t ParticleSetTraits< TVectorParticleSet<
        R, I, RAlloc, IAlloc > >::real_alignment;

    template< class R, class I, class RAlloc, class IAlloc >
    constexpr arch_size_t ParticleSetTraits< TVectorParticleSet<
        R, I, RAlloc, IAlloc > >::index_alignment;

    template< class R, class I, class RAlloc, class IAlloc >
    constexpr arch_size_t ParticleSetTraits< TVectorParticleSet<
        R, I, RAlloc, IAlloc > >::addr_alignment;
}

namespace SIXTRL_CXX_NAMESPACE
{
    /* ********************************************************************* */

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::particle_num_elements_t >::type
    ParticleSet_capacity( SIXTRL_PARTICLE_SET_ARGPTR_DEC const
        PSetT *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( pset->num_particles >= particle_num_elements_t{ 0 } );
        SIXTRL_ASSERT(
            ( pset->m_state.empty() ) ||
            ( static_cast< std::size_t >( pset->num_particles ) <=
              pset->m_state.size() ) );

        SIXTRL_ASSERT( pset->m_x.size() <= pset->m_px.size() );
        SIXTRL_ASSERT( pset->m_x.size() <= pset->m_y.size() );
        SIXTRL_ASSERT( pset->m_x.size() <= pset->m_py.size() );
        SIXTRL_ASSERT( pset->m_x.size() <= pset->m_zeta.size() );
        SIXTRL_ASSERT( pset->m_x.size() <= pset->m_delta.size() );

        SIXTRL_ASSERT( pset->m_x.size() <= pset->m_state.size() );
        SIXTRL_ASSERT( pset->m_x.size() <= pset->m_at_element.size() );
        SIXTRL_ASSERT( pset->m_x.size() <= pset->m_at_turn.size() );
        SIXTRL_ASSERT( pset->m_x.size() <= pset->m_particle_id.size() );

        SIXTRL_ASSERT( pset->m_x.size() <= pset->m_psigma.size() );
        SIXTRL_ASSERT( pset->m_x.size() <= pset->m_rpp.size() );
        SIXTRL_ASSERT( pset->m_x.size() <= pset->m_rvv.size() );
        SIXTRL_ASSERT( pset->m_x.size() <= pset->m_chi.size() );
        SIXTRL_ASSERT( pset->m_x.size() <= pset->m_charge_ratio.size() );

        SIXTRL_ASSERT( pset->m_x.size() <= pset->m_charge0.size() );
        SIXTRL_ASSERT( pset->m_x.size() <= pset->m_mass0.size() );
        SIXTRL_ASSERT( pset->m_x.size() <= pset->m_beta0.size() );
        SIXTRL_ASSERT( pset->m_x.size() <= pset->m_gamma0.size() );
        SIXTRL_ASSERT( pset->m_x.size() <= pset->m_pc0.size() );

        SIXTRL_ASSERT( pset->m_x.size() <= pset->m_s.size() );

        return static_cast< SIXTRL_CXX_NAMESPACE::particle_num_elements_t >(
            pset->m_x.size() );
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_set_capacity( SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT*
            SIXTRL_RESTRICT pset,
        particle_num_elements_t const capacity) SIXTRL_NOEXCEPT
    {
        typedef typename ParticleSetTraits< PSetT >::real_t  real_t;
        typedef typename ParticleSetTraits< PSetT >::index_t index_t;

        namespace st = SIXTRL_CXX_NAMESPACE;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( pset != SIXTRL_NULLPTR ) &&
            ( capacity > particle_num_elements_t{ 0 } ) )
        {
            status  = st::ParticleSet_vector_set_capacity(
                pset->m_x, capacity, real_t{ 0 } );

            status |= st::ParticleSet_vector_set_capacity(
                pset->m_px, capacity, real_t{ 0 } );

            status |= st::ParticleSet_vector_set_capacity(
                pset->m_y, capacity, real_t{ 0 } );

            status |= st::ParticleSet_vector_set_capacity(
                pset->m_py, capacity, real_t{ 0 } );

            status |= st::ParticleSet_vector_set_capacity(
                pset->m_zeta, capacity, real_t{ 0 } );

            status |= st::ParticleSet_vector_set_capacity(
                pset->m_delta, capacity, real_t{ 0 } );

            status |= st::ParticleSet_vector_set_capacity(
                pset->m_state, capacity, index_t{ 1 } );

            status |= st::ParticleSet_vector_set_capacity(
                pset->m_at_element, capacity, index_t{ 0 } );

            status |= st::ParticleSet_vector_set_capacity(
                pset->m_at_turn, capacity, index_t{ 0 } );

            status |= st::ParticleSet_vector_set_capacity(
                pset->m_particle_id, capacity, index_t{ 0 } );

            status |= st::ParticleSet_vector_set_capacity(
                pset->m_psigma, capacity, real_t{ 0 } );

            status |= st::ParticleSet_vector_set_capacity(
                pset->m_rpp, capacity, real_t{ 1 } );

            status |= st::ParticleSet_vector_set_capacity(
                pset->m_rvv, capacity, real_t{ 1 } );

            status |= st::ParticleSet_vector_set_capacity(
                pset->m_chi, capacity, real_t{ 1 } );

            status |= st::ParticleSet_vector_set_capacity(
                pset->m_charge_ratio, capacity, real_t{ 1 } );

            status |= st::ParticleSet_vector_set_capacity(
                pset->m_charge0, capacity, st::PhysConst_charge0< real_t >() );

            status |= st::ParticleSet_vector_set_capacity( pset->m_mass0,
                capacity, st::PhysConst_mass_proton_ev< real_t >() );

            status |= st::ParticleSet_vector_set_capacity(
                pset->m_beta0, capacity, real_t{ 0 } );

            status |= st::ParticleSet_vector_set_capacity(
                pset->m_gamma0, capacity, real_t{ 1 } );

            status |= st::ParticleSet_vector_set_capacity(
                pset->m_pc0, capacity, real_t{ 0 } );

            status |= st::ParticleSet_vector_set_capacity(
                pset->m_s, capacity, real_t{ 0 } );
        }
        else if( pset != SIXTRL_NULLPTR )
        {
            pset->m_x.clear();
            pset->m_px.clear();
            pset->m_y.clear();
            pset->m_py.clear();
            pset->m_zeta.clear();
            pset->m_delta.clear();

            pset->m_state.clear();
            pset->m_at_element.clear();
            pset->m_at_turn.clear();
            pset->m_particle_id.clear();

            pset->m_psigma.clear();
            pset->m_rpp.clear();
            pset->m_rvv.clear();
            pset->m_chi.clear();
            pset->m_charge_ratio.clear();

            pset->m_charge0.clear();
            pset->m_mass0.clear();
            pset->m_beta0.clear();
            pset->m_gamma0.clear();
            pset->m_pc0.clear();
            pset->m_s.clear();

            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_set_num_particles( SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT*
            SIXTRL_RESTRICT pset,
        particle_num_elements_t const num_particles) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( ( pset != SIXTRL_NULLPTR ) &&
            ( num_particles >= particle_num_elements_t{ 0 } ) )
        {
            if( st::ParticleSet_capacity( pset ) >= num_particles )
            {
                pset->num_particles = num_particles;
                status = st::ARCH_STATUS_SUCCESS;
            }
            else
            {
                status = st::ParticleSet_set_capacity( pset, num_particles );
                if( status == st::ARCH_STATUS_SUCCESS )
                {
                    pset->num_particles = num_particles;
                }
            }
        }

        return status;
    }

    /* --------------------------------------------------------------------- */
    /* x: */

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::particle_addr_t >::type
    ParticleSet_x_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC const
        PSetT *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        return static_cast< particle_addr_t >( reinterpret_cast<
            std::uintptr_t >( pset->m_x.data() ) );
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_set_x_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT*
        SIXTRL_RESTRICT /*pset*/, particle_addr_t const x_addr ) SIXTRL_NOEXCEPT
    {
        return ( x_addr == particle_addr_t{ 0 } )
            ? SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS
            : SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::particle_num_elements_t >::type
    ParticleSet_x_length( SIXTRL_PARTICLE_SET_ARGPTR_DEC const PSetT *const
        SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( pset->num_particles >= particle_num_elements_t{ 0 } );
        SIXTRL_ASSERT( pset->m_x.size() >= static_cast<
                            std::size_t >( pset->num_particles ) );

        return pset->num_particles;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* px: */

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::particle_addr_t >::type
    ParticleSet_px_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC const
        PSetT *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        return static_cast< particle_addr_t >( reinterpret_cast<
            std::uintptr_t >( pset->m_px.data() ) );
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_set_px_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT*
        SIXTRL_RESTRICT /*pset*/, particle_addr_t const px_addr ) SIXTRL_NOEXCEPT
    {
        return ( px_addr == particle_addr_t{ 0 } )
            ? SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS
            : SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::particle_num_elements_t >::type
    ParticleSet_px_length( SIXTRL_PARTICLE_SET_ARGPTR_DEC const PSetT *const
        SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( pset->num_particles >= particle_num_elements_t{ 0 } );
        SIXTRL_ASSERT( pset->m_px.size() >= static_cast<
                            std::size_t >( pset->num_particles ) );

        return pset->num_particles;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* y: */

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::particle_addr_t >::type
    ParticleSet_y_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC const
        PSetT *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        return static_cast< particle_addr_t >( reinterpret_cast<
            std::uintptr_t >( pset->m_y.data() ) );
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_set_y_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT*
        SIXTRL_RESTRICT /*pset*/, particle_addr_t const y_addr ) SIXTRL_NOEXCEPT
    {
        return ( y_addr == particle_addr_t{ 0 } )
            ? SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS
            : SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::particle_num_elements_t >::type
    ParticleSet_y_length( SIXTRL_PARTICLE_SET_ARGPTR_DEC const PSetT *const
        SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( pset->num_particles >= particle_num_elements_t{ 0 } );
        SIXTRL_ASSERT( pset->m_y.size() >= static_cast<
                            std::size_t >( pset->num_particles ) );

        return pset->num_particles;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* py: */

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::particle_addr_t >::type
    ParticleSet_py_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC const
        PSetT *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        return static_cast< particle_addr_t >( reinterpret_cast<
            std::uintptr_t >( pset->m_py.data() ) );
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_set_py_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT*
        SIXTRL_RESTRICT /*pset*/, particle_addr_t const py_addr ) SIXTRL_NOEXCEPT
    {
        return ( py_addr == particle_addr_t{ 0 } )
            ? SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS
            : SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::particle_num_elements_t >::type
    ParticleSet_py_length( SIXTRL_PARTICLE_SET_ARGPTR_DEC const PSetT *const
        SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( pset->num_particles >= particle_num_elements_t{ 0 } );
        SIXTRL_ASSERT( pset->m_py.size() >= static_cast<
                            std::size_t >( pset->num_particles ) );

        return pset->num_particles;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* zeta: */

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::particle_addr_t >::type
    ParticleSet_zeta_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC const
        PSetT *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        return static_cast< particle_addr_t >( reinterpret_cast<
            std::uintptr_t >( pset->m_zeta.data() ) );
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_set_zeta_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT*
        SIXTRL_RESTRICT /*pset*/, particle_addr_t const zeta_addr ) SIXTRL_NOEXCEPT
    {
        return ( zeta_addr == particle_addr_t{ 0 } )
            ? SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS
            : SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::particle_num_elements_t >::type
    ParticleSet_zeta_length( SIXTRL_PARTICLE_SET_ARGPTR_DEC const PSetT *const
        SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( pset->num_particles >= particle_num_elements_t{ 0 } );
        SIXTRL_ASSERT( pset->m_zeta.size() >= static_cast<
                            std::size_t >( pset->num_particles ) );

        return pset->num_particles;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* delta: */

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::particle_addr_t >::type
    ParticleSet_delta_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC const
        PSetT *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        return static_cast< particle_addr_t >( reinterpret_cast<
            std::uintptr_t >( pset->m_delta.data() ) );
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_set_delta_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT*
        SIXTRL_RESTRICT /*pset*/, particle_addr_t const delta_addr ) SIXTRL_NOEXCEPT
    {
        return ( delta_addr == particle_addr_t{ 0 } )
            ? SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS
            : SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::particle_num_elements_t >::type
    ParticleSet_delta_length( SIXTRL_PARTICLE_SET_ARGPTR_DEC const PSetT *const
        SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( pset->num_particles >= particle_num_elements_t{ 0 } );
        SIXTRL_ASSERT( pset->m_delta.size() >= static_cast<
                            std::size_t >( pset->num_particles ) );

        return pset->num_particles;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* state: */

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::particle_addr_t >::type
    ParticleSet_state_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC const
        PSetT *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        return static_cast< particle_addr_t >( reinterpret_cast<
            std::uintptr_t >( pset->m_state.data() ) );
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_set_state_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT*
        SIXTRL_RESTRICT /*pset*/, particle_addr_t const state_addr ) SIXTRL_NOEXCEPT
    {
        return ( state_addr == particle_addr_t{ 0 } )
            ? SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS
            : SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::particle_num_elements_t >::type
    ParticleSet_state_length( SIXTRL_PARTICLE_SET_ARGPTR_DEC const PSetT *const
        SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( pset->num_particles >= particle_num_elements_t{ 0 } );
        SIXTRL_ASSERT( pset->m_state.size() >= static_cast<
                            std::size_t >( pset->num_particles ) );

        return pset->num_particles;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* at_element: */

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::particle_addr_t >::type
    ParticleSet_at_element_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC const
        PSetT *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        return static_cast< particle_addr_t >( reinterpret_cast<
            std::uintptr_t >( pset->m_at_element.data() ) );
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_set_at_element_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT*
        SIXTRL_RESTRICT /*pset*/, particle_addr_t const at_element_addr ) SIXTRL_NOEXCEPT
    {
        return ( at_element_addr == particle_addr_t{ 0 } )
            ? SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS
            : SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::particle_num_elements_t >::type
    ParticleSet_at_element_length( SIXTRL_PARTICLE_SET_ARGPTR_DEC const PSetT *const
        SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( pset->num_particles >= particle_num_elements_t{ 0 } );
        SIXTRL_ASSERT( pset->m_at_element.size() >= static_cast<
                            std::size_t >( pset->num_particles ) );

        return pset->num_particles;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* at_turn: */

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::particle_addr_t >::type
    ParticleSet_at_turn_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC const
        PSetT *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        return static_cast< particle_addr_t >( reinterpret_cast<
            std::uintptr_t >( pset->m_at_turn.data() ) );
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_set_at_turn_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT*
        SIXTRL_RESTRICT /*pset*/, particle_addr_t const at_turn_addr ) SIXTRL_NOEXCEPT
    {
        return ( at_turn_addr == particle_addr_t{ 0 } )
            ? SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS
            : SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::particle_num_elements_t >::type
    ParticleSet_at_turn_length( SIXTRL_PARTICLE_SET_ARGPTR_DEC const PSetT *const
        SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( pset->num_particles >= particle_num_elements_t{ 0 } );
        SIXTRL_ASSERT( pset->m_at_turn.size() >= static_cast<
                            std::size_t >( pset->num_particles ) );

        return pset->num_particles;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* particle_id: */

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::particle_addr_t >::type
    ParticleSet_particle_id_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC const
        PSetT *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        return static_cast< particle_addr_t >( reinterpret_cast<
            std::uintptr_t >( pset->m_particle_id.data() ) );
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_set_particle_id_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT*
        SIXTRL_RESTRICT /*pset*/, particle_addr_t const particle_id_addr ) SIXTRL_NOEXCEPT
    {
        return ( particle_id_addr == particle_addr_t{ 0 } )
            ? SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS
            : SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::particle_num_elements_t >::type
    ParticleSet_particle_id_length( SIXTRL_PARTICLE_SET_ARGPTR_DEC const PSetT *const
        SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( pset->num_particles >= particle_num_elements_t{ 0 } );
        SIXTRL_ASSERT( pset->m_particle_id.size() >= static_cast<
                            std::size_t >( pset->num_particles ) );

        return pset->num_particles;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* psigma: */

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::particle_addr_t >::type
    ParticleSet_psigma_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC const
        PSetT *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        return static_cast< particle_addr_t >( reinterpret_cast<
            std::uintptr_t >( pset->m_psigma.data() ) );
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_set_psigma_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT*
        SIXTRL_RESTRICT /*pset*/, particle_addr_t const psigma_addr ) SIXTRL_NOEXCEPT
    {
        return ( psigma_addr == particle_addr_t{ 0 } )
            ? SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS
            : SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::particle_num_elements_t >::type
    ParticleSet_psigma_length( SIXTRL_PARTICLE_SET_ARGPTR_DEC const PSetT *const
        SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( pset->num_particles >= particle_num_elements_t{ 0 } );
        SIXTRL_ASSERT( pset->m_psigma.size() >= static_cast<
                            std::size_t >( pset->num_particles ) );

        return pset->num_particles;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* rpp: */

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::particle_addr_t >::type
    ParticleSet_rpp_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC const
        PSetT *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        return static_cast< particle_addr_t >( reinterpret_cast<
            std::uintptr_t >( pset->m_rpp.data() ) );
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_set_rpp_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT*
        SIXTRL_RESTRICT /*pset*/, particle_addr_t const rpp_addr ) SIXTRL_NOEXCEPT
    {
        return ( rpp_addr == particle_addr_t{ 0 } )
            ? SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS
            : SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::particle_num_elements_t >::type
    ParticleSet_rpp_length( SIXTRL_PARTICLE_SET_ARGPTR_DEC const PSetT *const
        SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( pset->num_particles >= particle_num_elements_t{ 0 } );
        SIXTRL_ASSERT( pset->m_rpp.size() >= static_cast<
                            std::size_t >( pset->num_particles ) );

        return pset->num_particles;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* rvv: */

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::particle_addr_t >::type
    ParticleSet_rvv_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC const
        PSetT *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        return static_cast< particle_addr_t >( reinterpret_cast<
            std::uintptr_t >( pset->m_rvv.data() ) );
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_set_rvv_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT*
        SIXTRL_RESTRICT /*pset*/, particle_addr_t const rvv_addr ) SIXTRL_NOEXCEPT
    {
        return ( rvv_addr == particle_addr_t{ 0 } )
            ? SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS
            : SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::particle_num_elements_t >::type
    ParticleSet_rvv_length( SIXTRL_PARTICLE_SET_ARGPTR_DEC const PSetT *const
        SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( pset->num_particles >= particle_num_elements_t{ 0 } );
        SIXTRL_ASSERT( pset->m_rvv.size() >= static_cast<
                            std::size_t >( pset->num_particles ) );

        return pset->num_particles;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* chi: */

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::particle_addr_t >::type
    ParticleSet_chi_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC const
        PSetT *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        return static_cast< particle_addr_t >( reinterpret_cast<
            std::uintptr_t >( pset->m_chi.data() ) );
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_set_chi_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT*
        SIXTRL_RESTRICT /*pset*/, particle_addr_t const chi_addr ) SIXTRL_NOEXCEPT
    {
        return ( chi_addr == particle_addr_t{ 0 } )
            ? SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS
            : SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::particle_num_elements_t >::type
    ParticleSet_chi_length( SIXTRL_PARTICLE_SET_ARGPTR_DEC const PSetT *const
        SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( pset->num_particles >= particle_num_elements_t{ 0 } );
        SIXTRL_ASSERT( pset->m_chi.size() >= static_cast<
                            std::size_t >( pset->num_particles ) );

        return pset->num_particles;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* charge_ratio: */

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::particle_addr_t >::type
    ParticleSet_charge_ratio_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC const
        PSetT *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        return static_cast< particle_addr_t >( reinterpret_cast<
            std::uintptr_t >( pset->m_charge_ratio.data() ) );
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_set_charge_ratio_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT*
        SIXTRL_RESTRICT /*pset*/, particle_addr_t const
            charge_ratio_addr ) SIXTRL_NOEXCEPT
    {
        return ( charge_ratio_addr == particle_addr_t{ 0 } )
            ? SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS
            : SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::particle_num_elements_t >::type
    ParticleSet_charge_ratio_length( SIXTRL_PARTICLE_SET_ARGPTR_DEC const
        PSetT *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( pset->num_particles >= particle_num_elements_t{ 0 } );
        SIXTRL_ASSERT( pset->m_charge_ratio.size() >= static_cast<
                            std::size_t >( pset->num_particles ) );

        return pset->num_particles;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* charge0: */

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::particle_addr_t >::type
    ParticleSet_charge0_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC const
        PSetT *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        return static_cast< particle_addr_t >( reinterpret_cast<
            std::uintptr_t >( pset->m_charge0.data() ) );
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_set_charge0_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT*
        SIXTRL_RESTRICT /*pset*/, particle_addr_t const charge0_addr ) SIXTRL_NOEXCEPT
    {
        return ( charge0_addr == particle_addr_t{ 0 } )
            ? SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS
            : SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::particle_num_elements_t >::type
    ParticleSet_charge0_length( SIXTRL_PARTICLE_SET_ARGPTR_DEC const PSetT *const
        SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( pset->num_particles >= particle_num_elements_t{ 0 } );
        SIXTRL_ASSERT( pset->m_charge0.size() >= static_cast<
                            std::size_t >( pset->num_particles ) );

        return pset->num_particles;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* mass0: */

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::particle_addr_t >::type
    ParticleSet_mass0_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC const
        PSetT *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        return static_cast< particle_addr_t >( reinterpret_cast<
            std::uintptr_t >( pset->m_mass0.data() ) );
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_set_mass0_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT*
        SIXTRL_RESTRICT /*pset*/, particle_addr_t const mass0_addr ) SIXTRL_NOEXCEPT
    {
        return ( mass0_addr == particle_addr_t{ 0 } )
            ? SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS
            : SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::particle_num_elements_t >::type
    ParticleSet_mass0_length( SIXTRL_PARTICLE_SET_ARGPTR_DEC const PSetT *const
        SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( pset->num_particles >= particle_num_elements_t{ 0 } );
        SIXTRL_ASSERT( pset->m_mass0.size() >= static_cast<
                            std::size_t >( pset->num_particles ) );

        return pset->num_particles;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* beta0: */

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::particle_addr_t >::type
    ParticleSet_beta0_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC const
        PSetT *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        return static_cast< particle_addr_t >( reinterpret_cast<
            std::uintptr_t >( pset->m_beta0.data() ) );
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_set_beta0_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT*
        SIXTRL_RESTRICT /*pset*/, particle_addr_t const beta0_addr ) SIXTRL_NOEXCEPT
    {
        return ( beta0_addr == particle_addr_t{ 0 } )
            ? SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS
            : SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::particle_num_elements_t >::type
    ParticleSet_beta0_length( SIXTRL_PARTICLE_SET_ARGPTR_DEC const PSetT *const
        SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( pset->num_particles >= particle_num_elements_t{ 0 } );
        SIXTRL_ASSERT( pset->m_beta0.size() >= static_cast<
                            std::size_t >( pset->num_particles ) );

        return pset->num_particles;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* gamma0: */

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::particle_addr_t >::type
    ParticleSet_gamma0_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC const
        PSetT *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        return static_cast< particle_addr_t >( reinterpret_cast<
            std::uintptr_t >( pset->m_gamma0.data() ) );
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_set_gamma0_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT*
        SIXTRL_RESTRICT /*pset*/, particle_addr_t const gamma0_addr ) SIXTRL_NOEXCEPT
    {
        return ( gamma0_addr == particle_addr_t{ 0 } )
            ? SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS
            : SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::particle_num_elements_t >::type
    ParticleSet_gamma0_length( SIXTRL_PARTICLE_SET_ARGPTR_DEC const PSetT *const
        SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( pset->num_particles >= particle_num_elements_t{ 0 } );
        SIXTRL_ASSERT( pset->m_gamma0.size() >= static_cast<
                            std::size_t >( pset->num_particles ) );

        return pset->num_particles;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* pc0: */

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::particle_addr_t >::type
    ParticleSet_pc0_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC const
        PSetT *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        return static_cast< particle_addr_t >( reinterpret_cast<
            std::uintptr_t >( pset->m_pc0.data() ) );
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_set_pc0_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT*
        SIXTRL_RESTRICT /*pset*/, particle_addr_t const pc0_addr ) SIXTRL_NOEXCEPT
    {
        return ( pc0_addr == particle_addr_t{ 0 } )
            ? SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS
            : SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::particle_num_elements_t >::type
    ParticleSet_pc0_length( SIXTRL_PARTICLE_SET_ARGPTR_DEC const PSetT *const
        SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( pset->num_particles >= particle_num_elements_t{ 0 } );
        SIXTRL_ASSERT( pset->m_pc0.size() >= static_cast<
                            std::size_t >( pset->num_particles ) );

        return pset->num_particles;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* s: */

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::particle_addr_t >::type
    ParticleSet_s_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC const
        PSetT *const SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        return static_cast< particle_addr_t >( reinterpret_cast<
            std::uintptr_t >( pset->m_s.data() ) );
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_set_s_addr( SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT*
        SIXTRL_RESTRICT /*pset*/, particle_addr_t const s_addr ) SIXTRL_NOEXCEPT
    {
        return ( s_addr == particle_addr_t{ 0 } )
            ? SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS
            : SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::particle_num_elements_t >::type
    ParticleSet_s_length( SIXTRL_PARTICLE_SET_ARGPTR_DEC const PSetT *const
        SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( pset != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( pset->num_particles >= particle_num_elements_t{ 0 } );
        SIXTRL_ASSERT( pset->m_s.size() >= static_cast<
                            std::size_t >( pset->num_particles ) );

        return pset->num_particles;
    }

    /* ********************************************************************* */

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* >::type
    ParticleSet_preset( SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT*
        SIXTRL_RESTRICT pset ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        if( pset != SIXTRL_NULLPTR )
        {
            st::ParticleSet_set_num_particles(
                pset, st::particle_num_elements_t{ 0 } );

            pset->m_x.clear();
            pset->m_px.clear();
            pset->m_y.clear();
            pset->m_py.clear();
            pset->m_zeta.clear();
            pset->m_delta.clear();

            pset->m_state.clear();
            pset->m_at_element.clear();
            pset->m_at_turn.clear();
            pset->m_particle_id.clear();

            pset->m_psigma.clear();
            pset->m_rpp.clear();
            pset->m_rvv.clear();
            pset->m_chi.clear();
            pset->m_charge_ratio.clear();

            pset->m_charge0.clear();
            pset->m_mass0.clear();
            pset->m_beta0.clear();
            pset->m_gamma0.clear();
            pset->m_pc0.clear();
            pset->m_s.clear();
        }

        return pset;
    }

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >(),
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_init(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* SIXTRL_RESTRICT pset,
        particle_num_elements_t const num_particles,
        particle_num_elements_t capacity = particle_num_elements_t{ 0 } )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        SIXTRL_ASSERT( num_particles >= st::particle_num_elements_t{ 0 } );
        if( capacity <= num_particles ) capacity = num_particles;

        st::arch_status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( pset != SIXTRL_NULLPTR )
        {
            status = st::ParticleSet_set_capacity( pset, capacity );
        }

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            pset->num_particles = num_particles;
        }

        return status;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template< class PSetT, typename XIter, typename PxIter, typename YIter,
              typename PyIter, typename ZetaIter, typename DeltaIter,
              typename StateIter, typename AtElemIter, typename AtTurnIter,
              typename IdIter, typename PSigmaIter, typename RppIter,
              typename RvvIter, typename ChiIter, typename ChargeRatioIter,
              typename Charge0Iter, typename Mass0Iter, typename Beta0Iter,
              typename Gamma0Iter, typename Pc0Iter, typename SIter >
     SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::ParticleSet_impl_std_vector< PSetT >() &&
        SIXTRL_CXX_NAMESPACE::is_iterator< XIter >::value &&
        SIXTRL_CXX_NAMESPACE::is_iterator< PxIter >::value &&
        SIXTRL_CXX_NAMESPACE::is_iterator< YIter >::value &&
        SIXTRL_CXX_NAMESPACE::is_iterator< PyIter >::value &&
        SIXTRL_CXX_NAMESPACE::is_iterator< ZetaIter >::value &&
        SIXTRL_CXX_NAMESPACE::is_iterator< DeltaIter >::value &&
        SIXTRL_CXX_NAMESPACE::is_iterator< StateIter >::value &&
        SIXTRL_CXX_NAMESPACE::is_iterator< AtElemIter >::value &&
        SIXTRL_CXX_NAMESPACE::is_iterator< AtTurnIter >::value &&
        SIXTRL_CXX_NAMESPACE::is_iterator< IdIter >::value &&
        SIXTRL_CXX_NAMESPACE::is_iterator< PSigmaIter >::value &&
        SIXTRL_CXX_NAMESPACE::is_iterator< RppIter >::value &&
        SIXTRL_CXX_NAMESPACE::is_iterator< RvvIter >::value &&
        SIXTRL_CXX_NAMESPACE::is_iterator< ChiIter >::value &&
        SIXTRL_CXX_NAMESPACE::is_iterator< ChargeRatioIter >::value &&
        SIXTRL_CXX_NAMESPACE::is_iterator< Charge0Iter >::value &&
        SIXTRL_CXX_NAMESPACE::is_iterator< Mass0Iter >::value &&
        SIXTRL_CXX_NAMESPACE::is_iterator< Beta0Iter >::value &&
        SIXTRL_CXX_NAMESPACE::is_iterator< Gamma0Iter >::value &&
        SIXTRL_CXX_NAMESPACE::is_iterator< Pc0Iter >::value &&
        SIXTRL_CXX_NAMESPACE::is_iterator< SIter >::value,
        SIXTRL_CXX_NAMESPACE::arch_status_t >::type
    ParticleSet_init_detailed(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* SIXTRL_RESTRICT pset,
        particle_num_elements_t const num_particles,
        XIter x_begin, PxIter px_begin, YIter y_begin, PyIter py_begin,
        ZetaIter zeta_begin, DeltaIter delta_begin, StateIter state_begin,
        AtElemIter at_elem_begin, AtTurnIter at_turn_begin, IdIter id_begin,
        PSigmaIter psigma_begin, RppIter rpp_begin, RvvIter rvv_begin,
        ChiIter chi_begin, ChargeRatioIter charge_ratio_begin,
        Charge0Iter charge0_begin, Mass0Iter mass0_begin, Beta0Iter beta0_begin,
        Gamma0Iter gamma0_begin, Pc0Iter pc0_begin, SIter s_begin,
        particle_num_elements_t capacity = particle_num_elements_t{ 0 }
    ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::arch_status_t status = st::ParticleSet_init< PSetT >(
            pset, num_particles, capacity );

        if( status == st::ARCH_STATUS_SUCCESS )
        {
            auto x_end = x_begin;
            std::advance( x_end, st::ParticleSet_x_length( pset ) );
            std::copy( x_begin, x_end, pset->m_x.begin() );

            auto px_end = px_begin;
            std::advance( px_end, st::ParticleSet_px_length( pset ) );
            std::copy( px_begin, px_end, pset->m_px.begin() );

            auto y_end = y_begin;
            std::advance( y_end, st::ParticleSet_y_length( pset ) );
            std::copy( y_begin, y_end, pset->m_y.begin() );

            auto py_end = py_begin;
            std::advance( py_end, st::ParticleSet_py_length( pset ) );
            std::copy( py_begin, py_end, pset->m_py.begin() );

            auto zeta_end = zeta_begin;
            std::advance( zeta_end, st::ParticleSet_zeta_length( pset ) );
            std::copy( zeta_begin, zeta_end, pset->m_zeta.begin() );

            auto delta_end = delta_begin;
            std::advance( delta_end, st::ParticleSet_delta_length( pset ) );
            std::copy( delta_begin, delta_end, pset->m_delta.begin() );

            auto state_end = state_begin;
            std::advance( state_end, st::ParticleSet_state_length( pset ) );
            std::copy( state_begin, state_end, pset->m_state.begin() );

            auto at_element_end = at_elem_begin;
            std::advance( at_element_end,
                st::ParticleSet_at_element_length( pset ) );
            std::copy( at_elem_begin, at_element_end,
                       pset->m_at_element.begin() );

            auto at_turn_end = at_turn_begin;
            std::advance( at_turn_end, st::ParticleSet_at_turn_length( pset ) );
            std::copy( at_turn_begin, at_turn_end, pset->m_at_turn.begin() );

            auto id_end = id_begin;
            std::advance( id_end, st::ParticleSet_particle_id_length( pset ) );
            std::copy( id_begin, id_end, pset->m_particle_id.begin() );

            auto psigma_end = psigma_begin;
            std::advance( psigma_end, st::ParticleSet_psigma_length( pset ) );
            std::copy( psigma_begin, psigma_end, pset->m_psigma.begin() );

            auto rpp_end = rpp_begin;
            std::advance( rpp_end, st::ParticleSet_rpp_length( pset ) );
            std::copy( rpp_begin, rpp_end, pset->m_rpp.begin() );

            auto rvv_end = rvv_begin;
            std::advance( rvv_end, st::ParticleSet_rvv_length( pset ) );
            std::copy( rvv_begin, rvv_end, pset->m_rvv.begin() );

            auto chi_end = chi_begin;
            std::advance( chi_end, st::ParticleSet_chi_length( pset ) );
            std::copy( chi_begin, chi_end, pset->m_chi.begin() );

            auto charge_ratio_end = charge_ratio_begin;
            std::advance( charge_ratio_end,
                          st::ParticleSet_charge_ratio_length( pset ) );

            std::copy( charge_ratio_begin, charge_ratio_end,
                       pset->m_charge_ratio.begin() );

            auto charge0_end = charge0_begin;
            std::advance( charge0_end, st::ParticleSet_charge0_length( pset ) );
            std::copy( charge0_begin, charge0_end, pset->m_charge0.begin() );

            auto mass0_end = mass0_begin;
            std::advance( mass0_end, st::ParticleSet_mass0_length( pset ) );
            std::copy( mass0_begin, mass0_end, pset->m_mass0.begin() );

            auto beta0_end = beta0_begin;
            std::advance( beta0_end, st::ParticleSet_beta0_length( pset ) );
            std::copy( beta0_begin, beta0_end, pset->m_beta0.begin() );

            auto gamma0_end = gamma0_begin;
            std::advance( gamma0_end, st::ParticleSet_gamma0_length( pset ) );
            std::copy( gamma0_begin, gamma0_end, pset->m_gamma0.begin() );

            auto pc0_end = pc0_begin;
            std::advance( pc0_end, st::ParticleSet_pc0_length( pset ) );
            std::copy( pc0_begin, pc0_end, pset->m_pc0.begin() );

            auto s_end = s_begin;
            std::advance( s_end, st::ParticleSet_s_length( pset ) );
            std::copy( s_begin, s_end, pset->m_s.begin() );
        }

        return status;
    }
}

#endif /* __cplusplus */

#endif /* SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SET_VECTOR_CXX_HPP__ */
