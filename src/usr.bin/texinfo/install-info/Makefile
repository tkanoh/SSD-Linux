#	$ssdlinux: Makefile,v 1.4 2002/12/03 03:11:40 yamagata Exp $
#	$NetBSD: Makefile,v 1.5 2002/03/01 06:03:20 jmc Exp $

PROG=		install-info

.include <bsd.prog.mk>

.PATH: ${DIST}/texinfo/util ${DIST}/texinfo/doc

infodir-meta:
.if defined(UNPRIVED) && (${MKINFO} != "no")
	echo "${DESTDIR}/usr/share/info/dir type=file mode=0644 uname=root gname=wheel" | \
		sed -e 's|^/|./|g' -e 's|//|/|g' >>${METALOG}
.endif
