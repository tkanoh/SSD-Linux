/*
  $Id: ok.c,v 1.15 2004/11/26 09:57:24 todoroki Exp $
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <pwd.h>
#include <grp.h>
#define  __USE_XOPEN
#include <unistd.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include "setup.h"

/*
  戻り値 

  OK:		「変更しました」の画面を出す。
  OK_SAVE:	SAVE確認画面を出す。
  CONT:		元の画面を出す。
*/

int
ok_dhcp(char *arg)
{
  write_conf();

  return OK;
}

int
ok_dhcp3(char *arg)
{
  write_conf();

  return OK;
}

static int
add(const char *list_key, const char *id_key)
{
  char *val, *new_arg;
  List *alst;
  char *n;

  n = getval(id_key);
  val = getval(list_key);
  alst = list_split(0, val ? val : "");
  if(list_grep_item(alst, n))
    return CONT;

  list_push(alst, n);
  new_arg = list_join(alst);
  putval(list_key, new_arg, 1);

  return my_atoi(n);
}

int
ok_named_slave(char *arg)
{
  write_conf();

  return OK;
}

int
ok_named_master_soa(char *arg)
{
  write_conf();

  return OK;
}

int
ok_named_master(char *arg)
{
  char *domain, *typ, *res;
  int n = 0;
  int m;
  char *v = getval(X_NAMED_ZONE_RECORD_ID);
  if(!v){
       putval(X_NAMED_ZONE_RECORD_ID, "0", 1);
  }
  
  m = my_atoi(HTML_script_arg2->str);
  n = add(R_sprintf("x_named_zone_record__%d__", m), X_NAMED_ZONE_RECORD_ID);

  domain = getval(X_NAMED_ZONE_RECORD_DOMAIN___T);
  typ = getval(X_NAMED_ZONE_RECORD_TYP___T);
  res = getval(X_NAMED_ZONE_RECORD_RESOURCE___T);

  if(domain && typ && res){
    putval(R_sprintf("x_named_zone_record__%d__%d", m, n),
	   R_sprintf("%s %s %s", domain, typ, res),
	   1);
  }

  write_conf();

  return CONT;
}

/*
  ゾーン追加
 */
int
ok_named2(char *arg)
{
  char *typ, *name;
  int n;

  typ = getval("typ");
  if(!strcmp(typ, "named_master_soa"))
       return ok_named_master_soa(arg);

  if(HTML_script_arg1->str[0] == 'm')
    return ok_named_master(arg);
  if(HTML_script_arg1->str[0] == 's')
    return ok_named_slave(arg);

  n = add(X_NAMED_ZONE__, X_NAMED_ZONE_ID);
  
  name = getval(X_NAMED_ZONE_NAME___T);
  typ = getval(X_NAMED_ZONE_TYP___T);
  if(typ && name){
    putval(R_sprintf("x_named_zone__%d", n), R_sprintf("%s %s", typ, name), 1);
    putval(R_sprintf("x_named_zone_soa_mname__%d", n), R_sprintf("%s.%s", getval(X_HOSTNAME),getval(X_DOMAINNAME)), 1);
    putval(R_sprintf("x_named_zone_soa_rname__%d", n), R_sprintf("root.%s", getval(X_DOMAINNAME)), 1);
/*
    putval(R_sprintf("x_named_zone_record__%d", n), "0", 1);
    putval(R_sprintf("x_named_zone_record__%d__", n), "0", 1);
    putval(R_sprintf("x_named_zone_record__%d__0", n), R_sprintf(" NS %s.%s", getval(X_HOSTNAME), getval(X_DOMAINNAME)), 1);
*/
  }

  write_conf();

  return CONT;
}

int
ok_named(char *arg)
{
  if(*arg == '2')
    return ok_named2(arg);

  if(HTML_script_arg1->str[0] == 'm')
    return ok_named_master(arg);
  if(HTML_script_arg1->str[0] == 's')
    return ok_named_slave(arg);

  write_conf();

  return OK;
}

int
ok_httpd(char *arg)
{
  write_conf();
  return OK;
}

