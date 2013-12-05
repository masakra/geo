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

#include "Coordinate.h"

#include "Geo.h"
#include <math.h>
#include <stdlib.h>

Coordinate::Coordinate()
	: value( nan( 0 ) )
{
}

Coordinate::Coordinate( double val )
	: value( val )
{
}

Coordinate::operator double() const
{
	return value;
}

bool
Coordinate::isValid() const
{
	return value == value;	// nan == nan is False
}

std::string
Coordinate::strShort( const char * format, char positive, char negative ) const
{
	char str[ STR_BUF_SIZE ];

	double i,
		   f = modf( value, &i );

	snprintf( str, STR_BUF_SIZE, format,
			( value > 0 ? positive : negative ),
			i,
			f * 60. );

	return std::string( str );
}

double
Coordinate::radian() const
{
	return geo::deg2rad( value );
}

bool
Coordinate::operator%( double other ) const
{
	return ( value * other ) > 0.;
}

double
Coordinate::gmsc2g( const std::string & g, const std::string & m, const std::string & s,
		const std::string & c )
{
	int gi = strtol( g.c_str(), 0, 10 ),
		mi = strtol( m.c_str(), 0, 10 ),
		si = strtol( s.c_str(), 0, 10 ),
		ci = strtol( c.c_str(), 0, 10 );

	return gi + mi / 60.0 + ( si + ci / 100.0 ) / 3600.0;
}

