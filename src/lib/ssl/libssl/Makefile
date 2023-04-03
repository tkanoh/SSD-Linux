#	$ssdlinux: Makefile,v 1.10 2004/10/28 02:34:13 yamagata Exp $

.include <bsd.own.mk>

LIB=		ssl
SSLVERSION=	0.9.7e
INCS=		kssl.h ssl.h ssl2.h ssl23.h ssl3.h tls1.h
INCSDIR=	/usr/include/openssl
MKPIC=		yes
MKPICINSTALL=	no

DIST=		${.CURDIR}/../../../dist/openssl
.PATH:		${DIST}/ssl ${DIST}/include/openssl

.include "${.CURDIR}/../Makefile.cflags"

CPPFLAGS+=	-I${DIST}/crypto -I${DIST} -I${DIST}/include

SRCS=		s2_meth.c s2_srvr.c s2_clnt.c s2_lib.c s2_enc.c s2_pkt.c s3_meth.c \
		s3_srvr.c s3_clnt.c s3_lib.c s3_enc.c s3_pkt.c s3_both.c s23_meth.c \
		s23_srvr.c s23_clnt.c s23_lib.c s23_pkt.c t1_meth.c t1_srvr.c \
		t1_clnt.c t1_lib.c t1_enc.c ssl_lib.c ssl_err2.c ssl_cert.c \
		ssl_sess.c ssl_ciph.c ssl_stat.c ssl_rsa.c ssl_asn1.c ssl_txt.c \
		ssl_algs.c bio_ssl.c ssl_err.c kssl.c

maninstall:
	@for i in ${DIST}/doc/ssl/*.pod; do \
		fn=`basename $$i .pod`; \
		if [ "$$fn" = "des_modes" ]; then sec=7; else sec=3; fi; \
		echo "installing man$$sec/`basename $$i .pod`.$$sec"; \
		(cd `dirname $$i`; \
			perl ${DIST}/util/pod2man.pl --section=$$sec --center=OpenSSL \
			--release=${SSLVERSION} `basename $$i`) \
			> ${DESTDIR}${MANDIR}/man$$sec/`basename $$i .pod`.$$sec; \
	done

.include <bsd.lib.mk>
