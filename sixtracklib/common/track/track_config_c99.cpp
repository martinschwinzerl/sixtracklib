#include "sixtracklib/common/track/track_config.h"

#include <algorithm>
#include <cstddef>
#include <cmath>
#include <cstring>
#include <sstream>
#include <string>
#include <memory>
#include <vector>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/track/definitions.h"
#include "sixtracklib/common/track/track_config.hpp"

namespace st = SIXTRL_CXX_NAMESPACE;

namespace SIXTRL_CXX_NAMESPACE
{
    namespace
    {
        static constexpr uint64_t TRACK_FEATURE_NUM_BITS  = uint64_t{ 2 };
        static constexpr uint64_t TRACK_FEATURE_BITMASK   = uint64_t{ 0x0003 };

        static constexpr uint64_t LIMIT_CHECK_FEATURE_NUM_BITS = uint64_t{ 2 };
        static constexpr uint64_t LIMIT_CHECK_FEATURE_BITMASK = uint64_t{ 0x3 };

        static constexpr uint64_t LIMIT_MIN_MAX_NUM_BITS   = uint64_t{ 13 };
        static constexpr uint64_t LIMIT_MIN_MAX_BITMASK    = uint64_t{ 0x1fff };
        static constexpr double   LIMIT_MIN_MAX_MULTIPLIER = double{ 1e3 };

        static constexpr uint64_t LIMIT_MIN_LENGTH_NUM_BITS   = uint64_t{ 12 };
        static constexpr double   LIMIT_MIN_LENGTH_MULTIPLIER = double{ 1e3 };
        static constexpr uint64_t LIMIT_MIN_LENGTH_BITMASK = uint64_t{ 0x0fff };
    }
}

::NS(TrackConfig)* NS(TrackConfig_create)()
{
    return ::NS(TrackConfig_preset)( new ::NS(TrackConfig) );
}

::NS(TrackConfig)* NS(TrackConfig_new_from_variant)(
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TrackConfigVariant) *const
        SIXTRL_RESTRICT variant )
{
    ::NS(TrackConfig)* new_config = nullptr;

    std::unique_ptr< ::NS(TrackConfig) > ptr_track_config(
        ::NS(TrackConfig_create)() );

    if( ptr_track_config.get() != nullptr )
    {
        if( st::ARCH_STATUS_SUCCESS == ::NS(TrackConfig_init_from_variant)(
            ptr_track_config.get(), variant ) )
        {
            new_config = ptr_track_config.release();
        }
    }

    return new_config;
}

void NS(TrackConfig_delete)( ::NS(TrackConfig)* SIXTRL_RESTRICT config )
{
    delete config;
}

/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - */

::NS(arch_status_t) NS(TrackConfig_update_variant)(
    SIXTRL_BUFFER_DATAPTR_DEC ::NS(TrackConfig)* SIXTRL_RESTRICT config )
{
    using _size_t = ::NS(buffer_size_t);

    ::NS(arch_status_t) status = st::ARCH_STATUS_GENERAL_FAILURE;

    SIXTRL_ASSERT( ::NS(TRACK_CONFIG_VARIANT_NUM_FLAGS) == 3 );
    SIXTRL_ASSERT( ::NS(TRACK_CONFIG_VARIANT_KERNEL_IMPL_FLAG_INDEX) == 0 );

    SIXTRL_ASSERT( ::NS(TRACK_CONFIG_VARIANT_ENABLE_TRACK_MAPS_FLAG_INDEX)
                    == 1 );

    SIXTRL_ASSERT( ::NS(TRACK_CONFIG_VARIANT_GLOBAL_LIMIT_RECT_CHECK_FLAG_INDEX)
                   == 2 );

    if( config != nullptr )
    {
        config->variant.flags[ 0 ] = static_cast< uint64_t >(
            config->kernel_impl_flags );

        /* ----------------------------------------------------------------- */

        uint64_t track_features = uint64_t{ 0 };
        uint64_t num_bits_used  = uint64_t{ 0 };

        track_features |= ( st::TRACK_FEATURE_BITMASK &
            static_cast< uint64_t >( config->track_bb4d ) );

        num_bits_used += st::TRACK_FEATURE_NUM_BITS;

        track_features |= ( st::TRACK_FEATURE_BITMASK &
            static_cast< uint64_t >( config->track_bb6d ) ) << num_bits_used;

        num_bits_used += st::TRACK_FEATURE_NUM_BITS;

        track_features |= ( st::TRACK_FEATURE_BITMASK &
            static_cast< uint64_t >( config->track_sc_coasting ) )
                << num_bits_used;

        num_bits_used += st::TRACK_FEATURE_NUM_BITS;

        track_features |= ( st::TRACK_FEATURE_BITMASK &
            static_cast< uint64_t >( config->track_sc_bunched ) )
                << num_bits_used;

        num_bits_used += st::TRACK_FEATURE_NUM_BITS;

        track_features |= ( st::TRACK_FEATURE_BITMASK &
            static_cast< uint64_t >( config->track_tricub ) ) << num_bits_used;

        num_bits_used += st::TRACK_FEATURE_NUM_BITS;



        track_features |= ( st::LIMIT_CHECK_FEATURE_BITMASK &
            static_cast< uint64_t >( config->global_limit_rect_check ) )
                << num_bits_used;

        num_bits_used += st::LIMIT_CHECK_FEATURE_NUM_BITS;

        SIXTRL_ASSERT( num_bits_used <= uint64_t{ 64 } );

        config->variant.flags[ 1 ] = track_features;

        /* ----------------------------------------------------------------- */

        uint64_t global_check_rect_params = uint64_t{ 0 };
        num_bits_used = uint64_t{ 0 };

        uint64_t const min_x = st::TrackConfig_convert_double_to_uint64_bitmask(
            config->global_limit_rect_min_x, st::LIMIT_MIN_MAX_MULTIPLIER,
                st::LIMIT_MIN_MAX_NUM_BITS, true );

        global_check_rect_params |= min_x;
        num_bits_used += st::LIMIT_MIN_MAX_NUM_BITS;

        uint64_t const max_x = st::TrackConfig_convert_double_to_uint64_bitmask(
            config->global_limit_rect_max_x, st::LIMIT_MIN_MAX_MULTIPLIER,
                st::LIMIT_MIN_MAX_NUM_BITS, true );

        global_check_rect_params |= ( max_x << num_bits_used );
        num_bits_used += st::LIMIT_MIN_MAX_NUM_BITS;

        uint64_t const min_y = st::TrackConfig_convert_double_to_uint64_bitmask(
            config->global_limit_rect_min_y, st::LIMIT_MIN_MAX_MULTIPLIER,
                st::LIMIT_MIN_MAX_NUM_BITS, true );

        global_check_rect_params |= ( min_y << num_bits_used );
        num_bits_used += st::LIMIT_MIN_MAX_NUM_BITS;

        uint64_t const max_y = st::TrackConfig_convert_double_to_uint64_bitmask(
            config->global_limit_rect_max_y, st::LIMIT_MIN_MAX_MULTIPLIER,
                st::LIMIT_MIN_MAX_NUM_BITS, true );

        global_check_rect_params |= ( max_y << num_bits_used );
        num_bits_used += st::LIMIT_MIN_MAX_NUM_BITS;

        uint64_t const max_y = st::TrackConfig_convert_double_to_uint64_bitmask(
            config->global_limit_rect_min_length,
                st::LIMIT_MIN_LENGTH_MULTIPLIER, st::LIMIT_MIN_LENGTH_NUM_BITS,
                    false );

        global_check_rect_params |= ( max_y << num_bits_used );
        num_bits_used += st::LIMIT_MIN_MAX_NUM_BITS;

        SIXTRL_ASSERT( num_bits_used <= uint64_t{ 64 } );
        config->variant.flags[ 2 ] = global_check_rect_params;

        /* ---------------------------------------------------------------- */

        status = st::ARCH_STATUS_SUCCESS;
    }

    return status;
}

