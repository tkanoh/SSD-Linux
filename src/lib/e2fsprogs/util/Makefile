#	$ssdlinux: Makefile,v 1.5 2003/09/08 06:36:27 yamagata Exp $

.include <bsd.own.mk>

PROG=		subst
MKMAN=		no
SCRIPTS=	../include/ext2fs/ext2_types.h
SCRIPTS+=	../libcom_err/compile_et

CC=		${HOST_CC}

DIST=		${.CURDIR}/../../../dist/e2fsprogs
.PATH:		${DIST}/util

.include "${.CURDIR}/../Makefile.cflags"

CLEANFILES=	subst.conf
CLEANFILES+=	../include/ext2fs/ext2_types.h
CLEANFILES+=	../libcom_err/compile_et

./subst.conf: subst.conf.in
	sed -e 's!@CURDIR@!'${.CURDIR}'!' subst.conf.in > ./subst.conf

../include/ext2fs/ext2_types.h: ./subst.conf
	mkdir -p ../include/ext2fs
	./subst -f ./subst.conf ${DIST}/lib/ext2fs/ext2_types.h.in ${.TARGET}

../libcom_err/compile_et: ./subst.conf
	./subst -f ./subst.conf ${DIST}/lib/et/compile_et.sh.in ${.TARGET}
	chmod +x ${.TARGET}

proginstall::

scriptsinstall::

.include <bsd.prog.mk>
