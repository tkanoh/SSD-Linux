#	$ssdlinux: Makefile,v 1.3 2002/06/06 02:32:39 yamagata Exp $

.include <bsd.own.mk>

PROG=		ping
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/usagi-tool/src/netkit-base
.PATH:		${DIST}/${PROG}

CPPFLAGS+=	-Dss_family=__ss_family -Dss_len=__ss_len
CPPFLAGS+=	-I${DIST} -I${DIST}/${PROG}

.include <bsd.prog.mk>
