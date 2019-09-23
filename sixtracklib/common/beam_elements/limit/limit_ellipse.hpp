#ifndef SIXTRACKLIB_COMMON_BE_LIMIT_ELLIPSE_BE_LIMIT_ELLIPSE_CXX_HPP__
#define SIXTRACKLIB_COMMON_BE_LIMIT_ELLIPSE_BE_LIMIT_ELLIPSE_CXX_HPP__

#include "sixtracklib/sixtracklib.hpp"

#include "cxx/common/beam_elements/beam_elements_base.hpp"
#include "cxx/common/beam_elements/limit/limit_traits.hpp"
#include "cxx/common/beam_elements/limit/limit_ellipse_data.hpp"
#include "cxx/common/beam_elements/limit/limit_ellipse.h"

namespace SIXTRL_CXX_NAMESPACE
{
    template< class BeObjData > class LimitEllipseInterface :
        public SIXTRL_CXX_NAMESPACE::BeamElementBase<
                BeObjData, ::NS(LimitEllipse) >
    {
        public:

        typedef SIXTRL_CXX_NAMESPACE::BeamElementBase<
            BeObjData, ::NS(LimitEllipse) > _base_t;

        typedef typename _base_t::c_api_t       c_api_t;
        typedef SIXTRL_CXX_NAMESPACE::Buffer    buffer_t;
        typedef buffer_t::c_api_t               c_buffer_t;

        template< typename T > using can_store_cobj_t =
            std::enable_if< _base_t::SupportsCObjectsStorage(), T >;

        typedef SIXTRL_CXX_NAMESPACE::LimitEllipseTraits< BeObjData >
                be_traits_t;

        typedef typename be_traits_t::real_t real_t;

        static_assert( !SIXTRL_CXX_NAMESPACE::ObjData_has_data_ptrs<
            BeObjData >(), "LimitEllipse* implementations aren't "
            "supposed to have dataptrs" );

        /* ----------------------------------------------------------------- */

        SIXTRL_FN LimitEllipseInterface() { this->init(); }

        SIXTRL_FN explicit LimitEllipseInterface(
            const c_api_t *const SIXTRL_RESTRICT ell ) { this->init( ell ); }

        SIXTRL_FN LimitEllipseInterface(
            real_t const& SIXTRL_RESTRICT_REF a_squ,
            real_t const& SIXTRL_RESTRICT_REF b_squ )
        {
            this->init( a_squ, b_squ );
        }

        SIXTRL_FN LimitEllipseInterface(
            LimitEllipseInterface< BeObjData > const& other) = default;

        SIXTRL_FN LimitEllipseInterface(
            LimitEllipseInterface< BeObjData >&& other ) = default;

        SIXTRL_FN LimitEllipseInterface< BeObjData >& operator=(
            LimitEllipseInterface< BeObjData > const& other) = default;

        SIXTRL_FN LimitEllipseInterface< BeObjData >& operator=(
            LimitEllipseInterface< BeObjData >&& other ) = default;

        SIXTRL_FN ~LimitEllipseInterface() = default;

        SIXTRL_FN void init()
        {
            this->a_squ   = real_t{ 1.0 };
            this->b_squ   = real_t{ 1.0 };
            this->a_b_squ = real_t{ 1.0 };
        }

        SIXTRL_FN void init( const c_api_t *const SIXTRL_RESTRICT ell )
        {
            if( ell != nullptr )
            {
                this->init( real_t( ell->a_squ ), real_t( ell->b_squ ) );
            }
            else this->init();
        }

        SIXTRL_FN void init( real_t const& SIXTRL_RESTRICT_REF a_squ,
            real_t const& SIXTRL_RESTRICT_REF b_squ )
        {
            this->a_squ   = a_squ;
            this->b_squ   = b_squ;
            this->a_b_squ = a_squ * b_squ;
        }

        /* ----------------------------------------------------------------- */

        static SIXTRL_FN typename can_store_cobj_t< bool >::type
        CanStoreObjectOnBuffer( const c_buffer_t *const SIXTRL_RESTRICT buffer,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_objects = nullptr,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_slots = nullptr,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_dataptrs = nullptr )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            typedef st::LimitEllipseInterface< BeObjData > _this_t;
            return st::Obj_can_store_on_buffer< BeObjData >( buffer,
                SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_LIMIT_ELLIPSE, nullptr,
                    sizeof( _this_t ), requ_num_objects, requ_num_slots,
                        requ_num_dataptrs );
        }

        static SIXTRL_FN typename can_store_cobj_t< bool >::type
        CanStoreObjectOnBuffer(
            buffer_t const& SIXTRL_RESTRICT_REF buffer,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_objects = nullptr,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_slots = nullptr,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_dataptrs = nullptr )
        {
            return SIXTRL_CXX_NAMESPACE::LimitEllipseInterface<
                BeObjData >::CanStoreObjectOnBuffer( buffer.getCApiPtr(),
                    requ_num_objects, requ_num_slots, requ_num_dataptrs );
        }

        static SIXTRL_FN
        typename can_store_cobj_t< LimitEllipseInterface< BeObjData >* >::type
        CreateNewObject( c_buffer_t* SIXTRL_RESTRICT buffer )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            using _this_t = st::LimitEllipseInterface< BeObjData >;
            _this_t temp;

