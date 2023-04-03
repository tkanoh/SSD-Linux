#	$ssdlinux: Makefile,v 1.4 2003/01/06 02:11:17 kanoh Exp $
#
# proting from XFree86 4.1.0 xc/programs/xterm

.include <bsd.own.mk>

PROG=		resize
SRCS=		${PROG}.c xstrings.c

CPPFLAGS+=	-fno-strength-reduce -ansi -pedantic -Wall -Wpointer-arith
CPPFLAGS+=	-I./include
CPPFLAGS+=	-Dlinux
.if ${TARGET_HOSTTYPE} == "i386"
CPPFLAGS+=	-D__i386__
.endif
CPPFLAGS+=	-D_POSIX_C_SOURCE=199309L -D_POSIX_SOURCE -D_XOPEN_SOURCE 
CPPFLAGS+=	-D_BSD_SOURCE -D_SVID_SOURCE -D_GNU_SOURCE -DFUNCPROTO=15
CPPFLAGS+=	-DNARROWPROTO -DSCROLLBAR_RIGHT -DOPT_WIDE_CHARS -DXRENDERFONT

LDADD+=		-L${.CURDIR}/../../lib/libtermcap -ltermcap
DPADD+=		${.CURDIR}/../../lib/libtermcap/libtermcap.a

NOGCCERROR=	yes

.include <bsd.prog.mk>
