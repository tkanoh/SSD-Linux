#	$ssdlinux: Makefile,v 1.7 2005/01/06 03:28:10 yamagata Exp $

.include <bsd.own.mk>

LIB=		tar
SRCS=		prepargs.c rtapelib.c
SRCS+=		allocsa.c
SRCS+=		argp-ba.c argp-eexst.c \
		argp-fmtstream.c argp-fs-xinl.c argp-help.c \
		argp-parse.c argp-pv.c argp-pvh.c argp-xinl.c
SRCS+=		argmatch.c
SRCS+=		backupfile.c
SRCS+=		dirname.c basename.c stripslash.c
SRCS+=		exclude.c
SRCS+=		exitfail.c
SRCS+=		full-write.c
SRCS+=		getdate.c
SRCS+=		getopt.c getopt1.c
SRCS+=		gettime.c
SRCS+=		hash.c
SRCS+=		human.c
SRCS+=		localcharset.c
SRCS+=		modechange.c
SRCS+=		quote.c
SRCS+=		quotearg.c
SRCS+=		safe-read.c
SRCS+=		safe-write.c
SRCS+=		save-cwd.c
SRCS+=		savedir.c
SRCS+=		xmalloc.c
SRCS+=		xalloc-die.c
SRCS+=		xgetcwd.c
SRCS+=		xstrtol.c xstrtoul.c
SRCS+=		xstrtoumax.c
SRCS+=		mktime.c
CLEANFILES=	localedir.h getopt.h
MKMAN=		no

DIST=		${.CURDIR}/../../../dist/${LIB}
.PATH:		${DIST}/lib

.include "${.CURDIR}/../Makefile.cflags"
CPPFLAGS+=	-DLIBDIR=\"/usr/lib\"
CPPFLAGS+=	-I${.CURDIR}
CPPFLAGS+=	-I${DIST}/lib
CPPFLAGS+=	-I${.CURDIR}/../include

localedir.h: Makefile
	rm -f ./localedir.h
	echo '#define LOCALEDIR "/usr/share/locale"' > ./localedir.h
	echo "#ifndef DEFAULT_RMT_COMMAND" >> ./localedir.h
	echo "# define DEFAULT_RMT_COMMAND \"/usr/libexec/`echo \"rmt\" | sed 's,^.*/,,;s,x,x,'`\"" >> ./localedir.h
	echo "#endif" >> ./localedir.h

rtapelib.o: localedir.h

argp-parse.c: getopt.h

getopt.h:
	rm -f ${.TARGET}
	cp ${DIST}/lib/getopt_.h ${.TARGET}

libinstall::

.include <bsd.lib.mk>
