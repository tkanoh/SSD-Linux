#	$ssdlinux: Makefile,v 1.3 2004/05/31 06:41:07 yamagata Exp $

.include <bsd.own.mk>

LIB=		pamc
SRCS=		pamc_client.c pamc_converse.c pamc_load.c
MKPIC=		yes
MKPICINSTALL=	no
INCS=		pam_client.h

DIST=		${.CURDIR}/../../../dist/Linux-PAM
.PATH:		${DIST}/libpamc ${DIST}/libpamc/include/security

.include "${.CURDIR}/../Makefile.cflags"

.include <bsd.lib.mk>
