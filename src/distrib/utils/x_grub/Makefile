#	$ssdlinux: Makefile,v 1.4 2003/07/09 06:26:17 yamagata Exp $

.include <bsd.own.mk>

PROG=		grub
SRCS=		main.c asmstub.c device.c
OBJS=		libgrub_a-boot.o \
		libgrub_a-builtins.o libgrub_a-common.o \
		libgrub_a-char_io.o libgrub_a-cmdline.o \
		libgrub_a-disk_io.o libgrub_a-gunzip.o \
		libgrub_a-fsys_ext2fs.o libgrub_a-stage2.o

#OBJS+=		libgrub_a-fsys_fat.o 
#OBJS+=		libgrub_a-fsys_ffs.o
#OBJS+=		libgrub_a-fsys_minix.o
#OBJS+=		libgrub_a-fsys_reiserfs.o
#OBJS+=		libgrub_a-fsys_vstafs.o

MKMAN=		no

DIST=		${.CURDIR}/../../../dist/grub
.PATH:		${DIST}/grub ${DIST}/stage2 ${DIST}/lib

CPPFLAGS+=	-I${.CURDIR}/../../../usr.sbin/grub/include
CPPFLAGS+=	-I${DIST}/stage1
CPPFLAGS+=	-I${DIST}/stage2
CPPFLAGS+=	-I${DIST}/lib
CPPFLAGS+=	-Wall -Wmissing-prototypes -Wunused -Wshadow
CPPFLAGS+=	-Wpointer-arith -falign-jumps=1 -falign-loops=1
CPPFLAGS+=	-falign-functions=1 -Wundef -fwritable-strings
CPPFLAGS+=	-DHAVE_CONFIG_H
#CPPFLAGS+=	-DHAVE_LIBCURSES=1
CPPFLAGS+=	-DGRUB_UTIL=1
CPPFLAGS+=	-DFSYS_EXT2FS=1
#CPPFLAGS+=	-DFSYS_FAT=1
#CPPFLAGS+=	-DFSYS_FFS=1
#CPPFLAGS+=	-DFSYS_MINIX=1
#CPPFLAGS+=	-DFSYS_REISERFS=1
#CPPFLAGS+=	-DFSYS_VSTAFS=1
CPPFLAGS+=	-DNO_HELPMSG=1

LDSTATIC=	-static -s
#LDADD+=		-L${.CURDIR}/../../../lib/libncurses  -lncurses

NOGCCERROR=	yes

${OBJS}:
	${CC} ${CPPFLAGS} -c -o ${.TARGET} \
		${DIST}/stage2/${.TARGET:S/libgrub_a-//:.o=.c}

proginstall:

.include <bsd.prog.mk>
