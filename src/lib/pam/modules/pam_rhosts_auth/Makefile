#	$ssdlinux: Makefile,v 1.4 2004/05/31 08:28:15 yamagata Exp $

.include <bsd.own.mk>

MODULE=		pam_rhosts_auth
MODULEDIR=	pam_rhosts

.include "${.CURDIR}/../Makefile.cflags"

CPPFLAGS+=	-I${MSRCDIR}/pammodutil/include

.include <bsd.prog.mk>
