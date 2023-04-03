#	$ssdlinux: Makefile,v 1.1 2004/11/11 17:13:55 kanoh Exp $
#	$NetBSD: Makefile.inc,v 1.6 1997/10/22 23:14:11 lukem Exp $
#	@(#)Makefile.inc	8.2 (Berkeley) 2/21/94
#
.include <bsd.own.mk>
LIB=		db1

MKPIC=		yes
MKPICINSTALL=	no

CPPFLAGS+=	-D__DBINTERFACE_PRIVATE

.include "${.CURDIR}/btree/Makefile.inc"
.include "${.CURDIR}/db/Makefile.inc"
.include "${.CURDIR}/hash/Makefile.inc"
.include "${.CURDIR}/include/Makefile.inc"
.include "${.CURDIR}/man/Makefile.inc"
.include "${.CURDIR}/mpool/Makefile.inc"
.include "${.CURDIR}/recno/Makefile.inc"

.include <bsd.lib.mk>
