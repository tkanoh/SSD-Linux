#	$ssdlinux: Makefile,v 1.8 2004/06/18 02:36:10 yamagata Exp $

.include <bsd.own.mk>

PROG=		grub
SRCS=		main.c asmstub.c
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../../dist/grub
.PATH:		${DIST}/grub ${DIST}/docs

CPPFLAGS+=	-I${.CURDIR}/../include
CPPFLAGS+=	-I${DIST}/stage1
CPPFLAGS+=	-I${DIST}/stage2
CPPFLAGS+=	-I${DIST}/lib
CPPFLAGS+=	-Wall -Wmissing-prototypes -Wunused -Wshadow
CPPFLAGS+=	-Wpointer-arith -falign-jumps=1 -falign-loops=1
CPPFLAGS+=	-falign-functions=1 -Wundef -fwritable-strings
CPPFLAGS+=	-DHAVE_CONFIG_H
CPPFLAGS+=	-DHAVE_LIBCURSES=1
CPPFLAGS+=	-DGRUB_UTIL=1
CPPFLAGS+=	-DFSYS_EXT2FS=1
CPPFLAGS+=	-DFSYS_FAT=1
CPPFLAGS+=	-DFSYS_FFS=1
CPPFLAGS+=	-DFSYS_ISO9660=1
CPPFLAGS+=	-DFSYS_JFS=1
CPPFLAGS+=	-DFSYS_MINIX=1
CPPFLAGS+=	-DFSYS_REISERFS=1
CPPFLAGS+=	-DFSYS_UFS2=1
CPPFLAGS+=	-DFSYS_VSTAFS=1
CPPFLAGS+=	-DFSYS_XFS=1
CPPFLAGS+=	-DUSE_MD5_PASSWORDS=1
CPPFLAGS+=	-DSUPPORT_HERCULES=1
CPPFLAGS+=	-DSUPPORT_SERIAL=1

LDADD+=         -L${.CURDIR}/../lib -lcommon
LDADD+=         -L${.CURDIR}/../../../lib/libncurses/build/lib -lncurses
LDADD+=         ${.CURDIR}/../stage2/libgrub.a
DPADD+=         ${.CURDIR}/../lib/libcommon.a
DPADD+=         ${.CURDIR}/../../../lib/libncurses/build/lib/libncurses.a

NOGCCERROR=	yes

.include <bsd.prog.mk>