::NS(arch_status_t) NS(TrackConfig_init_from_variant)(
    SIXTRL_BUFFER_DATAPTR_DEC NS(TrackConfig)* SIXTRL_RESTRICT config,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(TrackConfigVariant) *const
        SIXTRL_RESTRICT variant )
{
    using feature_t = ::NS(track_conf_feature_t);

    ::NS(arch_status_t) status = st::ARCH_STATUS_GENERAL_FAILURE;

    SIXTRL_ASSERT( ::NS(TRACK_CONFIG_VARIANT_NUM_FLAGS) == 3 );
    SIXTRL_ASSERT( ::NS(TRACK_CONFIG_VARIANT_KERNEL_IMPL_FLAG_INDEX) == 0 );

    SIXTRL_ASSERT( ::NS(TRACK_CONFIG_VARIANT_ENABLE_TRACK_MAPS_FLAG_INDEX)
                    == 1 );

    SIXTRL_ASSERT( ::NS(TRACK_CONFIG_VARIANT_GLOBAL_LIMIT_RECT_CHECK_FLAG_INDEX)
                   == 2 );

    if( ( config != nullptr ) && ( variant != nullptr ) )
    {
        std::copy( &variant->flags[ 0 ],
                   &variant->flags[ ::NS(TRACK_CONFIG_VARIANT_NUM_FLAGS) ],
                   &config->variant.flags[ 0 ] );

        config->kernel_impl_flags = config->variant.flags[ 0 ];

        /* ----------------------------------------------------------------- */

        uint64_t track_features = config->variant.flags[ 1 ];
        uint64_t num_bits_used  = uint64_t{ 0 };

        config->track_bb4d = static_cast< feature_t >(
            track_features & st::TRACK_FEATURE_BITMASK );

        track_features >>= st::TRACK_FEATURE_NUM_BITS;
        num_bits_used += st::TRACK_FEATURE_NUM_BITS;


        config->track_bb6d = static_cast< feature_t >(
            track_features & st::TRACK_FEATURE_BITMASK );

        track_features >>= st::TRACK_FEATURE_NUM_BITS;
        num_bits_used += st::TRACK_FEATURE_NUM_BITS;


        config->track_sc_coasting = static_cast< feature_t >(
            track_features & st::TRACK_FEATURE_BITMASK );

        track_features >>= st::TRACK_FEATURE_NUM_BITS;
        num_bits_used += st::TRACK_FEATURE_NUM_BITS;


        config->track_sc_bunched = static_cast< feature_t >(
            track_features & st::TRACK_FEATURE_BITMASK );

        track_features >>= st::TRACK_FEATURE_NUM_BITS;
        num_bits_used += st::TRACK_FEATURE_NUM_BITS;


        config->track_tricub = static_cast< feature_t >(
            track_features & st::TRACK_FEATURE_BITMASK );

        track_features >>= st::TRACK_FEATURE_NUM_BITS;
        num_bits_used += st::TRACK_FEATURE_NUM_BITS;


        config->global_limit_rect_check = static_cast< feature_t >(
            track_features & st::LIMIT_CHECK_FEATURE_BITMASK );

        track_features >>= st::LIMIT_CHECK_FEATURE_NUM_BITS;
        num_bits_used += st::LIMIT_CHECK_FEATURE_NUM_BITS;

        SIXTRL_ASSERT( num_bits_used <= uint64_t{ 64 } );

        /* ----------------------------------------------------------------- */

        uint64_t global_check_rect_params = config->variant.flags[ 1 ];
        num_bits_used = uint64_t{ 0 };

        TrackConfig_convert_uint64_bitmask_to_double(
            uint64_t const bitmask, uint64_t const num_bits,
            double const multiplicator, bool can_be_negative ) SIXTRL_NOEXCEPT;

        config->global_limit_rect_min_x =
            st::TrackConfig_convert_uint64_bitmask_to_double(
                ( global_check_rect_params & st::LIMIT_MIN_MAX_BITMASK ),
                    st::LIMIT_MIN_MAX_NUM_BITS, st::LIMIT_MIN_MAX_MULTIPLIER,
                        true );

        num_bits_used += st::LIMIT_MIN_MAX_NUM_BITS;
        global_check_rect_params >>= st::LIMIT_MIN_MAX_NUM_BITS;

        config->global_limit_rect_max_x =
            st::TrackConfig_convert_uint64_bitmask_to_double(
                ( global_check_rect_params & st::LIMIT_MIN_MAX_BITMASK ),
                    st::LIMIT_MIN_MAX_NUM_BITS, st::LIMIT_MIN_MAX_MULTIPLIER,
                        true );

        num_bits_used += st::LIMIT_MIN_MAX_NUM_BITS;
        global_check_rect_params >>= st::LIMIT_MIN_MAX_NUM_BITS;

        config->global_limit_rect_min_y =
            st::TrackConfig_convert_uint64_bitmask_to_double(
                ( global_check_rect_params & st::LIMIT_MIN_MAX_BITMASK ),
                    st::LIMIT_MIN_MAX_NUM_BITS, st::LIMIT_MIN_MAX_MULTIPLIER,
                        true );

        num_bits_used += st::LIMIT_MIN_MAX_NUM_BITS;
        global_check_rect_params >>= st::LIMIT_MIN_MAX_NUM_BITS;

        config->global_limit_rect_max_y =
            st::TrackConfig_convert_uint64_bitmask_to_double(
                ( global_check_rect_params & st::LIMIT_MIN_MAX_BITMASK ),
                    st::LIMIT_MIN_MAX_NUM_BITS, st::LIMIT_MIN_MAX_MULTIPLIER,
                        true );

        num_bits_used += st::LIMIT_MIN_MAX_NUM_BITS;
        global_check_rect_params >>= st::LIMIT_MIN_MAX_NUM_BITS;

        config->global_limit_rect_min_length =
            st::TrackConfig_convert_uint64_bitmask_to_double(
                ( global_check_rect_params & st::LIMIT_MIN_LENGTH_BITMASK ),
                    st::LIMIT_MIN_LENGTH_NUM_BITS,
                        st::LIMIT_MIN_LENGTH_MULTIPLIER, true );

        num_bits_used += st::LIMIT_MIN_LENGTH_NUM_BITS;
        global_check_rect_params >>= st::LIMIT_MIN_LENGTH_NUM_BITS;

        SIXTRL_ASSERT( num_bits_used <= uint64_t{ 64 } );

        /* ---------------------------------------------------------------- */

        status = st::ARCH_STATUS_SUCCESS;
    }

    return status;
}

