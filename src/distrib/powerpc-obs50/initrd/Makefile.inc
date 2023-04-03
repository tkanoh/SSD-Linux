#	$ssdlinux: Makefile.inc,v 1.4 2004/02/09 08:40:20 yamagata Exp $

LIST_S?= common ifconfig
.if ${IPV6} == "yes"
LIST_S+= ipv6
.endif
MTREE_CONF_S?= ${LIST_S}
FLASHCFG_S?= ${LIST_S}

.include "${.CURDIR}/../Makefile.inc"

DEV_LOOP=	/dev/loop0
DEV_ZERO=	/dev/zero
MOUNT_POINT=	/mnt
TMPDIR=		/tmp
MODULESDIR=	${DESTDIR}/lib/modules/${KERNEL_VERSION}
UTILSDIR=	${.CURDIR}/../../utils
COMMON_INITRDDIR=	${.CURDIR}/../initrd
COMMON_ETCDIR=	${COMMON_INITRDDIR}/etc
INITRD_FS_SIZE=	8192

MTREE_CONF=	mtree.conf
RAMDISKBINDIR=	${.CURDIR}/../ramdiskbin
LIST=		list
FLASHCFG=	flashcfg
.if defined(CROSS_BUILD)
STRIPBIN=${TARGET_MACHTYPE}-strip
.else
STRIPBIN=strip
.endif

.MAIN: all
all: prebuild ${INITRD_FS_GZ}

prebuild:
.if defined(CONTRIBS)
	for i in ${CONTRIBS}; \
	do \
		if [ ! -f ${SRCTOPDIR}/contrib/$${i}/${BUILD_VERSION_FILE} ]; then \
			(cd ${SRCTOPDIR}/contrib/$${i} && bmake); \
		fi;\
		if [ ! -d /usr/contrib/$${i} ]; then \
			(cd ${SRCTOPDIR}/contrib/$${i} && bmake install); \
		fi;\
	 done
.endif
.if defined(REQUIREMENT)
	${REQUIREMENT}
.endif

${INITRD_FS_GZ}: ${MTREE_CONF} ${LIST} ${FLASHCFG}
	dd if=${DEV_ZERO} of=${.CURDIR}/${INITRD_FS} bs=1k count=${INITRD_FS_SIZE}
	losetup ${DEV_LOOP} ${.CURDIR}/${INITRD_FS}
	mke2fs ${DEV_LOOP} ${INITRD_FS_SIZE}
	mount -t ext2 ${DEV_LOOP} ${MOUNT_POINT}
	dirs=`cat ${.CURDIR}/${MTREE_CONF}`;(cd ${MOUNT_POINT}; \
	for i in $$dirs; do \
		mkdir -p $$i; \
	done )
	CURDIR=${.CURDIR} OBJDIR=${RAMDISKBINDIR} \
		COMMON_ETCDIR=${COMMON_ETCDIR} TARGDIR=${MOUNT_POINT} \
		STRIPBIN=${STRIPBIN} TMPDIR=${TMPDIR} \
		sh ${COMMON_INITRDDIR}/runlist.sh ${.CURDIR}/${LIST}
	umount ${MOUNT_POINT}
	losetup -d ${DEV_LOOP}
	rm -f ${.CURDIR}/${INITRD_FS_GZ}
	gzip -9 ${.CURDIR}/${INITRD_FS}

clean: init
	rm -f 	${INITRD_FS_GZ} ${INITRD_FS} \
		${MTREE_CONF} ${MTREE_CONF}.tmp \
		${LIST} ${LIST}.tmp ${FLASHCFG}

init:
	-umount ${MOUNT_POINT}
	-losetup -d ${DEV_LOOP}

${MTREE_CONF} ${LIST}: ${.TARGET}.tmp 
	sed -e 's|@KERNEL_VERSION@|${KERNEL_VERSION}|' \
	    -e 's|@SRCTOPDIR@|${SRCTOPDIR}|' \
	    -e 's|@UTILSDIR@|${UTILSDIR}|' \
	    -e 's|@MODULESDIR@|${MODULESDIR}|' \
	    -e 's|@COMMON_ETCDIR@|${COMMON_ETCDIR}|' \
	    -e 's|@CURDIR@|${.CURDIR}|' \
	    -e 's|@OPENBLOCKS@|${TARGET_OPENBLOCKS}|' \
	    -e '/^#/d' ${.TARGET}.tmp > ${.TARGET}

${MTREE_CONF}.tmp:
	rm -f ${.TARGET}
	for i in ${MTREE_CONF_S}; \
	do \
		if [ -f ${COMMON_INITRDDIR}/${MTREE_CONF}_in/$${i} ]; then \
			sed -e '/^#/d' ${COMMON_INITRDDIR}/${MTREE_CONF}_in/$${i} >> ${.TARGET}; \
		fi; \
	done; \
	if [ -f ${MTREE_CONF}.in ]; then \
		sed -e '/^#/d' ${MTREE_CONF}.in >> ${.TARGET}; \
	fi

${LIST}.tmp:
	rm -f ${.TARGET}
	for i in ${LIST_S}; \
	do \
		if [ -f ${COMMON_INITRDDIR}/${LIST}_in/$${i} ]; then \
			sed -e '/^#/d' ${COMMON_INITRDDIR}/${LIST}_in/$${i} >> ${.TARGET}; \
		fi; \
	done; \
	if [ -f ${LIST}.in ]; then \
		sed -e '/^#/d' ${LIST}.in >> ${.TARGET}; \
	fi

${FLASHCFG}:
	rm -f ${.TARGET}
	for i in ${FLASHCFG_S}; \
	do \
		if [ -f ${COMMON_INITRDDIR}/${FLASHCFG}_in/$${i} ]; then \
			sed -e '/^#/d' ${COMMON_INITRDDIR}/${FLASHCFG}_in/$${i} >> ${.TARGET}; \
		fi; \
	done; \
	if [ -f ${FLASHCFG}.in ]; then \
		sed -e '/^#/d' ${FLASHCFG}.in >> ${.TARGET}; \
	fi

install:
