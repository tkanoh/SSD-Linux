#	$ssdlinux: Makefile,v 1.2 2002/06/06 09:38:28 yamagata Exp $

.include <bsd.own.mk>

.for F in da.gmo de.gmo es.gmo fr.gmo ko.gmo nl.gmo no.gmo no@nynorsk.gmo \
	pl.gmo pt.gmo sl.gmo sv.gmo
FILES+=		${F}
FILESDIR_${F}=	/usr/share/locale/${F:.gmo=}/LC_MESSAGES
FILESNAME_${F}=	gettext.mo
.endfor

.PATH: ${DIST}/gettext/po

.include <bsd.prog.mk>
