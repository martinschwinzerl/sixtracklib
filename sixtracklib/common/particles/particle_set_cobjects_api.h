#ifndef SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SET_COBJECTS_API_H__
#define SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SET_COBJECTS_API_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/particles/particle_set.h"
    #include "sixtracklib/common/particles/particle_set.hpp"
    #include "sixtracklib/common/particles/particle_set_init.h"
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/cobjects/index_object.h"
    #include "sixtracklib/common/cobjects/cbuffer_view.hpp"
    #include "sixtracklib/common/cobjects/flat_buffer.h"
    #include "sixtracklib/common/internal/objects_type_id.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    /* ===================================================================== */
    /* NS(ParticleSet): */

    template<> struct ObjTypeIdDataTypeMap<
        cobj_type_id_t, SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_PARTICLE_SET >
    {
        typedef ::NS(ParticleSet) value_type;
    };

    template<> struct ObjDataTypeIdTraits< ::NS(ParticleSet), cobj_type_id_t >
    {
        static_assert( SIXTRL_CXX_NAMESPACE::ObjData_is_c_api_type<
            ::NS(ParticleSet) >(), "NS(ParticleSet) should be a C-API type" );

        static SIXTRL_FN constexpr cobj_type_id_t TypeId() SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_PARTICLE_SET;
        }
    };

    template<> struct CObjElemNumPointers< ::NS(ParticleSet), void >
    {
        static constexpr cobj_size_t min_num_ptrs = cobj_size_t{ 21 };
        static constexpr cobj_size_t max_num_ptrs = cobj_size_t{ 21 };
    };

    template<> struct CObjElemFieldOffsets< ::NS(ParticleSet) >
     {
         static constexpr cobj_size_t offsets[ 21 ] =
         {
            offsetof( ::NS(ParticleSet), x_addr ),            /* x     */
            offsetof( ::NS(ParticleSet), px_addr ),           /* px    */
            offsetof( ::NS(ParticleSet), y_addr ),            /* y     */
            offsetof( ::NS(ParticleSet), py_addr ),           /* py    */
            offsetof( ::NS(ParticleSet), zeta_addr ),         /* zeta  */
            offsetof( ::NS(ParticleSet), delta_addr ),        /* delta */

            offsetof( ::NS(ParticleSet), state_addr ),        /* state */
            offsetof( ::NS(ParticleSet), at_element_addr ),   /* at_element */
            offsetof( ::NS(ParticleSet), at_turn_addr ),      /* at_turn */
            offsetof( ::NS(ParticleSet), particle_id_addr ),  /* particle_id */

            offsetof( ::NS(ParticleSet), psigma_addr ),       /* psigma */
            offsetof( ::NS(ParticleSet), rvv_addr ),          /* rpp */
            offsetof( ::NS(ParticleSet), rpp_addr ),          /* rvv */
            offsetof( ::NS(ParticleSet), chi_addr ),          /* chi */
            offsetof( ::NS(ParticleSet), charge_ratio_addr ), /* charge_ratio */

            offsetof( ::NS(ParticleSet), charge0_addr ),      /* charge0 */
            offsetof( ::NS(ParticleSet), mass0_addr ),        /* mass0 */
            offsetof( ::NS(ParticleSet), beta0_addr ),        /* beta0 */
            offsetof( ::NS(ParticleSet), gamma0_addr ),       /* gamma0 */
            offsetof( ::NS(ParticleSet), pc0_addr ),          /* pc0 */

            offsetof( ::NS(ParticleSet), s_addr )             /* s */
         };
     };

    template<> struct CObjElemFieldSizes< ::NS(ParticleSet) >
    {
        static constexpr cobj_size_t sizes[ 21 ] =
        {
            sizeof( ParticleSetTraits< ::NS(ParticleSet) >::real_t ), /* x     */
            sizeof( ParticleSetTraits< ::NS(ParticleSet) >::real_t ), /* px    */
            sizeof( ParticleSetTraits< ::NS(ParticleSet) >::real_t ), /* y     */
            sizeof( ParticleSetTraits< ::NS(ParticleSet) >::real_t ), /* py    */
            sizeof( ParticleSetTraits< ::NS(ParticleSet) >::real_t ), /* zeta  */
            sizeof( ParticleSetTraits< ::NS(ParticleSet) >::real_t ), /* delta */

            sizeof( ParticleSetTraits< ::NS(ParticleSet) >::index_t ), /* state */
            sizeof( ParticleSetTraits< ::NS(ParticleSet) >::index_t ), /* at_element */
            sizeof( ParticleSetTraits< ::NS(ParticleSet) >::index_t ), /* at_turn */
            sizeof( ParticleSetTraits< ::NS(ParticleSet) >::index_t ), /* particle_id */

            sizeof( ParticleSetTraits< ::NS(ParticleSet) >::real_t ),  /* psigma */
            sizeof( ParticleSetTraits< ::NS(ParticleSet) >::real_t ),  /* rpp */
            sizeof( ParticleSetTraits< ::NS(ParticleSet) >::real_t ),  /* rvv */
            sizeof( ParticleSetTraits< ::NS(ParticleSet) >::real_t ),  /* chi */
            sizeof( ParticleSetTraits< ::NS(ParticleSet) >::real_t ),  /* charge_ratio */

            sizeof( ParticleSetTraits< ::NS(ParticleSet) >::real_t ),  /* charge0 */
            sizeof( ParticleSetTraits< ::NS(ParticleSet) >::real_t ),  /* mass0 */
            sizeof( ParticleSetTraits< ::NS(ParticleSet) >::real_t ),  /* beta0 */
            sizeof( ParticleSetTraits< ::NS(ParticleSet) >::real_t ),  /* gamma0 */
            sizeof( ParticleSetTraits< ::NS(ParticleSet) >::real_t ),  /* pc0 */

            sizeof( ParticleSetTraits< ::NS(ParticleSet) >::real_t )   /* s */
        };
    };

    template<> struct CObjElemFieldCounts< ::NS(ParticleSet) >
    {
        static SIXTRL_INLINE SIXTRL_FN cobj_status_t init_field_counts(
            SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT counts_begin,
            cobj_size_t const max_num_counts,
            SIXTRL_BUFFER_ARGPTR_DEC const ::NS(ParticleSet) *const
                SIXTRL_RESTRICT pset = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            st::cobj_status_t status = st::COBJECTS_STATUS_GENERAL_FAILURE;

            if( ( pset != SIXTRL_NULLPTR ) &&
                ( max_num_counts >= cobj_size_t{ 21 } ) )
            {
                const cobj_size_t nptrs = st::CObjElem_num_ptrs<
                    ::NS(ParticleSet) >( pset );

                const cobj_size_t count = st::ParticleSet_capacity( pset );

                SIXTRL_ASSERT( nptrs <= max_num_counts );
                status = st::COBJECTS_STATUS_SUCCESS;

                for( cobj_size_t ii = 0u ; ii < nptrs ; ++ii )
                {
                    counts_begin[ ii ] = count;
                }

                for( cobj_size_t ii = nptrs ; ii < max_num_counts ; ++ii )
                {
                    counts_begin[ ii ] = cobj_size_t{ 0 };
                }
            }

            return status;
        }
    };

    /* ********************************************************************* */

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_FN constexpr cobj_type_id_t ParticleSet_type_id(
        SIXTRL_PARTICLE_SET_ARGPTR_DEC const PSetT *const SIXTRL_RESTRICT
            /* p */ = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        static_assert(
            SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >(),
            "Requires PSetT to be a ParticleSet element" );

        return ObjDataTypeIdTraits<
            PSetT, SIXTRL_CXX_NAMESPACE::cobj_type_id_t >::TypeId();
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_FN constexpr typename std::enable_if<
        SIXTRL_CXX_NAMESPACE::ParticleSet_is_type< PSetT >(),
        cobj_size_t >::type
    ParticleSet_num_pointers( SIXTRL_PARTICLE_SET_ARGPTR_DEC const PSetT
        *const SIXTRL_RESTRICT p = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        return SIXTRL_CXX_NAMESPACE::CObjElem_num_ptrs< PSetT >( p );
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN cobj_size_t
    ParticleSet_required_num_bytes( cobj_size_t const slot_size,
        SIXTRL_PARTICLE_SET_ARGPTR_DEC const PSetT *const SIXTRL_RESTRICT
            p = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::ParticleSet_is_type< PSetT >(),
            "Requires PSetT to be a ParticleSet element" );

        return st::CObjElem_required_num_bytes< PSetT >( slot_size, p );
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN cobj_size_t
    ParticleSet_required_num_slots( cobj_size_t const slot_size,
        SIXTRL_PARTICLE_SET_ARGPTR_DEC const PSetT *const SIXTRL_RESTRICT
            p = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::ParticleSet_is_type< PSetT >(),
            "Requires PSetT to be a ParticleSet element" );

        return st::CObjElem_required_num_slots< PSetT >( slot_size, p );
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
    SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT const*
    ParticleSet_const_from_cobj_index( SIXTRL_BUFFER_OBJ_ARGPTR_DEC const
            ::NS(CObjIndex) *const SIXTRL_RESTRICT index_obj,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::ParticleSet_is_type< PSetT >(),
            "Requires PSetT to be a ParticleSet element" );

        return st::CObjElem_const_from_cobj_index<
            PSetT >( index_obj, slot_size );
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT*
    ParticleSet_from_cobj_index( SIXTRL_BUFFER_OBJ_ARGPTR_DEC ::NS(CObjIndex)*
        SIXTRL_RESTRICT index_obj, cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::ParticleSet_is_type< PSetT >(),
            "Requires PSetT to be a ParticleSet element" );

        return st::CObjElem_from_cobj_index< PSetT >(
            index_obj, slot_size );
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
    SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT const*
    ParticleSet_const_from_flat_cbuffer(
        SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
        cobj_size_t const pos_in_buffer,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::ParticleSet_is_type< PSetT >(),
            "Requires PSetT to be a ParticleSet element" );

        return st::ParticleSet_const_from_cobj_index< PSetT >(
            ::NS(CObjFlatBuffer_const_index)( buffer, pos_in_buffer,
                slot_size ), slot_size );
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
    SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT*
    ParticleSet_from_flat_cbuffer(
        SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
        cobj_size_t const pos_in_buffer,
        cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::ParticleSet_is_type< PSetT >(),
            "Requires PSetT to be a ParticleSet element" );

        return st::ParticleSet_from_cobj_index< PSetT >(
            ::NS(CObjFlatBuffer_index)( buffer, pos_in_buffer, slot_size ),
                slot_size );
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
    SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT const*
    ParticleSet_const_from_cbuffer( SIXTRL_BUFFER_ARGPTR_DEC const
            CBufferView *const SIXTRL_RESTRICT cbuffer,
        cobj_size_t const pos_in_buffer ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::ParticleSet_is_type< PSetT >(),
            "Requires PSetT to be a ParticleSet element" );

        return ( cbuffer != SIXTRL_NULLPTR )
            ? st::ParticleSet_const_from_cobj_index< PSetT >(
                cbuffer->index_at( pos_in_buffer ), cbuffer->slot_size() )
            : SIXTRL_NULLPTR;
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
    SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT*
    ParticleSet_from_cbuffer(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView* SIXTRL_RESTRICT cbuffer,
        cobj_size_t const pos_in_buffer ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::ParticleSet_is_type< PSetT >(),
            "Requires PSetT to be a ParticleSet element" );

        return ( cbuffer != SIXTRL_NULLPTR )
            ? st::ParticleSet_from_cobj_index< PSetT >(
                cbuffer->index_at( pos_in_buffer ), cbuffer->slot_size() )
            : SIXTRL_NULLPTR;
    }

    #if !defined( _GPUCODE )

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN bool ParticleSet_can_add_copy(
        SIXTRL_BUFFER_ARGPTR_DEC const CBufferView *const SIXTRL_RESTRICT cbuffer,
        SIXTRL_PARTICLE_SET_ARGPTR_DEC const PSetT *const ptr_orig,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT
            ptr_requ_buffer_size = SIXTRL_NULLPTR,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT
            ptr_requ_num_slots = SIXTRL_NULLPTR,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT
            ptr_requ_num_objects = SIXTRL_NULLPTR,
        SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT
            ptr_requ_num_pointers = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::ParticleSet_is_type< PSetT >(),
            "Requires PSetT to be a ParticleSet element" );

        return ( ( cbuffer != SIXTRL_NULLPTR ) &&
                 ( cbuffer->can_add_copy_of_object( ptr_orig,
                    ptr_requ_buffer_size, ptr_requ_num_slots,
                    ptr_requ_num_objects, ptr_requ_num_pointers ) ) );
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
    SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* ParticleSet_add_copy(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView* SIXTRL_RESTRICT cbuffer,
        SIXTRL_PARTICLE_SET_ARGPTR_DEC const PSetT *const ptr_orig )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        static_assert( st::ParticleSet_is_type< PSetT >(),
            "Requires PSetT to be a ParticleSet element" );

        return ( cbuffer != SIXTRL_NULLPTR )
            ? st::CBufferView_add_copy_of_object_detail( *cbuffer, ptr_orig,
                nullptr, nullptr, nullptr, nullptr, false )
            : SIXTRL_NULLPTR;
    }

    template< class PSetT >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
    SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT*
    ParticleSet_new(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView* SIXTRL_RESTRICT cbuffer,
        particle_num_elements_t const num_particles,
        SIXTRL_PARTICLE_SET_ARGPTR_DEC const PSetT *const SIXTRL_RESTRICT
            /* p */ = SIXTRL_NULLPTR )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* added_obj = SIXTRL_NULLPTR;

        static_assert( st::ParticleSet_is_type< PSetT >(),
            "Requires PSetT to be a ParticleSet element" );

        if( cbuffer != SIXTRL_NULLPTR )
        {
            SIXTRL_ARGPTR_DEC PSetT orig;
            if( st::ARCH_STATUS_SUCCESS == st::ParticleSet_init(
                    &orig, num_particles ) )
            {
                added_obj = st::ParticleSet_add_copy( cbuffer, &orig );
            }
        }

        return added_obj;
    }

    template< class PSetT, typename... Args >
    SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT*
    ParticleSet_add(
        SIXTRL_BUFFER_ARGPTR_DEC CBufferView* SIXTRL_RESTRICT cbuffer,
        Args&&... args,
        SIXTRL_PARTICLE_SET_ARGPTR_DEC const PSetT *const
            SIXTRL_RESTRICT /* p */ = SIXTRL_NULLPTR )
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* added_obj = SIXTRL_NULLPTR;

        static_assert( st::ParticleSet_is_type< PSetT >(),
            "Requires PSetT to be a ParticleSet element" );

        if( cbuffer != SIXTRL_NULLPTR )
        {
            SIXTRL_ARGPTR_DEC PSetT orig;
            if( st::ARCH_STATUS_SUCCESS == st::ParticleSet_init(
                    &orig, std::forward< Args >( args )... ) )
            {
                added_obj = st::ParticleSet_add_copy( cbuffer, &orig );
            }
        }

        return added_obj;
    }

    #endif /* !defined( _GPUCODE ) */
}

