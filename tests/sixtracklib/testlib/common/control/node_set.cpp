#include "sixtracklib/testlib/common/control/node_set.hpp"
#include "sixtracklib/common/control/node_store.hpp"
#include "sixtracklib/common/control/node_set.hpp"

namespace SIXTRL_CXX_NAMESPACE
{
    namespace tests
    {
        namespace st = SIXTRL_CXX_NAMESPACE;
        using _set_t = st::tests::TestNodeSetBase;

        TestNodeSetBase::TestNodeSetBase(
            st::NodeStore& SIXTRL_RESTRICT_REF store ) :
            st::NodeSetBase( store )
        {
        }

        void TestNodeSetBase::setMinNumSelectableNodes(
            _set_t::size_type const min_sel_cnt )
        {
            _set_t::lock_t const lock( *this->lockable() );
            this->doSetMinNumSelectableNodes( lock, min_sel_cnt );
        }

        void TestNodeSetBase::setMaxNumSelectableNodes(
            _set_t::size_type const max_sel_cnt )
        {
            _set_t::lock_t const lock( *this->lockable() );
            this->doSetMaxNumSelectableNodes( lock, max_sel_cnt );
        }

        void TestNodeSetBase::setMinNumDefaultNodes(
            _set_t::size_type const min_default_cnt )
        {
            _set_t::lock_t const lock( *this->lockable() );
            this->doSetMinNumDefaultNodes( lock, min_default_cnt );
        }

        void TestNodeSetBase::setMaxNumDefaultNodes(
            _set_t::size_type const max_default_cnt )
        {
            _set_t::lock_t const lock( *this->lockable() );
            this->doSetMaxNumDefaultNodes( lock, max_default_cnt );
        }

        /* ----------------------------------------------------------------- */

        TestNodeSetSingle::TestNodeSetSingle(
            st::NodeStore& SIXTRL_RESTRICT_REF store ) :
            st::NodeSetSingle( store )
        {
            this->doSetCanDirectlyChangeSelectedNodeFlag( true );
            this->doSetCanUnselectNodeFlag( true );
            this->doSetUseAutoselectFlag( false );
        }

        void TestNodeSetSingle::setMinNumSelectableNodes(
            TestNodeSetSingle::size_type const min_sel_cnt )
        {
            _set_t::lock_t const lock( *this->lockable() );
            this->doSetMinNumSelectableNodes( lock, min_sel_cnt );
        }

        void TestNodeSetSingle::setMaxNumSelectableNodes(
            TestNodeSetSingle::size_type const max_sel_cnt )
        {
            _set_t::lock_t const lock( *this->lockable() );
            this->doSetMaxNumSelectableNodes( lock, max_sel_cnt );
        }

        void TestNodeSetSingle::setMinNumDefaultNodes(
            TestNodeSetSingle::size_type const min_default_cnt )
        {
            _set_t::lock_t const lock( *this->lockable() );
            this->doSetMinNumDefaultNodes( lock, min_default_cnt );
        }

        void TestNodeSetSingle::setMaxNumDefaultNodes(
            TestNodeSetSingle::size_type const max_default_cnt )
        {
            _set_t::lock_t const lock( *this->lockable() );
            this->doSetMaxNumDefaultNodes( lock, max_default_cnt );
        }

        void TestNodeSetSingle::setCanDirectlyChangeSelectedNodeFlag(
            bool const flag )
        {
            this->doSetCanDirectlyChangeSelectedNodeFlag( flag );
        }

        void TestNodeSetSingle::setCanUnselectNodeFlag(
            bool const flag )
        {
            this->doSetCanUnselectNodeFlag( flag );
        }

        void TestNodeSetSingle::setUseAutoselectFlag( bool const flag )
        {
            this->doSetUseAutoselectFlag( flag );
        }
    }
}

/* end: tests/sixtracklib/testlib/common/control/node_set.cpp */
