#	$ssdlinux: Makefile,v 1.5 2003/08/29 02:14:12 todoroki Exp $

.include <bsd.own.mk>

.ifmake clean
SUBDIR= libzebra zebra bgpd ripd ospfd vtysh
SUBDIR+= ripngd ospf6d
.else

SUBDIR= libzebra zebra bgpd ripd ospfd vtysh
.if ${IPV6} == "yes"
SUBDIR+= ripngd ospf6d
.endif

.endif

.include <bsd.subdir.mk>

