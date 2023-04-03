/*	$ssdlinux: times.c,v 1.1.1.1 2002/05/02 13:37:04 kanoh Exp $	*/
/*
 * Copyright (c) 1999 Herbert Xu <herbert@debian.org>
 * This file contains code for the times builtin.
 * $Id: times.c,v 1.1.1.1 2002/05/02 13:37:04 kanoh Exp $
 */

#include <stdio.h>
#include <sys/times.h>
#include <unistd.h>

#define main timescmd
#undef printf

int main() {
	struct tms buf;
	long int clk_tck = sysconf(_SC_CLK_TCK);

	times(&buf);
	printf("%dm%fs %dm%fs\n%dm%fs %dm%fs\n",
	       (int) (buf.tms_utime / clk_tck / 60),
	       ((double) buf.tms_utime) / clk_tck,
	       (int) (buf.tms_stime / clk_tck / 60),
	       ((double) buf.tms_stime) / clk_tck,
	       (int) (buf.tms_cutime / clk_tck / 60),
	       ((double) buf.tms_cutime) / clk_tck,
	       (int) (buf.tms_cstime / clk_tck / 60),
	       ((double) buf.tms_cstime) / clk_tck);
	fflush(stdout);
	return 0;
}
