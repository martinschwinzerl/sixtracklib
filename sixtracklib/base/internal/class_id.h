#ifndef SIXTRACKLIB_BASE_INTERNAL_CLASS_ID_H__
#define SIXTRACKLIB_BASE_INTERNAL_CLASS_ID_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/base/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

/* ************************************************************************* */

typedef SIXTRL_UINT64_T NS(obj_class_id_t);
typedef SIXTRL_UINT64_T NS(obj_class_variant_t);

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    typedef ::NS(obj_class_id_t) obj_class_id_t;
    typedef ::NS(obj_class_variant_t) obj_class_variant_t;
}
#endif /* C++ */

/* ************************************************************************* */
/* various: */

#if !defined( SIXTRL_CLASS_ID_UNDEFINED )
    #define SIXTRL_CLASS_ID_UNDEFINED 0xffff
#endif /* !defined( SIXTRL_CLASS_ID_UNDEFINED ) */

#if !defined( _GPUCODE )
#if defined( __cplusplus )
extern "C" {
#endif /* c++ */

SIXTRL_STATIC_VAR const NS(obj_class_id_t) NS(CLASS_ID_UNDEFINED) =
    ( NS(obj_class_id_t) )SIXTRL_CLASS_ID_UNDEFINED;

#if defined( __cplusplus )
}
#endif /* c++ */
#endif /* Host */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    static constexpr obj_class_id_t CLASS_ID_UNDEFINED =
        static_cast< obj_class_id_t >( SIXTRL_CLASS_ID_UNDEFINED );

} /* ns: SIXTRL_CXX_NAMESPACE */
#endif /* C++ */

/* ------------------------------------------------------------------------- */
/* node: */

#if !defined( SIXTRL_CLASS_ID_ARCHITECTURE )
    #define SIXTRL_CLASS_ID_ARCHITECTURE 0
#endif /* !defined( SIXTRL_CLASS_ID_ARCHITECTURE ) */

#if !defined( SIXTRL_CLASS_ID_NODE_ID )
    #define SIXTRL_CLASS_ID_NODE_ID 1
#endif /* !defined( SIXTRL_CLASS_ID_NODE_ID ) */

#if !defined( SIXTRL_CLASS_ID_NODE_INFO )
    #define SIXTRL_CLASS_ID_NODE_INFO 2
#endif /* !defined( SIXTRL_CLASS_ID_NODE_INFO ) */

#if !defined( _GPUCODE )
#if defined( __cplusplus )
extern "C" {
#endif /* c++ */

SIXTRL_STATIC_VAR const NS(obj_class_id_t) NS(CLASS_ID_ARCHITECTURE) =
    ( NS(obj_class_id_t) )SIXTRL_CLASS_ID_ARCHITECTURE;

SIXTRL_STATIC_VAR const NS(obj_class_id_t) NS(CLASS_ID_NODE_ID) =
    ( NS(obj_class_id_t) )SIXTRL_CLASS_ID_NODE_ID;

SIXTRL_STATIC_VAR const NS(obj_class_id_t) NS(CLASS_ID_NODE_INFO) =
    ( NS(obj_class_id_t) )SIXTRL_CLASS_ID_NODE_INFO;

#if defined( __cplusplus )
}
#endif /* c++ */
#endif /* Host */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    static constexpr obj_class_id_t CLASS_ID_ARCHITECTURE =
        static_cast< obj_class_id_t >( SIXTRL_CLASS_ID_ARCHITECTURE );

    static constexpr obj_class_id_t CLASS_ID_NODE_ID =
        static_cast< obj_class_id_t >( SIXTRL_CLASS_ID_NODE_ID );


    static constexpr obj_class_id_t CLASS_ID_NODE_INFO =
        static_cast< obj_class_id_t >( SIXTRL_CLASS_ID_NODE_INFO );

} /* ns: SIXTRL_CXX_NAMESPACE */
#endif /* C++ */
#endif /* SIXTRACKLIB_BASE_INTERNAL_CLASS_ID_H__ */