template< class PSetT >
SIXTRL_STATIC SIXTRL_FN constexpr SIXTRL_CXX_NAMESPACE::cobj_type_id_t
NS(ParticleSet_type_id)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const PSetT *const
    SIXTRL_RESTRICT p = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::ParticleSet_type_id< PSetT >( p );
}

template< class PSetT >
SIXTRL_STATIC SIXTRL_FN constexpr SIXTRL_CXX_NAMESPACE::cobj_size_t
NS(ParticleSet_num_pointers)(
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const PSetT *const
    SIXTRL_RESTRICT p = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::ParticleSet_num_pointers< PSetT >( p );
}

template< class PSetT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::cobj_size_t
NS(ParticleSet_required_num_bytes)(
    SIXTRL_CXX_NAMESPACE::cobj_size_t const slot_size,
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const PSetT *const SIXTRL_RESTRICT
        p = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    return st::ParticleSet_required_num_bytes< PSetT >( slot_size, p );
}

template< class PSetT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_CXX_NAMESPACE::cobj_size_t
NS(ParticleSet_required_num_slots)(
    SIXTRL_CXX_NAMESPACE::cobj_size_t const slot_size,
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const PSetT *const SIXTRL_RESTRICT
        p = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    return st::ParticleSet_required_num_slots< PSetT >( slot_size, p );
}

