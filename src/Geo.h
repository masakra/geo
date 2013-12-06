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

/*! \namespace geo
 *
 * \brief 
 */

#ifndef GEO_H
#define GEO_H

#include "Coordinates.h"

namespace geo {

#define EARTH_RADIUS 6372795.0
#define RAD_100_KM 0.0156917019926
#define RAD_50_KM 0.00784585099631
#define M_PER_NM 1852.0 ///< Метров в морской миле

enum Semisphere {
	North = 'N',
	East = 'E',
	South = 'S',
	West = 'W'
};

double deg2rad( double deg );

double rad2deg( double rad );

double nm2m( double nm );

double m2nm( double m );

double ortodromiaRad( const Coordinates & from, const Coordinates & to );

double ortodromia( const Coordinates & from, const Coordinates & to );

double feet2m( double feet );

double m2feet( double m );

double knot2kmh( double knot );

Coordinates newCoordinatesRad( const Coordinates & point, double ath, double rad );

double trueCourseRad( const Coordinates & from, const Coordinates & to );

double trueCourseDeg( const Coordinates & from, const Coordinates & to );

int m2fl( int m );

Coordinates centerBetween( const Coordinates & c1, const Coordinates & c2 );

double distanceToOrto( const Coordinates & point, const Coordinates & ortoFrom, const Coordinates & ortoTo );
};

#endif

