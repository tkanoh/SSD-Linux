/* $USAGI: rtsol.c,v 1.2 2002/01/29 11:09:05 mk Exp $ */
/* Copyright (C) 2001 SOUM Corporation. All rights reserved.
 * Modifyied by masa@soum.co.jp
 */

/*
 * Copyright (C) 1995, 1996, 1997, and 1998 WIDE Project.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE PROJECT AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE PROJECT OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip6.h>
#include <netinet/icmp6.h>
#include <unistd.h>
#include <stdio.h>
#include <err.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/sysctl.h>
#include <netdb.h>
#include <sys/time.h>
#include <sys/types.h>

#define	RTR_SOLICITATION_TIMEOUT	4
#define	ALLROUTER	"ff02::2"

static int verbose = 0;

void usage()
{
	fprintf (stderr, "usage : rtsol [-v] interfacename\n");
	exit(1);
}

int main(int argc, char **argv)
{
    struct sockaddr_in6 to;
    struct icmp6_hdr *icp;
    u_int hlim = 255;
    u_char outpack[sizeof(struct icmp6_hdr)];
    u_short index;
    int s, i, cc = sizeof(struct icmp6_hdr);
    fd_set fdset;
    struct timeval timeout;
    int opt;

    while ((opt = getopt(argc, argv, "v")) != -1) {
	    switch (opt) {
	    case 'v':
		    verbose++;
		    break;
	    default:
		    usage();
	    }
    }
    argc -= optind;
    argv += optind;

    if (argc != 1) {
	    usage();
    }

    index = (u_short)if_nametoindex(argv[0]);
    if (index == 0) {
	perror ("if_nametoindex");
	exit (1);
    }

    {
	struct addrinfo hints, *res;
	int error;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET6;
	error = getaddrinfo(ALLROUTER, NULL, &hints, &res);
	if (error) {
	    fprintf (stderr, "getaddrinfo : %s.\n", gai_strerror(error));
	    exit (1);
	}
	memcpy(&to, res->ai_addr, res->ai_addrlen);
    }

    if ((s = socket(AF_INET6, SOCK_RAW, IPPROTO_ICMPV6)) < 0) {
	perror("socket");
	exit (1);
    }

    if (setsockopt(s, IPPROTO_IPV6, IPV6_MULTICAST_HOPS, &hlim,
		    sizeof(hlim)) == -1) {
	perror ("setsockopt(IPV6_MULTICAST_HOPS)");
	exit (1);
    }

    /* fill ICMP header */
    icp = (struct icmp6_hdr *)outpack;
    icp->icmp6_type = ND_ROUTER_SOLICIT;
    icp->icmp6_code = 0;
    icp->icmp6_cksum = 0;
    icp->icmp6_data32[0] = 0;

    /* send message */
    if (verbose) 
	    fprintf (stderr, "send RS packet!\n");

    i = sendit(s, (char *)outpack, cc, &to, index);
    if (i < 0) {
	perror ("send solicitation");
	exit (1);
    } else if (i != cc) {
	fprintf (stderr, "%s: short write (wrote %d of be %d)\n",
		argv[0], i, cc);
    }

    FD_ZERO(&fdset);
    FD_SET(s, &fdset);
    timeout.tv_sec = RTR_SOLICITATION_TIMEOUT;
    timeout.tv_usec = 0;
    /* waiting for RA message */
    if (select(s + 1, &fdset, NULL, NULL, &timeout) > 0) {
	    if (verbose)
		    fprintf (stderr, "receive RA packet!\n");
    } else {
	    if (verbose)
		    fprintf (stderr, "Couldn't receive RA packet!\n");
	    
	close(s);
	exit(1);
    }
    close(s);

    /* normal exit */
    exit(0);
}

int sendit(int s, char *p, int len, struct sockaddr_in6 *sock, int ifindex)
{
    return sendto(s, p, len, 0, (struct sockaddr *)sock, sizeof(struct sockaddr_in6));
}