::NS(buffer_size_t) NS(TrackConfig_compiler_options_required_capacity)(
    SIXTRL_BUFFER_DATAPTR_DEC const ::NS(TrackConfig)
        *const SIXTRL_RESTRICT conf,
    SIXTRL_ARGTPR_DEC char const* SIXTRL_RESTRICT option_prefix )
{
    std::string _option_prefix = std::string{ "-D" };

    if( ( option_prefix != nullptr ) &&
        ( std::strlen( option_prefix ) >= 0u ) )
    {
        _option_prefix = std::string{ option_prefix };
    }

    return st::TrackConfig_compiler_options( conf, _option_prefix ).size();
}

::NS(arch_status_t) NS(TrackConfig_compiler_options)(
    SIXTRL_ARGPTR_DEC char* compiler_options_cstr,
    ::NS(buffer_size_t) const compiler_options_cstr_capacity,
    SIXTRL_BUFFER_DATAPTR_DEC const ::NS(TrackConfig)
        *const SIXTRL_RESTRICT conf,
    SIXTRL_ARGTPR_DEC char const* SIXTRL_RESTRICT option_prefix )
{
    ::NS(arch_status_t) status = st::ARCH_STATUS_GENERAL_FAILURE;

    if( ( conf != nullptr ) && ( compiler_options_cstr != nullptr ) &&
        ( compiler_options_cstr_capacity > ::NS(buffer_size_t){ 0 } ) )
    {
        std::set( compiler_options_cstr,
                  compiler_options_cstr + compiler_options_cstr_capacity,
                  '\0' );

        std::string _option_prefix = std::string{ "-D" };

        if( ( option_prefix != nullptr ) &&
            ( std::strlen( option_prefix ) >= 0u ) )
        {
            _option_prefix = std::string{ option_prefix };
        }

        std::string const compiler_options = st::TrackConfig_compiler_options(
            conf, _option_prefix );

        std::strncpy( compiler_options_cstr, compiler_options.c_str(),
                      compiler_options_cstr_capacity -
                          ::NS(buffer_size_t){ 1 } );

        if( compiler_options_cstr_capacity > compiler_options.size() )
        {
            status = st::ARCH_STATUS_SUCCESS;
        }
    }

    return status;
}

