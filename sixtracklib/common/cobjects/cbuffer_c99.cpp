#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/cbuffer.h"
    #include "sixtracklib/common/internal/file_tools.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cstdio>
    #include <memory>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( __cplusplus )

::NS(cobj_status_type) NS(CBuffer_init_as_buffer)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    ::NS(cobj_size_type) const capacity ) {
    return NS(CBuffer_init_as_buffer_detailed)( buffer, capacity,
        ::NS(cobj_size_type){ 0 }, ::NS(cobj_size_type){ 0 },
        ::NS(cobj_size_type){ 0 }, ::NS(cobj_size_type){ 0 },
        ::NS(CBUFFER_DEFAULT_SLOT_SIZE),
        ::NS(CBUFFER_FLAGS_ALLOW_REMAPPING) |
        ::NS(CBUFFER_FLAGS_ALLOW_ALLOC) |
        ::NS(CBUFFER_FLAGS_ALLOW_REALLOC) |
        ::NS(CBUFFER_FLAGS_ALLOW_APPEND) |
        ::NS(CBUFFER_FLAGS_OWNS_STORED_DATA) |
        ::NS(CBUFFER_FLAGS_FORCE_INIT) ); }

::NS(cobj_status_type) NS(CBuffer_init_as_buffer_detailed)(
    SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer)* SIXTRL_RESTRICT buffer,
    ::NS(cobj_size_type) const capacity,
    ::NS(cobj_size_type) const max_num_slots,
    ::NS(cobj_size_type) const max_num_objects,
    ::NS(cobj_size_type) const max_num_pointers,
    ::NS(cobj_size_type) const max_num_garbage_ranges,
    ::NS(cobj_size_type) const slot_size,
    ::NS(cobj_buffer_flags_type) flags )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    typedef ::NS(cobj_size_type) st_size_t;
    typedef ::NS(cobj_status_type) st_status_t;
    typedef ::NS(cobj_addr_type) st_addr_t;

    st_status_t status = st::STATUS_GENERAL_FAILURE;
    if( ( buffer != SIXTRL_NULLPTR ) && ( slot_size > st_size_t{ 0 } ) ) {
        SIXTRL_ARGPTR_DEC st_size_t effective_capacity = capacity;
        SIXTRL_ARGPTR_DEC st_size_t requ_capacity =
            ::NS(CObjFlatBuffer_predict_required_buffer_size)( max_num_slots,
                max_num_objects, max_num_pointers, max_num_garbage_ranges,
                    slot_size );

        if( effective_capacity < requ_capacity )
            effective_capacity = requ_capacity;

        if( effective_capacity < ::NS(CBuffer_min_buffer_size)( slot_size ) )
            effective_capacity = ::NS(CBuffer_min_buffer_size)( slot_size );

        if( ( ::NS(CBuffer_owns_stored_data)( buffer ) ) &&
            ( ::NS(CBuffer_p_const_base_begin)( buffer ) != nullptr ) )
        {
            if( !::NS(CObjFlatBuffer_has_cbuffer_structure)(
                ::NS(CBuffer_p_base)( buffer ), st_size_t{ 0 }, slot_size ) )
            {
                requ_capacity = effective_capacity;

                status = ::NS(CObjFlatBuffer_init_empty_detailed)(
                    ::NS(CBuffer_p_base)( buffer ), requ_capacity, slot_size,
                        max_num_slots, max_num_objects, max_num_pointers,
                            max_num_garbage_ranges, &effective_capacity );
            }
            else
            {
                status = ::NS(CBuffer_allocate)( buffer, max_num_slots,
                    max_num_objects, max_num_pointers, max_num_garbage_ranges );
            }
        }
        else
        {
            st_addr_t datastore_addr = st::COBJECTS_NULL_ADDRESS;
            st_addr_t base_addr = st::COBJECTS_NULL_ADDRESS;

            if( ::NS(CBuffer_owns_stored_data)( buffer ) )
            {
               ::NS(CBuffer_free)( buffer );
            }

            if( ::NS(CBuffer_is_buffer_flag_set_detailed)(
                 flags, st::CBUFFER_FLAGS_STORAGE_IS_CXX_VECTOR ) )
            {
                datastore_addr = ::NS(CBuffer_init_cxx_vector_store)(
                    &effective_capacity, slot_size );
            }
            else
            {
                flags &= ~( st::CBUFFER_FLAGS_STORAGE_IS_CXX_VECTOR );
                flags |=    st::CBUFFER_FLAGS_STORAGE_IS_C_PTR;

                datastore_addr = ::NS(CBuffer_init_c99_ptr_store)(
                    &effective_capacity, slot_size );
            }

            if( ( datastore_addr != st::COBJECTS_NULL_ADDRESS ) &&
                ( effective_capacity >= capacity ) &&
                ( effective_capacity >= requ_capacity ) )
            {
                requ_capacity = effective_capacity;
                base_addr = ::NS(CObjFlatBuffer_aligned_base_addr)(
                    datastore_addr, requ_capacity, slot_size,
                        &effective_capacity, slot_size );

                requ_capacity = effective_capacity;

                if( base_addr != st::COBJECTS_NULL_ADDRESS )
                {
                    if( ::NS(CBuffer_is_buffer_flag_set_detailed)( flags,
                        st::CBUFFER_FLAGS_FORCE_INIT ) )
                    {
                        SIXTRL_ARGPTR_DEC NS(cobj_size_type) buffer_size =
                            ( NS(cobj_size_type) )0u;

                        status = ::NS(CObjFlatBuffer_init_empty_detailed)(
                            ( SIXTRL_CBUFFER_DATAPTR_DEC unsigned char* )(
                                uintptr_t )base_addr, requ_capacity, slot_size,
                                    max_num_slots, max_num_objects,
                                        max_num_pointers, max_num_garbage_ranges,
                                            &buffer_size );

                        SIXTRL_ASSERT( ( status != st::STATUS_SUCCESS ) ||
                            ( ( buffer_size <= effective_capacity ) &&
                              ( buffer_size >= ::NS(CBuffer_min_buffer_size)(
                                slot_size ) ) ) );

                        ( void )buffer_size;
                    }
                    else
                    {
                        status = st::STATUS_SUCCESS;
                    }
                }
            }

            if( ( status == st::STATUS_SUCCESS ) &&
                ( base_addr != st::COBJECTS_NULL_ADDRESS ) &&
                ( datastore_addr != st::COBJECTS_NULL_ADDRESS ) &&
                ( effective_capacity >= capacity ) )
            {
                buffer->m_datastore_addr = datastore_addr;
                buffer->m_base_addr = base_addr;
                buffer->m_capacity = effective_capacity;
                buffer->m_slot_size = slot_size;
                buffer->m_buffer_flags = flags;
            }

            if( ( status != st::STATUS_SUCCESS ) &&
                ( datastore_addr != st::COBJECTS_NULL_ADDRESS ) )
            {
                if( ::NS(CBuffer_is_buffer_flag_set_detailed)(
                    flags, st::CBUFFER_FLAGS_STORAGE_IS_CXX_VECTOR ) )
                {
                    ::NS(CBuffer_free_cxx_vector_store)( datastore_addr );
                    datastore_addr = st::COBJECTS_NULL_ADDRESS;
                }
                else if( ::NS(CBuffer_is_buffer_flag_set_detailed)(
                          flags, st::CBUFFER_FLAGS_STORAGE_IS_C_PTR ) )
                {
                    ::NS(CBuffer_free_c99_ptr_store)( datastore_addr );
                    datastore_addr = st::COBJECTS_NULL_ADDRESS;
                }

                SIXTRL_ASSERT( datastore_addr == st::COBJECTS_NULL_ADDRESS );
            }
        }
    }

    return status;
}