            return st::ObjStore_get_ptr_obj_from_info< _this_t >(
                st::Obj_store_on_buffer( buffer,
                    st::OBJECT_TYPE_LIMIT_ELLIPSE, temp.ptrBeData() ),
                st::ObjDataStoreTraits< BeObjData >::ObjTypeId() );
        }

        static SIXTRL_FN
        typename can_store_cobj_t< LimitEllipseInterface< BeObjData >* >::type
        CreateNewObject( buffer_t& SIXTRL_RESTRICT_REF buffer )
        {
            return SIXTRL_CXX_NAMESPACE::LimitEllipseInterface<
                BeObjData >::CreateNewObject( buffer.getCApiPtr() );
        }

        template< typename... Args > static SIXTRL_FN
        typename can_store_cobj_t< LimitEllipseInterface< BeObjData >* >::type
        AddObject( c_buffer_t* SIXTRL_RESTRICT buffer, Args&&... args )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            using _this_t = st::LimitEllipseInterface< BeObjData >;
            _this_t temp( std::forward< Args >( args )... );

            return st::ObjStore_get_ptr_obj_from_info< _this_t >(
                st::Obj_store_on_buffer( buffer,
                    st::OBJECT_TYPE_LIMIT_ELLIPSE, temp.ptrBeData() ),
                st::ObjDataStoreTraits< BeObjData >::ObjTypeId() );
        }

        template< typename... Args > static SIXTRL_FN
        typename can_store_cobj_t< LimitEllipseInterface< BeObjData >* >::type
        AddObject( buffer_t& SIXTRL_RESTRICT_REF buffer, Args&&... args )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            using _this_t = st::LimitEllipseInterface< BeObjData >;
            _this_t temp( std::forward< Args >( args )... );

            return st::ObjStore_get_ptr_obj_from_info< _this_t >(
                st::Obj_store_on_buffer( buffer.getCApiPtr(),
                    st::OBJECT_TYPE_LIMIT_ELLIPSE, temp.ptrBeData() ),
                st::ObjDataStoreTraits< BeObjData >::ObjTypeId() );
        }

        SIXTRL_FN typename can_store_cobj_t<
            LimitEllipseInterface< BeObjData >* >::type
        storeCopy( c_buffer_t* SIXTRL_RESTRICT buffer )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            using _this_t = st::LimitEllipseInterface< BeObjData >;
            return st::ObjStore_get_ptr_obj_from_info< _this_t >(
                st::Obj_store_on_buffer( buffer,
                    st::OBJECT_TYPE_LIMIT_ELLIPSE, this->ptrBeData() ),
                st::ObjDataStoreTraits< BeObjData >::ObjTypeId() );
        }

        SIXTRL_FN typename can_store_cobj_t<
            LimitEllipseInterface< BeObjData >* >::type
        storeCopy( buffer_t& SIXTRL_RESTRICT_REF buffer )
        {
            return this->storeCopy( buffer.getCApiPtr() );
        }

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        static SIXTRL_FN typename can_store_cobj_t< LimitEllipseInterface<
            BeObjData > const* >::type
        GetConstObj( const c_buffer_t *const SIXTRL_RESTRICT buffer,
                ::NS(buffer_size_t) const index )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            using _this_t = st::LimitEllipseInterface< BeObjData >;
            return ObjStore_get_ptr_const_obj_from_info< _this_t >(
                ::NS(Buffer_get_const_object)( buffer, index ),
                st::ObjDataStoreTraits< BeObjData >::ObjTypeId() );
        }

        static SIXTRL_FN
        typename can_store_cobj_t< LimitEllipseInterface< BeObjData >* >::type
        GetObj( c_buffer_t* SIXTRL_RESTRICT buffer,
                ::NS(buffer_size_t) const index )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            using _this_t = st::LimitEllipseInterface< BeObjData >;
            return ObjStore_get_ptr_obj_from_info< _this_t >(
                ::NS(Buffer_get_object)( buffer, index ),
                st::ObjDataStoreTraits< BeObjData >::ObjTypeId() );
        }

        static SIXTRL_FN typename can_store_cobj_t< LimitEllipseInterface<
            BeObjData > const* >::type
        GetConstObj( const buffer_t const& SIXTRL_RESTRICT_REF buffer,
                ::NS(buffer_size_t) const index )
        {
            return SIXTRL_CXX_NAMESPACE::LimitEllipseInterface<
                BeObjData >::GetConstObj( buffer.getCApiPtr(), index );
        }

        static SIXTRL_FN
        typename can_store_cobj_t< LimitEllipseInterface< BeObjData >* >::type
        GetObj( buffer_t& SIXTRL_RESTRICT_REF buffer,
                ::NS(buffer_size_t) const index )
        {
            return SIXTRL_CXX_NAMESPACE::LimitEllipseInterface<
                BeObjData >::GetObj( buffer.getCApiPtr(), index );
        }
    };

    typedef LimitEllipseInterface< ::NS(LimitEllipse) > CLimitEllipse;
    typedef LimitEllipseInterface<
        LimitEllipseData< double > > LimitEllipse;

    template< class R, std::size_t RAlign = st::TypeStoreTraits<
        R >::StorageAlign() >

    using TLimitEllipse = LimitEllipseInterface<
        LimitEllipseData< R, RAlign > >;
}

#endif /* SIXTRACKLIB_COMMON_BE_LIMIT_ELLIPSE_BE_LIMIT_ELLIPSE_CXX_HPP__ */

/* end: sixtracklib/common/beam_elements/limit/limit_ellipse.hpp */
