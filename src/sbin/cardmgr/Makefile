#	$ssdlinux: Makefile,v 1.8 2002/10/24 07:29:53 yamagata Exp $

.include <bsd.own.mk>

PROG=		cardmgr
SCRIPTS=	pcinitrd
SRCS=		${PROG}.c yacc_config.c lex_config.c
MAN=		${PROG}.8 ${SCRIPTS}.8
CLEANFILES=	${SRCS:M*.c:.c=.d}

DIST=		${.CURDIR}/../../dist/pcmcia-cs
.PATH:		${DIST}/${PROG} ${DIST}/man

CPPFLAGS+=	-MD -Wall -Wstrict-prototypes -pipe \
		-I${.CURDIR}/../../lib/modules/pcmcia/include \
		-I${.CURDIR}/../../linux/include \
		-I${DIST}/modules

NOGCCERROR=	yes

.include <bsd.prog.mk>
