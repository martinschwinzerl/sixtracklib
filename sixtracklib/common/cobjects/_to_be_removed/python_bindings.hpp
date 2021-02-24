#ifndef SIXTRACKLIB_COMMON_COBJECTS_PYTHON_BINDINGS_CXX_HPP__
#define SIXTRACKLIB_COMMON_COBJECTS_PYTHON_BINDINGS_CXX_HPP__

#if defined( __cplusplus ) && !defined( _GPUCODE )

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/cobjects/cbuffer_view.hpp"
#include "sixtracklib/common/cobjects/cbuffer.hpp"
#include "sixtracklib/common/internal/compiler_compability.h"
#include "sixtracklib/common/internal/type_store_traits.hpp"

namespace SIXTRL_CXX_NAMESPACE
{
namespace python
{
    template< class E >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() &&
        !SIXTRL_CXX_NAMESPACE::CObjElem_allow_delegate_storage< E >(),
        void >::type
    setup_cobjects_load_store_for_type(
        pybind11::module& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( m ),
        pybind11::class_< E >& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( elem_obj ),
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBufferView >&
            SIXTRL_RESTRICT_REF SIXTRL_UNUSED( cbuffer_view_obj ),
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBuffer >&
            SIXTRL_RESTRICT_REF SIXTRL_UNUSED( cbuffer_obj ),
        SIXTRL_BUFFER_DATAPTR_DEC const E *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( ptr_obj_dummy ) = nullptr )
     {
         return;
     }

