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
    }

    /* ********************************************************************* */

    constexpr size_t item_t::DEFAULT_BLOCK_INDENT;
    constexpr size_t item_t::DEFAULT_TOPLEVEL_INDENT;

    /* ===================================================================== */

    string_t const& item_t::name_str() const SIXTRL_NOEXCEPT {
        return this->m_name; }

    char_t const* item_t::name() const SIXTRL_NOEXCEPT {
        return this->m_name.c_str(); }

    status_t item_t::set_name( string_t const& SIXTRL_RESTRICT_REF name ) {
        this->m_name = name; return st::STATUS_SUCCESS; }

    string_t const& item_t::prefix_str() const SIXTRL_NOEXCEPT {
        return this->m_prefix; }

    char_t const* item_t::prefix() const SIXTRL_NOEXCEPT {
        return this->m_prefix.c_str(); }

    status_t item_t::set_prefix(
        string_t const& SIXTRL_RESTRICT_REF prefix_str ) {
        this->m_prefix = prefix_str; return st::STATUS_SUCCESS; }

    string_t const& item_t::separator_str() const SIXTRL_NOEXCEPT {
        return this->m_separator; }

    char_t const* item_t::separator() const SIXTRL_NOEXCEPT {
        return this->m_separator.c_str(); }

    status_t item_t::set_separator(
        string_t const& SIXTRL_RESTRICT_REF separator_str ) {
        this->m_separator = separator_str; return st::STATUS_SUCCESS; }

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

    bool item_t::value_needs_quotes() const SIXTRL_NOEXCEPT {
        return this->m_value_needs_quotes; }

    status_t item_t::set_value_needs_quotes(
        bool const needs_quotes ) SIXTRL_NOEXCEPT {
        this->m_value_needs_quotes = needs_quotes;
        return st::STATUS_SUCCESS; }

    bool item_t::is_define_macro() const SIXTRL_NOEXCEPT {
        return this->m_is_define_macro; }

    status_t item_t::set_is_define_macro(
        bool const is_define_macro_flag ) SIXTRL_NOEXCEPT {
        this->m_is_define_macro = is_define_macro_flag;
        return st::STATUS_SUCCESS; }

    string_t item_t::to_string() const {
        std::ostringstream a2str;
        status_t const status = this->do_print( a2str );
        return ( status == st::STATUS_SUCCESS ) ? a2str.str() : string_type{}; }

    size_t item_t::required_string_capacity() const {
        string_t const temp_str( this->to_string() );
        return temp_str.size() + size_t{ 1 }; }

    status_t item_t::to_string( char_t* SIXTRL_RESTRICT out_str_buffer,
        size_t const out_str_buffer_capacity ) const
    {
        status_t status = st::STATUS_GENERAL_FAILURE;
        string_type const temp( this->to_string() );

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

    status_t item_t::print( std::ostream& SIXTRL_RESTRICT_REF out_str ) const
    {
        return this->do_print( out_str );
    }

    string_t item_t::to_define_block_string(
        size_t const block_indent, size_t const top_level_indent  ) const {
        std::ostringstream a2str;
        status_t const status = this->do_print_define_block(
            a2str, block_indent, top_level_indent );
        return ( status == st::STATUS_SUCCESS ) ? a2str.str() : string_t{};
    }

    size_t item_t::required_define_block_string_capacity(
        size_t const block_indent, size_t const top_level_indent ) const {
        item_t::string_type const temp( this->to_define_block_string() );
        return temp.size() + size_t{ 1 };
    }

    status_t item_t::to_define_block_string(
        char_t* SIXTRL_RESTRICT out_str_buffer,
        size_t const out_str_buffer_capacity,
        size_t const block_indent, size_t const top_level_indent ) const {

        status_t status = st::STATUS_GENERAL_FAILURE;
        string_type const temp( this->to_define_block_string(
            block_indent, top_level_indent ) );

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
        size_t const block_indent, size_type const top_level_indent ) const {
        return this->do_print_define_block(
            out_str, block_indent, top_level_indent ); }

    item_t::BaseCompileOptionItem( item_t::backend_id_t const backend_id ) :
        st::BaseBackendObj( backend_id,
            st::CLASS_ID_PROGRAM_COMPILE_OPTION_ITEM ) {}

    status_t item_t::do_print( std::ostream& SIXTRL_RESTRICT_REF out_str ) const
    {
        status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( !this->m_name.empty() ) ||
            ( ( !this->m_prefix.empty() ) &&
              ( !this->m_is_define_macro ) ) )
        {
            out_str << this->m_prefix << this->m_name << this->m_separator;

            if( !this->m_value_needs_quotes )
            {
                out_str << this->m_value;
            }
            else
            {
                out_str << "\"" << this->m_value << "\"";
            }

            status = st::STATUS_SUCCESS;
        }

        return status;
    }

    status_t item_t::do_print_define_block(
        std::ostream& SIXTRL_RESTRICT_REF out_str,
        size_t const block_indent, size_t const top_level_indent ) const {
        status_t status = st::STATUS_GENERAL_FAILURE;

        if( ( this->m_is_define_macro ) && ( !this->m_name.empty() ) )
        {
            string_type const block_indent_str = ( block_indent > size_t{ 0 } )
                ? string_type( block_indent, ' ' ) : string_type{};

            string_type const tld_indent_str =
                ( top_level_indent > size_t{ 0 } )
                    ? string_type( block_indent, ' ' ) : string_type{};

            out_str << tld_indent_str
                    << "#if !defined( " << this->m_name << " )\r\n"
                    << tld_indent_str << block_indent_str
                    << "#define " << this->m_name;

            if( ( !this->m_value.empty() ) || ( this->m_value_needs_quotes ) )
            {
                out_str << " ";

                if( !this->m_value_needs_quotes )
                {
                    out_str << this->m_value;
                }
                else
                {
                    out_str << "\"" << this->m_value << "\"";
                }
            }

            out_str << "\r\n"
                    << tld_indent_str << "#endif /* !defined( "
                    << this->m_name << " ) */\r\n";

            status = st::STATUS_SUCCESS;
        }

        return status;
    }

} /* ns: SIXTRL_CXX_NAMESPACE */
#endif /* C++, Host */
