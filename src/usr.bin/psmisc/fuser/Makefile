#	$ssdlinux: Makefile,v 1.3 2005/03/15 01:18:26 yamagata Exp $

.include <bsd.own.mk>

PROG=		fuser
SRCS=		fuser.c signals.c
CLEANFILES=	signames.h

.include "${.CURDIR}/../Makefile.cflags"

signals.c: signames.h
signames.h: signames.c
	rm -f ${.TARGET}
	${CC} -E -dM ${.CURDIR}/../../../dist/psmisc/src/signames.c |\
	tr -s '\t ' ' ' | sort -n -k 3 | sed \
		's:#define SIG\([A-Z]\+[0-9]*\) \([0-9]\+\) *\(\|/\*.*\)$$:{ \2,"\1" },:p;d' | \
	grep -v '[0-9][0-9][0-9]' >${.TARGET}

.include <bsd.prog.mk>
