#	$ssdlinux: Makefile,v 1.13 2004/08/18 08:11:29 yamagata Exp $

.include <bsd.own.mk>

LIB=		openbsd-compat
# OPENBSD
SRCS=		base64.c basename.c bindresvport.c daemon.c dirname.c getcwd.c \
		getgrouplist.c getopt.c getrrsetbyname.c glob.c inet_aton.c inet_ntoa.c \
		inet_ntop.c mktemp.c readpassphrase.c realpath.c rresvport.c \
		setenv.c setproctitle.c sigact.c strlcat.c strlcpy.c strmode.c \
		strsep.c strtoul.c vis.c
# COMPAT
SRCS+=		bsd-arc4random.c bsd-closefrom.c bsd-cray.c bsd-cygwin_util.c bsd-getpeereid.c \
		bsd-misc.c bsd-nextstep.c bsd-openpty.c bsd-snprintf.c bsd-waitpid.c \
		fake-rfc2553.c xmmap.c xcrypt.c
# PORTS
SRCS+=		port-irix.c port-aix.c
MKMAN=		no

DIST=		${.CURDIR}/../../../dist/openssh
.PATH:		${DIST}/${LIB}

CPPFLAGS+=	-I${.CURDIR}/../libssh -I${DIST}/${LIB} -I${DIST}
.if defined(CROSS_BUILD) || defined(NEW_GLIBC)
CPPFLAGS+=	-I${DIST}/../openssl/include
.endif

.if ${TARGET_HOSTTYPE} == "powerpc"
NOGCCERROR=	yes
.endif

libinstall::

.include <bsd.lib.mk>