bool NS(TrackConfig_can_be_added)(
    SIXTRL_BUFFER_ARGPTR_DEC const ::NS(Buffer) *const SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC ::NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_objects,
    SIXTRL_ARGPTR_DEC ::NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_slots,
    SIXTRL_ARGPTR_DEC ::NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_dataptrs )
{
    typedef ::NS(buffer_size_t) buf_size_t;

    bool can_be_added = false;
    ::NS(arch_status_t) status = SIXTRL_ARCH_STATUS_GENERAL_FAILURE;

    ::NS(TrackConfig) config;
    ::NS(TrackConfig_preset)( &config );

    buf_size_t const num_dataptrs = ::NS(TrackConfig_num_dataptrs)( &config );
    buf_size_t const slot_size = ::NS(Buffer_get_slot_size)( buffer );

    buf_size_t sizes[]  = { buf_size_t{ 0 } };
    buf_size_t counts[] = { buf_size_t{ 0 } };

    SIXTRL_ASSERT( num_dataptrs == buf_size_t{ 1 } );

    status = ::NS(TrackConfig_attributes_sizes)(
        &sizes[ 0 ], num_dataptrs, &config, slot_size );

    if( status == st::ARCH_STATUS_SUCCESS )
    {
        status = ::NS(TrackConfig_attributes_counts)(
            &counts[ 0 ], num_dataptrs, &config );
    }

    if( status == st::ARCH_STATUS_SUCCESS )
    {
        can_be_added = ::NS(Buffer_can_add_object)( buffer, sizeof( config ),
            num_dataptrs, sizes, counts, ptr_requ_objects, ptr_requ_slots,
                ptr_requ_dataptrs );
    }

    return can_be_added;
}

SIXTRL_BUFFER_DATAPTR_DEC ::NS(TrackConfig)* NS(TrackConfig_new)(
    SIXTRL_BUFFER_ARGPTR_DEC ::NS(Buffer)* SIXTRL_RESTRICT buffer )
{
    typedef ::NS(buffer_size_t) buf_size_t;

    SIXTRL_BUFFER_DATAPTR_DEC ::NS(TrackConfig)* config = nullptr;
    ::NS(arch_status_t) status = st::ARCH_STATUS_GENERAL_FAILURE;

    ::NS(TrackConfig) temp_config;
    ::NS(TrackConfig_preset)( &temp_config );

    buf_size_t const num_dataptrs =
        ::NS(TrackConfig_num_dataptrs)( &temp_config );

    buf_size_t offsets[] = { buf_size_t{ 0 } };
    buf_size_t sizes[]   = { buf_size_t{ 0 } };
    buf_size_t counts[]  = { buf_size_t{ 0 } };
    buf_size_t const slot_size = ::NS(Buffer_get_slot_size)( buffer );

    SIXTRL_ASSERT( num_dataptrs == buf_size_t{ 1 } );
    ::NS(TrackConfig_preset)( &temp_config );

    status = ::NS(TrackConfig_attributes_offsets)(
        &offsets[ 0 ], num_dataptrs, &temp_config, slot_size );

    if( status == st::ARCH_STATUS_SUCCESS )
    {
        status = ::NS(TrackConfig_attributes_counts)(
            &counts[ 0 ], num_dataptrs, &temp_config );
    }

    if( status == st::ARCH_STATUS_SUCCESS )
    {
        status = ::NS(TrackConfig_attributes_sizes)(
            &sizes[ 0 ], num_dataptrs, &temp_config, slot_size );
    }

    if( status == st::ARCH_STATUS_SUCCESS )
    {
        config = ( SIXTRL_BUFFER_DATAPTR_DEC ::NS(TrackConfig)* )(
            uintptr_t )::NS(Object_get_begin_addr)( ::NS(Buffer_add_object)(
                buffer, &temp_config, sizeof( temp_config ),
                    NS(TrackConfig_type_id)( &temp_config ), num_dataptrs,
                        &offsets[ 0 ], &sizes[ 0 ], &counts[ 0 ] ) );
    }

    return config;
}

