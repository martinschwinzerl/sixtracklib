#ifndef SIXTRACKLIB_BASE_PROGRAM_DEFINITIONS_H__
#define SIXTRACKLIB_BASE_PROGRAM_DEFINITIONS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */


typedef SIXTRL_INT64_T  NS(program_code_id_t);
typedef SIXTRL_INT64_T  NS(program_ir_id_t);
typedef SIXTRL_UINT64_T NS(program_compile_option_kind_t);
typedef SIXTRL_INT64_T  NS(program_compiled_id_t);
typedef SIXTRL_INT64_T  NS(kernel_id_t);

#if !defined( SIXTRL_PROGRAM_CODE_ILLEGAL_ID )
    #define SIXTRL_PROGRAM_CODE_ILLEGAL_ID -1
#endif /* #define SIXTRL_PROGRAM_CODE_ILLEGAL_ID -1 */

#if !defined( SIXTRL_PROGRAM_INTERMEDIATE_REPR_ILLEGAL_ID )
    #define SIXTRL_PROGRAM_INTERMEDIATE_REPR_ILLEGAL_ID -1
#endif /* #define SIXTRL_PROGRAM_INTERMEDIATE_REPR_ILLEGAL_ID -1 */

#if !defined( SIXTRL_PROGRAM_COMPILED_ILLEGAL_ID )
    #define SIXTRL_PROGRAM_COMPILED_ILLEGAL_ID -1
#endif /* #define SIXTRL_PROGRAM_COMPILED_ILLEGAL_ID -1 */

#if !defined( SIXTRL_KERNEL_ILLEGAL_ID )
    #define SIXTRL_KERNEL_ILLEGAL_ID -1
#endif /* #define SIXTRL_KERNEL_ILLEGAL_ID -1 */

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if !defined( SIXTRL_PROGRAM_COMP_OPTION_KIND_DEFINE )
    #define SIXTRL_PROGRAM_COMP_OPTION_KIND_DEFINE 0
#endif /* !defined( SIXTRL_PROGRAM_COMP_OPTION_KIND_DEFINE ) */

#if !defined( SIXTRL_PROGRAM_COMP_OPTION_KIND_INCLUDE )
    #define SIXTRL_PROGRAM_COMP_OPTION_KIND_INCLUDE_DIR 1
#endif /* !defined( SIXTRL_PROGRAM_COMP_OPTION_KIND_INCLUDE ) */

#if !defined( SIXTRL_PROGRAM_COMP_OPTION_KIND_UNDEF )
    #define SIXTRL_PROGRAM_COMP_OPTION_KIND_UNDEF 2
#endif /* !defined( SIXTRL_PROGRAM_COMP_OPTION_KIND_UNDEF ) */

#if !defined( SIXTRL_PROGRAM_COMP_OPTION_KIND_UNSPECIFIED )
    #define SIXTRL_PROGRAM_COMP_OPTION_KIND_UNSPECIFIED 126
#endif /* !defined( SIXTRL_PROGRAM_COMP_OPTION_KIND_UNSPECIFIED ) */

#if !defined( SIXTRL_PROGRAM_COMP_OPTION_KIND_UNSPECIFIED_LONG )
    #define SIXTRL_PROGRAM_COMP_OPTION_KIND_UNSPECIFIED_LONG 127
#endif /* !defined( SIXTRL_PROGRAM_COMP_OPTION_KIND_UNSPECIFIED_LONG ) */

#if !defined( SIXTRL_PROGRAM_COMP_OPTION_KIND_ILLEGAL )
    #define SIXTRL_PROGRAM_COMP_OPTION_KIND_ILLEGAL 255
#endif /* !defined( SIXTRL_PROGRAM_COMP_OPTION_KIND_ILLEGAL ) */

#if !defined( _GPUCODE )
#if defined( __cplusplus )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC_VAR const NS(program_code_id_t) NS(PROGRAM_CODE_ILLEGAL_ID) =
    ( NS(program_code_id_t) )SIXTRL_PROGRAM_CODE_ILLEGAL_ID;

SIXTRL_STATIC_VAR const NS(program_ir_id_t)
    NS(PROGRAM_INTERMEDIATE_REPR_ILLEGAL_ID) = ( NS(program_ir_id_t)
        )SIXTRL_PROGRAM_INTERMEDIATE_REPR_ILLEGAL_ID;

SIXTRL_STATIC_VAR const NS(program_compiled_id_t)
    NS(PROGRAM_COMPILED_ILLEGAL_ID) = ( NS(program_compiled_id_t)
        )SIXTRL_PROGRAM_COMPILED_ILLEGAL_ID;

SIXTRL_STATIC_VAR const NS(kernel_id_t) NS(KERNEL_ILLEGAL_ID) =
    ( NS(kernel_id_t) )SIXTRL_KERNEL_ILLEGAL_ID;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC_VAR const NS(program_compile_option_kind_t)
    NS(PROGRAM_COMP_OPTION_KIND_DEFINE) = ( NS(program_compile_option_kind_t)
        )SIXTRL_PROGRAM_COMP_OPTION_KIND_DEFINE;

