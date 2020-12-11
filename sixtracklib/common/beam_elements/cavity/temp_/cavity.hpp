#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_CXX_HPP__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/beam_elements/cavity/definitions.h"
    #include "sixtracklib/common/beam_elements/cavity/cavity.h"
    #include "sixtracklib/common/beam_elements/cavity/cavity_api.h"
    #include "sixtracklib/common/beam_elements/cavity/cavity_data.hpp"
    #include "sixtracklib/common/beam_elements/cavity/cavity_data_api.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/internal/obj_base_class.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template< class ObjData, SIXTRL_CXX_NAMESPACE::store_backend_t StoreT >
    class TCavityImpl : public ObjDataStorageInterfaceBase<
        ObjData, StoreT, SIXTRL_CXX_NAMESPACE::TCavityImpl< ObjData, StoreT > >
    {
        public:
        typedef typename CavityTraits< ObjData >::real_t real_t;

        template< typename... Args >
        SIXTRL_FN void init( Args&&... args )
        {
            SIXTRL_CXX_NAMESPACE::Cavity_init(
                this->as_ptr_data(), std::forward< Args >( args )... );
        }

        template< typename VoltageArg >
        SIXTRL_FN void set_length( VoltageArg voltage )
        {
            SIXTRL_CXX_NAMESPACE::Cavity_set_voltage(
                this->as_ptr_data(), voltage );
        }

        template< typename FrequArg >
        SIXTRL_FN void set_frequency( FrequArg frequency )
        {
            SIXTRL_CXX_NAMESPACE::Cavity_set_frequency(
                this->as_ptr_data(), frequency );
        }

        template< typename LagArg >
        SIXTRL_FN void set_lag( LagArg lag )
        {
            SIXTRL_CXX_NAMESPACE::Cavity_set_lag( this->as_ptr_data(), lag );
        }
    };
}

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/obj_base_class.hpp"
    #include "sixtracklib/common/beam_elements/cavity/cavity_cobjects_api.h"
    #include "sixtracklib/common/beam_elements/cavity/cavity_data_cobjects_api.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template< class R,
        arch_size_t RAlign = SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
    using TCavity = TCavityImpl< CavityData< R, RAlign >, STORAGE_BE_COBJECTS >;

    typedef TCavityImpl< CCavityEquivData, STORAGE_BE_COBJECTS > Cavity;
    typedef TCavityImpl< ::NS(Cavity),     STORAGE_BE_COBJECTS > CCavity;
}

#endif /* __cplusplus */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_CAVITY_CXX_HPP__ */
