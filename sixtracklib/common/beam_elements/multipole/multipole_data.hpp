#ifndef SIXTRACKLIB_COMMON_BE_MULTIPOLE_BE_MULTIPOLE_DATA_CXX_HPP__
#define SIXTRACKLIB_COMMON_BE_MULTIPOLE_BE_MULTIPOLE_DATA_CXX_HPP__

#include <cstddef>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/beam_elements/definitions.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/beam_elements/multipole/definitions.h"
#include "sixtracklib/common/beam_elements/multipole/multipole_traits.hpp"
#include "sixtracklib/common/internal/obj_store_traits.hpp"
#include "sixtracklib/common/track/obj_track_traits.hpp"

namespace SIXTRL_CXX_NAMESPACE
{
    template< typename R, std::size_t RAlign =
            SIXTRL_CXX_NAMESPACE::TypeStoreTraits< R >::StorageAlign(),
        std::size_t OAlign = SIXTRL_CXX_NAMESPACE::TypeStoreTraits<
            ::NS(multipole_order_t) >::StorageAlign() >
    struct MultipoleData
    {
        typedef R real_t;
        typedef ::NS(multipole_order_t) order_t;
        typedef ::NS(be_multipole_address_t) bal_addr_t;

        static SIXTRL_FN constexpr std::size_t
        RealAlignment() { return RAlign; }

        static SIXTRL_FN constexpr std::size_t
        OrderAlignment() { return OAlign; }

        static SIXTRL_FN constexpr std::size_t
        BalParamAlignment()
        {
            return SIXTRL_CXX_NAMESPACE::TypeStoreTraits<
                bal_addr_t >::StorageAlign();
        }

        order_t    order    SIXTRL_ALIGN( OAlign );
        real_t     length   SIXTRL_ALIGN( RAlign );
        real_t     hxl      SIXTRL_ALIGN( RAlign );
        real_t     hyl      SIXTRL_ALIGN( RAlign );
        bal_addr_t bal_addr SIXTRL_ALIGN( ( MultipoleData<
            R, RAlign, OAlign >::BalParamAlignment() ) );
    };

    /* --------------------------------------------------------------------- */

    template< class R, std::size_t RAlign, std::size_t OAlign >
    typename SIXTRL_CXX_NAMESPACE::MultipoleData< R, RAlign, OAlign >::order_t
    MultipoleData_get_order( MultipoleData< R, RAlign, OAlign > const&
        SIXTRL_RESTRICT_REF mpdata ) SIXTRL_NOEXCEPT
    {
        return mpdata.order;
    }

    template< class R, std::size_t RAlign, std::size_t OAlign >
    SIXTRL_BE_DATAPTR_DEC typename SIXTRL_CXX_NAMESPACE::MultipoleData<
        R, RAlign, OAlign >::real_t const*
    MultipoleData_get_ptr_const_bal( MultipoleData< R, RAlign, OAlign > const&
        SIXTRL_RESTRICT_REF mpdata ) SIXTRL_NOEXCEPT
    {
        typedef SIXTRL_BE_DATAPTR_DEC
            typename SIXTRL_CXX_NAMESPACE::MultipoleData<
                R, RAlign, OAlign >::real_t const* ptr_t;

        return reinterpret_cast< ptr_t >( mpdata.bal_addr );
    }

    template< class R, std::size_t RAlign, std::size_t OAlign >
    SIXTRL_BE_DATAPTR_DEC typename SIXTRL_CXX_NAMESPACE::MultipoleData<
        R, RAlign, OAlign >::real_t* MultipoleData_get_ptr_const_bal(
        MultipoleData< R, RAlign, OAlign > const& SIXTRL_RESTRICT_REF
            mpdata ) SIXTRL_NOEXCEPT
    {
        typedef SIXTRL_BE_DATAPTR_DEC
            typename SIXTRL_CXX_NAMESPACE::MultipoleData<
                R, RAlign, OAlign >::real_t* ptr_t;

        return reinterpret_cast< ptr_t >( mpdata.bal_addr );
    }

    template< class R, std::size_t RAlign, std::size_t OAlign >
    typename SIXTRL_CXX_NAMESPACE::MultipoleData< R, RAlign, OAlign >::real_t
    MultipoleData_get_const_bal( MultipoleData< R, RAlign, OAlign > const&
        SIXTRL_RESTRICT_REF mpdata ) SIXTRL_NOEXCEPT
    {
        auto ptr = SIXTRL_CXX_NAMESPACE::MultipoleData_get_ptr_const_bal(
            mpdata );

        SIXTRL_ASSERT( ptr != nullptr );
        SIXTRL_ASSERT( mpdata->order > index );

        return ptr[ index ];

    }

