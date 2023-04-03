#	$ssdlinux: Makefile,v 1.1 2004/08/09 04:36:06 todoroki Exp $

.include <bsd.own.mk>

.include "../Makefile.inc"

PROG=		pcimodules
SRCS=		${PROG}.c common.c
MKMAN=		no

DIST=		${.CURDIR}/../../../dist/pciutils
.PATH:		${DIST}

NOGCCERROR=	yes

.include <bsd.prog.mk>
