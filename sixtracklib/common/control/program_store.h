#ifndef SIXTRACKLIB_COMMON_CONTROL_PROGRAM_STORE_H__
#define SIXTRACKLIB_COMMON_CONTROL_PROGRAM_STORE_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/program_item.h"
    #include "sixtracklib/common/backends/backend_obj_base.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus )
    #include <memory>
    #include <vector>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES )  && defined( __cplusplus ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    class ProgramStoreBase : public SIXTRL_CXX_NAMESPACE::BackendObjBase
    {
        public:

        using item_base_type  = SIXTRL_CXX_NAMESPACE::ProgramItemBase;
        using program_id_type = SIXTRL_CXX_NAMESPACE::ctrl_program_id_type;

        static constexpr class_id_type BASE_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::PROGRAM_STORE_BASE_CLASS_ID;

        static constexpr program_id_type ILLEGAL_PROGRAM_ID =
            SIXTRL_CXX_NAMESPACE::CONTROLLER_PROGRAM_ID_ILLEGAL;

        SIXTRL_HOST_FN size_type num_stored_items() const SIXTRL_NOEXCEPT ;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN virtual item_base_type const* program_item(
            program_id_type const id ) const;

        SIXTRL_HOST_FN virtual item_base_type const* program_item(
            program_id_type const id );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN program_id_type program_id(
            item_base_type const& SIXTRL_RESTRICT_REF stored_program
        ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool is_stored(
            program_id_type const id ) const SIXTRL_NOEXCEPT ;

        SIXTRL_HOST_FN std::unique_ptr< item_base_type > remove(
            program_id_type const id ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN virtual ~ProgramStoreBase();

        protected:

        SIXTRL_HOST_FN ProgramStoreBase(
            backend_id_type const backend_id,
            class_id_type const derived_class_id ) :
            BackendObjBase( backend_id, BASE_CLASS_ID, derived_class_id ),
            m_items()
        {}

        SIXTRL_HOST_FN ProgramStoreBase( ProgramStoreBase const& ) = delete;
        SIXTRL_HOST_FN ProgramStoreBase( ProgramStoreBase&& ) = delete;

        SIXTRL_HOST_FN ProgramStoreBase& operator=(
            ProgramStoreBase const& ) = delete;

        SIXTRL_HOST_FN ProgramStoreBase& operator=(
            ProgramStoreBase&& ) = delete;

        SIXTRL_HOST_FN virtual item_base_type* do_get_program_item(
            program_id_type const id );

        SIXTRL_HOST_FN size_type _items_vector_size() const SIXTRL_NOEXCEPT {
            return this->m_items.size(); }

        SIXTRL_HOST_FN program_id_type _store_new_item(
            std::unique_ptr< item_base_type >&& item_to_store );

        SIXTRL_HOST_FN size_type _count_non_null_items() const SIXTRL_NOEXCEPT;

        private:

        std::vector< std::unique_ptr< item_base_type > > m_items;
        size_type m_num_stored_items = size_type{ 0 };
    };

    template<> struct BackendObjTraits< SIXTRL_CXX_NAMESPACE::ProgramStoreBase >
    {
        static constexpr backend_id_type BACKEND_ID =
            SIXTRL_CXX_NAMESPACE::BACKEND_ID_NONE;

        static constexpr derived_class_id_type BASE_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::PROGRAM_STORE_BASE_CLASS_ID;

        static constexpr derived_class_id_type DERIVED_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::PROGRAM_STORE_BASE_CLASS_ID;
    };

    template<> struct BackendObjInvTraits<
        SIXTRL_CXX_NAMESPACE::BACKEND_ID_NONE,
        SIXTRL_CXX_NAMESPACE::PROGRAM_STORE_BASE_CLASS_ID >
    {
        typedef SIXTRL_CXX_NAMESPACE::ProgramStoreBase backend_obj_type;
    };
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
typedef SIXTRL_CXX_NAMESPACE::ProgramStoreBase NS(ProgramStoreBase);
#else  /*  defined( _GPUCODE ) || !defined( __cplusplus ) */
typedef void NS(ProgramStoreBase);
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */
#endif /* SIXTRACKLIB_COMMON_CONTROL_PROGRAM_STORE_H__ */
