#	$ssdlinux: Makefile,v 1.10 2004/11/05 06:26:59 yamagata Exp $

.include <bsd.own.mk>

LIB=		proc
SRCS=		alloc.c devname.c escape.c ksym.c pwcache.c \
		readproc.c sig.c slab.c sysinfo.c version.c whattime.c
INCS=		devname.h procps.h readproc.h sig.h \
		sysinfo.h version.h whattime.h
INCSDIR=	/usr/include/${LIB}

MKPIC=		yes
MKPICLIB=	no
MKPICINSTALL=	no
MKMAN=		no

DIST=		${.CURDIR}/../../dist/procps/${LIB}
.PATH:		${DIST}

NOGCCERROR=	yes

.include <bsd.lib.mk>

CPPFLAGS+=	-D_GNU_SOURCE -fno-common -ffast-math -I ${DIST} \
		-W -Wall -Wshadow -Wcast-align -Wredundant-decls \
		-Wbad-function-cast -Wcast-qual -Wwrite-strings \
		-Waggregate-return \
		-Wstrict-prototypes -Wmissing-prototypes \
		-fpic
CPPFLAGS+=	-DVERSION=\"${SHLIB_MAJOR}\" -DSUBVERSION=\"${SHLIB_MINOR}\"
.ifdef SHLIB_TEENY
CPPFLAGS+=	-DMINORVERSION=\"${SHLIB_TEENY}\"
.endif

bugfix:
	rm -f libproc.so.${SHLIB_FULLVERSION}
	${CC} -shared -Wl,-soname,libproc.so.${SHLIB_FULLVERSION} \
		-o libproc.so.${SHLIB_FULLVERSION} ${SRCS:M*.c:.c=.o} -lc
