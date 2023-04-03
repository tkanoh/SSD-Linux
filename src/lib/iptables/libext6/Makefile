#	$ssdlinux: Makefile,v 1.7 2005/02/14 03:02:27 yamagata Exp $

.include <bsd.own.mk>

LIB=		ext6
IPTSRCS=	libip6t_eui64.c libip6t_hl.c libip6t_icmpv6.c libip6t_length.c \
		libip6t_limit.c libip6t_mac.c libip6t_mark.c \
		libip6t_multiport.c libip6t_owner.c libip6t_physdev.c \
		libip6t_standard.c libip6t_tcp.c libip6t_udp.c libip6t_HL.c \
		libip6t_LOG.c libip6t_MARK.c libip6t_TRACE.c \
		libip6t_ah.c libip6t_dst.c libip6t_esp.c libip6t_frag.c \
		libip6t_hbh.c libip6t_ipv6header.c libip6t_rt.c \
		libip6t_REJECT.c
SRCS=		initext6.c ${IPTSRCS}
CLEANFILES=	initext6.c

DIST=		${.CURDIR}/../../../dist/iptables
.PATH:		${DIST}/extensions

.include "${.CURDIR}/../Makefile.cflags"

CPPFLAGS+=	-DNO_SHARED_LIBS=1 -D_INIT=${.TARGET:S/^lib//:S/.o//}_init

NOGCCERROR=	yes

libinstall::

initext6.c:
	echo "" > ${.TARGET}
	for i in ${IPTSRCS}; do \
		j=`echo $${i} | sed -e 's/^lib//' -e 's/\.c/_init\(void\)/'`; \
		echo "extern void $${j};" >> ${.TARGET}; \
	done
	echo "void init_extensions(void) {" >> ${.TARGET}
	for i in ${IPTSRCS}; do \
		j=`echo $${i} | sed -e 's/^lib//' -e 's/\.c/_init\(\)/'`; \
		echo "  $${j};" >> ${.TARGET}; \
	done
	echo "}" >> ${.TARGET}

.include <bsd.lib.mk>
