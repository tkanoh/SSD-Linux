/*	$ssdlinux: talkaddr.h,v 1.1.1.1 2002/05/02 13:37:12 kanoh Exp $	*/
/*
 * Copyright (C) 2001 USAGI/WIDE Project.
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

#ifndef __TALKADDR_H
#define __TALKADDR_H

#include <netinet/in.h>

# define __bswap_constant_16(x) \
	((((x) & 0xff00ull) >> 8) | (((x) & 0x00ffull) << 8))

/* constants */
#define TF_UNSPEC	__bswap_constant_16(0)
#define TF_LOCAL	__bswap_constant_16(1)
#define	TF_INET		__bswap_constant_16(2)
#define TF_INET6	__bswap_constant_16(3)

/* types */
typedef	u_int16_t	ta_family_t;
typedef u_int16_t	ta_port_t;
typedef int		talklen_t;

/* structures */
struct talkaddr {
	ta_family_t	ta_family;	/* TF_xxx */
	ta_port_t	ta_port;
	u_int32_t	ta_addr;
	u_int32_t	ta_junk1;
	u_int32_t	ta_junk2;
};

#ifdef INET6
struct talkaddr6 {
	ta_family_t	ta_family;	/* TF_INET6 */
	ta_port_t	ta_port;
	u_int32_t	ta_zero;
	u_int32_t	ta_junk1;
	u_int32_t	ta_junk2;
	struct in6_addr	ta_addr6;
};
#endif

/* functions */
ta_family_t talkfamily(sa_family_t af);
sa_family_t sockfamily(ta_family_t tf);
struct talkaddr *saddr2taddr(const struct sockaddr *sa, struct talkaddr *ta);
struct sockaddr *taddr2saddr(const struct talkaddr *ta, struct sockaddr *sa);

#endif	/* __TALKADDR_H */
