#ifndef SIXTRACKLIB_PYTHON_WRAPPER_BUFFER_PROTOCOL_ADAPTER_CLASS_H__
#define SIXTRACKLIB_PYTHON_WRAPPER_BUFFER_PROTOCOL_ADAPTER_CLASS_H__

#include "sixtracklib/common/cobjects/definitions.h"
#include "python/sixtracklib/_wrapper/tl/optional.hpp"

#include <memory>
#include <vector>
#include <stdexcept>

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace SIXTRL_CXX_NAMESPACE
{
namespace python
{
    struct InitHelper;

    SIXTRL_HOST_FN void InitHelper_buffer_protocol( InitHelper& root );
    SIXTRL_HOST_FN void InitHelper_buffer_protocol_real_adapter( InitHelper& );
    SIXTRL_HOST_FN void InitHelper_buffer_protocol_int64_adapter( InitHelper& );

    /* --------------------------------------------------------------------- */

    template< typename T,
        typename PtrConstT = SIXTRL_CBUFFER_DATAPTR_DEC typename std::decay<
            T >::type const*,
        typename PtrT = SIXTRL_CBUFFER_DATAPTR_DEC typename std::decay<
            T >::type* >
    struct TBufferAdapter
    {
        using value_type = typename std::decay< T >::type;
        using size_type  = ::NS(size_type);
        using addr_type  = ::NS(address_type);
        using raw_type   = ::NS(cobj_raw_type);

        using raw_const_pointer = SIXTRL_CBUFFER_DATAPTR_DEC raw_type const*;
        using raw_pointer = SIXTRL_CBUFFER_DATAPTR_DEC raw_type*;

        using const_pointer = PtrConstT;
        using pointer = PtrT;

        SIXTRL_HOST_FN explicit TBufferAdapter(
            addr_type begin_addr = SIXTRL_CXX_NAMESPACE::COBJECTS_NULL_ADDRESS,
            size_type length = size_type{ 0 } ) :
        m_begin_addr( begin_addr ), m_length( length )
        {
            if( ( begin_addr % sizeof( value_type ) ) != addr_type{ 0 } )
                throw std::runtime_error( "illegal alignment of begin addr" );
        }

        SIXTRL_HOST_FN TBufferAdapter(
            TBufferAdapter< T, PtrConstT, PtrT > const& ) = default;

        SIXTRL_HOST_FN TBufferAdapter(
            TBufferAdapter< T, PtrConstT, PtrT >&& ) = default;

        SIXTRL_HOST_FN TBufferAdapter< T, PtrConstT, PtrT >& operator=(
            TBufferAdapter< T, PtrConstT, PtrT > const& ) = default;

        SIXTRL_HOST_FN TBufferAdapter< T, PtrConstT, PtrT >& operator=(
            TBufferAdapter< T, PtrConstT, PtrT >&& ) = default;

        SIXTRL_HOST_FN ~TBufferAdapter() = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_INLINE SIXTRL_HOST_FN
        size_type raw_length() const SIXTRL_NOEXCEPT {
            return this->m_length * sizeof( value_type ); }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_INLINE SIXTRL_HOST_FN
        raw_const_pointer raw_begin() const SIXTRL_NOEXCEPT {
            return reinterpret_cast< raw_const_pointer >(
                static_cast< uintptr_t >( this->m_begin_addr ) ); }

        SIXTRL_INLINE SIXTRL_HOST_FN
        raw_const_pointer raw_end() const SIXTRL_NOEXCEPT
        {
            raw_const_pointer ptr_end = this->raw_begin();
            if( ptr_end != nullptr ) ptr_end = ptr_end + this->raw_length();
            return ptr_end;
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_INLINE SIXTRL_HOST_FN raw_pointer raw_begin() SIXTRL_NOEXCEPT {
            return reinterpret_cast< raw_pointer >(
                static_cast< uintptr_t >( this->m_begin_addr ) ); }

        SIXTRL_INLINE SIXTRL_HOST_FN raw_pointer raw_end() SIXTRL_NOEXCEPT {
            raw_pointer ptr_end = this->raw_begin();
            if( ptr_end != nullptr ) ptr_end = ptr_end + this->raw_length();
            return ptr_end; }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_INLINE SIXTRL_HOST_FN
        raw_const_pointer const_raw_begin() SIXTRL_NOEXCEPT {
            return reinterpret_cast< raw_const_pointer >(
                static_cast< uintptr_t >( this->m_begin_addr ) ); }

        SIXTRL_INLINE SIXTRL_HOST_FN raw_const_pointer
        const_raw_end() SIXTRL_NOEXCEPT
        {
            raw_const_pointer ptr_end = this->raw_begin();
            if( ptr_end != nullptr ) ptr_end = ptr_end + this->raw_length();
            return ptr_end;
        }

        /* ----------------------------------------------------------------- */

        SIXTRL_INLINE SIXTRL_HOST_FN size_type length() const SIXTRL_NOEXCEPT {
            return this->m_length; }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_INLINE SIXTRL_HOST_FN
        const_pointer value_begin() const SIXTRL_NOEXCEPT {
            return reinterpret_cast< const_pointer >(
                static_cast< uintptr_t >( this->m_begin_addr ) ); }

        SIXTRL_INLINE SIXTRL_HOST_FN
        const_pointer value_end() const SIXTRL_NOEXCEPT
        {
            const_pointer ptr_end = this->value_begin();
            if( ptr_end != nullptr ) ptr_end = ptr_end + this->length();
            return ptr_end;
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_INLINE SIXTRL_HOST_FN pointer value_begin() SIXTRL_NOEXCEPT {
            return reinterpret_cast< pointer >(
                static_cast< uintptr_t >( this->m_begin_addr ) ); }

        SIXTRL_INLINE SIXTRL_HOST_FN pointer value_end() SIXTRL_NOEXCEPT {
            pointer ptr_end = this->value_begin();
            if( ptr_end != nullptr ) ptr_end = ptr_end + this->length();
            return ptr_end; }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_INLINE SIXTRL_HOST_FN
        const_pointer const_value_begin() SIXTRL_NOEXCEPT {
            return reinterpret_cast< const_pointer >(
                static_cast< uintptr_t >( this->m_begin_addr ) ); }

        SIXTRL_INLINE SIXTRL_HOST_FN const_pointer
        const_value_end() SIXTRL_NOEXCEPT
        {
            const_pointer ptr_end = this->value_begin();
            if( ptr_end != nullptr ) ptr_end = ptr_end + this->length();
            return ptr_end;
        }

        /* ----------------------------------------------------------------- */

        addr_type m_begin_addr;
        size_type m_length;
    };

    using RealBufferAdapter  = TBufferAdapter< SIXTRL_REAL_TYPE >;
    using Int64BufferAdapter = TBufferAdapter< SIXTRL_INT64_TYPE >;

//     struct RealBufferAdapter
//     {
//         using value_type = SIXTRL_REAL_TYPE;
//         using size_type  = ::NS(size_type);
//         using addr_type  = ::NS(address_type);
//         using raw_type   = ::NS(cobj_raw_type);
//
//         using raw_const_pointer = SIXTRL_CBUFFER_DATAPTR_DEC raw_type const*;
//         using raw_pointer = SIXTRL_CBUFFER_DATAPTR_DEC raw_type*;
//
//         using const_pointer = SIXTRL_CBUFFER_DATAPTR_DEC value_type const*;
//         using pointer = SIXTRL_CBUFFER_DATAPTR_DEC value_type*;
//
//         SIXTRL_HOST_FN explicit RealBufferAdapter(
//             addr_type begin_addr = SIXTRL_CXX_NAMESPACE::COBJECTS_NULL_ADDRESS,
//             size_type length = size_type{ 0 } ) :
//         m_begin_addr( begin_addr ), m_length( length )
//         {
//             if( ( begin_addr % sizeof( value_type ) ) != addr_type{ 0 } )
//                 throw std::runtime_error( "illegal alignment of begin addr" );
//         }
//
//         SIXTRL_HOST_FN RealBufferAdapter( RealBufferAdapter const& ) = default;
//         SIXTRL_HOST_FN RealBufferAdapter( RealBufferAdapter&& ) = default;
//
//         SIXTRL_HOST_FN RealBufferAdapter& operator=(
//             RealBufferAdapter const& ) = default;
//
//         SIXTRL_HOST_FN RealBufferAdapter& operator=(
//             RealBufferAdapter&& ) = default;
//
//         SIXTRL_HOST_FN ~RealBufferAdapter() = default;
//
//         /* ----------------------------------------------------------------- */
//
//         SIXTRL_INLINE SIXTRL_HOST_FN
//         size_type raw_length() const SIXTRL_NOEXCEPT {
//             return this->m_length * sizeof( value_type ); }
//
//         /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
//
//         SIXTRL_INLINE SIXTRL_HOST_FN
//         raw_const_pointer raw_begin() const SIXTRL_NOEXCEPT {
//             return reinterpret_cast< raw_const_pointer >(
//                 static_cast< uintptr_t >( this->m_begin_addr ) ); }
//
//         SIXTRL_INLINE SIXTRL_HOST_FN
//         raw_const_pointer raw_end() const SIXTRL_NOEXCEPT
//         {
//             raw_const_pointer ptr_end = this->raw_begin();
//             if( ptr_end != nullptr ) ptr_end = ptr_end + this->raw_length();
//             return ptr_end;
//         }
//
//         /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
//
//         SIXTRL_INLINE SIXTRL_HOST_FN raw_pointer raw_begin() SIXTRL_NOEXCEPT {
//             return reinterpret_cast< raw_pointer >(
//                 static_cast< uintptr_t >( this->m_begin_addr ) ); }
//
//         SIXTRL_INLINE SIXTRL_HOST_FN raw_pointer raw_end() SIXTRL_NOEXCEPT {
//             raw_pointer ptr_end = this->raw_begin();
//             if( ptr_end != nullptr ) ptr_end = ptr_end + this->raw_length();
//             return ptr_end; }
//
//         /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
//
//         SIXTRL_INLINE SIXTRL_HOST_FN
//         raw_const_pointer const_raw_begin() SIXTRL_NOEXCEPT {
//             return reinterpret_cast< raw_const_pointer >(
//                 static_cast< uintptr_t >( this->m_begin_addr ) ); }
//
//         SIXTRL_INLINE SIXTRL_HOST_FN raw_const_pointer
//         const_raw_end() SIXTRL_NOEXCEPT
//         {
//             raw_const_pointer ptr_end = this->raw_begin();
//             if( ptr_end != nullptr ) ptr_end = ptr_end + this->raw_length();
//             return ptr_end;
//         }
//
//         /* ----------------------------------------------------------------- */
//
//         SIXTRL_INLINE SIXTRL_HOST_FN size_type length() const SIXTRL_NOEXCEPT {
//             return this->m_length; }
//
//         /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
//
//         SIXTRL_INLINE SIXTRL_HOST_FN
//         const_pointer value_begin() const SIXTRL_NOEXCEPT {
//             return reinterpret_cast< const_pointer >(
//                 static_cast< uintptr_t >( this->m_begin_addr ) ); }
//
//         SIXTRL_INLINE SIXTRL_HOST_FN
//         const_pointer value_end() const SIXTRL_NOEXCEPT
//         {
//             const_pointer ptr_end = this->value_begin();
//             if( ptr_end != nullptr ) ptr_end = ptr_end + this->length();
//             return ptr_end;
//         }
//
//         /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
//
//         SIXTRL_INLINE SIXTRL_HOST_FN pointer value_begin() SIXTRL_NOEXCEPT {
//             return reinterpret_cast< pointer >(
//                 static_cast< uintptr_t >( this->m_begin_addr ) ); }
//
//         SIXTRL_INLINE SIXTRL_HOST_FN pointer value_end() SIXTRL_NOEXCEPT {
//             pointer ptr_end = this->value_begin();
//             if( ptr_end != nullptr ) ptr_end = ptr_end + this->length();
//             return ptr_end; }
//
//         /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
//
//         SIXTRL_INLINE SIXTRL_HOST_FN
//         const_pointer const_value_begin() SIXTRL_NOEXCEPT {
//             return reinterpret_cast< const_pointer >(
//                 static_cast< uintptr_t >( this->m_begin_addr ) ); }
//
//         SIXTRL_INLINE SIXTRL_HOST_FN const_pointer
//         const_value_end() SIXTRL_NOEXCEPT
//         {
//             const_pointer ptr_end = this->value_begin();
//             if( ptr_end != nullptr ) ptr_end = ptr_end + this->length();
//             return ptr_end;
//         }
//
//         /* ----------------------------------------------------------------- */
//
//         addr_type m_begin_addr;
//         size_type m_length;
//     };

    /* ********************************************************************* */

//     struct Int64BufferAdapter
//     {
//         using value_type = SIXTRL_INT64_TYPE;
//         using size_type  = ::NS(size_type);
//         using addr_type  = ::NS(address_type);
//         using raw_type   = ::NS(cobj_raw_type);
//
//         using raw_const_pointer = SIXTRL_CBUFFER_DATAPTR_DEC raw_type const*;
//         using raw_pointer = SIXTRL_CBUFFER_DATAPTR_DEC raw_type*;
//
//         using const_pointer = SIXTRL_CBUFFER_DATAPTR_DEC value_type const*;
//         using pointer = SIXTRL_CBUFFER_DATAPTR_DEC value_type*;
//
//         SIXTRL_HOST_FN explicit Int64BufferAdapter(
//             addr_type begin_addr = SIXTRL_CXX_NAMESPACE::COBJECTS_NULL_ADDRESS,
//             size_type length = size_type{ 0 } ) :
//         m_begin_addr( begin_addr ), m_length( length )
//         {
//             if( ( begin_addr % sizeof( value_type ) ) != addr_type{ 0 } )
//                 throw std::runtime_error( "illegal alignment of begin addr" );
//         }
//
//         SIXTRL_HOST_FN Int64BufferAdapter( Int64BufferAdapter const& ) = default;
//         SIXTRL_HOST_FN Int64BufferAdapter( Int64BufferAdapter&& ) = default;
//
//         SIXTRL_HOST_FN Int64BufferAdapter& operator=(
//             Int64BufferAdapter const& ) = default;
//
//         SIXTRL_HOST_FN Int64BufferAdapter& operator=(
//             Int64BufferAdapter&& ) = default;
//
//         SIXTRL_HOST_FN ~Int64BufferAdapter() = default;
//
//         /* ----------------------------------------------------------------- */
//
//         SIXTRL_INLINE SIXTRL_HOST_FN
//         size_type raw_length() const SIXTRL_NOEXCEPT {
//             return this->m_length * sizeof( value_type ); }
//
//         /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
//
//         SIXTRL_INLINE SIXTRL_HOST_FN
//         raw_const_pointer raw_begin() const SIXTRL_NOEXCEPT {
//             return reinterpret_cast< raw_const_pointer >(
//                 static_cast< uintptr_t >( this->m_begin_addr ) ); }
//
//         SIXTRL_INLINE SIXTRL_HOST_FN
//         raw_const_pointer raw_end() const SIXTRL_NOEXCEPT
//         {
//             raw_const_pointer ptr_end = this->raw_begin();
//             if( ptr_end != nullptr ) ptr_end = ptr_end + this->raw_length();
//             return ptr_end;
//         }
//
//         /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
//
//         SIXTRL_INLINE SIXTRL_HOST_FN raw_pointer raw_begin() SIXTRL_NOEXCEPT {
//             return reinterpret_cast< raw_pointer >(
//                 static_cast< uintptr_t >( this->m_begin_addr ) ); }
//
//         SIXTRL_INLINE SIXTRL_HOST_FN raw_pointer raw_end() SIXTRL_NOEXCEPT {
//             raw_pointer ptr_end = this->raw_begin();
//             if( ptr_end != nullptr ) ptr_end = ptr_end + this->raw_length();
//             return ptr_end; }
//
//         /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
//
//         SIXTRL_INLINE SIXTRL_HOST_FN
//         raw_const_pointer const_raw_begin() SIXTRL_NOEXCEPT {
//             return reinterpret_cast< raw_const_pointer >(
//                 static_cast< uintptr_t >( this->m_begin_addr ) ); }
//
//         SIXTRL_INLINE SIXTRL_HOST_FN raw_const_pointer
//         const_raw_end() SIXTRL_NOEXCEPT
//         {
//             raw_const_pointer ptr_end = this->raw_begin();
//             if( ptr_end != nullptr ) ptr_end = ptr_end + this->raw_length();
//             return ptr_end;
//         }
//
//         /* ----------------------------------------------------------------- */
//
//         SIXTRL_INLINE SIXTRL_HOST_FN size_type length() const SIXTRL_NOEXCEPT {
//             return this->m_length; }
//
//         /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
//
//         SIXTRL_INLINE SIXTRL_HOST_FN
//         const_pointer value_begin() const SIXTRL_NOEXCEPT {
//             return reinterpret_cast< const_pointer >(
//                 static_cast< uintptr_t >( this->m_begin_addr ) ); }
//
//         SIXTRL_INLINE SIXTRL_HOST_FN
//         const_pointer value_end() const SIXTRL_NOEXCEPT
//         {
//             const_pointer ptr_end = this->value_begin();
//             if( ptr_end != nullptr ) ptr_end = ptr_end + this->length();
//             return ptr_end;
//         }
//
//         /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
//
//         SIXTRL_INLINE SIXTRL_HOST_FN pointer value_begin() SIXTRL_NOEXCEPT {
//             return reinterpret_cast< pointer >(
//                 static_cast< uintptr_t >( this->m_begin_addr ) ); }
//
//         SIXTRL_INLINE SIXTRL_HOST_FN pointer value_end() SIXTRL_NOEXCEPT {
//             pointer ptr_end = this->value_begin();
//             if( ptr_end != nullptr ) ptr_end = ptr_end + this->length();
//             return ptr_end; }
//
//         /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
//
//         SIXTRL_INLINE SIXTRL_HOST_FN
//         const_pointer const_value_begin() SIXTRL_NOEXCEPT {
//             return reinterpret_cast< const_pointer >(
//                 static_cast< uintptr_t >( this->m_begin_addr ) ); }
//
//         SIXTRL_INLINE SIXTRL_HOST_FN const_pointer
//         const_value_end() SIXTRL_NOEXCEPT
//         {
//             const_pointer ptr_end = this->value_begin();
//             if( ptr_end != nullptr ) ptr_end = ptr_end + this->length();
//             return ptr_end;
//         }
//
//         /* ----------------------------------------------------------------- */
//
//         addr_type m_begin_addr;
//         size_type m_length;
//     };

    /* ********************************************************************* */

    template< typename T >
    SIXTRL_INLINE SIXTRL_CXX_NAMESPACE::address_type
    PyArray_1d_begin_addr_if_compatible(
        tl::optional< pybind11::array_t< T, pybind11::array::c_style |
            pybind11::array::forcecast > > optional_arg,
        SIXTRL_CXX_NAMESPACE::size_type requ_min_num_elements,
        SIXTRL_CXX_NAMESPACE::size_type requ_max_num_elements =
            SIXTRL_CXX_NAMESPACE::size_type{ 0 },
        SIXTRL_CXX_NAMESPACE::address_type const fallback_addr =
            SIXTRL_CXX_NAMESPACE::COBJECTS_NULL_ADDRESS )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        namespace py = pybind11;
        using st_size_t = st::size_type;

        st::address_type  result_addr = fallback_addr;
        if( !optional_arg.has_value() ) return fallback_addr;

        auto const& in_array_arg = optional_arg.value();
        py::buffer_info in_array_info = in_array_arg.request();

        if( in_array_info.ndim != 1 ) {
            throw std::runtime_error( "in_array_arg has a ndim != 1" ); }

        if( ( requ_max_num_elements != st_size_t{ 0 } ) &&
            ( requ_max_num_elements <  requ_min_num_elements ) )
        {
            requ_max_num_elements = requ_min_num_elements;
        }

        if( ( ( requ_max_num_elements == st_size_t{ 0 } ) ||
              ( requ_max_num_elements >= in_array_info.shape[ 0 ] ) ) &&
            ( requ_min_num_elements <= in_array_info.shape[ 0 ] ) )
        {
            result_addr = static_cast< st::address_type >(
                reinterpret_cast< uintptr_t >( in_array_info.ptr ) );
        }

        return result_addr;
    }

    template< typename T, typename PtrT = T const* >
    SIXTRL_INLINE PtrT PyArray_1d_begin_pointer_if_compatible(
        tl::optional< pybind11::array_t< T, pybind11::array::c_style |
            pybind11::array::forcecast > > in_array_arg,
        SIXTRL_CXX_NAMESPACE::size_type requ_min_num_elements,
        SIXTRL_CXX_NAMESPACE::size_type requ_max_num_elements =
            SIXTRL_CXX_NAMESPACE::size_type{ 0 } ) {
        namespace stpy = SIXTRL_CXX_NAMESPACE::python;
        return reinterpret_cast< PtrT >( static_cast< uintptr_t >(
            stpy::PyArray_1d_begin_addr_if_compatible( in_array_arg,
                requ_min_num_elements, requ_max_num_elements ) ) );
    }

    /* ********************************************************************** */

    template< typename T >
    SIXTRL_INLINE bool PyArray_is_dense_1d(
        tl::optional< pybind11::array_t< T, pybind11::array::c_style |
            pybind11::array::forcecast > > in_array_arg,
        ::NS(size_type) const min_length = ::NS(size_type){ 0 } )
    {
        namespace py = pybind11;
        if( !in_array_arg.has_value() ) return false;

        py::buffer_info info = in_array_arg.value().request();
        if( info.ndim != 1 ) throw std::runtime_error( "ndim != 1" );

        return ( ( info.shape[ 0 ]   > py::ssize_t{ 0 } ) &&
                 ( info.strides[ 0 ] > py::ssize_t{ 0 } ) &&
                 ( sizeof( T ) == static_cast< ::NS(size_type) >(
                    info.strides[ 0 ] ) ) );
    }

    template< typename T >
    SIXTRL_INLINE bool PyArray_is_dense_or_not_available(
        tl::optional< pybind11::array_t< T, pybind11::array::c_style |
            pybind11::array::forcecast > > in_array_arg )
    {
        namespace stpy = SIXTRL_CXX_NAMESPACE::python;
        return ( ( !in_array_arg.has_value() ) ||
                 ( stpy::PyArray_is_dense_1d< T >( in_array_arg ) ) );
    }

    /* --------------------------------------------------------------------- */

    template< typename T >
    SIXTRL_INLINE ::NS(size_type) PyArray_length_1d(
        tl::optional< pybind11::array_t< T, pybind11::array::c_style |
            pybind11::array::forcecast > > opt_arg,
        ::NS(size_type) const min_length = ::NS(size_type){ 0 } ) {
        namespace py = pybind11;
        ::NS(size_type) length = min_length;
        if( !opt_arg.has_value() ) return length;

        auto const& in_array_arg = opt_arg.value();
        py::buffer_info info = in_array_arg.request();
        if( info.ndim != 1 ) throw std::runtime_error( "ndim != 1" );
        if( ( info.shape[ 0 ] > py::ssize_t{ 0 } ) &&
            ( static_cast< ::NS(size_type) >( info.shape[ 0 ] ) > length ) )
            length = static_cast< ::NS(size_type) >( info.shape[ 0 ] );
        return length; }

    /* --------------------------------------------------------------------- */

    template< typename T >
    SIXTRL_INLINE ::NS(size_type) PyArray_stride_1d(
        tl::optional< pybind11::array_t< T, pybind11::array::c_style |
            pybind11::array::forcecast > > in_array_arg )
    {
        if( !in_array_arg.has_value() )
            return sizeof( typename std::decay< T >::type );

        pybind11::buffer_info const info = in_array_arg.value().request();

        if( info.ndim != 1 )
            throw std::runtime_error( "ndim != 1" );

        if( info.shape[ 0 ] == pybind11::ssize_t{ 0 } )
            throw std::runtime_error( "stride == 0" );

        return static_cast< ::NS(size_type) >( info.strides[ 0 ] );
    }

    /* --------------------------------------------------------------------- */

    template< typename T >
    SIXTRL_INLINE ::NS(address_type) PyArray_base_addr_1d(
        tl::optional< pybind11::array_t< T, pybind11::array::c_style |
                pybind11::array::forcecast > > in_array_arg,
        ::NS(size_type) requ_alignment  = ::NS(size_type){ 1 },
        ::NS(size_type) const requ_min_length = ::NS(size_type){ 0 },
        ::NS(address_type) const fallback_addr = ::NS(COBJECTS_NULL_ADDRESS),
        SIXTRL_ARGPTR_DEC ::NS(size_type)*
            SIXTRL_RESTRICT ptr_raw_length = nullptr,
        SIXTRL_ARGPTR_DEC ::NS(size_type)*
            SIXTRL_RESTRICT ptr_eff_length = nullptr )
    {
        namespace py = pybind11;
        using addr_type = ::NS(address_type);
        using size_type = ::NS(size_type);

        if( !in_array_arg.has_value() ) return fallback_addr;
        addr_type base_addr = fallback_addr;

        py::buffer_info info = in_array_arg.value().request();

        if( info.ndim != 1 ) throw std::runtime_error( "ndim != 1" );
        if( info.shape[ 0 ] < py::ssize_t{ 0 } )
            throw std::runtime_error( "shape[ 0 ] < 0" );

        if( info.strides[ 0 ] == py::ssize_t{ 0 } )
            throw std::runtime_error( "strides == 0" );

        if( requ_alignment == size_type{ 0 } )
            requ_alignment =  size_type{ 1 };

        py::ssize_t const nlen = info.shape[ 0 ];

        if( ( info.ptr != nullptr ) && ( nlen > py::ssize_t{ 0 } ) &&
            ( static_cast< size_type >( nlen ) >= requ_min_length ) &&
            ( ( nlen == py::ssize_t{ 0 } ) ||
              ( nlen >  static_cast< py::ssize_t >( requ_alignment ) ) ) )
        {
            base_addr = static_cast< addr_type >(
                reinterpret_cast< uintptr_t >( info.ptr ) );

            size_type raw_length = static_cast< size_type >( nlen );
            size_type eff_length = raw_length;

            if( ( base_addr != SIXTRL_CXX_NAMESPACE::COBJECTS_NULL_ADDRESS ) &&
                ( nlen > py::ssize_t{ 0 } ) &&
                ( ( base_addr % requ_alignment ) != addr_type{ 0 } ) )
            {
                auto offset = requ_alignment - ( base_addr % requ_alignment );
                base_addr  += offset;
                eff_length -= offset;
            }

            if( ptr_raw_length != nullptr ) *ptr_raw_length = raw_length;
            if( ptr_eff_length != nullptr ) *ptr_eff_length = eff_length;
        }

        return base_addr;
    }

    template< typename T, typename PtrT = SIXTRL_CBUFFER_DATAPTR_DEC T const* >
    SIXTRL_INLINE PtrT PyArray_base_pointer_1d(
        tl::optional< pybind11::array_t< T, pybind11::array::c_style |
            pybind11::array::forcecast > > in_array_arg )
    {
        return reinterpret_cast< PtrT >( static_cast< uintptr_t >(
            SIXTRL_CXX_NAMESPACE::python::PyArray_base_addr_1d< T >(
                in_array_arg, ::NS(size_type ){ 1 }, ::NS(size_type){ 0 },
                    ::NS(COBJECTS_NULL_ADDRESS) ) ) );
    }

    /* ---------------------------------------------------------------------- */

    template< typename ValueT, typename IntegerT >
    SIXTRL_INLINE ::NS(address_type) PyArray_stable_base_addr_1d(
        tl::optional< pybind11::array_t< ValueT, pybind11::array::c_style |
            pybind11::array::forcecast > > opt_arg,
        IntegerT const& SIXTRL_RESTRICT_REF capacity,
        IntegerT& SIXTRL_RESTRICT_REF length,
        std::unique_ptr< std::vector< ValueT > >& buffer_if_not_large_enough,
        ValueT const& default_value = ValueT{} )
    {
        namespace py = pybind11;
        namespace stpy = SIXTRL_CXX_NAMESPACE::python;
        using addr_type = ::NS(address_type);
        using size_type = ::NS(size_type);

        addr_type base_addr = ::NS(COBJECTS_NULL_ADDRESS);

        if( capacity < IntegerT{ 0 } )
            throw std::runtime_error( "capacity < 0" );

        length = IntegerT{ 0 };
        if( opt_arg.has_value() )
        {
            auto const& in_array_arg = opt_arg.value();
            py::buffer_info const info = in_array_arg.request();

            if( info.ndim != 1 ) throw std::runtime_error( "ndim != 1" );
            if( info.shape[ 0 ] < py::ssize_t{ 0 } )
                throw std::runtime_error( "shape[ 0 ] < 0" );

            if( info.ptr != nullptr )
            {
                length = static_cast< IntegerT >( info.shape[ 0 ] );

                if( ( length > IntegerT{ 0 } ) && ( length >= capacity ) )
                {
                    base_addr = static_cast< addr_type >( reinterpret_cast<
                        uintptr_t >( info.ptr ) );
                }
            }
        }

        if( length < capacity )
        {
            if( buffer_if_not_large_enough.get() != nullptr )
            {
                buffer_if_not_large_enough.reset( new std::vector< ValueT >(
                    static_cast< size_type >( capacity ), default_value ) );
            }
            else
            {
                buffer_if_not_large_enough->resize(
                    static_cast< size_type >( capacity ), default_value );
            }

            if( ( length > IntegerT{ 0 } ) && ( opt_arg.has_value() ) )
            {
                py::buffer_info info = opt_arg.value().request();

                if( info.ptr != nullptr )
                {
                    auto in_begin = reinterpret_cast< ValueT const* >(
                            reinterpret_cast< uintptr_t >( info.ptr ) );

                    auto in_end = in_begin;
                    std::advance( in_end, length );

                    std::copy( in_begin, in_end,
                            buffer_if_not_large_enough->begin() );
                }
            }

            base_addr = static_cast< addr_type >( reinterpret_cast<
                uintptr_t >( buffer_if_not_large_enough->data() ) );
        }

        return base_addr;
    }

    template< typename ValueT, typename IntegerT,
              typename PtrT = SIXTRL_CBUFFER_DATAPTR_DEC ValueT const* >
    SIXTRL_INLINE PtrT PyArray_stable_base_pointer_1d(
        tl::optional< pybind11::array_t< ValueT, pybind11::array::c_style |
            pybind11::array::forcecast > > in_array_arg,
        IntegerT const& SIXTRL_RESTRICT_REF capacity,
        IntegerT& SIXTRL_RESTRICT_REF length,
        std::unique_ptr< std::vector< ValueT > >& buffer_if_not_large_enough,
        ValueT const& default_value = ValueT{} )
    {
        return reinterpret_cast< PtrT >( static_cast< uintptr_t >(
            SIXTRL_CXX_NAMESPACE::python::PyArray_stable_base_addr_1d<
                ValueT, IntegerT >( in_array_arg, capacity, length,
                    buffer_if_not_large_enough, default_value ) ) );
    }

} /* end: namespace python */
} /* end: namespace SIXTRL_CXX_NAMESPACE */

#endif /* SIXTRACKLIB_PYTHON_WRAPPER_BUFFER_PROTOCOL_ADAPTER_CLASS_H__ */
