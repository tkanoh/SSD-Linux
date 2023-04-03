#	$ssdlinux: Makefile,v 1.4 2003/10/24 03:04:38 kanoh Exp $

.include <bsd.own.mk>

LIB=		isc
MKMAN=		no

CPPFLAGS+=	-DLIBINTERFACE=7
CPPFLAGS+=	-DLIBREVISION=1
CPPFLAGS+=	-DLIBAGE=0

DIST=		${.CURDIR}/../../../dist/bind/lib/isc
.PATH:		${DIST}/unix ${DIST}/nls ${DIST}/nothreads ${DIST}

.if ${TARGET_HOSTTYPE} == "powerpc"
CPPFLAGS+=	-DWORDS_BIGENDIAN=1
.endif

# ${DIST}/unix
CPPFLAGS+=	-I${DIST}/unix/include
SRCS=		app.c dir.c entropy.c errno2result.c file.c fsaccess.c interfaceiter.c \
		keyboard.c net.c os.c resource.c socket.c stdio.c stdtime.c strerror.c \
		syslog.c time.c

# ${DIST}/nls
CPPFLAGS+=	-I${DIST}/nls/include
SRCS+=		msgcat.c

# ${DIST}/nothreads
CPPFLAGS+=	-I${DIST}/nothreads/include
SRCS+=		condition.c mutex.c thread.c

# ${DIST}
CPPFLAGS+=	-I${DIST}/include
SRCS+=		inet_pton.c assertions.c base64.c bitstring.c buffer.c bufferlist.c \
		commandline.c error.c event.c hash.c heap.c hex.c hmacmd5.c lex.c lfsr.c lib.c \
		log.c md5.c mem.c mutexblock.c netaddr.c ondestroy.c quota.c random.c \
		ratelimiter.c result.c rwlock.c serial.c sha1.c sockaddr.c string.c symtab.c \
		task.c taskpool.c timer.c version.c

NOGCCERROR=	yes

libinstall::

.include <bsd.lib.mk>
