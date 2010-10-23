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

#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <math.h>

#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH

#include <core/core.h>
#include <core/option.h>
#include "privateoption.h"

CompOption::Vector noOptions (0);

CompOption::Value::Value () :
    priv (new PrivateValue ())
{
}

CompOption::Value::Value (const Value &v) :
    priv (new PrivateValue (*v.priv))
{
}

CompOption::Value::~Value ()
{
    delete priv;
}

CompOption::Value::Value (const bool b) :
    priv (new PrivateValue ())
{
    set (b);
}

CompOption::Value::Value (const int i) :
    priv (new PrivateValue ())
{
    set (i);
}

CompOption::Value::Value (const float f) :
    priv (new PrivateValue ())
{
    set (f);
}

CompOption::Value::Value (const unsigned short *color) :
    priv (new PrivateValue ())
{
    set (color);
}

CompOption::Value::Value (const CompString& s) :
    priv (new PrivateValue ())
{
    set (s);
}

CompOption::Value::Value (const char *s) :
    priv (new PrivateValue ())
{
    set (s);
}


CompOption::Value::Value (const CompMatch& m) :
    priv (new PrivateValue ())
{
    set (m);
}

CompOption::Value::Value (const CompAction& a) :
    priv (new PrivateValue ())
{
    set (a);
}

CompOption::Value::Value (CompOption::Type type, const Vector& l) :
    priv (new PrivateValue ())
{
    set (type, l);
}

CompOption::Type
CompOption::Value::type () const
{
    return priv->type;
}

void
CompOption::Value::set (const bool b)
{
    priv->reset ();
    priv->type = CompOption::TypeBool;
    priv->value.b = b;
}

void
CompOption::Value::set (const int i)
{
    priv->reset ();
    priv->type = CompOption::TypeInt;
    priv->value.i = i;
}

void
CompOption::Value::set (const float f)
{
    priv->reset ();
    priv->type = CompOption::TypeFloat;
    priv->value.f = f;
}

void
CompOption::Value::set (const unsigned short *color)
{
    priv->reset ();
    priv->type = CompOption::TypeColor;
    priv->value.c[0] = color[0];
    priv->value.c[1] = color[1];
    priv->value.c[2] = color[2];
    priv->value.c[3] = color[3];
}

void
CompOption::Value::set (const CompString& s)
{
    priv->reset ();
    priv->type = CompOption::TypeString;
    priv->string = s;
}

void
CompOption::Value::set (const char *s)
{
    priv->reset ();
    priv->type = CompOption::TypeString;
    priv->string = CompString (s);
}

void
CompOption::Value::set (const CompMatch& m)
{
    priv->reset ();
    priv->type = CompOption::TypeMatch;
    priv->match = m;
}

void
CompOption::Value::set (const CompAction& a)
{
    priv->reset ();
    priv->type = CompOption::TypeAction;
    priv->action = a;
}

void
CompOption::Value::set (CompOption::Type type, const Vector& l)
{
    priv->reset ();
    priv->type = CompOption::TypeList;
    priv->list = l;
    priv->listType = type;
}

static bool
checkIsAction (CompOption::Type type)
{
    switch (type) {
	case CompOption::TypeAction:
	case CompOption::TypeKey:
	case CompOption::TypeButton:
	case CompOption::TypeEdge:
	case CompOption::TypeBell:
	    return true;
	default:
	    break;
    }

    return false;
}

bool
CompOption::Value::b ()
{
    if (!priv->checkType (CompOption::TypeBool))
	return false;

    return priv->value.b;
}

int
CompOption::Value::i ()
{
    if (!priv->checkType (CompOption::TypeInt))
	return 0;

    return priv->value.i;
}

float
CompOption::Value::f ()
{
    if (!priv->checkType (CompOption::TypeFloat))
	return 0.0;

    return priv->value.f;
}

static unsigned short defaultColor[4] = { 0x0, 0x0, 0x0, 0xffff};

unsigned short *
CompOption::Value::c ()
{
    if (!priv->checkType (CompOption::TypeColor))
	return reinterpret_cast<unsigned short *> (defaultColor);

    return priv->value.c;
}

CompString
CompOption::Value::s ()
{
    if (!priv->checkType (CompOption::TypeString))
	return "";

    return priv->string;
}

CompMatch &
CompOption::Value::match ()
{
    priv->checkType (CompOption::TypeMatch);

    return priv->match;
}

CompAction &
CompOption::Value::action ()
{
    priv->checkType (priv->type);

    if (!checkIsAction (priv->type))
	compLogMessage ("core", CompLogLevelWarn,
			"CompOption::Value not an action");

    return priv->action;
}

CompOption::Type
CompOption::Value::listType ()
{
    priv->checkType (CompOption::TypeList);

    return priv->listType;
}

CompOption::Value::Vector &
CompOption::Value::list ()
{
    priv->checkType (CompOption::TypeList);

    return priv->list;
}

CompOption::Value::operator bool ()
{
    return b ();
}

CompOption::Value::operator int ()
{
    return i ();
}

CompOption::Value::operator float ()
{
    return f ();
}

CompOption::Value::operator unsigned short * ()
{
    return c ();
}

CompOption::Value::operator CompString ()
{
    return s ();
}

CompOption::Value::operator CompMatch & ()
{
    return match ();
}

CompOption::Value::operator CompAction & ()
{
    return action ();
}

CompOption::Value::operator CompAction * ()
{
    return &action ();
}

CompOption::Value::operator Type ()
{
    return listType ();
}

CompOption::Value::operator Vector & ()
{
    return list ();
}

bool
CompOption::Value::operator== (const CompOption::Value &val)
{
    if (priv->type != val.priv->type)
	return false;

    switch (priv->type)
    {
	case CompOption::TypeBool:
	    return priv->value.b == val.priv->value.b;
	    break;

	case CompOption::TypeInt:
	    return priv->value.i == val.priv->value.i;
	    break;

	case CompOption::TypeFloat:
	    return priv->value.f == val.priv->value.f;
	    break;

	case CompOption::TypeColor:
	    return (priv->value.c[0] == val.priv->value.c[0]) &&
		   (priv->value.c[1] == val.priv->value.c[1]) &&
		   (priv->value.c[2] == val.priv->value.c[2]) &&
		   (priv->value.c[3] == val.priv->value.c[3]);
	    break;

	case CompOption::TypeString:
	    return priv->string.compare (val.priv->string) == 0;
	    break;

	case CompOption::TypeMatch:
	    return priv->match == val.priv->match;
	    break;

	case CompOption::TypeAction:
	    return priv->action == val.priv->action;
	    break;

	case CompOption::TypeList:
	    if (priv->listType != val.priv->listType)
		return false;

	    if (priv->list.size () != val.priv->list.size ())
		return false;

	    for (unsigned int i = 0; i < priv->list.size (); i++)
		if (priv->list[i] != val.priv->list[i])
		    return false;

	    return true;
	    break;

	default:
	    break;
    }

    return true;
}

bool
CompOption::Value::operator!= (const CompOption::Value &val)
{
    return !(*this == val);
}

CompOption::Value &
CompOption::Value::operator= (const CompOption::Value &val)
{
    delete priv;
    priv = new PrivateValue (*val.priv);

    return *this;
}

PrivateValue::PrivateValue () :
    type (CompOption::TypeUnset),
    string (""),
    action (),
    match (),
    listType (CompOption::TypeUnset),
    list ()
{
    memset (&value, 0, sizeof (ValueUnion));
}

PrivateValue::PrivateValue (const PrivateValue& p) :
    type (p.type),
    string (p.string),
    action (p.action),
    match (p.match),
    listType (p.listType),
    list (p.list)
{
    memcpy (&value, &p.value, sizeof (ValueUnion));
}

