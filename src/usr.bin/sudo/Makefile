#	$ssdlinux: Makefile,v 1.16 2005/01/06 03:34:10 yamagata Exp $

.include <bsd.own.mk>

PROG=		sudo		
SRCS=		check.c env.c getspwuid.c gettime.c goodpath.c fileops.c find_path.c \
		interfaces.c logging.c parse.c set_perms.c sudo.c sudo_edit.c \
		tgetpass.c zero_bytes.c \
		sudo_auth.c passwd.c sudo.tab.c lex.yy.c alloc.c defaults.c
SRCS+=		strlcpy.c strlcat.c closefrom.c
MAN=		${PROG}.8 sudoers.5
BINMODE=	4111

.if defined(DESTDIR) || !make(install)
FILES=		sudoers
FILESDIR=	/etc
FILESMODE=	440
.endif

DIST=		${.CURDIR}/../../dist/${PROG}
.PATH:		${DIST} ${DIST}/auth

CPPFLAGS+=	-I${.CURDIR}
CPPFLAGS+=	-D_PATH_SUDOERS=\"/etc/sudoers\"
CPPFLAGS+=	-D_PATH_SUDOERS_TMP=\"/etc/sudoers.tmp\"
CPPFLAGS+=	-DSUDOERS_UID=0
CPPFLAGS+=	-DSUDOERS_GID=0
CPPFLAGS+=	-DSUDOERS_MODE=0440
CPPFLAGS+=	-I${DIST}
LDADD+=		-lcrypt
.include "${.CURDIR}/Makefile.cflags"
.if defined(USE_PAM)
SRCS+=		pam.c
CPPFLAGS+=	-DWITHOUT_PASSWD=1
CPPFLAGS+=	-DHAVE_PAM=1
CPPFLAGS+=	-I${DIST}/auth
.if defined(CROSS_BUILD) || defined(NEW_GLIBC)
CPPFLAGS+=	-I${DIST}/../../lib/pam/include
CPPFLAGS+=	-I${DIST}/../Linux-PAM/libpam/include
CPPFLAGS+=	-I${DIST}/../Linux-PAM/libpamc/include
CPPFLAGS+=	-I${DIST}/../Linux-PAM/libpam_misc/include
.endif
LDADD+=		-ldl
LDADD+=		-L${.CURDIR}/../../lib/pam/libpam -lpam
.endif

MLINKS=		${PROG}.8 ${PROG}edit.8
SYMLINKS=	${BINDIR}/${PROG} ${BINDIR}/${PROG}edit

NOGCCERROR=	yes

.include <bsd.prog.mk>
