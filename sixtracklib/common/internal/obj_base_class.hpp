#ifndef SIXTRACKLIB_COMMON_INTERNAL_OBJ_BASE_CLASS_CXX_HPP__
#define SIXTRACKLIB_COMMON_INTERNAL_OBJ_BASE_CLASS_CXX_HPP__

#if defined( __cplusplus )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cstdlib>
    #include <type_traits>
    #if !defined( _GPUCODE )
        #include <vector>
    #endif /* !defiend( _GPUCODE ) */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/internal/obj_type_id_traits.hpp"
    #include "sixtracklib/common/internal/obj_c_api_traits.hpp"
    #include "sixtracklib/common/internal/obj_data_type_traits.hpp"
    #include "sixtracklib/common/internal/obj_store_traits.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template< class ObjData, typename TypeIdT, class Derived = void >
    class ObjDataInterfaceBase : public ObjData
    {
        public:

        typedef TypeIdT type_id_t;

        private:

        typedef SIXTRL_CXX_NAMESPACE::ObjDataInterfaceBase<
                    ObjData, TypeIdT, Derived > _this_t;

        typedef SIXTRL_CXX_NAMESPACE::ObjDataTypeIdTraits< ObjData, type_id_t >
                _obj_type_traits_t;

        typedef SIXTRL_CXX_NAMESPACE::ObjDataCApiTypeTraits< ObjData >
                _c_api_traits_t;

        typedef SIXTRL_CXX_NAMESPACE::ObjTypeIdTraits< type_id_t >
                _type_id_traits_t;

        typedef SIXTRL_CXX_NAMESPACE::TypeIdOperations< type_id_t >
                _type_id_operations_t;

        public:

        typedef ObjData                             cxx_api_t;
        typedef ObjData                             obj_data_t;
        typedef typename _c_api_traits_t::c_api_t   c_api_t;
        typedef SIXTRL_CXX_NAMESPACE::arch_size_t   size_type;
        typedef SIXTRL_CXX_NAMESPACE::arch_status_t status_t;

        /* ----------------------------------------------------------------- */

        static constexpr type_id_t ILLEGAL_TYPE_ID =
            _type_id_operations_t::IllegalTypeId();

        /* ----------------------------------------------------------------- */

        SIXTRL_FN ObjDataInterfaceBase() = default;
        SIXTRL_FN ObjDataInterfaceBase( ObjDataInterfaceBase<
            ObjData, TypeIdT, Derived > const& ) = default;

        template< typename Arg=ObjData, typename... Args, typename std::enable_if<
            std::is_constructible< ObjData, Arg, Args... >::value &&
            !std::is_same< typename std::decay< Arg >::type, ObjData >::value,
            int >::type = 0 >
        SIXTRL_FN ObjDataInterfaceBase( Arg&& other, Args&&... args ) :
            ObjData( std::forward< Arg >( other ),
                     std::forward< Args >( args )... )
        {

        }

        SIXTRL_FN ObjDataInterfaceBase< ObjData, TypeIdT, Derived >& operator=(
            ObjDataInterfaceBase< ObjData, TypeIdT, Derived >
                const& ) = default;

        SIXTRL_FN ObjDataInterfaceBase< ObjData, TypeIdT, Derived >& operator=(
            ObjDataInterfaceBase< ObjData, TypeIdT, Derived >&& ) = default;

        protected:

        SIXTRL_FN ~ObjDataInterfaceBase() = default;

        public:

        /* ----------------------------------------------------------------- */

        SIXTRL_FN cxx_api_t const& as_const_data() SIXTRL_NOEXCEPT
        {
            return static_cast< cxx_api_t const& >( *this );
        }

        SIXTRL_FN cxx_api_t const& as_data() const SIXTRL_NOEXCEPT
        {
            return static_cast< cxx_api_t const& >( *this );
        }

        SIXTRL_FN cxx_api_t& as_data() SIXTRL_NOEXCEPT
        {
            return static_cast< cxx_api_t& >( *this );
        }

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

        SIXTRL_FN cxx_api_t* as_ptr_data() SIXTRL_NOEXCEPT
        {
            return static_cast< cxx_api_t const* >( this );
        }

        SIXTRL_FN cxx_api_t const* as_ptr_data() const SIXTRL_NOEXCEPT
        {
            return static_cast< cxx_api_t const* >( this );
        }

        SIXTRL_FN cxx_api_t const* as_ptr_const_data() SIXTRL_NOEXCEPT
        {
            return static_cast< cxx_api_t const* >( this );
        }

        /* ----------------------------------------------------------------- */

        static SIXTRL_FN constexpr type_id_t type_id() SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ObjData_type_id<
                ObjData, type_id_t >();
        }

        static SIXTRL_FN constexpr bool is_type_id_illegal() SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ObjDataTypeId_is_illegal<
                ObjData, type_id_t >();
        }

        static SIXTRL_FN constexpr bool is_type_id_variant() SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ObjDataTypeId_is_variant<
                ObjData, type_id_t >();
        }

        static SIXTRL_FN constexpr type_id_t type_id_variant() SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ObjDataTypeId_variant<
                ObjData, type_id_t >();
        }

        /* ----------------------------------------------------------------- */

        static SIXTRL_FN constexpr
        bool is_convertible_to_c_api() SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ObjData_has_c_api_type< ObjData >();
        }

        static SIXTRL_FN constexpr
        bool is_not_convertible_to_c_api() SIXTRL_NOEXCEPT
        {
            return !SIXTRL_CXX_NAMESPACE::ObjData_has_c_api_type< ObjData >();
        }

        SIXTRL_INLINE SIXTRL_FN c_api_t const*
        as_ptr_c_api() const SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ObjData_bitcast_to_const_c_api<
                ObjData >( this->as_ptr_data() );
        }

        SIXTRL_INLINE SIXTRL_FN c_api_t* as_ptr_c_api() SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ObjData_bitcast_to_c_api<
                ObjData >( this->as_ptr_data() );
        }

        SIXTRL_INLINE SIXTRL_FN c_api_t const*
        as_ptr_const_c_api() SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ObjData_bitcast_to_const_c_api<
                ObjData >( this->as_ptr_const_data() );
        }
    };

    template< class ObjData, SIXTRL_CXX_NAMESPACE::store_backend_t StoreT,
              class Derived >
    class ObjDataStorageInterfaceBase : public ObjDataInterfaceBase< ObjData,
        typename StorageBackendTraits< StoreT >::type_id_t, Derived >
    {
        private:

        typedef SIXTRL_CXX_NAMESPACE::StorageBackendTraits< StoreT >
                _storage_be_traits_t;

        typedef SIXTRL_CXX_NAMESPACE::ObjDataInterfaceBase< ObjData,
            typename _storage_be_traits_t::type_id_t, Derived > _base_t;

        typedef SIXTRL_CXX_NAMESPACE::ObjDataStorageInterfaceBase<
            ObjData, StoreT, Derived > _this_t;

        public:

        typedef SIXTRL_CXX_NAMESPACE::store_backend_t   store_backend_t;
        typedef typename _base_t::type_id_t             type_id_t;
        typedef typename _base_t::cxx_api_t             cxx_api_t;
        typedef typename _base_t::c_api_t               c_api_t;
        typedef typename _base_t::size_type             size_type;

        using _base_t::ObjDataInterfaceBase;
        using _base_t::operator=;

        static constexpr store_backend_t STORAGE_BACKEND = StoreT;
    };

    template< class Derived,
              store_backend_t StoreT, typename _Enabled = void  >
    struct IsObjDataStorageInterfaceTraits
    {
        static SIXTRL_FN constexpr bool is_interface() SIXTRL_NOEXCEPT
        {
            return false;
        }
    };

    template< class Derived,
              store_backend_t StoreT, typename _Enabled = void >
    struct ObjDataDerivedStorageTraits
    {
        static SIXTRL_FN constexpr bool allow_derived_storage() SIXTRL_NOEXCEPT
        {
            return false;
        }
    };
}

#endif /* __cplusplus */

#endif /* SIXTRACKLIB_COMMON_INTERNAL_OBJ_BASE_CLASS_CXX_HPP__ */