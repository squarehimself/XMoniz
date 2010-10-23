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

#include <core/pluginclasses.h>

PluginClassStorage::PluginClassStorage (PluginClassStorage::Indices& iList) :
    pluginClasses (0)
{
    if (iList.size () > 0)
	pluginClasses.resize (iList.size ());
}

unsigned int
PluginClassStorage::allocatePluginClassIndex (PluginClassStorage::Indices& iList)
{
    unsigned int i;

    for (i = 0; i < iList.size (); i++)
    {
	if (!iList.at (i))
	{
	    iList.at (i) = true;
	    return i;
	}
    }

    i = iList.size ();
    iList.resize (i + 1);
    iList.at (i) = true;

    return i;
}

void
PluginClassStorage::freePluginClassIndex (PluginClassStorage::Indices& iList,
					  unsigned int                 idx)
{
    unsigned int size = iList.size ();

    if (idx >= size)
	return;

    if (idx < size - 1)
    {
	iList.at (idx) = false;
	return;
    }

    iList.resize (size - 1);
}
