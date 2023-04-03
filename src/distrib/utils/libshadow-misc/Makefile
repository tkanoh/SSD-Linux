#	$ssdlinux: Makefile,v 1.10 2004/02/25 07:39:33 yamagata Exp $

.include <bsd.own.mk>

LIB=		misc
SRCS=		addgrps.c age.c basename.c chkname.c chkshell.c \
		chowndir.c chowntty.c console.c copydir.c entry.c \
		failure.c fields.c getdate.c hushed.c \
		isexpired.c limits.c list.c log.c login_access.c \
		login_desrpc.c login_krb.c loginprompt.c mail.c \
		motd.c myname.c obscure.c pam_pass.c pwd2spwd.c \
		pwdcheck.c pwd_init.c rlogin.c salt.c setugid.c \
		setup.c setupenv.c shell.c strtoday.c \
		sub.c sulog.c ttytype.c tz.c ulimit.c utmp.c valid.c
.if ${TARGET_SSDHOSTTYPEX} == "powerpc-obs50" || ${TARGET_SSDHOSTTYPEX} == "powerpc-obs2xx"
SRCS+=		env.c xmalloc.c
.else
SRCS+=		x_env.c
.endif
MKMAN=		no

DIST=		${.CURDIR}/../../../dist/shadow
.PATH:		${DIST}/libmisc

FORCE_NO_PAM=	yes
.include "${.CURDIR}/../../../lib/shadow/Makefile.cflags"

NOGCCERROR=	yes

libinstall::

.include <bsd.lib.mk>
