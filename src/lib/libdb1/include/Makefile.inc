#	$ssdlinux: Makefile.inc,v 1.1 2004/11/11 17:13:56 kanoh Exp $

.PATH: ${.CURDIR}/include

INCS=		compat.h db.h mpool.h ndbm.h
INCSDIR=	/usr/include/db1

CPPFLAGS+=	-I${.CURDIR}/include
