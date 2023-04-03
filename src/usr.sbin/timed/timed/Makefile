#	$ssdlinux: Makefile,v 1.2 2002/06/06 06:51:55 yamagata Exp $

.include <bsd.own.mk>

PROG=		timed
MAN=		${PROG}.8
SRCS=		acksend.c candidate.c correct.c master.c networkdelta.c \
		readmsg.c slave.c timed.c

DIST=		${.CURDIR}/../../../dist/usagi-tool/src/netkit-timed/timed
.PATH:		${DIST}/timed

LIBINET6=	${.CURDIR}/../../../lib/libinet6
.include "${LIBINET6}/Makefile.cflags"
.include "${LIBINET6}/Makefile.ldflags"

LDADD+=		-L${.CURDIR}/../lib -ltimed -lutil

.include <bsd.prog.mk>
