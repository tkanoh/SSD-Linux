#	$ssdlinux: Makefile.inc,v 1.3 2002/07/05 07:07:34 kanoh Exp $

WARNS?=	0
WFORMAT?= 2
BINDIR?=/usr/bin
NONLS= yes

.if ${IPV6} == "yes"
CPPFLAGS+= -DINET6 -Dss_family=__ss_family -Dss_len=__ss_len
.endif
