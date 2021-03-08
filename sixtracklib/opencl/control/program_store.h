#ifndef SIXTRACKLIB_OPENCL_CONTROL_PROGRAM_STORE_H__
#define SIXTRACKLIB_OPENCL_CONTROL_PROGRAM_STORE_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/opencl/definitions.h"
    #include "sixtracklib/opencl/control/context.h"
    #include "sixtracklib/opencl/control/program_item.h"
    #include "sixtracklib/common/control/program_store.h"
    #include "sixtracklib/common/generated/path.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/opencl/opencl.hpp"
    #include "sixtracklib/common/backends/backend_obj_base.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus )
    #include <map>
    #include <ostream>
    #include <string>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    struct OclProgramConfigItem
    {
        SIXTRL_HOST_FN OclProgramConfigItem() = default;

        SIXTRL_HOST_FN OclProgramConfigItem( OclProgramConfigItem&& ) = default;
        SIXTRL_HOST_FN OclProgramConfigItem(
            OclProgramConfigItem const& ) = default;

        SIXTRL_HOST_FN OclProgramConfigItem& operator=(
            OclProgramConfigItem const& ) = default;

        SIXTRL_HOST_FN OclProgramConfigItem& operator=(
            OclProgramConfigItem&& ) = default;

        SIXTRL_HOST_FN virtual ~OclProgramConfigItem() = default;

        SIXTRL_HOST_FN void clear() {
            this->compile_flags.clear(); compile_default_ipaths = true; }

        SIXTRL_HOST_FN friend std::ostream& operator<<(
            std::ostream& SIXTRL_RESTRICT_REF ostr,
            OclProgramConfigItem const& SIXTRL_RESTRICT_REF rhs )
        {
            bool first = true;
            for( auto const& elem : rhs.compile_flags )
            {
                if( !first ) ostr << " ";
                else first = false;

                ostr << elem;
            }

            if( rhs.compile_default_ipaths )
            {
                if( !first ) ostr << " ";
                ostr << "-I " << ::NS(PATH_TO_SIXTRL_INCLUDE_DIR);
            }

            return ostr;
        }

        std::vector< std::string > compile_flags = std::vector< std::string >{};
        bool compile_default_ipaths = true;
    };

    class OclProgramConfigStore : SIXTRL_CXX_NAMESPACE::BackendObjBase
    {
        public:

        using program_key_type   = SIXTRL_CXX_NAMESPACE::OclProgramKey;
        using context_key_type   = SIXTRL_CXX_NAMESPACE::OclContextKey;
        using config_item_type   = SIXTRL_CXX_NAMESPACE::OclProgramConfigItem;
        using config_source_type =
            SIXTRL_CXX_NAMESPACE::ocl_program_config_source_type;

        static constexpr class_id_type BASE_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::OPENCL_PROGRAM_CONFIG_CLASS_ID;

        static constexpr class_id_type CLASS_ID =
            SIXTRL_CXX_NAMESPACE::OPENCL_PROGRAM_CONFIG_CLASS_ID;

        static constexpr config_source_type SOURCE_NOT_FOUND =
            SIXTRL_CXX_NAMESPACE::OPENCL_PROGRAM_CONFIG_SOURCE_NOT_FOUND;

        static constexpr config_source_type SOURCE_EXACT =
            SIXTRL_CXX_NAMESPACE::OPENCL_PROGRAM_CONFIG_SOURCE_EXACT;

        static constexpr config_source_type SOURCE_CONTEXT =
            SIXTRL_CXX_NAMESPACE::OPENCL_PROGRAM_CONFIG_SOURCE_CONTEXT;

        static constexpr config_source_type SOURCE_PLATFORM =
            SIXTRL_CXX_NAMESPACE::OPENCL_PROGRAM_CONFIG_SOURCE_PLATFORM;

        static constexpr config_source_type SOURCE_PROGRAM =
            SIXTRL_CXX_NAMESPACE::OPENCL_PROGRAM_CONFIG_SOURCE_PROGRAM;

        static constexpr config_source_type SOURCE_GLOBAL =
            SIXTRL_CXX_NAMESPACE::OPENCL_PROGRAM_CONFIG_SOURCE_GLOBAL;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN OclProgramConfigStore() :
            BackendObjBase( SIXTRL_CXX_NAMESPACE::BACKEND_ID_OPENCL,
                BASE_CLASS_ID, CLASS_ID ), m_items()
        {
            namespace st = SIXTRL_CXX_NAMESPACE;
            st::status_type const status = this->update_default_config_item(
                st::OclProgramConfigItem{} );

            if( status != st::STATUS_SUCCESS )
                throw std::runtime_error( "unable to add default config item" );
        }

        SIXTRL_HOST_FN OclProgramConfigStore(
            OclProgramConfigStore const& ) = default;

        SIXTRL_HOST_FN OclProgramConfigStore(
            OclProgramConfigStore&& ) = default;

        SIXTRL_HOST_FN OclProgramConfigStore& operator=(
            OclProgramConfigStore const& ) = default;

        SIXTRL_HOST_FN OclProgramConfigStore& operator=(
            OclProgramConfigStore&& ) = default;

        SIXTRL_HOST_FN virtual ~OclProgramConfigStore() = default;

        SIXTRL_HOST_FN void clear();

        SIXTRL_HOST_FN status_type update_from_file(
            std::string const& SIXTRL_RESTRICT_REF path_to_config_file );

        SIXTRL_HOST_FN status_type update_from_string(
            std::string const& SIXTRL_RESTRICT_REF config_string );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN config_item_type const* find(
            program_key_type const& SIXTRL_RESTRICT_REF key,
            bool const use_best_possible_match = true,
            config_source_type* SIXTRL_RESTRICT ptr_source = nullptr
        ) const SIXTRL_NOEXCEPT;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN config_item_type const* default_config_item(
            context_key_type const& SIXTRL_RESTRICT_REF context_key
        ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN config_item_type const* default_config_item(
            std::string const& SIXTRL_RESTRICT_REF program_name,
            std::string const& SIXTRL_RESTRICT_REF program_options =
                std::string{}
        ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN config_item_type const*
            default_config_item() const SIXTRL_NOEXCEPT;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN status_type update_config_item(
            config_item_type const& SIXTRL_RESTRICT_REF item,
            program_key_type const& SIXTRL_RESTRICT_REF key );

        SIXTRL_HOST_FN status_type update_default_config_item(
            config_item_type const& SIXTRL_RESTRICT_REF item,
            context_key_type const& SIXTRL_RESTRICT_REF context_key );

        SIXTRL_HOST_FN status_type update_default_config_item(
            config_item_type const& SIXTRL_RESTRICT_REF item,
            std::string const& SIXTRL_RESTRICT_REF program_name,
            std::string const& SIXTRL_RESTRICT_REF program_options =
                std::string{} );

        SIXTRL_HOST_FN status_type update_default_config_item(
            config_item_type const& SIXTRL_RESTRICT_REF item );

        private:

        std::map< program_key_type, config_item_type > m_items;
    };

    template<> struct BackendObjTraits<
        SIXTRL_CXX_NAMESPACE::OclProgramConfigStore >
    {
        static constexpr backend_id_type BACKEND_ID =
            SIXTRL_CXX_NAMESPACE::BACKEND_ID_OPENCL;

        static constexpr derived_class_id_type BASE_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::OPENCL_PROGRAM_CONFIG_CLASS_ID;

        static constexpr derived_class_id_type DERIVED_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::OPENCL_PROGRAM_CONFIG_CLASS_ID;
    };

    template<> struct BackendObjInvTraits<
        SIXTRL_CXX_NAMESPACE::BACKEND_ID_OPENCL,
        SIXTRL_CXX_NAMESPACE::OPENCL_PROGRAM_CONFIG_CLASS_ID >
    {
        typedef SIXTRL_CXX_NAMESPACE::OclProgramConfigStore backend_obj_type;
    };

    /* ********************************************************************** */

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

        SIXTRL_HOST_FN bool is_stored(
            key_type const& key ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN program_id_type store( key_type const& key,
            std::unique_ptr< ocl_program_item_type >&& prg_item_to_store );

        using SIXTRL_CXX_NAMESPACE::ProgramStoreBase::remove;

        SIXTRL_HOST_FN std::unique_ptr< item_base_type >
        remove( key_type const& key );

        using SIXTRL_CXX_NAMESPACE::ProgramStoreBase::program_id;

        SIXTRL_HOST_FN program_id_type program_id(
            key_type const& SIXTRL_RESTRICT_REF key ) const SIXTRL_NOEXCEPT;

        using SIXTRL_CXX_NAMESPACE::ProgramStoreBase::program_item;

        SIXTRL_HOST_FN ocl_program_item_type const* program_item(
            program_id_type const id ) const override;

        SIXTRL_HOST_FN ocl_program_item_type const* program_item(
            program_id_type const id ) override;

        SIXTRL_HOST_FN ocl_program_item_type const* program_item(
            key_type const& key ) {
            return static_cast< OclProgramStore const& >(
                *this ).program_item( key ); }

        SIXTRL_HOST_FN ocl_program_item_type const* program_item(
            key_type const& key ) const;

        protected:

        SIXTRL_HOST_FN virtual ocl_program_item_type* do_get_program_item(
            key_type const& key );

        SIXTRL_HOST_FN ocl_program_item_type* do_get_program_item(
            program_id_type const id ) override;

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
typedef SIXTRL_CXX_NAMESPACE::OclProgramConfigItem NS(OclProgramConfigItem);
typedef SIXTRL_CXX_NAMESPACE::OclProgramConfigStore NS(OclProgramConfigStore);
#else /* !defined( __cplusplus ) || defined( _GPUCODE ) */
typedef void NS(OclProgramStore);
typedef void NS(OclProgramConfigItem);
typedef void NS(OclProgramConfigStore);
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#endif /* SIXTRACKLIB_OPENCL_CONTROL_PROGRAM_STORE_H__ */
