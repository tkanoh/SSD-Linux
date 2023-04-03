/*
	$Id: io.c,v 1.2 2003/03/12 01:54:08 yamagata Exp $
 */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <net/if.h>
#include <net/route.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "setup.h"

char *
get_interface_adr(char *interface)
{
  int s;
  int ret;
  struct ifreq	ifr;
  struct sockaddr_in *sa;
  unsigned char *p;

  if(!interface)
    return NULL;

  ifr.ifr_addr.sa_family = AF_INET;
  strcpy(ifr.ifr_name, interface);

  s = socket(ifr.ifr_addr.sa_family, SOCK_DGRAM, 0);
  ret = ioctl(s, SIOCGIFADDR,  &ifr);
  p = (char *)sa = (struct sockaddr_in *)&(ifr.ifr_addr);
  close(s);

  return R_sprintf("%d.%d.%d.%d", p[4], p[5], p[6], p[7]);
}

#if 0
main()
{
  interface_address("eth0");
}
#endif
