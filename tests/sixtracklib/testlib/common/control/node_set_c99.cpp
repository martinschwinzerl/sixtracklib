#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/testlib/common/control/node_set.h"
    #include "sixtracklib/testlib/common/control/node_set.hpp"

    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/node_store.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace st_tests = SIXTRL_CXX_NAMESPACE::tests;

::NS(TestNodeSetBase)* NS(TestNodeSetBase_create)(
    ::NS(NodeStore)* SIXTRL_RESTRICT store )
{
    return ( store != nullptr )
        ? new st_tests::TestNodeSetBase( *store ) : nullptr;
}

void NS(TestNodeSetBase_set_min_num_selectable_nodes)(
    ::NS(TestNodeSetBase)* SIXTRL_RESTRICT node_set,
    ::NS(arch_size_t) const min_sel_cnt )
{
    if( node_set != nullptr )
        node_set->setMinNumSelectableNodes( min_sel_cnt );
}

void NS(TestNodeSetBase_set_max_num_selectable_nodes)(
    ::NS(TestNodeSetBase)* SIXTRL_RESTRICT node_set,
    ::NS(arch_size_t) const max_sel_cnt )
{
    if( node_set != nullptr )
        node_set->setMaxNumSelectableNodes( max_sel_cnt );
}

void NS(TestNodeSetBase_set_min_num_default_nodes)(
    ::NS(TestNodeSetBase)* SIXTRL_RESTRICT node_set,
    ::NS(arch_size_t) const min_default_cnt )
{
    if( node_set != nullptr )
        node_set->setMinNumDefaultNodes( min_default_cnt );
}

void NS(TestNodeSetBase_set_max_num_default_nodes)(
    ::NS(TestNodeSetBase)* SIXTRL_RESTRICT node_set,
    ::NS(arch_size_t) const max_default_cnt )
{
    if( node_set != nullptr )
        node_set->setMaxNumDefaultNodes( max_default_cnt );
}

/* ------------------------------------------------------------------------- */

::NS(TestNodeSetSingle)* NS(TestNodeSetSingle_create)(
    ::NS(NodeStore)* SIXTRL_RESTRICT store )
{
    return ( store != nullptr )
        ? new st_tests::TestNodeSetSingle( *store ) : nullptr;
}

void NS(TestNodeSetSingle_set_min_num_selectable_nodes)(
    ::NS(TestNodeSetSingle)* SIXTRL_RESTRICT node_set,
    ::NS(arch_size_t) const min_sel_cnt )
{
    if( node_set != nullptr )
        node_set->setMinNumSelectableNodes( min_sel_cnt );
}

void NS(TestNodeSetSingle_set_max_num_selectable_nodes)(
    ::NS(TestNodeSetSingle)* SIXTRL_RESTRICT node_set,
    ::NS(arch_size_t) const max_sel_cnt )
{
    if( node_set != nullptr )
        node_set->setMaxNumSelectableNodes( max_sel_cnt );
}

void NS(TestNodeSetSingle_set_min_num_default_nodes)(
    ::NS(TestNodeSetSingle)* SIXTRL_RESTRICT node_set,
    ::NS(arch_size_t) const min_default_cnt )
{
    if( node_set != nullptr )
        node_set->setMinNumDefaultNodes( min_default_cnt );
}

void NS(TestNodeSetSingle_set_max_num_default_nodes)(
    ::NS(TestNodeSetSingle)* SIXTRL_RESTRICT node_set,
    ::NS(arch_size_t) const max_default_cnt )
{
    if( node_set != nullptr )
        node_set->setMaxNumDefaultNodes( max_default_cnt );
}

void NS(TestNodeSetSingle_set_can_directly_change_selected_node_flag)(
    ::NS(TestNodeSetSingle)* SIXTRL_RESTRICT node_set, bool const flag )
{
    if( node_set != nullptr )
        node_set->setCanDirectlyChangeSelectedNodeFlag( flag );
}

void NS(TestNodeSetSingle_set_can_unselect_node_flag)(
    ::NS(TestNodeSetSingle)* SIXTRL_RESTRICT node_set, bool const flag )
{
    if( node_set != nullptr )
        node_set->setCanUnselectNodeFlag( flag );
}

void NS(TestNodeSetSingle_set_use_auto_select_flag)(
    ::NS(TestNodeSetSingle)* SIXTRL_RESTRICT node_set, bool const flag )
{
    if( node_set != nullptr ) node_set->setUseAutoselectFlag( flag );
}

/* end: tests/sixtracklib/testlib/common/control/node_set_c99.cpp */
