#	$ssdlinux: Makefile,v 1.2 2002/06/03 07:31:21 yamagata Exp $

.include <bsd.own.mk>

LIB=		net-tools
MKMAN=		no

DIST=		${.CURDIR}/../../dist/usagi-tool/src/net-tools
.PATH:		${DIST}/lib

CPPFLAGS+=	-I${.CURDIR} -I${DIST} -I${DIST}/lib -I${DIST}/include

LIBINET6=	${.CURDIR}/../libinet6
.include "${LIBINET6}/Makefile.cflags"

HWSRCS=		hw.c loopback.c slip.c ether.c ax25.c ppp.c arcnet.c tr.c \
		tunnel.c frame.c sit.c rose.c ash.c fddi.c hippi.c hdlclapb.c \
		strip.c irda.c ec_hw.c x25.c
AFSRCS=		unix.c inet.c inet6.c ax25.c ipx.c ddp.c ipx.c netrom.c \
		af.c rose.c econet.c x25.c
AFGRSRCS=	inet_gr.c inet6_gr.c ipx_gr.c ddp_gr.c netrom_gr.c ax25_gr.c \
		rose_gr.c getroute.c x25_gr.c
AFSRSRCS=	inet_sr.c inet6_sr.c netrom_sr.c ipx_sr.c setroute.c x25_sr.c
ACTSRCS=	slip_ac.c ppp_ac.c activate.c
VARIA=		getargs.c masq_info.c proc.c util.c nstrcmp.c interface.c sockets.c

#.ifdef HAVE_IP_TOOLS
VARIA+=		util-ank.c
#.endif

SRCS+=		${HWSRCS} ${AFSRCS} ${AFGRSRCS} ${AFSRSRCS} ${ACTSRCS} ${VARIA}

NOGCCERROR=	yes

libinstall::

.include <bsd.lib.mk>
