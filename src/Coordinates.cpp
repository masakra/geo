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

#include "Coordinates.h"

Coordinates::Coordinates()
	:latitude(), longitude()
{
}

Coordinates::Coordinates( Longitude lon, Latitude lat )
	: latitude( lat ), longitude( lon )
{
}

bool
Coordinates::isValid() const
{
	return latitude.isValid() && longitude.isValid();
}

std::string
Coordinates::strShort( const char * delim ) const
{
	char str[ STR_BUF_SIZE + STR_BUF_SIZE ];

	snprintf( str, STR_BUF_SIZE + STR_BUF_SIZE, "%s%s%s",
			latitude.strShort().c_str(),
			delim,
			longitude.strShort().c_str() );

	return std::string( str );
}

Coordinates
Coordinates::fromMercator( double x, double y )		// static
{
	return Coordinates( Longitude::fromMercator( x ), Latitude::fromMercator( y ) );
}

bool
Coordinates::operator==( const Coordinates & other ) const
{
	return latitude == other.latitude && longitude == other.longitude;
}

