#	$ssdlinux: Makefile,v 1.2 2002/05/15 06:33:42 yamagata Exp $
#	$NetBSD: Makefile,v 1.7 2001/12/12 01:49:06 tv Exp $

LIB=		common
SRCS+=		substring.c xexit.c xmalloc.c xstrdup.c

CPPFLAGS+=	-DGNULOCALEDIR=\"/usr/share/locale\" \
		-DLOCALE_ALIAS_PATH=\"/usr/share/locale:.\"

NOLINT=		# defined
NOPROFILE=	# defined
NOPIC=		# defined
NOLINKLIB=	# defined
MKLINT=		no
MKPROFILE=	no
MKPIC=		no
MKLINKLIB=	no

.include <bsd.lib.mk>

.PATH: ${DIST}/texinfo/lib ${DIST}/texinfo/po

all: ${FILES}
.SUFFIXES: .gmo .mo
.gmo.mo:
	@cp $< $@
