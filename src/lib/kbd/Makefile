#	$ssdlinux: Makefile,v 1.3 2002/11/08 07:02:31 yamagata Exp $

LIB=		kbd
SRCS=		findfile.c getfd.c kdfontop.c kdmapop.c ksyms.c \
		loadunimap.c mapscrn.c psffontop.c utf8.c xmalloc.c
MKMAN=		no
CLEANFILES=	analyze.c

DIST=		${.CURDIR}/../../dist/kbd
.PATH:		${DIST}/src

CPPFLAGS+=	-Wall -Wmissing-prototypes -Wstrict-prototypes
CPPFLAGS+=	-DDATADIR=\"/usr/share/kbd\" -I${.CURDIR}/dummy -I${DIST}/src

all: analyze.c

analyze.c:
	rm -f ${.TARGET}
	flex -8 -t ${DIST}/src/analyze.l > ${.TARGET}

libinstall::

.include <bsd.lib.mk>
