#	$ssdlinux: bsd.mkdist.mk,v 1.27 2004/11/02 17:06:06 kanoh Exp $

.if !defined(_BSD_MKDIST_MK_)
_BSD_MKDIST_MK_=1

.if defined(MAKECONF) && exists(${MAKECONF})
.include "${MAKECONF}"
.elif exists(/etc/mk.conf)
.include "/etc/mk.conf"
.endif

.if defined(CROSS_BUILD) && !defined(CROSS_LIB)
.if defined(MAKECONF) && exists(${MAKECONF}.${CROSS_BUILD})
.include "${MAKECONF}.${CROSS_BUILD}"
.elif exists(/etc/mk.conf.${CROSS_BUILD})
.include "/etc/mk.conf.${CROSS_BUILD}"
.endif
.else
.if defined(MAKECONF) && exists(${MAKECONF}.${HOSTTYPE})
.include "${MAKECONF}.${HOSTTYPE}"
.elif exists(/etc/mk.conf.${HOSTTYPE})
.include "/etc/mk.conf.${HOSTTYPE}"
.endif
.endif

FETCH_CMD?=	/usr/bin/ftp
DISTDIR?=	/usr/src/dist
DISTFILESDIR?=	/usr/src/dist/distfiles
RELEASEDISTDIR?=${RELEASEDIR}/distfiles
VERSIONS_FILE?= ${DISTDIR}/${VERSIONS_FILE_NAME}
VERSIONS_FILE_TMP= ${VERSIONS_FILE}.tmp
MD5_FILE?=	md5
EXTRACT_SUFX?=	tar.gz
DISTRELEASE?=	0

.if !defined(DIST_PATH)
DIST_PATH?=	${DISTFILESDIR}:/cdrom/distfiles
.else
DIST_PATH=	${DISTFILESDIR}:/cdrom/distfiles:${DIST_PATH}
.endif