int
ok_sendmail2(char *arg)
{
  char *val, *new_arg;
  List *alst;
  int n;

  n = getval_int(X_SENDMAIL_RELAY_ID);

  val = getval(X_SENDMAIL_RELAY__);
  alst = list_split(0, val ? val : "");

  if(list_grep_item(alst, R_itoa(n)))
    return CONT;

  list_push(alst, R_sprintf("%d", n));

  new_arg = list_join(alst);
  putval(X_SENDMAIL_RELAY__, new_arg, 1);

  my_free(new_arg);
  list_delete(alst);

  val = getval(X_SENDMAIL_RELAY___T);
  if(val)
    putval(R_sprintf("x_sendmail_relay__%d", n), val, 1);
  delval(X_SENDMAIL_RELAY___T);

  write_conf();

  return CONT;
}

int
ok_sendmail(char *arg)
{
  if(*arg == '2')
    return ok_sendmail2(arg);

  write_conf();

  return OK;
}

int
ok_save(char *arg)
{
  int v;

  v = my_atoi(getval(X_SAVE_MODE));
  rename(RC_CONF_TMP, RC_CONF);

  return OK_SAVE;	/* save は特別な処理をする */
}

int
ok_network(char *arg)
{
  char *adr, *mask;
  unsigned int adr_ip4[4];
  unsigned int mask_ip4[4];
  unsigned int bcast_ip4[4];
  
  adr = getval(X_ETH_ADR__ETH0);
  mask = getval(X_ETH_SUBNET_MASK__ETH0);
  if(adr && mask){
    sscanf(adr, "%d.%d.%d.%d", adr_ip4, adr_ip4+1, adr_ip4+2, adr_ip4+3);
    sscanf(mask, "%d.%d.%d.%d", mask_ip4, mask_ip4+1, mask_ip4+2, mask_ip4+3);
    bcast_ip4[0] = (adr_ip4[0] & mask_ip4[0]) | (0xff & ~mask_ip4[0]);
    bcast_ip4[1] = (adr_ip4[1] & mask_ip4[1]) | (0xff & ~mask_ip4[1]);
    bcast_ip4[2] = (adr_ip4[2] & mask_ip4[2]) | (0xff & ~mask_ip4[2]);
    bcast_ip4[3] = (adr_ip4[3] & mask_ip4[3]) | (0xff & ~mask_ip4[3]);
    putval(X_ETH_BROADCAST__ETH0,
	   R_sprintf("%d.%d.%d.%d", bcast_ip4[0], bcast_ip4[1], bcast_ip4[2], bcast_ip4[3]), 1);
  }

  adr = getval(X_ETH_ADR__ETH1);
  mask = getval(X_ETH_SUBNET_MASK__ETH1);
  if(adr && mask){
    sscanf(adr, "%d.%d.%d.%d", adr_ip4, adr_ip4+1, adr_ip4+2, adr_ip4+3);
    sscanf(mask, "%d.%d.%d.%d", mask_ip4, mask_ip4+1, mask_ip4+2, mask_ip4+3);
    bcast_ip4[0] = (adr_ip4[0] & mask_ip4[0]) | (0xff & ~mask_ip4[0]);
    bcast_ip4[1] = (adr_ip4[1] & mask_ip4[1]) | (0xff & ~mask_ip4[1]);
    bcast_ip4[2] = (adr_ip4[2] & mask_ip4[2]) | (0xff & ~mask_ip4[2]);
    bcast_ip4[3] = (adr_ip4[3] & mask_ip4[3]) | (0xff & ~mask_ip4[3]);
    putval(X_ETH_BROADCAST__ETH1,
	   R_sprintf("%d.%d.%d.%d", bcast_ip4[0], bcast_ip4[1], bcast_ip4[2], bcast_ip4[3]), 1);
  }

  write_conf();

  return OK;
}

int
ok_ipv6(char *arg)
{
  int fd;
  struct ifreq ifr;
  unsigned char *p;

  fd = socket(AF_INET, SOCK_DGRAM, 0);

  strcpy(ifr.ifr_name, "eth0");
  ioctl(fd, SIOCGIFHWADDR, &ifr);
  p = ifr.ifr_hwaddr.sa_data;
  putval(X_IPV6_LOCAL__ETH0,
	 R_sprintf("%x:%x:%x:%x",
		   (p[0] ^ 2) * 256 + p[1],
		   p[2] * 256 + 0xff,
		   0xfe00 + p[3],
		   p[4] * 256 + p[5]), 1);

  strcpy(ifr.ifr_name, "eth1");
  ioctl(fd, SIOCGIFHWADDR, &ifr);
  p = ifr.ifr_hwaddr.sa_data;
  putval(X_IPV6_LOCAL__ETH1,
	 R_sprintf("%x:%x:%x:%x",
		   (p[0] ^ 2) * 256 + p[1],
		   p[2] * 256 + 0xff,
		   0xfe00 + p[3],
		   p[4] * 256 + p[5]), 1);

  write_conf();

  return OK;
}

