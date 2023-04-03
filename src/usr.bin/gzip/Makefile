#	$ssdlinux: Makefile,v 1.3 2004/06/16 02:28:23 yamagata Exp $

.include <bsd.own.mk>

PROG=		gzip
SRCS=		${PROG}.c zip.c deflate.c trees.c bits.c unzip.c inflate.c \
		util.c crypt.c lzw.c unlzw.c unlzh.c unpack.c getopt.c
MAN=		gzexe.1 gzip.1 zdiff.1 zforce.1 zgrep.1 zmore.1 znew.1
	
DIST=		${.CURDIR}/../../dist/gzip
.PATH:		${DIST}

CPPFLAGS+=	-DSTDC_HEADERS=1 -DHAVE_UNISTD_H=1 -DDIRENT=1 -Dunix -I${DIST}

.if (${MACHINE_ARCH} == "m68k" || ${MACHINE_ARCH} == "i386")
SRCS+=		match.S
CPPFLAGS+=	-DASMV
MATCHCPPFLAGS=	-traditional -D__linux__

.if (${OBJECT_FMT} == "ELF")
MATCHCPPFLAGS+=	-DNO_UNDERLINE
.endif

.endif	# m68k || i386

LDSTATIC?= 	-static
#LDADD+=	-lbz2
#DPADD+=	${LIBBZ2}

MLINKS+= 	gzip.1 gunzip.1 gzip.1 gzcat.1 gzip.1 zcat.1
MLINKS+= 	zdiff.1 zcmp.1
#MLINKS+= 	gzip.1 uncompress.1
MLINKS+= 	zgrep.1 zegrep.1 zgrep.1 zfgrep.1
LINKS+=		${BINDIR}/gzip ${BINDIR}/gunzip
LINKS+=		${BINDIR}/gzip ${BINDIR}/gzcat
LINKS+=		${BINDIR}/gzip ${BINDIR}/zcat
LINKS+=		${BINDIR}/zdiff ${BINDIR}/zcmp
#LINKS+=		${BINDIR}/gzip ${BINDIR}/uncompress
LINKS+=		${BINDIR}/zgrep ${BINDIR}/zegrep
LINKS+=		${BINDIR}/zgrep ${BINDIR}/zfgrep

FILES=		zforce gzexe znew zmore zdiff zgrep
FILESMODE=	${BINMODE}
CLEANFILES=	zforce gzexe znew zmore zdiff zgrep

.if (${MACHINE_ARCH} == "m68k" || ${MACHINE_ARCH} == "i386")
match.o: ${DIST}/match.S
	$(CPP) ${MATCHCPPFLAGS} ${DIST}/match.S >_match.s
	$(CC) -c _match.s
	mv _match.o match.o
	rm -f _match.s
.endif

all: zforce gzexe znew zmore zdiff zgrep

zdiff: zdiff.in
	sed -e "1d" -e "s|BINDIR|${BINDIR}|" ${DIST}/${.TARGET}.in > ${.TARGET}

zgrep: zgrep.in
	sed -e "1d" -e "s|BINDIR|${BINDIR}|" ${DIST}/${.TARGET}.in > ${.TARGET}

zmore: zmore.in
	sed -e "1d" -e "s|BINDIR|${BINDIR}|" ${DIST}/${.TARGET}.in > ${.TARGET}

znew: znew.in
	sed -e "1d" -e "s|BINDIR|${BINDIR}|" ${DIST}/${.TARGET}.in > ${.TARGET}

zforce: zforce.in
	sed -e "1d" -e "s|BINDIR|${BINDIR}|" ${DIST}/${.TARGET}.in > ${.TARGET}

gzexe: gzexe.in
	sed -e "1d" -e "s|BINDIR|${BINDIR}|" ${DIST}/${.TARGET}.in > ${.TARGET}

NOGCCERROR=	yes

.include <bsd.prog.mk>
