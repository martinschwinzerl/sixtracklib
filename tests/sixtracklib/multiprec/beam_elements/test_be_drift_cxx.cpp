#include "sixtracklib/multiprec/beam_elements/drift.hpp"

#include <cstddef>
#include <cstdlib>
#include <limits>
#include <cmath>

#include <gtest/gtest.h>

#include "sixtracklib/common/cobjects/definitions.h"
#include "sixtracklib/common/beam_elements/drift/drift.h"
#include "sixtracklib/common/beam_elements/drift/storage_cobjects.h"


TEST( CxxMultiprecBeamElementsDriftTests, Conversion )
{
    namespace  st = SIXTRL_CXX_NAMESPACE;
//     using _size_t = st::cobj_size_t;

//     constexpr _size_t NDouble = _size_t{  53 };
    constexpr unsigned NQuad = unsigned{ 113 };
//     constexpr _size_t NDQuad  = _size_t{ 227 };

//     using DoubleDrift  = st::MultiPrecDrift< NDouble >;
    using QuadDrift    = st::MultiPrecDrift< NQuad >;
//     using DblQuadDrift = st::MultiPrecDrift< NDQuad >;

    QuadDrift qdrift;
    qdrift.length = 20.0;

    ::NS(Drift) c99_drift_01;
    ::NS(Drift_preset)( &c99_drift_01 );
    ::NS(Drift_set_length)( &c99_drift_01, 42.0 );

    ASSERT_TRUE( qdrift.allow_conversion_from< ::NS(Drift) >() );
    ASSERT_TRUE( qdrift.allow_conversion_to< ::NS(Drift) >() );

    ASSERT_TRUE( qdrift.convert_to< ::NS(Drift) >( &c99_drift_01 ) ==
                 st::ARCH_STATUS_SUCCESS );

    ASSERT_TRUE( std::fabs( static_cast< double >( qdrift.length ) -
                            ::NS(Drift_length)( &c99_drift_01 ) ) <
                 std::numeric_limits< double >::epsilon() );

    ::NS(Drift_set_length)( &c99_drift_01, 42.0 );

    ASSERT_TRUE( qdrift.convert_from< ::NS(Drift) >( &c99_drift_01 ) ==
                 st::ARCH_STATUS_SUCCESS );

    ASSERT_TRUE( std::fabs( static_cast< double >( qdrift.length ) -
                            ::NS(Drift_length)( &c99_drift_01 ) ) <
                 std::numeric_limits< double >::epsilon() );


//     ASSERT_TRUE( qdrift.allow_conversion_to< ::NS(Drift) >() );

//     st::be_real_t qdrift_length = st::Drift_length( &qdrift );

//     ASSERT_TRUE( std::fabs( static_cast< st::be_real_t >( qdrift.length ) -
//                  ::NS(Drift_length)( &c99_drift_01 ) <=
//                      std::numeric_limits< st::be_real_t >::epsilon() ) );

// //     ASSERT_TRUE( qdrift.convert_to< ::NS(Drift) >( &c99_drift ) ==
//                  st::ARCH_STATUS_SUCCESS );




//     ASSERT_TRUE( st::CObjElem_allow_conversion< ::NS(Drift), QuadDrift >() );

}
