#include "sixtracklib/common/architecture/architecture.h"
#include "sixtracklib/common/architecture/architecture.hpp"

#include <cstddef>
#include <cstdlib>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/architecture/definitions.h"
#include "sixtracklib/common/architecture/arch_data.hpp"

namespace st = SIXTRL_CXX_NAMESPACE;

::NS(Architectures)* NS(Architectures_get_ptr)()
{
    return st::Architectures_get_ptr();
}

::NS(Architectures) const* NS(Architectures_get_const_ptr)()
{
    return st::Architectures_get_const_ptr();
}

/* ************************************************************************* */

bool NS(Architectures_has_architecture)(
    const ::NS(Architectures) *const SIXTRL_RESTRICT architectures,
    ::NS(arch_id_t) const arch_id )
{
    return ( ( architectures != nullptr ) &&
             ( architectures->hasArchitectures( arch_id ) ) );
}

bool NS(Architectures_has_arch_str)(
    const ::NS(Architectures) *const SIXTRL_RESTRICT architectures,
    ::NS(arch_id_t) const arch_id )
{
    return ( ( architectures != nullptr ) &&
             ( architectures->hasArchStr( arch_id ) ) );
}

char const* NS(Architectures_get_arch_str)(
    const ::NS(Architectures) *const SIXTRL_RESTRICT architectures,
    ::NS(arch_id_t) const arch_id )
{
    return ( architectures != nullptr )
        ? architectures->ptrArchStr( arch_id ) : nullptr;
}

/* ------------------------------------------------------------------------- */

::NS(arch_id_t) NS(Architectures_get_arch_id)(
    const ::NS(Architectures) *const SIXTRL_RESTRICT architectures,
    char const* SIXTRL_RESTRICT arch_str )
{
    return ( architectures != nullptr )
        ? architectures->archId( arch_str ) : st::ARCHITECTURE_ILLEGAL;
}

/* ------------------------------------------------------------------------- */

::NS(ArchData) const* NS(Architectures_get_ptr_const_arch_data)(
    const ::NS(Architectures) *const SIXTRL_RESTRICT architectures,
    NS(arch_id_t) const arch_id )
{
    return ( architectures != nullptr )
        ? architectures->ptrArchDataBase( arch_id ) : nullptr;
}

::NS(ArchData) const* NS(Architectures_get_ptr_const_arch_data_by_arch_str)(
    const ::NS(Architectures) *const SIXTRL_RESTRICT architectures,
    char const* SIXTRL_RESTRICT arch_str )
{
    return ( architectures != nullptr )
        ? architectures->ptrArchDataBase( arch_str ) : nullptr;
}

/* ------------------------------------------------------------------------- */

::NS(arch_size_t) NS(Architectures_get_num_architectures)(
    const ::NS(Architectures) *const SIXTRL_RESTRICT architectures )
{
    return ( architectures != nullptr )
        ? architectures->numArchitectures() : ::NS(arch_size_t){ 0 };
}

/* ------------------------------------------------------------------------- */

bool NS(Architectures_has_handle)(
    const ::NS(Architectures) *const SIXTRL_RESTRICT architectures,
    NS(arch_id_t) const arch_id )
{
    return ( ( architectures != nullptr ) &&
             ( architectures->hasHandle( arch_id ) ) );
}

bool NS(Architectures_is_enabled)(
    const ::NS(Architectures) *const SIXTRL_RESTRICT architectures,
    NS(arch_id_t) const arch_id )
{
    return ( ( architectures != nullptr ) &&
             ( architectures->isEnabled( arch_id ) ) );
}

bool NS(Architectures_is_activated)(
    const ::NS(Architectures) *const SIXTRL_RESTRICT architectures,
    NS(arch_id_t) const arch_id )
{
    return ( ( architectures != nullptr ) &&
             ( architectures->isActivated( arch_id ) ) );
}

bool NS(Architectures_is_available)(
    const ::NS(Architectures) *const SIXTRL_RESTRICT architectures,
    NS(arch_id_t) const arch_id )
{
    return ( ( architectures != nullptr ) &&
             ( architectures->isAvailable( arch_id ) ) );
}

bool NS(Architectures_is_shutdown)(
    const ::NS(Architectures) *const SIXTRL_RESTRICT architectures,
    NS(arch_id_t) const arch_id )
{
    return ( ( architectures != nullptr ) &&
             ( architectures->isShutdown( arch_id ) ) );
}

::NS(arch_init_flags_t) NS(Architectures_get_init_flags)(
    const ::NS(Architectures) *const SIXTRL_RESTRICT architectures,
    ::NS(arch_id_t) const arch_id )
{
    return ( architectures != nullptr )
        ? architectures->initFlags( arch_id ) : st::ARCH_INIT_STATE_NONE;
}

/* end: sixtracklib/common/architecture/architecture_c99.cpp */
