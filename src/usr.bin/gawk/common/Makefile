#	$ssdlinux: Makefile,v 1.4 2004/08/24 04:08:43 yamagata Exp $

.include <bsd.own.mk>

LIB=		common
SRCS=		array.c awkgram.c builtin.c dfa.c ext.c field.c gawkmisc.c \
		getopt.c getopt1.c io.c main.c msg.c node.c random.c re.c \
		regex.c replace.c version.c

.include "${.CURDIR}/../Makefile.cflags"

libinstall::

.include <bsd.lib.mk>
