#	$ssdlinux: Makefile,v 1.14 2004/07/05 01:51:55 todoroki Exp $
.include <bsd.own.mk>

.include "../Makefile.cflags"

.MAIN: all

all:
	for d in asm linux net pcmcia static; do \
		if [ ! -d ${.CURDIR}/$$d ]; then \
			mkdir ${.CURDIR}/$$d; \
		fi \
	done
	UTS_VERSION=`uname -v`; \
	VERSION_CODE=`expr $(KERNEL_MAJOR) \* 65536 + $(KERNEL_MINOR) \* 256 + $(KERNEL_PATCHLEVEL)`; \
	sed -e 's!@KERNSRC@!$(KERNSRC)!' \
	    -e 's!@KERNEL_VERSION@!$(KERNEL_VERSION)!' \
	    -e 's!@UTS_VERSION@!'"$$UTS_VERSION"'!' \
	    -e 's!@VERSION_CODE@!'"$$VERSION_CODE"'!' \
	    -e 's!@BINDIR@!$(BINDIR)!' \
	    -e 's!@MANDIR@!$(MANDIR)/!' \
	    -e 's!@MACHINE_ARCH@!$(TARGET_HOSTTYPE)!' \
	    -e 's!@HOSTTYPE@!$(TARGET_HOSTTYPE)!' \
	    ${.CURDIR}/autoconf.h.in-${KERNEL_VERSION}.${TARGET_SSDHOSTTYPEX} > ${.CURDIR}/pcmcia/autoconf.h
	for d in asm linux net pcmcia static; do \
		cp -a ${DIST}/include/$$d/* ${.CURDIR}/$$d; \
	done

clean:
	for d in asm linux net pcmcia static; do \
		rm -rf ${.CURDIR}/$$d; \
	done

cleandir:
