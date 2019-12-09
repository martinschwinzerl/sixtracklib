#ifndef SIXTRACKL_COMMON_BE_LIMIT_BE_LIMIT_ZETA_CXX_HPP__
#define SIXTRACKL_COMMON_BE_LIMIT_BE_LIMIT_ZETA_CXX_HPP__

#if defined( __cplusplus )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cstddef>
    #include <cstdint>
    #include <cstdlib>
    #include <type_traits>
    #include <utility>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/be_limit/be_limit_zeta.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/particles/definitions.h"
    #include "sixtracklib/common/buffer.hpp"
    #include "sixtracklib/common/buffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace SIXTRL_CXX_NAMESPACE
{
    template< typename T >
    struct TLimitZeta

    struct LimitZeta : public ::NS(LimitZeta)
    {
        typedef SIXTRL_CXX_NAMESPACE::Buffer buffer_t;
        typedef buffer_t::c_api_t c_buffer_t;
        typedef buffer_t::size_type size_type;
        typedef buffer_t::type_id_t type_id_t;
        typedef ::NS(LimitZeta) c_api_t;
        typedef ::NS(particle_real_t) real_t;

        SIXTRL_FN LimitZeta() SIXTRL_NOEXCEPT;

        SIXTRL_FN LimitZeta(
            real_t const min_zeta, real_t const max_zeta ) SIXTRL_NOEXCEPT;

        SIXTRL_FN LimitZeta( LimitZeta const& other ) = default;
        SIXTRL_FN LimitZeta& operator=( LimitZeta const& rhs ) = default;

        SIXTRL_FN LimitZeta( LimitZeta&& other ) = default;
        SIXTRL_FN LimitZeta& operator=( LimitZeta&& rhs ) = default;

        SIXTRL_FN ~LimitZeta() = default;

        /* ----------------------------------------------------------------- */

        #if !defined( _GPUCODE )

        SIXTRL_STATIC SIXTRL_FN
        SIXTRL_BE_ARGPTR_DEC LimitZeta const* FromBuffer(
            SIXTRL_BUFFER_ARGPTR_DEC Buffer const& SIXTRL_RESTRICT_REF buffer,
            size_type const buffer_index ) SIXTRL_NOEXCEPT;

        SIXTRL_STATIC SIXTRL_FN
        SIXTRL_BE_ARGPTR_DEC LimitZeta const* FromBuffer(
            SIXTRL_BUFFER_ARGPTR_DEC const ::NS(Buffer) *const
                SIXTRL_RESTRICT buffer,
            size_type const buffer_index ) SIXTRL_NOEXCEPT;

        SIXTRL_STATIC SIXTRL_FN
        SIXTRL_BE_ARGPTR_DEC LimitZeta const* FromBufferObject(
            SIXTRL_BUFFER_ARGPTR_DEC SIXTRL_BUFFER_OBJ_ARGPTR_DEC const
                NS(Object) *const SIXTRL_RESTRICT item_info ) SIXTRL_NOEXCEPT;

        SIXTRL_STATIC SIXTRL_FN
        SIXTRL_BE_ARGPTR_DEC LimitZeta* FromBuffer(
            SIXTRL_BUFFER_ARGPTR_DEC Buffer& SIXTRL_RESTRICT_REF buffer,
            size_type const buffer_index ) SIXTRL_NOEXCEPT;

        SIXTRL_STATIC SIXTRL_FN
        SIXTRL_BE_ARGPTR_DEC LimitZeta* FromBuffer(
            SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
            size_type const buffer_index ) SIXTRL_NOEXCEPT;

        SIXTRL_STATIC SIXTRL_FN
        SIXTRL_BE_ARGPTR_DEC AssignAddressItem* FromBufferObject(
            SIXTRL_BUFFER_OBJ_ARGPTR_DEC
                NS(Object)* SIXTRL_RESTRICT item_info ) SIXTRL_NOEXCEPT;

        #endif /* !defined( _GPUCODE ) */

        /* ----------------------------------------------------------------- */

        #if !defined( _GPUCODE )

        SIXTRL_STATIC SIXTRL_FN bool CanAddToBuffer(
            buffer_t& SIXTRL_RESTRICT_REF buffer,
            SIXTRL_BUFFER_ARGPTR_DEC size_type* SIXTRL_RESTRICT
                ptr_requ_objects  = nullptr,
            SIXTRL_BUFFER_ARGPTR_DEC size_type* SIXTRL_RESTRICT
                ptr_requ_slots    = nullptr,
            SIXTRL_BUFFER_ARGPTR_DEC size_type* SIXTRL_RESTRICT
                ptr_requ_dataptrs = nullptr ) SIXTRL_NOEXCEPT;

        SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC LimitZeta*
        CreateNewOnBuffer(
            buffer_t& SIXTRL_RESTRICT_REF buffer ) SIXTRL_NOEXCEPT;

        SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC LimitZeta*
        AddToBuffer( buffer_t& SIXTRL_RESTRICT_REF buffer,
            real_t const min_zeta, real_t const max_zeta );

        #endif /* !defined( _GPUCODE ) */

        /* ----------------------------------------------------------------- */

        SIXTRL_FN type_id_t getTypeId() const SIXTRL_NOEXCEPT;
        SIXTRL_FN size_type getNumDataPtrs() const SIXTRL_NOEXCEPT;

        SIXTRL_FN SIXTRL_BE_ARGPTR_DEC c_api_t const*
            getCApiPtr() const SIXTRL_NOEXCEPT;

        SIXTRL_FN SIXTRL_BE_ARGPTR_DEC c_api_t*
            getCApiPtr() SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_FN void preset() SIXTRL_NOEXCEPT;
        SIXTRL_FN bool valid() const SIXTRL_NOEXCEPT;

        SIXTRL_FN real_t get_min_zeta() const SIXTRL_NOEXCEPT;
        SIXTRL_FN real_t get_max_zeta() const SIXTRL_NOEXCEPT;

        /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

        SIXTRL_FN void set_min_zeta( real_t const min_zeta ) SIXTRL_NOEXCEPT;
        SIXTRL_FN void set_max_zeta( real_t const max_zeta ) SIXTRL_NOEXCEPT;
    };

    #if !defined( _GPUCODE )

    SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC LimitZeta* LimitZeta_new(
        Buffer& SIXTRL_RESTRICT_REF buffer );

    SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC LimitZeta* LimitZeta_new(
        SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT ptr_buffer );

    SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC LimitZeta* LimitZeta_add(
        LimitZeta::buffer_t& SIXTRL_RESTRICT_REF buffer,
        LimitZeta::real_t const min_zeta, LimitZeta::real_t const max_zeta );

    SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC LimitZeta* LimitZeta_add(
        SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT ptr_buffer,
        LimitZeta::real_t const min_zeta, LimitZeta::real_t const max_zeta );

    SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC LimitZeta* LimitZeta_add_copy(
        Buffer& SIXTRL_RESTRICT_REF buffer,
        LimitZeta const& SIXTRL_RESTRICT_REF orig );

    SIXTRL_STATIC SIXTRL_FN SIXTRL_BE_ARGPTR_DEC LimitZeta* LimitZeta_add_copy(
        SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT ptr_buffer,
        LimitZeta const& SIXTRL_RESTRICT_REF orig );

    #endif /* !defined( _GPUCODE ) */

    template<> struct ObjectTypeTraits< ::NS(LimitZeta) >
    {
        SIXTRL_STATIC SIXTRL_INLINE object_type_id_t Type() SIXTRL_NOEXCEPT
        {
            return ::NS(OBJECT_TYPE_LIMIT_ZETA);
        }
    };

    template<> struct ObjectTypeTraits< LimitZeta >
    {
        SIXTRL_STATIC SIXTRL_INLINE object_type_id_t Type() SIXTRL_NOEXCEPT
        {
            return ::NS(OBJECT_TYPE_LIMIT_ZETA);
        }
    };
}

/* ************************************************************************* */
/* ************************************************************************* */

namespace SIXTRL_CXX_NAMESPACE
{

}

#endif /* C++ */

#endif /* SIXTRACKL_COMMON_BE_LIMIT_BE_LIMIT_ZETA_CXX_HPP__ */
