#	$ssdlinux: Makefile,v 1.7 2004/10/20 06:49:39 yamagata Exp $

.include <bsd.own.mk>

LIB=		ntp
SRCS=	a_md5encrypt.c adjtime.c atoint.c atolfp.c atouint.c \
	audio.c authencrypt.c authkeys.c authparity.c authreadkeys.c \
	authusekey.c binio.c buftvtots.c caljulian.c calleapwhen.c caltontp.c \
	calyearstart.c clocktime.c clocktypes.c decodenetnum.c dofptoa.c \
	dolfptoa.c emalloc.c findconfig.c fptoa.c fptoms.c getopt.c \
	gpstolfp.c hextoint.c hextolfp.c humandate.c icom.c ieee754io.c \
	inttoa.c iosignal.c lib_strbuf.c machines.c md5c.c memmove.c \
	mfptoa.c mfptoms.c mktime.c modetoa.c mstolfp.c msutotsf.c \
	msyslog.c netof.c numtoa.c numtohost.c octtoint.c prettydate.c \
	ranny.c recvbuff.c refnumtoa.c snprintf.c statestr.c strdup.c \
	strerror.c syssignal.c systime.c tsftomsu.c tstotv.c tvtoa.c tvtots.c \
	uglydate.c uinttoa.c utvtoa.c ymd2yd.c

DIST=		${.CURDIR}/../../../dist/ntp
.PATH:		${DIST}/libntp

CPPFLAGS+=	-I${DIST}/libntp

libinstall::

NOGCCERROR=	yes

.include <bsd.lib.mk>
