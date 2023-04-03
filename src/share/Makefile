#	$ssdlinux: Makefile,v 1.4 2003/08/29 02:14:12 todoroki Exp $

.include <bsd.own.mk>

.ifmake clean
SUBDIR= mk man me tmac kbd
.else

.ifndef BUILD_WORLD
SUBDIR= mk
.endif

SUBDIR+= man me tmac
#SUBDIR+= kbd

#.if ${MKNLS} != "no"
#SUBDIR+=locale
#.endif

.endif

.include <bsd.subdir.mk>
