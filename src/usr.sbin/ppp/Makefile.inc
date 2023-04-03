#	$ssdlinux: Makefile.inc,v 1.1 2002/06/21 09:11:49 kanoh Exp $

BINDIR?=	/usr/sbin
WARNS?=		0
NONLS=		yes

DIST=		${.CURDIR}/../../../dist/ppp
.PATH:		${DIST}/${PROG} ${DIST}/etc.ppp
