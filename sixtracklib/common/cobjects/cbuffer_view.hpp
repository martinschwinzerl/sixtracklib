#ifndef SIXTRACKLIB_COMMON_COBJECTS_CBUFFER_VIEW_CXX_HPP__
#define SIXTRACKLIB_COMMON_COBJECTS_CBUFFER_VIEW_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/cobjects/cbuffer.h"
    #include "sixtracklib/common/cobjects/cobj_type_traits.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if !defined( _GPUCODE )
        #include <cstdlib>
        #include <type_traits>
        #include <iostream>
        #include <stdexcept>
        #include <vector>
        #include <string>
    #endif /* !defiend( _GPUCODE ) */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */
#endif /* C++ */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    struct CBufferView : public ::NS(CBuffer)
    {
        typedef SIXTRL_CXX_NAMESPACE::cobj_size_type         size_type;
        typedef SIXTRL_CXX_NAMESPACE::cobj_obj_id_type       obj_id_type;
        typedef SIXTRL_CXX_NAMESPACE::cobj_addr_type         addr_type;
        typedef SIXTRL_CXX_NAMESPACE::cobj_status_type       status_type;
        typedef SIXTRL_CXX_NAMESPACE::cobj_addr_diff_type    addr_diff_type;
        typedef SIXTRL_CXX_NAMESPACE::cobj_buffer_flags_type flags_type;

        typedef SIXTRL_CXX_NAMESPACE::cobj_raw_type          raw_type;
        typedef SIXTRL_CBUFFER_DATAPTR_DEC raw_type*         raw_pointer;
        typedef SIXTRL_CBUFFER_DATAPTR_DEC raw_type const*   raw_const_pointer;

        typedef SIXTRL_CXX_NAMESPACE::CObjIndex              obj_index_type;
        typedef SIXTRL_CXX_NAMESPACE::cobj_obj_index_pointer obj_index_pointer;
        typedef SIXTRL_CXX_NAMESPACE::cobj_obj_index_const_pointer
                obj_index_const_pointer;

        static constexpr size_type DEFAULT_SLOT_SIZE       =
            SIXTRL_CXX_NAMESPACE::CBUFFER_DEFAULT_SLOT_SIZE;

        static constexpr size_type DEFAULT_HEADER_SIZE =
            SIXTRL_CXX_NAMESPACE::CBUFFER_DEFAULT_HEADER_SIZE;

        static constexpr size_type DEFAULT_MINIMAL_SIZE =
            SIXTRL_CXX_NAMESPACE::CBUFFER_DEFAULT_MIN_BUFFER_SIZE;

        static constexpr addr_type NULL_ADDRESS =
            SIXTRL_CXX_NAMESPACE::COBJECTS_NULL_ADDRESS;

        static constexpr flags_type FLAGS_NONE =
            SIXTRL_CXX_NAMESPACE::CBUFFER_FLAGS_NONE;

        static constexpr flags_type FLAGS_ALLOW_REMAPPING =
            SIXTRL_CXX_NAMESPACE::CBUFFER_FLAGS_ALLOW_REMAPPING;

        static constexpr flags_type FLAGS_ALLOW_ALLOC =
            SIXTRL_CXX_NAMESPACE::CBUFFER_FLAGS_ALLOW_ALLOC;

        static constexpr flags_type FLAGS_ALLOW_REALLOC =
            SIXTRL_CXX_NAMESPACE::CBUFFER_FLAGS_ALLOW_REALLOC;

        static constexpr flags_type FLAGS_ALLOW_APPEND =
            SIXTRL_CXX_NAMESPACE::CBUFFER_FLAGS_ALLOW_APPEND;

        static constexpr flags_type FLAGS_FORCE_INIT =
            SIXTRL_CXX_NAMESPACE::CBUFFER_FLAGS_FORCE_INIT;

        static constexpr flags_type FLAGS_OWNS_STORED_DATA =
            SIXTRL_CXX_NAMESPACE::CBUFFER_FLAGS_OWNS_STORED_DATA;

        static constexpr flags_type FLAGS_SPECIAL_MEMORY =
            SIXTRL_CXX_NAMESPACE::CBUFFER_FLAGS_SPECIAL_MEMORY;

        static constexpr flags_type FLAGS_STORAGE_IS_C_PTR =
            SIXTRL_CXX_NAMESPACE::CBUFFER_FLAGS_STORAGE_IS_C_PTR;

        static constexpr flags_type FLAGS_VIEW_DEFAULT =
            SIXTRL_CXX_NAMESPACE::CBUFFER_FLAGS_DEFAULT_VIEW_FLAGS;

        static constexpr flags_type FLAGS_BUFFER_DEFAULT =
            SIXTRL_CXX_NAMESPACE::CBUFFER_FLAGS_DEFAULT_BUFFER_FLAGS;

        /* ---------------------------------------------------------------- */

        static SIXTRL_FN size_type MIN_BUFFER_SIZE(
            size_type const slot_size = DEFAULT_SLOT_SIZE ) SIXTRL_NOEXCEPT {
                return ::NS(CObjFlatBuffer_min_buffer_size)( slot_size ); }

        static SIXTRL_FN size_type HEADER_SIZE(
            size_type const slot_size = DEFAULT_SLOT_SIZE ) SIXTRL_NOEXCEPT {
                return ::NS(CObjFlatBuffer_header_size)( slot_size ); }

        static SIXTRL_FN flags_type ADD_FLAG_TO_SET(
            flags_type const haystack,
            flags_type const needle ) SIXTRL_NOEXCEPT {
            return haystack | needle; }

        static SIXTRL_FN flags_type REMOVE_FLAG_FROM_SET(
            flags_type const haystack,
            flags_type const needle ) SIXTRL_NOEXCEPT {
            return haystack & ~needle; }

        static SIXTRL_FN bool IS_FLAG_SET(
            flags_type const haystack,
            flags_type const needle ) SIXTRL_NOEXCEPT {
            return ( ( needle != FLAGS_NONE ) &&
                     ( ( haystack & needle ) == needle ) ); }

        static SIXTRL_FN size_type REQUIRED_BUFFER_LENGTH(
            size_type const max_n_slots,
            size_type const max_n_objs,
            size_type const max_n_ptrs,
            size_type const max_n_garbage = size_type{ 0 },
            size_type const slot_size = DEFAULT_SLOT_SIZE ) SIXTRL_NOEXCEPT {
            return ::NS(CObjFlatBuffer_predict_required_buffer_size)(
                max_n_slots, max_n_objs, max_n_ptrs, max_n_garbage, slot_size );}

        static SIXTRL_FN addr_type ALIGNED_BASE_ADDR(
            addr_type const raw_base_addr,
            size_type const raw_capacity,
            size_type alignment = size_type{ 1 },
            SIXTRL_ARGPTR_DEC size_type* ptr_capacity = SIXTRL_NULLPTR,
            size_type const slot_size = DEFAULT_SLOT_SIZE ) SIXTRL_NOEXCEPT {
            return ::NS(CObjFlatBuffer_aligned_base_addr)( raw_base_addr,
                raw_capacity, alignment, ptr_capacity, slot_size ); }

        /* ----------------------------------------------------------------- */

        SIXTRL_FN explicit CBufferView(
            addr_type base_addr = CBufferView::NULL_ADDRESS,
            size_type const capacity = size_type{ 0 },
            size_type const slot_size = CBufferView::DEFAULT_SLOT_SIZE,
            flags_type const flags = CBufferView::FLAGS_VIEW_DEFAULT
        ) SIXTRL_NOEXCEPT;

        SIXTRL_FN CBufferView( SIXTRL_CBUFFER_ARGPTR_DEC CBufferView const&
            SIXTRL_RESTRICT_REF orig );

        SIXTRL_FN CBufferView( SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer) const&
            SIXTRL_RESTRICT_REF orig );

        SIXTRL_FN CBufferView( SIXTRL_CBUFFER_ARGPTR_DEC CBufferView&&
            orig ) SIXTRL_NOEXCEPT;

        SIXTRL_FN CBufferView( SIXTRL_CBUFFER_ARGPTR_DEC
            ::NS(CBuffer)&& orig ) SIXTRL_NOEXCEPT;

        SIXTRL_FN SIXTRL_CBUFFER_ARGPTR_DEC CBufferView& operator=(
            SIXTRL_CBUFFER_ARGPTR_DEC CBufferView const& rhs );

        SIXTRL_FN SIXTRL_CBUFFER_ARGPTR_DEC CBufferView& operator=(
            SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer) const&
                SIXTRL_RESTRICT_REF rhs );

        SIXTRL_FN SIXTRL_CBUFFER_ARGPTR_DEC CBufferView& operator=(
            SIXTRL_CBUFFER_ARGPTR_DEC CBufferView&& rhs ) SIXTRL_NOEXCEPT;

        SIXTRL_FN SIXTRL_CBUFFER_ARGPTR_DEC CBufferView& operator=(
            SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer)&& rhs ) SIXTRL_NOEXCEPT;

        #if !defined( _GPUCODE )
        SIXTRL_FN virtual ~CBufferView() SIXTRL_NOEXCEPT;
        #else
        SIXTRL_FN ~CBufferView() SIXTRL_NOEXCEPT;
        #endif /* !defined( _GPUCODE ) */

        /* ----------------------------------------------------------------- */

        SIXTRL_INLINE SIXTRL_FN SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer) const*
        as_c_api() const SIXTRL_NOEXCEPT { return static_cast<
            SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer) const* >( this ); }

        SIXTRL_INLINE SIXTRL_FN SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer) const*
        as_const_c_api() SIXTRL_NOEXCEPT { namespace st = SIXTRL_CXX_NAMESPACE;
            return static_cast< st::CBufferView const& >( *this ).as_c_api(); }

        SIXTRL_INLINE SIXTRL_FN SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer)*
        as_c_api() SIXTRL_NOEXCEPT {
            return static_cast< SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer)* >(
                this ); }

        /* ------------------------------------------------------------------ */

        SIXTRL_FN flags_type flags() const SIXTRL_NOEXCEPT {
            return this->m_buffer_flags; }

        SIXTRL_FN bool allow_remap() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_allow_remap)( this->as_c_api() ); }

        SIXTRL_FN bool allow_allocate() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_allow_allocate)( this->as_c_api() ); }

        SIXTRL_FN bool allow_realloc() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_allow_realloc)( this->as_c_api() ); }

        SIXTRL_FN bool allow_append() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_allow_append)( this->as_c_api() ); }

        SIXTRL_FN bool owns_stored_data() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_owns_stored_data)( this->as_c_api() ); }

        SIXTRL_FN bool has_special_memory() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_has_special_memory)( this->as_c_api() ); }

        SIXTRL_FN bool storage_is_c_ptr() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_storage_is_c_ptr)( this->as_c_api() ); }

        SIXTRL_FN bool storage_is_cxx_vector() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_storage_is_cxx_vector)( this->as_c_api() ); }

        /* ----------------------------------------------------------------- */

        SIXTRL_INLINE SIXTRL_FN size_type slot_size() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_slot_size)( this->as_c_api() ); }

        /* ----------------------------------------------------------------- */

        SIXTRL_INLINE SIXTRL_FN size_type size() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_size)( this->as_c_api() ); }

        SIXTRL_INLINE SIXTRL_FN size_type capacity() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_capacity)( this->as_c_api() ); }

        SIXTRL_FN size_type size_header() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_size_header)( this->as_c_api() ); }

        SIXTRL_FN size_type size_section_header(
            size_type const sec_id ) const SIXTRL_NOEXCEPT {
        return ::NS(CBuffer_size_section_header)( this->as_c_api(), sec_id ); }

        SIXTRL_FN size_type size_slots() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_size_slots)( this->as_c_api() ); }

        SIXTRL_FN size_type size_objects() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_size_objects)( this->as_c_api() ); }

        SIXTRL_FN size_type size_pointers() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_size_pointers)( this->as_c_api() ); }

        SIXTRL_FN size_type size_garbage() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_size_garbage)( this->as_c_api() ); }

        SIXTRL_INLINE SIXTRL_FN size_type n_slots() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_num_slots)( this->as_c_api() ); }

        SIXTRL_INLINE SIXTRL_FN size_type n_objects() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_num_objects)( this->as_c_api() ); }

        SIXTRL_INLINE SIXTRL_FN size_type n_pointers() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_num_pointers)( this->as_c_api() ); }

        SIXTRL_INLINE SIXTRL_FN size_type n_garbage() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_num_garbage)( this->as_c_api() ); }

        SIXTRL_INLINE SIXTRL_FN size_type num_slots() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_num_slots)( this->as_c_api() ); }

        SIXTRL_INLINE SIXTRL_FN size_type num_objects() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_num_objects)( this->as_c_api() ); }

        SIXTRL_INLINE SIXTRL_FN size_type num_pointers() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_num_pointers)( this->as_c_api() ); }

        SIXTRL_INLINE SIXTRL_FN size_type num_garbage() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_num_garbage)( this->as_c_api() ); }

        SIXTRL_FN size_type max_slots() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_max_slots)( this->as_c_api() ); }

        SIXTRL_FN size_type max_objects() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_max_objects)( this->as_c_api() ); }

        SIXTRL_FN size_type max_pointers() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_max_pointers)( this->as_c_api() ); }

        SIXTRL_FN size_type max_garbage() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_max_garbage)( this->as_c_api() ); }

        /* ----------------------------------------------------------------- */

        SIXTRL_INLINE SIXTRL_FN addr_type begin_addr() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_begin_addr)( this->as_c_api() ); }

        SIXTRL_INLINE SIXTRL_FN addr_type end_addr() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_end_addr)( this->as_c_api() ); }

        SIXTRL_FN addr_type begin_addr_slots() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_begin_addr_slots)( this->as_c_api() ); }

        SIXTRL_FN addr_type begin_addr_objects() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_begin_addr_objects)( this->as_c_api() ); }

        SIXTRL_FN addr_type begin_addr_pointers() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_begin_addr_pointers)( this->as_c_api() ); }

        SIXTRL_FN addr_type begin_addr_garbage() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_begin_addr_garbage)( this->as_c_api() ); }

        SIXTRL_FN addr_type end_addr_slots() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_end_addr_slots)( this->as_c_api() ); }

        SIXTRL_FN addr_type end_addr_objects() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_end_addr_objects)( this->as_c_api() ); }

        SIXTRL_FN addr_type end_addr_pointers() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_end_addr_pointers)( this->as_c_api() ); }

        SIXTRL_FN addr_type end_addr_garbage() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_end_addr_garbage)( this->as_c_api() ); }

        /* ----------------------------------------------------------------- */

        SIXTRL_INLINE SIXTRL_FN addr_type base() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_base_address)( this->as_c_api() ); }

        SIXTRL_INLINE SIXTRL_FN addr_type base_address() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_base_address)( this->as_c_api() ); }

        SIXTRL_INLINE SIXTRL_FN raw_const_pointer p_base() const SIXTRL_NOEXCEPT
        {
            return ::NS(CBuffer_p_const_base)( this->as_c_api() );
        }

        SIXTRL_INLINE SIXTRL_FN raw_const_pointer
        p_base_begin() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_p_const_base_begin)( this->as_c_api() ); }

        SIXTRL_INLINE SIXTRL_FN raw_const_pointer
        p_base_end() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_p_const_base_end)( this->as_c_api() ); }

        SIXTRL_INLINE SIXTRL_FN raw_pointer p_base_begin() SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_p_base_begin)( this->as_c_api() ); }

        SIXTRL_INLINE SIXTRL_FN raw_pointer p_base_end() SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_p_base_end)( this->as_c_api() ); }

        SIXTRL_INLINE SIXTRL_FN raw_pointer p_base() SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_p_base)( this->as_c_api() ); }

        SIXTRL_INLINE SIXTRL_FN raw_const_pointer p_const_base_begin(
            ) SIXTRL_NOEXCEPT { return ::NS(CBuffer_p_const_base_begin)(
                this->as_c_api() ); }

        SIXTRL_INLINE SIXTRL_FN raw_const_pointer p_const_base_end(
            ) SIXTRL_NOEXCEPT { return ::NS(CBuffer_p_const_base_end)(
                this->as_c_api() ); }

        SIXTRL_INLINE SIXTRL_FN raw_const_pointer p_const_base(
            ) SIXTRL_NOEXCEPT { return ::NS(CBuffer_p_const_base)(
                this->as_c_api() ); }

        /* ----------------------------------------------------------------- */

        SIXTRL_FN raw_const_pointer p_slots() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_p_const_slots)( this->as_c_api() ); }

        SIXTRL_FN raw_pointer p_slots() SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_p_slots)( this->as_c_api() ); }

        SIXTRL_FN raw_const_pointer p_const_slots() SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_p_const_slots)( this->as_c_api() ); }

        SIXTRL_FN raw_const_pointer p_slots_end() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_p_const_slots_end)( this->as_c_api() ); }

        SIXTRL_FN raw_const_pointer p_const_slots_end() SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_p_const_slots_end)( this->as_c_api() ); }

        SIXTRL_FN raw_pointer p_slots_end() SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_p_slots_end)( this->as_c_api() ); }

        SIXTRL_FN raw_const_pointer p_objects() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_p_const_objects)( this->as_c_api() ); }

        SIXTRL_FN raw_pointer p_objects() SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_p_objects)( this->as_c_api() ); }

        SIXTRL_FN raw_const_pointer p_const_objects() SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_p_const_objects)( this->as_c_api() ); }

        SIXTRL_FN raw_const_pointer p_objects_end() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_p_const_objects_end)( this->as_c_api() ); }

        SIXTRL_FN raw_const_pointer p_const_objects_end() SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_p_const_objects_end)( this->as_c_api() ); }

        SIXTRL_FN raw_pointer p_objects_end() SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_p_objects_end)( this->as_c_api() ); }

        SIXTRL_FN raw_const_pointer p_pointers() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_p_const_pointers)( this->as_c_api() ); }

        SIXTRL_FN raw_pointer p_pointers() SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_p_pointers)( this->as_c_api() ); }

        SIXTRL_FN raw_const_pointer p_const_pointers() SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_p_const_pointers)( this->as_c_api() ); }

        SIXTRL_FN raw_const_pointer p_pointers_end() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_p_const_pointers_end)( this->as_c_api() ); }

        SIXTRL_FN raw_const_pointer p_const_pointers_end() SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_p_const_pointers_end)( this->as_c_api() ); }

        SIXTRL_FN raw_pointer p_pointers_end() SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_p_pointers_end)( this->as_c_api() ); }

        SIXTRL_FN raw_const_pointer p_garbage() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_p_const_garbage)( this->as_c_api() ); }

        SIXTRL_FN raw_pointer p_garbage() SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_p_garbage)( this->as_c_api() ); }

        SIXTRL_FN raw_const_pointer p_const_garbage() SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_p_const_garbage)( this->as_c_api() ); }

        SIXTRL_FN raw_const_pointer p_garbage_end() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_p_const_garbage_end)( this->as_c_api() ); }

        SIXTRL_FN raw_const_pointer p_const_garbage_end() SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_p_const_garbage_end)( this->as_c_api() ); }

        SIXTRL_FN raw_pointer p_garbage_end() SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_p_garbage_end)( this->as_c_api() ); }

        /* ----------------------------------------------------------------- */

        SIXTRL_FN addr_diff_type address_to_offset( addr_type const address
            ) const SIXTRL_NOEXCEPT { return ::NS(CBuffer_address_to_offset)(
                this->as_c_api(), address ); }

        SIXTRL_FN addr_type offset_to_address( addr_diff_type const offset
            ) const SIXTRL_NOEXCEPT { return ::NS(CBuffer_offset_to_address)(
                this->as_c_api(), offset ); }

        /* ----------------------------------------------------------------- */

        SIXTRL_FN bool has_capacity_for_allocate( size_type const max_n_slots,
            size_type const max_n_objs, size_type const max_n_ptrs,
            size_type const max_n_garbage = size_type{ 0 }
        ) const SIXTRL_NOEXCEPT { return ::NS(CBuffer_has_capacity_for_allocate)(
            this->as_c_api(), max_n_slots, max_n_objs, max_n_ptrs,
                max_n_garbage ); }

        SIXTRL_FN bool can_allocate( size_type const max_n_slots,
            size_type const max_n_objs, size_type const max_n_ptrs,
            size_type const max_n_garbage = size_type{ 0 }
        ) const SIXTRL_NOEXCEPT { return ::NS(CBuffer_can_allocate)(
            this->as_c_api(), max_n_slots, max_n_objs, max_n_ptrs,
                max_n_garbage ); }

        SIXTRL_FN status_type allocate( size_type const max_n_slots,
            size_type const max_n_objs, size_type const max_n_ptrs,
            size_type const max_n_garbage = size_type{ 0 } ) {
            return ::NS(CBuffer_allocate)( this->as_c_api(), max_n_slots,
                max_n_objs, max_n_ptrs, max_n_garbage ); }

        SIXTRL_FN status_type reallocate( size_type const max_n_slots,
            size_type const max_n_objs, size_type const max_n_ptrs,
            size_type const max_n_garbage = size_type{ 0 } ) {
            return ::NS(CBuffer_reallocate)( this->as_c_api(), max_n_slots,
                max_n_objs, max_n_ptrs, max_n_garbage ); }

        /* ----------------------------------------------------------------- */

        SIXTRL_INLINE SIXTRL_FN bool needs_remapping() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_needs_remapping)( this->as_c_api() ); }

        SIXTRL_INLINE SIXTRL_FN bool can_remap() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_can_remap)( this->as_c_api() ); }

        SIXTRL_FN status_type remap() SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_remap)( this->as_c_api() ); }

        /* ----------------------------------------------------------------- */

        SIXTRL_INLINE SIXTRL_FN obj_index_const_pointer
        objects_begin() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_const_objects_begin)( this->as_c_api() ); }

        SIXTRL_INLINE SIXTRL_FN obj_index_pointer objects_begin(
            ) SIXTRL_NOEXCEPT { return ::NS(CBuffer_objects_begin)(
                this->as_c_api() ); }

        SIXTRL_INLINE SIXTRL_FN obj_index_const_pointer const_objects_begin(
            ) SIXTRL_NOEXCEPT { return ::NS(CBuffer_const_objects_begin)(
                this->as_c_api() ); }

        SIXTRL_INLINE SIXTRL_FN obj_index_const_pointer objects_end(
            ) const SIXTRL_NOEXCEPT { return ::NS(CBuffer_const_objects_end)(
                this->as_c_api() ); }

        SIXTRL_INLINE SIXTRL_FN obj_index_pointer objects_end(
            ) SIXTRL_NOEXCEPT { return ::NS(CBuffer_objects_end)(
                this->as_c_api() ); }

        SIXTRL_INLINE SIXTRL_FN obj_index_const_pointer const_objects_end(
            ) SIXTRL_NOEXCEPT { return ::NS(CBuffer_const_objects_end)(
                this->as_c_api() ); }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_INLINE SIXTRL_FN obj_index_const_pointer
        indices_begin() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_const_objects_begin)( this->as_c_api() ); }

        SIXTRL_INLINE SIXTRL_FN obj_index_pointer indices_begin(
            ) SIXTRL_NOEXCEPT { return ::NS(CBuffer_objects_begin)(
                this->as_c_api() ); }

        SIXTRL_INLINE SIXTRL_FN obj_index_const_pointer const_indices_begin(
            ) SIXTRL_NOEXCEPT { return ::NS(CBuffer_const_objects_begin)(
                this->as_c_api() ); }

        SIXTRL_INLINE SIXTRL_FN obj_index_const_pointer indices_end(
            ) const SIXTRL_NOEXCEPT { return ::NS(CBuffer_const_objects_end)(
                this->as_c_api() ); }

        SIXTRL_INLINE SIXTRL_FN obj_index_pointer indices_end(
            ) SIXTRL_NOEXCEPT { return ::NS(CBuffer_objects_end)(
                this->as_c_api() ); }

        SIXTRL_INLINE SIXTRL_FN obj_index_const_pointer const_indices_end(
            ) SIXTRL_NOEXCEPT { return ::NS(CBuffer_const_objects_end)(
                this->as_c_api() ); }

        /* ----------------------------------------------------------------- */

        SIXTRL_FN size_type reserve_factor_nominator() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_reserve_factor_nominator)( this->as_c_api() ); }

        SIXTRL_FN size_type reserve_factor_denominator() const SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_reserve_factor_denominator)( this->as_c_api() ); }

        SIXTRL_FN void set_reserve_factor_nominator(
            size_type const factor_nominator ) SIXTRL_NOEXCEPT {
                ::NS(CBuffer_set_reserve_factor_nominator)(
                    this->as_c_api(), factor_nominator ); }

        SIXTRL_FN void set_reserve_factor_denominator(
            size_type const factor_nominator ) SIXTRL_NOEXCEPT {
                ::NS(CBuffer_set_reserve_factor_denominator)(
                    this->as_c_api(), factor_nominator ); }

        SIXTRL_FN void set_reserve_factor( size_type const factor_nominator,
            size_type const factor_denominator ) SIXTRL_NOEXCEPT {
            ::NS(CBuffer_set_reserve_factor)( this->as_c_api(),
                factor_nominator, factor_denominator ); }

        SIXTRL_FN size_type reserve_scale_capacity(
            size_type const capacity ) SIXTRL_NOEXCEPT {
                return ::NS(CBuffer_reserve_scale_capacity)(
                    this->as_c_api(), capacity ); }

        SIXTRL_FN status_type reserve( size_type const capacity ) {
            return ::NS(CBuffer_reserve)( this->as_c_api(), capacity ); }

        SIXTRL_FN status_type reserve_detailed( size_type const max_n_slots,
            size_type const max_n_objs, size_type const max_n_ptrs,
                size_type const max_n_garbage ) {
            return ::NS(CBuffer_reserve_detailed)( this->as_c_api(),
                max_n_slots, max_n_objs, max_n_ptrs, max_n_garbage ); }

        /* ----------------------------------------------------------------- */

        SIXTRL_INLINE SIXTRL_FN obj_index_const_pointer index_at(
            size_type const pos_in_buffer ) const SIXTRL_NOEXCEPT {
                return ::NS(CBuffer_const_index_at)(
                    this->as_c_api(), pos_in_buffer ); }

        SIXTRL_INLINE SIXTRL_FN obj_index_const_pointer const_index_at(
            size_type const pos_in_buffer ) SIXTRL_NOEXCEPT {
                return ::NS(CBuffer_const_index_at)(
                    this->as_c_api(), pos_in_buffer ); }

        SIXTRL_INLINE SIXTRL_FN obj_index_pointer index_at(
            size_type const pos_in_buffer ) SIXTRL_NOEXCEPT {
                return ::NS(CBuffer_index_at)(
                    this->as_c_api(), pos_in_buffer ); }

        SIXTRL_INLINE SIXTRL_FN obj_index_const_pointer operator[](
            size_type const pos_in_buffer ) const SIXTRL_NOEXCEPT {
                return ::NS(CBuffer_const_index_at)(
                    this->as_c_api(), pos_in_buffer ); }

        SIXTRL_INLINE SIXTRL_FN obj_index_pointer operator[](
            size_type const pos_in_buffer ) SIXTRL_NOEXCEPT {
                return ::NS(CBuffer_index_at)(
                    this->as_c_api(), pos_in_buffer ); }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_INLINE SIXTRL_FN obj_id_type obj_typeid(
            size_type const pos_in_buffer ) const SIXTRL_NOEXCEPT {
                return ::NS(CObjIndex_type_id)( ::NS(CBuffer_const_index_at)(
                    this->as_c_api(), pos_in_buffer ) ); }

        SIXTRL_INLINE SIXTRL_FN size_type obj_size(
            size_type const pos_in_buffer ) const SIXTRL_NOEXCEPT {
                return ::NS(CObjIndex_size)( ::NS(CBuffer_const_index_at)(
                    this->as_c_api(), pos_in_buffer ) ); }

        SIXTRL_FN size_type obj_num_slots(
            size_type const pos_in_buf ) const SIXTRL_NOEXCEPT {
            SIXTRL_ASSERT( this->slot_size() > size_type{ 0 } );
            size_type const num_bytes = this->obj_size( pos_in_buf );
            size_type num_slots = this->obj_size( pos_in_buf );
            num_slots /= this->slot_size();
            if( num_slots * this->slot_size() < num_bytes ) ++num_slots;
            return num_slots; }

        SIXTRL_INLINE SIXTRL_FN addr_type obj_address(
            size_type const pos_in_buffer ) const SIXTRL_NOEXCEPT {
            return ::NS(CObjIndex_begin_addr)( ::NS(CBuffer_const_index_at)(
                this->as_c_api(), pos_in_buffer ) ); }

        /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

        template< class E > SIXTRL_FN typename std::enable_if<
            !SIXTRL_CXX_NAMESPACE::CObjects_is_legal_type< E >(), bool >::type
        is_obj_type( size_type const SIXTRL_UNUSED( pos_in_buffer ),
            SIXTRL_CBUFFER_ARGPTR_DEC E const* SIXTRL_UNUSED( ptr ) = nullptr
        ) const SIXTRL_NOEXCEPT { return false; }

        template< class E > SIXTRL_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::CObjects_is_legal_type< E >(), bool >::type
        is_obj_type( size_type const pos_in_buffer,
            SIXTRL_CBUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
                ptr = nullptr ) const SIXTRL_NOEXCEPT {
            namespace st = SIXTRL_CXX_NAMESPACE;
            return ::NS(CObjIndex_is_consistent_with_type)(
                ::NS(CBuffer_const_index_at)( this->as_c_api(), pos_in_buffer ),
                st::CObjects_type_id< E >(),
                st::CObjects_reserved_handle_size< E >(
                    ::NS(CBuffer_slot_size)( this->as_c_api() ), ptr ) ); }

        /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .  */

        template< class E >
        SIXTRL_FN typename std::enable_if<
           !SIXTRL_CXX_NAMESPACE::CObjects_is_legal_type< E >(),
            typename CObjectsStoreResultTypeTraits< E >::const_pointer >::type
        get_object( size_type const SIXTRL_UNUSED( pos_in_buffer ),
            SIXTRL_CBUFFER_ARGPTR_DEC const E *const SIXTRL_UNUSED(
                ptr_cls_elem ) = nullptr ) const SIXTRL_NOEXCEPT {
            return nullptr; }

        template< class E >
        SIXTRL_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::CObjects_is_legal_type< E >(),
            typename CObjectsStoreResultTypeTraits< E >::const_pointer >::type
        get_object( size_type const pos_in_buf,
            typename CObjectsCopyArgTypeTraits< E >::const_pointer const
                SIXTRL_RESTRICT ptr_cls_elem = nullptr ) const SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::CObjIndex_to_elem< E >(
                ::NS(CBuffer_const_index_at)( this->as_c_api(), pos_in_buf ),
                    ::NS(CBuffer_slot_size)( this->as_c_api() ), ptr_cls_elem );
        }

        template< class E >
        typename CObjectsStoreResultTypeTraits< E >::const_pointer
        get_const_object( size_type const pos_in_buf,
            typename CObjectsCopyArgTypeTraits< E >::const_pointer const
                SIXTRL_RESTRICT ptr_cls_elem = nullptr ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::CObjIndex_to_elem< E >(
                ::NS(CBuffer_const_index_at)( this->as_c_api(), pos_in_buf ),
                    ::NS(CBuffer_slot_size)( this->as_c_api() ), ptr_cls_elem );
        }

        template< class E >
        typename CObjectsStoreResultTypeTraits< E >::pointer
        get_object( size_type const pos_in_buf,
            typename CObjectsCopyArgTypeTraits< E >::const_pointer const
                SIXTRL_RESTRICT ptr_cls_elem = nullptr ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::CObjIndex_to_elem< E >(
                ::NS(CBuffer_index_at)( this->as_c_api(), pos_in_buf ),
                    ::NS(CBuffer_slot_size)( this->as_c_api() ), ptr_cls_elem );
        }

        /* ------------------------------------------------------------------ */

        SIXTRL_FN bool can_add_copy_of_object(
            size_type const obj_handle_size, size_type const num_dataptrs,
            SIXTRL_ARGPTR_DEC size_type const* SIXTRL_RESTRICT sizes,
            SIXTRL_ARGPTR_DEC size_type const* SIXTRL_RESTRICT counts,
            SIXTRL_ARGPTR_DEC size_type*
                SIXTRL_RESTRICT requ_buffer_size = nullptr,
            SIXTRL_ARGPTR_DEC size_type*
                SIXTRL_RESTRICT requ_n_slots = nullptr,
            SIXTRL_ARGPTR_DEC size_type*
                SIXTRL_RESTRICT requ_n_objects = nullptr,
            SIXTRL_ARGPTR_DEC size_type*
                SIXTRL_RESTRICT requ_n_pointers = nullptr ) SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_can_add_copy_of_object)( this->as_c_api(),
                obj_handle_size, num_dataptrs, sizes, counts, requ_buffer_size,
                    requ_n_slots, requ_n_objects, requ_n_pointers ); }

        SIXTRL_FN bool can_add_copy_of_trivial_object(
            size_type const obj_handle_size,
            SIXTRL_ARGPTR_DEC size_type*
                SIXTRL_RESTRICT requ_buffer_size = nullptr,
            SIXTRL_ARGPTR_DEC size_type*
                SIXTRL_RESTRICT requ_n_slots = nullptr,
            SIXTRL_ARGPTR_DEC size_type*
                SIXTRL_RESTRICT requ_n_objects = nullptr,
            SIXTRL_ARGPTR_DEC size_type*
                SIXTRL_RESTRICT requ_n_pointers = nullptr
        ) SIXTRL_NOEXCEPT {
            return ::NS(CBuffer_can_add_copy_of_trivial_object)(
                this->as_c_api(), obj_handle_size, requ_buffer_size,
                    requ_n_slots, requ_n_objects, requ_n_pointers ); }

        /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

        template< class E >
        SIXTRL_FN typename std::enable_if<
            !SIXTRL_CXX_NAMESPACE::CObjects_is_legal_type< E >(), bool >::type
        can_add_copy(
            typename CObjectsCopyArgTypeTraits< E >::const_pointer
                const SIXTRL_RESTRICT SIXTRL_UNUSED( ptr ) = nullptr
        ) SIXTRL_NOEXCEPT { return false; }

        template< class E >
        SIXTRL_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::CObjects_is_legal_type< E >() &&
            SIXTRL_CXX_NAMESPACE::CObjects_is_trivial_type< E >(), bool >::type
        can_add_copy(
            typename CObjectsCopyArgTypeTraits< E >::const_pointer
                const SIXTRL_RESTRICT ptr = nullptr,
            SIXTRL_ARGPTR_DEC cobj_size_type*
                SIXTRL_RESTRICT requ_buffer_size = nullptr,
            SIXTRL_ARGPTR_DEC cobj_size_type*
                SIXTRL_RESTRICT requ_n_slots = nullptr,
            SIXTRL_ARGPTR_DEC cobj_size_type*
                SIXTRL_RESTRICT requ_n_objs = nullptr,
            SIXTRL_ARGPTR_DEC cobj_size_type*
                SIXTRL_RESTRICT requ_n_ptrs = nullptr ) SIXTRL_NOEXCEPT {
            namespace st = SIXTRL_CXX_NAMESPACE;
            return ::NS(CBuffer_can_add_copy_of_trivial_object)(
                this->as_c_api(),
                st::CObjects_reserved_handle_size< E >( this->slot_size(), ptr ),
                requ_buffer_size, requ_n_slots, requ_n_objs, requ_n_ptrs ); }

        template< class E >
        SIXTRL_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::CObjects_is_legal_type< E >() &&
           !SIXTRL_CXX_NAMESPACE::CObjects_is_trivial_type< E >() &&
            ( SIXTRL_CXX_NAMESPACE::CObjects_num_pointers< E >() ==
                SIXTRL_CXX_NAMESPACE::cobj_size_type{ 0 } ), bool >::type
        can_add_copy(
            typename CObjectsCopyArgTypeTraits< E >::const_pointer
                const SIXTRL_RESTRICT ptr = nullptr,
            SIXTRL_ARGPTR_DEC cobj_size_type*
                SIXTRL_RESTRICT requ_buffer_size = nullptr,
            SIXTRL_ARGPTR_DEC cobj_size_type*
                SIXTRL_RESTRICT requ_n_slots = nullptr,
            SIXTRL_ARGPTR_DEC cobj_size_type*
                SIXTRL_RESTRICT requ_n_objs = nullptr,
            SIXTRL_ARGPTR_DEC cobj_size_type*
                SIXTRL_RESTRICT requ_n_ptrs = nullptr ) SIXTRL_NOEXCEPT {
            namespace st = SIXTRL_CXX_NAMESPACE;
            return ::NS(CBuffer_can_add_copy_of_trivial_object)(
                this->as_c_api(), st::CObjects_reserved_handle_size< E >(
                    this->slot_size(), ptr ), requ_buffer_size, requ_n_slots,
                        requ_n_objs, requ_n_ptrs ); }

        template< class E >
        SIXTRL_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::CObjects_is_legal_type< E >() &&
           !SIXTRL_CXX_NAMESPACE::CObjects_is_trivial_type< E >() &&
            ( SIXTRL_CXX_NAMESPACE::CObjects_num_pointers< E >() <=
                SIXTRL_CXX_NAMESPACE::cobj_size_type{ 25 } ), bool >::type
        can_add_copy(
            typename CObjectsCopyArgTypeTraits< E >::const_pointer
                const SIXTRL_RESTRICT ptr = nullptr,
            SIXTRL_ARGPTR_DEC cobj_size_type*
                SIXTRL_RESTRICT requ_buffer_size = nullptr,
            SIXTRL_ARGPTR_DEC cobj_size_type*
                SIXTRL_RESTRICT requ_n_slots = nullptr,
            SIXTRL_ARGPTR_DEC cobj_size_type*
                SIXTRL_RESTRICT requ_n_objs = nullptr,
            SIXTRL_ARGPTR_DEC cobj_size_type*
                SIXTRL_RESTRICT requ_n_ptrs = nullptr ) SIXTRL_NOEXCEPT {

            namespace st = SIXTRL_CXX_NAMESPACE;
            SIXTRL_ASSERT( st::CObjects_num_pointers< E >() >
                           st::cobj_size_type{ 0 } );

            st::cobj_size_type const slot_size =
                ::NS(CBuffer_slot_size)( this->as_c_api() );

            SIXTRL_ASSERT( slot_size > st::cobj_size_type{ 0 } );

            SIXTRL_ARGPTR_DEC st::cobj_size_type SIZES[ 25 ];
            SIXTRL_ARGPTR_DEC st::cobj_size_type COUNTS[ 25 ];

            st::cobj_status_type status = st::CObjects_attribute_sizes< E >(
                &SIZES[ 0 ], 25u, ptr, slot_size );

            if( status == st::STATUS_SUCCESS )
                status = st::CObjects_attribute_counts< E >(
                    &COUNTS[ 0 ], 25u, ptr, slot_size );

            return ( ( status == st::STATUS_SUCCESS ) &&
                     ( ::NS(CBuffer_can_add_copy_of_object)( this->as_c_api(),
                        st::CObjects_reserved_handle_size< E >( slot_size, ptr ),
                        st::CObjects_num_pointers< E >(), &SIZES[ 0 ],
                        &COUNTS[ 0 ], requ_buffer_size, requ_n_slots,
                        requ_n_objs, requ_n_ptrs ) ) ); }

        template< class E >
        SIXTRL_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::CObjects_is_legal_type< E >() &&
           !SIXTRL_CXX_NAMESPACE::CObjects_is_trivial_type< E >() &&
            ( SIXTRL_CXX_NAMESPACE::CObjects_num_pointers< E >() >
                SIXTRL_CXX_NAMESPACE::cobj_size_type{ 25 } ), bool >::type
        can_add_copy(
            typename CObjectsCopyArgTypeTraits< E >::const_pointer
                const SIXTRL_RESTRICT ptr = nullptr,
            SIXTRL_ARGPTR_DEC cobj_size_type*
                SIXTRL_RESTRICT requ_buffer_size = nullptr,
            SIXTRL_ARGPTR_DEC cobj_size_type*
                SIXTRL_RESTRICT requ_n_slots = nullptr,
            SIXTRL_ARGPTR_DEC cobj_size_type*
                SIXTRL_RESTRICT requ_n_objs = nullptr,
            SIXTRL_ARGPTR_DEC cobj_size_type*
                SIXTRL_RESTRICT requ_n_ptrs = nullptr ) SIXTRL_NOEXCEPT {

            namespace st = SIXTRL_CXX_NAMESPACE;
            SIXTRL_ASSERT( st::CObjects_num_pointers< E >() >
                           st::cobj_size_type{ 0 } );

            st::cobj_size_type const slot_size =
                ::NS(CBuffer_slot_size)( this->as_c_api() );

            SIXTRL_ASSERT( slot_size > st::cobj_size_type{ 0 } );

            std::vector< st::cobj_size_type > SIZES(
                st::CObjects_num_pointers< E >(), st::cobj_size_type{ 0 } );

            std::vector< st::cobj_size_type > COUNTS(
                st::CObjects_num_pointers< E >(), st::cobj_size_type{ 0 } );

            st::cobj_status_type status = st::CObjects_attribute_sizes< E >(
                SIZES.data(), st::CObjects_num_pointers< E >(), ptr, slot_size );

            if( status == st::STATUS_SUCCESS )
                status = st::CObjects_attribute_counts< E >( COUNTS.data(),
                    st::CObjects_num_pointers< E >(), ptr, slot_size );

            return ( ( status == st::STATUS_SUCCESS ) &&
                     ( ::NS(CBuffer_can_add_copy_of_object)( this->as_c_api(),
                        st::CObjects_reserved_handle_size< E >( slot_size, ptr ),
                        st::CObjects_num_pointers< E >(), SIZES.data(),
                        COUNTS.data(), requ_buffer_size, requ_n_slots,
                        requ_n_objs, requ_n_ptrs ) ) ); }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_FN obj_index_pointer add_copy_of_object_detailed(
            SIXTRL_CBUFFER_ARGPTR_DEC const void *const SIXTRL_RESTRICT handle,
            size_type const reserved_handle_size,
            size_type const actual_handle_size,
            cobj_obj_id_type const type_id,
            size_type const num_dataptrs,
            SIXTRL_ARGPTR_DEC size_type const* SIXTRL_RESTRICT offsets,
            SIXTRL_ARGPTR_DEC size_type const* SIXTRL_RESTRICT sizes,
            SIXTRL_ARGPTR_DEC size_type const* SIXTRL_RESTRICT counts,
            bool const fill_with_zeros = true ) {
            return ::NS(CBuffer_add_copy_of_object_detailed)( this->as_c_api(),
                handle, reserved_handle_size, actual_handle_size, type_id,
                    num_dataptrs, offsets, sizes, counts, fill_with_zeros ); }

        SIXTRL_FN obj_index_pointer add_copy_of_object(
            SIXTRL_CBUFFER_ARGPTR_DEC const void *const SIXTRL_RESTRICT handle,
            size_type const handle_size,
            cobj_obj_id_type const type_id,
            size_type const num_dataptrs,
            SIXTRL_ARGPTR_DEC size_type const* SIXTRL_RESTRICT offsets,
            SIXTRL_ARGPTR_DEC size_type const* SIXTRL_RESTRICT sizes,
            SIXTRL_ARGPTR_DEC size_type const* SIXTRL_RESTRICT counts,
            bool const fill_with_zeros = true ) {
            return ::NS(CBuffer_add_copy_of_object)( this->as_c_api(), handle,
                handle_size, type_id, num_dataptrs, offsets, sizes, counts,
                    fill_with_zeros ); }

        SIXTRL_FN obj_index_pointer add_copy_of_trivial_object(
            SIXTRL_CBUFFER_ARGPTR_DEC const void *const SIXTRL_RESTRICT handle,
            size_type const handle_size, cobj_obj_id_type const type_id,
            bool const fill_with_zeros = true ) {
            return ::NS(CBuffer_add_copy_of_trivial_object)( this->as_c_api(),
                handle, handle_size, type_id, fill_with_zeros ); }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        template< class E >
        SIXTRL_FN typename std::enable_if<
            !SIXTRL_CXX_NAMESPACE::CObjects_is_legal_type< E >(),
            typename CObjectsStoreResultTypeTraits< E >::pointer >::type
        add_copy( typename CObjectsCopyArgTypeTraits< E >::const_pointer
            const SIXTRL_RESTRICT SIXTRL_UNUSED( ptr ) ) SIXTRL_NOEXCEPT {
                return nullptr; }

        template< class E >
        SIXTRL_FN typename std::enable_if<
            SIXTRL_CXX_NAMESPACE::CObjects_is_legal_type< E >() &&
            SIXTRL_CXX_NAMESPACE::CObjects_is_trivial_type< E >(),
            typename CObjectsStoreResultTypeTraits< E >::pointer >::type
        add_copy( typename CObjectsCopyArgTypeTraits< E >::const_pointer const
            SIXTRL_RESTRICT ptr ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            auto const slot_size = ::NS(CBuffer_slot_size)( this->as_c_api() );
            SIXTRL_ASSERT( slot_size > size_type{ 0 } );
            return st::CObjIndex_to_elem< E >(
                ::NS(CBuffer_add_copy_of_trivial_object)( this->as_c_api(),
                ptr, st::CObjects_reserved_handle_size< E >( slot_size, ptr ),
                st::CObjects_type_id< E >(), true ), slot_size, ptr );
        }

        template< class E >
        SIXTRL_FN typename std::enable_if<
            (  SIXTRL_CXX_NAMESPACE::CObjects_is_legal_type< E >() ) &&
            ( !SIXTRL_CXX_NAMESPACE::CObjects_is_trivial_type< E >() ) &&
            (  SIXTRL_CXX_NAMESPACE::CObjects_num_pointers< E >() ==
               SIXTRL_CXX_NAMESPACE::cobj_size_type{ 0 } ),
            typename CObjectsStoreResultTypeTraits< E >::pointer >::type
        add_copy( typename CObjectsCopyArgTypeTraits< E >::const_pointer const
            SIXTRL_RESTRICT ptr ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            auto const slot_size = ::NS(CBuffer_slot_size)( this->as_c_api() );
            SIXTRL_ASSERT( slot_size > size_type{ 0 } );
            return st::CObjIndex_to_elem< E >(
                ::NS(CBuffer_add_copy_of_object_detailed)( this->as_c_api(),
                    ptr,
                    st::CObjects_reserved_handle_size< E >( slot_size, ptr ),
                    st::CObjects_actual_handle_size< E >( slot_size, ptr ),
                    st::CObjects_type_id< E >(),
                    st::CObjects_num_pointers< E >(),
                    nullptr, nullptr, nullptr, true ), slot_size, ptr ); }

        template< class E >
        SIXTRL_FN typename std::enable_if<
            (  SIXTRL_CXX_NAMESPACE::CObjects_is_legal_type< E >() ) &&
            ( !SIXTRL_CXX_NAMESPACE::CObjects_is_trivial_type< E >() ) &&
            (  SIXTRL_CXX_NAMESPACE::CObjects_num_pointers< E >() >
               SIXTRL_CXX_NAMESPACE::cobj_size_type{ 0 } ) &&
            (  SIXTRL_CXX_NAMESPACE::CObjects_num_pointers< E >() <=
               SIXTRL_CXX_NAMESPACE::cobj_size_type{ 25 } ),
               typename CObjectsStoreResultTypeTraits< E >::pointer >::type
        add_copy( typename CObjectsCopyArgTypeTraits< E >::const_pointer const
            SIXTRL_RESTRICT ptr ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            auto const slot_size = ::NS(CBuffer_slot_size)( this->as_c_api() );
            SIXTRL_ASSERT( slot_size > size_type{ 0 } );

            obj_index_pointer ptr_added_elem = nullptr;
            static size_type constexpr MAX_NUM_PTRS = size_type{ 25 };

            SIXTRL_ARGPTR_DEC size_type OFFSETS[ MAX_NUM_PTRS ];
            SIXTRL_ARGPTR_DEC size_type SIZES[ MAX_NUM_PTRS ];
            SIXTRL_ARGPTR_DEC size_type COUNTS[ MAX_NUM_PTRS ];

            st::cobj_status_type status = st::CObjects_attribute_offsets< E >(
                &OFFSETS[ 0 ], MAX_NUM_PTRS, ptr, slot_size );

            if( status == st::STATUS_SUCCESS )
                status = st::CObjects_attribute_sizes< E >(
                    &SIZES[ 0 ], MAX_NUM_PTRS, ptr, slot_size );

            if( status == st::STATUS_SUCCESS )
                status = st::CObjects_attribute_counts< E >(
                    &COUNTS[ 0 ], MAX_NUM_PTRS, ptr, slot_size );

            if( status == st::STATUS_SUCCESS ) {
                ptr_added_elem = ::NS(CBuffer_add_copy_of_object_detailed)(
                    this->as_c_api(), ptr,
                    st::CObjects_reserved_handle_size< E >( slot_size, ptr ),
                    st::CObjects_actual_handle_size< E >( slot_size, ptr ),
                    st::CObjects_type_id< E >(),
                    st::CObjects_num_pointers< E >(),
                    &OFFSETS[ 0 ], &SIZES[ 0 ], &COUNTS[ 0 ], true ); }

            return  st::CObjIndex_to_elem< E >(
                ptr_added_elem, slot_size, ptr ); }

        template< class E >
        SIXTRL_FN typename std::enable_if<
            (  SIXTRL_CXX_NAMESPACE::CObjects_is_legal_type< E >() ) &&
            ( !SIXTRL_CXX_NAMESPACE::CObjects_is_trivial_type< E >() ) &&
            (  SIXTRL_CXX_NAMESPACE::CObjects_num_pointers< E >() >
               SIXTRL_CXX_NAMESPACE::cobj_size_type{ 25 } ),
               typename CObjectsStoreResultTypeTraits< E >::pointer >::type
        add_copy( typename CObjectsCopyArgTypeTraits< E >::const_pointer const
            SIXTRL_RESTRICT ptr ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            auto const slot_size = ::NS(CBuffer_slot_size)( this->as_c_api() );
            SIXTRL_ASSERT( slot_size > size_type{ 0 } );

            obj_index_pointer ptr_added_elem = nullptr;
            size_type const nptrs = st::CObjects_num_pointers< E >();
            SIXTRL_ASSERT( nptrs > size_type{ 25 } );

            std::vector< size_type > OFFSETS( nptrs, size_type{ 0 } );
            std::vector< size_type > SIZES(   nptrs, size_type{ 0 } );
            std::vector< size_type > COUNTS(  nptrs, size_type{ 0 } );

            st::cobj_status_type status = st::CObjects_attribute_offsets< E >(
                    OFFSETS.data(), OFFSETS.size(), ptr, slot_size );

            if( status == st::STATUS_SUCCESS )
                status = st::CObjects_attribute_sizes< E >(
                    SIZES.data(), SIZES.size(), ptr, slot_size );

            if( status == st::STATUS_SUCCESS )
                status = st::CObjects_attribute_counts< E >(
                    COUNTS.data(), COUNTS.size(), ptr, slot_size );

            if( status == st::STATUS_SUCCESS ) {
                ptr_added_elem = ::NS(CBuffer_add_copy_of_object_detailed)(
                    this->as_c_api(), ptr,
                    st::CObjects_reserved_handle_size< E >( slot_size, ptr ),
                    st::CObjects_actual_handle_size< E >( slot_size, ptr ),
                    st::CObjects_type_id< E >(), nptrs,
                    OFFSETS.data(), SIZES.data(), COUNTS.data(), true ); }

            return st::CObjIndex_to_elem< E >( ptr_added_elem, slot_size, ptr );
        }

        template< class E >
        SIXTRL_FN typename CObjectsStoreResultTypeTraits< E >::pointer
        add_copy( typename CObjectsCopyArgTypeTraits< E >::const_reference
            SIXTRL_RESTRICT_REF orig ) SIXTRL_NOEXCEPT {
            return this->add_copy< E >( std::addressof( orig ) ); }
    };

    #if !defined( _GPUCODE )
    SIXTRL_STATIC SIXTRL_FN CBufferView::status_type
    CBuffer_to_file( CBufferView& SIXTRL_RESTRICT_REF view,
                     std::string const& SIXTRL_RESTRICT_REF path_to_file );

    SIXTRL_STATIC SIXTRL_FN CBufferView::status_type
    CBuffer_to_file( CBufferView& SIXTRL_RESTRICT_REF view,
                     char const* SIXTRL_RESTRICT path_to_file );

    SIXTRL_STATIC SIXTRL_FN CBufferView::status_type
    CBuffer_to_file( CBufferView& SIXTRL_RESTRICT_REF view,
                     std::string const& SIXTRL_RESTRICT_REF path_to_file,
                     CBufferView::addr_type const norm_base_addr );

    SIXTRL_STATIC SIXTRL_FN CBufferView::status_type
    CBuffer_to_file( CBufferView& SIXTRL_RESTRICT_REF view,
                     char const* SIXTRL_RESTRICT path_to_file,
                     CBufferView::addr_type const norm_base_addr );

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_STATIC SIXTRL_FN CBufferView::status_type
    CBuffer_to_file_normalised( CBufferView& SIXTRL_RESTRICT_REF view,
                     std::string const& SIXTRL_RESTRICT_REF path_to_file,
                     CBufferView::addr_type const norm_base_addr );

    SIXTRL_STATIC SIXTRL_FN CBufferView::status_type
    CBuffer_to_file_normalised( CBufferView& SIXTRL_RESTRICT_REF view,
                     char const* SIXTRL_RESTRICT path_to_file,
                     CBufferView::addr_type const norm_base_addr );

    /* --------------------------------------------------------------------- */

    SIXTRL_STATIC SIXTRL_FN CBufferView::status_type
    CBuffer_from_file( CBufferView& SIXTRL_RESTRICT_REF view,
        std::string const& SIXTRL_RESTRICT_REF path_to_file );

    SIXTRL_STATIC SIXTRL_FN CBufferView::status_type
    CBuffer_from_file( CBufferView& SIXTRL_RESTRICT_REF view,
        char const* SIXTRL_RESTRICT path_to_file );

    #endif /* !defined( _GPUCODE ) */
}

#if !defined( _GPUCODE )
extern "C" {
#endif /* !defined( _GPUCODE ) */

typedef SIXTRL_CXX_NAMESPACE::CBufferView NS(CBufferView);

#if !defined( _GPUCODE )
}
#endif /* !defined( _GPUCODE ) */

#else

typedef struct NS(CBufferView) NS(CBufferView);

#endif /* __cplusplus */

/* ************************************************************************* */
/* Implementation of inline methods and functions */
/* ************************************************************************* */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    SIXTRL_INLINE CBufferView::CBufferView(
        CBufferView::addr_type const base_addr,
        CBufferView::size_type const capacity,
        CBufferView::size_type const slot_size,
        CBufferView::flags_type const flags ) SIXTRL_NOEXCEPT
        : ::NS(CBuffer){ CBufferView::NULL_ADDRESS,
            CBufferView::DEFAULT_SLOT_SIZE,
            CBufferView::size_type{ 0u },
            CBufferView::size_type{ 1u }, CBufferView::size_type{ 1u },
            CBufferView::FLAGS_NONE, CBufferView::NULL_ADDRESS }
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        st::cobj_status_type status = st::STATUS_GENERAL_FAILURE;

        if( ( base_addr == st::CBufferView::NULL_ADDRESS ) &&
            ( st::CBufferView::IS_FLAG_SET( flags,
              st::CBufferView::FLAGS_OWNS_STORED_DATA ) ) )
        {
            status = ::NS(CBuffer_init_as_buffer)( this->as_c_api(), capacity );
        }
        else if( base_addr != st::CBufferView::NULL_ADDRESS )
        {
            status = ::NS(CBuffer_init_as_view_detailed)(
                this->as_c_api(), base_addr, slot_size, capacity, flags );
        }

        if( status != st::STATUS_SUCCESS )
        {
            this->m_base_addr = CBufferView::NULL_ADDRESS;
            this->m_slot_size = CBufferView::DEFAULT_SLOT_SIZE;
            this->m_capacity  = CBufferView::size_type{ 0 };
            this->m_reserve_factor_nominator =
            this->m_reserve_factor_denominator = CBufferView::size_type{ 1 };
            this->m_buffer_flags = CBufferView::FLAGS_NONE;
            this->m_datastore_addr = CBufferView::NULL_ADDRESS;
        }
    }

    /* ---------------------------------------------------------------------- */

    SIXTRL_INLINE CBufferView::CBufferView(
        SIXTRL_CBUFFER_ARGPTR_DEC CBufferView const& orig ) :
        ::NS(CBuffer){ CBufferView::NULL_ADDRESS,
            CBufferView::DEFAULT_SLOT_SIZE,
            CBufferView::size_type{ 0u },
            CBufferView::size_type{ 1u }, CBufferView::size_type{ 1u },
            CBufferView::FLAGS_NONE, CBufferView::NULL_ADDRESS }
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef st::CBufferView this_type;

        this_type::status_type status = st::STATUS_GENERAL_FAILURE;
        if( ( orig.base_address() !=  this_type::NULL_ADDRESS ) &&
            ( !this_type::IS_FLAG_SET( orig.flags(),
               this_type::FLAGS_OWNS_STORED_DATA ) ) &&
            ( orig.slot_size() >  this_type::size_type{ 0 } ) &&
            ( orig.capacity()  >= this_type::DEFAULT_MINIMAL_SIZE ) )
        {
            status = ::NS(CBuffer_init_as_view_detailed)( this->as_c_api(),
                orig.base_address(), orig.slot_size(), orig.capacity(),
                    orig.flags() );
        }
        else if( ( orig.base_address() != this_type::NULL_ADDRESS ) &&
                 ( this_type::IS_FLAG_SET( orig.flags(),
                   this_type::FLAGS_OWNS_STORED_DATA ) ) &&
                 ( this_type::IS_FLAG_SET( orig.flags(),
                   this_type::FLAGS_ALLOW_REMAPPING ) ) &&
                (  orig.slot_size() >  this_type::size_type{ 0 } ) &&
                (  orig.capacity()  >= this_type::DEFAULT_MINIMAL_SIZE ) )
        {
            status = ::NS(CBuffer_init_as_copy_of_cbuffer)(
                    this->as_c_api(), orig.as_c_api() );
        }

        #if !defined( _GPUCODE )
        if( status != st::STATUS_SUCCESS )
        {
            throw std::runtime_error(
                "unable to construct view or buffer as a copy" );
        }
        #else /* defined( _GPUCODE ) */
        SIXTRL_ASSERT( status == ::NS(cobj_status_type){SIXTRL_STATUS_SUCCESS});
        ( void )status;
        #endif /* !defined( _GPUCODE ) */
    }

    SIXTRL_INLINE CBufferView::CBufferView(
        SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer) const& SIXTRL_RESTRICT_REF b ) :
        ::NS(CBuffer){ CBufferView::NULL_ADDRESS,
            CBufferView::DEFAULT_SLOT_SIZE,
            CBufferView::size_type{ 0u },
            CBufferView::size_type{ 1u }, CBufferView::size_type{ 1u },
            CBufferView::FLAGS_NONE, CBufferView::NULL_ADDRESS }
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef st::CBufferView this_type;

        this_type::status_type status = st::STATUS_GENERAL_FAILURE;
        if( ( ::NS(CBuffer_base_address)( &b ) !=  this_type::NULL_ADDRESS ) &&
            ( !this_type::IS_FLAG_SET( ::NS(CBuffer_flags)( &b ),
               this_type::FLAGS_OWNS_STORED_DATA ) ) &&
            ( ::NS(CBuffer_slot_size)( &b ) >  this_type::size_type{ 0 } ) &&
            ( ::NS(CBuffer_capacity)( &b ) >= this_type::DEFAULT_MINIMAL_SIZE ) )
        {
            status = ::NS(CBuffer_init_as_view_detailed)( this->as_c_api(),
                ::NS(CBuffer_base_address)( &b ), ::NS(CBuffer_capacity)( &b ),
                    ::NS(CBuffer_slot_size)( &b ), ::NS(CBuffer_flags)( &b ) );
        }
        else if( ( ::NS(CBuffer_base_address)( &b ) !=
                   this_type::NULL_ADDRESS ) &&
                 ( this_type::IS_FLAG_SET( ::NS(CBuffer_flags)( &b ),
                   this_type::FLAGS_OWNS_STORED_DATA ) ) &&
                 ( this_type::IS_FLAG_SET( ::NS(CBuffer_flags)( &b ),
                   this_type::FLAGS_ALLOW_REMAPPING ) ) &&
                (  ::NS(CBuffer_slot_size)( &b ) >
                   this_type::size_type{ 0 } ) &&
                (  ::NS(CBuffer_capacity)( &b ) >=
                   this_type::DEFAULT_MINIMAL_SIZE ) )
        {
            status = ::NS(CBuffer_init_as_copy_of_cbuffer)(
                this->as_c_api(), &b );
        }

        #if !defined( _GPUCODE )
        if( status != st::STATUS_SUCCESS )
        {
            throw std::runtime_error(
                "unable to construct view or buffer as a copy" );
        }
        #else /* defined( _GPUCODE ) */
        SIXTRL_ASSERT( status == ::NS(cobj_status_type){SIXTRL_STATUS_SUCCESS});
        ( void )status;
        #endif /* !defined( _GPUCODE ) */
    }

    SIXTRL_INLINE CBufferView::CBufferView(
        SIXTRL_CBUFFER_ARGPTR_DEC CBufferView&& orig ) SIXTRL_NOEXCEPT  :
        ::NS(CBuffer){ orig.base_address(), orig.slot_size(), orig.capacity(),
            orig.reserve_factor_nominator(), orig.reserve_factor_denominator(),
            orig.flags(), CBufferView::NULL_ADDRESS }
    {
        typedef SIXTRL_CXX_NAMESPACE::CBufferView this_type;
        orig.m_reserve_factor_nominator   = this_type::size_type{ 1 };
        orig.m_reserve_factor_denominator = this_type::size_type{ 1 };

        orig.m_base_addr       = this_type::NULL_ADDRESS;
        orig.m_slot_size       = this_type::size_type{ 0u };
        orig.m_capacity        = this_type::size_type{ 0u };
        orig.m_buffer_flags    = this_type::FLAGS_NONE;

        this->m_datastore_addr = std::move( orig.m_datastore_addr );
        orig.m_datastore_addr  = this_type::NULL_ADDRESS;
    }

    SIXTRL_INLINE CBufferView::CBufferView(
        SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer)&& orig ) SIXTRL_NOEXCEPT :
        ::NS(CBuffer){
            ::NS(CBuffer_base_address)( &orig ),
            ::NS(CBuffer_slot_size)( &orig ),
            ::NS(CBuffer_capacity)( &orig ),
            ::NS(CBuffer_reserve_factor_nominator)( &orig ),
            ::NS(CBuffer_reserve_factor_denominator)( &orig ),
            ::NS(CBuffer_flags)( &orig ),
            CBufferView::NULL_ADDRESS }
    {
        typedef SIXTRL_CXX_NAMESPACE::CBufferView this_type;

        orig.m_reserve_factor_nominator   = this_type::size_type{ 1 };
        orig.m_reserve_factor_denominator = this_type::size_type{ 1 };

        orig.m_base_addr       = this_type::NULL_ADDRESS;
        orig.m_slot_size       = this_type::size_type{ 0u };
        orig.m_capacity        = this_type::size_type{ 0u };
        orig.m_buffer_flags    = this_type::FLAGS_NONE;

        this->m_datastore_addr = std::move( orig.m_datastore_addr );
        orig.m_datastore_addr  = this_type::NULL_ADDRESS;
    }

    /* ---------------------------------------------------------------------- */

    SIXTRL_INLINE SIXTRL_CBUFFER_ARGPTR_DEC CBufferView& CBufferView::operator=(
        SIXTRL_CBUFFER_ARGPTR_DEC CBufferView const& rhs )
    {
        if( &rhs != this )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            st::cobj_status_type status = ::NS(CBuffer_init_as_copy_of_cbuffer)(
                this->as_c_api(), rhs.as_c_api() );

            #if !defined( _GPUCODE )
            if( status != st::STATUS_SUCCESS )
            {
                throw std::runtime_error( "unable to perform copy assignment" );
            }
            #else /* defined( _GPUCODE ) */
            SIXTRL_ASSERT( status == ::NS(cobj_status_type){
                    SIXTRL_STATUS_SUCCESS } );
            ( void )status;
            #endif /* !defined( _GPUCODE ) */
        }

        return *this;
    }

    SIXTRL_INLINE SIXTRL_CBUFFER_ARGPTR_DEC CBufferView& CBufferView::operator=(
        SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer) const& SIXTRL_RESTRICT_REF rhs )
    {
        if( &rhs != this->as_const_c_api() )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            st::cobj_status_type status = ::NS(CBuffer_init_as_copy_of_cbuffer)(
                this->as_c_api(), &rhs );

            #if !defined( _GPUCODE )
            if( status != st::STATUS_SUCCESS )
            {
                throw std::runtime_error( "unable to perform copy assignment" );
            }
            #else /* defined( _GPUCODE ) */
            SIXTRL_ASSERT( status == ::NS(cobj_status_type){
                    SIXTRL_STATUS_SUCCESS } );
            ( void )status;
            #endif /* !defined( _GPUCODE ) */
        }

        return *this;
    }

    SIXTRL_INLINE SIXTRL_CBUFFER_ARGPTR_DEC CBufferView& CBufferView::operator=(
        SIXTRL_CBUFFER_ARGPTR_DEC CBufferView&& rhs ) SIXTRL_NOEXCEPT {
        return CBufferView::operator=( *rhs.as_const_c_api() ); }

    SIXTRL_INLINE SIXTRL_CBUFFER_ARGPTR_DEC CBufferView& CBufferView::operator=(
            SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer)&& rhs ) SIXTRL_NOEXCEPT {
        typedef SIXTRL_CXX_NAMESPACE::CBufferView this_type;
        if( this->as_c_api() != &rhs )
        {
            if( this->owns_stored_data() )
            {
                if( this->storage_is_c_ptr() ) {
                    ::NS(CBuffer_free_c99_ptr_store)( this->m_datastore_addr );
                    this->m_datastore_addr = this_type::NULL_ADDRESS; }
                else if( this->storage_is_cxx_vector() ) {
                    ::NS(CBuffer_free_cxx_vector_store)( this->m_datastore_addr );
                    this->m_datastore_addr = this_type::NULL_ADDRESS; }
            }

            SIXTRL_ASSERT( this->m_datastore_addr == this_type::NULL_ADDRESS );

            this->m_base_addr = std::move( rhs.m_base_addr );
            rhs.m_base_addr   = this_type::NULL_ADDRESS;

            this->m_slot_size = std::move( rhs.m_slot_size );
            rhs.m_slot_size   = this_type::size_type{ 0 };

            this->m_capacity  = std::move( rhs.m_capacity );
            rhs.m_capacity    = this_type::size_type{ 0 };

            this->m_reserve_factor_nominator =
                std::move( rhs.m_reserve_factor_nominator );
            rhs.m_reserve_factor_nominator = this_type::size_type{ 1 };

            this->m_reserve_factor_denominator = std::move(
                rhs.m_reserve_factor_denominator );
            rhs.m_reserve_factor_denominator = this_type::size_type{ 1 };

            this->m_buffer_flags = std::move( rhs.m_buffer_flags );
            rhs.m_buffer_flags   = this_type::FLAGS_NONE;

            this->m_datastore_addr = std::move( rhs.m_datastore_addr );
            rhs.m_datastore_addr   = this_type::NULL_ADDRESS;
        }

        return *this;
    }

    SIXTRL_INLINE CBufferView::~CBufferView() SIXTRL_NOEXCEPT {
        typedef SIXTRL_CXX_NAMESPACE::CBufferView this_type;

        if( ( this->owns_stored_data() ) && ( this->p_const_base() != nullptr ) )
        {
            SIXTRL_ASSERT( !this->has_special_memory() );
            SIXTRL_ASSERT(  this->storage_is_c_ptr() ||
                            this->storage_is_cxx_vector() );

            if( this->storage_is_c_ptr() ) {
                ::NS(CBuffer_free_c99_ptr_store)( this->m_datastore_addr );
                this->m_datastore_addr = this_type::NULL_ADDRESS;
            }
            else if( this->storage_is_cxx_vector() ) {
                ::NS(CBuffer_free_cxx_vector_store)( this->m_datastore_addr );
                this->m_datastore_addr = this_type::NULL_ADDRESS;
            }
        }

        SIXTRL_ASSERT( this->m_datastore_addr == this_type::NULL_ADDRESS );

        this->m_base_addr = this_type::NULL_ADDRESS;;
        this->m_slot_size = this_type::size_type{ 0u };
        this->m_capacity  = this_type::size_type{ 0u };

        this->m_reserve_factor_nominator   = this_type::size_type{ 1 };
        this->m_reserve_factor_denominator = this_type::size_type{ 1 };
        this->m_buffer_flags = this_type::FLAGS_NONE; }

    /* ---------------------------------------------------------------------- */

    SIXTRL_INLINE CBufferView::status_type CBuffer_to_file(
        CBufferView& SIXTRL_RESTRICT_REF view,
        std::string const& SIXTRL_RESTRICT_REF path_to_file ) {
        return ::NS(CBuffer_to_file)( view.as_c_api(), path_to_file.c_str() ); }

    SIXTRL_INLINE CBufferView::status_type CBuffer_to_file(
        CBufferView& SIXTRL_RESTRICT_REF view,
        char const* SIXTRL_RESTRICT path_to_file ) {
        return ::NS(CBuffer_to_file)( view.as_c_api(), path_to_file ); }

    SIXTRL_INLINE CBufferView::status_type CBuffer_to_file(
        CBufferView& SIXTRL_RESTRICT_REF view,
        std::string const& SIXTRL_RESTRICT_REF path_to_file,
        CBufferView::addr_type const norm_base_addr ) {
        return ::NS(CBuffer_to_file_normalised)( view.as_c_api(),
            path_to_file.c_str(), norm_base_addr ); }

    SIXTRL_INLINE CBufferView::status_type CBuffer_to_file(
        CBufferView& SIXTRL_RESTRICT_REF view,
        char const* SIXTRL_RESTRICT path_to_file,
        CBufferView::addr_type const norm_base_addr ) {
        return ::NS(CBuffer_to_file_normalised)(
            view.as_c_api(), path_to_file, norm_base_addr ); }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE CBufferView::status_type CBuffer_to_file_normalised(
        CBufferView& SIXTRL_RESTRICT_REF view,
        std::string const& SIXTRL_RESTRICT_REF path_to_file,
        CBufferView::addr_type const norm_base_addr ) {
        return ::NS(CBuffer_to_file_normalised)( view.as_c_api(),
            path_to_file.c_str(), norm_base_addr ); }

    SIXTRL_INLINE CBufferView::status_type CBuffer_to_file_normalised(
        CBufferView& SIXTRL_RESTRICT_REF view,
        char const* SIXTRL_RESTRICT path_to_file,
        CBufferView::addr_type const norm_base_addr ) {
        return ::NS(CBuffer_to_file_normalised)(
            view.as_c_api(), path_to_file, norm_base_addr ); }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE CBufferView::status_type
    CBuffer_from_file( CBufferView& SIXTRL_RESTRICT_REF view,
        std::string const& SIXTRL_RESTRICT_REF path_to_file ) {
        return ::NS(CBuffer_from_file)( view.as_c_api(), path_to_file.c_str() );
    }

    SIXTRL_INLINE CBufferView::status_type
    CBuffer_from_file( CBufferView& SIXTRL_RESTRICT_REF view,
        char const* SIXTRL_RESTRICT path_to_file ) {
        return ::NS(CBuffer_from_file)( view.as_c_api(), path_to_file ); }


} /* end: SIXTRL_CXX_NAMESPACE */
#endif /* defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_COBJECTS_CBUFFER_VIEW_CXX_HPP__*/
