#	$ssdlinux: Makefile,v 1.6 2004/06/22 09:02:53 yamagata Exp $

.include <bsd.own.mk>

PROG=		ip6tables
SRCS=		${PROG}.c ${PROG}-standalone.c
MAN=		${PROG}.8
CLEANFILES=	${MAN} libip6t_matches.man libip6t_targets.man

DIST=		${.CURDIR}/../../../dist/iptables
.PATH:		${DIST}

.include "${.CURDIR}/../../../lib/iptables/Makefile.cflags"

CPPFLAGS+=	-DIP6T_LIB_DIR=\"${IPT_LIB_DIR}\"

.if defined(STATIC_IPT)
CPPFLAGS+=	-DNO_SHARED_LIBS=1
LDSTATIC=	-static
LDADD+=		-L${.CURDIR}/../../../lib/iptables/libext6 -lext6
DPADD+=		${.CURDIR}/../../../lib/iptables/libext6/libext6.a
.else
CPPFLAGS+=	-rdynamic
.endif

DPADD+=         ${.CURDIR}/../libiptc/libiptc.a
LDADD+=         -L${.CURDIR}/../libiptc -liptc
LDADD+=		-ldl -lnsl

${MAN}: libip6t_matches.man libip6t_targets.man
	sed -e '/@MATCH@/ r libip6t_matches.man' -e '/@TARGET@/ r libip6t_targets.man' ${DIST}/${.TARGET}.in >${.TARGET}

libip6t_targets.man:
	for ext in HL LOG MARK REJECT ROUTE TRACE; do \
		echo ".SS $$ext" ;\
		cat ${DIST}/extensions/libip6t_$$ext.man ;\
	done >${.TARGET}
	if [ -n "" ]; then \
		extra= ;\
		for ext in $${extra:-""}; do \
			echo ".SS $$ext (not supported, see Patch-O-Matic)" ;\
			cat ${DIST}/extensions/libip6t_$$ext.man ;\
		done ;\
	fi >>${.TARGET}

libip6t_matches.man:
	for ext in ah condition dst esp eui64 frag fuzzy hbh hl icmpv6 ipv6header length limit mac mark multiport nth owner random rt tcp udp; do \
		echo ".SS $$ext" ;\
		cat ${DIST}/extensions/libip6t_$$ext.man ;\
	done >${.TARGET}
	if [ -n "" ]; then \
		extra= ;\
		for ext in $${extra:-""}; do \
			echo ".SS $$ext (not supported, see Patch-O-Matic)" ;\
			cat ${DIST}/extensions/libip6t_$$ext.man ;\
		done ;\
	fi >>${.TARGET}

.include <bsd.prog.mk>
