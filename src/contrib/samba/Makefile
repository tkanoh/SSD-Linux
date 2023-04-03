#	$ssdlinux: Makefile,v 1.3 2004/03/19 05:39:37 yamagata Exp $

.include <bsd.own.mk>

DISTNAME=	samba
DISTDIR=	${.CURDIR}/../../dist/${DISTNAME}/source
ALT_VERSIONS_FILE_DIR=	 ${.CURDIR}/../../dist
GNU_PREFIX=	/usr/contrib/samba
CONFIGURE_ENV= CPPFLAGS=-I${.CURDIR}/build/include
CONFIGURE_OPTIONS= --with-i18n-swat
GMAKE_ENV=	
#NO_INSTALL=	yes
GMAKE_INSTALL_OPTIONS= DESTDIR=$(DESTDIR)
INSTALL_STRIP=  no
BINDIR=		${GNU_PREFIX}/bin
SBINDIR=	${GNU_PREFIX}/sbin
GNU_STRIP=	${BINDIR}/make_printerdef ${BINDIR}/make_smbcodepage \
		${BINDIR}/make_unicodemap ${BINDIR}/nmblookup ${BINDIR}/rpcclient \
		${BINDIR}/smbcacls ${BINDIR}/smbclient ${BINDIR}/smbcontrol \
		${BINDIR}/smbpasswd ${BINDIR}/smbspool ${BINDIR}/smbstatus \
		${BINDIR}/tdbbackup ${BINDIR}/testparm ${BINDIR}/testprns \
		${BINDIR}/wbinfo
GNU_STRIP+=	${SBINDIR}/nmbd ${SBINDIR}/smbd ${SBINDIR}/swat ${SBINDIR}/winbindd

.include <bsd.gnu.mk>