     template< class E >
     SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >() ||
        SIXTRL_CXX_NAMESPACE::CObjElem_allow_delegate_storage< E >(),
        void >::type
    setup_cobjects_load_store_for_type(
        pybind11::module& SIXTRL_RESTRICT_REF m,
        pybind11::class_< E >& SIXTRL_RESTRICT_REF elem_obj,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBufferView >&
            SIXTRL_RESTRICT_REF cbuffer_view_obj,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBuffer >&
            SIXTRL_RESTRICT_REF cbuffer_obj,
        SIXTRL_BUFFER_ARGPTR_DEC const E *const
            SIXTRL_RESTRICT SIXTRL_UNUSED( ptr_obj_dummy ) = nullptr )
     {
        namespace st = SIXTRL_CXX_NAMESPACE;
        namespace py = pybind11;

        typedef st::CBufferView cbuffer_view_t;
        typedef st::CBuffer cbuffer_t;

        cbuffer_view_obj.def( "can_load_object",
            []( SIXTRL_BUFFER_ARGPTR_DEC cbuffer_view_t const&
                    SIXTRL_RESTRICT_REF self,
                st::cobj_size_t const pos_in_buffer,
                SIXTRL_BUFFER_ARGPTR_DEC E const& SIXTRL_RESTRICT_REF obj )
            {
                return self.can_load_object_type< E >(
                    pos_in_buffer, std::addressof( obj ) );
            },
            "Check whether we can update an destination object with the "
            "state loaded from the buffer at pos_in_buffer",
            py::arg( "pos_in_buffer" ), py::arg( "destination" ) );

        cbuffer_view_obj.def( "can_store_object",
            []( SIXTRL_BUFFER_ARGPTR_DEC cbuffer_view_t const&
                    SIXTRL_RESTRICT_REF self,
                st::cobj_size_t const pos_in_buffer,
                SIXTRL_BUFFER_ARGPTR_DEC E const& SIXTRL_RESTRICT_REF obj )
            {
                return self.can_store_object_type< E >(
                    pos_in_buffer, std::addressof( obj ) );
            },
            "Check whether we can update the buffer at pos_in_buffer with the "
            "state of the source object",
            py::arg( "pos_in_buffer" ), py::arg( "source" ) );

        cbuffer_view_obj.def( "prepare_load_object",
            []( SIXTRL_BUFFER_ARGPTR_DEC cbuffer_view_t const&
                    SIXTRL_RESTRICT_REF self,
                st::cobj_size_t const pos_in_buffer,
                SIXTRL_BUFFER_ARGPTR_DEC E& destination )
            {
                if( st::ARCH_STATUS_SUCCESS != self.prepare_load_object(
                    pos_in_buffer, std::addressof( destination ) ) )
                    throw std::runtime_error( "Unable to prepare obj for load" );
                return std::addressof( self );
            },"Prepare the destination object for loading with data from buffer"
            " at pos_in_buffer", py::arg( "pos_in_buffer" ),
            py::arg( "destination" ) );

        cbuffer_view_obj.def( "prepare_store_object",
            []( SIXTRL_BUFFER_ARGPTR_DEC cbuffer_view_t&
                    SIXTRL_RESTRICT_REF self,
                st::cobj_size_t const pos_in_buffer,
                SIXTRL_BUFFER_ARGPTR_DEC E const& source )
            {
                if( st::ARCH_STATUS_SUCCESS != self.prepare_load_object(
                    pos_in_buffer, std::addressof( source ) ) )
                    throw std::runtime_error( "Unable to prepare obj for store" );
                return std::addressof( self );
            },"Prepare the destination object for loading with data from buffer"
            " at pos_in_buffer", py::arg( "pos_in_buffer" ),
            py::arg( "source" ) );

        cbuffer_view_obj.def( "load_object",
            []( SIXTRL_BUFFER_ARGPTR_DEC cbuffer_view_t const&
                    SIXTRL_RESTRICT_REF self,
                st::cobj_size_t const pos_in_buffer,
                SIXTRL_BUFFER_ARGPTR_DEC E& SIXTRL_RESTRICT_REF destination )
            {
                if( st::ARCH_STATUS_SUCCESS != self.load_object< E >(
                    pos_in_buffer, std::addressof( destination ) ) )
                    throw std::runtime_error( "Unable to load obj from buffer" );
                return std::addressof( self );
            },
            "Load contents from buffer at pos_in_buffer into destination obj",
            py::arg( "pos_in_buffer" ), py::arg( "destination" ) );

        cbuffer_view_obj.def( "store_object",
            []( SIXTRL_BUFFER_ARGPTR_DEC cbuffer_view_t&
                    SIXTRL_RESTRICT_REF self,
                st::cobj_size_t const pos_in_buffer,
                SIXTRL_BUFFER_ARGPTR_DEC E const& SIXTRL_RESTRICT_REF source )
            {
                if( st::ARCH_STATUS_SUCCESS != self.store_object< E >(
                    pos_in_buffer, std::addressof( source ) ) )
                    throw std::runtime_error( "Unable to store obj to buffer" );
                return std::addressof( self );
            },
            "Stores state from obj to buffer at pos_in_buffer",
            py::arg( "pos_in_buffer" ), py::arg( "source" ) );

        /* ----------------------------------------------------------------- */

        elem_obj.def( "can_load_from",
            []( SIXTRL_BUFFER_ARGPTR_DEC E const& self,
                SIXTRL_BUFFER_ARGPTR_DEC cbuffer_view_t const& view,
                st::cobj_size_t idx )
            {
                return view.can_load_object_type< E >(
                    idx, std::addressof( self ) );
            }, py::arg( "view_or_buffer" ), py::arg( "index" ) );

        elem_obj.def( "prepare_load_from",
            []( SIXTRL_BUFFER_ARGPTR_DEC E& self,
                SIXTRL_BUFFER_ARGPTR_DEC cbuffer_view_t const& view,
                st::cobj_size_t idx )
            {
                if( st::ARCH_STATUS_SUCCESS != view.prepare_load_object< E >(
                    idx, std::addressof( self ) ) )
                    throw std::runtime_error( "Unable to prepare load obj" );
                return std::addressof( self );
            }, py::arg( "view_or_buffer" ), py::arg( "index" ) );

        elem_obj.def( "load_from",
            []( SIXTRL_BUFFER_ARGPTR_DEC E& SIXTRL_RESTRICT_REF self,
                SIXTRL_BUFFER_ARGPTR_DEC cbuffer_view_t const&
                    SIXTRL_RESTRICT_REF view, st::cobj_size_t const idx )
            {
                if( st::ARCH_STATUS_SUCCESS != view.load_object< E >(
                        idx, std::addressof( self ) ) )
                    throw std::runtime_error(
                        "Unable to load obj from buffer" );
                return std::addressof( self );
            }, py::arg( "view_or_buffer" ), py::arg( "index" ) );

        elem_obj.def( "can_store_to",
            []( SIXTRL_BUFFER_ARGPTR_DEC E const& self,
                SIXTRL_BUFFER_ARGPTR_DEC cbuffer_view_t const& view,
                st::cobj_size_t const idx )
            {
                return view.can_store_object_type< E >(
                    idx, std::addressof( self ) );
            }, py::arg( "view_or_buffer" ), py::arg( "index" ) );

        elem_obj.def( "prepare_store_to",
            []( SIXTRL_BUFFER_ARGPTR_DEC E const& self,
                SIXTRL_BUFFER_ARGPTR_DEC cbuffer_view_t& view,
                st::cobj_size_t const idx )
            {
                if( st::ARCH_STATUS_SUCCESS != view.prepare_store_object< E >(
                    idx, std::addressof( self ) ) )
                    throw std::runtime_error( "Unable to prepare store obj" );
                return std::addressof( self );
            }, py::arg( "view_or_buffer" ), py::arg( "index" ) );

        elem_obj.def( "store_to",
            []( SIXTRL_BUFFER_ARGPTR_DEC E const& SIXTRL_RESTRICT_REF self,
                SIXTRL_BUFFER_ARGPTR_DEC cbuffer_view_t&
                    SIXTRL_RESTRICT_REF view, st::cobj_size_t const idx )
            {
                if( st::ARCH_STATUS_SUCCESS != view.store_object< E >(
                        idx, std::addressof( self ) ) )
                    throw std::runtime_error( "Unable to store obj tobuffer" );
                return std::addressof( self );
            }, py::arg( "view_or_buffer" ), py::arg( "index" ) );
     }

