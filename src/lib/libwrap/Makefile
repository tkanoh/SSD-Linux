#	$ssdlinux: Makefile,v 1.2 2002/06/18 06:44:08 yamagata Exp $

.include <bsd.own.mk>

LIB=		wrap

SRCS=		hosts_access.c options.c shell_cmd.c rfc931.c eval.c \
		hosts_ctl.c refuse.c percent_x.c clean_exit.c setenv.c \
		fromhost.c fix_options.c socket.c tli.c workarounds.c \
		update.c misc.c diag.c percent_m.c myvsyslog.c
MAN=		hosts_access.3 hosts_access.5 hosts_options.5
MLINKS+=	hosts_access.5 hosts.allow.5
MLINKS+=	hosts_access.5 hosts.deny.5
MLINKS+=	hosts_access.3 hosts_ctl.3
MLINKS+=	hosts_access.3 request_init.3
MLINKS+=	hosts_access.3 request_set.3

INCS=		tcpd.h
INCSDIR=	/usr/include

DIST=		${.CURDIR}/../../dist/usagi-tool/src/tcp_wrappers
.PATH:		${DIST}

CPPFLAGS+=	-I${DIST}
LIBINET6=	${.CURDIR}/../libinet6
.include "${LIBINET6}/Makefile.cflags"

.include "Makefile.cflags"

.include <bsd.lib.mk>
