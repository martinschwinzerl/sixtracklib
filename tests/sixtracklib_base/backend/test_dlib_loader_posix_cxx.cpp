#include "sixtracklib_base/backend/dlib_loader_posix.h"
#include <memory>
#include <gtest/gtest.h>


TEST( CXXBaseBackendPosixDynLibLoader, basic_usage )
{
    namespace st = SIXTRL_CXX_NAMESPACE;
    std::string const path_to_dlib(
        "/home/mschwinz/git/sixtracklib_upstream/build/sixtracklib/backends/cuda/libsixtrack_cuda.so" );

    st::PosixDynLibLoader temp( path_to_dlib );

    ASSERT_TRUE( !temp.has_dynamic_lib_handle() );
    ASSERT_TRUE(  temp.has_path_to_dynamic_lib() );

    std::shared_ptr< st::BaseDynLibLoader > ptr_base;

    ASSERT_TRUE( ptr_base.get() == nullptr );
    ptr_base.reset( new st::PosixDynLibLoader( path_to_dlib ) );
    ASSERT_TRUE( ptr_base.get() != nullptr );
    ASSERT_TRUE( !ptr_base->has_dynamic_lib_handle() );
    ASSERT_TRUE(  ptr_base->has_path_to_dynamic_lib() );
}
