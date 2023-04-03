#	$ssdlinux: bsd.depall.mk,v 1.1.1.1 2002/05/02 13:37:09 kanoh Exp $
#	$NetBSD: bsd.depall.mk,v 1.2 2000/01/22 19:31:01 mycroft Exp $

dependall: realdepend .MAKE
	@cd ${.CURDIR}; \
	${MAKE} realall
