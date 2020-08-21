#ifndef SIXTRACKLIB_BASE_INTERNAL_CLASS_ID_H__
#define SIXTRACKLIB_BASE_INTERNAL_CLASS_ID_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/definitions.h"
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
/* sixtracklib_base/backend: */

#if !defined( SIXTRL_CLASS_ID_BACKEND )
    #define SIXTRL_CLASS_ID_BACKEND 0
#endif /* !defined( SIXTRL_CLASS_ID_BACKEND ) */

/* ------------------------------------------------------------------------- */
/* sixtracklib_base/node: */

#if !defined( SIXTRL_CLASS_ID_NODE_ID )
    #define SIXTRL_CLASS_ID_NODE_ID 1
#endif /* !defined( SIXTRL_CLASS_ID_NODE_ID ) */

#if !defined( SIXTRL_CLASS_ID_NODE_INFO )
    #define SIXTRL_CLASS_ID_NODE_INFO 2
#endif /* !defined( SIXTRL_CLASS_ID_NODE_INFO ) */

/* ------------------------------------------------------------------------- */
/* sixtracklib_base/control: */

#if !defined( SIXTRL_CLASS_ID_CONTEXT )
    #define SIXTRL_CLASS_ID_CONTEXT 3
#endif /* !defined( SIXTRL_CLASS_ID_CONTEXT ) */

#if !defined( SIXTRL_CLASS_ID_CONTEXT_STORE )
    #define SIXTRL_CLASS_ID_CONTEXT_STORE 4
#endif /* !defined( SIXTRL_CLASS_ID_CONTEXT_STORE ) */

/* ------------------------------------------------------------------------- */
/* sixtracklib_base/program: */

#if !defined( SIXTRL_CLASS_ID_PROGRAM_COMPILE_OPTION_ITEM )
    #define SIXTRL_CLASS_ID_PROGRAM_COMPILE_OPTION_ITEM 5
#endif /* !defined( SIXTRL_CLASS_ID_PROGRAM_COMPILE_OPTION_ITEM ) */

#if !defined( SIXTRL_CLASS_ID_PROGRAM_COMPILE_OPTIONS )
    #define SIXTRL_CLASS_ID_PROGRAM_COMPILE_OPTIONS 6
#endif /* !defined( SIXTRL_CLASS_ID_PROGRAM_COMPILE_OPTIONS ) */

#if !defined( SIXTRL_CLASS_ID_PROGRAM_CODE )
    #define SIXTRL_CLASS_ID_PROGRAM_CODE 7
#endif /* !defined( SIXTRL_CLASS_ID_PROGRAM_CODE ) */

#if !defined( SIXTRL_CLASS_ID_PROGRAM_INTERMEDIATE_REPR )
    #define SIXTRL_CLASS_ID_PROGRAM_INTERMEDIATE_REPR 8
#endif /* !defined( SIXTRL_CLASS_ID_PROGRAM_INTERMEDIATE_REPR ) */

#if !defined( SIXTRL_CLASS_ID_PROGRAM_COMPILED )
    #define SIXTRL_CLASS_ID_PROGRAM_COMPILED 9
#endif /* !defined( SIXTRL_CLASS_ID_PROGRAM_COMPILED ) */

#if !defined( SIXTRL_CLASS_ID_PROGRAM_KERNEL )
    #define SIXTRL_CLASS_ID_PROGRAM_KERNEL 10
#endif /* !defined( SIXTRL_CLASS_ID_PROGRAM_KERNEL ) */

