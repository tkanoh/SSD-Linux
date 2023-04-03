#	$ssdlinux: Makefile,v 1.7 2004/03/19 09:14:19 yamagata Exp $

.include <bsd.own.mk>

DISTNAME=	netatalk
CONFIGURE_FULL_PREFIX= 1
GNU_PREFIX=	/usr/contrib/${DISTNAME}
GNU_LIBDIR=	${GNU_PREFIX}/lib
GNU_MANDIR=	${GNU_PREFIX}/man
GNU_SYSCONFDIR=	${GNU_PREFIX}/etc
CONFIGURE_ENV=
CONFIGURE_OPTIONS= --with-shadow --with-tcp-wrappers \
		--with-pam=no --with-ssl-dir=no \
		--with-pkgconfdir=${GNU_PREFIX}/etc
GMAKE_ENV=
#NO_INSTALL=	yes
GMAKE_INSTALL_OPTIONS= DESTDIR=$(DESTDIR)
INSTALL_STRIP=  no
BINDIR=		${GNU_PREFIX}/bin
SBINDIR=	${GNU_PREFIX}/sbin
GNU_STRIP=	${BINDIR}/${TARGET_MACHTYPE}-achfile \
		${BINDIR}/${TARGET_MACHTYPE}-adv1tov2 \
		${BINDIR}/${TARGET_MACHTYPE}-aecho \
		${BINDIR}/${TARGET_MACHTYPE}-afile \
		${BINDIR}/${TARGET_MACHTYPE}-getzones \
		${BINDIR}/${TARGET_MACHTYPE}-makecode \
		${BINDIR}/${TARGET_MACHTYPE}-megatron \
		${BINDIR}/${TARGET_MACHTYPE}-nbplkup \
		${BINDIR}/${TARGET_MACHTYPE}-nbprgstr \
		${BINDIR}/${TARGET_MACHTYPE}-nbpunrgstr \
		${BINDIR}/${TARGET_MACHTYPE}-pap \
		${BINDIR}/${TARGET_MACHTYPE}-papstatus \
		${BINDIR}/${TARGET_MACHTYPE}-parsecode \
		${BINDIR}/${TARGET_MACHTYPE}-psorder \
		${BINDIR}/${TARGET_MACHTYPE}-test_parse_mtab \
		${BINDIR}/${TARGET_MACHTYPE}-timeout
GNU_STRIP+=	${SBINDIR}/${TARGET_MACHTYPE}-afpd \
		${SBINDIR}/${TARGET_MACHTYPE}-atalkd \
		${SBINDIR}/${TARGET_MACHTYPE}-papd \
		${SBINDIR}/${TARGET_MACHTYPE}-psa \
		${SBINDIR}/${TARGET_MACHTYPE}-psf

.include <bsd.gnu.mk>
