#ifndef SIXTRACKLIB_COMMON_BE_MULTIPOLE_BE_MULTIPOLE_TRAITS_CXX_HPP__
#define SIXTRACKLIB_COMMON_BE_MULTIPOLE_BE_MULTIPOLE_TRAITS_CXX_HPP__

namespace sixtrack_cxx
{
    template< class BeObjData >
    struct BeMultipoleTraits
    {
        typedef typename BeObjData::real_t          real_t;
        typedef typename BeObjData::order_t         order_t;
        typedef typename BeObjData::bal_addr_t      bal_addr_t;
    };
}

#endif /* SIXTRACKLIB_COMMON_BE_MULTIPOLE_BE_MULTIPOLE_TRAITS_CXX_HPP__ */
/* end: */
