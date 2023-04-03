#	$ssdlinux: Makefile,v 1.3 2002/10/11 09:58:14 kanoh Exp $

.include <bsd.own.mk>

PROG=		mipdiag
.ifdef DESTDIR
FILES=		network-mip6.conf
FILESMODE=	444
FILESDIR=	/etc
.endif
MAN=		${PROG}.8 mipv6_sas.conf.5 network-mip6.conf.5

DIST=		${.CURDIR}/../../dist/usagi-tool/src/miplv6
.PATH:		${DIST}

network-mip6.conf:
	sed -e "s/\@sysconfdir\@/`echo /etc | sed -e 's#/#\\\\/#g'`/g" \
		${DIST}/network-mip6.conf.in > network-mip6.conf
${MAN}:
	cp ${DIST}/${.TARGET}.man ${.TARGET}

CLEANFILES+=	network-mip6.conf ${MAN}

.include <bsd.prog.mk>
