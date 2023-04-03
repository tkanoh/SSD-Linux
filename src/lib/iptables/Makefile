#	$ssdlinux: Makefile,v 1.2 2004/06/25 01:11:23 yamagata Exp $

.include <bsd.own.mk>

SUBDIR= libext
.if ${IPV6} == "yes"
SUBDIR+= libext6
.endif
SUBDIR+= share

.include <bsd.subdir.mk>
