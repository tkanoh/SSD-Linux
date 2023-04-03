#	$ssdlinux: Makefile,v 1.4 2004/11/18 03:44:10 yamagata Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	readline-
DISTVERSION=	5.0
MASTER_SITES=	ftp://ftp.cwru.edu/pub/bash
PATCH_SITES=	ftp://ftp.cwru.edu/pub/bash/readline-5.0-patches
PATCHFILES=	readline50-001
PATCHFILES+=	readline50-002
PATCHFILES+=	readline50-003
PATCHFILES+=	readline50-004
PATCHFILES+=	readline50-005
PATCH_STRIP_COUNT=	0
DISTRELEASE=	1
DEPENDENT=	lib/readline

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
