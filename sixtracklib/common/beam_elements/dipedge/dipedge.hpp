#ifndef SIXTRACKLIB_COMMON_BE_DIPOLE_EDGE_BE_DIPOLE_EDGE_CXX_HPP__
#define SIXTRACKLIB_COMMON_BE_DIPOLE_EDGE_BE_DIPOLE_EDGE_CXX_HPP__

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/internal/objects_type_id.h"

#include "sixtracklib/common/beam_elements/beam_elements_base.hpp"
#include "sixtracklib/common/beam_elements/dipedge/dipedge_traits.hpp"
#include "sixtracklib/common/beam_elements/dipedge/dipedge_data.hpp"
#include "sixtracklib/common/beam_elements/dipedge/dipedge.h"
#include "sixtracklib/common/buffer.hpp"
#include "sixtracklib/common/buffer.h"

namespace SIXTRL_CXX_NAMESPACE
{
    template< class BeObjData > class DipoleEdgeInterface :
        public SIXTRL_CXX_NAMESPACE::BeamElementBase<
            BeObjData, ::NS(DipoleEdge) >
    {
        public:

        typedef SIXTRL_CXX_NAMESPACE::BeamElementBase<
            BeObjData, ::NS(DipoleEdge) > _base_t;

        typedef SIXTRL_CXX_NAMESPACE::Buffer    buffer_t;
        typedef buffer_t::c_api_t               c_buffer_t;

        typedef typename _base_t::c_api_t c_api_t;

        template< typename T > using can_store_cobj_t =
            std::enable_if< _base_t::SupportsCObjectsStorage(), T >;

        typedef SIXTRL_CXX_NAMESPACE::DipoleEdgeTraits< BeObjData > be_traits_t;
        typedef typename be_traits_t::real_t real_t;

        static_assert( !SIXTRL_CXX_NAMESPACE::ObjData_has_data_ptrs< BeObjData >(),
            "DipoleEdge* implementations are not supposed to have dataptrs" );

        /* ----------------------------------------------------------------- */

        SIXTRL_FN DipoleEdgeInterface() { this->init(); }

        SIXTRL_FN explicit DipoleEdgeInterface( const c_api_t *const
            SIXTRL_RESTRICT ptr_dipedge ) { this->init( ptr_dipedge ); }

        SIXTRL_FN DipoleEdgeInterface( real_t const& SIXTRL_RESTRICT_REF _r21,
            real_t const& SIXTRL_RESTRICT_REF _r43 )
        {
            this->init( _r21, _r43 );
        }

        SIXTRL_FN DipoleEdgeInterface(
            DipoleEdgeInterface< BeObjData > const& other) = default;

        SIXTRL_FN DipoleEdgeInterface(
            DipoleEdgeInterface< BeObjData >&& other ) = default;

        SIXTRL_FN DipoleEdgeInterface< BeObjData >& operator=(
            DipoleEdgeInterface< BeObjData > const& other) = default;

        SIXTRL_FN DipoleEdgeInterface< BeObjData >& operator=(
            DipoleEdgeInterface< BeObjData >&& other ) = default;

        SIXTRL_FN ~DipoleEdgeInterface() = default;

        SIXTRL_FN void init()
        {
            this->r21 = real_t{ 0.0 };
            this->r43 = real_t{ 0.0 };
        }

        SIXTRL_FN void init( const c_api_t *const SIXTRL_RESTRICT dipedge )
        {
            if( dipedge != nullptr )
            {
                this->init( real_t( dipedge->r21 ), real_t( dipedge->r43 ) );
            }
            else this->init();
        }

        SIXTRL_FN void init( real_t const& SIXTRL_RESTRICT_REF _r21,
                             real_t const& SIXTRL_RESTRICT_REF _r43 )
        {
            this->r21 = _r21;
            this->r43 = _r43;
        }

        /* ----------------------------------------------------------------- */

        static SIXTRL_FN typename can_store_cobj_t< bool >::type
        CanStoreObjectOnBuffer(
            const c_buffer_t *const SIXTRL_RESTRICT buffer,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_objects = nullptr,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_slots = nullptr,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_dataptrs = nullptr )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            using _this_t = st::DipoleEdgeInterface< BeObjData >;
            return SIXTRL_CXX_NAMESPACE::Obj_can_store_on_buffer< BeObjData >( buffer,
                SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_DIPEDGE, nullptr,
                    sizeof( _this_t ), requ_num_objects, requ_num_slots,
                        requ_num_dataptrs );
        }

