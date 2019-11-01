#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
// #include <set>
#include <sstream>
#include <vector>
#include <map>
#include <tuple>

// #include "clang/Driver/Options.h"
// #include "clang/AST/AST.h"
// #include "clang/AST/ASTContext.h"
// #include "clang/AST/ASTConsumer.h"
// #include "clang/AST/RecursiveASTVisitor.h"
// #include "clang/Frontend/ASTConsumers.h"
// #include "clang/Frontend/FrontendActions.h"
// #include "clang/Frontend/CompilerInstance.h"
// #include "clang/Tooling/CommonOptionsParser.h"
// #include "clang/Tooling/Tooling.h"
// #include "clang/Rewrite/Core/Rewriter.h"
// #include "clang/ASTMatchers/ASTMatchers.h"
// #include "clang/ASTMatchers/ASTMatchFinder.h"

#include "libcodegen/cxx_to_c99_config.hpp"

int main( int const argc, char* argv[] )
{
    sixtrack::tools::CxxToC99Generator generator(
        "/home/martin/git/sixtracklib/sixtracklib/common/architecture/c99_bindings.toml" );

    sixtrack::tools::CxxClassConfig const& config1 =
        generator.class_config( "ArchData" );

    sixtrack::tools::CxxClassConfig const& config2 =
        generator.class_config( "Architecture" );

    return 0;
}

/* end: tools/codegenerators/create_c99_from_cxx.cpp */
