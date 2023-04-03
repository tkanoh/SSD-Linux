#	$ssdlinux: Makefile.inc,v 1.3 2002/06/11 08:35:17 kanoh Exp $

BINDIR?=	/usr/sbin
WARNS?=		0
NONLS=		yes

CPPFLAGS+=	-DNEWDB
.if ${IPV6} == "yes"
CPPFLAGS+=	-DNETINET6
.endif
CPPFLAGS+=	-I${.CURDIR}/../include	-I${DIST}/include

LDADD+=		-L${.CURDIR}/../libsmdb -lsmdb
LDADD+=		-L${.CURDIR}/../libsmutil -lsmutil
LDADD+=		-L${.CURDIR}/../libsm -lsm
LDADD+=		-L${.CURDIR}/../../../lib/libdb -ldb
LDADD+=		-lresolv -lcrypt -lnsl -ldl
DPADD+=		${.CURDIR}/../libsmdb/libsmdb.a
DPADD+=		${.CURDIR}/../libsmutil/libsmutil.a
DPADD+=		${.CURDIR}/../libsm/libsm.a
DPADD+=		-L${.CURDIR}/../../../lib/libdb/libdb.a