template< class PSetT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT const*
NS(ParticleSet_const_from_cobj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const ::NS(CObjIndex) *const
        SIXTRL_RESTRICT index_obj,
    SIXTRL_CXX_NAMESPACE::cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::ParticleSet_const_from_cobj_index<
        PSetT >( index_obj, slot_size );
}

template< class PSetT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT*
NS(ParticleSet_from_cobj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC ::NS(CObjIndex)* SIXTRL_RESTRICT index_obj,
    SIXTRL_CXX_NAMESPACE::cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    return st::ParticleSet_from_cobj_index< PSetT >( index_obj, slot_size );
}

template< class PSetT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT const*
NS(ParticleSet_const_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    SIXTRL_CXX_NAMESPACE::cobj_size_t const pos_in_buffer,
    SIXTRL_CXX_NAMESPACE::cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::ParticleSet_const_from_flat_cbuffer<
        PSetT >( buffer, pos_in_buffer, slot_size );
}

template< class PSetT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT*
NS(ParticleSet_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    SIXTRL_CXX_NAMESPACE::cobj_size_t const pos_in_buffer,
    SIXTRL_CXX_NAMESPACE::cobj_size_t const slot_size ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::ParticleSet_from_flat_cbuffer<
        PSetT >( buffer, pos_in_buffer, slot_size );
}

