#	$ssdlinux: Makefile,v 1.54 2005/02/09 07:49:41 todoroki Exp $

.include "${.CURDIR}/../share/mk/bsd.own.mk"

BUILD_SRCDIST?=		yes
BUILD_COMMONDIST?=	yes
BUILD_DISTFILES?=	yes
TEMPDESTDIR=	${DESTDIR}/TMP

BASELIST=	${.CURDIR}/${TARGET_SSDHOSTTYPEX}/distlst/base.lst
.if defined(CROSS_BUILD)
COMPLIST=	${.CURDIR}/${TARGET_SSDHOSTTYPEX}/distlst/comp.lst.cross
.else
COMPLIST=	${.CURDIR}/${TARGET_SSDHOSTTYPEX}/distlst/comp.lst
.endif

SSDSRCS=	AUTHORS ChangeLog LICENCE Makefile bin contrib cross distrib etc lib libexec mkdist sbin share tools usr.bin usr.sbin

.if defined(DESTDIR) && defined(RELEASEDIR)
release: release_dirs srcdist distfiles basedist kerndist compdist etcdist mandist contribdist crossdist checksum bootfsdist
.else
release:
	@echo "Must be set DESTDIR and RELEASEDIR for 'make release'."
.endif

release_dirs:
	mkdir -p ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/binary
.if ${TARGET_SSDHOSTTYPEX} == "powerpc-obs2xx"
	mkdir -p ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/cfroot
.endif
	mkdir -p ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/installation
.if ${TARGET_SSDHOSTTYPEX} == "i386"
	mkdir -p ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/installation/floppy
	mkdir -p ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/installation/netboot
.endif
	mkdir -p ${RELEASEDIR}/source
	rm -f ${RELEASEDIR}/${SSDVERSION}-*
	cd ${RELEASEDIR} && ln -s ./ ${SSDRELEASENAME}

srcdist:
.if ${BUILD_SRCDIST} == "yes"
	(cd ${DESTDIR}/usr && rm -rf src)
.if ${HAVE_CVS} == "yes"
.ifdef ${SSDCVSTAG}
	(cd ${DESTDIR}/usr && cvs export -r ${SSDCVSTAG} src)
.else
	(cd ${DESTDIR}/usr && cvs export -D ${SSDCVSDATE} src)
.endif
.else
	mkdir -p ${DESTDIR}/usr/src
	(cd ${.CURDIR}/../; tar --exclude=CVS --exclude=build --exclude=*.o \
		--exclude=*.so --exclude=*.a -cvpf - ${SSDSRCS}) | \
		(cd ${DESTDIR}/usr/src;  tar xpf -)
	ln -sf ${.CURDIR}/../dist ${DESTDIR}/usr/src/dist
	(cd ${DESTDIR}/usr/src/distrib && ${MAKE} clean)
	(cd ${DESTDIR}/usr/src && ${MAKE} -DFORCE_CLEAN \
		TOOLCHAINDIR=${DESTDIR}/${TOOLCHAINDIR} clean )
	(cd ${DESTDIR}/usr/src && ${MAKE} -DFORCE_CLEAN \
		TOOLCHAINDIR=${DESTDIR}/${TOOLCHAINDIR} cleandir )
	rm -f ${DESTDIR}/usr/src/dist
.endif
	mkdir -p ${DESTDIR}/usr/src/dist/distfiles
	(cd ${DESTDIR} && tar cvpzf ${RELEASEDIR}/source/src.tgz ./usr/src )
	( cd ${RELEASEDIR}/source && md5sum *.tgz > MD5 )
	touch ${RELEASEDIR}/source
.endif

distfiles:
.if ${BUILD_DISTFILES} == "yes"
	rm -rf ${RELEASEDIR}/distfiles
	mkdir -p ${RELEASEDIR}/distfiles
	(cd ${.CURDIR}/../mkdist && ${MAKE} distfiles)
.endif

