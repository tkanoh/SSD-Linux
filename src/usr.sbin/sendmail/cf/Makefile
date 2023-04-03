#	$ssdlinux: Makefile,v 1.4 2002/06/24 04:12:16 yamagata Exp $

.include <bsd.own.mk>

SCRIPTSDIR=	${DESTDIR}/usr/share/sendmail

DIST=		${.CURDIR}/../../../dist/sendmail

.MAIN: all

all:

install:
	if [ ! -d ${SCRIPTSDIR} ] ; then \
		mkdir -p ${SCRIPTSDIR};\
	fi
	(cd ${DIST} && tar cf - cf devtools ) | (cd ${SCRIPTSDIR} && tar xf - )
	tar cf - cf | (cd ${SCRIPTSDIR} && tar xf - )

clean:

cleandir:
