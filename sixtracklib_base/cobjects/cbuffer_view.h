#ifndef SIXTRACKLIB_BASE_COBJECTS_CBUFFER_VIEW_H__
#define SIXTRACKLIB_BASE_COBJECTS_CBUFFER_VIEW_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/cobjects/definitions.h"
    #include "sixtracklib_base/cobjects/index_object.h"
    #include "sixtracklib_base/cobjects/garbage_range.h"
    #include "sixtracklib_base/cobjects/element_traits.h"
    #include "sixtracklib_base/cobjects/obj_delegate.h"
    #include "sixtracklib_base/internal/compiler_attributes.h"
    #include "sixtracklib_base/internal/obj_convert.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <cstdlib>
        #include <iostream>
        #include <string>
        #include <type_traits>
        #include <vector>
    #endif /* C++ */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    class CBufferView
    {
        public:

        typedef SIXTRL_CXX_NAMESPACE::size_t              size_type;
        typedef SIXTRL_CXX_NAMESPACE::cobj_type_id_t      type_id_t;
        typedef SIXTRL_CXX_NAMESPACE::cobj_address_t      address_t;
        typedef SIXTRL_CXX_NAMESPACE::status_t            status_t;
        typedef SIXTRL_CXX_NAMESPACE::cobj_address_diff_t address_diff_t;
        typedef SIXTRL_CXX_NAMESPACE::cobj_buffer_flags_t flags_t;

        typedef SIXTRL_CXX_NAMESPACE::cobj_raw_t          raw_t;
        typedef SIXTRL_BUFFER_DATAPTR_DEC raw_t*          ptr_raw_data_t;
        typedef SIXTRL_BUFFER_DATAPTR_DEC raw_t const*    ptr_const_raw_data_t;

        typedef SIXTRL_CXX_NAMESPACE::CObjIndex           index_obj_t;
        typedef SIXTRL_CXX_NAMESPACE::ptr_cobj_index_t    ptr_index_obj_t;
        typedef SIXTRL_CXX_NAMESPACE::ptr_const_cobj_index_t
                ptr_const_index_obj_t;

        typedef SIXTRL_BUFFER_DATAPTR_DEC int64_t const*  ptr_const_view_i64_t;
        typedef SIXTRL_BUFFER_DATAPTR_DEC int64_t*        ptr_view_i64_t;
        typedef SIXTRL_CXX_NAMESPACE::store_backend_t     store_be_t;

        static constexpr size_type DEFAULT_SLOT_SIZE       =
            SIXTRL_CXX_NAMESPACE::CBUFFER_DEFAULT_SLOT_SIZE;

        static constexpr size_type DEFAULT_HEADER_SIZE =
            SIXTRL_CXX_NAMESPACE::CBUFFER_DEFAULT_HEADER_SIZE;

        static constexpr size_type BUFFER_MINIMAL_SIZE =
            SIXTRL_CXX_NAMESPACE::CBUFFER_MIN_SIZE;

        static constexpr address_t NULL_ADDRESS =
            SIXTRL_CXX_NAMESPACE::COBJECTS_NULL_ADDRESS;

        static constexpr store_be_t DEFAULT_STORE_BE =
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT;

        static constexpr flags_t FLAGS_NONE            = flags_t{ 0x00000000 };
        static constexpr flags_t FLAGS_ALLOW_REMAPPING = flags_t{ 0x00000001 };
        static constexpr flags_t FLAGS_ALLOW_ALLOC     = flags_t{ 0x00000002 };
        static constexpr flags_t FLAGS_ALLOW_REALLOC   = flags_t{ 0x00000004 };
        static constexpr flags_t FLAGS_ALLOW_APPEND    = flags_t{ 0x00000008 };
        static constexpr flags_t FLAGS_FORCE_INIT      = flags_t{ 0x20000000 };
        static constexpr flags_t FLAGS_OWNS_STORED_DATA= flags_t{ 0x40000000 };
        static constexpr flags_t FLAGS_SPECIAL_MEMORY  = flags_t{ 0x80000000 };

        static constexpr flags_t FLAGS_BASE_DEFAULT =
            FLAGS_ALLOW_REMAPPING | FLAGS_ALLOW_ALLOC |
            FLAGS_ALLOW_REALLOC   | FLAGS_ALLOW_APPEND;

        /* ---------------------------------------------------------------- */

        static SIXTRL_FN flags_t add_flag_to_set(
            flags_t const haystack, flags_t const needle ) SIXTRL_NOEXCEPT;

        static SIXTRL_FN flags_t remove_flag_from_set(
            flags_t const haystack, flags_t const needle ) SIXTRL_NOEXCEPT;

        static SIXTRL_FN bool is_flag_set(
            flags_t const haystack, flags_t const needle ) SIXTRL_NOEXCEPT;

        static SIXTRL_FN size_type required_buffer_length(
            size_type const max_num_slots,
            size_type const max_num_objects,
            size_type const max_num_pointers,
            size_type const max_num_garbage_ranges = size_type{ 0 },
            size_type const slot_size = DEFAULT_SLOT_SIZE ) SIXTRL_NOEXCEPT;

        static SIXTRL_FN address_t aligned_base_addr(
            address_t const raw_base_addr,
            size_type const raw_capacity,
            size_type alignment = size_type{ 1 },
            SIXTRL_ARGPTR_DEC size_type* ptr_capacity = SIXTRL_NULLPTR,
            size_type const slot_size = DEFAULT_SLOT_SIZE ) SIXTRL_NOEXCEPT;


        /* ----------------------------------------------------------------- */

        SIXTRL_FN explicit CBufferView( address_t base_addr = NULL_ADDRESS,
            size_type const slot_size = DEFAULT_SLOT_SIZE,
            size_type const capacity = size_type{ 0 },
            flags_t const flags = FLAGS_BASE_DEFAULT ) SIXTRL_NOEXCEPT;


        SIXTRL_FN CBufferView( SIXTRL_ARGPTR_DEC CBufferView const& ) = default;
        SIXTRL_FN CBufferView( SIXTRL_ARGPTR_DEC CBufferView&& ) = default;

        SIXTRL_FN SIXTRL_ARGPTR_DEC CBufferView& operator=(
            SIXTRL_ARGPTR_DEC CBufferView const& ) = default;

        SIXTRL_FN SIXTRL_ARGPTR_DEC CBufferView& operator=(
            SIXTRL_ARGPTR_DEC CBufferView&& ) = default;

        /* TODO: This is currently non-virtual to retain standard-layout /
         *       trivially copyable status.
         *       NEVER EVER delete an instance of and derived class
         *       via a pointer to CBufferView !!!!! */

        #if defined( _GPUCODE )

        SIXTRL_FN ~CBufferView() = default;

        #else

        SIXTRL_FN virtual ~CBufferView() = default;

        #endif /* defined( _GPUCODE ) */

        /* ----------------------------------------------------------------- */

        SIXTRL_FN flags_t flags() const SIXTRL_NOEXCEPT;

        SIXTRL_FN void _set_flags_dangerous(
            flags_t const flags ) SIXTRL_NOEXCEPT;

        SIXTRL_FN bool allow_remap()        const SIXTRL_NOEXCEPT;
        SIXTRL_FN bool allow_allocate()     const SIXTRL_NOEXCEPT;
        SIXTRL_FN bool allow_realloc()      const SIXTRL_NOEXCEPT;
        SIXTRL_FN bool allow_append()       const SIXTRL_NOEXCEPT;
        SIXTRL_FN bool owns_stored_data()   const SIXTRL_NOEXCEPT;
        SIXTRL_FN bool has_special_memory() const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_FN size_type slot_size() const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_FN size_type size() const SIXTRL_NOEXCEPT;
        SIXTRL_FN size_type capacity() const SIXTRL_NOEXCEPT;
        SIXTRL_FN size_type size_header() const SIXTRL_NOEXCEPT;
        SIXTRL_FN size_type size_section_header(
            size_type const sec_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_FN size_type size_slots()              const SIXTRL_NOEXCEPT;
        SIXTRL_FN size_type size_objects()            const SIXTRL_NOEXCEPT;
        SIXTRL_FN size_type size_pointers()           const SIXTRL_NOEXCEPT;
        SIXTRL_FN size_type size_garbage()            const SIXTRL_NOEXCEPT;

        SIXTRL_FN size_type n_slots()                 const SIXTRL_NOEXCEPT;
        SIXTRL_FN size_type n_objects()               const SIXTRL_NOEXCEPT;
        SIXTRL_FN size_type n_pointers()              const SIXTRL_NOEXCEPT;
        SIXTRL_FN size_type n_garbage()               const SIXTRL_NOEXCEPT;

        SIXTRL_FN size_type max_slots()               const SIXTRL_NOEXCEPT;
        SIXTRL_FN size_type max_objects()             const SIXTRL_NOEXCEPT;
        SIXTRL_FN size_type max_pointers()            const SIXTRL_NOEXCEPT;
        SIXTRL_FN size_type max_garbage()             const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_FN address_t begin_addr()              const SIXTRL_NOEXCEPT;
        SIXTRL_FN address_t end_addr()                const SIXTRL_NOEXCEPT;

        SIXTRL_FN address_t begin_addr_slots()        const SIXTRL_NOEXCEPT;
        SIXTRL_FN address_t begin_addr_objects()      const SIXTRL_NOEXCEPT;
        SIXTRL_FN address_t begin_addr_pointers()     const SIXTRL_NOEXCEPT;
        SIXTRL_FN address_t begin_addr_garbage()      const SIXTRL_NOEXCEPT;

        SIXTRL_FN address_t end_addr_slots()          const SIXTRL_NOEXCEPT;
        SIXTRL_FN address_t end_addr_objects()        const SIXTRL_NOEXCEPT;
        SIXTRL_FN address_t end_addr_pointers()       const SIXTRL_NOEXCEPT;
        SIXTRL_FN address_t end_addr_garbage()        const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_FN address_t base()                    const SIXTRL_NOEXCEPT;
        SIXTRL_FN address_t base_address()            const SIXTRL_NOEXCEPT;
        SIXTRL_FN ptr_const_raw_data_t p_base()       const SIXTRL_NOEXCEPT;
        SIXTRL_FN ptr_const_raw_data_t p_base_begin() const SIXTRL_NOEXCEPT;
        SIXTRL_FN ptr_const_raw_data_t p_base_end()   const SIXTRL_NOEXCEPT;

        SIXTRL_FN ptr_raw_data_t p_base_begin()             SIXTRL_NOEXCEPT;
        SIXTRL_FN ptr_raw_data_t p_base_end()               SIXTRL_NOEXCEPT;

        SIXTRL_FN ptr_raw_data_t       p_base()             SIXTRL_NOEXCEPT;
        SIXTRL_FN ptr_const_raw_data_t p_const_base_begin() SIXTRL_NOEXCEPT;
        SIXTRL_FN ptr_const_raw_data_t p_const_base_end()   SIXTRL_NOEXCEPT;
        SIXTRL_FN ptr_const_raw_data_t p_const_base()       SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_FN ptr_const_raw_data_t p_slots() const         SIXTRL_NOEXCEPT;
        SIXTRL_FN ptr_raw_data_t       p_slots()               SIXTRL_NOEXCEPT;
        SIXTRL_FN ptr_const_raw_data_t p_const_slots()         SIXTRL_NOEXCEPT;

        SIXTRL_FN ptr_const_raw_data_t p_slots_end() const     SIXTRL_NOEXCEPT;
        SIXTRL_FN ptr_const_raw_data_t p_const_slots_end()     SIXTRL_NOEXCEPT;
        SIXTRL_FN ptr_raw_data_t       p_slots_end()           SIXTRL_NOEXCEPT;

        SIXTRL_FN ptr_const_raw_data_t p_objects() const       SIXTRL_NOEXCEPT;
        SIXTRL_FN ptr_raw_data_t       p_objects()             SIXTRL_NOEXCEPT;
        SIXTRL_FN ptr_const_raw_data_t p_const_objects()       SIXTRL_NOEXCEPT;

        SIXTRL_FN ptr_const_raw_data_t p_objects_end() const   SIXTRL_NOEXCEPT;
        SIXTRL_FN ptr_const_raw_data_t p_const_objects_end()   SIXTRL_NOEXCEPT;
        SIXTRL_FN ptr_raw_data_t       p_objects_end()         SIXTRL_NOEXCEPT;


        SIXTRL_FN ptr_const_raw_data_t p_pointers() const      SIXTRL_NOEXCEPT;
        SIXTRL_FN ptr_raw_data_t       p_pointers()            SIXTRL_NOEXCEPT;
        SIXTRL_FN ptr_const_raw_data_t p_const_pointers()      SIXTRL_NOEXCEPT;

        SIXTRL_FN ptr_const_raw_data_t p_pointers_end() const  SIXTRL_NOEXCEPT;
        SIXTRL_FN ptr_const_raw_data_t p_const_pointers_end()  SIXTRL_NOEXCEPT;
        SIXTRL_FN ptr_raw_data_t       p_pointers_end()        SIXTRL_NOEXCEPT;

        SIXTRL_FN ptr_const_raw_data_t p_garbage() const       SIXTRL_NOEXCEPT;
        SIXTRL_FN ptr_raw_data_t       p_garbage()             SIXTRL_NOEXCEPT;
        SIXTRL_FN ptr_const_raw_data_t p_const_garbage()       SIXTRL_NOEXCEPT;

        SIXTRL_FN ptr_const_raw_data_t p_garbage_end() const   SIXTRL_NOEXCEPT;
        SIXTRL_FN ptr_const_raw_data_t p_const_garbage_end()   SIXTRL_NOEXCEPT;
        SIXTRL_FN ptr_raw_data_t       p_garbage_end()         SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_FN ptr_const_index_obj_t objects_begin() const  SIXTRL_NOEXCEPT;
        SIXTRL_FN ptr_index_obj_t       objects_begin()        SIXTRL_NOEXCEPT;
        SIXTRL_FN ptr_const_index_obj_t const_objects_begin()  SIXTRL_NOEXCEPT;

        SIXTRL_FN ptr_const_index_obj_t objects_end() const    SIXTRL_NOEXCEPT;
        SIXTRL_FN ptr_index_obj_t       objects_end()          SIXTRL_NOEXCEPT;
        SIXTRL_FN ptr_const_index_obj_t const_objects_end()    SIXTRL_NOEXCEPT;


        SIXTRL_FN ptr_const_index_obj_t index_at(
            size_type const pos_in_buffer ) const SIXTRL_NOEXCEPT;

        SIXTRL_FN ptr_const_index_obj_t const_index_at(
            size_type const pos_in_buffer ) SIXTRL_NOEXCEPT;

        SIXTRL_FN ptr_index_obj_t index_at(
            size_type const pos_in_buffer ) SIXTRL_NOEXCEPT;

        SIXTRL_FN ptr_const_index_obj_t operator[](
            size_type const pos_in_buffer ) const SIXTRL_NOEXCEPT;

        SIXTRL_FN ptr_index_obj_t operator[](
            size_type const pos_in_buffer ) SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_FN address_diff_t address_to_offset(
            address_t const address ) const SIXTRL_NOEXCEPT;

        SIXTRL_FN address_t offset_to_address(
            address_diff_t const offset ) const SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_FN bool has_capacity_for_allocate(
            size_type const max_num_slots = size_type{ 0 },
            size_type const max_num_objects = size_type{ 0 },
            size_type const max_num_pointers = size_type{ 0 },
            size_type const max_num_garbage_ranges =
                size_type{ 0 } ) const SIXTRL_NOEXCEPT;

        SIXTRL_FN bool can_allocate(
            size_type const max_num_slots = size_type{ 0 },
            size_type const max_num_objects = size_type{ 0 },
            size_type const max_num_pointers = size_type{ 0 },
            size_type const max_num_garbage_ranges =
                size_type{ 0 } ) const SIXTRL_NOEXCEPT;

        SIXTRL_FN status_t allocate(
            size_type const max_num_slots = size_type{ 0 },
            size_type const max_num_objects = size_type{ 0 },
            size_type const max_num_pointers = size_type{ 0 },
            size_type const max_num_garbage_ranges =
                size_type{ 0 } ) SIXTRL_NOEXCEPT;

        SIXTRL_FN status_t reallocate(
            size_type const max_num_slots,
            size_type const max_num_objects,
            size_type const max_num_pointers,
            size_type const max_num_garbage_ranges =
                size_type{ 0 } ) SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_FN bool needs_remapping() const SIXTRL_NOEXCEPT;
        SIXTRL_FN bool can_remap() const SIXTRL_NOEXCEPT;
        SIXTRL_FN status_t remap() SIXTRL_NOEXCEPT;

        /* ***************************************************************** */
        /* ******           READING ELEMENTS FROM THE BUFFER          ****** */
        /* ***************************************************************** */

        template< class T >
        SIXTRL_FN SIXTRL_BUFFER_OBJ_DATAPTR_DEC T const* get_object(
            size_type const pos_in_buffer,
            SIXTRL_BUFFER_ARGPTR_DEC const T *const
                ptr_cls_elem = nullptr ) const SIXTRL_NOEXCEPT;

        template< class T >
        SIXTRL_FN SIXTRL_BUFFER_OBJ_DATAPTR_DEC T const* get_const_object(
            size_type const pos_in_buffer,
            SIXTRL_BUFFER_ARGPTR_DEC const T *const
                ptr_cls_elem = nullptr ) const SIXTRL_NOEXCEPT;

        template< class T >
        SIXTRL_FN SIXTRL_BUFFER_OBJ_DATAPTR_DEC T* get_object(
            size_type const pos_in_buffer,
            SIXTRL_BUFFER_ARGPTR_DEC const T *const
                ptr_cls_elem = nullptr ) SIXTRL_NOEXCEPT;

        /* ***************************************************************** */
        /* *****         SUPPORT FOR STORE / LOAD OPERATIONS          ****** */
        /* ***************************************************************** */

        /* ----------------------------------------------------------------- */
        /* a) check can load/store: */

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* case 1: type neither directly nor via delegate loadable/storable
         *         from/to CBufferView -> return error */

        template< class E, store_backend_t DstStoreT =
                  SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT >
        SIXTRL_FN SIXTRL_INLINE typename std::enable_if<
            ( !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
              !SIXTRL_CXX_NAMESPACE::CObjElem_allow_delegate_storage< E >() ) ||
            ( DstStoreT == SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL ),
            bool >::type
        can_load_object_type( size_type const SIXTRL_UNUSED( pos_in_buffer ),
            SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
                SIXTRL_UNUSED( dst ) ) const
        {
            return false;
        }

        template< class SrcT, class DstT, store_backend_t DstStoreT =
                  SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT >
        SIXTRL_FN SIXTRL_INLINE typename std::enable_if<
            ( !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< SrcT >() &&
              !SIXTRL_CXX_NAMESPACE::CObjElem_allow_delegate_storage<
                  DstT >() ) ||
            ( DstStoreT == SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL ),
            bool >::type
        can_load_object_type_detailed(
            size_type const SIXTRL_UNUSED( pos_in_buffer ),
            SIXTRL_BUFFER_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT
                SIXTRL_UNUSED( dst ) ) const
        {
            return false;
        }

        template< class E, store_backend_t SrcStoreT =
                  SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT >
        SIXTRL_FN SIXTRL_INLINE typename std::enable_if<
            ( !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
              !SIXTRL_CXX_NAMESPACE::CObjElem_allow_delegate_storage< E >() ) ||
            ( SrcStoreT == SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL ),
            bool >::type
        can_store_object_type(SIXTRL_BUFFER_ARGPTR_DEC const E *const
                SIXTRL_RESTRICT SIXTRL_UNUSED( src ) ) const
        {
            return false;
        }

        template< class SrcT, class DstT, store_backend_t SrcStoreT =
                  SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT >
        SIXTRL_FN SIXTRL_INLINE typename std::enable_if<
            ( !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< DstT >() &&
              !SIXTRL_CXX_NAMESPACE::CObjElem_allow_delegate_storage<
                  DstT >() ) ||
            ( SrcStoreT == SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL ),
            bool >::type
        can_store_object_detailed_type(
            size_type const SIXTRL_UNUSED( pos_in_buffer ),
            SIXTRL_BUFFER_ARGPTR_DEC const SrcT *const
                SIXTRL_RESTRICT SIXTRL_UNUSED( src ) ) const
        {
            return false;
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* case 2: directly loadable/storable */

        template< class E, store_backend_t DstStoreT =
                  SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT >
        SIXTRL_FN SIXTRL_INLINE typename std::enable_if<
            DstStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL &&
            SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
           !SIXTRL_CXX_NAMESPACE::CObjElem_allow_delegate_storage< E >(),
            bool >::type
        can_load_object_type( size_type const pos_in_buffer,
            SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT dst ) const
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            constexpr st::store_backend_t SrcStoreT = st::STORAGE_BE_COBJECTS;
            SIXTRL_BUFFER_DATAPTR_DEC const E *const src =
                this->get_object< E >( pos_in_buffer );

            return ( ( dst != SIXTRL_NULLPTR ) && ( src != SIXTRL_NULLPTR ) &&
                     ( ( src == dst ) ||
                       ( st::ObjDataConverter< E, E, SrcStoreT, DstStoreT
                           >::allow( dst, src ) ) ) );
        }

        template< class E, store_backend_t SrcStoreT =
                  SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT >
        SIXTRL_FN SIXTRL_INLINE typename std::enable_if<
            SrcStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL &&
            SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
           !SIXTRL_CXX_NAMESPACE::CObjElem_allow_delegate_storage< E >(),
            bool >::type
        can_store_object_type( size_type const pos_in_buffer,
            SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT src ) const
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            constexpr st::store_backend_t DstStoreT = st::STORAGE_BE_COBJECTS;
            SIXTRL_BUFFER_DATAPTR_DEC E const* dst =
                this->get_object< E >( pos_in_buffer );

            return ( ( dst != SIXTRL_NULLPTR ) && ( src != SIXTRL_NULLPTR ) &&
                     ( ( src == dst ) ||
                       ( st::ObjDataConverter< E, E, SrcStoreT,
                             DstStoreT >::allow( dst, src ) ) ) );
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* case 3: storeable/loadable via delegate */

        template< class DstT, store_backend_t DstStoreT =
                  SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT >
        SIXTRL_FN SIXTRL_INLINE typename std::enable_if<
            DstStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL &&
           !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< DstT >() &&
            SIXTRL_CXX_NAMESPACE::CObjElem_allow_delegate_storage< DstT >(),
            bool >::type
        can_load_object_type( size_type const pos_in_buffer, SIXTRL_BUFFER_ARGPTR_DEC
            const DstT *const SIXTRL_RESTRICT dst ) const
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            constexpr st::store_backend_t SrcStoreT = st::STORAGE_BE_COBJECTS;
            typedef st::ObjDataDelegateTraits< DstT > delegate_traits_t;
            typedef typename delegate_traits_t::delegate_t SrcT;

            static_assert( !st::ObjData_is_specific_illegal_type< SrcT >(),
                           "SrcT required to be a legal type" );

            static_assert( !std::is_same< SrcT, DstT >::value,
                "SrcT and DstT are expected to be different types" );

            SIXTRL_BUFFER_DATAPTR_DEC SrcT const* src =
                this->get_object< SrcT >( pos_in_buffer );

            SIXTRL_ASSERT( ( src == SIXTRL_NULLPTR ) ||
                ( reinterpret_cast< std::uintptr_t >( dst ) !=
                  reinterpret_cast< std::uintptr_t >( src ) ) );

            return  ( ( src != SIXTRL_NULLPTR ) && ( dst != SIXTRL_NULLPTR ) &&
                      ( st::ObjDataConverter< SrcT, DstT, SrcStoreT, DstStoreT
                          >::allow( dst, src ) ) );
        }

        template< class SrcT, store_backend_t SrcStoreT =
                  SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT >
        SIXTRL_FN SIXTRL_INLINE typename std::enable_if<
            SrcStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL &&
           !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< SrcT >() &&
            SIXTRL_CXX_NAMESPACE::CObjElem_allow_delegate_storage< SrcT >(),
            bool >::type
        can_store_object_type( size_type const pos_in_buffer,
            SIXTRL_BUFFER_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) const
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            constexpr st::store_backend_t DstStoreT = st::STORAGE_BE_COBJECTS;
            typedef st::ObjDataDelegateTraits< SrcT > delegate_traits_t;
            typedef typename delegate_traits_t::delegate_t DstT;

            static_assert( !st::ObjData_is_specific_illegal_type< DstT >(),
                           "DstT required to be a legal type" );

            static_assert( !std::is_same< SrcT, DstT >::value,
                "SrcT and DstT are expected to be different types" );

            SIXTRL_BUFFER_DATAPTR_DEC DstT const* dst =
                this->get_object< DstT >( pos_in_buffer );

            SIXTRL_ASSERT( ( dst == SIXTRL_NULLPTR ) ||
                ( reinterpret_cast< std::uintptr_t >( dst ) !=
                  reinterpret_cast< std::uintptr_t >( src ) ) );

            return  ( ( src != SIXTRL_NULLPTR ) && ( dst != SIXTRL_NULLPTR ) &&
                      ( st::ObjDataConverter< SrcT, DstT, SrcStoreT, DstStoreT
                          >::allow( dst, src ) ) );
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* case 4: explicit SrcT, DstT storeable/loadable */

        template< class SrcT, class DstT, store_backend_t DstStoreT =
                  SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT >
        SIXTRL_FN SIXTRL_INLINE typename std::enable_if<
            DstStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL &&
            SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< SrcT >(),
            bool >::type
        can_load_object_type_detailed(
            size_type const pos_in_buffer,
            SIXTRL_BUFFER_ARGPTR_DEC const DstT *const SIXTRL_RESTRICT dst
        ) const
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            constexpr st::store_backend_t SrcStoreT = st::STORAGE_BE_COBJECTS;
            SIXTRL_BUFFER_DATAPTR_DEC SrcT const* src =
                this->get_object< SrcT >( pos_in_buffer );

            bool can_load = false;

            if( ( dst != SIXTRL_NULLPTR ) && ( src != SIXTRL_NULLPTR ) )
            {
                if( ( !std::is_same< SrcT, DstT >::value ) ||
                    ( reinterpret_cast< std::uintptr_t >( src ) !=
                      reinterpret_cast< std::uintptr_t >( dst ) ) )
                {
                    can_load = st::ObjDataConverter< SrcT, DstT, SrcStoreT,
                        DstStoreT >::allow( dst, src );
                }
                else can_load = true;
            }

            return can_load;
        }

        template< class SrcT, class DstT, store_backend_t SrcStoreT =
                  SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT >
        SIXTRL_FN SIXTRL_INLINE typename std::enable_if<
            SrcStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL &&
            SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< DstT >(),
            bool >::type
        can_store_object_detailed_type(
            size_type const pos_in_buffer,
            SIXTRL_BUFFER_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) const
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            constexpr st::store_backend_t DstStoreT = st::STORAGE_BE_COBJECTS;
            SIXTRL_BUFFER_DATAPTR_DEC DstT const* dst =
                this->get_object< DstT >( pos_in_buffer );

            bool can_load = false;

            if( ( dst != SIXTRL_NULLPTR ) && ( src != SIXTRL_NULLPTR ) )
            {
                if( ( !std::is_same< SrcT, DstT >::value ) ||
                    ( reinterpret_cast< std::uintptr_t >( src ) !=
                      reinterpret_cast< std::uintptr_t >( dst ) ) )
                {
                    can_load = st::ObjDataConverter< SrcT, DstT, SrcStoreT,
                        DstStoreT >::allow( dst, src );
                }
                else can_load = true;
            }

            return can_load;
        }

        /* ----------------------------------------------------------------- */
        /* b) prepare for load/store object */

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* case 1: type neither directly nor via delegate loadable/storable
         *         from/to CBufferView -> return error */

        template< class E, store_backend_t DstStoreT =
                  SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT >
        SIXTRL_FN SIXTRL_INLINE typename std::enable_if<
            ( !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
              !SIXTRL_CXX_NAMESPACE::CObjElem_allow_delegate_storage< E >() ) ||
            ( DstStoreT == SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL ),
            CBufferView::status_t >::type
        prepare_load_object( size_type const SIXTRL_UNUSED( pos_in_buffer ),
            SIXTRL_BUFFER_ARGPTR_DEC E* SIXTRL_RESTRICT SIXTRL_UNUSED( dst )
        ) const
        {
            return SIXTRL_CXX_NAMESPACE::STATUS_GENERAL_FAILURE;
        }

        template< class SrcT, class DstT, store_backend_t DstStoreT =
                  SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT >
        SIXTRL_FN SIXTRL_INLINE typename std::enable_if<
            !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< SrcT >() ||
            DstStoreT == SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL,
            CBufferView::status_t >::type
        prepare_load_object_detailed(
            size_type const SIXTRL_UNUSED( pos_in_buffer ),
            SIXTRL_BUFFER_ARGPTR_DEC DstT* SIXTRL_RESTRICT SIXTRL_UNUSED( dst )
        ) const
        {
            return SIXTRL_CXX_NAMESPACE::STATUS_GENERAL_FAILURE;
        }

        template< class E, store_backend_t SrcStoreT =
                  SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT >
        SIXTRL_FN SIXTRL_INLINE typename std::enable_if<
            ( !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
              !SIXTRL_CXX_NAMESPACE::CObjElem_allow_delegate_storage< E >() ) ||
            ( SrcStoreT == SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL ),
            CBufferView::status_t >::type
        prepare_store_object( size_type const SIXTRL_UNUSED( pos_in_buffer ),
            SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
                SIXTRL_UNUSED( src ) )
        {
            return SIXTRL_CXX_NAMESPACE::STATUS_GENERAL_FAILURE;
        }

        template< class SrcT, class DstT, store_backend_t SrcStoreT =
                  SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT >
        SIXTRL_FN SIXTRL_INLINE typename std::enable_if<
            !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< DstT >() ||
            SrcStoreT == SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL,
            CBufferView::status_t >::type
        prepare_store_object_detailed(
            size_type const SIXTRL_UNUSED( pos_in_buffer ),
            SIXTRL_BUFFER_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT
                 SIXTRL_UNUSED( src ) ) const
        {
            return SIXTRL_CXX_NAMESPACE::STATUS_GENERAL_FAILURE;
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* case 2: directly loadable/storable */

        template< class E, store_backend_t DstStoreT =
                  SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT >
        SIXTRL_FN SIXTRL_INLINE typename std::enable_if<
            DstStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL &&
            SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
           !SIXTRL_CXX_NAMESPACE::CObjElem_allow_delegate_storage< E >(),
            CBufferView::status_t >::type
        prepare_load_object( size_type const pos_in_buffer,
            SIXTRL_BUFFER_ARGPTR_DEC E* SIXTRL_RESTRICT dst ) const
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            CBufferView::status_t status = st::STATUS_GENERAL_FAILURE;

            constexpr st::store_backend_t SrcStoreT = st::STORAGE_BE_COBJECTS;
            typedef st::ObjDataConverter< E, E, SrcStoreT, DstStoreT > conv_t;

            SIXTRL_BUFFER_DATAPTR_DEC E const* src =
                this->get_object< E >( pos_in_buffer );

            if( ( src != SIXTRL_NULLPTR ) && ( dst != SIXTRL_NULLPTR ) )
            {
                status = ( ( dst != src ) &&
                           ( conv_t::requires_prepare( dst, src ) ) )
                    ? conv_t::prepare( dst, src ) : st::STATUS_SUCCESS;
            }

            return status;
        }

        template< class E, store_backend_t SrcStoreT =
                  SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT >
        SIXTRL_FN SIXTRL_INLINE typename std::enable_if<
            SrcStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL &&
            SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
           !SIXTRL_CXX_NAMESPACE::CObjElem_allow_delegate_storage< E >(),
            CBufferView::status_t >::type
        prepare_store_object( size_type const pos_in_buffer,
            SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT src )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            CBufferView::status_t status = st::STATUS_GENERAL_FAILURE;

            constexpr st::store_backend_t DstStoreT = st::STORAGE_BE_COBJECTS;
            using conv_t = st::ObjDataConverter< E, E, SrcStoreT, DstStoreT >;

            SIXTRL_BUFFER_DATAPTR_DEC E* dst =
                this->get_object< E >( pos_in_buffer );

            if( ( src != SIXTRL_NULLPTR ) && ( dst != SIXTRL_NULLPTR ) )
            {
                status = ( ( src != dst ) &&
                           ( conv_t::requires_prepare( dst, src ) ) )
                    ? conv_t::prepare( dst, src ) : st::STATUS_SUCCESS;
            }

            return status;
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* case 3: loadable/storable via delegate */

        template< class DstT, store_backend_t DstStoreT =
                  SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT >
        SIXTRL_FN SIXTRL_INLINE typename std::enable_if<
            DstStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL &&
           !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< DstT >() &&
            SIXTRL_CXX_NAMESPACE::CObjElem_allow_delegate_storage< DstT >(),
            CBufferView::status_t >::type
        prepare_load_object( size_type const pos_in_buffer,
            SIXTRL_BUFFER_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst ) const
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            CBufferView::status_t status = st::STATUS_GENERAL_FAILURE;

            typedef st::ObjDataDelegateTraits< DstT > delegate_traits_t;
            typedef typename delegate_traits_t::delegate_t SrcT;

            constexpr st::store_backend_t SrcStoreT = st::STORAGE_BE_COBJECTS;
            typedef st::ObjDataConverter< SrcT, DstT, SrcStoreT, DstStoreT >
                    conv_t;

            SIXTRL_BUFFER_DATAPTR_DEC SrcT const* src =
                this->get_object< SrcT >( pos_in_buffer );

            if( ( src != SIXTRL_NULLPTR ) && ( dst != SIXTRL_NULLPTR ) )
            {
                status = ( ( ( !std::is_same< SrcT, DstT >::value ) ||
                             ( reinterpret_cast< std::uintptr_t >( src ) !=
                               reinterpret_cast< std::uintptr_t >( dst ) ) ) &&
                           ( conv_t::requires_prepare( dst, src ) ) )
                    ? conv_t::prepare( dst, src ) : st::STATUS_SUCCESS;
            }

            return status;
        }

        template< class SrcT, store_backend_t SrcStoreT =
                  SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT >
        SIXTRL_FN SIXTRL_INLINE typename std::enable_if<
            SrcStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL &&
           !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< SrcT >() &&
            SIXTRL_CXX_NAMESPACE::CObjElem_allow_delegate_storage< SrcT >(),
            CBufferView::status_t >::type
        prepare_store_object( size_type const pos_in_buffer,
            SIXTRL_BUFFER_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            CBufferView::status_t status = st::STATUS_GENERAL_FAILURE;

            typedef st::ObjDataDelegateTraits< SrcT > delegate_traits_t;
            typedef typename delegate_traits_t::delegate_t DstT;

            constexpr st::store_backend_t DstStoreT = st::STORAGE_BE_COBJECTS;
            typedef st::ObjDataConverter< SrcT, DstT, SrcStoreT, DstStoreT >
                    conv_t;

            SIXTRL_BUFFER_DATAPTR_DEC DstT* dst =
                this->get_object< DstT >( pos_in_buffer );

            if( ( src != SIXTRL_NULLPTR ) && ( dst != SIXTRL_NULLPTR ) )
            {
                status = ( ( ( !std::is_same< SrcT, DstT >::value ) ||
                             ( reinterpret_cast< std::uintptr_t >( src ) !=
                               reinterpret_cast< std::uintptr_t >( dst ) ) ) &&
                           ( conv_t::requires_prepare( dst, src ) ) )
                    ? conv_t::prepare( dst, src ) : st::STATUS_SUCCESS;
            }

            return status;
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* case 4: explicit DstT and SrcT types */

        template< class SrcT, class DstT, store_backend_t DstStoreT =
                  SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT >
        SIXTRL_FN SIXTRL_INLINE typename std::enable_if<
            DstStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL &&
            SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< SrcT >(),
            CBufferView::status_t >::type
        prepare_load_object_detailed( size_type const pos_in_buffer,
            SIXTRL_BUFFER_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst ) const
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            CBufferView::status_t status = st::STATUS_GENERAL_FAILURE;

            constexpr st::store_backend_t SrcStoreT = st::STORAGE_BE_COBJECTS;
            typedef st::ObjDataConverter< SrcT, DstT, SrcStoreT, DstStoreT >
                    conv_t;

            static_assert( !st::ObjData_is_specific_illegal_type< SrcT >(),
                           "SrcT required to be a legal type" );

            SIXTRL_BUFFER_DATAPTR_DEC SrcT const* src =
                this->get_object< SrcT >( pos_in_buffer );

            if( ( src != SIXTRL_NULLPTR ) && ( dst != SIXTRL_NULLPTR ) )
            {
                status = ( ( ( !std::is_same< SrcT, DstT >::value ) ||
                             ( reinterpret_cast< std::uintptr_t >( src ) !=
                               reinterpret_cast< std::uintptr_t >( dst ) ) ) &&
                           ( conv_t::requires_prepare( dst, src ) ) )
                    ? conv_t::prepare( dst, src ) : st::STATUS_SUCCESS;
            }

            return status;
        }

        template< class SrcT, class DstT, store_backend_t SrcStoreT =
                  SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT >
        SIXTRL_FN SIXTRL_INLINE typename std::enable_if<
             SrcStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL &&
            !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< DstT >(),
            CBufferView::status_t >::type
        prepare_store_object_detailed(
            size_type const pos_in_buffer,
            SIXTRL_BUFFER_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src
        ) const
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            CBufferView::status_t status = st::STATUS_GENERAL_FAILURE;

            constexpr st::store_backend_t DstStoreT = st::STORAGE_BE_COBJECTS;
            typedef st::ObjDataConverter< SrcT, DstT, SrcStoreT, DstStoreT >
                    conv_t;

            static_assert( !st::ObjData_is_specific_illegal_type< SrcT >(),
                           "SrcT required to be a legal type" );

            SIXTRL_BUFFER_DATAPTR_DEC DstT* dst =
                this->get_object< DstT >( pos_in_buffer );

            if( ( src != SIXTRL_NULLPTR ) && ( dst != SIXTRL_NULLPTR ) )
            {
                status = ( ( ( !std::is_same< SrcT, DstT >::value ) ||
                             ( reinterpret_cast< std::uintptr_t >( src ) !=
                               reinterpret_cast< std::uintptr_t >( dst ) ) ) &&
                           ( conv_t::requires_prepare( dst, src ) ) )
                    ? conv_t::prepare( dst, src ) : st::STATUS_SUCCESS;
            }

            return status;
        }

        /* ----------------------------------------------------------------- */
        /* c) perform load/store object */

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* case 1: type neither directly nor via delegate loadable/storable
         *         from/to CBufferView -> return error */

        template< class E, store_backend_t DstStoreT =
                  SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
                  typename... Args >
        SIXTRL_FN SIXTRL_INLINE typename std::enable_if<
            ( !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
              !SIXTRL_CXX_NAMESPACE::CObjElem_allow_delegate_storage< E >() ) ||
            ( DstStoreT == SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL ),
            CBufferView::status_t >::type
        load_object( size_type const SIXTRL_UNUSED( pos_in_buffer ),
            SIXTRL_BUFFER_ARGPTR_DEC E* SIXTRL_RESTRICT SIXTRL_UNUSED( dst ),
            Args&&... SIXTRL_UNUSED( conv_parameters ) ) const
        {
            return SIXTRL_CXX_NAMESPACE::STATUS_GENERAL_FAILURE;
        }

        template< class SrcT, class DstT, store_backend_t DstStoreT =
                  SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT, typename... Args >
        SIXTRL_FN SIXTRL_INLINE typename std::enable_if<
            !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< SrcT >() ||
            DstStoreT == SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL,
            CBufferView::status_t >::type
        load_object_detailed(
            size_type const SIXTRL_UNUSED( pos_in_buffer ),
            SIXTRL_BUFFER_ARGPTR_DEC DstT* SIXTRL_RESTRICT SIXTRL_UNUSED( dst ),
            Args&&... SIXTRL_UNUSED( conv_parameters ) ) const
        {
            return SIXTRL_CXX_NAMESPACE::STATUS_GENERAL_FAILURE;
        }

        template< class E, store_backend_t SrcStoreT =
                  SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT, typename... Args >
        SIXTRL_FN SIXTRL_INLINE typename std::enable_if<
            ( !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
              !SIXTRL_CXX_NAMESPACE::CObjElem_allow_delegate_storage< E >() ) ||
            ( SrcStoreT == SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL ),
            CBufferView::status_t >::type
        store_object( size_type const SIXTRL_UNUSED( pos_in_buffer ),
            SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
                SIXTRL_UNUSED( src ),
            Args&&... SIXTRL_UNUSED( conv_parameters ) )
        {
            return SIXTRL_CXX_NAMESPACE::STATUS_GENERAL_FAILURE;
        }

        template< class SrcT, class DstT, store_backend_t SrcStoreT =
                  SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT, typename... Args >
        SIXTRL_FN SIXTRL_INLINE typename std::enable_if<
            !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< DstT >() ||
            SrcStoreT == SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL,
            CBufferView::status_t >::type
        store_object_detailed(
            size_type const SIXTRL_UNUSED( pos_in_buffer ),
            SIXTRL_BUFFER_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT
                 SIXTRL_UNUSED( src ),
            Args&&... SIXTRL_UNUSED( conv_parameters ) )
        {
            return SIXTRL_CXX_NAMESPACE::STATUS_GENERAL_FAILURE;
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* case 2: directly storable / loadable */

        template< class E, store_backend_t DstStoreT =
                  SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT,
                  typename...  Args>
        SIXTRL_FN SIXTRL_INLINE typename std::enable_if<
            DstStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL &&
            SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
           !SIXTRL_CXX_NAMESPACE::CObjElem_allow_delegate_storage< E >(),
            CBufferView::status_t >::type
        load_object( size_type const pos_in_buffer,
            SIXTRL_BUFFER_ARGPTR_DEC E* SIXTRL_RESTRICT dst,
            Args&&... conv_parameters ) const
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            CBufferView::status_t status = st::STATUS_GENERAL_FAILURE;
            constexpr st::store_backend_t SrcStoreT = st::STORAGE_BE_COBJECTS;
            typedef st::ObjDataConverter< E, E, SrcStoreT, DstStoreT > conv_t;

            SIXTRL_BUFFER_DATAPTR_DEC E const* src =
                this->get_object< E >( pos_in_buffer );

            if( ( src != SIXTRL_NULLPTR ) && ( dst != SIXTRL_NULLPTR ) )
            {
                status = ( src != dst )
                    ? conv_t::perform( dst, src, std::forward< Args >(
                        conv_parameters )... ) : st::STATUS_SUCCESS;
            }

            return status;
        }

        template< class E, store_backend_t SrcStoreT =
                  SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT, typename... Args >
        SIXTRL_FN SIXTRL_INLINE typename std::enable_if<
            SrcStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL &&
            SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
           !SIXTRL_CXX_NAMESPACE::CObjElem_allow_delegate_storage< E >(),
            CBufferView::status_t >::type
        store_object( size_type const pos_in_buffer,
            SIXTRL_BUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT src,
            Args&&... conv_parameters )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            CBufferView::status_t status = st::STATUS_GENERAL_FAILURE;

            constexpr st::store_backend_t DstStoreT = st::STORAGE_BE_COBJECTS;
            typedef st::ObjDataConverter< E, E, SrcStoreT, DstStoreT > conv_t;

            SIXTRL_BUFFER_DATAPTR_DEC E* dst =
                this->get_object< E >( pos_in_buffer );

            if( ( src != SIXTRL_NULLPTR ) && ( dst != SIXTRL_NULLPTR ) )
            {
                status = ( src != dst )
                    ? conv_t::perform( dst, src, std::forward< Args >(
                        conv_parameters )... ) : st::STATUS_SUCCESS;
            }

            return status;
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* case 3: loadable/storable via delegate */

        template< class DstT, store_backend_t DstStoreT =
                  SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT, typename... Args  >
        SIXTRL_FN SIXTRL_INLINE typename std::enable_if<
            DstStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL &&
           !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< DstT >() &&
            SIXTRL_CXX_NAMESPACE::CObjElem_allow_delegate_storage< DstT >(),
            CBufferView::status_t >::type
        load_object( size_type const pos_in_buffer,
            SIXTRL_BUFFER_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
            Args&&... conv_parameters ) const
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            CBufferView::status_t status = st::STATUS_GENERAL_FAILURE;

            typedef st::ObjDataDelegateTraits< DstT > delegate_traits_t;
            typedef typename delegate_traits_t::delegate_t SrcT;

            constexpr st::store_backend_t SrcStoreT = st::STORAGE_BE_COBJECTS;
            typedef st::ObjDataConverter< SrcT, DstT, SrcStoreT, DstStoreT >
                    conv_t;

            SIXTRL_BUFFER_DATAPTR_DEC SrcT const* src =
                this->get_object< SrcT >( pos_in_buffer );

            if( ( src != SIXTRL_NULLPTR ) && ( dst != SIXTRL_NULLPTR ) )
            {
                status = ( ( !std::is_same< SrcT, DstT >::value ) ||
                           ( reinterpret_cast< std::uintptr_t >( src ) !=
                             reinterpret_cast< std::uintptr_t >( dst ) ) )
                    ? conv_t::perform( dst, src, std::forward< Args >(
                        conv_parameters )... ) : st::STATUS_SUCCESS;
            }

            return status;
        }

        template< class SrcT, store_backend_t SrcStoreT =
                  SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT, typename... Args >
        SIXTRL_FN SIXTRL_INLINE typename std::enable_if<
            SrcStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL &&
           !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< SrcT >() &&
            SIXTRL_CXX_NAMESPACE::CObjElem_allow_delegate_storage< SrcT >(),
            CBufferView::status_t >::type
        store_object( size_type const pos_in_buffer,
            SIXTRL_BUFFER_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
            Args&&... conv_parameters )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            CBufferView::status_t status = st::STATUS_GENERAL_FAILURE;

            typedef st::ObjDataDelegateTraits< SrcT, SrcStoreT > delegate_traits_t;
            typedef typename delegate_traits_t::delegate_t DstT;

            constexpr st::store_backend_t DstStoreT = st::STORAGE_BE_COBJECTS;
            typedef st::ObjDataConverter< SrcT, DstT, SrcStoreT, DstStoreT >
                    conv_t;

            SIXTRL_BUFFER_DATAPTR_DEC DstT* dst =
                this->get_object< DstT >( pos_in_buffer );

            if( ( src != SIXTRL_NULLPTR ) && ( dst != SIXTRL_NULLPTR ) )
            {
                status = ( ( !std::is_same< SrcT, DstT >::value ) ||
                           ( reinterpret_cast< std::uintptr_t >( src ) !=
                             reinterpret_cast< std::uintptr_t >( dst ) ) )
                    ? conv_t::perform( dst, src, std::forward< Args >(
                        conv_parameters )... ) : st::STATUS_SUCCESS;
            }

            return status;
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* case 4: explicit DstT and SrcT types */

        template< class SrcT, class DstT, store_backend_t DstStoreT =
                  SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT, typename... Args >
        SIXTRL_FN SIXTRL_INLINE typename std::enable_if<
            DstStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL &&
            SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< SrcT >(),
            CBufferView::status_t >::type
        load_object_detailed(
            size_type const pos_in_buffer,
            SIXTRL_BUFFER_ARGPTR_DEC DstT* SIXTRL_RESTRICT dst,
            Args&&... conv_parameters ) const
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            CBufferView::status_t status = st::STATUS_GENERAL_FAILURE;

            constexpr st::store_backend_t SrcStoreT = st::STORAGE_BE_COBJECTS;
            typedef st::ObjDataConverter< SrcT, DstT, SrcStoreT, DstStoreT >
                    conv_t;

            static_assert( !st::ObjData_is_specific_illegal_type< SrcT >(),
                           "SrcT required to be a legal type" );

            SIXTRL_BUFFER_DATAPTR_DEC SrcT const* src =
                this->get_object< SrcT >( pos_in_buffer );

            if( ( src != SIXTRL_NULLPTR ) && ( dst != SIXTRL_NULLPTR ) )
            {
                bool const is_not_same_obj = (
                    ( !std::is_same< SrcT, DstT >::value ) ||
                    ( reinterpret_cast< std::uintptr_t >( dst ) ==
                      reinterpret_cast< std::uintptr_t >( src ) ) );

                status = ( is_not_same_obj )
                    ? conv_t::perform( dst, src, std::forward< Args >(
                        conv_parameters )... ) : st::STATUS_SUCCESS;
            }

            return status;
        }

        template< class SrcT, class DstT, store_backend_t SrcStoreT =
                  SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT, typename... Args >
        SIXTRL_FN SIXTRL_INLINE typename std::enable_if<
             SrcStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL &&
            !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< DstT >(),
            CBufferView::status_t >::type
        store_object_detailed(
            size_type const pos_in_buffer,
            SIXTRL_BUFFER_ARGPTR_DEC const SrcT *const SIXTRL_RESTRICT src,
            Args&&... conv_parameters ) const
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            CBufferView::status_t status = st::STATUS_GENERAL_FAILURE;

            constexpr st::store_backend_t DstStoreT = st::STORAGE_BE_COBJECTS;
            typedef st::ObjDataConverter< SrcT, DstT, SrcStoreT, DstStoreT >
                    conv_t;

            static_assert( !st::ObjData_is_specific_illegal_type< SrcT >(),
                           "SrcT required to be a legal type" );

            SIXTRL_BUFFER_DATAPTR_DEC DstT* dst =
                this->get_object< DstT >( pos_in_buffer );

            if( ( src != SIXTRL_NULLPTR ) && ( dst != SIXTRL_NULLPTR ) )
            {
                bool const is_not_same_obj = (
                    ( !std::is_same< SrcT, DstT >::value ) ||
                    ( reinterpret_cast< std::uintptr_t >( dst ) ==
                      reinterpret_cast< std::uintptr_t >( src ) ) );

                status = ( is_not_same_obj )
                    ? conv_t::perform( dst, src, std::forward< Args >(
                        conv_parameters )... ) : st::STATUS_SUCCESS;
            }

            return status;
        }

        /* ***************************************************************** */
        /* *****  LOW-LEVEL SUPPORT FOR WRITING ELEMENTS TO THE BUFFER ***** */
        /* ***************************************************************** */

        template< class T >
        SIXTRL_FN bool can_add_copy_of_object(
            SIXTRL_BUFFER_ARGPTR_DEC const T *const SIXTRL_RESTRICT ptr_elem,
            SIXTRL_BUFFER_ARGPTR_DEC size_type*
                SIXTRL_RESTRICT requ_buffer_size = nullptr,
            SIXTRL_BUFFER_ARGPTR_DEC size_type*
                SIXTRL_RESTRICT requ_n_slots = nullptr,
            SIXTRL_BUFFER_ARGPTR_DEC size_type*
                SIXTRL_RESTRICT requ_n_objs = nullptr,
            SIXTRL_BUFFER_ARGPTR_DEC size_type*
                SIXTRL_RESTRICT requ_n_ptrs = nullptr ) const SIXTRL_NOEXCEPT;

        protected:

        SIXTRL_FN void do_set_base_addr(
            address_t const base_addr ) SIXTRL_NOEXCEPT;

        SIXTRL_FN void do_set_store_addr(
            address_t const store_addr ) SIXTRL_NOEXCEPT;

        SIXTRL_FN void do_set_slot_size(
            size_type const slot_size ) SIXTRL_NOEXCEPT;

        SIXTRL_FN void do_set_capacity(
            size_type const capacity ) SIXTRL_NOEXCEPT;

        SIXTRL_FN void do_set_flags( flags_t const flags ) SIXTRL_NOEXCEPT;

        private:

        address_t       m_base_addr;
        size_type       m_slot_size;
        size_type       m_capacity;
        flags_t         m_flags;
    };

    #if !defined( _GPUCODE )

    SIXTRL_EXTERN SIXTRL_HOST_FN CBufferView::status_t CBuffer_to_file(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView const& SIXTRL_RESTRICT_REF view,
        char const* SIXTRL_RESTRICT path_to_binary_dump );

    SIXTRL_EXTERN SIXTRL_HOST_FN CBufferView::status_t CBuffer_to_file(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView const& SIXTRL_RESTRICT_REF view,
        std::string const& SIXTRL_RESTRICT_REF path_to_binary_dump );

    /* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

    SIXTRL_EXTERN SIXTRL_HOST_FN CBufferView::status_t
    CBuffer_to_file_normalized(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView& SIXTRL_RESTRICT_REF view,
        char const* SIXTRL_RESTRICT path_to_binary_dump,
        CBufferView::address_t const normalized_base_addr );

    SIXTRL_EXTERN SIXTRL_HOST_FN CBufferView::status_t
    CBuffer_to_file_normalized(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView& SIXTRL_RESTRICT_REF view,
        std::string const& SIXTRL_RESTRICT_REF path_to_binary_dump,
        CBufferView::address_t const normalized_base_addr );

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_EXTERN SIXTRL_HOST_FN CBufferView::status_t CBufferView_from_file(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView& SIXTRL_RESTRICT_REF view,
        char const* SIXTRL_RESTRICT_REF path_to_binary_dump,
        SIXTRL_ARGPTR_DEC CBufferView::size_type* SIXTRL_RESTRICT
            ptr_required_capacity = nullptr );

    SIXTRL_EXTERN SIXTRL_HOST_FN CBufferView::status_t CBufferView_from_file(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView& SIXTRL_RESTRICT_REF view,
        std::string const& SIXTRL_RESTRICT_REF path_to_binary_dump,
        SIXTRL_ARGPTR_DEC CBufferView::size_type* SIXTRL_RESTRICT
            ptr_required_capacity = nullptr );

    #endif /* !defined( _GPUCODE ) */

    template< class T >
    SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_OBJ_DATAPTR_DEC T*
    CBufferView_add_copy_of_object_detail(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView& SIXTRL_RESTRICT_REF view,
        SIXTRL_BUFFER_ARGPTR_DEC const T *const SIXTRL_RESTRICT ptr_elem,
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t*
            SIXTRL_RESTRICT requ_buffer_size,
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t*
            SIXTRL_RESTRICT requ_n_slots,
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t*
            SIXTRL_RESTRICT requ_n_objs,
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t*
            SIXTRL_RESTRICT requ_n_ptrs,
        bool const init_with_zeros = false ) SIXTRL_NOEXCEPT;

    template< class T, typename... Args >
    SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_OBJ_DATAPTR_DEC T*
    CBufferView_create_new_object(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView& SIXTRL_RESTRICT_REF view,
        Args&&... init_args );

    template< class T, typename... Args >
    SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_OBJ_DATAPTR_DEC T*
    CBufferView_add_object(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView& SIXTRL_RESTRICT_REF view,
        Args&&... init_args );
}

