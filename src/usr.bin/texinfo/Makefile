#	$ssdlinux: Makefile,v 1.8 2005/01/05 03:33:11 yamagata Exp $
#	$NetBSD: Makefile,v 1.10 2001/09/02 23:00:30 wiz Exp $

.include <bsd.own.mk>

SUBDIR=		common .WAIT info infokey install-info makeinfo texi2dvi texi2pdf texindex

.if ${MKSHARE} != "no"
FILESDIR=	/usr/share/texinfo
FILES=		epsf.tex texinfo.tex
.endif

.if ${MKNLS} != "no"
.for F in cs.gmo da.gmo de.gmo de_AT.gmo eo.gmo fr.gmo he.gmo hr.gmo ja.gmo \
	nb.gmo nl.gmo no.gmo ru.gmo sv.gmo tr.gmo zh_CN.gmo zh_TW.gmo
FILES+=		${F}
FILESDIR_${F}=  /usr/share/locale/${F:.gmo=}/LC_MESSAGES
FILESNAME_${F}= texinfo.mo
.endfor
# XXX: Do we want to install the following files too?
#FILES+= 	txi-cs.tex txi-de.tex txi-en.tex txi-es.tex txi-fr.tex \
#		txi-it.tex txi-nl.tex txi-no.tex txi-pl.tex txi-pt.tex txi-tr.tex
.endif

MAN=		info.5 texinfo.5

TEXINFO=	info-stnd.texi info.texi texinfo.txi

DIST=		${.CURDIR}/../../dist
INFOFLAGS=	-I${DIST}/texinfo/doc

.PATH: ${DIST}/texinfo ${DIST}/texinfo/doc ${DIST}/texinfo/po

.include <bsd.man.mk>
.include <bsd.info.mk>
.include <bsd.files.mk>
.include <bsd.subdir.mk>