bool
PrivateValue::checkType (CompOption::Type refType)
{
    if (type == CompOption::TypeUnset)
    {
	compLogMessage ("core", CompLogLevelWarn,
			"Value type is not yet set");
	return false;
    }

    if (type != refType)
    {
	compLogMessage ("core", CompLogLevelWarn,
			"Value type does not match (is %d, expected %d)",
			type, refType);
	return false;
    }

    return true;
}

void
PrivateValue::reset ()
{
    switch (type) {
	case CompOption::TypeString:
	    string = "";
	    break;
	case CompOption::TypeMatch:
	    match = CompMatch ();
	    break;
	case CompOption::TypeAction:
	    action = CompAction ();
	    break;
	case CompOption::TypeList:
	    list.clear ();
	    listType = CompOption::TypeBool;
	    break;
	default:
	    break;
    }
    type = CompOption::TypeBool;
}

CompOption::Restriction::Restriction () :
    priv (new PrivateRestriction ())
{
}

CompOption::Restriction::Restriction (const CompOption::Restriction::Restriction &r) :
    priv (new PrivateRestriction (*r.priv))
{
}

CompOption::Restriction::~Restriction ()
{
    delete priv;
}

int
CompOption::Restriction::iMin ()
{
    if (priv->type == CompOption::TypeInt)
	return priv->rest.i.min;
    return MINSHORT;
}

int
CompOption::Restriction::iMax ()
{
    if (priv->type == CompOption::TypeInt)
	return priv->rest.i.max;
    return MAXSHORT;
}

float
CompOption::Restriction::fMin ()
{
    if (priv->type == CompOption::TypeFloat)
	return priv->rest.f.min;
    return MINSHORT;
}

float
CompOption::Restriction::fMax ()
{
    if (priv->type == CompOption::TypeFloat)
	return priv->rest.f.min;
    return MINSHORT;
}

float
CompOption::Restriction::fPrecision ()
{
    if (priv->type == CompOption::TypeFloat)
	return priv->rest.f.precision;
    return 0.1f;
}


void
CompOption::Restriction::set (int min, int max)
{
    priv->type = CompOption::TypeInt;
    priv->rest.i.min = min;
    priv->rest.i.max = max;
}

void
CompOption::Restriction::set (float min, float max, float precision)
{
    priv->type = CompOption::TypeFloat;
    priv->rest.f.min       = min;
    priv->rest.f.max       = max;
    priv->rest.f.precision = precision;
}

bool
CompOption::Restriction::inRange (int i)
{
    if (priv->type != CompOption::TypeInt)
	return true;
    if (i < priv->rest.i.min)
	return false;
    if (i > priv->rest.i.max)
	return false;
    return true;
}

bool
CompOption::Restriction::inRange (float f)
{
    if (priv->type != CompOption::TypeFloat)
	return true;
    if (f < priv->rest.f.min)
	return false;
    if (f > priv->rest.f.max)
	return false;
    return true;
}

CompOption::Restriction &
CompOption::Restriction::operator= (const CompOption::Restriction &rest)
{
    delete priv;
    priv = new PrivateRestriction (*rest.priv);
    return *this;
}

CompOption *
CompOption::Class::getOption (const CompString &name)
{
    CompOption *o = CompOption::findOption (getOptions (), name);
    return o;
}

CompOption *
CompOption::findOption (CompOption::Vector &options,
			CompString         name,
			unsigned int       *index)
{
    unsigned int i;

    for (i = 0; i < options.size (); i++)
    {
	if (options[i].priv->name == name)
	{
	    if (index)
		*index = i;

	    return &options[i];
	}
    }

    return NULL;
}

CompOption::CompOption () :
    priv (new PrivateOption ())
{
}

CompOption::CompOption (const CompOption &o) :
    priv (new PrivateOption (*o.priv))
{
}

