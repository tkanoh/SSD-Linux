#	$ssdlinux: Makefile,v 1.3 2004/07/04 07:07:59 yamagata Exp $

.include <bsd.own.mk>

PROG=		vtysh
SRCS=		vtysh_main.c vtysh.c vtysh_cmd.c vtysh_user.c vtysh_config.c
MAN=		${PROG}.1

FILES=		${PROG}.conf.sample
FILESMODE=	600
FILESDIR=	/etc

DIST=		${.CURDIR}/../../../dist/zebra
.PATH:		${DIST}/${PROG} ${DIST}/doc

CPPFLAGS+=	-I${DIST}/${PROG}
.if defined(CROSS_BUILD) || defined(NEW_GLIBC)
CPPFLAGS+=	-I${DIST}/../
.endif

.include <bsd.prog.mk>
