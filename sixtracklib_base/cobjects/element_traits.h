#ifndef SIXTRACKLIB_BASE_COBJECTS_ELEMENT_TRAITS_H__
#define SIXTRACKLIB_BASE_COBJECTS_ELEMENT_TRAITS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/cobjects/definitions.h"
    #include "sixtracklib_base/internal/obj_type_id_traits.h"
    #include "sixtracklib_base/internal/obj_data_type_traits.h"
    #include "sixtracklib_base/internal/obj_store_traits.h"
#endif /* SIXTRL_NO_INCLUDES */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class Elem > using CObjElemTypeIdTraits =
        ObjDataTypeIdTraits< Elem, cobj_type_id_t >;

    template< cobj_type_id_t type_id > using CObjElemTypeIdDataTypeMap =
        ObjTypeIdDataTypeMap< cobj_type_id_t, type_id >;

    /* --------------------------------------------------------------------- */

    template< class E, typename... Args > SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
    SIXTRL_CXX_NAMESPACE::status_t CObjElem_init(
        SIXTRL_BUFFER_ARGPTR_DEC E* SIXTRL_RESTRICT obj, Args&&... args )
    {
        return SIXTRL_CXX_NAMESPACE::ObjDataInitialiser<
            E, SIXTRL_CXX_NAMESPACE::STORAGE_BE_COBJECTS >::init(
                obj, std::forward< Args >( args )... );
    }

    template< class E >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN void
    CObjElem_preset( SIXTRL_BUFFER_ARGPTR_DEC E* SIXTRL_RESTRICT obj )
    {
        SIXTRL_CXX_NAMESPACE::ObjDataInitialiser< E,
            SIXTRL_CXX_NAMESPACE::STORAGE_BE_COBJECTS >::preset( obj );
    }

    /* --------------------------------------------------------------------- */

    template< class Elem > static SIXTRL_FN constexpr
    cobj_type_id_t CObjElem_type_id() SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ObjData_type_id< Elem, cobj_type_id_t >();
    }

    template< class Elem > static SIXTRL_FN constexpr bool
    CObjElemTypeId_is_illegal() SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ObjDataTypeId_is_illegal<
            Elem, cobj_type_id_t >();
    }

    template< class Elem > static SIXTRL_FN constexpr bool
    CObjElemTypeId_is_legal() SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ObjDataTypeId_is_legal<
            Elem, cobj_type_id_t >();
    }

    /* --------------------------------------------------------------------- */

    template< class Elem > static SIXTRL_FN constexpr bool
    CObjElem_is_variant() SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ObjDataTypeId_is_variant<
            Elem, cobj_type_id_t >();
    }

    template< class Elem > static SIXTRL_FN constexpr cobj_type_id_t
        CObjElem_variant() SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ObjDataTypeId_variant<
            Elem, cobj_type_id_t >();
    }

    template< class Elem, cobj_type_id_t variant >
    static SIXTRL_FN constexpr cobj_type_id_t
        CObjElem_add_variant() SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ObjDataTypeId_add_variant<
            Elem, cobj_type_id_t, variant >();
    }

    template< class Elem > static SIXTRL_INLINE SIXTRL_FN
    SIXTRL_CXX_NAMESPACE::cobj_type_id_t CObjElem_add_variant(
        SIXTRL_CXX_NAMESPACE::cobj_type_id_t const variant ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ObjDataTypeId_add_variant(
            SIXTRL_CXX_NAMESPACE::CObjElem_type_id< Elem >(), variant );
    }

    template< class Elem > static SIXTRL_FN constexpr
    SIXTRL_CXX_NAMESPACE::cobj_type_id_t CObjElem_remove_variant() SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ObjDataTypeId_remove_variant<
            Elem, cobj_type_id_t >();
    }

    /* --------------------------------------------------------------------- */

    template< class Elem, cobj_type_id_t type_id >
    static SIXTRL_FN constexpr bool Elem_has_type_for_type_id() SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ObjData_has_type_for_type_id<
            Elem, type_id >();
    }

    template< class Elem > static SIXTRL_FN constexpr
    bool Elem_type_traits_consistent() SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ObjData_type_traits_consistent<
            Elem, cobj_type_id_t >();
    }

    /* ===================================================================== */
    /* Specialization of ObjDataDirectStorageTraits for CObjects             */
    /* We can directly store any class that is memcopy-able and has
     * standard layout (i.e. behaves like a C-struct, a.k.a a POD) ->
     * we use the ObjDataCObjects_can_use_storage_backend<>() predicate
     * within the specialization for any ObjData type */

    template< class Elem >
    struct ObjDataDirectStorageTraits< Elem, STORAGE_BE_COBJECTS >
    {
        static SIXTRL_FN constexpr bool CanStore() SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::ObjData_can_be_memcopied< Elem >();
        }
    };

    template< class E > static SIXTRL_FN constexpr bool
        CObjElem_allow_direct_storage() SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::ObjData_allow_direct_storage<
            E, SIXTRL_CXX_NAMESPACE::STORAGE_BE_COBJECTS >();
    }

    template< class Elem >
    using CObjElemDirectStorageTraits =
        ObjDataDirectStorageTraits< Elem, STORAGE_BE_COBJECTS >;
}
#endif /* !defined( __cplusplus ) */
#endif /* SIXTRACKLIB_BASE_COBJECTS_ELEMENT_TRAITS_H__ */
