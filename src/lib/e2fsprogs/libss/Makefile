#	$ssdlinux: Makefile,v 1.8 2004/07/13 02:48:07 yamagata Exp $

.include <bsd.own.mk>

LIB=		ss
SRCS=		ss_err.c std_rqs.c invocation.c help.c execute_cmd.c listen.c \
		parse.c error.c prompt.c request_tbl.c list_rqs.c pager.c \
		requests.c data.c get_readline.c
MKPIC=		yes
MKPICINSTALL=	no
MKMAN=		no

FILES=		ss.h
FILES+=		../include/${LIB}/${LIB}_err.h
FILESMODE=	444
FILESDIR=	/usr/include/${LIB}

DIST=		${.CURDIR}/../../../dist/e2fsprogs
.PATH:		${DIST}/lib/${LIB}

.include "${.CURDIR}/../Makefile.cflags"

CPPFLAGS+=	-I${.CURDIR}

CLEANFILES=	ss_err.c ../include/${LIB}/${LIB}_err.h
CLEANFILES+=	std_rqs.c mk_cmds
 
mk_cmds:
	../util/subst -f ../util/subst.conf ${DIST}/lib/${LIB}/mk_cmds.sh.in ${.TARGET}
	chmod +x ${.TARGET}

ss_err.c: 
	../libcom_err/compile_et ${DIST}/lib/${LIB}/${LIB}_err.et
	mkdir -p ../include/${LIB}
	mv ${LIB}_err.h ../include/${LIB}/${LIB}_err.h

std_rqs.c: mk_cmds
	DIR=${DIST}/lib/${LIB} _SS_DIR_OVERRIDE=. ./mk_cmds ${DIST}/lib/${LIB}/std_rqs.ct

clean:
	if [ -d ../include/${LIB} ]; then \
		rmdir ../include/${LIB}; \
	fi

.include <bsd.lib.mk>
