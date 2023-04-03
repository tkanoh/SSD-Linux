#	$ssdlinux: Makefile,v 1.2 2002/12/29 16:52:16 kanoh Exp $
#	$NetBSD: Makefile,v 1.1.1.1 1999/12/20 05:57:40 sakamoto Exp $

.include <bsd.own.mk>

PROG=   crunchide
SRCS=	crunchide.c
MAN=	crunchide.1
#MKMAN=	no

BINUTILSDIR=	${.CURDIR}/../../binutils/build
CPPFLAGS+=	-I./
LDADD+=		-L${BINUTILSDIR}/bfd -lbfd
LDADD+=		-L${BINUTILSDIR}/libiberty -liberty
DPADD+=		${BINUTILSDIR}/bfd/libbfd.a
DPADD+=		${BINUTILSDIR}/libiberty/libiberty.a

.include <bsd.prog.mk>
