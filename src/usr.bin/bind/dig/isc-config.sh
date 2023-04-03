#!/bin/sh
#	$ssdlinux: isc-config.sh,v 1.3 2005/03/14 03:45:47 yamagata Exp $
#
# Copyright (C) 2000, 2001  Internet Software Consortium.
#
# Permission to use, copy, modify, and distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND INTERNET SOFTWARE CONSORTIUM
# DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL
# INTERNET SOFTWARE CONSORTIUM BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING
# FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
# NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
# WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

# Id: isc-config.sh.in,v 1.10.2.1 2004/03/09 06:09:08 marka Exp $

prefix=/usr
exec_prefix=${prefix}
exec_prefix_set=

usage()
{
	cat << EOF
Usage: isc-config [OPTIONS] [LIBRARIES]
Options:
	[--prefix[=DIR]]
	[--exec-prefix[=DIR]]
	[--version]
	[--libs]
	[--cflags]
Libraries:
	isc
	isccc
	isccfg
	dns
	lwres
EOF
	exit $1
}

if test $# -eq 0; then
	usage 1 1>&2
fi

while test $# -gt 0; do
	case "$1" in
	-*=*) optarg=`echo "$1" | sed 's/[-_a-zA-Z0-9]*=//'` ;;
	*) optarg= ;;
	esac

	case "$1" in
	--prefix=*)
		prefix=$optarg
		if test "x$exec_prefix_set" = x ; then
			exec_prefix=$prefix
		fi
		;;
	--prefix)
		echo_prefix=true
		;;
	--exec-prefix=*)
		exec_prefix=$optarg
		;;
	--exec-prefix)
		echo_exec_prefix=true
		;;
	--version)
		echo VERSION=9.2.5
		exit 0
		;;
	--cflags)
		echo_cflags=true
		;;
	--libs)
		echo_libs=true;
		;;
	isc)
		libisc=true;
		;;
	isccc)
		libisccc=true;
		libisc=true;
		;;
	isccfg)
		libisccfg=true;
		libisc=true;
		;;
	dns)
		libdns=true;
		libisc=true;
		;;
	lwres)
		liblwres=true;
		;;
	*)
		usage 1 1>&2
	esac
	shift
done

if test x"$echo_prefix" = x"true" ; then
	echo $prefix
fi
if test x"$echo_exec_prefix" = x"true" ; then
	echo $exec_prefix
fi
if test x"$echo_cflags" = x"true"; then
	includes="-I${exec_prefix}/include"
	if test x"$libisc" = x"true"; then
		includes="$includes    "
	fi
	echo $includes
fi
if test x"$echo_libs" = x"true"; then
	libs=-L${exec_prefix}/lib
	if test x"$liblwres" = x"true" ; then
		libs="$libs -llwres"
	fi
	if test x"$libdns" = x"true" ; then
		libs="$libs -ldns -L/usr/lib -lcrypto"
	fi
	if test x"$libisccfg" = x"true" ; then
		libs="$libs -lisccfg"
	fi
	if test x"$libisccc" = x"true" ; then
		libs="$libs -lisccc"
	fi
	if test x"$libisc" = x"true" ; then
		libs="$libs -lisc"
		needothers=true
	fi
	if test x"$needothers" = x"true" ; then
		libs="$libs  -lnsl "
	fi
	echo $libs
fi
