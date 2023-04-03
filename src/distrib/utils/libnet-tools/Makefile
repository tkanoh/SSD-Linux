#	$ssdlinux: Makefile,v 1.2 2002/06/12 02:58:30 yamagata Exp $
.include <bsd.own.mk>

LIB=		net-tools

SRCS+=	hw.c loopback.c slip.c ether.c ax25.c ppp.c arcnet.c tr.c
SRCS+=	tunnel.c frame.c sit.c rose.c ash.c fddi.c hippi.c hdlclapb.c
SRCS+=	strip.c irda.c ec_hw.c x25.c
SRCS+=	unix.c inet.c inet6.c ax25.c ipx.c ddp.c ipx.c netrom.c
SRCS+=	af.c rose.c econet.c
SRCS+=	inet_gr.c inet6_gr.c ipx_gr.c ddp_gr.c netrom_gr.c ax25_gr.c
SRCS+=	rose_gr.c getroute.c x25_gr.c
SRCS+=	inet_sr.c inet6_sr.c netrom_sr.c ipx_sr.c setroute.c x25_sr.c
SRCS+=	slip_ac.c ppp_ac.c activate.c
SRCS+=	getargs.c masq_info.c proc.c nstrcmp.c interface.c sockets.c
SRCS+=	net-tools-util.c
MKMAN=		NO

DIST=		${.CURDIR}/../../../dist
LDIR=		${.CURDIR}/../../../lib

.PATH:		${LDIR}/net-tools ${DIST}/usagi-tool/src/net-tools/lib 
 
CPPFLAGS+=	-DLIBDIR=\"/usr/lib\" -DHAVE_CONFIG_H
CPPFLAGS+=	-I${.CURDIR}
CPPFLAGS+=	-I${LDIR}/net-tools
CPPFLAGS+=	-I${DIST}/usagi-tool/src/net-tools
CPPFLAGS+=	-I${DIST}/usagi-tool/src/net-tools/lib
CPPFLAGS+=	-I${DIST}/usagi-tool/src/net-tools/include
CPPFLAGS+=	-DNET_TOOL_LIB_INSTALLER

NOGCCERROR=	yes

libinstall:

.include <bsd.lib.mk>
