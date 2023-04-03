#	$ssdlinux: Makefile,v 1.6 2004/06/22 09:02:53 yamagata Exp $

.include <bsd.own.mk>

PROG=		iptables
SRCS=		${PROG}.c ${PROG}-standalone.c
MAN=		${PROG}.8
CLEANFILES=	${MAN} libipt_matches.man libipt_targets.man

DIST=		${.CURDIR}/../../../dist/${PROG}
.PATH:		${DIST}

.include "${.CURDIR}/../../../lib/${PROG}/Makefile.cflags"

CPPFLAGS+=	-DIPT_LIB_DIR=\"${IPT_LIB_DIR}\"

.if defined(STATIC_IPT)
CPPFLAGS+=	-DNO_SHARED_LIBS=1
LDSTATIC=	-static
LDADD+=		-L${.CURDIR}/../../../lib/${PROG}/libext -lext
DPADD+=		${.CURDIR}/../../../lib/${PROG}/libext/libext.a
.else
CPPFLAGS+=	-rdynamic
.endif

DPADD+=         ${.CURDIR}/../libiptc/libiptc.a
LDADD+=         -L${.CURDIR}/../libiptc -liptc
LDADD+=		-ldl -lnsl

${MAN}: libipt_matches.man libipt_targets.man
	sed -e '/@MATCH@/ r libipt_matches.man' -e '/@TARGET@/ r libipt_targets.man' ${DIST}/${.TARGET}.in >${.TARGET}

libipt_targets.man:
	for ext in BALANCE CLASSIFY CLUSTERIP CONNMARK DNAT DSCP ECN LOG MARK MASQUERADE MIRROR NETMAP NOTRACK REDIRECT REJECT ROUTE SNAT TCPMSS TOS TRACE TTL ULOG; do \
		echo ".SS $$ext" ;\
		cat ${DIST}/extensions/libipt_$$ext.man ;\
	done >${.TARGET}
	if [ -n "" ]; then \
		extra= ;\
		for ext in $${extra:-""}; do \
			echo ".SS $$ext (not supported, see Patch-O-Matic)" ;\
			cat ${DIST}/extensions/libipt_$$ext.man ;\
		done ;\
	fi >>${.TARGET}

libipt_matches.man:
	for ext in addrtype ah childlevel condition connmark connrate conntrack dscp dstlimit ecn esp fuzzy helper icmp iprange length limit mac mark mport multiport nth owner physdev pkttype random realm state tcp tcpmss time tos ttl udp unclean; do \
		echo ".SS $$ext" ;\
		cat ${DIST}/extensions/libipt_$$ext.man ;\
	done >${.TARGET}
	if [ -n "" ]; then \
		extra= ;\
		for ext in $${extra:-""}; do \
			echo ".SS $$ext (not supported, see Patch-O-Matic)" ;\
			cat ${DIST}/extensions/libipt_$$ext.man ;\
		done ;\
	fi >>${.TARGET}

.include <bsd.prog.mk>