_DISTNAME=		${DISTNAME:S/-$//:S/_$//:S/.$//}
.if defined(ALTDISTNAME)
__DISTNAME=		${ALTDISTNAME}
.else
__DISTNAME=		${_DISTNAME}
.endif

MASTER_SITE_BACKUP?=	ftp://openlab.plathome.co.jp/pub/ssdlinux/distfiles

#MASTER_SITE_KERN?=	ftp://ftp.kernel.org/pub/linux
MASTER_SITE_KERN?=	ftp://openlab.plathome.co.jp/pub/linux/kernel.org
MASTER_SITE_OBSS?=	ftp://openlab.plathome.co.jp/pub/OpenBlockSS
#MASTER_SITE_GNU?=	ftp://ftp.gnu.org/pub/gnu
MASTER_SITE_GNU?=	ftp://ftp.iij.ad.jp/pub/GNU
MASTER_SITE_NONGNU?=	ftp://ftp.gnu.org/pub/non-gnu
MASTER_SITE_NETKIT?=	ftp://ftp.uk.linux.org/pub/linux/Networking/netkit
MASTER_SITE_LFS?=	ftp://ftp.linuxfromscratch.org/lfs-packages/3.0
USAGI_RELEASE?=		stable
MASTER_SITE_USAGI?=	ftp://ftp.linux-ipv6.org/pub/usagi/${USAGI_RELEASE}/split

.if ${DISTNAME} == "linux-"
MASTER_SITES?=		${MASTER_SITE_BACKUP}
#MASTER_SITES?=		${MASTER_SITE_KERN}/kernel/v${KERNEL_MAJOR}.${KERNEL_MINOR}
.endif
.if defined(KERN_DISTDIR)
MASTER_SITES?=		${MASTER_SITE_KERN}${KERN_DISTDIR}
.endif
.if defined(GNU_DIST)
MASTER_SITES?=		${MASTER_SITE_GNU}/${_DISTNAME}
.endif
.if defined(GNU_DISTDIR)
MASTER_SITES?=		${MASTER_SITE_GNU}${GNU_DISTDIR}
.endif
.if defined(NONGNU_DIST)
MASTER_SITES?=		${MASTER_SITE_NONGNU}/${_DISTNAME}
.endif
.if defined(NETKIT_DIST)
MASTER_SITES?=		${MASTER_SITE_NETKIT}
.endif
.if defined(USAGI_DIST)
MASTER_SITES?=		${MASTER_SITE_USAGI}
EXTRACT_SUFX=		tar.bz2
.endif
.if defined(LFS_PATCH_DIST) || defined(LFS_PATCH_NAME)
PATCH_SITES?=		${MASTER_SITE_LFS}
.if defined(LFS_PATCH_NAME)
PATCHFILES+=		${LFS_PATCH_NAME}.patch.bz2
.else
PATCHFILES+=		${DISTNAME}${DISTVERSION}.patch.bz2
.endif # defined(LFS_PATCH_NAME)
.endif # defined(LFS_PATCH_DIST)
.if defined(USAGI_PATCHFILES)
PATCH_SITES?=		${MASTER_SITE_USAGI}
PATCHFILES+=		${USAGI_PATCHFILES}
.endif # defined(USAGI_PATCH_FILES)

.if !defined(MASTER_SITE_OVERRIDE)
MASTER_SITES+=  	${MASTER_SITE_BACKUP}
PATCH_SITES+=   	${MASTER_SITE_BACKUP}
OTHER_SITES+=   	${MASTER_SITE_BACKUP}
.else
MASTER_SITES:=		${MASTER_SITE_OVERRIDE} ${MASTER_SITES}
PATCH_SITES:=		${MASTER_SITE_OVERRIDE} ${PATCH_SITES}
OTHER_SITES:=		${MASTER_SITE_OVERRIDE} ${OTHER_SITES}
.endif

DISTFILES=		${DISTNAME}${DISTVERSION}.${EXTRACT_SUFX}
PATCH_STRIP_COUNT?=	1
LOCAL_PATCH_STRIP_COUNT?=	1
PATCH_OPTIONS?=
LOCAL_PATCH_OPTIONS?=
.ifdef LOCAL_PATCHFILESDIR 
_LOCAL_PATCHFILESDIR=	${.CURDIR}/${LOCAL_PATCHFILESDIR}
.else
_LOCAL_PATCHFILESDIR=	${.CURDIR}
.endif

.if defined(ADDFILES)
DISTFILES+=		${ADDFILES}
ADDFILESDIR?=		${DISTDIR}/${__DISTNAME}
.endif

ALLFILES?=		${DISTFILES} ${PATCHFILES} ${OTHERFILES}

.if !exists(${DISTFILESDIR}/${DISTNAME}${DISTVERSION}.${EXTRACT_SUFX}) && exists(${DISTDIR}/${__DISTNAME})
FORCE_EXTRACT=		yes
.endif


.if exists(${VERSIONS_FILE})
EXIST!= grep -c "^${__DISTNAME} ${DISTVERSION} ${DISTRELEASE}$$" ${VERSIONS_FILE} || true
.else
EXIST=	0
.endif

.if !exists(${DISTDIR}/${__DISTNAME}) || defined(FORCE_EXTRACT) || ${EXIST} == "0"
DO_EXTRACT=		yes
.endif



MKDIST_DEBUG_LEVEL?=	0
_MKDIST_SILENT=		@
_MKDIST_DEBUG=
.if ${MKDIST_DEBUG_LEVEL} > 0
_MKDIST_SILENT=
.endif
.if ${MKDIST_DEBUG_LEVEL} > 1
_MKDIST_DEBUG=	set -x;
.endif



_CHECK_DIST_PATH= \
	if [ "X${DIST_PATH}" != "X" ]; then \
		for d in "" `echo ${DIST_PATH} | tr ':' ' '`; do  \
			if [ "X$$d" = "X" -o "X$$d" = "X${DISTFILESDIR}" ]; then continue; fi; \
		done; \
	fi

_FETCH_FILE= \
	if [ ! -f $$file -a ! -f $$bfile -a ! -h $$bfile ]; then    \
		echo ">> $$bfile doesn't seem to exist on this system."; \
		for site in $$sites; do \
			echo ">> Attempting to fetch $$bfile from $${site}."; \
			if ${FETCH_CMD} ${FETCH_BEFORE_ARGS} $${site}/$${bfile} ${FETCH_AFTER_ARGS}; then \
				if [ -n "${FAILOVER_FETCH}" -a -f ${MD5_FILE} -a -f ${DISTFILESDIR}/$$bfile ]; then \
					CKSUM=`md5sum < ${DISTFILESDIR}/$$bfile | awk '{print $$1}'`; \
					CKSUM2=`awk '$$2 == "('$$file')"{print $$1;}' ${MD5_FILE}`; \
					if [ "$$CKSUM" = "$$CKSUM2" -o "$$CKSUM2" = "IGNORE" ]; then \
						continue 2;     \
					else                \
						echo ">> Checksum failure - trying next site."; \
					fi; \
				elif [ ! -f ${DISTFILESDIR}/$$bfile ]; then \
					echo ">> FTP didn't fetch expected file, trying next site." ; \
				else \
					continue 2; \
				fi; \
			fi \
		done; \
		echo ">> Couldn't fetch it - please try to retrieve this"; \
		echo ">> $$bfile manually into ${DISTFILESDIR} and try again."; \
		exit 1; \
	fi

MASTER_SORT?=
MASTER_SORT_REGEX?=
MASTER_SORT_REGEX+= ${MASTER_SORT:S/./\\./g:C/.*/:\/\/[^\/]*&\//}
MASTER_SORT_AWK= BEGIN { RS = " "; ORS = " "; IGNORECASE = 1 ; gl = "${MASTER_SORT_REGEX}"; }
.for srt in ${MASTER_SORT_REGEX}
MASTER_SORT_AWK+= /${srt:C/\//\\\//g}/ { good["${srt}"] = good["${srt}"] " " $$0 ; next; }
.endfor
MASTER_SORT_AWK+= { rest = rest " " $$0; } END { n=split(gl, gla); for(i=1;i<=n;i++) { print good[gla[i]]; } print rest; }
SORTED_MASTER_SITES!= echo '${MASTER_SITES}' | awk '${MASTER_SORT_AWK}'


.MAIN:	all
all:	fetch versioncheck preextract extract patch postextract

.if !target(fetch)
fetch:
	${_MKDIST_SILENT}${_MKDIST_DEBUG} \
 	 if [ ! -d ${DISTFILESDIR} ]; then mkdir -p ${DISTFILESDIR}; fi; 
	${_MKDIST_SILENT}(${_MKDIST_DEBUG}cd ${DISTFILESDIR}; \
	sites="${SORTED_MASTER_SITES}"; \
	for file in "" ${DISTFILES}; do \
		if [ "X$$file" = X"" ]; then continue; fi; \
		bfile=`basename $$file`; \
		${_CHECK_DIST_PATH}; \
		${_FETCH_FILE} \
	done)
.if defined(PATCHFILES)
	${_MKDIST_SILENT}(${_MKDIST_DEBUG}cd ${DISTFILESDIR}; \
	sites="${PATCH_SITES}"; \
	for file in "" ${PATCHFILES}; do \
		if [ "X$$file" = X"" ]; then continue; fi; \
		bfile=`basename $$file`; \
		${_CHECK_DIST_PATH}; \
		${_FETCH_FILE} \
	done)
.endif
.if defined(OTHERFILES)
	${_MKDIST_SILENT}(${_MKDIST_DEBUG}cd ${DISTFILESDIR}; \
	sites="${OTHER_SITES}"; \
	for file in "" ${OTHERFILES}; do \
		if [ "X$$file" = X"" ]; then continue; fi; \
		bfile=`basename $$file`; \
		${_CHECK_DIST_PATH}; \
		${_FETCH_FILE} \
	done)
.endif
.endif # !target(fetch)



.if !target(versioncheck)
versioncheck:
.if ${EXIST} == "0"
	${_MKDIST_SILENT}${_MKDIST_DEBUG} echo "Version ${DISTVERSION} ${DISTRELEASE} not extracted."
.if !exists(${VERSIONS_FILE})
	${_MKDIST_SILENT}${_MKDIST_DEBUG} echo "#Distname Version Release" > ${VERSIONS_FILE}
.endif
	${_MKDIST_SILENT}${_MKDIST_DEBUG} echo "Remove old dist/${__DISTNAME} if exist ..."
	${_MKDIST_SILENT}${_MKDIST_DEBUG} rm -rf ${DISTDIR}/${__DISTNAME}
.if defined(CLEAN_ALTRENAMEDISTDIR)
	${_MKDIST_SILENT}${_MKDIST_DEBUG} ${CLEAN_ALTRENAMEDISTDIR}
.endif
	${_MKDIST_SILENT}${_MKDIST_DEBUG} \
	grep -v "^${__DISTNAME} " ${VERSIONS_FILE} > ${VERSIONS_FILE_TMP}
	${_MKDIST_SILENT}${_MKDIST_DEBUG} \
	mv ${VERSIONS_FILE_TMP} ${VERSIONS_FILE}
.endif # ${EXIST} == "0"
.endif # !target(versioncheck)



_UNZIPBIN= \
	bfileprefix=`echo $$bfile | sed -e 's/\.bz2$$//' -e 's/\.gz$$//' -e 's/\.tgz$$//' -e 's/\.//g'`; \
	bfilesufix=`echo $$bfile | sed -e 's/\.//g' -e 's/^'$$bfileprefix'//'`; \
	case $$bfilesufix in \
	gz)	unzipbin="gunzip -c";; \
	bz2)	unzipbin="bunzip2 -c";; \
	tgz)	unzipbin="gunzip -c";; \
	*)	unzipbin="cat";; \
	esac