#if !defined( _GPUCODE )
#if defined( __cplusplus )
extern "C" {
#endif /* c++ */

/* ------------------------------------------------------------------------- */
/* sixtracklib_base/backend: */

SIXTRL_STATIC_VAR const NS(obj_class_id_t) NS(CLASS_ID_BACKEND) =
    ( NS(obj_class_id_t) )SIXTRL_CLASS_ID_BACKEND;

/* ------------------------------------------------------------------------- */
/* sixtracklib_base/node: */

SIXTRL_STATIC_VAR const NS(obj_class_id_t) NS(CLASS_ID_NODE_ID) =
    ( NS(obj_class_id_t) )SIXTRL_CLASS_ID_NODE_ID;

SIXTRL_STATIC_VAR const NS(obj_class_id_t) NS(CLASS_ID_NODE_INFO) =
    ( NS(obj_class_id_t) )SIXTRL_CLASS_ID_NODE_INFO;

/* ------------------------------------------------------------------------- */
/* sixtracklib_base/control: */

SIXTRL_STATIC_VAR const NS(obj_class_id_t) NS(CLASS_ID_CONTEXT) =
    ( NS(obj_class_id_t) )SIXTRL_CLASS_ID_CONTEXT;

SIXTRL_STATIC_VAR const NS(obj_class_id_t) NS(CLASS_ID_CONTEXT_STORE) =
    ( NS(obj_class_id_t) )SIXTRL_CLASS_ID_CONTEXT_STORE;

/* ------------------------------------------------------------------------- */
/* sixtracklib_base/program: */

SIXTRL_STATIC_VAR const NS(obj_class_id_t)
    NS(CLASS_ID_PROGRAM_COMPILE_OPTION_ITEM) = ( NS(obj_class_id_t)
        )SIXTRL_CLASS_ID_PROGRAM_COMPILE_OPTION_ITEM;

SIXTRL_STATIC_VAR const NS(obj_class_id_t)
    NS(CLASS_ID_PROGRAM_COMPILE_OPTIONS) = ( NS(obj_class_id_t)
        )SIXTRL_CLASS_ID_PROGRAM_COMPILE_OPTIONS;

SIXTRL_STATIC_VAR const NS(obj_class_id_t) NS(CLASS_ID_PROGRAM_CODE) =
    ( NS(obj_class_id_t) )SIXTRL_CLASS_ID_PROGRAM_CODE;

SIXTRL_STATIC_VAR const NS(obj_class_id_t)
    NS(CLASS_ID_PROGRAM_INTERMEDIATE_REPR) = ( NS(obj_class_id_t)
        )SIXTRL_CLASS_ID_PROGRAM_INTERMEDIATE_REPR;

SIXTRL_STATIC_VAR const NS(obj_class_id_t) NS(CLASS_ID_PROGRAM_COMPILED) =
    ( NS(obj_class_id_t) )SIXTRL_CLASS_ID_PROGRAM_COMPILED;

SIXTRL_STATIC_VAR const NS(obj_class_id_t) NS(CLASS_ID_PROGRAM_KERNEL) =
    ( NS(obj_class_id_t) )SIXTRL_CLASS_ID_PROGRAM_KERNEL;

#if defined( __cplusplus )
}
#endif /* c++ */
#endif /* Host */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    /* --------------------------------------------------------------------- */
    /* sixtracklib_base/backend: */

    static constexpr obj_class_id_t CLASS_ID_BACKEND =
        static_cast< obj_class_id_t >( SIXTRL_CLASS_ID_BACKEND );

    /* --------------------------------------------------------------------- */
    /* sixtracklib_base/node: */

    static constexpr obj_class_id_t CLASS_ID_NODE_ID =
        static_cast< obj_class_id_t >( SIXTRL_CLASS_ID_NODE_ID );

    static constexpr obj_class_id_t CLASS_ID_NODE_INFO =
        static_cast< obj_class_id_t >( SIXTRL_CLASS_ID_NODE_INFO );

    /* --------------------------------------------------------------------- */
    /* sixtracklib_base/control: */

    static constexpr obj_class_id_t CLASS_ID_CONTEXT =
        static_cast< obj_class_id_t >( SIXTRL_CLASS_ID_CONTEXT );

    static constexpr obj_class_id_t CLASS_ID_CONTEXT_STORE =
        static_cast< obj_class_id_t >( SIXTRL_CLASS_ID_CONTEXT_STORE );

    /* --------------------------------------------------------------------- */
    /* sixtracklib_base/program: */

    static constexpr obj_class_id_t CLASS_ID_PROGRAM_COMPILE_OPTION_ITEM =
        static_cast< obj_class_id_t >(
            SIXTRL_CLASS_ID_PROGRAM_COMPILE_OPTION_ITEM );

    static constexpr obj_class_id_t CLASS_ID_PROGRAM_COMPILE_OPTIONS =
        static_cast< obj_class_id_t >(
            SIXTRL_CLASS_ID_PROGRAM_COMPILE_OPTIONS );

    static constexpr obj_class_id_t CLASS_ID_PROGRAM_CODE  =
        static_cast< obj_class_id_t >( SIXTRL_CLASS_ID_PROGRAM_CODE );

    static constexpr obj_class_id_t CLASS_ID_PROGRAM_INTERMEDIATE_REPR =
        static_cast< obj_class_id_t >(
            SIXTRL_CLASS_ID_PROGRAM_INTERMEDIATE_REPR );

    static constexpr obj_class_id_t CLASS_ID_PROGRAM_COMPILED =
        static_cast< obj_class_id_t >( SIXTRL_CLASS_ID_PROGRAM_COMPILED );

    static constexpr obj_class_id_t CLASS_ID_PROGRAM_KERNEL  =
        static_cast< obj_class_id_t >( SIXTRL_CLASS_ID_PROGRAM_KERNEL );

} /* ns: SIXTRL_CXX_NAMESPACE */
#endif /* C++ */
#endif /* SIXTRACKLIB_BASE_INTERNAL_CLASS_ID_H__ */
