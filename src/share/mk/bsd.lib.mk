#	$ssdlinux: bsd.lib.mk,v 1.4 2002/12/12 15:30:36 kanoh Exp $

.if !target(__initialized__)
__initialized__:
.if exists(${.CURDIR}/../Makefile.inc)
.include "${.CURDIR}/../Makefile.inc"
.endif
.include <bsd.own.mk>
.include <bsd.obj.mk>
.include <bsd.depall.mk>
.MAIN:		all
.endif

.PHONY:		checkver cleanlib libinstall incinstall
realinstall:	checkver libinstall incinstall
clean cleandir: cleanlib

.if exists(${SHLIB_VERSION_FILE})
SHLIB_MAJOR != . ${SHLIB_VERSION_FILE} ; echo $$major
SHLIB_MINOR != . ${SHLIB_VERSION_FILE} ; echo $$minor
SHLIB_TEENY != . ${SHLIB_VERSION_FILE} ; echo $$teeny

# Check for higher installed library versions.
.if !defined(NOCHECKVER) && !defined(NOCHECKVER_${LIB}) && \
	exists(${BSDSRCDIR}/lib/checkver)
checkver:
	@(cd ${.CURDIR} && \
		sh ${BSDSRCDIR}/lib/checkver -v ${SHLIB_VERSION_FILE} \
		    -d ${DESTDIR}${LIBDIR} ${LIB})
.endif
.endif

.if !target(checkver)
checkver:
.endif

print-shlib-major:
.if defined(SHLIB_MAJOR)
	@echo ${SHLIB_MAJOR}
.else
	@false
.endif

print-shlib-minor:
.if defined(SHLIB_MINOR)
	@echo ${SHLIB_MINOR}
.else
	@false
.endif

print-shlib-teeny:
.if defined(SHLIB_TEENY)
	@echo ${SHLIB_TEENY}
.else
	@false
.endif

.if defined(SHLIB_MAJOR) && !empty(SHLIB_MAJOR)
.if defined(SHLIB_MINOR) && !empty(SHLIB_MINOR)
.if defined(SHLIB_TEENY) && !empty(SHLIB_TEENY)
SHLIB_FULLVERSION=${SHLIB_MAJOR}.${SHLIB_MINOR}.${SHLIB_TEENY}
.else
SHLIB_FULLVERSION=${SHLIB_MAJOR}.${SHLIB_MINOR}
.endif
.else
SHLIB_FULLVERSION=${SHLIB_MAJOR}
.endif
.endif

# add additional suffixes not exported.
# .po is used for profiling object files.
# .so is used for PIC object files.
.SUFFIXES: .out .a .ln .so .po .o .s .S .c .cc .C .m .F .f .r .y .l .cl .p .h
.SUFFIXES: .sh .m4 .m


# Set PICFLAGS to cc flags for producing position-independent code,
# if not already set.  Includes -DPIC, if required.

# Data-driven table using make variables to control how shared libraries
# are built for different platforms and object formats.
# OBJECT_FMT:		currently either "ELF" or "a.out", from <bsd.own.mk>
# SHLIB_SOVERSION:	version number to be compiled into a shared library
#			via -soname. Usualy ${SHLIB_MAJOR} on ELF.
#			NetBSD/pmax used to use ${SHLIB_MAJOR}[.${SHLIB_MINOR}
#			[.${SHLIB_TEENY}]]
# SHLIB_SHFLAGS:	Flags to tell ${LD} to emit shared library.
#			with ELF, also set shared-lib version for ld.so.
# SHLIB_LDSTARTFILE:	support .o file, call C++ file-level constructors
# SHLIB_LDENDFILE:	support .o file, call C++ file-level destructors
# FPICFLAGS:		flags for ${FC} to compile .[fF] files to .so objects.
# CPPICFLAGS:		flags for ${CPP} to preprocess .[sS] files for ${AS}
# CPICFLAGS:		flags for ${CC} to compile .[cC] files to .so objects.
# CAPICFLAGS		flags for {$CC} to compiling .[Ss] files
#		 	(usually just ${CPPPICFLAGS} ${CPICFLAGS})
# APICFLAGS:		flags for ${AS} to assemble .[sS] to .so objects.

.if ${MACHINE_ARCH} == "alpha"
		# Alpha-specific shared library flags
FPICFLAGS ?= -fPIC
CPICFLAGS ?= -fPIC -DPIC
CPPPICFLAGS?= -DPIC 
CAPICFLAGS?= ${CPPPICFLAGS} ${CPICFLAGS}
APICFLAGS ?=
.elif ${MACHINE_ARCH} == "mipsel" || ${MACHINE_ARCH} == "mipseb"
		# mips-specific shared library flags

# On mips, all libs are compiled with ABIcalls, not just sharedlibs.
MKPICLIB= no

# so turn shlib PIC flags on for ${AS}.
AINC+=-DABICALLS
AFLAGS+= -fPIC
AS+=	-KPIC

.elif ${MACHINE_ARCH} == "vax" && ${OBJECT_FMT} == "ELF"
# On the VAX, all object are PIC by default, not just sharedlibs.
MKPICLIB= no

.elif (${MACHINE_ARCH} == "sparc" || ${MACHINE_ARCH} == "sparc64") && \
       ${OBJECT_FMT} == "ELF"

FPICFLAGS ?= -fPIC
CPICFLAGS ?= -fPIC -DPIC
CPPPICFLAGS?= -DPIC 
CAPICFLAGS?= ${CPPPICFLAGS} ${CPICFLAGS}
APICFLAGS ?= -KPIC

.else

# Platform-independent flags for NetBSD a.out shared libraries (and PowerPC)
SHLIB_LDSTARTFILE=
SHLIB_LDENDFILE=
SHLIB_SOVERSION=${SHLIB_FULLVERSION}
SHLIB_SHFLAGS=
FPICFLAGS ?= -fPIC
CPICFLAGS?= -fPIC -DPIC
CPPPICFLAGS?= -DPIC 
CAPICFLAGS?= ${CPPPICFLAGS} ${CPICFLAGS}
APICFLAGS?= -k

.endif

MKPICLIB?= yes

# Platform-independent linker flags for ELF shared libraries
.if ${OBJECT_FMT} == "ELF"
SHLIB_SOVERSION=	${SHLIB_MAJOR}
SHLIB_SHFLAGS=		-soname lib${LIB}.so.${SHLIB_SOVERSION}
SHLIB_LDSTARTFILE?=	${DESTDIR}/usr/lib/crtbeginS.o
SHLIB_LDENDFILE?=	${DESTDIR}/usr/lib/crtendS.o
.endif

CFLAGS+=	${COPTS}
FFLAGS+=	${FOPTS}

.c.o:
.if defined(COPTS) && !empty(COPTS:M*-g*)
	${COMPILE.c} ${.IMPSRC}
.else
	@echo ${COMPILE.c:Q} ${.IMPSRC}
	@${COMPILE.c} ${.IMPSRC} -o ${.TARGET}.o
	@${LD} -x -r ${.TARGET}.o -o ${.TARGET}
	@rm -f ${.TARGET}.o
.endif

.c.po:
.if defined(COPTS) && !empty(COPTS:M*-g*)
	${COMPILE.c} -pg ${.IMPSRC} -o ${.TARGET}
.else
	@echo ${COMPILE.c:Q} -pg ${.IMPSRC} -o ${.TARGET}
	@${COMPILE.c} -pg ${.IMPSRC} -o ${.TARGET}.o
	@${LD} -X -r ${.TARGET}.o -o ${.TARGET}
	@rm -f ${.TARGET}.o
.endif

.c.so:
.if defined(COPTS) && !empty(COPTS:M*-g*)
	${COMPILE.c} ${CPICFLAGS} ${.IMPSRC} -o ${.TARGET}
.else
	@echo ${COMPILE.c:Q} ${CPICFLAGS} ${.IMPSRC} -o ${.TARGET}
	@${COMPILE.c} ${CPICFLAGS} ${.IMPSRC} -o ${.TARGET}.o
	@${LD} -x -r ${.TARGET}.o -o ${.TARGET}
	@rm -f ${.TARGET}.o
.endif

.c.ln:
	${LINT} ${LINTFLAGS} ${CPPFLAGS:M-[IDU]*} -i ${.IMPSRC}

.cc.o .C.o:
.if defined(COPTS) && !empty(COPTS:M*-g*)
	${COMPILE.cc} ${.IMPSRC}
.else
	@echo ${COMPILE.cc:Q} ${.IMPSRC}
	@${COMPILE.cc} ${.IMPSRC} -o ${.TARGET}.o
	@${LD} -x -r ${.TARGET}.o -o ${.TARGET}
	@rm -f ${.TARGET}.o
.endif

.cc.po .C.po:
.if defined(COPTS) && !empty(COPTS:M*-g*)
	${COMPILE.cc} -pg ${.IMPSRC} -o ${.TARGET}
.else
	@echo ${COMPILE.cc:Q} -pg ${.IMPSRC} -o ${.TARGET}
	@${COMPILE.cc} -pg ${.IMPSRC} -o ${.TARGET}.o
	@${LD} -X -r ${.TARGET}.o -o ${.TARGET}
	@rm -f ${.TARGET}.o
.endif

.cc.so .C.so:
.if defined(COPTS) && !empty(COPTS:M*-g*)
	${COMPILE.cc} ${CPICFLAGS} ${.IMPSRC} -o ${.TARGET}
.else
	@echo ${COMPILE.cc:Q} ${CPICFLAGS} ${.IMPSRC} -o ${.TARGET}
	@${COMPILE.cc} ${CPICFLAGS} ${.IMPSRC} -o ${.TARGET}.o
	@${LD} -x -r ${.TARGET}.o -o ${.TARGET}
	@rm -f ${.TARGET}.o
.endif

.f.o:
.if defined(FOPTS) && !empty(FOPTS:M*-g*)
	${COMPILE.f} ${.IMPSRC}
.else
	@echo ${COMPILE.f:Q} ${.IMPSRC}
	@${COMPILE.f} ${.IMPSRC} -o ${.TARGET}.o
	@${LD} -x -r ${.TARGET}.o -o ${.TARGET}
	@rm -f ${.TARGET}.o
.endif

.f.po:
.if defined(FOPTS) && !empty(FOPTS:M*-g*)
	${COMPILE.f} -pg ${.IMPSRC} -o ${.TARGET}
.else
	@echo ${COMPILE.f:Q} -pg ${.IMPSRC} -o ${.TARGET}
	@${COMPILE.f} -pg ${.IMPSRC} -o ${.TARGET}.o
	@${LD} -X -r ${.TARGET}.o -o ${.TARGET}
	@rm -f ${.TARGET}.o
.endif

.f.so:
.if defined(FOPTS) && !empty(FOPTS:M*-g*)
	${COMPILE.f} ${FPICFLAGS} ${.IMPSRC} -o ${.TARGET}
.else
	@echo ${COMPILE.f:Q} ${FPICFLAGS} ${.IMPSRC} -o ${.TARGET}
	@${COMPILE.f} ${FPICFLAGS} ${.IMPSRC} -o ${.TARGET}.o
	@${LD} -x -r ${.TARGET}.o -o ${.TARGET}
	@rm -f ${.TARGET}.o
.endif

.f.ln:
	${ECHO} Skipping lint for Fortran libraries.

.m.o:
.if defined(OBJCFLAGS) && !empty(OBJCFLAGS:M*-g*)
	${COMPILE.m} ${.IMPSRC}
.else
	@echo ${COMPILE.m:Q} ${.IMPSRC}
	@${COMPILE.m} ${.IMPSRC} -o ${.TARGET}.o
	@${LD} -x -r ${.TARGET}.o -o ${.TARGET}
	@rm -f ${.TARGET}.o
.endif

.m.po:
.if defined(OBJCFLAGS) && !empty(OBJCFLAGS:M*-g*)
	${COMPILE.m} -pg ${.IMPSRC} -o ${.TARGET}
.else
	@echo ${COMPILE.m:Q} -pg ${.IMPSRC} -o ${.TARGET}
	@${COMPILE.m} -pg ${.IMPSRC} -o ${.TARGET}.o
	@${LD} -X -r ${.TARGET}.o -o ${.TARGET}
	@rm -f ${.TARGET}.o
.endif

.m.so:
.if defined(OBJCFLAGS) && !empty(OBJCFLAGS:M*-g*)
	${COMPILE.m} ${CPICFLAGS} ${.IMPSRC} -o ${.TARGET}
.else
	@echo ${COMPILE.m:Q} ${CPICFLAGS} ${.IMPSRC} -o ${.TARGET}
	@${COMPILE.m} ${CPICFLAGS} ${.IMPSRC} -o ${.TARGET}.o
	@${LD} -x -r ${.TARGET}.o -o ${.TARGET}
	@rm -f ${.TARGET}.o
.endif

.S.o .s.o:
	@echo ${COMPILE.S:Q} ${CFLAGS:M-[ID]*} ${AINC} ${.IMPSRC}
	@${COMPILE.S} ${CFLAGS:M-[ID]*} ${AINC} ${.IMPSRC} -o ${.TARGET}.o
	@${LD} -x -r ${.TARGET}.o -o ${.TARGET}
	@rm -f ${.TARGET}.o

.S.po .s.po:
	@echo ${COMPILE.S:Q} -DGPROF -DPROF ${CFLAGS:M-[ID]*} ${AINC} ${.IMPSRC} -o ${.TARGET}
	@${COMPILE.S} -DGPROF -DPROF ${CFLAGS:M-[ID]*} ${AINC} ${.IMPSRC} -o ${.TARGET}.o
	@${LD} -X -r ${.TARGET}.o -o ${.TARGET}
	@rm -f ${.TARGET}.o

.S.so .s.so:
	@echo ${COMPILE.S:Q} ${CAPICFLAGS} ${CFLAGS:M-[ID]*} ${AINC} ${.IMPSRC} -o ${.TARGET}
	@${COMPILE.S} ${CAPICFLAGS} ${CFLAGS:M-[ID]*} ${AINC} ${.IMPSRC} -o ${.TARGET}.o
	@${LD} -x -r ${.TARGET}.o -o ${.TARGET}
	@rm -f ${.TARGET}.o

.if ${MKPIC} == "no" || (defined(LDSTATIC) && ${LDSTATIC} != "") \
	|| ${MKLINKLIB} != "no"
_LIBS=lib${LIB}.a
.else
_LIBS=
.endif

OBJS+=${SRCS:N*.h:N*.sh:R:S/$/.o/g}

.if ${MKPROFILE} != "no"
_LIBS+=lib${LIB}_p.a
POBJS+=${OBJS:.o=.po}
.endif

.if ${MKPIC} != "no"
.if ${MKPICLIB} == "no"
SOLIB=lib${LIB}.a
.else
SOLIB=lib${LIB}_pic.a
_LIBS+=${SOLIB}
SOBJS+=${OBJS:.o=.so}
.endif
.if defined(SHLIB_FULLVERSION)
_LIBS+=lib${LIB}.so.${SHLIB_FULLVERSION}
.endif
.endif

LOBJS+=${LSRCS:.c=.ln} ${SRCS:M*.c:.c=.ln}
.if ${MKLINT} != "no" && ${MKLINKLIB} != "no" && !empty(LOBJS)
_LIBS+=llib-l${LIB}.ln
.endif

.if ${MKPIC} == "no" || (defined(LDSTATIC) && ${LDSTATIC} != "") \
	|| ${MKLINKLIB} != "no"
ALLOBJS=${OBJS} ${POBJS} ${SOBJS}
.else
ALLOBJS=${POBJS} ${SOBJS} 
.endif
.if ${MKLINT} != "no" && ${MKLINKLIB} != "no" && !empty(LOBJS)
ALLOBJS+=${LOBJS}
.endif
.NOPATH: ${ALLOBJS} ${_LIBS}

realall: ${SRCS} ${ALLOBJS:O} ${_LIBS}

#__archivebuild: .USE
#	@rm -f ${.TARGET}
#	@${AR} cq ${.TARGET} `NM=${NM} ${LORDER} ${.ALLSRC:M*o} | ${TSORT}`
#	${RANLIB} ${.TARGET}

__archivebuild: .USE
	@rm -f ${.TARGET}
	@${AR} cq ${.TARGET} ${.ALLSRC:M*o}
	${RANLIB} ${.TARGET}

__archiveinstall: .USE
	${INSTALL} ${RENAME} ${PRESERVE} ${COPY} ${INSTPRIV} -o ${LIBOWN} \
	    -g ${LIBGRP} -m 600 ${.ALLSRC} ${.TARGET}
	${RANLIB} -t ${.TARGET}
	chmod ${LIBMODE} ${.TARGET}

DPSRCS+=	${SRCS:M*.l:.l=.c} ${SRCS:M*.y:.y=.c}
CLEANFILES+=	${DPSRCS}
.if defined(YHEADER)
CLEANFILES+=	${SRCS:M*.y:.y=.h}
.endif

lib${LIB}.a:: ${OBJS} __archivebuild
	@echo building standard ${LIB} library

lib${LIB}_p.a:: ${POBJS} __archivebuild
	@echo building profiled ${LIB} library

lib${LIB}_pic.a:: ${SOBJS} __archivebuild
	@echo building shared object ${LIB} library

