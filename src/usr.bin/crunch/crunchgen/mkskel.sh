#!/bin/sh

#	$ssdlinux: mkskel.sh,v 1.1.1.1 2002/05/02 13:37:10 kanoh Exp $
#	$NetBSD$

# idea and sed lines taken straight from flex

cat <<!EOF
/* File created via mkskel.sh */

char *crunched_skel[] = {
!EOF

sed 's/\\/&&/g' $* | sed 's/"/\\"/g' | sed 's/.*/  "&",/'

cat <<!EOF
  0
};
!EOF