template< class PSetT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT const*
NS(ParticleSet_const_from_cbuffer)(
    SIXTRL_BUFFER_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::CBufferView *const
        SIXTRL_RESTRICT cbuffer,
    SIXTRL_CXX_NAMESPACE::cobj_size_t const pos_in_buffer ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::ParticleSet_const_from_cbuffer< PSetT >(
        cbuffer, pos_in_buffer );
}

template< class PSetT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN
SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT*
NS(ParticleSet_from_cbuffer)(
    SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBufferView*
        SIXTRL_RESTRICT cbuffer,
    SIXTRL_CXX_NAMESPACE::cobj_size_t const pos_in_buffer ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::ParticleSet_from_cbuffer< PSetT >(
        cbuffer, pos_in_buffer );
}

#if !defined( _GPUCODE )

template< class PSetT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN bool NS(ParticleSet_can_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC const SIXTRL_CXX_NAMESPACE::CBufferView *const
        SIXTRL_RESTRICT cbuffer,
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const PSetT *const ptr_orig,
    SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::cobj_size_t* SIXTRL_RESTRICT
        ptr_requ_buffer_size = SIXTRL_NULLPTR,
    SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::cobj_size_t* SIXTRL_RESTRICT
        ptr_requ_num_slots = SIXTRL_NULLPTR,
    SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::cobj_size_t* SIXTRL_RESTRICT
        ptr_requ_num_objects = SIXTRL_NULLPTR,
    SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::cobj_size_t* SIXTRL_RESTRICT
        ptr_requ_num_pointers = SIXTRL_NULLPTR ) SIXTRL_NOEXCEPT
{
    return SIXTRL_CXX_NAMESPACE::ParticleSet_can_add_copy( cbuffer, ptr_orig,
        ptr_requ_buffer_size, ptr_requ_num_slots, ptr_requ_num_objects,
            ptr_requ_num_pointers );
}

