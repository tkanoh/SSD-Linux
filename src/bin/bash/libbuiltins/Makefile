#	$ssdlinux: Makefile,v 1.7 2004/08/29 05:27:07 yamagata Exp $

.include <bsd.own.mk>

LIB=		builtins

DIST=		${.CURDIR}/../../../dist/bash
BDIST=		${DIST}/${LIB}

DEFSRCS=	${BDIST}/alias.def ${BDIST}/bind.def ${BDIST}/break.def \
		${BDIST}/builtin.def ${BDIST}/caller.def \
		${BDIST}/cd.def ${BDIST}/colon.def \
		${BDIST}/command.def ${BDIST}/declare.def ${BDIST}/echo.def \
		${BDIST}/enable.def ${BDIST}/eval.def ${BDIST}/getopts.def \
		${BDIST}/exec.def ${BDIST}/exit.def ${BDIST}/fc.def \
		${BDIST}/fg_bg.def ${BDIST}/hash.def ${BDIST}/help.def \
		${BDIST}/history.def ${BDIST}/jobs.def ${BDIST}/kill.def \
		${BDIST}/let.def ${BDIST}/read.def ${BDIST}/return.def \
		${BDIST}/set.def ${BDIST}/setattr.def ${BDIST}/shift.def \
		${BDIST}/source.def ${BDIST}/suspend.def ${BDIST}/test.def \
		${BDIST}/times.def ${BDIST}/trap.def ${BDIST}/type.def \
		${BDIST}/ulimit.def ${BDIST}/umask.def ${BDIST}/wait.def \
		${BDIST}/pushd.def ${BDIST}/shopt.def \
		${BDIST}/printf.def ${BDIST}/complete.def

RESERVEDDEF=	${BDIST}/reserved.def

_DEFSRCS_C=	${DEFSRCS:M*.def:.def=.c}
DEFSRCS_C=	${_DEFSRCS_C:T}

SRCS=		builtins.c ${DEFSRCS_C} \
		common.c evalfile.c evalstring.c getopt.c bashgetopt.c \
		mkbuiltins.c pipesize.h
 
CLEANFILES=	mkbuiltins mkbuiltins.o builtins.c builtext.h ${DEFSRCS_C} \
		psize.aux pipesize.h

CPPFLAGS+=	-I${BDIST}

.PATH:		${BDIST}

mkbuiltins:
	${HOST_CC} ${CPPFLAGS} -c ${BDIST}/mkbuiltins.c
	${HOST_CC} -rdynamic ${CFLAGS} -o ${.TARGET} ${.TARGET}.o -ldl
	
builtins.c : mkbuiltins
	./mkbuiltins -externfile builtext.h -structfile ${.TARGET} -noproduction \
		-D . ${DEFSRCS} ${RESERVEDDEF}

pipesize.h: psize.aux
	${SHELL} ${BDIST}/psize.sh > ${.TARGET}

psize.aux:
	${CC} ${CPPFLAGS} -o ${.TARGET} ${BDIST}/psize.c

${DEFSRCS_C}: mkbuiltins
	./mkbuiltins -D . ${BDIST}/${.TARGET:M*.c:.c=.def}

libinstall::

.include <bsd.lib.mk>
