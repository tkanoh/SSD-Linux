#	$ssdlinux: sys.mk,v 1.12 2003/03/18 01:23:38 kanoh Exp $
#	$NetBSD: sys.mk,v 1.60 2001/06/29 23:50:01 eeh Exp $
#	@(#)sys.mk	8.2 (Berkeley) 3/21/94

unix?=		We run NetBSD.

.SUFFIXES: .out .a .ln .o .s .S .c .cc .cpp .cxx .C .F .f .r .y .l .cl .p .h
.SUFFIXES: .sh .m4

.LIBS:		.a

.if defined(DESTDIR)
.if defined(CROSS_BUILD)
CC?=		${TARGET_MACHTYPE}-gcc
AR?=		${TARGET_MACHTYPE}-ar
RANLIB?=	${TARGET_MACHTYPE}-ranlib
AS?=		${TARGET_MACHTYPE}-as
.endif
.if defined(NEW_GLIBC)
CC?=		${TARGET_MACHTYPE}${NEW_GLIBC}-gcc
AR?=		${TARGET_MACHTYPE}${NEW_GLIBC}-ar
RANLIB?=	${TARGET_MACHTYPE}${NEW_GLIBC}-ranlib
AS?=		${TARGET_MACHTYPE}${NEW_GLIBC}-as
.endif
AR?=		ar
RANLIB?=	ranlib
AS?=		as
.else
AR?=		ar
RANLIB?=	ranlib
AS?=		as
.endif

ARFLAGS?=	rl

AFLAGS?=
.if ${MACHINE_ARCH} == "sparc64" 
AFLAGS+= -Wa,-Av9a
.endif
COMPILE.s?=	${CC} ${AFLAGS} -c
LINK.s?=	${CC} ${AFLAGS} ${LDFLAGS}
COMPILE.S?=	${CC} ${AFLAGS} ${CPPFLAGS} -c -traditional-cpp
LINK.S?=	${CC} ${AFLAGS} ${CPPFLAGS} ${LDFLAGS}

.if defined(DESTDIR)
.if defined(CROSS_BUILD)
CC?=		${TARGET_MACHTYPE}-gcc
.endif
.if defined(NEW_GLIBC)
CC?=		${TARGET_MACHTYPE}${NEW_GLIBC}-gcc
.endif
CC?=		gcc
.else
CC?=		gcc
.endif

.if ${MACHINE_ARCH} == "alpha" || \
    ${MACHINE_ARCH} == "arm" || ${MACHINE_ARCH} == "arm26" || \
		${MACHINE_ARCH} == "arm32" || \
    ${MACHINE_ARCH} == "i386" || \
    ${MACHINE_ARCH} == "m68k" || \
    ${MACHINE_ARCH} == "mipsel" || ${MACHINE_ARCH} == "mipseb" || \
    ${MACHINE_ARCH} == "sparc" || \
    ${MACHINE_ARCH} == "vax"
DBG?=	-O2
.elif ${MACHINE_ARCH} == "x86_64"
DBG?=
.else
DBG?=	-O
.endif
CFLAGS?=	${DBG}
COMPILE.c?=	${CC} ${CFLAGS} ${CPPFLAGS} -c
LINK.c?=	${CC} ${CFLAGS} ${CPPFLAGS} ${LDFLAGS}

.if defined(DESTDIR)
.if defined(CROSS_BUILD)
CXX?=		${TARGET_MACHTYPE}-c++
.endif
.if defined(NEW_GLIBC)
CXX?=		${TARGET_MACHTYPE}${NEW_GLIBC}-c++
.endif
CXX?=		c++
.else
CXX?=		c++
.endif
CXXFLAGS?=	${CFLAGS}
COMPILE.cc?=	${CXX} ${CXXFLAGS} ${CPPFLAGS} -c
LINK.cc?=	${CXX} ${CXXFLAGS} ${CPPFLAGS} ${LDFLAGS}

OBJC?=		${CC}
OBJCFLAGS?=	${CFLAGS}
COMPILE.m?=	${OBJC} ${OBJCFLAGS} ${CPPFLAGS} -c
LINK.m?=	${OBJC} ${OBJCFLAGS} ${CPPFLAGS} ${LDFLAGS}

.if defined(DESTDIR)
.if defined(CROSS_BUILD)
CPP?=		${TARGET_MACHTYPE}-cpp
.endif
.if defined(NEW_GLIBC)
CPP?=		${TARGET_MACHTYPE}${NEW_GLIBC}-cpp
.endif
CPP?=		cpp
.else
CPP?=		cpp
.endif
CPPFLAGS?=	

FC?=		f77
FFLAGS?=	-O
RFLAGS?=
COMPILE.f?=	${FC} ${FFLAGS} -c
LINK.f?=	${FC} ${FFLAGS} ${LDFLAGS}
COMPILE.F?=	${FC} ${FFLAGS} ${CPPFLAGS} -c
LINK.F?=	${FC} ${FFLAGS} ${CPPFLAGS} ${LDFLAGS}
COMPILE.r?=	${FC} ${FFLAGS} ${RFLAGS} -c
LINK.r?=	${FC} ${FFLAGS} ${RFLAGS} ${LDFLAGS}

.if defined(CROSS_BUILD)
INSTALL?=	${TARGET_MACHTYPE}-install
.else
INSTALL?=	install
.endif

LEX?=		lex
LFLAGS?=
LEX.l?=		${LEX} ${LFLAGS}

