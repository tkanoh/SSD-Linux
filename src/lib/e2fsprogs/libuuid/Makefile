#	$ssdlinux: Makefile,v 1.8 2005/03/02 05:58:56 yamagata Exp $

.include <bsd.own.mk>

LIB=		uuid
SRCS=		clear.c compare.c copy.c gen_uuid.c isnull.c pack.c \
		parse.c unpack.c unparse.c uuid_time.c
MAN=		uuid.3 uuid_clear.3 uuid_compare.3 uuid_copy.3 \
		uuid_generate.3 uuid_is_null.3 uuid_parse.3 \
		uuid_time.3 uuid_unparse.3
MKPIC=		yes
MKPICINSTALL=	no

FILES=		uuid.h
FILES+=		../include/${LIB}/${LIB}_types.h
FILESMODE=	444
FILESDIR=	/usr/include/${LIB}

DIST=		${.CURDIR}/../../../dist/e2fsprogs
.PATH:		${DIST}/lib/${LIB}

.include "${.CURDIR}/../Makefile.cflags"
CPPFLAGS+=	-I${.CURDIR}

CLEANFILES=	${MAN}
CLEANFILES+=	../include/ext2fs/ext2_types.h
CLEANFILES+=	../include/${LIB}/${LIB}_types.h

clear.c: ${LIB}_types.h

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

.include <bsd.lib.mk>
