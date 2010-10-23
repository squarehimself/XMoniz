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
#include <core/window.h>
#include <privatewindow.h>


CompWindow::Geometry::Geometry () :
    mBorder (0)
{
}

CompWindow::Geometry::Geometry (int x,
				int y,
				int width,
				int height,
				int border) :
    CompRect (x, y, width, height),
    mBorder (border)
{
}

int
CompWindow::Geometry::border () const
{
    return mBorder;
}

void
CompWindow::Geometry::setBorder (int border)
{
    mBorder = border;
}

void
CompWindow::Geometry::set (int x,
			   int y,
			   int width,
			   int height,
			   int border)
{
    setX (x);
    setY (y);
    setWidth (width);
    setHeight (height);
    mBorder = border;
}

CompWindow::Geometry &
CompWindow::serverGeometry () const
{
    return priv->serverGeometry;
}

CompWindow::Geometry &
CompWindow::geometry () const
{
    return priv->geometry;
}

int
CompWindow::x () const
{
    return priv->geometry.x ();
}

int
CompWindow::y () const
{
    return priv->geometry.y ();
}

CompPoint
CompWindow::pos () const
{
    return CompPoint (priv->geometry.x (), priv->geometry.y ());
}

/* With border */
int
CompWindow::width () const
{
    return priv->width;
}

int
CompWindow::height () const
{
    return priv->height;
}

CompSize
CompWindow::size () const
{
    return CompSize (priv->width, priv->height);
}

int
CompWindow::serverX () const
{
    return priv->serverGeometry.x ();
}

int
CompWindow::serverY () const
{
    return priv->serverGeometry.y ();
}

CompPoint
CompWindow::serverPos () const
{
    return CompPoint (priv->serverGeometry.x (),
		      priv->serverGeometry.y ());
}

/* With border */
int
CompWindow::serverWidth () const
{
    return priv->serverGeometry.width () +
	   2 * priv->serverGeometry.border ();
}

int
CompWindow::serverHeight () const
{
    return priv->serverGeometry.height () +
	   2 * priv->serverGeometry.border ();
}

const CompSize
CompWindow::serverSize () const
{
    return CompSize (priv->serverGeometry.width () +
		     2 * priv->serverGeometry.border (),
		     priv->serverGeometry.height () +
		     2 * priv->serverGeometry.border ());
}

CompRect
CompWindow::inputRect () const // TUX BUGFIX
{
    return CompRect (priv->geometry.x () - priv->input.left,
		     priv->geometry.y () - priv->input.top,
		     //priv->geometry.width () +
		     priv->width  +
		     priv->input.left + priv->input.right,
		     //priv->geometry.height () +
		     priv->height  +
		     priv->input.top + priv->input.bottom);
}

CompRect
CompWindow::serverInputRect () const
{
    return CompRect (priv->serverGeometry.x () - priv->input.left,
		     priv->serverGeometry.y () - priv->input.top,
		     priv->serverGeometry.width () +
		     priv->input.left + priv->input.right,
		     priv->serverGeometry.height () +
		     priv->input.top + priv->input.bottom);
}

CompRect
CompWindow::outputRect () const
{
    return CompRect (priv->geometry.x () - priv->output.left,
		     priv->geometry.y () - priv->output.top,
		     priv->geometry.width () +
		     priv->output.left + priv->output.right,
		     priv->geometry.height () +
		     priv->output.top + priv->output.bottom);
}

CompRect
CompWindow::serverOutputRect () const
{
    return CompRect (priv->serverGeometry.x () - priv->output.left,
		     priv->serverGeometry.y () - priv->output.top,
		     priv->serverGeometry.width () +
		     priv->output.left + priv->output.right,
		     priv->serverGeometry.height () +
		     priv->output.top + priv->output.bottom);
}
