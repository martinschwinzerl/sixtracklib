#include "python/sixtracklib/_wrapper/testlib.h"
#include "python/sixtracklib/_wrapper/tl/optional.hpp"
#include "python/sixtracklib/_wrapper/cxx11_optional.h"
#include "python/sixtracklib/_wrapper/buffer_protocol.h"
#include "python/sixtracklib/_wrapper/init_helper.h"

#include "sixtracklib/common/cobjects/cbuffer_view.hpp"
#include "sixtracklib/common/cobjects/cbuffer.hpp"


#if defined( SIXTRL_TESTLIB_ENABLED ) && ( SIXTRL_TESTLIB_ENABLED == 1 )
    #include "sixtracklib/testlib.h"
#endif /* defined( SIXTRL_TESTLIB_ENABLED ) */

#include <limits>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE {
namespace python {

namespace
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    namespace stpy = SIXTRL_CXX_NAMESPACE::python;
    namespace py = pybind11;
}

void InitHelper_testlib( stpy::InitHelper& root )
{
    stpy::InitHelper_testlib_cobj_test_no_ptrs( root );
    stpy::InitHelper_testlib_cobj_test_dataptrs( root );

    py::module& m = root.m;

    #if defined( SIXTRL_TESTLIB_ENABLED ) && ( SIXTRL_TESTLIB_ENABLED == 1 )
    m.def( "Testlib_enabled", []() { return true; } );
    #else  /*  defined( SIXTRL_TESTLIB_ENABLED ) */
    m.def( "Testlib_enabled", []() { return false; } );
    #endif /* !defined( SIXTRL_TESTLIB_ENABLED ) */
}

