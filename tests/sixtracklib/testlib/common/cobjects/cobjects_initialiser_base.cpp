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
        typedef ObjsInitialiserBase     base_t;
        typedef CObjElemInitialiserBase this_t;
    }

    this_t::size_type this_t::slot_size() const SIXTRL_NOEXCEPT
    {
        return this->m_slot_size;
    }

    this_t::status_t this_t::set_slot_size(
        this_t::size_type const slot_size ) SIXTRL_NOEXCEPT
    {
        this_t::status_t status = st::ARCH_STATUS_GENERAL_FAILURE;

        if( slot_size > this_t::size_type{ 0 } )
        {
            this->m_slot_size = slot_size;
            status = st::ARCH_STATUS_SUCCESS;
        }

        return status;
    }

    this_t::status_t this_t::do_reset()
    {
        this->m_slot_size = st::CBUFFER_DEFAULT_SLOT_SIZE;
        return base_t::do_reset();
    }

    std::pair< this_t::address_t, this_t::status_t >
    this_t::do_add_ptr_field( this_t::size_type requ_capacity,
                              this_t::size_type alignment )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        typedef this_t::size_type size_t;

        std::pair< address_t, status_t > result = std::make_pair(
            address_t{ 0 }, st::ARCH_STATUS_GENERAL_FAILURE );

        if( this->slot_size() > size_t{ 0 } )
        {
            if( alignment != size_t{ 0 } )
            {
                alignment = ::NS(CObjFlatBuffer_slot_based_size)(
                    alignment, this->slot_size() );
            }
            else
            {
                 alignment = this->slot_size();
            }

            SIXTRL_ASSERT( alignment > size_t{ 0 } );
            SIXTRL_ASSERT( ( alignment % this->slot_size() ) == size_t{ 0 } );

            result = base_t::do_add_ptr_field(
                ::NS(CObjFlatBuffer_slot_based_size)(
                    requ_capacity, this->slot_size() ), alignment );
        }

        return result;
    }

} /* namespace: tests */
} /* namespace: SIXTRL_CXX_NAMESPACE */
#endif /* C++, Host */
