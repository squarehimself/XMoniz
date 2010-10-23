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
 *	    Sam Spilsbury <smspillaz@gmail.com>
 */

#include <core/screen.h>
#include "privatescreen.h"

const unsigned int ModifierHandler::virtualModMask[7] = {
            CompAltMask, CompMetaMask, CompSuperMask, CompHyperMask,
            CompModeSwitchMask, CompNumLockMask, CompScrollLockMask
};

const int ModifierHandler::maskTable[8] = {
	    ShiftMask, LockMask, ControlMask, Mod1Mask,
	    Mod2Mask, Mod3Mask, Mod4Mask, Mod5Mask
};

unsigned int
ModifierHandler::ignoredModMask ()
{
    return mIgnoredModMask;
}

const XModifierKeymap *
ModifierHandler::modMap ()
{
    return mModMap;
}

void
ModifierHandler::updateModifierMappings ()
{
    unsigned int    modMask[CompModNum];
    int		    i, minKeycode, maxKeycode, keysymsPerKeycode = 0;
    KeySym*         key;

    for (i = 0; i < CompModNum; i++)
	modMask[i] = 0;

    XDisplayKeycodes (screen->dpy (), &minKeycode, &maxKeycode);
    key = XGetKeyboardMapping (screen->dpy (),
			       minKeycode, (maxKeycode - minKeycode + 1),
			       &keysymsPerKeycode);

    if (mModMap)
	XFreeModifiermap (mModMap);

    mModMap = XGetModifierMapping (screen->dpy ());
    if (mModMap && mModMap->max_keypermod > 0)
    {
	KeySym keysym;
	int    index, size, mask;

	size = maskTableSize * mModMap->max_keypermod;

	for (i = 0; i < size; i++)
	{
	    if (!mModMap->modifiermap[i])
		continue;

	    index = 0;
	    do
	    {
		keysym = XKeycodeToKeysym (screen->dpy (),
					   mModMap->modifiermap[i],
					   index++);
	    } while (!keysym && index < keysymsPerKeycode);

	    if (keysym)
	    {
		mask = maskTable[i / mModMap->max_keypermod];

		if (keysym == XK_Alt_L ||
		    keysym == XK_Alt_R)
		{
		    modMask[CompModAlt] |= mask;
		}
		else if (keysym == XK_Meta_L ||
			 keysym == XK_Meta_R)
		{
		    modMask[CompModMeta] |= mask;
		}
		else if (keysym == XK_Super_L ||
			 keysym == XK_Super_R)
		{
		    modMask[CompModSuper] |= mask;
		}
		else if (keysym == XK_Hyper_L ||
			 keysym == XK_Hyper_R)
		{
		    modMask[CompModHyper] |= mask;
		}
		else if (keysym == XK_Mode_switch)
		{
		    modMask[CompModModeSwitch] |= mask;
		}
		else if (keysym == XK_Scroll_Lock)
		{
		    modMask[CompModScrollLock] |= mask;
		}
		else if (keysym == XK_Num_Lock)
		{
		    modMask[CompModNumLock] |= mask;
		}
	    }
	}

	for (i = 0; i < CompModNum; i++)
	{
	    if (!modMask[i])
		modMask[i] = CompNoMask;
	}

	if (memcmp (modMask, mModMask, sizeof (modMask)))
	{
	    memcpy (mModMask, modMask, sizeof (modMask));

	    mIgnoredModMask = LockMask |
		(modMask[CompModNumLock]    & ~CompNoMask) |
		(modMask[CompModScrollLock] & ~CompNoMask);

	    screen->priv->updatePassiveKeyGrabs ();
	}
    }

    if (key)
	XFree (key);
}

unsigned int
ModifierHandler::virtualToRealModMask (unsigned int modMask)
{
    int i;

    for (i = 0; i < CompModNum; i++)
    {
	if (modMask & virtualModMask[i])
	{
	    modMask &= ~virtualModMask[i];
	    modMask |= mModMask[i];
	}
    }

    return modMask;
}

unsigned int
ModifierHandler::keycodeToModifiers (int keycode)
{
    unsigned int mods = 0;
    int mod, k;

    for (mod = 0; mod < maskTableSize; mod++)
    {
	for (k = 0; k < mModMap->max_keypermod; k++)
	{
	    if (mModMap->modifiermap[mod *
		mModMap->max_keypermod + k] == keycode)
		mods |= maskTable[mod];
	}
    }

    return mods;
}

ModifierHandler::ModifierHandler () :
    mIgnoredModMask (LockMask),
    mModMap (0)
{
    for (int i = 0; i < ModNum; i++)
	mModMask[i] = NoMask;
}

ModifierHandler::~ModifierHandler ()
{
    if (mModMap)
	XFreeModifiermap (mModMap);

    mModMap = NULL;
}
