#	$ssdlinux: Makefile,v 1.2 2004/12/14 04:25:58 todoroki Exp $

.include <bsd.own.mk>
.include "../Makefile.inc"

CONTRIBS=	samba netatalk
CONTRIBS_INSTALL= netatalk
LIST_S=		common flashcfg sh useradd httpd ${CONTRIBS}
MTREE_CONF_S=	${LIST_S} dhcpd named sendmail 

REQUIREMENT=	(cd ${SRCTOPDIR}/distrib/utils/x_ls && bmake)

.include "${.CURDIR}/../../standard/initrd/Makefile.inc"
