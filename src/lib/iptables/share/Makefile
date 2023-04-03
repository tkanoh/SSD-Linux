#	$ssdlinux: Makefile,v 1.8 2005/02/14 03:02:09 yamagata Exp $

.include <bsd.own.mk>

# IPv4
LIBS=		libipt_ah.so libipt_addrtype.so libipt_comment.so
LIBS+=		libipt_connlimit.so libipt_connmark.so
LIBS+=		libipt_conntrack.so libipt_dscp.so libipt_ecn.so
LIBS+=		libipt_esp.so libipt_hashlimit.so libipt_helper.so
LIBS+=		libipt_icmp.so libipt_iprange.so
LIBS+=		libipt_length.so libipt_limit.so libipt_mac.so libipt_mark.so
LIBS+=		libipt_multiport.so libipt_owner.so libipt_physdev.so
LIBS+=		libipt_pkttype.so libipt_realm.so libipt_rpc.so libipt_sctp.so
LIBS+=		libipt_standard.so libipt_state.so libipt_tcp.so
LIBS+=		libipt_tcpmss.so libipt_tos.so libipt_ttl.so libipt_udp.so
LIBS+=		libipt_unclean.so  libipt_CLASSIFY.so libipt_CONNMARK.so
LIBS+=		libipt_DNAT.so
LIBS+=		libipt_DSCP.so libipt_ECN.so libipt_LOG.so libipt_MARK.so
LIBS+=		libipt_MASQUERADE.so libipt_MIRROR.so libipt_NETMAP.so
LIBS+=		libipt_NOTRACK.so libipt_REDIRECT.so libipt_REJECT.so
LIBS+=		libipt_SAME.so libipt_SNAT.so libipt_TARPIT.so libipt_TCPMSS.so
LIBS+=		libipt_TOS.so libipt_TRACE.so libipt_TTL.so libipt_ULOG.so
# IPv6
LIBS+=		libip6t_eui64.so libip6t_hl.so libip6t_icmpv6.so
LIBS+=		libip6t_length.so libip6t_limit.so libip6t_mac.so
LIBS+=		libip6t_mark.so libip6t_multiport.so libip6t_owner.so
LIBS+=		libip6t_physdev.so libip6t_standard.so libip6t_tcp.so
LIBS+=		libip6t_udp.so libip6t_HL.so libip6t_LOG.so libip6t_MARK.so
LIBS+=		libip6t_TRACE.so
LIBS+=		libip6t_ah.so libip6t_dst.so libip6t_esp.so libip6t_frag.so
LIBS+=		libip6t_hbh.so libip6t_ipv6header.so libip6t_rt.so
LIBS+=		libip6t_REJECT.so

DIST=		${.CURDIR}/../../../dist/iptables
.PATH:		${DIST}/extensions

.include "${.CURDIR}/../Makefile.cflags"

CPPFLAGS+=	-fPIC

.MAIN: ${LIBS}

clean:
	rm -f ${LIBS} *.o

cleandir:

.if defined(STATIC_IPT)
${LIBS}:

install:

.else

${LIBS}:
	${CC} ${CPPFLAGS} -o ${.TARGET:M*.so:.so=.o} -c ${DIST}/extensions/${.TARGET:M*.so:.so=.c}
	${LD} -shared -o ${.TARGET} ${.TARGET:M*.so:.so=.o}

install:
	@[ -d ${DESTDIR}${IPT_LIB_DIR} ] || mkdir -p ${DESTDIR}${IPT_LIB_DIR}
	${INSTALL} -c -m ${LIBMODE} -o ${LIBOWN} -g ${LIBGRP} ${LIBS} ${DESTDIR}${IPT_LIB_DIR}
.endif
