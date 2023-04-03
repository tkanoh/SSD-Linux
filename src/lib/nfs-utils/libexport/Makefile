#	$ssdlinux: Makefile,v 1.2 2003/09/04 08:06:21 yamagata Exp $

.include <bsd.own.mk>

LIB=		export
SRCS=		mount_clnt.c mount_xdr.c client.c export.c \
		hostname.c nfsctl.c rmtab.c xtab.c
MKPIC=		no
MKMAN=		no
DIST=		${.CURDIR}/../../../dist/nfs-utils
.PATH:		${DIST}/support/export

.include "${.CURDIR}/../Makefile.cflags"

CLEANFILES=	mount.x mount.h mount_clnt.c mount_xdr.c ../include/mount.h

mount_clnt.c: mount.h
	rm -f ${.TARGET}
	rpcgen -l -o ${.TARGET} mount.x

mount_xdr.c: mount.h
	rm -f ${.TARGET}
	rpcgen -c -o ${.TARGET} mount.x

mount.h:
	rm -f ${.TARGET}
	cp ${DIST}/support/export/mount.x .
	rpcgen -h -o ${.TARGET} mount.x
	cp ${.TARGET} ../include

NOGCCERROR=	yes

.include <bsd.lib.mk>
