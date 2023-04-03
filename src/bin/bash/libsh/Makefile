#	$ssdlinux: Makefile,v 1.6 2004/08/29 05:27:07 yamagata Exp $

.include <bsd.own.mk>

LIB=		sh
SRCS=		clktck.c clock.c getenv.c oslib.c setlinebuf.c \
		itos.c zread.c zwrite.c shtty.c shmatch.c \
		netconn.c netopen.c timeval.c makepath.c pathcanon.c \
		pathphys.c tmpfile.c stringlist.c stringvec.c spell.c shquote.c \
		strtrans.c strindex.c snprintf.c mailstat.c fmtulong.c \
		fmtullong.c fmtumax.c xstrchr.c zcatfd.c

DIST=		${.CURDIR}/../../../dist/bash
.PATH:		${DIST}/lib/${LIB}

libinstall::

NOGCCERROR=	yes

.include <bsd.lib.mk>
