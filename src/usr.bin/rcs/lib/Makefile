#	$ssdlinux: Makefile,v 1.1 2002/05/13 08:07:50 kanoh Exp $
#	$NetBSD: Makefile,v 1.17 1999/03/13 23:19:06 lukem Exp $

# Define FSYNC_ALL to get slower but safer writes in case of crashes in
# the middle of CVS/RCS changes
CPPFLAGS+=-DFSYNC_ALL

.include <bsd.own.mk>		# for RCS_LOCALID

# If you wish to use a different Id token in addition to Id,
# set the variable RCS_LOCALID in mk.conf or environment.
.if defined(RCS_LOCALID)
CPPFLAGS+=-DLOCALID=\"${RCS_LOCALID}\"
.endif

LIB=	rcs
SRCS=	maketime.c merger.c partime.c rcsedit.c rcsfcmp.c rcsfnms.c rcsgen.c \
	rcskeep.c rcskeys.c rcslex.c rcsmap.c rcsrev.c rcssyn.c rcstime.c \
	rcsutil.c version.c

MKLINT=	no
MKPIC=	no
MKPROFILE=no
NOGCCERROR=yes

# only needed during build
libinstall::

.include <bsd.lib.mk>
