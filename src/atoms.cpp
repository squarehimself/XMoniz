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

#include <core/atoms.h>

namespace Atoms {
    Atom supported;
    Atom supportingWmCheck;

    Atom utf8String;

    Atom wmName;

    Atom winType;
    Atom winTypeDesktop;
    Atom winTypeDock;
    Atom winTypeToolbar;
    Atom winTypeMenu;
    Atom winTypeUtil;
    Atom winTypeSplash;
    Atom winTypeDialog;
    Atom winTypeNormal;
    Atom winTypeDropdownMenu;
    Atom winTypePopupMenu;
    Atom winTypeTooltip;
    Atom winTypeNotification;
    Atom winTypeCombo;
    Atom winTypeDnd;

    Atom winOpacity;
    Atom winBrightness;
    Atom winSaturation;
    Atom winActive;
    Atom winDesktop;

    Atom workarea;

    Atom desktopViewport;
    Atom desktopGeometry;
    Atom currentDesktop;
    Atom numberOfDesktops;

    Atom winState;
    Atom winStateModal;
    Atom winStateSticky;
    Atom winStateMaximizedVert;
    Atom winStateMaximizedHorz;
    Atom winStateShaded;
    Atom winStateSkipTaskbar;
    Atom winStateSkipPager;
    Atom winStateHidden;
    Atom winStateFullscreen;
    Atom winStateAbove;
    Atom winStateBelow;
    Atom winStateDemandsAttention;
    Atom winStateDisplayModal;

    Atom winActionMove;
    Atom winActionResize;
    Atom winActionStick;
    Atom winActionMinimize;
    Atom winActionMaximizeHorz;
    Atom winActionMaximizeVert;
    Atom winActionFullscreen;
    Atom winActionClose;
    Atom winActionShade;
    Atom winActionChangeDesktop;
    Atom winActionAbove;
    Atom winActionBelow;

    Atom wmAllowedActions;

    Atom wmStrut;
    Atom wmStrutPartial;

    Atom wmUserTime;

    Atom wmIcon;
    Atom wmIconGeometry;

    Atom clientList;
    Atom clientListStacking;

    Atom frameExtents;
    Atom frameWindow;

    Atom wmState;
    Atom wmChangeState;
    Atom wmProtocols;
    Atom wmClientLeader;

    Atom wmDeleteWindow;
    Atom wmTakeFocus;
    Atom wmPing;
    Atom wmSyncRequest;

    Atom wmSyncRequestCounter;

    Atom wmFullscreenMonitors;

    Atom closeWindow;
    Atom wmMoveResize;
    Atom moveResizeWindow;
    Atom restackWindow;

    Atom showingDesktop;

    Atom xBackground[2];

    Atom toolkitAction;
    Atom toolkitActionWindowMenu;
    Atom toolkitActionForceQuitDialog;

    Atom mwmHints;

    Atom xdndAware;
    Atom xdndEnter;
    Atom xdndLeave;
    Atom xdndPosition;
    Atom xdndStatus;
    Atom xdndDrop;

    Atom manager;
    Atom targets;
    Atom multiple;
    Atom timestamp;
    Atom version;
    Atom atomPair;

    Atom startupId;

