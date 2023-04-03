#	$ssdlinux: Makefile,v 1.2 2003/03/13 08:37:16 yamagata Exp $

.include <bsd.own.mk>

.MAIN: all
all: mtree.conf

mtree.conf: mtree.conf.in
	sed -e 's|@KERNEL_VERSION@|${KERNEL_VERSION}|g' \
	    -e 's|@GCC_VERSION@|${GCC_VERSION}|g' \
	    -e 's|@ARCH@|powerpc|g' \
	    -e '/^#/d' \
	    ${.TARGET}.in > ${.TARGET}

mtree.conf.in: mtree.conf.in.in
	if [ "${MTA}" = "postfix" ]; then \
		sed -e '/\.\/usr\/libexec\/ppp/i\
./usr/libexec/postfix' ${.TARGET}.in > ${.TARGET}; \
	else \
		cp ${.TARGET}.in ${.TARGET}; \
	fi

clean:
	rm -f mtree.conf mtree.conf.in
