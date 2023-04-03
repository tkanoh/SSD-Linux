#	$ssdlinux: Makefile,v 1.3 2002/06/06 02:19:09 yamagata Exp $

.include <bsd.own.mk>

PROG=		setserial
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/${PROG}
.PATH:		${DIST}

CPPFLAGS+=	-DHAVE_ASM_IOCTLS_H=1 -DHAVE_LINUX_HAYESESP_H=1 -I${DIST}

.include <bsd.prog.mk>
