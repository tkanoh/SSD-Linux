#	$ssdlinux: Makefile,v 1.5 2003/07/09 06:14:21 yamagata Exp $

.include <bsd.own.mk>

STAGE1=		stage1

DIST=		${.CURDIR}/../../../dist/grub
.PATH:		${DIST}/stage1

CFLAGS=		-fno-builtin -nostdinc
CFLAGS+=	-DHAVE_CONFIG_H
CFLAGS+=	-DHAVE_LIBCURSES=1
CFLAGS+=	-I${DIST}/stage1
CFLAGS+=	-I${.CURDIR}/../include
CFLAGS+=	-I${DIST}/stage2
CFLAGS+=	-Wall -Wmissing-prototypes -Wunused -Wshadow 
CFLAGS+=	-Wpointer-arith -falign-jumps=1 -falign-loops=1 
CFLAGS+=	-falign-functions=1 -Wundef -c

.MAIN: all
all: ${STAGE1}

${STAGE1}:  ${.TARGET}.exec
	objcopy -O binary ${.TARGET}.exec ${.TARGET}

${STAGE1}.exec: ${.TARGET:M*.exec:.exec=.o}
	${CC} -g  -nostdlib -Wl,-N,-Ttext,7C00 -o ${.TARGET} ${.TARGET:M*.exec:.exec=.o}

${STAGE1}.o:
	${CC} ${CFLAGS} -o ${.TARGET} ${DIST}/stage1/${.TARGET:M*.o:.o=.S}

install:
	${INSTALL} -c -m 644 ${STAGE1} ${DESTDIR}/usr/mdec/grub/${TARGET_HOSTTYPE}-ssd

clean:
	rm -f *.o *.exec ${STAGE1}

cleandir:
