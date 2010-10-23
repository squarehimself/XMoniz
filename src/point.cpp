/*
 * Copyright © 2008 Dennis Kasprzyk
 *
 * Permission to use, copy, modify, distribute, and sell this software
 * and its documentation for any purpose is hereby granted without
 * fee, provided that the above copyright notice appear in all copies
 * and that both that copyright notice and this permission notice
 * appear in supporting documentation, and that the name of
 * Dennis Kasprzyk not be used in advertising or publicity pertaining to
 * distribution of the software without specific, written prior permission.
 * Dennis Kasprzyk makes no representations about the suitability of this
 * software for any purpose. It is provided "as is" without express or
 * implied warranty.
 *
 * DENNIS KASPRZYK DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN
 * NO EVENT SHALL DENNIS KASPRZYK BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
 * WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * Authors: Dennis Kasprzyk <onestone@compiz-fusion.org>
 */

#include <core/point.h>

CompPoint::CompPoint () :
   mX (0),
   mY (0)
{
}

CompPoint::CompPoint (int x, int y) :
   mX (x),
   mY (y)
{
}

void
CompPoint::set (int x, int y)
{
    mX = x;
    mY = y;
}

void
CompPoint::setX (int x)
{
    mX = x;
}

void
CompPoint::setY (int y)
{
    mY = y;
}

bool
CompPoint::operator== (const CompPoint &point) const
{
    return (mX == point.mX) && (mY == point.mY);
}

bool
CompPoint::operator!= (const CompPoint &point) const
{
    return !(*this == point);
}

CompPoint &
CompPoint::operator+= (const CompPoint &point)
{
    mX += point.mX;
    mY += point.mY;

    return *this;
}

CompPoint
CompPoint::operator+ (const CompPoint &rhs) const
{
    return CompPoint (mX + rhs.mX, mY + rhs.mY);
}

CompPoint &
CompPoint::operator-= (const CompPoint &point)
{
    mX -= point.mX;
    mY -= point.mY;

    return *this;
}

CompPoint
CompPoint::operator- (const CompPoint &rhs) const
{
    return CompPoint (mX - rhs.mX, mY - rhs.mY);
}

