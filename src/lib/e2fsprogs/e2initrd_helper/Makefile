#	$ssdlinux: Makefile,v 1.1 2005/03/02 06:00:50 yamagata Exp $

.include <bsd.own.mk>

PROG=		e2initrd_helper
MKMAN=		no
BINDIR=		/usr/lib

DIST=		${.CURDIR}/../../../dist/e2fsprogs
.PATH:		${DIST}/misc

.include "${.CURDIR}/../Makefile.cflags"

LDADD+=		-L${LIBE2FSDIR}/libext2fs -lext2fs
LDADD+=		-L${LIBE2FSDIR}/libcom_err -lcom_err
LDADD+=		-L${LIBE2FSDIR}/libblkid -lblkid
LDADD+=		-L${LIBE2FSDIR}/libuuid -luuid
LDADD+=		-L${LIBE2FSDIR}/libe2p -le2p
DPADD+=		${LIBE2FSDIR}/libext2fs/libext2fs.a
DPADD+=		${LIBE2FSDIR}/libcom_err/libcom_err.a
DPADD+=		${LIBE2FSDIR}/libblkid/libblkid.a
DPADD+=		${LIBE2FSDIR}/libuuid/libuuid.a
DPADD+=		${LIBE2FSDIR}/libe2p/libe2p.a

.include <bsd.prog.mk>
