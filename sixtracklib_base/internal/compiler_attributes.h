#ifndef SIXTRACKLIB_BASE_INTERNAL_COMPILER_ATTRIBUTES_H__
#define SIXTRACKLIB_BASE_INTERNAL_COMPILER_ATTRIBUTES_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib_base/definitions.h"
#endif /* C++ */

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* SIXTRL_UNUSED( arg ) */

#if !defined SIXTRL_UNUSED
    #if defined( __cplusplus )
        #define SIXTRL_UNUSED( arg ) /* can be omitted -> nothing to do here! */
    #elif ( ( defined( __GNUC__ ) && ( __GNUC__ >= 3 ) ) ) || \
          ( defined( __clang__ ) )
        #define SIXTRL_UNUSED( arg ) arg __attribute__((unused))
    #else
        #define SIXTRL_UNUSED( arg ) arg
    #endif /* C++ / compiler */
#endif /* !defined( SIXTRL_UNUSED ) */

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* SIXTRL_DLIB_CONSTRUCTOR */

#if !defined SIXTRL_DLIB_CONSTRUCTOR
    #if ( ( defined( __STDC_VERSION__ ) && __STDC_VERSION__ >= 199901L ) || \
            defined( __cplusplus ) )

        #if defined( __GNUC__ ) && \
            ( ( __GNUC__ > 4 ) || \
              ( ( __GNUC__ == 4 ) && ( __GNUC_MINOR__ >= 7 ) ) )

            #define SIXTRL_DLIB_CONSTRUCTOR __attribute__((constructor))
            #if !defined( SIXTRL_DLIB_CONSTRUCTOR_ENABLED )
                #define SIXTRL_DLIB_CONSTRUCTOR_ENABLED 1
            #endif /* !defined( SIXTRL_DLIB_CONSTRUCTOR_ENABLED ) */
        #elif defined __clang__
            #define SIXTRL_DLIB_CONSTRUCTOR __attribute__((constructor))
            #if !defined( SIXTRL_DLIB_CONSTRUCTOR_ENABLED )
                #define SIXTRL_DLIB_CONSTRUCTOR_ENABLED 1
            #endif /* !defined( SIXTRL_DLIB_CONSTRUCTOR_ENABLED ) */
        #endif /* Specific Compilers */
    #endif /* C99, C++ */

    #if !defined( SIXTRL_DLIB_CONSTRUCTOR )
        #define SIXTRL_DLIB_CONSTRUCTOR
    #endif /* !defined( SIXTRL_DLIB_CONSTRUCTOR ) */

    #if !defined( SIXTRL_DLIB_CONSTRUCTOR_ENABLED )
        #define SIXTRL_DLIB_CONSTRUCTOR_ENABLED 0
    #endif /* !defined( SIXTRL_DLIB_CONSTRUCTOR_ENABLED ) */
#endif /* !defined( SIXTRL_DLIB_CONSTRUCTOR ) */

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* SIXTRL_DLIB_CONSTRUCTOR_PRIORITY( priority ) */

#if !defined SIXTRL_DLIB_CONSTRUCTOR_PRIORITY
    #if ( ( defined( __STDC_VERSION__ ) && __STDC_VERSION__ >= 199901L ) || \
            defined( __cplusplus ) )

        #if defined( __GNUC__ ) && \
            ( ( __GNUC__ > 4 ) || \
              ( ( __GNUC__ == 4 ) && ( __GNUC_MINOR__ >= 7 ) ) )
            #define SIXTRL_DLIB_CONSTRUCTOR_PRIORITY( priority ) __attribute__((constructor(priority)))
            #if !defined( SIXTRL_DLIB_CONSTRUCTOR_PRIORITY_ENABLED )
                #define SIXTRL_DLIB_CONSTRUCTOR_PRIORITY_ENABLED 1
            #endif /* !defined( SIXTRL_DLIB_CONSTRUCTOR_PRIORITY_ENABLED ) */
        #elif defined __clang__
            #define SIXTRL_DLIB_CONSTRUCTOR_PRIORITY( priority ) __attribute__((constructor(priority)))
            #if !defined( SIXTRL_DLIB_CONSTRUCTOR_PRIORITY_ENABLED )
                #define SIXTRL_DLIB_CONSTRUCTOR_PRIORITY_ENABLED 1
            #endif /* !defined( SIXTRL_DLIB_CONSTRUCTOR_PRIORITY_ENABLED ) */
        #endif /* Specific Compilers */
    #endif /* C99, C++ */

    #if !defined( SIXTRL_DLIB_CONSTRUCTOR_PRIORITY )
        #define SIXTRL_DLIB_CONSTRUCTOR_PRIORITY( priority )
    #endif /* !defined( SIXTRL_DLIB_CONSTRUCTOR_PRIORITY ) */

    #if !defined( SIXTRL_DLIB_CONSTRUCTOR_PRIORITY_ENABLED )
            #define SIXTRL_DLIB_CONSTRUCTOR_PRIORITY_ENABLED 0
        #endif /* !defined( SIXTRL_DLIB_CONSTRUCTOR_PRIORITY_ENABLED ) */
