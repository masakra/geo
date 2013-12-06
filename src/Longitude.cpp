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

#include "Longitude.h"

#include "Geo.h"
#include <math.h>

Longitude::Longitude()
	: Coordinate()
{
}

Longitude::Longitude( double val )
	: Coordinate( val )
{
	bound();
}

void
Longitude::bound()
{
	if ( ! isValid() )
		return;

	while ( value > 180.0 )
		value -= 360.0;

	while ( value < -180.0 )
		value += 360.0;
}

double
Longitude::mercator() const
{
	return radian();
}

bool
Longitude::operator%( Longitude longitude ) const
{
	return Coordinate::operator%( longitude );
}

std::string
Longitude::strShort() const
{
	return Coordinate::strShort( "%c%03.0f°%04.1f′", geo::West, geo::East );
}

Longitude
Longitude::fromMercator( double x )	// static
{
	return geo::rad2deg( x );
}

