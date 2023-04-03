#	$ssdlinux: Makefile.inc,v 1.3 2002/06/06 06:51:55 yamagata Exp $

BINDIR?=	/usr/sbin
WARNS?=		0
WFORMAT?=	2
NONLS=		yes

NOGCCERROR=	yes

CPPFLAGS+=	-Wall -W -Wpointer-arith -Wbad-function-cast -Wcast-qual \
		-Wstrict-prototypes -Wmissing-prototypes \
		-Wmissing-declarations -Wnested-externs -Winline \
		-I${DIST}/timed -I${DIST}/timedc
