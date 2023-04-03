#	$ssdlinux: Makefile,v 1.2 2003/08/29 02:14:12 todoroki Exp $

.include <bsd.own.mk>

.ifmake clean
SUBDIR= amiga atari i386 include mac sun
.else

SUBDIR=	 include
.if ${MACHINE_ARCH} == "amiga"
SUBDIR+= amiga
.endif
.if ${MACHINE_ARCH} == "atari"
SUBDIR+= atari
.endif
.if ${MACHINE_ARCH} == "i386"
SUBDIR+= i386
.endif
.if ${MACHINE_ARCH} == "mac68k" || ${MACHINE_ARCH} == "macppc"
SUBDIR+= mac
.endif
.if ${MACHINE_ARCH} == "sparc" || ${MACHINE_ARCH} == "sparc64"
SUBDIR+= sun
.endif

.endif

FILES=	README

FILESDIR=	$(BINDIR)/keymaps
.PATH:		${.CURDIR}/../../../dist/kbd/data/keymaps

SYMLINKS=	mac ppc

.include <bsd.prog.mk>
.include <bsd.subdir.mk>