.if defined(DESTDIR)
.if defined(CROSS_BUILD)
LD?=		${TARGET_MACHTYPE}-ld
.endif
.if defined(NEW_GLIBC)
LD?=		${TARGET_MACHTYPE}${NEW_GLIBC}-ld
.endif
LD?=		ld
.else
LD?=		ld
.endif
LDFLAGS?=

LINT?=		lint
LINTFLAGS?=	-chapbxzF

LORDER?=	lorder

MAKE?=		bmake
GMAKE?=		make

.if defined(DESTDIR)
.if defined(CROSS_BUILD)
NM?=		${TARGET_MACHTYPE}-nm
.endif
.if defined(NEW_GLIBC)
NM?=		${TARGET_MACHTYPE}${NEW_GLIBC}-nm
.endif
NM?=		nm
.else
NM?=		nm
.endif

PC?=		pc
PFLAGS?=
COMPILE.p?=	${PC} ${PFLAGS} ${CPPFLAGS} -c
LINK.p?=	${PC} ${PFLAGS} ${CPPFLAGS} ${LDFLAGS}

SHELL?=		sh

.if defined(DESTDIR)
.if defined(CROSS_BUILD)
SIZE?=		${TARGET_MACHTYPE}-size
.endif
.if defined(NEW_GLIBC)
SIZE?=		${TARGET_MACHTYPE}${NEW_GLIBC}-size
.endif
SIZE?=		size
.else
SIZE?=		size
.endif

TSORT?= 	tsort -q

YACC?=		bison
YFLAGS?=
YACC.y?=	${YACC} ${YFLAGS}

# C
.c:
	${LINK.c} -o ${.TARGET} ${.IMPSRC} ${LDLIBS}
.c.o:
	${COMPILE.c} ${.IMPSRC}
.c.a:
	${COMPILE.c} ${.IMPSRC}
	${AR} ${ARFLAGS} $@ $*.o
	rm -f $*.o
.c.ln:
	${LINT} ${LINTFLAGS} ${CPPFLAGS:M-[IDU]*} -i ${.IMPSRC}

# C++
.cc .cpp .cxx .C:
	${LINK.cc} -o ${.TARGET} ${.IMPSRC} ${LDLIBS}
.cc.o .cpp.o .cxx.o .C.o:
	${COMPILE.cc} ${.IMPSRC}
.cc.a .cpp.a .cxx.a .C.a:
	${COMPILE.cc} ${.IMPSRC}
	${AR} ${ARFLAGS} $@ $*.o
	rm -f $*.o

# Fortran/Ratfor
.f:
	${LINK.f} -o ${.TARGET} ${.IMPSRC} ${LDLIBS}
.f.o:
	${COMPILE.f} ${.IMPSRC}
.f.a:
	${COMPILE.f} ${.IMPSRC}
	${AR} ${ARFLAGS} $@ $*.o
	rm -f $*.o

.F:
	${LINK.F} -o ${.TARGET} ${.IMPSRC} ${LDLIBS}
.F.o:
	${COMPILE.F} ${.IMPSRC}
.F.a:
	${COMPILE.F} ${.IMPSRC}
	${AR} ${ARFLAGS} $@ $*.o
	rm -f $*.o

.r:
	${LINK.r} -o ${.TARGET} ${.IMPSRC} ${LDLIBS}
.r.o:
	${COMPILE.r} ${.IMPSRC}
.r.a:
	${COMPILE.r} ${.IMPSRC}
	${AR} ${ARFLAGS} $@ $*.o
	rm -f $*.o

# Pascal
.p:
	${LINK.p} -o ${.TARGET} ${.IMPSRC} ${LDLIBS}
.p.o:
	${COMPILE.p} ${.IMPSRC}
.p.a:
	${COMPILE.p} ${.IMPSRC}
	${AR} ${ARFLAGS} $@ $*.o
	rm -f $*.o

# Assembly
.s:
	${LINK.s} -o ${.TARGET} ${.IMPSRC} ${LDLIBS}
.s.o:
	${COMPILE.s} ${.IMPSRC}
.s.a:
	${COMPILE.s} ${.IMPSRC}
	${AR} ${ARFLAGS} $@ $*.o
	rm -f $*.o
.S:
	${LINK.S} -o ${.TARGET} ${.IMPSRC} ${LDLIBS}
.S.o:
	${COMPILE.S} ${.IMPSRC}
.S.a:
	${COMPILE.S} ${.IMPSRC}
	${AR} ${ARFLAGS} $@ $*.o
	rm -f $*.o

# Lex
.l:
	${LEX.l} ${.IMPSRC}
	${LINK.c} -o ${.TARGET} lex.yy.c ${LDLIBS} -ll
	rm -f lex.yy.c
.l.c:
	${LEX.l} ${.IMPSRC}
	mv lex.yy.c ${.TARGET}
.l.o:
	${LEX.l} ${.IMPSRC}
	${COMPILE.c} -o ${.TARGET} lex.yy.c 
	rm -f lex.yy.c

# Yacc
.y:
	${YACC.y} ${.IMPSRC}
	${LINK.c} -o ${.TARGET} y.tab.c ${LDLIBS}
	rm -f y.tab.c
.y.c:
	${YACC.y} ${.IMPSRC}
	mv y.tab.c ${.TARGET}
.y.o:
	${YACC.y} ${.IMPSRC}
	${COMPILE.c} -o ${.TARGET} y.tab.c
	rm -f y.tab.c

# Shell
.sh:
	rm -f ${.TARGET}
	cp ${.IMPSRC} ${.TARGET}
