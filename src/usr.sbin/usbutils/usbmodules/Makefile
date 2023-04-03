#	$ssdlinux: Makefile,v 1.2 2005/02/15 01:15:46 todoroki Exp $

.include <bsd.own.mk>

PROG=	usbmodules
SRCS=	usbmodules.o usbmisc.o
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../../dist/usbutils
.PATH:		${DIST}/

CPPFLAGS+=	-I../ -I${DIST}/${PROG}
CPPFLAGS+=	-DHAVE_CONFIG_H
CPPFLAGS+=	-DUSBIDS_FILE='"/usr/share/usb.ids"'
CPPFLAGS+=	-I${DESTDIR}/usr/include

LDADD+=         ${DESTDIR}/usr/lib/libusb.a

NOGCCERROR=	yes

.include <bsd.prog.mk>
