#	$ssdlinux: Makefile,v 1.13 2004/07/17 09:39:22 kanoh Exp $

.include <bsd.own.mk>

STAGE2=		stage2
STAGE2ELTORITO=		stage2_eltorito
STAGE15=	e2fs_stage1_5 \
		fat_stage1_5 \
		ffs_stage1_5 \
		iso9660_stage1_5 \
		jfs_stage1_5 \
		minix_stage1_5 \
		reiserfs_stage1_5 \
		ufs2_stage1_5 \
		vstafs_stage1_5 \
		xfs_stage1_5

PREASMOBJS=	pre_stage2_exec-asm.o
PREOBJS=	pre_stage2_exec-bios.o pre_stage2_exec-boot.o \
		pre_stage2_exec-builtins.o pre_stage2_exec-char_io.o \
		pre_stage2_exec-cmdline.o pre_stage2_exec-common.o \
		pre_stage2_exec-console.o pre_stage2_exec-disk_io.o \
		pre_stage2_exec-fsys_ext2fs.o \
		pre_stage2_exec-fsys_fat.o \
		pre_stage2_exec-fsys_ffs.o \
		pre_stage2_exec-fsys_iso9660.o \
		pre_stage2_exec-fsys_jfs.o \
		pre_stage2_exec-fsys_minix.o \
		pre_stage2_exec-fsys_reiserfs.o \
		pre_stage2_exec-fsys_ufs2.o \
		pre_stage2_exec-fsys_vstafs.o \
		pre_stage2_exec-fsys_xfs.o \
		pre_stage2_exec-gunzip.o pre_stage2_exec-hercules.o \
		pre_stage2_exec-md5.o pre_stage2_exec-serial.o \
		pre_stage2_exec-smp-imps.o pre_stage2_exec-stage2.o \
		pre_stage2_exec-terminfo.o pre_stage2_exec-tparm.o

LIBOBJS=	libgrub_a-bios.o libgrub_a-boot.o \
		libgrub_a-builtins.o libgrub_a-char_io.o \
		libgrub_a-cmdline.o libgrub_a-common.o \
		libgrub_a-disk_io.o \
		libgrub_a-fsys_ext2fs.o \
		libgrub_a-fsys_fat.o \
		libgrub_a-fsys_ffs.o \
		libgrub_a-fsys_iso9660.o \
		libgrub_a-fsys_jfs.o \
		libgrub_a-fsys_minix.o \
		libgrub_a-fsys_reiserfs.o \
		libgrub_a-fsys_ufs2.o \
		libgrub_a-fsys_vstafs.o \
		libgrub_a-fsys_xfs.o \
		libgrub_a-gunzip.o \
		libgrub_a-md5.o libgrub_a-serial.o \
		libgrub_a-stage2.o libgrub_a-terminfo.o \
		libgrub_a-tparm.o 

STARTASMOBJS=	start_exec-start.o

STARTELTORITOASMOBJS=	start_eltorito_exec-start_eltorito.o

E2FS15ASMOBJS=	e2fs_stage1_5_exec-start.o e2fs_stage1_5_exec-asm.o
E2FS15OBJS=	e2fs_stage1_5_exec-common.o e2fs_stage1_5_exec-char_io.o \
		e2fs_stage1_5_exec-disk_io.o e2fs_stage1_5_exec-stage1_5.o \
		e2fs_stage1_5_exec-fsys_ext2fs.o e2fs_stage1_5_exec-bios.o

FAT15ASMOBJS=	fat_stage1_5_exec-start.o fat_stage1_5_exec-asm.o
FAT15OBJS=	fat_stage1_5_exec-common.o fat_stage1_5_exec-char_io.o \
		fat_stage1_5_exec-disk_io.o fat_stage1_5_exec-stage1_5.o \
		fat_stage1_5_exec-fsys_fat.o fat_stage1_5_exec-bios.o

FFS15ASMOBJS=	ffs_stage1_5_exec-start.o ffs_stage1_5_exec-asm.o
FFS15OBJS=	ffs_stage1_5_exec-common.o ffs_stage1_5_exec-char_io.o \
		ffs_stage1_5_exec-disk_io.o ffs_stage1_5_exec-stage1_5.o \
		ffs_stage1_5_exec-fsys_ffs.o ffs_stage1_5_exec-bios.o

