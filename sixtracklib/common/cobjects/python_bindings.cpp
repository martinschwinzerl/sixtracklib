#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

#include <memory>
#include <string>
#include <tuple>
#include <iostream>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/cobjects/definitions.h"
#include "sixtracklib/common/cobjects/cbuffer_view.hpp"
#include "sixtracklib/common/cobjects/cbuffer.hpp"
#include "sixtracklib/common/internal/compiler_compability.h"

namespace SIXTRL_CXX_NAMESPACE
{
namespace python
{
    namespace
    {
        namespace py = pybind11;
        namespace st = SIXTRL_CXX_NAMESPACE;

        typedef SIXTRL_CXX_NAMESPACE::CBufferView view_t;
        typedef SIXTRL_CXX_NAMESPACE::CBuffer     buffer_t;

        template <typename... Args>
        using overload_cast_ = pybind11::detail::overload_cast_impl<Args...>;
    }

    void init_common_cobjects( py::module& m,
                               py::class_< view_t >& cbuffer_view,
                               py::class_< buffer_t >& cbuffer )
    {
        cbuffer_view.def( py::init<view_t::address_t, view_t::size_type,
                           view_t::size_type, view_t::flags_t >(),
                         py::arg( "base_addr" ) = view_t::NULL_ADDRESS,
                         py::arg( "slot_size" ) = view_t::DEFAULT_SLOT_SIZE,
                         py::arg( "capacity"  ) = view_t::size_type{ 0 },
                         py::arg( "flags"     ) = view_t::FLAGS_BASE_DEFAULT );



        cbuffer_view.def_static( "add_flag_to_set", &view_t::add_flag_to_set,
            "add a CBufferView/CBuffer property flag to a flagset",
            py::arg( "flag_set" ), py::arg( "flag" ) );

        cbuffer_view.def_static( "remove_flag_from_set",
            &view_t::remove_flag_from_set,
            "remove a CBufferView/CBuffer property flag from a flag set",
            py::arg( "flag_set" ), py::arg( "flag" ) );

        cbuffer_view.def_static( "is_flag_set", &view_t::is_flag_set,
            "checks if a CBufferView/CBuffer property flag set contains a specific flag",
            py::arg( "flag_set" ), py::arg( "flag" ) );

        cbuffer_view.def_static( "required_buffer_length",
            &view_t::required_buffer_length,
            "calculate the required CBufferView/CBuffer capacity for a given "
            "layout, assuming default / standard parameters",
            py::arg( "max_num_slots" ), py::arg( "max_num_objects" ),
            py::arg( "max_num_pointers" ),
            py::arg( "max_num_garbage_ranges" ) = view_t::size_type{ 0 },
            py::arg( "slot_size" ) = view_t::DEFAULT_SLOT_SIZE );

        cbuffer_view.def_static( "aligned_base_addr",
             []( view_t::address_t const raw_base_addr,
                 view_t::size_type const raw_capacity,
                 view_t::size_type const alignment,
                 view_t::size_type const slot_size ) ->
                 std::tuple< view_t::address_t, view_t::size_type >
             {
                 view_t::size_type result_capacity = view_t::size_type{ 0 };
                 view_t::address_t const base_addr = view_t::aligned_base_addr(
                     raw_base_addr, raw_capacity, alignment, &result_capacity,
                         slot_size );

                 return std::make_tuple( base_addr, result_capacity );
             },
             "find first base_addr starting from any given raw_base_addr that "
             "fulfilles the given alignment properties, optionally returns "
             "the modified capacity",
             py::arg( "raw_base_addr" ), py::arg( "raw_capacity" ),
             py::arg( "alignment" ) = view_t::size_type{ 1 },
             py::arg( "slot_size" ) = view_t::DEFAULT_SLOT_SIZE );

        cbuffer_view.def_property_readonly( "flags", &view_t::flags );
        cbuffer_view.def_property_readonly( "allow_remap", &view_t::allow_remap );
        cbuffer_view.def_property_readonly( "allow_allocate", &view_t::allow_allocate );
        cbuffer_view.def_property_readonly( "allow_append", &view_t::allow_append );
        cbuffer_view.def_property_readonly( "owns_stored_data", &view_t::owns_stored_data );
        cbuffer_view.def_property_readonly( "has_special_memory", &view_t::has_special_memory );

        cbuffer_view.def_property_readonly( "slot_size", &view_t::slot_size );
        cbuffer_view.def_property_readonly( "size", &view_t::size );
        cbuffer_view.def_property_readonly( "capacity", &view_t::capacity );
        cbuffer_view.def_property_readonly( "size_header", &view_t::size_header );
        cbuffer_view.def( "size_section_header", &view_t::size_section_header );

        cbuffer_view.def_property_readonly( "size_slots", &view_t::size_slots );
        cbuffer_view.def_property_readonly( "size_objects", &view_t::size_objects );
        cbuffer_view.def_property_readonly( "size_pointers", &view_t::size_pointers );
        cbuffer_view.def_property_readonly( "size_garbage", &view_t::size_garbage );

        cbuffer_view.def_property_readonly( "n_slots", &view_t::n_slots );
        cbuffer_view.def_property_readonly( "n_objects", &view_t::n_objects );
        cbuffer_view.def_property_readonly( "n_pointers", &view_t::n_pointers );
        cbuffer_view.def_property_readonly( "n_garbage", &view_t::n_garbage );

        cbuffer_view.def_property_readonly( "max_slots", &view_t::max_slots );
        cbuffer_view.def_property_readonly( "max_objects", &view_t::max_objects );
        cbuffer_view.def_property_readonly( "max_pointers", &view_t::max_pointers );
        cbuffer_view.def_property_readonly( "max_garbage", &view_t::max_garbage );

        cbuffer_view.def_property_readonly( "begin_addr", &view_t::begin_addr );
        cbuffer_view.def_property_readonly( "end_addr", &view_t::end_addr );

        cbuffer_view.def_property_readonly( "begin_addr_slots", &view_t::begin_addr_slots );
        cbuffer_view.def_property_readonly( "begin_addr_objects", &view_t::begin_addr_objects );
        cbuffer_view.def_property_readonly( "begin_addr_pointers", &view_t::begin_addr_pointers );
        cbuffer_view.def_property_readonly( "begin_addr_garbage", &view_t::begin_addr_garbage );

        cbuffer_view.def_property_readonly( "end_addr_slots", &view_t::end_addr_slots );
        cbuffer_view.def_property_readonly( "end_addr_objects", &view_t::end_addr_objects );
        cbuffer_view.def_property_readonly( "end_addr_pointers", &view_t::end_addr_pointers );
        cbuffer_view.def_property_readonly( "end_addr_garbage", &view_t::end_addr_garbage );

        cbuffer_view.def_property_readonly( "base", &view_t::base );
        cbuffer_view.def_property_readonly( "base_address", &view_t::base_address );

        cbuffer_view.def( "p_base", ( view_t::ptr_const_raw_data_t ( view_t::*
            )() const )&view_t::p_base );
        cbuffer_view.def( "p_base_begin", ( view_t::ptr_const_raw_data_t (
            view_t::*)() const )&view_t::p_base_begin );
        cbuffer_view.def( "p_base_end", ( view_t::ptr_const_raw_data_t (
            view_t::*)() const )&view_t::p_base_end );

        cbuffer_view.def( "p_base_begin", ( view_t::ptr_raw_data_t ( view_t::*
            )() )&view_t::p_base_begin );
        cbuffer_view.def( "p_base_end", ( view_t::ptr_raw_data_t ( view_t::*
            )() )&view_t::p_base_end );

        cbuffer_view.def( "p_base", ( view_t::ptr_raw_data_t ( view_t::*
            )() )&view_t::p_base );
        cbuffer_view.def( "p_const_base_begin", &view_t::p_const_base_begin );
        cbuffer_view.def( "p_const_base_end", &view_t::p_const_base_end );
        cbuffer_view.def( "p_const_base", &view_t::p_const_base );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        cbuffer_view.def( "p_slots", ( view_t::ptr_const_raw_data_t (
            view_t::* )() const )&view_t::p_slots );
        cbuffer_view.def( "p_slots",  ( view_t::ptr_raw_data_t ( view_t::* )()
            )&view_t::p_slots );
        cbuffer_view.def( "p_const_slots", &view_t::p_const_slots );

        cbuffer_view.def( "p_slots_end", ( view_t::ptr_const_raw_data_t (
            view_t::* )() const )&view_t::p_slots_end );
        cbuffer_view.def( "p_slots_end",  ( view_t::ptr_raw_data_t ( view_t::* )()
            )&view_t::p_slots_end );
        cbuffer_view.def( "p_const_slots_end", &view_t::p_const_slots_end );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        cbuffer_view.def( "p_objects", ( view_t::ptr_const_raw_data_t (
            view_t::* )() const )&view_t::p_objects );
        cbuffer_view.def( "p_objects",  ( view_t::ptr_raw_data_t ( view_t::* )()
            )&view_t::p_objects );
        cbuffer_view.def( "p_const_objects", &view_t::p_const_objects );

        cbuffer_view.def( "p_objects_end", ( view_t::ptr_const_raw_data_t (
            view_t::* )() const )&view_t::p_objects_end );
        cbuffer_view.def( "p_objects_end",  ( view_t::ptr_raw_data_t (
            view_t::* )() )&view_t::p_objects_end );
        cbuffer_view.def( "p_const_objects_end", &view_t::p_const_objects_end );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        cbuffer_view.def( "p_pointers", ( view_t::ptr_const_raw_data_t (
            view_t::* )() const )&view_t::p_pointers );
        cbuffer_view.def( "p_pointers",  ( view_t::ptr_raw_data_t (
            view_t::* )() )&view_t::p_pointers );
        cbuffer_view.def( "p_const_pointers", &view_t::p_const_pointers );

        cbuffer_view.def( "p_pointers_end", ( view_t::ptr_const_raw_data_t (
            view_t::* )() const )&view_t::p_pointers_end );
        cbuffer_view.def( "p_pointers_end",  ( view_t::ptr_raw_data_t (
            view_t::* )() )&view_t::p_pointers_end );
        cbuffer_view.def( "p_const_pointers_end",
                          &view_t::p_const_pointers_end );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        cbuffer_view.def( "p_garbage", ( view_t::ptr_const_raw_data_t (
            view_t::* )() const )&view_t::p_garbage );
        cbuffer_view.def( "p_garbage",  ( view_t::ptr_raw_data_t ( view_t::* )()
            )&view_t::p_garbage );
        cbuffer_view.def( "p_const_garbage", &view_t::p_const_garbage );

        cbuffer_view.def( "p_garbage_end", ( view_t::ptr_const_raw_data_t (
            view_t::* )() const )&view_t::p_garbage_end );
        cbuffer_view.def( "p_garbage_end",  ( view_t::ptr_raw_data_t (
            view_t::* )() )&view_t::p_garbage_end );
        cbuffer_view.def( "p_const_garbage_end", &view_t::p_const_garbage_end );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        cbuffer_view.def( "objects_begin", ( view_t::ptr_const_index_obj_t (
            view_t::* )() const )&view_t::objects_begin );
        cbuffer_view.def( "objects_begin",  ( view_t::ptr_index_obj_t (
            view_t::* )() )&view_t::objects_begin );
        cbuffer_view.def( "const_objects_begin", &view_t::const_objects_begin );

        cbuffer_view.def( "objects_end", ( view_t::ptr_const_index_obj_t (
            view_t::* )() const )&view_t::objects_end );
        cbuffer_view.def( "objects_end",  ( view_t::ptr_index_obj_t (
            view_t::* )() )&view_t::objects_end );
        cbuffer_view.def( "const_objects_end", &view_t::const_objects_end );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        cbuffer_view.def( "index_at", ( view_t::ptr_const_index_obj_t (
            view_t::* )( view_t::size_type ) const )&view_t::index_at,
            "get object index at position", py::arg( "index" ) );

        cbuffer_view.def( "index_at", ( view_t::ptr_index_obj_t (
            view_t::* )( view_t::size_type ) )&view_t::index_at,
            "get object index at position", py::arg( "index" ) );

        cbuffer_view.def( "const_index_at", ( view_t::ptr_const_index_obj_t (
            view_t::* )( view_t::size_type ) const )&view_t::const_index_at,
            "get object index at position", py::arg( "index" ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        cbuffer_view.def( "address_to_offset", &view_t::address_to_offset );
        cbuffer_view.def( "offset_to_address", &view_t::offset_to_address );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        cbuffer_view.def( "has_capacity_for_allocate",
             &view_t::has_capacity_for_allocate,
             "check if view has enough capacity to allocate for buffer layout",
             py::arg( "max_num_slots" ) = view_t::size_type{ 0 },
             py::arg( "max_num_objects" ) = view_t::size_type{ 0 },
             py::arg( "max_num_pointers" ) = view_t::size_type{ 0 },
             py::arg( "max_num_garbage_ranges" ) = view_t::size_type{ 0 } );


        cbuffer_view.def( "can_allocate", &view_t::can_allocate,
             "check if view can allocate for buffer layout",
             py::arg( "max_num_slots" ) = view_t::size_type{ 0 },
             py::arg( "max_num_objects" ) = view_t::size_type{ 0 },
             py::arg( "max_num_pointers" ) = view_t::size_type{ 0 },
             py::arg( "max_num_garbage_ranges" ) = view_t::size_type{ 0 } );

        cbuffer_view.def( "allocate", &view_t::allocate,
             "attempt to allocate the view with the given layout",
             py::arg( "max_num_slots" ) = view_t::size_type{ 0 },
             py::arg( "max_num_objects" ) = view_t::size_type{ 0 },
             py::arg( "max_num_pointers" ) = view_t::size_type{ 0 },
             py::arg( "max_num_garbage_ranges" ) = view_t::size_type{ 0 } );

        cbuffer_view.def( "reallocate", &view_t::allocate,
             "attempt to re-allocate the view with the given layout",
             py::arg( "max_num_slots" ), py::arg( "max_num_objects" ),
             py::arg( "max_num_pointers" ),
             py::arg( "max_num_garbage_ranges" ) = view_t::size_type{ 0 } );

        /* ----------------------------------------------------------------- */

        cbuffer_view.def_property_readonly( "needs_remapping", &view_t::needs_remapping );
        cbuffer_view.def_property_readonly( "can_remap", &view_t::can_remap );
        cbuffer_view.def( "remap", &view_t::remap );

        /* ================================================================= */

        cbuffer.def( py::init( []( buffer_t::size_type const capacity,
            buffer_t::size_type const slot_size, buffer_t::flags_t const flags )
            { return st::make_unique< buffer_t >(
                    capacity, slot_size, flags ); } ),
            py::arg( "capacity"  ) = view_t::BUFFER_MINIMAL_SIZE,
            py::arg( "slot_size" ) = view_t::DEFAULT_SLOT_SIZE,
            py::arg( "flags" ) = buffer_t::FLAGS_CBUFFER_DEFAULT );

        cbuffer.def( py::init( []( view_t const& view,
                                   buffer_t::flags_t const flags )
            { return st::make_unique< buffer_t >( view, flags ); } ),
            py::arg( "view" ),
            py::arg( "flags" ) = buffer_t::FLAGS_CBUFFER_DEFAULT );

        cbuffer.def( py::init( []( char const* path_to_file,
            buffer_t::size_type const slot_size, buffer_t::flags_t const flags )
            { return st::make_unique< buffer_t >(
                    path_to_file, slot_size, flags );
            } ), py::arg( "path_to_file" ), py::arg( "slot_size" ),
                 py::arg( "flags" ) );

        cbuffer.def( py::init( []( std::string const& path_to_file,
            buffer_t::size_type const slot_size, buffer_t::flags_t const flags )
            { return st::make_unique< buffer_t >( path_to_file, slot_size,
                flags ); } ), py::arg( "path_to_file" ), py::arg( "slot_size" ),
                    py::arg( "flags" ) );

        cbuffer.def( py::init( [](
                        buffer_t::size_type const max_num_slots,
                        buffer_t::size_type const max_num_objects,
                        buffer_t::size_type const max_num_pointers,
                        buffer_t::size_type const max_num_garbage_ranges,
                        buffer_t::size_type const slot_size,
                        buffer_t::flags_t const flags )
            { return st::make_unique< buffer_t >( max_num_slots, max_num_objects,
              max_num_pointers, max_num_garbage_ranges, slot_size, flags ); } ),
              py::arg( "max_num_slots" ),
              py::arg( "max_num_objects" ),
              py::arg( "max_num_pointers" ),
              py::arg( "max_num_garbage_ranges" ),
              py::arg( "slot_size" ) = view_t::DEFAULT_SLOT_SIZE,
              py::arg( "flags" ) = buffer_t::FLAGS_CBUFFER_DEFAULT );

        cbuffer.def( "reserve", ( buffer_t::status_t ( buffer_t::* )(
                        buffer_t::size_type ) )&buffer_t::reserve,
                     "reserve number of bytes of capacity",
                     py::arg( "capacity" ) );

        cbuffer.def( "reserve", ( buffer_t::status_t ( buffer_t::* )(
                        buffer_t::size_type, buffer_t::size_type,
                        buffer_t::size_type, buffer_t::size_type )
                            )&buffer_t::reserve,
                     "reserve capacity for given layout",
                     py::arg( "max_num_slots" ), py::arg( "max_num_objects" ),
                     py::arg( "max_num_pointers" ),
                     py::arg( "max_num_garbage_ranges" ) );


        cbuffer.def( "from_view", &buffer_t::from_view,
                     "load contents of CBufferView into the CBuffer",
                     py::arg( "view" ) );

        cbuffer.def( "from_flat_buffer", &buffer_t::from_flat_buffer,
                     "load contenst from a flat buffer into the CBuffer",
                     py::arg( "flat_buffer_begin" ), py::arg( "slot_size" ) );

        cbuffer.def( "fromfile", ( buffer_t::status_t ( buffer_t::* )(
                        std::string const& ) )&buffer_t::fromfile,
                     "load contents of file into buffer",
                     py::arg( "filename" ) );
        cbuffer.def( "fromfile", ( buffer_t::status_t ( buffer_t::* )(
                        char const* SIXTRL_RESTRICT ) )&buffer_t::fromfile,
                     "load contents of file into buffer",
                     py::arg( "filename" ) );

        cbuffer.def( "tofile", ( buffer_t::status_t ( buffer_t::* )(
                        std::string const& ) const )&buffer_t::tofile,
                     "store contents of buffer into file", py::arg( "filename" ) );
        cbuffer.def( "tofile", ( buffer_t::status_t ( buffer_t::* )(
                        std::string const&, buffer_t::address_t )
                               )&buffer_t::tofile,
                     "store contents of buffer into file and set base address "
                     "to specified value",
                     py::arg( "filename" ), py::arg( "base_addr" ) );

        cbuffer.def( "tofile", ( buffer_t::status_t ( buffer_t::* )(
                        char const* SIXTRL_RESTRICT ) const )&buffer_t::tofile,
                     "store contents of buffer into file", py::arg( "filename" ) );
        cbuffer.def( "tofile", ( buffer_t::status_t ( buffer_t::* )(
                        char const* SIXTRL_RESTRICT, buffer_t::address_t const )
                           )&buffer_t::tofile,
                     "store contents of buffer into file and set base address "
                     "to specified value",
                     py::arg( "filename" ), py::arg( "base_addr" ) );

        cbuffer.def( "set_realloc_factor", ( buffer_t::status_t (buffer_t::*)(
                            buffer_t::size_type ) )&buffer_t::set_realloc_factor,
                     "set the reallocation factor (>1, integer)", py::arg( "factor" ) );
        cbuffer.def( "set_realloc_factor", ( buffer_t::status_t (buffer_t::*)(
                            buffer_t::size_type, buffer_t::size_type ) )&buffer_t::set_realloc_factor,
                     "set the reallocation factor (nominator > denominator)",
                     py::arg( "nomaintor" ), py::arg( "denominator" ) );
    }

} /* namespace: python */
} /* namespace: SIXTRL_CXX_NAMESPACE */








