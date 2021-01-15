#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "sixtracklib/testlib.h"
#include "sixtracklib/sixtracklib.hpp"
#include "sixtracklib/common/be_cavity/be_cavity.hpp"
#include "sixtracklib/common/be_srotation/be_srotation.hpp"
#include "sixtracklib/common/be_xyshift/be_xyshift.hpp"
#include "sixtracklib/common/be_multipole/be_multipole.hpp"

int main( int argc, char* argv[] )
{
    namespace st = SIXTRL_CXX_NAMESPACE;

    if( argc < 3 )
    {
        std::cout << "Usage: " << argv[ 0 ]
                  << " PATH_TO_COBJ_FILE PATH_TO_DUMP_FILE" << std::endl;
        return 0;
    }

    bool success = true;
    std::vector< double > flat_array;
    flat_array.reserve( 1u << 22u );
    flat_array.clear();

    st::Buffer buffer( argv[ 1 ] );
    st::buffer_size_t const nobj = buffer.getNumObjects();

    for( st::buffer_size_t ii = 0u ; ii < nobj ; ++ii )
    {
        auto obj = buffer[ ii ];

        if( obj != nullptr )
        {
            auto const type_id = ::NS(Object_get_type_id)( obj );
            switch( type_id )
            {
                case ::NS(OBJECT_TYPE_DRIFT):
                {
                    auto elem = buffer.get< st::Drift >( ii );
                    flat_array.push_back( static_cast< double >( type_id ) );
                    flat_array.push_back( elem->getLength() );
                    break;
                }

                case ::NS(OBJECT_TYPE_DRIFT_EXACT):
                {
                    auto elem = buffer.get< st::DriftExact >( ii );
                    flat_array.push_back( static_cast< double >( type_id ) );
                    flat_array.push_back( elem->getLength() );
                    break;
                }

                case ::NS(OBJECT_TYPE_CAVITY):
                {
                    auto elem = buffer.get< st::Cavity >( ii );
                    flat_array.push_back( static_cast< double >( type_id ) );
                    flat_array.push_back( elem->getVoltage() );
                    flat_array.push_back( elem->getFrequency() );
                    flat_array.push_back( elem->getLag() );
                    break;
                }

                case ::NS(OBJECT_TYPE_XYSHIFT):
                {
                    auto elem = buffer.get< st::XYShift >( ii );
                    flat_array.push_back( static_cast< double >( type_id ) );
                    flat_array.push_back( elem->getDx() );
                    flat_array.push_back( elem->getDy() );
                    break;
                }

                case ::NS(OBJECT_TYPE_SROTATION):
                {
                    auto elem = buffer.get< st::SRotation >( ii );
                    flat_array.push_back( static_cast< double >( type_id ) );
                    flat_array.push_back( elem->getCosAngle() );
                    flat_array.push_back( elem->getSinAngle() );
                    break;
                }

                case ::NS(OBJECT_TYPE_MULTIPOLE):
                {
                    auto elem = buffer.get< st::Multipole >( ii );
                    if( elem->getOrder() > 16 )
                    {
                        throw std::runtime_error( "Order too large to dump" );
                    }

                    flat_array.push_back( static_cast< double >( type_id ) );
                    flat_array.push_back( static_cast< double >( elem->getOrder() ) );
                    flat_array.push_back( static_cast< double >( elem->getLength() ) );
                    flat_array.push_back( static_cast< double >( elem->getHxl() ) );
                    flat_array.push_back( static_cast< double >( elem->getHyl() ) );

                    double bal_array[ 34 ];
                    std::fill( &bal_array[ 0 ], &bal_array[ 34 ], double{ 0.0 } );
                    std::copy( elem->begin(), elem->end(), &bal_array[ 0 ] );
                    flat_array.insert( flat_array.end(),
                        &bal_array[ 0 ], &bal_array[ 34 ] );
                    break;
                }

                case ::NS(OBJECT_TYPE_LIMIT_RECT):
                {
                    ::NS(LimitRect) const* elem =
                        ::NS(LimitRect_const_from_buffer)(
                            buffer.getCApiPtr(), ii );

                    if( elem == nullptr )
                    {
                        throw std::runtime_error( "illegal beam element" );
                    }

                    flat_array.push_back( static_cast< double >(
                        ::NS(OBJECT_TYPE_LIMIT_RECT) ) ); // type_id
                    flat_array.push_back( elem->min_x );
                    flat_array.push_back( elem->max_x );
                    flat_array.push_back( elem->min_y );
                    flat_array.push_back( elem->max_y );
                    break;
                }

                case ::NS(OBJECT_TYPE_LIMIT_ELLIPSE):
                {
                    ::NS(LimitEllipse) const* elem =
                        ::NS(LimitEllipse_const_from_buffer)(
                            buffer.getCApiPtr(), ii );

                    if( elem == nullptr )
                    {
                        throw std::runtime_error( "illegal beam element" );
                    }

                    flat_array.push_back( static_cast< double >(
                        ::NS(OBJECT_TYPE_LIMIT_ELLIPSE) ) ); // type_id
                    flat_array.push_back( elem->a_squ );
                    flat_array.push_back( elem->b_squ );
                    flat_array.push_back( elem->a_b_squ );
                    break;
                }

                case ::NS(OBJECT_TYPE_LIMIT_RECT_ELLIPSE):
                {
                    ::NS(LimitRectEllipse) const* elem =
                        ::NS(LimitRectEllipse_const_from_buffer)(
                            buffer.getCApiPtr(), ii );

                    if( elem == nullptr )
                    {
                        throw std::runtime_error( "illegal beam element" );
                    }

                    flat_array.push_back( static_cast< double >( 13 ) ); // type-id
                    flat_array.push_back( elem->max_x );
                    flat_array.push_back( elem->max_y );
                    flat_array.push_back( elem->a_squ );
                    flat_array.push_back( elem->b_squ );
                    flat_array.push_back( elem->a_squ_b_squ );
                    break;
                }

                case ::NS(OBJECT_TYPE_DIPEDGE):
                {
                    ::NS(DipoleEdge) const* elem =
                    ::NS(DipoleEdge_const_from_buffer)( buffer.getCApiPtr(), ii );

                    if( elem == nullptr )
                    {
                        throw std::runtime_error( "illegal beam element" );
                    }

                    flat_array.push_back( static_cast<
                        double >( ::NS(OBJECT_TYPE_DIPEDGE) ) ); // type-id
                    flat_array.push_back( elem->r21 );
                    flat_array.push_back( elem->r43 );
                    break;
                }

                case ::NS(OBJECT_TYPE_BEAM_MONITOR):
                {
                    break;
                }

                case ::NS(OBJECT_TYPE_SC_COASTING):
                {
                    ::NS(SCCoasting) const* elem =
                        ::NS(SCCoasting_const_from_buffer)(
                            buffer.getCApiPtr(), ii );

                    if( elem == nullptr )
                    {
                        throw std::runtime_error( "illegal beam element" );
                    }

                    flat_array.push_back( double{ 16.0 } ); // type_id
                    flat_array.push_back( elem->number_of_particles );
                    flat_array.push_back( elem->circumference );
                    flat_array.push_back( elem->sigma_x );
                    flat_array.push_back( elem->sigma_y );
                    flat_array.push_back( elem->length );
                    flat_array.push_back( elem->x_co );
                    flat_array.push_back( elem->y_co );
                    flat_array.push_back( elem->min_sigma_diff );
                    flat_array.push_back( static_cast< double >( elem->enabled ) );
                    break;
                }

                default:
                {
                    success = false;
                    std::cout << "Unknown beam-element type_id = " << type_id
                              << std::endl;
                }
            };
        }
        else
        {
            success = false;
        }

        if( !success ) break;
    }

    if( success )
    {
        double const num_slots_in_flat_array = static_cast< double >(
            flat_array.size() );

        std::ofstream fout( argv[ 2 ], std::ios::out | std::ios::binary );
        fout.write( reinterpret_cast< char const* >( &num_slots_in_flat_array ),
                    sizeof( double ) );
        fout.write( reinterpret_cast< char const* >( flat_array.data() ),
                    flat_array.size() * sizeof( double ) );
    }

    return 0;
}
