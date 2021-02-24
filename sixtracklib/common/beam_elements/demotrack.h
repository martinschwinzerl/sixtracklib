#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DEMOTRACK_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DEMOTRACK_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/definitions.h"
    #include "sixtracklib/common/cobjects/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus )
    #include <algorithm>
    #include <memory>
    #include <vector>
    #include <cstdio>
#endif /* !defined( SIXTRL_NO_INCLUDES ) && defined( __cplusplus ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdbool.h>
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

struct NS(CObjIndex);
struct NS(CBuffer);

typedef enum
{
    NS(DEMOTRACK_FODO_LATTICE_FLAGS_NONE)            = 0x00,
    NS(DEMOTRACK_FODO_LATTICE_USE_DRIFT_EXACT_FLAG)  = 0x01,
    NS(DEMOTRACK_FODO_LATTICE_ADD_END_TRACK_MARKER)  = 0x02,
    NS(DEMOTRACK_FODO_LATTICE_ADD_DUMMY_SPACECHARGE) = 0x04
}
NS(demotrack_lattice_flags_type);

typedef enum
{
    NS(DEMOTRACK_BEAM_ELEMENT_UNKNOWN) = 0,
    NS(DEMOTRACK_BEAM_ELEMENT_DRIFT) = 2,
    NS(DEMOTRACK_BEAM_ELEMENT_DRIFT_EXACT) = 3,
    NS(DEMOTRACK_BEAM_ELEMENT_MULTIPOLE) = 4,
    NS(DEMOTRACK_BEAM_ELEMENT_CAVITY) = 5,
    NS(DEMOTRACK_BEAM_ELEMENT_XY_SHIFT) = 6,
    NS(DEMOTRACK_BEAM_ELEMENT_SROTATION) = 7,
    NS(DEMOTRACK_BEAM_ELEMENT_LIMIT_RECT) = 11,
    NS(DEMOTRACK_BEAM_ELEMENT_LIMIT_ELLIPSE) = 12,
    NS(DEMOTRACK_BEAM_ELEMENT_LIMIT_RECT_ELLIPSE) = 13,
    NS(DEMOTRACK_BEAM_ELEMENT_SC_COASTING) = 16,
    NS(DEMOTRACK_BEAM_ELEMENT_SC_QGAUSSIAN_PROFILE) = 17,
    NS(DEMOTRACK_BEAM_ELEMENT_DIPEDGE) = 24,
    NS(DEMOTRACK_BEAM_ELEMENT_END_OF_TRACK) = 255
}
NS(demotrack_belement_type);

