#	$ssdlinux: Makefile,v 1.14 2005/01/06 03:33:32 yamagata Exp $

.include <bsd.own.mk>

PROG=		visudo		
MAN=		${PROG}.8
BINMODE=	111

.if defined(DESTDIR) || !make(install)
FILES=		sudoers
FILESDIR=	/etc
FILESMODE=	440
.endif

DIST=		${.CURDIR}/../../dist/sudo
.PATH:		${DIST}

CPPFLAGS+=	-I${.CURDIR}/../../usr.bin/sudo
CPPFLAGS+=	-D_PATH_SUDOERS=\"/etc/sudoers\"
CPPFLAGS+=	-D_PATH_SUDOERS_TMP=\"/etc/sudoers.tmp\"
CPPFLAGS+=	-DSUDOERS_UID=0
CPPFLAGS+=	-DSUDOERS_GID=0
CPPFLAGS+=	-DSUDOERS_MODE=0440
CPPFLAGS+=	-I${DIST}
.include "${.CURDIR}/../../usr.bin/sudo/Makefile.cflags"
.if defined(USE_PAM)
CPPFLAGS+=	-DWITHOUT_PASSWD=1
CPPFLAGS+=	-DHAVE_PAM=1
.endif
LDADD+=		${.CURDIR}/../../usr.bin/sudo/fileops.o \
		${.CURDIR}/../../usr.bin/sudo/gettime.o \
		${.CURDIR}/../../usr.bin/sudo/goodpath.o \
		${.CURDIR}/../../usr.bin/sudo/find_path.o \
		${.CURDIR}/../../usr.bin/sudo/sudo.tab.o \
		${.CURDIR}/../../usr.bin/sudo/lex.yy.o \
		${.CURDIR}/../../usr.bin/sudo/alloc.o \
		${.CURDIR}/../../usr.bin/sudo/defaults.o
LDADD+=		${.CURDIR}/../../usr.bin/sudo/strlcpy.o \
		${.CURDIR}/../../usr.bin/sudo/strlcat.o \
		${.CURDIR}/../../usr.bin/sudo/closefrom.o

.include <bsd.prog.mk>
