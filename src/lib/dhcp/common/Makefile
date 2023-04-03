#	$ssdlinux: Makefile,v 1.6 2005/03/02 01:43:35 yamagata Exp $
.include <bsd.own.mk>

.include "${.CURDIR}/../Makefile.cflags"

LIB=		dhcp
SRCS=		raw.c parse.c nit.c icmp.c dispatch.c conflex.c upf.c bpf.c socket.c \
		lpf.c dlpi.c packet.c tr.c ethernet.c memory.c print.c options.c \
		inet.c tree.c tables.c alloc.c fddi.c ctrace.c dns.c resolv.c \
		execute.c discover.c comapi.c
MAN=		dhcp-options.5 dhcp-options.5

DIST=		${.CURDIR}/../../../dist/${LIB}
.PATH:		${DIST}/common

CPPFLAGS+=	-I${DIST} -I${DIST}/includes

libinstall::

.include <bsd.lib.mk>
