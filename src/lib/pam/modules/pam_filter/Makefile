#	$ssdlinux: Makefile,v 1.6 2004/07/02 13:42:25 yamagata Exp $

.include <bsd.own.mk>

MODULE=		pam_filter

.include "${.CURDIR}/../Makefile.cflags"

.if defined(CROSS_BUILD) || defined(NEW_GLIBC)
CLEANFILES+=	${.CURDIR}/../../include/security/${MODULE}.h
${MODULE}.c: ${MODULE}.h
${MODULE}.h:
	rm -f ${.CURDIR}/../../include/security/${.TARGET}
	cp ${MSRCDIR}/${MODULE}/include/${.TARGET} ${.CURDIR}/../../include/security/${.TARGET}
.endif

.include <bsd.prog.mk>
