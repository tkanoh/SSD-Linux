#	$ssdlinux: Makefile,v 1.4 2004/06/16 23:06:56 kanoh Exp $

.include <bsd.own.mk>

LIB=		misc
SRCS=		addgrps.c age.c basename.c chkname.c chkshell.c \
		chowndir.c chowntty.c console.c copydir.c entry.c \
		env.c failure.c fields.c getdate.c hushed.c \
		isexpired.c limits.c list.c log.c login_access.c \
		login_desrpc.c login_krb.c loginprompt.c mail.c \
		motd.c myname.c obscure.c pam_pass.c pwd2spwd.c \
		pwdcheck.c pwd_init.c rlogin.c salt.c setugid.c \
		setup.c setupenv.c shell.c strtoday.c \
		sub.c sulog.c ttytype.c tz.c ulimit.c utmp.c \
		valid.c xmalloc.c
MKMAN=		no

DIST=		${.CURDIR}/../../../dist/shadow
.PATH:		${DIST}/libmisc

FORCE_NO_PAM=	yes
.include "${.CURDIR}/../Makefile.cflags"

libinstall::

.include <bsd.lib.mk>
