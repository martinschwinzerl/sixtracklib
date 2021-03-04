#ifndef SIXTRACKLIB_COMMON_BACKENDS_BACKEND_OBJ_BASE_H__
#define SIXTRACKLIB_COMMON_BACKENDS_BACKEND_OBJ_BASE_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/backends/definitions.h"
    #include "sixtracklib/common/backends/backends.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <type_traits>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    class BackendObjBase
    {
        public:

        using backend_id_type = SIXTRL_CXX_NAMESPACE::backend_id_type;
        using class_id_type   = SIXTRL_CXX_NAMESPACE::derived_class_id_type;
        using status_type     = SIXTRL_CXX_NAMESPACE::status_type;
        using size_type       = SIXTRL_CXX_NAMESPACE::size_type;

        SIXTRL_HOST_FN class_id_type base_class_id() const SIXTRL_NOEXCEPT {
            return this->m_base_class_id; }

        SIXTRL_HOST_FN class_id_type derived_class_id() const SIXTRL_NOEXCEPT {
            return this->m_derived_class_id; }

        SIXTRL_HOST_FN backend_id_type backend_id() const SIXTRL_NOEXCEPT {
            return this->m_backend_id; }

        SIXTRL_HOST_FN std::string const& backend_str() const {
            return this->m_backend_str; }

            SIXTRL_HOST_FN char const* backend_cstr() const {
            return this->m_backend_str.c_str(); }

        SIXTRL_HOST_FN size_type required_backend_str_capacity() const {
            return ( !this->m_backend_str.empty() )
                ? this->m_backend_str.size() + size_type{ 1 }
                : size_type{ 0 }; }

        SIXTRL_HOST_FN status_type backend_str(
            char* SIXTRL_RESTRICT str, size_type const str_capacity ) const {
            status_type status = SIXTRL_CXX_NAMESPACE::STATUS_GENERAL_FAILURE;
            if( ( str != nullptr ) && ( str_capacity > size_type{ 0 } ) &&
                ( str_capacity > this->m_backend_str.size() ) )
            {
                std::strncat( str, this->m_backend_str.c_str(),
                              str_capacity - size_type{ 1 } );
                status = SIXTRL_CXX_NAMESPACE::STATUS_SUCCESS;
            }
            return status; }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN virtual ~BackendObjBase() = default;

        protected:

        SIXTRL_HOST_FN BackendObjBase(
            backend_id_type const backend_id,
            class_id_type const base_class_id,
            class_id_type const derived_class_id ) :
            m_backend_str( SIXTRL_CXX_NAMESPACE::Backends_string_by_id(
                backend_id ) ),
            m_backend_id( backend_id ), m_base_class_id( base_class_id ),
            m_derived_class_id( derived_class_id )
        {

        }

        SIXTRL_HOST_FN BackendObjBase( BackendObjBase const& ) = default;
        SIXTRL_HOST_FN BackendObjBase( BackendObjBase&& ) = default;

        SIXTRL_HOST_FN BackendObjBase& operator=( BackendObjBase&& ) = default;
        SIXTRL_HOST_FN BackendObjBase& operator=(
            BackendObjBase const& ) = default;

        SIXTRL_HOST_FN void set_backend_id(
            backend_id_type const id ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void set_base_class_id(
            backend_id_type const id ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN void set_derived_class_id(
            backend_id_type const id ) SIXTRL_NOEXCEPT;

        std::string     m_backend_str;

        backend_id_type m_backend_id;
        class_id_type   m_base_class_id;
        class_id_type   m_derived_class_id;
    };

    /* --------------------------------------------------------------------- */

    template< class Obj >
    struct BackendObjTraits
    {
        static constexpr backend_id_type BACKEND_ID =
            SIXTRL_CXX_NAMESPACE::BACKEND_ID_NONE;

        static constexpr derived_class_id_type BASE_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::DERIVED_CLASS_ID_NONE;

        static constexpr derived_class_id_type DERIVED_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::DERIVED_CLASS_ID_NONE;
    };

    template< class Obj >
    constexpr SIXTRL_CXX_NAMESPACE::backend_id_type
    BackendObjTraits< Obj >::BACKEND_ID;

    template< class Obj >
    constexpr SIXTRL_CXX_NAMESPACE::derived_class_id_type
    BackendObjTraits< Obj >::BASE_CLASS_ID;

    template< class Obj >
    constexpr SIXTRL_CXX_NAMESPACE::derived_class_id_type
    BackendObjTraits< Obj >::DERIVED_CLASS_ID;


    template< SIXTRL_CXX_NAMESPACE::backend_id_type BackendId,
              SIXTRL_CXX_NAMESPACE::derived_class_id_type DerivedClassId >
    struct BackendObjInvTraits
    {
        typedef void backend_obj_type;
    };

    /* --------------------------------------------------------------------- */

    template< class Obj >
    SIXTRL_STATIC SIXTRL_HOST_FN SIXTRL_INLINE constexpr bool
    BackendObj_is_derived_from_base() SIXTRL_NOEXCEPT {
        return std::is_base_of< BackendObjBase, Obj >::value; }

    template< class Obj,
        SIXTRL_CXX_NAMESPACE::backend_id_type TARGET_BACKEND_ID,
        SIXTRL_CXX_NAMESPACE::derived_class_id_type TARGET_DERIVED_CLASS_ID,
        SIXTRL_CXX_NAMESPACE::derived_class_id_type TARGET_BASE_CLASS_ID >
    SIXTRL_STATIC SIXTRL_HOST_FN SIXTRL_INLINE constexpr bool
    BackendObj_is_derived_class() SIXTRL_NOEXCEPT
    {
        return ( TARGET_BACKEND_ID != SIXTRL_CXX_NAMESPACE::BACKEND_ID_NONE ) &&
               ( TARGET_BACKEND_ID == SIXTRL_CXX_NAMESPACE::BackendObjTraits<
                    Obj >::BACKEND_ID ) &&
               ( TARGET_BASE_CLASS_ID !=
                 SIXTRL_CXX_NAMESPACE::DERIVED_CLASS_ID_NONE ) &&
               ( TARGET_BASE_CLASS_ID == SIXTRL_CXX_NAMESPACE::BackendObjTraits<
                    Obj >::BASE_CLASS_ID ) &&
               ( TARGET_DERIVED_CLASS_ID !=
                 SIXTRL_CXX_NAMESPACE::DERIVED_CLASS_ID_NONE ) &&
               ( TARGET_DERIVED_CLASS_ID ==
                 SIXTRL_CXX_NAMESPACE::BackendObjTraits<
                    Obj >::DERIVED_CLASS_ID ) &&
               ( !std::is_void< typename BackendObjInvTraits< TARGET_BACKEND_ID,
                    TARGET_DERIVED_CLASS_ID >::backend_obj_type >::value ) &&
               ( std::is_same< Obj,  typename BackendObjInvTraits<
                    TARGET_BACKEND_ID, TARGET_DERIVED_CLASS_ID
                        >::backend_obj_type >::value );
    }

    /* --------------------------------------------------------------------- */

    template< class BaseT, class DerivedT >
    SIXTRL_STATIC SIXTRL_HOST_FN SIXTRL_INLINE constexpr bool
    BackendObjBase_can_cast_base_to_derived() SIXTRL_NOEXCEPT
    {
        return (
            ( std::is_base_of< BaseT, DerivedT >::value ) &&
            ( BackendObjTraits< BaseT >::BASE_CLASS_ID !=
              SIXTRL_CXX_NAMESPACE::DERIVED_CLASS_ID_NONE ) &&
            ( BackendObjTraits< DerivedT >::BASE_CLASS_ID !=
              SIXTRL_CXX_NAMESPACE::DERIVED_CLASS_ID_NONE ) );
    }

    template< class BaseT, class DerivedT >
    SIXTRL_STATIC SIXTRL_HOST_FN SIXTRL_INLINE bool
    BackendObjBase_is_derived( BaseT const& base_elem ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using traits_t = st::BackendObjTraits< DerivedT >;

        SIXTRL_ASSERT( base_elem.base_class_id() ==
                       st::BackendObjTraits< BaseT >::BASE_CLASS_ID );

        return ( traits_t::BACKEND_ID == base_elem.backend_id() ) &&
               ( traits_t::BASE_CLASS_ID == base_elem.base_class_id() ) &&
               ( traits_t::DERIVED_CLASS_ID == base_elem.derived_class_id() );
    }

    template< class BaseT, class DerivedT >
    SIXTRL_STATIC SIXTRL_HOST_FN SIXTRL_INLINE
    typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::BackendObjBase_can_cast_base_to_derived<
            BaseT, DerivedT >(), DerivedT const* >::type
    BackendObjBase_cast_to_derived(
        const BaseT *const SIXTRL_RESTRICT ptr ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return ( ( ptr != nullptr ) &&
                 ( st::BackendObjBase_is_derived< BaseT, DerivedT >( *ptr ) ) )
            ? static_cast< DerivedT const* >( ptr ) : nullptr;
    }

    template< class BaseT, class DerivedT >
    SIXTRL_STATIC SIXTRL_HOST_FN SIXTRL_INLINE
    typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::BackendObjBase_can_cast_base_to_derived<
            BaseT, DerivedT >(), DerivedT const* >::type
    BackendObjBase_cast_to_derived(
        const BaseT *const SIXTRL_RESTRICT SIXTRL_UNUSED( ptr ) ) SIXTRL_NOEXCEPT
    {
        return nullptr;
    }

    template< class BaseT, class DerivedT >
    SIXTRL_STATIC SIXTRL_HOST_FN SIXTRL_INLINE DerivedT const*
    BackendObjBase_cast_to_const_derived( BaseT* SIXTRL_RESTRICT ptr
        ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return st::BackendObjBase_cast_to_derived< BaseT, DerivedT >(
            static_cast< BaseT const* >( ptr ) );
    }

    template< class BaseT, class DerivedT >
    SIXTRL_STATIC SIXTRL_HOST_FN SIXTRL_INLINE DerivedT*
    BackendObjBase_cast_to_derived( BaseT* SIXTRL_RESTRICT ptr ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        return const_cast< DerivedT* >( st::BackendObjBase_cast_to_const_derived<
            BaseT, DerivedT >( ptr ) );
    }

} /* end: namespace SIXTRL_CXX_NAMESPACE */
#endif /* C++, Host */
#endif /* SIXTRACKLIB_COMMON_BACKENDS_BACKEND_OBJ_BASE_H__ */
