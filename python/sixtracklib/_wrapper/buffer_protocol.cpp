#include "python/sixtracklib/_wrapper/cxx11_optional.h"
#include "python/sixtracklib/_wrapper/buffer_protocol.h"
#include "python/sixtracklib/_wrapper/init_helper.h"

#include "sixtracklib/common/cobjects/definitions.h"
#include "sixtracklib/common/cobjects/cbuffer_view.hpp"

#include <tuple>

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

namespace SIXTRL_CXX_NAMESPACE {
namespace python {
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        namespace stpy = SIXTRL_CXX_NAMESPACE::python;
        namespace py = pybind11;
    }

    void InitHelper_buffer_protocol( stpy::InitHelper& root )
    {
        using real_type  = SIXTRL_REAL_TYPE;
        using index_type = SIXTRL_INT64_TYPE;
        using size_type  = ::NS(size_type);
        using addr_type  = ::NS(address_type);

        stpy::InitHelper_buffer_protocol_real_adapter( root );
        stpy::InitHelper_buffer_protocol_int64_adapter( root );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        using py_array_real_t = py::array_t< real_type,
            py::array::c_style | py::array::forcecast >;

        root.m.def( "CObjects_numpy_1d_real_length",
            []( tl::optional< py_array_real_t > optional_arg ) {
                return stpy::PyArray_length_1d< real_type >( optional_arg ); },
            py::arg( "np_array" ) = tl::optional< py_array_real_t >() );

        root.m.def( "CObjects_numpy_1d_real_stride",
            []( tl::optional< py_array_real_t > optional_arg ) {
                return stpy::PyArray_stride_1d< real_type >( optional_arg ); },
            py::arg( "np_array" ) = tl::optional< py_array_real_t >() );

        root.m.def( "CObjects_numpy_1d_real_is_dense",
            []( tl::optional< py_array_real_t > optional_arg ) {
                return stpy::PyArray_is_dense_1d< real_type>( optional_arg ); },
            py::arg( "np_array" ) = tl::optional< py_array_real_t >() );

        root.m.def( "CObjects_numpy_1d_real_is_dense_or_not_available",
            []( tl::optional< py_array_real_t > optional_arg ) {
                return stpy::PyArray_is_dense_or_not_available< real_type>(
                    optional_arg ); },
            py::arg( "np_array" ) = tl::optional< py_array_real_t >() );

        root.m.def( "CObjects_numpy_1d_real_base_addr",
            []( tl::optional< py_array_real_t > optional_arg,
                size_type const requ_alignment,
                size_type const requ_min_length,
                addr_type const fallback_addr ) -> addr_type {
                addr_type const base_addr = stpy::PyArray_base_addr_1d< real_type
                    >( optional_arg, requ_alignment, requ_min_length,
                        fallback_addr, nullptr, nullptr );
                return base_addr; },
            py::arg( "np_array" ) = tl::optional< py_array_real_t >(),
            py::arg( "requ_alignment" ) = size_type{ 1 },
            py::arg( "requ_min_length" ) = size_type{ 0 },
            py::arg( "fallback_addr" ) = st::COBJECTS_NULL_ADDRESS );

        root.m.def( "CObjects_numpy_1d_real_base_addr_detailed",
            []( tl::optional< py_array_real_t > optional_arg,
                size_type const requ_alignment,
                size_type const requ_min_length,
                addr_type const fallback_addr ) ->
                std::tuple< addr_type, size_type, size_type > {
                SIXTRL_ARGPTR_DEC size_type raw_length = size_type{ 0 };
                SIXTRL_ARGPTR_DEC size_type eff_length = size_type{ 0 };
                addr_type const base_addr = stpy::PyArray_base_addr_1d< real_type
                    >( optional_arg, requ_alignment, requ_min_length,
                        fallback_addr, &raw_length, &eff_length );
                return std::make_tuple( base_addr, raw_length, eff_length ); },
            py::arg( "np_array" ) = tl::optional< py_array_real_t >(),
            py::arg( "requ_alignment" ) = size_type{ 1 },
            py::arg( "requ_min_length" ) = size_type{ 0 },
            py::arg( "fallback_addr" ) = st::COBJECTS_NULL_ADDRESS );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        using py_array_index_t = py::array_t< index_type,
            py::array::c_style | py::array::forcecast >;

        root.m.def( "CObjects_numpy_1d_index_length",
            []( tl::optional< py_array_index_t > optional_arg ) {
                return stpy::PyArray_length_1d< index_type >( optional_arg ); },
            py::arg( "np_array" ) = tl::optional< py_array_index_t >() );

        root.m.def( "CObjects_numpy_1d_index_stride",
            []( tl::optional< py_array_index_t > optional_arg ) {
                return stpy::PyArray_stride_1d< index_type >( optional_arg ); },
            py::arg( "np_array" ) = tl::optional< py_array_index_t >() );

        root.m.def( "CObjects_numpy_1d_index_is_dense",
            []( tl::optional< py_array_index_t > optional_arg ) {
                return stpy::PyArray_is_dense_1d< index_type>( optional_arg ); },
            py::arg( "np_array" ) = tl::optional< py_array_index_t >() );

        root.m.def( "CObjects_numpy_1d_index_is_dense_or_not_available",
            []( tl::optional< py_array_index_t > optional_arg ) {
                return stpy::PyArray_is_dense_or_not_available< index_type>(
                    optional_arg ); },
            py::arg( "np_array" ) = tl::optional< py_array_index_t >() );

        root.m.def( "CObjects_numpy_1d_index_base_addr",
            []( tl::optional< py_array_index_t > optional_arg,
                size_type const requ_alignment,
                size_type const requ_min_length,
                addr_type const fallback_addr ){
                addr_type const base_addr = stpy::PyArray_base_addr_1d<
                    index_type >( optional_arg, requ_alignment, requ_min_length,
                        fallback_addr, nullptr, nullptr );
                return base_addr; },
            py::arg( "np_array" ) = tl::optional< py_array_index_t >(),
            py::arg( "requ_alignment" ) = size_type{ 1 },
            py::arg( "requ_min_length" ) = size_type{ 0 },
            py::arg( "fallback_addr" ) = st::COBJECTS_NULL_ADDRESS );

        root.m.def( "CObjects_numpy_1d_index_base_addr_detailed",
            []( tl::optional< py_array_index_t > optional_arg,
                size_type const requ_alignment,
                size_type const requ_min_length,
                addr_type const fallback_addr ) ->
                std::tuple< addr_type, size_type, size_type > {
                SIXTRL_ARGPTR_DEC size_type raw_length = size_type{ 0 };
                SIXTRL_ARGPTR_DEC size_type eff_length = size_type{ 0 };
                addr_type const base_addr = stpy::PyArray_base_addr_1d<
                    index_type >( optional_arg, requ_alignment, requ_min_length,
                        fallback_addr, &raw_length, &eff_length );
                return std::make_tuple( base_addr, raw_length, eff_length ); },
            py::arg( "np_array" ) = tl::optional< py_array_index_t >(),
            py::arg( "requ_alignment" ) = size_type{ 1 },
            py::arg( "requ_min_length" ) = size_type{ 0 },
            py::arg( "fallback_addr" ) = st::COBJECTS_NULL_ADDRESS );
    }

    void InitHelper_buffer_protocol_real_adapter( stpy::InitHelper& root ) {
        using value_type = RealBufferAdapter::value_type;
        auto& obj = root.real_adapter_type;
        obj.def_buffer( []( RealBufferAdapter& adapter ) -> py::buffer_info {
            return pybind11::buffer_info( adapter.raw_begin(),
                sizeof( value_type ),
                pybind11::format_descriptor< value_type >::format(), 1,
                { adapter.length() }, { sizeof( value_type ) } ); } );
    }

    void InitHelper_buffer_protocol_int64_adapter( stpy::InitHelper& root ) {
        using value_type = RealBufferAdapter::value_type;
        auto& obj = root.int64_adapter_type;
        obj.def_buffer(
            []( Int64BufferAdapter& adapter ) -> pybind11::buffer_info
            {
                return pybind11::buffer_info(
                    adapter.raw_begin(),
                    sizeof( value_type ),
                    pybind11::format_descriptor< value_type >::format(), 1,
                    { adapter.length() },
                    { sizeof( value_type ) } );
            } );
    }

} /* end: namespace python */
} /* end: namespace SIXTRL_CXX_NAMESPACE */