    template< class R, std::size_t RAlign, std::size_t OAlign >
    typename SIXTRL_CXX_NAMESPACE::MultipoleData< R, RAlign, OAlign >::real_t&
    MultipoleData_get_bal( MultipoleData< R, RAlign, OAlign >&
        SIXTRL_RESTRICT_REF mpdata ) SIXTRL_NOEXCEPT
    {
        auto ptr = SIXTRL_CXX_NAMESPACE::MultipoleData_get_ptr_bal( mpdata );

        SIXTRL_ASSERT( ptr != nullptr );
        SIXTRL_ASSERT( mpdata->order > index );

        return ptr[ index ];

    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template<> struct ObjDataStoreTraits< SIXTRL_CXX_NAMESPACE::MultipoleData<
        double, 8u, 8u > >
    {
        static SIXTRL_FN constexpr
        SIXTRL_CXX_NAMESPACE::object_type_id_t ObjTypeId()
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_MULTIPOLE;
        }

        static SIXTRL_FN constexpr bool HasCApiLayout() { return true; }
    };

    template< class R, std::size_t RealAlign, std::size_t OrderAlign >
    struct ObjDataTrackTraits< SIXTRL_CXX_NAMESPACE::MultipoleData<
        R, RealAlign, OrderAlign > >
    {
        static SIXTRL_FN constexpr
        SIXTRL_CXX_NAMESPACE::object_type_id_t ObjTypeId()
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_MULTIPOLE;
        }
    };

    template< class R, std::size_t RAlign, std::size_t OAlign >
    struct ObjDataStoreLayoutTraits< SIXTRL_CXX_NAMESPACE::MultipoleData<
        R, RAlign, OAlign > >
    {
        typedef SIXTRL_CXX_NAMESPACE::MultipoleData<
                R, RAlign, OAlign > _obj_data_t;

        typedef SIXTRL_CXX_NAMESPACE::ObjDataStoreLayoutTraits< _obj_data_t >
                _obj_data_store_layout_traits_t;

        typedef ::NS(buffer_size_t) size_type;
        typedef ::NS(arch_status_t) status_t;

        typedef typename SIXTRL_CXX_NAMESPACE::MultipoleData<
            R, RAlign, OAlign >::real_t real_t;

        typedef typename SIXTRL_CXX_NAMESPACE::MultipoleData<
            R, RAlign, OAlign >::order_t order_t;

        static SIXTRL_FN constexpr size_type NumDataPtrs()
        {
            return size_type{ 1u };
        }

        static SIXTRL_FN constexpr bool VarNumDataPtrCounts() { return true; }

        static SIXTRL_FN status_t GetDataPtrTypeOffsets(
            size_type* SIXTRL_RESTRICT offsets_begin )
        {
            if( offsets_begin != nullptr )
            {
                *offsets_begin = offsetof( _obj_data_t, bal );
                return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
            }

            return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
        }

        static SIXTRL_FN status_t GetDataPtrTypeSizes(
            size_type* SIXTRL_RESTRICT sizes_begin )
        {
            if( sizes_begin != nullptr )
            {
                *sizes_begin = sizeof( typename _obj_data_t::real_t );
                return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS;
            }

            return SIXTRL_CXX_NAMESPACE::ARCH_STATUS_GENERAL_FAILURE;
        }

        static SIXTRL_FN status_t GetDataPtrTypeCounts(
            const _obj_data_t *const SIXTRL_RESTRICT mpdata,
            size_type* SIXTRL_RESTRICT counts )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

            if( counts != nullptr )
            {
                if( ( mpdata != nullptr ) && ( mpdata->order >= order_t{ 0 } ) )
                {
                    *counts = static_cast< size_type >( 2u ) * (
                        mpdata->order + order_t{ 1 } );
                }
                else
                {
                    *counts = size_type{ 0u };
                }

                status = st::ARCH_STATUS_SUCCESS;
            }

            return status;
        }
    };
}

#endif /* SIXTRACKLIB_COMMON_BE_MULTIPOLE_BE_MULTIPOLE_DATA_CXX_HPP__ */
/* end: /common/beam_elements/multipole/multipole_data.hpp */
