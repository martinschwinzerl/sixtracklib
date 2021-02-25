#include "python/sixtracklib/_wrapper/common_cobjects.h"

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/cobjects/definitions.h"
#include "sixtracklib/common/cobjects/index_object.h"
#include "sixtracklib/common/cobjects/garbage_range.h"

#include "python/sixtracklib/_wrapper/init_helper.h"

#include <memory>
#include <utility>

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

namespace SIXTRL_CXX_NAMESPACE
{
namespace python
{
    namespace
    {
        namespace py = pybind11;
        namespace st = SIXTRL_CXX_NAMESPACE;
        namespace stpy = SIXTRL_CXX_NAMESPACE::python;
    }

    void InitHelper_common_cobjects( stpy::InitHelper& root )
    {
        stpy::InitHelper_common_cobjects_cobj_index( root );
        stpy::InitHelper_common_cobjects_cobj_garbage_range( root );
        stpy::InitHelper_common_cobjects_cbuffer_view( root );
        stpy::InitHelper_common_cobjects_cbuffer( root );

        root.m.def( "CObjects_default_slot_size",
            [](){ return st::CBufferView::DEFAULT_SLOT_SIZE; } );
    }

    void InitHelper_common_cobjects_cobj_index( stpy::InitHelper& root )
    {
        using c_type = ::NS(CObjIndex);
        auto& obj = root.cobj_index_type;

        obj.def( py::init<>() );
        obj.def_readwrite( "begin_addr", &c_type::begin_addr );
        obj.def_readwrite( "type_id", &c_type::type_id );
        obj.def_readwrite( "size", &c_type::size );
    }

    void InitHelper_common_cobjects_cobj_garbage_range( stpy::InitHelper& root )
    {
        using c_type = ::NS(CObjGarbageRange);
        auto& obj = root.cobj_garbage_range_type;

        obj.def( py::init<>() );
        obj.def_readwrite( "begin_addr", &c_type::begin_addr );
        obj.def_readwrite( "size", &c_type::size );
    }

