/*	$ssdlinux: net-tools-util.c,v 1.1.1.1 2002/05/02 13:37:05 kanoh Exp $	*/
/* Copyright 1998 by Andi Kleen. Subject to the GPL. */ 
/* $Id: net-tools-util.c,v 1.1.1.1 2002/05/02 13:37:05 kanoh Exp $ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>

#include "util.h"


static void oom(void)
{
    fprintf(stderr, "out of virtual memory\n");
    exit(2);
}

int kernel_version(void)
{
    struct utsname uts;
    int major, minor, patch;

    if (uname(&uts) < 0)
	return -1;
    if (sscanf(uts.release, "%d.%d.%d", &major, &minor, &patch) != 3)
	return -1;
    return KRELEASE(major, minor, patch);
}


/* Like strncpy but make sure the resulting string is always 0 terminated. */  
char *safe_strncpy(char *dst, const char *src, size_t size)
{   
    dst[size-1] = '\0';
    return strncpy(dst,src,size-1);   
}
