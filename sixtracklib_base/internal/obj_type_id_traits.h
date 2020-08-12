#ifndef SIXTRACKLIB_BASE_INTERNAL_OBJ_TYPE_ID_TRAITS_H__
#define SIXTRACKLIB_BASE_INTERNAL_OBJ_TYPE_ID_TRAITS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/definitions.h"
    #include "sixtracklib_base/internal/base_types.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <algorithm>
        #include <cstdlib>
        #include <limits>
        #include <vector>
        #include <type_traits>
    #endif /* C++ */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< typename TypeIdType, typename _Enable = void >
    struct SIXTRL_BASE_EXPORT_API ObjTypeIdTraits;

    template< typename TypeIdType >
    struct SIXTRL_BASE_EXPORT_API ObjTypeIdTraits< TypeIdType, typename
        std::enable_if< std::numeric_limits< TypeIdType >::is_integer >::type >
    {
        typedef TypeIdType  type_id_t;

        static SIXTRL_FN constexpr type_id_t
        BaseTypeEncodeBitmask() SIXTRL_NOEXCEPT
        {
            return static_cast< type_id_t >( 0x0000ffff );
        }

        static SIXTRL_FN constexpr type_id_t
        BaseTypeDecodeBitmask() SIXTRL_NOEXCEPT
        {
            return static_cast< type_id_t >( 0x0000ffff );
        }

        static SIXTRL_FN constexpr type_id_t BaseTypeNumBits() SIXTRL_NOEXCEPT
        {
            return static_cast< type_id_t >( 16 );
        }

        static SIXTRL_FN constexpr type_id_t
        VariantDecodeBitMask() SIXTRL_NOEXCEPT
        {
            return static_cast< type_id_t >( 0x3fff0000 );
        }

        static SIXTRL_FN constexpr type_id_t
        VariantEncodeBitMask() SIXTRL_NOEXCEPT
        {
            return static_cast< type_id_t >( 0x00003fff );
        }

        static SIXTRL_FN constexpr type_id_t VariantNumBits() SIXTRL_NOEXCEPT
        {
            return static_cast< type_id_t >( 14 );
        }

        static SIXTRL_FN constexpr type_id_t
        IllegalTypeVariant() SIXTRL_NOEXCEPT
        {
            return static_cast< TypeIdType >( 0x40000000 );
        }

        static SIXTRL_FN constexpr type_id_t
        IllegalTypeNumBits() SIXTRL_NOEXCEPT
        {
            return static_cast< TypeIdType >( 1 );
        }
    };

    /* --------------------------------------------------------------------- */

    template< class TypeIdTypeTraits, typename _Enable = void >
    struct SIXTRL_BASE_EXPORT_API GenericTypeIdOperations
    {
        static_assert( 1 != 0, "Should never get here" );
    };

    template< class TypeIdTypeTraits >
    struct SIXTRL_BASE_EXPORT_API GenericTypeIdOperations< TypeIdTypeTraits,
        typename std::enable_if<
            std::numeric_limits< typename TypeIdTypeTraits::type_id_t
                >::is_integer &&
            std::numeric_limits< typename TypeIdTypeTraits::type_id_t
                >::digits >= ( TypeIdTypeTraits::BaseTypeNumBits() +
                               TypeIdTypeTraits::VariantNumBits() +
                               TypeIdTypeTraits::IllegalTypeNumBits() ),
            typename TypeIdTypeTraits::type_id_t >::type >
    {
        private:

        typedef TypeIdTypeTraits                        type_id_traits_t;
        typedef typename type_id_traits_t::type_id_t    type_id_t;

        public:

        static SIXTRL_FN constexpr type_id_t min_type_id() SIXTRL_NOEXCEPT
        {
            return static_cast< type_id_t >( 0 );
        }

        static SIXTRL_FN constexpr type_id_t max_type_id() SIXTRL_NOEXCEPT
        {
            return std::numeric_limits< type_id_t >::max &
                type_id_traits_t::BaseTypeEncodeBitmask();
        }

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        static SIXTRL_FN constexpr type_id_t min_variant() SIXTRL_NOEXCEPT
        {
            return static_cast< type_id_t >( 0 );
        }

        static SIXTRL_FN constexpr type_id_t max_variant() SIXTRL_NOEXCEPT
        {
            return std::numeric_limits< type_id_t >::max() &
                type_id_traits_t::VariantEncodeBitMask();
        }

        template< type_id_t type_id >
        static SIXTRL_FN constexpr bool is_variant() SIXTRL_NOEXCEPT
        {
            return ( type_id_traits_t::VariantDecodeBitMask() & type_id ) !=
                     type_id_t{ 0 };
        }

        static SIXTRL_INLINE SIXTRL_FN bool is_variant(
            type_id_t const type_id ) SIXTRL_NOEXCEPT
        {
            return ( type_id_traits_t::VariantDecodeBitMas() & type_id ) !=
                     type_id_t{ 0 };
        }

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        template< type_id_t type_id >
        static SIXTRL_FN constexpr type_id_t variant() SIXTRL_NOEXCEPT
        {
            return ( type_id_traits_t::VariantDecodeBitMask() & type_id ) >>
                     type_id_traits_t::BaseTypeNumBits();
        }

        static SIXTRL_INLINE SIXTRL_FN type_id_t variant(
            type_id_t const type_id ) SIXTRL_NOEXCEPT
        {
            return ( type_id_traits_t::VariantDecodeBitMask() & type_id ) >>
                     type_id_traits_t::BaseTypeNumBits();
        }

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        template< type_id_t variant_type_id >
        static SIXTRL_FN constexpr type_id_t remove_variant() SIXTRL_NOEXCEPT
        {
            return ( type_id_traits_t::BaseTypeDecodeBitmask() &
                     variant_type_id );
        }

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        static SIXTRL_FN constexpr type_id_t IllegalTypeId() SIXTRL_NOEXCEPT
        {
            return type_id_traits_t::VariantDecodeBitMask() |
                   type_id_traits_t::IllegalTypeVariant()   |
                   type_id_traits_t::BaseTypeEncodeBitmask();
        }

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        template< type_id_t type_id >
        static SIXTRL_FN constexpr bool is_illegal() SIXTRL_NOEXCEPT
        {
            return ( type_id_traits_t::IllegalTypeVariant() & type_id ) ==
                     type_id_traits_t::IllegalTypeVariant();
        }

        template< type_id_t type_id >
        static SIXTRL_FN constexpr bool is_legal() SIXTRL_NOEXCEPT
        {
            return ( type_id_traits_t::IllegalTypeVariant() & type_id ) !=
                     type_id_traits_t::IllegalTypeVariant();
        }

        static SIXTRL_INLINE SIXTRL_FN bool is_illegal(
            type_id_t const type_id ) SIXTRL_NOEXCEPT
        {
            return ( type_id_traits_t::IllegalTypeVariant() & type_id ) ==
                     type_id_traits_t::IllegalTypeVariant();
        }

        static SIXTRL_INLINE SIXTRL_FN bool is_legal(
            type_id_t const type_id ) SIXTRL_NOEXCEPT
        {
            return ( type_id_traits_t::IllegalTypeVariant() & type_id ) ==
                     type_id_traits_t::IllegalTypeVariant();
        }

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        template< type_id_t base, type_id_t variant >
        static SIXTRL_FN constexpr type_id_t add_variant() SIXTRL_NOEXCEPT
        {
            return ( !is_illegal< base >() )
                 ? ( ( ( type_id_traits_t::VariantEncodeBitMask() & variant )
                            << type_id_traits_t::BaseTypeNumBits() ) |
                     ( type_id_traits_t::BaseTypeEncodeBitmask() & base ) )
                 : IllegalTypeId();
        }

        static SIXTRL_INLINE SIXTRL_FN type_id_t add_variant(
            type_id_t const base, type_id_t const variant ) SIXTRL_NOEXCEPT
        {
            return ( !is_illegal( base ) )
                 ? ( ( ( type_id_traits_t::VariantEncodeBitMask() & variant )
                            << type_id_traits_t::BaseTypeNumBits() ) |
                     ( type_id_traits_t::BaseTypeEncodeBitmask() & base ) )
                 : type_id_traits_t::IllegalTypeId();
        }
    };

    template< typename TypeIdT >
    using TypeIdOperations = SIXTRL_CXX_NAMESPACE::GenericTypeIdOperations<
        SIXTRL_CXX_NAMESPACE::ObjTypeIdTraits< TypeIdT >, TypeIdT >;

    template< typename TypeIdT > static SIXTRL_FN constexpr TypeIdT
    ObjTypeId_illegal_type_id() SIXTRL_NOEXCEPT
    {
        return TypeIdOperations< TypeIdT >::IllegalTypeId();
    }

    template< typename TypeIdT, TypeIdT type_id >
    static SIXTRL_FN constexpr bool ObjTypeId_is_illegal() SIXTRL_NOEXCEPT
    {
        return TypeIdOperations< TypeIdT >::template is_illegal< type_id >();
    }

    template< typename TypeIdT, TypeIdT type_id >
    static SIXTRL_FN constexpr bool ObjTypeId_is_legal() SIXTRL_NOEXCEPT
    {
        return TypeIdOperations< TypeIdT >::template is_legal< type_id >();
    }

    template< typename TypeIdT > static SIXTRL_FN constexpr TypeIdT
    ObjTypeId_max_type_id() SIXTRL_NOEXCEPT
    {
        return TypeIdOperations< TypeIdT >::max_type_id();
    }

    template< typename TypeIdT > static SIXTRL_FN constexpr TypeIdT
    ObjTypeId_min_type_id() SIXTRL_NOEXCEPT
    {
        return TypeIdOperations< TypeIdT >::min_type_id();
    }

    template< typename TypeIdT > static SIXTRL_FN constexpr TypeIdT
    ObjTypeId_min_variant() SIXTRL_NOEXCEPT
    {
        return TypeIdOperations< TypeIdT >::min_variant();
    }

    template< typename TypeIdT > static SIXTRL_FN constexpr TypeIdT
    ObjTypeId_max_variant() SIXTRL_NOEXCEPT
    {
        return TypeIdOperations< TypeIdT >::max_variant();
    }

    template< typename TypeIdT, TypeIdT type_id >
    static SIXTRL_FN constexpr bool ObjTypeId_is_variant() SIXTRL_NOEXCEPT
    {
        return TypeIdOperations< TypeIdT >::template is_variant< type_id >();
    }

    template< typename TypeIdT, TypeIdT type_id >
    static SIXTRL_FN constexpr TypeIdT ObjTypeId_variant() SIXTRL_NOEXCEPT
    {
        return TypeIdOperations< TypeIdT >::template variant< type_id >();
    }

    template< typename TypeIdT, TypeIdT type_id, TypeIdT variant >
    static SIXTRL_FN constexpr TypeIdT ObjTypeId_add_variant() SIXTRL_NOEXCEPT
    {
        return TypeIdOperations<
            TypeIdT >::template add_variant< type_id, variant >();
    }

    template< typename TypeIdT >
    static SIXTRL_INLINE SIXTRL_FN TypeIdT ObjTypeId_add_variant(
        TypeIdT const type_id, TypeIdT const variant ) SIXTRL_NOEXCEPT
    {
        return TypeIdOperations< TypeIdT >::add_variant( type_id, variant );
    }

    template< typename TypeIdT, TypeIdT variant_type_id >
    static SIXTRL_FN constexpr TypeIdT ObjTypeId_remove_variant() SIXTRL_NOEXCEPT
    {
        return TypeIdOperations< TypeIdT >::template remove_variant<
            variant_type_id >();
    }

    template< typename TypeIdT > static SIXTRL_INLINE SIXTRL_FN TypeIdT
    ObjTypeId_remove_variant( TypeIdT const variant_type_id ) SIXTRL_NOEXCEPT
    {
        return TypeIdOperations< TypeIdT >::remove_variant( variant_type_id );
    }
}

#endif /* __cplusplus */
#endif /* SIXTRACKLIB_BASE_INTERNAL_OBJ_TYPE_ID_TRAITS_H__ */
