#	$ssdlinux: Makefile,v 1.3 2004/05/31 06:39:10 yamagata Exp $

.include <bsd.own.mk>

LIB=		pam_misc
SRCS=		help_env.c misc_conv.c
MKPIC=		yes
MKPICINSTALL=	no
INCS+=		pam_misc.h

DIST=		${.CURDIR}/../../../dist/Linux-PAM
.PATH:		${DIST}/libpam_misc ${DIST}/libpam_misc/include/security

.include "${.CURDIR}/../Makefile.cflags"

.include <bsd.lib.mk>
