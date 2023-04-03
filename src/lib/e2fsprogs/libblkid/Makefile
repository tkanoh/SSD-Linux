#	$ssdlinux: Makefile,v 1.4 2005/03/02 05:59:51 yamagata Exp $

.include <bsd.own.mk>

LIB=		blkid
SRCS=		cache.c dev.c devname.c devno.c getsize.c llseek.c probe.c \
		read.c resolve.c save.c tag.c version.c
MAN=		lib${LIB}.3
MKPIC=		yes
MKPICINSTALL=	no

FILES=		blkid.h
FILES+=		../include/${LIB}/${LIB}_types.h
FILESMODE=	444
FILESDIR=	/usr/include/${LIB}

DIST=		${.CURDIR}/../../../dist/e2fsprogs
.PATH:		${DIST}/lib/${LIB}

.include "${.CURDIR}/../Makefile.cflags"
CPPFLAGS+=	-I${.CURDIR}

CLEANFILES=	${MAN}
CLEANFILES+=	../include/${LIB}/${LIB}_types.h

cache.c: ${LIB}_types.h

${LIB}_types.h:
	if [ ! -d ../include/${LIB} ]; then \
		mkdir -p ../include/${LIB}; \
	fi
	sed -e 's,@SIZEOF_SHORT@,2,' \
	    -e 's,@SIZEOF_INT@,4,' \
	    -e 's,@SIZEOF_LONG@,4,' \
	    -e 's,@SIZEOF_LONG_LONG@,8,' \
		${DIST}/lib/${LIB}/${.TARGET}.in > ../include/${LIB}/${.TARGET}

${MAN}:
	../util/subst -f ../util/subst.conf ${DIST}/lib/${LIB}/${.TARGET}.in ${.TARGET}

clean:
	if [ -d ../include/${LIB} ]; then \
		rmdir ../include/${LIB}; \
	fi
	if [ -d ../include/ext2fs ]; then \
		if [ ! -f ../include/ext2fs/* ]; then \
			rmdir ../include/ext2fs; \
			rmdir ../include; \
		fi; \
	fi

.include <bsd.lib.mk>
