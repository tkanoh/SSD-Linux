#	$ssdlinux: Makefile,v 1.4 2005/03/02 01:43:22 yamagata Exp $
.include <bsd.own.mk>

.include "${.CURDIR}/../Makefile.cflags"

LIB=		omapi
SRCS=		protocol.c buffer.c alloc.c result.c connection.c errwarn.c \
		listener.c dispatch.c generic.c support.c handle.c message.c \
		convert.c hash.c auth.c inet_addr.c array.c trace.c mrtrace.c \
		toisc.c iscprint.c
MAN=		${LIB}.3

DIST=		${.CURDIR}/../../../dist/dhcp
.PATH:		${DIST}/omapip ${DIST}/common

CPPFLAGS+=	-I${DIST} -I${DIST}/includes

libinstall::

.include <bsd.lib.mk>
