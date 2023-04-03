#	$ssdlinux: Makefile,v 1.135 2005/03/14 01:14:56 yamagata Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	ncurses-
DISTVERSION=	5.4
GNU_DIST=	yes
DEPENDENT=	lib/libncurses

ROLLUP_DATE=	20041211
ROLLUP_SH=	${DISTNAME}${DISTVERSION}-${ROLLUP_DATE}-patch.sh
OTHER_SITES=	ftp://dickey.his.com/ncurses/${DISTVERSION}
OTHERFILES=	${ROLLUP_SH}.bz2

PATCH_SITES=	ftp://dickey.his.com/ncurses/${DISTVERSION}
PATCH_DATE=	20050312
.if defined(PATCH_DATE)
PATCHFILES+=	${DISTNAME}${DISTVERSION}-20041218.patch.gz
PATCHFILES+=	${DISTNAME}${DISTVERSION}-20041225.patch.gz
PATCHFILES+=	${DISTNAME}${DISTVERSION}-20050101.patch.gz
PATCHFILES+=	${DISTNAME}${DISTVERSION}-20050108.patch.gz
PATCHFILES+=	${DISTNAME}${DISTVERSION}-20050115.patch.gz
PATCHFILES+=	${DISTNAME}${DISTVERSION}-20050122.patch.gz
PATCHFILES+=	${DISTNAME}${DISTVERSION}-20050129.patch.gz
PATCHFILES+=	${DISTNAME}${DISTVERSION}-20050205.patch.gz
PATCHFILES+=	${DISTNAME}${DISTVERSION}-20050212.patch.gz
PATCHFILES+=	${DISTNAME}${DISTVERSION}-20050219.patch.gz
PATCHFILES+=	${DISTNAME}${DISTVERSION}-20050226.patch.gz
PATCHFILES+=	${DISTNAME}${DISTVERSION}-20050305.patch.gz
PATCHFILES+=	${DISTNAME}${DISTVERSION}-${PATCH_DATE}.patch.gz
.endif

.if defined(ROLLUP_DATE)
.if defined(PATCH_DATE)
DISTRELEASE=	${PATCH_DATE}
ALTPATCHCMD=	cd ${DISTDIR}/ncurses && bzip2 -d -c ${DISTFILESDIR}/${OTHERFILES} > ${ROLLUP_SH} && sh ${ROLLUP_SH} && rm ${ROLLUP_SH}; \
		cd ${DISTDIR}/ncurses; \
		for file in ${PATCHFILES}; do \
			echo "Patch  $${file}..."; \
			gzip -d -c ${DISTFILESDIR}/$${file} | patch -p1; \
		done
.else
DISTRELEASE=	${ROLLUP_DATE}
POSTEXTRACT=	cd ${DISTDIR}/ncurses && bzip2 -d -c ${DISTFILESDIR}/${OTHERFILES} > ${ROLLUP_SH} && sh ${ROLLUP_SH} && rm ${ROLLUP_SH}
.endif # defined(PATCH_DATE)
.else
.if defined(PATCH_DATE)
DISTRELEASE=	${PATCH_DATE}
.endif # defined(PATCH_DATE)
.endif # defined(ROLLUP_DATE)

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
