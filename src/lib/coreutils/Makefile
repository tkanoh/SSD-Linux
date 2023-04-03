#	$ssdlinux: Makefile,v 1.5 2004/03/22 02:38:40 yamagata Exp $

.include <bsd.own.mk>

LIB=		fetish
SRCS=		acl.c getdate.c posixtm.c posixver.c strftime.c getopt.c \
		getopt1.c hash.c hash-pjw.c addext.c argmatch.c backupfile.c \
		basename.c \
		c-strtod.c canon-host.c cloexec.c closeout.c cycle-check.c \
		diacrit.c \
		dirname.c dup-safer.c exclude.c exitfail.c filemode.c \
		file-type.c fopen-safer.c fts.c full-read.c full-write.c \
		gettime.c getugroups.c hard-locale.c human.c idcache.c isdir.c \
		imaxtostr.c linebuffer.c localcharset.c long-options.c \
		makepath.c mbswidth.c md5.c memcasecmp.c memcoll.c \
		modechange.c offtostr.c path-concat.c physmem.c quote.c \
		quotearg.c readtokens.c root-dev-ino.c \
		safe-read.c safe-write.c same.c \
		save-cwd.c savedir.c settime.c sha1.c stripslash.c \
		time_r.c umaxtostr.c \
		unicodeio.c userspec.c utimens.c \
		version-etc.c \
		xfts.c xgetcwd.c xgethostname.c \
		xmalloc.c xmemcoll.c xnanosleep.c xreadlink.c xstrdup.c \
		xstrndup.c \
		xstrtod.c xstrtoimax.c xstrtol.c xstrtoul.c xstrtoumax.c yesno.c
SRCS+=		free.c fsusage.c getndelim2.c mktime.c mountlist.c readutmp.c \
		sig2str.c strnlen.c 
CLEANFILES=	alloca.h localedir.h

DIST=		${.CURDIR}/../../dist/coreutils
.PATH:		${DIST}/lib

CPPFLAGS+=	-DLIBDIR=\"/usr/lib\" -DHAVE_CONFIG_H -I${.CURDIR} -I${DIST}/lib
.if ${TARGET_HOSTTYPE} == "powerpc"
CPPFLAGS+=	-DWORDS_BIGENDIAN=1
.endif

all: alloca.h localedir.h

alloca.h: ${DIST}/lib/alloca_.h
	rm -f ${.TARGET}
	cp ${DIST}/lib/alloca_.h ${.TARGET}

localedir.h:
	rm -f ${.TARGET}
	echo '#define LOCALEDIR "/usr/share/locale"' >${.TARGET}

libinstall::

.include <bsd.lib.mk>