        static SIXTRL_FN typename can_store_cobj_t< bool >::type
        CanStoreObjectOnBuffer(
            buffer_t const& SIXTRL_RESTRICT buffer,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_objects = nullptr,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_slots = nullptr,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_dataptrs = nullptr )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            using _this_t = st::DipoleEdgeInterface< BeObjData >;
            return _this_t::CanStoreObjectOnBuffer( buffer.getCApiPtr(),
                requ_num_objects, requ_num_slots, requ_num_dataptrs );
        }

        static SIXTRL_FN
        typename can_store_cobj_t< DipoleEdgeInterface< BeObjData >* >::type
        CreateNewObject( buffer_t& SIXTRL_RESTRICT buffer )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            using _this_t = st::DipoleEdgeInterface< BeObjData >;
            return _this_t::CreateNewObject( buffer.getCApiPtr() );
        }

        template< typename... Args >
        static SIXTRL_FN
        typename can_store_cobj_t< DipoleEdgeInterface< BeObjData >* >::type
        AddObject( c_buffer_t* SIXTRL_RESTRICT buffer, Args&&... args )
        {
            namespace  st = SIXTRL_CXX_NAMESPACE;
            using _this_t = st::DipoleEdgeInterface< BeObjData >;
            _this_t temp( std::forward< Args >( args )... );

            return SIXTRL_CXX_NAMESPACE::ObjStore_get_ptr_obj_from_info< _this_t >(
                SIXTRL_CXX_NAMESPACE::Obj_store_on_buffer( buffer,
                SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_DIPEDGE, temp.ptrBeData() ),
                SIXTRL_CXX_NAMESPACE::ObjDataStoreTraits< BeObjData >::ObjTypeId() );
        }

        template< typename... Args >
        static SIXTRL_FN
        typename can_store_cobj_t< DipoleEdgeInterface< BeObjData >* >::type
        AddObject( buffer_t& SIXTRL_RESTRICT_REF buffer, Args&&... args )
        {
            namespace  st = SIXTRL_CXX_NAMESPACE;
            using _this_t = st::DipoleEdgeInterface< BeObjData >;
            _this_t temp( std::forward< Args >( args )... );

            return SIXTRL_CXX_NAMESPACE::ObjStore_get_ptr_obj_from_info< _this_t >(
                SIXTRL_CXX_NAMESPACE::Obj_store_on_buffer( buffer.getCApiPtr(),
                SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_DIPEDGE, temp.ptrBeData() ),
                SIXTRL_CXX_NAMESPACE::ObjDataStoreTraits< BeObjData >::ObjTypeId() );
        }

        SIXTRL_FN
        typename can_store_cobj_t< DipoleEdgeInterface< BeObjData >* >::type
        storeCopy( c_buffer_t* SIXTRL_RESTRICT buffer )
        {
            using _this_t = SIXTRL_CXX_NAMESPACE::DipoleEdgeInterface< BeObjData >;
            return SIXTRL_CXX_NAMESPACE::ObjStore_get_ptr_obj_from_info< _this_t >(
                SIXTRL_CXX_NAMESPACE::Obj_store_on_buffer( buffer,
                SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_DIPEDGE, this->ptrBeData() ),
                SIXTRL_CXX_NAMESPACE::ObjDataStoreTraits< BeObjData >::ObjTypeId() );
        }

        SIXTRL_FN
        typename can_store_cobj_t< DipoleEdgeInterface< BeObjData >* >::type
        storeCopy( buffer_t& SIXTRL_RESTRICT_REF buffer )
        {
            return this->storeCopy( buffer.getCApiPtr() );
        }

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        static SIXTRL_FN
        typename can_store_cobj_t< DipoleEdgeInterface< BeObjData > const* >::type
        GetConstObj( const c_buffer_t *const SIXTRL_RESTRICT buffer,
                ::NS(buffer_size_t) const index )
        {
            using _this_t = SIXTRL_CXX_NAMESPACE::DipoleEdgeInterface< BeObjData >;
            return ObjStore_get_ptr_const_obj_from_info< _this_t >(
                ::NS(Buffer_get_const_object)( buffer, index ),
                SIXTRL_CXX_NAMESPACE::ObjDataStoreTraits< BeObjData >::ObjTypeId() );
        }

        static SIXTRL_FN
        typename can_store_cobj_t< DipoleEdgeInterface< BeObjData >* >::type
        GetObj( c_buffer_t* SIXTRL_RESTRICT buffer,
                ::NS(buffer_size_t) const index )
        {
            using _this_t = SIXTRL_CXX_NAMESPACE::DipoleEdgeInterface< BeObjData >;
            return ObjStore_get_ptr_obj_from_info< _this_t >(
                ::NS(Buffer_get_object)( buffer, index ),
                SIXTRL_CXX_NAMESPACE::ObjDataStoreTraits< BeObjData >::ObjTypeId() );
        }

        static SIXTRL_FN
        typename can_store_cobj_t< DipoleEdgeInterface< BeObjData > const* >::type
        GetConstObj( buffer_t const& SIXTRL_RESTRICT_REF buffer,
                ::NS(buffer_size_t) const index )
        {
            using _this_t = SIXTRL_CXX_NAMESPACE::DipoleEdgeInterface< BeObjData >;
            return _this_t::GetConstObj( buffer.getCApiPtr(), index );
        }

        static SIXTRL_FN
        typename can_store_cobj_t< DipoleEdgeInterface< BeObjData >* >::type
        GetObj( buffer_t& SIXTRL_RESTRICT buffer,
                ::NS(buffer_size_t) const index )
        {
            using _this_t = SIXTRL_CXX_NAMESPACE::DipoleEdgeInterface< BeObjData >;
            return _this_t::GetObj( buffer.getCApiPtr(), index );
        }
    };

    typedef DipoleEdgeInterface< ::NS(DipoleEdge) > CDipoleEdge;
    typedef DipoleEdgeInterface< DipoleEdgeData< double > > DipoleEdge;

    template< class R, std::size_t RAlign =
        SIXTRL_CXX_NAMESPACE::TypeStoreTraits< R >::StorageAlign() >
    using TDipoleEdge = DipoleEdgeInterface< DipoleEdgeData< R, RAlign > >;
}

#endif /* SIXTRACKLIB_COMMON_BE_DIPOLE_EDGE_BE_DIPOLE_EDGE_CXX_HPP__ */
/* end: */