#endif /* !defined( SIXTRL_DLIB_CONSTRUCTOR_PRIORITY ) */

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* SIXTRL_DLIB_DESTRUCTOR */

#if !defined SIXTRL_DLIB_DESTRUCTOR
    #if ( ( defined( __STDC_VERSION__ ) && __STDC_VERSION__ >= 199901L ) || \
            defined( __cplusplus ) )

        #if defined( __GNUC__ ) && \
            ( ( __GNUC__ > 4 ) || \
              ( ( __GNUC__ == 4 ) && ( __GNUC_MINOR__ >= 7 ) ) )
            #define SIXTRL_DLIB_DESTRUCTOR __attribute__((destructor))
            #if !defined( SIXTRL_DLIB_DESTRUCTOR_ENABLED )
                #define SIXTRL_DLIB_DESTRUCTOR_ENABLED 1
            #endif /* !defined( SIXTRL_DLIB_DESTRUCTOR_ENABLED ) */
        #elif defined __clang__
            #define SIXTRL_DLIB_DESTRUCTOR __attribute__((destructor))
            #if !defined( SIXTRL_DLIB_DESTRUCTOR_ENABLED )
                #define SIXTRL_DLIB_DESTRUCTOR_ENABLED 1
            #endif /* !defined( SIXTRL_DLIB_DESTRUCTOR_ENABLED ) */
        #endif /* Specific Compilers */
    #endif /* C99, C++ */

    #if !defined( SIXTRL_DLIB_DESTRUCTOR )
        #define SIXTRL_DLIB_DESTRUCTOR( priority )
    #endif /* !defined( SIXTRL_DLIB_DESTRUCTOR ) */

    #if !defined( SIXTRL_DLIB_DESTRUCTOR_ENABLED )
                #define SIXTRL_DLIB_DESTRUCTOR_ENABLED 0
            #endif /* !defined( SIXTRL_DLIB_DESTRUCTOR_ENABLED ) */
#endif /* !defined( SIXTRL_DLIB_DESTRUCTOR_PRIORITY ) */

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* SIXTRL_DLIB_DESTRUCTOR_PRIORITY( priority ) */

#if !defined( SIXTRL_DLIB_DESTRUCTOR_PRIORITY )
    #if ( ( defined( __STDC_VERSION__ ) && __STDC_VERSION__ >= 199901L ) || \
            defined( __cplusplus ) )

        #if defined( __GNUC__ ) && \
            ( ( __GNUC__ > 4 ) || \
              ( ( __GNUC__ == 4 ) && ( __GNUC_MINOR__ >= 7 ) ) )
            #define SIXTRL_DLIB_DESTRUCTOR_PRIORITY( priority ) __attribute__((destructor(priority)))
            #if !defined( SIXTRL_DLIB_DESTRUCTOR_PRIORITY_ENABLED )
                #define SIXTRL_DLIB_DESTRUCTOR_PRIORITY_ENABLED 1
            #endif /* !defined( SIXTRL_DLIB_DESTRUCTOR_PRIORITY_ENABLED ) */
        #elif defined __clang__
            #define SIXTRL_DLIB_DESTRUCTOR_PRIORITY( priority ) __attribute__((destructor(priority)))
            #if !defined( SIXTRL_DLIB_DESTRUCTOR_PRIORITY_ENABLED )
                #define SIXTRL_DLIB_DESTRUCTOR_PRIORITY_ENABLED 1
            #endif /* !defined( SIXTRL_DLIB_DESTRUCTOR_PRIORITY_ENABLED ) */
        #endif /* Specific Compilers */
    #endif /* C99, C++ */

    #if !defined( SIXTRL_DLIB_DESTRUCTOR_PRIORITY )
        #define SIXTRL_DLIB_DESTRUCTOR_PRIORITY( priority )
    #endif /* !defined( SIXTRL_DLIB_DESTRUCTOR_PRIORITY ) */

    #if !defined( SIXTRL_DLIB_DESTRUCTOR_PRIORITY_ENABLED )
        #define SIXTRL_DLIB_DESTRUCTOR_PRIORITY_ENABLED 0
    #endif /* !defined( SIXTRL_DLIB_DESTRUCTOR_PRIORITY_ENABLED ) */
#endif /* !defined( SIXTRL_DLIB_DESTRUCTOR_PRIORITY ) */

/* ************************************************************************* */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* C++, Host */

#if !defined( _GPUCODE )

#if defined( SIXTRL_DLIB_CONSTRUCTOR_ENABLED ) && \
    SIXTRL_DLIB_CONSTRUCTOR_ENABLED == 1
SIXTRL_STATIC_VAR bool SIXTRL_CONSTEXPR_OR_CONST
    NS(DLIB_CONSTRUCTOR_ENABLED) = true;
#else  /* !defined( SIXTRL_DLIB_CONSTRUCTOR_ENABLED ) && 0 */
SIXTRL_STATIC_VAR bool SIXTRL_CONSTEXPR_OR_CONST
    NS(DLIB_CONSTRUCTOR_ENABLED) = false;
