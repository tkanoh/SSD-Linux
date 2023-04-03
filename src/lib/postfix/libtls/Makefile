#	$ssdlinux: Makefile,v 1.1 2005/03/10 08:41:14 yamagata Exp $

.include <bsd.own.mk>

LIB=		tls
SRCS=		tls_prng_dev.c tls_prng_egd.c tls_prng_file.c \
		tls_prng_exch.c tls_stream.c tls_bio_ops.c tls_misc.c tls_dh.c \
		tls_rsa.c tls_verify.c tls_certkey.c tls_session.c tls_temp.c \
		tls_client.c tls_server.c tls_scache.c tls_mgr.c tls_seed.c

DIST=		${.CURDIR}/../../../dist/postfix
.PATH:		${DIST}/src/${LIB}

libinstall::

.include <bsd.lib.mk>
