#	$ssdlinux: Makefile,v 1.3 2002/10/25 09:20:09 yamagata Exp $

.include <bsd.own.mk>

CLIENT=		epic_cb
MKMAN=		no

.include "../Makefile.cflags"

CPPFLAGS=	${AFLAGS} -MD -c -O2 ${INCLUDES} -D__KERNEL__ -DEXPORT_SYMTAB ${MFLAG} -DMODULE -DCARDBUS

.include <bsd.prog.mk>
