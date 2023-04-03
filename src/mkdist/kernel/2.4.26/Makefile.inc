#	$ssdlinux: Makefile.inc,v 1.13 2005/01/31 04:53:08 todoroki Exp $

# linux-ppc-2.4.26 kernel from BitKeeper 2.4 Stable Updated 5/26/04
# on http://www.ppckernel.org/

_DISTRELEASE=		31

LOCAL_PATCHFILESDIR=	${KERNEL_DIFF_PATH}

PATCH_SITES=		http://prism54.org/pub/linux/testing/kernel/v2.4/2004-06
PATCHFILES=		patch-${KERNEL_VERSION}-prism54-1.2.bz2
LOCAL_PATCHFILES=	linux-ppc-obs.diff
LOCAL_PATCHFILES+=	obs200_HZ.diff

# for IPv6
.if ${IPV6} == "yes"
# usagi-linux24-stable_20040104-2.4.26.tar.bz2 and
# usagi-linux24-stable_20040104-2.4.27.tar.bz2 was made from
# usagi-linux24-stable_20040104-2.4.21.tar.bz2.
USAGI_RELEASE=		stable_20040104
PATCH_OPTIONS= -F3
USAGI_PATCHFILES=	usagi-linux24-${USAGI_RELEASE}-${KERNEL_VERSION}.diff.bz2
LOCAL_PATCHFILES+=	usagi-linux24.crypto.diff
.endif