template< class PSetT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN
SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT* NS(ParticleSet_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBufferView*
        SIXTRL_RESTRICT cbuffer,
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const PSetT *const ptr_orig )
{
    return SIXTRL_CXX_NAMESPACE::ParticleSet_add_copy< PSetT >(
        cbuffer, ptr_orig );
}

template< class PSetT >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_HOST_FN SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT*
NS(ParticleSet_new)( SIXTRL_BUFFER_ARGPTR_DEC
        SIXTRL_CXX_NAMESPACE::CBufferView* SIXTRL_RESTRICT cbuffer,
    SIXTRL_CXX_NAMESPACE::particle_num_elements_t const num_particles )
{
    return SIXTRL_CXX_NAMESPACE::ParticleSet_new< PSetT >(
        cbuffer, num_particles );
}

template< class PSetT, typename... Args >
SIXTRL_STATIC SIXTRL_INLINE SIXTRL_FN SIXTRL_PARTICLE_SET_ARGPTR_DEC PSetT*
NS(ParticleSet_add)( SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_CXX_NAMESPACE::CBufferView*
        SIXTRL_RESTRICT cbuffer, Args&&... args,
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const PSetT *const SIXTRL_RESTRICT
        p = SIXTRL_NULLPTR )
{
    return SIXTRL_CXX_NAMESPACE::ParticleSet_add< PSetT, Args... >(
        cbuffer, std::forward< Args >( args )..., p );
}

