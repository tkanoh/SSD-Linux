#	$ssdlinux: Makefile,v 1.3 2002/10/03 07:19:20 yamagata Exp $

.include <bsd.own.mk>

PROG=		bzip2

DIST=		${.CURDIR}/../../dist/${PROG}
.PATH:		${DIST}

CPPFLAGS+=	-I${DIST}
CPPFLAGS+=	-Wall -Winline -fomit-frame-pointer -fno-strength-reduce
CPPFLAGS+=	-D_FILE_OFFSET_BITS=64

LIBBZ2DIR=	${.CURDIR}/../../lib/libbz2
LDDIR!=         cd ${LIBBZ2DIR} && ${PRINTOBJDIR}
LDADD+=         -L${LDDIR} -lbz2
DPADD+=         ${LIBNCURSES}/libbz2.a

LINKS+=		${BINDIR}/${PROG} ${BINDIR}/bunzip2
LINKS+=		${BINDIR}/${PROG} ${BINDIR}/bzcat

.include <bsd.prog.mk>
