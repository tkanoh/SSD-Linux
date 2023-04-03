/*
	$Id: setup.c,v 1.40 2005/01/31 05:24:28 yamagata Exp $
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <signal.h>
#ifndef TESTSERVER
#include <shadow.h>
#endif
#include <pwd.h>
#include <crypt.h>

#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "setup.h"

extern void z_userlist();

extern int ok_dhcp(char *);
extern int ok_dhcp3(char *);
extern int ok_save(char *);
extern int ok_system(char *);
extern int ok_system2(char *);
extern int ok_network(char *);
extern int ok_ipv6(char *);
extern int ok_portfw(char *);
extern int ok_fw(char *);
extern int ok_masq(char *);
extern int ok_sendmail(char *);
extern int ok_sendmail2(char *);
extern int ok_sendmail3(char *);
extern int ok_user(char *);
extern int ok_named(char *);
extern int ok_httpd(char *);
extern int ok_samba(char *);

extern int del(char *);

typedef struct _Menu{
  int active;
  struct _Menu *child;
  int idx;
  char *tmpl;
  char *str;
  int (*ok_hook)(char *);
  int (*del_hook)(char *);
} Menu;

static Menu sub_menu[] = {
  {1, 0, VC_DHCPD, "dhcpd", "dhcpd", ok_dhcp},
  {1, 0, VC_SENDMAIL, "sendmail", "sendmail", ok_sendmail, del},
  {1, 0, VC_NAMED, "named", "named", ok_named, del},
  {1, 0, VC_HTTPD, "httpd", "httpd", ok_httpd, del},
  {-1, 0, 0, NULL},
};

static Menu top_menu[] = {
  {0, 0, VC_SAVE, "save", "設定保存", ok_save},
  {1, 0, VC_SYSTEM, "system", "システム", ok_system},
#ifndef CUSTOM0
  {1, 0, VC_USER, "user", "ユーザ管理", ok_user, del},
#endif
  {1, 0, VC_NETWORK, "network", "ネットワーク", ok_network},
#ifdef CUSTOM0
  {1, 0, VC_SAMBA, "samba", "samba", ok_samba},
#else
#ifdef IPV6
  {1, 0, VC_IPV6, "ipv6", "IPv6", ok_ipv6},
#endif
  {1, 0, VC_MASQ, "masq", "アドレス変換", ok_masq},
  {1, 0, VC_FW, "fw", "簡易ファイヤウォール", ok_fw, del},
  {1, sub_menu, VC_MISC, "misc", "その他"},
#endif
#if 0
  {1, 0, VC_HELP, "help", "ヘルプ"},
#endif
  {-1, 0, 0, NULL},
};

const char *update_timer =
"<script>"
"<!--"
"var sec = 0;"
"function timeform() {"
""
"  hour = document.i_timer.i_hour.value - 0;"
"  min  = document.i_timer.i_min.value - 0;"
""
"  /* ++sec; */"
"  if(sec >= 60){"
"    sec = 0;"
"    ++min;"
"  }"
"  if(min >= 60){"
"    min = 0;"
"    ++hour;"
"  }"
""
"  if ( hour < 10 ) { hour = \"0\" + hour; }"
"  if ( min  < 10 ) { min  = \"0\" + min; }"
""
"  document.i_timer.i_hour.value = hour;"
"  document.i_timer.i_min.value  = min;"
""
"  window.setTimeout( \"timeform()\", 1000 );"
"}"
"// -->"
"</script>";

#define N_MENU		(sizeof(top_menu)/sizeof(Menu) - 1)

char *HTML_request_uri;
char *HTML_script_name;
char *HTML_notice = "";
char *HTML_server_addr;
int   HTML_server_port;

Str  *HTML_script;
Str  *HTML_script_op;
Str  *HTML_script_subop;

Str  *HTML_script_arg1;
Str  *HTML_script_arg2;

Str  *HTML_location;
Str  *HTML_error;

Ring *ring;

static int d_flg;

