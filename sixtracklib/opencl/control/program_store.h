#ifndef SIXTRACKLIB_OPENCL_CONTROL_PROGRAM_STORE_H__
#define SIXTRACKLIB_OPENCL_CONTROL_PROGRAM_STORE_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/opencl/definitions.h"
    #include "sixtracklib/opencl/control/context.h"
    #include "sixtracklib/opencl/control/program_item.h"
    #include "sixtracklib/common/control/program_store.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus )
    #include <map>
    #include <string>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    class OclProgramStore : public SIXTRL_CXX_NAMESPACE::ProgramStoreBase
    {
        public:

        using key_type = SIXTRL_CXX_NAMESPACE::OclProgramKey;
        using ocl_program_item_type = SIXTRL_CXX_NAMESPACE::OclProgramItemBase;

        static constexpr class_id_type CLASS_ID =
            SIXTRL_CXX_NAMESPACE::OPENCL_PROGRAM_STORE_CLASS_ID;

        SIXTRL_HOST_FN OclProgramStore() : ProgramStoreBase(
            SIXTRL_CXX_NAMESPACE::BACKEND_ID_OPENCL, CLASS_ID )
        {

        }

        SIXTRL_HOST_FN OclProgramStore( OclProgramStore const& ) = delete;
        SIXTRL_HOST_FN OclProgramStore( OclProgramStore&& ) = delete;

        SIXTRL_HOST_FN OclProgramStore& operator=( OclProgramStore&& ) = delete;
        SIXTRL_HOST_FN OclProgramStore& operator=(
            OclProgramStore const& ) = delete;

        SIXTRL_HOST_FN virtual ~OclProgramStore();

        using SIXTRL_CXX_NAMESPACE::ProgramStoreBase::is_stored;

        SIXTRL_HOST_FN bool is_stored( key_type const& key,
            guard_type const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool is_stored( key_type const& key ) const {
            return this->is_stored( key, this->create_lock() ); }

        SIXTRL_HOST_FN program_id_type store( key_type const& key,
            std::unique_ptr< ocl_program_item_type >&& prg_item_to_store,
            guard_type const& SIXTRL_RESTRICT_REF lock );

        SIXTRL_HOST_FN program_id_type store( key_type const& key,
            std::unique_ptr< ocl_program_item_type >&& prg_item_to_store ) {
            return this->store( key, std::move( prg_item_to_store ),
                                this->create_lock() ); }

        using SIXTRL_CXX_NAMESPACE::ProgramStoreBase::remove;

        SIXTRL_HOST_FN std::unique_ptr< item_base_type > remove(
            key_type const& key,
            guard_type const& SIXTRL_RESTRICT_REF lock );

        SIXTRL_HOST_FN std::unique_ptr< item_base_type > remove(
            key_type const& key ) {
            return std::move( this->remove( key, this->create_lock() ) ); }

        using SIXTRL_CXX_NAMESPACE::ProgramStoreBase::program_id;

        SIXTRL_HOST_FN program_id_type program_id(
            key_type const& SIXTRL_RESTRICT_REF key,
            guard_type const& SIXTRL_RESTRICT_REF lock ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN program_id_type program_id(
            key_type const& SIXTRL_RESTRICT_REF key ) const {
            return this->program_id( key, this->create_lock() ); }

        using SIXTRL_CXX_NAMESPACE::ProgramStoreBase::program_item;

        SIXTRL_HOST_FN ocl_program_item_type const* program_item(
            program_id_type const id,
            guard_type const& SIXTRL_RESTRICT_REF guard ) const override;

        SIXTRL_HOST_FN ocl_program_item_type const* program_item(
            key_type const& key,
            guard_type const& SIXTRL_RESTRICT_REF guard ) const;

        protected:

        SIXTRL_HOST_FN virtual ocl_program_item_type* do_get_program_item(
            key_type const& key, guard_type const& SIXTRL_RESTRICT_REF guard );

        SIXTRL_HOST_FN ocl_program_item_type* do_get_program_item(
            program_id_type const id,
            guard_type const& SIXTRL_RESTRICT_REF guard ) override;

        private:

        std::map< key_type, program_id_type > m_key_to_id_map;
    };

    template<> struct BackendObjTraits< SIXTRL_CXX_NAMESPACE::OclProgramStore >
    {
        static constexpr backend_id_type BACKEND_ID =
            SIXTRL_CXX_NAMESPACE::BACKEND_ID_OPENCL;

        static constexpr derived_class_id_type BASE_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::PROGRAM_STORE_BASE_CLASS_ID;

        static constexpr derived_class_id_type DERIVED_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::OPENCL_PROGRAM_STORE_CLASS_ID;
    };

    template<> struct BackendObjInvTraits<
        SIXTRL_CXX_NAMESPACE::BACKEND_ID_OPENCL,
        SIXTRL_CXX_NAMESPACE::OPENCL_PROGRAM_STORE_CLASS_ID >
    {
        typedef SIXTRL_CXX_NAMESPACE::OclProgramStore backend_obj_type;
    };
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
typedef SIXTRL_CXX_NAMESPACE::OclProgramStore NS(OclProgramStore);
#else /* !defined( __cplusplus ) || defined( _GPUCODE ) */
typedef void NS(OclProgramStore);
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#endif /* SIXTRACKLIB_OPENCL_CONTROL_PROGRAM_STORE_H__ */