    void InitHelper_common_cobjects_cbuffer_view( stpy::InitHelper& root )
    {
        using view_t     = st::CBufferView;
        using raw_type   = view_t::raw_type;
        using flags_type = view_t::flags_type;
        using size_type  = view_t::size_type;
        using addr_type  = view_t::addr_type;
        using ext_flat_buffer_type =
            py::array_t< raw_type, py::array::c_style | py::array::forcecast >;

        auto& obj = root.cbuffer_view_type;

        obj.def( py::init(
                []( addr_type const base_addr, size_type const capacity,
                    size_type const slot_size, flags_type const flags ) {
                return std::unique_ptr< view_t >( new view_t(
                    base_addr, capacity, slot_size, flags ) ); } ),
            "default constructor for a CBufferView instance",
            py::arg( "base_addr" ) = view_t::NULL_ADDRESS,
            py::arg( "capacity"  ) = view_t::size_type{ 0 },
            py::arg( "slot_size" ) = view_t::DEFAULT_SLOT_SIZE,
            py::arg( "flags"     ) = view_t::FLAGS_VIEW_DEFAULT );

        obj.def( py::init(
            []( ext_flat_buffer_type& ext_flat_buffer,
                size_type const slot_size, flags_type flags )
            {
                py::buffer_info flat_buffer_info = ext_flat_buffer.request();

                if( view_t::IS_FLAG_SET( flags,
                        st::CBUFFER_FLAGS_OWNS_STORED_DATA ) )
                {
                    throw std::runtime_error(
                        "can only construct a view, not a buffer, using an "
                        "externally provided flat buffer" );
                }

                flags &= ~( st::CBUFFER_FLAGS_OWNS_STORED_DATA |
                            st::CBUFFER_FLAGS_STORAGE_IS_C_PTR |
                            st::CBUFFER_FLAGS_STORAGE_IS_CXX_VECTOR );

                if( slot_size == 0 )
                    throw std::runtime_error( "slot_size == 0" );

                if( flat_buffer_info.ndim != 1 )
                    throw std::runtime_error( "ndim != 1" );

                SIXTRL_ARGPTR_DEC size_type effective_capacity =
                    static_cast< size_type >( flat_buffer_info.shape[ 0 ] );

                addr_type base_addr = static_cast< addr_type >(
                    reinterpret_cast< uintptr_t >( flat_buffer_info.ptr ) );

                if( base_addr % slot_size != addr_type{ 0 } )
                {
                    base_addr = ::NS(CObjFlatBuffer_aligned_base_addr)(
                        base_addr, flat_buffer_info.shape[ 0 ], slot_size,
                            &effective_capacity, slot_size );
                }

                if( effective_capacity < view_t::MIN_BUFFER_SIZE( slot_size ) )
                {
                    throw std::runtime_error(
                        "capacity insufficiant for flat buffer" );
                }

                if( base_addr == st::COBJECTS_NULL_ADDRESS )
                {
                    throw std::runtime_error( "illegal base_addr" );
                }

                if( !::NS(CObjFlatBuffer_has_cbuffer_structure)(
                    reinterpret_cast< SIXTRL_CBUFFER_ARGPTR_DEC raw_type const*
                        >( static_cast< uintptr_t >( base_addr ) ),
                    effective_capacity, slot_size ) )
                {
                    throw std::runtime_error(
                        "flat buffer doesn't have a cbuffer structure" );
                }

                return std::unique_ptr< view_t >( new view_t(
                    base_addr, effective_capacity, slot_size, flags ) ); } ),
            "construct using an external flat buffer (for example provided "
            "by the _data member of a python cobjects CBuffer). Note "
            "that anything other than slot_size == 8 will probably not work "
            "here",
            py::arg( "ext_flat_buffer" ),
            py::arg( "slot_size" ) = view_t::DEFAULT_SLOT_SIZE,
            py::arg( "flags" ) = view_t::FLAGS_VIEW_DEFAULT );


        obj.def_property_readonly_static( "DEFAULT_SLOT_SIZE",
            []( py::object /* */ ) -> size_type {
                return view_t::DEFAULT_SLOT_SIZE; }, "get default slot size" );

        obj.def_static( "MIN_BUFFER_SIZE", &view_t::MIN_BUFFER_SIZE,
            "calculate the minimum admissible buffer size for a given slot size",
            py::arg( "slot_size" ) = view_t::DEFAULT_SLOT_SIZE );

        obj.def_static( "HEADER_SIZE", &view_t::HEADER_SIZE,
            "calculate the buffers header size for a given slot size",
            py::arg( "slot_size" ) = view_t::DEFAULT_SLOT_SIZE );

        obj.def_static( "ADD_FLAG_TO_SET", &view_t::ADD_FLAG_TO_SET,
            "add a CBufferView/CBuffer property flag to a flagset",
            py::arg( "flag_set" ), py::arg( "flag" ) );

        obj.def_static( "REMOVE_FLAG_FROM_SET",
            &view_t::REMOVE_FLAG_FROM_SET,
            "remove a CBufferView/CBuffer property flag from a flag set",
            py::arg( "flag_set" ), py::arg( "flag" ) );

        obj.def_static( "IS_FLAG_SET", &view_t::IS_FLAG_SET,
            "checks if a CBufferView/CBuffer property flag set contains a specific flag",
            py::arg( "flag_set" ), py::arg( "flag" ) );

        obj.def_static( "REQUIRED_BUFFER_LENGTH",
            &view_t::REQUIRED_BUFFER_LENGTH,
            "calculate the required CBufferView/CBuffer capacity for a given "
            "layout, assuming default / standard parameters",
            py::arg( "max_num_slots" ), py::arg( "max_num_objects" ),
            py::arg( "max_num_pointers" ),
            py::arg( "max_num_garbage_ranges" ) = view_t::size_type{ 0 },
            py::arg( "slot_size" ) = view_t::DEFAULT_SLOT_SIZE );

        obj.def_static( "ALIGNED_BASE_ADDR",
             []( view_t::addr_type const raw_base_addr,
                 view_t::size_type const raw_capacity,
                 view_t::size_type const alignment,
                 view_t::size_type const slot_size ) ->
                 std::tuple< view_t::addr_type, view_t::size_type >
             {
                 view_t::size_type result_capacity = view_t::size_type{ 0 };
                 view_t::addr_type const base_addr = view_t::ALIGNED_BASE_ADDR(
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

        obj.def( "as_c_api", ( SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer) const*
            (view_t::*)() const )&view_t::as_c_api );
        obj.def( "as_c_api", ( SIXTRL_CBUFFER_ARGPTR_DEC ::NS(CBuffer)*
            (view_t::*)() )&view_t::as_c_api );
        obj.def( "as_const_c_api", &view_t::as_const_c_api );

        obj.def_property_readonly( "flags", &view_t::flags );
        obj.def_property_readonly( "allow_remap", &view_t::allow_remap );
        obj.def_property_readonly( "allow_allocate", &view_t::allow_allocate );
        obj.def_property_readonly( "allow_append", &view_t::allow_append );
        obj.def_property_readonly( "owns_stored_data", &view_t::owns_stored_data );
        obj.def_property_readonly( "has_special_memory", &view_t::has_special_memory );
        obj.def_property_readonly( "storage_is_c_ptr", &view_t::storage_is_c_ptr );
        obj.def_property_readonly( "storage_is_cxx_vector", &view_t::storage_is_cxx_vector );

        obj.def_property_readonly( "slot_size", &view_t::slot_size );
        obj.def_property_readonly( "size", &view_t::size );
        obj.def_property_readonly( "capacity", &view_t::capacity );
        obj.def_property_readonly( "size_header", &view_t::size_header );
        obj.def( "size_section_header", &view_t::size_section_header );

        obj.def_property_readonly( "size_slots", &view_t::size_slots );
        obj.def_property_readonly( "size_objects", &view_t::size_objects );
        obj.def_property_readonly( "size_pointers", &view_t::size_pointers );
        obj.def_property_readonly( "size_garbage", &view_t::size_garbage );

        obj.def_property_readonly( "n_slots", &view_t::n_slots );
        obj.def_property_readonly( "n_objects", &view_t::n_objects );
        obj.def_property_readonly( "n_pointers", &view_t::n_pointers );
        obj.def_property_readonly( "n_garbage", &view_t::n_garbage );

        obj.def_property_readonly( "num_slots", &view_t::n_slots );
        obj.def_property_readonly( "num_objects", &view_t::n_objects );
        obj.def_property_readonly( "num_pointers", &view_t::n_pointers );
        obj.def_property_readonly( "num_garbage", &view_t::n_garbage );

        obj.def_property_readonly( "max_slots", &view_t::max_slots );
        obj.def_property_readonly( "max_objects", &view_t::max_objects );
        obj.def_property_readonly( "max_pointers", &view_t::max_pointers );
        obj.def_property_readonly( "max_garbage", &view_t::max_garbage );

        obj.def_property_readonly( "begin_addr", &view_t::begin_addr );
        obj.def_property_readonly( "end_addr", &view_t::end_addr );

        obj.def_property_readonly( "begin_addr_slots", &view_t::begin_addr_slots );
        obj.def_property_readonly( "begin_addr_objects", &view_t::begin_addr_objects );
        obj.def_property_readonly( "begin_addr_pointers", &view_t::begin_addr_pointers );
        obj.def_property_readonly( "begin_addr_garbage", &view_t::begin_addr_garbage );

        obj.def_property_readonly( "end_addr_slots", &view_t::end_addr_slots );
        obj.def_property_readonly( "end_addr_objects", &view_t::end_addr_objects );
        obj.def_property_readonly( "end_addr_pointers", &view_t::end_addr_pointers );
        obj.def_property_readonly( "end_addr_garbage", &view_t::end_addr_garbage );

        obj.def_property_readonly( "base", &view_t::base );
        obj.def_property_readonly( "base_address", &view_t::base_address );

        obj.def( "p_base", ( view_t::raw_const_pointer ( view_t::*
            )() const )&view_t::p_base );
        obj.def( "p_base_begin", ( view_t::raw_const_pointer (
            view_t::*)() const )&view_t::p_base_begin );
        obj.def( "p_base_end", ( view_t::raw_const_pointer (
            view_t::*)() const )&view_t::p_base_end );

        obj.def( "p_base_begin", ( view_t::raw_pointer ( view_t::*
            )() )&view_t::p_base_begin );
        obj.def( "p_base_end", ( view_t::raw_pointer ( view_t::*
            )() )&view_t::p_base_end );

        obj.def( "p_base", ( view_t::raw_pointer ( view_t::*
            )() )&view_t::p_base );
        obj.def( "p_const_base_begin", &view_t::p_const_base_begin );
        obj.def( "p_const_base_end", &view_t::p_const_base_end );
        obj.def( "p_const_base", &view_t::p_const_base );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def( "p_slots", ( view_t::raw_const_pointer (
            view_t::* )() const )&view_t::p_slots );
        obj.def( "p_slots",  ( view_t::raw_pointer ( view_t::* )()
            )&view_t::p_slots );
        obj.def( "p_const_slots", &view_t::p_const_slots );

        obj.def( "p_slots_end", ( view_t::raw_const_pointer (
            view_t::* )() const )&view_t::p_slots_end );
        obj.def( "p_slots_end",  ( view_t::raw_pointer ( view_t::* )()
            )&view_t::p_slots_end );
        obj.def( "p_const_slots_end", &view_t::p_const_slots_end );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def( "p_objects", ( view_t::raw_const_pointer (
            view_t::* )() const )&view_t::p_objects );
        obj.def( "p_objects",  ( view_t::raw_pointer ( view_t::* )()
            )&view_t::p_objects );
        obj.def( "p_const_objects", &view_t::p_const_objects );

        obj.def( "p_objects_end", ( view_t::raw_const_pointer (
            view_t::* )() const )&view_t::p_objects_end );
        obj.def( "p_objects_end",  ( view_t::raw_pointer (
            view_t::* )() )&view_t::p_objects_end );
        obj.def( "p_const_objects_end", &view_t::p_const_objects_end );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def( "p_pointers", ( view_t::raw_const_pointer (
            view_t::* )() const )&view_t::p_pointers );
        obj.def( "p_pointers",  ( view_t::raw_pointer (
            view_t::* )() )&view_t::p_pointers );
        obj.def( "p_const_pointers", &view_t::p_const_pointers );

        obj.def( "p_pointers_end", ( view_t::raw_const_pointer (
            view_t::* )() const )&view_t::p_pointers_end );
        obj.def( "p_pointers_end",  ( view_t::raw_pointer (
            view_t::* )() )&view_t::p_pointers_end );
        obj.def( "p_const_pointers_end",
                          &view_t::p_const_pointers_end );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def( "p_garbage", ( view_t::raw_const_pointer (
            view_t::* )() const )&view_t::p_garbage );
        obj.def( "p_garbage",  ( view_t::raw_pointer ( view_t::* )()
            )&view_t::p_garbage );
        obj.def( "p_const_garbage", &view_t::p_const_garbage );

        obj.def( "p_garbage_end", ( view_t::raw_const_pointer (
            view_t::* )() const )&view_t::p_garbage_end );
        obj.def( "p_garbage_end",  ( view_t::raw_pointer (
            view_t::* )() )&view_t::p_garbage_end );
        obj.def( "p_const_garbage_end", &view_t::p_const_garbage_end );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def( "objects_begin", ( view_t::obj_index_const_pointer (
            view_t::* )() const )&view_t::objects_begin );
        obj.def( "objects_begin",  ( view_t::obj_index_pointer (
            view_t::* )() )&view_t::objects_begin );
        obj.def( "const_objects_begin", &view_t::const_objects_begin );

        obj.def( "objects_end", ( view_t::obj_index_const_pointer (
            view_t::* )() const )&view_t::objects_end );
        obj.def( "objects_end",  ( view_t::obj_index_pointer (
            view_t::* )() )&view_t::objects_end );
        obj.def( "const_objects_end", &view_t::const_objects_end );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def( "index_at", ( view_t::obj_index_const_pointer (
            view_t::* )( view_t::size_type ) const )&view_t::index_at,
            "get object index at position", py::arg( "index" ) );

        obj.def( "index_at", ( view_t::obj_index_pointer (
            view_t::* )( view_t::size_type ) )&view_t::index_at,
            "get object index at position", py::arg( "index" ) );

        obj.def( "const_index_at", ( view_t::obj_index_const_pointer (
            view_t::* )( view_t::size_type ) const )&view_t::const_index_at,
            "get object index at position", py::arg( "index" ) );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def( "address_to_offset", &view_t::address_to_offset );
        obj.def( "offset_to_address", &view_t::offset_to_address );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        obj.def( "has_capacity_for_allocate",
             &view_t::has_capacity_for_allocate,
             "check if view has enough capacity to allocate for buffer layout",
             py::arg( "max_num_slots" ), py::arg( "max_num_objects" ),
             py::arg( "max_num_pointers" ),
             py::arg( "max_num_garbage_ranges" ) = view_t::size_type{ 0 } );


        obj.def( "can_allocate", &view_t::can_allocate,
             "check if view can allocate for buffer layout",
             py::arg( "max_num_slots" ),
             py::arg( "max_num_objects" ),
             py::arg( "max_num_pointers" ),
             py::arg( "max_num_garbage_ranges" ) = view_t::size_type{ 0 } );

        obj.def( "allocate", &view_t::allocate,
             "attempt to allocate the view with the given layout",
             py::arg( "max_num_slots" ),
             py::arg( "max_num_objects" ),
             py::arg( "max_num_pointers" ),
             py::arg( "max_num_garbage_ranges" ) = view_t::size_type{ 0 } );

        obj.def( "reallocate", &view_t::reallocate,
             "attempt to re-allocate the view with the given layout",
             py::arg( "max_num_slots" ), py::arg( "max_num_objects" ),
             py::arg( "max_num_pointers" ),
             py::arg( "max_num_garbage_ranges" ) = view_t::size_type{ 0 } );

        /* ----------------------------------------------------------------- */

        obj.def_property_readonly( "needs_remapping", &view_t::needs_remapping );
        obj.def_property_readonly( "can_remap", &view_t::can_remap );
        obj.def( "remap", &view_t::remap );

        /* ----------------------------------------------------------------- */

        obj.def( "const_objects_begin", &view_t::const_objects_begin );
        obj.def( "objects_begin", ( view_t::obj_index_const_pointer (
            view_t::* )() const )&view_t::objects_begin );
        obj.def( "objects_begin", ( view_t::obj_index_pointer (
            view_t::* )() )&view_t::objects_begin );

        obj.def( "const_objects_end", &view_t::const_objects_end );
        obj.def( "objects_end", ( view_t::obj_index_const_pointer (
            view_t::* )() const )&view_t::objects_end );
        obj.def( "objects_end", ( view_t::obj_index_pointer (
            view_t::* )() )&view_t::objects_end );


        obj.def( "const_indices_begin", &view_t::const_indices_begin );
        obj.def( "indices_begin", ( view_t::obj_index_const_pointer (
            view_t::* )() const )&view_t::indices_begin );
        obj.def( "indices_begin", ( view_t::obj_index_pointer (
            view_t::* )() )&view_t::indices_begin );

        obj.def( "const_indices_end", &view_t::const_indices_end );
        obj.def( "indices_end", ( view_t::obj_index_const_pointer (
            view_t::* )() const )&view_t::indices_end );
        obj.def( "indices_end", ( view_t::obj_index_pointer (
            view_t::* )() )&view_t::indices_end );

        obj.def( "const_index_at", &view_t::const_index_at );
        obj.def( "index_at", ( view_t::obj_index_const_pointer (
            view_t::* )( view_t::size_type const ) const )&view_t::index_at );
        obj.def( "index_at", ( view_t::obj_index_pointer (
            view_t::* )( view_t::size_type const ) )&view_t::index_at );

        /* ----------------------------------------------------------------- */

        obj.def_property( "reserve_factor_nominator",
            &view_t::reserve_factor_nominator,
            &view_t::set_reserve_factor_nominator );

        obj.def_property( "reserve_factor_denominator",
            &view_t::reserve_factor_denominator,
            &view_t::set_reserve_factor_denominator );

        obj.def( "set_reserve_factor", &view_t::set_reserve_factor );
        obj.def( "reserve_scale_capacity", &view_t::reserve_scale_capacity );
        obj.def( "reserve", &view_t::reserve );
        obj.def( "reserve_detailed", &view_t::reserve_detailed );

        /* ----------------------------------------------------------------- */

        obj.def( "obj_typeid", &view_t::obj_typeid );
        obj.def( "obj_size", &view_t::obj_size );
        obj.def( "obj_num_slots", &view_t::obj_num_slots );
        obj.def( "obj_address", &view_t::obj_address );

        /* ----------------------------------------------------------------- */

        obj.def( "can_add_copy_of_object", []( view_t& self,
                 view_t::size_type const obj_handle_size,
                 view_t::size_type const num_dataptrs,
                 py::array_t< view_t::size_type > sizes,
                 py::array_t< view_t::size_type > counts ) ->
                 std::tuple< bool, view_t::size_type >
             {
                 py::buffer_info sizes_info = sizes.request();
                 py::buffer_info counts_info = counts.request();

                 if( ( sizes_info.ndim != 1 ) || ( counts_info.ndim != 1 ) )
                 {
                     throw std::runtime_error(
                        "sizes/counts: ndim has to be 1!" );
                }

                if( sizes_info.size != counts_info.size )
                {
                    throw std::runtime_error(
                        "sizes/counts have to have the same shape and stride" );
                }

                if( ( sizes_info.size < num_dataptrs ) ||
                    ( counts_info.size < num_dataptrs ) )
                {
                    throw std::runtime_error(
                        "sizes/counts have to have enough entries for the shape" );
                }

                 SIXTRL_ARGPTR_DEC view_t::size_type requ_buffer_size =
                    view_t::size_type{ 0 };

                 bool const can_be_added = self.can_add_copy_of_object(
                    obj_handle_size, num_dataptrs,
                    static_cast< view_t::size_type const* >( sizes_info.ptr ),
                    static_cast< view_t::size_type const* >( counts_info.ptr ),
                    &requ_buffer_size, nullptr, nullptr, nullptr );

                 return std::make_tuple( can_be_added, requ_buffer_size );
            },
            "checks whether an object with the provided properties can be added",
            py::arg( "obj_handle_size" ), py::arg( "num_dataptrs" ),
            py::arg( "sizes" ), py::arg( "counts" ) );

        obj.def( "can_add_copy_of_object", []( view_t& self,
                 view_t::size_type const obj_handle_size ) ->
                 std::tuple< bool, view_t::size_type >
             {
                 SIXTRL_ARGPTR_DEC view_t::size_type requ_buffer_size =
                    view_t::size_type{ 0 };

                 bool const can_be_added = self.can_add_copy_of_trivial_object(
                    obj_handle_size, &requ_buffer_size, nullptr, nullptr,
                        nullptr );

                 return std::make_tuple( can_be_added, requ_buffer_size );
            },
            "checks whether a trivial object (i.e. one without any pointer "
            "members) can be added", py::arg( "obj_handle_size" ) );

        obj.def( "fromfile",
            []( view_t& self, std::string const& path_to_file ) ->
            view_t::status_type
            {
                return st::CBuffer_from_file( self, path_to_file );
            },
            "attempts to initializes the cbuffer/view with the contents of a file",
            py::arg( "path_to_file" ) );

        obj.def( "tofile",
            []( view_t& self, std::string const& path_to_file ) ->
            view_t::status_type
            {
                return st::CBuffer_to_file( self, path_to_file );
            },
            "attempts to dump the contents of the cbuffer/view to a file",
            py::arg( "path_to_file" ) );

        obj.def( "tofile",
            []( view_t& self, std::string const& path_to_file,
                view_t::addr_type const normalised_addr ) ->
            view_t::status_type
            {
                return st::CBuffer_to_file_normalised(
                    self, path_to_file, normalised_addr );
            },
            "attempts to dump the contents of the cbuffer/view to a file",
            py::arg( "path_to_file" ), py::arg( "normalised_addr" ) );

        obj.def( "tofile_normalised",
            []( view_t& self, std::string const& path_to_file,
                view_t::addr_type const normalised_addr ) ->
            view_t::status_type
            {
                return st::CBuffer_to_file_normalised(
                    self, path_to_file, normalised_addr );
            },
            "attempts to dump the contents of the cbuffer/view to a file",
            py::arg( "path_to_file" ), py::arg( "normalised_addr" ) );
    }

    void InitHelper_common_cobjects_cbuffer( stpy::InitHelper& root )
    {
        using buffer_t = st::CBuffer;
        using view_t = st::CBufferView;
        auto& obj = root.cbuffer_type;

        obj.def( py::init( [](
            buffer_t::size_type capacity,
            buffer_t::size_type const slot_size )
        {
            if( capacity < buffer_t::MIN_BUFFER_SIZE( slot_size ) )
            {
                capacity = buffer_t::MIN_BUFFER_SIZE( slot_size );
            }

            return std::unique_ptr< buffer_t >(
                new buffer_t( capacity, slot_size ) ); } ),
            py::arg( "capacity"  ) = buffer_t::DEFAULT_MINIMAL_SIZE,
            py::arg( "slot_size" ) = buffer_t::DEFAULT_SLOT_SIZE );

        obj.def( py::init( []( view_t const& view )
            { return std::unique_ptr< buffer_t >( new st::CBuffer( view ) ); } ),
            py::arg( "view" ) );

        obj.def( py::init( []( std::string const& path_to_file,
            buffer_t::size_type const slot_size )
            { return std::unique_ptr< buffer_t >( new buffer_t(
                    path_to_file, slot_size ) ); } ),
                py::arg( "path_to_file" ),
                py::arg( "slot_size" ) = view_t::DEFAULT_SLOT_SIZE );

        obj.def( py::init( [](
            buffer_t::size_type const max_num_slots,
            buffer_t::size_type const max_num_objects,
            buffer_t::size_type const max_num_pointers,
            buffer_t::size_type const max_num_garbage_ranges,
            buffer_t::size_type const slot_size,
            buffer_t::flags_type const flags )
            { return std::unique_ptr< buffer_t >( new buffer_t(
                max_num_slots, max_num_objects, max_num_pointers,
                    max_num_garbage_ranges, slot_size, flags ) ); } ),
              py::arg( "max_num_slots" ),
              py::arg( "max_num_objects" ),
              py::arg( "max_num_pointers" ),
              py::arg( "max_num_garbage_ranges" ) = buffer_t::size_type{ 0 },
              py::arg( "slot_size" ) = view_t::DEFAULT_SLOT_SIZE,
              py::arg( "flags" ) = buffer_t::FLAGS_BUFFER_DEFAULT );
    }


} /* end: namespace python */
} /* end: namespace SIXTRL_CXX_NAMESPACE */

