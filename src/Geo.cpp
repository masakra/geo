/***************************************************************************
 *   Copyright (C) 2013 by Sergey N Chursanov                              *
 *                                                                         *
 *   email: masakra@mail.ru                                                *
 *   jabber: masakra@jabber.ru                                             *
 *                                                                         *
 *   Permission is hereby granted, free of charge, to any person obtaining *
 *   a copy of this software and associated documentation files (the       *
 *   "Software"), to deal in the Software without restriction, including   *
 *   without limitation the rights to use, copy, modify, merge, publish,   *
 *   distribute, sublicense, and/or sell copies of the Software, and to    *
 *   permit persons to whom the Software is furnished to do so, subject to *
 *   the following conditions:                                             *
 *                                                                         *
 *   The above copyright notice and this permission notice shall be        *
 *   included in all copies or substantial portions of the Software.       *
 *                                                                         *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       *
 *   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    *
 *   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. *
 *   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR     *
 *   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, *
 *   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR *
 *   OTHER DEALINGS IN THE SOFTWARE.                                       *
 ***************************************************************************/

#include "Geo.h"

#include <math.h>

double
geo::deg2rad( double deg )
{
	return deg * M_PI / 180.;
}

double
geo::rad2deg( double rad )
{
	return rad * 180. / M_PI;
}

double
geo::nm2m( double nm )
{
	return nm * M_PER_NM;
}

double
geo::m2nm( double m )
{
	return m / M_PER_NM;
}

double
geo::ortodromiaRad( const Coordinates & from, const Coordinates & to )
{
	double f1 = deg2rad( from.latitude ),
		   l1 = deg2rad( from.longitude ),
		   f2 = deg2rad( to.latitude ),
		   l2 = deg2rad( to.longitude ),
		   dl = l1 - l2;

	//printf("from = %s, to = %s\n", from.strShort().c_str(), to.strShort().c_str() );

	//printf("f1 = %f, f2 = %f, l1 = %f, l2 = %f, dl = %f\n", f1, f2, l1, l2, dl );
	//printf("cos(f1) = %f, cos(f2) = %f, cos(dl) = %f, sin(f1) = %f, sin(f2) = %f\n",
			//cos(f1), cos(f2), cos(dl), sin(f1), sin(f2) );
	//printf("acos() = %f\n", .999999822880 );

	if ( from.latitude % to.latitude ) {	// широты в одном полушарии
		//printf("одно полушарие\n");
		if ( dl > M_PI_2 ) {
			return acos( sin( f1 ) * sin( f2 ) - cos( f1 ) * cos( f2 ) * cos( M_PI - dl ) );
		} else {
			return acos( sin( f1 ) * sin( f2 ) + cos( f1 ) * cos( f2 ) * cos( dl ) );
		}
	} else {
		//printf("разные полушария\n");
		if ( dl > M_PI_2 ) {
			//printf("больше %f\n", M_PI_2);
			return M_PI - acos( sin( f1 ) * sin( f2 ) + cos( f1 ) * cos( f2 ) * cos( M_PI - dl ) );
		} else {
			//printf("меньше %f\n", M_PI_2);
			return acos( cos( f1 ) * cos( f2 ) * cos( dl ) - sin( f1 ) * sin( f2 ) );
		}
	}
}

double
geo::ortodromia( const Coordinates & from, const Coordinates & to )
{
	if ( ! from.isValid() || ! to.isValid() )
		return .0;

	if ( from == to )
		return .0;

	return ortodromiaRad( from, to ) * EARTH_RADIUS;
}

double
geo::feet2m( double feet )
{
	return feet * .3048;
}

double
geo::m2feet( double m )
{
	return m / .3048;
}

double
geo::knot2kmh( double knot )
{
	return knot * 1.852;
}

Coordinates
geo::newCoordinatesRad( const Coordinates & point, double ath, double rad )
{
	// ath - азимут в радианах
	// rad - дистанция в радианах

	/* http://gis-lab.info/qa/angles-sphere.html
		расчитывается треугольник:
		исходная точка (A)
		 - северный полюс (N)
		 - искомая точка
		cos a = cos b * cos c + sin b * sin c * cos A
		*/

	const double c = deg2rad( 90 - point.latitude ),    // расстояние до полюса

	// расстояние от полюса до искомой точки - новая широта
	a = acos( cos( rad ) * cos( c ) + sin( rad ) * sin( c ) * cos( ath ) );

	// угол у северного полюса
	// он же - разница долгот
	//qreal N = acos((cos(b) - cos(c) * cos(a)) / (sin(c) * sin(a)));

	// подкосинусное выражение в некоторых случаях может быть > 1
	// вероятно из-за ошибки вычисления, сделана принудительная проверка
	double sac = ( cos( rad ) - cos( c ) * cos( a ) ) / sin( c ) / sin( a );

	if ( sac > 1.0 )
		sac = 1.0;

	//qreal N = acos( ( cos( rad ) - cos( c ) * cos( a ) ) / sin( c ) / sin( a ) );
	double N = acos( sac );

	if ( ath > M_PI )
		N *= -1;


	return Coordinates( point.longitude + rad2deg( N ), 90 - rad2deg( a ) );
}

double
geo::trueCourseRad( const Coordinates & from, const Coordinates & to )
{
	double f1 = deg2rad( from.latitude ),
		   l1 = deg2rad( from.longitude ),
		   f2 = deg2rad( to.latitude ),
		   l2 = deg2rad( to.longitude ),
		   pi2 = M_PI * 2,
		   rad = atan2f( ( sin( l2 - l1 ) * cos( f2 ) ),
				   ( cos( f1 ) * sin( f2 ) - sin( f1 ) * cos( f2 ) * cos( fabs( l2 - l1 ) ) ) );

	while ( rad < 0 )
		rad += pi2;

	return fmodf( rad, pi2 );
}

double
geo::trueCourseDeg( const Coordinates & from, const Coordinates & to )
{
	return rad2deg( trueCourseRad( from, to ) );
}

int
geo::m2fl( int m )
{
	// округление до тысяч, что бы в конце был '0'
	const int feet_thou = round( m2feet( m ) / 1000.0 );

	// округление до сотен
	return feet_thou * 10;
}

Coordinates
geo::centerBetween( const Coordinates & c1, const Coordinates & c2 )
{
	const double ath = trueCourseRad( c1, c2 ),
				 dist = ortodromiaRad( c1, c2 );

	return newCoordinatesRad( c1, ath, dist / 2.0 );
}

double
geo::distanceToOrto( const Coordinates & point, const Coordinates & from, const Coordinates & to )
{
	/*
	 * По сферической теореме синусов. sin a / sin A == sin b / sin B == sin c / sin C
	 * sin( 90 ) == 1
	 */
	const double ortoAngle = trueCourseRad( from, to ),
				 pointAngle = trueCourseRad( from, point ),
				 angle = ortoAngle - pointAngle,
				 distance = ortodromiaRad( from, point );

	return abs( angle * distance ) * EARTH_RADIUS;
}