int
ok_masq(char *arg)
{
  write_conf();

  return OK;
}

int
ok_system3(char *arg)
{
  char *cmd;
  char *n;
  int ret;

  setvalflag(X_YEAR, RC_bNULL);
  setvalflag(X_MON, RC_bNULL);
  setvalflag(X_MDAY, RC_bNULL);
  setvalflag(X_HOUR, RC_bNULL);
  setvalflag(X_MIN, RC_bNULL);
  setvalflag(X_SEC, RC_bNULL);

  n = getval(X_NTP_HOSTNAME);
  if(strlen(n) > 6) {
    cmd = R_sprintf("/usr/sbin/ntpdate %s",n);
    ret = system(cmd);
  }
  write_conf();
  return OK;
}

int
ok_system2(char *arg)
{
  struct timeval tp;
  struct timezone tzp;
  struct tm tm;

  tm.tm_year = getval_int("i_year") - 1900;
  if(tm.tm_year){
    tm.tm_mon = (getval_int("i_mon") - 1) % 12;
    tm.tm_mday = getval_int("i_mday");
    tm.tm_hour = getval_int("i_hour") % 24;
    tm.tm_min = getval_int("i_min") % 60;
    tm.tm_sec = getval_int("i_sec") % 60;

    /* タイムゾーンの取得 */
    gettimeofday(&tp, &tzp);
    /* epoch設定 */
    tp.tv_sec = timelocal(&tm);
#ifdef DEBUG
    fprintf(stderr, "%s", ctime(&tp.tv_sec));
#endif
    /* 時間の設定 */
    settimeofday(&tp, &tzp);
  }

  return OK_NOSAVE;
}

int
ok_system(char *arg)
{
  if(*arg == '2')
	return ok_system2(arg);
  if(*arg == '3')
	return ok_system3(arg);

  setvalflag(X_YEAR, RC_bNULL);
  setvalflag(X_MON, RC_bNULL);
  setvalflag(X_MDAY, RC_bNULL);
  setvalflag(X_HOUR, RC_bNULL);
  setvalflag(X_MIN, RC_bNULL);
  setvalflag(X_SEC, RC_bNULL);

  write_conf();

  return OK;
}

int
ok_user(char *arg)
{
  int ret;
  char *passwd1, *passwd2;
  char *cmd;
  char pid[8];

  passwd1 = getval(X_USER_PASSWD___T);
  passwd2 = getval(X_USER_PASSWD2___T);

  if(strcmp(passwd1, passwd2)){
    str_append_charp(HTML_error, R_sprintf("<FONT COLOR=red><B>エラー</B></FONT>&nbsp;%s<BR>\n", "パスワードが一致しません"));
    return NG;
  }
#if 0
  cmd = R_sprintf("/usr/sbin/groupadd -g %s %s",
		  getval(X_USER_ID),
		  getval(X_USER_LOGIN___T));
  ret = system(cmd);
#endif

  sprintf(pid, "%d", getpid());
  cmd = R_sprintf("/usr/sbin/useradd -m -u %s -g %d -p %s -d %s/%s -c '%s' %s > /dev/null",
		  getval(X_USER_ID),
		  USER_GROUP,
		  crypt(getval(X_USER_PASSWD___T), pid),
		  USER_HOME,
		  getval(X_USER_LOGIN___T),
		  getval(X_USER_NAME___T),
		  getval(X_USER_LOGIN___T));
  ret = system(cmd);
/*
  fprintf(stderr, "cmd=%s ret=%d\n", cmd, ret);
*/
  return CONT;
}

static void
del_user(int uid)
{
  struct group *grp;
  struct passwd *pwd;
  int ret = 0;
  char *cmd;
  /*
    uid = gid
   */
  pwd = getpwuid(uid);
  grp = getgrgid(uid);

  if(pwd){
    cmd = R_sprintf("/usr/sbin/userdel -r %s", pwd->pw_name);
    ret = system(cmd);
/*
    fprintf(stderr, "cmd=%s ret=%d\n", cmd, ret);
*/

    if(grp){
      cmd = R_sprintf("/usr/sbin/groupdel %s", grp->gr_name);
      ret = system(cmd);
/*
      fprintf(stderr, "cmd=%s ret=%d\n", cmd, ret);
*/
    }
  }
}

static void
del_ent(const char *key, char *tgt)
{
  List *lst;

  lst = list_split(0, getval(key));

  list_remove_item(lst, tgt);

  putval(key, list_join(lst), 1);

  list_delete(lst);
}

int
del(char *arg)
{
  int del;
  char *typ;
  Env *e;

  e = envtop.next;
  while(e->key){
    if(0)
      ;
    else if(e->key && sscanf(e->key, "d__%d", &del) == 1){
      typ = getval("typ");
/*
      fprintf(stderr, "typ=%s del=%d\n", typ, del);
*/
      if(!strcmp(typ, "sendmail"))
	del_ent(X_SENDMAIL_RELAY__, R_itoa(del));
      else if(!strcmp(typ, "user"))
	del_user(del);
      else if(!strcmp(typ, "portfw"))
	del_ent(X_PORTFW__, R_itoa(del));
      else if(!strcmp(typ, "fw"))
	del_ent(X_FW__, R_itoa(del));
      else if(!strcmp(typ, "named"))
	del_ent(X_NAMED_ZONE__, R_itoa(del));
      else if(!strcmp(typ, "named_master"))
	del_ent(R_sprintf("x_named_zone_record__%s__",HTML_script_arg2->str), R_itoa(del));
      break;
    }
    e = e->next;
  }

  write_conf();

  return OK;
}

int
ok_portfw(char *arg)
{
  char *val, *new_arg;
  List *alst;
  int n;

  n = getval_int(X_PORTFW_ID);

  val = getval(X_PORTFW__);
  alst = list_split(0, val ? val : "");

  if(list_grep_item(alst, R_itoa(n)))
    return CONT;
  
  list_push(alst, R_sprintf("%d", n));

  new_arg = list_join(alst);
  putval(X_PORTFW__, new_arg, 1);

  my_free(new_arg);
  list_delete(alst);

  putval(R_sprintf("x_portfw__%d", n),
	 R_sprintf("%s %s %s %s %s",
		   getval(X_PORTFW_PROTO___T),
		   getval(X_PORTFW_INTERFACE___T),
		   getval(X_PORTFW_SRC_PORT___T),
		   getval(X_PORTFW_DST_IP___T),
		   getval(X_PORTFW_DST_PORT___T)),
	 1);

  write_conf();

  return CONT;
}

int
ok_fw(char *arg)
{
  char *val, *new_arg = NULL;
  List *alst;
  int n;

  if(*arg == '\0' || *arg == '1')
    return ok_portfw(arg);

  n = getval_int(X_FW_ID);

  val = getval(X_FW__);
  alst = list_split(0, val ? val : "");
  /*
    既にある場合は何もしない。
   */
  if(list_grep_item(alst, R_itoa(n)))
    return CONT;

  list_push(alst, R_itoa(n));

  new_arg = list_join(alst);
  putval(X_FW__, new_arg, 1);

  my_free(new_arg);
  list_delete(alst);

  putval(R_sprintf("x_fw__%d", n),
	 R_sprintf("%d %s %s %s %s %s %s %s %s",
		   n,
		   getval(X_FW_PROTO___T),
		   getval(X_FW_SRC_IP___T),
		   getval(X_FW_SRC_SUBNET_MASK___T),
		   getval(X_FW_SRC_PORT___T),
		   getval(X_FW_DST_IP___T),
		   getval(X_FW_DST_SUBNET_MASK___T),
		   getval(X_FW_DST_PORT___T),
		   getval(X_FW_ACTION___T)),
	 1);

  write_conf();

  return CONT;
}

int
ok_samba(char *arg)
{
  write_conf();
  return OK;
}
