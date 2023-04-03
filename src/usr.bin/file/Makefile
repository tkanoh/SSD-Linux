#	$ssdlinux: Makefile,v 1.19 2005/02/14 03:15:50 yamagata Exp $

.include <bsd.own.mk>

PROG=		file
VERSION=	4.13
SRCS=		file.c magic.c apprentice.c softmagic.c ascmagic.c \
		compress.c is_tar.c readelf.c print.c fsmagic.c \
		funcs.c apptype.c
MAN=		${PROG}.1 magic.4 libmagic.3
FILES=		magic magic.mime magic.mgc magic.mime.mgc
FILESDIR=	/usr/share/file
MAGIC=		${FILESDIR}/magic
CLEANFILES=	${MAN} magic magic.mime magic.mgc magic.mime.mgc

DIST=		${.CURDIR}/../../dist/${PROG}
.PATH:		${DIST}/src ${DIST}/magic ${DIST}/doc

CPPFLAGS=	-DHAVE_CONFIG_H -I${.CURDIR} -DMAGIC='"${MAGIC}"'
.if defined(CROSS_BUILD) || defined(NEW_GLIBC)
CPPFLAGS+=	-I${DIST}/../zlib
.endif

LDADD=		-L${.CURDIR}/../../lib/libz -lz

realall:	file magic magic.mgc magic.mime.mgc

magic_FRAGMENTS = \
Magdir/acorn \
Magdir/adi \
Magdir/adventure \
Magdir/allegro \
Magdir/alliant \
Magdir/alpha \
Magdir/amanda \
Magdir/amigaos \
Magdir/animation \
Magdir/apl \
Magdir/apple \
Magdir/applix \
Magdir/archive \
Magdir/asterix \
Magdir/att3b \
Magdir/audio \
Magdir/bFLT \
Magdir/blender \
Magdir/blit \
Magdir/bout \
Magdir/bsdi \
Magdir/cad \
Magdir/c-lang \
Magdir/c64 \
Magdir/cddb \
Magdir/chi \
Magdir/chord \
Magdir/cisco \
Magdir/citrus \
Magdir/claris \
Magdir/clipper \
Magdir/spec \
Magdir/commands \
Magdir/communications \
Magdir/compress \
Magdir/console \
Magdir/convex \
Magdir/ctags \
Magdir/dact \
Magdir/database \
Magdir/diamond \
Magdir/diff \
Magdir/digital \
Magdir/dolby \
Magdir/dump \
Magdir/editors \
Magdir/elf \
Magdir/encore \
Magdir/epoc \
Magdir/esri \
Magdir/fcs \
Magdir/filesystems \
Magdir/flash \
Magdir/fonts \
Magdir/frame \
Magdir/freebsd \
Magdir/fsav \
Magdir/games \
Magdir/geos \
Magdir/gcc \
Magdir/gimp \
Magdir/gnu \
Magdir/grace \
Magdir/gringotts \
Magdir/hdf \
Magdir/hitachi-sh \
Magdir/hp \
Magdir/human68k \
Magdir/ibm370 \
Magdir/ibm6000 \
Magdir/iff \
Magdir/images \
Magdir/intel \
Magdir/interleaf \
Magdir/island \
Magdir/ispell \
Magdir/java \
Magdir/jpeg \
Magdir/karma \
Magdir/lecter \
Magdir/lex \
Magdir/lif \
Magdir/linux \
Magdir/lisp \
Magdir/mach \
Magdir/macintosh \
Magdir/magic \
Magdir/mail.news \
Magdir/maple \
Magdir/mathematica \
Magdir/matroska \
Magdir/mcrypt \
Magdir/mime \
Magdir/mips \
Magdir/mirage \
Magdir/misctools \
Magdir/mkid \
Magdir/mlssa \
Magdir/mmdf \
Magdir/modem \
Magdir/motorola \
Magdir/msdos \
Magdir/msvc \
Magdir/natinst \
Magdir/ncr \
Magdir/netbsd \
Magdir/netscape \
Magdir/news \
Magdir/nitpicker \
Magdir/ocaml \
Magdir/octave \
Magdir/olf \
Magdir/os2 \
Magdir/os9 \
Magdir/osf1 \
Magdir/palm \
Magdir/parix \
Magdir/pbm \
Magdir/pdf \
Magdir/pdp \
Magdir/perl \
Magdir/pgp \
Magdir/pkgadd \
Magdir/plan9 \
Magdir/plus5 \
Magdir/printer \
Magdir/project \
Magdir/psdbms \
Magdir/psion \
Magdir/pulsar \
Magdir/pyramid \
Magdir/python \
Magdir/riff \
Magdir/revision \
Magdir/rpm \
Magdir/rtf \
Magdir/sc \
Magdir/sccs \
Magdir/sendmail \
Magdir/sequent \
Magdir/sgi \
Magdir/sgml \
Magdir/sharc \
Magdir/sinclair \
Magdir/sketch \
Magdir/smalltalk \
Magdir/sniffer \
Magdir/dyadic \
Magdir/softquad \
Magdir/spectrum \
Magdir/sql \
Magdir/sun \
Magdir/sysex \
Magdir/teapot \
Magdir/terminfo \
Magdir/tex \
Magdir/tgif \
Magdir/ti-8x \
Magdir/timezone \
Magdir/troff \
Magdir/tuxedo \
Magdir/typeset \
Magdir/unknown \
Magdir/uuencode \
Magdir/varied.out \
Magdir/varied.script \
Magdir/vax \
Magdir/vicar \
Magdir/virtutech \
Magdir/visx \
Magdir/vms \
Magdir/vmware \
Magdir/vorbis \
Magdir/vxl \
Magdir/wordprocessors \
Magdir/xdelta \
Magdir/xenix \
Magdir/xo65 \
Magdir/xwindows \
Magdir/zilog \
Magdir/zyxel

