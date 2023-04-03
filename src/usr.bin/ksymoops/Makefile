#	$ssdlinux: Makefile,v 1.5 2002/12/29 17:00:13 kanoh Exp $

.include 	<bsd.own.mk>

PROG=		ksymoops
SRCS=		io.c ksyms.c ${PROG}.c map.c misc.c object.c oops.c re.c \
		symbol.c
MAN=		${PROG}.8
BINMODE=	555

DIST=		${.CURDIR}/../../dist/${PROG}
.PATH:		${DIST}

CPPFLAGS+=	-Dlinux -Wall -Wno-conversion -Waggregate-return 
CPPFLAGS+=	-Wstrict-prototypes -Wmissing-prototypes
CPPFLAGS+=	-DINSTALL_PREFIX="\"/usr\"" -DCROSS="\"\""
CPPFLAGS+=	-DDEF_KSYMS=\"/proc/ksyms\"
CPPFLAGS+=	-DDEF_LSMOD=\"/proc/modules\"
CPPFLAGS+=	-DDEF_OBJECTS=\"/lib/modules/*r/\"
CPPFLAGS+=	-DDEF_MAP=\"/System.map\"
CPPFLAGS+=	-I${.CURDIR}/../binutils/build/bfd
CPPFLAGS+=	-I${DIST}/../binutils/include

LDADD+=		-Wl,-Bstatic
LDADD+=		-L${.CURDIR}/../binutils/build/bfd -lbfd
LDADD+=		-L${.CURDIR}/../binutils/build/libiberty -liberty
LDADD+=		-Wl,-Bdynamic

NOGCCERROR=	yes

.include <bsd.prog.mk>
