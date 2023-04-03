#	$ssdlinux: Makefile,v 1.3 2005/02/07 05:20:14 yamagata Exp $

.include <bsd.own.mk>

PROG=		strace		
SRCS=		strace.c syscall.c util.c desc.c file.c ipc.c \
		io.c ioctl.c mem.c net.c process.c bjm.c \
		resource.c signal.c sock.c system.c term.c \
		time.c proc.c stream.c		
MAN=		${PROG}.1
SCRIPTS=	strace-graph

DIST=		${.CURDIR}/../../dist/${PROG}
.PATH:		${DIST}

CPPFLAGS+=	-I${.CURDIR}
CPPFLAGS+=	-I${DIST}/linux/${TARGET_HOSTTYPE}
CPPFLAGS+=	-I${DIST}/linux
.if ${TARGET_HOSTTYPE} == "i386"
CPPFLAGS+=	-DHAVE_LITTLE_ENDIAN_LONG_LONG=1
CPPFLAGS+=	-DHAVE_STRUCT___OLD_KERNEL_STAT=1
CPPFLAGS+=	-DHAVE_SYS_REG_H=1
CPPFLAGS+=	-DI386=1
.elif ${TARGET_HOSTTYPE} == "powerpc"
CPPFLAGS+=	-DPOWERPC=1
.endif
CPPFLAGS+=	-DHAVE_CONFIG_H
CPPFLAGS+=	-Wall -g -O2
.if ${GLIBC_VERSION} == "2.3.3"
CPPFLAGS+=	-DHAVE_SYS_EPOLL_H=1
.elif ${GLIBC_VERSION} == "2.3.1"
NOGCCERROR=	yes
.endif

.include <bsd.prog.mk>
