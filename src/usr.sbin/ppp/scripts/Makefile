#	$ssdlinux: Makefile,v 1.3 2004/02/05 06:09:46 yamagata Exp $

.include <bsd.own.mk>

.if defined(DESTDIR) || !make(install)
SCRIPTS=	ppp-on ppp-off ppp-on-dialer
SCRIPTSDIR=	/etc/ppp
SCRIPTSMODE=	555
.endif

DIST=           ${.CURDIR}/../../../dist/ppp
.PATH:          ${DIST}/${PROG} ${DIST}/scripts

.include <bsd.prog.mk>
