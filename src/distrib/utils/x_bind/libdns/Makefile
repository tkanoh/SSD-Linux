#	$ssdlinux: Makefile,v 1.6 2005/03/14 03:44:58 yamagata Exp $

.include <bsd.own.mk>

LIB=		dns
MKMAN=		no

CPPFLAGS+=	-W -Wall -Wmissing-prototypes -Wcast-qual -Wwrite-strings
CPPFLAGS+=	-I${.CURDIR}/../../../../lib/bind/include

CPPFLAGS+=	-DLIBINTERFACE=11
CPPFLAGS+=	-DLIBREVISION=2
CPPFLAGS+=	-DLIBAGE=0

ISCDIST=	${.CURDIR}/../../../../dist/bind/lib/isc

DIST=		${.CURDIR}/../../../../dist/bind/lib/dns
.PATH:		${DIST}

CPPFLAGS+=	-I${.CURDIR}
CPPFLAGS+=	-I${DIST}/include
CPPFLAGS+=	-I${ISCDIST}
CPPFLAGS+=	-I${ISCDIST}/include
CPPFLAGS+=	-I${ISCDIST}/unix/include
CPPFLAGS+=	-I${ISCDIST}/nothreads/include

.if ${TARGET_HOSTTYPE} == "powerpc"
CPPFLAGS+=	-DWORDS_BIGENDIAN=1
.endif


CPPFLAGS+=	-I${DIST}/include
CPPFLAGS+=	-DUSE_MD5
SRCS=		dst_api.c dst_lib.c dst_parse.c \
		dst_result.c gssapi_link.c gssapictx.c \
		hmac_link.c key.c \
		openssl_link.c openssldh_link.c \
		openssldsa_link.c opensslrsa_link.c
SRCS+=		dummy.c \
		a6.c acl.c adb.c byaddr.c \
		cache.c callbacks.c compress.c \
		db.c dbiterator.c dbtable.c diff.c dispatch.c \
		dnssec.c forward.c journal.c keytable.c \
		lib.c log.c lookup.c \
		master.c masterdump.c message.c \
		name.c ncache.c nxt.c peer.c \
		rbt.c rbtdb.c rbtdb64.c rdata.c rdatalist.c \
		rdataset.c rdatasetiter.c rdataslab.c request.c \
		resolver.c result.c rootns.c sdb.c soa.c ssu.c \
		stats.c tcpmsg.c time.c timer.c tkey.c \
		tsig.c ttl.c validator.c \
		version.c view.c xfrin.c zone.c zonekey.c zt.c

dummy.c: gen
	touch dummy.c
	
gen:
	${HOST_CC} ${CPPFLAGS} -o gen ${DIST}/gen.c -lnsl
	./gen -s ${DIST} > code.h

CLEANFILES+=	gen gen.o \
		code.h dummy.c

NOGCCERROR=	yes

libinstall::

.include <bsd.lib.mk>
