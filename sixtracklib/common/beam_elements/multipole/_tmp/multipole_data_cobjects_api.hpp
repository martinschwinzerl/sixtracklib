#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_MULTIPOLE_DATA_COBJECTS_API_CXX_HPP__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_MULTIPOLE_DATA_COBJECTS_API_CXX_HPP__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/beam_elements/multipole/multipole_data.hpp"
    #include "sixtracklib/common/beam_elements/multipole/multipole_data_api.hpp"
    #include "sixtracklib/common/cobjects/definitions.h"
    #include "sixtracklib/common/cobjects/index_object.h"
    #include "sixtracklib/common/cobjects/cbuffer_view.hpp"
    #include "sixtracklib/common/cobjects/flat_buffer.h"
    #include "sixtracklib/common/internal/type_store_traits.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template<> struct ObjTypeIdDataTypeMap<
        cobj_type_id_t, SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_MULTIPOLE >
    {
        typedef ::NS(Multipole) value_type;
    };

    template<> struct ObjDataTypeIdTraits< ::NS(Drift), cobj_type_id_t >
    {
        static_assert(
            SIXTRL_CXX_NAMESPACE::ObjData_is_c_api_type< ::NS(Multipole) >(),
            "NS(Multipole) should be a C-API type" );

        static SIXTRL_FN constexpr cobj_type_id_t TypeId() SIXTRL_NOEXCEPT
        {
            return SIXTRL_CXX_NAMESPACE::OBJECT_TYPE_MULTIPOLE;
        }
    };

    template<> struct CObjElemNumPointers< ::NS(Multipole), void >
    {
        static constexpr cobj_size_t min_num_ptrs = cobj_size_t{ 1 };
        static constexpr cobj_size_t max_num_ptrs = cobj_size_t{ 1 };
    };

    template<> struct CObjElemFieldOffsets< ::NS(Multipole) >
    {
        static constexpr cobj_size_t offsets[ 1 ] =
        {
            offsetof( ::NS(Multipole), bal_addr )
        };
    };

    template<> struct CObjElemFieldSizes< ::NS(Multipole) >
    {
        static constexpr cobj_size_t sizes[] =
        {
            sizeof( MultipoleTraits< ::NS(Multipole) >::real_t )
        };
    };

    template<> struct CObjElemFieldCounts< ::NS(Multipole) >
    {
        static SIXTRL_INLINE SIXTRL_FN cobj_status_t init_field_counts(
            SIXTRL_BUFFER_ARGPTR_DEC cobj_size_t* SIXTRL_RESTRICT counts_begin,
            cobj_size_t const max_num_counts,
            SIXTRL_BUFFER_ARGPTR_DEC const ::NS(Multipole) *const
                SIXTRL_RESTRICT ptr_elem = nullptr ) SIXTRL_NOEXCEPT
        {
            cobj_size_t counts = cobj_size_t{ 0 };

            if( ( ptr_elem != nullptr ) &&
                ( SIXTRL_CXX_NAMESPACE::CObjElem_num_ptrs< ::NS(Multipole) >(
                    ptr_elem ) == cobj_size_t{ 1 } ) )
            {
                counts = SIXTRL_CXX_NAMESPACE::Multipole_bal_length( ptr_elem );
            }

            return SIXTRL_CXX_NAMESPACE::CObjElem_init_array_as_copy_fill_remainder(
                counts_begin, max_num_counts, &counts, cobj_size_t{ 1 },
                    cobj_size_t{ 0 } );
        }
    };


    template< class R, class O, arch_size_t RAlign, arch_size_t OAlign >
    SIXTRL_STATIC SIXTRL_FN cobj_type_id_t Multipole_type_id() SIXTRL_NOEXCEPT;



}
#endif /* defined( __cplusplus ) */


#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_MULTIPOLE_MULTIPOLE_DATA_COBJECTS_API_CXX_HPP__ */
