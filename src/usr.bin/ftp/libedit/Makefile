#	$ssdlinux: Makefile,v 1.5 2004/07/04 05:51:50 yamagata Exp $

.include <bsd.own.mk>

LIB=		edit
SRCS=		chared.c common.c el.c emacs.c fcns.c help.c hist.c \
		key.c map.c parse.c prompt.c read.c refresh.c search.c \
		sig.c term.c tty.c vi.c tokenizer.c history.c

CLEANFILES=	common.h emacs.h fcns.c fcns.h help.c help.h vi.h

DIST=		${.CURDIR}/../../../dist/tnftp
.PATH:		${DIST}/libedit

.if ${IPV6} == "yes"
CPPFLAGS+=	-DHAVE_AF_INET6=1
CPPFLAGS+=	-DHAVE_SOCKADDR_IN6=1
CPPFLAGS+=	-DHAVE_IN6ADDRSZ=1
.endif
CPPFLAGS+=	-I${DIST}/libedit -I${DIST} -I${.CURDIR} -I${.CURDIR}/.. -I${DIST}/libnetbsd
.if defined(CROSS_BUILD) || defined(NEW_GLIBC)
CPPFLAGS+=	-I${DIST}/../termcap
.endif
LIBINET6=	${.CURDIR}/../../../lib/libinet6
.include "${LIBINET6}/Makefile.cflags"

NOGCCERROR=	yes

vi.h: vi.c
	sh makelist -h ${DIST}/libedit/vi.c > ${.TARGET}

emacs.h: emacs.c
	sh makelist -h ${DIST}/libedit/emacs.c > ${.TARGET}

common.h: common.c
	sh makelist -h ${DIST}/libedit/common.c > ${.TARGET}

fcns.h: vi.h emacs.h common.h
	sh makelist -fh vi.h emacs.h common.h > ${.TARGET}

fcns.c: vi.h emacs.h common.h fcns.h
	sh makelist -fc vi.h emacs.h common.h > ${.TARGET}

help.c: vi.c emacs.c common.c help.h
	sh makelist -bc ${DIST}/libedit/vi.c \
		        ${DIST}/libedit/emacs.c \
		        ${DIST}/libedit/common.c > ${.TARGET}

help.h: vi.c emacs.c common.c
	sh makelist -bh ${DIST}/libedit/vi.c \
		        ${DIST}/libedit/emacs.c \
		        ${DIST}/libedit/common.c > ${.TARGET}

libinstall::

.include <bsd.lib.mk>
