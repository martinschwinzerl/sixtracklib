
#ifndef SIXTRL_BASE_EXPORT_API_H
#define SIXTRL_BASE_EXPORT_API_H

#ifdef SIXTRL_BASE_IS_STATIC_BUILD
#  define SIXTRL_BASE_EXPORT_API
#  define SIXTRL_BASE_PRIVATE_API
#else
#  ifndef SIXTRL_BASE_EXPORT_API
#    ifdef sixtrack_base_EXPORTS
        /* We are building this library */
#      define SIXTRL_BASE_EXPORT_API __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define SIXTRL_BASE_EXPORT_API __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef SIXTRL_BASE_PRIVATE_API
#    define SIXTRL_BASE_PRIVATE_API __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef SIXTRL_BASE_DEPRECATED_API
#  define SIXTRL_BASE_DEPRECATED_API __attribute__ ((__deprecated__))
#endif

#ifndef SIXTRL_BASE_DEPRECATED_API_EXPORT
#  define SIXTRL_BASE_DEPRECATED_API_EXPORT SIXTRL_BASE_EXPORT_API SIXTRL_BASE_DEPRECATED_API
#endif

#ifndef SIXTRL_BASE_DEPRECATED_API_NO_EXPORT
#  define SIXTRL_BASE_DEPRECATED_API_NO_EXPORT SIXTRL_BASE_PRIVATE_API SIXTRL_BASE_DEPRECATED_API
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef SIXTRACK_BASE_NO_DEPRECATED
#    define SIXTRACK_BASE_NO_DEPRECATED
#  endif
#endif

#endif /* SIXTRL_BASE_EXPORT_API_H */