/*
char shutdown_cmd[256];
 */
char shutdown_arg[16];

void
sysupdate()
{
  int i;
  FILE *fp;
  List *lst, *lst2;
  char *typ;

  /*
    UPSETCONFを出力
    (ここで必ずファイルサイズが0になるよう修正)
   */
  fp = fopen(UPSETCONF, "w");
  if(!fp)
       fprintf(stderr, "Cannot open %s\n", UPSETCONF);
  else{
       if((typ = getval(X_FW__)) != NULL){
	    lst = list_split(0, typ);
	    for(i=0 ; i<lst->n ; ++i){
		 lst2 = list_split(0, getval(R_sprintf("x_fw__%s", lst->item[i])));
		 fprintf(fp, "/sbin/iptables -A INPUT --proto %s ", lst2->item[1]);
		 if(!strcasecmp(lst2->item[2], "ANY"))
		      ;
		 else
		      fprintf(fp, "--source %s/%d ", lst2->item[2], ip4_to_mask(lst2->item[3]));
		 
		 if(!strcasecmp(lst2->item[4], "ANY"))
		      ;
		 else
		      fprintf(fp, "--source-port %s ", lst2->item[4]);
		 
		 if(!strcasecmp(lst2->item[5], "ANY"))
		      ;
		 else
		      fprintf(fp, "--destination %s/%d ", lst2->item[5], ip4_to_mask(lst2->item[6]));
		 
		 if(!strcasecmp(lst2->item[7], "ANY"))
		      ;
		 else
		      fprintf(fp, "--destination-port %s ", lst2->item[7]);
		 
		 fprintf(fp, "-j %s\n", lst2->item[8]);
	    }
       }
       if((typ = getval(X_MSQ_TYP)) != NULL){
	    switch(typ[0]){
	    default:
		 break;
	    case '2':
		 fprintf(fp, "/sbin/iptables -t nat -A POSTROUTING -o eth1 -j MASQUERADE\n");
		 break;
	    case '3':
		 fprintf(fp, "/sbin/iptables -t nat -A POSTROUTING -o eth0 -j MASQUERADE\n");
		 break;
	    }
       }

       if((typ = getval(X_PORTFW__)) != NULL){
	   lst = list_split(0, typ);
	   for(i=0 ; i<lst->n ; ++i){
	       lst2 = list_split(0, getval(R_sprintf("x_portfw__%s", lst->item[i])));
	       fprintf(fp, "/sbin/iptables -A PREROUTING -t nat -p %s -d %s --dport %s -j DNAT --to-destination %s:%s\n",
		       lst2->item[0], getval(R_sprintf("x_eth_adr__%s", lst2->item[1])),
		       lst2->item[2], lst2->item[3],
		       lst2->item[4]);
	       list_delete(lst2);
	   }
	   list_delete(lst);
       }
       fclose(fp);
  }

  /*
    RADVDCONFを出力
    (ここで必ずファイルサイズが0になるよう修正)
   */
  fp = fopen(RADVDCONF, "w");
  if (fp == NULL) {
       fprintf(stderr, "Cannot open %s\n", RADVDCONF);
  } else {
    if (((typ = getval(X_IPV6_ENABLE__ETH0)) != NULL) &&
	(strncmp(typ, "YES", 4) == 0) &&
	((typ = getval(X_IPV6_PREFIX__ETH0)) != NULL)) {
      fprintf(fp,
	      "interface eth0\n{\n\tAdvSendAdvert on;\n\tprefix\t%s::/64\n"
	      "\t{\n\t\tAdvOnLink on;\n\t\tAdvAutonomous on;\n\t\tAdvRouterAddr on;\n\t};\n};\n",
	      typ);
    }
    if (((typ = getval(X_IPV6_ENABLE__ETH1)) != NULL) &&
	(strncmp(typ, "YES", 4) == 0) &&
	((typ = getval(X_IPV6_PREFIX__ETH1)) != NULL)) {
      fprintf(fp,
	      "interface eth1\n{\n\tAdvSendAdvert on;\n\tprefix\t%s::/64\n"
	      "\t{\n\t\tAdvOnLink on;\n\t\tAdvAutonomous on;\n\t\tAdvRouterAddr on;\n\t};\n};\n",
	      typ);
    }
    fclose(fp);
  }
}

