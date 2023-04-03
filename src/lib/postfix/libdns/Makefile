#	$ssdlinux: Makefile,v 1.3 2005/03/10 08:40:39 yamagata Exp $

.include <bsd.own.mk>

LIB=		dns
SRCS=		dns_lookup.c dns_rr.c dns_strerror.c dns_strtype.c dns_rr_to_pa.c \
		dns_sa_to_rr.c dns_rr_eq_sa.c dns_rr_to_sa.c

DIST=		${.CURDIR}/../../../dist/postfix
.PATH:		${DIST}/src/${LIB}

libinstall::

.include <bsd.lib.mk>
