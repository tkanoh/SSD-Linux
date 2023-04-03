#	$ssdlinux: Makefile,v 1.14 2003/08/29 02:14:11 todoroki Exp $

.include <bsd.own.mk>

.ifmake clean
SUBDIR=         thttpd setup samba netatalk
.else

.if ${TARGET_SSDHOSTTYPEX} == "powerpc-obs2xx"
SUBDIR=		thttpd setup
.ifmake clean
SUBDIR+=	samba netatalk
.endif
.endif

.endif

.include <bsd.subdir.mk>
