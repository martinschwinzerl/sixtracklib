#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles/particles.h"
    #include "sixtracklib/common/cobjects/cbuffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particles) const*
NS(Particles_const_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT b,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT {
    return NS(Particles_const_from_cbuffer)( b, idx ); }

SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particles)* NS(Particles_from_cbuffer_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(cobj_size_type) const idx ) SIXTRL_NOEXCEPT {
    return NS(Particles_from_cbuffer)( buffer, idx ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

bool NS(Particles_cbuffer_can_be_added_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer,
    NS(particles_num_type) const max_num_particles,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_buffer_size,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_slots,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_objects,
    SIXTRL_ARGPTR_DEC NS(cobj_size_type)* SIXTRL_RESTRICT ptr_requ_dataptrs
) SIXTRL_NOEXCEPT { return NS(Particles_cbuffer_can_be_added)(
    buffer, max_num_particles, ptr_requ_buffer_size, ptr_requ_slots,
        ptr_requ_objects, ptr_requ_dataptrs ); }

SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particles)* NS(Particles_cbuffer_new_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(particles_num_type) const max_num_particles ) {
    return NS(Particles_cbuffer_new)( buffer, max_num_particles ); }

SIXTRL_CBUFFER_OBJ_DATAPTR_DEC NS(Particles)* NS(Particles_cbuffer_add_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    NS(particles_num_type) const max_num_particles,
    NS(particles_num_type) const num_particles,
    NS(particles_real_const_pointer)  charge0_ptr,
    NS(particles_real_const_pointer)  mass0_ptr,
    NS(particles_real_const_pointer)  beta0_ptr,
    NS(particles_real_const_pointer)  gamma0_ptr,
    NS(particles_real_const_pointer)  p0c_ptr,
    NS(particles_real_const_pointer)  s_ptr,
    NS(particles_real_const_pointer)  x_ptr,
    NS(particles_real_const_pointer)  y_ptr,
    NS(particles_real_const_pointer)  px_ptr,
    NS(particles_real_const_pointer)  py_ptr,
    NS(particles_real_const_pointer)  zeta_ptr,
    NS(particles_real_const_pointer)  psigma_ptr,
    NS(particles_real_const_pointer)  delta_ptr,
    NS(particles_real_const_pointer)  rpp_ptr,
    NS(particles_real_const_pointer)  rvv_ptr,
    NS(particles_real_const_pointer)  chi_ptr,
    NS(particles_real_const_pointer)  charge_ratio_ptr,
    NS(particles_index_const_pointer) id_ptr,
    NS(particles_index_const_pointer) at_element_ptr,
    NS(particles_index_const_pointer) at_turn_ptr,
    NS(particles_index_const_pointer) state_ptr ) {
    return NS(Particles_cbuffer_add)( buffer, max_num_particles, num_particles,
        charge0_ptr, mass0_ptr, beta0_ptr, gamma0_ptr, p0c_ptr,
            s_ptr, x_ptr, y_ptr, px_ptr, py_ptr, zeta_ptr, psigma_ptr, delta_ptr,
                rpp_ptr, rvv_ptr, chi_ptr, charge_ratio_ptr, id_ptr,
                    at_element_ptr, at_turn_ptr, state_ptr ); }

SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* NS(Particles_cbuffer_add_copy_ext)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT pset ) {
    return NS(Particles_cbuffer_add_copy)( buffer, pset ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

void NS(Particles_difference_max_value_ext)(
    SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT destination,
    SIXTRL_PARTICLES_ARGPTR_DEC NS(particles_num_type)*
        SIXTRL_RESTRICT max_value_index,
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const
        SIXTRL_RESTRICT src ) SIXTRL_NOEXCEPT {
    NS(Particles_difference_max_value)( destination, max_value_index, src ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

NS(cobj_obj_id_type) NS(Particles_cobj_type_id_ext)( void ) SIXTRL_NOEXCEPT {
    return NS(Particles_cobj_type_id)(); }

NS(cobj_size_type) NS(Particles_cobj_num_dataptrs_ext)( void ) SIXTRL_NOEXCEPT {
    return NS(Particles_cobj_num_dataptrs)(); }

NS(cobj_size_type) NS(Particles_cobj_actual_handle_size_ext)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
        return NS(Particles_cobj_actual_handle_size)( slot_size ); }

NS(cobj_size_type) NS(Particles_cobj_reserved_handle_size_ext)(
    NS(cobj_size_type) slot_size ) SIXTRL_NOEXCEPT {
        return NS(Particles_cobj_reserved_handle_size)( slot_size ); }

NS(size_type) NS(Particles_cobj_required_num_bytes_ext)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p,
    NS(size_type) slot_size ) SIXTRL_NOEXCEPT {
    return NS(Particles_cobj_required_num_bytes)( p, slot_size ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_PARTICLES_ARGPTR_DEC NS(Particles)*
NS(Particles_preset_ext)( SIXTRL_PARTICLES_ARGPTR_DEC
    NS(Particles)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    return NS(Particles_preset)( p ); }

NS(status_type) NS(Particles_clear_ext)( SIXTRL_PARTICLES_ARGPTR_DEC
    NS(Particles)* SIXTRL_RESTRICT p ) SIXTRL_NOEXCEPT {
    return NS(Particles_clear)( p ); }

NS(particles_num_type) NS(Particles_max_num_particles_ext)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return NS(Particles_max_num_particles)( p ); }

NS(particles_num_type) NS(Particles_num_particles_ext)(
    SIXTRL_PARTICLES_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT p
) SIXTRL_NOEXCEPT { return NS(Particles_num_particles)( p ); }

/* -------------------------------------------------------------------------- */

bool NS(CObjIndex_range_contains_particle_set_ext)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* SIXTRL_RESTRICT begin,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* SIXTRL_RESTRICT end
) SIXTRL_NOEXCEPT {
    return NS(CObjIndex_range_contains_particle_set)( begin, end ); }

NS(size_type) NS(CObjIndex_range_total_num_particle_sets_ext)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* SIXTRL_RESTRICT begin,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* SIXTRL_RESTRICT end
) SIXTRL_NOEXCEPT {
    return NS(CObjIndex_range_total_num_particle_sets)( begin, end ); }

NS(particles_num_type) NS(CObjIndex_range_total_num_individual_particles_ext)(
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* SIXTRL_RESTRICT begin,
    SIXTRL_CBUFFER_OBJ_ARGPTR_DEC NS(CObjIndex) const* SIXTRL_RESTRICT end
) SIXTRL_NOEXCEPT {
    return NS(CObjIndex_range_total_num_individual_particles)( begin, end ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

bool NS(CObjFlatBuffer_contains_particle_set_ext)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT begin,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(CObjFlatBuffer_contains_particle_set)( begin, slot_size ); }

NS(size_type) NS(CObjFlatBuffer_total_num_particle_sets_ext)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(CObjFlatBuffer_total_num_particle_sets)( buffer, slot_size ); }

NS(particles_num_type) NS(CObjFlatBuffer_total_num_individual_particles_ext)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(CObjFlatBuffer_total_num_individual_particles)(
        buffer, slot_size ); }

