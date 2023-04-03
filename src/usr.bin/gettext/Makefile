#	$ssdlinux: Makefile,v 1.8 2005/02/25 07:04:40 yamagata Exp $
#	$NetBSD: Makefile,v 1.3 2000/11/08 16:26:46 itojun Exp $

.include <bsd.own.mk>

# gettext-runtime
SUBDIR=	libgrt .WAIT gettext ngettext envsubst

# gettext-tools/
# lib
SUBDIR+=lib .WAIT \
# info
SUBDIR+=info
# src
SUBDIR+=msgcmp .WAIT msgfmt .WAIT msgmerge .WAIT msgunfmt .WAIT xgettext .WAIT msgattrib .WAIT \
	msgcat .WAIT msgcomm msgconv msgen msgexec msgfilter libgrep .WAIT msggrep msginit msguniq
# misc
SUBDIR+=gettextize autopoint

#.if ${MKNLS} != "no"
##SUBDIR+=locale
#.endif

.include <bsd.subdir.mk>
