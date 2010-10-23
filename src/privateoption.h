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

#ifndef _PRIVATEOPTION_H
#define _PRIVATEOPTION_H

#include <vector>

#include <core/action.h>
#include <core/match.h>
#include <core/screen.h>

typedef struct _CompOptionIntRestriction {
    int min;
    int max;
} IntRestriction;

typedef struct _CompOptionFloatRestriction {
    float min;
    float max;
    float precision;
} FloatRestriction;

typedef union {
    IntRestriction    i;
    FloatRestriction  f;
} RestrictionUnion;

class PrivateRestriction {
    public:
	CompOption::Type type;
	RestrictionUnion rest;
};

typedef union {
    bool	   b;
    int		   i;
    float	   f;
    unsigned short c[4];
} ValueUnion;

class PrivateValue {
    public:
	PrivateValue ();
	PrivateValue (const PrivateValue&);

	void reset ();
	bool checkType (CompOption::Type refType);

	CompOption::Type          type;
	ValueUnion                value;
	CompString                string;
	CompAction                action;
	CompMatch                 match;
	CompOption::Type          listType;
	CompOption::Value::Vector list;
};

class PrivateOption
{
    public:
	PrivateOption ();
	PrivateOption (const PrivateOption &);

	CompString              name;
	CompOption::Type        type;
	CompOption::Value       value;
	CompOption::Restriction rest;
};

#endif
