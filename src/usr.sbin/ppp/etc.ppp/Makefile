#	$ssdlinux: Makefile,v 1.2 2004/02/05 06:07:48 yamagata Exp $

.include <bsd.own.mk>

.if defined(DESTDIR) || !make(install)
SCRIPTS=	options
SCRIPTSDIR=	/etc/ppp
SCRIPTSMODE=	640
FILES=		pap-secrets chap-secrets
FILESDIR=	/etc/ppp
FILESMODE=	600
.endif

.include <bsd.prog.mk>
