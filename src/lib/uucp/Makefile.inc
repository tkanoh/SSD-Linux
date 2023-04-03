#	$ssdlinux: Makefile.inc,v 1.3 2003/06/12 08:51:14 yamagata Exp $

WARNS?=	0
WFORMAT?= 2
NONLS= yes

CPPFLAGS+=	-Wstrict-prototypes -Wmissing-prototypes
CPPFLAGS+=	-DSBINDIR=\"/usr/libexec/uucp\"
CPPFLAGS+=	-DNEWCONFIGLIB=\"/etc/uucp\"
CPPFLAGS+=	-DOLDCONFIGLIB=\"/etc/uucp/old\"

CPPFLAGS+=	-I${.CURDIR}/../include
