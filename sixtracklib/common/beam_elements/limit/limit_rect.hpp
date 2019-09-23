#ifndef SIXTRACKLIB_COMMON_BE_LIMIT_RECT_BE_LIMIT_RECT_CXX_HPP__
#define SIXTRACKLIB_COMMON_BE_LIMIT_RECT_BE_LIMIT_RECT_CXX_HPP__

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/buffer.hpp"
#include "sixtracklib/common/buffer.h"

#include "sixtracklib/common/beam_elements/beam_elements_base.hpp"
#include "sixtracklib/common/beam_elements/limit/limit_traits.hpp"
#include "sixtracklib/common/beam_elements/limit/limit_rect_data.hpp"
#include "sixtracklib/common/beam_elements/limit/limit_rect.h"

namespace SIXTRACK_CXX_NAMESPACE
{
    template< class BeObjData > class LimitRectInterface :
        public SIXTRACK_CXX_NAMESPACE::BeamElementBase<
                BeObjData, ::NS(LimitRect) >
    {
        public:

        typedef SIXTRACK_CXX_NAMESPACE::BeamElementBase<
            BeObjData, ::NS(LimitRect) > _base_t;

        typedef typename _base_t::c_api_t    c_api_t;
        typedef SIXTRL_CXX_NAMESPACE::Buffer buffer_t;
        typedef buffer_t::c_api_t            c_buffer_t;

        template< typename T > using can_store_cobj_t =
            std::enable_if< _base_t::SupportsCObjectsStorage(), T >;

        typedef SIXTRACK_CXX_NAMESPACE::LimitRectTraits< BeObjData >
                be_traits_t;

        typedef typename be_traits_t::real_t real_t;

        static_assert( !SIXTRACK_CXX_NAMESPACE::ObjData_has_data_ptrs< BeObjData >(),
            "LimitRect* implementations aren't supposed to have dataptrs" );

        /* ----------------------------------------------------------------- */

        SIXTRL_FN LimitRectInterface() { this->init(); }

        SIXTRL_FN explicit LimitRectInterface( const c_api_t *const
            SIXTRL_RESTRICT limit ) { this->init( limit ); }

        SIXTRL_FN LimitRectInterface(
            real_t const& SIXTRL_RESTRICT_REF min_coord,
            real_t const& SIXTRL_RESTRICT_REF max_coord )
        {
            this->init( min_coord, max_coord );
        }

        SIXTRL_FN LimitRectInterface(
            real_t const& SIXTRL_RESTRICT_REF min_x,
            real_t const& SIXTRL_RESTRICT_REF max_x,
            real_t const& SIXTRL_RESTRICT_REF min_y,
            real_t const& SIXTRL_RESTRICT_REF max_y )
        {
            this->init( min_x, max_x, min_y, max_y );
        }

        SIXTRL_FN LimitRectInterface(
            LimitRectInterface< BeObjData > const& other) = default;

        SIXTRL_FN LimitRectInterface(
            LimitRectInterface< BeObjData >&& other ) = default;

        SIXTRL_FN LimitRectInterface< BeObjData >& operator=(
            LimitRectInterface< BeObjData > const& other) = default;

        SIXTRL_FN LimitRectInterface< BeObjData >& operator=(
            LimitRectInterface< BeObjData >&& other ) = default;

        SIXTRL_FN ~LimitRectInterface() = default;

        SIXTRL_FN void init()
        {
            this->min_x = real_t{ -1.0 };  this->max_x = real_t{  1.0 };
            this->min_y = real_t{ -1.0 };  this->max_y = real_t{  1.0 };
        }

        SIXTRL_FN void init( const c_api_t *const SIXTRL_RESTRICT limit )
        {
            if( limit != nullptr )
            {
                this->min_x = real_t( limit->min_x );
                this->max_x = real_t( limit->max_x );
                this->min_y = real_t( limit->min_y );
                this->max_y = real_t( limit->max_y );
            }
            else this->init();
        }

        SIXTRL_FN void init( real_t const& SIXTRL_RESTRICT_REF min_coord,
            real_t const& SIXTRL_RESTRICT_REF max_coord )
        {
            this->min_x = min_coord;   this->max_x = max_coord;
            this->min_y = min_coord;   this->max_y = max_coord;
        }

        SIXTRL_FN void init( real_t const& SIXTRL_RESTRICT_REF min_x,
            real_t const& SIXTRL_RESTRICT_REF max_x,
            real_t const& SIXTRL_RESTRICT_REF min_y,
            real_t const& SIXTRL_RESTRICT_REF max_y )
        {
            this->min_x = min_x;   this->max_x = max_x;
            this->min_y = min_y;   this->max_y = max_y;
        }

        /* ----------------------------------------------------------------- */

        static SIXTRL_FN typename can_store_cobj_t< bool >::type
        CanStoreObjectOnBuffer( const c_buffer_t *const SIXTRL_RESTRICT buffer,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_objects = nullptr,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_slots = nullptr,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_dataptrs = nullptr )
        {
            typedef SIXTRACK_CXX_NAMESPACE::LimitRectInterface< BeObjData > _this_t;
            return SIXTRACK_CXX_NAMESPACE::Obj_can_store_on_buffer< BeObjData >( buffer,
                SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_LIMIT_RECT, sizeof( _this_t ),
                    requ_num_objects, requ_num_slots, requ_num_dataptrs );
        }

        static SIXTRL_FN typename can_store_cobj_t< bool >::type
        CanStoreObjectOnBuffer( buffer_t const& SIXTRL_RESTRICT_REF buffer,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_objects = nullptr,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_slots = nullptr,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_dataptrs = nullptr )
        {
            return SIXTRACK_CXX_NAMESPACE::LimitRectInterface<
                BeObjData >::CanStoreObjectOnBuffer( buffer.getCApiPtr(),
                    requ_num_objects, requ_num_objects, requ_num_dataptrs );
        }

        static SIXTRL_FN
        typename can_store_cobj_t< LimitRectInterface< BeObjData >* >::type
        CreateNewObject( c_buffer_t* SIXTRL_RESTRICT buffer )
        {
            using _this_t = SIXTRACK_CXX_NAMESPACE::LimitRectInterface< BeObjData >;
            _this_t temp;

            return SIXTRACK_CXX_NAMESPACE::ObjStore_get_ptr_obj_from_info< _this_t >(
                SIXTRACK_CXX_NAMESPACE::Obj_store_on_buffer( buffer,
                SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_LIMIT_RECT, temp.ptrBeData() ),
                SIXTRACK_CXX_NAMESPACE::ObjDataStoreTraits< BeObjData >::ObjTypeId() );
        }

        static SIXTRL_FN
        typename can_store_cobj_t< LimitRectInterface< BeObjData >* >::type
        CreateNewObject( buffer_t& SIXTRL_RESTRICT_REF buffer )
        {
            return SIXTRACK_CXX_NAMESPACE::LimitRectInterface<
                BeObjData >::CreateNewObject( buffer.getCApiPtr() );
        }

        template< typename... Args > static SIXTRL_FN
        typename can_store_cobj_t< LimitRectInterface< BeObjData >* >::type
        AddObject( c_buffer_t* SIXTRL_RESTRICT buffer, Args&&... args )
        {
            using _this_t = SIXTRACK_CXX_NAMESPACE::LimitRectInterface< BeObjData >;
            _this_t temp( std::forward< Args >( args )... );

            return SIXTRACK_CXX_NAMESPACE::ObjStore_get_ptr_obj_from_info< _this_t >(
                SIXTRACK_CXX_NAMESPACE::Obj_store_on_buffer( buffer,
                SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_LIMIT_RECT, temp.ptrBeData() ),
                SIXTRACK_CXX_NAMESPACE::ObjDataStoreTraits< BeObjData >::ObjTypeId() );
        }

        template< typename... Args > static SIXTRL_FN
        typename can_store_cobj_t< LimitRectInterface< BeObjData >* >::type
        AddObject( buffer_t& SIXTRL_RESTRICT_REF buffer, Args&&... args )
        {
            namespace  st = SIXTRACK_CXX_NAMESPACE;
            using _this_t = st::LimitRectInterface< BeObjData >;
            _this_t temp( std::forward< Args >( args )... );

            return st::ObjStore_get_ptr_obj_from_info< _this_t >(
                st::Obj_store_on_buffer( buffer.getCApiPtr(),
                st::OBJECT_TYPE_LIMIT_RECT, temp.ptrBeData() ),
                st::ObjDataStoreTraits< BeObjData >::ObjTypeId() );
        }

        SIXTRL_FN typename can_store_cobj_t< LimitRectInterface< BeObjData >* >::type
        storeCopy( c_buffer_t* SIXTRL_RESTRICT buffer )
        {
            using _this_t = SIXTRACK_CXX_NAMESPACE::LimitRectInterface< BeObjData >;
            return SIXTRACK_CXX_NAMESPACE::ObjStore_get_ptr_obj_from_info< _this_t >(
                SIXTRACK_CXX_NAMESPACE::Obj_store_on_buffer( buffer,
                SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_LIMIT_RECT, this->ptrBeData() ),
                SIXTRACK_CXX_NAMESPACE::ObjDataStoreTraits< BeObjData >::ObjTypeId() );
        }

        SIXTRL_FN typename can_store_cobj_t< LimitRectInterface< BeObjData >* >::type
        storeCopy( buffer_t& SIXTRL_RESTRICT_REF buffer )
        {
            return this->storeCopy( buffer.getCApiPtr() );
        }

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        static SIXTRL_FN
        typename can_store_cobj_t< LimitRectInterface< BeObjData > const* >::type
        GetConstObj( const c_buffer_t *const SIXTRL_RESTRICT buffer,
                ::NS(buffer_size_t) const index )
        {
            using _this_t = SIXTRACK_CXX_NAMESPACE::LimitRectInterface< BeObjData >;
            return ObjStore_get_ptr_const_obj_from_info< _this_t >(
                ::NS(Buffer_get_const_object)( buffer, index ),
                SIXTRACK_CXX_NAMESPACE::ObjDataStoreTraits< BeObjData >::ObjTypeId() );
        }

        static SIXTRL_FN
        typename can_store_cobj_t< LimitRectInterface< BeObjData >* >::type
        GetObj( c_buffer_t* SIXTRL_RESTRICT buffer,
                ::NS(buffer_size_t) const index )
        {
            using _this_t = SIXTRACK_CXX_NAMESPACE::LimitRectInterface< BeObjData >;
            return ObjStore_get_ptr_obj_from_info< _this_t >(
                ::NS(Buffer_get_object)( buffer, index ),
                SIXTRACK_CXX_NAMESPACE::ObjDataStoreTraits< BeObjData >::ObjTypeId() );
        }

        static SIXTRL_FN
        typename can_store_cobj_t< LimitRectInterface< BeObjData > const* >::type
        GetConstObj( buffer_t const& SIXTRL_RESTRICT_REF buffer,
                ::NS(buffer_size_t) const index )
        {
            return SIXTRACK_CXX_NAMESPACE::LimitRectInterface<
                BeObjData >::GetConstObj( buffer.getCApiPtr(), index );
        }

        static SIXTRL_FN
        typename can_store_cobj_t< LimitRectInterface< BeObjData >* >::type
        GetObj( buffer_t& SIXTRL_RESTRICT_REF buffer,
                ::NS(buffer_size_t) const index )
        {
            return SIXTRACK_CXX_NAMESPACE::LimitRectInterface<
                BeObjData >::GetObj( buffer.getCApiPtr(), index );
        }
    };

    typedef LimitRectInterface< ::NS(LimitRect) > CLimitRect;
    typedef LimitRectInterface< LimitRectData< double, 8u > > LimitRect;

    template< class R, std::size_t RAlign =
        SIXTRACK_CXX_NAMESPACE::TypeStoreTraits< R >::StorageAlign() >
    using TLimitRect = LimitRectInterface< LimitRectData< R, RAlign > >;
}

#endif /* SIXTRACKLIB_COMMON_BE_LIMIT_RECT_BE_LIMIT_RECT_CXX_HPP__ */

/* end: /common/beam_elements/limit/limit_rect.hpp */
