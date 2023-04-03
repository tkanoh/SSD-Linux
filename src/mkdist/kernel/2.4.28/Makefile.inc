#	$ssdlinux: Makefile.inc,v 1.7 2005/01/31 04:53:09 todoroki Exp $

# linux-ppc-2.4.28 kernel from kernel.org 11/17/04
# on http://www.kernel.org/pub/linux/kernel/v2.4/

_DISTRELEASE=		6

LOCAL_PATCHFILESDIR=	${KERNEL_DIFF_PATH}

# Prism54 driver is build into source tree.

LOCAL_PATCHFILES=	linux-ppc-obs.diff
LOCAL_PATCHFILES+=	obs200_HZ.diff

# for IPv6
.if ${IPV6} == "yes"
# usagi-linux24-stable_20040104-2.4.26.tar.bz2 and
# usagi-linux24-stable_20040104-2.4.27.tar.bz2 and
# usagi-linux24-stable_20040104-2.4.28.tar.bz2 was made from
# usagi-linux24-stable_20040104-2.4.21.tar.bz2.
PATCH_OPTIONS= -F3
USAGI_RELEASE=		stable_20040104
USAGI_PATCHFILES=	usagi-linux24-${USAGI_RELEASE}-${KERNEL_VERSION}.diff.bz2
.endif
