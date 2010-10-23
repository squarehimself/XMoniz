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

#include <stdio.h>

#include <X11/Xlib-xcb.h>
#include <X11/Xutil.h>
#include <X11/Xregion.h>

#include <core/core.h>

#include "privateregion.h"

const CompRegion infiniteRegion (CompRect (MINSHORT, MINSHORT,
				           MAXSHORT * 2, MAXSHORT * 2));
const CompRegion emptyRegion;

CompRegion::CompRegion ()
{
    priv = new PrivateRegion ();
}

CompRegion::CompRegion (const CompRegion &c)
{
    priv = new PrivateRegion ();
    priv->box = c.priv->box;
    if (priv->box.rects)
	priv->box.rects = &priv->box.extents;
    if (c.priv->region)
    {
	priv->region = XCreateRegion ();
	XUnionRegion (CompRegion ().handle (), c.priv->region, priv->region);
    }
}

CompRegion::CompRegion ( int x, int y, int w, int h)
{
    priv = new PrivateRegion ();
    priv->box.extents = CompRect (x, y, w, h).region ()->extents;
    priv->box.numRects = 1;
    priv->box.rects = &priv->box.extents;
}

CompRegion::CompRegion (const CompRect &r)
{
    priv = new PrivateRegion ();
    priv->box.extents = r.region ()->extents;
    priv->box.numRects = 1;
    priv->box.rects = &priv->box.extents;
}

CompRegion::~CompRegion ()
{
    delete priv;
}

const Region
CompRegion::handle () const
{
    return (priv->region)? priv->region : &priv->box;
}

CompRegion &
CompRegion::operator= (const CompRegion &c)
{
    priv->box = c.priv->box;
    if (priv->box.rects)
	priv->box.rects = &priv->box.extents;
    if (c.priv->region)
    {
	if (!priv->region)
	    priv->region = XCreateRegion ();
	XUnionRegion (CompRegion ().handle (), c.priv->region, priv->region);
    }
    else
    {
	if (priv->region)
	{
	    XDestroyRegion (priv->region);
	    priv->region = NULL;
	}
    }
    return *this;
}

bool
CompRegion::operator== (const CompRegion &c) const
{
    return XEqualRegion (handle (), c.handle ());
}

bool
CompRegion::operator!= (const CompRegion &c) const
{
    return !(*this == c);
}

CompRect
CompRegion::boundingRect () const
{
    BOX b = handle ()->extents;
    return CompRect (b.x1, b.y1, b.x2 - b.x1, b.y2 - b.y1);
}

bool
CompRegion::contains (const CompPoint &p) const
{
    return XPointInRegion (handle (), p.x (), p.y ());
}

bool
CompRegion::contains (const CompRect &r) const
{
    int result;

    result = XRectInRegion (handle (), r.x (), r.y (), r.width (), r.height ());

    return result == RectangleIn;
}

bool
CompRegion::contains (int x, int y, int width, int height) const
{
    int result;

    result = XRectInRegion (handle (), x, y, width, height);

    return result == RectangleIn;
}

CompRegion
CompRegion::intersected (const CompRegion &r) const
{
    CompRegion reg (r);
    reg.priv->makeReal ();
    XIntersectRegion (reg.handle (), handle (), reg.handle ());
    return reg;
}

CompRegion
CompRegion::intersected (const CompRect &r) const
{
    CompRegion reg (r);
    reg.priv->makeReal ();
    XIntersectRegion (reg.handle (), handle (), reg.handle ());
    return reg;
}

bool
CompRegion::intersects (const CompRegion &r) const
{
    return !intersected (r).isEmpty ();
}

bool
CompRegion::intersects (const CompRect &r) const
{
    int result;
    result = XRectInRegion (handle (), r.x (), r.y (), r.width (), r.height ());

    return result != RectangleOut;
}

bool
CompRegion::isEmpty () const
{
    return XEmptyRegion (handle ());
}

int
CompRegion::numRects () const
{
    return handle ()->numRects;
}

CompRect::vector
CompRegion::rects () const
{
    CompRect::vector rv;
    if (!numRects ())
	return rv;
    if (!priv->region)
    {
	rv.push_back (CompRect (priv->box.extents.x1,
		                priv->box.extents.y1,
				priv->box.extents.x2 - priv->box.extents.x1,
				priv->box.extents.y2 - priv->box.extents.y1));
	return rv;
    }

    BOX b;
    for (int i = 0; i < priv->region->numRects; i++)
    {
	b = priv->region->rects[i];
	rv.push_back (CompRect (b.x1, b.y1, b.x2 - b.x1, b.y2 - b.y1));
    }
    return rv;
}