CompOption::CompOption (CompString name, CompOption::Type type) :
    priv (new PrivateOption ())
{
    setName (name, type);
}

static void
finiScreenOptionValue (CompScreen        *s,
		       CompOption::Value &v,
		       CompOption::Type  type)
{
    switch (type) {
	case CompOption::TypeAction:
	case CompOption::TypeKey:
	case CompOption::TypeButton:
	case CompOption::TypeEdge:
	case CompOption::TypeBell:
	    if (v.action ().state () & CompAction::StateAutoGrab)
		s->removeAction (&v.action ());
	    break;

	case CompOption::TypeList:
	    foreach (CompOption::Value &val, v.list ())
		finiScreenOptionValue (s, val, v.listType ());
	    break;

	default:
	    break;
    }
}

static void
finiOptionValue (CompOption::Value &v,
		 CompOption::Type  type)
{
    switch (type) {
	case CompOption::TypeAction:
	case CompOption::TypeKey:
	case CompOption::TypeButton:
	case CompOption::TypeEdge:
	case CompOption::TypeBell:
	    if (v.action ().state () & CompAction::StateAutoGrab && screen)
		screen->removeAction (&v.action ());
	    break;

	case CompOption::TypeList:
	    foreach (CompOption::Value &val, v.list ())
		finiOptionValue (val, v.listType ());
	    break;

	default:
	    break;
    }
}

CompOption::~CompOption ()
{
    finiOptionValue (priv->value, priv->type);
    delete priv;
}

void
CompOption::setName (CompString name, CompOption::Type type)
{
    priv->name = name;
    priv->type = type;
}

CompString
CompOption::name ()
{
    return priv->name;
}

CompOption::Type
CompOption::type ()
{
    return priv->type;
}

CompOption::Value &
CompOption::value ()
{
    return priv->value;
}

CompOption::Restriction &
CompOption::rest ()
{
    return priv->rest;
}

bool
CompOption::set (CompOption::Value &val)
{
    if (isAction () && priv->type != CompOption::TypeAction)
	val.action ().copyState (priv->value.action ());

    if (priv->type != val.type () &&
	(!isAction () || !checkIsAction (val.type ())))
    {
	compLogMessage ("core", CompLogLevelWarn,
			"Can't set Value with type %d to "
			"option \"%s\" with type %d",
			val.type (), priv->name.c_str (), priv->type);
	return false;
    }

    if (priv->value == val)
	return false;

    if (isAction () &&
        priv->value.action ().state () & CompAction::StateAutoGrab && screen)
    {
	if (!screen->addAction (&val.action ()))
	    return false;
	else
	    screen->removeAction (&priv->value.action ());
    }

    switch (priv->type)
    {
	case CompOption::TypeInt:
	    if (!priv->rest.inRange (val.i ()))
		return false;
	    break;

	case CompOption::TypeFloat:
	{
	    float v, p;
	    int sign = (val.f () < 0 ? -1 : 1);

	    if (!priv->rest.inRange (val.f ()))
		return false;

	    p = 1.0f / priv->rest.fPrecision ();
	    v = ((int) (val.f () * p + sign * 0.5f)) / p;

	    priv->value.set (v);
	    return true;
	}

	case CompOption::TypeAction:
	    return false;

	case CompOption::TypeKey:
	    if (val.action ().type () == value().action ().type () && 
		!(val.action ().type () & CompAction::BindingTypeKey))
		return false;
	    break;

	case CompOption::TypeButton:
	    if (val.action ().type () == value().action ().type () && 
		!(val.action ().type () & (CompAction::BindingTypeButton |
					   CompAction::BindingTypeEdgeButton)))
		return false;
	    break;

	default:
	    break;
    }

    priv->value = val;

    return true;
}

bool
CompOption::isAction ()
{
    return checkIsAction (priv->type);
}

CompOption &
CompOption::operator= (const CompOption &option)
{
    delete priv;
    priv = new PrivateOption (*option.priv);
    return *this;
}

