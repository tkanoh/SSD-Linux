#	$ssdlinux: Makefile,v 1.6 2003/12/05 02:46:18 yamagata Exp $

.include <bsd.own.mk>

PROG=		rsync
SRCS=		${PROG}.c generator.c receiver.c cleanup.c sender.c \
		exclude.c util.c main.c checksum.c match.c syscall.c \
		log.c backup.c options.c flist.c io.c compat.c hlink.c \
		token.c uidlist.c socket.c fileio.c batch.c clientname.c \
		progress.c pipe.c \
		params.c loadparm.c clientserver.c access.c connection.c \
		authenticate.c
MAN=		${PROG}.1 rsyncd.conf.5

DIST=		${.CURDIR}/../../../dist/rsync
.PATH:		${DIST}

CPPFLAGS+=	-I${.CURDIR}/../ -I${DIST} -I${DIST}/popt

LDADD+=		-L${.CURDIR}/../lib -lrsync
LDADD+=		-L${.CURDIR}/../popt -lpopt
LDADD+=		-L${.CURDIR}/../zlib -lzlib
DPADD+=		${.CURDIR}/../lib/librsync.a
DPADD+=		${.CURDIR}/../popt/libpopt.a
DPADD+=		${.CURDIR}/../zlib/libzlib.a

.include <bsd.prog.mk>