SIXTRL_STATIC SIXTRL_FN NS(demotrack_belement_type)
NS(Demotrack_belems_type_id_from_cobj_type_id)(
    NS(cobj_obj_id_type) const cobj_type_id ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(demotrack_belement_type)
NS(Demotrack_belems_type_id_for_cobj_index)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const struct NS(CObjIndex) *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(size_type)
NS(Demotrack_belems_requ_num_slots_for_type_id)(
    NS(demotrack_belement_type) const dt_type_id ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(size_type)
NS(Demotrack_belems_requ_num_slots_for_cobj_type_id)(
    NS(cobj_obj_id_type) const cobj_type_id ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(size_type)
NS(Demotrack_belems_requ_num_slots_for_cobj_index)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const struct NS(CObjIndex) *const
        SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(size_type)
NS(Demotrack_belems_requ_num_slots_for_cobj_index_range)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const* SIXTRL_RESTRICT b,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const* SIXTRL_RESTRICT end
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN bool NS(Demotrack_belems_can_convert_cobj_index_range)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const* SIXTRL_RESTRICT b,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC struct NS(CObjIndex) const* SIXTRL_RESTRICT end
) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(demotrack_belement_type)
NS(Demotrack_belems_type_id_from_storage)(
    NS(be_real_type) const* stored_demotrack_lattice,
    NS(size_type) const num_stored_slots,
    NS(size_type) const current_slot ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN NS(size_type) NS(Demotrack_belems_num_stored_objects)(
    NS(be_real_type) const* stored_demotrack_lattice,
    NS(size_type) const num_stored_slots ) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN NS(size_type)
NS(Demotrack_belems_cobj_index_range_to_flat_buffer_real)(
    NS(size_type) max_num_buffer_elements,
    NS(be_real_type)* SIXTRL_RESTRICT data_buffer_begin,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* begin,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* end );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(size_type)
NS(Demotrack_belems_cbuffer_to_flat_buffer_real)(
    NS(size_type) max_num_buffer_elements,
    NS(be_real_type)* SIXTRL_RESTRICT data_buffer_begin,
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT
        cobj_buffer );

#endif /* !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    struct CBufferView;

    template< typename T, class Alloc = std::allocator< T > >
    SIXTRL_STATIC SIXTRL_HOST_FN ::NS(size_type)
    TDemotrack_belems_cobj_index_range_to_flat_buffer(
        std::vector< T, Alloc >& demotrack_buffer,
        SIXTRL_CBUFFER_OBJ_ARGPTR_DEC ::NS(CObjIndex) const* begin,
        SIXTRL_CBUFFER_OBJ_ARGPTR_DEC ::NS(CObjIndex) const* end );

    template< typename T, class Alloc = std::allocator< T > >
    SIXTRL_STATIC SIXTRL_HOST_FN ::NS(size_type)
    TDemotrack_belems_cbuffer_to_flat_buffer(
        std::vector< T, Alloc >& demotrack_buffer,
        CBufferView const& SIXTRL_RESTRICT_REF cbuffer );

} /* end: namespace SIXTRL_CXX_NAMESPACE */
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

/* ************************************************************************* */
/* ************************************************************************* */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/all_beam_elements.h"
    #include "sixtracklib/common/cobjects/index_object.h"
    #include "sixtracklib/common/cobjects/cbuffer.h"
    #include "sixtracklib/common/cobjects/cbuffer_view.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

SIXTRL_INLINE NS(demotrack_belement_type)
NS(Demotrack_belems_type_id_from_cobj_type_id)(
    NS(cobj_obj_id_type) const cobj_type_id ) SIXTRL_NOEXCEPT {

    NS(demotrack_belement_type) dt_type_id =
        NS(DEMOTRACK_BEAM_ELEMENT_UNKNOWN);

    switch( cobj_type_id )
    {
        case NS(COBJECTS_TYPE_ID_CAVITY):
        {
            dt_type_id =  NS(DEMOTRACK_BEAM_ELEMENT_CAVITY);
            break;
        }

        case NS(COBJECTS_TYPE_ID_DIPOLE_EDGE):
        {
            dt_type_id =  NS(DEMOTRACK_BEAM_ELEMENT_DIPEDGE);
            break;
        }

        case NS(COBJECTS_TYPE_ID_DRIFT):
        {
            dt_type_id =  NS(DEMOTRACK_BEAM_ELEMENT_DRIFT);
            break;
        }

        case NS(COBJECTS_TYPE_ID_DRIFT_EXACT):
        {
            dt_type_id =  NS(DEMOTRACK_BEAM_ELEMENT_DRIFT_EXACT);
            break;
        }

        case NS(COBJECTS_TYPE_ID_END_TRACKING):
        {
            dt_type_id =  NS(DEMOTRACK_BEAM_ELEMENT_END_OF_TRACK);
            break;
        }

        case NS(COBJECTS_TYPE_ID_LIMIT_RECT):
        {
            dt_type_id =  NS(DEMOTRACK_BEAM_ELEMENT_LIMIT_RECT);
            break;
        }

        case NS(COBJECTS_TYPE_ID_LIMIT_ELLIPSE):
        {
            dt_type_id =  NS(DEMOTRACK_BEAM_ELEMENT_LIMIT_ELLIPSE);
            break;
        }

        case NS(COBJECTS_TYPE_ID_LIMIT_RECT_ELLIPSE):
        {
            dt_type_id =  NS(DEMOTRACK_BEAM_ELEMENT_LIMIT_RECT_ELLIPSE);
            break;
        }

        case NS(COBJECTS_TYPE_ID_MULTIPOLE):
        {
            dt_type_id =  NS(DEMOTRACK_BEAM_ELEMENT_MULTIPOLE);
            break;
        }

        case NS(COBJECTS_TYPE_ID_SROTATION):
        {
            dt_type_id =  NS(DEMOTRACK_BEAM_ELEMENT_SROTATION);
            break;
        }

        case NS(COBJECTS_TYPE_ID_XY_SHIFT):
        {
            dt_type_id =  NS(DEMOTRACK_BEAM_ELEMENT_XY_SHIFT);
            break;
        }

        case NS(COBJECTS_TYPE_ID_SC_COASTING):
        {
            dt_type_id = NS(DEMOTRACK_BEAM_ELEMENT_SC_COASTING);
            break;
        }

        case NS(COBJECTS_TYPE_ID_SC_QGAUSSIAN_PROFILE):
        {
            dt_type_id = NS(DEMOTRACK_BEAM_ELEMENT_SC_QGAUSSIAN_PROFILE);
            break;
        }

        default:
        {
            dt_type_id = NS(DEMOTRACK_BEAM_ELEMENT_UNKNOWN);
        }
    };

    return dt_type_id;
}

SIXTRL_INLINE NS(demotrack_belement_type)
NS(Demotrack_belems_type_id_for_cobj_index)( SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const
    NS(CObjIndex) *const SIXTRL_RESTRICT obj ) SIXTRL_NOEXCEPT
{
    return ( obj != SIXTRL_NULLPTR )
        ? NS(Demotrack_belems_type_id_from_cobj_type_id)(
            NS(CObjIndex_type_id)( obj ) )
        : NS(DEMOTRACK_BEAM_ELEMENT_UNKNOWN);
}

SIXTRL_INLINE NS(size_type) NS(Demotrack_belems_requ_num_slots_for_type_id)(
    NS(demotrack_belement_type) const dt_type_id ) SIXTRL_NOEXCEPT {
    NS(size_type) num_slots = ( NS(size_type) )0u;

    switch( dt_type_id )
    {
        case NS(DEMOTRACK_BEAM_ELEMENT_CAVITY):  { num_slots =  4u; break; }
        case NS(DEMOTRACK_BEAM_ELEMENT_DIPEDGE): { num_slots =  3u; break; }
        case NS(DEMOTRACK_BEAM_ELEMENT_DRIFT):   { num_slots =  2u; break; }

        case NS(DEMOTRACK_BEAM_ELEMENT_DRIFT_EXACT):
        {
            num_slots =  2u;
            break;
        }

        case NS(DEMOTRACK_BEAM_ELEMENT_END_OF_TRACK):
        {
            num_slots =  4u;
            break;
        }

        case NS(DEMOTRACK_BEAM_ELEMENT_LIMIT_RECT): { num_slots =  5u; break; }

        case NS(DEMOTRACK_BEAM_ELEMENT_LIMIT_ELLIPSE):
        {
            num_slots =  4u;
            break;
        }

        case NS(DEMOTRACK_BEAM_ELEMENT_LIMIT_RECT_ELLIPSE):
        {
            num_slots =  6u;
            break;
        }

        case NS(DEMOTRACK_BEAM_ELEMENT_MULTIPOLE): { num_slots = 39u; break; }
        case NS(DEMOTRACK_BEAM_ELEMENT_SROTATION): { num_slots =  3u; break; }
        case NS(DEMOTRACK_BEAM_ELEMENT_XY_SHIFT):  { num_slots =  3u; break; }

        case NS(DEMOTRACK_BEAM_ELEMENT_SC_COASTING):
        {
            num_slots = 10u;
            break;
        }

        case NS(DEMOTRACK_BEAM_ELEMENT_SC_QGAUSSIAN_PROFILE):
        {
            num_slots = 11u;
            break;
        }

        default:
        {
            num_slots = ( NS(size_type) )0u;
        }
    };

    return num_slots;
}

SIXTRL_INLINE NS(size_type) NS(Demotrack_belems_requ_num_slots_for_cobj_type_id)(
    NS(cobj_obj_id_type) const cobj_type_id ) SIXTRL_NOEXCEPT {
    return NS(Demotrack_belems_requ_num_slots_for_type_id)(
        NS(Demotrack_belems_type_id_from_cobj_type_id)( cobj_type_id ) ); }

SIXTRL_INLINE NS(size_type) NS(Demotrack_belems_requ_num_slots_for_cobj_index)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const SIXTRL_RESTRICT obj
) SIXTRL_NOEXCEPT {
    return ( obj != SIXTRL_NULLPTR )
        ? NS(Demotrack_belems_requ_num_slots_for_cobj_type_id)(
            NS(CObjIndex_type_id)( obj ) )
        : ( NS(size_type) )0u;
}

SIXTRL_INLINE NS(size_type)
NS(Demotrack_belems_requ_num_slots_for_cobj_index_range)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* SIXTRL_RESTRICT it,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* SIXTRL_RESTRICT end
) SIXTRL_NOEXCEPT
{
    NS(size_type) total_num_slots = ( NS(size_type) )0u;

    if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) &&
        ( ( uintptr_t )it <= ( uintptr_t )end ) )
    {
        for( ; it != end ; ++it )
        {
            NS(size_type) const elem_num_slots =
                NS(Demotrack_belems_requ_num_slots_for_cobj_index)( it );

            if( elem_num_slots >= ( NS(size_type) )1u )
            {
                total_num_slots += elem_num_slots;
            }
            else
            {
                total_num_slots = ( NS(size_type) )0u;
                break;
            }
        }
    }

    return total_num_slots;
}

