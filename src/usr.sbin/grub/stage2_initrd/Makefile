#	$ssdlinux: Makefile,v 1.1 2004/06/18 06:07:09 yamagata Exp $

.include <bsd.own.mk>

STAGE2=		stage2

PREASMOBJS=	pre_stage2_exec-asm.o
PREOBJS=	pre_stage2_exec-bios.o pre_stage2_exec-boot.o \
		pre_stage2_exec-builtins.o pre_stage2_exec-char_io.o \
		pre_stage2_exec-cmdline.o pre_stage2_exec-common.o \
		pre_stage2_exec-console.o pre_stage2_exec-disk_io.o \
		pre_stage2_exec-fsys_ext2fs.o \
		pre_stage2_exec-gunzip.o pre_stage2_exec-hercules.o \
		pre_stage2_exec-md5.o pre_stage2_exec-serial.o \
		pre_stage2_exec-smp-imps.o pre_stage2_exec-stage2.o \
		pre_stage2_exec-terminfo.o pre_stage2_exec-tparm.o

STARTASMOBJS=	start_exec-start.o

DIST=		${.CURDIR}/../../../dist/grub
.PATH:		${DIST}/stage2

CFLAGS=		-I${DIST}/stage2
CFLAGS+=	-I${.CURDIR}/../include
CFLAGS+=	-I${DIST}/stage1

CFLAGS+=	-Wall -Wmissing-prototypes -Wunused -Wshadow 
CFLAGS+=	-Wpointer-arith -falign-jumps=1 -falign-loops=1 
CFLAGS+=	-falign-functions=1 -Wundef -c

FSYSFLAGS=	-DFSYS_EXT2FS=1
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

STARTCFLAGS=	-Os -fno-builtin -nostdinc
STARTCFLAGS+=	${SUPPORTFLAGS}
STARTCFLAGS+=	${CFLAGS} -I${.CURDIR}

.MAIN: all
all: ${STAGE2}

${STAGE2}: pre_${.TARGET} start
	cat start pre_${.TARGET} > ${.TARGET}

pre_stage2: pre_stage2.exec
	objcopy -O binary pre_stage2.exec pre_stage2
	rm -f stage2_size.h
	set dummy `ls -l pre_stage2`; \
	echo "#define STAGE2_SIZE $$6" > stage2_size.h

pre_stage2.exec: ${PREASMOBJS} ${PREOBJS}
	${CC} -g -o ${.TARGET} -nostdlib -Wl,-N -Wl,-Ttext -Wl,8200 ${PREASMOBJS} ${PREOBJS} ../netboot/libdrivers.a -lc

${PREASMOBJS}:
	${CC} ${PRECFLAGS} -o ${.TARGET} \
		${DIST}/stage2/${.TARGET:S/pre_stage2_exec-//:.o=.S}

${PREOBJS}:
	${CC} ${PRECFLAGS} -o ${.TARGET} \
		${DIST}/stage2/${.TARGET:S/pre_stage2_exec-//:.o=.c}

start: start.exec
	objcopy -O binary start.exec start

start.exec: ${STARTASMOBJS}
	${CC} -g -o ${.TARGET} -nostdlib -Wl,-N -Wl,-Ttext -Wl,8000 ${STARTASMOBJS}

${STARTASMOBJS}:
	${CC} ${STARTCFLAGS} -o ${.TARGET} \
		${DIST}/stage2/${.TARGET:S/start_exec-//:.o=.S}

${STARTELTORITOASMOBJS}:
	${CC} ${STARTCFLAGS} -o ${.TARGET} \
		${DIST}/stage2/${.TARGET:S/start_eltorito_exec-//:.o=.S}

install:

clean:
	rm -f *.o *.exec *.a *.h pre_* start ${STAGE2}

cleandir:
