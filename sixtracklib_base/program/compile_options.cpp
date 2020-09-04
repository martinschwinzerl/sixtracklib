#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/program/compile_options.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cstring>
    #include <sstream>
    #include <string>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        namespace st    = SIXTRL_CXX_NAMESPACE;
        using item_t    = st::BaseCompileOptionItem;
        using size_t    = item_t::size_type;
        using string_t  = item_t::string_type;
        using char_t    = item_t::string_char_type;
        using status_t  = item_t::status_type;

        using base_options_t      = st::BaseCompileOptions;
        using def_block_options_t = st::BaseDefineBlockCompileOptions;
        using cmd_line_options_t  = st::BaseCmdLineCompileOptions;
    }

    /* ********************************************************************* */

    constexpr item_t::kind_type item_t::KIND_DEFINE;
    constexpr item_t::kind_type item_t::KIND_UNDEF;
    constexpr item_t::kind_type item_t::KIND_INCLUDE_DIR;
    constexpr item_t::kind_type item_t::KIND_UNSPECIFIED;
    constexpr item_t::kind_type item_t::KIND_UNSPECIFIED_LONG;
    constexpr item_t::kind_type item_t::KIND_ILLEGAL;

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    constexpr item_t::string_char_type item_t::DEFAULT_BLOCK_INDENT_STR[];
    constexpr item_t::string_char_type item_t::DEFAULT_TOP_LEVEL_INDENT_STR[];

    /* ===================================================================== */

    string_t const& item_t::name_str() const SIXTRL_NOEXCEPT {
        return this->m_name; }

    char_t const* item_t::name() const SIXTRL_NOEXCEPT {
        return this->m_name.c_str(); }

    status_t item_t::set_name( string_t const& SIXTRL_RESTRICT_REF name ) {
        this->m_name = name; return st::STATUS_SUCCESS; }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    string_t const& item_t::prefix_str() const SIXTRL_NOEXCEPT {
        return this->m_prefix; }

    char_t const* item_t::prefix() const SIXTRL_NOEXCEPT {
        return this->m_prefix.c_str(); }

    status_t item_t::set_prefix(
        string_t const& SIXTRL_RESTRICT_REF prefix_str ) {
        this->m_prefix = prefix_str; return st::STATUS_SUCCESS; }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    string_t const& item_t::separator_str() const SIXTRL_NOEXCEPT {
        return this->m_separator; }

    char_t const* item_t::separator() const SIXTRL_NOEXCEPT {
        return this->m_separator.c_str(); }

    status_t item_t::set_separator(
        string_t const& SIXTRL_RESTRICT_REF separator_str ) {
        this->m_separator = separator_str; return st::STATUS_SUCCESS; }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    bool item_t::has_value() const SIXTRL_NOEXCEPT {
        return ( ( !this->m_value.empty() ) ||
                 ( this->m_value_needs_quotes ) ); }

    string_t const& item_t::value_str() const SIXTRL_NOEXCEPT {
        return this->m_value; }

    char_t const* item_t::value() const SIXTRL_NOEXCEPT {
        return this->m_value.c_str(); }

    status_t item_t::set_value(
        string_type const& SIXTRL_RESTRICT_REF value_str ) {
        this->m_value = value_str; return st::STATUS_SUCCESS; }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    bool item_t::value_needs_quotes() const SIXTRL_NOEXCEPT {
        return this->m_value_needs_quotes; }

    status_t item_t::set_value_needs_quotes(
        bool const needs_quotes ) SIXTRL_NOEXCEPT {
        this->m_value_needs_quotes = needs_quotes;
        return st::STATUS_SUCCESS; }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    bool item_t::is_define_macro() const SIXTRL_NOEXCEPT {
        return ( this->m_macro_kind == item_t::KIND_DEFINE ); }

    bool item_t::is_undef_macro() const SIXTRL_NOEXCEPT {
        return ( this->m_macro_kind == item_t::KIND_UNDEF ); }

    bool item_t::is_include_dir_macro() const SIXTRL_NOEXCEPT {
        return ( this->m_macro_kind == item_t::KIND_INCLUDE_DIR ); }

    bool item_t::is_unspecified_macro() const SIXTRL_NOEXCEPT {
        return ( this->m_macro_kind == item_t::KIND_UNSPECIFIED ); }

    bool item_t::is_unspecified_long_macro() const SIXTRL_NOEXCEPT {
        return ( this->m_macro_kind == item_t::KIND_UNSPECIFIED_LONG ); }

    item_t::kind_type item_t::macro_kind() const SIXTRL_NOEXCEPT {
        return this->m_macro_kind; }

    st_status_t item_t::set_macro_kind( item_t::kind_type const
        macro_kind ) SIXTRL_NOEXCEPT {
            this->m_macro_kind = macro_kind;
            return st::STATUS_SUCCESS; }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    string_t item_t::to_cmd_line_string() const {
        std::ostringstream a2str;
        status_t const status = this->do_print_cmd_line( a2str );
        return ( status == st::STATUS_SUCCESS )
            ? a2str.str() : string_type{}; }

    size_t item_t::required__cmd_line_string_capacity() const {
        string_t const temp_str( this->to_cmd_line_string() );
        return temp_str.size() + size_t{ 1 }; }

    status_t item_t::to_cmd_line_string( char_t* SIXTRL_RESTRICT out_str_buffer,
        size_t const out_str_buffer_capacity ) const
    {
        status_t status = st::STATUS_GENERAL_FAILURE;
        string_type const temp( this->to_cmd_line_string() );

        if( ( out_str_buffer != nullptr ) &&
            ( out_str_buffer_capacity > size_t{ 0 } ) )
        {
            std::memset( out_str_buffer, ( int )'\0', out_str_buffer_capacity );

            if( ( !temp.empty() ) && ( temp.size() < out_str_buffer_capacity ) )
            {
                std::strncpy( out_str_buffer, temp.c_str(),
                                out_str_buffer_capacity - 1u );

                status = st::STATUS_SUCCESS;
            }
        }

        return status;
    }

    status_t item_t::print_cmd_line(
        std::ostream& SIXTRL_RESTRICT_REF out_str ) const
    {
        return this->do_print_cmd_line( out_str );
    }

    string_t item_t::to_define_block_string(
        string_t const& SIXTRL_RESTRICT_REF block_indent_str,
        string_t const& SIXTRL_RESTRICT_REF top_level_indent_str ) const {
        std::ostringstream a2str;
        status_t const status = this->do_print_define_block(
            a2str, block_indent_str, top_level_indent_str );
        return ( status == st::STATUS_SUCCESS ) ? a2str.str() : string_t{};
    }

    size_t item_t::required_define_block_string_capacity(
        string_t const& SIXTRL_RESTRICT_REF block_indent_str,
        string_t const& SIXTRL_RESTRICT_REF top_level_indent_str ) const {
        item_t::string_type const temp( this->to_define_block_string(
            block_indent_str, top_level_indent_str ) );
        return temp.size() + size_t{ 1 };
    }

    status_t item_t::to_define_block_string(
        char_t* SIXTRL_RESTRICT out_str_buffer,
        size_t const out_str_buffer_capacity,
        string_t const& SIXTRL_RESTRICT_REF block_indent_str,
        string_t const& SIXTRL_RESTRICT_REF top_level_indent_str ) const {

        status_t status = st::STATUS_GENERAL_FAILURE;
        string_type const temp( this->to_define_block_string(
            block_indent_str, top_level_indent_str ) );

        if( ( out_str_buffer != nullptr ) &&
            ( out_str_buffer_capacity > size_t{ 0 } ) )
        {
            std::memset( out_str_buffer, ( int )'\0', out_str_buffer_capacity );

            if( ( !temp.empty() ) && ( temp.size() < out_str_buffer_capacity ) )
            {
                std::strncpy( out_str_buffer, temp.c_str(),
                                out_str_buffer_capacity - 1u );

                status = st::STATUS_SUCCESS;
            }
        }

        return status;
    }

    status_t item_t::print_define_block(
        std::ostream& SIXTRL_RESTRICT_REF out_str,
        string_t const& SIXTRL_RESTRICT_REF block_indent_str,
        string_t const& SIXTRL_RESTRICT_REF top_level_indent_str ) const {
        return this->do_print_define_block(
            out_str, block_indent_str, top_level_indent_str ); }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    item_t::stored_base_item_type item_t::clone() const {
        return this->do_clone(); }

    /* ===================================================================== */

    item_t::BaseCompileOptionItem(
        item_t::backend_id_t const backend_id ) :
        st::BaseBackendObj( backend_id,
            st::CLASS_ID_PROGRAM_COMPILE_OPTION_ITEM ) {}

    status_t item_t::do_print_cmd_line(
        std::ostream& SIXTRL_RESTRICT_REF out_str ) const
    {
        status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( ( this->is_define_macro() ) ||
              ( this->is_unspecified_macro() ) ||
              ( this->is_unspecified_long_macro() ) ) &&
            ( !this->name_str().empty() ) &&
            ( !this->prefix_str().empty() ) &&
            ( ( !this->separator_str().empty() ) ||
              ( !this->value_str().empty() ) ||
              ( !this->value_needs_quotes() ) ) )
        {
            out_str << this->prefix_str() << this->name_str()
                    << this->separator_str();

            if( this->value_needs_quotes() ) out_str << "\"";
            out_str << this->value_str();
            if( this->value_needs_quotes() ) out_str << "\"";
            status = st::STATUS_SUCCESS;
        }
        else if( ( this->is_undef_macro() ) && ( !this->name_str().empty() ) &&
            ( !this->prefix_str().empty() ) )
        {
            out_str << this->prefix_str() << this->name_str();
            status = st::STATUS_SUCCESS;
        }
        else if( ( this->is_include_dir_macro() ) &&
                 ( !this->value_str().empty() ) )
        {
            out_str << this->prefix_str() << this->separator_str();

            if( this->value_needs_quotes() ) out_str << "\"";
            out_str << this->value_str();
            if( this->value_needs_quotes() ) out_str << "\"";
            status = st::STATUS_SUCCESS;
        }

        return status;
    }

    status_t item_t::do_print_define_block(
        std::ostream& SIXTRL_RESTRICT_REF out_str,
        string_t const& SIXTRL_RESTRICT_REF block_indent_str,
        string_t const& SIXTRL_RESTRICT_REF top_level_indent_str ) const {
        status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( ( this->is_define_macro() ) ||
              ( this->is_undef_macro() ) ) &&
            ( !this->name_str().empty() ) &&
            ( !this->is_always_cmd_line_flag() ) )
        {
            if( this->is_define_macro() )
            {
                out_str << top_level_indent_str
                        << "#if !defined( " << this->name_str() << " )\r\n"
                        << top_level_indent_str << block_indent_str
                        << "#define " << this->name_str();

                if( ( !this->value_str().empty() ) ||
                    ( this->value_needs_quotes() ) )
                {
                    out_str << " ";

                    if( !this->value_needs_quotes() )
                    {
                        out_str << this->value_str();
                    }
                    else
                    {
                        out_str << "\"" << this->value_str() << "\"";
                    }
                }

                out_str << "\r\n"
                        << top_level_indent_str << "#endif /* !defined( "
                        << this->name_str() << " ) */\r\n";

                status = st::STATUS_SUCCESS;
            }
            else if( this->is_undef_macro() )
            {
                out_str << top_level_indent_str
                        << "#if defined( " << this->name_str() << " )\r\n"
                        << top_level_indent_str << block_indent_str
                        << "#undef " << this->m_name << "\r\n"
                        << top_level_indent_str
                        << "#endif /* defined( " << this->name_str()
                        << " )\r\n";

                status = st::STATUS_SUCCESS;
            }
        }

        return status;
    }

    item_t::stored_base_item_type item_t::do_clone() const {
        return stored_base_item_type{
            new item_t( *this ), item_t::DELETE_BASE_ITEM }; }

    /* ********************************************************************* */

    constexpr base_options_t::class_variant_t
        base_options_t::COMPILE_OPTIONS_VARIANT_DEFAULT;

    constexpr base_options_t::class_variant_t
        base_options_t::COMPILE_OPTIONS_VARIANT_CMD_LINE;

    constexpr base_options_t::class_variant_t
        base_options_t::COMPILE_OPTIONS_VARIANT_DEFINE_BLOCK;

    /* ===================================================================== */

    bool base_options_t::is_cmd_line_options_store() const SIXTRL_NOEXCEPT {
        bool const is_cmd_line_options_store_flag = this->is_class_variant(
            base_options_t::COMPILE_OPTIONS_VARIANT_CMD_LINE );

        SIXTRL_ASSERT(
            ( (  is_cmd_line_options_store_flag ) &&
              ( !this->is_define_block_options_store() ) ) ||
            ( ( !is_cmd_line_options_store_flag ) &&
              (  this->is_define_block_options_store() ) ) ||
            ( ( !is_cmd_line_options_store_flag ) &&
              ( !this->is_define_block_options_store() ) ) );

        return is_cmd_line_options_store_flag;
    }

    cmd_line_options_t const*
    base_options_t::as_cmd_line_options_store() const SIXTRL_NOEXCEPT {
        return ( this->is_cmd_line_options_store() )
            ? static_cast< cmd_line_options_t const* >( this ) : nullptr; }

    cmd_line_options_t*
    base_options_t::as_cmd_line_options_store() SIXTRL_NOEXCEPT {
        return const_cast< cmd_line_options_t* >( static_cast<
            base_options_t const* >( this )->as_cmd_line_options_store() ); }

    /* --------------------------------------------------------------------- */

    bool base_options_t::is_define_block_options_store() const SIXTRL_NOEXCEPT
    {
        bool const is_define_block_store = this->is_class_variant(
            base_options_t::COMPILE_OPTIONS_VARIANT_DEFINE_BLOCK );

        SIXTRL_ASSERT(
            ( (  is_define_block_store ) &&
              ( !this->is_cmd_line_options_store() ) ) ||
            ( ( !is_define_block_store ) &&
              (  this->is_cmd_line_options_store() ) ) ||
            ( ( !is_define_block_store ) &&
              ( !this->is_cmd_line_options_store() ) ) );

        return is_define_block_store;
    }

    def_block_options_t const*
    base_options_t::as_define_block_compile_options() const SIXTRL_NOEXCEPT {
        return ( this->is_define_block_options_store() )
            ? static_cast< def_block_options_t const* >( this ) : nullptr; }

    def_block_options_t*
    base_options_t::as_define_block_compile_options() SIXTRL_NOEXCEPT {
        return const_cast< def_block_options_t* >( static_cast< base_options_t
            const* >( this )->as_define_block_compile_options() ); }

    /* --------------------------------------------------------------------- */

    size_t base_options_t::num_stored_items() const SIXTRL_NOEXCEPT {
        return this->m_stored_items.size(); }

    item_t const*
    base_options_t::item( size_t const idx ) const SIXTRL_NOEXCEPT {
        return ( idx < this->m_stored_items.size() )
            ? this->m_stored_items[ idx ].get() : nullptr; }

    item_t* base_options_t::item( size_t const idx ) SIXTRL_NOEXCEPT {
        return ( idx < this->m_stored_items.size() )
            ? this->m_stored_items[ idx ].get() : nullptr; }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    st_status_t base_options_t::append(
        base_options_t::stored_item_type item_to_append ) {
        return this->do_insert_item( std::move( item_to_append ),
            this->m_stored_items.end() );
    }

    st_status_t base_options_t::prepend(
        base_options_t::stored_item_type item_to_preprend ) {
        return this->do_insert_item( std::move( item_to_preprend ),
            this->m_stored_items.begin() );
    }

    st_status_t base_options_t::insert_at_pos( base_options_t::stored_item_type
        item_to_add, size_type const at_pos ) {
        st_status_t status = st::STATUS_GENERAL_FAILURE;
        size_t const nn = this->num_stored_items();

        if( ( at_pos == nn ) || ( at_pos + size_t{ 1 } == nn ) )
        {
            status = this->do_insert_item( std::move( item_to_add ),
                this->m_stored_items.cend() );
        }
        else if( at_pos + size_t{ 1 } < nn )
        {
            auto insert_before_this_item = this->m_stored_items.cbegin();
            std::advance( insert_before_this_item, at_pos + size_t{ 1 } );
            status = this->do_insert_item( std::move(
                item_to_add ), insert_before_this_item );
        }

        return status;
    }

    st_status_t base_options_t::remove( size_t const at_pos ) {
        st_status_t status = st::STATUS_GENERAL_FAILURE;
        if( at_pos < this->m_stored_items.size() )
        {
            auto it = this->m_stored_items.begin();
            std::advance( it, at_pos );
            status = this->do_remove_item( it );
        }

        return status;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    void base_options_t::clear() { this->do_clear(); }

    bool base_options_t::is_committed() const SIXTRL_NOEXCEPT {
        return this->m_is_committed; }

    st_status_t base_options_t::commit() { return this->do_commit(); }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    size_t base_options_t::find_next_by_kind(
        base_options_t::item_kind_type const item_kind,
        size_t const start_pos ) const SIXTRL_NOEXCEPT {

        size_t const nn = this->num_stored_items();
        size_t next_pos = nn;

        if( ( item_kind != st::PROGRAM_COMP_OPTION_KIND_ILLEGAL ) &&
            ( start_pos < nn ) )
        {
            using stored_item_t = base_options_t::stored_item_type;

            auto start_it = this->m_stored_items.begin();
            std::advance( start_it, start_pos );

            auto found_it = std::find_if( start_it, this->m_stored_items.end(),
                [item_kind]( stored_item_t const& ptr_test ) -> bool
                {
                    return ( ( ptr_test.get() != nullptr ) &&
                             ( ptr_test->macro_kind() == item_kind ) ); } );

            if( found_it != this->m_stored_items.end() )
            {
                next_pos = std::distance( this->m_stored_items.begin(),
                                          found_it );
                SIXTRL_ASSERT( next_pos < nn );
            }
        }

        return next_pos;
    }

    bool base_options_t::has_items_by_kind(
        base_options_t::item_kind_type const item_kind ) const SIXTRL_NOEXCEPT {
        return ( this->find_next_by_kind( item_kind, 0u ) <
                 this->m_stored_items.size() ); }

    size_t base_options_t::num_items_by_kind(
        base_options_t::item_kind_type const item_kind ) const SIXTRL_NOEXCEPT {
        size_t num_items = size_t{ 0 };
        size_t const nn = this->num_stored_items();
        size_t next_pos = size_t{ 0 };

        while( next_pos < nn )
        {
            next_pos = this->find_next_by_kind( item_kind, next_pos );
            SIXTRL_ASSERT( ( next_pos >= nn ) ||
                ( ( this->item( next_pos ) != nullptr ) &&
                  ( this->item( next_pos )->macro_kind() == item_kind ) ) );

            if( next_pos < nn ) ++num_items;
            ++next_pos;
        }

        return num_items;
    }

    size_t base_options_t::item_pos_by_kind(
        size_t const* SIXTRL_RESTRICT item_pos_begin,
        size_t const max_num_item_pos_entries,
        base_options_t::item_kind_type const item_kind ) const SIXTRL_NOEXCEPT {
        size_t const* item_pos_end = item_pos_begin;
        if( item_pos_end != nullptr )
            std::advance( item_pos_end, max_num_item_pos_entries );
        return this->item_pos_by_kind(
            item_pos_begin, item_pos_end, item_kind );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    size_t base_options_t::find_next_by_name(
        string_t const& SIXTRL_RESTRICT_REF cmp_name,
        size_t const start_pos ) const SIXTRL_NOEXCEPT {
        size_t const nn = this->num_stored_items();
        size_t next_pos = nn;

        if( ( !cmp_name.empty() ) && ( start_pos < nn ) )
        {
            using stored_item_t = base_options_t::stored_item_type;

            auto start_it = this->m_stored_items.begin();
            std::advance( start_it, start_pos );

            auto found_it = std::find_if( start_it, this->m_stored_items.end(),
                [&cmp_name]( stored_item_t const& ptr_test ) -> bool
                {
                    return ( ( ptr_test.get() != nullptr ) &&
                        ( !ptr_test->name_str().empty() ) &&
                        (  ptr_test->name_str().compare( cmp_name ) == 0 ) ); }
            );

            if( found_it != this->m_stored_items.end() )
            {
                next_pos = std::distance(
                    this->m_stored_items.begin(), found_it );
                SIXTRL_ASSERT( next_pos < nn );
            }
        }

        return next_pos;
    }

    bool base_options_t::has_items_by_name(
        string_t const& SIXTRL_RESTRICT_REF name ) const SIXTRL_NOEXCEPT {
        return ( this->find_next_by_name( name, 0u ) <
                 this->num_stored_items() );
    }

    size_t base_options_t::num_items_by_name(
        string_t const& SIXTRL_RESTRICT_REF name ) const SIXTRL_NOEXCEPT {
        size_t num_items = size_t{ 0 };
        size_t const nn = this->num_stored_items();
        size_t next_pos = size_t{ 0 };

        while( next_pos < nn )
        {
            next_pos = this->find_next_by_name( name, next_pos );
            SIXTRL_ASSERT( ( next_pos >= nn ) ||
                ( ( this->item( next_pos ) != nullptr ) &&
                  ( this->item( next_pos )->name_str().compare(
                      name ) == 0 ) ) );

            if( next_pos < nn ) ++num_items;
            ++next_pos;
        }

        return num_items;
    }

    size_t base_options_t::item_pos_by_name(
        size_t const* SIXTRL_RESTRICT item_pos_begin,
        size_t const max_num_item_pos_entries,
        string_t const& SIXTRL_RESTRICT_REF name ) const SIXTRL_NOEXCEPT {
        size_t const* item_pos_end = item_pos_begin;
        if( item_pos_end != nullptr )
            std::advance( item_pos_end, max_num_item_pos_entries );
        return this->item_pos_by_name( item_pos_begin, item_pos_end, name );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    string_t base_options_t::to_string() const {
        std::ostringstream a2str;
        st_status_t const status = this->do_print( a2str );
        return ( status == st::STATUS_SUCCESS ) ? a2str.str() : string_t{};
    }

    size_t base_options_t::required_string_capacity() const {
        std::ostringstream a2str;
        st_status_t const status = this->do_print( a2str );
        return ( status == st::STATUS_SUCCESS )
            ? a2str.str().size() + size_t{ 1 } : st_size_t{ 0 };
    }

    st_status_t base_options_t::to_string(
        base_options_t::string_char_type* SIXTRL_RESTRICT out_str_buffer,
        size_t const out_str_buffer_capacity ) const {
        st_status_t status = st::STATUS_GENERAL_FAILURE;
        if( ( out_str_buffer != nullptr ) &&
            ( out_str_buffer_capacity > st_size_t{ 0 } ) )
        {
            std::memset( out_str_buffer, ( int )'\0', out_str_buffer_capacity );
            std::ostringstream a2str;
            if( this->do_print( a2str ) == st::STATUS_SUCCESS )
            {
                string_t const temp = a2str.str();
                if( temp.size() <= out_str_buffer_capacity )
                {
                    std::strncpy( out_str_buffer, temp.c_str(),
                                  out_str_buffer_capacity - st_size_t{ 1 } );
                    status = st::STATUS_SUCCESS;
                }
            }
        }
        return status;
    }

    st_status_t base_options_t::print(
        std::ostream& SIXTRL_RESTRICT_REF ostr ) const {
        return this->do_print( ostr );
    }

    /* ===================================================================== */

    base_options_t::BaseCompileOptions(
        base_options_t::backend_id_t const backend_id,
        base_options_t::class_variant_t const variant ) :
        st::BaseBackendObj( backend_id, st::CLASS_ID_PROGRAM_COMPILE_OPTIONS,
            variant ), m_stored_items()
    {
    }

    base_options_t::BaseCompileOptions(
        BaseCompileOptions const& SIXTRL_RESTRICT_REF other ) :
        st::BaseBackendObj( other ), m_stored_items()
    {
        st_status_t status = this->do_insert_range_of_input_items_base_impl(
            other.m_stored_items.begin(), other.m_stored_items.end(),
                this->m_stored_items.cend() );

        if( status == st::STATUS_SUCCESS )
        {
            if( other.is_committed() )
            {
                status = this->do_commit_base_impl();
            }
            else
            {
                this->update_is_committed_flag( false );
            }
        }

        SIXTRL_ASSERT( status == st::STATUS_SUCCESS );
        ( void )status;
    }

    BaseCompileOptions& base_options_t::operator=(
        BaseCompileOptions const& SIXTRL_RESTRICT_REF rhs ) {

        if( this != &rhs )
        {
            st_status_t status =
                this->do_insert_range_of_input_items_base_impl(
                    rhs.m_stored_items.begin(), rhs.m_stored_items.end(),
                        this->m_stored_items.cend() );

            if( rhs.is_committed() )
            {
                status = this->do_commit();
            }
            else
            {
                this->update_is_committed_flag( false );
            }

            SIXTRL_ASSERT( status == st::STATUS_SUCCESS );
            ( void )status;
        }

        return *this;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    void base_options_t::do_clear() { this->m_stored_items.clear(); }

    st_status_t base_options_t::do_insert_item(
        base_options_t::stored_item_type item_to_add,
        base_options_t::const_iterator insert_before_this_item ) {
        return this->do_insert_item_base_impl(
            std::move( item_to_add ), insert_before_this_item ); }

    st_status_t base_options_t::do_insert_range_of_input_items(
        base_options_t::const_iterator in_item_begin,
        base_options_t::const_iterator in_item_end,
        base_options_t::const_iterator insert_before_this_item ) {
        return this->do_insert_range_of_input_items_base_impl(
            in_item_begin, in_item_end, insert_before_this_item );
    }


    st_status_t base_options_t::do_remove_item(
        base_options_t::iterator item_iter )
    {
        this->m_stored_items.erase( item_iter );
        this->m_is_committed = false;
        return st::STATUS_SUCCESS;
    }

    st_status_t base_options_t::do_commit() {
        return this->do_commit_base_impl();
    }

    void base_options_t::update_is_committed_flag( bool const is_committed
        ) SIXTRL_NOEXCEPT { this->m_is_committed = is_committed; }

    st_status_t base_options_t::do_insert_range_of_input_items_base_impl(
        base_options_t::const_iterator in_item_it,
        base_options_t::const_iterator in_item_end,
        base_options_t::const_iterator insert_before_this_item ) {

        st_status_t status = st::STATUS_SUCCESS;
        for( ; in_item_it != in_item_end ; ++in_item_it )
        {
            if( in_item_it->get() == nullptr )
            {
                status = st::STATUS_GENERAL_FAILURE;
                break;
            }

            status = this->do_insert_item_base_impl(
                    ( *in_item_it )->clone(), insert_before_this_item );

            if( status != st::STATUS_SUCCESS ) break;
        }

        return status;
    }

    st_status_t base_options_t::do_insert_item_base_impl(
        base_options_t::stored_item_type item_to_add,
        base_options_t::const_iterator insert_before_this_item ) {

        st_status_t status = st::STATUS_GENERAL_FAILURE;
        bool const is_cmd_line_store = this->is_cmd_line_options_store();
        bool const is_def_block_store = this->is_define_block_options_store();

        SIXTRL_ASSERT(
            ( ( !is_cmd_line_store ) && (  is_def_block_store ) ) ||
            ( (  is_cmd_line_store ) && ( !is_def_block_store ) ) ||
            ( ( !is_cmd_line_store ) && ( !is_def_block_store ) ) );

        /* This should never happen, but to avoid a segfault ...  */
        if( ( item_to_add.get() != nullptr ) &&
            ( item_to_add->macro_kind() != item_t::KIND_ILLEGAL ) &&
            ( ( is_cmd_line_store ) ||
              ( ( is_def_block_store ) &&
                ( !item_to_add->is_always_cmd_line_flag() ) &&
                ( ( item_to_add->is_define_macro() ) ||
                  ( item_to_add->is_undef_macro() ) ) ) ) )
        {
            auto ret = this->m_stored_items.insert( insert_before_this_item,
                 base_options_t::stored_item_type{
                     nullptr, item_to_add.get_deleter() } );

            if( ret != this->m_stored_items.end() )
            {
                *ret = std::move( item_to_add );
                this->m_is_committed = false;
                status = st::STATUS_SUCCESS;
            }
        }

        return status;
    }

    st_status_t base_options_t::do_commit_base_impl() {
        this->update_is_committed_flag( true );
        return st::STATUS_SUCCESS;
    }

    /* ********************************************************************* */

    cmd_line_options_t::string_type const&
    cmd_line_options_t::define_macro_prefix_str() const SIXTRL_NOEXCEPT {
        return this->m_define_macro_prefix; }

    cmd_line_options_t::string_char_type const*
    cmd_line_options_t::define_macro_prefix() const SIXTRL_NOEXCEPT {
        return this->m_define_macro_prefix.c_str(); }

    cmd_line_options_t::status_type cmd_line_options_t::set_define_macro_prefix(
        cmd_line_options_t::string_type const& SIXTRL_RESTRICT_REF prefix_str )
    {
        this->m_define_macro_prefix = prefix_str;
        return st::STATUS_SUCCESS;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    cmd_line_options_t::string_type const&
    cmd_line_options_t::define_macro_separator_str() const SIXTRL_NOEXCEPT {
        return this->m_define_macro_separator; }

    cmd_line_options_t::string_char_type const*
    cmd_line_options_t::define_macro_separator() const SIXTRL_NOEXCEPT {
        return this->m_define_macro_separator.c_str(); }

    cmd_line_options_t::status_type
    cmd_line_options_t::set_define_macro_separator(
        string_t const& SIXTRL_RESTRICT_REF separator_str ) {
        this->m_define_macro_separator = separator_str;
        return st::STATUS_SUCCESS; }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    cmd_line_options_t::string_type const&
    cmd_line_options_t::undef_macro_prefix_str() const SIXTRL_NOEXCEPT {
        return this->m_undef_macro_prefix; }

    cmd_line_options_t::string_char_type const*
    cmd_line_options_t::undef_macro_prefix() const SIXTRL_NOEXCEPT {
        return this->m_undef_macro_prefix.c_str(); }

    cmd_line_options_t::status_type cmd_line_options_t::set_undef_macro_prefix(
        cmd_line_options_t::string_type const& SIXTRL_RESTRICT_REF prefix_str ) {
        this->m_undef_macro_prefix = prefix_str; return st::STATUS_SUCCESS; }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    cmd_line_options_t::string_type const&
    cmd_line_options_t::include_dir_macro_prefix_str() const SIXTRL_NOEXCEPT {
        return this->m_include_dir_macro_prefix; }

    cmd_line_options_t::string_char_type const*
    cmd_line_options_t::include_dir_macro_prefix() const SIXTRL_NOEXCEPT {
        return this->m_include_dir_macro_prefix.c_str(); }

    st_status_t cmd_line_options_t::set_include_dir_macro_prefix(
        string_t const& SIXTRL_RESTRICT_REF prefix_str ) {
        this->m_include_dir_macro_prefix = prefix_str;
        return st::STATUS_SUCCESS; }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    cmd_line_options_t::string_type const&
    cmd_line_options_t::unspec_macro_prefix_str() const SIXTRL_NOEXCEPT {
        return this->m_unspec_macro_prefix; }

    cmd_line_options_t::string_char_type const*
    cmd_line_options_t::unspec_macro_prefix() const SIXTRL_NOEXCEPT {
        return this->m_unspec_macro_prefix.c_str(); }

    cmd_line_options_t::status_type cmd_line_options_t::set_unspec_macro_prefix(
        string_t const& SIXTRL_RESTRICT_REF prefix_str ) {
        this->m_unspec_macro_prefix = prefix_str; return st::STATUS_SUCCESS; }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    string_t const&
    cmd_line_options_t::unspec_macro_separator_str() const SIXTRL_NOEXCEPT {
        return this->m_unspec_macro_separator; }

    cmd_line_options_t::string_char_type const*
    cmd_line_options_t::unspec_macro_separator() const SIXTRL_NOEXCEPT {
        return this->m_unspec_macro_separator.c_str(); }

    st_status_t cmd_line_options_t::set_unspec_macro_separator(
        string_t const& SIXTRL_RESTRICT_REF separator_str ){
        this->m_unspec_macro_separator = separator_str;
        return st::STATUS_SUCCESS; }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    string_t const&
    cmd_line_options_t::unspec_long_macro_prefix_str() const SIXTRL_NOEXCEPT {
        return this->m_unspec_long_macro_prefix; }

    cmd_line_options_t::string_char_type const*
    cmd_line_options_t::unspec_long_macro_prefix() const SIXTRL_NOEXCEPT {
        return this->m_unspec_long_macro_prefix.c_str(); }

    st_status_t cmd_line_options_t::set_unspec_long_macro_prefix(
        string_t const& SIXTRL_RESTRICT_REF prefix_str ) {
        this->m_unspec_long_macro_prefix = prefix_str;
        return st::STATUS_SUCCESS; }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    string_t const&
    cmd_line_options_t::unspec_long_macro_separator_str() const SIXTRL_NOEXCEPT
    { return this->m_unspec_long_macro_separator; }

    cmd_line_options_t::string_char_type const*
    cmd_line_options_t::unspec_long_macro_separator() const SIXTRL_NOEXCEPT {
        return this->m_unspec_long_macro_separator.c_str(); }

    st_status_t cmd_line_options_t::set_unspec_long_macro_separator(
        string_t const& SIXTRL_RESTRICT_REF separator_str ) {
        this->m_unspec_long_macro_separator = separator_str;
        return st::STATUS_SUCCESS; }

    /* ===================================================================== */

    cmd_line_options_t::BaseCmdLineCompileOptions(
        cmd_line_options_t::backend_id_t const backend_id ) :
        SIXTRL_CXX_NAMESPACE::BaseCompileOptions( backend_id,
            base_options_t::COMPILE_OPTIONS_VARIANT_CMD_LINE )
    {
    }

    cmd_line_options_t::BaseCmdLineCompileOptions(
        BaseCompileOptions const& SIXTRL_RESTRICT_REF other ) :
        SIXTRL_CXX_NAMESPACE::BaseCompileOptions( other.backend_id(),
        base_options_t::COMPILE_OPTIONS_VARIANT_CMD_LINE )
    {
        base_options_t::operator=( other );
    }

    cmd_line_options_t& cmd_line_options_t::operator=(
            def_block_options_t const& SIXTRL_RESTRICT_REF rhs ) {
        this->clear();
        base_options_t::operator=( rhs );
        return *this;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    st_status_t cmd_line_options_t::do_insert_item(
        cmd_line_options_t::stored_item_type item_to_add,
        cmd_line_options_t::const_iterator insert_before_this_item) {

        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( item_to_add.get() != nullptr )
        {
            if( (  item_to_add->is_define_macro() ) &&
                ( !item_to_add->name_str().empty() ) )
            {
                status = st::STATUS_SUCCESS;

                if( item_to_add->prefix_str().empty() )
                {
                    status |= ( !this->define_macro_prefix_str().empty() )
                        ? item_to_add->set_prefix(
                            this->define_macro_prefix_str() )
                        : st::STATUS_GENERAL_FAILURE;
                }

                if( item_to_add->separator_str().empty() )
                {
                    status |= ( !this->define_macro_separator_str().empty() )
                        ? item_to_add->set_separator(
                            this->define_macro_separator_str() )
                        : st::STATUS_GENERAL_FAILURE;
                }
            }
            if( (  item_to_add->is_undef_macro() ) &&
                ( !item_to_add->name_str().empty() ) )
            {
                status = st::STATUS_SUCCESS;

                if( item_to_add->prefix_str().empty() )
                {
                    status |= ( !this->undef_macro_prefix_str().empty() )
                        ? item_to_add->set_prefix(
                            this->undef_macro_prefix_str() )
                        : st::STATUS_GENERAL_FAILURE;
                }
            }
            else if( item_to_add->is_include_dir_macro() )
            {
                status = st::STATUS_SUCCESS;

                if( item_to_add->prefix_str().empty() )
                {
                    status |= ( !this->include_dir_macro_prefix_str().empty() )
                        ? item_to_add->set_prefix(
                            this->include_dir_macro_prefix_str() )
                        : st::STATUS_GENERAL_FAILURE;
                }
            }
            else if( ( item_to_add->is_unspecified_macro() )&&
                     ( !item_to_add->name_str().empty() ) )
            {
                status = st::STATUS_SUCCESS;

                if( item_to_add->prefix_str().empty() )
                {
                    status |= ( !this->unspec_macro_prefix_str().empty() )
                        ? item_to_add->set_prefix(
                            this->unspec_macro_prefix_str() )
                        : st::STATUS_GENERAL_FAILURE;
                }

                if( item_to_add->separator_str().empty() )
                {
                    status |= ( !this->unspec_macro_separator_str().empty() )
                        ? item_to_add->set_separator(
                            this->unspec_macro_separator_str() )
                        : st::STATUS_GENERAL_FAILURE;
                }
            }
            else if( ( item_to_add->is_unspecified_long_macro() )&&
                     ( !item_to_add->name_str().empty() ) )
            {
                status = st::STATUS_SUCCESS;

                if( item_to_add->prefix_str().empty() )
                {
                    status |= ( !this->unspec_long_macro_prefix_str().empty() )
                        ? item_to_add->set_prefix(
                            this->unspec_long_macro_prefix_str() )
                        : st::STATUS_GENERAL_FAILURE;
                }

                if( item_to_add->separator_str().empty() )
                {
                    status |= ( !this->unspec_long_macro_separator_str(
                            ).empty() )
                        ? item_to_add->set_separator(
                            this->unspec_long_macro_separator_str() )
                        : st::STATUS_GENERAL_FAILURE;
                }
            }
        }

        if( status == st::STATUS_SUCCESS )
        {
            status = base_options_t::do_insert_item( std::move(
                item_to_add ), insert_before_this_item );
        }

        return status;
    }

    st_status_t cmd_line_options_t::do_print(
        std::ostream& SIXTRL_RESTRICT_REF out_str ) const {
        size_t const nn = this->num_stored_items();

        st_status_t status = st::STATUS_SUCCESS;
        bool first = true;

        for( size_t ii = size_t{ 0 } ; ii < nn ; ++ii )
        {
            auto ptr_item = this->item( ii );

            if( !first ) out_str << this->m_print_separator;

            if( ptr_item != nullptr )
            {
                status = ptr_item->print_cmd_line( out_str );
                if( status == st::STATUS_SUCCESS )
                {
                    first = false;
                }
            }
        }

        return status;
    }

    /* ********************************************************************* */

    string_t const&
    def_block_options_t::block_indent_str() const SIXTRL_NOEXCEPT {
        return this->m_block_indent_str; }

    def_block_options_t::string_char_type const*
    def_block_options_t::block_indent() const SIXTRL_NOEXCEPT {
        return this->m_block_indent_str.c_str(); }

    st_status_t def_block_options_t::set_block_indent(
        string_t const& SIXTRL_RESTRICT_REF block_indent ) {
        this->m_block_indent_str = block_indent;
        return st::STATUS_SUCCESS; }

    st_status_t def_block_options_t::set_block_indent_detailed(
        size_t const block_indent_size,
        def_block_options_t::string_char_type const fill_char ) {
        string_t const block_indent( block_indent_size, fill_char );
        return this->set_block_indent( block_indent ); }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    def_block_options_t::string_type const&
    def_block_options_t::def_block_str() const SIXTRL_NOEXCEPT {
        return this->m_def_block_string;
    }

    def_block_options_t::string_char_type const*
    def_block_options_t::def_block() const SIXTRL_NOEXCEPT {
        return this->m_def_block_string.c_str();
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    string_t const& def_block_options_t::top_level_indent_str(
        ) const SIXTRL_NOEXCEPT { return this->m_top_level_indent_str; }

    def_block_options_t::string_char_type const*
    def_block_options_t::top_level_indent() const SIXTRL_NOEXCEPT {
        return this->m_top_level_indent_str.c_str(); }

    st_status_t def_block_options_t::set_top_level_indent(
        string_t const& SIXTRL_RESTRICT_REF top_level_indent_str ) {
        this->m_top_level_indent_str = top_level_indent_str;
        return st::STATUS_SUCCESS; }

    st_status_t def_block_options_t::set_top_level_indent_detailed(
        size_t const top_level_indent_size,
        def_block_options_t::string_char_type const fill_char ) {
        string_t tl_indent_str( top_level_indent_size, fill_char );
        return this->set_top_level_indent( tl_indent_str );
    }

    def_block_options_t::BaseDefineBlockCompileOptions(
        def_block_options_t::backend_id_t const backend_id ) :
        SIXTRL_CXX_NAMESPACE::BaseCompileOptions( backend_id,
            base_options_t::COMPILE_OPTIONS_VARIANT_DEFINE_BLOCK ) {}

    def_block_options_t::BaseDefineBlockCompileOptions(
        base_options_t const& SIXTRL_RESTRICT_REF other ) :
        base_options_t::BaseCompileOptions( other.backend_id(),
            base_options_t::COMPILE_OPTIONS_VARIANT_DEFINE_BLOCK )
    {
        base_options_t::operator=( other );
    }

    def_block_options_t& def_block_options_t::operator=(
        cmd_line_options_t const& SIXTRL_RESTRICT_REF rhs ) {
        this->do_clear();
        base_options_t::operator=( rhs );
        return *this; }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    void def_block_options_t::do_clear() {
        this->m_def_block_string.clear();
        base_options_t::do_clear();
    }

    st_status_t def_block_options_t::do_insert_item(
        def_block_options_t::stored_item_type item_to_add,
        def_block_options_t::const_iterator insert_before_this_item ) {

        st_status_t status = st::STATUS_GENERAL_FAILURE;

        if( (  item_to_add.get() != nullptr ) &&
            ( !item_to_add->name_str().empty() ) &&
            ( !item_to_add->is_always_cmd_line_flag() ) )
        {
            if( ( item_to_add->is_define_macro() ) ||
                ( item_to_add->is_undef_macro()  ) )
            {
                status = st::STATUS_SUCCESS;
            }
        }

        if( status == st::STATUS_SUCCESS )
        {
            status = base_options_t::do_insert_item( std::move(
                item_to_add ), insert_before_this_item );
        }

        return status;

    }

    st_status_t def_block_options_t::do_print(
        std::ostream& SIXTRL_RESTRICT_REF out_str ) const{

        st_status_t status = st::STATUS_SUCCESS;
        size_t const nn = this->num_stored_items();
        bool first = true;

        for( size_t ii = size_t{ 0 } ; ii < nn ; ++ii )
        {
            auto ptr_item = this->item( ii );

            if( !first ) out_str << this->m_print_separator;

            if( ptr_item != nullptr )
            {
                status = ptr_item->print_define_block( out_str,
                    this->m_block_indent_str, this->m_top_level_indent_str );

                if( status == st::STATUS_SUCCESS )
                {
                    first = false;
                }
            }
        }

        return status;
    }

    def_block_options_t::status_type def_block_options_t::do_commit() {
        std::ostringstream a2str;
        st_status_t const status = this->do_print( a2str );
        if( status == st::STATUS_SUCCESS )
        {
            this->m_def_block_string = a2str.str();
        }
        else
        {
            this->m_def_block_string.clear();
        }

        return status;
    }

} /* ns: SIXTRL_CXX_NAMESPACE */

void NS(CompileOptionItem_delete)( ::NS(BaseCompileOptionItem)* SIXTRL_RESTRICT
    item ) SIXTRL_NOEXCEPT {
        SIXTRL_CXX_NAMESPACE::BaseCompileOptionItem::DELETE_BASE_ITEM( item ); }

#endif /* C++, Host */
