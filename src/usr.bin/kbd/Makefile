#	$ssdlinux: Makefile,v 1.3 2003/08/29 02:14:12 todoroki Exp $
#	$ID$

.include <bsd.own.mk>

.ifmake clean
SUBDIR=  chvt deallocvt dumpkeys fgconsole kbd_mode kbdrate
SUBDIR+= psfxtable setfont setleds setmetamode showconsolefont showkey
SUBDIR+= resizecons getkeycodes setkeycodes unicode_start unicode_stop
.else

SUBDIR=  chvt deallocvt dumpkeys fgconsole kbd_mode kbdrate
SUBDIR+= psfxtable setfont setleds setmetamode showconsolefont showkey
.if ${MACHINE_ARCH} == "i386"
SUBDIR+= resizecons
.endif
.if ${MACHINE_ARCH} == "mac68k" || \
    ${MACHINE_ARCH} == "macppc" || \
    ${MACHINE_ARCH} == "sparc" || \
    ${MACHINE_ARCH} == "sparc64"
SUBDIR+= getkeycodes setkeycodes
.endif
SUBDIR+= unicode_start unicode_stop

.endif

.include <bsd.subdir.mk>
