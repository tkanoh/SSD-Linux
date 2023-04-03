#	$ssdlinux: Makefile,v 1.2 2005/01/05 03:33:11 yamagata Exp $

.include <bsd.own.mk>

PROG=		infokey
SRCS=		${PROG}.c key.c

CPPFLAGS+=	-I${DIST}/texinfo/info \
		-DINFODIR=\"/usr/pkg/info:/usr/X11R6/info:/usr/X11/info:/usr/local/info:/usr/share/info:/usr/info\"

.include <bsd.prog.mk>

.PATH: ${DIST}/texinfo/info ${DIST}/texinfo/doc ${.CURDIR}/../info
