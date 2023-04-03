#	$ssdlinux: Makefile,v 1.3 2004/05/31 06:39:42 yamagata Exp $

.include <bsd.own.mk>

LIB=		pam

SRCS=		pam_item.c pam_strerror.c pam_end.c pam_start.c pam_data.c \
		pam_delay.c pam_dispatch.c pam_handlers.c pam_misc.c \
		pam_account.c pam_auth.c pam_session.c pam_password.c \
		pam_env.c pam_log.c

MAN=		pam.8 pam.conf.8 pam.d.8
MAN+=		pam_authenticate.3 pam_chauthtok.3 pam_close_session.3
MAN+=		pam_end.3 pam_fail_delay.3 pam_open_session.3
MAN+=		pam_setcred.3 pam_start.3 pam_strerror.3

INCS=		_pam_aconf.h pam_filter.h
INCS+=		_pam_compat.h _pam_macros.h _pam_types.h pam_appl.h 
INCS+=		pam_malloc.h  pam_modules.h

# pam.conf install from src/etc
#FILES=		pam.conf
#FILESDIR=	/etc
#FILESMODE=	444
MKPIC=		yes
MKPICINSTALL=	no

DIST=		${.CURDIR}/../../../dist/Linux-PAM
.PATH:		${DIST}/libpam ${DIST}/doc/man \
		${.CURDIR}/../include/security ${DIST}/libpam/include/security \
		${DIST}/modules/pam_filter/include

.include "${.CURDIR}/../Makefile.cflags"

.include <bsd.lib.mk>