UFS215ASMOBJS=	ufs2_stage1_5_exec-start.o ufs2_stage1_5_exec-asm.o
UFS215OBJS=	ufs2_stage1_5_exec-common.o ufs2_stage1_5_exec-char_io.o \
		ufs2_stage1_5_exec-disk_io.o ufs2_stage1_5_exec-stage1_5.o \
		ufs2_stage1_5_exec-fsys_ufs2.o ufs2_stage1_5_exec-bios.o

MINIX15ASMOBJS=	minix_stage1_5_exec-start.o minix_stage1_5_exec-asm.o
MINIX15OBJS=	minix_stage1_5_exec-common.o minix_stage1_5_exec-char_io.o \
		minix_stage1_5_exec-disk_io.o minix_stage1_5_exec-stage1_5.o \
		minix_stage1_5_exec-fsys_minix.o minix_stage1_5_exec-bios.o

REISERFS15ASMOBJS= reiserfs_stage1_5_exec-start.o reiserfs_stage1_5_exec-asm.o
REISERFS15OBJS=	reiserfs_stage1_5_exec-common.o reiserfs_stage1_5_exec-char_io.o \
		reiserfs_stage1_5_exec-disk_io.o reiserfs_stage1_5_exec-stage1_5.o \
		reiserfs_stage1_5_exec-fsys_reiserfs.o reiserfs_stage1_5_exec-bios.o

VSTAFS15ASMOBJS= vstafs_stage1_5_exec-start.o vstafs_stage1_5_exec-asm.o
VSTAFS15OBJS=	vstafs_stage1_5_exec-common.o vstafs_stage1_5_exec-char_io.o \
		vstafs_stage1_5_exec-disk_io.o vstafs_stage1_5_exec-stage1_5.o \
		vstafs_stage1_5_exec-fsys_vstafs.o vstafs_stage1_5_exec-bios.o

JFS15ASMOBJS=	jfs_stage1_5_exec-start.o jfs_stage1_5_exec-asm.o
JFS15OBJS=	jfs_stage1_5_exec-common.o jfs_stage1_5_exec-char_io.o \
		jfs_stage1_5_exec-disk_io.o jfs_stage1_5_exec-stage1_5.o \
		jfs_stage1_5_exec-fsys_jfs.o jfs_stage1_5_exec-bios.o

XFS15ASMOBJS=	xfs_stage1_5_exec-start.o xfs_stage1_5_exec-asm.o
XFS15OBJS=	xfs_stage1_5_exec-common.o xfs_stage1_5_exec-char_io.o \
		xfs_stage1_5_exec-disk_io.o xfs_stage1_5_exec-stage1_5.o \
		xfs_stage1_5_exec-fsys_xfs.o xfs_stage1_5_exec-bios.o

ISO966015ASMOBJS=	iso9660_stage1_5_exec-start_eltorito.o \
		iso9660_stage1_5_exec-asm.o
ISO966015OBJS=	iso9660_stage1_5_exec-common.o iso9660_stage1_5_exec-char_io.o \
		iso9660_stage1_5_exec-disk_io.o iso9660_stage1_5_exec-stage1_5.o \
		iso9660_stage1_5_exec-fsys_iso9660.o iso9660_stage1_5_exec-bios.o

DISKLESSASMOBJS=  diskless_exec-asm.o
DISKLESSOBJS=	diskless_exec-bios.o diskless_exec-boot.o \
		diskless_exec-builtins.o diskless_exec-char_io.o \
		diskless_exec-cmdline.o diskless_exec-common.o \
		diskless_exec-console.o diskless_exec-disk_io.o \
		diskless_exec-fsys_ext2fs.o diskless_exec-fsys_fat.o \
		diskless_exec-fsys_ffs.o diskless_exec-fsys_iso9660.o \
		diskless_exec-fsys_jfs.o diskless_exec-fsys_minix.o \
		diskless_exec-fsys_reiserfs.o diskless_exec-fsys_ufs2.o \
		diskless_exec-fsys_vstafs.o diskless_exec-fsys_xfs.o \
		diskless_exec-gunzip.o diskless_exec-hercules.o \
		diskless_exec-md5.o diskless_exec-serial.o \
		diskless_exec-smp-imps.o diskless_exec-stage2.o \
		diskless_exec-terminfo.o diskless_exec-tparm.o