CompRegion
CompRegion::subtracted (const CompRegion &r) const
{
    CompRegion rv;
    rv.priv->makeReal ();
    XSubtractRegion (handle (), r.handle (), rv.handle ());
    return rv;
}

CompRegion
CompRegion::subtracted (const CompRect &r) const
{
    CompRegion rv;
    rv.priv->makeReal ();
    XSubtractRegion (handle (), r.region (), rv.handle ());
    return rv;
}

void
CompRegion::translate (int dx, int dy)
{
    priv->makeReal ();
    XOffsetRegion (handle (), dx, dy);
}

void
CompRegion::translate (const CompPoint &p)
{
    translate (p.x (), p.y ());
}

CompRegion
CompRegion::translated (int dx, int dy) const
{
    CompRegion rv (*this);
    rv.translate (dx, dy);
    return rv;
}

CompRegion
CompRegion::translated (const CompPoint &p) const
{
    CompRegion rv (*this);
    rv.translate (p);
    return rv;
}

void
CompRegion::shrink (int dx, int dy)
{
    priv->makeReal ();
    XShrinkRegion (handle (), dx, dy);
}

void
CompRegion::shrink (const CompPoint &p)
{
    translate (p.x (), p.y ());
}

CompRegion
CompRegion::shrinked (int dx, int dy) const
{
    CompRegion rv (*this);
    rv.shrink (dx, dy);
    return rv;
}

CompRegion
CompRegion::shrinked (const CompPoint &p) const
{
    CompRegion rv (*this);
    rv.shrink (p);
    return rv;
}

CompRegion
CompRegion::united (const CompRegion &r) const
{
    CompRegion rv;
    rv.priv->makeReal ();
    XUnionRegion (handle (), r.handle (), rv.handle ());
    return rv;
}

CompRegion
CompRegion::united (const CompRect &r) const
{
    CompRegion rv;
    rv.priv->makeReal ();
    XUnionRegion (handle (), r.region (), rv.handle ());
    return rv;
}

CompRegion
CompRegion::xored (const CompRegion &r) const
{
    CompRegion rv;
    rv.priv->makeReal ();
    XXorRegion (handle (), r.handle (), rv.handle ());
    return rv;
}

const CompRegion
CompRegion::operator& (const CompRegion &r) const
{
    return intersected (r);
}

const CompRegion
CompRegion::operator& (const CompRect &r) const
{
    return intersected (r);
}

CompRegion &
CompRegion::operator&= (const CompRegion &r)
{
    return *this = *this & r;
}

CompRegion &
CompRegion::operator&= (const CompRect &r)
{
    return *this = *this & r;
}

const CompRegion
CompRegion::operator+ (const CompRegion &r) const
{
    return united (r);
}

const CompRegion
CompRegion::operator+ (const CompRect &r) const
{
    return united (r);
}

CompRegion &
CompRegion::operator+= (const CompRegion &r)
{
    return *this = *this + r;
}

CompRegion &
CompRegion::operator+= (const CompRect &r)
{
    return *this = *this + r;
}

const CompRegion
CompRegion::operator- (const CompRegion &r) const
{
    return subtracted (r);
}

const CompRegion
CompRegion::operator- (const CompRect &r) const
{
    return subtracted (r);
}

CompRegion &
CompRegion::operator-= (const CompRegion &r)
{
    return *this = *this - r;
}

CompRegion &
CompRegion::operator-= (const CompRect &r)
{
    return *this = *this - r;
}

const CompRegion
CompRegion::operator^ (const CompRegion &r) const
{
    return xored (r);
}

CompRegion &
CompRegion::operator^= (const CompRegion &r)
{
    return *this = *this ^ r;
}

const CompRegion
CompRegion::operator| (const CompRegion &r) const
{
    return united (r);
}

CompRegion &
CompRegion::operator|= (const CompRegion &r)
{
    return *this = *this | r;
}


PrivateRegion::PrivateRegion ()
{
    region = NULL;
    box.numRects = 0;
    box.extents.x1 = 0;
    box.extents.y1 = 0;
    box.extents.x2 = 0;
    box.extents.y2 = 0;
    box.rects = NULL;
    box.size = 0;
}

PrivateRegion::~PrivateRegion ()
{
    if (region)
	XDestroyRegion (region);
}

void
PrivateRegion::makeReal ()
{
    if (region)
	return;
    region = XCreateRegion ();
    if (box.numRects)
	XUnionRegion (CompRegion ().handle (), &box, region);
}

