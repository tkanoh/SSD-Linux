#	$ssdlinux: Makefile,v 1.6 2004/02/25 04:44:57 yamagata Exp $

.include <bsd.own.mk>

PROG=		kill
SRCS=		skill.c

DIST=		${.CURDIR}/../../dist/procps
.PATH:		${DIST}

LIPROCDIR=	${.CURDIR}/../../lib/libproc
LDDIR!=		cd ${LIPROCDIR} && ${PRINTOBJDIR}
LDADD+=		-L${LDDIR} -lproc
DPADD+=		${LIPROCDIR}/libproc.a

CPPFLAGS+=	-D_GNU_SOURCE -fno-common -ffast-math \
		-W -Wall -Wshadow -Wcast-align -Wredundant-decls \
		-Wbad-function-cast -Wcast-qual -Wwrite-strings \
		-Waggregate-return \
		-Wstrict-prototypes -Wmissing-prototypes
LDFLAGS=	-s

NOGCCERROR=	yes

.include <bsd.prog.mk>
