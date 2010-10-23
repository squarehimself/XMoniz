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

#include <core/timer.h>
#include <core/screen.h>
#include "privatescreen.h"

CompTimer::CompTimer () :
    mActive (false),
    mMinTime (0),
    mMaxTime (0),
    mMinLeft (0),
    mMaxLeft (0),
    mCallBack (NULL)
{
}

CompTimer::~CompTimer ()
{
    if (mActive)
	screen->priv->removeTimer (this);
}

void
CompTimer::setTimes (unsigned int min, unsigned int max)
{
    bool wasActive = mActive;
    if (mActive)
	stop ();
    mMinTime = min;
    mMaxTime = (min <= max)? max : min;

    if (wasActive)
	start ();
}

void
CompTimer::setCallback (CompTimer::CallBack callback)
{
    bool wasActive = mActive;
    if (mActive)
	stop ();
    mCallBack = callback;

    if (wasActive)
	start ();
}

void
CompTimer::start ()
{
    stop ();

    if (mCallBack.empty ())
    {
	compLogMessage ("core", CompLogLevelWarn,
			"Attempted to start timer without callback.");
	return;
    }

    mActive = true;
    screen->priv->addTimer (this);
}

void
CompTimer::start (unsigned int min, unsigned int max)
{
    stop ();
    setTimes (min, max);
    start ();
}

void
CompTimer::start (CompTimer::CallBack callback,
		  unsigned int min, unsigned int max)
{
    stop ();
    setTimes (min, max);
    setCallback (callback);
    start ();
}

void
CompTimer::stop ()
{
    mActive = false;
    screen->priv->removeTimer (this);
}

unsigned int
CompTimer::minTime ()
{
    return mMinTime;
}

unsigned int
CompTimer::maxTime ()
{
    return mMaxTime;
}

unsigned int
CompTimer::minLeft ()
{
    return (mMinLeft < 0)? 0 : mMinLeft;
}

unsigned int
CompTimer::maxLeft ()
{
    return (mMaxLeft < 0)? 0 : mMaxLeft;
}

bool
CompTimer::active ()
{
    return mActive;
}