SIXTRL_BUFFER_DATAPTR_DEC ::NS(TrackConfig)* NS(TrackConfig_add)(
    SIXTRL_BUFFER_ARGPTR_DEC ::NS(Buffer)* SIXTRL_RESTRICT buffer,
     ::NS(track_conf_bitfield_t) const kernel_impl_flags,
     ::NS(track_conf_feature_t) const track_bb4d,
     ::NS(track_conf_feature_t) const track_bb6d,
     ::NS(track_conf_feature_t) const track_sc_coasting,
     ::NS(track_conf_feature_t) const track_sc_bunched,
     ::NS(track_conf_feature_t) const track_tricub,
     ::NS(track_conf_feature_t) const global_limit_rect_check,
     ::NS(track_conf_real_t) const global_limit_rect_min_x,
     ::NS(track_conf_real_t) const global_limit_rect_max_x,
     ::NS(track_conf_real_t) const global_limit_rect_min_y,
     ::NS(track_conf_real_t) const global_limit_rect_max_y,
     ::NS(track_conf_real_t) const global_limit_rect_min_length )
{
    typedef ::NS(buffer_size_t) buf_size_t;

    SIXTRL_BUFFER_DATAPTR_DEC ::NS(TrackConfig)* config = nullptr;
    ::NS(arch_status_t) status = st::ARCH_STATUS_GENERAL_FAILURE;

    ::NS(TrackConfig) temp_config;
    ::NS(TrackConfig_preset)( &temp_config );
    ::NS(TrackConfig_set_kernel_impl_flags)( &temp_config, kernel_impl_flags );
    ::NS(TrackConfig_set_track_bb4d)( &temp_config, track_bb4d );
    ::NS(TrackConfig_set_track_bb6d)( &temp_config, track_bb6d );
    ::NS(TrackConfig_set_track_sc_coasting)( &temp_config, track_sc_coasting );
    ::NS(TrackConfig_set_track_sc_bunched)( &temp_config, track_sc_bunched );
    ::NS(TrackConfig_set_track_tricub)( &temp_config, track_tricub );

    ::NS(TrackConfig_set_global_limit_rect_check)(
        &temp_config, global_limit_rect_check );

    ::NS(TrackConfig_set_global_limit_rect_min_x)(
        &temp_config, global_limit_rect_min_x );

    ::NS(TrackConfig_set_global_limit_rect_max_x)(
        &temp_config, global_limit_rect_max_x );

    ::NS(TrackConfig_set_global_limit_rect_min_y)(
        &temp_config, global_limit_rect_min_y );

    ::NS(TrackConfig_set_global_limit_rect_max_y)(
        &temp_config, global_limit_rect_max_y );

    ::NS(TrackConfig_set_global_limit_rect_min_length)(
        &temp_config, global_limit_rect_min_length );


    buf_size_t const num_dataptrs =
        ::NS(TrackConfig_num_dataptrs)( &temp_config );

    buf_size_t offsets[] = { buf_size_t{ 0 } };
    buf_size_t sizes[]   = { buf_size_t{ 0 } };
    buf_size_t counts[]  = { buf_size_t{ 0 } };
    buf_size_t const slot_size = ::NS(Buffer_get_slot_size)( buffer );

    SIXTRL_ASSERT( num_dataptrs == buf_size_t{ 1 } );

    status = ::NS(TrackConfig_attributes_offsets)(
        &offsets[ 0 ], num_dataptrs, &temp_config, slot_size );

    if( status == st::ARCH_STATUS_SUCCESS )
    {
        status = ::NS(TrackConfig_attributes_counts)(
            &counts[ 0 ], num_dataptrs, &temp_config );
    }

    if( status == st::ARCH_STATUS_SUCCESS )
    {
        status = ::NS(TrackConfig_attributes_sizes)(
            &sizes[ 0 ], num_dataptrs, &temp_config, slot_size );
    }

    if( status == st::ARCH_STATUS_SUCCESS )
    {
        status = ::NS(TrackConfig_update_variant)( &temp_config );
    }

    if( status == st::ARCH_STATUS_SUCCESS )
    {
        config = ( SIXTRL_BUFFER_DATAPTR_DEC ::NS(TrackConfig)* )(
            uintptr_t )::NS(Object_get_begin_addr)( ::NS(Buffer_add_object)(
                buffer, &temp_config, sizeof( temp_config ),
                    NS(TrackConfig_type_id)( &temp_config ), num_dataptrs,
                        &offsets[ 0 ], &sizes[ 0 ], &counts[ 0 ] ) );
    }

    return config;
}

SIXTRL_BUFFER_DATAPTR_DEC ::NS(TrackConfig)* NS(TrackConfig_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC ::NS(Buffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC const ::NS(TrackConfig) *const SIXTRL_RESTRICT config )
{
    return NS(TrackConfig_add)( buffer,
        ::NS(TrackConfig_kernel_impl_flags)( config ),
        ::NS(TrackConfig_track_bb4d)( config ),
        ::NS(TrackConfig_track_bb6d)( config ),
        ::NS(TrackConfig_track_sc_coasting)( config ),
        ::NS(TrackConfig_track_sc_bunched)( config ),
        ::NS(TrackConfig_track_tricub)( config ),
        ::NS(TrackConfig_track_global_limit_rect_check)( config ),
        ::NS(TrackConfig_track_global_limit_rect_min_x)( config ),
        ::NS(TrackConfig_track_global_limit_rect_max_x)( config ),
        ::NS(TrackConfig_track_global_limit_rect_min_y)( config ),
        ::NS(TrackConfig_track_global_limit_rect_max_y)( config ),
        ::NS(TrackConfig_track_global_limit_rect_min_length)( config ) );
}

/* ========================================================================= */

namespace SIXTRL_CXX_NAMESPACE
{
    std::string TrackConfig_compiler_options(
        const ::NS(TrackConfig) *const SIXTRL_RESTRICT config,
        std::string const& SIXTRL_RESTRICT_REF option_prefix )
    {
        std::ostringstream a2str( "" );

        if( config != nullptr )
        {
            a2str
                << "/* ****************************************************"
                << "********************* */\r\n"
                << "/* Compiler Options: Enabled/Disabled Features */
                << "/* ****************************************************"
                << "********************* */\r\n"
                << "#if !defined( SIXTRL_ENABLE_BEAM_FIELDS_BEAM_BEAM_4D )\r\n"
                << "    #define SIXTRL_ENABLE_BEAM_FIELDS_BEAM_BEAM_4D "
                << config->track_bb4d << "\r\n"
                << "#endif /* SIXTRL_ENABLE_BEAM_FIELDS_BEAM_BEAM_4D */\r\n"
                << "\r\n"
                << "#if !defined( SIXTRL_ENABLE_BEAM_FIELDS_BEAM_BEAM_6D )\r\n"
                << "    #define SIXTRL_ENABLE_BEAM_FIELDS_BEAM_BEAM_6D "
                << config->track_bb6d << "\r\n"
                << "#endif /* SIXTRL_ENABLE_BEAM_FIELDS_BEAM_BEAM_6D */\r\n"
                << "\r\n"
                << "#if !defined( SIXTRL_ENABLE_SPACE_CHARGE_COASTING )\r\n"
                << "    #define SIXTRL_ENABLE_SPACE_CHARGE_COASTING "
                << config->track_sc_coasting << "\r\n"
                << "#endif /* SIXTRL_ENABLE_SPACE_CHARGE_COASTING */\r\n"
                << "\r\n"
                << "#if !defined( SIXTRL_ENABLE_SPACE_CHARGE_BUNCHED )\r\n"
                << "    #define SIXTRL_ENABLE_SPACE_CHARGE_BUNCHED "
                << config->track_sc_coasting << "\r\n"
                << "#endif /* SIXTRL_ENABLE_SPACE_CHARGE_BUNCHED */\r\n"
                << "\r\n"
                << "#if !defined( SIXTRL_ENABLE_TRICUB )\r\n"
                << "    #define SIXTRL_ENABLE_TRICUB "
                << config->track_tricub << "\r\n"
                << "#endif /* SIXTRL_ENABLE_TRICUB */\r\n\r\n"
                << "/* ****************************************************"
                << "********************* */\r\n"
                << "/* Compiler Options: Global Limit Rect Check */
                << "/* ****************************************************"
                << "********************* */\r\n"
                << "#if !defined( SIXTRL_GLOBAL_LIMIT_RECT_CHECK )\r\n"
                << "    #define SIXTRL_GLOBAL_LIMIT_RECT_CHECK "
                << config->global_limit_rect_check << "\r\n"
                << "#endif /* SIXTRL_GLOBAL_LIMIT_RECT_CHECK */\r\n"
                << "\r\n"
                << "#if !defined( SIXTRL_GLOBAL_LIMIT_RECT_MIN_X )\r\n"
                << "    #define SIXTRL_GLOBAL_LIMIT_RECT_MIN_X "
                << config->global_limit_rect_min_x << " /* [m] */\r\n"
                << "#endif /* SIXTRL_GLOBAL_LIMIT_RECT_MIN_X */\r\n"
                << "\r\n"
                << "#if !defined( SIXTRL_GLOBAL_LIMIT_RECT_MAX_X )\r\n"
                << "    #define SIXTRL_GLOBAL_LIMIT_RECT_MAX_X "
                << config->global_limit_rect_max_x << " /* [m] */\r\n"
                << "#endif /* SIXTRL_GLOBAL_LIMIT_RECT_MAX_X */\r\n"
                << "\r\n"
                << "#if !defined( SIXTRL_GLOBAL_LIMIT_RECT_MIN_Y )\r\n"
                << "    #define SIXTRL_GLOBAL_LIMIT_RECT_MIN_Y "
                << config->global_limit_rect_min_y << " /* [m] */\r\n"
                << "#endif /* SIXTRL_GLOBAL_LIMIT_RECT_MIN_Y */\r\n"
                << "\r\n"
                << "#if !defined( SIXTRL_GLOBAL_LIMIT_RECT_MAX_Y )\r\n"
                << "    #define SIXTRL_GLOBAL_LIMIT_RECT_MAX_Y "
                << config->global_limit_rect_max_y << " /* [m] */\r\n"
                << "#endif /* SIXTRL_GLOBAL_LIMIT_RECT_MAX_Y */\r\n"
                << "\r\n"
                << "#if !defined( SIXTRL_GLOBAL_LIMIT_RECT_MIN_LENGTH )\r\n"
                << "    #define SIXTRL_GLOBAL_LIMIT_RECT_MIN_LENGTH "
                << config->global_limit_rect_min_length << " /* [m] */\r\n"
                << "#endif /* SIXTRL_GLOBAL_LIMIT_RECT_MIN_LENGTH */\r\n";
        }

        return a2str.str();
    }

    uint64_t TrackConfig_convert_double_to_uint64_bitmask(
        double x, double const multiplicator, uint64_t const num_bits,
        bool can_be_negative ) SIXTRL_NOEXCEPT
    {
        static constexpr uint64_t ONE = uint64_t{ 1 };

        uint64_t result = uint64_t{ 0 };
        bool const is_positive = ( x >= double{ 0.0 } );

        if( ( multiplicator > double{ 0.0 } ) &&
            ( num_bits > uint64_t{ 0 } ) &&
            ( ( is_positive ) || ( can_be_negative ) ) )
        {
            uint64_t const max_value_bitmask = ( is_positive )
                ? ( ONE <<   num_bits ) - ONE
                : ( ONE << ( num_bits   - ONE ) ) - ONE;

            uint64_t const sign_bitmask = ( is_positive )
                ? uint64_t{ 0 } : ( ONE << ( num_bits - ONE ) );

            if( !is_positive ) x = -x;
            x *= multiplicator;

            double int_abs_x = double{ 0.0 };
            double const frac_scaled_abs_x = std::modf( x, &int_abs_x );

            result = static_cast< uint64_t >( int_abs_x ) +
                ( frac_scaled_abs_x > double{ 0.5 } ) ? ONE : uint64_t{ 0 };

            if( result > max_value_bitmask ) result = max_value_bitmask;
            result |= sign_bitmask;
        }

        return result;
    }

    double TrackConfig_convert_uint64_bitmask_to_double(
        uint64_t bitmask, uint64_t const num_bits,
        double const multiplicator, bool can_be_negative ) SIXTRL_NOEXCEPT
    {
        static constexpr uint64_t ONE = uint64_t{ 1 };

        double result = double{ 0.0 };

        if( ( num_bits > uint64_t{ 0 } ) && ( multiplicator > double{ 0.0 } ) )
        {
            uint64_t const max_bitmask_incl_sign = ( ONE << num_bits ) - ONE;
            uint64_t const sign_bitmask = ( ONE << ( num_bits - ONE ) );

            bool is_positive = false;

            if( can_be_negative )
            {
                is_positive = ( ( bitmask & sign_bitmask ) == uint64_t{ 0 } );
                if( !is_positive ) bitmask &= ~( sign_bitmask );
            }
            else if( ( bitmask & sign_bitmask ) == uint64_t{ 0 } )
            {
                is_positive = true;
            }

            SIXTRL_ASSERT( ( is_positive ) || ( can_be_negative ) );

            result = static_cast< double >( bitmask ) / multiplicator;
            if( !is_positive ) result = -result;
        }

        return result;
    }
}

