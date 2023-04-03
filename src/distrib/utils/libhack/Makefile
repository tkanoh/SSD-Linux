#	$ssdlinux: Makefile,v 1.10 2004/03/24 01:06:44 yamagata Exp $

.include <bsd.own.mk>

LIB=		hack

.if ${TARGET_HOSTTYPE} == "i386"
SRCS=		addext.c argmatch.c
SRCS+=		backupfile.c basename.c
SRCS+=		closeout.c cycle-check.c
SRCS+=		dirname.c dup-safer.c
SRCS+=		exclude.c
SRCS+=		filemode.c file-type.c fopen-safer.c fsusage.c full-write.c
SRCS+=		gettime.c
SRCS+=		hard-locale.c human.c hash.c hash-pjw.c
SRCS+=		idcache.c isdir.c imaxtostr.c
SRCS+=		linebuffer.c long-options.c
SRCS+=		makepath.c mbswidth.c memcasecmp.c memcoll.c modechange.c mountlist.c
SRCS+=		path-concat.c physmem.c posixtm.c posixver.c
SRCS+=		quote.c quotearg.c
SRCS+=		safe-read.c safe-write.c same.c save-cwd.c savedir.c settime.c strftime.c stripslash.c
SRCS+=		umaxtostr.c userspec.c
SRCS+=		version-etc.c
SRCS+=		xgetcwd.c xgethostname.c xmalloc.c xmemcoll.c xnanosleep.c xreadlink.c xstrdup.c xstrtod.c xstrtol.c xstrtoul.c xstrtoumax.c
SRCS+=		yesno.c

DIST=		${.CURDIR}/../../../dist/coreutils50

.elif ${TARGET_HOSTTYPE} == "powerpc"
SRCS=		addext.c argmatch.c
SRCS+=		backupfile.c basename.c
SRCS+=		c-strtod.c closeout.c cycle-check.c
SRCS+=		dirname.c
SRCS+=		exclude.c exitfail.c
SRCS+=		file-type.c full-write.c filemode.c free.c fsusage.c
SRCS+=		gettime.c
SRCS+=		hard-locale.c hash.c hash-pjw.c human.c
SRCS+=		idcache.c imaxtostr.c isdir.c
SRCS+=		long-options.c
SRCS+=		makepath.c mbswidth.c mktime.c modechange.c mountlist.c
SRCS+=		path-concat.c posixtm.c posixver.c
SRCS+=		quote.c quotearg.c
SRCS+=		root-dev-ino.c
SRCS+=		safe-read.c safe-write.c same.c save-cwd.c savedir.c settime.c strftime.c stripslash.c
SRCS+=		time_r.c
SRCS+=		umaxtostr.c userspec.c utimens.c
SRCS+=		version-etc.c
SRCS+=		xfts.c xgetcwd.c xgethostname.c xmalloc.c xnanosleep.c xreadlink.c xstrtod.c xstrtol.c xstrtoul.c xstrtoumax.c
SRCS+=		yesno.c

DIST=		${.CURDIR}/../../../dist/coreutils
.endif

SRCS+=		usage.c
MKMAN= 		NO
.PATH:		${DIST}/lib

.if ${TARGET_HOSTTYPE} == "i386"
CPPFLAGS+=	-DLIBDIR=\"/usr/lib\" -DHAVE_CONFIG_H -I${.CURDIR}/../../../lib/coreutils50 -I${DIST}/lib
CPPFLAGS+=	-DHAVE_LONG_DOUBLE=1
.elif ${TARGET_HOSTTYPE} == "powerpc"
CPPFLAGS+=	-DLIBDIR=\"/usr/lib\" -DHAVE_CONFIG_H -I${.CURDIR}/../../../lib/coreutils -I${DIST}/lib
CPPFLAGS+=      -DWORDS_BIGENDIAN=1
.endif

libinstall:

.include <bsd.lib.mk>