/*
  CGIの引数を取得する。メモリの少ないOpenBlockSのことを考慮し、
  1024バイト以上の引数は受けない。

  d_で始まる変数があった場合は1を返す。それ以外は0。
 */

int
ht_getarg()
{
  int len;
  char *env;
  char *envbuf = "";
  int n;
  int i;
  char *p;
  char *key = "";
  char *val = "";

  env = getenv("QUERY_STRING");
  if(env && *env){
    if(strlen(env) > 1024)
      panic("getarg");
    envbuf = my_strdup(env);
#ifdef DEBUG
    /*
      デバグを用意にするため全く同じ環境で起動できるよう、出力をする
     */
    {
      FILE *fp;

      fp = fopen("/tmp/setup.debug", "w");
      fprintf(fp, "#!/bin/sh\n");
      fprintf(fp, "export QUERY_STRING=\"%s\"\n", env);
      fprintf(fp, "export PATH=/usr/local/bin:$PATH\n");
      fprintf(fp, "export LD_LIBRARY_PATH=/lib:/usr/lib:$LD_LIBRARY_PATH\n");
      fprintf(fp, "gdb /usr/contrib/etc/setup/setup.cgi\n");
      fclose(fp);
    }
#endif
  }
  else{ 
    env = getenv("REDIRECT_CONTENT_LENGTH");
    if(env && *env){
      len = atoi(env);
      if(len > 1024)
	panic("getarg");
      envbuf = R_malloc(len + 1);
      read(0, envbuf, len);
      envbuf[len] = '\0';
    }
    else{
      env = getenv("CONTENT_LENGTH");
      if(env && *env){
	len = atoi(env);
	if(len > 1024)
	     panic("getarg");
	envbuf = R_malloc(len+1);
	read(0, envbuf, len);
	envbuf[len] = '\0';
      }
    }
  }

  p = envbuf;
  n = 0;
  if(*p)
    n = 1;

  while(*p)
    if(*(p++) == '&')
      ++n;
  
  p = envbuf;
  for(i=0 ; i<n ; ++i){
    key = p;
    while(*p && *p != '&' && *p != '=')
      ++p;
    if(*p == '='){
      *(p++) = '\0';
      val = p;
      while(*p && *p != '&')
	++p;
      *(p++) = '\0';
    }
    else
      *(p++) = '\0';

    val = ring_htdecode(ring, val);

    if(key[1] == '_'){
      if(key[0] == 'j'){ /* 既に「i_」がある場合は登録しない */
	key[0] = 'i';
	if(!getval(key)){
	  putval(key, val, 1);
	  key[0] = 'x';
	  putval(key, val, 1);
	}
      }
      else if(key[0] == 'i'){
	putval(key, val, 1);
	key[0] = 'x';
	putval(key, val, 1);
      }
      else if(key[0] == 'd'){	/* 削除フラグ */
	d_flg = 1;
	putval(key, val, 1);
      }
      else
	putval(key, val, 1);
    }
    else
      putval(key, val, 0);
  }

  return d_flg;
}

static Menu *
op2menu(Menu *m, char *op)
{
  Menu *ret;

  if(!m)
    return NULL;
  if(!op)
    return NULL;

  while(m->active >= 0){
    if(!strcmp(m->tmpl, op))
      return m;
    if(m->child){
      ret = op2menu(m->child, op);
      if(ret)
	return ret;
    }

    ++m;
  }

  return NULL;
}

