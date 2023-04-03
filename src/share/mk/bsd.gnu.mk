#	$ssdlinux: bsd.gnu.mk,v 1.64 2003/12/03 08:08:41 kanoh Exp $

.if !defined(_BSD_GNU_MK_)
_BSD_GNU_MK_=1

.if !target(__initialized__)
__initialized__:
.if exists(${.CURDIR}/../Makefile.inc)
.include "${.CURDIR}/../Makefile.inc"
.endif
.include <bsd.own.mk>
.include <bsd.obj.mk>
.include <bsd.depall.mk>

.if defined(TOOLCHAIN) || defined(TOOLS_GLIBC)
.undef DESTDIR
.endif

.if defined(CROSS_BUILD)
.if !defined(CROSS_LIB)
GNU_HOST=	${TARGET_MACHTYPE}
.endif
.if ${DISTNAME} != "gcc"
CONFIGURE_ENV+=  AR=${TARGET_MACHTYPE}-ar
CONFIGURE_ENV+=  AS=${TARGET_MACHTYPE}-as
CONFIGURE_ENV+=  LD=${TARGET_MACHTYPE}-ld
CONFIGURE_ENV+=  NM=${TARGET_MACHTYPE}-nm
CONFIGURE_ENV+=	 RANLIB=${TARGET_MACHTYPE}-ranlib 
CONFIGURE_ENV+=  CXX=${TARGET_MACHTYPE}-c++
CONFIGURE_ENV+=  SIZE=${TARGET_MACHTYPE}-size
CONFIGURE_ENV+=  CC=${TARGET_MACHTYPE}-gcc
CONFIGURE_ENV+=  CC_FOR_BUILD=gcc
CONFIGURE_ENV+=  CXX_FOR_BUILD=c++
CONFIGURE_ENV+=  BUILD_CC=gcc
GMAKE_OPTIONS+=	 CC_FOR_BUILD=gcc
GMAKE_OPTIONS+=	 CXX_FOR_BUILD=cc++
GMAKE_INSTALL_OPTIONS+= CC_FOR_BUILD=gcc
.endif
CONFIGURE_ENV+=	 STRIP=${TARGET_MACHTYPE}-strip 
CONFIGURE_ENV+=	 INSTALL=/usr/cross/${TARGET_HOSTTYPE}/bin/${TARGET_MACHTYPE}-install
GMAKE_INSTALL_OPTIONS+= STRIP=${TARGET_MACHTYPE}-strip
GMAKE_INSTALL_OPTIONS+= INSTALL=${TARGET_MACHTYPE}-install
STRIP?= ${TARGET_MACHTYPE}-strip
.else
CC?=    gcc
STRIP?= strip
.endif

.if defined(NEW_GLIBC) && !defined(TOOLCHAIN)
.if !defined(TOOLS_GLIBC)
GNU_HOST=	${TARGET_MACHTYPE}${NEW_GLIBC}
.endif
CONFIGURE_ENV+=  AR=${TARGET_MACHTYPE}${NEW_GLIBC}-ar
CONFIGURE_ENV+=  AS=${TARGET_MACHTYPE}${NEW_GLIBC}-as
CONFIGURE_ENV+=  LD=${TARGET_MACHTYPE}${NEW_GLIBC}-ld
CONFIGURE_ENV+=  NM=${TARGET_MACHTYPE}${NEW_GLIBC}-nm
CONFIGURE_ENV+=	 RANLIB=${TARGET_MACHTYPE}${NEW_GLIBC}-ranlib 
CONFIGURE_ENV+=	 STRIP=${TARGET_MACHTYPE}${NEW_GLIBC}-strip 
CONFIGURE_ENV+=  CXX=${TARGET_MACHTYPE}${NEW_GLIBC}-c++
CONFIGURE_ENV+=  SIZE=${TARGET_MACHTYPE}${NEW_GLIBC}-size
CONFIGURE_ENV+=  CC=${TARGET_MACHTYPE}${NEW_GLIBC}-gcc
CONFIGURE_ENV+=  CC_FOR_BUILD=gcc
CONFIGURE_ENV+=  BUILD_CC=gcc
GMAKE_OPTIONS+=	 CC_FOR_BUILD=gcc
GMAKE_INSTALL_OPTIONS+= CC_FOR_BUILD=gcc
STRIP?= ${TARGET_MACHTYPE}${NEW_GLIBC}-strip
.if ${DISTNAME} != "binutils" && ${DISTNAME} != "m4"
GNU_EXEC_PREFIX= ${TOOLCHAINDIR}
.endif
.else
CC?=    gcc
STRIP?= strip
.endif

