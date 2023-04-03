#	$ssdlinux: Makefile,v 1.2 2002/06/04 08:58:44 yamagata Exp $

.include <bsd.own.mk>

PROG=		biff

DIST=		${.CURDIR}/../../dist/usagi-tool/src/biff+comsat/${PROG}
.PATH:		${DIST}

CPPFLAGS+=	-Wall -W -Wpointer-arith -Wbad-function-cast -Wcast-qual \
		-Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations \
		-Wnested-externs -Winline -I${DIST} -I${.CURDIR}

.include <bsd.prog.mk>
