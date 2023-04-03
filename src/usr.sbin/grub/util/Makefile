#	$ssdlinux: Makefile,v 1.8 2005/02/09 02:34:08 yamagata Exp $

.include <bsd.own.mk>

PROG=		mbchk
SCRIPTS=	grub-md5-crypt grub-install grub-terminfo grub-set-default
MAN=		${PROG}.1 grub-md5-crypt.8 grub-install.8 grub-terminfo.8
GRUBVERSION=	0.96

DIST=		${.CURDIR}/../../../dist/grub
.PATH:		${DIST}/util ${DIST}/docs

CPPFLAGS+=	-I${.CURDIR}/../include
CPPFLAGS+=	-I${DIST}/lib
CPPFLAGS+=	-I${DIST}/docs
CPPFLAGS+=	-Wall -Wmissing-prototypes -Wunused -Wshadow
CPPFLAGS+=	-Wpointer-arith -falign-jumps=1 -falign-loops=1
CPPFLAGS+=	-falign-functions=1 -Wundef -fwritable-strings
CPPFLAGS+=	-DHAVE_CONFIG_H
CPPFLAGS+=	-DHAVE_LIBCURSES=1

LDADD+=         -L${.CURDIR}/../lib -lcommon
DPADD+=         ${.CURDIR}/../lib/libcommon.a

CLEANFILES=	${SCRIPTS}

NOGCCERROR=	yes

${SCRIPTS}: ${DIST}/util/${.TARGET}.in
	sed -e 's|@prefix@|/usr|' -e 's|@exec_prefix@|/usr|' \
	    -e 's|@sbindir@|/usr/sbin|' -e 's|@libdir@|/usr/mdec|' \
	    -e 's|@PACKAGE@|grub|' -e 's|@VERSION@|${GRUBVERSION}|' \
	    -e 's|@host_cpu@|${TARGET_HOSTTYPE}|' -e 's|@host_os@|linux-gnu|' \
	    -e 's|@host_vendor@|ssd|' \
	    ${DIST}/util/${.TARGET}.in > ${.TARGET}

SYMLINKS+=	${BINDIR}/grub-install /usr/mdec/installboot
MLINKS+=	grub-install.8 installboot.8

.include <bsd.prog.mk>
