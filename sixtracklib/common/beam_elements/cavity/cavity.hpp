#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_CAVITY_CXX_HPP__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_CAVITY_CXX_HPP__

#include <type_traits>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/buffer.h"

#include "sixtracklib/common/beam_elements/beam_elements_base.hpp"
#include "sixtracklib/common/beam_elements/cavity/cavity_traits.hpp"
#include "sixtracklib/common/beam_elements/cavity_data.hpp"
#include "sixtracklib/common/beam_elements/cavity.h"

namespace sixtrack_cxx
{
    template< class BeObjData >
    class CavityInterface :
        public SIXTRL_CXX_NAMESPACE::BeamElementBase< BeObjData, ::NS(Cavity) >
    {
        public:

        typedef SIXTRL_CXX_NAMESPACE::Buffer buffer_t;
        typedef buffer_t::c_api_t c_buffer_t;

        typedef SIXTRL_CXX_NAMESPACE::BeamElementBase< BeObjData, ::NS(Cavity) >
                _base_t;

        typedef typename _base_t::c_api_t c_api_t;

        template< typename T > using can_store_cobj_t =
            std::enable_if< _base_t::SupportsCObjectsStorage(), T >;

        typedef SIXTRL_CXX_NAMESPACE::CavityTraits< BeObjData > be_traits_t;
        typedef typename be_traits_t::real_t real_t;

        static_assert( !SIXTRL_CXX_NAMESPACE::ObjData_has_data_ptrs<
            BeObjData >(),
            "Cavity* implementations are not supposed to have dataptrs" );

        /* ----------------------------------------------------------------- */

        SIXTRL_FN CavityInterface() { this->init(); }

        SIXTRL_FN explicit CavityInterface( const c_api_t *const
            SIXTRL_RESTRICT cavity ) { this->init( cavity ); }

        SIXTRL_FN CavityInterface( real_t const& SIXTRL_RESTRICT_REF _voltage,
            real_t const& SIXTRL_RESTRICT_REF _frequency,
            real_t const& SIXTRL_RESTRICT_REF _lag )
        {
            this->init( _voltage, _frequency, _lag );
        }

        SIXTRL_FN CavityInterface(
            CavityInterface< BeObjData > const& other) = default;

        SIXTRL_FN CavityInterface(
            CavityInterface< BeObjData >&& other ) = default;

        SIXTRL_FN CavityInterface< BeObjData >& operator=(
            CavityInterface< BeObjData > const& other) = default;

        SIXTRL_FN CavityInterface< BeObjData >& operator=(
            CavityInterface< BeObjData >&& other ) = default;

        SIXTRL_FN ~CavityInterface() = default;

        SIXTRL_FN void init()
        {
            this->voltage   = real_t{ 0.0 };
            this->frequency = real_t{ 0.0 };
            this->lag       = real_t{ 0.0 };
        }

        SIXTRL_FN void init( const c_api_t *const SIXTRL_RESTRICT cavity )
        {
            if( cavity != nullptr )
            {
                this->voltage   = real_t( cavity->voltage );
                this->frequency = real_t( cavity->frequency );
                this->lag       = real_t( cavity->lag );
            }
            else this->init();
        }

        SIXTRL_FN void init( real_t const& SIXTRL_RESTRICT_REF _voltage,
            real_t const& SIXTRL_RESTRICT_REF _frequency,
            real_t const& SIXTRL_RESTRICT_REF _lag )
        {
            this->voltage   = _voltage;
            this->frequency = _frequency;
            this->lag       = _lag;
        }

        /* ----------------------------------------------------------------- */

        static SIXTRL_FN typename can_store_cobj_t< bool >::type
        CanStoreObjectOnBuffer(
            const c_buffer_t *const SIXTRL_RESTRICT buffer,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_objects = nullptr,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_slots = nullptr,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_dataptrs = nullptr )
        {
            using _this_t = SIXTRL_CXX_NAMESPACE::CavityInterface< BeObjData >;
            return SIXTRL_CXX_NAMESPACE::Obj_can_store_on_buffer< BeObjData >( buffer,
                SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_CAVITY, nullptr,
                sizeof( _this_t ), requ_num_objects, requ_num_slots,
                    requ_num_dataptrs );
        }

        static SIXTRL_FN typename can_store_cobj_t< bool >::type
        CanStoreObjectOnBuffer( buffer_t const& SIXTRL_RESTRICT_REF buffer,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_objects = nullptr,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_slots = nullptr,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_dataptrs = nullptr )
        {
            using _this_t = SIXTRL_CXX_NAMESPACE::CavityInterface< BeObjData >;
            return _this_t::CanStoreObjectOnBuffer( buffer.getCApiPtr(),
                requ_num_objects, requ_num_slots, requ_num_dataptrs );
        }

        static SIXTRL_FN
        typename can_store_cobj_t< CavityInterface< BeObjData >* >::type
        CreateNewObject( c_buffer_t* SIXTRL_RESTRICT buffer )
        {
            using _this_t = SIXTRL_CXX_NAMESPACE::CavityInterface< BeObjData >;
            _this_t temp;

            return SIXTRL_CXX_NAMESPACE::ObjStore_get_ptr_obj_from_info< _this_t >(
                SIXTRL_CXX_NAMESPACE::Obj_store_on_buffer( buffer,
                SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_CAVITY, temp.ptrBeData() ),
                SIXTRL_CXX_NAMESPACE::ObjDataStoreTraits< BeObjData >::ObjTypeId() );
        }

        static SIXTRL_FN
        typename can_store_cobj_t< CavityInterface< BeObjData >* >::type
        CreateNewObject( buffer_t& SIXTRL_RESTRICT_REF buffer )
        {
            using _this_t = SIXTRL_CXX_NAMESPACE::CavityInterface< BeObjData >;
            return _this_t::CreateNewObject( buffer.getCApiPtr() );
        }

        template< typename... Args >
        static SIXTRL_FN
        typename can_store_cobj_t< CavityInterface< BeObjData >* >::type
        AddObject( c_buffer_t* SIXTRL_RESTRICT buffer, Args&&... args )
        {
            using _this_t = SIXTRL_CXX_NAMESPACE::CavityInterface< BeObjData >;
            _this_t temp( std::forward< Args >( args )... );

            return SIXTRL_CXX_NAMESPACE::ObjStore_get_ptr_obj_from_info< _this_t >(
                SIXTRL_CXX_NAMESPACE::Obj_store_on_buffer( buffer,
                SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_CAVITY, temp.ptrBeData() ),
                SIXTRL_CXX_NAMESPACE::ObjDataStoreTraits< BeObjData >::ObjTypeId() );
        }

        template< typename... Args >
        static SIXTRL_FN
        typename can_store_cobj_t< CavityInterface< BeObjData >* >::type
        AddObject( buffer_t& SIXTRL_RESTRICT_REF buffer, Args&&... args )
        {
            using _this_t = SIXTRL_CXX_NAMESPACE::CavityInterface< BeObjData >;
            _this_t temp( std::forward< Args >( args )... );

            return SIXTRL_CXX_NAMESPACE::ObjStore_get_ptr_obj_from_info< _this_t >(
                SIXTRL_CXX_NAMESPACE::Obj_store_on_buffer( buffer.getCApiPtr(),
                SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_CAVITY, temp.ptrBeData() ),
                SIXTRL_CXX_NAMESPACE::ObjDataStoreTraits< BeObjData >::ObjTypeId() );
        }

        SIXTRL_FN typename can_store_cobj_t< CavityInterface< BeObjData >* >::type
        storeCopy( c_buffer_t* SIXTRL_RESTRICT buffer )
        {
            using _this_t = SIXTRL_CXX_NAMESPACE::CavityInterface< BeObjData >;
            return SIXTRL_CXX_NAMESPACE::ObjStore_get_ptr_obj_from_info< _this_t >(
                SIXTRL_CXX_NAMESPACE::Obj_store_on_buffer( buffer,
                SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_CAVITY, this->ptrBeData() ),
                SIXTRL_CXX_NAMESPACE::ObjDataStoreTraits< BeObjData >::ObjTypeId() );
        }

        SIXTRL_FN typename can_store_cobj_t< CavityInterface< BeObjData >* >::type
        storeCopy( buffer_t& SIXTRL_RESTRICT_REF buffer )
        {
            return this->storeCopy( buffer.getCApiPtr() );
        }

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        static SIXTRL_FN
        typename can_store_cobj_t< CavityInterface< BeObjData > const* >::type
        GetConstObj( const c_buffer_t *const SIXTRL_RESTRICT buffer,
                ::NS(buffer_size_t) const index )
        {
            using _this_t = SIXTRL_CXX_NAMESPACE::CavityInterface< BeObjData >;
            return ObjStore_get_ptr_const_obj_from_info< _this_t >(
                ::NS(Buffer_get_const_object)( buffer, index ),
                SIXTRL_CXX_NAMESPACE::ObjDataStoreTraits< BeObjData >::ObjTypeId() );
        }

        static SIXTRL_FN
        typename can_store_cobj_t< CavityInterface< BeObjData >* >::type
        GetObj( c_buffer_t* SIXTRL_RESTRICT buffer,
                ::NS(buffer_size_t) const index )
        {
            using _this_t = SIXTRL_CXX_NAMESPACE::CavityInterface< BeObjData >;
            return ObjStore_get_ptr_obj_from_info< _this_t >(
                ::NS(Buffer_get_object)( buffer, index ),
                SIXTRL_CXX_NAMESPACE::ObjDataStoreTraits< BeObjData >::ObjTypeId() );
        }

        static SIXTRL_FN
        typename can_store_cobj_t< CavityInterface< BeObjData > const* >::type
        GetConstObj( buffer_t const& SIXTRL_RESTRICT buffer,
                     ::NS(buffer_size_t) const index )
        {
            using _this_t = SIXTRL_CXX_NAMESPACE::CavityInterface< BeObjData >;
            return _this_t::GetConstObj( buffer.getCApiPtr(), index );
        }

        static SIXTRL_FN
        typename can_store_cobj_t< CavityInterface< BeObjData >* >::type
        GetObj( buffer_t& SIXTRL_RESTRICT buffer,
                ::NS(buffer_size_t) const index )
        {
            using _this_t = SIXTRL_CXX_NAMESPACE::CavityInterface< BeObjData >;
            return _this_t::GetObj( buffer.getCApiPtr(), index );
        }
    };

    typedef CavityInterface< ::NS(Cavity) > CCavity;
    typedef CavityInterface< CavityData< double, 8 > > Cavity;

    template< class R, std::size_t RAlign =
        SIXTRL_CXX_NAMESPACE::TypeStoreTraits< R >::StorageAlign() >
    using TCavity = CavityInterface< CavityData< R, RAlign > >;
}

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_CAVITY_CXX_HPP__ */
/* end: */
