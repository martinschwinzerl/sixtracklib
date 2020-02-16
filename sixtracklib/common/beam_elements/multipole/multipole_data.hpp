#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_DATA_CXX_HPP__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_DATA_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/multipole/definitions.h"
    #include "sixtracklib/common/beam_elements/multipole/multipole.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )

namespace SIXTRL_CXX_NAMESPACE
{
    template< class R, class Order,
        SIXTRL_CXX_NAMESPACE::arch_size_t RAlign =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< R >(),
        SIXTRL_CXX_NAMESPACE::arch_size_t OrderAlign =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< Order >(),
        SIXTRL_CXX_NAMESPACE::arch_size_t AddressAlign =
            SIXTRL_CXX_NAMESPACE::Type_storage_align< be_address_t >() >
    struct MultipoleData
    {
        Order           order       SIXTRL_ALIGN( OrderAlign );
        R               length      SIXTRL_ALIGN( RAlign );
        R               hxl         SIXTRL_ALIGN( RAlign );
        R               hyl         SIXTRL_ALIGN( RAlign );

        be_address_t    bal_addr    SIXTRL_ALIGN( AddressAlign );
    };

    /* ********************************************************************* */
    /* Create a typedef for the equivalent MultipoleData to the C-API type:  */
    /* ********************************************************************* */

    typedef MultipoleData< be_real_t, be_order_t,
        SIXTRL_CXX_NAMESPACE::Type_storage_align< be_real_t >(),
        SIXTRL_CXX_NAMESPACE::Type_storage_align< be_order_t >(),
        SIXTRL_CXX_NAMESPACE::Type_storage_align< be_address_t>() >
        CMultipoleEquivData;

    template<> struct ObjDataCApiTypeTraits< CMultipoleEquivData >
    {
        static_assert(
            SIXTRL_CXX_NAMESPACE::ObjData_can_be_equivalent_to_c_api_type<
                CMultipoleEquivData, ::NS(Multipole) >(),
            "CMultipoleEquivData and ::NS(Multipole) are not "
            "equivalent C-Api types" );

        typedef ::NS(Multipole) c_api_t;
    };

    /* ********************************************************************* */
    /* Specializations for MultipoleData: */
    /* ********************************************************************* */

    template< class R, class Order,
        arch_size_t RAlign, arch_size_t OrderAlign, arch_size_t AddrAlign >
    struct MultipoleTraits<
        MultipoleData< R, Order, RAlign, OrderAlign, AddrAlign > >
    {
        typedef R               real_t;
        typedef Order           order_t;
        typedef be_address_t    address_t;

        static constexpr arch_size_t real_alignment    = RAlign;
        static constexpr arch_size_t order_alignment   = OrderAlign;
        static constexpr arch_size_t address_alignment = AddrAlign;
    };

    template< class R, class Order,
              arch_size_t RAlign, arch_size_t OAlign, arch_size_t AddrAlign >
    constexpr arch_size_t MultipoleTraits< MultipoleData<
        R, Order, RAlign, OAlign, AddrAlign > >::real_alignment;

    template< class R, class Order,
              arch_size_t RAlign, arch_size_t OAlign, arch_size_t AddrAlign >
    constexpr arch_size_t MultipoleTraits< MultipoleData<
        R, Order, RAlign, OAlign, AddrAlign > >::order_alignment;

    template< class R, class Order,
              arch_size_t RAlign, arch_size_t OAlign, arch_size_t AddrAlign >
    constexpr arch_size_t MultipoleTraits< MultipoleData<
        R, Order, RAlign, OAlign, AddrAlign > >::address_alignment;
}

#endif /* __cplusplus */

#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_DATA_CXX_HPP__ */
