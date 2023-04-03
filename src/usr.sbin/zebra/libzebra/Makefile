#	$ssdlinux: Makefile,v 1.4 2003/11/29 15:53:33 kanoh Exp $

.include <bsd.own.mk>

LIB=		zebra
SRCS=		version.c network.c pid_output.c getopt.c getopt1.c \
		daemon.c print_version.c checksum.c vector.c linklist.c \
		vty.c command.c sockunion.c prefix.c thread.c if.c \
		memory.c buffer.c table.c hash.c filter.c routemap.c \
		distribute.c stream.c str.c log.c plist.c zclient.c \
		sockopt.c smux.c md5.c keychain.c 

DIST=		${.CURDIR}/../../../dist/zebra
.PATH:		${DIST}/lib

libinstall::

CLEANFILES=	version.c

version.c:
	echo '' >version.c
	echo 'char *host_name = "${TARGET_MACHTYPE}";' >>version.c

.include <bsd.lib.mk>
