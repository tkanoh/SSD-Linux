#	$ssdlinux: Makefile.inc,v 1.1 2004/11/11 17:13:56 kanoh Exp $
#	$NetBSD: Makefile.inc,v 1.5 1996/05/03 21:38:43 cgd Exp $
#       @(#)Makefile.inc	8.1 (Berkeley) 6/4/93

.PATH: ${.CURDIR}/recno

SRCS+=	rec_close.c rec_delete.c rec_get.c rec_open.c rec_put.c rec_search.c \
	rec_seq.c rec_utils.c
