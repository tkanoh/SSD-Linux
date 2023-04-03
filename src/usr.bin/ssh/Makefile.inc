#	$ssdlinux: Makefile.inc,v 1.5 2004/02/26 07:30:18 yamagata Exp $

WARNS?=	0
WFORMAT?= 2
BINDIR?=/usr/bin
NONLS= yes

.include "${.CURDIR}/../../../lib/ssh/Makefile.cflags"

CPPFLAGS+=	-I${.CURDIR}/../../../lib/ssh/libssh -I${DIST}

LDADD=		-L${.CURDIR}/../../../lib/ssh/libssh -lssh
LDADD+=		-L${.CURDIR}/../../../lib/ssh/libopenbsd-compat -lopenbsd-compat
LDADD+=		-lresolv
LDADD+=		-L${.CURDIR}/../../../lib/ssl/libcrypto -lcrypto
LDADD+=		-lutil
LDADD+=		-L${.CURDIR}/../../../lib/libz -lz
LDADD+=		-lnsl -lcrypt

NOGCCERROR=	yes
