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

#include <compiz.h>

#include <cstring>
#include <cstdarg>
#include <cstdio>

CompString compPrintf (const char *format, ...)
{
    va_list    ap;
    CompString rv;

    va_start (ap, format);
    rv = compPrintf (format, ap);
    va_end (ap);

    return rv;
}

CompString compPrintf (const char *format, va_list ap)
{
    va_list      aq;
    unsigned int size = strlen (format) + 1;
    int          n;
    char         *str;

    if (!format)
	return CompString ("");

    str = new char[size];

    if (!str)
	return CompString ("");

    while (1)
    {
	/* Try to print in the allocated space. */
	va_copy (aq, ap);
	n = vsnprintf (str, size, format, aq);
	va_end (aq);

	/* If that worked, leave the loop. */
	if (n > -1 && n < (int) size)
	    break;

	/* Else try again with more space. */
	if (n > -1)       /* glibc 2.1 */
	    size = n + 1; /* precisely what is needed */
	else              /* glibc 2.0 */
	    size++;       /* one more than the old size */

	delete [] str;
	str = new char[size];

	if (!str)
	{
	    return CompString ("");
	}
    }

    CompString rv (str);
    delete [] str;
    return rv;
}
