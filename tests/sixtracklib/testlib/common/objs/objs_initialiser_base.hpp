#ifndef SIXTRACKLIB_TESTLIB_COMMON_OBJS_OBJS_INITIALIZER_BASE_CXX_HPP__
#define SIXTRACKLIB_TESTLIB_COMMON_OBJS_OBJS_INITIALIZER_BASE_CXX_HPP__

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
    #include "sixtracklib/common/internal/type_store_traits.hpp"
    #include "sixtracklib/common/internal/buffer_main_defines.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
namespace tests
{
    class ObjsInitialiserBase
    {
        public:

        typedef SIXTRL_CXX_NAMESPACE::arch_status_t  status_t;
        typedef SIXTRL_CXX_NAMESPACE::arch_address_t address_t;
        typedef SIXTRL_CXX_NAMESPACE::arch_size_t    size_type;

        SIXTRL_HOST_FN ObjsInitialiserBase() = default;

        SIXTRL_HOST_FN ObjsInitialiserBase(
            ObjsInitialiserBase const& ) = default;

        SIXTRL_HOST_FN ObjsInitialiserBase(
            ObjsInitialiserBase&& ) = default;

        SIXTRL_HOST_FN ObjsInitialiserBase& operator=(
            ObjsInitialiserBase const& ) = default;

        SIXTRL_HOST_FN ObjsInitialiserBase& operator=(
            ObjsInitialiserBase&& ) = default;

        SIXTRL_HOST_FN virtual ~ObjsInitialiserBase() = default;

        SIXTRL_HOST_FN status_t reset();

        SIXTRL_HOST_FN std::pair< address_t, status_t >
        add_ptr_field( size_type const elem_size, size_type const num_elements,
                       size_type alignment);

        SIXTRL_HOST_FN std::pair< address_t, status_t >
        add_ptr_field( size_type const requ_capacity, size_type alignment);

        template< class FieldT >
        SIXTRL_HOST_FN std::pair< address_t, status_t >
        add_ptr_field( size_type const num_elements,
                       size_type alignment = size_type{ 0 } )
        {
            if( alignment == size_type{ 0 } )
                alignment = SIXTRL_CXX_NAMESPACE::Type_storage_align<FieldT>();

            size_type const requ_capacity = sizeof( FieldT ) * num_elements;
            return this->do_add_ptr_field( requ_capacity, alignment );
        }

        protected:

        SIXTRL_HOST_FN virtual status_t do_reset();

        SIXTRL_HOST_FN virtual std::pair< address_t, status_t >
        do_add_ptr_field( size_type requ_capacity, size_type alignment );

        private:

        std::vector< std::unique_ptr<
            SIXTRL_BUFFER_DATAPTR_DEC unsigned char[] > > ptr_field_arrays;
    };

} /* namespace: tests */
} /* namespace: SIXTRL_CXX_NAMESPACE */
#endif /* C++, Host */

#endif /* SIXTRACKLIB_TESTLIB_COMMON_OBJS_OBJS_INITIALIZER_BASE_CXX_HPP__ */
