/*	$ssdlinux: Composite.h,v 1.1.1.1 2002/05/02 13:37:11 kanoh Exp $	*/
/* $Xorg: Composite.h,v 1.3 2000/08/17 19:46:09 cpqbld Exp $ */

/***********************************************************

Copyright 1987, 1988, 1998  The Open Group

All Rights Reserved.

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of The Open Group shall not be
used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization from The Open Group.


Copyright 1987, 1988 by Digital Equipment Corporation, Maynard, Massachusetts.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the name of Digital not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.  

DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/

#ifndef _XtComposite_h
#define _XtComposite_h

typedef struct _CompositeClassRec *CompositeWidgetClass;

typedef Cardinal (*XtOrderProc)(
#if NeedFunctionPrototypes
    Widget 	/* child */
#endif
);

_XFUNCPROTOBEGIN

extern void XtManageChildren(
#if NeedFunctionPrototypes
    WidgetList 		/* children */,
    Cardinal 		/* num_children */
#endif
);

extern void XtManageChild(
#if NeedFunctionPrototypes
    Widget 		/* child */
#endif
);

extern void XtUnmanageChildren(
#if NeedFunctionPrototypes
    WidgetList 		/* children */,
    Cardinal 		/* num_children */
#endif
);

extern void XtUnmanageChild(
#if NeedFunctionPrototypes
    Widget 		/* child */
#endif
);

typedef void (*XtDoChangeProc)(
#if NeedFunctionPrototypes
    Widget		/* composite_parent */,
    WidgetList		/* unmanage_children */,
    Cardinal *		/* num_unmanage_children */,
    WidgetList		/* manage_children */,
    Cardinal *		/* num_manage_children */,
    XtPointer		/* client_data */
#endif
);

extern void XtChangeManagedSet(
#if NeedFunctionPrototypes
    WidgetList		/* unmanage_children */,
    Cardinal		/* num_unmanage_children */,
    XtDoChangeProc	/* do_change_proc */,
    XtPointer		/* client_data */,
    WidgetList		/* manage_children */,
    Cardinal		/* num_manage_children */
#endif
);

_XFUNCPROTOEND

#ifndef COMPOSITE
externalref WidgetClass compositeWidgetClass;
#endif

#endif /* _XtComposite_h */
/* DON'T ADD STUFF AFTER THIS #endif */
