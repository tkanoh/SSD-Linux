#	$ssdlinux: Makefile,v 1.4 2002/12/12 09:09:23 yamagata Exp $
#	$NetBSD: Makefile,v 1.14 2000/06/05 17:41:19 mycroft Exp $
#	@(#)Makefile	8.1 (Berkeley) 6/6/93

.include <bsd.own.mk>

PROG=		lpd
SRCS=		${PROG}.c printjob.c recvjob.c lpdchar.c key.c modes.c
MAN=		${PROG}.8
BINDIR=		/usr/sbin

.include "${.CURDIR}/../Makefile.cflags"
.include "${.CURDIR}/../Makefile.ldflags"

.PATH:		${DIST}/${PROG}

CPPFLAGS+=	-I${DIST}/${PROG}

.include <bsd.prog.mk>
