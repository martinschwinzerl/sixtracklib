#ifndef SIXTRACKLIB_COMMON_BEAM_ELEMENTS_BEAM_ELEMENTS_BASE_CXX_HPP__
#define SIXTRACKLIB_COMMON_BEAM_ELEMENTS_BEAM_ELEMENTS_BASE_CXX_HPP__

#include <type_traits>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/buffer.h"
#include "sixtracklib/common/internal/obj_store_traits.hpp"

namespace SIXTRL_CXX_NAMESPACE
{
    template< class BeObjData, class CApiBeObjData >
    class BeamElementBase : public BeObjData
    {
        public:

        typedef BeObjData           be_data_t;
        typedef CApiBeObjData       c_api_t;
        typedef ::NS(buffer_size_t) size_type;

        static SIXTRL_FN constexpr bool SupportsCObjectsStorage()
        {
            return sixtrack_cxx::ObjData_can_be_stored_on_cobjects_buffer<
                be_data_t >();
        }

        static SIXTRL_FN constexpr size_type NumDataPtrs()
        {
            return sixtrack_cxx::ObjDataStoreLayoutTraits<
                be_data_t >::NumDataPtrs();
        }

        static SIXTRL_FN constexpr bool HasDataPtrs()
        {
            return ( sixtrack_cxx::ObjDataStoreLayoutTraits<
                be_data_t >::NumDataPtrs() == size_type{ 0 } );
        }

        static SIXTRL_FN constexpr bool SupportsCObjectsTrivialStorage()
        {
            return ( ( sixtrack_cxx::ObjData_can_be_stored_on_cobjects_buffer<
                        be_data_t >() ) &&
                     ( sixtrack_cxx::BeamElementBase< be_data_t, c_api_t
                        >::NumDataPtrs() == size_type{ 0 } ) );
        }

        static SIXTRL_FN constexpr bool NumOfDataPtrsCountsDependsOnData()
        {
            return ( ( sixtrack_cxx::BeamElementBase< be_data_t, c_api_t
                    >::NumDataPtrs() != size_type{ 0 } ) &&
                ( sixtrack_cxx::ObjDataStoreLayoutTraits< be_data_t
                    >::VarNumDataPtrCounts() ) );
        }

        /* ---------------------------------------------------------------- */

        static SIXTRL_FN constexpr bool HasCApiMemoryLayout()
        {
            return sixtrack_cxx::ObjDataStoreTraits< be_data_t >::HasCApiLayout();
        }

        SIXTRL_FN c_api_t const* ptrConstCApi() const SIXTRL_RESTRICT
        {
            using _this_t = sixtrack_cxx::BeamElementBase< be_data_t, c_api_t >;
            return ( _this_t::HasCApiMemoryLayout() )
                ? static_cast< c_api_t const* >( this ) : nullptr;
        }

        SIXTRL_FN c_api_t const* ptrCApi() const SIXTRL_RESTRICT
        {
            using _this_t = sixtrack_cxx::BeamElementBase< be_data_t, c_api_t >;
            return ( _this_t::HasCApiMemoryLayout() )
                ? static_cast< c_api_t const* >( this ) : nullptr;
        }

        SIXTRL_FN c_api_t* ptrCApi() SIXTRL_RESTRICT
        {
            using _this_t = sixtrack_cxx::BeamElementBase< be_data_t, c_api_t >;
            return ( _this_t::HasCApiMemoryLayout() )
                ? static_cast< c_api_t* >( this ) : nullptr;
        }

        /* ----------------------------------------------------------------- */

        SIXTRL_FN be_data_t& beData() SIXTRL_NOEXCEPT
        {
            return static_cast< be_data_t& >( *this );
        }

        SIXTRL_FN be_data_t const& beData() const SIXTRL_NOEXCEPT
        {
            return static_cast< be_data_t const& >( *this );
        }

        SIXTRL_FN be_data_t* ptrBeData() SIXTRL_NOEXCEPT
        {
            return static_cast< be_data_t* >( this );
        }

        SIXTRL_FN be_data_t const* ptrBeData() const SIXTRL_NOEXCEPT
        {
            return static_cast< be_data_t const* >( this );
        }
    };
}


#endif /* SIXTRACKLIB_COMMON_BEAM_ELEMENTS_BEAM_ELEMENTS_BASE_CXX_HPP__  */
/* end: */
