#	$ssdlinux: Makefile,v 1.5 2003/04/01 05:06:19 yamagata Exp $

.include <bsd.own.mk>

PROG=		ssh
SRCS=		${PROG}.c sshconnect.c sshconnect1.c sshconnect2.c sshtty.c \
		readconf.c clientloop.c

DIST=		${.CURDIR}/../../../dist/openssh
.PATH:		${DIST}

SYMLINKS+=	${BINDIR}/${PROG} ${BINDIR}/slogin
MLINKS+=	${PROG}.1 slogin.1

.include <bsd.prog.mk>
