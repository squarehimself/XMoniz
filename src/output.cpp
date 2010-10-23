/*
 * Copyright © 2008 Dennis Kasprzyk
 * Copyright © 2007 Novell, Inc.
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
 *          David Reveman <davidr@novell.com>
 */

#include <core/core.h>
#include <core/output.h>

CompOutput::CompOutput ()
{
    mName = "";
    mId = ~0;
}

CompString
CompOutput::name () const
{
    return mName;
}

unsigned int
CompOutput::id () const
{
    return mId;
}

const CompRect&
CompOutput::workArea () const
{
    return mWorkArea;
}

void
CompOutput::setWorkArea (const CompRect& workarea)
{
    mWorkArea = workarea;

    if (workarea.x () < (int) x1 ())
	mWorkArea.setX (x1 ());

    if (workarea.y () < (int) y1 ())
	mWorkArea.setY (y1 ());

    if (workarea.x2 () > (int) x2 ())
	mWorkArea.setWidth (x2 () - mWorkArea.x ());

    if (workarea.y2 () > (int) y2 ())
	mWorkArea.setHeight (y2 () - mWorkArea.y ());
}

void
CompOutput::setGeometry (int x,
			 int y,
			 int width,
			 int height)
{
    CompRect::setGeometry (x, y, width, height);

    mWorkArea = *this;
}

void
CompOutput::setId (CompString name, unsigned int id)
{
    mName = name;
    mId = id;
}

