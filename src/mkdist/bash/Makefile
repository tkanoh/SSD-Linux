#	$ssdlinux: Makefile,v 1.11 2004/12/15 08:35:24 todoroki Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	bash-
DISTVERSION=	3.0
MASTER_SITES=	ftp://ftp.cwru.edu/pub/bash
PATCH_SITES=	ftp://ftp.cwru.edu/pub/bash/bash-3.0-patches
PATCHFILES=	bash30-001
PATCHFILES+=	bash30-002
PATCHFILES+=	bash30-003
PATCHFILES+=	bash30-004
PATCHFILES+=	bash30-005
PATCHFILES+=	bash30-006
PATCHFILES+=	bash30-007
PATCHFILES+=	bash30-008
PATCHFILES+=	bash30-009
PATCHFILES+=	bash30-010
PATCHFILES+=	bash30-011
PATCHFILES+=	bash30-012
PATCHFILES+=	bash30-013
PATCHFILES+=	bash30-014
PATCHFILES+=	bash30-015
PATCHFILES+=	bash30-016
PATCH_STRIP_COUNT=	0
DISTRELEASE=	1
DEPENDENT=	bin/bash
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/bash

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