.MAIN:	all
.endif

.PHONY:		gnuclean gnuinstall gnubuild configure configure-help
all:		configure gnubuild
bootstrap:	configure gnubootstrap
realinstall:	gnuinstall
clean cleandir: gnuclean

GMAKE?=		make

DISTDIR?=	../../../dist/$(DISTNAME)
CONFIGURE?=	configure
BUILDDIR=	${.CURDIR}/build

INSTALL_STRIP?=	yes

.if defined(NO_COMPAT_CONFIGURE)
GNU_PREFIXS=
.else
GNU_PREFIX?=		/usr
BINDIR?=		$(GNU_PREFIX)/bin		
GNU_HOST?=		$(TARGET_MACHTYPE)
GNU_TARGET?=		$(GNU_HOST)
.if ${MKNLS} == "no" | defined(NONLS)
GNU_NLS=		--disable-nls
.endif
.if defined(CONFIGURE_FULL_PREFIX)
GNU_EXEC_PREFIX?=	$(GNU_PREFIX) 
GNU_BINDIR?=		${BINDIR:S/\/sbin/\/bin/}
GNU_SBINDIR?=		${BINDIR:S/\/bin/\/sbin/}
GNU_LIBEXECDIR?=	$(GNU_PREFIX)/libexec
GNU_DATADIR?=		$(GNU_PREFIX)/share
GNU_SYSCONFDIR?=	/etc
GNU_SHAREDSTATEDIR?=	$(GNU_PREFIX)/com 
GNU_LOCALSTATEDIR?=	/var
GNU_LIBDIR?=		$(LIBDIR)
GNU_INCLUDEDIR?=	$(GNU_PREFIX)/include
GNU_OLDINCLUDEDIR?=	/usr/include
GNU_INFODIR?=		$(INFODIR)
GNU_MANDIR?=		$(MANDIR)
GNU_TARGET?=		$(TARGET_MACHTYPE)
GNU_HOST?=		$(TARGET_MACHTYPE)
.if ${MKCATPAGES} == "no" | defined(NOMAN)
GNU_CATPAGES?=		no
.endif
.if ${MKNLS} == "no" | defined(NONLS)
GNU_INC_GETTEXT?=	no
.endif
GNU_PREFIXS=	--prefix=$(GNU_PREFIX) \
		--exec-prefix=$(GNU_EXEC_PREFIX) --bindir=$(GNU_BINDIR) \
		--sbindir=$(GNU_SBINDIR) --libexecdir=$(GNU_LIBEXECDIR) \
		--datadir=$(GNU_DATADIR) --sysconfdir=$(GNU_SYSCONFDIR) \
		--sharedstatedir=$(GNU_SHAREDSTATEDIR) \
		--localstatedir=$(GNU_LOCALSTATEDIR) \
		--libdir=$(GNU_LIBDIR) --includedir=$(GNU_INCLUDEDIR) \
		--oldincludedir=$(GNU_OLDINCLUDEDIR) \
		--infodir=$(GNU_INFODIR) --mandir=$(GNU_MANDIR) \
		--with-catgets=$(GNU_CATPAGES) \
		--with-included-gettext=$(GNU_INC_GETTEXT)
