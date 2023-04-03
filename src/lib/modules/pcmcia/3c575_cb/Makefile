#	$ssdlinux: Makefile,v 1.4 2002/10/25 03:10:07 yamagata Exp $

.include <bsd.own.mk>

CLIENT=		3c575_cb
MAN=		tc575_cb.4

.include "../Makefile.cflags"

CPPFLAGS=	${AFLAGS} -MD -c -O2 ${INCLUDES} -D__KERNEL__ -DEXPORT_SYMTAB ${MFLAG} -DMODULE -DCARDBUS

.include <bsd.prog.mk>
