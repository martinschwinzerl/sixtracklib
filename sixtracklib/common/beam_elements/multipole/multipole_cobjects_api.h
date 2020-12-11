#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_MULTIPOLE_COBJECTS_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_MULTIPOLE_COBJECTS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/multipole/multipole.h"
    #include "sixtracklib/common/beam_elements/multipole/multipole.hpp"
    #include "sixtracklib/common/beam_elements/multipole/multipole_derived_api.h"
    #include "sixtracklib/common/beam_elements/multipole/multipole_init.h"
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/cobjects/index_object.h"
    #include "sixtracklib/common/cobjects/cbuffer_view.hpp"
    #include "sixtracklib/common/cobjects/flat_buffer.h"
    #include "sixtracklib/common/internal/objects_type_id.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template<> struct ObjTypeIdDataTypeMap<
        cobj_type_id_t, SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_MULTIPOLE >
    {
        typedef ::NS(Multipole) value_type;
    };

    template<> struct ObjDataTypeIdTraits< ::NS(Multipole), cobj_type_id_t >
    {
        static_assert( SIXTRL_CXX_NAMESPACE::ObjData_is_c_api_type<
            ::NS(Multipole) >(), "NS(Multipole) should be a C-API type" );

        static SIXTRL_FN constexpr cobj_type_id_t TypeId() SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_MULTIPOLE;
        }
    };

    template<> struct CObjElemNumPointers< ::NS(Multipole), void >
    {
        static constexpr cobj_size_t min_num_ptrs = cobj_size_t{ 1 };
        static constexpr cobj_size_t max_num_ptrs = cobj_size_t{ 1 };
    };

    template<> struct CObjElemFieldOffsets< ::NS(Multipole) >
     {
         static constexpr cobj_size_t offsets[ 1 ] =
         {
            offsetof( ::NS(Multipole), bal_addr )
         };
     };

    template<> struct CObjElemFieldSizes< ::NS(Multipole) >
    {
        static constexpr cobj_size_t sizes[ 1 ] =
        {
            sizeof( MultipoleTraits< ::NS(Multipole) >::real_t )
        };
    };

    template<> struct CObjElemFieldCounts< ::NS(Multipole) >
    {
        static SIXTRL_INLINE SIXTRL_FN cobj_status_t init_field_counts(
            SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT counts_begin,
            cobj_size_t const max_num_counts,
            SIXTRL_BUFFER_ARGPTR_DEC const ::NS(Multipole) *const
                SIXTRL_RESTRICT pset = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            typedef st::cobj_size_t st_size_t;

            st::cobj_status_t status = st::COBJECTS_STATUS_GENERAL_FAILURE;
            SIXTRL_ASSERT( st::CObjElem_num_ptrs< ::NS(Multipole) >( pset ) ==
                           st_size_t{ 1 } );

            if( ( pset != SIXTRL_NULLPTR ) &&
                ( max_num_counts >= st_size_t{ 1 } ) )
            {
                st_size_t ii = st_size_t{ 0 };
                counts_begin[ ii++ ] = st::Multipole_bal_capacity( pset );

                for(  ; ii < max_num_counts ; ++ii )
                {
                    counts_begin[ ii ] = st_size_t{ 0 };
                }

                status = st::COBJECTS_STATUS_SUCCESS;
            }

            return status;
        }
    };

    /* ********************************************************************* */

    template< class MultipoleT >
    SIXTRL_STATIC SIXTRL_FN constexpr cobj_type_id_t Multipole_type_id(
        SIXTRL_BE_ARGPTR_DEC const MultipoleT *const SIXTRL_RESTRICT
            /* p */ = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        static_assert(
            SIXTRL_CXX_NAMESPACE::Multipole_is_type< MultipoleT >(),
            "Requires MultipoleT to be a Multipole element" );

        return ObjDataTypeIdTraits< MultipoleT,
            SIXTRL_CXX_NAMESPACE::cobj_type_id_t >::TypeId();
    }

    template< class MultipoleT >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::Multipole_is_type< MultipoleT >(),
        cobj_size_t >::type
    Multipole_num_pointers( SIXTRL_BE_ARGPTR_DEC const MultipoleT *const
        SIXTRL_RESTRICT p = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_num_ptrs< MultipoleT >( p );
    }

    template< class MultipoleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN cobj_size_t
    Multipole_required_num_bytes( cobj_size_t const slot_size,
        SIXTRL_BE_ARGPTR_DEC const MultipoleT *const SIXTRL_RESTRICT
            p = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        static_assert(
            SIXTRL_CXX_NAMESPACE::Multipole_is_type< MultipoleT >(),
            "Requires MultipoleT to be a Multipole element" );

        return SIXTRL_CXX_NAMESPACE::CObjElem_required_num_bytes< MultipoleT >(
            slot_size, p );
    }

    template< class MultipoleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN cobj_size_t
    Multipole_required_num_slots( cobj_size_t const slot_size,
        SIXTRL_BE_ARGPTR_DEC const MultipoleT *const SIXTRL_RESTRICT
            p = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        static_assert(
            SIXTRL_CXX_NAMESPACE::Multipole_is_type< MultipoleT >(),
            "Requires MultipoleT to be a Multipole element" );

        return SIXTRL_CXX_NAMESPACE::CObjElem_required_num_slots< MultipoleT >(
            slot_size, p );
    }

    template< class MultipoleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
    SIXTRL_BE_ARGPTR_DEC MultipoleT const*
    Multipole_const_from_cobj_index( SIXTRL_BUFFER_OBJ_ARGPTR_DEC const
            ::NS(CObjIndex) *const SIXTRL_RESTRICT index_obj,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
    {
        static_assert(
            SIXTRL_CXX_NAMESPACE::Multipole_is_type< MultipoleT >(),
            "Requires MultipoleT to be a Multipole element" );

        return SIXTRL_CXX_NAMESPACE::CObjElem_const_from_cobj_index<
            MultipoleT >( index_obj, slot_size );
    }

    template< class MultipoleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
    SIXTRL_BE_ARGPTR_DEC MultipoleT*
    Multipole_from_cobj_index( SIXTRL_BUFFER_OBJ_ARGPTR_DEC ::NS(CObjIndex)*
            SIXTRL_RESTRICT index_obj,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
    {
        static_assert(
            SIXTRL_CXX_NAMESPACE::Multipole_is_type< MultipoleT >(),
            "Requires MultipoleT to be a Multipole element" );

        return SIXTRL_CXX_NAMESPACE::CObjElem_from_cobj_index<
            MultipoleT >( index_obj, slot_size );
    }

    template< class MultipoleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
    SIXTRL_BE_ARGPTR_DEC MultipoleT const*
    Multipole_const_from_flat_cbuffer(
        SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
        cobj_size_t const pos_in_buffer,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
    {
        static_assert(
            SIXTRL_CXX_NAMESPACE::Multipole_is_type< MultipoleT >(),
            "Requires MultipoleT to be a Multipole element" );

        return SIXTRL_CXX_NAMESPACE::Multipole_const_from_cobj_index<
            MultipoleT >( ::NS(CObjFlatBuffer_const_index)(
                buffer, pos_in_buffer, slot_size ), slot_size );
    }

    template< class MultipoleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
    SIXTRL_BE_ARGPTR_DEC MultipoleT*
    Multipole_from_flat_cbuffer(
        SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
        cobj_size_t const pos_in_buffer,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
    {
        static_assert(
            SIXTRL_CXX_NAMESPACE::Multipole_is_type< MultipoleT >(),
            "Requires MultipoleT to be a Multipole element" );

        return SIXTRL_CXX_NAMESPACE::Multipole_from_cobj_index< MultipoleT >(
            ::NS(CObjFlatBuffer_index)( buffer, pos_in_buffer, slot_size ),
                slot_size );
    }

    template< class MultipoleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
    SIXTRL_BE_ARGPTR_DEC MultipoleT const*
    Multipole_const_from_cbuffer( SIXTRL_BUFFER_ARGPTR_DEC const
            CBufferView *const SIXTRL_RESTRICT cbuffer,
        cobj_size_t const pos_in_buffer ) SIXTRL_NOEXCEPT
    {
        static_assert(
            SIXTRL_CXX_NAMESPACE::Multipole_is_type< MultipoleT >(),
            "Requires MultipoleT to be a Multipole element" );

        return ( cbuffer != SIXTRL_NULLPTR )
            ? SIXTRL_CXX_NAMESPACE::Multipole_const_from_cobj_index<
                MultipoleT >( cbuffer->index_at( pos_in_buffer ),
                                cbuffer->slot_size() )
            : SIXTRL_NULLPTR;
    }

    template< class MultipoleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
    SIXTRL_BE_ARGPTR_DEC MultipoleT*
    Multipole_from_cbuffer(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView* SIXTRL_RESTRICT cbuffer,
        cobj_size_t const pos_in_buffer ) SIXTRL_NOEXCEPT
    {
        static_assert(
            SIXTRL_CXX_NAMESPACE::Multipole_is_type< MultipoleT >(),
            "Requires MultipoleT to be a Multipole element" );

        return ( cbuffer != SIXTRL_NULLPTR )
            ? SIXTRL_CXX_NAMESPACE::Multipole_from_cobj_index< MultipoleT >(
                cbuffer->index_at( pos_in_buffer ), cbuffer->slot_size() )
            : SIXTRL_NULLPTR;
    }

    #if !defined( _GPUCODE )

    template< class MultipoleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN bool Multipole_can_add_copy(
        SIXTRL_BUFFER_ARGPTR_DEC const CBufferView *const SIXTRL_RESTRICT cbuffer,
        SIXTRL_BE_ARGPTR_DEC const MultipoleT *const ptr_orig,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT
            ptr_requ_buffer_size = SIXTRL_NULLPTR,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT
            ptr_requ_num_slots = SIXTRL_NULLPTR,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT
            ptr_requ_num_objects = SIXTRL_NULLPTR,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT
            ptr_requ_num_pointers = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        static_assert(
            SIXTRL_CXX_NAMESPACE::Multipole_is_type< MultipoleT >(),
            "Requires MultipoleT to be a Multipole element" );

        return ( ( cbuffer != SIXTRL_NULLPTR ) &&
                 ( cbuffer->can_add_copy_of_object( ptr_orig,
                    ptr_requ_buffer_size, ptr_requ_num_slots,
                    ptr_requ_num_objects, ptr_requ_num_pointers ) ) );
    }

    template< class MultipoleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
    SIXTRL_BE_ARGPTR_DEC MultipoleT* Multipole_add_copy(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView* SIXTRL_RESTRICT cbuffer,
        SIXTRL_BE_ARGPTR_DEC const MultipoleT *const ptr_orig )
    {
        static_assert(
            SIXTRL_CXX_NAMESPACE::Multipole_is_type< MultipoleT >(),
            "Requires MultipoleT to be a Multipole element" );

        return ( cbuffer != SIXTRL_NULLPTR )
            ? SIXTRL_CXX_NAMESPACE::CBufferView_add_copy_of_object_detail(
                *cbuffer, ptr_orig, nullptr, nullptr, nullptr, nullptr, false )
            : SIXTRL_NULLPTR;
    }

    template< class MultipoleT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
    SIXTRL_BE_ARGPTR_DEC MultipoleT*
    Multipole_new(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView* SIXTRL_RESTRICT cbuffer,
        typename TypeMethodParamTraits< typename MultipoleTraits< MultipoleT
            >::order_t >::const_argument_type order,
        SIXTRL_BE_ARGPTR_DEC const MultipoleT *const SIXTRL_RESTRICT
            /* p */ = SIXTRL_NULLPTR )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_BE_ARGPTR_DEC MultipoleT* added_obj = SIXTRL_NULLPTR;

        static_assert(
            SIXTRL_CXX_NAMESPACE::Multipole_is_type< MultipoleT >(),
            "Requires MultipoleT to be a Multipole element" );

        if( cbuffer != SIXTRL_NULLPTR )
        {
            SIXTRL_ARGPTR_DEC MultipoleT orig;
            if( st::ARCH_STATUS_SUCCESS == st::Multipole_init( &orig, order ) )
            {
                added_obj = st::Multipole_add_copy( cbuffer, &orig );
            }
        }

        return added_obj;
    }

    template< class MultipoleT, typename... Args >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BE_ARGPTR_DEC MultipoleT*
    Multipole_add(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView* SIXTRL_RESTRICT cbuffer,
        typename TypeMethodParamTraits< typename MultipoleTraits< MultipoleT
            >::order_t >::const_argument_type order,
        Args&&... args, SIXTRL_BE_ARGPTR_DEC const MultipoleT *const
            SIXTRL_RESTRICT /* p */ = SIXTRL_NULLPTR )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_BE_ARGPTR_DEC MultipoleT* added_obj = SIXTRL_NULLPTR;

        static_assert( SIXTRL_CXX_NAMESPACE::Multipole_is_type< MultipoleT >(),
            "Requires MultipoleT to be a Multipole element" );

        if( cbuffer != SIXTRL_NULLPTR )
        {
            SIXTRL_ARGPTR_DEC MultipoleT orig;
            if( st::ARCH_STATUS_SUCCESS == st::Multipole_init(
                    &orig, order, std::forward< Args >( args )... ) )
            {
                added_obj = st::Multipole_add_copy( cbuffer, &orig );
            }
        }

        return added_obj;
    }

    #endif /* !defined( _GPUCODE ) */
}

template< class MultipoleT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
constexpr SIXTRL_CXX_NAMESPACE::cobj_type_id_t
NS(Multipole_type_id)( SIXTRL_BE_ARGPTR_DEC const MultipoleT *const
    SIXTRL_RESTRICT p = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Multipole_type_id< MultipoleT >( p );
}

template< class MultipoleT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
constexpr SIXTRL_CXX_NAMESPACE::cobj_size_t
NS(Multipole_num_pointers)(
    SIXTRL_BE_ARGPTR_DEC const MultipoleT *const
    SIXTRL_RESTRICT p = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Multipole_num_pointers< MultipoleT >( p );
}

template< class MultipoleT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::cobj_size_t
NS(Multipole_required_num_bytes)(
    SIXTRL_CXX_NAMESPACE::cobj_size_t const slot_size,
    SIXTRL_BE_ARGPTR_DEC const MultipoleT *const SIXTRL_RESTRICT
        p = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Multipole_required_num_bytes< MultipoleT >(
        slot_size, p );
}

template< class MultipoleT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::cobj_size_t
NS(Multipole_required_num_slots)(
    SIXTRL_CXX_NAMESPACE::cobj_size_t const slot_size,
    SIXTRL_BE_ARGPTR_DEC const MultipoleT *const SIXTRL_RESTRICT
        p = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Multipole_required_num_slots< MultipoleT >(
        slot_size, p );
}

template< class MultipoleT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BE_ARGPTR_DEC MultipoleT const*
NS(Multipole_const_from_cobj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const ::NS(CObjIndex) *const
        SIXTRL_RESTRICT index_obj,
    SIXTRL_CXX_NAMESPACE::cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Multipole_const_from_cobj_index<
        MultipoleT >( index_obj, slot_size );
}

template< class MultipoleT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BE_ARGPTR_DEC MultipoleT*
NS(Multipole_from_cobj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC ::NS(CObjIndex)* SIXTRL_RESTRICT index_obj,
    SIXTRL_CXX_NAMESPACE::cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Multipole_from_cobj_index<
        MultipoleT >( index_obj, slot_size );
}

template< class MultipoleT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BE_ARGPTR_DEC MultipoleT const*
NS(Multipole_const_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    SIXTRL_CXX_NAMESPACE::cobj_size_t const pos_in_buffer,
    SIXTRL_CXX_NAMESPACE::cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Multipole_const_from_flat_cbuffer<
        MultipoleT >( buffer, pos_in_buffer, slot_size );
}

template< class MultipoleT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BE_ARGPTR_DEC MultipoleT*
NS(Multipole_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    SIXTRL_CXX_NAMESPACE::cobj_size_t const pos_in_buffer,
    SIXTRL_CXX_NAMESPACE::cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Multipole_from_flat_cbuffer<
        MultipoleT >( buffer, pos_in_buffer, slot_size );
}

template< class MultipoleT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BE_ARGPTR_DEC MultipoleT const*
NS(Multipole_const_from_cbuffer)(
    SIXTRL_BUFFER_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::CBufferView *const
        SIXTRL_RESTRICT cbuffer,
    SIXTRL_CXX_NAMESPACE::cobj_size_t const pos_in_buffer ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Multipole_const_from_cbuffer< MultipoleT >(
        cbuffer, pos_in_buffer );
}

template< class MultipoleT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BE_ARGPTR_DEC MultipoleT*
NS(Multipole_from_cbuffer)(
    SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBufferView*
        SIXTRL_RESTRICT cbuffer,
    SIXTRL_CXX_NAMESPACE::cobj_size_t const pos_in_buffer ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Multipole_from_cbuffer< MultipoleT >(
        cbuffer, pos_in_buffer );
}

#if !defined( _GPUCODE )

template< class MultipoleT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN bool NS(Multipole_can_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::CBufferView *const
        SIXTRL_RESTRICT cbuffer,
    SIXTRL_BE_ARGPTR_DEC const MultipoleT *const ptr_orig,
    SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::cobj_size_t* SIXTRL_RESTRICT
        ptr_requ_buffer_size = SIXTRL_NULLPTR,
    SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::cobj_size_t* SIXTRL_RESTRICT
        ptr_requ_num_slots = SIXTRL_NULLPTR,
    SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::cobj_size_t* SIXTRL_RESTRICT
        ptr_requ_num_objects = SIXTRL_NULLPTR,
    SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::cobj_size_t* SIXTRL_RESTRICT
        ptr_requ_num_pointers = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::Multipole_can_add_copy( cbuffer, ptr_orig,
        ptr_requ_buffer_size, ptr_requ_num_slots, ptr_requ_num_objects,
            ptr_requ_num_pointers );
}

template< class MultipoleT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC MultipoleT*
NS(Multipole_add_copy)( SIXTRL_BUFFER_ARGPTR_DEC
        SIXTRL_CXX_NAMESPACE::CBufferView* SIXTRL_RESTRICT cbuffer,
    SIXTRL_BE_ARGPTR_DEC const MultipoleT *const ptr_orig )
{
    return SIXTRL_CXX_NAMESPACE::Multipole_add_copy< MultipoleT >(
        cbuffer, ptr_orig );
}

template< class MultipoleT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC MultipoleT*
NS(Multipole_new)( SIXTRL_BUFFER_ARGPTR_DEC
        SIXTRL_CXX_NAMESPACE::CBufferView* SIXTRL_RESTRICT cbuffer,
    typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
        SIXTRL_CXX_NAMESPACE::MultipoleTraits< MultipoleT >::order_t
            >::const_argument_type order )
{
    return SIXTRL_CXX_NAMESPACE::Multipole_new< MultipoleT >(
        cbuffer, order );
}

template< class MultipoleT, typename... Args >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_BE_ARGPTR_DEC MultipoleT*
NS(Multipole_add)(
    SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBufferView*
        SIXTRL_RESTRICT cbuffer,
    typename SIXTRL_CXX_NAMESPACE::TypeMethodParamTraits< typename
        SIXTRL_CXX_NAMESPACE::MultipoleTraits< MultipoleT >::order_t
            >::const_argument_type order, Args&&... args,
    SIXTRL_BE_ARGPTR_DEC const MultipoleT *const SIXTRL_RESTRICT
        p = SIXTRL_NULLPTR )
{
    return SIXTRL_CXX_NAMESPACE::Multipole_add< MultipoleT, Args... >(
        cbuffer, order, std::forward< Args >( args )..., p );
}

#endif /* !defined( _GPUCODE ) */
#endif /* __cplusplus */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC SIXTRL_FN NS(cobj_type_id_t)
NS(Multipole_type_id)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(Multipole) const*
NS(Multipole_const_from_cobj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const
        SIXTRL_RESTRICT index_obj,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(Multipole)*
NS(Multipole_from_cobj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* SIXTRL_RESTRICT index_obj,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(Multipole) const*
NS(Multipole_const_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC NS(Multipole)*
NS(Multipole_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_type_id_t)
NS(Multipole_type_id_ext)( void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Multipole_can_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(CBufferView) *const
        SIXTRL_RESTRICT cbuffer,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const ptr_orig,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)* SIXTRL_RESTRICT requ_num_slots,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)* SIXTRL_RESTRICT requ_num_objects,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)* SIXTRL_RESTRICT requ_num_pointers
) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(Multipole)*
NS(Multipole_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(CBufferView)* SIXTRL_RESTRICT cbuffer,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const ptr_orig );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_BE_ARGPTR_DEC NS(Multipole)*
NS(Multipole_new)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(CBufferView)* SIXTRL_RESTRICT cbuffer,
    NS(be_order_t) const order );

