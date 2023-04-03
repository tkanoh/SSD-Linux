#	$ssdlinux: Makefile,v 1.12 2003/01/09 03:02:09 kanoh Exp $

.include <bsd.own.mk>

PROG=		pack_cis
SRCS=		${PROG}.c lex_cis.c yacc_cis.c
MAN=		${PROG}.8
CLEANFILES=	${SRCS:M*.c:.c=.d}

CPPFLAGS=	-MD

.include "${.CURDIR}/../Makefile.cflags"

.if ${TARGET_SSDHOSTTYPEX} == "powerpc-obs50" || ${TARGET_SSDHOSTTYPEX} == "powerpc-obs2xx"
LDADD+=		-lm
.endif

NOGCCERROR=	yes

.include <bsd.prog.mk>
