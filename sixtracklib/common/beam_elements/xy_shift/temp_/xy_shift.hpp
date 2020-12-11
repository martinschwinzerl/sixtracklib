#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_XY_SHIFT_CXX_HPP__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_XY_SHIFT_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/beam_elements/xy_shift/definitions.h"
    #include "sixtracklib/common/beam_elements/xy_shift/xy_shift.h"
    #include "sixtracklib/common/beam_elements/xy_shift/xy_shift_api.h"
    #include "sixtracklib/common/beam_elements/xy_shift/xy_shift_data.hpp"
    #include "sixtracklib/common/beam_elements/xy_shift/xy_shift_data_api.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/internal/obj_base_class.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template< class ObjData, SIXTRL_CXX_NAMESPACE::store_backend_t StoreT >
    class TXYShiftImpl : public ObjDataStorageInterfaceBase<
        ObjData, StoreT, SIXTRL_CXX_NAMESPACE::TXYShiftImpl< ObjData, StoreT > >
    {
        public:
        typedef typename XYShiftTraits< ObjData >::real_t real_t;

        template< typename... Args >
        SIXTRL_FN void init( Args&&... args )
        {
            SIXTRL_CXX_NAMESPACE::XYShift_init(
                this->as_ptr_data(), std::forward< Args >( args )... );
        }

        template< typename DXArg >
        SIXTRL_FN void set_dx( DXArg dx ) SIXTRL_NOEXCEPT
        {
            SIXTRL_CXX_NAMESPACE::XYShift_set_dx( this->as_ptr_data(), dx );
        }

        template< typename DYArg >
        SIXTRL_FN void set_dy( DYArg dy ) SIXTRL_NOEXCEPT
        {
            SIXTRL_CXX_NAMESPACE::XYShift_set_dy( this->as_ptr_data(), dy );
        }
    };
}

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/obj_base_class.hpp"
    #include "sixtracklib/common/beam_elements/xy_shift/xy_shift_cobjects_api.h"
    #include "sixtracklib/common/beam_elements/xy_shift/xy_shift_data_cobjects_api.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template< class R,
        arch_size_t RAlign = SIXTRL_CXX_NAMESPACE::Type_storage_align< R >() >
    using TXYShift = TXYShiftImpl< XYShiftData< R, RAlign >, STORAGE_BE_COBJECTS >;

    typedef TXYShiftImpl< CXYShiftEquivData, STORAGE_BE_COBJECTS > XYShift;
    typedef TXYShiftImpl< ::NS(XYShift),     STORAGE_BE_COBJECTS > CXYShift;
}

#endif /* __cplusplus */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_XY_SHIFT_CXX_HPP__ */