     /* -------------------------------------------------------------------- */

    template< class E >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
       !SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >(),
        void >::type
    setup_cobjects_store_direct_base_for_type(
        pybind11::module& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( m ),
        pybind11::class_< E >& SIXTRL_RESTRICT_REF SIXTRL_UNUSED( elem_obj ),
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBufferView >&
            SIXTRL_RESTRICT_REF SIXTRL_UNUSED( cbuffer_view_obj ),
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBuffer >&
            SIXTRL_RESTRICT_REF SIXTRL_UNUSED( cbuffer_obj ),
        SIXTRL_BUFFER_DATAPTR_DEC const E *const
            SIXTRL_UNUSED( ptr_dummy ) = nullptr )
    {
        return;
    }

    template< class E >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjElem_allow_direct_storage< E >(),
        void >::type
    setup_cobjects_store_direct_base_for_type(
        pybind11::module& SIXTRL_RESTRICT_REF m,
        pybind11::class_< E >& SIXTRL_RESTRICT_REF elem_obj,
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBufferView >&
            SIXTRL_RESTRICT_REF SIXTRL_UNUSED( cbuffer_view_obj ),
        pybind11::class_< SIXTRL_CXX_NAMESPACE::CBuffer >&
            SIXTRL_RESTRICT_REF cbuffer_obj,
        SIXTRL_BUFFER_DATAPTR_DEC const E *const
            SIXTRL_UNUSED( ptr_dummy ) = nullptr )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        namespace py = pybind11;
        typedef SIXTRL_BUFFER_ARGPTR_DEC E elem_obj_t;

        cbuffer_obj.def( "add_copy",
         []( SIXTRL_BUFFER_ARGPTR_DEC st::CBuffer& SIXTRL_RESTRICT_REF self,
             SIXTRL_BUFFER_ARGPTR_DEC E const& SIXTRL_RESTRICT_REF orig )
            {
                SIXTRL_BUFFER_DATAPTR_DEC elem_obj_t* ptr_added_elem =
                self.add_copy< E >( &orig );

                if( ptr_added_elem == nullptr ) throw std::runtime_error(
                        "Unable to create elem obj on cbuffer" );
                return ptr_added_elem;
            }, py::arg( "orig" ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* free methods / functions */

        typedef st::CBufferView cbuffer_view_t;
        typedef st::CBuffer cbuffer_t;

        elem_obj.def_static( "add_copy",
         []( SIXTRL_BUFFER_ARGPTR_DEC cbuffer_t& SIXTRL_RESTRICT_REF cbuffer,
             SIXTRL_BUFFER_ARGPTR_DEC E const& SIXTRL_RESTRICT_REF orig )
           {
               elem_obj_t* ptr_added_elem = cbuffer.add_copy< E >( &orig );
                if( ptr_added_elem == nullptr ) throw std::runtime_error(
                        "Unable to create elem obj copy on cbuffer" );
                return ptr_added_elem;
           }, py::arg( "cbuffer"), py::arg( "orig" ) );

        elem_obj.def_static( "get",
            []( SIXTRL_BUFFER_ARGPTR_DEC cbuffer_t& SIXTRL_RESTRICT_REF cbuffer,
                st::cobj_size_t const idx )
            {
                elem_obj_t* ptr_elem = cbuffer.get_object< E >( idx );
                if( ptr_elem == nullptr ) throw std::runtime_error(
                        "Unable to get elem obj from cbuffer" );
                return ptr_elem ;
           }, py::arg( "view_or_buffer" ), py::arg( "index" ) );

        /* ----------------------------------------------------------------- */
        /* cobjects buffer methods */

        elem_obj.def_property_readonly_static( "cobj_type_id",
            []( py::object SIXTRL_UNUSED( self ) )
            { return st::CObjElem_type_id< E >(); },
            "cobjects type_id of the associated type" );

        elem_obj.def_property_readonly_static( "cobj_num_ptrs",
            []( py::object SIXTRL_UNUSED( self ) )
            { return st::CObjElem_num_ptrs< E >( nullptr ); },
            "cobjects num of dataptrs for the associated type" );
    }

} /* namespace: python */
} /* namespace: SIXTRL_CXX_NAMESPACE */

#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_COBJECTS_PYTHON_BINDINGS_CXX_HPP__ */
