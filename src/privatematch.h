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

#ifndef _PRIVATEMATCH_H
#define _PRIVATEMATCH_H

#include <core/match.h>
#include <boost/shared_ptr.hpp>

#define MATCH_OP_AND_MASK (1 << 0)
#define MATCH_OP_NOT_MASK (1 << 1)

class MatchOp {
    public:
	typedef enum {
	    TypeNone,
	    TypeGroup,
	    TypeExp
	} Type;

	typedef std::list<MatchOp *> List;

	MatchOp ();
	virtual ~MatchOp ();

	virtual Type type () { return TypeNone; };

	unsigned int flags;
};

class MatchExpOp : public MatchOp {
    public:
	MatchExpOp ();
	MatchExpOp (const MatchExpOp &);

	MatchOp::Type type () { return MatchOp::TypeExp; };

	CompString	      value;

	boost::shared_ptr<CompMatch::Expression> e;
};

class MatchGroupOp : public MatchOp {
    public:
	MatchGroupOp ();
	~MatchGroupOp ();
	MatchGroupOp (const MatchGroupOp &);

	MatchGroupOp & operator= (const MatchGroupOp &);

	MatchOp::Type type () { return MatchOp::TypeGroup; };

	MatchOp::List op;
};

class PrivateMatch {
    public:
	PrivateMatch ();

    public:
	MatchGroupOp op;
};

#endif
