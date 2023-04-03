#	$ssdlinux: Makefile,v 1.1 2002/07/02 05:17:16 yamagata Exp $

.include <bsd.own.mk>

PROG=		pwcat
BINDIR=		/usr/libexec/awk
MKMAN=		no

FILES=		passwd.awk group.awk
FILES+=		assert.awk ctime.awk gettime.awk nextfile.awk readable.awk \
		bits2str.awk ftrans.awk join.awk noassign.awk rewind.awk \
		cliff_rand.awk getopt.awk libintl.awk ord.awk round.awk
FILESDIR=	/usr/share/awk
CLEANFILES=	passwd.awk group.awk

.include "${.CURDIR}/../Makefile.cflags"

.PATH:		${DIST}/awklib/eg/lib

CPPFLAGS=	-O2
LDADD=		-rdynamic

realall:	${PROG} ${FILES}

passwd.awk: ${DIST}/awklib/eg/lib/passwdawk.in
	sed 's;/usr/local/libexec/awk;${FILESDIR};' < \
		${DIST}/awklib/eg/lib/passwdawk.in > ${.TARGET}

group.awk: ${DIST}/awklib/eg/lib/groupawk.in
	sed 's;/usr/local/libexec/awk;${FILESDIR};' < \
		${DIST}/awklib/eg/lib/groupawk.in > ${.TARGET}

.include <bsd.prog.mk>
