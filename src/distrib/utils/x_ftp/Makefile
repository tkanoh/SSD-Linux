#	$ssdlinux: Makefile,v 1.3 2004/02/12 11:49:59 yamagata Exp $

.include <bsd.own.mk>

PROG=		ftp
SRCS=		cmds.c cmdtab.c complete.c domacro.c fetch.c ftp.c main.c progressbar.c ruserpass.c util.c
SRCS+=		fgetln.c setprogname.c sl_init.c strlcat.c strlcpy.c strunvis.c strvis.c fparseln.c glob.c
MKMAN=		no

NOGCCERROR=	yes

DIST=		${.CURDIR}/../../../dist/tnftp
FTPSRC=		${.CURDIR}/../../../usr.bin/ftp
.PATH:		${DIST}/src ${DIST}/libnetbsd

CPPFLAGS=	-DNO_EDITCOMPLETE
CPPFLAGS+=	-DNO_USAGE
CPPFLAGS+=	-I${FTPSRC} -I${DIST}
CPPFLAGS+=	-I${DIST}/src -I${DIST}/libnetbsd

proginstall:

.include <bsd.prog.mk>
