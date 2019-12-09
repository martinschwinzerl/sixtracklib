#ifndef SIXTRACKL_COMMON_CONTROL_KERNEL_VARIANT_CXX_HPP__
#define SIXTRACKL_COMMON_CONTROL_KERNEL_VARIANT_CXX_HPP__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <algorithm>
    #include <cstddef>
    #include <cstdint>
    #include <cstdlib>
    #include <cmath>
    #include <sstream>
    #include <string>
    #include <stdexcept>
    #include <utility>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )

namespace SIXTRL_CXX_NAMESPACE
{
    template< SIXTRL_CXX_NAMESPACE::arch_size_t N >
    struct KernelVariantFlags
    {
        using flag_field_t = uint64_t;
        using size_type = SIXTRL_CXX_NAMESPACE::arch_size_t;

        flag_field_t flags[ N ] SIXTRL_ALIGN( 8 );

        friend void swap(
            KernelVariantFlags< N > const& SIXTRL_RESTRICT_REF lhs,
            KernelVariantFlags< N > const& SIXTRL_RESTRICT_REF rhs
        ) SIXTRL_NOEXCEPT
        {
            if( &lhs != &rhs )
            {
                flag_field_t TEMP[ N ];
                std::copy( &lhs.flags[ 0 ], &lhs.flags[ N ], &TEMP[ 0 ] );
                std::copy( &rhs.flags[ 0 ], &rhs.flags[ N ], &lhs.flags[ 0 ] );
                std::copy( &TEMP[ 0 ], &TEMP[ N ], &rhs.flags[ 0 ] );
            }
        }

        /* TODO: Use spaceship operator once c++20 can be relied upon */
        friend bool operator<(
            KernelVariantFlags< N > const& SIXTRL_RESTRICT_REF lhs,
            KernelVariantFlags< N > const& SIXTRL_RESTRICT_REF rhs
        ) SIXTRL_NOEXCEPT
        {
            return lhs.compare_less( rhs.flags, N );
        }

        friend bool operator<=(
            KernelVariantFlags< N > const& SIXTRL_RESTRICT_REF lhs,
            KernelVariantFlags< N > const& SIXTRL_RESTRICT_REF rhs
        ) SIXTRL_NOEXCEPT
        {
            return !rhs.compare_less( lhs.flags, N );
        }

        friend bool operator>(
            KernelVariantFlags< N > const& SIXTRL_RESTRICT_REF lhs,
            KernelVariantFlags< N > const& SIXTRL_RESTRICT_REF rhs
        ) SIXTRL_NOEXCEPT
        {
            return rhs.compare_less( lhs.flags, N );
        }

        friend bool operator>=(
            KernelVariantFlags< N > const& SIXTRL_RESTRICT_REF lhs,
            KernelVariantFlags< N > const& SIXTRL_RESTRICT_REF rhs
        ) SIXTRL_NOEXCEPT
        {
            return !lhs.compare_less( rhs.flags, N );
        }

        friend bool operator==(
            KernelVariantFlags< N > const& SIXTRL_RESTRICT_REF lhs,
            KernelVariantFlags< N > const& SIXTRL_RESTRICT_REF rhs
        ) SIXTRL_NOEXCEPT
        {
            return lhs.compare_equal( rhs.flags, N );
        }

        friend bool operator!=(
            KernelVariantFlags< N > const& SIXTRL_RESTRICT_REF lhs,
            KernelVariantFlags< N > const& SIXTRL_RESTRICT_REF rhs
        ) SIXTRL_NOEXCEPT
        {
            return !lhs.compare_equal( rhs.flags, N );
        }

        flag_field_t operator[]( size_type const idx ) const SIXTRL_NOEXCEPT;
        flag_field_t& operator[]( size_type const idx );

        flag_field_t const* begin() const SIXTRL_NOEXCEPT;
        flag_field_t const* end()   const SIXTRL_NOEXCEPT;

        flag_field_t* begin() SIXTRL_NOEXCEPT;
        flag_field_t* end()   SIXTRL_NOEXCEPT;

        bool compare_less( flag_field_t[] const SIXTRL_RESTRICT rhs_flags,
            size_type const num_flag_fields ) const SIXTRL_NOEXCEPT;

        bool compare_equal( flag_field_t[] const SIXTRL_RESTRICT rhs_flags,
            size_type const num_flag_fields ) const SIXTRL_NOEXCEPT;

        void clear() SIXTRL_NOEXCEPT;
    };

