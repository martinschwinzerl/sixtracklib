#ifndef SIXTRACKLIB_COMMMON_PARTICLES_TRACK_PARTICLE_BASE_CXX_HPP__
#define SIXTRACKLIB_COMMMON_PARTICLES_TRACK_PARTICLE_BASE_CXX_HPP__

#include <cstddef>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/internal/objects_type_id.h"

#include "sixtracklib/common/internal/math_constant_traits.hpp"
#include "sixtracklib/common/particles/particle_traits.hpp"
#include "sixtracklib/common/particles/track_particle.h"
#include "sixtracklib/common/particles/track_particle_data.hpp"
#include "sixtracklib/common/buffer.hpp"
#include "sixtracklib/common/buffer.h"

namespace SIXTRL_CXX_NAMESPACE
{
    template< class ParticleData >
    class TrackParticleInterface : public ParticleData
    {
        public:

        typedef ParticleData        particle_data_t;
        typedef ::NS(TrackParticle) c_api_t;
        typedef ::NS(buffer_size_t) size_type;

        typedef typename TrackParticleDataTraits< ParticleData >::real_t real_t;
        typedef typename TrackParticleDataTraits< ParticleData >::int_t  int_t;

        static SIXTRL_FN constexpr bool SupportsCObjectsStorage()
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            return st::ObjData_can_be_stored_on_cobjects_buffer<
                particle_data_t >();
        }

        template< typename T > using can_store_cobj_t = std::enable_if<
            TrackParticleInterface< ParticleData
                >::SupportsCObjectsStorage(), T >;