void InitHelper_testlib_cobj_test_no_ptrs( stpy::InitHelper& root )
{
    #if defined( SIXTRL_TESTLIB_ENABLED ) && ( SIXTRL_TESTLIB_ENABLED == 1 )

    using elem_type = ::NS(CObjTestNoPtrs);
    using real_type = ::NS(cobj_test_real_type);
    using uint_type = ::NS(cobj_test_uint64_type);
    using int_type  = ::NS(cobj_test_int64_type);
    using cbuffer_view_type = st::CBufferView;

    using real_adapter_type  = stpy::RealBufferAdapter;
    using py_array_real_t = py::array_t<
            real_type, py::array::c_style | py::array::forcecast >;

    auto& obj = root.cobj_test_no_ptrs_type;

    obj.def( py::init( []( cbuffer_view_type& cbuffer, real_type const a_value,
        uint_type const b_value, int_type const d_value ) {

        return std::unique_ptr< elem_type, py::nodelete >(
            ::NS(CObjTestNoPtrs_cbuffer_add)( cbuffer.as_c_api(), a_value,
                b_value, nullptr, d_value ) ); } ),
    "construct a default-valued instance on a cbuffer/cbufferview",
    py::arg( "cbuffer" ),
    py::arg( "a_value" ) = ::NS(CObjTestNoPtrs_default_a)(),
    py::arg( "b_value" ) = ::NS(CObjTestNoPtrs_default_b)(),
    py::arg( "d_value" ) = ::NS(CObjTestNoPtrs_default_b)() );

    obj.def( py::init( []( cbuffer_view_type& cbuffer,
        real_type const a_value, uint_type const b_value,
        tl::optional< py_array_real_t > c_values, int_type const d_value )
    {
        using in_c_values_ptr = SIXTRL_TESTLIB_ARGPTR_DEC real_type const*;
        std::unique_ptr< std::vector< real_type > > dummy_c_values( nullptr );
        uint_type c_length = uint_type{ 0 };
        uint_type const c_capacity = uint_type{ 6 };
        in_c_values_ptr c_values_ptr = stpy::PyArray_stable_base_pointer_1d<
            real_type, uint_type, in_c_values_ptr >( c_values, c_capacity,
                c_length, dummy_c_values, ::NS(CObjTestNoPtrs_default_c)() );

        return std::unique_ptr< elem_type, py::nodelete >(
            ::NS(CObjTestNoPtrs_cbuffer_add)( cbuffer.as_c_api(), a_value,
                b_value, c_values_ptr, d_value ) ); } ),
    "constructor a new instance on a CBufferView/CBuffer",
    py::arg( "cbuffer" ),
    py::arg( "a_value" ), py::arg( "b_value" ),
    py::arg( "c_values" ), py::arg( "d_value" ) );

    /* ----------------------------------------------------------------- */

    obj.def_static( "GET",
        []( cbuffer_view_type& view, size_type const pos_in_buffer )
            -> SIXTRL_TESTLIB_ARGPTR_DEC ::NS(CObjTestNoPtrs)* {
            return ::NS(CObjTestNoPtrs_from_cbuffer)(
                view.as_c_api(), pos_in_buffer ); },
        py::return_value_policy::reference,
        "get instance of CObjTestNoPtrs from a CBufferView at pos_in_buffer",
        py::arg( "cbuffer" ), py::arg( "pos_in_buffer" ) );

    obj.def_static( "CREATE_NEW",
        []( cbuffer_view_type& view )
            -> SIXTRL_TESTLIB_ARGPTR_DEC ::NS(CObjTestNoPtrs)*
        { return ::NS(CObjTestNoPtrs_cbuffer_new)( view.as_c_api() ); },
        py::return_value_policy::reference,
        "append a new CObjTestNoPtrs instance to a CBufferView/CBuffer",
        py::arg( "cbuffer" ) );

    obj.def_static( "ADD", []( cbuffer_view_type& view,
        real_type const a_value, uint_type const b_value,
        tl::optional< py_array_real_t > c_values, int_type const d_value )
            -> SIXTRL_TESTLIB_ARGPTR_DEC ::NS(CObjTestNoPtrs)*
        {
            using in_c_values_ptr = SIXTRL_TESTLIB_ARGPTR_DEC real_type const*;
            std::unique_ptr< std::vector< real_type > > dummy_c_values( nullptr );
            uint_type c_length = uint_type{ 0 };
            uint_type const c_capacity = uint_type{ 6 };
            in_c_values_ptr c_values_ptr = stpy::PyArray_stable_base_pointer_1d<
                real_type, uint_type, in_c_values_ptr >( c_values, c_capacity,
                c_length, dummy_c_values, ::NS(CObjTestNoPtrs_default_c)() );

            return ::NS(CObjTestNoPtrs_cbuffer_add)( view.as_c_api(), a_value,
                b_value, c_values_ptr, d_value ); },
        py::return_value_policy::reference,
        "append a fully parameterised CObjTestNoPtrs instance to a "
        "CBufferView/CBuffer",
        py::arg( "cbuffer" ), py::arg( "a_value" ), py::arg( "b_value" ),
        py::arg( "c_values" ), py::arg( "d_value" ) );

    obj.def_static( "ADD_COPY",
        []( cbuffer_view_type& view, elem_type const& elem )
            -> SIXTRL_TESTLIB_ARGPTR_DEC ::NS(CObjTestNoPtrs)*
        {
            return ::NS(CObjTestNoPtrs_cbuffer_add_copy)(
                view.as_c_api(), &elem );
        },
        py::return_value_policy::reference,
        "append a copy of the CObjTestNoPtrs instance provided to the "
        "CBufferView/CBuffer instance",
        py::arg( "cbuffer" ), py::arg( "original" ) );

    obj.def( "copy_to_cbuffer",
        []( elem_type const& elem, cbuffer_view_type& view )
            -> SIXTRL_TESTLIB_ARGPTR_DEC ::NS(CObjTestNoPtrs)*
        {
            return ::NS(CObjTestNoPtrs_cbuffer_add_copy)(
                view.as_c_api(), &elem );
        },
        py::return_value_policy::reference,
        "append a copy of the calling CObjTestNoPtrs instance to a "
        "CBufferView/CBuffer instance",
        py::arg( "cbuffer" ) );

    /* ---------------------------------------------------------------------- */

    obj.def_property( "a",
        []( elem_type const& elem ) { return ::NS(CObjTestNoPtrs_a)( &elem ); },
        []( elem_type& elem, real_type const a ) {
            return ::NS(CObjTestNoPtrs_set_a)( &elem, a ); } );

    obj.def_property( "b",
        []( elem_type const& elem ) { return ::NS(CObjTestNoPtrs_a)( &elem ); },
        []( elem_type& elem, uint_type const b ) {
            return ::NS(CObjTestNoPtrs_set_b)( &elem, b ); } );

    obj.def_property_readonly( "c_length", []( elem_type const& elem ) {
        return ::NS(CObjTestNoPtrs_c_length)( &elem ); } );

    obj.def( "c", []( elem_type const& elem ) -> real_adapter_type {
        return real_adapter_type(
            reinterpret_cast< uintptr_t >(
                ::NS(CObjTestNoPtrs_c_const_begin)( &elem ) ),
            ::NS(CObjTestNoPtrs_c_length)( &elem ) ); } );

    obj.def( "c", []( elem_type const& elem, size_type const idx ) -> real_type
        { return ::NS(CObjTestNoPtrs_c)( &elem, idx ); } );

    obj.def( "set_c", []( elem_type& elem, size_type const idx,
        real_type const c_value ) {
        return ::NS(CObjTestNoPtrs_set_c)( &elem, idx, c_value ); } );

    obj.def_property( "d",
        []( elem_type const& elem ) { return ::NS(CObjTestNoPtrs_a)( &elem ); },
        []( elem_type& elem, int_type const d ) {
            return ::NS(CObjTestNoPtrs_set_b)( &elem, d ); } );

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    obj.def( "clear", []( elem_type& self ) {
        return ::NS(CObjTestNoPtrs_clear)( &self ); } );

    obj.def( "init", []( elem_type& self, real_type const a_value,
        uint_type const b_value, tl::optional< py_array_real_t > c_values,
        int_type const d_value ) {
            using in_c_values_ptr = SIXTRL_TESTLIB_ARGPTR_DEC real_type const*;
            std::unique_ptr< std::vector< real_type > > dummy_c_values( nullptr );
            uint_type c_length = uint_type{ 0 };
            uint_type const c_capacity = uint_type{ 6 };
            in_c_values_ptr c_values_ptr = stpy::PyArray_stable_base_pointer_1d<
                real_type, uint_type, in_c_values_ptr >( c_values, c_capacity,
                    c_length, dummy_c_values );

            return ::NS(CObjTestNoPtrs_init)( &self,
                a_value, b_value, c_values_ptr, d_value ); },
        py::arg( "a_value" ), py::arg( "b_value" ), py::arg( "c_values" ),
        py::arg( "d_value" ) );

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    obj.def( "compare", []( elem_type const& self, elem_type const& rhs ) -> int {
        return ::NS(CObjTestNoPtrs_compare)( &self, &rhs ); } );

    obj.def_static( "COMPARE",
        []( elem_type const& self, elem_type const& rhs ) -> int {
        return ::NS(CObjTestNoPtrs_compare)( &self, &rhs ); } );

    /* ---------------------------------------------------------------------- */

    obj.def_property_readonly_static( "COBJ_TYPE_ID",
        []( py::object /* */ ) { return ::NS(CObjTestNoPtrs_cobj_type_id)(); } );

    obj.def_property_readonly_static( "COBJ_NUM_DATAPTRS",
        []( py::object /* */ ) { return ::NS(CObjTestNoPtrs_cobj_num_dataptrs)();
    } );

    obj.def_static( "COBJ_ACTUAL_HANDLE_SIZE",
        []( size_type const slot_size ) {
        return ::NS(CObjTestNoPtrs_cobj_actual_handle_size)( slot_size ); },
        "Calculate the actual handle size of the type in bytes "
        "for a given slot size",
        py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

    obj.def_static( "COBJ_RESERVED_HANDLE_SIZE",
        []( size_type const slot_size ) {
        return ::NS(CObjTestNoPtrs_cobj_reserved_handle_size)( slot_size ); },
        "Calculate the reserved handle size of the type in bytes "
        "for a given slot size. For most types, this should be identical "
        "to the actual handle size",
        py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

        obj.def_static( "COBJ_REQUIRED_NUM_SLOTS",
            []( size_type const slot_size ) {
                if( slot_size == size_type{ 0 } )
                    throw std::runtime_error( "slot_size == 0" );
                return ::NS(CObjTestNoPtrs_cobj_reserved_handle_size)(
                    slot_size ) / slot_size; },
                py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

    obj.def( "cobj_required_num_bytes",
        []( elem_type const& self, size_type const slot_size ) {
            return ::NS(CObjTestNoPtrs_cobj_required_num_bytes)(
                &self, slot_size ); },
        "Calculate the required total number of bytes to store the calling "
        "instance in a CBufferView/CBuffer for a given slot_size",
        py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

    #else /* defined( SIXTRL_TESTLIB_ENABLED ) */
    ( void )root;
    #endif /* defined( SIXTRL_TESTLIB_ENABLED ) */
}

void InitHelper_testlib_cobj_test_dataptrs( stpy::InitHelper& root )
{
    #if defined( SIXTRL_TESTLIB_ENABLED ) && ( SIXTRL_TESTLIB_ENABLED == 1 )

    using elem_type = ::NS(CObjTestDataptrs);
    using real_type = ::NS(cobj_test_real_type);
    using uint_type = ::NS(cobj_test_uint64_type);
    using addr_type = ::NS(address_type);
    using cbuffer_view_type = st::CBufferView;

    using real_adapter_type  = stpy::RealBufferAdapter;
    using py_array_real_t = py::array_t<
            real_type, py::array::c_style | py::array::forcecast >;

    auto& obj = root.cobj_test_dataptrs_type;

    obj.def( py::init( []( cbuffer_view_type& cbuffer,
        uint_type const b_capacity, uint_type const c_capacity,
        real_type const a_value ) {
        return std::unique_ptr< elem_type, py::nodelete >(
            ::NS(CObjTestDataptrs_cbuffer_add)( cbuffer.as_c_api(), a_value,
                b_capacity, b_capacity, addr_type{ 0 },
                    c_capacity, b_capacity, addr_type{ 0 } ) ); } ),
    "construct a default-valued instance on a cbuffer/cbufferview",
    py::arg( "cbuffer" ),
    py::arg( "b_capacity" ),
    py::arg( "c_capacity" ),
    py::arg( "a_value" ) = ::NS(CObjTestDataptrs_default_a)() );

    obj.def( py::init( []( cbuffer_view_type& cbuffer,
        real_type const a_value,
        tl::optional< py_array_real_t > b_values,
        tl::optional< py_array_real_t > c_values,
        uint_type const b_capacity, uint_type c_capacity )
    {
        uint_type const nn_b = std::max(
            static_cast< size_type >( b_capacity ),
            stpy::PyArray_length_1d< real_type >( b_values ) );

        uint_type b_length = uint_type{ 0 };
        std::unique_ptr< std::vector< real_type > > dummy_b_values( nullptr );
        addr_type const b_addr = stpy::PyArray_stable_base_addr_1d< real_type,
            uint_type >( b_values, nn_b, b_length, dummy_b_values,
                ::NS(CObjTestDataptrs_default_b)() );

        uint_type const nn_c = std::max(
            static_cast< size_type >( c_capacity ),
            stpy::PyArray_length_1d< real_type >( c_values ) );

        uint_type c_length = uint_type{ 0 };
        std::unique_ptr< std::vector< real_type > > dummy_c_values( nullptr );
        addr_type const c_addr = stpy::PyArray_stable_base_addr_1d< real_type,
            uint_type >( c_values, nn_c, c_length, dummy_c_values,
                ::NS(CObjTestDataptrs_default_c)() );

        return std::unique_ptr< elem_type, py::nodelete >(
            ::NS(CObjTestDataptrs_cbuffer_add)( cbuffer.as_c_api(), a_value,
            nn_b, b_length, b_addr, nn_c, c_length, c_addr ) ); } ),
    "construct a fully parameterised instance on a cbuffer/cbuffer",
    py::arg( "cbuffer" ),
    py::arg( "a_value" ),
    py::arg( "b_values" ), py::arg( "c_values" ),
    py::arg( "b_capacity" ) = uint_type{ 0 },
    py::arg( "c_capacity" ) = uint_type{ 0 } );

    /* ----------------------------------------------------------------- */

    obj.def_static( "GET",
        []( cbuffer_view_type& view, size_type const pos_in_buffer )
            -> SIXTRL_TESTLIB_ARGPTR_DEC ::NS(CObjTestDataptrs)* {
            return ::NS(CObjTestDataptrs_from_cbuffer)(
                view.as_c_api(), pos_in_buffer ); },
        py::return_value_policy::reference,
        "get instance of CObjTestDataptrs from a CBufferView at pos_in_buffer",
        py::arg( "cbuffer" ), py::arg( "pos_in_buffer" ) );

    obj.def_static( "CREATE_NEW",
        []( cbuffer_view_type& view,
            uint_type const b_capacity, uint_type const c_capacity )
            -> SIXTRL_TESTLIB_ARGPTR_DEC ::NS(CObjTestDataptrs)*
        { return ::NS(CObjTestDataptrs_cbuffer_new)( view.as_c_api(),
            b_capacity, c_capacity ); },
        py::return_value_policy::reference,
        "append a new CObjTestDataptrs instance to a CBufferView/CBuffer",
        py::arg( "cbuffer" ), py::arg( "b_capacity" ), py::arg( "c_capacity" ) );

    obj.def_static( "ADD", []( cbuffer_view_type& cbuffer, real_type a_value,
        tl::optional< py_array_real_t > b_values,
        tl::optional< py_array_real_t > c_values,
        uint_type b_capacity, uint_type c_capacity  )
            -> SIXTRL_TESTLIB_ARGPTR_DEC ::NS(CObjTestDataptrs)*
        {
            uint_type const nn_b = std::max(
                static_cast< size_type >( b_capacity ),
                stpy::PyArray_length_1d< real_type >( b_values ) );

            uint_type b_length = uint_type{ 0 };
            std::unique_ptr< std::vector< real_type > > dummy_b_values( nullptr );
            addr_type const b_addr = stpy::PyArray_stable_base_addr_1d< real_type,
                uint_type >( b_values, nn_b, b_length, dummy_b_values,
                    ::NS(CObjTestDataptrs_default_b)() );

            uint_type const nn_c = std::max(
                static_cast< size_type >( c_capacity ),
                stpy::PyArray_length_1d< real_type >( c_values ) );

            uint_type c_length = uint_type{ 0 };
            std::unique_ptr< std::vector< real_type > > dummy_c_values( nullptr );
            addr_type const c_addr = stpy::PyArray_stable_base_addr_1d<
                real_type, uint_type >( c_values, nn_c, c_length, dummy_c_values,
                    ::NS(CObjTestDataptrs_default_c)() );

            return ::NS(CObjTestDataptrs_cbuffer_add)( cbuffer.as_c_api(),
                a_value, nn_b, b_length, b_addr, nn_c, c_length, c_addr ); },
        py::return_value_policy::reference,
        "append a fully parameterised CObjTestDataptrs instance to a "
        "CBufferView/CBuffer",
        py::arg( "cbuffer" ),  py::arg( "a_value" ),
        py::arg( "b_values" ), py::arg( "c_values" ),
        py::arg( "b_capacity" ) = uint_type{ 0 },
        py::arg( "c_capacity" ) = uint_type{ 0 } );

    obj.def_static( "ADD_COPY",
        []( cbuffer_view_type& view, elem_type const& elem )
            -> SIXTRL_TESTLIB_ARGPTR_DEC ::NS(CObjTestDataptrs)*
        {
            return ::NS(CObjTestDataptrs_cbuffer_add_copy)(
                view.as_c_api(), &elem );
        },
        py::return_value_policy::reference,
        "append a copy of the CObjTestDataptrs instance provided to the "
        "CBufferView/CBuffer instance",
        py::arg( "cbuffer" ), py::arg( "original" ) );

    obj.def( "copy_to_cbuffer",
        []( elem_type const& elem, cbuffer_view_type& view )
            -> SIXTRL_TESTLIB_ARGPTR_DEC ::NS(CObjTestDataptrs)*
        {
            return ::NS(CObjTestDataptrs_cbuffer_add_copy)(
                view.as_c_api(), &elem );
        },
        py::return_value_policy::reference,
        "append a copy of the calling CObjTestDataptrs instance to a "
        "CBufferView/CBuffer instance",
        py::arg( "cbuffer" ) );

    /* ---------------------------------------------------------------------- */

    obj.def_property( "a",
        []( elem_type const& elem ) { return ::NS(CObjTestDataptrs_a)( &elem ); },
        []( elem_type& elem, real_type const a ) {
            return ::NS(CObjTestDataptrs_set_a)( &elem, a ); } );

    obj.def_property_readonly( "b_capacity", []( elem_type const& elem ) {
        return ::NS(CObjTestDataptrs_b_capacity)( &elem ); } );

    obj.def_property( "b_length",
        []( elem_type const& elem ) {
            return ::NS(CObjTestDataptrs_b_length)( &elem ); },
        []( elem_type& elem, uint_type const b_length ) {
            if( b_length > ::NS(CObjTestDataptrs_b_capacity)( &elem ) )
                throw std::runtime_error( "b_length exceeds b_capacity" );
            return ::NS(CObjTestDataptrs_set_b_length)( &elem, b_length ); } );

    obj.def( "b", []( elem_type const& elem ) -> real_adapter_type {
        return real_adapter_type(
            ::NS(CObjTestDataptrs_b_addr)( &elem ),
            ::NS(CObjTestDataptrs_b_length)( &elem ) ); } );

    obj.def( "b", []( elem_type const& elem, size_type const idx ) -> real_type
        { return ::NS(CObjTestDataptrs_c)( &elem, idx ); } );

    obj.def( "set_b", []( elem_type& elem, size_type const idx,
        real_type const b_value ) {
        return ::NS(CObjTestDataptrs_set_b)( &elem, idx, b_value ); } );



    obj.def_property_readonly( "c_capacity", []( elem_type const& elem ) {
        return ::NS(CObjTestDataptrs_c_capacity)( &elem ); } );

    obj.def_property( "c_length",
        []( elem_type const& elem ) {
            return ::NS(CObjTestDataptrs_c_length)( &elem ); },
        []( elem_type& elem, uint_type const c_length ) {
            if( c_length > ::NS(CObjTestDataptrs_c_capacity)( &elem ) )
                throw std::runtime_error( "c_length exceeds c_capacity" );
            return ::NS(CObjTestDataptrs_set_c_length)( &elem, c_length ); } );

    obj.def( "c", []( elem_type const& elem ) -> real_adapter_type {
        return real_adapter_type(
            ::NS(CObjTestDataptrs_c_addr)( &elem ),
            ::NS(CObjTestDataptrs_c_length)( &elem ) ); } );

    obj.def( "c", []( elem_type const& elem, size_type const idx ) -> real_type
        { return ::NS(CObjTestDataptrs_c)( &elem, idx ); } );

    obj.def( "set_c", []( elem_type& elem, size_type const idx,
        real_type const c_value ) {
        return ::NS(CObjTestDataptrs_set_c)( &elem, idx, c_value ); } );

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    obj.def( "clear", []( elem_type& self ) {
        return ::NS(CObjTestDataptrs_clear)( &self ); } );

    obj.def( "init", []( elem_type& self, real_type const a_value,
        tl::optional< py_array_real_t > b_values,
        tl::optional< py_array_real_t > c_values )
        {
            using in_data_pointer = SIXTRL_TESTLIB_ARGPTR_DEC real_type const*;

            uint_type b_capacity = ::NS(CObjTestDataptrs_b_capacity)( &self );
            uint_type b_length = stpy::PyArray_length_1d< real_type >( b_values );
            addr_type b_addr = st::COBJECTS_NULL_ADDRESS;

            if( b_length >= b_capacity )
            {
                if( b_length > b_capacity ) b_capacity = b_length;
                b_addr = stpy::PyArray_base_addr_1d< real_type >(
                    b_values, b_addr );
            }
            else
            {
                throw std::runtime_error( "b_values exceed b_capacity limit" );
            }

            uint_type c_capacity = ::NS(CObjTestDataptrs_c_capacity)( &self );
            uint_type c_length = stpy::PyArray_length_1d< real_type >( c_values );
            addr_type c_addr = st::COBJECTS_NULL_ADDRESS;

            if( c_length >= c_capacity )
            {
                if( c_length > c_capacity ) c_capacity = c_length;
                c_addr = stpy::PyArray_base_addr_1d< real_type >(
                    c_values, c_addr );
            }
            else
            {
                throw std::runtime_error( "c_values exceed c_capacity limit" );
            }

            ::NS(CObjTestDataptrs_init)( &self, a_value, b_capacity,
                b_length, b_addr, c_capacity, c_length, c_addr );
        }, py::arg( "a_value" ), py::arg( "b_values" ), py::arg( "c_values" ) );

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

    obj.def( "compare", []( elem_type const& self, elem_type const& rhs ) -> int {
        return ::NS(CObjTestDataptrs_compare)( &self, &rhs ); } );

    obj.def_static( "COMPARE",
        []( elem_type const& self, elem_type const& rhs ) -> int {
        return ::NS(CObjTestDataptrs_compare)( &self, &rhs ); } );

    /* ---------------------------------------------------------------------- */

    obj.def_property_readonly_static( "COBJ_TYPE_ID",
        []( py::object /* */ ) { return ::NS(CObjTestDataptrs_cobj_type_id)(); } );

    obj.def_property_readonly_static( "COBJ_NUM_DATAPTRS",
        []( py::object /* */ ) { return ::NS(CObjTestDataptrs_cobj_num_dataptrs)();
    } );

    obj.def_static( "COBJ_ACTUAL_HANDLE_SIZE",
        []( size_type const slot_size ) {
        return ::NS(CObjTestDataptrs_cobj_actual_handle_size)( slot_size ); },
        "Calculate the actual handle size of the type in bytes "
        "for a given slot size",
        py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

    obj.def_static( "COBJ_RESERVED_HANDLE_SIZE",
        []( size_type const slot_size ) {
        return ::NS(CObjTestDataptrs_cobj_reserved_handle_size)( slot_size ); },
        "Calculate the reserved handle size of the type in bytes "
        "for a given slot size. For most types, this should be identical "
        "to the actual handle size",
        py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

    obj.def_static( "COBJ_REQUIRED_NUM_SLOTS",
        []( uint_type b_capacity, uint_type c_capacity,
            size_type const slot_size ) {
            if( slot_size == size_type{ 0 } )
                throw std::runtime_error( "slot_size == 0" );

            elem_type elem;
            ::NS(CObjTestDataptrs_clear)( &elem );
            ::NS(CObjTestDataptrs_set_b_capacity)( &elem, b_capacity );
            ::NS(CObjTestDataptrs_set_b_length)( &elem, b_capacity );
            ::NS(CObjTestDataptrs_set_c_capacity)( &elem, c_capacity );
            ::NS(CObjTestDataptrs_set_c_length)( &elem, c_capacity );
            return ::NS(CObjTestDataptrs_cobj_required_num_bytes)(
                &elem, slot_size ) / slot_size; },
            py::arg( "b_capacity" ), py::arg( "c_capacity" ),
            py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

    obj.def( "cobj_required_num_bytes",
        []( elem_type const& self, size_type const slot_size ) {
            return ::NS(CObjTestDataptrs_cobj_required_num_bytes)(
                &self, slot_size ); },
        "Calculate the required total number of bytes to store the calling "
        "instance in a CBufferView/CBuffer for a given slot_size",
        py::arg( "slot_size" ) = st::CBUFFER_DEFAULT_SLOT_SIZE );

    #else /* defined( SIXTRL_TESTLIB_ENABLED ) */
    ( void )root;
    #endif /* defined( SIXTRL_TESTLIB_ENABLED ) */
}

} /* end: namespace python */
} /* end: namespace SIXTRL_CXX_NAMESPACE */
#endif /* defined( __cplusplus ) */
