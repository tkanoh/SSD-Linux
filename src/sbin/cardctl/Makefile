#	$ssdlinux: Makefile,v 1.5 2002/10/23 06:30:00 yamagata Exp $

.include <bsd.own.mk>

PROG=		cardctl
MAN=		${PROG}.8
BINMODE=	4555

DIST=		${.CURDIR}/../../dist/pcmcia-cs
.PATH:		${DIST}/cardmgr ${DIST}/man

CPPFLAGS+=	-Wall -Wstrict-prototypes -pipe \
 		-I${.CURDIR}/../../lib/modules/pcmcia/include \
		-I${.CURDIR}/../../linux/include

.include <bsd.prog.mk>
