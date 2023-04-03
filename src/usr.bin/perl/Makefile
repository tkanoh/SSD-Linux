#	$ssdlinux: Makefile,v 1.14 2003/01/10 02:46:35 kanoh Exp $

.include <bsd.own.mk>

DISTNAME=	perl
NO_COMPAT_CONFIGURE= 1
.if defined(CROSS_BUILD_PERL)
PERL_TARGET_USER?=	root
PERL_TARGET_DIR?=	/tmp
PERL_TARGET_RUN?=	ssh
PERL_TARGET_TO?=	scp
PERL_TARGET_FROM?=	scp
CONFIGURE= Configure -des -Dusecrosscompile -Dmksymlinks \
	-Darchname=${TARGET_HOSTTYPE}-linux \
	-Dtargethost=${PERL_TARGET_HOST} \
	-Dtargetdir=${PERL_TARGET_DIR} \
	-Dtargetuser=${PERL_TARGET_USER} \
	-Dtargetrun=${PERL_TARGET_RUN} \
	-Dtargetto=${PERL_TARGET_TO} \
	-Dtargetfrom=${PERL_TARGET_FROM} \
	-Dman1dir=${MANDIR}/man1 \
	-Dman3dir=${MANDIR}/man3 \
	-Dprefix=/usr \
	-Dinstallprefix=/usr \
	-Dinstallprefixexp=/usr \
	-Dcc=${TARGET_MACHTYPE}-gcc \
	-Dusrinc=/usr/cross/${TARGET_HOSTTYPE}/include \
	-Dincpth=/usr/cross/${TARGET_HOSTTYPE}/include \
	-Dusrinc=/usr/cross/${TARGET_HOSTTYPE}/lib
.else
CONFIGURE= Configure -des -Dmksymlinks \
	-Darchname=${TARGET_HOSTTYPE}-linux \
	-Dman1dir=${MANDIR}/man1 \
	-Dman3dir=${MANDIR}/man3 \
	-Dprefix=/usr \
	-Dinstallprefix=/usr \
	-Dinstallprefixexp=/usr
.endif
CONFIGURE_ENV=
CONFIGURE_OPTIONS=
GMAKE_ENV=
GMAKE_OPTIONS=
GMAKE_INSTALL_OPTIONS= DESTDIR=${DESTDIR}
.if ${TARGET_HOSTTYPE} != "powerpc"
DO_MAKE_TEST= 1
.endif

.include <bsd.gnu.mk>
