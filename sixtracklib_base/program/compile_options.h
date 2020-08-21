#ifndef SIXTRACKLIB_BASE_PROGRAM_COMPILE_OPTIONS_H__
#define SIXTRACKLIB_BASE_PROGRAM_COMPILE_OPTIONS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/program/definitions.h"
    #include "sixtracklib_base/backend/backend_obj.h"
    #include "sixtracklib_base/internal/class_id.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <algorithm>
        #include <cstddef>
        #include <cstdlib>
        #include <cstdio>
        #include <cstring>
        #include <memory>
        #include <ostream>
        #include <string>
    #endif /* C++, Host */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    class SIXTRL_BASE_EXPORT_API BaseCompileOptionItem :
        public SIXTRL_CXX_NAMESPACE::BaseBackendObj
    {
        public:

        typedef std::string string_type;
        typedef std::string::value_type string_char_type;
        typedef SIXTRL_CXX_NAMESPACE::size_t size_type;
        typedef SIXTRL_CXX_NAMESPACE::program_compile_option_kind_t kind_type;

        static constexpr size_type DEFAULT_BLOCK_INDENT = size_type{ 4 };
        static constexpr size_type DEFAULT_TOPLEVEL_INDENT = size_type{ 0 };

        static constxpr kind_type KIND_DEFINE =
            SIXTRL_CXX_NAMESPACE::PROGRAM_COMP_OPTION_KIND_DEFINE;

        static constexpr kind_type KIND_UNDEF =
            SIXTRL_CXX_NAMESPACE::PROGRAM_COMP_OPTION_KIND_UNDEF;

        kind_type KIND_INCLUDE_DIR =
            SIXTRL_CXX_NAMESPACE::PROGRAM_COMP_OPTION_KIND_INCLUDE_DIR;

        kind_type KIND_UNSPECIFIED =
            SIXTRL_CXX_NAMESPACE::PROGRAM_COMP_OPTION_KIND_UNSPECIFIED;

        kind_type KIND_UNSPECIFIED_LONG =
            SIXTRL_CXX_NAMESPACE::PROGRAM_COMP_OPTION_KIND_UNSPECIFIED_LONG;

        /* ================================================================= */

        SIXTRL_HOST_FN virtual ~BaseCompileOptionItem() = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN friend void swap(
            BaseCompileOptionItem& SIXTRL_RESTRICT_REF lhs,
            BaseCompileOptionItem& SIXTRL_RESTRICT_REF rhs ) SIXTRL_NOEXCEPT
        {
            using std::swap;
            swap( lhs.m_name,                rhs.m_name );
            swap( lhs.m_prefix,              rhs.m_prefix );
            swap( lhs.m_value,               rhs.m_value );
            swap( lhs.m_separator,           rhs.m_separator );
            swap( lhs.m_value_needs_quotes,  rhs.m_value_needs_quotes );
            swap( lhs.m_is_define_macro,     rhs.m_is_define_macro );
            swap( lhs.m_only_cmd_line_flag,  rhs.m_only_cmd_line_flag );
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN string_type const& name_str() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN string_char_type const* name() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN status_type set_name(
            string_type const& SIXTRL_RESTRICT_REF name );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN string_type const& prefix_str() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN string_char_type const* prefix() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN status_type set_prefix(
            string_type const& SIXTRL_RESTRICT_REF prefix_str );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN string_type const& separator_str() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN string_char_type const* separator() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN status_type set_separator(
            string_type const& SIXTRL_RESTRICT_REF prefix_str );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN bool has_value() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN string_type const& value_str() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN string_char_type const* value() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN status_type set_value(
            string_type const& SIXTRL_RESTRICT_REF value_str );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN bool value_needs_quotes() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN status_type set_value_needs_quotes(
            bool const needs_quotes ) SIXTRL_NOEXCEPT;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN bool is_define_macro() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN status_type set_is_define_macro(
            bool const is_define_macro_flag ) SIXTRL_NOEXCEPT;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN bool is_always_cmd_line_flag() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN status_type set_is_always_cmd_line_flag(
            bool const is_always_cmd_line_opt ) SIXTRL_NOEXCEPT;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN string_type to_cmd_line_string() const;
        SIXTRL_HOST_FN size_type required__cmd_line_string_capacity() const;

        SIXTRL_HOST_FN status_type to_cmd_line_string(
            string_char_type* SIXTRL_RESTRICT out_str_buffer,
            size_type const out_str_buffer_capacity ) const;

        SIXTRL_HOST_FN status_type print_cmd_line(
            std::ostream& SIXTRL_RESTRICT_REF out_str ) const;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN string_type to_define_block_string(
            size_type const block_indent = DEFAULT_BLOCK_INDENT,
            size_type const top_level_indent = DEFAULT_TOPLEVEL_INDENT ) const;

        SIXTRL_HOST_FN size_type required_define_block_string_capacity(
            size_type const block_indent = DEFAULT_BLOCK_INDENT,
            size_type const top_level_indent = DEFAULT_TOPLEVEL_INDENT ) const;

        SIXTRL_HOST_FN status_type to_define_block_string(
            string_char_type* SIXTRL_RESTRICT out_str_buffer,
            size_type const out_str_buffer_capacity,
            size_type const block_indent = DEFAULT_BLOCK_INDENT,
            size_type const top_level_indent = DEFAULT_TOPLEVEL_INDENT ) const;

        SIXTRL_HOST_FN status_type print_define_block(
            std::ostream& SIXTRL_RESTRICT_REF out_str,
            size_type const block_indent = DEFAULT_BLOCK_INDENT,
            size_type const top_level_indent = DEFAULT_TOPLEVEL_INDENT ) const;

        protected:

        SIXTRL_HOST_FN explicit BaseCompileOptionItem(
            backend_id_t const backend_id );

        SIXTRL_HOST_FN BaseCompileOptionItem(
            BaseCompileOptionItem const& ) = default;

        SIXTRL_HOST_FN BaseCompileOptionItem(
            BaseCompileOptionItem&& ) = default;

        SIXTRL_HOST_FN BaseCompileOptionItem& operator=(
            BaseCompileOptionItem const& ) = default;

        SIXTRL_HOST_FN BaseCompileOptionItem& operator=(
            BaseCompileOptionItem&& ) = default;

        SIXTRL_HOST_FN virtual status_type do_print_cmd_line(
            std::ostream& SIXTRL_RESTRICT_REF out_str ) const;

        SIXTRL_HOST_FN virtual status_type do_print_define_block(
            std::ostream& SIXTRL_RESTRICT_REF out_str,
            size_type const block_indent,
            size_type const top_level_indent ) const;

        private:

        string_type m_name;
        string_type m_prefix = string_type{};
        string_type m_value = string_type{};
        string_type m_separator = string_type{};
        kind_type   m_option_kind = KIND_UNSPECIFIED;
        bool m_value_needs_quotes = false;
        bool m_only_cmd_line_flag = false;
    };

    class BaseCmdLineCompileOptions;
    class BaseDefineBlockCompileOptions;

    class SIXTRL_BASE_EXPORT_API BaseCompileOptions :
        public SIXTRL_CXX_NAMESPACE::BaseBackendObj
    {
        public:

        typedef SIXTRL_CXX_NAMESPACE::BaseCompileOptionItem base_item_t;
        typedef void (*base_item_delete_fn_t)( base_item_t* SIXTRL_RESTRICT );
        typedef std::unique_ptr< base_item_t, base_item_delete_fn_t >
                stored_item_t;

        typedef item_t::size_type size_type;
        typedef item_t::string_type string_type;
        typedef item_t::string_char_type string_char_type;

        static constexpr class_variant_t COMPILE_OPTIONS_VARIANT_DEFAULT =
            class_variant_t{ 0x00 };

        static constexpr class_variant_t COMPILE_OPTIONS_VARIANT_CMD_LINE =
            class_variant_t{ 0x01 };

        static constexpr class_variant_t COMPILE_OPTIONS_VARIANT_DEFINE_BLOCK =
            class_variant_t{ 0x02 };

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN virtual ~BaseCompileOptions() = default;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool is_cmd_line_options_store() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN BaseCmdLineCompileOptions const*
        as_cmd_line_options_store() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN BaseCmdLineCompileOptions*
        as_cmd_line_options_store() SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN bool
        is_define_block_options_store() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN BaseDefineBlockCompileOptions const*
        as_define_block_compile_options() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN BaseDefineBlockCompileOptions*
        as_define_block_compile_options() SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        protected:

        SIXTRL_HOST_FN explicit BaseCompileOptions(
            backend_id_t const backend_id );

        SIXTRL_HOST_FN BaseCompileOptions(
            BaseCompileOptions const& SIXTRL_RESTRICT_REF other );

        SIXTRL_HOST_FN BaseCompileOptions(
            BaseCompileOptions&& SIXTRL_RESTRICT_REF other ) = default;

        SIXTRL_HOST_FN BaseCompileOptions& operator=(
            BaseCompileOptions const& SIXTRL_RESTRICT_REF rhs );

        SIXTRL_HOST_FN BaseCompileOptions& operator=(
            BaseCompileOptions&& SIXTRL_RESTRICT_REF rhs );

        private:

        std::vector< stored_item_t > m_stored_items;
        string_type m_define_macro_prefix = string_type{};
    };

} /* ns: SIXTRL_CXX_NAMESPACE */
#endif /* C++, Host */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!                   Exported Plugin C-API :: Types                !!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

#if defined( __cplusplus )
typedef SIXTRL_CXX_NAMESPACE::BaseCompileOptionItem NS(BaseCompileOptionItem);
#else /* C */
typedef struct NS(BaseCompileOptionItem);
typedef struct NS(BaseCompileOptionItem) NS(BaseCompileOptionItem);
#endif /* C / C++ */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!                Exported Plugin C-API :: Functions               !!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

SIXTRL_BASE_EXPORT_API void NS(CompileOptionItem_delete)(
    NS(BaseCompileOptionItem)* SIXTRL_RESTRICT item ) SIXTRL_NOEXCEPT;


#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_BASE_PROGRAM_COMPILE_OPTIONS_H__ */
