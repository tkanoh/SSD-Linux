#	$ssdlinux: Makefile,v 1.3 2003/09/10 08:08:07 yamagata Exp $

.include <bsd.own.mk>

LIBOBJS=	libdrivers_a-config.o libdrivers_a-fsys_tftp.o \
		libdrivers_a-main.o libdrivers_a-misc.o \
		libdrivers_a-pci.o  libdrivers_a-timer.o

DRVOBJS=	eepro100.o

DIST=		${.CURDIR}/../../../dist/grub
.PATH:		${DIST}/netboot

CFLAGS=		-I${DIST}/netboot
CFLAGS+=	-I${DIST}/stage2
CFLAGS+=	-I${.CURDIR}/../include
CFLAGS+=	-I${DIST}/stage1

CFLAGS+=	-Wall -Wmissing-prototypes -Wunused -Wshadow 
CFLAGS+=	-Wpointer-arith -falign-jumps=1 -falign-loops=1 
CFLAGS+=	-falign-functions=1 -Wundef -g -c

LIBCFLAGS=	-DHAVE_CONFIG_H
LIBCFLAGS+=	${CFLAGS}
LIBCFLAGS+=	-Os
LIBCFLAGS+=	-nostdinc
LIBCFLAGS+=	-DFSYS_TFTP=1
LIBCFLAGS+=	-DINCLUDE_EEPRO100=1	
LIBCFLAGS+=	-DCONGESTED=1
LIBCFLAGS+=	-DNE_SCAN=0x280,0x300,0x320,0x340
LIBCFLAGS+=	-DWD_DEFAULT_MEM=0xCC000

.MAIN: all
all: libdrivers.a

libdrivers.a: ${LIBOBJS} ${DRVOBJS}
	ar cru ${.TARGET} ${LIBOBJS} ${DRVOBJS}
	ranlib ${.TARGET}

${LIBOBJS}:
	${CC} ${LIBCFLAGS} -o ${.TARGET} \
		${DIST}/netboot/${.TARGET:S/libdrivers_a-//:.o=.c}

${DRVOBJS}:
	${CC} ${LIBCFLAGS} -o ${.TARGET} \
		${DIST}/netboot/${.TARGET:M*.o:.o=.c}

install:

clean:
	rm -f *.o libdrivers.a

cleandir:
