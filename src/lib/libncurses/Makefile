#	$ssdlinux: Makefile,v 1.15 2004/06/28 01:26:28 yamagata Exp $

.include <bsd.own.mk>

DISTNAME=	ncurses
GNU_BINDIR=	/usr/bin
GNU_SBINDIR=	/usr/sbin
HAVE_DESTDIR=	1
CONFIGURE_ENV=
CONFIGURE_FULL_PREFIX=	1
CONFIGURE_OPTIONS=	--without-debug
CONFIGURE_OPTIONS+=	--with-shared
GMAKE_ENV=
GMAKE_OPTIONS=

GMAKE_INSTALL_OPTIONS=	DESTDIR=${DESTDIR}
INSTALL_STRIP=	no
.if defined(NEW_GLIBC) || defined(CROSS_BUILD)
GMAKE_INSTALL_PART= install.progs install.includes install.libs install.man
POSTINSTALL_SCRIPT= (cd /usr/share/terminfo ; tar cvpf - .) | (cd ${DESTDIR}/usr/share/terminfo; tar xpf -)
.endif

LINKS+=		/usr/lib/libncurses.a	/usr/lib/libcurses.a 
SYMLINKS+=	/usr/bin/${TARGET_MACHTYPE}-clear	/usr/bin/clear
SYMLINKS+=	/usr/bin/${TARGET_MACHTYPE}-infocmp	/usr/bin/infocmp
SYMLINKS+=	/usr/bin/${TARGET_MACHTYPE}-tic	/usr/bin/tic
SYMLINKS+=	/usr/bin/${TARGET_MACHTYPE}-toe	/usr/bin/toe
SYMLINKS+=	/usr/bin/${TARGET_MACHTYPE}-tput	/usr/bin/tput
SYMLINKS+=	/usr/bin/${TARGET_MACHTYPE}-tset	/usr/bin/tset
SYMLINKS+=	/usr/bin/tset	/usr/bin/reset
SYMLINKS+=	/usr/bin/tic	/usr/bin/captoinfo
SYMLINKS+=	/usr/bin/tic	/usr/bin/infotocap
SYMLINKS+=	/usr/share/man/man1/${TARGET_MACHTYPE}-captoinfo.1m	/usr/share/man/man1/captoinfo.1m
SYMLINKS+=	/usr/share/man/man1/${TARGET_MACHTYPE}-clear.1		/usr/share/man/man1/clear.1
SYMLINKS+=	/usr/share/man/man1/${TARGET_MACHTYPE}-infocmp.1m	/usr/share/man/man1/infocmp.1m
SYMLINKS+=	/usr/share/man/man1/${TARGET_MACHTYPE}-infotocap.1m	/usr/share/man/man1/infotocap.1m
SYMLINKS+=	/usr/share/man/man1/${TARGET_MACHTYPE}-tic.1m		/usr/share/man/man1/tic.1m
SYMLINKS+=	/usr/share/man/man1/${TARGET_MACHTYPE}-toe.1m		/usr/share/man/man1/toe.1m
SYMLINKS+=	/usr/share/man/man1/${TARGET_MACHTYPE}-tput.1		/usr/share/man/man1/tput.1
SYMLINKS+=	/usr/share/man/man1/${TARGET_MACHTYPE}-tset.1		/usr/share/man/man1/tset.1
SYMLINKS+=	/usr/share/man/man1/tset.1			/usr/share/man/man1/reset.1

.include <bsd.gnu.mk>
