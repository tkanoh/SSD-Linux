#	$ssdlinux: list2sh.awk,v 1.2 2003/04/08 06:39:10 kanoh Exp $
#	$NetBSD: list2sh.awk,v 1.5 1996/10/09 00:13:38 jtc Exp $

BEGIN {
	printf("cd ${CURDIR}\n");
	printf("\n");
}
/^$/ || /^#/ {
	print $0;
	next;
}
$1 == "COPY" {
	printf("echo '%s'\n", $0);
	printf("rm -f ${TARGDIR}/%s\n", $3);
	printf("cp %s ${TARGDIR}/%s\n", $2, $3);
	next;
}
$1 == "SCOPY" {
	printf("echo '%s'\n", $0);
	printf("rm -f ${TARGDIR}/%s\n", $3);
	printf("cp %s ${TARGDIR}/%s\n", $2, $3);
	printf("chmod 555 ${TARGDIR}/%s\n", $3);
	next;
}
$1 == "BCOPY" {
	printf("echo '%s'\n", $0);
	printf("cp %s ${TMPDIR}/`basename %s`\n", $2, $2);
	printf("chmod 555 ${TMPDIR}/`basename %s`\n", $2);
	printf("${STRIPBIN} ${TMPDIR}/`basename %s`\n", $2);
	printf("rm -f ${TARGDIR}/%s\n", $3);
	printf("cp -p ${TMPDIR}/`basename %s` ${TARGDIR}/%s\n", $2, $3);
	printf("rm -f  ${TMPDIR}/`basename %s`\n", $2);
	next;
}
$1 == "ECOPY" {
	printf("echo %s\n", $0);
	printf("rm -f ${TARGDIR}/%s\n", $4);
	printf("cp -f %s ${TARGDIR}/%s\n", $3, $4);
	printf("if [ -f ${COMMON_ETCDIR}/`basename %s` ]; then cp -f ${COMMON_ETCDIR}/`basename %s` ${TARGDIR}/%s;fi\n", $4, $4, $4);
	printf("if [ -f ${CURDIR}/etc/`basename %s` ]; then cp -f ${CURDIR}/etc/`basename %s` ${TARGDIR}/%s;fi\n", $4, $4, $4);
	printf("chmod %s ${TARGDIR}/%s\n",$2, $4);
	next;
}
$1 == "LINK" {
	printf("echo '%s'\n", $0);
	printf("rm -f ${TARGDIR}/%s\n", $3);
	printf("(cd ${TARGDIR}; ln %s %s)\n", $2, $3);
	next;
}
$1 == "SYMLINK" {
	printf("echo '%s'\n", $0);
	printf("rm -f ${TARGDIR}/%s\n", $3);
	printf("(cd ${TARGDIR}; ln -s %s %s)\n", $2, $3);
	next;
}
$1 == "COPYDIR" {
	printf("echo '%s'\n", $0);
	printf("(cd ${TARGDIR}/%s && find . ! -name . | xargs /bin/rm -rf)\n",
	    $3);
	printf("(cd %s && find . ! -name . | cpio -pdamu ${TARGDIR}/%s)\n", $2,
	    $3);
	next;
}
$1 == "SPECIAL" {
	printf("echo '%s'\n", $0);
	printf("(cd ${TARGDIR};");
	for (i = 2; i <= NF; i++)
		printf(" %s", $i);
	printf(")\n");
	next;
}
{
	printf("echo '%s'\n", $0);
	printf("echo 'Unknown keyword \"%s\" at line %d of input.'\n", $1, NR);
	printf("exit 1\n");
	exit 1;
}
END {
	printf("\n");
	printf("exit 0\n");
	exit 0;
}
