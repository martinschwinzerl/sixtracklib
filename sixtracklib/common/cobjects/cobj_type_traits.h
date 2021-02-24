#ifndef SIXTRACKLIB_COMMON_COBJECTS_COBJ_TYPE_TRAITS_CXX_HPP__
#define SIXTRACKLIB_COMMON_COBJECTS_COBJ_TYPE_TRAITS_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/cobjects/cobj_illegal_type.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <type_traits>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< class E >
    SIXTRL_FN static constexpr cobj_obj_id_type CObjects_type_id(
        ) SIXTRL_NOEXCEPT { return CObjectsTraits< E >::TYPE_ID; }

    template< class E >
    SIXTRL_FN static constexpr bool CObjects_has_illegal_id() SIXTRL_NOEXCEPT {
        return ( SIXTRL_CXX_NAMESPACE::CObjects_type_id< E >() ==
                 SIXTRL_CXX_NAMESPACE::COBJECTS_TYPE_ID_ILLEGAL ) ||
               ( SIXTRL_CXX_NAMESPACE::CObjects_type_id< E >() ==
                 SIXTRL_CXX_NAMESPACE::COBJECTS_TYPE_ID_UNDEFINED ); }

    template< class E >
    SIXTRL_FN static constexpr bool CObjects_has_legal_id() SIXTRL_NOEXCEPT {
        return !SIXTRL_CXX_NAMESPACE::CObjects_has_illegal_id< E >(); }

    template< class E >
    SIXTRL_FN static constexpr bool CObjects_is_legal_type() SIXTRL_NOEXCEPT {
        return SIXTRL_CXX_NAMESPACE::CObjects_has_legal_id< E >(); }

    /* ---------------------------------------------------------------------- */

    template< class E >
    SIXTRL_FN static constexpr cobj_size_type
    CObjects_num_pointers() SIXTRL_NOEXCEPT { return
        SIXTRL_CXX_NAMESPACE::CObjectsNumPointersTraits< E >::NUM_POINTERS; }

    /* ---------------------------------------------------------------------- */

    template< class E >
    SIXTRL_FN static constexpr bool
    CObjects_has_trivial_handle_size() SIXTRL_NOEXCEPT {
        return SIXTRL_CXX_NAMESPACE::CObjectsTrivialHandleSizeTraits<
            E >::HAS_TRIVIAL_HANDLE_SIZE; }

    /* ---------------------------------------------------------------------- */

    template< class E >
    SIXTRL_FN static typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::CObjects_is_legal_type< E >(),
        SIXTRL_CXX_NAMESPACE::cobj_size_type >::type
    CObjects_actual_handle_size(
        SIXTRL_CXX_NAMESPACE::cobj_size_type const SIXTRL_UNUSED( slot_size ) =
            SIXTRL_CXX_NAMESPACE::cobj_size_type{ SIXTRL_DEFAULT_ALIGN },
        SIXTRL_CBUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( ptr ) = nullptr ) SIXTRL_NOEXCEPT {
        return SIXTRL_CXX_NAMESPACE::cobj_size_type{ 0 }; }

    template< class E >
    SIXTRL_FN static typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjects_is_legal_type< E >(),
        SIXTRL_CXX_NAMESPACE::cobj_size_type >::type
    CObjects_actual_handle_size(
        SIXTRL_CXX_NAMESPACE::cobj_size_type const slot_size =
            SIXTRL_CXX_NAMESPACE::cobj_size_type{ SIXTRL_DEFAULT_ALIGN },
        SIXTRL_CBUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( ptr ) = nullptr ) SIXTRL_NOEXCEPT {
        return SIXTRL_CXX_NAMESPACE::CObjectsActualHandleSizeTraits<
            E >::HANDLE_SIZE( slot_size ); }

    /* ---------------------------------------------------------------------- */

    template< class E >
    SIXTRL_FN static typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::CObjects_is_legal_type< E >(),
        SIXTRL_CXX_NAMESPACE::cobj_size_type >::type
    CObjects_reserved_handle_size(
        SIXTRL_CXX_NAMESPACE::cobj_size_type const SIXTRL_UNUSED( slot_size ) =
            SIXTRL_CXX_NAMESPACE::cobj_size_type{ SIXTRL_DEFAULT_ALIGN },
        SIXTRL_CBUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( ptr ) = nullptr ) SIXTRL_NOEXCEPT{
        return SIXTRL_CXX_NAMESPACE::cobj_size_type{ 0 }; }

    template< class E >
    SIXTRL_FN static typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::CObjects_is_legal_type< E >(),
        SIXTRL_CXX_NAMESPACE::cobj_size_type >::type
    CObjects_reserved_handle_size(
        SIXTRL_CXX_NAMESPACE::cobj_size_type const slot_size =
            SIXTRL_CXX_NAMESPACE::cobj_size_type{ SIXTRL_DEFAULT_ALIGN },
        SIXTRL_CBUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( ptr ) = nullptr ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_ASSERT( slot_size > st::cobj_size_type{ 0 } );

        SIXTRL_ASSERT(
            ( ( st::CObjects_has_trivial_handle_size< E >() ) &&
              ( st::CObjects_actual_handle_size< E >( slot_size ) ==
                st::CObjectsReservedHandleSizeTraits<
                    E >::HANDLE_SIZE( slot_size ) ) ) ||
            ( ( !st::CObjects_has_trivial_handle_size< E >() ) &&
              ( st::CObjects_actual_handle_size< E >( slot_size ) <
                st::CObjectsReservedHandleSizeTraits<
                    E >::HANDLE_SIZE( slot_size ) ) ) );

        return st::CObjectsReservedHandleSizeTraits<
            E >::HANDLE_SIZE( slot_size );
    }

    /* --------------------------------------------------------------------- */

    template< class E >
    SIXTRL_FN static constexpr bool CObjects_is_trivial_type() SIXTRL_NOEXCEPT {
        return (
            ( SIXTRL_CXX_NAMESPACE::CObjects_has_legal_id< E >() ) &&
            ( SIXTRL_CXX_NAMESPACE::CObjects_num_pointers< E >() ==
              SIXTRL_CXX_NAMESPACE::cobj_size_type{ 0 } ) &&
            ( SIXTRL_CXX_NAMESPACE::CObjects_has_trivial_handle_size< E >() )
        ); }

    template< class E >
    SIXTRL_FN static constexpr bool
    CObjects_is_non_trivial_type() SIXTRL_NOEXCEPT { return (
            (  SIXTRL_CXX_NAMESPACE::CObjects_has_legal_id< E >() ) &&
            ( !SIXTRL_CXX_NAMESPACE::CObjects_is_trivial_type< E >() ) ); }

    /* ---------------------------------------------------------------------- */

    template< class E >
    SIXTRL_FN static typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::CObjects_is_legal_type< E >(),
         SIXTRL_CXX_NAMESPACE::cobj_size_type >::type
    CObjects_required_num_bytes(
        SIXTRL_CBUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( ptr ) = nullptr,
        SIXTRL_CXX_NAMESPACE::cobj_size_type const SIXTRL_UNUSED( slot_size ) =
            SIXTRL_CXX_NAMESPACE::cobj_size_type{ SIXTRL_DEFAULT_ALIGN }
         ) SIXTRL_NOEXCEPT {
        return SIXTRL_CXX_NAMESPACE::cobj_size_type{ 0 }; }

    template< class E >
    SIXTRL_FN static typename std::enable_if<
         SIXTRL_CXX_NAMESPACE::CObjects_is_trivial_type< E >(),
         SIXTRL_CXX_NAMESPACE::cobj_size_type >::type
    CObjects_required_num_bytes(
        SIXTRL_CBUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( ptr ) = nullptr,
        SIXTRL_CXX_NAMESPACE::cobj_size_type const slot_size =
            SIXTRL_CXX_NAMESPACE::cobj_size_type{ SIXTRL_DEFAULT_ALIGN }
         ) SIXTRL_NOEXCEPT {
        return SIXTRL_CXX_NAMESPACE::CObjects_reserved_handle_size<
            E >( slot_size ); }

    template< class E >
    SIXTRL_FN static typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::CObjects_is_trivial_type< E >(),
         SIXTRL_CXX_NAMESPACE::cobj_size_type >::type
    CObjects_required_num_bytes(
        SIXTRL_CBUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT ptr = nullptr,
        SIXTRL_CXX_NAMESPACE::cobj_size_type const slot_size =
            SIXTRL_CXX_NAMESPACE::cobj_size_type{ SIXTRL_DEFAULT_ALIGN }
         ) SIXTRL_NOEXCEPT {
        return SIXTRL_CXX_NAMESPACE::CObjectsRequiredNumBytesTraits<
            E >::REQUIRED_NUM_BYTES( ptr, slot_size ); }

    /* ---------------------------------------------------------------------- */

    template< class E >
    SIXTRL_FN static typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::CObjects_is_legal_type< E >(),
         SIXTRL_CXX_NAMESPACE::cobj_status_type >::type
    CObjects_attribute_offsets(
        SIXTRL_ARGPTR_DEC cobj_size_type* SIXTRL_RESTRICT
            SIXTRL_UNUSED( offsets_begin ),
        cobj_size_type const SIXTRL_UNUSED( max_num_offsets ),
        SIXTRL_CBUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( ptr ),
        cobj_size_type const SIXTRL_UNUSED( slot_size ) =
            cobj_size_type{ SIXTRL_DEFAULT_ALIGN } ) SIXTRL_NOEXCEPT {
        return SIXTRL_CXX_NAMESPACE::STATUS_GENERAL_FAILURE; }

    template< class E >
    SIXTRL_FN static typename std::enable_if<
         SIXTRL_CXX_NAMESPACE::CObjects_is_legal_type< E >(),
         SIXTRL_CXX_NAMESPACE::cobj_size_type >::type
    CObjects_attribute_offsets(
        SIXTRL_ARGPTR_DEC cobj_size_type* SIXTRL_RESTRICT offsets_begin,
        cobj_size_type const max_num_offsets,
        SIXTRL_CBUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT ptr,
        cobj_size_type const slot_size = cobj_size_type{ SIXTRL_DEFAULT_ALIGN }
        ) SIXTRL_NOEXCEPT {
        return CObjectsAttributesOffsetsTraits< E >::GET(
            offsets_begin, max_num_offsets, ptr, slot_size ); }

    /* --------------------------------------------------------------------- */

    template< class E >
    SIXTRL_FN static typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::CObjects_is_legal_type< E >(),
         SIXTRL_CXX_NAMESPACE::cobj_status_type >::type
    CObjects_attribute_sizes(
        SIXTRL_ARGPTR_DEC cobj_size_type* SIXTRL_RESTRICT
            SIXTRL_UNUSED( sizes_begin ),
        cobj_size_type const SIXTRL_UNUSED( max_num_sizes ),
        SIXTRL_CBUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( ptr ),
        cobj_size_type const SIXTRL_UNUSED( slot_size ) =
            cobj_size_type{ SIXTRL_DEFAULT_ALIGN } ) SIXTRL_NOEXCEPT {
        return SIXTRL_CXX_NAMESPACE::STATUS_GENERAL_FAILURE; }

    template< class E >
    SIXTRL_FN static typename std::enable_if<
         SIXTRL_CXX_NAMESPACE::CObjects_is_legal_type< E >(),
         SIXTRL_CXX_NAMESPACE::cobj_size_type >::type
    CObjects_attribute_sizes(
        SIXTRL_ARGPTR_DEC cobj_size_type* SIXTRL_RESTRICT sizes_begin,
        cobj_size_type const max_num_sizes,
        SIXTRL_CBUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT ptr,
        cobj_size_type const slot_size = cobj_size_type{ SIXTRL_DEFAULT_ALIGN }
        ) SIXTRL_NOEXCEPT {
        return CObjectsAttributesSizesTraits< E >::GET(
            sizes_begin, max_num_sizes, ptr, slot_size ); }

    /* --------------------------------------------------------------------- */

    template< class E >
    SIXTRL_FN static typename std::enable_if<
        !SIXTRL_CXX_NAMESPACE::CObjects_is_legal_type< E >(),
         SIXTRL_CXX_NAMESPACE::cobj_status_type >::type
    CObjects_attribute_counts(
        SIXTRL_ARGPTR_DEC cobj_size_type* SIXTRL_RESTRICT
            SIXTRL_UNUSED( counts_begin ),
        cobj_size_type const SIXTRL_UNUSED( max_num_counts ),
        SIXTRL_CBUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT
            SIXTRL_UNUSED( ptr ),
        cobj_size_type const SIXTRL_UNUSED( slot_size ) =
            cobj_size_type{ SIXTRL_DEFAULT_ALIGN } ) SIXTRL_NOEXCEPT {
        return SIXTRL_CXX_NAMESPACE::STATUS_GENERAL_FAILURE; }

    template< class E >
    SIXTRL_FN static typename std::enable_if<
         SIXTRL_CXX_NAMESPACE::CObjects_is_legal_type< E >(),
         SIXTRL_CXX_NAMESPACE::cobj_size_type >::type
    CObjects_attribute_counts(
        SIXTRL_ARGPTR_DEC cobj_size_type* SIXTRL_RESTRICT counts_begin,
        cobj_size_type const max_num_counts,
        SIXTRL_CBUFFER_ARGPTR_DEC const E *const SIXTRL_RESTRICT ptr,
        cobj_size_type const slot_size = cobj_size_type{ SIXTRL_DEFAULT_ALIGN }
        ) SIXTRL_NOEXCEPT {
        return CObjectsAttributesCountsTraits< E >::GET(
            counts_begin, max_num_counts, ptr, slot_size ); }

    /* --------------------------------------------------------------------- */

    template< cobj_obj_id_type TypeId >
    SIXTRL_FN static constexpr bool
    CObjTypeId_maps_to_illegal_type() SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjects_is_illegal_type<
            typename CObjectsIdTraits< TypeId >::value_type >();
    }

} /* end: SIXTRL_CXX_NAMESPACE */
#endif /* C++ */
#endif /* SIXTRACKLIB_COMMON_COBJECTS_COBJ_TYPE_TRAITS_CXX_HPP__ */
