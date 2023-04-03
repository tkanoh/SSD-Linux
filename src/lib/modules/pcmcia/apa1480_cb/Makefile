#	$ssdlinux: Makefile,v 1.2 2002/11/02 09:24:10 kanoh Exp $

.include <bsd.own.mk>

CLIENT=		apa1480_cb
MODULEOBJ=	apa1480_stub.o
KERNOBJ=	aic7xxx_osm.o aic7xxx_proc.o aic7770_osm.o \
		aic7xxx_osm_pci.o \
		aic7xxx_core.o aic7xxx_93cx6.o aic7770.o \
		aic7xxx_pci.o
MKMAN=		no
KERNDRVDIR=	scsi/aic7xxx

.include "../Makefile.cflags"

.include <bsd.prog.mk>
