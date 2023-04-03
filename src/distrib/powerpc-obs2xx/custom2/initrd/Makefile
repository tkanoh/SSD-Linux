#	$ssdlinux: Makefile,v 1.2 2004/12/14 04:25:58 todoroki Exp $

.include <bsd.own.mk>
.include "../Makefile.inc"

LIST_S= common flashcfg bash modules sshd useradd httpd setup_cgi
.if (!defined(NEW_GLIBC) && !defined(CROSS_BUILD)) || defined(CROSS_BUILD_PERL)
LIST_S+= perl
.endif

.include "${.CURDIR}/../../standard/initrd/Makefile.inc"
