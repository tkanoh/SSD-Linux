#	$ssdlinux: Makefile,v 1.1 2004/08/09 04:36:06 todoroki Exp $

.include <bsd.own.mk>

SCRIPTS=	update-pciids
SCRIPTSDIR=	/usr/sbin
SCRIPTSMODE=	755
MKMAN=		no
CLEANFILES=	update-pciids

DIST=		${.CURDIR}/../../dist/pciutils
.PATH:		${DIST}

update-pciids:
	sed <${DIST}/update-pciids.sh >$@ "s@^DEST=.*@DEST=/usr/share/pci.ids@"

.include <bsd.prog.mk>