.if defined(GNU_WITH_HEADER)
GNU_PREFIXS+=		--with-headers=$(GNU_WITH_HEADER)
.endif
.if defined(GNU_WITH_LIBS)
GNU_PREFIXS+=		--with-libs=$(GNU_WITH_LIBS)
.endif
.else
GNU_PREFIXS=	--prefix=$(GNU_PREFIX)
.if defined(GNU_EXEC_PREFIX)
GNU_PREFIXS+=	--exec-prefix=$(GNU_EXEC_PREFIX) 
.endif
.if defined(GNU_BINDIR)
GNU_PREFIXS+=	--bindir=$(GNU_BINDIR)
.endif
.if defined(GNU_SBINDIR)
GNU_PREFIXS+=	--sbindir=$(GNU_SBINDIR)
.endif
.if defined(GNU_LIBEXECDIR)
GNU_PREFIXS+=	--libexecdir=$(GNU_LIBEXECDIR)
.endif
.if defined(GNU_DATADIR)
GNU_PREFIXS+=	--datadir=$(GNU_DATADIR)
.endif
.if defined(GNU_SYSCONFDIR)
GNU_PREFIXS+=	--sysconfdir=$(GNU_SYSCONFDIR)
.endif
.if defined(GNU_SHAREDSTATEDIR)
GNU_PREFIXS+=	--sharedstatedir=$(GNU_SHAREDSTATEDIR)
.endif
.if defined(GNU_LOCALSTATEDIR)
GNU_PREFIXS+=	--localstatedir=$(GNU_LOCALSTATEDIR)
.endif
.if defined(GNU_LIBDIR)
GNU_PREFIXS+=	--libdir=$(GNU_LIBDIR)
.endif
.if defined(GNU_INCLUDEDIR)
GNU_PREFIXS+=	--includedir=$(GNU_INCLUDEDIR)
.endif
.if defined(GNU_OLDINCLUDEDIR)
GNU_PREFIXS+=	--oldincludedir=$(GNU_OLDINCLUDEDIR)
.endif
.if defined(GNU_INFODIR)
GNU_PREFIXS+=	--infodir=$(GNU_INFODIR)
.endif
.if defined(GNU_MANDIR)
GNU_PREFIXS+=	--mandir=$(GNU_MANDIR)
.endif
.if defined(GNU_CATPAGES)
GNU_PREFIXS+= --with-catgets=$(GNU_CATPAGES)
.endif
.if defined(GNU_INC_GETTEXT)
GNU_PREFIXS+= --with-included-gettext=$(GNU_INC_GETTEXT)
.endif 
.endif # defined(CONFIGURE_FULL_PREFIX)
.if !defined(NO_GNU_TARGET)
GNU_PREFIXS+=	--target=$(GNU_TARGET)
.endif
.if !defined(NO_GNU_HOST)
GNU_PREFIXS+=	--host=$(GNU_HOST)
.endif
.endif # defined(NO_COMPAT_CONFIGURE)

.if defined(LDSTATIC)
CONFIGURE_ENV+= LDFLAGS="$(LDSTATIC) -s"
.endif

