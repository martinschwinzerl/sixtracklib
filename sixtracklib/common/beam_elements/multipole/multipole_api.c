#include "sixtracklib/common/beam_elements/multipole/multipole_api.h"
#include "sixtracklib/common/beam_elements/multipole/multipole.h"
#include "sixtracklib/common/beam_elements/multipole/buffer.h"

bool NS(Multipole_can_be_added)(
    SIXTRL_BE_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    NS(multipole_order_t) const order,
    SIXTRL_BE_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_objects,
    SIXTRL_BE_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_slots,
    SIXTRL_BE_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_dataptrs )
{
    typedef NS(buffer_size_t) buf_size_t;

    buf_size_t const bal_size = ( buf_size_t )2u + ( ( order >= 0 )
        ? ( buf_size_t )2u * order : ( buf_size_t )0u );

    buf_size_t const num_dataptrs = ( buf_size_t )1u;
    buf_size_t const sizes[]  = { sizeof( NS(multipole_real_t) ) };
    buf_size_t const counts[] = { bal_size };

    return NS(Buffer_can_add_object)( buffer, sizeof( NS(Multipole) ),
            num_dataptrs, sizes, counts, ptr_requ_objects, ptr_requ_slots,
                ptr_requ_dataptrs );
}


SIXTRL_BUFFER_DATAPTR_DEC NS(Multipole)* NS(Multipole_new)(
    SIXTRL_BE_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(multipole_order_t) const order )
{
    typedef NS(Multipole)                       elem_t;
    typedef NS(buffer_size_t)                   buf_size_t;
    typedef SIXTRL_BE_ARGPTR_DEC elem_t*        ptr_to_elem_t;
    typedef SIXTRL_BE_ARGPTR_DEC NS(Object)*    ptr_to_obj_t;
    typedef NS(multipole_real_t)                real_t;

    ptr_to_obj_t ptr_obj = SIXTRL_NULLPTR;
    buf_size_t const obj_size = sizeof( elem_t );

    NS(object_type_id_t) const type_id = NS(OBJECT_TYPE_MULTIPOLE);

    elem_t temp_obj;

    temp_obj.order    = order;
    temp_obj.length   = ( real_t )0.0;
    temp_obj.hxl      = ( real_t )0.0;
    temp_obj.hyl      = ( real_t )0.0;
    temp_obj.bal_addr = 0u;

    if( order >= ( NS(multipole_order_t) )0 )
    {
        buf_size_t const bal_size     = ( buf_size_t )( 2 * order + 2 );
        buf_size_t const num_dataptrs = ( buf_size_t )1u;

        buf_size_t const offsets[]    = { offsetof( elem_t, bal_addr ) };
        buf_size_t const sizes[]      = { sizeof( real_t ) };
        buf_size_t const counts[]     = { bal_size };

        SIXTRL_ASSERT( num_dataptrs == ( buf_size_t )1u );

        ptr_obj = NS(Buffer_add_object)( buffer, &temp_obj, obj_size , type_id,
                num_dataptrs, offsets, sizes, counts );
    }
    else
    {
        buf_size_t const num_dataptrs = ( buf_size_t )0u;

        ptr_obj = NS(Buffer_add_object)( buffer, &temp_obj, obj_size , type_id,
                num_dataptrs, SIXTRL_NULLPTR, SIXTRL_NULLPTR, SIXTRL_NULLPTR );
    }

    return ( ptr_to_elem_t )( uintptr_t )NS(Object_get_begin_addr)( ptr_obj );
}

SIXTRL_BUFFER_DATAPTR_DEC NS(Multipole)* NS(Multipole_add)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(multipole_order_t) const order,
    SIXTRL_BUFFER_DATAPTR_DEC NS(multipole_real_t) const*
        SIXTRL_RESTRICT ptr_to_bal,
    NS(multipole_real_t)  const length,
    NS(multipole_real_t)  const hxl,
    NS(multipole_real_t)  const hyl )
{
    typedef NS(Multipole)                               elem_t;
    typedef NS(buffer_size_t)                           buf_size_t;
    typedef SIXTRL_ARGPTR_DEC elem_t*                   ptr_to_elem_t;
    typedef SIXTRL_ARGPTR_DEC NS(Object)*               ptr_to_obj_t;
    typedef SIXTRL_ARGPTR_DEC NS(multipole_real_t )*    ptr_to_bal_t;

    SIXTRL_STATIC_VAR NS(multipole_order_t) const INV_ORDER =
        ( NS(multipole_order_t) )-1;

    ptr_to_obj_t ptr_obj = SIXTRL_NULLPTR;
    buf_size_t const obj_size = sizeof( elem_t );

    NS(object_type_id_t) const type_id = NS(OBJECT_TYPE_MULTIPOLE);

    elem_t temp_obj;
    NS(Multipole_set_length)( &temp_obj, length );
    NS(Multipole_set_hxl)(    &temp_obj, hxl );
    NS(Multipole_set_hyl)(    &temp_obj, hyl );

    if( order > INV_ORDER )
    {
        buf_size_t const num_dataptrs = ( buf_size_t )1u;

        buf_size_t const offsets[] =
        {
            offsetof( elem_t, bal_addr )
        };

        buf_size_t const sizes[] =
        {
            sizeof( NS(multipole_real_t) )
        };

        buf_size_t const counts[] =
        {
            ( buf_size_t )( 2 * order + 2 )
        };

        if( ptr_to_bal != SIXTRL_NULLPTR )
        {
            NS(Multipole_assign_bal)(
                &temp_obj, order, ( ptr_to_bal_t )ptr_to_bal );
        }
        else
        {
            NS(Multipole_assign_bal)( &temp_obj, INV_ORDER, SIXTRL_NULLPTR );
            NS(Multipole_set_order)( &temp_obj, order );
        }

        SIXTRL_ASSERT( num_dataptrs == ( buf_size_t )1u );

        ptr_obj = NS(Buffer_add_object)( buffer, &temp_obj, obj_size , type_id,
            num_dataptrs, offsets, sizes, counts );
    }
    else
    {
        buf_size_t const num_dataptrs = ( buf_size_t )0u;
        NS(Multipole_assign_bal)( &temp_obj, INV_ORDER, SIXTRL_NULLPTR );

        ptr_obj = NS(Buffer_add_object)( buffer, &temp_obj, obj_size, type_id,
            num_dataptrs, SIXTRL_NULLPTR, SIXTRL_NULLPTR, SIXTRL_NULLPTR );
    }

    SIXTRL_ASSERT( NS(Multipole_get_order)( &temp_obj ) == order );

    return ( ptr_to_elem_t )( uintptr_t )NS(Object_get_begin_addr)( ptr_obj );
}

SIXTRL_BUFFER_DATAPTR_DEC NS(Multipole)* NS(Multipole_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BE_ARGPTR_DEC const NS(Multipole) *const SIXTRL_RESTRICT multipole )
{
    return NS(Multipole_add)( buffer,
        NS(Multipole_get_order)( multipole ),
        NS(Multipole_get_const_bal)( multipole ),
        NS(Multipole_get_length)( multipole ),
        NS(Multipole_get_hxl)( multipole ),
        NS(Multipole_get_hyl)( multipole ) );
}

/* end: sixtracklib/common/beam_elements/multipole/multipole_api.c */
