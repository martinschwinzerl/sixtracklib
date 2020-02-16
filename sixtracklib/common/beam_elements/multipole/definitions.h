#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_DEFINITIONS_H__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_DEFINITIONS_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stddef.h>
    #include <stdlib.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/beam_elements/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class MultipoleDataObj >
    struct MultipoleTraits
    {
        typedef SIXTRL_CXX_NAMESPACE::be_real_t     real_t;
        typedef SIXTRL_CXX_NAMESPACE::be_order_t    order_t;
        typedef SIXTRL_CXX_NAMESPACE::buffer_addr_t address_t;

        static constexpr arch_size_t real_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< real_t >();

        static constexpr arch_size_t order_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< order_t >();

        static constexpr arch_size_t address_alignment =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< order_t >();
    };

    template< class MultipoleDataObj >
    constexpr arch_size_t MultipoleTraits< MultipoleDataObj >::real_alignment;

    template< class MultipoleDataObj >
    constexpr arch_size_t MultipoleTraits< MultipoleDataObj >::order_alignment;

    template< class MultipoleDataObj >
    constexpr arch_size_t MultipoleTraits<
        MultipoleDataObj >::address_alignment;
}
#endif /* __cplusplus */

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_DEFINITIONS_H__ */