.if !target(extract)
extract:
.if defined(DO_EXTRACT)
.if defined(FORCE_EXTRACT)
	${_MKDIST_SILENT}${_MKDIST_DEBUG} rm -rf ${DISTDIR}/${__DISTNAME}
	${_MKDIST_SILENT}${_MKDIST_DEBUG} \
	grep -v "^${__DISTNAME} " ${VERSIONS_FILE} > ${VERSIONS_FILE_TMP}
	${_MKDIST_SILENT}${_MKDIST_DEBUG} mv ${VERSIONS_FILE_TMP} ${VERSIONS_FILE}
.endif
	${_MKDIST_SILENT}${_MKDIST_DEBUG} \
 	if [ ! -d ${DISTDIR} ]; then mkdir -p ${DISDIR}; fi; 
.if defined(NOTOPDIR)
	${_MKDIST_SILENT}${_MKDIST_DEBUG} \
	mkdir ${DISTDIR}/${DISTNAME}${DISTVERSION};
	${_MKDIST_SILENT} ${_MKDIST_DEBUG} \
	file=${DISTNAME}${DISTVERSION}.${EXTRACT_SUFX}; \
	bfile=`basename $$file`; \
	${_UNZIPBIN}; \
	echo "Extract $$file ..."; \
	$$unzipbin ${DISTFILESDIR}/$$file | tar -C ${DISTDIR}/${DISTNAME}${DISTVERSION} -xf - ;
