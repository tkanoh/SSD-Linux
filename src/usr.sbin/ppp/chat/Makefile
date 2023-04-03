#	$ssdlinux: Makefile,v 1.3 2004/11/15 06:01:25 yamagata Exp $

.include <bsd.own.mk>

PROG=		chat
MAN=		${PROG}.8

CPPFLAGS+=	-pipe -DTERMIOS -DSIGTYPE=void -UNO_SLEEP -DFNDELAY=O_NDELAY

.include <bsd.prog.mk>