bootfsdist: bootfs
.if ${TARGET_SSDHOSTTYPEX} == "i386"
	cp  ${.CURDIR}/${TARGET_SSDHOSTTYPEX}/bootfs/boot.fs ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/installation/floppy
	cp  ${.CURDIR}/${TARGET_SSDHOSTTYPEX}/bootfs/boot.fs.gz ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/installation/floppy
	cp  ${.CURDIR}/${TARGET_SSDHOSTTYPEX}/bootfs-big/boot-big.fs ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/installation/floppy
	cp  ${.CURDIR}/${TARGET_SSDHOSTTYPEX}/bootfs-big/boot-big.fs.gz ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/installation/floppy
	cp  ${.CURDIR}/${TARGET_SSDHOSTTYPEX}/instfs/inst.fs ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/installation/floppy
	cp  ${.CURDIR}/${TARGET_SSDHOSTTYPEX}/instfs/inst.fs.gz ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/installation/floppy
	(cd ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/installation/floppy && md5sum *.fs *.gz > MD5)
	cp  ${.CURDIR}/../linux/arch/i386/boot/bzImage ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/installation/netboot
	cp  ${DESTDIR}/usr/mdec/grub/i386-ssd/nbgrub ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/installation/netboot
	cp  ${DESTDIR}/usr/mdec/grub/i386-ssd/pxegrub ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/installation/netboot
	cp  ${.CURDIR}/${TARGET_SSDHOSTTYPEX}/initrd/initrd.fs.gz ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/installation/netboot
	cp  ${.CURDIR}/${TARGET_SSDHOSTTYPEX}/bootfs-big/menu.lst ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/installation/netboot/grub.conf.sample
	(cd ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/installation/netboot && md5sum nbgrub pxegrub bzImage *.gz grub.conf.sample > MD5)
.elif ${TARGET_SSDHOSTTYPEX} == "powerpc-obs2xx"
	cp  ${.CURDIR}/${TARGET_SSDHOSTTYPEX}/standard/initrd/ramdisk.image.gz ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/installation
	cp  ${.CURDIR}/${TARGET_SSDHOSTTYPEX}/standard/treeboot/zImage.initrd.treeboot ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/installation
	cp  ${.CURDIR}/${TARGET_SSDHOSTTYPEX}/product/initrd/ramdisk.image-product.gz ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/installation
	cp  ${.CURDIR}/${TARGET_SSDHOSTTYPEX}/product/treeboot/zImage.initrd.treeboot-product ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/installation
.if ${TARGET_SSDHOSTTYPE} == "powerpc-obs266"
	cp  ${.CURDIR}/${TARGET_SSDHOSTTYPEX}/standard-big/initrd/ramdisk.image.big.gz ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/installation
	cp  ${.CURDIR}/${TARGET_SSDHOSTTYPEX}/standard-big/treeboot/zImage.initrd.treeboot.big ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/installation
	cp  ${.CURDIR}/${TARGET_SSDHOSTTYPEX}/product-big/initrd/ramdisk.image.big-product.gz ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/installation
	cp  ${.CURDIR}/${TARGET_SSDHOSTTYPEX}/product-big/treeboot/zImage.initrd.treeboot.big-product ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/installation
	cp  ${.CURDIR}/${TARGET_SSDHOSTTYPEX}/standard-pcmcia/initrd/ramdisk.image.pcmcia.gz ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/installation
	cp  ${.CURDIR}/${TARGET_SSDHOSTTYPEX}/standard-pcmcia/treeboot/zImage.initrd.treeboot.pcmcia ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/installation
	cp  ${.CURDIR}/${TARGET_SSDHOSTTYPEX}/product-pcmcia/initrd/ramdisk.image.pcmcia-product.gz ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/installation
	cp  ${.CURDIR}/${TARGET_SSDHOSTTYPEX}/product-pcmcia/treeboot/zImage.initrd.treeboot.pcmcia-product ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/installation
.endif
	(cd ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/installation && md5sum zImage.initrd.* *.gz > MD5)
	cp  ${.CURDIR}/${TARGET_SSDHOSTTYPEX}/cfroot/standard/cfroot.image.tgz ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/cfroot
	cp  ${.CURDIR}/${TARGET_SSDHOSTTYPEX}/cfroot/product/cfroot.image-product.tgz ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/cfroot
	(cd ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/cfroot && md5sum *.tgz > MD5)
.elif ${TARGET_SSDHOSTTYPEX} == "powerpc-obs50"
	cp  ${.CURDIR}/${TARGET_SSDHOSTTYPEX}/initrd/ramdisk.image.gz ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/installation
	cp  ${.CURDIR}/${TARGET_SSDHOSTTYPEX}/treeboot/zImage.initrd.embedded ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/installation
	(cd ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/installation && md5sum zImage.initrd.* *.gz > MD5)
.endif

basedist:
	mkdir -p ${TEMPDESTDIR}
	( cd ${DESTDIR} && tar cvpf - `cat ${BASELIST}`) \
		| ( cd ${TEMPDESTDIR} && tar xpf - )
.if defined(CROSS_BUILD)
	( cd /usr/share && tar cvpf - zoneinfo ) \
		| ( cd ${TEMPDESTDIR}/usr/share && tar xpf - )
.endif
	( cd ${TEMPDESTDIR} && rm -rf `cat ${COMPLIST}` )
	( cd ${TEMPDESTDIR} && tar cvpzf ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/binary/base.tgz ./* )
	rm -rf ${TEMPDESTDIR}

kerndist:
.if ${TARGET_SSDHOSTTYPEX} == "i386"
	(cd ${DESTDIR} && tar cvpzf ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/binary/kern.tgz ./vmlinuz ./vmlinuz.* ./System.map ./System.map.* )
.else
	(cd ${DESTDIR} && tar cvpzf ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/binary/kern.tgz ./System.map ./System.map.*)
.endif

compdist:
.if ${BUILD_COMMONDIST} == "yes"
.if ${TARGET_SSDHOSTTYPEX} == "powerpc-obs2xx" || ${TARGET_SSDHOSTTYPEX} == "powerpc-obs50"
	(cd ${.CURDIR}/../; tar cvpf - linux/Makefile linux/include linux/arch/ppc/platforms/*.h) | (cd ${DESTDIR}/usr/src;  tar xpf -)
.else
	(cd ${.CURDIR}/../; tar cvpf - linux/Makefile linux/include ) | (cd ${DESTDIR}/usr/src;  tar xpf -)
.endif
	( cd ${DESTDIR} && tar cvpzf ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/binary/comp.tgz `cat ${COMPLIST}` )
.endif

etcdist:
.if ${BUILD_COMMONDIST} == "yes" || ${TARGET_SSDHOSTTYPEX} == "powerpc-obs50"
	( cd ${DESTDIR} && tar cvpzf ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/binary/etc.tgz ./etc )
.endif

mandist:
.if ${BUILD_COMMONDIST} == "yes"
	mkdir -p ${TEMPDESTDIR}
	( cd ${DESTDIR} && tar cvpf - ./usr/share/man ./usr/share/info ./usr/share/doc ) \
		| ( cd ${TEMPDESTDIR} && tar xpf - )
	( cd ${TEMPDESTDIR} && rm -rf `cat ${COMPLIST}` )
	( cd ${TEMPDESTDIR} && tar cvpzf ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/binary/man.tgz ./* )
	rm -rf ${TEMPDESTDIR}
.endif

contribdist:
.if ${BUILD_COMMONDIST} == "yes"
.if ${TARGET_SSDHOSTTYPEX} == "powerpc-obs2xx"
	( cd ${DESTDIR} && tar cvpzf ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/binary/contrib.tgz ./usr/contrib ./home )
.endif
.endif

crossdist:
.if ${TARGET_SSDHOSTTYPEX} == "i386"
	( cd ${DESTDIR} && tar cvpzf ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/binary/cross.tgz ./usr/cross )
.endif

checksum:
	( cd ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/binary && md5sum *.tgz > MD5 )
	( cd ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}/binary && ln -sf ../../source/src.tgz )
	cp ${.CURDIR}/../AUTHORS	${RELEASEDIR}
	cp ${.CURDIR}/../ChangeLog	${RELEASEDIR}
	cp ${.CURDIR}/../LICENCE	${RELEASEDIR}

bootfs:
	(cd ${.CURDIR}/utils && ${MAKE} )
	(cd ${.CURDIR}/${TARGET_SSDHOSTTYPEX} && ${MAKE} )

clean:
	(cd ${.CURDIR}/i386 && ${MAKE} clean)
	(cd ${.CURDIR}/powerpc-obs2xx && ${MAKE} clean)
	(cd ${.CURDIR}/powerpc-obs50 && ${MAKE} clean)
	(cd ${.CURDIR}/utils && ${MAKE} clean)
