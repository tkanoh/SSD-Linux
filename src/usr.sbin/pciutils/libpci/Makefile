#       $ssdlinux: Makefile,v 1.2 2004/08/09 06:05:56 yamagata Exp $

.include <bsd.own.mk>

LIB=    pci
SRCS=   access.c generic.c dump.c names.c filter.c proc.c

.if ${TARGET_SSDHOSTTYPE} == "i386"
SRCS+=	i386-ports.c
.endif
MKMAN=  no
CLEANFILES=     config.h

DIST=           ${.CURDIR}/../../../dist/pciutils
.PATH:          ${DIST}/lib
CPPFLAGS+=      -I${.CURDIR} -I${DIST}/lib

access.o:  config.h

config.h:
	/bin/cp config.h.${TARGET_SSDHOSTTYPEX} config.h

libinstall::

.include <bsd.lib.mk>
