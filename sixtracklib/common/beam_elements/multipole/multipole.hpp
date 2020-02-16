#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_CXX_HPP__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/beam_elements/multipole/definitions.h"
    #include "sixtracklib/common/beam_elements/multipole/multipole.h"
    #include "sixtracklib/common/beam_elements/multipole/multipole_data.hpp"
    #include "sixtracklib/common/internal/math_factorial.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cstddef>
    #include <cstdlib>
    #include <cmath>
    #include <memory>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/internal/obj_base_class.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template< class ObjData, store_backend_t StoreT >
    class TMultipoleImpl : public ObjDataStorageInterfaceBase<
        ObjData, StoreT, TMultipoleImpl< ObjData, StoreT > >
    {
        public:

        typedef typename MultipoleTraits< ObjData >::real_t         real_t;
        typedef typename MultipoleTraits< ObjData >::order_t        order_t;
        typedef typename MultipoleTraits< ObjData >::address_t      address_t;

        typedef typename TypeMethodParamTraits< real_t >::argument_type
                real_arg_t;

        typedef typename TypeMethodParamTraits< real_t >::const_existing_type
                real_const_existing_t;

        typedef typename TypeMethodParamTraits< order_t >::argument_type
                order_arg_t;

        typedef typename TypeMethodParamTraits< order_t >::const_existing_type
                order_const_existing_t;

        typedef typename TypeMethodParamTraits< address_t >::argument_type
                address_arg_t;

        typedef typename TypeMethodParamTraits< address_t>::const_existing_type
                address_const_existing_t;

        typedef SIXTRL_BE_DATAPTR_DEC real_t const* ptr_const_bal_t;
        typedef SIXTRL_BE_DATAPTR_DEC real_t*       ptr_bal_t;

        order_t num_bal_values() const SIXTRL_NOEXCEPT
        {
            return order_t{ 2 } * this->order + order_t{ 2 };
        }

        ptr_const_bal_t bal_values_begin() const SIXTRL_NOEXCEPT
        {
            return reinterpret_cast< ptr_const_bal_t >( static_cast<
                uintptr_t >( this->bal_addr ) );
        }

        ptr_const_bal_t bal_values_end()   const SIXTRL_NOEXCEPT
        {
            ptr_const_bal_t ptr_end = this->bal_values_begin();

            if( ptr_end != nullptr )
            {
                ptr_end = ptr_end + this->num_bal_values();
            }

            return ptr_end;
        }

        ptr_bal_t const_bal_values_begin() SIXTRL_NOEXCEPT
        {
            typedef TMultipoleImpl< ObjData, StoreT > _this_t;
            return static_cast< _this_t const& >( *this ).bal_values_begin();
        }

        ptr_bal_t const_bal_values_end()   SIXTRL_NOEXCEPT
        {
            typedef TMultipoleImpl< ObjData, StoreT > _this_t;
            return static_cast< _this_t const& >( *this ).bal_values_end();
        }

        ptr_bal_t bal_values_begin() SIXTRL_NOEXCEPT
        {
            return const_cast< ptr_bal_t >( this->const_bal_values_begin() );
        }

        ptr_bal_t bal_values_end() SIXTRL_NOEXCEPT
        {
            return const_cast< ptr_bal_t >( this->const_bal_values_end() );
        }

        real_const_existing_t bal( order_t const ii ) const SIXTRL_NOEXCEPT
        {
            order_t const num_bal_values = this->num_bal_values();
            ptr_const_bal_t ptr_begin = this->bal_values_begin();

            return ( ( ptr_begin != nullptr ) && ( ii < num_bal_values ) )
                        ? ptr_begin[ ii ] : real_t{ 0 };
        }

        void set_bal( order_t const ii, real_arg_t bal_value ) SIXTRL_NOEXCEPT
        {
            order_t const num_bal_values = this->num_bal_values();
            ptr_bal_t ptr_begin = this->bal_values_begin();

            if( ( ptr_begin != nullptr ) && ( ii < num_bal_values ) )
            {
                ptr_begin[ ii ] = bal_value;
            }
        }

        real_t knl( order_t const ii ) const SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            return this->bal( ii ) *
                st::Calc_factorial< real_t, order_t >( ii );
        }

        real_t ksl( order_t const ii ) const SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            return this->bal( ii ) *
                st::Calc_factorial< real_t, order_t >( ii );
        }

        void set_knl( order_t const ii, real_arg_t knl_value )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            this->set_bal( order_t{ 2 } * ii,
                knl_value * st::Calc_inv_factorial< real_t, order_t >( ii ) );
        }

        void set_ksl( order_t const ii, real_arg_t ksl_value )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            this->set_bal( order_t{ 2 } * ii + order_t{ 1 },
                ksl_value * st::Calc_inv_factorial< real_t, order_t >( ii ) );
        }
    };

    /* --------------------------------------------------------------------- */

    template< class E, store_backend_t St > SIXTRL_INLINE SIXTRL_FN
    typename TMultipoleImpl< E, St >::order_const_existing_t Multipole_order(
        SIXTRL_BE_ARGPTR_DEC const TMultipoleImpl< E, St >
            *const SIXTRL_RESTRICT mpole ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( mpole != nullptr );
        return mpole->order;
    }

    template< class E, store_backend_t St > SIXTRL_INLINE SIXTRL_FN
    void Multipole_set_order(
        SIXTRL_BE_ARGPTR_DEC TMultipoleImpl< E, St >* SIXTRL_RESTRICT mpole,
        typename TMultipoleImpl< E, St >::order_arg_t order ) SIXTRL_NOEXCEPT
    {
        if( mpole != nullptr ) mpole->order = order;
    }

    template< class E, store_backend_t St > SIXTRL_INLINE SIXTRL_FN
    typename TMultipoleImpl< E, St >::order_t Multipole_num_bal_values(
        SIXTRL_BE_ARGPTR_DEC const TMultipoleImpl< E, St > *const
            SIXTRL_RESTRICT mpole ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( mpole != nullptr );
        return mpole->num_bal_values();
    }

    /* --------------------------------------------------------------------- */

    template< class E, store_backend_t St > SIXTRL_INLINE SIXTRL_FN
    typename TMultipoleImpl< E, St >::real_const_existing_t Multipole_length(
        SIXTRL_BE_ARGPTR_DEC const TMultipoleImpl< E, St >
            *const SIXTRL_RESTRICT mpole ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( mpole != nullptr );
        return mpole->length;
    }

    template< class E, store_backend_t St > SIXTRL_INLINE SIXTRL_FN
    void Multipole_set_length(
        SIXTRL_BE_ARGPTR_DEC TMultipoleImpl< E, St >* SIXTRL_RESTRICT mpole,
        typename TMultipoleImpl< E, St >::real_arg_t length ) SIXTRL_NOEXCEPT
    {
        if( mpole != nullptr ) mpole->length = length;
    }

    /* --------------------------------------------------------------------- */

    template< class E, store_backend_t St > SIXTRL_INLINE SIXTRL_FN
    typename TMultipoleImpl< E, St >::real_const_existing_t Multipole_hxl(
        SIXTRL_BE_ARGPTR_DEC const TMultipoleImpl< E, St >
            *const SIXTRL_RESTRICT mpole ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( mpole != nullptr );
        return mpole->hxl;
    }

    template< class E, store_backend_t St > SIXTRL_INLINE SIXTRL_FN
    void Multipole_set_hxl(
        SIXTRL_BE_ARGPTR_DEC TMultipoleImpl< E, St >* SIXTRL_RESTRICT mpole,
        typename TMultipoleImpl< E, St >::real_arg_t hxl ) SIXTRL_NOEXCEPT
    {
        if( mpole != nullptr ) mpole->hxl = hxl;
    }

    /* --------------------------------------------------------------------- */

    template< class E, store_backend_t St > SIXTRL_INLINE SIXTRL_FN
    typename TMultipoleImpl< E, St >::real_const_existing_t Multipole_hyl(
        SIXTRL_BE_ARGPTR_DEC const TMultipoleImpl< E, St >
            *const SIXTRL_RESTRICT mpole ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( mpole != nullptr );
        return mpole->hyl;
    }

    template< class E, store_backend_t St > SIXTRL_INLINE SIXTRL_FN
    void Multipole_set_hyl(
        SIXTRL_BE_ARGPTR_DEC TMultipoleImpl< E, St >* SIXTRL_RESTRICT mpole,
        typename TMultipoleImpl< E, St >::real_arg_t hyl ) SIXTRL_NOEXCEPT
    {
        if( mpole != nullptr ) mpole->hyl = hyl;
    }

    /* --------------------------------------------------------------------- */

    template< class E, store_backend_t St > SIXTRL_INLINE SIXTRL_FN
    typename TMultipoleImpl< E, St >::address_const_existing_t
    Multipole_bal_addr( SIXTRL_BE_ARGPTR_DEC const TMultipoleImpl< E, St >
            *const SIXTRL_RESTRICT mpole ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( mpole != nullptr );
        return mpole->bal_addr;
    }

    template< class E, store_backend_t St > SIXTRL_INLINE SIXTRL_FN
    void Multipole_set_bal_addr(
        SIXTRL_BE_ARGPTR_DEC TMultipoleImpl< E, St >* SIXTRL_RESTRICT mpole,
        typename TMultipoleImpl< E, St >::address_arg_t bal_addr
    ) SIXTRL_NOEXCEPT
    {
        if( mpole != nullptr ) mpole->bal_addr = bal_addr;
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    template< class E, store_backend_t St > SIXTRL_INLINE SIXTRL_FN
    typename TMultipoleImpl< E, St >::ptr_const_bal_t
    Multipole_bal_values_begin( SIXTRL_BE_ARGPTR_DEC const
        TMultipoleImpl< E, St > *const SIXTRL_RESTRICT mpole ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( mpole != nullptr );
        return mpole->bal_values_begin();
    }

    template< class E, store_backend_t St > SIXTRL_INLINE SIXTRL_FN
    typename TMultipoleImpl< E, St >::ptr_const_bal_t
    Multipole_const_bal_values_begin(
        SIXTRL_BE_ARGPTR_DEC TMultipoleImpl< E, St >* SIXTRL_RESTRICT mpole
    ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( mpole != nullptr );
        return mpole->const_bal_values_begin();
    }

    template< class E, store_backend_t St > SIXTRL_INLINE SIXTRL_FN
    typename TMultipoleImpl< E, St >::ptr_bal_t
    Multipole_bal_values_begin( SIXTRL_BE_ARGPTR_DEC TMultipoleImpl< E, St >*
        SIXTRL_RESTRICT mpole ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( mpole != nullptr );
        return mpole->bal_values_begin();
    }

    template< class E, store_backend_t St > SIXTRL_INLINE SIXTRL_FN
    typename TMultipoleImpl< E, St >::ptr_const_bal_t
    Multipole_bal_values_end( SIXTRL_BE_ARGPTR_DEC const
        TMultipoleImpl< E, St > *const SIXTRL_RESTRICT mpole ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( mpole != nullptr );
        return mpole->bal_values_end();
    }

    template< class E, store_backend_t St > SIXTRL_INLINE SIXTRL_FN
    typename TMultipoleImpl< E, St >::ptr_const_bal_t
    Multipole_const_bal_values_end(
        SIXTRL_BE_ARGPTR_DEC TMultipoleImpl< E, St >* SIXTRL_RESTRICT mpole
    ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( mpole != nullptr );
        return mpole->const_bal_values_end();
    }

    template< class E, store_backend_t St > SIXTRL_INLINE SIXTRL_FN
    typename TMultipoleImpl< E, St >::ptr_bal_t
    Multipole_bal_values_end( SIXTRL_BE_ARGPTR_DEC TMultipoleImpl< E, St >*
        SIXTRL_RESTRICT mpole ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( mpole != nullptr );
        return mpole->bal_values_end();
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    template< class E, store_backend_t St > SIXTRL_INLINE SIXTRL_FN
    typename TMultipoleImpl< E, St >::real_const_existing_t
    Multipole_bal( SIXTRL_BE_ARGPTR_DEC const TMultipoleImpl< E, St > *const
            SIXTRL_RESTRICT mpole,
        typename TMultipoleImpl< E, St >::order_arg_t ii ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( mpole != nullptr );
        return mpole->bal( ii );
    }

    template< class E, store_backend_t St > SIXTRL_INLINE SIXTRL_FN
    typename TMultipoleImpl< E, St >::real_const_existing_t
    Multipole_knl(
        SIXTRL_BE_ARGPTR_DEC const TMultipoleImpl< E, St > *const
            SIXTRL_RESTRICT mpole,
        typename TMultipoleImpl< E, St >::order_arg_t ii ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( mpole != nullptr );
        return mpole->knl( ii );
    }

    template< class E, store_backend_t St > SIXTRL_INLINE SIXTRL_FN
    typename TMultipoleImpl< E, St >::real_const_existing_t
    Multipole_ksl(
        SIXTRL_BE_ARGPTR_DEC const TMultipoleImpl< E, St > *const
            SIXTRL_RESTRICT mpole,
        typename TMultipoleImpl< E, St >::order_arg_t ii ) SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( mpole != nullptr );
        return mpole->ksl( ii );
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  */

    template< class E, store_backend_t St > SIXTRL_INLINE SIXTRL_FN void
    Multipole_set_bal( SIXTRL_BE_ARGPTR_DEC const TMultipoleImpl< E, St >
            *const SIXTRL_RESTRICT mpole,
        typename TMultipoleImpl< E, St >::order_arg_t ii,
        typename TMultipoleImpl< E, St >::real_arg_t bal_val ) SIXTRL_NOEXCEPT
    {
        if( mpole != nullptr ) mpole->set_bal( ii, bal_val );
    }

    template< class E, store_backend_t St > SIXTRL_INLINE SIXTRL_FN void
    Multipole_set_knl( SIXTRL_BE_ARGPTR_DEC const TMultipoleImpl< E, St >
            *const SIXTRL_RESTRICT mpole,
        typename TMultipoleImpl< E, St >::order_arg_t ii,
        typename TMultipoleImpl< E, St >::real_arg_t knl_val ) SIXTRL_NOEXCEPT
    {
        if( mpole != nullptr ) mpole->set_knl( ii, knl_val );
    }

    template< class E, store_backend_t St > SIXTRL_INLINE SIXTRL_FN void
    Multipole_set_ksl( SIXTRL_BE_ARGPTR_DEC const TMultipoleImpl< E, St >
            *const SIXTRL_RESTRICT mpole,
        typename TMultipoleImpl< E, St >::order_arg_t ii,
        typename TMultipoleImpl< E, St >::real_arg_t ksl_val ) SIXTRL_NOEXCEPT
    {
        if( mpole != nullptr ) mpole->set_ksl( ii, ksl_val );
    }

}

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/obj_base_class.hpp"
    #include "sixtracklib/common/beam_elements/multipole/storage_cobjects.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template< class R, class O,
        arch_size_t RAlign = SIXTRL_CXX_NAMESPACE::Type_storage_align< R >(),
        arch_size_t OAlign = SIXTRL_CXX_NAMESPACE::Type_storage_align< O >(),
        arch_size_t AddrAlign = SIXTRL_CXX_NAMESPACE::Type_storage_align<
            be_address_t >() >
    using TMultipole = TMultipoleImpl<
        MultipoleData< R, O, RAlign, OAlign, AddrAlign >, STORAGE_BE_COBJECTS>;

    typedef TMultipoleImpl<CMultipoleEquivData, STORAGE_BE_COBJECTS> Multipole;
    typedef TMultipoleImpl<::NS(Multipole), STORAGE_BE_COBJECTS>    CMultipole;
}

#endif /* __cplusplus */
#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_DRIFT_CXX_HPP__ */
