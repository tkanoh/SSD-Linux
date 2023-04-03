#	$ssdlinux: Makefile,v 1.4 2004/07/04 07:08:57 yamagata Exp $

.include <bsd.own.mk>

LIB=		smdb
SRCS=		smdb.c smdb1.c smdb2.c smndbm.c

DIST=		${.CURDIR}/../../../dist/sendmail
.PATH:		${DIST}/lib${LIB}

CPPFLAGS+=	-DNOT_SENDMAIL -I${DIST}/sendmail
.if defined(CROSS_BUILD) || defined(NEW_GLIBC)
CPPFLAGS+=	-I${.CURDIR}/../../../lib/libdb
.endif

libinstall::

.include <bsd.lib.mk>