::NS(cobj_status_type) NS(CBuffer_init_from_file)(
    SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC char const* SIXTRL_RESTRICT path_to_file ) SIXTRL_NOEXCEPT
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    typedef st::cobj_size_type st_size_t;

    st::cobj_status_type status = st::STATUS_GENERAL_FAILURE;

    if( ( path_to_file == nullptr ) || ( buffer == nullptr ) ) return status;

    std::unique_ptr< ::FILE, decltype( &std::fclose ) > fp(
        std::fopen( path_to_file, "rb" ), &std::fclose );

    if( ( buffer != nullptr ) && ( fp.get() != nullptr ) )
    {
        st_size_t const slot_size = ::NS(CBuffer_slot_size)( buffer );
        st_size_t const required_file_size = st::File_num_bytes(
            path_to_file, ::NS(CBuffer_min_buffer_size)( slot_size ) );

        st_size_t capacity = ::NS(CBuffer_capacity)( buffer );

        if( ( ::NS(CBuffer_p_const_base)( buffer ) != nullptr ) &&
            ( ::NS(CBuffer_slot_size )( buffer ) > st_size_t{ 0 } ) &&
            ( ::NS(CBuffer_p_const_base)( buffer ) != nullptr ) &&
            ( ::NS(CBuffer_allow_allocate)( buffer ) ) &&
            ( ::NS(CBuffer_allow_remap)( buffer ) ) )
        {
            if( capacity >= required_file_size )
            {
                status = st::STATUS_SUCCESS;
            }
            else if( ::NS(CBuffer_owns_stored_data)( buffer ) )
            {
                status = ::NS(CBuffer_reserve)( buffer, required_file_size );
                capacity = ::NS(CBuffer_capacity)( buffer );
            }
        }

        if( ( status == st::STATUS_SUCCESS ) &&
            ( capacity >= required_file_size ) )
        {
            SIXTRL_ASSERT( ::NS(CBuffer_allow_allocate)( buffer ) );
            SIXTRL_ASSERT( ::NS(CBuffer_allow_remap)( buffer ) );
            SIXTRL_ASSERT( capacity == ::NS(CBuffer_capacity)( buffer ) );

            status = st::STATUS_GENERAL_FAILURE;

            auto ret = std::fread( ::NS(CBuffer_p_base)( buffer ),
                sizeof( ::NS(cobj_raw_type) ), required_file_size, fp.get() );

            if( ( ret == required_file_size ) &&
                ( ::NS(CObjFlatBuffer_has_cbuffer_structure)(
                    ::NS(CBuffer_p_const_base)( buffer ), capacity,
                        ::NS(CBuffer_slot_size)( buffer ) ) ) )
            {
                status = ::NS(CBuffer_remap)( buffer );
            }

            if( status != st::STATUS_SUCCESS )
            {
                ::NS(CObjFlatBuffer_init_empty)( ::NS(CBuffer_p_base)( buffer ),
                    ::NS(CBuffer_capacity)( buffer ),
                        ::NS(CBuffer_slot_size)( buffer ) );
            }
        }
    }

    return status;
}

void NS(CBuffer_delete)(
    SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer)* SIXTRL_RESTRICT b ) {
    if( b != SIXTRL_NULLPTR )
    {
        ::NS(CBuffer_free)( b );
        delete( b );
        b = SIXTRL_NULLPTR;
    }
}

SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer)* NS(CBuffer_new_as_view)(
    ::NS(cobj_addr_type) const base_addr, ::NS(cobj_size_type) const capacity )
{
    SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer)* b = NS(CBuffer_preset)(
        new SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer) );
    if( ::NS(cobj_status_type){ SIXTRL_STATUS_SUCCESS } !=
        ::NS(CBuffer_init_as_view)( b, base_addr, capacity ) )
    {
        ::NS(CBuffer_delete)( b );
        b = SIXTRL_NULLPTR;
    }

    return b;
}

SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer)* NS(CBuffer_new_as_view_detailed)(
    ::NS(cobj_addr_type) const base_addr,
    ::NS(cobj_size_type) const slot_size,
    ::NS(cobj_size_type) const capacity,
    ::NS(cobj_buffer_flags_type) const flags )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer)* b = NS(CBuffer_preset)(
        new SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer) );

    if( ::NS(CBuffer_init_as_view_detailed)(
            b, base_addr, slot_size, capacity, flags ) != st::STATUS_SUCCESS ) {
        ::NS(CBuffer_delete)( b );
        b = SIXTRL_NULLPTR; }
    return b;
}

SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer)* NS(CBuffer_new)( void ) {
    namespace st = SIXTRL_CXX_NAMESPACE;
    st::cobj_size_type const slot_size = st::CBUFFER_DEFAULT_SLOT_SIZE;
    st::cobj_buffer_flags_type const buffer_flags =
        st::CBUFFER_FLAGS_ALLOW_REMAPPING  | st::CBUFFER_FLAGS_ALLOW_ALLOC  |
        st::CBUFFER_FLAGS_ALLOW_REALLOC    | st::CBUFFER_FLAGS_ALLOW_APPEND |
        st::CBUFFER_FLAGS_STORAGE_IS_C_PTR | st::CBUFFER_FLAGS_FORCE_INIT;
    return ::NS(CBuffer_new_detailed)(
        ::NS(CBuffer_min_buffer_size)( slot_size ), slot_size, buffer_flags ); }

SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer)* NS(CBuffer_new_with_capacity)(
    ::NS(cobj_size_type) const capacity ) {
    namespace st = SIXTRL_CXX_NAMESPACE;
    st::cobj_buffer_flags_type const buffer_flags =
        st::CBUFFER_FLAGS_ALLOW_REMAPPING | st::CBUFFER_FLAGS_ALLOW_ALLOC  |
        st::CBUFFER_FLAGS_ALLOW_REALLOC   | st::CBUFFER_FLAGS_ALLOW_APPEND |
        st::CBUFFER_FLAGS_FORCE_INIT | st::CBUFFER_FLAGS_STORAGE_IS_C_PTR;
    return ::NS(CBuffer_new_detailed)(
        capacity, st::CBUFFER_DEFAULT_SLOT_SIZE, buffer_flags ); }

SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer)* NS(CBuffer_new_detailed)(
    ::NS(cobj_size_type) capacity, ::NS(cobj_size_type) const slot_size,
    ::NS(cobj_buffer_flags_type) flags ) {
    namespace st = SIXTRL_CXX_NAMESPACE;
    typedef st::cobj_size_type st_size_t;

    SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer)* b = SIXTRL_NULLPTR;

    if( slot_size > st::cobj_size_type{ 0 } )
    {
        flags |= st::CBUFFER_FLAGS_OWNS_STORED_DATA;

        if( !::NS(CBuffer_is_buffer_flag_set_detailed)( flags,
                st::CBUFFER_FLAGS_STORAGE_IS_CXX_VECTOR ) )
            flags |= st::CBUFFER_FLAGS_STORAGE_IS_C_PTR;

        b = ::NS(CBuffer_preset)( new SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer) );

        if( ( b != nullptr ) &&
            ( st::STATUS_SUCCESS != ::NS(CBuffer_init_as_buffer_detailed)(
                b, capacity, st_size_t{ 0 }, st_size_t{ 0 }, st_size_t{ 0 },
                    st_size_t{ 0 }, slot_size, flags ) ) )
        {
            delete b;
            b = nullptr;
        }
    }

    return b;
}

SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer)* NS(CBuffer_new_as_copy)(
    SIXTRL_CBUFFER_ARGPTR_DEC const ::NS(CBuffer) *const SIXTRL_RESTRICT orig ){
    namespace st = SIXTRL_CXX_NAMESPACE;
    return ::NS(CBuffer_new_as_copy_detailed)( orig,
        st::CBUFFER_FLAGS_ALLOW_REMAPPING | st::CBUFFER_FLAGS_ALLOW_ALLOC |
        st::CBUFFER_FLAGS_ALLOW_REALLOC   | st::CBUFFER_FLAGS_ALLOW_APPEND ); }

SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer)* NS(CBuffer_new_as_copy_detailed)(
    SIXTRL_CBUFFER_ARGPTR_DEC const ::NS(CBuffer) *const SIXTRL_RESTRICT orig,
    ::NS(cobj_buffer_flags_type) buf_flags ) {
    namespace st = SIXTRL_CXX_NAMESPACE;
    using st_size_t = st::cobj_size_type;
    st_size_t const slot_size = ::NS(CBuffer_slot_size)( orig );

    SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer)* b = SIXTRL_NULLPTR;
    if( ( orig != SIXTRL_NULLPTR ) &&
        ( ::NS(CBuffer_slot_size)( orig ) > st_size_t{ 0 } ) &&
        ( ::NS(CBuffer_capacity)( orig ) >=
          ::NS(CBuffer_min_buffer_size)( slot_size ) ) )
    {
        bool const orig_has_cbuffer_data = (
            ( ::NS(CBuffer_p_const_base)( orig ) == SIXTRL_NULLPTR ) ||
            ( ::NS(CObjFlatBuffer_has_cbuffer_structure)(
                ::NS(CBuffer_p_const_base)( orig ),
                    ::NS(CBuffer_capacity)( orig ), slot_size ) ) );

        if( !orig_has_cbuffer_data ) buf_flags |= st::CBUFFER_FLAGS_FORCE_INIT;
        b = ::NS(CBuffer_new_detailed)(
            ::NS(CBuffer_capacity)( orig ), slot_size, buf_flags );

        st::cobj_status_type status = st::STATUS_GENERAL_FAILURE;

        if( ( b != SIXTRL_NULLPTR ) && ( orig_has_cbuffer_data ) )
        {
            typedef ::NS(cobj_raw_type) raw_type;

            SIXTRL_CBUFFER_ARGPTR_DEC raw_type const* src =
                ::NS(CBuffer_p_const_base)( orig );

            SIXTRL_CBUFFER_ARGPTR_DEC raw_type* dest =
                ::NS(CBuffer_p_base)( b );

            st::cobj_size_type const n_bytes = ::NS(CBuffer_size)( orig );

            SIXTRL_ASSERT( ::NS(CBuffer_capacity)( b ) >=
                           ::NS(CBuffer_size)( orig ) );

            SIXTRACKLIB_COPY_VALUES( raw_type, dest, src, n_bytes );
            status = ::NS(CObjFlatBuffer_remap)( ::NS(CBuffer_p_base)( b ),
                ::NS(CBuffer_slot_size)( b ) );
        }
        else
        {
            status = ::NS(CObjFlatBuffer_init_empty)( ::NS(CBuffer_p_base)( b ),
                ::NS(CBuffer_capacity)( b ), ::NS(CBuffer_slot_size)( b ) );
        }

        if( status != st::STATUS_SUCCESS )
        {
            ::NS(CBuffer_delete)( b );
            b = SIXTRL_NULLPTR;
        }
    }

    return b;
}

SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer)* NS(CBuffer_new_from_file)(
    char const* SIXTRL_RESTRICT path_to_file ) {
    namespace st = SIXTRL_CXX_NAMESPACE;
    return ::NS(CBuffer_new_from_file_detailed)( path_to_file,
        st::CBUFFER_DEFAULT_SLOT_SIZE,
        st::CBUFFER_FLAGS_ALLOW_ALLOC | st::CBUFFER_FLAGS_ALLOW_APPEND |
        st::CBUFFER_FLAGS_ALLOW_REALLOC | st::CBUFFER_FLAGS_ALLOW_REMAPPING ); }

SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)*
NS(CBuffer_new_from_file_detailed)( char const* SIXTRL_RESTRICT path_to_file,
    ::NS(cobj_size_type) const slot_size, ::NS(cobj_buffer_flags_type) flags ) {
    namespace st = SIXTRL_CXX_NAMESPACE;
    SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer)* b = SIXTRL_NULLPTR;
    st::cobj_size_type f_size = st::File_num_bytes( path_to_file );
    if( f_size < ::NS(CBuffer_min_buffer_size)( slot_size ) ) return b;

    flags &= ~( st::CBUFFER_FLAGS_FORCE_INIT );
    b = ::NS(CBuffer_new_detailed)( f_size, slot_size, flags );

    if( ( b != SIXTRL_NULLPTR ) &&
        ( ::NS(CBuffer_init_from_file)( b, path_to_file ) !=
          ::NS(STATUS_SUCCESS) ) )
    {
        ::NS(CBuffer_delete)( b );
        b = SIXTRL_NULLPTR;
    }

    return b;
}

SIXTRL_CBUFFER_ARGPTR_DEC NS(CBuffer)* NS(CBuffer_new_with_structure)(
    ::NS(cobj_size_type) const max_num_slots,
    ::NS(cobj_size_type) const max_num_objects,
    ::NS(cobj_size_type) const max_num_pointers,
    ::NS(cobj_size_type) const max_num_garbage_ranges,
    ::NS(cobj_size_type) const slot_size, ::NS(cobj_buffer_flags_type) flags ) {

    namespace st = SIXTRL_CXX_NAMESPACE;
    SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer)* b = SIXTRL_NULLPTR;

    flags &= ~( st::CBUFFER_FLAGS_FORCE_INIT );
    flags |= st::CBUFFER_FLAGS_ALLOW_ALLOC;

    st::cobj_size_type const requ_buffer_capacity =
        ::NS(CBuffer_required_buffer_length)( max_num_slots, max_num_objects,
            max_num_pointers, max_num_garbage_ranges, slot_size );

    if( requ_buffer_capacity > ::NS(CBuffer_min_buffer_size)( slot_size ) )
        b = ::NS(CBuffer_new_detailed)( requ_buffer_capacity, slot_size, flags );

    if( ( b != SIXTRL_NULLPTR ) &&
        ( st::STATUS_SUCCESS != ::NS(CBuffer_allocate)( b, max_num_slots,
            max_num_objects, max_num_pointers, max_num_garbage_ranges ) ) )
    {
        ::NS(CBuffer_delete)( b );
        b = SIXTRL_NULLPTR;
    }

    return b;
}

::NS(cobj_status_type) NS(CBuffer_from_file)(
    SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer)* SIXTRL_RESTRICT buffer,
    char const* SIXTRL_RESTRICT path_to_file ) {
    return ::NS(CBuffer_init_from_file)( buffer, path_to_file ); }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

