#ifndef SIXTRACKLIB_COMMON_BE_SROTATION_BE_SROTATION_CXX_HPP__
#define SIXTRACKLIB_COMMON_BE_SROTATION_BE_SROTATION_CXX_HPP__

#include "sixtracklib/sixtracklib.hpp"

#include "cxx/common/be/beam_elements_base.hpp"
#include "cxx/common/be/srotation/be_srotation_traits.hpp"
#include "cxx/common/be/srotation/be_srotation_data.hpp"
#include "cxx/common/be/srotation/be_srotation.h"
#include "cxx/common/be/srotation/buffer.hpp"

namespace SIXTRL_CXX_NAMESPACE
{
    template< class BeObjData > class SRotationInterface :
        public SIXTRL_CXX_NAMESPACE::BeamElementBase<
                BeObjData, ::NS(SRotation) >
    {
        public:

        typedef SIXTRL_CXX_NAMESPACE::BeamElementBase< BeObjData,
                ::NS(SRotation) > _base_t;

        typedef typename _base_t::c_api_t c_api_t;
        typedef SIXTRL_CXX_NAMESPACE::Buffer buffer_t;
        typedef buffer_t::c_api_t c_buffer_t;

        template< typename T > using can_store_cobj_t =
            std::enable_if< _base_t::SupportsCObjectsStorage(), T >;

        typedef SIXTRL_CXX_NAMESPACE::SRotationTraits< BeObjData > be_traits_t;
        typedef typename be_traits_t::real_t real_t;

        static_assert( !SIXTRL_CXX_NAMESPACE::ObjData_has_data_ptrs< BeObjData >(),
            "SRotation* implementations aren't supposed to have dataptrs" );

        /* ----------------------------------------------------------------- */

        SIXTRL_FN SRotationInterface() { this->init(); }

        SIXTRL_FN explicit SRotationInterface(
            const c_api_t *const SIXTRL_RESTRICT srot ) { this->init( srot ); }

        SIXTRL_FN explicit SRotationInterface(
            real_t const& SIXTRL_RESTRICT_REF angle ) { this->init( angle ); }

        SIXTRL_FN SRotationInterface(
            real_t const& SIXTRL_RESTRICT_REF _cos_z,
            real_t const& SIXTRL_RESTRICT_REF _sin_z )
        {
            this->init( _cos_z, _sin_z );
        }

        SIXTRL_FN SRotationInterface(
            SRotationInterface< BeObjData > const& other) = default;

        SIXTRL_FN SRotationInterface(
            SRotationInterface< BeObjData >&& other ) = default;

        SIXTRL_FN SRotationInterface< BeObjData >& operator=(
            SRotationInterface< BeObjData > const& other) = default;

        SIXTRL_FN SRotationInterface< BeObjData >& operator=(
            SRotationInterface< BeObjData >&& other ) = default;

        SIXTRL_FN ~SRotationInterface() = default;

        SIXTRL_FN void init()
        {
            this->cos_z = real_t{ 1.0 };    this->sin_z = real_t{ 0.0 };
        }

        SIXTRL_FN void init( real_t const& SIXTRL_RESTRICT_REF angle )
        {
            using std::cos;
            using std::sin;

            this->cos_z = cos( angle );
            this->sin_z = sin( angle );
        }

        SIXTRL_FN void init( const c_api_t *const SIXTRL_RESTRICT srot )
        {
            if( srot != nullptr )
            {
                this->cos_z = real_t( srot->cos_z );
                this->sin_z = real_t( srot->sin_z );
            }
            else this->init();
        }

        SIXTRL_FN void init( real_t const& SIXTRL_RESTRICT_REF _cos_z,
            real_t const& SIXTRL_RESTRICT_REF _sin_z )
        {
            this->cos_z = _cos_z;
            this->sin_z = _sin_z;
        }

        /* ----------------------------------------------------------------- */

        static SIXTRL_FN typename can_store_cobj_t< bool >::type
        CanStoreObjectOnBuffer(
            const c_buffer_t *const SIXTRL_RESTRICT buffer,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_objects = nullptr,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_slots = nullptr,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_dataptrs = nullptr )
        {
            using _this_t = SIXTRL_CXX_NAMESPACE::SRotationInterface< BeObjData >;
            return SIXTRL_CXX_NAMESPACE::Obj_can_store_on_buffer< BeObjData >( buffer,
                SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_SROTATION, sizeof( _this_t ),
                    requ_num_objects, requ_num_slots, requ_num_dataptrs );
        }

        static SIXTRL_FN typename can_store_cobj_t< bool >::type
        CanStoreObjectOnBuffer( buffer_t const& SIXTRL_RESTRICT_REF buffer,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_objects = nullptr,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_slots = nullptr,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_dataptrs = nullptr )
        {
            return SIXTRL_CXX_NAMESPACE::SRotationInterface<
                BeObjData >::CanStoreObjectOnBuffer( buffer.getCApiPtr(),
                    requ_num_objects, requ_num_slots, requ_num_dataptrs );
        }

        static SIXTRL_FN
        typename can_store_cobj_t< SRotationInterface< BeObjData >* >::type
        CreateNewObject( c_buffer_t* SIXTRL_RESTRICT buffer )
        {
            using _this_t = SIXTRL_CXX_NAMESPACE::SRotationInterface< BeObjData >;
            _this_t temp;

            return SIXTRL_CXX_NAMESPACE::ObjStore_get_ptr_obj_from_info< _this_t >(
                SIXTRL_CXX_NAMESPACE::Obj_store_on_buffer( buffer,
                SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_SROTATION, temp.ptrBeData() ),
                SIXTRL_CXX_NAMESPACE::ObjDataStoreTraits< BeObjData >::ObjTypeId() );
        }

        static SIXTRL_FN
        typename can_store_cobj_t< SRotationInterface< BeObjData >* >::type
        CreateNewObject( buffer_t& SIXTRL_RESTRICT buffer )
        {
            return SIXTRL_CXX_NAMESPACE::SRotationInterface<
                BeObjData >::CreateNewObject( buffer.getCApiPtr() );
        }

        template< typename... Args > static SIXTRL_FN
        typename can_store_cobj_t< SRotationInterface< BeObjData >* >::type
        AddObject( c_buffer_t* SIXTRL_RESTRICT buffer, Args&&... args )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            using _this_t = st::SRotationInterface< BeObjData >;
            _this_t temp( std::forward< Args >( args )... );

            return st::ObjStore_get_ptr_obj_from_info< _this_t >(
                st::Obj_store_on_buffer( buffer,
                    st::OBJECT_TYPE_SROTATION, temp.ptrBeData() ),
                st::ObjDataStoreTraits< BeObjData >::ObjTypeId() );
        }