.else
	${_MKDIST_SILENT} ${_MKDIST_DEBUG} \
	file=${DISTNAME}${DISTVERSION}.${EXTRACT_SUFX}; \
	bfile=`basename $$file`; \
	${_UNZIPBIN}; \
	echo "Extract $$file ..."; \
	$$unzipbin ${DISTFILESDIR}/$$file | tar -C ${DISTDIR} -xf - ;
.endif # defined(NOTOPDIR)
.if !defined(ALTRENAMEDISTDIR)
	${_MKDIST_SILENT}${_MKDIST_DEBUG} \
	mv ${DISTDIR}/${DISTNAME}${DISTVERSION} ${DISTDIR}/${__DISTNAME};
.else
	${_MKDIST_SILENT}${_MKDIST_DEBUG} ${ALTRENAMEDISTDIR};
.endif # !defined(ALTRENAMEDISTDIR)
.if defined(ADDFILES)
	${_MKDIST_SILENT} ${_MKDIST_DEBUG} \
	for file in "" ${ADDFILES}; do \
		if [ "X$$file" = X"" ]; then continue; fi; \
		bfile=`basename $$file`; \
		${_UNZIPBIN}; \
		echo "Extract $$file ..."; \
		$$unzipbin ${DISTFILESDIR}/$$file | tar -C ${ADDFILESDIR} -xf - ; \
	done
.endif # defined(ADDFILES)
	${_MKDIST_SILENT}${_MKDIST_DEBUG} \
		echo "${__DISTNAME} ${DISTVERSION} ${DISTRELEASE}" >> ${VERSIONS_FILE}
.endif # defined(DO_EXTRACT)
.endif # !target(extract)



.if !target(patch)
patch:
.if defined(DO_EXTRACT)
.if defined(ALTPATCHCMD)
	${_MKDIST_SILENT} ${_MKDIST_DEBUG} ${ALTPATCHCMD}
.else
.if defined(PATCHFILES)
	${_MKDIST_SILENT}(${_MKDIST_DEBUG}cd ${DISTDIR}/${__DISTNAME}; \
	for file in "" ${PATCHFILES}; do \
		if [ "X$$file" = X"" ]; then continue; fi; \
		bfile=`basename $$file`; \
		${_UNZIPBIN}; \
		echo "Patch $$file ..."; \
		$$unzipbin ${DISTFILESDIR}/$$file | patch -p${PATCH_STRIP_COUNT} ${PATCH_OPTIONS}; \
	done)
.endif # defined(PATCHFILES)
.endif # defined(ALTPATCHCMD)
.if defined(LOCAL_PATCHFILES)
	${_MKDIST_SILENT}(${_MKDIST_DEBUG}cd ${DISTDIR}/${__DISTNAME}; \
	for file in "" ${LOCAL_PATCHFILES}; do \
		if [ "X$$file" = X"" ]; then continue; fi; \
		echo "Patch $$file ..."; \
		patch -p${LOCAL_PATCH_STRIP_COUNT} ${LOCAL_PATCH_OPTIONS} < ${_LOCAL_PATCHFILESDIR}/$$file; \
	done)