#if !defined( _GPUCODE )
extern "C" {
#endif /* !defined( _GPUCODE ) */

typedef SIXTRL_CXX_NAMESPACE::CBufferView   NS(CBufferView);

#if !defined( _GPUCODE )
}
#endif /* !defined( _GPUCODE ) */

#else

typedef struct NS(CBufferView) NS(CBufferView);

#endif /* __cplusplus */

/* ************************************************************************* */
/* Implementation of inline methods and functions */
/* ************************************************************************* */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/cobjects/flat_buffer.h"
    #include "sixtracklib_base/cobjects/element_store_restore.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class T >
    SIXTRL_INLINE SIXTRL_BUFFER_OBJ_DATAPTR_DEC T*
    CBufferView_add_copy_of_object_detail(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView& SIXTRL_RESTRICT_REF view,
        SIXTRL_BUFFER_ARGPTR_DEC const T *const SIXTRL_RESTRICT ptr_elem,
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t* SIXTRL_RESTRICT requ_buffer_size,
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t* SIXTRL_RESTRICT requ_n_slots,
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t* SIXTRL_RESTRICT requ_n_objs,
        SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::size_t* SIXTRL_RESTRICT requ_n_ptrs,
        bool const init_with_zeros ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef SIXTRL_BUFFER_OBJ_DATAPTR_DEC T* _ptr_elem_t;

        _ptr_elem_t ptr_added_element = nullptr;

        if( view.can_add_copy_of_object( ptr_elem, requ_buffer_size,
                requ_n_slots, requ_n_objs, requ_n_ptrs ) )
        {
            ptr_added_element = st::CObjElem_add_copy_of_object(
                view.p_base(), view.slot_size(), ptr_elem, init_with_zeros );
        }

        return ptr_added_element;
    }

    template< class T, typename... Args >
    SIXTRL_INLINE SIXTRL_BUFFER_OBJ_DATAPTR_DEC T*
    CBufferView_create_new_object(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView& SIXTRL_RESTRICT_REF view,
        Args&&... init_args )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_BUFFER_OBJ_DATAPTR_DEC T* ptr_added_element = SIXTRL_NULLPTR;
        SIXTRL_BUFFER_OBJ_ARGPTR_DEC T temp;

        st::CObjElem_preset( &temp );

        if( st::STATUS_SUCCESS == st::ObjDataInitialiser<
                T, st::STORAGE_BE_COBJECTS >::init(
                    &temp, std::forward< Args >( init_args )... ) )
        {
            ptr_added_element = st::CBufferView_add_copy_of_object_detail(
                view, &temp, nullptr, nullptr, nullptr, nullptr, false );
        }

        return ptr_added_element;
    }

    template< class T, typename... Args >
    SIXTRL_STATIC SIXTRL_FN SIXTRL_BUFFER_OBJ_DATAPTR_DEC T*
    CBufferView_add_object(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView& SIXTRL_RESTRICT_REF view,
        Args&&... init_args )
    {
        return SIXTRL_CXX_NAMESPACE::CBufferView_create_new_object< T >(
            view, std::forward< Args >( init_args )... );
    }

    /* ===================================================================== */

    SIXTRL_INLINE CBufferView::CBufferView(
        CBufferView::address_t const base_addr,
        CBufferView::size_type const slot_size,
        CBufferView::size_type const buffer_capacity,
        CBufferView::flags_t const flags ) SIXTRL_NOEXCEPT :
        m_base_addr( base_addr ),
        m_slot_size( slot_size ),
        m_capacity( buffer_capacity ),
        m_flags( flags )
    {
        typedef SIXTRL_CXX_NAMESPACE::CBufferView _this_t;
        typedef _this_t::size_type _size_t;

        if( ( !_this_t::is_flag_set(
                    this->m_flags, _this_t::FLAGS_FORCE_INIT ) ) &&
            ( ::NS(CObjFlatBuffer_has_cbuffer_structure)(
                    this->p_base(), buffer_capacity, slot_size ) ) )
        {
            /* This looks like a valid CBuffer header -> use the size to
             * update the capacity in case the capacity is smaller than
             * the given size */

            CBufferView::size_type const read_buffer_size =
                ::NS(CObjFlatBuffer_size)( this->p_base(), slot_size );

            if( read_buffer_size > this->capacity() )
            {
                this->do_set_capacity( read_buffer_size );
            }
        }
        else if( ( this->p_base() != nullptr ) &&
                 ( slot_size > _size_t{ 0 } ) )
        {
            ::NS(CObjFlatBuffer_init_empty)(
                this->p_base(), buffer_capacity, slot_size );
        }
    }


    SIXTRL_INLINE CBufferView::flags_t CBufferView::add_flag_to_set(
        CBufferView::flags_t const haystack,
        CBufferView::flags_t const needle ) SIXTRL_NOEXCEPT
    {
        return haystack & needle;
    }

    SIXTRL_INLINE CBufferView::flags_t CBufferView::remove_flag_from_set(
        CBufferView::flags_t const haystack,
        CBufferView::flags_t const needle ) SIXTRL_NOEXCEPT
    {
        return haystack & ~needle;
    }

    SIXTRL_INLINE bool CBufferView::is_flag_set(
        CBufferView::flags_t const haystack,
        CBufferView::flags_t const needle ) SIXTRL_NOEXCEPT
    {
        return ( ( needle != FLAGS_NONE ) &&
                 ( ( needle & haystack ) == needle ) );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE CBufferView::flags_t
    CBufferView::flags() const SIXTRL_NOEXCEPT
    {
        return this->m_flags;
    }

    SIXTRL_INLINE void CBufferView::_set_flags_dangerous(
            CBufferView::flags_t const flags ) SIXTRL_NOEXCEPT
    {
        this->do_set_flags( flags );
    }

    SIXTRL_INLINE bool CBufferView::allow_remap() const SIXTRL_NOEXCEPT
    {
        return CBufferView::is_flag_set(
            this->m_flags, CBufferView::FLAGS_ALLOW_REMAPPING );
    }

    SIXTRL_INLINE bool CBufferView::allow_allocate() const SIXTRL_NOEXCEPT
    {
        return CBufferView::is_flag_set(
            this->m_flags, CBufferView::FLAGS_ALLOW_ALLOC );
    }

    SIXTRL_INLINE bool CBufferView::allow_realloc() const SIXTRL_NOEXCEPT
    {
        return CBufferView::is_flag_set(
            this->m_flags, CBufferView::FLAGS_ALLOW_REALLOC );
    }

    SIXTRL_INLINE bool CBufferView::allow_append() const SIXTRL_NOEXCEPT
    {
        return CBufferView::is_flag_set(
            this->m_flags, CBufferView::FLAGS_ALLOW_APPEND );
    }

    SIXTRL_INLINE bool CBufferView::owns_stored_data()   const SIXTRL_NOEXCEPT
    {
        return CBufferView::is_flag_set(
            this->m_flags, CBufferView::FLAGS_OWNS_STORED_DATA );
    }

    SIXTRL_INLINE bool CBufferView::has_special_memory() const SIXTRL_NOEXCEPT
    {
        return CBufferView::is_flag_set(
            this->m_flags, CBufferView::FLAGS_SPECIAL_MEMORY );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE CBufferView::size_type
    CBufferView::slot_size() const SIXTRL_NOEXCEPT
    {
        return this->m_slot_size;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE CBufferView::size_type
        CBufferView::size() const SIXTRL_NOEXCEPT
    {
        return ::NS(CObjFlatBuffer_size)( this->p_base(), this->slot_size() );
    }

    SIXTRL_INLINE CBufferView::size_type
        CBufferView::capacity() const SIXTRL_NOEXCEPT
    {
        return this->m_capacity;
    }

    SIXTRL_INLINE CBufferView::size_type
        CBufferView::size_header() const SIXTRL_NOEXCEPT
    {
        return ::NS(CObjFlatBuffer_size_header)(
            this->p_base(), this->slot_size() );
    }

    SIXTRL_INLINE CBufferView::size_type CBufferView::size_section_header(
            CBufferView::size_type const sec_id ) const SIXTRL_NOEXCEPT
    {
        return ::NS(CObjFlatBuffer_size_section_header)(
            this->p_base(), sec_id, this->slot_size() );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE CBufferView::size_type
        CBufferView::size_slots() const SIXTRL_NOEXCEPT
    {
        return ::NS(CObjFlatBuffer_size_slots)(
            this->p_base(), this->slot_size() );
    }

    SIXTRL_INLINE CBufferView::size_type
        CBufferView::size_objects() const SIXTRL_NOEXCEPT
    {
        return ::NS(CObjFlatBuffer_size_objects)(
            this->p_base(), this->slot_size() );
    }

    SIXTRL_INLINE CBufferView::size_type
        CBufferView::size_pointers() const SIXTRL_NOEXCEPT
    {
        return ::NS(CObjFlatBuffer_size_pointers)(
            this->p_base(), this->slot_size() );
    }

    SIXTRL_INLINE CBufferView::size_type
        CBufferView::size_garbage() const SIXTRL_NOEXCEPT
    {
        return ::NS(CObjFlatBuffer_size_garbage_ranges)(
            this->p_base(), this->slot_size() );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE CBufferView::size_type
        CBufferView::n_slots() const SIXTRL_NOEXCEPT
    {
        return ::NS(CObjFlatBuffer_num_slots)(
            this->p_base(), this->slot_size() );
    }

    SIXTRL_INLINE CBufferView::size_type
        CBufferView::n_objects() const SIXTRL_NOEXCEPT
    {
        return ::NS(CObjFlatBuffer_num_objects)(
            this->p_base(), this->slot_size() );
    }

    SIXTRL_INLINE CBufferView::size_type
        CBufferView::n_pointers() const SIXTRL_NOEXCEPT
    {
        return ::NS(CObjFlatBuffer_num_pointers)(
            this->p_base(), this->slot_size() );
    }

    SIXTRL_INLINE CBufferView::size_type
        CBufferView::n_garbage() const SIXTRL_NOEXCEPT
    {
        return ::NS(CObjFlatBuffer_num_garbage_ranges)(
            this->p_base(), this->slot_size() );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE CBufferView::size_type
        CBufferView::max_slots() const SIXTRL_NOEXCEPT
    {
        return ::NS(CObjFlatBuffer_max_num_slots)(
            this->p_base(), this->slot_size() );
    }

    SIXTRL_INLINE CBufferView::size_type
        CBufferView::max_objects() const SIXTRL_NOEXCEPT
    {
        return ::NS(CObjFlatBuffer_max_num_objects)(
            this->p_base(), this->slot_size() );
    }

    SIXTRL_INLINE CBufferView::size_type
        CBufferView::max_pointers() const SIXTRL_NOEXCEPT
    {
        return ::NS(CObjFlatBuffer_max_num_pointers)(
            this->p_base(), this->slot_size() );
    }

    SIXTRL_INLINE CBufferView::size_type
        CBufferView::max_garbage() const SIXTRL_NOEXCEPT
    {
        return ::NS(CObjFlatBuffer_max_num_garbage_ranges)(
            this->p_base(), this->slot_size() );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE CBufferView::address_t
        CBufferView::begin_addr() const SIXTRL_NOEXCEPT
    {
        return this->m_base_addr;
    }

    SIXTRL_INLINE CBufferView::address_t
        CBufferView::end_addr() const SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return ( this->m_base_addr != st::COBJECTS_NULL_ADDRESS )
            ? this->m_base_addr + this->size() : st::COBJECTS_NULL_ADDRESS;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE CBufferView::address_t
        CBufferView::begin_addr_slots() const SIXTRL_NOEXCEPT
    {
        return ::NS(CObjFlatBuffer_slots_begin_addr)(
            this->p_base(), this->slot_size() );
    }

    SIXTRL_INLINE CBufferView::address_t
        CBufferView::begin_addr_objects() const SIXTRL_NOEXCEPT
    {
        return ::NS(CObjFlatBuffer_indices_begin_addr)(
            this->p_base(), this->slot_size() );
    }

    SIXTRL_INLINE CBufferView::address_t
        CBufferView::begin_addr_pointers() const SIXTRL_NOEXCEPT
    {
        return ::NS(CObjFlatBuffer_pointers_begin_addr)(
            this->p_base(), this->slot_size() );
    }

    SIXTRL_INLINE CBufferView::address_t
        CBufferView::begin_addr_garbage() const SIXTRL_NOEXCEPT
    {
        return ::NS(CObjFlatBuffer_garbage_ranges_begin_addr)(
            this->p_base(), this->slot_size() );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE CBufferView::address_t
        CBufferView::end_addr_slots() const SIXTRL_NOEXCEPT
    {
        return ::NS(CObjFlatBuffer_section_end_addr)( this->p_base(),
            SIXTRL_CBUFFER_SECTION_ID_SLOTS, this->slot_size() );
    }

    SIXTRL_INLINE CBufferView::address_t
        CBufferView::end_addr_objects() const SIXTRL_NOEXCEPT
    {
        return ::NS(CObjFlatBuffer_section_end_addr)( this->p_base(),
            SIXTRL_CBUFFER_SECTION_ID_INDICES, this->slot_size() );
    }

    SIXTRL_INLINE CBufferView::address_t
        CBufferView::end_addr_pointers() const SIXTRL_NOEXCEPT
    {
        return ::NS(CObjFlatBuffer_section_end_addr)( this->p_base(),
            SIXTRL_CBUFFER_SECTION_ID_POINTERS, this->slot_size() );
    }

    SIXTRL_INLINE CBufferView::address_t
        CBufferView::end_addr_garbage() const SIXTRL_NOEXCEPT
    {
        return ::NS(CObjFlatBuffer_section_end_addr)( this->p_base(),
            SIXTRL_CBUFFER_SECTION_ID_GARBAGE, this->slot_size() );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE CBufferView::address_t
        CBufferView::base() const SIXTRL_NOEXCEPT
    {
        return this->m_base_addr;
    }

    SIXTRL_INLINE CBufferView::address_t
        CBufferView::base_address() const SIXTRL_NOEXCEPT
    {
        return this->m_base_addr;
    }

    SIXTRL_INLINE CBufferView::ptr_const_raw_data_t
        CBufferView::p_base() const SIXTRL_NOEXCEPT
    {
        return reinterpret_cast< CBufferView::ptr_const_raw_data_t >(
            static_cast< uintptr_t >( this->m_base_addr ) );
    }

    SIXTRL_INLINE CBufferView::ptr_const_raw_data_t
        CBufferView::p_base_begin() const SIXTRL_NOEXCEPT
    {
        return this->p_base();
    }

    SIXTRL_INLINE CBufferView::ptr_const_raw_data_t
        CBufferView::p_base_end() const SIXTRL_NOEXCEPT
    {
        CBufferView::ptr_const_raw_data_t ptr_end = this->p_base_begin();

        if( ptr_end != nullptr )
        {
            ptr_end = ptr_end + this->size();
        }

        return ptr_end;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE CBufferView::ptr_raw_data_t
        CBufferView::p_base_begin() SIXTRL_NOEXCEPT
    {
        return const_cast< CBufferView::ptr_raw_data_t >(
            this->p_const_base_begin() );
    }

    SIXTRL_INLINE CBufferView::ptr_raw_data_t
        CBufferView::p_base_end() SIXTRL_NOEXCEPT
    {
        return const_cast< CBufferView::ptr_raw_data_t >(
            this->p_const_base_end() );
    }

    SIXTRL_INLINE CBufferView::ptr_raw_data_t
        CBufferView::p_base() SIXTRL_NOEXCEPT
    {
        return const_cast< CBufferView::ptr_raw_data_t >(
            this->p_const_base() );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE CBufferView::ptr_const_raw_data_t
        CBufferView::p_const_base_begin() SIXTRL_NOEXCEPT
    {
        return static_cast< CBufferView const& >( *this ).p_base_begin();
    }

    SIXTRL_INLINE CBufferView::ptr_const_raw_data_t
        CBufferView::p_const_base_end() SIXTRL_NOEXCEPT
    {
        return static_cast< CBufferView const& >( *this ).p_base_end();
    }

    SIXTRL_INLINE CBufferView::ptr_const_raw_data_t
        CBufferView::p_const_base() SIXTRL_NOEXCEPT
    {
        return static_cast< CBufferView const& >( *this ).p_base();
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE CBufferView::ptr_const_raw_data_t
        CBufferView::p_slots() const SIXTRL_NOEXCEPT
    {
        return reinterpret_cast< CBufferView::ptr_const_raw_data_t >(
            static_cast< uintptr_t >( ::NS(CObjFlatBuffer_slots_begin_addr)(
                this->p_base(), this->slot_size() ) ) );
    }

    SIXTRL_INLINE CBufferView::ptr_raw_data_t
        CBufferView::p_slots() SIXTRL_NOEXCEPT
    {
        return const_cast< CBufferView::ptr_raw_data_t >(
            this->p_const_slots() );
    }

    SIXTRL_INLINE CBufferView::ptr_const_raw_data_t
        CBufferView::p_const_slots() SIXTRL_NOEXCEPT
    {
        return static_cast< CBufferView const& >( *this ).p_slots();
    }

    SIXTRL_INLINE CBufferView::ptr_const_raw_data_t
        CBufferView::p_slots_end() const SIXTRL_NOEXCEPT
    {
        return reinterpret_cast< CBufferView::ptr_const_raw_data_t >(
            static_cast< uintptr_t >( ::NS(CObjFlatBuffer_section_end_addr)(
                this->p_base(), SIXTRL_CBUFFER_SECTION_ID_SLOTS,
                    this->slot_size() ) ) );
    }

    SIXTRL_INLINE CBufferView::ptr_const_raw_data_t
        CBufferView::p_const_slots_end() SIXTRL_NOEXCEPT
    {
        return static_cast< CBufferView const& >( *this ).p_slots_end();
    }

    SIXTRL_INLINE CBufferView::ptr_raw_data_t
        CBufferView::p_slots_end() SIXTRL_NOEXCEPT
    {
        return const_cast< CBufferView::ptr_raw_data_t >(
            this->p_const_slots_end() );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE CBufferView::ptr_const_raw_data_t
        CBufferView::p_objects() const SIXTRL_NOEXCEPT
    {
        return reinterpret_cast< CBufferView::ptr_const_raw_data_t >(
            static_cast< uintptr_t >( ::NS(CObjFlatBuffer_indices_begin_addr)(
                this->p_base(), this->slot_size() ) ) );
    }

    SIXTRL_INLINE CBufferView::ptr_raw_data_t
        CBufferView::p_objects() SIXTRL_NOEXCEPT
    {
        return const_cast< CBufferView::ptr_raw_data_t >(
            this->p_const_objects() );
    }

    SIXTRL_INLINE CBufferView::ptr_const_raw_data_t
        CBufferView::p_const_objects() SIXTRL_NOEXCEPT
    {
        return static_cast< CBufferView const& >( *this ).p_objects();
    }

    SIXTRL_INLINE CBufferView::ptr_const_raw_data_t
        CBufferView::p_objects_end() const SIXTRL_NOEXCEPT
    {
        return reinterpret_cast< CBufferView::ptr_const_raw_data_t >(
            static_cast< uintptr_t >( ::NS(CObjFlatBuffer_section_end_addr)(
                this->p_base(), SIXTRL_CBUFFER_SECTION_ID_INDICES,
                    this->slot_size() ) ) );
    }

    SIXTRL_INLINE CBufferView::ptr_const_raw_data_t
        CBufferView::p_const_objects_end() SIXTRL_NOEXCEPT
    {
        return static_cast< CBufferView const& >( *this ).p_objects_end();
    }

    SIXTRL_INLINE CBufferView::ptr_raw_data_t
        CBufferView::p_objects_end() SIXTRL_NOEXCEPT
    {
        return const_cast< CBufferView::ptr_raw_data_t >(
            this->p_const_objects_end() );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE CBufferView::ptr_const_index_obj_t CBufferView::index_at(
        CBufferView::size_type const pos_in_buffer ) const SIXTRL_NOEXCEPT
    {
        return ::NS(CObjFlatBuffer_const_index)(
            this->p_base(), pos_in_buffer, this->slot_size() );
    }

    SIXTRL_INLINE CBufferView::ptr_const_index_obj_t
        CBufferView::const_index_at(
            CBufferView::size_type const pos_in_buffer ) SIXTRL_NOEXCEPT
    {
        return static_cast< CBufferView const& >(
            *this ).index_at( pos_in_buffer );
    }

    SIXTRL_INLINE CBufferView::ptr_index_obj_t CBufferView::index_at(
        CBufferView::size_type const pos_in_buffer ) SIXTRL_NOEXCEPT
    {
        return const_cast< CBufferView::ptr_index_obj_t >(
            this->const_index_at( pos_in_buffer ) );
    }

    SIXTRL_INLINE CBufferView::ptr_const_index_obj_t CBufferView::operator[](
        CBufferView::size_type const pos_in_buffer ) const SIXTRL_NOEXCEPT
    {
        return index_at( pos_in_buffer );
    }

    SIXTRL_INLINE CBufferView::ptr_index_obj_t CBufferView::operator[](
        CBufferView::size_type const pos_in_buffer ) SIXTRL_NOEXCEPT
    {
        return index_at( pos_in_buffer );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE CBufferView::ptr_const_raw_data_t
        CBufferView::p_pointers() const SIXTRL_NOEXCEPT
    {
        return reinterpret_cast< CBufferView::ptr_const_raw_data_t >(
            static_cast< uintptr_t >( ::NS(CObjFlatBuffer_pointers_begin_addr)(
                this->p_base(), this->slot_size() ) ) );
    }

    SIXTRL_INLINE CBufferView::ptr_raw_data_t
        CBufferView::p_pointers() SIXTRL_NOEXCEPT
    {
        return const_cast< CBufferView::ptr_raw_data_t >(
            this->p_const_pointers() );
    }

    SIXTRL_INLINE CBufferView::ptr_const_raw_data_t
        CBufferView::p_const_pointers() SIXTRL_NOEXCEPT
    {
        return static_cast< CBufferView const& >( *this ).p_pointers();
    }

    SIXTRL_INLINE CBufferView::ptr_const_raw_data_t
        CBufferView::p_pointers_end() const SIXTRL_NOEXCEPT
    {
        return reinterpret_cast< CBufferView::ptr_const_raw_data_t >(
            static_cast< uintptr_t >( ::NS(CObjFlatBuffer_section_end_addr)(
                this->p_base(), SIXTRL_CBUFFER_SECTION_ID_POINTERS,
                    this->slot_size() ) ) );
    }

    SIXTRL_INLINE CBufferView::ptr_const_raw_data_t
        CBufferView::p_const_pointers_end() SIXTRL_NOEXCEPT
    {
        return static_cast< CBufferView const& >( *this ).p_pointers_end();
    }

    SIXTRL_INLINE CBufferView::ptr_raw_data_t
        CBufferView::p_pointers_end() SIXTRL_NOEXCEPT
    {
        return const_cast< CBufferView::ptr_raw_data_t >(
            this->p_const_pointers_end() );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_INLINE CBufferView::ptr_const_raw_data_t
        CBufferView::p_garbage() const SIXTRL_NOEXCEPT
    {
        return reinterpret_cast< CBufferView::ptr_const_raw_data_t >(
            static_cast< uintptr_t >(
                ::NS(CObjFlatBuffer_garbage_ranges_begin_addr)( this->p_base(),
                    this->slot_size() ) ) );
    }

    SIXTRL_INLINE CBufferView::ptr_raw_data_t
        CBufferView::p_garbage() SIXTRL_NOEXCEPT
    {
        return const_cast< CBufferView::ptr_raw_data_t >(
            this->p_const_garbage() );
    }

    SIXTRL_INLINE CBufferView::ptr_const_raw_data_t
        CBufferView::p_const_garbage() SIXTRL_NOEXCEPT
    {
        return static_cast< CBufferView const& >( *this ).p_garbage();
    }

    SIXTRL_INLINE CBufferView::ptr_const_raw_data_t
        CBufferView::p_garbage_end() const   SIXTRL_NOEXCEPT
    {
        return reinterpret_cast< CBufferView::ptr_const_raw_data_t >(
            static_cast< uintptr_t >( ::NS(CObjFlatBuffer_section_end_addr)(
                this->p_base(), SIXTRL_CBUFFER_SECTION_ID_GARBAGE,
                    this->slot_size() ) ) );
    }

    SIXTRL_INLINE CBufferView::ptr_const_raw_data_t
        CBufferView::p_const_garbage_end()   SIXTRL_NOEXCEPT
    {
        return static_cast< CBufferView const& >( *this ).p_garbage_end();
    }

    SIXTRL_INLINE CBufferView::ptr_raw_data_t
        CBufferView::p_garbage_end() SIXTRL_NOEXCEPT
    {
        return const_cast< CBufferView::ptr_raw_data_t >(
            this->p_const_garbage_end() );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE CBufferView::ptr_const_index_obj_t
        CBufferView::objects_begin() const SIXTRL_NOEXCEPT
    {
        return ::NS(CObjFlatBuffer_const_indices_begin)(
            this->p_base(), this->slot_size() );
    }

    SIXTRL_INLINE CBufferView::ptr_index_obj_t
        CBufferView::objects_begin() SIXTRL_NOEXCEPT
    {
        return const_cast< CBufferView::ptr_index_obj_t >(
            this->const_objects_begin() );
    }

    SIXTRL_INLINE CBufferView::ptr_const_index_obj_t
        CBufferView::const_objects_begin()  SIXTRL_NOEXCEPT
    {
        return static_cast< CBufferView const& >( *this ).objects_begin();
    }

    SIXTRL_INLINE CBufferView::ptr_const_index_obj_t
        CBufferView::objects_end() const SIXTRL_NOEXCEPT
    {
        return ::NS(CObjFlatBuffer_const_indices_end)(
            this->p_base(), this->slot_size() );
    }

    SIXTRL_INLINE CBufferView::ptr_index_obj_t
        CBufferView::objects_end() SIXTRL_NOEXCEPT
    {
        return const_cast< CBufferView::ptr_index_obj_t >(
            this->const_objects_end() );
    }

    SIXTRL_INLINE CBufferView::ptr_const_index_obj_t
        CBufferView::const_objects_end() SIXTRL_NOEXCEPT
    {
        return static_cast< CBufferView const& >( *this ).objects_end();
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool CBufferView::has_capacity_for_allocate(
        CBufferView::size_type const max_num_slots,
        CBufferView::size_type const max_num_objects,
        CBufferView::size_type const max_num_pointers,
        CBufferView::size_type const max_num_garbage_ranges
    ) const SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef CBufferView::size_type _size_t;

        _size_t const requ_buffer_size =
            ::NS(CObjFlatBuffer_calc_required_buffer_size)(
                this->p_base(), max_num_slots, max_num_objects,
                    max_num_pointers, max_num_garbage_ranges,
                        this->slot_size() );

        SIXTRL_ASSERT( this->capacity() >= this->size() );

        return ( ( requ_buffer_size >= st::CBUFFER_MIN_SIZE ) &&
                 ( requ_buffer_size <= this->capacity() ) );
    }

    SIXTRL_INLINE bool CBufferView::can_allocate(
        CBufferView::size_type const max_num_slots,
        CBufferView::size_type const max_num_objects,
        CBufferView::size_type const max_num_pointers,
        CBufferView::size_type const max_num_garbage_ranges
    ) const SIXTRL_NOEXCEPT
    {
        return ( ( this->allow_allocate() ) &&
                 ( this->has_capacity_for_allocate( max_num_slots,
                    max_num_objects, max_num_pointers,
                        max_num_garbage_ranges ) ) );
    }

    SIXTRL_INLINE CBufferView::status_t CBufferView::allocate(
        CBufferView::size_type const max_num_slots,
        CBufferView::size_type const max_num_objects,
        CBufferView::size_type const max_num_pointers,
        CBufferView::size_type const max_num_garbage_ranges ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef CBufferView::status_t   _status_t;
        typedef CBufferView::size_type  _size_t;

        SIXTRL_ASSERT( this->capacity() >= this->size() );

        _size_t new_buffer_size = _size_t{ 0 };

        _status_t status = ::NS(CObjFlatBuffer_allocate)(
            this->p_base(), this->capacity(), this->slot_size(),
                max_num_slots, max_num_objects, max_num_pointers,
                    max_num_garbage_ranges, &new_buffer_size );

        SIXTRL_ASSERT( ( status != st::STATUS_SUCCESS ) ||
            ( ( new_buffer_size <= this->capacity() ) &&
              ( new_buffer_size >= st::CBUFFER_MIN_SIZE ) &&
              ( new_buffer_size == ::NS(CObjFlatBuffer_size)(
                this->p_base(), this->slot_size() ) ) &&
              ( _size_t{ 0 }           == this->n_slots() ) &&
              ( _size_t{ 0 }           == this->n_objects() ) &&
              ( _size_t{ 0 }           == this->n_pointers() ) &&
              ( _size_t{ 0 }           == this->n_garbage() ) &&
              ( max_num_slots          <= this->max_slots() ) &&
              ( max_num_objects        <= this->max_objects() ) &&
              ( max_num_pointers       <= this->max_pointers() ) &&
              ( max_num_garbage_ranges <= this->max_garbage() ) ) );

        return status;
    }

    SIXTRL_INLINE CBufferView::status_t CBufferView::reallocate(
        CBufferView::size_type const max_num_slots,
        CBufferView::size_type const max_num_objects,
        CBufferView::size_type const max_num_pointers,
        CBufferView::size_type const max_num_garbage_ranges ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef CBufferView::status_t   _status_t;
        typedef CBufferView::size_type  _size_t;

        _status_t status = st::STATUS_GENERAL_FAILURE;

        SIXTRL_ASSERT( this->capacity() >= this->size() );

        _size_t new_buffer_size = _size_t{ 0 };

        if( this->allow_realloc() )
        {
            status = ::NS(CObjFlatBuffer_reallocate)( this->p_base(),
                this->capacity(), this->slot_size(), max_num_slots,
                    max_num_objects, max_num_pointers, max_num_garbage_ranges,
                        &new_buffer_size );
        }

        SIXTRL_ASSERT( ( status != st::STATUS_SUCCESS ) ||
            ( ( new_buffer_size <= this->capacity() ) &&
              ( new_buffer_size >= st::CBUFFER_MIN_SIZE ) &&
              ( new_buffer_size == ::NS(CObjFlatBuffer_size)(
                this->p_base(), this->slot_size() ) ) &&
              ( max_num_slots          <= this->max_slots() ) &&
              ( max_num_objects        <= this->max_objects() ) &&
              ( max_num_pointers       <= this->max_pointers() ) &&
              ( max_num_garbage_ranges <= this->max_garbage() ) ) );

        return status;
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE bool CBufferView::needs_remapping() const SIXTRL_NOEXCEPT
    {
        return ::NS(CObjFlatBuffer_needs_remapping)(
            this->p_base(), this->slot_size() );
    }

    SIXTRL_INLINE bool CBufferView::can_remap() const SIXTRL_NOEXCEPT
    {
        return ( ( this->allow_remap() ) && ( this->needs_remapping() ) );
    }

    SIXTRL_INLINE CBufferView::status_t CBufferView::remap() SIXTRL_NOEXCEPT
    {
        CBufferView::status_t status =
            SIXTRL_CXX_NAMESPACE::STATUS_GENERAL_FAILURE;

        if( this->allow_remap() )
        {
            status = ::NS(CObjFlatBuffer_remap)(
                this->p_base(), this->slot_size() );
        }

        return status;
    }

    /* ********************************************************************* */
    /* ******             READING ELEMENTS FROM THE BUFFER            ****** */
    /* ********************************************************************* */

    template< class T >
    SIXTRL_INLINE SIXTRL_BUFFER_OBJ_DATAPTR_DEC T const*
    CBufferView::get_object(
        CBufferView::size_type const pos_in_buffer,
        SIXTRL_BUFFER_ARGPTR_DEC const T *const ptr_cls_elem
    ) const SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_const_from_cobj_index< T >(
            this->index_at( pos_in_buffer ), this->slot_size(), ptr_cls_elem );
    }

    template< class T >
    SIXTRL_FN SIXTRL_BUFFER_OBJ_DATAPTR_DEC T const*
    CBufferView::get_const_object( CBufferView::size_type const pos_in_buffer,
        SIXTRL_BUFFER_ARGPTR_DEC const T *const ptr_cls_elem
    ) const SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_const_from_cobj_index< T >(
            this->index_at( pos_in_buffer ),
                this->slot_size(), ptr_cls_elem );
    }

    template< class T >
    SIXTRL_FN SIXTRL_BUFFER_OBJ_DATAPTR_DEC T* CBufferView::get_object(
        CBufferView::size_type const pos_in_buffer,
        SIXTRL_BUFFER_ARGPTR_DEC const T *const ptr_cls_elem ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_from_cobj_index< T >(
            this->index_at( pos_in_buffer ),
                this->slot_size(), ptr_cls_elem );
    }

    /* ***************************************************************** */
    /* *****  LOW-LEVEL SUPPORT FOR WRITING ELEMENTS TO THE BUFFER ***** */
    /* ***************************************************************** */

    template< class T >
    SIXTRL_FN bool CBufferView::can_add_copy_of_object(
        SIXTRL_BUFFER_ARGPTR_DEC const T *const SIXTRL_RESTRICT ptr_elem,
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView::size_type*
            SIXTRL_RESTRICT requ_buffer_size,
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView::size_type*
            SIXTRL_RESTRICT requ_n_slots,
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView::size_type*
            SIXTRL_RESTRICT requ_n_objs,
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView::size_type*
            SIXTRL_RESTRICT requ_n_ptrs ) const SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_can_add_copy_of_object(
            this->p_base(), this->slot_size(), ptr_elem, requ_buffer_size,
                requ_n_slots, requ_n_objs, requ_n_ptrs );
    }

    /* --------------------------------------------------------------------- */

    SIXTRL_INLINE void CBufferView::do_set_base_addr(
        CBufferView::address_t const base_addr ) SIXTRL_NOEXCEPT
    {
        this->m_base_addr = base_addr;
    }

    SIXTRL_INLINE void CBufferView::do_set_slot_size(
        CBufferView::size_type const slot_size ) SIXTRL_NOEXCEPT
    {
        this->m_slot_size = slot_size;
    }

    SIXTRL_INLINE void CBufferView::do_set_capacity(
        CBufferView::size_type const capacity ) SIXTRL_NOEXCEPT
    {
        this->m_capacity = capacity;
    }

    SIXTRL_INLINE void CBufferView::do_set_flags(
        CBufferView::flags_t const flags ) SIXTRL_NOEXCEPT
    {
        this->m_flags = flags;
    }
}

#endif /* c++ */
#endif /* SIXTRACKLIB_BASE_COBJECTS_CBUFFER_VIEW_H__*/