::NS(cobj_status_type) NS(CBuffer_to_file)(
    SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer)* SIXTRL_RESTRICT buffer,
    char const* SIXTRL_RESTRICT path_to_file ) {
    namespace st = SIXTRL_CXX_NAMESPACE;
    st::cobj_status_type status = st::STATUS_GENERAL_FAILURE;

    if( ( buffer != SIXTRL_NULLPTR ) && ( path_to_file != SIXTRL_NULLPTR ) &&
        ( ::NS(CBuffer_p_const_base)( buffer ) != SIXTRL_NULLPTR ) &&
        ( ::NS(CBuffer_size)( buffer ) >= ::NS(CBuffer_min_buffer_size)(
            ::NS(CBuffer_slot_size)( buffer ) ) ) )
    {
        ::FILE* fp = std::fopen( path_to_file, "wb" );
        if( fp != SIXTRL_NULLPTR )
        {
            status = ( !::NS(CBuffer_needs_remapping)( buffer ) )
                ? st::STATUS_SUCCESS : ::NS(CBuffer_remap)( buffer );

            if( status == st::STATUS_SUCCESS )
            {
                st::cobj_size_type const n_bytes = ::NS(CBuffer_size)( buffer );
                auto ret = std::fwrite( ::NS(CBuffer_p_const_base)( buffer ),
                    sizeof( st::cobj_raw_type ), n_bytes, fp );

                if( ( ret < 0 ) ||
                    ( static_cast< st::cobj_size_type >( ret ) != n_bytes ) )
                {
                    status = st::STATUS_GENERAL_FAILURE;
                }
            }

            std::fflush( fp );
            std::fclose( fp );
            fp = SIXTRL_NULLPTR;
        }
    }

    return status;
}

::NS(cobj_status_type) NS(CBuffer_to_file_normalised)(
    SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer)* SIXTRL_RESTRICT b,
    char const* SIXTRL_RESTRICT path_to_file,
    ::NS(cobj_addr_type) const normalised_base_addr ) {
    namespace st = SIXTRL_CXX_NAMESPACE;
    st::cobj_status_type status = st::STATUS_GENERAL_FAILURE;
    st::cobj_size_type const slot_size = ::NS(CBuffer_slot_size)( b );

    if( ( b != SIXTRL_NULLPTR ) && ( path_to_file != SIXTRL_NULLPTR ) &&
        ( slot_size > st::cobj_size_type{ 0 } ) &&
        ( ::NS(CBuffer_p_const_base)( b ) != SIXTRL_NULLPTR ) &&
        ( ::NS(CBuffer_size)( b ) >=
          ::NS(CBuffer_min_buffer_size)( slot_size ) ) )
    {
        ::FILE* fp = std::fopen( path_to_file, "wb" );
        if( fp != SIXTRL_NULLPTR )
        {
            bool apply_remap = false;

            status = ( !::NS(CBuffer_needs_remapping)( b ) )
                ? st::STATUS_SUCCESS : ::NS(CBuffer_remap)( b );

            if( ( status == st::STATUS_SUCCESS ) &&
                ( normalised_base_addr != ::NS(CBuffer_base_address)( b ) ) )
            {
                status = ::NS(CObjFlatBuffer_apply_addr_offset)(
                    ::NS(CBuffer_p_base)( b ),
                    normalised_base_addr - ::NS(CBuffer_base_address)( b ),
                    slot_size );

                apply_remap = ( status == st::STATUS_SUCCESS );
            }
            else if( normalised_base_addr == ::NS(CBuffer_base_address)( b ) )
            {
                status = st::STATUS_SUCCESS;
            }

            if( status == st::STATUS_SUCCESS )
            {
                st::cobj_size_type const n_bytes = ::NS(CBuffer_size)( b );
                auto ret = std::fwrite( ::NS(CBuffer_p_const_base)( b ),
                    sizeof( st::cobj_raw_type ), n_bytes, fp );

                if( ( ret < 0 ) || ( static_cast< st::cobj_size_type >(
                      ret ) != n_bytes ) ) status = st::STATUS_GENERAL_FAILURE;
            }
            else if( status == st::STATUS_SUCCESS )
                status = st::STATUS_GENERAL_FAILURE;

            if( apply_remap ) ::NS(CBuffer_remap)( b );
            SIXTRL_ASSERT( !::NS(CBuffer_needs_remapping)( b ) );

            std::fflush( fp );
            std::fclose( fp );
            fp = SIXTRL_NULLPTR;

            if( status != st::STATUS_SUCCESS ) std::remove( path_to_file );
        }
    }

    return status;
}

#endif /* C++ */