SIXTRL_STATIC_VAR const NS(program_compile_option_kind_t)
    NS(PROGRAM_COMP_OPTION_KIND_INCLUDE_DIR) = ( NS(program_compile_option_kind_t)
        )SIXTRL_PROGRAM_COMP_OPTION_KIND_INCLUDE_DIR;

SIXTRL_STATIC_VAR const NS(program_compile_option_kind_t)
    NS(PROGRAM_COMP_OPTION_KIND_UNDEF) = ( NS(program_compile_option_kind_t)
        )SIXTRL_PROGRAM_COMP_OPTION_KIND_UNDEF;

SIXTRL_STATIC_VAR const NS(program_compile_option_kind_t)
    NS(PROGRAM_COMP_OPTION_KIND_UNSPECIFIED) = (
        NS(program_compile_option_kind_t)
            )SIXTRL_PROGRAM_COMP_OPTION_KIND_UNSPECIFIED;

SIXTRL_STATIC_VAR const NS(program_compile_option_kind_t)
    NS(PROGRAM_COMP_OPTION_KIND_UNSPECIFIED_LONG) = (
        NS(program_compile_option_kind_t)
            )SIXTRL_PROGRAM_COMP_OPTION_KIND_UNSPECIFIED_LONG;

SIXTRL_STATIC_VAR const NS(program_compile_option_kind_t)
    NS(PROGRAM_COMP_OPTION_KIND_ILLEGAL) = ( NS(program_compile_option_kind_t)
        )SIXTRL_PROGRAM_COMP_OPTION_KIND_ILLEGAL;

#if defined( __cplusplus )
}
#endif /* C++ */
#endif /* Host */

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    typedef ::NS(program_code_id_t)             program_code_id_t;
    typedef ::NS(program_ir_id_t)               program_ir_id_t;
    typedef ::NS(program_compile_option_kind_t) program_compile_option_kind_t;
    typedef ::NS(program_compiled_id_t)         program_compiled_id_t;
    typedef ::NS(kernel_id_t)                   kernel_id_t;

    static constexpr program_code_id_t PROGRAM_CODE_ILLEGAL_ID = static_cast<
        program_code_id_t >( SIXTRL_PROGRAM_CODE_ILLEGAL_ID );

    static constexpr program_ir_id_t PROGRAM_INTERMEDIATE_REPR_ILLEGAL_ID =
        static_cast< program_ir_id_t >(
            SIXTRL_PROGRAM_INTERMEDIATE_REPR_ILLEGAL_ID );

    static constexpr program_compiled_id_t PROGRAM_COMPILED_ILLEGAL_ID =
        static_cast< program_compiled_id_t >(
            SIXTRL_PROGRAM_COMPILED_ILLEGAL_ID );

    static constexpr kernel_id_t KERNEL_ILLEGAL_ID = static_cast<
        kernel_id_t >( SIXTRL_KERNEL_ILLEGAL_ID );

    /* --------------------------------------------------------------------- */

    static constexpr program_compile_option_kind_t
    PROGRAM_COMP_OPTION_KIND_DEFINE = static_cast<
        program_compile_option_kind_t >(
            SIXTRL_PROGRAM_COMP_OPTION_KIND_DEFINE );

    static constexpr program_compile_option_kind_t
    PROGRAM_COMP_OPTION_KIND_INCLUDE_DIR = static_cast<
        program_compile_option_kind_t >(
            SIXTRL_PROGRAM_COMP_OPTION_KIND_INCLUDE_DIR );

    static constexpr program_compile_option_kind_t
    PROGRAM_COMP_OPTION_KIND_UNDEF = static_cast<
        program_compile_option_kind_t >(
            SIXTRL_PROGRAM_COMP_OPTION_KIND_UNDEF );

    static constexpr program_compile_option_kind_t
    PROGRAM_COMP_OPTION_KIND_UNSPECIFIED = static_cast<
        program_compile_option_kind_t >(
            SIXTRL_PROGRAM_COMP_OPTION_KIND_UNSPECIFIED );

    static constexpr program_compile_option_kind_t
    PROGRAM_COMP_OPTION_KIND_UNSPECIFIED_LONG = static_cast<
        program_compile_option_kind_t >(
            SIXTRL_PROGRAM_COMP_OPTION_KIND_UNSPECIFIED_LONG );

    static constexpr program_compile_option_kind_t
    PROGRAM_COMP_OPTION_KIND_ILLEGAL = static_cast<
        program_compile_option_kind_t >(
            SIXTRL_PROGRAM_COMP_OPTION_KIND_ILLEGAL );

} /* ns: SIXTRL_CXX_NAMESPACE */
#endif /* C++ */
#endif /* SIXTRACKLIB_BASE_PROGRAM_DEFINITIONS_H__ */
