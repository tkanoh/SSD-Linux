#	$ssdlinux: Makefile,v 1.5 2003/12/09 16:48:06 kanoh Exp $

.include <bsd.own.mk>

LIB=		cvs
SRCS=		argmatch.c getdate.c getline.c getopt.c \
		getopt1.c getpass.c md5.c regex.c savecwd.c sighandle.c \
		stripslash.c xgetwd.c yesno.c

DIST=		${.CURDIR}/../../../dist/cvs
.PATH:		${DIST}/lib

CPPFLAGS+=	-I${DIST}/lib \
		-I${.CURDIR}/../ \
		-I${DIST} \
		-I${DIST}/src
CPPFLAGS+=	-DHAVE_CONFIG_H
.if ${IPV6} == "yes"
CPPFLAGS+=	-DENABLE_IPV6=1
.endif

libinstall::

.include <bsd.lib.mk>
