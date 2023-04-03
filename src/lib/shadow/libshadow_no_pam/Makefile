#	$ssdlinux: Makefile,v 1.4 2004/06/16 23:06:56 kanoh Exp $

.include <bsd.own.mk>

LIB=		shadow
SRCS=		commonio.c encrypt.c fputsx.c \
		getdef.c getpass.c groupio.c gshadow.c lockpw.c nscd.c \
		port.c pwauth.c pwio.c rad64.c sgetgrent.c sgetpwent.c \
		sgroupio.c shadow.c shadowio.c utent.c
MKPIC=		yes
MKPICINSTALL=	no
MKMAN=		no

DIST=		${.CURDIR}/../../../dist/shadow
.PATH:		${DIST}/lib ${DIST}/man

FORCE_NO_PAM=	yes
.include "${.CURDIR}/../Makefile.cflags"

libinstall::

.include <bsd.lib.mk>