        template< typename... Args > static SIXTRL_FN
        typename can_store_cobj_t< SRotationInterface< BeObjData >* >::type
        AddObject( buffer_t& SIXTRL_RESTRICT_REF buffer, Args&&... args )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            using _this_t = st::SRotationInterface< BeObjData >;
            _this_t temp( std::forward< Args >( args )... );

            return st::ObjStore_get_ptr_obj_from_info< _this_t >(
                st::Obj_store_on_buffer( buffer.getCApiPtr(),
                    st::OBJECT_TYPE_SROTATION, temp.ptrBeData() ),
                st::ObjDataStoreTraits< BeObjData >::ObjTypeId() );
        }

        SIXTRL_FN typename can_store_cobj_t<
            SRotationInterface< BeObjData >* >::type
        storeCopy( c_buffer_t* SIXTRL_RESTRICT buffer )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            using _this_t = SIXTRL_CXX_NAMESPACE::SRotationInterface< BeObjData >;
            return SIXTRL_CXX_NAMESPACE::ObjStore_get_ptr_obj_from_info< _this_t >(
                SIXTRL_CXX_NAMESPACE::Obj_store_on_buffer( buffer, this->ptrBeData(),
                    st::OBJECT_TYPE_SROTATION, sizeof( _this_t ) ),
                SIXTRL_CXX_NAMESPACE::ObjDataStoreTraits< BeObjData >::ObjTypeId() );
        }

        SIXTRL_FN typename can_store_cobj_t<
            SRotationInterface< BeObjData >* >::type
        storeCopy( buffer_t& SIXTRL_RESTRICT_REF buffer )
        {
            return this->storeCopy( buffer.getCApiPtr() );
        }

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        static SIXTRL_FN typename can_store_cobj_t<
            SRotationInterface< BeObjData > const* >::type
        GetConstObj( const c_buffer_t *const SIXTRL_RESTRICT buffer,
                ::NS(buffer_size_t) const index )
        {
            using _this_t = SIXTRL_CXX_NAMESPACE::SRotationInterface< BeObjData >;
            return ObjStore_get_ptr_const_obj_from_info< _this_t >(
                ::NS(Buffer_get_const_object)( buffer, index ),
                SIXTRL_CXX_NAMESPACE::ObjDataStoreTraits< BeObjData >::ObjTypeId() );
        }

        static SIXTRL_FN typename can_store_cobj_t<
            SRotationInterface< BeObjData >* >::type
        GetObj( c_buffer_t* SIXTRL_RESTRICT buffer,
                ::NS(buffer_size_t) const index )
        {
            using _this_t = SIXTRL_CXX_NAMESPACE::SRotationInterface< BeObjData >;
            return ObjStore_get_ptr_obj_from_info< _this_t >(
                ::NS(Buffer_get_object)( buffer, index ),
                SIXTRL_CXX_NAMESPACE::ObjDataStoreTraits< BeObjData >::ObjTypeId() );
        }

        static SIXTRL_FN typename can_store_cobj_t<
            SRotationInterface< BeObjData > const* >::type
        GetConstObj( buffer_t const& SIXTRL_RESTRICT_REF buffer,
                ::NS(buffer_size_t) const index )
        {
            return SIXTRL_CXX_NAMESPACE::SRotationInterface<
                BeObjData >::GetConstObj( buffer.getCApiPtr(), index );
        }

        static SIXTRL_FN typename can_store_cobj_t<
            SRotationInterface< BeObjData >* >::type
        GetObj( buffer_t& SIXTRL_RESTRICT_REF buffer,
                ::NS(buffer_size_t) const index )
        {
            return SIXTRL_CXX_NAMESPACE::SRotationInterface<
                BeObjData >::GetObj( buffer.getCApiPtr(), index );
        }
    };

    typedef SRotationInterface< ::NS(SRotation) > CSRotation;
    typedef SRotationInterface< SRotationData< double, 8u > > SRotation;

    template< class R, std::size_t RAlign =
        SIXTRL_CXX_NAMESPACE::TypeStoreTraits< R >::StorageAlign() >
    using TSRotation = SRotationInterface< SRotationData< R, RAlign > >;
}

#endif /* SIXTRACKLIB_COMMON_BE_SROTATION_BE_SROTATION_CXX_HPP__ */
/* end: sixtracklib/common/beam_elements/srotation/srotation.hpp */
