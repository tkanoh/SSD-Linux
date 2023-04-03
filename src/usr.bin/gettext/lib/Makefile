#	$ssdlinux: Makefile,v 1.9 2005/02/25 07:03:31 yamagata Exp $

.include <bsd.own.mk>

LIB=		gettextlib
SRCS=		allocsa.c argmatch.c backupfile.c addext.c basename.c \
		c-ctype.c c-strcasecmp.c c-strncasecmp.c \
		classpath.c closeout.c copy-file.c \
		csharpcomp.c csharpexec.c \
		error-progname.c execute.c exitfail.c\
		fatal-signal.c findprog.c fstrcmp.c full-write.c fwriteerror.c \
		gcd.c \
		hash.c javacomp.c javaexec.c linebreak.c \
		mbswidth.c obstack.c \
		concatpath.c \
		pipe.c progname.c progreloc.c \
		quote.c quotearg.c \
		safe-read.c safe-write.c sh-quote.c \
		tmpdir.c wait-process.c \
		xerror.c xmalloc.c xstrdup.c xallocsa.c xreadlink.c xsetenv.c \
		localcharset.c
MKPIC=		no
MKPROFILE=	no
MKLINT=		no

CPPFLAGS+=	-DEXEEXT=\"\" -DLIBDIR=\"/usr/lib\"
.include "${.CURDIR}/../Makefile.inc"
.include "${.CURDIR}/../Makefile.inc.tools"
.PATH:		${DIST}/gettext/gettext-tools/lib
CPPFLAGS+=	-I${.CURDIR}/../include

libinstall::

.include <bsd.lib.mk>
