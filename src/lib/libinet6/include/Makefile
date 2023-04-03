#	$ssdlinux: Makefile,v 1.7 2003/05/02 07:09:50 kanoh Exp $
.include <bsd.own.mk>

DIST=	${.CURDIR}/../../../dist/usagi-tool/usagi/libinet6

.MAIN: all

all:
	rm -rf ${.CURDIR}/bits ${.CURDIR}/net ${.CURDIR}/netinet
.if ${GLIBC_MAJOR_VERSION} ==  "2.3"
	cp ${DIST}/include_glibc23/netdb.h ${.CURDIR}/netdb.h
	cp -r ${DIST}/include_glibc23/bits ${.CURDIR}
	cp -r ${DIST}/include_glibc23/netinet ${.CURDIR}
.else
	cp ${DIST}/include_glibc22/ifaddrs.h ${.CURDIR}/ifaddrs.h
	cp ${DIST}/include_glibc22/netdb.h ${.CURDIR}/netdb.h
	cp -r ${DIST}/include_glibc22/bits ${.CURDIR}
	cp -r ${DIST}/include_glibc22/net ${.CURDIR}
	cp -r ${DIST}/include_glibc22/netinet ${.CURDIR}
.endif
	cp ${DIST}/include_glibc/bits/in.h ${.CURDIR}/bits
	cp ${DIST}/include_glibc/bits/sockaddr.h ${.CURDIR}/bits
	cp ${DIST}/include_glibc/netinet/icmp6.h ${.CURDIR}/netinet
	cp ${DIST}/include_glibc/netinet/ip6.h ${.CURDIR}/netinet

install:
.if ${GLIBC_MAJOR_VERSION} !=  "2.3"
	${INSTALL} -c -m 444 ifaddrs.h ${DESTDIR}/usr/include/ifaddrs.h
	${INSTALL} -c -m 444 net/if.h ${DESTDIR}/usr/include/net/if.h
.endif
	${INSTALL} -c -m 444 netdb.h ${DESTDIR}/usr/include/netdb.h
	${INSTALL} -c -m 444 bits/in.h ${DESTDIR}/usr/include/bits/in.h
	${INSTALL} -c -m 444 bits/sockaddr.h ${DESTDIR}/usr/include/bits/sockaddr.h
	${INSTALL} -c -m 444 bits/socket.h ${DESTDIR}/usr/include/bits/socket.h
	${INSTALL} -c -m 444 netinet/icmp6.h ${DESTDIR}/usr/include/netinet/icmp6.h
	${INSTALL} -c -m 444 netinet/in.h ${DESTDIR}/usr/include/netinet/in.h
	${INSTALL} -c -m 444 netinet/ip6.h ${DESTDIR}/usr/include/netinet/ip6.h

clean:
	rm -f ifaddrs.h netdb.h
	rm -rf ${.CURDIR}/bits ${.CURDIR}/net ${.CURDIR}/netinet

cleandir:
