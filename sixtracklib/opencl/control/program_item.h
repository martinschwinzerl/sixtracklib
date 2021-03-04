#ifndef SIXTRACKLIB_OPENCL_CONTROL_PROGRAM_ITEM_H__
#define SIXTRACKLIB_OPENCL_CONTROL_PROGRAM_ITEM_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/opencl/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES ) && defined( __cplusplus )
    #include "sixtracklib/opencl/opencl.hpp"
    #include "sixtracklib/opencl/control/context.h"
    #include "sixtracklib/common/control/node_id.h"
    #include "sixtracklib/common/control/program_item.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) && defined( __cplusplus ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus )
    #include <string>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    struct OclProgramKey
    {
        public:

        using ctx_key_type = SIXTRL_CXX_NAMESPACE::OclContextKey;
        using cmp_result_type = ::NS(cmp_result_type);

        SIXTRL_HOST_FN void clear() {
            this->ctx_key.clear();
            this->name.clear();
            this->options.clear(); }

        SIXTRL_HOST_FN cmp_result_type compare(
            OclProgramKey const& rhs ) const SIXTRL_NOEXCEPT
        {
            cmp_result_type ret = this->ctx_key.compare( rhs.ctx_key );

            if( ret == 0 )
            {
                if( !this->name.empty() )
                {
                    if( this->name.size() == rhs.name.size() )
                    {
                        ret = this->name.compare( rhs.name );
                    }
                    else
                    {
                        ret = ( this->name.size() > rhs.name.size() )
                            ? cmp_result_type{ 1 } : cmp_result_type{ -1 };
                    }
                }
                else if( !rhs.name.empty() )
                {
                    ret = cmp_result_type{ -1 };
                }
            }

            if( ret == 0 )
            {
                if( !this->options.empty() )
                {
                    if( this->options.size() == rhs.options.size() )
                    {
                        ret = this->options.compare( rhs.options );
                    }
                    else
                    {
                        ret = ( this->options.size() > rhs.options.size() )
                            ? cmp_result_type{ 1 } : cmp_result_type{ -1 };
                    }
                }
                else if( !rhs.options.empty() )
                {
                    ret = cmp_result_type{ -1 };
                }
            }

            return ret;
        }

        SIXTRL_HOST_FN bool is_legal() const SIXTRL_NOEXCEPT {
            return ( ( this->ctx_key.is_legal() ) &&
                     ( !this->name.empty() ) ); }

        SIXTRL_HOST_FN bool operator<(
            OclProgramKey const& rhs ) const SIXTRL_NOEXCEPT {
            return ( this->compare( rhs ) < cmp_result_type{ 0 } ); }

        SIXTRL_HOST_FN bool operator==(
            OclProgramKey const& rhs ) const SIXTRL_NOEXCEPT {
            return ( this->compare( rhs ) == cmp_result_type{ 0 } ); }

        SIXTRL_HOST_FN bool operator!=(
            OclProgramKey const& rhs ) const SIXTRL_NOEXCEPT {
            return ( this->compare( rhs ) != cmp_result_type{ 0 } ); }

        ctx_key_type ctx_key;
        std::string  name;
        std::string  options;
    };

    class OclProgramItemBase : public SIXTRL_CXX_NAMESPACE::ProgramItemBase
    {
        public:

        using program_key_type = SIXTRL_CXX_NAMESPACE::OclProgramKey;
        using context_type     = SIXTRL_CXX_NAMESPACE::OclContext;
        using node_id_type     = SIXTRL_CXX_NAMESPACE::NodeId;
        using platform_id_type = node_id_type::platform_id_type;
        using device_id_type   = node_id_type::device_id_type;

        SIXTRL_HOST_FN virtual ~OclProgramItemBase() = default;

        SIXTRL_HOST_FN void clear() { this->do_clear(); }

        SIXTRL_HOST_FN size_type num_kernels() const SIXTRL_NOEXCEPT {
            return this->m_kernel_names.size(); }

        SIXTRL_HOST_FN std::string const& kernel_name_str(
            size_type const kernel_idx ) const
        {
            if( kernel_idx >= this->m_kernel_names.size() )
            {
                throw std::runtime_error( "OclRtcProgramItem::kernel_name_str: "
                    "kernel_idx > num of kernel names" );
            }

            return this->m_kernel_names[ kernel_idx ];
        }

        SIXTRL_HOST_FN char const* kernel_name(
            size_type const kernel_idx ) const SIXTRL_NOEXCEPT
        {
            return ( kernel_idx < this->m_kernel_names.size() )
                ? this->m_kernel_names[ kernel_idx ].c_str()
                : nullptr;
        }

        SIXTRL_HOST_FN program_key_type const&
        program_key() const SIXTRL_NOEXCEPT { return this->m_program_key; }

        SIXTRL_HOST_FN cl::Program const& cl_program() const SIXTRL_NOEXCEPT {
            return this->m_cl_program; }

        SIXTRL_HOST_FN cl::Program& cl_program() SIXTRL_NOEXCEPT {
            return this->m_cl_program; }

        SIXTRL_HOST_FN bool is_rtc_program_item() const SIXTRL_NOEXCEPT {
            return ( this->derived_class_id() ==
                SIXTRL_CXX_NAMESPACE::OPENCL_RTC_PROGRAM_ITEM_CLASS_ID ); }

        protected:

        SIXTRL_HOST_FN OclProgramItemBase(
            class_id_type const derived_class_id ) :
            ProgramItemBase( SIXTRL_CXX_NAMESPACE::BACKEND_ID_OPENCL,
                             derived_class_id ),
            m_program_key(), m_cl_program()
        {}

        SIXTRL_HOST_FN OclProgramItemBase( OclProgramItemBase const& ) = default;
        SIXTRL_HOST_FN OclProgramItemBase( OclProgramItemBase&& ) = default;

        SIXTRL_HOST_FN OclProgramItemBase&
        operator=( OclProgramItemBase const& ) = default;

        SIXTRL_HOST_FN OclProgramItemBase&
        operator=( OclProgramItemBase&& ) = default;

        SIXTRL_HOST_FN virtual void do_clear();
        SIXTRL_HOST_FN virtual status_type do_parse_kernel_names();

        SIXTRL_HOST_FN virtual status_type do_update_program_key(
            context_type const& SIXTRL_RESTRICT_REF context,
            std::string const& SIXTRL_RESTRICT_REF name,
            std::string const& SIXTRL_RESTRICT_REF options );

        private:

        program_key_type m_program_key;
        cl::Program m_cl_program;
        std::vector< std::string > m_kernel_names = std::vector< std::string >{};
    };

    class OclRtcProgramItem : public OclProgramItemBase
    {
        public:

        static constexpr class_id_type CLASS_ID =
            SIXTRL_CXX_NAMESPACE::OPENCL_RTC_PROGRAM_ITEM_CLASS_ID;

        SIXTRL_HOST_FN OclRtcProgramItem() : OclProgramItemBase( CLASS_ID ) {}

        SIXTRL_HOST_FN OclRtcProgramItem( OclRtcProgramItem const& ) = default;
        SIXTRL_HOST_FN OclRtcProgramItem( OclRtcProgramItem&& ) = default;

        SIXTRL_HOST_FN OclRtcProgramItem& operator=(
            OclRtcProgramItem const& ) = default;

        SIXTRL_HOST_FN OclRtcProgramItem& operator=(
            OclRtcProgramItem&& ) = default;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN void clear();

        SIXTRL_HOST_FN status_type create_from_source(
            context_type const& SIXTRL_RESTRICT_REF context,
            std::string const& SIXTRL_RESTRICT_REF source_code );

        SIXTRL_HOST_FN status_type create_from_source_file(
            context_type const& SIXTRL_RESTRICT_REF context,
            std::string const& SIXTRL_RESTRICT_REF path_to_file );

        SIXTRL_HOST_FN void set_compile_flags(
            std::string const& SIXTRL_RESTRICT_REF compile_flags );

        SIXTRL_HOST_FN status_type build(
            context_type const& SIXTRL_RESTRICT_REF context,
            std::string const& SIXTRL_RESTRICT_REF program_name,
            std::string const& SIXTRL_RESTRICT_REF program_option =
                std::string{} );

        SIXTRL_HOST_FN bool is_compiled() const SIXTRL_NOEXCEPT {
            return this->m_is_compiled; }

        SIXTRL_HOST_FN std::string const& source_code() const SIXTRL_NOEXCEPT {
            return this->m_source_code; }

        SIXTRL_HOST_FN bool created_from_file() const SIXTRL_NOEXCEPT {
            return !this->m_path_to_file.empty(); }

        SIXTRL_HOST_FN std::string const& path_to_file() const SIXTRL_NOEXCEPT {
            return this->m_source_code; }

        SIXTRL_HOST_FN std::string const& compile_flags() const SIXTRL_NOEXCEPT {
            return this->m_compile_flags; }

        SIXTRL_HOST_FN size_type num_devices() const;

        SIXTRL_HOST_FN std::string build_log() const;

        SIXTRL_HOST_FN std::string const& build_log(
            size_type const device_idx ) const;

        protected:

        SIXTRL_HOST_FN void do_clear() override;

        private:

        SIXTRL_HOST_FN status_type _build_report_to_stream(
            std::ostream& SIXTRL_RESTRICT_REF ostr,
            platform_id_type const platform_id, device_id_type const device_id,
            cl::Device const& SIXTRL_RESTRICT_REF build_device );

        std::string m_source_code   = std::string{};
        std::string m_path_to_file  = std::string{};
        std::string m_compile_flags = std::string{};

        std::vector< std::string > m_build_log = std::vector< std::string >{};

        bool m_is_compiled = false;
    };

    template<> struct BackendObjTraits< SIXTRL_CXX_NAMESPACE::OclRtcProgramItem >
    {
        static constexpr backend_id_type BACKEND_ID =
            SIXTRL_CXX_NAMESPACE::BACKEND_ID_OPENCL;

        static constexpr derived_class_id_type BASE_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::PROGRAM_ITEM_BASE_CLASS_ID;

        static constexpr derived_class_id_type DERIVED_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::OPENCL_RTC_PROGRAM_ITEM_CLASS_ID;
    };

    template<> struct BackendObjInvTraits<
        SIXTRL_CXX_NAMESPACE::BACKEND_ID_NONE,
        SIXTRL_CXX_NAMESPACE::OPENCL_RTC_PROGRAM_ITEM_CLASS_ID >
    {
        typedef SIXTRL_CXX_NAMESPACE::OclRtcProgramItem backend_obj_type;
    };

} /* end: namespace SIXTRL_CXX_NAMESPACE */
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
typedef SIXTRL_CXX_NAMESPACE::OclProgramKey      NS(OclProgramKey);
typedef SIXTRL_CXX_NAMESPACE::OclProgramItemBase NS(OclProgramItemBase);
typedef SIXTRL_CXX_NAMESPACE::OclRtcProgramItem  NS(OclRtcProgramItem);
#else /* !defined( __cplusplus ) || defined( _GPUCODE ) */
typedef void NS(OclProgramKey);
typedef void NS(OclProgramItemBase);
typedef void NS(OclRtcProgramItem);
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */
#endif /* SIXTRACKLIB_OPENCL_CONTROL_PROGRAM_ITEM_H__ */