bool
CompOption::getBoolOptionNamed (const Vector&     options,
				const CompString& name,
				bool              defaultValue)
{
    foreach (const CompOption &o, options)
	if (o.priv->type == CompOption::TypeBool && o.priv->name == name)
	    return o.priv->value.b ();

    return defaultValue;
}

int
CompOption::getIntOptionNamed (const Vector&     options,
			       const CompString& name,
			       int               defaultValue)
{
    foreach (const CompOption &o, options)
	if (o.priv->type == CompOption::TypeInt && o.priv->name == name)
	    return o.priv->value.i ();

    return defaultValue;
}

float
CompOption::getFloatOptionNamed (const Vector&     options,
				 const CompString& name,
				 const float&      defaultValue)
{
    foreach (const CompOption &o, options)
	if (o.priv->type == CompOption::TypeFloat && o.priv->name == name)
	    return o.priv->value.f ();

    return defaultValue;
}

CompString
CompOption::getStringOptionNamed (const Vector&     options,
				  const CompString& name,
				  const CompString& defaultValue)
{
    foreach (const CompOption &o, options)
	if (o.priv->type == CompOption::TypeString && o.priv->name == name)
	    return o.priv->value.s ();

    return defaultValue;
}

unsigned short *
CompOption::getColorOptionNamed (const Vector&        options,
				 const CompString&    name,
				 unsigned short       *defaultValue)
{
    foreach (const CompOption &o, options)
	if (o.priv->type == CompOption::TypeColor && o.priv->name == name)
	    return o.priv->value.c ();

    return defaultValue;
}

CompMatch
CompOption::getMatchOptionNamed (const Vector&     options,
				 const CompString& name,
				 const CompMatch&  defaultValue)
{
    foreach (const CompOption &o, options)
	if (o.priv->type == CompOption::TypeMatch && o.priv->name == name)
	    return o.priv->value.match ();

    return defaultValue;
}

bool
CompOption::stringToColor (CompString     color,
			   unsigned short *rgba)
{
    int c[4];

    if (sscanf (color.c_str (), "#%2x%2x%2x%2x",
		&c[0], &c[1], &c[2], &c[3]) == 4)
    {
	rgba[0] = c[0] << 8 | c[0];
	rgba[1] = c[1] << 8 | c[1];
	rgba[2] = c[2] << 8 | c[2];
	rgba[3] = c[3] << 8 | c[3];

	return true;
    }

    return false;
}

CompString
CompOption::colorToString (unsigned short *rgba)
{
    return compPrintf ("#%.2x%.2x%.2x%.2x", rgba[0] / 256, rgba[1] / 256,
					    rgba[2] / 256, rgba[3] / 256);
}

CompString
CompOption::typeToString (CompOption::Type type)
{
    switch (type) {
	case CompOption::TypeBool:
	    return "bool";
	case CompOption::TypeInt:
	    return "int";
	case CompOption::TypeFloat:
	    return "float";
	case CompOption::TypeString:
	    return "string";
	case CompOption::TypeColor:
	    return "color";
	case CompOption::TypeAction:
	    return "action";
	case CompOption::TypeKey:
	    return "key";
	case CompOption::TypeButton:
	    return "button";
	case CompOption::TypeEdge:
	    return "edge";
	case CompOption::TypeBell:
	    return "bell";
	case CompOption::TypeMatch:
	    return "match";
	case CompOption::TypeList:
	    return "list";
	default:
	    break;
    }

    return "unknown";
}

bool
CompOption::setOption (CompOption        &o,
		       CompOption::Value &value)
{
    return o.set (value);
}

PrivateOption::PrivateOption () :
    name (""),
    type (CompOption::TypeUnset),
    value (),
    rest ()
{
}

PrivateOption::PrivateOption (const PrivateOption &p) :
    name (p.name),
    type (p.type),
    value (p.value),
    rest (p.rest)
{
}

