#	$ssdlinux: Makefile,v 1.3 2004/06/07 02:11:13 yamagata Exp $

.include <bsd.own.mk>

PROG=		ex
SRCS=		ex.c ex_addr.c ex_cmds.c ex_cmds2.c ex_cmdsub.c
SRCS+=		ex_data.c ex_extern.c ex_get.c ex_io.c ex_put.c ex_re.c
SRCS+=		ex_set.c ex_subr.c ex_tagio.c ex_temp.c ex_tty.c ex_unix.c
SRCS+=		ex_v.c ex_vadj.c ex_vget.c ex_vmain.c ex_voper.c
SRCS+=		ex_vops.c ex_vops2.c ex_vops3.c ex_vput.c ex_vwind.c
SRCS+=		printf.c ex_version.c
MAN=		ex.1 vi.1

DIST=		${.CURDIR}/../../dist/${PROG}
.PATH:		${DIST}

.include "${.CURDIR}/Makefile.cflags"

LDADD+=		${.CURDIR}/../../libexec/exrecover/mapmalloc.o
DPADD+=		${.CURDIR}/../../libexec/exrecover/mapmalloc.o
LIBNCURSESDIR=	${.CURDIR}/../../lib/libncurses/build/lib
LDDIR!=		cd ${LIBNCURSESDIR} && ${PRINTOBJDIR}
LDADD+=		-L${LDDIR} -lncurses
DPADD+=		${LIBNCURSESDIR}/libncurses.a

MLINKS=		ex.1	edit.1
MLINKS+=	vi.1	vedit.1
MLINKS+=	vi.1	view.1
SYMLINKS=	${BINDIR}/ex	${BINDIR}/edit
SYMLINKS+=	${BINDIR}/ex	${BINDIR}/vedit
SYMLINKS+=	${BINDIR}/ex	${BINDIR}/vi
SYMLINKS+=	${BINDIR}/ex	${BINDIR}/view

.include <bsd.prog.mk>
