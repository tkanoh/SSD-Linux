#	$ssdlinux: Makefile.inc,v 1.1.1.1 2002/05/02 13:37:07 kanoh Exp $

BINDIR?=	/usr/libexec/postfix
WARNS?=		0
NONLS=		yes

.include "${.CURDIR}/../../../lib/postfix/Makefile.cflags"