    void init (Display *dpy)
    {
	supported         = XInternAtom (dpy, "_NET_SUPPORTED", 0);
	supportingWmCheck = XInternAtom (dpy, "_NET_SUPPORTING_WM_CHECK", 0);

	utf8String = XInternAtom (dpy, "UTF8_STRING", 0);

	wmName = XInternAtom (dpy, "_NET_WM_NAME", 0);

	winType        = XInternAtom (dpy, "_NET_WM_WINDOW_TYPE", 0);
	winTypeDesktop = XInternAtom (dpy, "_NET_WM_WINDOW_TYPE_DESKTOP",
					     0);
	winTypeDock    = XInternAtom (dpy, "_NET_WM_WINDOW_TYPE_DOCK", 0);
	winTypeToolbar = XInternAtom (dpy, "_NET_WM_WINDOW_TYPE_TOOLBAR",
					     0);
	winTypeMenu    = XInternAtom (dpy, "_NET_WM_WINDOW_TYPE_MENU", 0);
	winTypeUtil    = XInternAtom (dpy, "_NET_WM_WINDOW_TYPE_UTILITY",
					     0);
	winTypeSplash  = XInternAtom (dpy, "_NET_WM_WINDOW_TYPE_SPLASH", 0);
	winTypeDialog  = XInternAtom (dpy, "_NET_WM_WINDOW_TYPE_DIALOG", 0);
	winTypeNormal  = XInternAtom (dpy, "_NET_WM_WINDOW_TYPE_NORMAL", 0);

	winTypeDropdownMenu =
	    XInternAtom (dpy, "_NET_WM_WINDOW_TYPE_DROPDOWN_MENU", 0);
	winTypePopupMenu    =
	    XInternAtom (dpy, "_NET_WM_WINDOW_TYPE_POPUP_MENU", 0);
	winTypeTooltip      =
	    XInternAtom (dpy, "_NET_WM_WINDOW_TYPE_TOOLTIP", 0);
	winTypeNotification =
	    XInternAtom (dpy, "_NET_WM_WINDOW_TYPE_NOTIFICATION", 0);
	winTypeCombo        =
	    XInternAtom (dpy, "_NET_WM_WINDOW_TYPE_COMBO", 0);
	winTypeDnd          =
	    XInternAtom (dpy, "_NET_WM_WINDOW_TYPE_DND", 0);

	winOpacity    = XInternAtom (dpy, "_NET_WM_WINDOW_OPACITY", 0);
	winBrightness = XInternAtom (dpy, "_NET_WM_WINDOW_BRIGHTNESS", 0);
	winSaturation = XInternAtom (dpy, "_NET_WM_WINDOW_SATURATION", 0);

	winActive  = XInternAtom (dpy, "_NET_ACTIVE_WINDOW", 0);
	winDesktop = XInternAtom (dpy, "_NET_WM_DESKTOP", 0);
	workarea   = XInternAtom (dpy, "_NET_WORKAREA", 0);

	desktopViewport  = XInternAtom (dpy, "_NET_DESKTOP_VIEWPORT", 0);
	desktopGeometry  = XInternAtom (dpy, "_NET_DESKTOP_GEOMETRY", 0);
	currentDesktop   = XInternAtom (dpy, "_NET_CURRENT_DESKTOP", 0);
	numberOfDesktops = XInternAtom (dpy, "_NET_NUMBER_OF_DESKTOPS", 0);

	winState	             = XInternAtom (dpy, "_NET_WM_STATE", 0);
	winStateModal            =
	    XInternAtom (dpy, "_NET_WM_STATE_MODAL", 0);
	winStateSticky           =
	    XInternAtom (dpy, "_NET_WM_STATE_STICKY", 0);
	winStateMaximizedVert    =
	    XInternAtom (dpy, "_NET_WM_STATE_MAXIMIZED_VERT", 0);
	winStateMaximizedHorz    =
	    XInternAtom (dpy, "_NET_WM_STATE_MAXIMIZED_HORZ", 0);
	winStateShaded           =
	    XInternAtom (dpy, "_NET_WM_STATE_SHADED", 0);
	winStateSkipTaskbar      =
	    XInternAtom (dpy, "_NET_WM_STATE_SKIP_TASKBAR", 0);
	winStateSkipPager        =
	    XInternAtom (dpy, "_NET_WM_STATE_SKIP_PAGER", 0);
	winStateHidden           =
	    XInternAtom (dpy, "_NET_WM_STATE_HIDDEN", 0);
	winStateFullscreen       =
	    XInternAtom (dpy, "_NET_WM_STATE_FULLSCREEN", 0);
	winStateAbove            =
	    XInternAtom (dpy, "_NET_WM_STATE_ABOVE", 0);
	winStateBelow            =
	    XInternAtom (dpy, "_NET_WM_STATE_BELOW", 0);
	winStateDemandsAttention =
	    XInternAtom (dpy, "_NET_WM_STATE_DEMANDS_ATTENTION", 0);
	winStateDisplayModal     =
	    XInternAtom (dpy, "_NET_WM_STATE_DISPLAY_MODAL", 0);

	winActionMove          = XInternAtom (dpy, "_NET_WM_ACTION_MOVE", 0);
	winActionResize        =
	    XInternAtom (dpy, "_NET_WM_ACTION_RESIZE", 0);
	winActionStick         =
	    XInternAtom (dpy, "_NET_WM_ACTION_STICK", 0);
	winActionMinimize      =
	    XInternAtom (dpy, "_NET_WM_ACTION_MINIMIZE", 0);
	winActionMaximizeHorz  =
	    XInternAtom (dpy, "_NET_WM_ACTION_MAXIMIZE_HORZ", 0);
	winActionMaximizeVert  =
	    XInternAtom (dpy, "_NET_WM_ACTION_MAXIMIZE_VERT", 0);
	winActionFullscreen    =
	    XInternAtom (dpy, "_NET_WM_ACTION_FULLSCREEN", 0);
	winActionClose         =
	    XInternAtom (dpy, "_NET_WM_ACTION_CLOSE", 0);
	winActionShade         =
	    XInternAtom (dpy, "_NET_WM_ACTION_SHADE", 0);
	winActionChangeDesktop =
	    XInternAtom (dpy, "_NET_WM_ACTION_CHANGE_DESKTOP", 0);
	winActionAbove         =
	    XInternAtom (dpy, "_NET_WM_ACTION_ABOVE", 0);
	winActionBelow         =
	    XInternAtom (dpy, "_NET_WM_ACTION_BELOW", 0);

	wmAllowedActions = XInternAtom (dpy, "_NET_WM_ALLOWED_ACTIONS", 0);

	wmStrut        = XInternAtom (dpy, "_NET_WM_STRUT", 0);
	wmStrutPartial = XInternAtom (dpy, "_NET_WM_STRUT_PARTIAL", 0);

	wmUserTime = XInternAtom (dpy, "_NET_WM_USER_TIME", 0);

	wmIcon         = XInternAtom (dpy,"_NET_WM_ICON", 0);
	wmIconGeometry = XInternAtom (dpy, "_NET_WM_ICON_GEOMETRY", 0);

	clientList         = XInternAtom (dpy, "_NET_CLIENT_LIST", 0);
	clientListStacking =
	    XInternAtom (dpy, "_NET_CLIENT_LIST_STACKING", 0);

	frameExtents = XInternAtom (dpy, "_NET_FRAME_EXTENTS", 0);
	frameWindow  = XInternAtom (dpy, "_NET_FRAME_WINDOW", 0);

	wmState        = XInternAtom (dpy, "WM_STATE", 0);
	wmChangeState  = XInternAtom (dpy, "WM_CHANGE_STATE", 0);
	wmProtocols    = XInternAtom (dpy, "WM_PROTOCOLS", 0);
	wmClientLeader = XInternAtom (dpy, "WM_CLIENT_LEADER", 0);

	wmDeleteWindow = XInternAtom (dpy, "WM_DELETE_WINDOW", 0);
	wmTakeFocus    = XInternAtom (dpy, "WM_TAKE_FOCUS", 0);
	wmPing         = XInternAtom (dpy, "_NET_WM_PING", 0);
	wmSyncRequest  = XInternAtom (dpy, "_NET_WM_SYNC_REQUEST", 0);

	wmSyncRequestCounter =
	    XInternAtom (dpy, "_NET_WM_SYNC_REQUEST_COUNTER", 0);

	wmFullscreenMonitors =
	    XInternAtom (dpy, "_NET_WM_FULLSCREEN_MONITORS", 0);

	closeWindow      = XInternAtom (dpy, "_NET_CLOSE_WINDOW", 0);
	wmMoveResize     = XInternAtom (dpy, "_NET_WM_MOVERESIZE", 0);
	moveResizeWindow = XInternAtom (dpy, "_NET_MOVERESIZE_WINDOW", 0);
	restackWindow    = XInternAtom (dpy, "_NET_RESTACK_WINDOW", 0);

	showingDesktop = XInternAtom (dpy, "_NET_SHOWING_DESKTOP", 0);

	xBackground[0] = XInternAtom (dpy, "_XSETROOT_ID", 0);
	xBackground[1] = XInternAtom (dpy, "_XROOTPMAP_ID", 0);

	toolkitAction                =
	    XInternAtom (dpy, "_COMPIZ_TOOLKIT_ACTION", 0);
	toolkitActionWindowMenu      =
	    XInternAtom (dpy, "_COMPIZ_TOOLKIT_ACTION_WINDOW_MENU", 0);
	toolkitActionForceQuitDialog =
	    XInternAtom (dpy, "_COMPIZ_TOOLKIT_ACTION_FORCE_QUIT_DIALOG", 0);

	mwmHints = XInternAtom (dpy, "_MOTIF_WM_HINTS", 0);

	xdndAware    = XInternAtom (dpy, "XdndAware", 0);
	xdndEnter    = XInternAtom (dpy, "XdndEnter", 0);
	xdndLeave    = XInternAtom (dpy, "XdndLeave", 0);
	xdndPosition = XInternAtom (dpy, "XdndPosition", 0);
	xdndStatus   = XInternAtom (dpy, "XdndStatus", 0);
	xdndDrop     = XInternAtom (dpy, "XdndDrop", 0);

	manager   = XInternAtom (dpy, "MANAGER", 0);
	targets   = XInternAtom (dpy, "TARGETS", 0);
	multiple  = XInternAtom (dpy, "MULTIPLE", 0);
	timestamp = XInternAtom (dpy, "TIMESTAMP", 0);
	version   = XInternAtom (dpy, "VERSION", 0);
	atomPair  = XInternAtom (dpy, "ATOM_PAIR", 0);

	startupId = XInternAtom (dpy, "_NET_STARTUP_ID", 0);
    }
};