DIST=		${.CURDIR}/../../../dist/grub
.PATH:		${DIST}/stage2

CFLAGS=		-I${.CURDIR}
CFLAGS+=	-I${DIST}/stage2
CFLAGS+=	-I${.CURDIR}/../include
CFLAGS+=	-I${DIST}/stage1

CFLAGS+=	-Wall -Wmissing-prototypes -Wunused -Wshadow 
CFLAGS+=	-Wpointer-arith -falign-jumps=1 -falign-loops=1 
CFLAGS+=	-falign-functions=1 -Wundef -c

FSYSFLAGS=	-DFSYS_EXT2FS=1
FSYSFLAGS+=	-DFSYS_FAT
FSYSFLAGS+=	-DFSYS_FFS=1
FSYSFLAGS+=	-DFSYS_ISO9660=1
FSYSFLAGS+=	-DFSYS_JFS=1
FSYSFLAGS+=	-DFSYS_MINIX=1
FSYSFLAGS+=	-DFSYS_REISERFS=1
FSYSFLAGS+=	-DFSYS_UFS2=1
FSYSFLAGS+=	-DFSYS_VSTAFS=1
FSYSFLAGS+=	-DFSYS_XFS=1
FSYSFLAGS+=	-DUSE_MD5_PASSWORDS=1

SUPPORTFLAGS+=	-DSUPPORT_SERIAL=1
SUPPORTFLAGS+=	-DSUPPORT_HERCULES=1
SUPPORTFLAGS+=	-DHAVE_CONFIG_H
SUPPORTFLAGS+=	-DHAVE_LIBCURSES=1
SUPPORTFLAGS+=	-fwritable-strings

PRECFLAGS=	-Os -fno-builtin -nostdinc
PRECFLAGS+=	${SUPPORTFLAGS}
PRECFLAGS+=	${FSYSFLAGS}
PRECFLAGS+=	-I${DIST}/netboot
PRECFLAGS+=	-DFSYS_TFTP=1
PRECFLAGS+=	-DSUPPORT_NETBOOT=1
PRECFLAGS+=	${CFLAGS}

LIBCFLAGS=	-O2
LIBCFLAGS+=	-DGRUB_UTIL=1
LIBCFLAGS+=	${SUPPORTFLAGS}
LIBCFLAGS+=	${FSYSFLAGS}
LIBCFLAGS+=	${CFLAGS}
LIBCFLAGS+=	-I${DIST}/lib

STARTCFLAGS=	-Os -fno-builtin -nostdinc
STARTCFLAGS+=	${SUPPORTFLAGS}
STARTCFLAGS+=	${CFLAGS} -I${.CURDIR}

S15CFLAGS=	-Os -fno-builtin -nostdinc
S15CFLAGS+=	${SUPPORTFLAGS}
S15CFLAGS+=	-DNO_DECOMPRESSION=1
S15CFLAGS+=	-DSTAGE1_5=1
S15CFLAGS+=	-DNO_BLOCK_FILES=1
S15CFLAGS+=	${CFLAGS}

.MAIN: all
all: ${STAGE2} ${STAGE2ELTORITO} libgrub.a ${STAGE15} nbgrub pxegrub

${STAGE2}: pre_${.TARGET} start
	cat start pre_${.TARGET} > ${.TARGET}

${STAGE2ELTORITO}: pre_stage2 start_eltorito
	cat start_eltorito pre_stage2 > ${.TARGET}

${STAGE15}: ${.TARGET}.exec
	objcopy -O binary ${.TARGET}.exec ${.TARGET}

pre_stage2: pre_stage2.exec
	objcopy -O binary pre_stage2.exec pre_stage2
	rm -f stage2_size.h
	set dummy `ls -l pre_stage2`; \
	echo "#define STAGE2_SIZE $$6" > stage2_size.h

pre_stage2.exec: ${PREASMOBJS} ${PREOBJS}
	${CC} -g -o ${.TARGET} -nostdlib -Wl,-N -Wl,-Ttext -Wl,8200 \
		${PREASMOBJS} ${PREOBJS} ../netboot/libdrivers.a  