magic: Header Localstuff ${magic_FRAGMENTS}
	cat ${DIST}/magic/Header ${DIST}/magic/Localstuff > ${.TARGET}
	for frag in ${magic_FRAGMENTS}; do \
		if test -f ${DIST}/magic/$$frag; then \
			f=${DIST}/magic/$$frag; \
		else \
			f=$$frag; \
		fi; \
		cat $$f; \
	done >> ${.TARGET}

magic.mgc: magic file
.if defined(CROSS_BUILD) || defined(NEW_GLIBC)
	file -C -m magic
.else
	${.CURDIR}/file -C -m magic
.endif

magic.mime.mgc: magic.mime file
	cp ${DIST}/magic/magic.mime ${.CURDIR}
	file -C -m magic.mime

file.1: Makefile file.man
	@rm -f ${.TARGET}
	sed -e s@__CSECTION__@1@g \
	    -e s@__FSECTION__@4@g \
	    -e s@__VERSION__@${VERSION}@g \
	    -e s@__MAGIC__@${MAGIC}@g ${DIST}/doc/file.man > ${.TARGET}

magic.4: Makefile magic.man
	@rm -f ${.TARGET}
	sed -e s@__CSECTION__@1@g \
	    -e s@__FSECTION__@4@g \
	    -e s@__VERSION__@${VERSION}@g \
	    -e s@__MAGIC__@${MAGIC}@g ${DIST}/doc/magic.man > ${.TARGET}

libmagic.3: Makefile libmagic.man
	@rm -f ${.TARGET}
	sed -e s@__CSECTION__@1@g \
	    -e s@__FSECTION__@4@g \
	    -e s@__VERSION__@${VERSION}@g \
	    -e s@__MAGIC__@${MAGIC}@g ${DIST}/doc/libmagic.man > ${.TARGET}

.include <bsd.prog.mk>