lib${LIB}.so.${SHLIB_FULLVERSION}: ${SOLIB} ${DPADD} \
    ${SHLIB_LDSTARTFILE} ${SHLIB_LDENDFILE}
	@echo building shared ${LIB} library \(version ${SHLIB_FULLVERSION}\)
	@rm -f lib${LIB}.so.${SHLIB_FULLVERSION}
.if defined(DESTDIR) && defined(NOT_USE)
	$(LD) -nostdlib -x -shared ${SHLIB_SHFLAGS} -o ${.TARGET} \
	    ${SHLIB_LDSTARTFILE} \
	    --whole-archive ${SOLIB} \
	    --no-whole-archive ${LDADD} \
	    -L${DESTDIR}${LIBDIR} -R${LIBDIR} \
	    ${SHLIB_LDENDFILE}
.else
	$(LD) -x -shared ${SHLIB_SHFLAGS} -o ${.TARGET} \
	    ${SHLIB_LDSTARTFILE} \
	    --whole-archive ${SOLIB} --no-whole-archive ${LDADD} \
	    ${SHLIB_LDENDFILE}
.endif
.if ${OBJECT_FMT} == "ELF"
	ln -sf lib${LIB}.so.${SHLIB_FULLVERSION} lib${LIB}.so.${SHLIB_MAJOR}.tmp
	mv -f lib${LIB}.so.${SHLIB_MAJOR}.tmp lib${LIB}.so.${SHLIB_MAJOR}
	ln -sf lib${LIB}.so.${SHLIB_FULLVERSION} lib${LIB}.so.tmp
	mv -f lib${LIB}.so.tmp lib${LIB}.so
.endif

.if !empty(LOBJS)
LLIBS?=		-lc
llib-l${LIB}.ln: ${LOBJS}
	@echo building llib-l${LIB}.ln
	@rm -f llib-l${LIB}.ln
	@${LINT} -C${LIB} ${.ALLSRC} ${LLIBS}
.endif

cleanlib:
	rm -f a.out [Ee]rrs mklog core *.core ${CLEANFILES}
	rm -f lib${LIB}.a ${OBJS}
	rm -f lib${LIB}_p.a ${POBJS}
	rm -f lib${LIB}_pic.a lib${LIB}.so.* lib${LIB}.so ${SOBJS}
	rm -f llib-l${LIB}.ln ${LOBJS}

.if defined(SRCS)
afterdepend: .depend
	@(TMP=/tmp/_depend$$$$; \
	    sed -e 's/^\([^\.]*\).o[ ]*:/\1.o \1.po \1.so \1.ln:/' \
	      < .depend > $$TMP; \
	    mv $$TMP .depend)
.endif

.if !target(libinstall)
# Make sure it gets defined, in case MKPIC==no && MKLINKLIB==no
libinstall::

.if ${MKLINKLIB} != "no"
libinstall:: ${DESTDIR}${LIBDIR}/lib${LIB}.a
.PRECIOUS: ${DESTDIR}${LIBDIR}/lib${LIB}.a
.if !defined(UPDATE)
.PHONY: ${DESTDIR}${LIBDIR}/lib${LIB}.a
.endif

.if !defined(BUILD) && !make(all) && !make(lib${LIB}.a)
${DESTDIR}${LIBDIR}/lib${LIB}.a: .MADE
.endif
${DESTDIR}${LIBDIR}/lib${LIB}.a: lib${LIB}.a __archiveinstall
.endif

.if ${MKPROFILE} != "no"
libinstall:: ${DESTDIR}${LIBDIR}/lib${LIB}_p.a
.PRECIOUS: ${DESTDIR}${LIBDIR}/lib${LIB}_p.a
.if !defined(UPDATE)
.PHONY: ${DESTDIR}${LIBDIR}/lib${LIB}_p.a
.endif

.if !defined(BUILD) && !make(all) && !make(lib${LIB}_p.a)
${DESTDIR}${LIBDIR}/lib${LIB}_p.a: .MADE
.endif
${DESTDIR}${LIBDIR}/lib${LIB}_p.a: lib${LIB}_p.a __archiveinstall
.endif

.if ${MKPIC} != "no" && ${MKPICINSTALL} != "no"
libinstall:: ${DESTDIR}${LIBDIR}/lib${LIB}_pic.a
.PRECIOUS: ${DESTDIR}${LIBDIR}/lib${LIB}_pic.a
.if !defined(UPDATE)
.PHONY: ${DESTDIR}${LIBDIR}/lib${LIB}_pic.a
.endif

