#ifndef SIXTRACKLIB_COMMON_COBJECTS_OBJ_BASE_CLASS_CXX_HPP__
#define SIXTRACKLIB_COMMON_COBJECTS_OBJ_BASE_CLASS_CXX_HPP__

#if defined( __cplusplus )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cstdlib>
    #include <type_traits>
    #include <iostream>
    #if !defined( _GPUCODE )
        #include <vector>
    #endif /* !defiend( _GPUCODE ) */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/cobjects/element_traits.hpp"
    #include "sixtracklib/common/cobjects/element_pointers.hpp"
    #include "sixtracklib/common/cobjects/field_offsets.hpp"
    #include "sixtracklib/common/cobjects/field_sizes.hpp"
    #include "sixtracklib/common/cobjects/field_counts.hpp"
    #include "sixtracklib/common/cobjects/index_object.h"
    #include "sixtracklib/common/internal/obj_base_class.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template< class ObjData, class Derived >
    class ObjDataStorageInterfaceBase< ObjData,
        SIXTRL_CXX_NAMESPACE::STORAGE_BE_COBJECTS, Derived > :
        public ObjDataInterfaceBase< ObjData,
            SIXTRL_CXX_NAMESPACE::cobj_type_id_t, Derived >
    {
        private:

        typedef SIXTRL_CXX_NAMESPACE::ObjDataDelegateStorageTraits<
            ObjData, SIXTRL_CXX_NAMESPACE::STORAGE_BE_COBJECTS >
            _delegate_traits_t;

        typedef SIXTRL_CXX_NAMESPACE::ObjDataInterfaceBase< ObjData,
            SIXTRL_CXX_NAMESPACE::cobj_type_id_t, Derived > _base_t;

        typedef SIXTRL_CXX_NAMESPACE::ObjDataStorageInterfaceBase<
            ObjData, SIXTRL_CXX_NAMESPACE::STORAGE_BE_COBJECTS, Derived >
                _this_t;

        public:

        typedef SIXTRL_CXX_NAMESPACE::store_backend_t   store_backend_t;
        typedef typename _base_t::type_id_t             type_id_t;
        typedef typename _base_t::cxx_api_t             cxx_api_t;
        typedef typename _base_t::c_api_t               c_api_t;
        typedef typename _base_t::size_type             size_type;
        typedef typename _base_t::status_t              status_t;
        typedef typename _delegate_traits_t::Delegate   delegate_t;
        typedef SIXTRL_CXX_NAMESPACE::buffer_addr_t     buffer_addr_t;
        typedef ::NS(CObjIndex)                         index_obj_t;
        typedef ObjData                                 obj_data_t;

        using ObjDataInterfaceBase< ObjData, type_id_t, Derived >::operator=;
        using ObjDataInterfaceBase<
                ObjData, type_id_t, Derived >::ObjDataInterfaceBase;

        protected:

        SIXTRL_FN ~ObjDataStorageInterfaceBase() = default;

        public:

        static constexpr store_backend_t STORAGE_BACKEND = STORAGE_BE_COBJECTS;

        static SIXTRL_FN constexpr bool allow_direct_storage() SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage<
                cxx_api_t >();
        }

//         static SIXTRL_FN constexpr bool
//             has_delegate_type_defined() SIXTRL_NOEXCEPT
//         {
//             return SIXTRL_CXX_NAMESPACE::ObjDataCObjects_has_delegate_type_defined<
//                 cxx_api_t >();
//         }

//         static SIXTRL_FN constexpr bool
//             allow_delegate_storage() SIXTRL_NOEXCEPT
//         {
//             return SIXTRL_CXX_NAMESPACE::ObjDataCObjects_allow_delegate_storage<
//                 cxx_api_t >();
//         }

        /* ----------------------------------------------------------------- */
        /* dataptrs - interface */

        static SIXTRL_FN constexpr size_type min_num_ptrs() SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::CObjElem_min_num_ptrs< cxx_api_t >();
        }

        static SIXTRL_FN constexpr size_type max_num_ptrs() SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::CObjElem_max_num_ptrs< cxx_api_t >();
        }

        static SIXTRL_FN constexpr bool
        few_enough_ptrs_for_static_arrays() SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::CObjElem_few_enough_ptrs_for_static_array<
                cxx_api_t >();
        }

        static SIXTRL_FN constexpr bool
        too_many_ptrs_for_static_array() SIXTRL_NOEXCEPT
        {
            return
            SIXTRL_CXX_NAMESPACE::CObjElem_too_many_ptrs_for_static_array<
                cxx_api_t >();
        }

        static SIXTRL_FN constexpr bool
        definitely_has_no_ptrs() SIXTRL_NOEXCEPT
        {
            return
            SIXTRL_CXX_NAMESPACE::CObjElem_too_many_ptrs_for_static_array<
                cxx_api_t >();
        }

        static SIXTRL_FN constexpr bool
        definitely_has_ptrs() SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::CObjElem_definitely_has_ptrs<
                cxx_api_t >();
        }

        static SIXTRL_FN constexpr bool
        has_const_num_ptrs() SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::CObjElem_has_const_num_ptrs<
                cxx_api_t >();
        }

        static SIXTRL_FN constexpr bool
        allows_var_num_ptrs() SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::CObjElem_has_const_num_ptrs<
                cxx_api_t >();
        }

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_FN bool dataptr_index_legal(
            size_type const idx ) const SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::CObjElem_dataptr_index_legal(
                idx, this->as_ptr_const_data() );
        }

        SIXTRL_FN bool dataptr_index_illegal(
            size_type const idx ) const SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::CObjElem_dataptr_index_illegal(
                idx, this->as_ptr_const_data() );
        }

        template< class E = ObjData, typename std::enable_if<
            std::is_same< typename std::decay< E >::type, ObjData >::value &&
            ( SIXTRL_CXX_NAMESPACE::CObjElem_definitely_has_no_ptrs<
                E >() ||
              SIXTRL_CXX_NAMESPACE::CObjElem_has_const_num_ptrs< E >() )
                >::type >
        static SIXTRL_FN constexpr size_type num_ptrs(
            SIXTRL_BUFFER_OBJ_DATAPTR_DEC const E *const SIXTRL_RESTRICT
                /* ptr */ ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::CObjElem_num_ptrs< E >();
        }

        template< class E = ObjData, typename std::enable_if<
            std::is_same< typename std::decay< E >::type, ObjData >::value &&
            !SIXTRL_CXX_NAMESPACE::CObjElem_definitely_has_no_ptrs<
                E >() &&
            !SIXTRL_CXX_NAMESPACE::CObjElem_has_const_num_ptrs< E >() &&
             SIXTRL_CXX_NAMESPACE::CObjElem_allows_var_num_ptrs< E >()
        >::type >
        static SIXTRL_FN size_type num_ptrs( SIXTRL_BUFFER_OBJ_DATAPTR_DEC
            const E *const SIXTRL_RESTRICT ptr ) SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::CObjElem_num_ptrs< E >( ptr );
        }

        SIXTRL_FN size_type num_ptrs() const SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::CObjElem_num_ptrs< cxx_api_t >(
                this->as_ptr_data() );
        }

        /* ----------------------------------------------------------------- */
        /* layout - params interfaces: */

        /* a) offsets: */
        static SIXTRL_FN constexpr bool can_obtain_field_offset() SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::CObjElem_can_obtain_field_offsets<
                cxx_api_t >();
        }

        static SIXTRL_FN constexpr bool has_always_same_offsets() SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::CObjElem_has_always_same_offsets<
                cxx_api_t >();
        }

        static SIXTRL_FN constexpr bool
        requires_inspection_for_offsets() SIXTRL_NOEXCEPT
        {
            return
            SIXTRL_CXX_NAMESPACE::CObjElem_requires_inspection_for_offsets<
                cxx_api_t >();
        }

        template< class E = ObjData, typename std::enable_if<
            std::is_same< typename std::decay< E >::type, ObjData >::value
            >::type >
        static SIXTRL_FN status_t field_offsets(
            SIXTRL_ARGPTR_DEC size_type* SIXTRL_RESTRICT params_begin,
            SIXTRL_ARGPTR_DEC size_type const max_num_params_to_get,
            SIXTRL_BUFFER_OBJ_DATAPTR_DEC const E  *const SIXTRL_RESTRICT ptr )
        {
            return SIXTRL_CXX_NAMESPACE::CObjElem_field_offsets< E >(
                params_begin, max_num_params_to_get, ptr );
        }

        /*------------------------------------------------------------------ */
        /* b) sizes: */

        static SIXTRL_FN constexpr bool has_always_same_sizes() SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::CObjElem_has_always_same_sizes<
                cxx_api_t >();
        }

        static SIXTRL_FN constexpr bool
            requires_inspection_for_sizes() SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::CObjElem_requires_inspection_for_sizes<
                cxx_api_t >();
        }

        template< class E = ObjData, typename std::enable_if<
            std::is_same< typename std::decay< E >::type, ObjData >::value
            >::type >
        static SIXTRL_FN status_t field_sizes(
            SIXTRL_ARGPTR_DEC size_type* SIXTRL_RESTRICT params_begin,
            SIXTRL_ARGPTR_DEC size_type const max_num_params_to_get,
            SIXTRL_BUFFER_OBJ_DATAPTR_DEC const E  *const SIXTRL_RESTRICT ptr )
        {
            return SIXTRL_CXX_NAMESPACE::CObjElem_field_sizes< E >(
                params_begin, max_num_params_to_get, ptr );
        }

        /*------------------------------------------------------------------ */
        /* c) counts: */

        template< class E = ObjData, typename std::enable_if<
            std::is_same< typename std::decay< E >::type, ObjData >::value
            >::type >
        static SIXTRL_FN status_t field_counts(
            SIXTRL_ARGPTR_DEC size_type* SIXTRL_RESTRICT params_begin,
            SIXTRL_ARGPTR_DEC size_type const max_num_params_to_get,
            SIXTRL_BUFFER_OBJ_DATAPTR_DEC const E *const SIXTRL_RESTRICT ptr )
        {
            return SIXTRL_CXX_NAMESPACE::CObjElem_field_counts< E >(
                    params_begin, max_num_params_to_get, ptr );
        }
    };
}

#endif /* __cplusplus */

#endif /* SIXTRACKLIB_COMMON_COBJECTS_OBJ_BASE_CLASS_CXX_HPP__ */
