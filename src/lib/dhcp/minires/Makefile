#	$ssdlinux: Makefile,v 1.2 2003/10/01 06:10:47 yamagata Exp $
.include <bsd.own.mk>

.include "${.CURDIR}/../Makefile.cflags"

LIB=		res
SRCS=		res_mkupdate.c res_init.c res_update.c res_send.c res_comp.c \
		res_sendsigned.c res_findzonecut.c res_query.c res_mkquery.c \
		ns_date.c ns_parse.c ns_sign.c ns_name.c ns_samedomain.c \
		ns_verify.c
MKMAN=		no

DIST=		${.CURDIR}/../../../dist/dhcp
.PATH:		${DIST}/minires

CPPFLAGS+=	-I${DIST} -I${DIST}/includes
CPPFLAGS+=	-DHMAC_MD5 -DMINIRES_LIB

libinstall::

.include <bsd.lib.mk>
