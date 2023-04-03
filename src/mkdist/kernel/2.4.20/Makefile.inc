#	$ssdlinux: Makefile.inc,v 1.8 2004/12/21 05:53:53 todoroki Exp $

# linux-ppc-2.4.20 kernel from BitKeeper 2.4 Development ChangeSet@1.1176
# on http://www.ppckernel.org/

__DISTRELEASE=    	49

LOCAL_PATCHFILESDIR=	${KERNEL_DIFF_PATH}

# ext3 for 2.4 (http://www.zip.com.au/~akpm/linux/ext3/)
LOCAL_PATCHFILES=	sync_fs.diff
LOCAL_PATCHFILES+=	sync_fs-fix.diff
LOCAL_PATCHFILES+=	sync_fs-fix-2.diff
LOCAL_PATCHFILES+=	ext3-use-after-free.diff
LOCAL_PATCHFILES+=	ext3-scheduling-storm.diff
# CAN Patches
LOCAL_PATCHFILES+=	CAN-2003-0127.diff
LOCAL_PATCHFILES+=	CAN-2003-0961.diff
LOCAL_PATCHFILES+=	CAN-2003-0984.diff
LOCAL_PATCHFILES+=	CAN-2003-0985.diff
LOCAL_PATCHFILES+=	CAN-2004-0077.diff
LOCAL_PATCHFILES+=	CAN-2004-0003.diff
LOCAL_PATCHFILES+=	CAN-2004-0010.diff
LOCAL_PATCHFILES+=	CAN-2004-0109.diff
LOCAL_PATCHFILES+=	CAN-2004-0177.diff
LOCAL_PATCHFILES+=	CAN-2004-0178.diff
LOCAL_PATCHFILES+=	CAN-2004-0554.diff
# linux 2.4.20 and gcc 3.3 or newer.
.if ${GCC_VERSION} != "3.2.3"
LOCAL_PATCHFILES+=	linux-ppc-gcc-3.3.3.diff
.endif

# OpenBlockS patches
LOCAL_PATCHFILES+=	linux-ppc-obs.diff
LOCAL_PATCHFILES+=	obs200_HZ.diff
_DISTRELEASE=	${__DISTRELEASE}

# for IPv6
.if ${IPV6} == "yes"
USAGI_RELEASE=		stable_20030214
PATCH_OPTIONS= -F3
USAGI_PATCHFILES=	usagi-linux24-${USAGI_RELEASE}-${KERNEL_VERSION}.diff.bz2
.endif