.if !defined(HAVE_DESTDIR)
.if !defined(NO_COMPAT_CONFIGURE)
INST_GNU_PREFIX?=		$(GNU_PREFIX)
.if defined(GNU_EXEC_PREFIX)
INST_GNU_EXEC_PREFIX?=		$(GNU_EXEC_PREFIX)
.else
INST_GNU_EXEC_PREFIX?=		$(GNU_PREFIX)
.endif
.if defined(GNU_BINDIR)
INST_GNU_BINDIR?=		$(GNU_BINDIR)
.else
INST_GNU_BINDIR?=		${BINDIR:S/\/sbin/\/bin/}
.endif
.if defined(GNU_SBINDIR)
INST_GNU_SBINDIR?=		$(GNU_SBINDIR)
.else
INST_GNU_SBINDIR?=		${BINDIR:S/\/bin/\/sbin/}
.endif
.if defined(GNU_LIBEXECDIR)
INST_GNU_LIBEXECDIR?=		$(GNU_LIBEXECDIR)
.else
INST_GNU_LIBEXECDIR?=		$(GNU_PREFIX)/libexec
.endif
.if defined(GNU_DATADIR)
INST_GNU_DATADIR?=		$(GNU_DATADIR)
.else
INST_GNU_DATADIR?=		$(GNU_PREFIX)/share
.endif
.if defined(GNU_SYSCONFDIR)
INST_GNU_SYSCONFDIR?=		$(GNU_SYSCONFDIR)
.else
INST_GNU_SYSCONFDIR?=		/etc
.endif
.if defined(GNU_SHAREDSTATEDIR)
INST_GNU_SHAREDSTATEDIR?=	$(GNU_SHAREDSTATEDIR)
.else
INST_GNU_SHAREDSTATEDIR?=	$(GNU_PREFIX)/com 
.endif
.if defined(GNU_LOCALSTATEDIR)
INST_GNU_LOCALSTATEDIR?=	$(GNU_LOCALSTATEDIR)
.else
INST_GNU_LOCALSTATEDIR?=	/var
.endif
.if defined(GNU_LIBDIR)
INST_GNU_LIBDIR?=		$(GNU_LIBDIR)
.else
INST_GNU_LIBDIR?=		$(LIBDIR)
.endif
.if defined(GNU_INCLUDEDIR)
INST_GNU_INCLUDEDIR?=		$(GNU_INCLUDEDIR)
.else
INST_GNU_INCLUDEDIR?=		$(GNU_PREFIX)/include
.endif
.if defined(GNU_OLDINCLUDEDIR)
INST_GNU_OLDINCLUDEDIR?=	$(GNU_OLDINCLUDEDIR)
.else
INST_GNU_OLDINCLUDEDIR?=	/usr/include
.endif
.if defined(GNU_INFODIR)
INST_GNU_INFODIR?=		$(GNU_INFODIR)
.else
INST_GNU_INFODIR?=		$(INFODIR)
.endif
.if defined(GNU_MANDIR)
INST_GNU_MANDIR?=		$(GNU_MANDIR)
.else
INST_GNU_MANDIR?=		$(MANDIR)
.endif
INST_GNU_GETTEXTSRCDIR?=	$(GNU_PREFIX)/share/gettext/intl
GMAKE_INSTALL_PREFIX+=	prefix=$(DESTDIR)$(INST_GNU_PREFIX) \
		exec-prefix=$(DESTDIR)$(INST_GNU_EXEC_PREFIX) bindir=$(DESTDIR)$(INST_GNU_BINDIR) \
		sbindir=$(DESTDIR)$(INST_GNU_SBINDIR) libexecdir=$(DESTDIR)$(INST_GNU_LIBEXECDIR) \
		datadir=$(DESTDIR)$(INST_GNU_DATADIR) sysconfdir=$(DESTDIR)$(INST_GNU_SYSCONFDIR) \
		sharedstatedir=$(DESTDIR)$(INST_GNU_SHAREDSTATEDIR) \
		localstatedir=$(DESTDIR)$(INST_GNU_LOCALSTATEDIR) \
		libdir=$(DESTDIR)$(INST_GNU_LIBDIR) includedir=$(DESTDIR)$(INST_GNU_INCLUDEDIR) \
		oldincludedir=$(DESTDIR)$(INST_GNU_OLDINCLUDEDIR) \
		infodir=$(DESTDIR)$(INST_GNU_INFODIR) mandir=$(DESTDIR)$(INST_GNU_MANDIR) \
		gettextsrcdir=$(DESTDIR)$(INST_GNU_GETTEXTSRCDIR)
.endif # !defined(NO_COMPAT_CONFIGURE)
.endif # !defined(HAVE_DESTDIR)

.if exists($(BUILD_VERSION_FILE)) && exists($(BUILDDIR))
BUILD_VERSION!= cat $(BUILD_VERSION_FILE)
.if defined(ALT_VERSIONS_FILE_DIR)
BUILD_EQ_DIST!= grep -c "$(BUILD_VERSION)$$" $(ALT_VERSIONS_FILE_DIR)/$(VERSIONS_FILE_NAME) || true
.else 
BUILD_EQ_DIST!= cd $(BUILDDIR) && grep -c "$(BUILD_VERSION)$$" $(DISTDIR)/../$(VERSIONS_FILE_NAME) || true
.endif
.else
BUILD_EQ_DIST= 0
.endif

.if defined(ALT_DISTNAME)
_DISTNAME=$(ALT_DISTNAME)
.else
_DISTNAME= $(DISTNAME)
.endif

depend:
	cd $(BUILDDIR) && $(GMAKE) depend

gnubootstrap:
	cd $(BUILDDIR) && $(GMAKE_ENV) $(GMAKE) $(GMAKE_OPTIONS) bootstrap

gnubuild:
	cd $(BUILDDIR) && $(GMAKE_ENV) $(GMAKE) $(GMAKE_OPTIONS)
.if defined(DO_MAKE_TEST)
	cd $(BUILDDIR) && $(GMAKE_ENV) $(GMAKE) -i test
.endif
.if defined(POSTBUILD_SCRIPT)
	$(POSTBUILD_SCRIPT)
.endif

configure:
.if exists($(BUILDDIR)/Makefile)
.if ${BUILD_EQ_DIST} == "0"
	@echo delete old build directory
	rm -rf $(BUILDDIR) $(BUILD_VERSION_FILE)
	if [ ! -d $(BUILDDIR) ] ; then \
		mkdir $(BUILDDIR); \
	fi
	cd $(BUILDDIR) && \
	$(CONFIGURE_ENV) $(DISTDIR)/$(CONFIGURE) \
	$(GNU_PREFIXS) $(GNU_NLS) $(CONFIGURE_OPTIONS)
.if defined(ALT_VERSIONS_FILE_DIR)
	grep "$(_DISTNAME) " $(ALT_VERSIONS_FILE_DIR)/$(VERSIONS_FILE_NAME) > $(.CURDIR)/$(BUILD_VERSION_FILE)
.else
	cd $(BUILDDIR) && \
	grep "$(_DISTNAME) " $(DISTDIR)/../$(VERSIONS_FILE_NAME) > $(.CURDIR)/$(BUILD_VERSION_FILE)
.endif
.else
	@echo configure alreay done.
.endif
.else
	if [ ! -d $(BUILDDIR) ] ; then \
		mkdir $(BUILDDIR); \
	fi
	cd $(BUILDDIR) && \
	$(CONFIGURE_ENV) $(DISTDIR)/$(CONFIGURE) \
	$(GNU_PREFIXS) $(GNU_NLS) $(CONFIGURE_OPTIONS)
.if defined(ALT_VERSIONS_FILE_DIR)
	grep "$(_DISTNAME) " $(ALT_VERSIONS_FILE_DIR)/$(VERSIONS_FILE_NAME) > $(.CURDIR)/$(BUILD_VERSION_FILE)
.else
	cd $(BUILDDIR) && \
	grep "$(DISTNAME) " $(DISTDIR)/../$(VERSIONS_FILE_NAME) > $(.CURDIR)/$(BUILD_VERSION_FILE)
.endif
.endif

configure-help:
	if [ ! -d $(BUILDDIR) ] ; then \
		mkdir $(BUILDDIR); \
	fi
	cd $(BUILDDIR) && $(DISTDIR)/$(CONFIGURE) --help

gnuinstall:
.if !defined(NO_INSTALL)
.if defined(GMAKE_INSTALL_PART)
	cd $(BUILDDIR) && $(GMAKE) $(GMAKE_INSTALL_OPTIONS) $(GMAKE_INSTALL_PREFIX) $(GMAKE_INSTALL_PART)
.else
.if ${INSTALL_STRIP} != "no"
	cd $(BUILDDIR) && $(GMAKE) $(GMAKE_INSTALL_OPTIONS) $(GMAKE_INSTALL_PREFIX) install-strip
.else 
	cd $(BUILDDIR) && $(GMAKE) $(GMAKE_INSTALL_OPTIONS) $(GMAKE_INSTALL_PREFIX) install
.endif
.endif
.if defined(GNU_STRIP)
	@(set ${GNU_STRIP}; \
	while test $$# -ge 1; do \
		${STRIP} ${DESTDIR}$$1; \
		echo "strip ${DESTDIR}$$1"; \
		shift; \
	done; )
.endif
.if defined(SYMLINKS) && !empty(SYMLINKS)
	@(set ${SYMLINKS}; \
	 while test $$# -ge 2; do \
		l=$$1; \
		shift; \
		t=${DESTDIR}$$1; \
		shift; \
		if [ -h $$t ]; then \
			cur=`ls -ld $$t | awk '{print $$NF}'` ; \
			if [ "$$cur" = "$$l" ]; then \
				continue ; \
			fi; \
		fi; \
		echo "$$t -> $$l"; \
		rm -rf $$t; ln -s $$l $$t; \
	 done; )
.endif
.if defined(LINKS) && !empty(LINKS)
	@(set ${LINKS}; \
	 echo ".include <bsd.own.mk>"; \
	 while test $$# -ge 2; do \
		l=${DESTDIR}$$1; \
		shift; \
		t=${DESTDIR}$$1; \
		shift; \
		echo "realall: $$t"; \
		echo ".PHONY: $$t"; \
		echo "$$t:"; \
		echo "	@echo \"$$t -> $$l\""; \
		echo "	@rm -f $$t; ln $$l $$t"; \
	 done; \
	) | ${MAKE} -f- all
.endif
.if defined(POSTINSTALL_SCRIPT)
	$(POSTINSTALL_SCRIPT)
.endif
.endif

gnuclean:
	rm -rf $(BUILDDIR)
	rm -f $(BUILD_VERSION_FILE)

.endif

regress:
