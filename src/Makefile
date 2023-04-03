#	$ssdlinux: Makefile,v 1.75 2004/12/10 02:03:25 yamagata Exp $

.include "${.CURDIR}/share/mk/bsd.own.mk"

.ifdef	DESTDIR
BUILDTREEDIR=	${DESTDIR}
KERN_COMPILE_OPTIONS= INSTALL_MOD_PATH=${DESTDIR} ARCH=${ARCH}
.else
BUILDTREEDIR=	/
.endif

.ifdef UPDATE
NOCLEAN=	yes
.endif

.ifdef ALT_KERNEL_CONFIG
.if exists(${.CURDIR}/mkdist/kernel/${KERNEL_DIFF_PATH}/${_ALT_KERNEL_CONFIG})
KERNEL_CONFIG?= ${.CURDIR}/mkdist/kernel/${KERNEL_DIFF_PATH}/${_ALT_KERNEL_CONFIG}
.elif exists(${.CURDIR}/mkdist/kernel/${KERNEL_VERSION}/${_ALT_KERNEL_CONFIG})
KERNEL_CONFIG?= ${.CURDIR}/mkdist/kernel/${KERNEL_VERSION}/${_ALT_KERNEL_CONFIG}
.elif exists(${.CURDIR}/mkdist/kernel/${KERNEL_DIFF_PATH}/${_KERNEL_CONFIG})
KERNEL_CONFIG?=	${.CURDIR}/mkdist/kernel/${KERNEL_DIFF_PATH}/${_KERNEL_CONFIG}
.else
KERNEL_CONFIG?= ${.CURDIR}/mkdist/kernel/${KERNEL_VERSION}/${_KERNEL_CONFIG}
.endif
.else
.if exists(${.CURDIR}/mkdist/kernel/${KERNEL_DIFF_PATH}/${_KERNEL_CONFIG})
KERNEL_CONFIG?=	${.CURDIR}/mkdist/kernel/${KERNEL_DIFF_PATH}/${_KERNEL_CONFIG}
.else
KERNEL_CONFIG?= ${.CURDIR}/mkdist/kernel/${KERNEL_VERSION}/${_KERNEL_CONFIG}
.endif
.endif

.if defined(CROSS_BUILD)
KERN_COMPILE_OPTIONS+= CROSS_COMPILE=${TARGET_MACHTYPE}-
.else
KERN_COMPILE_OPTIONS+=
.endif

.MAIN: all
all: build

build: build_bin install build_zImage

extract_dist:
	(cd ${.CURDIR}/mkdist && ${MAKE})

dist_dir_lst:
	(cd ${.CURDIR}/distrib/${TARGET_SSDHOSTTYPEX}/distlst && ${MAKE})

build_tree: dist_dir_lst
.ifdef	DESTDIR
	mkdir -p ${DESTDIR}
.endif
	desttree=`cat ${.CURDIR}/distrib/${TARGET_SSDHOSTTYPEX}/distlst/mtree.conf`;\
	( cd ${BUILDTREEDIR} && for i in $$desttree; do mkdir -p $$i; done )
.ifdef	DESTDIR
	touch ${DESTDIR}/var/log/aculog
	touch ${DESTDIR}/var/log/authlog
	touch ${DESTDIR}/var/log/maillog
	touch ${DESTDIR}/var/log/messages
	touch ${DESTDIR}/var/log/wtmp
	touch ${DESTDIR}/var/log/xferlog
	touch ${DESTDIR}/var/log/lastlog
	chmod 1777 ${DESTDIR}/tmp
	chmod 1777 ${DESTDIR}/var/tmp
	chmod 1777 ${DESTDIR}/var/mail
	chmod 700 ${DESTDIR}/var/chroot/named
	chmod 700 ${DESTDIR}/var/chroot/sshd
	chown named.named ${DESTDIR}/etc/namedb/db
	chown named.named ${DESTDIR}/etc/namedb/2nd
	chown named.named ${DESTDIR}/var/run/named
	chmod 775 ${DESTDIR}/var/run/named
	chown smmsp.smmsp ${DESTDIR}/var/spool/clientmqueue
	chmod 770 ${DESTDIR}/var/spool/clientmqueue
	chmod 700 ${DESTDIR}/var/spool/mqueue
	chmod 1777 ${DESTDIR}/var/preserve
	chown uucp.daemon ${DESTDIR}/var/spool/lock
	chmod 755 ${DESTDIR}/var/spool/lock
	chown uucp.daemon ${DESTDIR}/var/log/aculog
.endif

build_bin: extract_dist clean_dest clean_release clean cleandir build_tree build_kernel build_tools install_lib build_usr

build_usr:
	cd ${.CURDIR}/etc/pcmcia && ${MAKE} clean
	cd ${.CURDIR}/etc  && ${MAKE}
	cd ${.CURDIR}/libexec && ${MAKE}
	cd ${.CURDIR}/share && ${MAKE}
	cd ${.CURDIR}/bin && ${MAKE}
	cd ${.CURDIR}/sbin && ${MAKE}
	cd ${.CURDIR}/usr.bin && ${MAKE} -DBUILD_WORLD
	cd ${.CURDIR}/usr.sbin && ${MAKE}
	cd ${.CURDIR}/contrib && ${MAKE}
.if ${TARGET_HOSTTYPE} == "i386" && !defined(NEW_GLIBC)
.ifdef DESTDIR 
	cd ${.CURDIR}/cross && ${MAKE}
.else
.if exists(/usr/cross/powerpc/bin/powerpc-ssd-linux-gnu-gcc)
	cd ${.CURDIR}/cross && ${MAKE}
.else
	cd ${.CURDIR}/cross/powerpc && ${MAKE} initial_build
.endif
.endif
.endif

build_lib1:
.ifndef SKIPBUILD
.if !exists(/usr/bin/perl)
	cd ${.CURDIR}/usr.bin/perl && ${MAKE} && ${MAKE} DESTDIR=/ install
.endif
	cd ${.CURDIR}/share/mk && ${MAKE} install
	cd ${.CURDIR}/usr.bin/binutils && ${MAKE} && ${MAKE} install
	cd ${.CURDIR}/usr.bin/gcc && ${MAKE} && ${MAKE} install
	cd ${.CURDIR}/usr.bin/binutils && ${MAKE} install
	cd ${.CURDIR}/lib/glibc && ${MAKE} && ${MAKE} install
.endif

build_lib2:
.ifndef SKIPBUILD
.if !exists(/usr/bin/perl)
	cd ${.CURDIR}/usr.bin/perl && ${MAKE} && ${MAKE} DESTDIR=/ install
.endif
	cd ${.CURDIR}/lib/ssl && ${MAKE} && ${MAKE} install
	cd ${.CURDIR}/lib/libz && ${MAKE} && ${MAKE} install
	cd ${.CURDIR}/lib/libdb && ${MAKE} && ${MAKE} install
.ifdef USE_PAM
	cd ${.CURDIR}/lib/pam && ${MAKE} && ${MAKE} install
.endif
	cd ${.CURDIR}/lib && ${MAKE} -DBUILD_WORLD
	cd ${.CURDIR}/lib/libproc && ${MAKE} bugfix && ${MAKE} install
.endif

build_kernel:
.if !defined(NOCLEAN) || defined(FORCE_CLEAN)
	cp ${KERNEL_CONFIG} ${.CURDIR}/linux/.config
	cd ${.CURDIR}/linux && ${GMAKE} ${KERN_COMPILE_OPTIONS} oldconfig
	cd ${.CURDIR}/linux && ${GMAKE} ${KERN_COMPILE_OPTIONS} clean
.endif
	cd ${.CURDIR}/linux && ${GMAKE} ${KERN_COMPILE_OPTIONS} dep
	cd ${.CURDIR}/linux && ${GMAKE} ${KERN_COMPILE_OPTIONS} bzImage
	cd ${.CURDIR}/linux && ${GMAKE} ${KERN_COMPILE_OPTIONS} modules

menuconfig:
	cp ${KERNEL_CONFIG} ${.CURDIR}/linux/.config
	cd ${.CURDIR}/linux && ${GMAKE} ${KERN_COMPILE_OPTIONS} menuconfig

install_lib: build_lib1 build_lib2
	cd ${.CURDIR}/lib && ${MAKE} -DBUILD_WORLD install

install: install_kernel
.ifdef DESTDIR
	cd ${.CURDIR}/etc && ${MAKE} install
.endif
.ifdef SKIPBUILD
	cd ${.CURDIR}/lib && ${MAKE} install
	cd ${.CURDIR}/share && ${MAKE} install
	cd ${.CURDIR}/bin && ${MAKE} install
	cd ${.CURDIR}/sbin && ${MAKE} install
	cd ${.CURDIR}/libexec && ${MAKE} install
	cd ${.CURDIR}/usr.bin && ${MAKE} install
	cd ${.CURDIR}/usr.sbin && ${MAKE} install
	cd ${.CURDIR}/contrib && ${MAKE} install
.if ${TARGET_HOSTTYPE} == "i386" && !defined(NEW_GLIBC)
	cd ${.CURDIR}/cross && ${MAKE} install 
.endif
.else
	cd ${.CURDIR}/share && ${MAKE} -DBUILD_WORLD install
	cd ${.CURDIR}/bin && ${MAKE} install
	cd ${.CURDIR}/sbin && ${MAKE} install
	cd ${.CURDIR}/libexec && ${MAKE} install
	cd ${.CURDIR}/usr.bin && ${MAKE} -DBUILD_WORLD install
	cd ${.CURDIR}/usr.sbin && ${MAKE} install
	cd ${.CURDIR}/contrib && ${MAKE} install
.if ${TARGET_HOSTTYPE} == "i386" && !defined(NEW_GLIBC)
	cd ${.CURDIR}/cross && ${MAKE} install
.endif
.endif

install_kernel:
.ifndef DESTDIR
.if ${TARGET_OPENBLOCKS} == "none"
	cd ${.CURDIR}/linux && ${GMAKE} ${KERN_COMPILE_OPTIONS} install
.else
	cd ${.CURDIR}/linux && ${INSTALL} -c -m 644 -o root -g wheel ./System.map /System.map
.endif
.endif
.ifdef CROSS_BUILD
	mv ${.CURDIR}/linux/System.map ${.CURDIR}/linux/System.map.none
.endif
	cd ${.CURDIR}/linux && ${GMAKE} ${KERN_COMPILE_OPTIONS} modules_install
.ifdef CROSS_BUILD
	mv ${.CURDIR}/linux/System.map.none ${.CURDIR}/linux/System.map
.endif
.ifdef DESTDIR
.if ${TARGET_OPENBLOCKS} == "none"
	${INSTALL} -c -m 644 -o root -g wheel ${.CURDIR}/linux/arch/${TARGET_HOSTTYPE}/boot/bzImage ${DESTDIR}/vmlinuz
	cp -p ${DESTDIR}/vmlinuz ${DESTDIR}/vmlinuz.${KERNEL_MAJOR}${KERNEL_MINOR}${KERNEL_PATCHLEVEL}
.endif
	${INSTALL} -c -m 644 -o root -g wheel ${.CURDIR}/linux/System.map ${DESTDIR}/System.map
	cp -p ${DESTDIR}/System.map ${DESTDIR}/System.map.${KERNEL_MAJOR}${KERNEL_MINOR}${KERNEL_PATCHLEVEL}
.endif

build_tools:
.if defined(NEW_GLIBC) && defined(DESTDIR)
	cd ${.CURDIR}/tools && ${MAKE} && ${MAKE} install
.endif

update_mk:
	cd ${.CURDIR}/share/mk && ${MAKE} -DUPDATE_MK install

clean:
.if !defined(NOCLEAN) || defined(FORCE_CLEAN)
	if [ -d ${.CURDIR}/linux ]; then \
		cd ${.CURDIR}/linux && ${GMAKE} distclean; \
	fi
	cd ${.CURDIR}/etc && ${MAKE} clean
	cd ${.CURDIR}/tools && ${MAKE} clean
	cd ${.CURDIR}/lib && ${MAKE} clean
	cd ${.CURDIR}/libexec && ${MAKE} clean
	cd ${.CURDIR}/share && ${MAKE} clean
	cd ${.CURDIR}/bin && ${MAKE} clean
	cd ${.CURDIR}/sbin && ${MAKE} clean
	cd ${.CURDIR}/usr.bin && ${MAKE} clean
	cd ${.CURDIR}/usr.sbin && ${MAKE} clean
	cd ${.CURDIR}/contrib && ${MAKE} clean
	cd ${.CURDIR}/cross && ${MAKE} clean
	cd ${.CURDIR}/distrib/utils && ${MAKE} clean
	cd ${.CURDIR}/distrib/${TARGET_SSDHOSTTYPEX} && ${MAKE} clean
.endif

cleandir:
.if !defined(NOCLEAN) || defined(FORCE_CLEAN)
	cd ${.CURDIR}/tools && ${MAKE} cleandir
	cd ${.CURDIR}/lib && ${MAKE} cleandir
	cd ${.CURDIR}/libexec && ${MAKE} cleandir
	cd ${.CURDIR}/share && ${MAKE} cleandir
	cd ${.CURDIR}/bin && ${MAKE} cleandir
	cd ${.CURDIR}/sbin && ${MAKE} cleandir
	cd ${.CURDIR}/usr.bin && ${MAKE} cleandir
	cd ${.CURDIR}/usr.sbin && ${MAKE} cleandir
	cd ${.CURDIR}/contrib && ${MAKE} cleandir
	cd ${.CURDIR}/cross && ${MAKE} cleandir
.endif

clean_dest:
.ifndef NOCLEAN
.ifdef DESTDIR
	rm -rf ${DESTDIR}
.endif
.endif

clean_release:
.ifndef NOCLEAN
.ifdef RELEASEDIR
	rm -rf ${RELEASEDIR}/${TARGET_SSDHOSTTYPE}
.endif
.endif

.if defined(DESTDIR) && defined(RELEASEDIR)
.ifdef SKIPBUILD
release: clean_dest clean_release build_tree install
	cd ${.CURDIR}/distrib && ${MAKE} release
.else
release: build_bin install
	cd ${.CURDIR}/distrib && ${MAKE} release
.endif
.else
release:
	@echo "Must be set DESTDIR and RELEASEDIR for 'make release'."
.endif

build_zImage:
.if !defined(CROSS_BUILD)
.if ${TARGET_SSDHOSTTYPEX} == "powerpc-obs2xx" || ${TARGET_SSDHOSTTYPEX} == "powerpc-obs50"
	cd ${.CURDIR}/distrib/utils && ${MAKE}
	cd ${.CURDIR}/distrib/${TARGET_SSDHOSTTYPEX} && ${MAKE}
.endif
.endif
