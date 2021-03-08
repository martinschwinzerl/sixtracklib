#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include <gtest/gtest.h>

#include "sixtracklib/common/generated/path.h"
#include "sixtracklib/opencl/control/program_store.h"

TEST( CXXOpenCLControlProgramConfig, ParseOpenCL01TomlConfig )
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    std::ostringstream a2str;
    a2str << "[opencl]\r\n"
          << "    compile_default_ipaths = true\r\n"
          << "    [opencl.0]\r\n"
          << "        compile_flags = [ \"-Werror\", \"-cl-strict-aliasign\", ]\r\n"
          << "    [opencl.1]\r\n"
          << "        active = false\r\n"
          << "    [opencl.2]\r\n"
          << "        active = false\r\n"
          << "    [opencl.3]\r\n"
          << "        active = false\r\n";

    std::string const toml_config_str = a2str.str();
    std::string const path_to_toml_file = std::tmpnam( nullptr );
    a2str.str( "" );

    std::ofstream temp_file( path_to_toml_file.c_str() );
    temp_file << toml_config_str << "\r\n";
    temp_file.close();

    st::OclProgramConfigStore config_store;

    ASSERT_TRUE( config_store.update_from_file(
        path_to_toml_file ) == st::STATUS_SUCCESS );

    st::ocl_program_config_source_type src_node;
    auto conf = config_store.find( st::OclProgramKey{}, false );
    ASSERT_FALSE( conf != nullptr );

    conf = config_store.find( st::OclProgramKey{}, true, &src_node );
    ASSERT_TRUE( conf != nullptr );
    ASSERT_TRUE( src_node == st::OclProgramConfigStore::SOURCE_GLOBAL );

    st::OclProgramKey prog_a_key;
    prog_a_key.clear();
    prog_a_key.ctx_key.platform_id = 0;

    auto platform0_conf = config_store.find( prog_a_key, false );
    ASSERT_TRUE( platform0_conf == nullptr );
    platform0_conf = config_store.find( prog_a_key, true, &src_node );
    ASSERT_TRUE( platform0_conf != nullptr );
    ASSERT_TRUE( platform0_conf != conf );

    a2str << "-I " << ::NS(PATH_TO_SIXTRL_INCLUDE_DIR);
    std::string const conf_compile_flags_str = a2str.str();
    a2str.str( "" );

    a2str << "-Werror -cl-strict-aliasign -I "
          << ::NS(PATH_TO_SIXTRL_INCLUDE_DIR);
    std::string const prog_a_compile_flags_str = a2str.str();
    a2str.str( "" );

    a2str << *conf;
    ASSERT_TRUE( a2str.str().compare( conf_compile_flags_str ) == 0 );
    a2str.str( "" );

    a2str << *platform0_conf;
    ASSERT_TRUE( a2str.str().compare( prog_a_compile_flags_str ) == 0 );
    a2str.str( "" );

    std::remove( path_to_toml_file.c_str() );

    config_store.clear();

    ASSERT_TRUE( config_store.update_from_string(
        toml_config_str ) == st::STATUS_SUCCESS );

    conf = config_store.find( st::OclProgramKey{}, false );
    ASSERT_FALSE( conf != nullptr );

    conf = config_store.find( st::OclProgramKey{}, true, &src_node );
    ASSERT_TRUE( conf != nullptr );
    ASSERT_TRUE( src_node == st::OclProgramConfigStore::SOURCE_GLOBAL );

    platform0_conf = config_store.find( prog_a_key, false );
    ASSERT_TRUE( platform0_conf == nullptr );
    platform0_conf = config_store.find( prog_a_key, true, &src_node );
    ASSERT_TRUE( platform0_conf != nullptr );
    ASSERT_TRUE( platform0_conf != conf );


}