#endif /* _GPUCODE */
#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!!!        Inline Methods and Functions Implementations       !!!!!!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/element_traits.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_INLINE NS(cobj_type_id_t) NS(Multipole_type_id)( void ) SIXTRL_NOEXCEPT
{
    #if defined( __cplusplus )
    SIXTRL_ASSERT( ::NS(OBJECT_TYPE_MULTIPOLE) ==
        SIXTRL_CXX_NAMESPACE::Multipole_type_id< ::NS(Multipole) >() );
    #endif /* C++ */

    return NS(OBJECT_TYPE_MULTIPOLE);
}

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(Multipole) const*
NS(Multipole_const_from_cobj_index)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC const
        NS(CObjIndex) *const SIXTRL_RESTRICT index_obj,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return ( SIXTRL_BE_ARGPTR_DEC NS(Multipole) const* )( uintptr_t
        )NS(CObjIndex_begin_addr_filter_by_type_info)( index_obj,
            NS(Multipole_type_id)(), sizeof( NS(Multipole) ), slot_size );
}

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(Multipole)*
NS(Multipole_from_cobj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* SIXTRL_RESTRICT index_obj,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return ( SIXTRL_BE_ARGPTR_DEC NS(Multipole)* )( uintptr_t
        )NS(CObjIndex_begin_addr_filter_by_type_info)(
            index_obj, NS(Multipole_type_id)(), sizeof( NS(Multipole) ),
                slot_size );
}

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(Multipole) const*
NS(Multipole_const_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return NS(Multipole_const_from_cobj_index)( NS(CObjFlatBuffer_const_index)(
        buffer, pos_in_buffer, slot_size ), slot_size );
}

SIXTRL_INLINE SIXTRL_BE_ARGPTR_DEC NS(Multipole)*
NS(Multipole_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return NS(Multipole_from_cobj_index)( NS(CObjFlatBuffer_index)(
        buffer, pos_in_buffer, slot_size ), slot_size );
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_MULTIPOLE_COBJECTS_H__ */
