#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_MULTIPOLE_C99_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_MULTIPOLE_C99_H__

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/internal/objects_type_id.h"

#if defined( __cplusplus )

#include "cxx/common/be/multipole/definitions.h"
#include "cxx/common/be/multipole/be_multipole_traits.hpp"
#include "cxx/common/internal/obj_store_traits.hpp"
#include "cxx/common/track/obj_track_traits.hpp"

extern "C" {
#endif /* defined( __cplusplus ) */

typedef struct NS(Multipole)
{
    NS(be_multipole_order_t)    order       SIXTRL_ALIGN( 8 );
    NS(be_multipole_real_t)     length      SIXTRL_ALIGN( 8 );
    NS(be_multipole_real_t)     hxl         SIXTRL_ALIGN( 8 );
    NS(be_multipole_real_t)     hyl         SIXTRL_ALIGN( 8 );
    NS(be_multipole_address_t)  bal_addr    SIXTRL_ALIGN( 8 );
}
NS(Multipole);

#if defined( __cplusplus )
}
#endif /* defined( __cplusplus ) */

#include "sixtracklib/common/beam_elements/multipole/multipole_api.h"

/* ------------------------------------------------------------------------- */

#if defined( __cplusplus )

namespace SIXTRL_CXX_NAMESPACE
{
    ::NS(be_multipole_order_t) MultipoleData_get_order(
        ::NS(Multipole) const& SIXTRL_RESTRICT_REF _mp ) SIXTRL_NOEXCEPT
    {
        return _mp.order;
    }

    SIXTRL_BE_DATAPTR_DEC ::NS(be_multipole_real_t) const*
    MultipoleData_get_ptr_const_bal(
        ::NS(Multipole) const& SIXTRL_RESTRICT_REF _mp ) SIXTRL_NOEXCEPT
    {
        typedef SIXTRL_BE_DATAPTR_DEC ::NS(be_multipole_real_t) const* ptr_t;
        return reinterpret_cast< ptr_t >( _mp.bal_addr );
    }

    SIXTRL_BE_DATAPTR_DEC ::NS(be_multipole_real_t)* MultipoleData_get_ptr_bal(
        ::NS(Multipole)& SIXTRL_RESTRICT_REF _mp ) SIXTRL_NOEXCEPT
    {
        typedef SIXTRL_BE_DATAPTR_DEC ::NS(be_multipole_real_t)* ptr_t;
        return reinterpret_cast< ptr_t >( _mp.bal_addr );
    }

    ::NS(be_multipole_real_t) MultipoleData_get_const_bal(
        ::NS(Multipole) const& SIXTRL_RESTRICT_REF _mp,
        ::NS(be_multipole_order_t) const order_index ) SIXTRL_NOEXCEPT
    {
        typedef SIXTRL_BE_DATAPTR_DEC ::NS(be_multipole_real_t) const* ptr_t;
        ptr_t bal = ::NS(MultipoleData_get_ptr_const_bal)( _mp );

        SIXTRL_ASSERT( bal != nullptr );
        SIXTRL_ASSERT( ::NS(MultipoleData_get_order)( _mp) > order_index );

        return bal[ order_index ];
    }

    ::NS(be_multipole_real_t)& MultipoleData_get_bal(
        ::NS(Multipole)& SIXTRL_RESTRICT_REF _mp,
        ::NS(be_multipole_order_t) const order_index ) SIXTRL_NOEXCEPT
    {
        typedef SIXTRL_BE_DATAPTR_DEC ::NS(be_multipole_real_t)* ptr_t;
        ptr_t bal = ::NS(MultipoleData_get_ptr_bal)( _mp );

        SIXTRL_ASSERT( bal != nullptr );
        SIXTRL_ASSERT( ::NS(MultipoleData_get_order)( _mp) > order_index );

        return bal[ order_index ];
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    template<> struct ObjDataStoreTraits< ::NS(Multipole) >
    {
        static SIXTRL_FN constexpr
        SIXTRL_CXX_NAMESPACE::object_type_id_t ObjTypeId()
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_MULTIPOLE;
        }

        static SIXTRL_FN constexpr bool HasCApiLayout() { return true; }
    };

    template<> struct ObjDataTrackTraits< ::NS(Multipole) >
    {
        static SIXTRL_FN constexpr
        SIXTRL_CXX_NAMESPACE::object_type_id_t ObjTypeId()
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_MULTIPOLE;
        }
    };

    template<> struct MultipoleTraits< ::NS(Multipole) >
    {
        typedef ::NS(be_multipole_real_t)       real_t;
        typedef ::NS(be_multipole_order_t)      order_t;
        typedef ::NS(be_multipole_address_t)    bal_addr_t;
    };

    template<> struct ObjDataStoreLayoutTraits< ::NS(Multipole) >
    {
        typedef ::NS(buffer_size_t) size_type;
        typedef ::NS(arch_status_t) status_t;
        typedef ::NS(be_multipole_order_t) order_t;
        typedef ::NS(be_multipole_real_t)  real_t;

        static SIXTRL_FN constexpr size_type NumDataPtrs() { return 1u; }
        static SIXTRL_FN constexpr bool VarNumDataPtrCounts() { return true; }

        static SIXTRL_FN status_t GetDataPtrTypeOffsets(
            size_type* SIXTRL_RESTRICT offsets_begin )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            typedef ::NS(Multipole) c_api_t;
            typedef st::ObjDataStoreLayoutTraits< c_api_t > _this_t;

            status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
            if( offsets_begin != nullptr )
            {
                *offsets_begin = offsetof( c_api_t, bal_addr );
                status = st::ARCH_STATUS_SUCCESS;
            }

            return status;
        }

        static SIXTRL_FN status_t GetDataPtrTypeSizes(
            size_type* SIXTRL_RESTRICT type_sizes )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            status_t status = st::ARCH_STATUS_GENERAL_FAILURE;
            if( type_sizes != nullptr )
            {
                *type_sizes = sizeof( real_t );
                status = st::ARCH_STATUS_SUCCESS;
            }

            return status;
        }

        static SIXTRL_FN status_t GetDataPtrTypeCounts(
            const ObjData *const mpdata, size_type* SIXTRL_RESTRICT counts )
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
                    *counts = size_type{ 0 };
                }

                status st::ARCH_STATUS_SUCCESS;
            }

            return status;
        }
    };
}

#endif /* c++ */

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_MULTIPOLE_C99_H__ */

/* end: sixtracklib/common/beam_elements/multipole/multipole.h */