SIXTRL_INLINE bool NS(Demotrack_belems_can_convert_cobj_index_range)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* SIXTRL_RESTRICT it,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* SIXTRL_RESTRICT end
) SIXTRL_NOEXCEPT
{
    bool can_convert = false;

    if( ( it != SIXTRL_NULLPTR ) && ( end != SIXTRL_NULLPTR ) &&
        ( ( uintptr_t )it <= ( uintptr_t )end ) )
    {
        can_convert = true;

        while( ( it != end ) && ( can_convert ) )
        {
            can_convert = (
                NS(Demotrack_belems_type_id_for_cobj_index)( it++ ) !=
                NS(DEMOTRACK_BEAM_ELEMENT_UNKNOWN) );
        }
    }

    return can_convert;
}

SIXTRL_INLINE NS(demotrack_belement_type)
NS(Demotrack_belems_type_id_from_storage)(
    NS(be_real_type) const* stored_demotrack_lattice,
    NS(size_type) const num_stored_slots,
    NS(size_type) const current_slot ) SIXTRL_NOEXCEPT {
    NS(demotrack_belement_type) dt_type_id = NS(DEMOTRACK_BEAM_ELEMENT_UNKNOWN);

    if( ( stored_demotrack_lattice != SIXTRL_NULLPTR ) &&
        ( num_stored_slots > ( NS(size_type) )0u ) &&
        ( num_stored_slots > current_slot + ( NS(size_type) )1u ) )
    {
        int const temp_type_id = ( int )stored_demotrack_lattice[ current_slot ];

        switch( temp_type_id )
        {
            case ( int )NS(DEMOTRACK_BEAM_ELEMENT_DRIFT):
            case ( int )NS(DEMOTRACK_BEAM_ELEMENT_DRIFT_EXACT):
            case ( int )NS(DEMOTRACK_BEAM_ELEMENT_MULTIPOLE):
            case ( int )NS(DEMOTRACK_BEAM_ELEMENT_CAVITY):
            case ( int )NS(DEMOTRACK_BEAM_ELEMENT_XY_SHIFT):
            case ( int )NS(DEMOTRACK_BEAM_ELEMENT_SROTATION):
            case ( int )NS(DEMOTRACK_BEAM_ELEMENT_LIMIT_RECT):
            case ( int )NS(DEMOTRACK_BEAM_ELEMENT_LIMIT_ELLIPSE):
            case ( int )NS(DEMOTRACK_BEAM_ELEMENT_LIMIT_RECT_ELLIPSE):
            case ( int )NS(DEMOTRACK_BEAM_ELEMENT_SC_COASTING):
            case ( int )NS(DEMOTRACK_BEAM_ELEMENT_SC_QGAUSSIAN_PROFILE):
            case ( int )NS(DEMOTRACK_BEAM_ELEMENT_DIPEDGE):
            case ( int )NS(DEMOTRACK_BEAM_ELEMENT_END_OF_TRACK):
            {
                dt_type_id = ( NS(demotrack_belement_type) )temp_type_id;
                break;
            }

            default:
            {
                dt_type_id = NS(DEMOTRACK_BEAM_ELEMENT_UNKNOWN);
            }
        };
    }

    return dt_type_id;
}

