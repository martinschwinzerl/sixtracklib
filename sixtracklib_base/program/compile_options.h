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
        #include <deque>
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
        typedef std::unique_ptr< BaseCompileOptionItem, void (*)(
            BaseCompileOptionItem* SIXTRL_RESTRICT ) > stored_base_item_type;

        static constexpr kind_type KIND_DEFINE =
            SIXTRL_CXX_NAMESPACE::PROGRAM_COMP_OPTION_KIND_DEFINE;

        static constexpr kind_type KIND_UNDEF =
            SIXTRL_CXX_NAMESPACE::PROGRAM_COMP_OPTION_KIND_UNDEF;

        static constexpr kind_type KIND_INCLUDE_DIR =
            SIXTRL_CXX_NAMESPACE::PROGRAM_COMP_OPTION_KIND_INCLUDE_DIR;

        static constexpr kind_type KIND_UNSPECIFIED =
            SIXTRL_CXX_NAMESPACE::PROGRAM_COMP_OPTION_KIND_UNSPECIFIED;

        static constexpr kind_type KIND_UNSPECIFIED_LONG =
            SIXTRL_CXX_NAMESPACE::PROGRAM_COMP_OPTION_KIND_UNSPECIFIED_LONG;

        static constexpr kind_type KIND_ILLEGAL =
            SIXTRL_CXX_NAMESPACE::PROGRAM_COMP_OPTION_KIND_ILLEGAL;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        static constexpr string_char_type DEFAULT_BLOCK_INDENT_STR[] = "    ";
        static constexpr string_char_type DEFAULT_TOP_LEVEL_INDENT_STR[] = "";

        /* ----------------------------------------------------------------- */

        static SIXTRL_HOST_FN void DELETE_BASE_ITEM( BaseCompileOptionItem*
            SIXTRL_RESTRICT item ) SIXTRL_NOEXCEPT { delete item; }

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
            swap( lhs.m_macro_kind,          rhs.m_macro_kind );
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
        SIXTRL_HOST_FN bool is_undef_macro() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool is_include_dir_macro() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool is_unspecified_macro() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN bool is_unspecified_long_macro() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN kind_type macro_kind() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_type set_macro_kind(
            kind_type const macro_kind ) SIXTRL_NOEXCEPT;

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
            string_type const& SIXTRL_RESTRICT_REF block_indent_str =
                DEFAULT_BLOCK_INDENT_STR,
            string_type const& SIXTRL_RESTRICT_REF top_level_indent_str =
                DEFAULT_TOP_LEVEL_INDENT_STR ) const;

        SIXTRL_HOST_FN size_type required_define_block_string_capacity(
            string_type const& SIXTRL_RESTRICT_REF block_indent_str =
                DEFAULT_BLOCK_INDENT_STR,
            string_type const& SIXTRL_RESTRICT_REF top_level_indent_str =
                DEFAULT_TOP_LEVEL_INDENT_STR ) const;

        SIXTRL_HOST_FN status_type to_define_block_string(
            string_char_type* SIXTRL_RESTRICT out_str_buffer,
            size_type const out_str_buffer_capacity,
            string_type const& SIXTRL_RESTRICT_REF block_indent_str =
                DEFAULT_BLOCK_INDENT_STR,
            string_type const& SIXTRL_RESTRICT_REF top_level_indent_str =
                DEFAULT_TOP_LEVEL_INDENT_STR ) const;

        SIXTRL_HOST_FN status_type print_define_block(
            std::ostream& SIXTRL_RESTRICT_REF out_str,
            string_type const& SIXTRL_RESTRICT_REF block_indent_str =
                DEFAULT_BLOCK_INDENT_STR,
            string_type const& SIXTRL_RESTRICT_REF top_level_indent_str =
                DEFAULT_TOP_LEVEL_INDENT_STR ) const;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN stored_base_item_type clone() const;

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
            string_type const& SIXTRL_RESTRICT_REF block_indent_str,
            string_type const& SIXTRL_RESTRICT_REF top_level_indent_str ) const;

        SIXTRL_HOST_FN virtual stored_base_item_type do_clone() const;

        private:

        string_type m_name;
        string_type m_prefix      = string_type{};
        string_type m_value       = string_type{};
        string_type m_separator   = string_type{};
        kind_type   m_macro_kind  = BaseCompileOptionItem::KIND_UNSPECIFIED;

        bool m_value_needs_quotes = false;
        bool m_only_cmd_line_flag = false;
    };

    /* ********************************************************************* */

    class BaseCmdLineCompileOptions;
    class BaseDefineBlockCompileOptions;

    class SIXTRL_BASE_EXPORT_API BaseCompileOptions :
        public SIXTRL_CXX_NAMESPACE::BaseBackendObj
    {
        public:

        typedef SIXTRL_CXX_NAMESPACE::BaseCompileOptionItem base_item_t;
        typedef void (*base_item_delete_fn_t)( base_item_t* SIXTRL_RESTRICT );
        typedef std::unique_ptr< base_item_t, base_item_delete_fn_t >
                stored_item_type;

        typedef base_item_t::size_type size_type;
        typedef base_item_t::string_type string_type;
        typedef base_item_t::string_char_type string_char_type;
        typedef base_item_t::kind_type item_kind_type;

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

        SIXTRL_HOST_FN size_type num_stored_items() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN base_item_t const* item(
            size_type const idx ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN base_item_t* item( size_type const idx ) SIXTRL_NOEXCEPT;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN status_type append( stored_item_type item_to_append );
        SIXTRL_HOST_FN status_type prepend( stored_item_type item_to_preprend );

        SIXTRL_HOST_FN status_type insert_at_pos(
            stored_item_type item_to_add, size_type const at_pos );

        SIXTRL_HOST_FN status_type remove( size_type const at_pos );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN void clear();
        SIXTRL_HOST_FN bool is_committed() const SIXTRL_NOEXCEPT;
        SIXTRL_HOST_FN status_type commit();

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN size_type find_next_by_kind(
            item_kind_type const item_kind,
            size_type const start_pos = size_type{ 0 } ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool has_items_by_kind(
            item_kind_type const item_kind ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type num_items_by_kind(
            item_kind_type const item_kind ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type item_pos_by_kind(
            size_type const* SIXTRL_RESTRICT item_pos_begin,
            size_type const max_num_item_pos_entries,
            item_kind_type const item_kind ) const SIXTRL_NOEXCEPT;

        template< typename AtPosIter >
        SIXTRL_HOST_FN size_type item_pos_by_kind(
            AtPosIter item_pos_begin, AtPosIter item_pos_end,
            item_kind_type const item_kind ) const SIXTRL_NOEXCEPT;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN size_type find_next_by_name(
            string_type const& SIXTRL_RESTRICT_REF name,
            size_type const start_pos = size_type{ 0 } ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN bool has_items_by_name(
            string_type const& SIXTRL_RESTRICT_REF name ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type num_items_by_name(
            string_type const& SIXTRL_RESTRICT_REF name ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN size_type item_pos_by_name(
            size_type const* SIXTRL_RESTRICT item_pos_begin,
            size_type const max_num_item_pos_entries,
            string_type const& SIXTRL_RESTRICT_REF name ) const SIXTRL_NOEXCEPT;

        template< typename AtPosIter >
        SIXTRL_HOST_FN size_type item_pos_by_name(
            AtPosIter item_pos_begin, AtPosIter item_pos_end,
            string_type const& SIXTRL_RESTRICT_REF name ) const SIXTRL_NOEXCEPT;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN string_type to_string() const;
        SIXTRL_HOST_FN size_type required_string_capacity() const;
        SIXTRL_HOST_FN status_type to_string(
            string_char_type* SIXTRL_RESTRICT out_str_buffer,
            size_type const out_str_buffer_capacity ) const;
        SIXTRL_HOST_FN status_type print(
            std::ostream& SIXTRL_RESTRICT_REF ostr ) const;

        SIXTRL_HOST_FN friend std::ostream& operator<<(
            std::ostream& SIXTRL_RESTRICT_REF out_str,
            BaseCompileOptions const& SIXTRL_RESTRICT_REF compile_options )
        {
            status_type const status = compile_options.print( out_str );
            SIXTRL_ASSERT( status == SIXTRL_CXX_NAMESPACE::STATUS_SUCCESS );
            ( void )status;
            return out_str;
        }

        protected:

        typedef std::deque< stored_item_type > compile_option_items_store_type;
        typedef compile_option_items_store_type::iterator iterator;
        typedef compile_option_items_store_type::const_iterator const_iterator;

        SIXTRL_HOST_FN explicit BaseCompileOptions(
            backend_id_t const backend_id, class_variant_t const variant );

        SIXTRL_HOST_FN BaseCompileOptions(
            BaseCompileOptions const& SIXTRL_RESTRICT_REF other );

        SIXTRL_HOST_FN BaseCompileOptions(
            BaseCompileOptions&& SIXTRL_RESTRICT_REF other ) = default;

        SIXTRL_HOST_FN BaseCompileOptions& operator=(
            BaseCompileOptions const& SIXTRL_RESTRICT_REF rhs );

        SIXTRL_HOST_FN BaseCompileOptions& operator=(
            BaseCompileOptions&& rhs ) = default;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN virtual void do_clear();

        SIXTRL_HOST_FN virtual status_type do_insert_item(
            stored_item_type item_to_add,
            const_iterator insert_before_this_item );

        SIXTRL_HOST_FN virtual status_type do_insert_range_of_input_items(
            const_iterator in_item_begin, const_iterator in_item_end,
            const_iterator insert_before_this_item );

        SIXTRL_HOST_FN virtual status_type do_remove_item(
            iterator item_to_remove );

        SIXTRL_HOST_FN virtual status_type do_print(
            std::ostream& SIXTRL_RESTRICT_REF ostr ) const = 0;

        SIXTRL_HOST_FN virtual status_type do_commit();

        SIXTRL_HOST_FN void update_is_committed_flag(
            bool const is_committed ) SIXTRL_NOEXCEPT;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        private:

        SIXTRL_HOST_FN status_type do_insert_item_base_impl(
            stored_item_type item_to_add,
            const_iterator insert_before_this_item );

        SIXTRL_HOST_FN status_type do_insert_range_of_input_items_base_impl(
            const_iterator in_item_begin, const_iterator in_item_end,
            const_iterator insert_before_this_item );

        SIXTRL_HOST_FN status_type do_commit_base_impl();

        compile_option_items_store_type m_stored_items;
        bool m_is_committed = true;
    };

    /* ********************************************************************* */

    class SIXTRL_BASE_EXPORT_API BaseCmdLineCompileOptions :
        public SIXTRL_CXX_NAMESPACE::BaseCompileOptions
    {
        public:

        SIXTRL_HOST_FN virtual ~BaseCmdLineCompileOptions() = default;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN string_type const&
        define_macro_prefix_str() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN string_char_type const*
        define_macro_prefix() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_type set_define_macro_prefix(
            string_type const& SIXTRL_RESTRICT_REF prefix_str );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN string_type const&
        define_macro_separator_str() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN string_char_type const*
        define_macro_separator() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_type set_define_macro_separator(
            string_type const& SIXTRL_RESTRICT_REF separator_str );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN string_type const&
        undef_macro_prefix_str() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN string_char_type const*
        undef_macro_prefix() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_type set_undef_macro_prefix(
            string_type const& SIXTRL_RESTRICT_REF prefix_str );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN string_type const&
        include_dir_macro_prefix_str() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN string_char_type const*
        include_dir_macro_prefix() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_type set_include_dir_macro_prefix(
            string_type const& SIXTRL_RESTRICT_REF prefix_str );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN string_type const&
        unspec_macro_prefix_str() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN string_char_type const*
        unspec_macro_prefix() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_type set_unspec_macro_prefix(
            string_type const& SIXTRL_RESTRICT_REF prefix_str );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN string_type const&
        unspec_macro_separator_str() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN string_char_type const*
        unspec_macro_separator() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_type set_unspec_macro_separator(
            string_type const& SIXTRL_RESTRICT_REF separator_str );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN string_type const&
        unspec_long_macro_prefix_str() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN string_char_type const*
        unspec_long_macro_prefix() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_type set_unspec_long_macro_prefix(
            string_type const& SIXTRL_RESTRICT_REF prefix_str );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN string_type const&
        unspec_long_macro_separator_str() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN string_char_type const*
        unspec_long_macro_separator() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_type set_unspec_long_macro_separator(
            string_type const& SIXTRL_RESTRICT_REF separator_str );

        protected:

        SIXTRL_HOST_FN BaseCmdLineCompileOptions(
            backend_id_t const backend_id );

        SIXTRL_HOST_FN BaseCmdLineCompileOptions(
            BaseCmdLineCompileOptions const&
                SIXTRL_RESTRICT_REF other ) = default;

        SIXTRL_HOST_FN BaseCmdLineCompileOptions(
            BaseCompileOptions const& SIXTRL_RESTRICT_REF other );

        SIXTRL_HOST_FN BaseCmdLineCompileOptions(
            BaseCmdLineCompileOptions&& other ) = default;

        SIXTRL_HOST_FN BaseCmdLineCompileOptions& operator=(
            BaseCmdLineCompileOptions const&
                SIXTRL_RESTRICT_REF rhs ) = default;

        SIXTRL_HOST_FN BaseCmdLineCompileOptions& operator=(
            BaseDefineBlockCompileOptions const& SIXTRL_RESTRICT_REF rhs );

        SIXTRL_HOST_FN BaseCmdLineCompileOptions& operator=(
            BaseCmdLineCompileOptions&& rhs ) = default;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN status_type do_insert_item(
            stored_item_type item_to_add,
            const_iterator predecessor_item) override;

        SIXTRL_HOST_FN status_type do_print(
            std::ostream& SIXTRL_RESTRICT_REF out_str ) const override;

        private:

        string_type m_define_macro_prefix = string_type{ "-D" };
        string_type m_define_macro_separator = string_type{ "=" };

        string_type m_undef_macro_prefix = string_type{ "-U" };
        string_type m_include_dir_macro_prefix = string_type{ "-I" };

        string_type m_unspec_macro_prefix = string_type{ "-" };
        string_type m_unspec_macro_separator = string_type{ "=" };

        string_type m_unspec_long_macro_prefix = string_type{ "--" };
        string_type m_unspec_long_macro_separator = string_type{ "=" };

        string_type m_print_separator = string_type{ ' ' };
    };

    /* ********************************************************************* */

    class SIXTRL_BASE_EXPORT_API BaseDefineBlockCompileOptions :
        public SIXTRL_CXX_NAMESPACE::BaseCompileOptions
    {
        public:

        SIXTRL_HOST_FN virtual ~BaseDefineBlockCompileOptions() = default;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN string_type const&
        block_indent_str() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN string_char_type const*
        block_indent() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_type set_block_indent(
            string_type const& SIXTRL_RESTRICT_REF block_indent_str );

        SIXTRL_HOST_FN status_type set_block_indent_detailed(
            size_type const block_indent_size,
            string_char_type const fill_char = string_char_type{ ' ' } );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN string_type const&
        top_level_indent_str() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN string_char_type const*
        top_level_indent() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_type set_top_level_indent(
            string_type const& SIXTRL_RESTRICT_REF top_level_indent_str );

        SIXTRL_HOST_FN status_type set_top_level_indent_detailed(
            size_type const top_level_indent_size,
            string_char_type const fill_char = string_char_type{ ' ' } );

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN string_type const&
        def_block_str() const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN string_char_type const*
        def_block() const SIXTRL_NOEXCEPT;

        protected:

        SIXTRL_HOST_FN BaseDefineBlockCompileOptions(
            backend_id_t const backend_id );

        SIXTRL_HOST_FN BaseDefineBlockCompileOptions(
            BaseDefineBlockCompileOptions const&
                SIXTRL_RESTRICT_REF other ) = default;

        SIXTRL_HOST_FN BaseDefineBlockCompileOptions(
            BaseCompileOptions const& SIXTRL_RESTRICT_REF other );

        SIXTRL_HOST_FN BaseDefineBlockCompileOptions(
            BaseDefineBlockCompileOptions&& other ) = default;

        SIXTRL_HOST_FN BaseDefineBlockCompileOptions& operator=(
            BaseDefineBlockCompileOptions const&
                SIXTRL_RESTRICT_REF rhs ) = default;

        SIXTRL_HOST_FN BaseDefineBlockCompileOptions& operator=(
            BaseCmdLineCompileOptions const& SIXTRL_RESTRICT_REF rhs );

        SIXTRL_HOST_FN BaseDefineBlockCompileOptions& operator=(
            BaseDefineBlockCompileOptions&& rhs ) = default;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN void do_clear() override;

        SIXTRL_HOST_FN status_type do_insert_item( stored_item_type item_to_add,
            const_iterator predecessor_item) override;

        SIXTRL_HOST_FN status_type do_commit() override;

        SIXTRL_HOST_FN status_type do_print(
            std::ostream& SIXTRL_RESTRICT_REF out_str ) const override;

        private:

        string_type m_block_indent_str =
            base_item_t::DEFAULT_BLOCK_INDENT_STR;

        string_type m_top_level_indent_str =
            base_item_t::DEFAULT_TOP_LEVEL_INDENT_STR;

        string_type m_print_separator = string_type{ "\r\n" };
        string_type m_def_block_string = string_type{};
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

typedef SIXTRL_CXX_NAMESPACE::BaseCompileOptionItem
        NS(BaseCompileOptionItem);

typedef SIXTRL_CXX_NAMESPACE::BaseCmdLineCompileOptions
        NS(BaseCmdLineCompileOptions);

typedef SIXTRL_CXX_NAMESPACE::BaseDefineBlockCompileOptions
        NS(BaseDefineBlockCompileOptions);

#else /* C */

typedef struct NS(BaseCompileOptionItem);
typedef struct NS(BaseCompileOptionItem) NS(BaseCompileOptionItem);

struct NS(BaseCmdLineCompileOptions);
typedef struct NS(BaseCmdLineCompileOptions) NS(BaseCmdLineCompileOptions);

struct NS(BaseDefineBlockCompileOptions);
typedef struct NS(BaseDefineBlockCompileOptions)
        NS(BaseDefineBlockCompileOptions);

#endif /* C / C++ */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!                Exported Plugin C-API :: Functions               !!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

SIXTRL_BASE_EXPORT_API void NS(CompileOptionItem_delete)(
    NS(BaseCompileOptionItem)* SIXTRL_RESTRICT item ) SIXTRL_NOEXCEPT;

SIXTRL_BASE_EXPORT_API void NS(CmdLineCompileOptions_delete)(
    NS(BaseCompileOptionItem)* SIXTRL_RESTRICT item ) SIXTRL_NOEXCEPT;

SIXTRL_BASE_EXPORT_API void NS(DefBlockCompileOptions_delete)(
    NS(BaseCompileOptionItem)* SIXTRL_RESTRICT item ) SIXTRL_NOEXCEPT;

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_BASE_PROGRAM_COMPILE_OPTIONS_H__ */
