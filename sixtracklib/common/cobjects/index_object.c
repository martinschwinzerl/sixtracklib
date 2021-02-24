#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/index_object.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

void NS(CObjIndex_fprint_slots)( FILE* SIXTRL_RESTRICT fp,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const SIXTRL_RESTRICT
        index_obj, NS(cobj_size_type) const num_slots_to_print )
{
    typedef SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(cobj_addr_type) const*
            addr_pointer_type;

    NS(cobj_obj_id_type) const type_id = NS(CObjIndex_type_id)( index_obj );
    NS(cobj_size_type) const slot_size = ( NS(cobj_size_type)
        )SIXTRL_CBUFFER_DEFAULT_SLOT_SIZE;

    NS(cobj_size_type) const obj_size  = NS(CObjIndex_size)( index_obj );
    NS(cobj_size_type) const num_slots = obj_size / slot_size;
    addr_pointer_type ptr_slots  = ( addr_pointer_type )( uintptr_t
        )NS(CObjIndex_begin_addr)( index_obj );

    NS(cobj_size_type) ii = ( NS(cobj_size_type) )0u;
    NS(cobj_size_type) nn = num_slots;

    if( fp == SIXTRL_NULLPTR ) return;

    if( ( num_slots_to_print > ( NS(cobj_size_type) )0u ) &&
        ( num_slots_to_print < num_slots ) ) {
        nn = num_slots_to_print; }

    fprintf( fp, "type_id            : %8d\r\n", ( int )type_id );
    fprintf( fp, "obj size           : %8d\r\n", ( int )obj_size );
    fprintf( fp, "num_slots          : %8d\r\n", ( int )num_slots );
    fprintf( fp, "num_slots to print : %8d\r\n", ( int )nn );

    for( ; ii < nn ; ++ii )
    {
        if( ii < ( NS(cobj_size_type) )21u )
        {
            fprintf( fp, "slot_id = %8lu | slot addr = %20lu "
                    "| slot_value = %20lu\r\n",
                    ( unsigned long )ii, ( unsigned long )&ptr_slots[ ii ],
                    ( unsigned long )ptr_slots[ ii ] );
        }
        else
        {
            fprintf( fp, "slot_id = %8lu | slot addr = %20lu "
                    "| slot_value = %+19.12f\r\n",
                    ( unsigned long )ii, ( unsigned long )&ptr_slots[ ii ],
                    *( ( SIXTRL_CBUFFER_OBJ_DATAPTR_DEC double const*
                        )&ptr_slots[ ii ] ) );
        }
    }
}

bool NS(CObjIndex_is_consistent_with_type_ext)(
    NS(cobj_obj_index_const_pointer) SIXTRL_RESTRICT obj,
    NS(cobj_obj_id_type) const requ_type_id,
    NS(cobj_size_type) const min_size ) SIXTRL_NOEXCEPT { return
        NS(CObjIndex_is_consistent_with_type)( obj, requ_type_id, min_size ); }

NS(cobj_addr_type) NS(CObjIndex_begin_addr_filter_by_type_info_ext)(
    NS(cobj_obj_index_const_pointer) SIXTRL_RESTRICT obj,
    NS(cobj_obj_id_type) const requ_type_id,
    NS(cobj_size_type) const min_size, NS(cobj_size_type) const slot_size
) SIXTRL_NOEXCEPT { return NS(CObjIndex_begin_addr_filter_by_type_info)(
        obj, requ_type_id, min_size, slot_size ); }