bool NS(CObjFlatBuffer_is_particle_set_buffer_ext)(
    SIXTRL_CBUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(size_type) const slot_size ) SIXTRL_NOEXCEPT {
    return NS(CObjFlatBuffer_is_particle_set_buffer)( buffer, slot_size ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

bool NS(CBuffer_is_particle_set_buffer)( SIXTRL_CBUFFER_ARGPTR_DEC
    const NS(CBuffer) *const SIXTRL_RESTRICT buffer ) SIXTRL_NOEXCEPT {
    return NS(CObjIndex_range_contains_particle_set)(
        NS(CBuffer_const_objects_begin)( buffer ),
        NS(CBuffer_const_objects_end)( buffer ) ); }

NS(size_type) NS(CBuffer_num_particle_sets)( SIXTRL_CBUFFER_ARGPTR_DEC
    const NS(CBuffer) *const SIXTRL_RESTRICT buffer ) SIXTRL_NOEXCEPT {
    return NS(CObjIndex_range_total_num_particle_sets)(
        NS(CBuffer_const_objects_begin)( buffer ),
        NS(CBuffer_const_objects_end)( buffer ) ); }

NS(particles_num_type) NS(CBuffer_num_individual_particles)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT buffer
) SIXTRL_NOEXCEPT {
    return NS(CObjIndex_range_total_num_individual_particles)(
        NS(CBuffer_const_objects_begin)( buffer ),
        NS(CBuffer_const_objects_end)( buffer ) ); }

/* ------------------------------------------------------------------------- */

static NS(status_type) NS(Particles_id_recursive_merge_sort)(
    NS(particle_index_type)* SIXTRL_RESTRICT particle_id_array,
    NS(particle_index_type)* SIXTRL_RESTRICT lhs_temp_array,
    NS(particle_index_type)* SIXTRL_RESTRICT rhs_temp_array,
    NS(particles_num_type) const left_index,
    NS(particles_num_type) const right_index );

static NS(status_type) NS(Particles_id_merge_and_check_duplicates)(
    NS(particle_index_type)* SIXTRL_RESTRICT particle_id_array,
    NS(particle_index_type)* SIXTRL_RESTRICT lhs_temp_array,
    NS(particle_index_type)* SIXTRL_RESTRICT rhs_temp_array,
    NS(particles_num_type) const lhs_begin_index,
    NS(particles_num_type) const lhs_end_index,
    NS(particles_num_type) const rhs_end_index );

/* ------------------------------------------------------------------------- */

NS(status_type) NS(Particles_id_merge_and_check_duplicates)(
    NS(particle_index_type)* SIXTRL_RESTRICT particle_id_array,
    NS(particle_index_type)* SIXTRL_RESTRICT lhs_temp_array,
    NS(particle_index_type)* SIXTRL_RESTRICT rhs_temp_array,
    NS(particles_num_type) const lhs_begin_index,
    NS(particles_num_type) const lhs_end_index,
    NS(particles_num_type) const rhs_end_index )
{
    typedef NS(particles_num_type) npart_type;
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;

    npart_type ii = ( npart_type )0u;
    npart_type jj = lhs_begin_index;
    npart_type kk = lhs_begin_index;

    npart_type const lhs_num = lhs_end_index - lhs_begin_index;
    npart_type const rhs_num = rhs_end_index - lhs_end_index;

    SIXTRL_ASSERT( lhs_temp_array    != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( rhs_temp_array    != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( particle_id_array != SIXTRL_NULLPTR );

    SIXTRL_ASSERT( lhs_begin_index >= ( npart_type )0u );
    SIXTRL_ASSERT( lhs_end_index   >= lhs_begin_index );
    SIXTRL_ASSERT( rhs_end_index   >= lhs_end_index   );

    for( ; jj < lhs_end_index ; ++jj, ++ii )
    {
        lhs_temp_array[ ii ] = particle_id_array[ jj ];
    }

    jj = lhs_end_index;
    ii = ( npart_type )0u;

    for(  ; jj < rhs_end_index ; ++jj, ++ii )
    {
        rhs_temp_array[ ii ] = particle_id_array[ jj ];
    }

    ii = ( npart_type )0u;
    jj = ( npart_type )0u;

    while( ( ii < lhs_num ) && ( jj < rhs_num ) )
    {
        if( lhs_temp_array[ ii ] < rhs_temp_array[ jj ] )
        {
            particle_id_array[ kk ] = lhs_temp_array[ ii ];
            ++ii;
        }
        else if( lhs_temp_array[ ii ] > rhs_temp_array[ jj ] )
        {
            particle_id_array[ kk ] = rhs_temp_array[ jj ];
            ++jj;
        }
        else
        {
            SIXTRL_ASSERT( lhs_temp_array[ ii ] == rhs_temp_array[ jj ] );
            status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
            break;
        }

        ++kk;
    };

    if( ( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) &&
        ( ii < lhs_num ) )
    {
        while( ii < lhs_num )
        {
            particle_id_array[ kk++ ] = lhs_temp_array[ ii++ ];
        };
    }

    if( ( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS ) &&
        ( jj < rhs_num ) )
    {
        while( jj < rhs_num )
        {
            particle_id_array[ kk++ ] = rhs_temp_array[ jj++ ];
        };
    }

    return status;
}

NS(status_type) NS(Particles_id_recursive_merge_sort)(
    NS(particle_index_type)* SIXTRL_RESTRICT particle_id_array,
    NS(particle_index_type)* SIXTRL_RESTRICT lhs_temp_array,
    NS(particle_index_type)* SIXTRL_RESTRICT rhs_temp_array,
    NS(particles_num_type) const left_index,
    NS(particles_num_type) const right_index )
{
    typedef NS(particles_num_type) npart_type;
    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;

    SIXTRL_ASSERT( particle_id_array != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( lhs_temp_array    != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( rhs_temp_array    != SIXTRL_NULLPTR );

    if( left_index < right_index )
    {
        npart_type const mid_index =
            left_index + ( right_index - left_index ) / 2;

        npart_type const mid_p1_index = mid_index + ( npart_type )1;

        if( ( 0 == NS(Particles_id_recursive_merge_sort)(
                particle_id_array, lhs_temp_array, rhs_temp_array,
                left_index, mid_index ) ) &&
            ( 0 == NS(Particles_id_recursive_merge_sort)(
                particle_id_array, lhs_temp_array, rhs_temp_array,
                mid_p1_index, right_index ) ) )
        {
            status = NS(Particles_id_merge_and_check_duplicates)(
                particle_id_array, lhs_temp_array, rhs_temp_array,
                left_index, mid_p1_index, right_index + ( npart_type )1u );
        }
    }
    else if( left_index == right_index ) status = 0;
    return status;
}

NS(status_type) NS(Particles_sort_and_find_min_max_id)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT particles,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_min_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_max_id )
{
    typedef NS(particles_num_type)  npart_type;
    typedef NS(particle_index_type) index_t;

    NS(status_type) status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
    NS(size_type) const num_particles = NS(Particles_num_particles)( particles );

    if( num_particles > ( npart_type )0u )
    {
        NS(size_type) const buffer_size = sizeof( npart_type ) * num_particles;

        npart_type* particle_id_array = ( npart_type* )malloc( buffer_size );
        npart_type* lhs_temp_array    = ( npart_type* )malloc( buffer_size );
        npart_type* rhs_temp_array    = ( npart_type* )malloc( buffer_size );

        if( ( buffer_size > ( NS(size_type) )0u ) &&
            ( particle_id_array != SIXTRL_NULLPTR ) &&
            ( lhs_temp_array    != SIXTRL_NULLPTR ) &&
            ( rhs_temp_array    != SIXTRL_NULLPTR ) )
        {
            npart_type ii = ( npart_type )0u;

            for( ; ii < num_particles ; ++ii )
            {
                index_t const temp_particle_id = NS(Particles_id)( particles, ii );

                lhs_temp_array[ ii ]    = ( npart_type )0u;
                rhs_temp_array[ ii ]    = ( npart_type )0u;
                particle_id_array[ ii ] = ( temp_particle_id >= ( index_t )0u )
                        ? ( npart_type )(  temp_particle_id )
                        : ( npart_type )( -temp_particle_id );
            }

            status = NS(Particles_id_recursive_merge_sort)(
                particle_id_array, lhs_temp_array, rhs_temp_array,
                ( npart_type )0u, num_particles - ( npart_type )1u );
        }

        #if !defined( NDEBUG )
        if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
        {
            npart_type ii = ( npart_type )0u;
            npart_type jj = ( npart_type )1u;

            for( ; jj < num_particles ; ++ii, ++jj )
            {
                if( particle_id_array[ ii ] >= particle_id_array[ jj ] )
                {
                    status = ( NS(status_type) )SIXTRL_STATUS_GENERAL_FAILURE;
                    break;
                }
            }
        }
        #endif /* !defined( NDEBUG ) */

        if( status == ( NS(status_type) )SIXTRL_STATUS_SUCCESS )
        {
            if( ptr_max_id != SIXTRL_NULLPTR )
            {
                *ptr_max_id = ( index_t )particle_id_array[
                    num_particles - ( npart_type )1u ];
            }

            if( ptr_min_id != SIXTRL_NULLPTR )
            {
                *ptr_min_id = ( index_t )particle_id_array[ 0 ];
            }
        }

        free( particle_id_array );
        free( lhs_temp_array );
        free( rhs_temp_array );

        particle_id_array = SIXTRL_NULLPTR;
        lhs_temp_array    = SIXTRL_NULLPTR;
        rhs_temp_array    = SIXTRL_NULLPTR;
    }

    return status;
}

void NS(Particles_find_min_max_attributes_ext)(
    SIXTRL_PARTICLE_ARGPTR_DEC const NS(Particles) *const SIXTRL_RESTRICT pset,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_min_part_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_max_part_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_min_element_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_max_element_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_min_turn_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_max_turn_id )
{
    NS(Particles_find_min_max_attributes)( pset, ptr_min_part_id,
        ptr_max_part_id, ptr_min_element_id, ptr_max_element_id,
            ptr_min_turn_id, ptr_max_turn_id );
}

void NS(Particles_cbuffer_find_min_max_attributes_in_particle_sets)(
    SIXTRL_CBUFFER_ARGPTR_DEC const NS(CBuffer) *const SIXTRL_RESTRICT pbuffer,
    NS(size_type) const  num_particle_sets,
    SIXTRL_ARGPTR_DEC NS(size_type) const* SIXTRL_RESTRICT indices_begin,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_min_part_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_max_part_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_min_element_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_max_element_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_min_turn_id,
    SIXTRL_ARGPTR_DEC NS(particle_index_type)* SIXTRL_RESTRICT ptr_max_turn_id )
{
    NS(Particles_cobj_flat_buffer_find_min_max_attributes_in_particle_sets)(
        NS(CBuffer_p_const_base)( pbuffer ), NS(CBuffer_slot_size)( pbuffer ),
            num_particle_sets, indices_begin, ptr_min_part_id, ptr_max_part_id,
                ptr_min_element_id, ptr_max_element_id, ptr_min_turn_id,
                    ptr_max_turn_id ); }

