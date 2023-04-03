#	$ssdlinux: Makefile,v 1.2 2003/01/16 02:05:15 kanoh Exp $

.include <bsd.own.mk>

.if defined(UPDATE_MK)
.undef DESTDIR
.endif

.if ${MKSHARE} != "no"
FILES=	bsd.README bsd.doc.mk bsd.dep.mk bsd.depall.mk bsd.files.mk \
	bsd.hostprog.mk bsd.inc.mk bsd.info.mk bsd.kernobj.mk bsd.kinc.mk \
	bsd.kmod.mk bsd.lib.mk bsd.links.mk bsd.man.mk bsd.nls.mk \
	bsd.obj.mk bsd.own.mk bsd.prog.mk bsd.subdir.mk bsd.sys.mk sys.mk \
	bsd.gnu.mk bsd.mkdist.mk

FILESDIR=/usr/share/mk
.endif
MKOBJ=	no

FILESMODE=444

.include <bsd.prog.mk>