#endif /* !defined( _GPUCODE ) */
#endif /* __cplusplus */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC SIXTRL_FN NS(cobj_type_id_t)
NS(ParticleSet_type_id)( void ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet) const*
NS(ParticleSet_const_from_cobj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(CObjIndex) *const
        SIXTRL_RESTRICT index_obj,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)*
NS(ParticleSet_from_cobj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* SIXTRL_RESTRICT index_obj,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet) const*
NS(ParticleSet_const_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)*
NS(ParticleSet_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT;

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN NS(cobj_type_id_t)
NS(ParticleSet_type_id_ext)( void ) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(ParticleSet_can_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(CBufferView) *const
        SIXTRL_RESTRICT cbuffer,
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const NS(ParticleSet) *const ptr_orig,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)* SIXTRL_RESTRICT requ_buffer_size,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)* SIXTRL_RESTRICT requ_num_slots,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)* SIXTRL_RESTRICT requ_num_objects,
    SIXTRL_BUFFER_ARGPTR_DEC NS(cobj_size_t)* SIXTRL_RESTRICT requ_num_pointers
) SIXTRL_NOEXCEPT;

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)*
NS(ParticleSet_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(CBufferView)* SIXTRL_RESTRICT cbuffer,
    SIXTRL_PARTICLE_SET_ARGPTR_DEC const NS(ParticleSet) *const ptr_orig );

SIXTRL_EXTERN SIXTRL_HOST_FN SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)*
NS(ParticleSet_new)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(CBufferView)* SIXTRL_RESTRICT cbuffer,
    NS(particle_num_elements_t) const num_particles );

#endif /* _GPUCODE */
#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!!!        Inline Methods and Functions Implementations       !!!!!!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/cobjects/element_traits.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_INLINE NS(cobj_type_id_t) NS(ParticleSet_type_id)( void ) SIXTRL_NOEXCEPT
{
    #if defined( __cplusplus )
    SIXTRL_ASSERT( ::NS(OBJECT_TYPE_PARTICLE) ==
        SIXTRL_CXX_NAMESPACE::ParticleSet_type_id< ::NS(ParticleSet) >() );
    #endif /* C++ */

    return NS(OBJECT_TYPE_PARTICLE);
}

SIXTRL_INLINE SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet) const*
NS(ParticleSet_const_from_cobj_index)( SIXTRL_BUFFER_OBJ_ARGPTR_DEC const
        NS(CObjIndex) *const SIXTRL_RESTRICT index_obj,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return ( SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet) const* )( uintptr_t
        )NS(CObjIndex_begin_addr_filter_by_type_info)(
            index_obj, NS(ParticleSet_type_id)(), sizeof( NS(ParticleSet) ),
                slot_size );
}

SIXTRL_INLINE SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)*
NS(ParticleSet_from_cobj_index)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(CObjIndex)* SIXTRL_RESTRICT index_obj,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return ( SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)* )( uintptr_t
        )NS(CObjIndex_begin_addr_filter_by_type_info)(
            index_obj, NS(ParticleSet_type_id)(), sizeof( NS(ParticleSet) ),
                slot_size );
}

SIXTRL_INLINE SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet) const*
NS(ParticleSet_const_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return NS(ParticleSet_const_from_cobj_index)( NS(CObjFlatBuffer_const_index)(
        buffer, pos_in_buffer, slot_size ), slot_size );
}

SIXTRL_INLINE SIXTRL_PARTICLE_SET_ARGPTR_DEC NS(ParticleSet)*
NS(ParticleSet_from_flat_cbuffer)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT buffer,
    NS(cobj_size_t) const pos_in_buffer,
    NS(cobj_size_t) const slot_size ) SIXTRL_NOEXCEPT
{
    return NS(ParticleSet_from_cobj_index)( NS(CObjFlatBuffer_index)(
        buffer, pos_in_buffer, slot_size ), slot_size );
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_PARTICLES_PARTICLE_SET_COBJECTS_API_H__ */
