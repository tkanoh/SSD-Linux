#	$ssdlinux: Makefile,v 1.4 2003/01/14 08:21:20 kanoh Exp $

.include <bsd.own.mk>

PROG=		vtund
SRCS=		main.c cfg_file.tab.c cfg_file.lex.c server.c client.c \
		lib.c llist.c auth.c tunnel.c lock.c netlib.c tun_dev.c \
		tap_dev.c pty_dev.c pipe_dev.c tcp_proto.c udp_proto.c \
		linkfd.c lfd_shaper.c lfd_zlib.c lfd_lzo.c lfd_encrypt.c
MKMAN=		no

DIST=		${.CURDIR}/../../../dist/vtun
.PATH:		${DIST} ${DIST}/linux ${DIST}/generic

VTUNDDIR=	${.CURDIR}/../../../usr.sbin/vtund

CPPFLAGS+=	-g -O -I${VTUNDDIR} -I${DIST}
CPPFLAGS+=	-I${.CURDIR}/../../../dist/openssl/include/openssl
CPPFLAGS+=	-DVTUN_CONFIG_FILE=\"/etc/vtund.conf\"
CPPFLAGS+=	-DVTUN_PID_FILE=\"/var/run/vtund.pid\"
CPPFLAGS+=	-DVTUN_STAT_DIR=\"/var/log/vtund\"
CPPFLAGS+=	-DVTUN_LOCK_DIR=\"/var/spool/lock/vtund\"
.if defined(CROSS_BUILD)
CPPFLAGS+=	-I${DIST}/../zlib
CPPFLAGS+=	-I${DESTDIR}/usr/include
.endif

LDADD+=		-L${.CURDIR}/../../../lib/libz -lz
LDADD+=		${.CURDIR}/../../../lib/ssl/libcrypto/libcrypto.a
DPADD+=		${.CURDIR}/../../../lib/libz/libz.a
DPADD+=		${.CURDIR}/../../../lib/ssl/libcrypto/libcrypto.a

CLEANFILES+=	cfg_file.tab.c cfg_file.tab.h cfg_file.lex.c

cfg_file.tab.c: cfg_file.y
	${YACC} -y -d -b cfg_file ${VTUNDDIR}/cfg_file.y

cfg_file.lex.c: cfg_file.l
	${LEX} -t  ${DIST}/cfg_file.l > cfg_file.lex.c

proginstall:

.include <bsd.prog.mk>
