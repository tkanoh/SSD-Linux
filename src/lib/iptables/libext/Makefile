#	$ssdlinux: Makefile,v 1.6 2005/02/14 03:02:44 yamagata Exp $

.include <bsd.own.mk>

LIB=		ext
IPTSRCS=	libipt_ah.c libipt_addrtype.c libipt_comment.c \
		libipt_connlimit.c libipt_connmark.c libipt_conntrack.c \
		libipt_dscp.c libipt_ecn.c libipt_esp.c libipt_hashlimit.c \
		libipt_helper.c libipt_icmp.c libipt_iprange.c \
		libipt_length.c libipt_limit.c libipt_mac.c libipt_mark.c \
		libipt_multiport.c libipt_owner.c libipt_physdev.c \
		libipt_pkttype.c libipt_realm.c libipt_rpc.c libipt_sctp.c \
		libipt_standard.c libipt_state.c libipt_tcp.c libipt_tcpmss.c \
		libipt_tos.c libipt_ttl.c libipt_udp.c libipt_unclean.c \
		libipt_CLASSIFY.c libipt_CONNMARK.c libipt_DNAT.c \
		libipt_DSCP.c libipt_ECN.c libipt_LOG.c libipt_MARK.c \
		libipt_MASQUERADE.c libipt_MIRROR.c libipt_NETMAP.c \
		libipt_NOTRACK.c libipt_REDIRECT.c libipt_REJECT.c \
		libipt_SAME.c libipt_SNAT.c libipt_TARPIT.c libipt_TCPMSS.c \
		libipt_TOS.c libipt_TRACE.c libipt_TTL.c libipt_ULOG.c
SRCS=		initext.c ${IPTSRCS}
CLEANFILES=	initext.c

DIST=		${.CURDIR}/../../../dist/iptables
.PATH:		${DIST}/extensions

.include "${.CURDIR}/../Makefile.cflags"

CPPFLAGS+=	-DNO_SHARED_LIBS=1 -D_INIT=${.TARGET:S/^lib//:S/.o//}_init

NOGCCERROR=	yes

libinstall::

initext.c:
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
