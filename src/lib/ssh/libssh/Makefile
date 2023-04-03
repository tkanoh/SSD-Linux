#	$ssdlinux: Makefile,v 1.9 2004/08/18 08:11:29 yamagata Exp $

.include <bsd.own.mk>

LIB=		ssh
SRCS=		acss.c authfd.c authfile.c bufaux.c buffer.c \
		canohost.c channels.c cipher.c cipher-acss.c cipher-aes.c \
		cipher-bf1.c cipher-ctr.c cipher-3des1.c cleanup.c \
		compat.c compress.c crc32.c deattack.c fatal.c hostfile.c \
		log.c match.c moduli.c mpaux.c nchan.c packet.c \
		readpass.c rsa.c tildexpand.c ttymodes.c xmalloc.c \
		atomicio.c key.c dispatch.c kex.c mac.c uidswap.c uuencode.c misc.c \
		monitor_fdpass.c rijndael.c ssh-dss.c ssh-rsa.c dh.c kexdh.c \
		kexgex.c kexdhc.c kexgexc.c scard.c msg.c progressmeter.c dns.c \
		entropy.c scard-opensc.c gss-genr.c
MKMAN=		no

DIST=		${.CURDIR}/../../../dist/openssh
.PATH:		${DIST}

.include "${.CURDIR}/../Makefile.cflags"

NOGCCERROR=	yes

CPPFLAGS+=	-I${.CURDIR} -I${DIST}

libinstall::

.include <bsd.lib.mk>
