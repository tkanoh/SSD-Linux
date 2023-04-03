#	$ssdlinux: Makefile,v 1.13 2003/03/26 09:39:21 yamagata Exp $

.include <bsd.own.mk>

PROG=		screen
SRCS=		kmapdef.c tty.c screen.c ansi.c fileio.c mark.c misc.c \
		resize.c socket.c search.c term.c window.c utmp.c \
		loadav.c putenv.c help.c termcap.c input.c attacher.c \
		pty.c process.c display.c comm.c acls.c braille.c \
		braille_tsi.c logfile.c layer.c sched.c teln.c \
		nethack.c \
		encoding.c

.if defined(DESTDIR) || !make(install)
SCRIPTS=	screenrc
SCRIPTSDIR=	/etc
SCRIPTSMODE=	444
.endif

DIST=		${.CURDIR}/../../dist/${PROG}
.PATH:		${DIST} ${DIST}/doc

CPPFLAGS+=	-I${.CURDIR} -I${DIST}
CPPFLAGS+=	-DETCSCREENRC='"/etc/screenrc"'
.if ${TARGET_HOSTTYPE} == "i386"
CPPFLAGS+=	-DPTYRANGE0='"abcdepqrstuvwxyz"'
.elif ${TARGET_HOSTTYPE} == "powerpc"
CPPFLAGS+=	-DUSEMEMCPY=1
CPPFLAGS+=	-DPTYRANGE0='"p"'
.endif
LDADD+=		-L${DIST}/../../lib/libncurses/build/lib -lncurses
LDADD+=		-lutil
LDADD+=		-lcrypt

CLEANFILES=	kmapdef.c tty.c comm.h osdef.h term.h ${SCRIPTS}

kmapdef.c:
	CPP="gcc -E " srcdir=${DIST} sh ${DIST}/osdef.sh
	AWK=gawk CC="gcc -O2" srcdir=${DIST} sh ${DIST}/comm.sh
	AWK=gawk srcdir=${DIST} sh ${DIST}/term.sh

tty.c:
	sh ${DIST}/tty.sh tty.c

${SCRIPTS}:
	if [ -d /usr/share/terminfo ]; then \
		tic ${DIST}/terminfo/screeninfo.src; \
		chmod 644 /usr/share/terminfo/s/screen*; \
	fi
	cp ${DIST}/etc/etcscreenrc ${.TARGET}

.include <bsd.prog.mk>
