#	$ssdlinux: Makefile,v 1.4 2004/02/26 07:30:18 yamagata Exp $

.include <bsd.own.mk>

PROG=		sftp
SRCS=		${PROG}.c sftp-client.c sftp-common.c sftp-glob.c

DIST=		${.CURDIR}/../../../dist/openssh
.PATH:		${DIST}

.include <bsd.prog.mk>