    template< SIXTRL_CXX_NAMESPACE::arch_size_t N >
    typename KernelVariantFlags< N >::flag_field_t
    KernelVariantFlags< N >::operator[](
        typename KernelVariantFlags< N >::size_type const idx
    ) const SIXTRL_NOEXCEPT
    {
        static_assert( N > typename KernelVariantFlags< N >::size_type{ 0 },
                      "Not defined for variant flags with N == 0" );

        return ( idx < N ) ? this->flags[ idx ]
            : typename KernelVariantFlags< N >::flag_field_t{ 0 };

    }

    template< SIXTRL_CXX_NAMESPACE::arch_size_t N >
    typename KernelVariantFlags< N >::flag_field_t&
    KernelVariantFlags< N >::operator[](
        typename KernelVariantFlags< N >::size_type const idx )
    {
        if( idx >= N )
        {
            std::ostringstream a2str;
            a2str << "idx >= " << N << " -> out of range";
            throw std::out_of_range( a2str.str() );
        }

        return this->flags[ idx ];
    }

    template< SIXTRL_CXX_NAMESPACE::arch_size_t N >
    typename KernelVariantFlags< N >::flag_field_t const*
    KernelVariantFlags< N >::begin() const SIXTRL_NOEXCEPT
    {
        return ( N > typename KernelVariantFlags< N >::size_type{ 0 } )
            ? &this->flags[ 0 ] : nullptr;
    }

    template< SIXTRL_CXX_NAMESPACE::arch_size_t N >
    typename KernelVariantFlags< N >::flag_field_t const*
    KernelVariantFlags< N >::end() const SIXTRL_NOEXCEPT
    {
        return ( N > typename KernelVariantFlags< N >::size_type{ 0 } )
            ? &this->flags[ N ] : nullptr;
    }

    template< SIXTRL_CXX_NAMESPACE::arch_size_t N >
    typename KernelVariantFlags< N >::flag_field_t*
    KernelVariantFlags< N >::begin() SIXTRL_NOEXCEPT
    {
        return const_cast< typename KernelVariantFlags< N >::size_type* >(
            static_cast< KernelVariantFlags< N > const& >( *this ).begin() );
    }

    template< SIXTRL_CXX_NAMESPACE::arch_size_t N >
    typename KernelVariantFlags< N >::flag_field_t*
    KernelVariantFlags< N >::end() SIXTRL_NOEXCEPT
    {
        return const_cast< typename KernelVariantFlags< N >::size_type* >(
            static_cast< KernelVariantFlags< N > const& >( *this ).end() );
    }

    template< SIXTRL_CXX_NAMESPACE::arch_size_t N >
    bool KernelVariantFlags< N >::compare_less(
        typename KernelVariantFlags< N >::flag_field_t[] const rhs_flags,
        typename KernelVariantFlags< N >::size_type const num_flag_fields
    ) const SIXTRL_NOEXCEPT
    {
        static_assert( N > typename KernelVariantFlags< N >::size_type{ 0 },
                      "Not defined for variant flags with N == 0" );

        bool is_smaller = N < num_flag_fields;

        if( ( !is_smaller ) && ( N == num_flag_fields ) )
        {
            is_smaller = ( 0 > std::memcmp( &this->flags[ 0 ], &rhs_flags[ 0 ],
                N * sizeof( typename KernelVariantFlags< N >::flag_field_t ) ) );
        }

        return is_smaller;
    }

    template< SIXTRL_CXX_NAMESPACE::arch_size_t N >
    bool KernelVariantFlags< N >::compare_equal(
        typename KernelVariantFlags< N >::flag_field_t[] const rhs_flags,
        typename KernelVariantFlags< N >::size_type const num_flag_fields
    ) const SIXTRL_NOEXCEPT
    {
        static_assert( N > typename KernelVariantFlags< N >::size_type{ 0 },
                      "Not defined for variant flags with N == 0" );

        return ( ( N == num_flag_fields ) &&
                 ( std::equal( &this->flags[ 0 ], &this->flags[ N ],
                               &rhs_flags[ 0 ] ) ) );
    }

    template< SIXTRL_CXX_NAMESPACE::arch_size_t N >
    void KernelVariantFlags< N >::clear() SIXTRL_NOEXCEPT
    {
        static_assert( N > typename KernelVariantFlags< N >::size_type{ 0 },
                      "Not defined for variant flags with N == 0" );

        std::fill( &this->flags[ 0 ], &this->flags[ N ],
            typename KernelVariantFlags< N >::flag_field_t{ 0 } );
    }
}

#endif /* !defined( __cplusplus ) && !defined( _GPUCODE ) */



#endif /* SIXTRACKL_COMMON_CONTROL_KERNEL_VARIANT_CXX_HPP__ */
