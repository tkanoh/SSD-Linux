#	$ssdlinux: Makefile,v 1.2 2002/06/03 07:14:03 yamagata Exp $

.include <bsd.own.mk>

PROG=		talkd
SRCS=		talkd.c announce.c print.c process.c \
		repairs.c table.c ctlmsg.c talkaddr.c
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/usagi-tool/src/netkit-ntalk
.PATH:		${DIST}/${PROG} ${DIST}/libtalk ${DIST}/include

LIBINET6=	${.CURDIR}/../../lib/libinet6
.include "${LIBINET6}/Makefile.cflags"
CPPFLAGS+=	-I${.CURDIR} -I${DIST} -I${DIST}/include

.include "${LIBINET6}/Makefile.ldflags"

NOGCCERROR=	yes

.include <bsd.prog.mk>
