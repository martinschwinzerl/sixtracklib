#ifndef SIXTRACKLIB_COMMON_BE_MULTIPOLE_BE_MULTIPOLE_CXX_HPP__
#define SIXTRACKLIB_COMMON_BE_MULTIPOLE_BE_MULTIPOLE_CXX_HPP__

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/beam_elements/multipole/definitions.h"

#include "sixtracklib/common/beam_elements/beam_elements_base.hpp"
#include "sixtracklib/common/beam_elements/multipole/multipole_traits.hpp"
#include "sixtracklib/common/beam_elements/multipole/multipole_data.hpp"
#include "sixtracklib/common/beam_elements/multipole/multipole.h"
#include "sixtracklib/common/buffer.hpp"

namespace SIXTRL_CXX_NAMESPACE
{
    template< class BeObjData >
    class MultipoleInterface : public SIXTRL_CXX_NAMESPACE::BeamElementBase<
        BeObjData, ::NS(Multipole) >
    {
        public:

        typedef SIXTRL_CXX_NAMESPACE::BeamElementBase<
            BeObjData, ::NS(Multipole) > _base_t;

        typedef typename _base_t::c_api_t c_api_t;
        typedef SIXTRL_CXX_NAMESPACE::Buffer buffer_t;
        typedef buffer_t::c_api_t c_buffer_t;

        template< typename T > using can_store_cobj_t =
            std::enable_if< _base_t::SupportsCObjectsStorage(), T >;

        typedef SIXTRL_CXX_NAMESPACE::MultipoleTraits< BeObjData > be_traits_t;
        typedef typename be_traits_t::real_t        real_t;
        typedef typename be_traits_t::order_t       order_t;
        typedef typename be_traits_t::bal_addr_t    bal_addr_t;

        static_assert( SIXTRL_CXX_NAMESPACE::ObjData_get_num_data_ptrs<
            BeObjData >() == ::NS(buffer_size_t){ 1 },
            "Multipole* implementations are required to have one dataptr" );

        static_assert( SIXTRL_CXX_NAMESPACE::ObjData_dataptr_type_count_can_vary<
            BeObjData >(), "Multipole* implementations are expected to "
            "have a storage size dependent on the order parameter" );

        /* ----------------------------------------------------------------- */

        SIXTRL_FN MultipoleInterface()
        {
            this->init();
        }

        SIXTRL_FN explicit MultipoleInterface(
            const c_api_t *const SIXTRL_RESTRICT mp )
        {
            if( mp != nullptr ) this->init( mp );
            else this->init();
        }

        SIXTRL_FN explicit MultipoleInterface( order_t const _order,
            real_t* SIXTRL_RESTRICT _ptr_to_ext_bal = nullptr )
        {
            this->init( _order, _ptr_to_ext_bal );
        }

        SIXTRL_FN MultipoleInterface( order_t const _order,
            real_t const& SIXTRL_RESTRICT_REF _length,
            real_t const& SIXTRL_RESTRICT_REF _hxl,
            real_t const& SIXTRL_RESTRICT_REF _hyl,
            real_t* SIXTRL_RESTRICT _ptr_to_ext_bal = nullptr )
        {
            this->init( _order, _length, _hxl, _hyl, _ptr_to_ext_bal );
        }

        SIXTRL_FN MultipoleInterface(
            MultipoleInterface< BeObjData > const& other) = default;

        SIXTRL_FN MultipoleInterface(
            MultipoleInterface< BeObjData >&& other ) = default;

        SIXTRL_FN MultipoleInterface< BeObjData >& operator=(
            MultipoleInterface< BeObjData > const& other) = default;

        SIXTRL_FN MultipoleInterface< BeObjData >& operator=(
            MultipoleInterface< BeObjData >&& other ) = default;

        SIXTRL_FN ~MultipoleInterface() = default;

        SIXTRL_FN void init()
        {
            this->order    = order_t{ 0 };
            this->length   = real_t{ 0.0 };
            this->hxl      = real_t{ 0.0 };
            this->hyl      = real_t{ 0.0 };
            this->bal_addr = bal_addr_t{ 0 };
        }

        SIXTRL_FN void init( const c_api_t *const SIXTRL_RESTRICT mp )
        {
            if( ( mp != nullptr ) && ( this->bal == nullptr ) &&
                ( this->order != order_t{ 0 } ) )
            {
                this->order    = mp->order;
                this->length   = real_t( mp->length );
                this->hxl      = real_t( mp->hxl );
                this->hyl      = real_t( mp->hyl );
                this->bal_addr = bal_addr_t{ 0 };
            }
        }

        SIXTRL_FN void init( order_t const _order,
            real_t* SIXTRL_RESTRICT _ptr_to_ext_bal = nullptr )
        {
            if( ( this->order == order_t{ 0 } ) && ( this->bal == nullptr ) )
            {
                this->order    = _order;
                this->length   = real_t{ 0.0 };
                this->hxl      = real_t{ 0.0 };
                this->hyl      = real_t{ 0.0 };
                this->bal_addr = static_cast< bal_addr_t >( reinterpret_cast<
                    uintptr_t >( _ptr_to_ext_bal ) );
            }
        }

        SIXTRL_FN void init( order_t const _order,
            real_t const& SIXTRL_RESTRICT_REF _length,
            real_t const& SIXTRL_RESTRICT_REF _hxl,
            real_t const& SIXTRL_RESTRICT_REF _hyl,
            real_t* SIXTRL_RESTRICT _ptr_to_ext_bal = nullptr )
        {
            if( ( this->order == order_t{ 0 } ) && ( this->bal == nullptr ) )
            {
                this->order    = _order;
                this->length   = _length;
                this->hxl      = _hxl;
                this->hyl      = _hyl;
                this->bal_addr = static_cast< bal_addr_t >( reinterpret_cast<
                    uintptr_t >( _ptr_to_ext_bal ) );
            }
        }

        /* ----------------------------------------------------------------- */

        template< typename Iter >
        SIXTRL_FN ::NS(arch_status_t) copyBalValues(
            order_t const other_order, Iter other_begin )
        {
            ::NS(arch_status_t) status = ::NS(ARCH_STATUS_GENERAL_FAILURE);

            if( ( this->order == other_order ) &&
                ( this->bal != nullptr ) )
            {
                real_t* out_it = this->bal;

                Iter in_it  = other_begin;
                Iter in_end = other_begin;
                std::advance( in_end, this->getNumBalParameters() );

                status = ::NS(ARCH_STATUS_SUCCESS);

                for( ; in_it != in_end ; ++in_it, ++out_it )
                {
                    *out_it = real_t( *in_it );
                }
            }

            return status;
        }

        /* ----------------------------------------------------------------- */

        SIXTRL_FN real_t const& operator[](
            order_t const index ) const SIXTRL_NOEXCEPT
        {
            return this->getConstBal( index );
        }

        SIXTRL_FN real_t& operator[]( order_t const index ) SIXTRL_NOEXCEPT
        {
            return this->getBal( index );
        }

        SIXTRL_FN real_t const& getConstBal(
            order_t const index ) const SIXTRL_NOEXCEPT
        {
            typedef SIXTRL_BE_DATAPTR_DEC real_t const* ptr_t;
            ptr_t ptr = reinterpret_cast< ptr_t >( static_cast< uintptr_t >(
                this->bal_addr ) );

            SIXTRL_ASSERT( ptr != nullptr );
            SIXTRL_ASSERT( this->getNumBalParameters() > index );

            return ptr[ index ];
        }

        SIXTRL_FN real_t& getBal( order_t const index ) SIXTRL_NOEXCEPT
        {
            typedef SIXTRL_BE_DATAPTR_DEC real_t* ptr_t;
            ptr_t ptr = reinterpret_cast< ptr_t >( static_cast< uintptr_t >(
                this->bal_addr ) );

            SIXTRL_ASSERT( ptr != nullptr );
            SIXTRL_ASSERT( this->getNumBalParameters() > index );

            return ptr[ index ];
        }

        SIXTRL_FN order_t getOrder() const SIXTRL_NOEXCEPT
        { return this->order; }

        SIXTRL_FN order_t getNumBalParameters() const SIXTRL_NOEXCEPT
        {
            return order_t{ 2 } * ( this->order + order_t{ 1 } );
        }

        /* ----------------------------------------------------------------- */

        static SIXTRL_FN typename can_store_cobj_t< bool >::type
        CanStoreObjectOnBuffer( const c_buffer_t *const SIXTRL_RESTRICT buffer,
            order_t const order,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_objects = nullptr,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_slots = nullptr,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_dataptrs = nullptr )
        {
            namespace  st = SIXTRL_CXX_NAMESPACE;
            using _this_t = SIXTRL_CXX_NAMESPACE::MultipoleInterface< BeObjData >;
            _this_t temp( order, nullptr );

            return SIXTRL_CXX_NAMESPACE::Obj_can_store_on_buffer< BeObjData >( buffer,
                st::OBJECT_TYPE_MULTIPOLE, temp.ptrBeData(), sizeof( _this_t ),
                    requ_num_objects, requ_num_slots, requ_num_dataptrs );
        }

        static SIXTRL_FN typename can_store_cobj_t< bool >::type
        CanStoreObjectOnBuffer( buffer_t const& SIXTRL_RESTRICT_REF buffer,
            order_t const order,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_objects = nullptr,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_slots = nullptr,
            ::NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_dataptrs = nullptr )
        {
            return SIXTRL_CXX_NAMESPACE::MultipoleInterface<
                BeObjData >::CanStoreObjectOnBuffer(
                    buffer.getCApiPtr(), order );
        }

        static SIXTRL_FN typename can_store_cobj_t< MultipoleInterface<
            BeObjData >* >::type CreateNewObject(
                c_buffer_t* SIXTRL_RESTRICT buffer, order_t const order )
        {
            namespace  st = SIXTRL_CXX_NAMESPACE;
            using _this_t = SIXTRL_CXX_NAMESPACE::MultipoleInterface< BeObjData >;
            _this_t temp( order, nullptr );

            return SIXTRL_CXX_NAMESPACE::ObjStore_get_ptr_obj_from_info< _this_t >(
                SIXTRL_CXX_NAMESPACE::Obj_store_on_buffer( buffer,
                    st::OBJECT_TYPE_MULTIPOLE, temp.ptrBeData() ),
                SIXTRL_CXX_NAMESPACE::ObjDataStoreTraits< BeObjData >::ObjTypeId() );
        }

        static SIXTRL_FN typename can_store_cobj_t< MultipoleInterface<
            BeObjData >* >::type CreateNewObject(
                buffer_t& SIXTRL_RESTRICT_REF buffer, order_t const order )
        {
            return SIXTRL_CXX_NAMESPACE::MultipoleInterface<
                BeObjData >::CreateNewObject( buffer.getCApiPtr(), order );
        }

        template< typename... Args > static SIXTRL_FN
        typename can_store_cobj_t< MultipoleInterface< BeObjData >* >::type
        AddObject( c_buffer_t* SIXTRL_RESTRICT buffer, Args&&... args )
        {
            namespace  st = SIXTRL_CXX_NAMESPACE;
            using _this_t = SIXTRL_CXX_NAMESPACE::MultipoleInterface< BeObjData >;
            _this_t temp( std::forward< Args >( args )... );

            return SIXTRL_CXX_NAMESPACE::ObjStore_get_ptr_obj_from_info< _this_t >(
                SIXTRL_CXX_NAMESPACE::Obj_store_on_buffer( buffer,
                    st::OBJECT_TYPE_MULTIPOLE, temp.ptrBeData() ),
                SIXTRL_CXX_NAMESPACE::ObjDataStoreTraits< BeObjData >::ObjTypeId() );
        }

        template< typename... Args > static SIXTRL_FN
        typename can_store_cobj_t< MultipoleInterface< BeObjData >* >::type
        AddObject( buffer_t& SIXTRL_RESTRICT_REF buffer, Args&&... args )
        {
            return SIXTRL_CXX_NAMESPACE::MultipoleInterface<
                BeObjData >::AddObject( buffer.getCApiPtr(),
                    std::forward< Args >( args )... );
        }

        SIXTRL_FN typename can_store_cobj_t< MultipoleInterface< BeObjData
            >* >::type storeCopy( c_buffer_t* SIXTRL_RESTRICT buffer )
        {
            namespace  st = SIXTRL_CXX_NAMESPACE;
            using _this_t = SIXTRL_CXX_NAMESPACE::MultipoleInterface< BeObjData >;

            return SIXTRL_CXX_NAMESPACE::ObjStore_get_ptr_obj_from_info< _this_t >(
                SIXTRL_CXX_NAMESPACE::Obj_store_on_buffer( buffer,
                    st::OBJECT_TYPE_MULTIPOLE, this->ptrBeData() ),
                SIXTRL_CXX_NAMESPACE::ObjDataStoreTraits< BeObjData >::ObjTypeId() );
        }

        SIXTRL_FN typename can_store_cobj_t< MultipoleInterface< BeObjData
            >* >::type storeCopy( buffer_t& SIXTRL_RESTRICT_REF buffer )
        {
            return this->storeCopy( buffer.getCApiPtr() );
        }

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        static SIXTRL_FN typename can_store_cobj_t< MultipoleInterface<
            BeObjData > const* >::type
        GetConstObj( const c_buffer_t *const SIXTRL_RESTRICT buffer,
                ::NS(buffer_size_t) const index )
        {
            using _this_t = SIXTRL_CXX_NAMESPACE::MultipoleInterface< BeObjData >;
            return ObjStore_get_ptr_const_obj_from_info< _this_t >(
                ::NS(Buffer_get_const_object)( buffer, index ),
                SIXTRL_CXX_NAMESPACE::ObjDataStoreTraits< BeObjData >::ObjTypeId() );
        }

        static SIXTRL_FN
        typename can_store_cobj_t< MultipoleInterface< BeObjData >* >::type
        GetObj( c_buffer_t* SIXTRL_RESTRICT buffer,
                ::NS(buffer_size_t) const index )
        {
            using _this_t = SIXTRL_CXX_NAMESPACE::MultipoleInterface< BeObjData >;
            return ObjStore_get_ptr_obj_from_info< _this_t >(
                ::NS(Buffer_get_object)( buffer, index ),
                SIXTRL_CXX_NAMESPACE::ObjDataStoreTraits< BeObjData >::ObjTypeId() );
        }

        static SIXTRL_FN typename can_store_cobj_t< MultipoleInterface<
            BeObjData > const* >::type GetConstObj(
                buffer_t const& SIXTRL_RESTRICT_REF buffer,
                ::NS(buffer_size_t) const index )
        {
            return SIXTRL_CXX_NAMESPACE::MultipoleInterface<
                BeObjData >::GetConstObj( buffer.getCApiPtr(), index );
        }

        static SIXTRL_FN
        typename can_store_cobj_t< MultipoleInterface< BeObjData >* >::type
        GetObj( buffer_t& SIXTRL_RESTRICT buffer,
                ::NS(buffer_size_t) const index )
        {
            return SIXTRL_CXX_NAMESPACE::MultipoleInterface<
                BeObjData >::GetObj( buffer.getCApiPtr(), index );
        }
    };

    /* --------------------------------------------------------------------- */

    typedef MultipoleInterface< ::NS(Multipole) > CMultipole;
    typedef MultipoleInterface< MultipoleData< double, 8u, 8u > > Multipole;

    template< class R, std::size_t RAlign =
            SIXTRL_CXX_NAMESPACE::TypeStoreTraits< R >::StorageAlign(),
        std::size_t OAlign = SIXTRL_CXX_NAMESPACE::TypeStoreTraits<
            ::NS(be_multipole_order_t) >::StorageAlign() >
    using TMultipole = MultipoleInterface< MultipoleData< R, RAlign, OAlign > >;
}

#endif /* SIXTRACKLIB_COMMON_BE_MULTIPOLE_BE_MULTIPOLE_CXX_HPP__ */

/* end: sixtracklib/common/beam_elements/multipole/multipole.hpp */