void
output_header(char *opt, char *javascript)
{
  printf("%sContent-Type: text/html; charset=euc-jp\n\n", HTML_location->str);
  printf("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">\n");
  printf(
"<html>"
"  <head>"
"  <meta HTTP-EQUIV=\"Content-Type\" CONTENT=\"text/html; charset=euc-jp\">"
"  <title>OpenBlockS設定メニュー</title>"
"  %s"
"  </head>", javascript);
  printf(
"  <body BGCOLOR=\"#ffffff\" %s>"
"  <CENTER><IMG SRC=\"/ob_title.gif\"></CENTER>", opt);
}

void
output_footer()
{
  printf(
"<hr>"
"<B>&copy; 2001-2005 Plat\'Home CO., LTD., Heart Internet Service</B><BR>"
"<FONT SIZE=\"-1\">OpenBlockS Auto Configuration, Version: %s, Last Build: %s</FONT><BR>"
"  </body>"
"</html>"
, /*getval(X_OPENBLOCKS_AUTOCONFIG_VERSION)*/ SETUP_CGI_VERSION, BUILD_DATE);
}

void
output_subtab(Menu *m0, char *op, char *subop)
{
  int i;
  char *c0 = COLOR_C0;
  char *c1 = COLOR_C1;
  Menu *m = m0;
  int n;

  if(!m0)
    return;
  if(!subop)
    subop = "";

  n = 0;

  printf("<TABLE WIDTH=\"100%%\" border=0 cellpadding=4 cellspacing=0>\n");
  printf("<TR>\n");

  i = 0;
  m = m0;
  while(m->active >= 0){
    ++n;
    if(!strcmp(subop, m->tmpl)) {/* 選択している */
      printf("<TD NOWRAP width=\"1%%\" align=\"left\" bgcolor=%s valign=\"top\"><FONT><B><A HREF=\"%s&op=%s&subop=%s\">%s</A></B></FONT></TD>\n", c1, HTML_script->str, op, m->tmpl, m->str);
    }
    else if(m->active)	/* 選択していない∧アクティブ */
      printf("<TD NOWRAP width=\"1%%\" align=\"left\" bgcolor=%s valign=\"top\"><FONT><B><A HREF=\"%s&op=%s&subop=%s\">%s</A></B></FONT></TD>\n", c0, HTML_script->str, op, m->tmpl, m->str);
    else			/* 選択していない∧非アクティブ */
      printf("<TD NOWRAP width=\"1%%\" align=\"left\" bgcolor=%s valign=\"top\"><FONT><B>%s</B></FONT></TD>\n", c0, m->str);
    
    printf("<TD WIDTH=\"1%%\"></TD>\n");
    ++i;
    ++m;
  }
  printf("<TD NOWRAP width=\"100%%\" align=\"left\" bgcolor=%s valign=\"top\"><FONT><B>&nbsp;</B></FONT></TD>\n", COLOR_WHITE);
  printf("</TR>\n");
  printf("<TR HEIGHT=1>\n");
  printf("<TD WIDTH=\"100%%\" HEIGHT=1 COLSPAN=%d bgcolor=%s>&nbsp;</TD>\n", n*2+1, c1);
  printf("</TR>\n");
  printf("</TABLE>\n");
}

void
output_tab(Menu *m0, char *op, char *subop)
{
  int i;
  char *c0 = COLOR_C0;
  char *c1 = COLOR_C1;
  Menu *m = m0;
  Menu *child = NULL;
  int n;

  if(!m0)
    return;
  if(!op)
    op = "";

  n = 0;

  printf("<TABLE WIDTH=\"100%%\" border=0 cellpadding=4 cellspacing=0>\n");
  printf("<TR>\n");

  i = 0;
  m = m0;
  while(m->active >= 0){
    ++n;
    if(!strcmp(op, m->tmpl)) {/* 選択している */
      printf("<TD NOWRAP width=\"1%%\" align=\"left\" bgcolor=%s valign=\"top\"><FONT><B><A HREF=\"%s&op=%s\">%s</A></B></FONT></TD>\n", c1, HTML_script->str, m->tmpl, m->str);
      if(m->child)
	child = m->child;
    }
    else if(m->active)	/* 選択していない∧アクティブ */
      printf("<TD NOWRAP width=\"1%%\" align=\"left\" bgcolor=%s valign=\"top\"><FONT><B><A HREF=\"%s&op=%s\">%s</A></B></FONT></TD>\n", c0, HTML_script->str, m->tmpl, m->str);
    else			/* 選択していない∧非アクティブ */
      printf("<TD NOWRAP width=\"1%%\" align=\"left\" bgcolor=%s valign=\"top\"><FONT><B>%s</B></FONT></TD>\n", c0, m->str);
    
    printf("<TD WIDTH=\"1%%\"></TD>\n");
    ++i;
    ++m;
  }
  printf("<TD NOWRAP width=\"100%%\" align=\"left\" bgcolor=%s valign=\"top\"><FONT><B>&nbsp;</B></FONT></TD>\n", COLOR_WHITE);
  printf("</TR>\n");
  printf("<TR HEIGHT=1>\n");
  printf("<TD WIDTH=\"100%%\" HEIGHT=1 COLSPAN=%d bgcolor=%s>&nbsp;</TD>\n", n*2+1, c1);
  printf("</TR>\n");
  printf("</TABLE>\n");

  if(child)
    output_subtab(child, op, subop);
}

void
eval_macro(char *zbuf)
{
  char *key;
  char *opt;

  key = my_strdup(zbuf);
  opt = my_strdup(zbuf);

  {
    Str *tmp;

    tmp = str_new();
    eval(tmp, zbuf);
    printf("%s", tmp->str);
    str_delete(tmp);
    return;
  }
}

void
output_body(char *file)
{
  int inflg = 0;
  int c = 0, c2;
  int z = 0;
  char zbuf[128];/* <? ?>の中身の保存用 */
  FILE *fp;
  char buf[1024], *p;
  List *stack;
  Str *filename;

  printf("<!--%s-->\n", file);
  filename = str_new();
  str_append_charp(filename, R_sprintf("%s-%s.t", file, HTML_script_arg1->str));
  fp = fopen(filename->str, "r");
  if(!fp){
    str_trunc(filename, 0);
    str_append_charp(filename, R_sprintf("%s.t", file));
    fp = fopen(filename->str, "r");
    if(!fp)
      return;
  }

  stack = list_new(16);

  while(fgets(buf, 1023, fp) != NULL){
    p = buf;
    while(*p){
      c = *(p++);

      if(inflg == 0 && c == '<'){	/* "<?"の中に入ったか? */
	c2 = *p;
	if(c2 == '?'){
	  inflg = 1;
	  z = 0;
	  ++p;
	  continue;
	}
      }
      if((inflg == 1 && c == '?') || z > 127){	/* "?>"の外へ出たか? */
	c2 = *p;
	if(c2 == '>'){
	  inflg = 0;
	  zbuf[z] = '\0';
	  eval_macro(zbuf);
	  ++p;
	  continue;
	}
      }
      if(inflg == 0)
	fputc(c, stdout);
      else
	zbuf[z++] = c;
    }
  }
  fclose(fp);
}

void      page_cannot_access(char *);
void      page_login(char *);
void      page_badpasswd(char *);
void      page_setup(char *, char *);

Str *
create_key(char *login)
{
  time_t t;
  Str *tmp;
  Str *new_key;

  tmp = str_new();
  new_key = str_new();
  t = time(NULL);
  /*
    CRYPT(login + stamp + secret, seed)
   */
  str_append_charp(tmp, login);
  str_append_charp(tmp, R_sprintf("%d", t));
  str_append_charp(tmp, "SECRET");
  str_append_charp(new_key, crypt(tmp->str, R_sprintf("$1$%u", getpid())));
  str_append_charp(new_key, ":");
  str_append_charp(new_key, R_sprintf("%d", t));

  str_delete(tmp);
  return new_key;
}

int
check_key(char *login, char *str)
{
  time_t t;
  List *lst;
  Str *tmp;
  char *key;
  char *stamp;
  int ret;

  tmp = str_new();

  lst = list_split(':', str);
  key = lst->item[0];
  stamp = lst->item[1];

  sscanf(stamp, "%d", (int *)&t);

  str_append_charp(tmp, login);
  str_append_charp(tmp, stamp);
  str_append_charp(tmp, "SECRET");

  ret = !strcmp(crypt(tmp->str, key), key);
  
  str_delete(tmp);
  list_delete(lst);

  return ret;
}

int
main(int argc, char *argv[])
{
  char *op;
  char *subop;
  struct hostent *hent;
  struct in_addr *server_addr;
  struct in_addr saddr;

  ring = ring_new(16);
  HTML_location = str_new();
  HTML_error = str_new();
  HTML_script_op = str_new();
  HTML_script_subop = str_new();
  HTML_script_arg1 = str_new();
  HTML_script_arg2 = str_new();
  HTML_script = str_new();

  read_conf();
  
  d_flg = ht_getarg();
  HTML_request_uri = getenv("REQUEST_URI");
  HTML_script_name = getenv("SCRIPT_NAME");

  saddr.s_addr = inet_addr(getenv("HTTP_HOST"));
  if(saddr.s_addr != -1) {
    HTML_server_addr = getenv("HTTP_HOST");
  }
  else {
    if((hent=gethostbyname(getenv("HTTP_HOST"))) == NULL)
      strcpy(HTML_server_addr,"unknown");
    else {
      if(hent->h_addrtype == AF_INET) {
        server_addr=(struct in_addr *)hent->h_addr;
        HTML_server_addr=inet_ntoa(*server_addr);
      }
      else {
        strcpy(HTML_server_addr,"unknown");
      }
    }
  }
  sscanf(getenv("SERVER_PORT"),"%d",&HTML_server_port);

  putval("c0", COLOR_C0, RC_bNULL);
  putval("c1", COLOR_C1, RC_bNULL);
  putval("c2", COLOR_C2, RC_bNULL);
  putval("c3", COLOR_C3, RC_bNULL);
  putval("gray0", COLOR_GRAY0, RC_bNULL);

  /*
    interfaceのアドレスをチェックする
   */

  if(is_updateval() == 3){
    top_menu[0].active = 1;
  }

  op = getval("op");
  if(!op || !*op)
    op = "system";

  subop = getval("subop");
  
  str_append_charp(HTML_script_op, op);
  str_append_charp(HTML_script_subop, subop);

  str_append_charp(HTML_script_arg1, getval("a"));
  str_append_charp(HTML_script_arg2, getval("a2"));

#ifndef TESTSERVER
  {
    char *adr;
    int eth_port;

    adr = get_interface_adr(getval(X_OPENBLOCKS_ACCESS_LIMIT));

    if((HTML_server_addr && (!adr || strcmp(adr, HTML_server_addr))) || 
	(HTTPD_PORT != HTML_server_port)) {
      sscanf(getval(X_OPENBLOCKS_ACCESS_LIMIT),"eth%d",&eth_port);
      page_cannot_access(R_sprintf("%1d",eth_port));
      goto End;
    }
  }
#endif

#ifndef TESTSERVER
  setuid(0);
  seteuid(0);
  setgid(0);
  setegid(0);
#endif

#if 1
  {
    char *login = getval(X_LOGIN);
    char *passwd = getval(X_PASSWD);
    char *key = getval(X_KEY);
#ifdef TESTSERVER
    struct passwd *pwent;
#else
    struct spwd *pwent;
#endif

    enum {
      NO_LOGIN,
      BAD_LOGIN,
      BAD_PASSWD,
      OK_LOGIN,
    } login_stat = NO_LOGIN;

/*
  x_keyは本来コンフィグファイルに出力されるべきものではない。
  万が一出力されていたら強引に出力フラグをクリアする
 */
    {
	 Env *p = getvalp(X_KEY);
	 if(p != NULL){
	      p->flag |= RC_bNULL;
	 }
    }

    if(!login || !login[0])
	;
    else if(passwd && passwd[0]){
#ifdef TESTSERVER
      pwent = getpwnam("root");
#else
      pwent = getspnam("root");
#endif
      if(pwent == NULL) 
        login_stat = BAD_LOGIN;
/*
      else if(strcmp(login, "admin"))
        login_stat = BAD_LOGIN;
 */
#ifdef TESTSERVER
      else if(strcmp(crypt(passwd, pwent->pw_passwd), pwent->pw_passwd))
	login_stat = BAD_PASSWD;
#else
      else if(strcmp(crypt(passwd, pwent->sp_pwdp), pwent->sp_pwdp))
	login_stat = BAD_PASSWD;
#endif
/*
      else if(strcmp(passwd, "system"))
	login_stat = BAD_PASSWD;
 */
      else{
	Str *new_key;

	new_key = create_key(login);
	/* GENERATE KEY */
	putval(X_KEY, new_key->str, RC_bWRITE | RC_bNULL);
	str_delete(new_key);

	login_stat = OK_LOGIN;
      }
    }
    else if(key && key[0]){
      /* KEY CHECK */
      if(check_key(login, key))
	login_stat = OK_LOGIN;
    }
    if(login_stat == BAD_PASSWD || login_stat == BAD_LOGIN){
      str_trunc(HTML_script_op, 0);
      str_append_charp(HTML_script_op, op);

      page_badpasswd("badpasswd");
      goto End;
    }
    else if(login_stat != OK_LOGIN){
      str_trunc(HTML_script_op, 0);
      str_append_charp(HTML_script_op, op);

      page_login("login");
      goto End;
    }
  }
  setvalflag(X_LOGIN, RC_bNULL);
  setvalflag(X_PASSWD, RC_bNULL);

  str_append_charp(HTML_script, R_sprintf("setup.cgi?i_login=%s&i_key=%s", getval(X_LOGIN), quote(getval(X_KEY))));
  putval("script", HTML_script->str, RC_bWRITE);

#endif

  page_setup(op, subop);
 End:
  str_delete(HTML_script);
  str_delete(HTML_script_op);
  str_delete(HTML_script_subop);
  str_delete(HTML_location);
  str_delete(HTML_error);
  str_delete(HTML_script_arg1);
  str_delete(HTML_script_arg2);

  ring_delete(ring);

  exit(0);
}

void
page_setup(char *op, char *subop)
{
  Menu *menu;

  menu = op2menu(top_menu, subop);
  if(!menu)
    menu = op2menu(top_menu, op);

  if(menu->idx >= 0){
    char *p;
    Env *e;
    int ok_status = CONT;
    char *okarg = NULL;

    e = envtop.next;
    while(e && e->key){
      if(e->key && !strncmp(e->key, "s_ok", 4)){
	okarg = my_strdup(e->key + 4);
	p = index(okarg, '=');
	if(p)
	  *p = '\0';
	break;
      }
      e = e->next;
    }
    if(okarg){
      if(err_chk(HTML_script_op->str, okarg))
	ok_status = NG;
      else if(menu->ok_hook)
	ok_status = menu->ok_hook(okarg);
    }
    else if(d_flg){
      if(menu->del_hook)
	menu->del_hook(NULL);
    }
    if(okarg)
      my_free(okarg);

    if(ok_status == OK_SAVE){
      char *save_mode;
      char *save_cmd = "";
      int fd;

      /*
	/etc/flashcfgが存在するか否かを確認
	存在しない場合や、サイズが 0の場合は flashcfgを実行しない
       */
      if((fd = open(ETC_FLASHCFG, O_RDONLY)) >= 0){
	   int len;
	   len = lseek(fd, 0, SEEK_END);
	   close(fd);
	   if(len > 0)
		save_cmd = R_sprintf("%s %s > /dev/null 2>&1", SBIN_FLASHCFG_SAVE, ETC_FLASHCFG);
      }
#ifdef DEBUG
      fprintf(stderr, "%s\n", save_cmd);
#endif

      output_header("", "");
      output_tab(top_menu, op, subop);

      printf("<h1>完了</h1>\n");
      output_body("ok3.t");

      save_mode = getval(X_SAVE_MODE);
      switch(*save_mode){
      default:
      case '1':
	yazaki_main();
	sysupdate();
	if(fd >= 0){
	     chdir("/etc");
	     system(save_cmd);
	}
	break;
      case '2':
	yazaki_main();
	sysupdate();
	if(fd >= 0){
	     chdir("/etc");
	     system(save_cmd);
	}
	strcpy(shutdown_arg, "-r");
	break;
      case '3':
	yazaki_main();
	sysupdate();
	if(fd >= 0){
	     chdir("/etc");
	     system(save_cmd);
	}
	strcpy(shutdown_arg, "-h");
	break;
      case '4':
	strcpy(shutdown_arg, "-h");
	break;
      case '5':
	{
	  FILE *def;
	  FILE *rc;
	  int c;
	  
	  def = fopen(RC_CONF_DEFAULT, "r");
	  rc = fopen(RC_CONF, "w");
	  while((c = fgetc(def)) != EOF)
	    fputc(c, rc);
	  fclose(rc);
	  fclose(def);
	}
	break;
      }

      output_footer();
    }
    else if(ok_status == OK || ok_status == OK_NOSAVE){
      output_header("", "");
      output_tab(top_menu, op, subop);
      
      if(is_updateval() == 3){
	printf("<h1>以下のように設定しました</h1>\n");
	output_change(HTML_script_op->str);
      }
      else{
	printf("<h1>変更点はありません</h1>\n");
      }
      output_footer();
    }
    else if(ok_status == NG){
      output_header("", "");
      output_tab(top_menu, op, subop);
      printf("<P>%s<P>\n", HTML_error->str);
      output_footer();
    }
    else{
      if(!strcmp(op, "system"))
	output_header("onLoad=\"timeform()\"", (char *)update_timer);
      else
	output_header("", "");

      output_tab(top_menu, op, subop);
      printf("<h1>%s</h1>\n", quote(menu->str));
      output_body(menu->tmpl);
      output_footer();
    }
  }

  if(shutdown_arg[0]){
    sigsetmask(sigmask(SIGTERM));
    if(fork()==0){
      close(0);
      close(1);
      close(2);
      sleep(3);
      //      system(shutdown_cmd);
      execl("/sbin/shutdown", "shutdown", shutdown_arg, "now", NULL);
    }
  }
 
  exit(0);
}

void
page_cannot_access(char *op)
{
  output_header("", "");
  printf("<TABLE WIDTH=\"100%%\" border=0 cellpadding=4 cellspacing=0>\n");
  printf("<TR><TD BGCOLOR=\"%s\">&nbsp;</TD></TR>\n", COLOR_C1);
  printf("</TABLE>\n");

  printf("<H1>アクセスエラー</H1>\n");
  printf("<P>\n");
  printf("設定メニューはイーサネット%s ポート%d からしか使用できません",op,HTTPD_PORT);
  printf("<P>\n");
  output_footer();
}

void
page_login(char *op)
{
  output_header("", "");
  printf("<TABLE WIDTH=\"100%%\" border=0 cellpadding=4 cellspacing=0>\n");
  printf("<TR><TD BGCOLOR=\"%s\">&nbsp;</TD></TR>\n", COLOR_C1);
  printf("</TABLE>\n");

  output_body("login");
  output_footer();
}

void
page_badpasswd(char *op)
{
  output_header("", "");
  printf("<TABLE WIDTH=\"100%%\" border=0 cellpadding=4 cellspacing=0>\n");
  printf("<TR><TD BGCOLOR=\"%s\">&nbsp;</TD></TR>\n", COLOR_C1);
  printf("</TABLE>\n");

  output_body("badpasswd");
  output_footer();
}
