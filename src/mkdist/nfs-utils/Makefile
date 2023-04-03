#	$ssdlinux: Makefile,v 1.6 2004/12/20 03:56:50 yamagata Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	nfs-utils-
DISTVERSION=	1.0.7
MASTER_SITES=	http://keihanna.dl.sourceforge.net/sourceforge/nfs
DEPENDENT=	lib/nfs-utils usr.bin/nfsstat libexec/rpc.rquotad
DEPENDENT+=	usr.sbin/exportfs usr.sbin/mountd usr.sbin/nfsd
DEPENDENT+=	usr.sbin/rpc.lockd usr.sbin/rpc.statd

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
