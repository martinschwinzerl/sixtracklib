#include "sixtracklib/common/control/node_id.hpp"

#include <cstddef>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <regex>
#include <utility>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/control/node_id.h"

namespace SIXTRL_CXX_NAMESPACE
{
    constexpr NodeId::platform_id_t NodeId::ILLEGAL_PLATFORM_ID;
    constexpr NodeId::device_id_t   NodeId::ILLEGAL_DEVICE_ID;
    constexpr NodeId::arch_id_t     NodeId::ARCH_ILLEGAL;
    constexpr NodeId::format_t      NodeId::DEFAULT_FORMAT;
}

/* end: sixtracklib/common/control/node_id.cpp */
