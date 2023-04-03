#	$ssdlinux: Makefile,v 1.2 2003/06/12 08:52:42 yamagata Exp $

.include <bsd.own.mk>

PROG=		uucico
SRCS=		uucico.c trans.c send.c rec.c xcmd.c prot.c protg.c \
		protf.c prott.c prote.c proti.c protj.c proty.c protz.c \
		time.c log.c chat.c conn.c util.c copy.c
MAN=		${PROG}.8

BINMODE=	4555

DIST=		${.CURDIR}/../../../dist/uucp
.PATH:		${DIST}

.include "${.CURDIR}/../../../lib/uucp/Makefile.cflags"

NOGCCERROR=	yes

.include <bsd.prog.mk>
