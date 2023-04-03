#	$ssdlinux: Makefile,v 1.10 2004/07/04 07:07:28 yamagata Exp $

.include <bsd.own.mk>

PROG=		vtund
SRCS=		main.c cfg_file.tab.c cfg_file.lex.c server.c client.c \
		lib.c llist.c auth.c tunnel.c lock.c netlib.c tun_dev.c \
		tap_dev.c pty_dev.c pipe_dev.c tcp_proto.c udp_proto.c \
		linkfd.c lfd_shaper.c lfd_zlib.c lfd_lzo.c lfd_encrypt.c
MAN=		${PROG}.8 ${PROG}.conf.5

DIST=		${.CURDIR}/../../dist/vtun
.PATH:		${DIST} ${DIST}/linux ${DIST}/generic

CPPFLAGS+=	-I${.CURDIR} -I${DIST}
CPPFLAGS+=	-I${.CURDIR}/../../dist/openssl/include/openssl
CPPFLAGS+=	-DVTUN_CONFIG_FILE=\"/etc/vtund.conf\"
CPPFLAGS+=	-DVTUN_PID_FILE=\"/var/run/vtund.pid\"
CPPFLAGS+=	-DVTUN_STAT_DIR=\"/var/log/vtund\"
CPPFLAGS+=	-DVTUN_LOCK_DIR=\"/var/spool/lock/vtund\"
.if defined(CROSS_BUILD) || defined(NEW_GLIBC)
CPPFLAGS+=	-I${DIST}/../zlib
CPPFLAGS+=	-I${DESTDIR}/usr/include
.endif

LDADD+=		-L${.CURDIR}/../../lib/libz -lz
LDADD+=		-L${.CURDIR}/../../lib/ssl/libcrypto -lcrypto
DPADD+=		${.CURDIR}/../../lib/libz/libz.a
DPADD+=		${.CURDIR}/../../lib/ssl/libcrypto/libcrypto.a

CLEANFILES+=	cfg_file.tab.c cfg_file.tab.h cfg_file.lex.c

cfg_file.tab.c: cfg_file.y
	${YACC} -y -d -b cfg_file cfg_file.y

cfg_file.lex.c: cfg_file.l
	${LEX} -t  ${DIST}/cfg_file.l > cfg_file.lex.c

.include <bsd.prog.mk>
