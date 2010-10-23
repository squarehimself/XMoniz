/*
 * Copyright © 2005 Novell, Inc.
 *
 * Permission to use, copy, modify, distribute, and sell this software
 * and its documentation for any purpose is hereby granted without
 * fee, provided that the above copyright notice appear in all copies
 * and that both that copyright notice and this permission notice
 * appear in supporting documentation, and that the name of
 * Novell, Inc. not be used in advertising or publicity pertaining to
 * distribution of the software without specific, written prior permission.
 * Novell, Inc. makes no representations about the suitability of this
 * software for any purpose. It is provided "as is" without express or
 * implied warranty.
 *
 * NOVELL, INC. DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN
 * NO EVENT SHALL NOVELL, INC. BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
 * WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * Author: David Reveman <davidr@novell.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <compiz.h>

#include <core/option.h>
#include <core/action.h>
#include <core/screen.h>
#include "privateaction.h"
#include "privatescreen.h"

struct _Modifier {
    const char *name;
    int        modifier;
} modifiers[] = {
    { "<Shift>",      ShiftMask		 },
    { "<Control>",    ControlMask	 },
    { "<Mod1>",	      Mod1Mask		 },
    { "<Mod2>",	      Mod2Mask		 },
    { "<Mod3>",	      Mod3Mask		 },
    { "<Mod4>",	      Mod4Mask		 },
    { "<Mod5>",	      Mod5Mask		 },
    { "<Alt>",	      CompAltMask        },
    { "<Meta>",	      CompMetaMask       },
    { "<Super>",      CompSuperMask      },
    { "<Hyper>",      CompHyperMask	 },
    { "<ModeSwitch>", CompModeSwitchMask }
};

#define N_MODIFIERS (sizeof (modifiers) / sizeof (struct _Modifier))

struct _Edge {
    const char *name;
    const char *modifierName;
} edges[] = {
    { "Left",	     "<LeftEdge>"	 },
    { "Right",	     "<RightEdge>"	 },
    { "Top",	     "<TopEdge>"	 },
    { "Bottom",	     "<BottomEdge>"	 },
    { "TopLeft",     "<TopLeftEdge>"	 },
    { "TopRight",    "<TopRightEdge>"	 },
    { "BottomLeft",  "<BottomLeftEdge>"	 },
    { "BottomRight", "<BottomRightEdge>" }
};

static CompString
modifiersToString (unsigned int modMask)
{
    CompString binding;

    for (unsigned int i = 0; i < N_MODIFIERS; i++)
    {
	if (modMask & modifiers[i].modifier)
	    binding += modifiers[i].name;
    }

    return binding;
}

static unsigned int
stringToModifiers (CompString  str)
{
    unsigned int mods = 0;

    for (unsigned int i = 0; i < N_MODIFIERS; i++)
    {
	if (str.find (modifiers[i].name) != std::string::npos)
	    mods |= modifiers[i].modifier;
    }

    return mods;
}

static unsigned int
bindingStringToEdgeMask (CompString  str)
{
    unsigned int edgeMask = 0;

    for (int i = 0; i < SCREEN_EDGE_NUM; i++)
	if (str.find (edges[i].modifierName) != std::string::npos)
	    edgeMask |= 1 << i;

    return edgeMask;
}

static CompString
edgeMaskToBindingString (unsigned int edgeMask)
{
    CompString binding;
    int        i;

    for (i = 0; i < SCREEN_EDGE_NUM; i++)
	if (edgeMask & (1 << i))
	    binding += edges[i].modifierName;

    return binding;
}

CompAction::KeyBinding::KeyBinding () :
    mModifiers (0),
    mKeycode (0)
{
}

CompAction::KeyBinding::KeyBinding (const KeyBinding& k) :
    mModifiers (k.mModifiers),
    mKeycode (k.mKeycode)
{
}

CompAction::KeyBinding::KeyBinding (int keycode, unsigned int modifiers) :
    mModifiers (modifiers),
    mKeycode (keycode)
{
}

unsigned int
CompAction::KeyBinding::modifiers () const
{
    return mModifiers;
}

int
CompAction::KeyBinding::keycode () const
{
    return mKeycode;
}

bool
CompAction::KeyBinding::fromString (const CompString &str)
{
    CompString   sStr;
    unsigned int mods;
    size_t       pos, start = 0;
    KeySym	 keysym;

    if (!screen)
	return false;

    mods = stringToModifiers (str);

    pos = str.rfind ('>');
    if (pos != std::string::npos)
	start = pos + 1;

    while (start < str.size () && !isalnum (str[start]))
	start++;

    if (start == str.size ())
    {
	if (mods)
	{
	    mKeycode   = 0;
	    mModifiers = mods;

	    return true;
	}

	return false;
    }

    sStr   = str.substr (start);
    keysym = XStringToKeysym (sStr.c_str ());

    if (keysym != NoSymbol)
    {
	KeyCode keycode;

	keycode = XKeysymToKeycode (screen->dpy (), keysym);
	if (keycode)
	{
	    mKeycode   = keycode;
	    mModifiers = mods;

	    return true;
	}
    }

    if (sStr.compare (0, 2, "0x") == 0)
    {
	mKeycode   = strtol (sStr.c_str (), NULL, 0);
	mModifiers = mods;

	return true;
    }

    return false;
}

CompString
CompAction::KeyBinding::toString () const
{
    CompString binding;

    if (!screen)
	return "";

    binding = modifiersToString (mModifiers);

    if (mKeycode != 0)
    {
	KeySym keysym;
	char   *keyname;

	keysym  = XKeycodeToKeysym (screen->dpy (), mKeycode, 0);
	keyname = XKeysymToString (keysym);

	if (keyname)
	    binding += keyname;
	else
	    binding += compPrintf ("0x%x", mKeycode);
    }

    return binding;
}

CompAction::ButtonBinding::ButtonBinding () :
    mModifiers (0),
    mButton (0)
{
}

CompAction::ButtonBinding::ButtonBinding (const ButtonBinding& b) :
    mModifiers (b.mModifiers),
    mButton (b.mButton)
{
}

CompAction::ButtonBinding::ButtonBinding (int button, unsigned int modifiers) :
    mModifiers (modifiers),
    mButton (button)
{
}

unsigned int
CompAction::ButtonBinding::modifiers () const
{
    return mModifiers;
}

int
CompAction::ButtonBinding::button () const
{
    return mButton;
}

bool
CompAction::ButtonBinding::fromString (const CompString &str)
{
    unsigned int mods;
    size_t       pos, start = 0;

    mods = stringToModifiers (str);

    pos = str.rfind ('>');
    if (pos != std::string::npos)
	start = pos + 1;

    while (start < str.size () && !isalnum (str[start]))
	start++;

    if (start != str.size () && str.compare (start, 6, "Button") == 0)
    {
	int buttonNum;

	if (sscanf (str.substr (start + 6).c_str (), "%d", &buttonNum) == 1)
	{
	    mButton    = buttonNum;
	    mModifiers = mods;

	    return true;
	}
    }

    return false;
}

CompString
CompAction::ButtonBinding::toString () const
{
    CompString binding;

    if (!mModifiers && !mButton)
	return "";

    binding = modifiersToString (mModifiers);
    binding += compPrintf ("Button%d", mButton);

    return binding;
}

CompAction::CompAction () :
    priv (new PrivateAction ())
{
}

CompAction::CompAction (const CompAction & a) :
    priv (new PrivateAction (*a.priv))
{
}

CompAction::~CompAction ()
{
    delete priv;
}

CompAction::CallBack
CompAction::initiate ()
{
    return priv->initiate;
}

CompAction::CallBack
CompAction::terminate ()
{
    return priv->terminate;
}

void
CompAction::setInitiate (const CompAction::CallBack &initiate)
{
    priv->initiate = initiate;
}

void
CompAction::setTerminate (const CompAction::CallBack &terminate)
{
    priv->terminate = terminate;
}

CompAction::State
CompAction::state ()
{
    return priv->state;
}

CompAction::BindingType
CompAction::type ()
{
    return priv->type;
}

CompAction::KeyBinding &
CompAction::key ()
{
    return priv->key;
}

void
CompAction::setKey (const CompAction::KeyBinding &key)
{
    priv->key = key;

    if (key.modifiers () || key.keycode ())
	priv->type = CompAction::BindingTypeKey;
    else
	priv->type = CompAction::BindingTypeNone;
}

CompAction::ButtonBinding &
CompAction::button ()
{
    return priv->button;
}

void
CompAction::setButton (const CompAction::ButtonBinding &button)
{
    priv->button = button;

    if (button.modifiers () || button.button ())
    {
	if (priv->edgeMask)
	    priv->type = CompAction::BindingTypeEdgeButton;
	else
	    priv->type = CompAction::BindingTypeButton;
    }
    else
    {
	priv->type = CompAction::BindingTypeNone;
    }
}

unsigned int
CompAction::edgeMask ()
{
    return priv->edgeMask;
}

void
CompAction::setEdgeMask (unsigned int edge)
{
    priv->edgeMask = edge;

    if (priv->type == CompAction::BindingTypeEdgeButton ||
        priv->type == CompAction::BindingTypeButton)
    {
	if (priv->edgeMask)
	    priv->type = CompAction::BindingTypeEdgeButton;
	else
	    priv->type = CompAction::BindingTypeButton;
    }
}

bool
CompAction::bell ()
{
    return priv->bell;
}

void
CompAction::setBell (bool bell)
{
    priv->bell = bell;
}

void
CompAction::setState (CompAction::State state)
{
    priv->state = state;
}

void
CompAction::copyState (const CompAction &action)
{
    priv->initiate  = action.priv->initiate;
    priv->terminate = action.priv->terminate;
    priv->state     = action.priv->state;

    memcpy (&priv->priv, &action.priv->priv, sizeof (CompPrivate));
}

bool
CompAction::operator== (const CompAction& val)
{
    if (priv->state != val.priv->state)
	return false;
    if (priv->type != val.priv->type)
	return false;
    if (priv->key.modifiers () != val.priv->key.modifiers ())
	return false;
    if (priv->key.keycode () != val.priv->key.keycode ())
	return false;
    if (priv->button.modifiers () != val.priv->button.modifiers ())
	return false;
    if (priv->button.button () != val.priv->button.button ())
	return false;
    if (priv->bell != val.priv->bell)
	return false;
    if (priv->edgeMask != val.priv->edgeMask)
	return false;
    if (memcmp (&priv->priv, &val.priv->priv, sizeof (CompPrivate)) != 0)
	return false;

    return true;
}

CompAction &
CompAction::operator= (const CompAction &action)
{
    delete priv;
    priv = new PrivateAction (*action.priv);

    return *this;
}

bool
CompAction::keyFromString (const CompString &str)
{
    bool retval = priv->key.fromString (str);

    if (retval)
    {
	priv->type = CompAction::BindingTypeKey;
    }
    else
    {
	priv->type = CompAction::BindingTypeNone;
	if (str == "Disabled")
	    retval = true;
    }

    return retval;
}

bool
CompAction::buttonFromString (const CompString &str)
{
    bool retval = priv->button.fromString (str);

    if (retval)
    {
	priv->edgeMask = bindingStringToEdgeMask (str);
	if (priv->edgeMask)
	    priv->type = CompAction::BindingTypeEdgeButton;
	else
	    priv->type = CompAction::BindingTypeButton;
    }
    else
    {
	priv->type = CompAction::BindingTypeNone;
	if (str == "Disabled")
	    retval = true;
    }

    return retval;
}

bool
CompAction::edgeMaskFromString (const CompString &str)
{
    unsigned int edgeMask = 0;
    size_t       pos;

    for (int i = 0; i < SCREEN_EDGE_NUM; i++)
    {
	pos = 0;
	while ((pos = str.find (edgeToString (i), pos)) != std::string::npos)
	{
	    if (pos > 0 && isalnum (str[pos - 1]))
	    {
		pos++;
		continue;
	    }

	    pos += edgeToString (i).size ();

	    if (pos < str.size () && isalnum (str[pos]))
		continue;

	    edgeMask |= 1 << i;
	}
    }

    priv->edgeMask = edgeMask;

    return (edgeMask != 0 || str.empty ());
}

CompString
CompAction::keyToString ()
{
    CompString binding;

    binding = priv->key.toString ();
    if (!binding.size ())
	return "Disabled";

    return binding;
}

CompString
CompAction::buttonToString ()
{
    CompString binding, edge;

    binding = modifiersToString (priv->button.modifiers ());
    binding += edgeMaskToBindingString (priv->edgeMask);

    binding += compPrintf ("Button%d", priv->button.button ());

    if (!priv->button.button ())
	return "Disabled";

    return binding;
}

CompString
CompAction::edgeMaskToString ()
{
    CompString edge;

    for (int i = 0; i < SCREEN_EDGE_NUM; i++)
    {
	if (priv->edgeMask & (1 << i))
	{
	    if (!edge.empty ())
		edge += " | ";

	    edge += edgeToString (i);
	}
    }

    return edge;
}


CompString
CompAction::edgeToString (unsigned int edge)
{
    return edges[edge].name;
}

PrivateAction::PrivateAction () :
    initiate (),
    terminate (),
    state (0),
    type (0),
    key (),
    button (),
    bell (false),
    edgeMask (0)
{
    memset (&priv, 0, sizeof (CompPrivate));
}

PrivateAction::PrivateAction (const PrivateAction& a) :
    initiate (a.initiate),
    terminate (a.terminate),
    state (a.state),
    type (a.type),
    key (a.key),
    button (a.button),
    bell (a.bell),
    edgeMask (a.edgeMask)
{
    memcpy (&priv, &a.priv, sizeof (CompPrivate));
}
