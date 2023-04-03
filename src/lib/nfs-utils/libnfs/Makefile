#	$ssdlinux: Makefile,v 1.2 2003/09/04 08:24:23 yamagata Exp $

.include <bsd.own.mk>

LIB=		nfs
SRCS=		exports.c rmtab.c xio.c \
		rpcmisc.c rpcdispatch.c xlog.c xmalloc.c wildmat.c \
		nfssvc.c nfsclient.c nfsexport.c getfh.c nfsctl.c \
		lockdsvc.c svc_socket.c cacheio.c
MKPIC=		no
MKMAN=		no
DIST=		${.CURDIR}/../../../dist/nfs-utils
.PATH:		${DIST}/support/nfs

.include "${.CURDIR}/../Makefile.cflags"

NOGCCERROR=	yes

.include <bsd.lib.mk>