SIXTRL_INLINE NS(size_type) NS(Demotrack_belems_num_stored_objects)(
    NS(be_real_type) const* stored_demotrack_lattice,
    NS(size_type) const num_stored_slots ) SIXTRL_NOEXCEPT {
    NS(size_type) num_objects = ( NS(size_type) )0u;

    if( ( stored_demotrack_lattice != SIXTRL_NULLPTR ) &&
        ( num_stored_slots > ( NS(size_type) )0u ) )
    {
        NS(size_type) slot_idx = ( NS(size_type) )0u;

        while( slot_idx < num_stored_slots )
        {
            NS(size_type) elem_num_slots = ( NS(size_type) )0u;
            NS(demotrack_belement_type) const dt_type_id =
                NS(Demotrack_belems_type_id_from_storage)(
                    stored_demotrack_lattice, num_stored_slots, slot_idx );

            if( dt_type_id == NS(DEMOTRACK_BEAM_ELEMENT_UNKNOWN) )
            {
                num_objects = ( NS(size_type) )0u;
                break;
            }

            elem_num_slots =
                NS(Demotrack_belems_requ_num_slots_for_type_id)( dt_type_id );

            if( ( elem_num_slots == ( NS(size_type) )0u ) ||
                ( slot_idx + elem_num_slots > num_stored_slots ) )
            {
                num_objects = ( NS(size_type) )0u;
                break;
            }

            slot_idx += elem_num_slots;
            ++num_objects;
        }
    }

    return num_objects;
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    template< typename T, class Alloc >
    ::NS(size_type) TDemotrack_belems_cbuffer_to_flat_buffer(
        std::vector< T, Alloc >& demotrack_buffer,
        SIXTRL_CXX_NAMESPACE::CBufferView const& SIXTRL_RESTRICT_REF cobj_buffer )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return st::TDemotrack_belems_cobj_index_range_to_flat_buffer(
            demotrack_buffer,
            cobj_buffer.objects_begin(), cobj_buffer.objects_end() );
    }

    template< typename T, class Alloc >
    ::NS(size_type) TDemotrack_belems_cobj_index_range_to_flat_buffer(
        std::vector< T, Alloc >& buffer,
        SIXTRL_CBUFFER_OBJ_ARGPTR_DEC ::NS(CObjIndex) const* it,
        SIXTRL_CBUFFER_OBJ_ARGPTR_DEC ::NS(CObjIndex) const* end ) {

        namespace st = SIXTRL_CXX_NAMESPACE;
        buffer.clear();

        st::size_type const requ_num_slots =
            ::NS(Demotrack_belems_requ_num_slots_for_cobj_index_range)( it, end );

        if( requ_num_slots > st::size_type{ 0 } )
        {
            SIXTRL_ASSERT( it  != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( end != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( reinterpret_cast< uintptr_t >( it ) <=
                           reinterpret_cast< uintptr_t >( end ) );

            buffer.reserve( requ_num_slots );

            for( ; it != end ; ++it )
            {
                st::status_type status = st::STATUS_SUCCESS;
                st::cobj_obj_id_type const cobj_type_id =
                    ::NS(CObjIndex_type_id)( it );

                ::NS(demotrack_belement_type) const dt_type_id =
                    ::NS(Demotrack_belems_type_id_for_cobj_index)( it );

                st::size_type const elem_num_slots =
                    ::NS(Demotrack_belems_requ_num_slots_for_cobj_index)( it );

                if( ( cobj_type_id == st::COBJECTS_TYPE_ID_UNDEFINED ) ||
                    ( cobj_type_id == st::COBJECTS_TYPE_ID_ILLEGAL ) ||
                    ( dt_type_id == ::NS(DEMOTRACK_BEAM_ELEMENT_UNKNOWN) ) ||
                    ( elem_num_slots < st::size_type{ 1 } ) )
                {
                    buffer.clear();
                    break;
                }

                st::size_type const cur_num_slots = buffer.size();
                buffer.push_back( static_cast< T >( dt_type_id ) );

                switch( ::NS(CObjIndex_type_id)( it ) )
                {
                    case ::NS(COBJECTS_TYPE_ID_CAVITY):
                    {
                        auto elem = ::NS(Cavity_const_from_cobj_index)( it );
                        if( elem != nullptr )
                        {
                            buffer.push_back( static_cast< T >(
                                ::NS(Cavity_voltage)( elem ) ) );
                            buffer.push_back( static_cast< T >(
                                ::NS(Cavity_frequency)( elem ) ) );
                            buffer.push_back( static_cast< T >(
                                ::NS(Cavity_lag)( elem ) ) );
                        }

                        break;
                    }

                    case ::NS(COBJECTS_TYPE_ID_DIPOLE_EDGE):
                    {
                        auto elem = ::NS(DipoleEdge_const_from_cobj_index)( it );
                        if( elem != nullptr )
                        {
                            buffer.push_back( static_cast< T >(
                                ::NS(DipoleEdge_r21)( elem ) ) );
                            buffer.push_back( static_cast< T >(
                                ::NS(DipoleEdge_r43)( elem ) ) );
                        }

                        break;
                    }

                    case ::NS(COBJECTS_TYPE_ID_DRIFT):
                    {
                        auto elem = ::NS(Drift_const_from_cobj_index)( it );

                        if( elem != nullptr )
                        {
                            buffer.push_back( static_cast< T >(
                                ::NS(Drift_length)( elem ) ) );
                        }

                        break;
                    }

                    case ::NS(COBJECTS_TYPE_ID_DRIFT_EXACT):
                    {
                        auto elem = ::NS(DriftExact_const_from_cobj_index)( it );

                        if( elem != nullptr )
                        {
                            buffer.push_back( static_cast< T >(
                                ::NS(DriftExact_length)( elem ) ) );
                        }

                        break;
                    }

                    case ::NS(COBJECTS_TYPE_ID_END_TRACKING):
                    {
                        auto elem = ::NS(EndTracking_const_from_cobj_index)( it );

                        if( elem != nullptr )
                        {
                            buffer.push_back( static_cast< T >(
                                ::NS(EndTracking_next_at_element)( elem ) ) );
                            buffer.push_back( static_cast< T >(
                                ::NS(EndTracking_next_buffer_idx)( elem ) ) );
                            buffer.push_back( ( ::NS(EndTracking_ends_turn)(
                                elem ) ) ? T{ 1. } : T{ 0. } );
                        }

                        break;
                    }

                    case ::NS(COBJECTS_TYPE_ID_LIMIT_RECT):
                    {
                        auto elem = ::NS(LimitRect_const_from_cobj_index)( it );
                        if( ( elem != nullptr ) &&
                            ( ::NS(LimitRect_is_consistent)( elem ) ) )
                        {
                            buffer.push_back( static_cast< T >(
                                ::NS(LimitRect_x_min)( elem ) ) );
                            buffer.push_back( static_cast< T >(
                                ::NS(LimitRect_x_max)( elem ) ) );
                            buffer.push_back( static_cast< T >(
                                ::NS(LimitRect_y_min)( elem ) ) );
                            buffer.push_back( static_cast< T >(
                                ::NS(LimitRect_y_max)( elem ) ) );
                        }

                        break;
                    }

                    case ::NS(COBJECTS_TYPE_ID_LIMIT_ELLIPSE):
                    {
                        auto elem = ::NS(LimitEllipse_const_from_cobj_index)( it );
                        if( ( elem != nullptr ) &&
                            ( ::NS(LimitEllipse_is_consistent)( elem ) ) )
                        {
                            buffer.push_back( static_cast< T >(
                                ::NS(LimitEllipse_a_squ)( elem ) ) );
                            buffer.push_back( static_cast< T >(
                                ::NS(LimitEllipse_b_squ)( elem ) ) );
                            buffer.push_back( static_cast< T >(
                                ::NS(LimitEllipse_a_b_squ)( elem ) ) );
                        }

                        break;
                    }

                    case ::NS(COBJECTS_TYPE_ID_LIMIT_RECT_ELLIPSE):
                    {
                        auto elem =
                            ::NS(LimitRectEllipse_const_from_cobj_index)( it );

                        if( ( elem != nullptr ) &&
                            ( ::NS(LimitRectEllipse_is_consistent)( elem ) ) )
                        {
                            buffer.push_back( static_cast< T >(
                                ::NS(LimitRectEllipse_x_max)( elem ) ) );
                            buffer.push_back( static_cast< T >(
                                ::NS(LimitRectEllipse_y_max)( elem ) ) );
                            buffer.push_back( static_cast< T >(
                                ::NS(LimitRectEllipse_a_squ)( elem ) ) );
                            buffer.push_back( static_cast< T >(
                                ::NS(LimitRectEllipse_b_squ)( elem ) ) );
                            buffer.push_back( static_cast< T >(
                                ::NS(LimitRectEllipse_a_b_squ)( elem ) ) );
                        }

                        break;
                    }

                    case ::NS(COBJECTS_TYPE_ID_MULTIPOLE):
                    {
                        auto elem = ::NS(Multipole_const_from_cobj_index)( it );

                        if( ( elem != nullptr ) &&
                            ( ::NS(Multipole_order)( elem ) >=
                              ::NS(be_order_type){ 0 } ) &&
                            ( ::NS(Multipole_order)( elem ) <=
                              ::NS(be_order_type){ 16 } ) )
                        {
                            T DUMMY_BAL_ARRAY[ 34 ] =
                            {
                                T{ 0 }, T{ 0 }, T{ 0 }, T{ 0 }, T{ 0 }, T{ 0 },
                                T{ 0 }, T{ 0 }, T{ 0 }, T{ 0 }, T{ 0 }, T{ 0 },
                                T{ 0 }, T{ 0 }, T{ 0 }, T{ 0 }, T{ 0 }, T{ 0 },
                                T{ 0 }, T{ 0 }, T{ 0 }, T{ 0 }, T{ 0 }, T{ 0 },
                                T{ 0 }, T{ 0 }, T{ 0 }, T{ 0 }, T{ 0 }, T{ 0 },
                                T{ 0 }, T{ 0 }, T{ 0 }, T{ 0 }
                            };

                            std::copy( ::NS(Multipole_const_bal_begin)( elem ),
                                       ::NS(Multipole_const_bal_end)( elem ),
                                       &DUMMY_BAL_ARRAY[ 0 ] );

                            buffer.push_back( static_cast< T >(
                                ::NS(Multipole_order)( elem ) ) );
                            buffer.push_back( static_cast< T >(
                                ::NS(Multipole_length)( elem ) ) );
                            buffer.push_back( static_cast< T >(
                                ::NS(Multipole_hxl)( elem ) ) );
                            buffer.push_back( static_cast< T >(
                                ::NS(Multipole_hyl)( elem ) ) );

                            for( ::NS(size_type) ii = 0u ; ii < 34u ; ++ii )
                                buffer.push_back( DUMMY_BAL_ARRAY[ ii ] );
                        }

                        break;
                    }

                    case ::NS(COBJECTS_TYPE_ID_SROTATION):
                    {
                        auto elem = ::NS(SRotation_const_from_cobj_index)( it );

                        if( elem != nullptr )
                        {
                            buffer.push_back( static_cast< T >(
                                ::NS(SRotation_cos_z)( elem ) ) );
                            buffer.push_back( static_cast< T >(
                                ::NS(SRotation_sin_z)( elem ) ) );
                        }

                        break;
                    }

                    case ::NS(COBJECTS_TYPE_ID_XY_SHIFT):
                    {
                        auto elem = ::NS(XYShift_const_from_cobj_index)( it );

                        if( elem != nullptr )
                        {
                            buffer.push_back( static_cast< T >(
                                ::NS(XYShift_dx)( elem ) ) );
                            buffer.push_back( static_cast< T >(
                                ::NS(XYShift_dy)( elem ) ) );
                        }

                        break;
                    }

                    case ::NS(COBJECTS_TYPE_ID_SC_COASTING):
                    {
                        auto elem = ::NS(SCCoasting_const_from_cobj_index)( it );

                        if( elem != nullptr )
                        {
                            buffer.push_back( static_cast< T >(
                                ::NS(SCCoasting_number_of_particles)( elem ) ) );
                            buffer.push_back( static_cast< T >(
                                ::NS(SCCoasting_circumference)( elem ) ) );
                            buffer.push_back( static_cast< T >(
                                ::NS(SCCoasting_sigma_x)( elem ) ) );
                            buffer.push_back( static_cast< T >(
                                ::NS(SCCoasting_sigma_y)( elem ) ) );
                            buffer.push_back( static_cast< T >(
                                ::NS(SCCoasting_length)( elem ) ) );
                            buffer.push_back( static_cast< T >(
                                ::NS(SCCoasting_x_co)( elem ) ) );
                            buffer.push_back( static_cast< T >(
                                ::NS(SCCoasting_y_co)( elem ) ) );
                            buffer.push_back( static_cast< T >(
                                ::NS(SCCoasting_min_sigma_diff)( elem ) ) );
                            buffer.push_back( ( ::NS(SCCoasting_enabled)(
                                elem ) ) ? T{ 1. } : T{ 0. } );
                        }

                        break;
                    }

                    case ::NS(COBJECTS_TYPE_ID_SC_QGAUSSIAN_PROFILE):
                    {
                        auto elem = ::NS(SCQGaussProfile_const_from_cobj_index)(
                            it );

                        if( elem != nullptr )
                        {
                            buffer.push_back( static_cast< T >(
                                ::NS(SCQGaussProfile_number_of_particles)(
                                    elem ) ) );

                            buffer.push_back( static_cast< T >(
                                ::NS(SCQGaussProfile_bunchlength_rms)(
                                    elem ) ) );
                            buffer.push_back( static_cast< T >(
                                ::NS(SCQGaussProfile_sigma_x)( elem ) ) );
                            buffer.push_back( static_cast< T >(
                                ::NS(SCQGaussProfile_sigma_y)( elem ) ) );
                            buffer.push_back( static_cast< T >(
                                ::NS(SCQGaussProfile_length)( elem ) ) );
                            buffer.push_back( static_cast< T >(
                                ::NS(SCQGaussProfile_x_co)( elem ) ) );
                            buffer.push_back( static_cast< T >(
                                ::NS(SCQGaussProfile_y_co)( elem ) ) );
                            buffer.push_back( static_cast< T >(
                                ::NS(SCQGaussProfile_min_sigma_diff)( elem ) ) );
                            buffer.push_back( static_cast< T >(
                                ::NS(SCQGaussProfile_q_param)( elem ) ) );
                            buffer.push_back( ( ::NS(SCQGaussProfile_enabled)(
                                elem ) ) ? T{ 1. } : T{ 0. } );
                        }

                        break;
                    }

                    default:
                    {
                        status = st::STATUS_GENERAL_FAILURE;
                    }
                };


                if( ( status != st::STATUS_SUCCESS ) ||
                    ( cur_num_slots + elem_num_slots != buffer.size() ) )
                {
                    buffer.clear();
                }
            }
        }

        return buffer.size();
    }
}
#endif /* C++, Host */
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */
