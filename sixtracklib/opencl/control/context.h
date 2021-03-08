#ifndef SIXTRACKLIB_OPENCL_CONTROL_CONTEXT_H__
#define SIXTRACKLIB_OPENCL_CONTROL_CONTEXT_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/opencl/definitions.h"
    #include "sixtracklib/opencl/control/node_store.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/node_id.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES ) && defined( __cplusplus )
    #include "sixtracklib/opencl/opencl.hpp"
    #include "sixtracklib/common/backends/backend_obj_base.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) && defined( __cplusplus ) */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus )
    #include <algorithm>
    #include <iterator>
    #include <map>
    #include <memory>
    #include <utility>
    #include <vector>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) && defined( __cplusplus ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    template< SIXTRL_CXX_NAMESPACE::size_type N >
    struct TNOclContextKey
    {
        using node_id_type     = SIXTRL_CXX_NAMESPACE::NodeId;
        using size_type        = SIXTRL_CXX_NAMESPACE::size_type;
        using context_id_type  = SIXTRL_CXX_NAMESPACE::size_type;
        using platform_id_type = node_id_type::platform_id_type;
        using device_id_type   = node_id_type::device_id_type;
        using cmp_result_type  = ::NS(cmp_result_type);

        static constexpr size_type NUM_MAX_DEVICES = N;

        static constexpr platform_id_type ILLEGAL_PLATFORM_ID =
            SIXTRL_CXX_NAMESPACE::NodeId::ILLEGAL_PLATFORM_ID;

        static constexpr device_id_type ILLEGAL_DEVICE_ID =
            SIXTRL_CXX_NAMESPACE::NodeId::ILLEGAL_DEVICE_ID;

        static constexpr size_type ILLEGAL_IDENTIFIER =
            size_type{ 0x7fffffffffffffff };

        SIXTRL_HOST_FN TNOclContextKey() {
            std::fill( &this->device_ids[ 0 ], &this->device_ids[ 0 ],
                       ILLEGAL_DEVICE_ID );
        }

        SIXTRL_HOST_FN TNOclContextKey( TNOclContextKey const& ) = default;
        SIXTRL_HOST_FN TNOclContextKey( TNOclContextKey&& ) = default;

        SIXTRL_HOST_FN TNOclContextKey& operator=(
            TNOclContextKey&& ) = default;

        SIXTRL_HOST_FN TNOclContextKey& operator=(
            TNOclContextKey const& ) = default;

        SIXTRL_HOST_FN ~TNOclContextKey() = default;

        SIXTRL_HOST_FN void clear() SIXTRL_NOEXCEPT {
            namespace st = SIXTRL_CXX_NAMESPACE;
            this->platform_id = st::NodeId::ILLEGAL_PLATFORM_ID;
            this->num_devices = size_type{ 0 };
            this->identifier = ILLEGAL_IDENTIFIER;
            std::fill( &this->device_ids[ 0 ],
                       &this->device_ids[ NUM_MAX_DEVICES ],
                       st::NodeId::ILLEGAL_DEVICE_ID );
        }

        SIXTRL_HOST_FN bool is_legal() const SIXTRL_NOEXCEPT {
            bool result = (
                ( this->platform_id != ILLEGAL_PLATFORM_ID ) &&
                ( this->identifier  != ILLEGAL_IDENTIFIER ) &&
                ( this->num_devices < NUM_MAX_DEVICES ) &&
                ( this->num_devices > size_type{ 0 } ) );

            if( result )
            {
                for( size_type ii = 0u ; ii < this->num_devices ; ++ii )
                {
                    if( this->device_ids[ ii ] == ILLEGAL_DEVICE_ID )
                    {
                        result = false;
                        break;
                    }
                }
            }

            return result;
        }


        SIXTRL_HOST_FN bool contains_node_id( node_id_type const&
            SIXTRL_RESTRICT_REF node_id ) const SIXTRL_NOEXCEPT
        {
            bool contains = false;

            if( ( node_id.is_legal() ) && ( this->is_legal() ) &&
                ( node_id.platform_id() == this->platform_id ) )
            {
                for( size_type ii = 0u ; ii < this->num_devices ; ++ii )
                {
                    if( this->device_ids[ ii ] == node_id.device_id() )
                    {
                        contains = true;
                        break;
                    }
                }
            }

            return contains;
        }

        SIXTRL_HOST_FN cmp_result_type compare(
            TNOclContextKey< N > const& rhs ) const SIXTRL_NOEXCEPT
        {
            cmp_result_type cmp_result = cmp_result_type{ 0 };

            if( this != &rhs )
            {
                if( this->num_devices != rhs.num_devices )
                {
                    cmp_result = ( this->num_devices > rhs.num_devices )
                        ? cmp_result_type{ 1 } : cmp_result_type{ -1 };
                }

                if( ( cmp_result == cmp_result_type{ 0 } ) &&
                    ( this->platform_id != rhs.platform_id ) )
                {
                    cmp_result = ( this->platform_id > rhs.platform_id )
                        ? cmp_result_type{ 1 } : cmp_result_type{ -1 };
                }

                if( cmp_result == cmp_result_type{ 0 } )
                {
                    cmp_result = std::memcmp(
                        &this->device_ids[ 0 ], &rhs.device_ids[ 0 ],
                        sizeof( device_id_type ) * this->num_devices );
                }

                if( ( cmp_result == cmp_result_type{ 0 } ) &&
                    ( this->identifier != rhs.identifier ) )
                {
                    cmp_result = ( this->identifier > rhs.identifier )
                        ? cmp_result_type{ 1 } : cmp_result_type{ -1 };
                }
            }

            return cmp_result;
        }

        SIXTRL_HOST_FN bool operator<(
            TNOclContextKey< NUM_MAX_DEVICES > const& rhs ) const SIXTRL_NOEXCEPT
        {
            return ( this->compare( rhs ) < cmp_result_type{ 0 } );
        }

        SIXTRL_HOST_FN bool operator==(
            TNOclContextKey< NUM_MAX_DEVICES > const& rhs ) const SIXTRL_NOEXCEPT
        {
            return ( this->compare( rhs ) == cmp_result_type{ 0 } );
        }

        SIXTRL_HOST_FN bool operator!=(
            TNOclContextKey< NUM_MAX_DEVICES > const& rhs ) const SIXTRL_NOEXCEPT
        {
            return ( this->compare( rhs ) != cmp_result_type{ 0 } );
        }

        device_id_type device_ids[ NUM_MAX_DEVICES ];

        size_type num_devices        = size_type{ 0 };
        platform_id_type platform_id = ILLEGAL_PLATFORM_ID;
        context_id_type identifier   = context_id_type{ 0 };
    };

    template< SIXTRL_CXX_NAMESPACE::size_type N >
    constexpr typename TNOclContextKey< N >::size_type
    TNOclContextKey< N >::NUM_MAX_DEVICES;

    template< SIXTRL_CXX_NAMESPACE::size_type N >
    constexpr typename TNOclContextKey< N >::platform_id_type
    TNOclContextKey< N >::ILLEGAL_PLATFORM_ID;

    template< SIXTRL_CXX_NAMESPACE::size_type N >
    constexpr typename TNOclContextKey< N >::device_id_type
    TNOclContextKey< N >::ILLEGAL_DEVICE_ID;

    template< SIXTRL_CXX_NAMESPACE::size_type N >
    constexpr typename TNOclContextKey< N >::size_type
    TNOclContextKey< N >::ILLEGAL_IDENTIFIER;



    typedef TNOclContextKey< 8 > OclContextKey;

    /* ********************************************************************* */

    class OclContext : public SIXTRL_CXX_NAMESPACE::BackendObjBase
    {
        public:

        using node_id_type     = SIXTRL_CXX_NAMESPACE::NodeId;
        using platform_id_type = node_id_type::platform_id_type;
        using device_id_type   = node_id_type::device_id_type;
        using node_index_type  = node_id_type::index_type;
        using node_store_type  = SIXTRL_CXX_NAMESPACE::OclNodeStore;
        using key_type         = SIXTRL_CXX_NAMESPACE::OclContextKey;

        static constexpr class_id_type BASE_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::OPENCL_CONTEXT_CLASS_ID;

        static constexpr class_id_type CLASS_ID =
            SIXTRL_CXX_NAMESPACE::OPENCL_CONTEXT_CLASS_ID;

        SIXTRL_HOST_FN OclContext(
            std::shared_ptr< node_store_type >& SIXTRL_RESTRICT_REF node_store,
            node_id_type const& SIXTRL_RESTRICT_REF node_id,
            size_type const key_identifier = size_type{ 0 } );

        SIXTRL_HOST_FN OclContext(
            std::shared_ptr< node_store_type >& SIXTRL_RESTRICT_REF node_store,
            platform_id_type const platform_id,
            device_id_type const* SIXTRL_RESTRICT device_ids_begin,
            size_type const num_devices,
            size_type const key_identifier = size_type{ 0 } );

        SIXTRL_HOST_FN OclContext(
            std::shared_ptr< node_store_type >& SIXTRL_RESTRICT_REF node_store,
            node_id_type const* SIXTRL_RESTRICT node_ids_begin,
            size_type const num_devices,
            size_type const key_identifier = size_type{ 0 } );

        template< typename NodeIdIter >
        SIXTRL_HOST_FN OclContext(
            std::shared_ptr< node_store_type >& SIXTRL_RESTRICT_REF node_store,
            NodeIdIter begin, NodeIdIter end,
            size_type const key_identifier = size_type{ 0 } ) :
            BackendObjBase( SIXTRL_CXX_NAMESPACE::BACKEND_ID_OPENCL,
                BASE_CLASS_ID, CLASS_ID ), m_key(), m_node_store( node_store )
        {
            namespace st = SIXTRL_CXX_NAMESPACE;

            static_assert( std::is_same<
                typename std::decay< typename std::iterator_traits< NodeIdIter
                    >::value_type >::value_type, node_id_type >::value,
                "NodeIdIter has required to be iterators for sixtrack::NodeId" );

            std::vector< node_id_type > temp_node_ids( begin, end );
            st::status_type const status = this->_init_context(
                temp_node_ids.data(), temp_node_ids.size(), key_identifier );

            if( status != st::STATUS_SUCCESS )
                throw std::runtime_error(
                    "unable to construct context from range of node_ids" );
        }

        SIXTRL_HOST_FN OclContext( OclContext const& ) = default;
        SIXTRL_HOST_FN OclContext( OclContext&& ) = default;

        SIXTRL_HOST_FN OclContext& operator=( OclContext&& ) = default;
        SIXTRL_HOST_FN OclContext& operator=( OclContext const& ) = default;

        SIXTRL_HOST_FN virtual ~OclContext() = default;

        SIXTRL_HOST_FN key_type const& key() const SIXTRL_NOEXCEPT {
            return this->m_key; }

        SIXTRL_HOST_FN size_type idx_for_node_id( node_id_type const&
            SIXTRL_RESTRICT_REF node_id ) const SIXTRL_NOEXCEPT {
            size_type idx = key_type::NUM_MAX_DEVICES;
            if( ( this->m_key.is_legal() ) && ( node_id.is_legal() ) &&
                ( this->m_key.platform_id == node_id.platform_id() ) &&
                ( this->m_key.num_devices > size_type{ 0 } ) &&
                ( this->m_node_store.get() != nullptr ) &&
                ( this->m_node_store->has_platform_id(
                    node_id.platform_id() ) ) )
            {
                SIXTRL_ASSERT( this->m_node_store->num_nodes(
                    node_id.platform_id() ) >= this->m_key.num_devices );

                for( size_type ii = 0u ; ii < this->m_key.num_devices ; ++ii ) {
                    if( this->m_key.device_ids[ ii ] == node_id.device_id() ) {
                        idx = ii;
                        break;
                    }
                }
            }
            return idx;
        }

        SIXTRL_HOST_FN node_index_type node_index_for_node_id(
            node_id_type const& SIXTRL_RESTRICT_REF node_id ) const SIXTRL_NOEXCEPT
        {
            node_index_type node_index = node_id_type::ILLEGAL_INDEX;

            if( ( this->m_key.is_legal() ) && ( node_id.is_legal() ) &&
                ( this->m_key.platform_id == node_id.platform_id() ) &&
                ( this->m_key.num_devices > size_type{ 0 } ) &&
                ( this->m_node_store.get() != nullptr ) &&
                ( this->m_node_store->has_platform_id(
                    node_id.platform_id() ) ) )
            {
                SIXTRL_ASSERT( this->m_node_store->num_nodes(
                    node_id.platform_id() ) >= this->m_key.num_devices );

                for( size_type ii = 0u ; ii < this->m_key.num_devices ; ++ii ) {
                    if( this->m_key.device_ids[ ii ] == node_id.device_id() ) {
                        SIXTRL_ASSERT( this->m_node_indices[ ii ] !=
                            node_id_type::ILLEGAL_INDEX );
                        node_index = this->m_node_indices[ ii ];
                        break;
                    }
                }
            }

            return node_index;
        }

        SIXTRL_HOST_FN size_type num_node_ids() const SIXTRL_NOEXCEPT
        {
            SIXTRL_ASSERT( this->m_node_store.get() != nullptr );
            SIXTRL_ASSERT( this->m_node_store->has_platform_id(
                this->m_key.platform_id ) );
            SIXTRL_ASSERT( this->m_node_store->num_nodes(
                this->m_key.platform_id ) >= this->m_key.num_devices );

            return this->m_key.num_devices;
        }

        SIXTRL_HOST_FN bool has_node_id(
            node_id_type const& node_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_id_type node_id(
            size_type const id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN status_type node_ids(
            std::vector< node_id_type >& SIXTRL_RESTRICT_REF node_ids ) const;

        SIXTRL_HOST_FN status_type cl_devices(
            std::vector< cl::Device >& SIXTRL_RESTRICT_REF cl_devices ) const;

        SIXTRL_HOST_FN cl::Device const& cl_device(
            node_id_type const& SIXTRL_RESTRICT_REF node_id ) const {
                return this->cl_device( node_id.platform_id(),
                    node_id.device_id() ); }

        SIXTRL_HOST_FN cl::Device const& cl_device(
            platform_id_type const platform_id,
            device_id_type const device_id ) const {
            if( this->m_node_store.get() == nullptr )
                throw std::runtime_error( "no node_store available" );
            return this->m_node_store->cl_device( platform_id, device_id ); }

        SIXTRL_HOST_FN cl::Device const& cl_device(
            node_index_type const node_index  ) const {
            if( this->m_node_store.get() == nullptr )
                throw std::runtime_error( "no node_store available" );
            return this->m_node_store->cl_device( node_index ); }

        SIXTRL_HOST_FN cl::Context& cl_context() SIXTRL_NOEXCEPT {
            return this->m_cl_context; }

        SIXTRL_HOST_FN cl::Context const& cl_context() const SIXTRL_NOEXCEPT {
            return this->m_cl_context; }

        SIXTRL_HOST_FN void clear()
        {
            this->m_key.clear();
            this->m_cl_context = cl::Context();

            std::fill( &this->m_node_indices[ 0 ],
                       &this->m_node_indices[ key_type::NUM_MAX_DEVICES ],
                       node_id_type::ILLEGAL_INDEX );
        }

        SIXTRL_HOST_FN std::shared_ptr< node_store_type > const&
        shared_node_store() const SIXTRL_NOEXCEPT { return this->m_node_store; }

        SIXTRL_HOST_FN std::shared_ptr< node_store_type >&
        shared_node_store() SIXTRL_NOEXCEPT { return this->m_node_store; }

        private:

        SIXTRL_HOST_FN status_type _init_context(
            node_id_type const* SIXTRL_RESTRICT node_ids_begin,
            size_type const num_node_ids, size_type const key_identifier );

        key_type m_key;
        node_index_type m_node_indices[ key_type::NUM_MAX_DEVICES ];
        cl::Context m_cl_context;
        std::shared_ptr< node_store_type > m_node_store;
    };

    template<> struct BackendObjTraits< SIXTRL_CXX_NAMESPACE::OclContext >
    {
        static constexpr backend_id_type BACKEND_ID =
            SIXTRL_CXX_NAMESPACE::BACKEND_ID_OPENCL;

        static constexpr derived_class_id_type BASE_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::OPENCL_CONTEXT_CLASS_ID;

        static constexpr derived_class_id_type DERIVED_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::OPENCL_CONTEXT_CLASS_ID;
    };

    template<> struct BackendObjInvTraits<
        SIXTRL_CXX_NAMESPACE::BACKEND_ID_OPENCL,
        SIXTRL_CXX_NAMESPACE::OPENCL_CONTEXT_CLASS_ID >
    {
        typedef SIXTRL_CXX_NAMESPACE::OclContext backend_obj_type;
    };

    /* ********************************************************************* */

    class OclContextStore : public SIXTRL_CXX_NAMESPACE::BackendObjBase {
        public:
        using context_type = SIXTRL_CXX_NAMESPACE::OclContext;
        using node_store_type = SIXTRL_CXX_NAMESPACE::OclNodeStore;
        using key_type = SIXTRL_CXX_NAMESPACE::OclContextKey;
        using node_id_type = key_type::node_id_type;
        using platform_id_type = key_type::platform_id_type;

        static constexpr class_id_type BASE_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::OPENCL_CONTEXT_STORE_CLASS_ID;

        static constexpr class_id_type CLASS_ID =
            SIXTRL_CXX_NAMESPACE::OPENCL_CONTEXT_STORE_CLASS_ID;

        SIXTRL_HOST_FN OclContextStore( std::shared_ptr< node_store_type >&
            SIXTRL_RESTRICT_REF ptr_node_store );

        SIXTRL_HOST_FN OclContextStore( OclContextStore const& ) = delete;
        SIXTRL_HOST_FN OclContextStore( OclContextStore&& ) = delete;

        SIXTRL_HOST_FN OclContextStore& operator=( OclContextStore&& ) = delete;
        SIXTRL_HOST_FN OclContextStore& operator=(
            OclContextStore const& ) = delete;

        SIXTRL_HOST_FN virtual ~OclContextStore();

        SIXTRL_HOST_FN bool empty() const SIXTRL_NOEXCEPT {
            return this->m_stored_ctx.empty(); }

        SIXTRL_HOST_FN size_type size() const SIXTRL_NOEXCEPT {
            return this->m_stored_ctx.size(); }

        SIXTRL_HOST_FN void keys(
            std::vector< key_type >& SIXTRL_RESTRICT_REF key_array,
            node_id_type const node_id ) {
            return this->keys( key_array, &node_id, size_type{ 1 } ); }

        SIXTRL_HOST_FN void keys(
            std::vector< key_type >& SIXTRL_RESTRICT_REF key_array,
            node_id_type const* node_ids_begin, size_type const num_node_ids );

        SIXTRL_HOST_FN std::shared_ptr< node_store_type >&
        share_node_store() SIXTRL_NOEXCEPT { return this->m_node_store; }

        template< typename NodeIdIter >
        SIXTRL_HOST_FN void keys(
            std::vector< key_type >& SIXTRL_RESTRICT_REF key_array,
            NodeIdIter node_ids_begin, NodeIdIter node_ids_end )
        {
            std::vector< node_id_type > temp_node_ids(
                node_ids_begin, node_ids_end );

            std::sort( temp_node_ids.begin(), temp_node_ids.end() );
            temp_node_ids.erase( std::unique( temp_node_ids.begin(),
                temp_node_ids.end() ), temp_node_ids.end() );

            this->keys( key_array, temp_node_ids.data(), temp_node_ids.size() );
        }

        SIXTRL_HOST_FN bool has_context(
            key_type const& SIXTRL_RESTRICT key ) const SIXTRL_NOEXCEPT {
            bool is_stored = false;
            if( !this->m_stored_ctx.empty() ) {
                auto it = this->m_stored_ctx.find( key );
                is_stored = ( ( it != this->m_stored_ctx.end() ) &&
                              ( it->second.get() != nullptr ) ); }
            return is_stored; }

        SIXTRL_HOST_FN std::shared_ptr< context_type > shared_context(
            key_type const& SIXTRL_RESTRICT key ) const {
            if( !this->m_stored_ctx.empty() ) {
                auto it = this->m_stored_ctx.find( key );
                if( it !=  this->m_stored_ctx.end() ) { return it->second; } }
            return std::shared_ptr< context_type >( nullptr ); }

        SIXTRL_HOST_FN status_type store_context(
            std::shared_ptr< context_type >& SIXTRL_RESTRICT_REF ptr_ctx ) {
            namespace st = SIXTRL_CXX_NAMESPACE;
            st::status_type status = st::STATUS_GENERAL_FAILURE;
            if( ptr_ctx.get() != nullptr ) {
                key_type const& key = ptr_ctx->key();

                if( ( key.platform_id != node_id_type::ILLEGAL_PLATFORM_ID ) &&
                    ( key.num_devices > size_type{ 0 } ) ) {
                    auto it = this->m_stored_ctx.find( key );
                    if( it == this->m_stored_ctx.end() ) {
                        auto ret = this->m_stored_ctx.emplace(
                            std::make_pair( key, ptr_ctx ) );
                        if( ret.second ) status = st::STATUS_SUCCESS; }
                }
            }
            return status;
        }

        SIXTRL_HOST_FN status_type remove_context(
            key_type const& SIXTRL_RESTRICT_REF key ) {
            namespace st = SIXTRL_CXX_NAMESPACE;
            st::status_type status = st::STATUS_GENERAL_FAILURE;
            if( !this->m_stored_ctx.empty() ) {
                auto it = this->m_stored_ctx.find( key );
                if( ( it != this->m_stored_ctx.end() ) &&
                    ( it->second.get() != nullptr ) ) {
                    it->second.reset();
                    this->m_stored_ctx.erase( it );
                    status = st::STATUS_SUCCESS;
                }
            }
            return status;
        }

        private:

        std::map< key_type, std::shared_ptr< context_type > > m_stored_ctx;
        std::shared_ptr< node_store_type > m_node_store;
    };

    template<> struct BackendObjTraits< SIXTRL_CXX_NAMESPACE::OclContextStore >
    {
        static constexpr backend_id_type BACKEND_ID =
            SIXTRL_CXX_NAMESPACE::BACKEND_ID_OPENCL;

        static constexpr derived_class_id_type BASE_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::OPENCL_CONTEXT_STORE_CLASS_ID;

        static constexpr derived_class_id_type DERIVED_CLASS_ID =
            SIXTRL_CXX_NAMESPACE::OPENCL_CONTEXT_STORE_CLASS_ID;
    };

    template<> struct BackendObjInvTraits<
        SIXTRL_CXX_NAMESPACE::BACKEND_ID_OPENCL,
        SIXTRL_CXX_NAMESPACE::OPENCL_CONTEXT_STORE_CLASS_ID >
    {
        typedef SIXTRL_CXX_NAMESPACE::OclContextStore backend_obj_type;
    };
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
typedef SIXTRL_CXX_NAMESPACE::OclContext NS(OclContext);
#else  /* !defined( __cplusplus ) || defined( _GPUCODE ) */
typedef void NS(OclContext);
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */
#endif /* SIXTRACKLIB_OPENCL_CONTROL_CONTEXT_H__ */
