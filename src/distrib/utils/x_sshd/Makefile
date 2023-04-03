#	$ssdlinux: Makefile,v 1.6 2005/03/10 05:13:46 yamagata Exp $

.include <bsd.own.mk>

PROG=		sshd
SRCS=		sshd.c auth-rhosts.c auth-passwd.c auth-rsa.c auth-rh-rsa.c \
		sshpty.c sshlogin.c servconf.c serverloop.c \
		auth.c auth1.c auth2.c auth-options.c session.c \
		auth-chall.c auth2-chall.c groupaccess.c \
		auth-skey.c auth-bsdauth.c auth2-hostbased.c auth2-kbdint.c \
		auth2-none.c auth2-passwd.c auth2-pubkey.c \
		monitor_mm.c monitor.c monitor_wrap.c kexdhs.c kexgexs.c \
		auth-krb5.c \
		auth2-gss.c gss-serv.c gss-serv-krb5.c \
		loginrec.c auth-pam.c auth-shadow.c auth-sia.c md5crypt.c \
		audit.c audit-bsm.c
MKMAN=		no
USE_PAM=no

DIST=		${.CURDIR}/../../../dist/openssh
.PATH:		${DIST}

.include "${.CURDIR}/../../../lib/ssh/Makefile.cflags"

LDADD=		-L${.CURDIR}/../../../lib/ssh/libssh -lssh
LDADD+=		-L${.CURDIR}/../../../lib/ssh/libopenbsd-compat -lopenbsd-compat
LDADD+=		-lresolv
LDADD+=		-L${.CURDIR}/../../../lib/ssl/libcrypto -lcrypto
LDADD+=		-lutil
LDADD+=		-L${.CURDIR}/../../../lib/libz -lz
LDADD+=		-lnsl -lcrypt

CPPFLAGS+=	-I${.CURDIR}/../../../lib/ssh/libssh -I${DIST}

NOGCCERROR=	yes

proginstall:

.include <bsd.prog.mk>
