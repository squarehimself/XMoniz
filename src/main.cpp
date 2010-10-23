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

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <compiz.h>

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#include <core/core.h>
#include "privatescreen.h"

char *programName;
char **programArgv;
int  programArgc;

char *backgroundImage = NULL;

bool shutDown = false;
bool restartSignal = false;

CompWindow *lastFoundWindow = 0;

bool replaceCurrentWm = false;
bool indirectRendering = false;
bool noDetection = false;
bool useDesktopHints = false;
bool debugOutput = false;
bool useCow = true;

unsigned int pluginClassHandlerIndex = 0;

static void
usage (void)
{
    printf ("Usage: %s "
	    "[--replace] "
	    "[--display DISPLAY]\n       "
	    "[--indirect-rendering] "
	    "[--sm-disable] "
	    "[--sm-client-id ID]\n       "
	    "[--bg-image PNG] "
	    "[--no-detection] "
	    "[--keep-desktop-hints]\n       "
	    "[--use-root-window] "
	    "[--debug] "
	    "[--version] "
	    "[--help] "
	    "[PLUGIN]...\n",
	    programName);
}

static void
signalHandler (int sig)
{
    int status;

    switch (sig) {
    case SIGCHLD:
	waitpid (-1, &status, WNOHANG | WUNTRACED);
	break;
    case SIGHUP:
	restartSignal = true;
	break;
    case SIGINT:
    case SIGTERM:
	shutDown = true;
    default:
	break;
    }
}

int
main (int argc, char **argv)
{
    char                    *displayName = 0;
    std::vector<CompString> plugins;
    int	                    i;
    bool                    disableSm = false;
    char                    *clientId = NULL;

    programName = argv[0];
    programArgc = argc;
    programArgv = argv;

    signal (SIGHUP, signalHandler);
    signal (SIGCHLD, signalHandler);
    signal (SIGINT, signalHandler);
    signal (SIGTERM, signalHandler);

    for (i = 1; i < argc; i++)
    {
	if (!strcmp (argv[i], "--help"))
	{
	    usage ();
	    return 0;
	}
	else if (!strcmp (argv[i], "--version"))
	{
	    printf (PACKAGE_STRING "\n");
	    return 0;
	}
	else if (!strcmp (argv[i], "--debug"))
	{
	    debugOutput = true;
	}
	else if (!strcmp (argv[i], "--display"))
	{
	    if (i + 1 < argc)
		displayName = argv[++i];
	}
	else if (!strcmp (argv[i], "--indirect-rendering"))
	{
	    indirectRendering = true;
	}
	else if (!strcmp (argv[i], "--keep-desktop-hints"))
	{
	    useDesktopHints = true;
	}
	else if (!strcmp (argv[i], "--use-root-window"))
	{
	    useCow = false;
	}
	else if (!strcmp (argv[i], "--replace"))
	{
	    replaceCurrentWm = true;
	}
	else if (!strcmp (argv[i], "--sm-disable"))
	{
	    disableSm = true;
	}
	else if (!strcmp (argv[i], "--sm-client-id"))
	{
	    if (i + 1 < argc)
		clientId = argv[++i];
	}
	else if (!strcmp (argv[i], "--no-detection"))
	{
	    noDetection = true;
	}
	else if (!strcmp (argv[i], "--bg-image"))
	{
	    if (i + 1 < argc)
		backgroundImage = argv[++i];
	}
	else if (*argv[i] == '-')
	{
	    compLogMessage ("core", CompLogLevelWarn,
			    "Unknown option '%s'\n", argv[i]);
	}
	else
	{
	    plugins.push_back (argv[i]);
	}
    }

    screen = new CompScreen ();
    if (!screen)
	return 1;

    modHandler = new ModifierHandler ();

    if (!modHandler)
	return 1;

    if (!plugins.empty ())
    {
	CompOption::Value::Vector list;
        CompOption::Value         value;
	CompOption                *o = screen->getOption ("active_plugins");

	foreach (CompString &str, plugins)
	{
	    value.set (str);
	    list.push_back (value);
	}

	value.set (CompOption::TypeString, list);

	if (o)
	    o->set (value);
    }

    if (!screen->init (displayName))
	return 1;

    modHandler->updateModifierMappings ();

    if (!disableSm)
	CompSession::init (clientId);

    screen->eventLoop ();

    if (!disableSm)
	CompSession::close ();

    delete screen;
    delete modHandler;

    if (restartSignal)
    {
	execvp (programName, programArgv);
	return 1;
    }

    return 0;
}
