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

#include <core/core.h>
#include <core/rect.h>

CompRect::CompRect ()
{
    mRegion.rects = &mRegion.extents;
    mRegion.numRects = 1;
    mRegion.extents.x1 = 0;
    mRegion.extents.x2 = 0;
    mRegion.extents.y1 = 0;
    mRegion.extents.y2 = 0;
}

CompRect::CompRect (int x, int y, int width, int height)
{
    mRegion.rects = &mRegion.extents;
    mRegion.numRects = 1;
    mRegion.extents.x1 = x;
    mRegion.extents.y1 = y;
    mRegion.extents.x2 = x + width;
    mRegion.extents.y2 = y + height;
}

CompRect::CompRect (const CompRect& r)
{
    mRegion = r.mRegion;
    mRegion.rects = &mRegion.extents;
}

CompRect::CompRect (const XRectangle xr)
{
    mRegion.rects = &mRegion.extents;
    mRegion.numRects = 1;
    mRegion.extents.x1 = xr.x;
    mRegion.extents.y1 = xr.y;
    mRegion.extents.x2 = xr.x + xr.width;
    mRegion.extents.y2 = xr.y + xr.height;
}

const Region
CompRect::region () const
{
    return const_cast<const Region> (&mRegion);
}

void
CompRect::setGeometry (int x,
		       int y,
		       int width,
		       int height)
{
    mRegion.extents.x1 = x;
    mRegion.extents.y1 = y;
    mRegion.extents.x2 = x + width;
    mRegion.extents.y2 = y + height;
}

void
CompRect::setX (int x)
{
    int width = mRegion.extents.x2 - mRegion.extents.x1;

    mRegion.extents.x1 = x;
    mRegion.extents.x2 = x + width;
}

void
CompRect::setY (int y)
{
    int height = mRegion.extents.y2 - mRegion.extents.y1;

    mRegion.extents.y1 = y;
    mRegion.extents.y2 = y + height;
}

void
CompRect::setPos (const CompPoint& pos)
{
    setX (pos.x ());
    setY (pos.y ());
}

void
CompRect::setWidth (int width)
{
    mRegion.extents.x2 = mRegion.extents.x1 + width;
}

void
CompRect::setHeight (int height)
{
    mRegion.extents.y2 = mRegion.extents.y1 + height;
}

void
CompRect::setSize (const CompSize& size)
{
    mRegion.extents.x2 = mRegion.extents.x1 + size.width ();
    mRegion.extents.y2 = mRegion.extents.y1 + size.height ();
}

void
CompRect::setLeft (int x1)
{
    mRegion.extents.x1 = x1;
    if (mRegion.extents.x2 < x1)
	mRegion.extents.x2 = x1;
}

void
CompRect::setTop (int y1)
{
    mRegion.extents.y1 = y1;
    if (mRegion.extents.y2 < y1)
	mRegion.extents.y2 = y1;
}

void
CompRect::setRight (int x2)
{
    mRegion.extents.x2 = x2;
    if (mRegion.extents.x1 > x2)
	mRegion.extents.x1 = x2;
}

void
CompRect::setBottom (int y2)
{
    mRegion.extents.y2 = y2;
    if (mRegion.extents.y1 > y2)
	mRegion.extents.y1 = y2;
}

bool
CompRect::contains (const CompPoint& point) const
{
    if (point.x () < x1 ())
	return false;
    if (point.x () > x2 ())
	return false;
    if (point.y () < y1 ())
	return false;
    if (point.y () > y2 ())
	return false;

    return true;
}

bool
CompRect::contains (const CompRect& rect) const
{
    if (rect.x1 () < x1 ())
	return false;
    if (rect.x2 () > x2 ())
	return false;
    if (rect.y1 () < y1 ())
	return false;
    if (rect.y2 () > y2 ())
	return false;

    return true;
}

bool
CompRect::intersects (const CompRect& rect) const
{
    int l, r, t, b;

    /* extents of overlapping rectangle */
    l = MAX (left (), rect.left ());
    r = MIN (right (), rect.right ());
    t = MAX (top (), rect.top ());
    b = MIN (bottom (), rect.bottom ());

    return (l < r) && (t < b);
}

bool
CompRect::isEmpty () const
{
    if (mRegion.extents.x1 != mRegion.extents.x2)
	return false;
    if (mRegion.extents.y1 != mRegion.extents.y2)
	return false;

    return true;
}

int
CompRect::area () const
{
    if (mRegion.extents.x2 < mRegion.extents.x1)
	return 0;
    if (mRegion.extents.y2 < mRegion.extents.y1)
	return 0;

    return (mRegion.extents.x2 - mRegion.extents.x1) *
	   (mRegion.extents.y2 - mRegion.extents.y1);
}

bool
CompRect::operator== (const CompRect &rect) const
{
    if (mRegion.extents.x1 != rect.mRegion.extents.x1)
	return false;
    if (mRegion.extents.y1 != rect.mRegion.extents.y1)
	return false;
    if (mRegion.extents.x2 != rect.mRegion.extents.x2)
	return false;
    if (mRegion.extents.y2 != rect.mRegion.extents.y2)
	return false;

    return true;
}

bool
CompRect::operator!= (const CompRect &rect) const
{
    return !(*this == rect);
}

CompRect
CompRect::operator& (const CompRect &rect) const
{
    CompRect result (*this);

    result &= rect;
    return result;
}

CompRect&
CompRect::operator&= (const CompRect &rect)
{
    int l, r, t, b;

    /* extents of overlapping rectangle */
    l = MAX (left (), rect.left ());
    r = MIN (right (), rect.right ());
    t = MAX (top (), rect.top ());
    b = MIN (bottom (), rect.bottom ());

    mRegion.extents.x1 = l;
    mRegion.extents.x2 = r;
    mRegion.extents.y1 = t;
    mRegion.extents.y2 = b;

    return *this;
}

CompRect &
CompRect::operator= (const CompRect &rect)
{
    mRegion.extents.x1 = rect.mRegion.extents.x1;
    mRegion.extents.y1 = rect.mRegion.extents.y1;
    mRegion.extents.x2 = rect.mRegion.extents.x2;
    mRegion.extents.y2 = rect.mRegion.extents.y2;

    return *this;
}

