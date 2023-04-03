#	$ssdlinux: Makefile,v 1.3 2003/07/09 06:15:29 yamagata Exp $

.include <bsd.own.mk>

LIB=		common
SRCS=		getopt.c getopt1.c device.c
MKMAN=		no

DIST=		${.CURDIR}/../../../dist/grub
.PATH:		${DIST}/lib

CPPFLAGS+=	-DHAVE_CONFIG_H
CPPFLAGS+=	-DHAVE_LIBCURSES=1
CPPFLAGS+=	-Wall -Wmissing-prototypes -Wunused 
CPPFLAGS+=	-Wshadow -Wpointer-arith
CPPFLAGS+=	-falign-jumps=1 -falign-loops=1
CPPFLAGS+=	-falign-functions=1 -Wundef
CPPFLAGS+=	-I${.CURDIR}/../include
CPPFLAGS+=	-I${DIST}/lib
CPPFLAGS+=	-I${DIST}/stage1
CPPFLAGS+=	-I${DIST}/stage2

NOGCCERROR=	yes

libinstall::

.include <bsd.lib.mk>
