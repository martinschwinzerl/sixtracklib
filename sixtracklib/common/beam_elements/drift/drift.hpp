#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_DRIFT_CXX_HPP__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_DRIFT_CXX_HPP__

#include "sixtracklib/common/definitions.h"

#include "sixtracklib/common/beam_elements/beam_elements_base.hpp"
#include "sixtracklib/common/beam_elements/drift/drift_traits.hpp"
#include "sixtracklib/common/beam_elements/drift/drift_data.hpp"
#include "sixtracklib/common/beam_elements/drift/drift.h"
#include "sixtracklib/common/buffer.hpp"
#include "sixtracklib/common/buffer.h"

namespace SIXTRL_CXX_NAMESPACE
{
    template< class BeObjData > class DriftInterface :
        public SIXTRL_CXX_NAMESPACE::BeamElementBase< BeObjData, ::NS(Drift) >
    {
        public:

        typedef SIXTRL_CXX_NAMESPACE::BeamElementBase< BeObjData, ::NS(Drift) > _base_t;
        typedef typename _base_t::c_api_t       c_api_t;
        typedef SIXTRL_CXX_NAMESPACE::Buffer    buffer_t;
        typedef buffer_t::c_api_t               c_buffer_t;

        template< typename T > using can_store_cobj_t =
            std::enable_if< _base_t::SupportsCObjectsStorage(), T >;

        typedef SIXTRL_CXX_NAMESPACE::DriftTraits< BeObjData > be_traits_t;
        typedef typename be_traits_t::real_t real_t;

        static_assert( !SIXTRL_CXX_NAMESPACE::ObjData_has_data_ptrs< BeObjData >(),
            "Drift* implementations are not supposed to have dataptrs" );

        /* ----------------------------------------------------------------- */

        SIXTRL_FN DriftInterface() { this->init(); }

        SIXTRL_FN DriftInterface( const c_api_t *const
            SIXTRL_RESTRICT drift ) { this->init( drift ); }

        SIXTRL_FN DriftInterface( real_t const& SIXTRL_RESTRICT_REF length )
        { this->init( length ); }

        SIXTRL_FN DriftInterface(
            DriftInterface< BeObjData > const& other) = default;

        SIXTRL_FN DriftInterface(
            DriftInterface< BeObjData >&& other ) = default;

        SIXTRL_FN DriftInterface< BeObjData >& operator=(
            DriftInterface< BeObjData > const& other) = default;

        SIXTRL_FN DriftInterface< BeObjData >& operator=(
            DriftInterface< BeObjData >&& other ) = default;

        SIXTRL_FN ~DriftInterface() = default;

        SIXTRL_FN void init() { this->length = real_t{ 0.0 }; }

        SIXTRL_FN void init( real_t const& SIXTRL_RESTRICT_REF length )
        {
            this->length = length;
        }

        SIXTRL_FN void init( const c_api_t *const SIXTRL_RESTRICT drift )
        {
            if( drift != nullptr )
            {
                this->init( real_t( drift->length ) );
            }
            else this->init();
        }

        /* ----------------------------------------------------------------- */

        static SIXTRL_FN typename can_store_cobj_t< bool >::type
        CanStoreObjectOnBuffer( const c_buffer_t *const SIXTRL_RESTRICT buffer,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_objects = nullptr,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_slots = nullptr,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_dataptrs = nullptr )
        {
            using _this_t = SIXTRL_CXX_NAMESPACE::DriftInterface< BeObjData >;
            return SIXTRL_CXX_NAMESPACE::Obj_can_store_on_buffer< BeObjData >( buffer,
                SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_DRIFT, nullptr,
                    sizeof( _this_t ), requ_num_objects, requ_num_slots,
                        requ_num_dataptrs );
        }

        static SIXTRL_FN typename can_store_cobj_t< bool >::type
        CanStoreObjectOnBuffer( buffer_t const& SIXTRL_RESTRICT buffer,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_objects = nullptr,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_slots = nullptr,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_dataptrs = nullptr )
        {
            using _this_t = SIXTRL_CXX_NAMESPACE::DriftInterface< BeObjData >;
            return _this_t::CanStoreObjectOnBuffer( buffer.getCApiPtr(),
                requ_num_objects, requ_num_slots, requ_num_dataptrs );
        }

        static SIXTRL_FN
        typename can_store_cobj_t< DriftInterface< BeObjData >* >::type
        CreateNewObject( c_buffer_t* SIXTRL_RESTRICT buffer )
        {
            using _this_t = SIXTRL_CXX_NAMESPACE::DriftInterface< BeObjData >;
            _this_t temp;

            return SIXTRL_CXX_NAMESPACE::ObjStore_get_ptr_obj_from_info< _this_t >(
                SIXTRL_CXX_NAMESPACE::Obj_store_on_buffer( buffer,
                SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_DRIFT, temp.ptrBeData() ),
                SIXTRL_CXX_NAMESPACE::ObjDataStoreTraits< BeObjData >::ObjTypeId() );
        }

        static SIXTRL_FN
        typename can_store_cobj_t< DriftInterface< BeObjData >* >::type
        CreateNewObject( buffer_t& SIXTRL_RESTRICT_REF buffer )
        {
            using _this_t = SIXTRL_CXX_NAMESPACE::DriftInterface< BeObjData >;
            return _this_t::CreateNewObject( buffer.getCApiPtr() );
        }

        template< typename... Args > static SIXTRL_FN
        typename can_store_cobj_t< DriftInterface< BeObjData >* >::type
        AddObject( c_buffer_t* SIXTRL_RESTRICT buffer, Args&&... args )
        {
            using _this_t = SIXTRL_CXX_NAMESPACE::DriftInterface< BeObjData >;
            _this_t temp( std::forward< Args >( args )... );

            return SIXTRL_CXX_NAMESPACE::ObjStore_get_ptr_obj_from_info< _this_t >(
                SIXTRL_CXX_NAMESPACE::Obj_store_on_buffer( buffer,
                SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_DRIFT, temp.ptrBeData() ),
                SIXTRL_CXX_NAMESPACE::ObjDataStoreTraits< BeObjData >::ObjTypeId() );
        }

        template< typename... Args > static SIXTRL_FN
        typename can_store_cobj_t< DriftInterface< BeObjData >* >::type
        AddObject( buffer_t& SIXTRL_RESTRICT_REF buffer, Args&&... args )
        {
            using _this_t = SIXTRL_CXX_NAMESPACE::DriftInterface< BeObjData >;
            _this_t temp( std::forward< Args >( args )... );

            return SIXTRL_CXX_NAMESPACE::ObjStore_get_ptr_obj_from_info< _this_t >(
                SIXTRL_CXX_NAMESPACE::Obj_store_on_buffer( buffer.getCApiPtr(),
                SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_DRIFT, temp.ptrBeData() ),
                SIXTRL_CXX_NAMESPACE::ObjDataStoreTraits< BeObjData >::ObjTypeId() );
        }

        SIXTRL_FN typename can_store_cobj_t< DriftInterface< BeObjData >* >::type
        storeCopy( c_buffer_t* SIXTRL_RESTRICT buffer )
        {
            using _this_t = SIXTRL_CXX_NAMESPACE::DriftInterface< BeObjData >;
            return SIXTRL_CXX_NAMESPACE::ObjStore_get_ptr_obj_from_info< _this_t >(
                SIXTRL_CXX_NAMESPACE::Obj_store_on_buffer( buffer,
                SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_DRIFT, this->ptrBeData() ),
                SIXTRL_CXX_NAMESPACE::ObjDataStoreTraits< BeObjData >::ObjTypeId() );
        }

        SIXTRL_FN typename can_store_cobj_t< DriftInterface< BeObjData >* >::type
        storeCopy( buffer_t& SIXTRL_RESTRICT_REF buffer )
        {
            return this->storeCopy( buffer.getCApiPtr() );
        }

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        static SIXTRL_FN
        typename can_store_cobj_t< DriftInterface< BeObjData > const* >::type
        GetConstObj( const c_buffer_t *const SIXTRL_RESTRICT buffer,
                ::NS(buffer_size_t) const index )
        {
            using _this_t = SIXTRL_CXX_NAMESPACE::DriftInterface< BeObjData >;
            return ObjStore_get_ptr_const_obj_from_info< _this_t >(
                ::NS(Buffer_get_const_object)( buffer, index ),
                SIXTRL_CXX_NAMESPACE::ObjDataStoreTraits< BeObjData >::ObjTypeId() );
        }

        static SIXTRL_FN
        typename can_store_cobj_t< DriftInterface< BeObjData >* >::type
        GetObj( c_buffer_t* SIXTRL_RESTRICT buffer,
                ::NS(buffer_size_t) const index )
        {
            using _this_t = SIXTRL_CXX_NAMESPACE::DriftInterface< BeObjData >;
            return ObjStore_get_ptr_obj_from_info< _this_t >(
                ::NS(Buffer_get_object)( buffer, index ),
                SIXTRL_CXX_NAMESPACE::ObjDataStoreTraits< BeObjData >::ObjTypeId() );
        }

        static SIXTRL_FN
        typename can_store_cobj_t< DriftInterface< BeObjData > const* >::type
        GetConstObj( buffer_t const& SIXTRL_RESTRICT_REF buffer,
                ::NS(buffer_size_t) const index )
        {
            using _this_t = SIXTRL_CXX_NAMESPACE::DriftInterface< BeObjData >;
            return _this_t::GetConstObj( buffer.getCApiPtr(), index );
        }

        static SIXTRL_FN
        typename can_store_cobj_t< DriftInterface< BeObjData >* >::type
        GetObj( buffer_t& SIXTRL_RESTRICT buffer,
                ::NS(buffer_size_t) const index )
        {
            using _this_t = SIXTRL_CXX_NAMESPACE::DriftInterface< BeObjData >;
            return _this_t::GetObj( buffer.getCApiPtr(), index );
        }
    };

    typedef DriftInterface< ::NS(Drift) > CDrift;
    typedef DriftInterface< DriftData< double, 8 > > Drift;

    template< class R, std::size_t RAlign =
        SIXTRL_CXX_NAMESPACE::TypeStoreTraits< R >::StorageAlign() >
    using TDrift = DriftInterface< DriftData< R, RAlign > >;
}

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_DRIFT_CXX_HPP__ */
/* end: */
