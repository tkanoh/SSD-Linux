#	$ssdlinux: Makefile,v 1.9 2004/02/26 07:31:13 yamagata Exp $

.include <bsd.own.mk>

PROG=		sftp-server
SRCS=		${PROG}.c sftp-common.c
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/openssh
.PATH:		${DIST}

.include "${.CURDIR}/../../lib/ssh/Makefile.cflags"

CPPFLAGS+=	-I${.CURDIR}/../../lib/ssh/libssh -I${DIST}

LDADD=		-L${.CURDIR}/../../lib/ssh/libssh -lssh
LDADD+=		-L${.CURDIR}/../../lib/ssh/libopenbsd-compat -lopenbsd-compat
LDADD+=		-lresolv
LDADD+=		-L${.CURDIR}/../../lib/ssl/libcrypto -lcrypto
LDADD+=		-lutil
LDADD+=		-L${.CURDIR}/../../lib/libz -lz
LDADD+=		-lnsl -lcrypt

.include <bsd.prog.mk>
