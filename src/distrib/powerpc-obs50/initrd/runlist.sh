#	$ssdlinux: runlist.sh,v 1.1 2003/04/07 06:45:45 kanoh Exp $
#	$NetBSD: runlist.sh,v 1.2 1996/10/09 00:13:39 jtc Exp $

if [ "X$1" = "X-d" ]; then
	SHELLCMD=cat
	shift
else
	SHELLCMD="sh -e"
fi

( while [ "X$1" != "X" ]; do
	cat $1
	shift
done ) | awk -f ../initrd/list2sh.awk | ${SHELLCMD}
