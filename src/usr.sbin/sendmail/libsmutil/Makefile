#	$ssdlinux: Makefile,v 1.2 2002/06/06 06:51:26 yamagata Exp $

.include <bsd.own.mk>

LIB=		smutil
SRCS=		debug.c err.c lockfile.c safefile.c snprintf.c cf.c

DIST=		${.CURDIR}/../../../dist/sendmail
.PATH:		${DIST}/lib${LIB}

CPPFLAGS+=	-DNOT_SENDMAIL -I${DIST}/sendmail

libinstall::

.include <bsd.lib.mk>
