#	$ssdlinux: Makefile,v 1.3 2002/10/25 09:21:33 yamagata Exp $

.include <bsd.own.mk>

CLIENT=		eepro100_cb
MKMAN=		no

.include "../Makefile.cflags"

CPPFLAGS=	${AFLAGS} -MD -c -O2 ${INCLUDES} -D__KERNEL__ -DEXPORT_SYMTAB ${MFLAG} -DMODULE -DCARDBUS

.include <bsd.prog.mk>
