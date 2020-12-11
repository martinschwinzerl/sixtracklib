#ifndef SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_COBJECTS_INITIALISER_BASE_CXX_HPP__
#define SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_COBJECTS_INITIALISER_BASE_CXX_HPP__

#if defined( __cplusplus ) && !defined( _GPUCODE )
#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <memory>
    #include <vector>
    #include <utility>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */
#endif /* C++, Host */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/cobjects/cbuffer_view.hpp"
    #include "sixtracklib/common/cobjects/flat_buffer.h"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
    #include "sixtracklib/testlib/common/objs/objs_initialiser_base.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    class CObjElemInitialiserBase : public ObjsInitialiserBase
    {
        public:

        SIXTRL_HOST_FN CObjElemInitialiserBase() = default;

        SIXTRL_HOST_FN CObjElemInitialiserBase(
            CObjElemInitialiserBase const& ) = default;

        SIXTRL_HOST_FN CObjElemInitialiserBase(
            CObjElemInitialiserBase&& ) = default;

        SIXTRL_HOST_FN CObjElemInitialiserBase& operator=(
            CObjElemInitialiserBase const& ) = default;

        SIXTRL_HOST_FN CObjElemInitialiserBase& operator=(
            CObjElemInitialiserBase&& ) = default;

        SIXTRL_HOST_FN virtual ~CObjElemInitialiserBase() = default;


        using ObjsInitialiserBase::add_ptr_field;

        SIXTRL_HOST_FN std::pair< address_t, status_t > add_ptr_field(
            SIXTRL_CXX_NAMESPACE::CBufferView const& SIXTRL_RESTRICT_REF view,
            size_type const requ_capacity,
            size_type alignment = size_type{ 0 } )
        {
            std::pair< address_t, status_t > res = std::make_pair(
                address_t{ 0 }, this->set_slot_size( view.slot_size() ) );

            if( res.second == SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS )
            {
                res = this->do_add_ptr_field( requ_capacity, alignment );
            }

            return res;
        }

        SIXTRL_HOST_FN std::pair< address_t, status_t > add_ptr_field(
        SIXTRL_CXX_NAMESPACE::CBufferView const& SIXTRL_RESTRICT_REF view,
            size_type const field_size, size_type const num_elements,
            size_type const alignment = size_type{ 0 } )
        {
            std::pair< address_t, status_t > res = std::make_pair(
                address_t{ 0 }, this->set_slot_size( view.slot_size() ) );

            if( res.second == SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS )
            {
                res = this->do_add_ptr_field(
                    field_size * num_elements, alignment );
            }

            return res;
        }

        template< typename FieldT >
        SIXTRL_HOST_FN  std::pair< address_t, status_t > add_ptr_field(
            SIXTRL_CXX_NAMESPACE::CBufferView const& SIXTRL_RESTRICT_REF view,
            size_type const num_elements,
            size_type const alignment = size_type{ 0 } )
        {
            std::pair< address_t, status_t > res = std::make_pair(
                address_t{ 0 }, this->set_slot_size( view.slot_size() ) );

            if( res.second == SIXTRL_CXX_NAMESPACE::ARCH_STATUS_SUCCESS )
            {
                res = this->do_add_ptr_field(
                    sizeof( FieldT ) * num_elements, alignment );
            }

            return res;
        }

        SIXTRL_HOST_FN size_type slot_size() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN status_t set_slot_size(
            size_type const slot_size ) SIXTRL_NOEXCEPT;

        protected:

        SIXTRL_HOST_FN status_t do_reset() override;
        SIXTRL_HOST_FN std::pair< address_t, status_t > do_add_ptr_field(
                        size_type requ_capacity, size_type alignment) override;

        private:

        size_type m_slot_size = SIXTRL_CXX_NAMESPACE::CBUFFER_DEFAULT_SLOT_SIZE;
    };

} /* namespace: tests */
} /* namespace: SIXTRL_CXX_NAMESPACE */
#endif /* C++, Host */

#endif /* SIXTRACKLIB_TESTLIB_COMMON_COBJECTS_COBJECTS_INITIALISER_BASE_CXX_HPP__ */
