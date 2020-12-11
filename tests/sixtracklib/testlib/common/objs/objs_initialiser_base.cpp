#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/testlib/common/cobjects/cobjects_initialiser_base.hpp"
    #include "sixtracklib/common/cobjects/flat_buffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    namespace
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef ObjsInitialiserBase base_t;
    }

    base_t::status_t base_t::reset()
    {
        return this->do_reset();
    }

    base_t::status_t base_t::do_reset()
    {
        this->ptr_field_arrays.clear();
        return st::ARCH_STATUS_SUCCESS;
    }

    std::pair< base_t::address_t, base_t::status_t >
    base_t::add_ptr_field(
        base_t::size_type const elem_size,
        base_t::size_type const num_elements,
        base_t::size_type alignment )
    {
        if( alignment == base_t::size_type{ 0 } )
        {
            alignment = ( elem_size > base_t::size_type{ 0 } )
                ? elem_size : base_t::size_type{ 1 };
        }

        size_t const requ_capacity = num_elements * elem_size;
        return this->do_add_ptr_field( requ_capacity, alignment );
    }

    std::pair< base_t::address_t, base_t::status_t >
    base_t::add_ptr_field(
        base_t::size_type const requ_capacity,
        base_t::size_type alignment)
    {
        if( alignment == base_t::size_type{ 0 } )
        {
            alignment = base_t::size_type{ 1 };
        }

        return this->do_add_ptr_field( requ_capacity, alignment );
    }

    std::pair< base_t::address_t, base_t::status_t >
    base_t::do_add_ptr_field(
        base_t::size_type requ_capacity, base_t::size_type alignment )
    {
        typedef base_t::address_t addr_t;
        typedef base_t::size_type size_t;
        typedef SIXTRL_BUFFER_DATAPTR_DEC unsigned char raw_t;

        std::pair< addr_t, base_t::status_t > result =
            std::make_pair( addr_t{ 0 }, st::ARCH_STATUS_GENERAL_FAILURE );

        if( requ_capacity > size_t{ 0 } )
        {
            if( alignment > size_t{ 1 } ) requ_capacity += alignment;
            std::unique_ptr< raw_t[] > ptr_field( new raw_t[ requ_capacity ] );

            addr_t field_addr = static_cast< addr_t >( reinterpret_cast<
                std::uintptr_t >( ptr_field.get() ) );

            this->ptr_field_arrays.push_back( std::move( ptr_field ) );

            if( field_addr != addr_t{ 0 } )
            {
                addr_t const mis_align = field_addr % alignment;
                result.second = st::ARCH_STATUS_SUCCESS;

                if( mis_align != addr_t{ 0 } )
                    field_addr += ( alignment - mis_align );
            }

            result.first = field_addr;
        }
        else
        {
            result.second = st::ARCH_STATUS_SUCCESS;
        }

        return result;
    }

} /* namespace: tests */
} /* namespace: SIXTRL_CXX_NAMESPACE */
#endif /* C++, Host */
