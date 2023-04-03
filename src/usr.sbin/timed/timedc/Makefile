#	$ssdlinux: Makefile,v 1.2 2002/06/06 06:51:55 yamagata Exp $

.include <bsd.own.mk>

PROG=		timedc
MAN=		${PROG}.8
SRCS=		cmds.c cmdtab.c timedc.c

DIST=		${.CURDIR}/../../../dist/usagi-tool/src/netkit-timed/timed
.PATH:		${DIST}/${PROG}

LIBINET6=	${.CURDIR}/../../../lib/libinet6
.include "${LIBINET6}/Makefile.cflags"
.include "${LIBINET6}/Makefile.ldflags"

LDADD+=		-L${.CURDIR}/../lib -ltimed

.include <bsd.prog.mk>
