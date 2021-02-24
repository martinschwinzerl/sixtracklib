#ifndef SIXTRACKLIB_COMMON_COBJECTS_CBUFFER_H__
#define SIXTRACKLIB_COMMON_COBJECTS_CBUFFER_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/cobjects/cbuffer_view.hpp"
    #include "sixtracklib/common/cobjects/obj_delegate.hpp"
    #include "sixtracklib/common/cobjects/element_store_restore.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cstdlib>
    #include <type_traits>
    #include <memory>
    #include <vector>
    #include <string>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */
#endif /* C++ */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    class CBuffer : public CBufferView
    {
        private:
        typedef std::vector< raw_type > raw_buffer_type;

        protected:

        static constexpr size_type
            DEFAULT_REALLOC_FACTOR_NOMINATOR = size_type{ 1 };

        static constexpr size_type
            DEFAULT_REALLOC_FACTOR_DENOMINATOR = size_type{ 1 };

        public:

        static constexpr flags_type FLAGS_CBUFFER_DEFAULT =
            CBufferView::FLAGS_ALLOW_REMAPPING |
            CBufferView::FLAGS_ALLOW_ALLOC     |
            CBufferView::FLAGS_ALLOW_REALLOC   |
            CBufferView::FLAGS_ALLOW_APPEND    |
            CBufferView::FLAGS_OWNS_STORED_DATA;

        SIXTRL_HOST_FN explicit CBuffer(
            size_type capacity = CBufferView::BUFFER_MINIMAL_SIZE,
            size_type const slot_size = CBufferView::DEFAULT_SLOT_SIZE,
            flags_type const flags = FLAGS_CBUFFER_DEFAULT );

        SIXTRL_HOST_FN CBuffer( CBufferView const& SIXTRL_RESTRICT_REF view,
            flags_type const flags = FLAGS_CBUFFER_DEFAULT );

        SIXTRL_HOST_FN CBuffer( char const* SIXTRL_RESTRICT path_to_file,
            size_type const slot_size = CBufferView::DEFAULT_SLOT_SIZE,
            flags_type const flags = FLAGS_CBUFFER_DEFAULT );

        SIXTRL_HOST_FN CBuffer(
            std::string const& SIXTRL_RESTRICT_REF path_to_file,
            size_type const slot_size = CBufferView::DEFAULT_SLOT_SIZE,
            flags_type const flags = FLAGS_CBUFFER_DEFAULT );

        SIXTRL_HOST_FN CBuffer(
            size_type const max_num_slots,
            size_type const max_num_objects,
            size_type const max_num_pointers,
            size_type const max_num_garbage_ranges,
            size_type const slot_size = CBufferView::DEFAULT_SLOT_SIZE,
            flags_type const flags = FLAGS_CBUFFER_DEFAULT );

        SIXTRL_HOST_FN CBuffer( CBuffer const& orig ) = default;
        SIXTRL_HOST_FN CBuffer( CBuffer&& orig ) = default;

        SIXTRL_HOST_FN CBuffer& operator=( CBuffer const& rhs ) = default;
        SIXTRL_HOST_FN CBuffer& operator=( CBuffer&& rhs ) = default;

        virtual SIXTRL_HOST_FN ~CBuffer() = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_type reserve( size_type capacity );

        SIXTRL_HOST_FN status_type reserve(
            size_type const max_num_slots,
            size_type const max_num_objects,
            size_type const max_num_pointers,
            size_type const max_num_garbage_ranges );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_type from_view(
            CBufferView const& SIXTRL_RESTRICT_REF view );

        SIXTRL_HOST_FN status_type from_flat_buffer(
            ::NS(cobj_raw_const_pointer) SIXTRL_RESTRICT flat_buffer_begin,
            size_type const slot_size );

        SIXTRL_HOST_FN status_type fromfile(
            std::string const& SIXTRL_RESTRICT_REF path_to_file );

        SIXTRL_HOST_FN status_type fromfile(
            char const* SIXTRL_RESTRICT path_to_file );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN status_type tofile(
            std::string const& SIXTRL_RESTRICT_REF path_to_file ) const;

        SIXTRL_HOST_FN status_type tofile(
            std::string const& SIXTRL_RESTRICT_REF path_to_file,
            addr_type const normalized_base_addr );

        SIXTRL_HOST_FN status_type tofile(
            char const* SIXTRL_RESTRICT path_to_file ) const;

        SIXTRL_HOST_FN status_type tofile(
            char const* SIXTRL_RESTRICT path_to_file,
            addr_type const normalized_base_addr );

        /* ----------------------------------------------------------------- */
        /* add_copy: */

        template< class E, store_backend_type SrcStoreT =
                  SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT >
        SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
            ( SrcStoreT == SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL ) ||
            ( !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
              !SIXTRL_CXX_NAMESPACE::CObjElem_allow_delegate_storage< E >() ),
               SIXTRL_BUFFER_DATAPTR_DEC E* >::type
        add_copy( SIXTRL_BUFFER_ARGPTR_DEC const E *const
                    SIXTRL_RESTRICT SIXTRL_UNUSED( elem ),
                  bool const SIXTRL_UNUSED( init_with_zeros ) = false )
        {
            return SIXTRL_NULLPTR;
        }

        template< class E, store_backend_type SrcStoreT =
                  SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT >
        SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
            SrcStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL &&
             SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
            !SIXTRL_CXX_NAMESPACE::CObjElem_allow_delegate_storage< E >(),
             SIXTRL_BUFFER_DATAPTR_DEC E* >::type
        add_copy( SIXTRL_BUFFER_ARGPTR_DEC const E *const elem,
                  bool const init_with_zeros = false ) {
            namespace st = SIXTRL_CXX_NAMESPACE;
            typedef CBuffer::size_type st_size_type;

            SIXTRL_BUFFER_DATAPTR_DEC E* added_elem = SIXTRL_NULLPTR;

            if( elem != SIXTRL_NULLPTR ) {
                SIXTRL_ARGPTR_DEC st_size_type requ_n_slots = st_size_type{ 0 };
                SIXTRL_ARGPTR_DEC st_size_type requ_n_objs  = st_size_type{ 0 };
                SIXTRL_ARGPTR_DEC st_size_type requ_n_ptrs  = st_size_type{ 0 };
                SIXTRL_ARGPTR_DEC st_size_type requ_buf_size = st_size_type{ 0 };

                bool can_add_copy = this->can_add_copy_of_object( elem,
                    &requ_buf_size, &requ_n_slots, &requ_n_objs, &requ_n_ptrs );

                if( !can_add_copy ) {
                    st::CBuffer::status_type status =
                        ( this->capacity() >= requ_buf_size )
                        ? st::STATUS_SUCCESS : this->reserve( requ_buf_size );

                    if( ( status == st::STATUS_SUCCESS ) &&
                        ( this->capacity() >= requ_buf_size ) ) {
                        status = this->reallocate( requ_n_slots, requ_n_objs
                            , requ_n_ptrs, this->max_garbage() ); }

                    if( status == st::STATUS_SUCCESS ) {
                        status = st::STATUS_GENERAL_FAILURE;
                        can_add_copy = this->can_add_copy_of_object( elem,
                            &requ_buf_size, &requ_n_slots, &requ_n_objs,
                                &requ_n_ptrs ); }
                }

                if( can_add_copy ) {
                    added_elem = st::CObjElem_add_copy_of_object< E >(
                        this->p_base(), this->slot_size(), elem, init_with_zeros
                    ); }
            }
            return added_elem;
        }

        template< class SrcT, CBufferView::store_backend_type SrcStoreT =
                  SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT >
        SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
            SrcStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL &&
            !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< SrcT >() &&
             SIXTRL_CXX_NAMESPACE::CObjElem_allow_delegate_storage< SrcT >(),
             SIXTRL_BUFFER_DATAPTR_DEC typename
                 SIXTRL_CXX_NAMESPACE::ObjDataDelegateTraits<
                     SrcT >::delegate_t* >::type
        add_copy( SIXTRL_BUFFER_ARGPTR_DEC const SrcT *const elem,
                  bool const init_with_zeros = false ) {
            namespace st = SIXTRL_CXX_NAMESPACE;
            constexpr store_backend_type DstStoreT = st::STORAGE_BE_COBJECTS;

            using DstT = typename st::ObjDataDelegateTraits<
                SrcT >::delegate_type;

            using conv_type = st::ObjDataConverter<
                SrcT, DstT, SrcStoreT, DstStoreT >;

            SIXTRL_BUFFER_DATAPTR_DEC DstT* added_elem = SIXTRL_NULLPTR;
            static_assert( st::CObjElem_allow_direct_storage< DstT >(),
                           "Delegate type should allow direct storage" );

            static_assert( st::ObjData_allow_type_conversion<
                SrcT, DstT, SrcStoreT, DstStoreT >(), "Illegal conversion" );

            status_type status = st::STATUS_GENERAL_FAILURE;
            if( elem != SIXTRL_NULLPTR )
            {
                SIXTRL_BUFFER_ARGPTR_DEC DstT temp;
                st::ObjDataInitialiser< DstT, DstStoreT >::preset( &temp );

                status = ( st::ObjData_type_conversion_can_requ_prepare< SrcT,
                            DstT, SrcStoreT, DstStoreT >() )
                    ? conv_type::prepare( &temp, elem ) : st::STATUS_SUCCESS;

                if( status == st::STATUS_SUCCESS )
                {
                    added_elem = this->add_copy< DstT >( &temp, init_with_zeros);
                    status = ( conv_type::allow( added_elem, elem ) )
                        ? conv_type::perform( added_elem, elem )
                        : st::STATUS_GENERAL_FAILURE;

                    if( status != st::STATUS_SUCCESS ) {
                        /* TODO; rollback the adding of the element! */
                        added_elem = SIXTRL_NULLPTR; }
                }
            }

            return added_elem; }

        /* ----------------------------------------------------------------- */
        /* create new: */

        template< class E, store_backend_type SrcStoreT =
                  SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT, typename... Args >
        SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
            !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
            !SIXTRL_CXX_NAMESPACE::CObjElem_allow_delegate_storage< E >(),
            SIXTRL_BUFFER_DATAPTR_DEC E* >::type
        create_new( Args&&... SIXTRL_UNUSED( init_parameters ) ) {
            return SIXTRL_NULLPTR; }

        template< class E, store_backend_type SrcStoreT =
                  SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT, typename... Args >
        SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
             SrcStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL &&
             SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
             !SIXTRL_CXX_NAMESPACE::CObjElem_allow_delegate_storage< E >(),
             SIXTRL_BUFFER_DATAPTR_DEC E* >::type
        create_new( Args&&... init_parameters ) {
            namespace st = SIXTRL_CXX_NAMESPACE;
            SIXTRL_BUFFER_DATAPTR_DEC E* added_elem = SIXTRL_NULLPTR;
            SIXTRL_BUFFER_ARGPTR_DEC E temp;
            if( st::ObjDataInitialiser< E >::init( &temp, std::forward< Args >(
                    init_parameters )... ) == st::STATUS_SUCCESS ) {
                added_elem = this->add_copy< E, SrcStoreT >( &temp ); }
            return added_elem; }

        template< class E, store_backend_type SrcStoreT =
                  SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT, typename... Args >
        SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
             SrcStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL &&
            !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
             SIXTRL_CXX_NAMESPACE::CObjElem_allow_delegate_storage< E >(),
             SIXTRL_BUFFER_DATAPTR_DEC typename
                 SIXTRL_CXX_NAMESPACE::ObjDataDelegateTraits< E >::delegate_t*
        >::type create_new( Args&&... init_parameters ) {
            namespace st = SIXTRL_CXX_NAMESPACE;
            using DstT = typename st::ObjDataDelegateTraits< E >::delegate_type;

            SIXTRL_BUFFER_DATAPTR_DEC DstT* added_elem = SIXTRL_NULLPTR;
            SIXTRL_BUFFER_ARGPTR_DEC E temp;

            if( st::ObjDataInitialiser< E >::init( &temp, std::forward< Args >(
                    init_parameters )... ) == st::STATUS_SUCCESS )
            {
                SIXTRL_BUFFER_ARGPTR_DEC DstT delegate_temp;
                st::ObjDataInitialiser< DstT, st::STORAGE_BE_DEFAULT >::preset(
                    &delegate_temp );

                st::status_type status =
                    ( st::ObjData_type_conversion_can_requ_prepare< E, DstT,
                          SrcStoreT, st::STORAGE_BE_DEFAULT >() )
                    ? st::ObjDataConverter< E, DstT, st::STORAGE_BE_DEFAULT,
                        st::STORAGE_BE_DEFAULT >::prepare( &delegate_temp, &temp )
                    : st::STATUS_SUCCESS;

                if( status == st::STATUS_SUCCESS ) {
                    added_elem = this->add_copy< DstT >( &delegate_temp ); }

                if( added_elem != SIXTRL_NULLPTR ) {
                    using conv_type = st::ObjDataConverter< E, DstT,
                            st::STORAGE_BE_DEFAULT, st::STORAGE_BE_COBJECTS >;

                    status = ( conv_type::allow( added_elem, &temp ) )
                        ? conv_type::perform( added_elem, &temp )
                        : st::STATUS_GENERAL_FAILURE;

                    if( status != st::STATUS_SUCCESS ) {
                        /* TODO; rollback the adding of the element! */
                        added_elem = SIXTRL_NULLPTR; }
                }
            }
            return added_elem; }

        /* ----------------------------------------------------------------- */
        /* add new: */

        template< class E, store_backend_type SrcStoreT =
                  SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT, typename... Args >
        SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
            !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
            !SIXTRL_CXX_NAMESPACE::CObjElem_allow_delegate_storage< E >(),
            SIXTRL_BUFFER_DATAPTR_DEC E* >::type
        add( Args&&... SIXTRL_UNUSED( init_parameters ) ) { return SIXTRL_NULLPTR; }

        template< class E, store_backend_type SrcStoreT =
                  SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT, typename... Args >
        SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
             SrcStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL &&
             SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
             !SIXTRL_CXX_NAMESPACE::CObjElem_allow_delegate_storage< E >(),
             SIXTRL_BUFFER_DATAPTR_DEC E* >::type
        add( Args&&... init_parameters ) {
            namespace st = SIXTRL_CXX_NAMESPACE;
            SIXTRL_BUFFER_DATAPTR_DEC E* added_elem = SIXTRL_NULLPTR;
            SIXTRL_BUFFER_ARGPTR_DEC E temp;
            if( st::ObjDataInitialiser< E >::init( &temp, std::forward< Args >(
                    init_parameters )... ) == st::STATUS_SUCCESS ) {
                added_elem = this->add_copy< E, SrcStoreT >( &temp ); }
            return added_elem; }

        template< class E, store_backend_type SrcStoreT =
                  SIXTRL_CXX_NAMESPACE::STORAGE_BE_DEFAULT, typename... Args >
        SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
             SrcStoreT != SIXTRL_CXX_NAMESPACE::STORAGE_BE_ILLEGAL &&
            !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
             SIXTRL_CXX_NAMESPACE::CObjElem_allow_delegate_storage< E >(),
             SIXTRL_BUFFER_DATAPTR_DEC typename
                 SIXTRL_CXX_NAMESPACE::ObjDataDelegateTraits< E >::delegate_t*
        >::type add( Args&&... init_parameters )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            using DstT = typename st::ObjDataDelegateTraits< E >::delegate_type;

            SIXTRL_BUFFER_DATAPTR_DEC DstT* added_elem = SIXTRL_NULLPTR;
            SIXTRL_BUFFER_ARGPTR_DEC E temp;

            if( st::ObjDataInitialiser< E >::init( &temp, std::forward< Args >(
                    init_parameters )... ) == st::STATUS_SUCCESS )
            {
                SIXTRL_BUFFER_ARGPTR_DEC DstT delegate_temp;
                st::ObjDataInitialiser< DstT, st::STORAGE_BE_DEFAULT >::preset(
                    &delegate_temp );

                st::status_type status =
                    ( st::ObjData_type_conversion_can_requ_prepare< E, DstT,
                          SrcStoreT, st::STORAGE_BE_DEFAULT >() )
                    ? st::ObjDataConverter< E, DstT, st::STORAGE_BE_DEFAULT,
                        st::STORAGE_BE_DEFAULT >::prepare( &delegate_temp, &temp)
                    : st::STATUS_SUCCESS;

                if( status == st::STATUS_SUCCESS ) {
                    added_elem = st::CBufferView_add_copy_of_object_detail(
                        *this, &delegate_temp, nullptr, nullptr, nullptr,
                            nullptr, true ); }

                if( added_elem != SIXTRL_NULLPTR ) {
                    using conv_type = st::ObjDataConverter< E, DstT,
                            st::STORAGE_BE_DEFAULT, st::STORAGE_BE_COBJECTS >;

                    status = ( conv_type::allow( added_elem, &temp ) )
                        ? conv_type::perform( added_elem, &temp )
                        : st::STATUS_GENERAL_FAILURE;

                    if( status != st::STATUS_SUCCESS ) {
                        /* TODO; rollback the adding of the element! */
                        added_elem = SIXTRL_NULLPTR; }
                }
            }
            return added_elem; }

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN status_type set_realloc_factor(
            size_type realloc_factor ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_type set_realloc_factor_frac(
            size_type realloc_factor_nominator,
            size_type realloc_factor_denominator ) SIXTRL_NOEXCEPT;

        private:

        raw_buffer_type m_raw_buffer;

        size_type m_realloc_factor_nominator =
            DEFAULT_REALLOC_FACTOR_NOMINATOR;

        size_type m_realloc_factor_denominator =
            DEFAULT_REALLOC_FACTOR_DENOMINATOR;
    };
} /* end: SIXTRL_CXX_NAMESPACE */

extern "C" {

typedef SIXTRL_CXX_NAMESPACE::CBuffer NS(CBuffer);

}

#else

typedef struct NS(CBuffer) NS(CBuffer);

#endif /* C++, Host */
#endif /* SIXTRACKLIB_COMMON_COBJECTS_CBUFFER_H__ */

