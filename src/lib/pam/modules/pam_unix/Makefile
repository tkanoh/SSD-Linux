#	$ssdlinux: Makefile,v 1.5 2004/11/24 01:15:14 yamagata Exp $

.include <bsd.own.mk>
.include "${.CURDIR}/../Makefile.inc"

MODULE=		pam_unix
MODULESOBJ=	pam_unix_auth.o pam_unix_acct.o pam_unix_sess.o pam_unix_passwd.o \
		support.o yppasswd_xdr.o bigcrypt.o
MD5OBJ=		md5_good.o md5_broken.o md5_crypt_good.o md5_crypt_broken.o

ALTMKSCRIPTS=	yes

.include "${.CURDIR}/../Makefile.cflags"

CPPFLAGS+=	-D"USE_LCKPWDF" -DCHKPWD_HELPER=\"/sbin/unix_chkpwd\"

${SCRIPTS}: ${MODULESOBJ} ${MD5OBJ}
.ifdef DESTDIR
	${CC} -shared -Xlinker -x -o ${.TARGET} ${MODULESOBJ} ${MD5OBJ} -nostdlib \
	-L${DESTDIR}${LIBDIR} -lnsl -lcrypt
.else
	${CC} -shared -Xlinker -x -o ${.TARGET} ${MODULESOBJ} ${MD5OBJ} -lnsl -lcrypt
.endif

${MODULESOBJ}: ${.TARGET:M*.o:.o=.c}
	${CC} ${CPPFLAGS} -c ${MSRCDIR}/${MODULEDIR}/${.TARGET:M*.o:.o=.c} -o ${.TARGET}

md5_good.o: md5.c
	${CC} ${CPPFLAGS} -DHIGHFIRST -D'MD5Name(x)=Good##x' -c ${MSRCDIR}/${MODULEDIR}/md5.c -o ${.TARGET}

md5_broken.o: md5.c
	${CC} ${CPPFLAGS} -D'MD5Name(x)=Broken##x' -c ${MSRCDIR}/${MODULEDIR}/md5.c -o ${.TARGET}

md5_crypt_good.o: md5_crypt.c
	${CC} ${CPPFLAGS} -D'MD5Name(x)=Good##x' -c ${MSRCDIR}/${MODULEDIR}/md5_crypt.c -o ${.TARGET}

md5_crypt_broken.o: md5_crypt.c
	${CC} ${CPPFLAGS} -D'MD5Name(x)=Broken##x' -c ${MSRCDIR}/${MODULEDIR}/md5_crypt.c -o ${.TARGET}

.include <bsd.prog.mk>