        static SIXTRL_FN constexpr size_type NumDataPtrs()
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            return st::ObjDataStoreLayoutTraits<
                particle_data_t >::NumDataPtrs();
        }

        static SIXTRL_FN constexpr bool HasDataPtrs()
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            return ( st::ObjDataStoreLayoutTraits<
                particle_data_t >::NumDataPtrs() == size_type{ 0 } );
        }

        static SIXTRL_FN constexpr bool SupportsCObjectsTrivialStorage()
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            return ( ( st::ObjData_can_be_stored_on_cobjects_buffer<
                        particle_data_t >() ) &&
                     ( st::BeamElementBase< particle_data_t, c_api_t
                        >::NumDataPtrs() == size_type{ 0 } ) );
        }

        static SIXTRL_FN constexpr bool NumOfDataPtrsCountsDependsOnData()
        {
            return ( ( BeamElementBase< particle_data_t, c_api_t
                    >::NumDataPtrs() != size_type{ 0 } ) &&
                ( ObjDataStoreLayoutTraits< particle_data_t
                    >::VarNumDataPtrCounts() ) );
        }

        /* ---------------------------------------------------------------- */

        static SIXTRL_FN constexpr bool HasCApiMemoryLayout()
        {
            return ObjDataStoreTraits< particle_data_t >::HasCApiLayout();
        }

        SIXTRL_FN c_api_t const* ptrConstCApi() const SIXTRL_RESTRICT
        {
            using _this_t = BeamElementBase< particle_data_t, c_api_t >;
            return ( _this_t::HasCApiMemoryLayout() )
                ? static_cast< c_api_t const* >( this ) : nullptr;
        }

        SIXTRL_FN c_api_t const* ptrCApi() const SIXTRL_RESTRICT
        {
            using _this_t = BeamElementBase< particle_data_t, c_api_t >;
            return ( _this_t::HasCApiMemoryLayout() )
                ? static_cast< c_api_t const* >( this ) : nullptr;
        }

        SIXTRL_FN c_api_t* ptrCApi() SIXTRL_RESTRICT
        {
            using _this_t = BeamElementBase< particle_data_t, c_api_t >;
            return ( _this_t::HasCApiMemoryLayout() )
                ? static_cast< c_api_t* >( this ) : nullptr;
        }

        /* ----------------------------------------------------------------- */

        SIXTRL_FN TrackParticleInterface() { this->init(); }

        SIXTRL_FN explicit TrackParticleInterface( const c_api_t *const
            SIXTRL_RESTRICT particle ) { this->init( particle ); }

        SIXTRL_FN explicit TrackParticleInterface(
            real_t const& SIXTRL_RESTRICT_REF length ) { this->init( length ); }

        SIXTRL_FN TrackParticleInterface(
            TrackParticleInterface< ParticleData > const& other) = default;

        SIXTRL_FN TrackParticleInterface(
            TrackParticleInterface< ParticleData >&& other ) = default;

        SIXTRL_FN TrackParticleInterface< ParticleData >& operator=(
            TrackParticleInterface< ParticleData > const& other) = default;

        SIXTRL_FN TrackParticleInterface< ParticleData >& operator=(
            TrackParticleInterface< ParticleData >&& other ) = default;

        SIXTRL_FN ~TrackParticleInterface() = default;

        SIXTRL_FN void init()
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            using real_constants_t = st::MathConstants< real_t >;
            using int_constants_t  = st::MathConstants< int_t >;

            this->q0     = real_constants_t::Zero();
            this->mass0  = real_constants_t::Zero();
            this->beta0  = real_constants_t::Zero();
            this->gamma0 = real_constants_t::Zero();
            this->p0c    = real_constants_t::Zero();

            this->s      = real_constants_t::Zero();
            this->x      = real_constants_t::Zero();
            this->y      = real_constants_t::Zero();
            this->px     = real_constants_t::Zero();
            this->py     = real_constants_t::Zero();
            this->zeta   = real_constants_t::Zero();

            this->psigma = real_constants_t::Zero();
            this->delta  = real_constants_t::Zero();
            this->rpp    = real_constants_t::One();
            this->rvv    = real_constants_t::One();
            this->chi    = real_constants_t::One();
            this->charge_ratio = real_constants_t::One();

            this->particle_id   = int_constants_t::Zero();
            this->at_element_id = int_constants_t::Zero();
            this->at_turn       = int_constants_t::Zero();
            this->state         = int_constants_t::One();
        }

        SIXTRL_FN void init( const c_api_t *const SIXTRL_RESTRICT particle )
        {
            if( particle != nullptr )
            {
                this->q0            = real_t( particle->q0 );
                this->mass0         = real_t( particle->mass0 );
                this->beta0         = real_t( particle->beta0 );
                this->gamma0        = real_t( particle->gamma0 );
                this->p0c           = real_t( particle->p0c );

                this->s             = real_t( particle->s );
                this->x             = real_t( particle->x );
                this->y             = real_t( particle->y );
                this->px            = real_t( particle->px );
                this->py            = real_t( particle->py );
                this->zeta          = real_t( particle->zeta );

                this->psigma        = real_t( particle->psigma );
                this->delta         = real_t( particle->delta );
                this->rpp           = real_t( particle->rpp );
                this->rvv           = real_t( particle->rvv );
                this->chi           = real_t( particle->chi );
                this->charge_ratio  = real_t( particle->charge_ratio );

                this->particle_id   = int_t( particle->particle_id );
                this->at_element_id = int_t( particle->at_element_id );
                this->at_turn       = int_t( particle->at_turn );
                this->state         = int_t( particle->state );
            }
        }

        SIXTRL_FN void init(
            real_t const& q0,    real_t const& mass0, real_t const& beta0,
            real_t const& gamm0, real_t const& p0c,   real_t const& s,
            real_t const& x,     real_t const& y,     real_t const& px,
            real_t const& py,    real_t const& zeta,  real_t const& psigma,
            real_t const& delta, real_t const& rpp,   real_t const& rvv,
            real_t const& chi,   real_t const& charge_ratio,
            int_t const& particle_id, int_t const& at_element_id,
            int_t const& at_turn,     int_t const& state )
        {
            this->q0            = q0;
            this->mass0         = mass0;
            this->beta0         = beta0;
            this->gamma0        = gamma0;
            this->p0c           = p0c;

            this->s             = s;
            this->x             = x;
            this->y             = y;
            this->px            = px;
            this->py            = py;
            this->zeta          = zeta;

            this->psigma        = psigma;
            this->delta         = delta;
            this->rpp           = rpp;
            this->rvv           = rvv;
            this->chi           = chi;
            this->charge_ratio  = charge_ratio;

            this->particle_id   = particle_id;
            this->at_element_id = at_element_id;
            this->at_turn       = at_turn;
            this->state         = state;
        }

        /* ----------------------------------------------------------------- */

        SIXTRL_FN particle_data_t& particleData() SIXTRL_NOEXCEPT
        {
            return static_cast< particle_data_t& >( *this );
        }

        SIXTRL_FN particle_data_t const& particleData() const SIXTRL_NOEXCEPT
        {
            return static_cast< particle_data_t const& >( *this );
        }

        SIXTRL_FN particle_data_t* ptrParticleData() SIXTRL_NOEXCEPT
        {
            return static_cast< particle_data_t* >( this );
        }

        SIXTRL_FN particle_data_t const* ptrParticleData() const SIXTRL_NOEXCEPT
        {
            return static_cast< particle_data_t const* >( this );
        }

        /* ----------------------------------------------------------------- */

        real_t getEnergy() const
        {
            return TrackParticleData_get_energy( *this );
        }

        void setEnergy( real_t const& SIXTRL_RESTRICT_REF new_energy )
        {
            TrackParticleData_set_energy( *this, new_energy );
        }

        void addEnergy( real_t const& SIXTRL_RESTRICT_REF delta_energy )
        {
            TrackParticleData_set_energy( *this, TrackParticleData_get_energy(
                *this ) + delta_energy );
        }

        /* ----------------------------------------------------------------- */

        static SIXTRL_FN typename can_store_cobj_t< bool >::type
        CanStoreObjectOnBuffer(
            const ::NS(Buffer) *const SIXTRL_RESTRICT buffer,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_objects = nullptr,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_slots = nullptr,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_dataptrs = nullptr )
        {
            using _this_t = TrackParticleInterface< ParticleData >;
            return Obj_can_store_on_buffer< ParticleData >( buffer,
                SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_TRACK_PARTICLE, nullptr,
                    sizeof( _this_t ), requ_num_objects, requ_num_slots,
                        requ_num_dataptrs );
        }

        static SIXTRL_FN typename can_store_cobj_t< bool >::type
        CanStoreObjectOnBuffer(
            SIXTRL_CXX_NAMESPACE::Buffer const& SIXTRL_RESTRICT_REF buffer,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_objects = nullptr,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_slots = nullptr,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_dataptrs = nullptr )
        {
            using _this_t = TrackParticleInterface< ParticleData >;
            return _this_t::CanStoreObjectOnBuffer( buffer.getCApiPtr(),
                requ_num_objects, requ_num_slots, requ_num_dataptrs );
        }

        static SIXTRL_FN
        typename can_store_cobj_t< TrackParticleInterface< ParticleData >* >::type
        CreateNewObject( ::NS(Buffer)* SIXTRL_RESTRICT buffer )
        {
            using _this_t = TrackParticleInterface< ParticleData >;
            _this_t temp;

            return ObjStore_get_ptr_obj_from_info< _this_t >(
                Obj_store_on_buffer( buffer,
                SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_TRACK_PARTICLE, temp.ptrBeData() ),
                ObjDataStoreTraits< ParticleData >::ObjTypeId() );
        }

        static SIXTRL_FN
        typename can_store_cobj_t< TrackParticleInterface<
            ParticleData >* >::type CreateNewObject(
            SIXTRL_CXX_NAMESPACE::Buffer& SIXTRL_RESTRICT_REF buffer )
        {
            using _this_t = TrackParticleInterface< ParticleData >;
            return _this_t::CreateNewObject( buffer.getCApiPtr() );
        }

        template< typename... Args >
        static SIXTRL_FN
        typename can_store_cobj_t< TrackParticleInterface< ParticleData >* >::type
        AddObject( ::NS(Buffer)* SIXTRL_RESTRICT buffer, Args&&... args )
        {
            using _this_t = TrackParticleInterface< ParticleData >;
            _this_t temp( std::forward< Args >( args )... );

            return ObjStore_get_ptr_obj_from_info< _this_t >(
                Obj_store_on_buffer( buffer,
                SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_TRACK_PARTICLE, temp.ptrBeData() ),
                ObjDataStoreTraits< ParticleData >::ObjTypeId() );
        }

        template< typename... Args >
        static SIXTRL_FN typename can_store_cobj_t<
            TrackParticleInterface< ParticleData >* >::type
        AddObject( SIXTRL_CXX_NAMESPACE::Buffer& SIXTRL_RESTRICT_REF buffer,
                   Args&&... args )
        {
            using _this_t = TrackParticleInterface< ParticleData >;
            _this_t temp( std::forward< Args >( args )... );

            return ObjStore_get_ptr_obj_from_info< _this_t >(
                Obj_store_on_buffer( buffer.getCApiPtr(),
                SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_TRACK_PARTICLE, temp.ptrBeData() ),
                ObjDataStoreTraits< ParticleData >::ObjTypeId() );
        }

        SIXTRL_FN typename can_store_cobj_t<
            TrackParticleInterface< ParticleData >* >::type
        storeCopy( ::NS(Buffer)* SIXTRL_RESTRICT buffer )
        {
            using _this_t = TrackParticleInterface< ParticleData >;
            return ObjStore_get_ptr_obj_from_info< _this_t >(
                Obj_store_on_buffer( buffer,
                SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_TRACK_PARTICLE, this->ptrBeData() ),
                ObjDataStoreTraits< ParticleData >::ObjTypeId() );
        }

        SIXTRL_FN typename can_store_cobj_t<
            TrackParticleInterface< ParticleData >* >::type
        storeCopy( SIXTRL_CXX_NAMESPACE::Buffer& SIXTRL_RESTRICT_REF buffer )
        {
            return this->storeCopy( buffer.getCApiPtr() );
        }

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        static SIXTRL_FN typename can_store_cobj_t<
            TrackParticleInterface< ParticleData > const* >::type
        GetConstObj( const ::NS(Buffer) *const SIXTRL_RESTRICT buffer,
                ::NS(buffer_size_t) const index )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            using _this_t = TrackParticleInterface< ParticleData >;
            return st::ObjStore_get_ptr_const_obj_from_info< _this_t >(
                ::NS(Buffer_get_const_object)( buffer, index ),
                st::ObjDataStoreTraits< ParticleData >::ObjTypeId() );
        }

        static SIXTRL_FN
        typename can_store_cobj_t< TrackParticleInterface< ParticleData >* >::type
        GetObj( ::NS(Buffer)* SIXTRL_RESTRICT buffer,
                ::NS(buffer_size_t) const index )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            using _this_t = TrackParticleInterface< ParticleData >;
            return ObjStore_get_ptr_obj_from_info< _this_t >(
                ::NS(Buffer_get_object)( buffer, index ),
                st::ObjDataStoreTraits< ParticleData >::ObjTypeId() );
        }

        static SIXTRL_FN typename can_store_cobj_t<
            TrackParticleInterface< ParticleData > const* >::type GetConstObj(
            SIXTRL_CXX_NAMESPACE::Buffer const& SIXTRL_RESTRICT_REF buffer,
            ::NS(buffer_size_t) const index )
        {
            using _this_t = TrackParticleInterface< ParticleData >;
            return _this_t::GetConstObj( buffer.getCApiPtr(), index );
        }

        static SIXTRL_FN
        typename can_store_cobj_t< TrackParticleInterface< ParticleData >* >::type
        GetObj( SIXTRL_CXX_NAMESPACE::Buffer& SIXTRL_RESTRICT_REF buffer,
                ::NS(buffer_size_t) const index )
        {
            using _this_t = TrackParticleInterface< ParticleData >;
            return _this_t::GetObj( buffer.getCApiPtr(), index );
        }
    };

    typedef TrackParticleInterface< ::NS(TrackParticle) > CTrackParticle;
    typedef TrackParticleInterface<
        TrackParticleData< double, int64_t, 8, 8 > > TrackParticle;

    template< class R, class I,
        std::size_t RAlign = TypeStoreTraits< R >::StorageAlign(),
        std::size_t IAlign = TypeStoreTraits< I >::StorageAlign() >
    using TTrackParticle = TrackParticleInterface<
        TrackPatricleData< R, I, RAlign, IAlign > >;
}

#endif /* SIXTRACKLIB_COMMMON_PARTICLES_TRACK_PARTICLE_BASE_CXX_HPP__ */
/* end: sixtracklib/common/particles/track_particle.hpp */
