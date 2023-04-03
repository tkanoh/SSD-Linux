#	$ssdlinux: Makefile,v 1.20 2004/11/15 02:37:39 yamagata Exp $

.include <bsd.own.mk>

PROG=		cvs
CVSVERSION=	1.11.18
SRCS=		add.c admin.c annotate.c buffer.c checkin.c checkout.c \
		classify.c client.c commit.c create_adm.c cvsrc.c diff.c \
		edit.c entries.c error.c expand_path.c fileattr.c filesubr.c \
		find_names.c hardlink.c hash.c history.c ignore.c import.c \
		lock.c log.c login.c logmsg.c main.c mkmodules.c modules.c \
		myndbm.c no_diff.c parseinfo.c patch.c rcs.c rcscmds.c \
		recurse.c release.c remove.c repos.c root.c run.c scramble.c \
		server.c stack.c status.c subr.c \
		tag.c update.c version.c vers_ts.c \
		watch.c wrapper.c zlib.c
SCRIPTS=	cvsbug
CLEANFILES=	${SCRIPTS}
MAN=		${PROG}.1 ${PROG}.5 ${SCRIPTS}.8

DIST=		${.CURDIR}/../../../dist/${PROG}
.PATH:		${DIST}/src ${DIST}/man ${DIST}/doc

CPPFLAGS+=	-I${DIST}/src \
		-I${.CURDIR}/../ \
		-I${DIST} \
		-I${DIST}/lib \
		-I${DIST}/diff \
		-I${DIST}/zlib
CPPFLAGS+=	-DHAVE_CONFIG_H
.if ${IPV6} == "yes"
CPPFLAGS+=	-DENABLE_IPV6=1
.endif
.if defined(RCS_LOCALID)
CPPFLAGS+=	-DLOCALID=\"${RCS_LOCALID}\"
.endif

LDADD+=		-L${.CURDIR}/../lib -lcvs
LDADD+=		-L${.CURDIR}/../diff -ldiff
LDADD+=		-L${DIST}/../../lib/libz -lz -lcrypt
DPADD+=		-L${.CURDIR}/../lib/libcvs.a
DPADD+=		-L${.CURDIR}/../diff/libdiff.a

${SCRIPTS}:
	sed -e 's/@PACKAGE_BUGREPORT@/bug-cvs@gnu.org/' \
	    -e 's/@VERSION@/${CVSVERSION}/' \
	    -e 's,@MKTEMP_SH_FUNCTION@,,' \
	    -e 's,@MKTEMP@,/usr/bin/mktemp,' \
	    -e 's,@SENDMAIL@,/usr/sbin/sendmail,' \
		${DIST}/src/${.TARGET}.in > ${.TARGET}

.include <bsd.prog.mk>