${PREASMOBJS}:
	${CC} ${PRECFLAGS} -o ${.TARGET} \
		${DIST}/stage2/${.TARGET:S/pre_stage2_exec-//:.o=.S}

${PREOBJS}:
	${CC} ${PRECFLAGS} -o ${.TARGET} \
		${DIST}/stage2/${.TARGET:S/pre_stage2_exec-//:.o=.c}

libgrub.a: ${LIBOBJS}
	ar cru ${.TARGET} ${LIBOBJS}
	ranlib ${.TARGET}

${LIBOBJS}:
	${CC} ${LIBCFLAGS} -o ${.TARGET} \
		${DIST}/stage2/${.TARGET:S/libgrub_a-//:.o=.c}

start: start.exec
	objcopy -O binary start.exec start

start.exec: ${STARTASMOBJS}
	${CC} -g -o ${.TARGET} -nostdlib -Wl,-N -Wl,-Ttext -Wl,8000 \
		${STARTASMOBJS}

${STARTASMOBJS}:
	${CC} ${STARTCFLAGS} -o ${.TARGET} \
		${DIST}/stage2/${.TARGET:S/start_exec-//:.o=.S}

start_eltorito: start_eltorito.exec
	objcopy -O binary start_eltorito.exec start_eltorito

start_eltorito.exec: ${STARTELTORITOASMOBJS}
	${CC} -g -o ${.TARGET} -nostdlib -Wl,-N -Wl,-Ttext -Wl,7000 \
		${STARTELTORITOASMOBJS}

${STARTELTORITOASMOBJS}:
	${CC} ${STARTCFLAGS} -o ${.TARGET} \
		${DIST}/stage2/${.TARGET:S/start_eltorito_exec-//:.o=.S}

e2fs_stage1_5.exec: ${E2FS15ASMOBJS} ${E2FS15OBJS}
	${CC} -g -o ${.TARGET} -nostdlib -Wl,-N -Wl,-Ttext -Wl,2000 \
		${E2FS15ASMOBJS} ${E2FS15OBJS}

${E2FS15ASMOBJS}:
	${CC} ${S15CFLAGS} -DFSYS_EXT2FS=1 -o ${.TARGET} \
		${DIST}/stage2/${.TARGET:S/e2fs_stage1_5_exec-//:.o=.S}

${E2FS15OBJS}:
	${CC} ${S15CFLAGS} -DFSYS_EXT2FS=1 -o ${.TARGET} \
		${DIST}/stage2/${.TARGET:S/e2fs_stage1_5_exec-//:.o=.c}

fat_stage1_5.exec: ${FAT15ASMOBJS} ${FAT15OBJS}
	${CC} -g -o ${.TARGET} -nostdlib -Wl,-N -Wl,-Ttext -Wl,2000 \
		${FAT15ASMOBJS} ${FAT15OBJS}

${FAT15ASMOBJS}:
	${CC} ${S15CFLAGS} -DFSYS_FAT=1 -o ${.TARGET} \
		${DIST}/stage2/${.TARGET:S/fat_stage1_5_exec-//:.o=.S}

${FAT15OBJS}:
	${CC} ${S15CFLAGS} -DFSYS_FAT=1 -o ${.TARGET} \
		${DIST}/stage2/${.TARGET:S/fat_stage1_5_exec-//:.o=.c}

ffs_stage1_5.exec: ${FFS15ASMOBJS} ${FFS15OBJS}
	${CC} -g -o ${.TARGET} -nostdlib -Wl,-N -Wl,-Ttext -Wl,2000 \
		${FFS15ASMOBJS} ${FFS15OBJS}

${FFS15ASMOBJS}:
	${CC} ${S15CFLAGS} -DFSYS_FFS=1 -o ${.TARGET} \
		${DIST}/stage2/${.TARGET:S/ffs_stage1_5_exec-//:.o=.S}

${FFS15OBJS}:
	${CC} ${S15CFLAGS} -DFSYS_FFS=1 -o ${.TARGET} \
		${DIST}/stage2/${.TARGET:S/ffs_stage1_5_exec-//:.o=.c}

ufs2_stage1_5.exec: ${UFS215ASMOBJS} ${UFS215OBJS}
	${CC} -g -o ${.TARGET} -nostdlib -Wl,-N -Wl,-Ttext -Wl,2000 \
		${UFS215ASMOBJS} ${UFS215OBJS}

${UFS215ASMOBJS}:
	${CC} ${S15CFLAGS} -DFSYS_UFS2=1 -o ${.TARGET} \
		${DIST}/stage2/${.TARGET:S/ufs2_stage1_5_exec-//:.o=.S}

${UFS215OBJS}:
	${CC} ${S15CFLAGS} -DFSYS_UFS2=1 -o ${.TARGET} \
		${DIST}/stage2/${.TARGET:S/ufs2_stage1_5_exec-//:.o=.c}

minix_stage1_5.exec: ${MINIX15ASMOBJS} ${MINIX15OBJS}
	${CC} -g -o ${.TARGET} -nostdlib -Wl,-N -Wl,-Ttext -Wl,2000 \
		${MINIX15ASMOBJS} ${MINIX15OBJS}

${MINIX15ASMOBJS}:
	${CC} ${S15CFLAGS} -DFSYS_MINIX=1 -o ${.TARGET} \
		${DIST}/stage2/${.TARGET:S/minix_stage1_5_exec-//:.o=.S}

${MINIX15OBJS}:
	${CC} ${S15CFLAGS} -DFSYS_MINIX=1 -o ${.TARGET} \
		${DIST}/stage2/${.TARGET:S/minix_stage1_5_exec-//:.o=.c}

reiserfs_stage1_5.exec: ${REISERFS15ASMOBJS} ${REISERFS15OBJS}
	${CC} -g -o ${.TARGET} -nostdlib -Wl,-N -Wl,-Ttext -Wl,2000 \
		${REISERFS15ASMOBJS} ${REISERFS15OBJS}

${REISERFS15ASMOBJS}:
	${CC} ${S15CFLAGS} -DFSYS_REISERFS=1 -o ${.TARGET} \
		${DIST}/stage2/${.TARGET:S/reiserfs_stage1_5_exec-//:.o=.S}

${REISERFS15OBJS}:
	${CC} ${S15CFLAGS} -DFSYS_REISERFS=1 -o ${.TARGET} \
		${DIST}/stage2/${.TARGET:S/reiserfs_stage1_5_exec-//:.o=.c}

vstafs_stage1_5.exec: ${VSTAFS15ASMOBJS} ${VSTAFS15OBJS}
	${CC} -g -o ${.TARGET} -nostdlib -Wl,-N -Wl,-Ttext -Wl,2000 \
		${VSTAFS15ASMOBJS} ${VSTAFS15OBJS}

${VSTAFS15ASMOBJS}:
	${CC} ${S15CFLAGS} -DFSYS_VSTAFS=1 -o ${.TARGET} \
		${DIST}/stage2/${.TARGET:S/vstafs_stage1_5_exec-//:.o=.S}

${VSTAFS15OBJS}:
	${CC} ${S15CFLAGS} -DFSYS_VSTAFS=1 -o ${.TARGET} \
		${DIST}/stage2/${.TARGET:S/vstafs_stage1_5_exec-//:.o=.c}

jfs_stage1_5.exec: ${JFS15ASMOBJS} ${JFS15OBJS}
	${CC} -g -o ${.TARGET} -nostdlib -Wl,-N -Wl,-Ttext -Wl,2000 \
		${JFS15ASMOBJS} ${JFS15OBJS}

${JFS15ASMOBJS}:
	${CC} ${S15CFLAGS} -DFSYS_JFS=1 -o ${.TARGET} \
		${DIST}/stage2/${.TARGET:S/jfs_stage1_5_exec-//:.o=.S}

${JFS15OBJS}:
	${CC} ${S15CFLAGS} -DFSYS_JFS=1 -o ${.TARGET} \
		${DIST}/stage2/${.TARGET:S/jfs_stage1_5_exec-//:.o=.c}

xfs_stage1_5.exec: ${XFS15ASMOBJS} ${XFS15OBJS}
	${CC} -g -o ${.TARGET} -nostdlib -Wl,-N -Wl,-Ttext -Wl,2000 \
		${XFS15ASMOBJS} ${XFS15OBJS}

${XFS15ASMOBJS}:
	${CC} ${S15CFLAGS} -DFSYS_XFS=1 -o ${.TARGET} \
		${DIST}/stage2/${.TARGET:S/xfs_stage1_5_exec-//:.o=.S}

${XFS15OBJS}:
	${CC} ${S15CFLAGS} -DFSYS_XFS=1 -o ${.TARGET} \
		${DIST}/stage2/${.TARGET:S/xfs_stage1_5_exec-//:.o=.c}

iso9660_stage1_5.exec: ${ISO966015ASMOBJS} ${ISO966015OBJS}
	${CC} -g -o ${.TARGET} -nostdlib -Wl,-N -Wl,-Ttext -Wl,2000 \
		${ISO966015ASMOBJS} ${ISO966015OBJS}

${ISO966015ASMOBJS}:
	${CC} ${S15CFLAGS} -DFSYS_ISO9660=1 -o ${.TARGET} \
		${DIST}/stage2/${.TARGET:S/iso9660_stage1_5_exec-//:.o=.S}

${ISO966015OBJS}:
	${CC} ${S15CFLAGS} -DFSYS_ISO9660=1 -o ${.TARGET} \
		${DIST}/stage2/${.TARGET:S/iso9660_stage1_5_exec-//:.o=.c}

nbgrub: diskless nbloader
	cat nbloader diskless > ${.TARGET}

nbloader: diskless_size.h
	${CC} ${PRECFLAGS} -o ${.TARGET}_exec-${.TARGET}.o ${DIST}/stage2/${.TARGET}.S
	${CC} -g -o ${.TARGET}.exec -nostdlib -Wl,-N -Wl,-Ttext -Wl,0 \
		${.TARGET}_exec-${.TARGET}.o
	objcopy -O binary ${.TARGET}.exec ${.TARGET}

pxegrub: diskless pxeloader
	cat pxeloader diskless > ${.TARGET}

pxeloader: diskless_size.h
	${CC} ${PRECFLAGS} -o ${.TARGET}_exec-${.TARGET}.o ${DIST}/stage2/${.TARGET}.S
	${CC} -g -o ${.TARGET}.exec -nostdlib -Wl,-N -Wl,-Ttext -Wl,7C00 \
		${.TARGET}_exec-${.TARGET}.o
	objcopy -O binary ${.TARGET}.exec ${.TARGET}

diskless_size.h: diskless
	set dummy `ls -l diskless`; \
	echo "#define DISKLESS_SIZE $6" > diskless_size.h

diskless: ${DISKLESSASMOBJS} ${DISKLESSOBJS}
	${CC} -g -o ${.TARGET}.exec -nostdlib -Wl,-N -Wl,-Ttext -Wl,8200 \
		${DISKLESSASMOBJS} ${DISKLESSOBJS} ../netboot/libdrivers.a
	objcopy -O binary ${.TARGET}.exec ${.TARGET}

${DISKLESSASMOBJS}:
	${CC} ${PRECFLAGS} -DDISKLESS=1 -o ${.TARGET} \
		${DIST}/stage2/${.TARGET:S/diskless_exec-//:.o=.S}

${DISKLESSOBJS}:
	${CC} ${PRECFLAGS} -DDISKLESS=1 -o ${.TARGET} \
		${DIST}/stage2/${.TARGET:S/diskless_exec-//:.o=.c}

install:
	${INSTALL} -c -m 644 ${STAGE2} ${STAGE2ELTORITO} ${STAGE15} nbgrub pxegrub \
		${DESTDIR}/usr/mdec/grub/${TARGET_HOSTTYPE}-ssd

.if defined(NEW_GLIBC)
libgrub_a-bios.c:
	for i in curses.h ncurses.h ncurses_dll.h unctrl.h; do \
		rm -f ${.CURDIR}/../include/$$i; \
		cp ${DESTDIR}/usr/include/$$i ${.CURDIR}/../include; \
	done
.endif

clean:
	rm -f *.o *.exec *.a *.h pre_* start ${STAGE2} start_eltorito \
		${STAGE2ELTORITO} ${STAGE15} \
		nbgrub pxegrub nbloader pxeloader diskless diskless_size.h
.if defined(NEW_GLIBC)
	for i in curses.h ncurses.h ncurses_dll.h unctrl.h; do \
	rm -f ${.CURDIR}/../include/$$i; \
	done
.endif

cleandir:
