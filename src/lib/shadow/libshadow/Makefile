#	$ssdlinux: Makefile,v 1.6 2004/06/16 23:06:56 kanoh Exp $

.include <bsd.own.mk>

LIB=		shadow
SRCS=		commonio.c encrypt.c fputsx.c \
		getdef.c getpass.c groupio.c gshadow.c lockpw.c nscd.c \
		port.c pwauth.c pwio.c rad64.c sgetgrent.c sgetpwent.c \
		sgroupio.c shadow.c shadowio.c utent.c
MKPIC=		yes
MKPICINSTALL=	no
MAN=		shadow.3 limits.5 login.access.5 login.defs.5 \
		passwd.5 porttime.5 shadow.5 suauth.5

DIST=		${.CURDIR}/../../../dist/shadow
.PATH:		${DIST}/lib ${DIST}/man

.include "${.CURDIR}/../Makefile.cflags"

.include <bsd.lib.mk>