#endif /*  defined( SIXTRL_DLIB_CONSTRUCTOR_ENABLED ) && 1 */

#if defined( SIXTRL_DLIB_CONSTRUCTOR_PRIORITY_ENABLED ) && \
    SIXTRL_DLIB_CONSTRUCTOR_PRIORITY_ENABLED == 1
SIXTRL_STATIC_VAR bool SIXTRL_CONSTEXPR_OR_CONST
    NS(DLIB_CONSTRUCTOR_PRIORITY_ENABLED) = true;
#else  /* !defined( SIXTRL_DLIB_CONSTRUCTOR_ENABLED ) && 0 */
SIXTRL_STATIC_VAR bool SIXTRL_CONSTEXPR_OR_CONST
    NS(DLIB_CONSTRUCTOR_PRIORITY_ENABLED) = false;
#endif /*  defined( SIXTRL_DLIB_CONSTRUCTOR_ENABLED ) && 1 */

#if defined( SIXTRL_DLIB_DESTRUCTOR_ENABLED ) && \
    SIXTRL_DLIB_DESTRUCTOR_ENABLED == 1
SIXTRL_STATIC_VAR bool SIXTRL_CONSTEXPR_OR_CONST
    NS(DLIB_DESTRUCTOR_ENABLED) = true;
#else  /* !defined( SIXTRL_DLIB_DESTRUCTOR_ENABLED ) && 0 */
SIXTRL_STATIC_VAR bool SIXTRL_CONSTEXPR_OR_CONST
    NS(DLIB_DESTRUCTOR_ENABLED) = false;
#endif /*  defined( SIXTRL_DLIB_DESTRUCTOR_ENABLED ) && 1 */

#if defined( SIXTRL_DLIB_DESTRUCTOR_PRIORITY_ENABLED ) && \
    SIXTRL_DLIB_DESTRUCTOR_PRIORITY_ENABLED == 1
SIXTRL_STATIC_VAR bool SIXTRL_CONSTEXPR_OR_CONST
    NS(DLIB_DESTRUCTOR_PRIORITY_ENABLED) = true;
#else  /* !defined( SIXTRL_DLIB_DESTRUCTOR_ENABLED ) && 0 */
SIXTRL_STATIC_VAR bool SIXTRL_CONSTEXPR_OR_CONST
    NS(DLIB_DESTRUCTOR_PRIORITY_ENABLED) = false;
#endif /*  defined( SIXTRL_DLIB_DESTRUCTOR_ENABLED ) && 1 */

#endif /* Host */

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
namespace SIXTRL_CXX_NAMESPACE
{
    #if defined( SIXTRL_DLIB_CONSTRUCTOR_ENABLED ) && \
        SIXTRL_DLIB_CONSTRUCTOR_ENABLED == 1
    static constexpr bool DLIB_CONSTRUCTOR_ENABLED = true;
    #else  /* !defined( SIXTRL_DLIB_CONSTRUCTOR_ENABLED ) && 0 */
    static constexpr bool DLIB_CONSTRUCTOR_ENABLED = false;
    #endif /*  defined( SIXTRL_DLIB_CONSTRUCTOR_ENABLED ) && 1 */

    #if defined( SIXTRL_DLIB_CONSTRUCTOR_PRIORITY_ENABLED ) && \
        SIXTRL_DLIB_CONSTRUCTOR_PRIORITY_ENABLED == 1
    static constexpr bool DLIB_CONSTRUCTOR_PRIORITY_ENABLED = true;
    #else  /* !defined( SIXTRL_DLIB_CONSTRUCTOR_ENABLED ) && 0 */
    static constexpr bool DLIB_CONSTRUCTOR_PRIORITY_ENABLED = false;
    #endif /*  defined( SIXTRL_DLIB_CONSTRUCTOR_ENABLED ) && 1 */

    #if defined( SIXTRL_DLIB_DESTRUCTOR_ENABLED ) && \
        SIXTRL_DLIB_DESTRUCTOR_ENABLED == 1
    static constexpr bool DLIB_DESTRUCTOR_ENABLED = true;
    #else  /* !defined( SIXTRL_DLIB_DESTRUCTOR_ENABLED ) && 0 */
    static constexpr bool DLIB_DESTRUCTOR_ENABLED = false;
    #endif /*  defined( SIXTRL_DLIB_DESTRUCTOR_ENABLED ) && 1 */

    #if defined( SIXTRL_DLIB_DESTRUCTOR_PRIORITY_ENABLED ) && \
        SIXTRL_DLIB_DESTRUCTOR_PRIORITY_ENABLED == 1
    static constexpr bool DLIB_DESTRUCTOR_PRIORITY_ENABLED = true;
    #else  /* !defined( SIXTRL_DLIB_DESTRUCTOR_ENABLED ) && 0 */
    static constexpr bool DLIB_DESTRUCTOR_PRIORITY_ENABLED = false;
    #endif /*  defined( SIXTRL_DLIB_DESTRUCTOR_ENABLED ) && 1 */
}
#endif /* C++, Host */
#endif /* SIXTRACKLIB_BASE_INTERNAL_COMPILER_ATTRIBUTES_H__ */
