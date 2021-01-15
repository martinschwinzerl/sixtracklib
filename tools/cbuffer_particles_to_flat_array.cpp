#include <algorithm>
#include <fstream>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "sixtracklib/testlib.h"
#include "sixtracklib/sixtracklib.hpp"

typedef struct NS(TempParticle) {
    double x;
    double px;
    double y;
    double py;
    double zeta;
    double delta;

    double rpp;
    double rvv;
    double psigma;
    double chi;
    double charge_ratio;

    double charge0;
    double mass0;
    double beta0;
    double gamma0;
    double p0c;

    uint64_t state;
    uint64_t at_element;
    int64_t at_turn;
    uint64_t id;
}
NS(TempParticle);

int main( int argc, char* argv[] )
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    if( argc < 3 )
    {
        std::cout << "Usage: " << argv[ 0 ]
                  << " PATH_TO_COBJ_FILE PATH_TO_DUMP_FILE" << std::endl;
        return 0;
    }

    st::Buffer buffer( argv[ 1 ] );
    st::buffer_size_t const nobj = buffer.getNumObjects();

    if( nobj <= 0u ) return 0;
    st::buffer_size_t npart = 0u;

    std::vector< st::buffer_size_t > indices( nobj, st::buffer_size_t{ 0 } );
    indices.clear();

    for( st::buffer_size_t ii = 0u ; ii < nobj ; ++ii )
    {
        auto obj = buffer[ ii ];
        if( obj == nullptr ) continue;

        auto const type_id = ::NS(Object_get_type_id)( obj );
        switch( type_id )
        {
            case ::NS(OBJECT_TYPE_PARTICLE):
            {
                auto pset = buffer.get< st::Particles >( ii );
                if( pset == nullptr )
                {
                    throw std::runtime_error( "illegal particle set instance" );
                }

                auto const nn = pset->getNumParticles();
                if( nn > 0 )
                {
                    indices.push_back( ii );
                    npart += nn;
                }

                break;
            }

            default: {}
        };
    }

    if( npart == 0u ) return 0;
    std::vector< ::NS(TempParticle) > flat_array( npart, ::NS(TempParticle){} );
    flat_array.clear();

    for( auto const ii : indices )
    {
        auto pset = buffer.get< st::Particles >( ii );
        int64_t const nn = pset->getNumParticles();
        for( int64_t jj = 0 ; jj < nn ; ++jj )
        {
            ::NS(TempParticle) p;
            p.x            = pset->getXValue( jj );
            p.px           = pset->getPxValue( jj );
            p.y            = pset->getYValue( jj );
            p.py           = pset->getPyValue( jj );
            p.zeta         = pset->getZetaValue( jj );
            p.delta        = pset->getDeltaValue( jj );

            p.rpp          = pset->getRppValue( jj );
            p.rvv          = pset->getRvvValue( jj );
            p.psigma       = pset->getPSigmaValue( jj );
            p.chi          = pset->getChiValue( jj );
            p.charge_ratio = pset->getChargeRatioValue( jj );

            p.charge0      = pset->getQ0Value( jj );
            p.mass0        = pset->getMass0Value( jj );
            p.beta0        = pset->getBeta0Value( jj );
            p.gamma0       = pset->getGamma0Value( jj );
            p.p0c          = pset->getP0cValue( jj );

            p.state        = ( pset->getStateValue( jj ) == 1 ) ? 1u : 0u;
            p.at_element   = pset->getAtElementIdValue( jj );
            p.at_turn      = pset->getAtTurnValue( jj );
            p.id           = pset->getParticleIdValue( jj );

            flat_array.push_back( p );
        }
    }

    if( flat_array.size() < npart ) return 0;

    double const temp_npart = static_cast< double >( npart );
    std::ofstream fout( argv[ 2 ], std::ios::out | std::ios::binary );
    fout.write( reinterpret_cast< char const* >( &temp_npart ),
                sizeof( double ) );

    for( auto const& p : flat_array )
    {
        fout.write( reinterpret_cast< char const* >( &p ),
                    sizeof( ::NS(TempParticle) ) );
    }

    return 0;
}
