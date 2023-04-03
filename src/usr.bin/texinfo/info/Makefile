#	$ssdlinux: Makefile,v 1.11 2005/01/05 04:06:31 yamagata Exp $
#	$NetBSD: Makefile,v 1.3 2001/09/02 22:16:58 wiz Exp $
.include <bsd.own.mk>

PROG=		info
SRCS=		dir.c display.c display.h doc.h dribble.c dribble.h \
		echo-area.c echo-area.h \
		filesys.c filesys.h footnotes.c footnotes.h gc.c gc.h \
		indices.c indices.h info-utils.c info-utils.h info.c info.h infodoc.c \
		infomap.c infomap.h m-x.c man.c man.h nodemenu.c nodes.c nodes.h \
		search.c search.h session.c session.h signals.c signals.h \
		termdep.h terminal.c terminal.h tilde.c tilde.h \
		variables.c variables.h window.c window.h \
		doc.c funs.h key.c
MAN=		${PROG}.1 ${PROG}.5

CPPFLAGS+=	-I${DIST}/texinfo/info \
		-DINFODIR=\"/usr/pkg/info:/usr/X11R6/info:/usr/X11/info:/usr/local/info:/usr/share/info:/usr/info\"
CPPFLAGS+=	-I${.CURDIR}
LDADD+=		-L${DIST}/../lib/libtermcap -ltermcap
DPADD+=		${LIBTERMCAP}

.if ${TARGET_HOSTTYPE} == "powerpc"
NOGCCERROR=	yes
.endif

.include <bsd.prog.mk>

.PATH: ${DIST}/texinfo/info ${DIST}/texinfo/doc
