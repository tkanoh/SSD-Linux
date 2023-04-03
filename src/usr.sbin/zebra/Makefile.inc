#	$ssdlinux: Makefile.inc,v 1.6 2003/11/29 15:53:33 kanoh Exp $

BINDIR?=	/usr/sbin
WARNS?=		0
NONLS=		yes

CPPFLAGS+=	-DHAVE_CONFIG_H -DSYSCONFDIR=\"/etc/\"
CPPFLAGS+=	-DMULTIPATH_NUM=1 -Wall
CPPFLAGS+=	-I${.CURDIR}/../include	-I${DIST} -I${DIST}/lib
.if ${TARGET_HOSTTYPE} == "powerpc"
CPPFLAGS+=	-DWORDS_BIGENDIAN=1
.endif

LIBREADLINEDIR=	${.CURDIR}/../../../lib/readline/readline
LIBNCURSESDIR=	${.CURDIR}/../../../lib/libncurses/build/lib
LDDIR_R!=	cd ${LIBREADLINEDIR} && ${PRINTOBJDIR}
LDDIR_N!=	cd ${LIBNCURSESDIR} && ${PRINTOBJDIR}
LDADD+=		-L${.CURDIR}/../libzebra -lzebra
LDADD+=		-lm -lcrypt
LDADD+=		-L${LDDIR_R} -lreadline
LDADD+=		-L${LDDIR_N} -lncurses
DPADD+=		${.CURDIR}/../libzebra/libzebra.a
DPADD+=		${LIBREADLINEDIR}/libreadline.a
DPADD+=		${LIBNCURSESDIR}/libncurses.a

NOGCCERROR=	yes
