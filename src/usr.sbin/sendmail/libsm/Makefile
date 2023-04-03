#	$ssdlinux: Makefile,v 1.4 2004/12/16 06:24:58 yamagata Exp $

.include <bsd.own.mk>

LIB=		sm
SRCS=		assert.c debug.c errstring.c exc.c heap.c match.c \
		rpool.c strdup.c strerror.c strl.c clrerr.c fclose.c \
		feof.c ferror.c fflush.c fget.c fpos.c findfp.c \
		flags.c fopen.c fprintf.c fpurge.c fput.c fread.c \
		fscanf.c fseek.c fvwrite.c fwalk.c fwrite.c get.c \
		makebuf.c put.c refill.c rewind.c setvbuf.c smstdio.c \
		snprintf.c sscanf.c stdio.c strio.c ungetc.c vasprintf.c \
		vfprintf.c vfscanf.c vprintf.c vsnprintf.c \
		wbuf.c wsetup.c string.c stringf.c xtrap.c \
		strto.c test.c path.c strcasecmp.c strrevcmp.c signal.c \
		clock.c config.c shm.c mbdb.c strexit.c cf.c ldap.c niprop.c \
		mpeix.c
CLEANFILES=	${.CURDIR}/../include/sm_os.h

DIST=		${.CURDIR}/../../../dist/sendmail
.PATH:		${DIST}/lib${LIB}

assert.c: sm_os.h

sm_os.h:
	rm -f ${.CURDIR}/../include/${.TARGET}
	cp ${DIST}/include/sm/os/sm_os_linux.h ${.CURDIR}/../include/${.TARGET}

libinstall::

.include <bsd.lib.mk>