.if !defined(BUILD) && !make(all) && !make(lib${LIB}_pic.a)
${DESTDIR}${LIBDIR}/lib${LIB}_pic.a: .MADE
.endif
.if ${MKPICLIB} == "no"
${DESTDIR}${LIBDIR}/lib${LIB}_pic.a:
	rm -f ${DESTDIR}${LIBDIR}/lib${LIB}_pic.a
	ln -s lib${LIB}.a ${DESTDIR}${LIBDIR}/lib${LIB}_pic.a
.else
${DESTDIR}${LIBDIR}/lib${LIB}_pic.a: lib${LIB}_pic.a __archiveinstall
.endif
.endif

.if ${MKPIC} != "no" && defined(SHLIB_FULLVERSION)
libinstall:: ${DESTDIR}${LIBDIR}/lib${LIB}.so.${SHLIB_FULLVERSION}
.PRECIOUS: ${DESTDIR}${LIBDIR}/lib${LIB}.so.${SHLIB_FULLVERSION}
.if !defined(UPDATE)
.PHONY: ${DESTDIR}${LIBDIR}/lib${LIB}.so.${SHLIB_FULLVERSION}
.endif

.if !defined(BUILD) && !make(all) && !make(lib${LIB}.so.${SHLIB_FULLVERSION})
${DESTDIR}${LIBDIR}/lib${LIB}.so.${SHLIB_FULLVERSION}: .MADE
.endif
${DESTDIR}${LIBDIR}/lib${LIB}.so.${SHLIB_FULLVERSION}: lib${LIB}.so.${SHLIB_FULLVERSION}
	${INSTALL} ${RENAME} ${PRESERVE} ${COPY} ${INSTPRIV} -o ${LIBOWN} \
	    -g ${LIBGRP} -m ${LIBMODE} ${.ALLSRC} ${.TARGET}
.if ${OBJECT_FMT} == "a.out" && !defined(DESTDIR)
	/sbin/ldconfig -m ${LIBDIR}
.endif
.if ${OBJECT_FMT} == "ELF"
	ln -sf lib${LIB}.so.${SHLIB_FULLVERSION}\
	    ${DESTDIR}${LIBDIR}/lib${LIB}.so.${SHLIB_MAJOR}.tmp
	mv -f ${DESTDIR}${LIBDIR}/lib${LIB}.so.${SHLIB_MAJOR}.tmp\
	    ${DESTDIR}${LIBDIR}/lib${LIB}.so.${SHLIB_MAJOR}
.if ${MKLINKLIB} != "no"
	ln -sf lib${LIB}.so.${SHLIB_FULLVERSION}\
	    ${DESTDIR}${LIBDIR}/lib${LIB}.so.tmp
	mv -f ${DESTDIR}${LIBDIR}/lib${LIB}.so.tmp\
	    ${DESTDIR}${LIBDIR}/lib${LIB}.so
.endif
.endif
.endif

.if ${MKLINT} != "no" && ${MKLINKLIB} != "no" && !empty(LOBJS)
libinstall:: ${DESTDIR}${LINTLIBDIR}/llib-l${LIB}.ln
.PRECIOUS: ${DESTDIR}${LINTLIBDIR}/llib-l${LIB}.ln
.if !defined(UPDATE)
.PHONY: ${DESTDIR}${LINTLIBDIR}/llib-l${LIB}.ln
.endif

.if !defined(BUILD) && !make(all) && !make(llib-l${LIB}.ln)
${DESTDIR}${LINTLIBDIR}/llib-l${LIB}.ln: .MADE
.endif
${DESTDIR}${LINTLIBDIR}/llib-l${LIB}.ln: llib-l${LIB}.ln
	${INSTALL} ${RENAME} ${PRESERVE} ${COPY} ${INSTPRIV} -o ${LIBOWN} \
	    -g ${LIBGRP} -m ${LIBMODE} ${.ALLSRC} ${DESTDIR}${LINTLIBDIR}
.endif
.endif

.include <bsd.man.mk>
.include <bsd.nls.mk>
.include <bsd.files.mk>
.include <bsd.inc.mk>
.include <bsd.links.mk>
.include <bsd.dep.mk>
.include <bsd.sys.mk>

# Make sure all of the standard targets are defined, even if they do nothing.
lint regress:
