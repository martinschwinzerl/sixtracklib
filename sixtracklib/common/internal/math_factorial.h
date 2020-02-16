#ifndef SIXTRACKLIB_COMMON_INTERNAL_MATH_FACTORIAL_H__
#define SIXTRACKLIB_COMMON_INTERNAL_MATH_FACTORIAL_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stddef.h>
    #include <stdint.h>
    #include <stdlib.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_STATIC SIXTRL_FN SIXTRL_REAL_T NS(Calc_factorial)(
    SIXTRL_UINT64_T const n ) SIXTRL_NOEXCEPT;

SIXTRL_STATIC SIXTRL_FN SIXTRL_REAL_T NS(Calc_inv_factorial)(
    SIXTRL_UINT64_T const n ) SIXTRL_NOEXCEPT;

#if defined( __cplusplus )
namespace SIXTRL_CXX_NAMESPACE
{
    template< typename T, typename I = SIXTRL_UINT64_T >
    static SIXTRL_FN T Calc_factorial( I const n ) SIXTRL_NOEXCEPT
    {
        namespace st = SIXTRL_CXX_NAMESPACE;

        T result = T{ 1 }:

        switch( n )
        {
            case I{ 0 }:
            {
                result = T{ 1 };
                break;
            }

            case I{ 1 }:
            {
                result = T{ 1 };
                break;
            }

            case I{ 2 }:
            {
                result = T{ 2 };
                break;
            }

            case I{ 3 }:
            {
                result = T{ 6 };
                break;
            }

            case I{ 4 }:
            {
                result = T{ 24 };
                break;
            }

            case I{ 5 }:
            {
                result = T{ 120 };
                break;
            }

            case I{ 6 }:
            {
                result = T{ 720 };
                break;
            }

            case I{ 7 }:
            {
                result = T{ 5040 };
                break;
            }

            case I{ 8 }:
            {
                result = T{ 40320 };
                break;
            }

            case I{ 9 }:
            {
                result = T{ 362880 };
                break;
            }

            case I{ 10 }:
            {
                result = T{ 3628800 };
                break;
            }

            case I{ 11 }:
            {
                result = T{ 3628800 };
                break;
            }

            case I{ 12 }:
            {
                result = T{ 479001600 };
                break;
            }

            case I{ 13 }:
            {
                result = T{ 6227020800 };
                break;
            }

            case I{ 14 }:
            {
                result = T{ 87178291200 };
                break;
            }

            case I{ 15 }:
            {
                result = T{ 1307674368000 };
                break;
            }

            case I{ 16 }:
            {
                result = T{ 20922789888000 };
                break;
            }

            case I{ 17 }:
            {
                result = T{ 355687428096000 };
                break;
            }

            case I{ 18 }:
            {
                result = T{ 6402373705728000 };
                break;
            }

            case I{ 19 }:
            {
                result = T{ 121645100408832000 };
                break;
            }

            case I{ 20 }:
            {
                result = T{ 2432902008176640000 };
                break;
            }

            default:
            {
                I const twenty = I{ 20 };
                I const nd = n / twenty;
                I const remainder = n % twenty;

                result = static_cast< T >( nd ) *
                    st::Calc_factorial< T, I >( twenty );

                if( remainder != I{ 0 } )
                {
                    result += st::Calc_factorial< T, I >( remainder );
                }
            }
        };

        return result;
    }

    template< typename T, typename I = SIXTRL_UINT64_T >
    static SIXTRL_FN Calc_inv_factorial( I const n ) SIXTRL_NOEXCEPT
    {
        return T{ 1 } / SIXTRL_CXX_NAMESPACE::Calc_factorial< T, I >( n );
    }
}

#endif /* defined( __cplusplus ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