.endif # defined(LOCAL_PATCHFILES)
.endif # defined(DO_EXTRACT)
.endif # !target(patch)



.if !target(preextract)
preextract:
.if defined(DO_EXTRACT)
.if defined(PREEXTRACT) && defined(DO_EXTRACT)
	${_MKDIST_SILENT} ${_MKDIST_DEBUG} \
	echo "Do pre extract ..."; \
	${PREEXTRACT}
.endif
.endif # defined(DO_EXTRACT)
.endif # !target(preextract)



.if !target(postextract)
postextract:
.if defined(DO_EXTRACT)
	${_MKDIST_SILENT}(${_MKDIST_DEBUG}cd ${DISTDIR}; \
	chmod 755 ${__DISTNAME}; \
	chown -R root.wheel ${__DISTNAME}; \
	chmod -R go+rX ${__DISTNAME} )
.if defined(POSTEXTRACT) && defined(DO_EXTRACT)
	${_MKDIST_SILENT} ${_MKDIST_DEBUG} \
	echo "Do post extract ..."; \
	${POSTEXTRACT}
.endif
.endif # defined(DO_EXTRACT)
.endif # !target(postextract)



.if !target(md5)
md5:
	${_MKDIST_SILENT}(${_MKDIST_DEBUG}cd ${DISTFILESDIR} && md5sum ${ALLFILES} > ${.CURDIR}/${MD5_FILE} )
.endif # !target(md5)



.if !target(distfiles)
distfiles:
.if !defined(RELEASEDIR)
	echo "Must be define RELEASEDIR."
.else
	${_MKDIST_SILENT}${_MKDIST_DEBUG} \
	if [ ! -d ${RELEASEDISTDIR} ]; then \
		mkdir -p ${RELEASEDISTDIR}; \
		echo "Make dir ${RELEASEDISTDIR}"; \
	fi; 
	${_MKDIST_SILENT}(${_MKDIST_DEBUG} \
	for file in "" ${DISTFILES}; do \
		if [ "X$$file" = X"" ]; then continue; fi; \
		echo "Copy $$file => ${RELEASEDISTDIR}"; \
		cp ${DISTFILESDIR}/$$file ${RELEASEDISTDIR}; \
	done)
.if defined(PATCHFILES)
	${_MKDIST_SILENT}(${_MKDIST_DEBUG} \
	for file in "" ${PATCHFILES}; do \
		if [ "X$$file" = X"" ]; then continue; fi; \
		echo "copy $$file => ${RELEASEDISTDIR}"; \
		cp ${DISTFILESDIR}/$$file ${RELEASEDISTDIR}; \
	done)
.endif
.if defined(OTHERFILES)
	${_MKDIST_SILENT}(${_MKDIST_DEBUG} \
	for file in "" ${OTHERFILES}; do \
		if [ "X$$file" = X"" ]; then continue; fi; \
		echo "copy $$file => ${RELEASEDISTDIR}"; \
		cp ${DISTFILESDIR}/$$file ${RELEASEDISTDIR}; \
	done)
.endif
.endif # !defined(RELEASEDIR)
.endif # !target(distfiles)



.if !target(versions_file)
versions_file:
	${_MKDIST_SILENT}${_MKDIST_DEBUG} \
		echo "${__DISTNAME} ${DISTVERSION} ${DISTRELEASE}" >> ${VERSIONS_FILE}
	${_MKDIST_SILENT}${_MKDIST_DEBUG} \
	for dir in ${DEPENDENT}; do \
		if [ -d ../../$$dir/build ]; then \
			echo "${__DISTNAME} ${DISTVERSION} ${DISTRELEASE}" > ../../$$dir/${BUILD_VERSION_FILE}; \
		fi; \
	done; 
.endif # !target(versions_file)



.if !target(clean)
clean:
	${_MKDIST_SILENT}${_MKDIST_DEBUG} rm -rf ${DISTDIR}/${__DISTNAME};
.if defined(CLEAN_ALTRENAMEDISTDIR)
	${_MKDIST_SILENT}${_MKDIST_DEBUG} ${CLEAN_ALTRENAMEDISTDIR};
.endif
	${_MKDIST_SILENT}${_MKDIST_DEBUG} \
	grep -v "^${__DISTNAME} " ${VERSIONS_FILE} > ${VERSIONS_FILE_TMP}
	${_MKDIST_SILENT}${_MKDIST_DEBUG} mv ${VERSIONS_FILE_TMP} ${VERSIONS_FILE}
.endif # !target(clean)



.endif # !defined(_BSD_MKDIST_MK_)
regress:
