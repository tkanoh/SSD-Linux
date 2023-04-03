#	$ssdlinux: Makefile,v 1.1.1.1 2002/05/02 13:37:11 kanoh Exp $

.include 	<bsd.own.mk>

LIB=		popt
SRCS=		findme.c popt.c poptconfig.c popthelp.c poptparse.c	

DIST=		${.CURDIR}/../../../dist/rsync
.PATH:		${DIST}/popt

CPPFLAGS+=	-I${.CURDIR}/../ -I${DIST}

libinstall::

.include <bsd.lib.mk>