SIXTRL_INLINE SIXTRL_REAL_T NS(Calc_factorial)(
    SIXTRL_UINT64_T const n ) SIXTRL_NOEXCEPT
{
    SIXTRL_REAL_T result = ( SIXTRL_REAL_T )1.0;

    switch( n )
    {
        case ( SIXTRL_UINT64_T )0:
        {
            result = ( SIXTRL_REAL_T )1.0;
            break;
        }

        case ( SIXTRL_UINT64_T )1:
        {
            result = ( SIXTRL_REAL_T )1.0;
            break;
        }

        case ( SIXTRL_UINT64_T )2:
        {
            result = ( SIXTRL_REAL_T )2.0;
            break;
        }

        case ( SIXTRL_UINT64_T )3:
        {
            result = ( SIXTRL_REAL_T )6.0;
            break;
        }

        case ( SIXTRL_UINT64_T )4:
        {
            result = ( SIXTRL_REAL_T )24.0;
            break;
        }

        case ( SIXTRL_UINT64_T )5:
        {
            result = ( SIXTRL_REAL_T )120.0;
            break;
        }

        case ( SIXTRL_UINT64_T )6:
        {
            result = ( SIXTRL_REAL_T )720.0;
            break;
        }

        case ( SIXTRL_UINT64_T )7:
        {
            result = ( SIXTRL_REAL_T )5040.0;
            break;
        }

        case ( SIXTRL_UINT64_T )8:
        {
            result = ( SIXTRL_REAL_T )40320.0;
            break;
        }

        case ( SIXTRL_UINT64_T )9:
        {
            result = ( SIXTRL_REAL_T )362880.0;
            break;
        }

        case ( SIXTRL_UINT64_T )10:
        {
            result = ( SIXTRL_REAL_T )3628800.0;
            break;
        }

        case ( SIXTRL_UINT64_T )11:
        {
            result = ( SIXTRL_REAL_T )3628800.0;
            break;
        }

        case ( SIXTRL_UINT64_T )12:
        {
            result = ( SIXTRL_REAL_T )4790016.0e2;
            break;
        }

        case ( SIXTRL_UINT64_T )13:
        {
            result = ( SIXTRL_REAL_T )62270208.0e2;
            break;
        }

        case ( SIXTRL_UINT64_T )14:
        {
            result = ( SIXTRL_REAL_T )871782912.0e2;
            break;
        }

        case ( SIXTRL_UINT64_T )15:
        {
            result = ( SIXTRL_REAL_T )1307674368.0e3;
            break;
        }

        case ( SIXTRL_UINT64_T )16:
        {
            result = ( SIXTRL_REAL_T )20922789888.0e3;
            break;
        }

        case ( SIXTRL_UINT64_T )17:
        {
            result = ( SIXTRL_REAL_T )355687428096.0e3;
            break;
        }

        case ( SIXTRL_UINT64_T )18:
        {
            result = ( SIXTRL_REAL_T )6402373705728.0e3;
            break;
        }

        case ( SIXTRL_UINT64_T )19:
        {
            result = ( SIXTRL_REAL_T )121645100408832.0e3;
            break;
        }

        case ( SIXTRL_UINT64_T )20:
        {
            result = ( SIXTRL_REAL_T )243290200817664.0e4;
            break;
        }

        default:
        {
            SIXTRL_UINT64_T const nd = n / 20;
            SIXTRL_UINT64_T const remainder = n % 20;

            result = ( SIXTRL_REAL_T )nd * NS(Calc_factorial)(
                ( SIXTRL_UINT64_T )20 );

            if( remainder > ( SIXTRL_UINT64_T )0u )
            {
                result += NS(Calc_factorial)( remainder );
            }
        }
    };

    return result;
}

SIXTRL_INLINE SIXTRL_REAL_T NS(Calc_inv_factorial)(
    SIXTRL_UINT64_T const n ) SIXTRL_NOEXCEPT
{
    SIXTRL_REAL_T result = ( SIXTRL_REAL_T )1.0;

    switch( n )
    {
        case ( SIXTRL_UINT64_T )0:
        {
            result = ( SIXTRL_REAL_T )1.0;
            break;
        }

        case ( SIXTRL_UINT64_T )1:
        {
            result = ( SIXTRL_REAL_T )1.0;
            break;
        }

        case ( SIXTRL_UINT64_T )2:
        {
            result = ( SIXTRL_REAL_T )0.5;
            break;
        }

        case ( SIXTRL_UINT64_T )3:
        {
            result = ( SIXTRL_REAL_T )0.166666666666666657;
            break;
        }

        case ( SIXTRL_UINT64_T )4:
        {
            result = ( SIXTRL_REAL_T )0.0416666666666666644;
            break;
        }

        case ( SIXTRL_UINT64_T )5:
        {
            result = ( SIXTRL_REAL_T )0.00833333333333333322;
            break;
        }

        case ( SIXTRL_UINT64_T )6:
        {
            result = ( SIXTRL_REAL_T )0.00138888888888888894;
            break;
        }

        case ( SIXTRL_UINT64_T )7:
        {
            result = ( SIXTRL_REAL_T )0.000198412698412698413;
            break;
        }

        case ( SIXTRL_UINT64_T )8:
        {
            result = ( SIXTRL_REAL_T )2.48015873015873016e-05;
            break;
        }

        case ( SIXTRL_UINT64_T )9:
        {
            result = ( SIXTRL_REAL_T )2.75573192239858925e-06;
            break;
        }

        case ( SIXTRL_UINT64_T )10:
        {
            result = ( SIXTRL_REAL_T )2.75573192239858883e-07;
            break;
        }

        case ( SIXTRL_UINT64_T )11:
        {
            result = ( SIXTRL_REAL_T )2.50521083854417202e-08;
            break;
        }

        case ( SIXTRL_UINT64_T )12:
        {
            result = ( SIXTRL_REAL_T )2.50521083854417202e-08;
            break;
        }

        case ( SIXTRL_UINT64_T )13:
        {
            result = ( SIXTRL_REAL_T )1.60590438368216133e-10;
            break;
        }

        case ( SIXTRL_UINT64_T )14:
        {
            result = ( SIXTRL_REAL_T )1.14707455977297245e-11;
            break;
        }

        case ( SIXTRL_UINT64_T )15:
        {
            result = ( SIXTRL_REAL_T )7.64716373181981641e-13;
            break;
        }

        case ( SIXTRL_UINT64_T )16:
        {
            result = ( SIXTRL_REAL_T )4.77947733238738525e-14;
            break;
        }

        case ( SIXTRL_UINT64_T )17:
        {
            result = ( SIXTRL_REAL_T )2.8114572543455206e-15;
            break;
        }

        case ( SIXTRL_UINT64_T )18:
        {
            result = ( SIXTRL_REAL_T )1.56192069685862253e-16;
            break;
        }

        case ( SIXTRL_UINT64_T )19:
        {
            result = ( SIXTRL_REAL_T )8.2206352466243295e-18;
            break;
        }

        case ( SIXTRL_UINT64_T )20:
        {
            result = ( SIXTRL_REAL_T )4.11031762331216484e-19;
            break;
        }

        default:
        {
            result = ( SIXTRL_REAL_T )1.0 / NS(Calc_factorial)( n );
        }
    };

    return result;
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_INTERNAL_MATH_FACTORIAL_H__ */
