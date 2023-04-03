#	$ssdlinux: Makefile,v 1.2 2002/06/12 03:11:56 yamagata Exp $
#	$NetBSD: Makefile,v 1.10 2001/10/05 01:17:30 jmc Exp $

PROG=		dhclient
MKMAN=		no
CPPFLAGS+=	-DCLIENT_PATH='"PATH=/usr/bin:/usr/sbin:/bin:/sbin"'

LIBDHCPDIR=	${.CURDIR}/../../../lib/dhcp
.include "${LIBDHCPDIR}/Makefile.cflags"

LDSTATIC?=	-static

RSRCDIR=	${.CURDIR}/../../../dist/dhcp
.PATH:		${RSRCDIR}/client ${RSRCDIR}/common ${RSRCDIR}/dst ${RSRCDIR}/omapip ${RSRCDIR}/minires
.NOPATH:	${PROG}

SRCS=		dhclient.c clparse.c

.include "Src-dst"
DSTOBJS+=	${DSTSRCS:N*.h:N*.sh:N*.fth:R:S/$/.o/g}
SRCS+=		${DSTSRCS}

.include "Src-omapip"
OMOBJS+=	${OMSRCS:N*.h:N*.sh:N*.fth:R:S/$/.o/g}
SRCS+=		${OMSRCS}

.include "Src-common"
COMOBJS+=	${COMSRCS:N*.h:N*.sh:N*.fth:R:S/$/.o/g}
SRCS+=		${COMSRCS}

.include "Src-minires"
RESOBJS+=	${RESSRCS:N*.h:N*.sh:N*.fth:R:S/$/.o/g}
SRCS+=		${RESSRCS}

CPPFLAGS+=	-DSMALL -I${RSRCDIR} -I${RSRCDIR}/includes
.if ${MACHINE} != "sparc64"
DBG=		-Os
.endif

all: ${PROG}

${DSTOBJS} ${RESOBJS}:
	${CC} ${CFLAGS} ${CPPFLAGS} -DMINIRES_LIB -c ${.IMPSRC}

.SUFFIXES: .OM.c

.c.OM.c:
	cp ${RSRCDIR}/omapip/$*.c $@

CLEANFILES+=	${SRCS:M*.OM.c}

.include <bsd.prog.mk>
