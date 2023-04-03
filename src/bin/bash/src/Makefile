#	$ssdlinux: Makefile,v 1.12 2004/08/23 03:34:23 yamagata Exp $

.include <bsd.own.mk>

PROG=		bash
SRCS=		shell.c eval.c y.tab.c general.c make_cmd.c print_cmd.c \
		dispose_cmd.c execute_cmd.c variables.c copy_cmd.c error.c \
		expr.c flags.c jobs.c subst.c hashcmd.c hashlib.c mailcheck.c \
		trap.c input.c unwind_prot.c pathexp.c sig.c test.c version.c \
		alias.c array.c arrayfunc.c braces.c bracecomp.c bashhist.c \
		bashline.c list.c stringlib.c locale.c findcmd.c redir.c \
		pcomplete.c pcomplib.c syntax.c xmalloc.c 
MAN=		${PROG}.1 bashbug.1
SCRIPTS=	bashbug

CLEANFILES=	lsignames.h signames.h syntax.c mksignames mksignames.o bashbug mksyntax

DIST=		${.CURDIR}/../../../dist/${PROG}
.PATH:		${DIST} ${DIST}/doc

LDADD+=		-rdynamic
LDADD+=		-L${.CURDIR}/../libbuiltins -lbuiltins
LDADD+=		-L${.CURDIR}/../libsh -lsh
LDADD+=		-L${.CURDIR}/../libreadline -lreadline
LDADD+=		-L${.CURDIR}/../libhistory -lhistory
LDADD+=		-L${.CURDIR}/../libglob -lglob
LDADD+=		-L${.CURDIR}/../libtilde -ltilde
LDADD+=		-L${.CURDIR}/../libmalloc -lmalloc
.if ${TARGET_HOSTTYPE} == "i386"
LDADD+=		-L${.CURDIR}/../../../lib/libtermcap -ltermcap
.elif ${TARGET_HOSTTYPE} == "powerpc"
LDADD+=		${.CURDIR}/../../../lib/libtermcap/libtermcap.a
.endif
LDADD+=		-ldl
DPADD+=		${.CURDIR}/../libbuiltins/libbuiltins.a
DPADD+=		${.CURDIR}/../libreadline/libreadline.a
DPADD+=		${.CURDIR}/../libhistory/libhistory.a
DPADD+=		${.CURDIR}/../libglob/libglob.a
DPADD+=		${.CURDIR}/../libtilde/libtilde.a
DPADD+=		${.CURDIR}/../libmalloc/libmalloc.a
DPADD+=		${.CURDIR}/../libsh/libsh.a
DPADD+=		${LIBTERMCAP}

LINKS=		${BINDIR}/bash ${BINDIR}/sh

mksignames: 
	${HOST_CC} ${CPPFLAGS} -o ${.TARGET} ${DIST}/support/${.TARGET}.c

mksyntax:
	${HOST_CC} ${CPPFLAGS} -o ${.TARGET} ${DIST}/${.TARGET}.c

syntax.c: signames.h mksyntax
	./mksyntax -o ${.TARGET}

lsignames.h: mksignames
	./mksignames ${.TARGET}

signames.h: lsignames.h
	if cmp -s lsignames.h ${.TARGET} ; then :; \
		else rm -f ${.TARGET} ; cp lsignames.h ${.TARGET} ; fi

bashbug:
	sed -e "s%!MACHINE!%$(MACHINE_ARCH)%" -e "s%!OS!%linux-gnu%" \
	    -e "s%!CFLAGS!%$(CPPFLAGS)%" -e "s%!CC!%$(CC)%" \
	    -e "s%!RELEASE!%$(BASHVERSION)%" -e "s%!PATCHLEVEL!%$(BASHPATCHLEVEL)%" \
	    -e "s%!MACHTYPE!%$(TARGET_MACHTYPE)%" -e "s%!RELSTATUS!%$(RELSTATUS)%" \
	    ${DIST}/support/${.TARGET}.sh > ${.TARGET}

trap.o: signames.h

NOGCCERROR=	yes
.include <bsd.prog.mk>
