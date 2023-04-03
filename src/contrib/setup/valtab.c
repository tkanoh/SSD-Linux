/*
	$Id: valtab.c,v 1.25 2004/11/29 07:57:57 todoroki Exp $
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pwd.h>
#include "setup.h"

char *
is_unixpath(const char *key, const char *desc)
{
  static char *err_msg = "パスの記述が間違っています";
  char *p;

  p = getval(key);
  while(*p){
    if(*p < 0x20)
      return err_msg;
    ++p;
  }
  return NULL;
}

char *
is_hostname(const char *key, const char *desc)
{
  char *p;
  static char *err_msg = "ホスト名の記述が間違っています";

  p = getval(key);
  while(*p){
    if(!isalnum(*p) && *p != '-' && *p != '.')
      return err_msg;
    ++p;
  }
  return NULL;
}

char *
is_ip4(const char *key, const char *desc)
{
  static char *err_msg = "IPアドレスの記述が間違っています (%s)";
  char	num[8];
  char *val;
  char	*p, c;
  int	i, j, k;

  val = p = getval(key);
  for ( k = 0; k < 4; k++ )
  {
    for ( i = 0; i < 7; i++ )
    {
      c = *p++;
      if ( c == '.' || c == 0x00 ) { break; }
      if ( !isdigit(c) ) { return R_sprintf(err_msg, val); }
      num[i] = c;
    }
    if ( i >= 4 || !i ) { return R_sprintf(err_msg, val); }
/*    if ( ( c == 0x00 ) && ( k != 3 ) ) { return R_sprintf(err_msg, val); } */

    num[i] = 0x00;
    j = sscanf( num, "%d", &i );
    if ( j != 1 ) { return R_sprintf(err_msg, val); }
    if ( i > 255 ) { return R_sprintf(err_msg, val); }
  }
  return NULL;
}

char *
is_ip4_2(const char *key, const char *desc)
{
  char	*p;

  p = getval(key);
  if(!strcasecmp(p, "ANY"))
    return NULL;

  return is_ip4(key, desc);
}

char *
is_numeric(const char *key, const char *desc)
{
  char *val0;
  char *val;

  val0 = val = getval(key);
  while(*val){
    if(!isdigit(*val) && !isspace(*val))
      return R_sprintf("値の記述が間違っています (%s)", val0);
    ++val;
  }

  return NULL;
}

char *
is_port(const char *key, const char *desc)
{
  char *p;
  p = getval(key);
  if(!strcasecmp(p, "ANY"))
    return NULL;

  return is_numeric(key, desc);
}

char *
is_uid(const char *key, const char *desc)
{
  int v;

  v = getval_int(key);

  if(v < 32768 || v > 60000)
    return "UIDは32768から60000の間の数字を指定してください";
  if(getpwuid(v))
    return "そのUIDはすでに使われています";

  return NULL;
}

char *
is_login(const char *key, const char *desc)
{
  char *p;
  char *val;

  val = getval(key);

  if(strlen(val) > 8)
    return "長さの制限を越えています";

  p = val;
  if(!isalpha(*p))
    return "英字で始まっていません";

  while(*p){
    if(!isalnum(*p) && *p != '_')
      return "使用できない文字が含まれています";
    ++p;
  }

  return NULL;
}

char *
is_print(const char *key, const char *desc)
{
  char *p;
  char *val;

  val = getval(key);

  p = val;
  while(*p){
    if(!isprint(*p))
      return R_sprintf("%sに使えない文字が含まれています", desc);
    ++p;
  }

  return NULL;
}

char *
chk_eth0(const char *key, const char *desc)
{
  char typ;

  typ = my_atoi(getval(X_ETH_TYP__ETH0));
  if(typ == 1)
    return NULL;

  return is_ip4(key, desc);
}

char *
chk_eth1(const char *key, const char *desc)
{
  char typ;

  typ = my_atoi(getval(X_ETH_TYP__ETH1));
  if(typ == 1)
    return NULL;

  return is_ip4(key, desc);
}

static char *msq_typ[] = {
  "",
  "IPマスカレードを使用しない",
  "eth0->eth1",
  "eth1->eth0"
};

static char *eth_typ[] = {
  "",
  "DHCPを利用する",
  "手動で指定する"
};

static VTab vtab[] = {
  {"x_user_id", "UID", "", VC_USER, VCF_NOTNULL, is_uid, NULL},
  {"x_user_login___T", "ログイン名", "", VC_USER, VCF_NOTNULL, is_login, NULL},
  {"x_user_name___T", "ユーザ名", "", VC_USER, VCF_NOTNULL, is_print, NULL},
  {"x_user_passwd___T", "パスワード", "", VC_USER, VCF_NOTNULL, is_print, NULL},
  {"x_user_passwd2___T", "パスワード2", "", VC_USER, VCF_NOTNULL, is_print, NULL},

  {"x_defaultroute_adr", "デフォルトルータ", "", VC_NETWORK, VCF_NOTNULL, is_ip4, NULL},
  {"x_defaultroute_interface", "デフォルトルータインタフェース", "", VC_NETWORK, 0, NULL, NULL},

  {"x_eth_typ__eth0", "eth0 モード", "", VC_NETWORK, 0, NULL, eth_typ},
  {"x_eth_adr__eth0", "eth0 IPアドレス", "", VC_NETWORK, 0, chk_eth0, NULL},
  
  
  {"x_eth_subnet_mask__eth0", "eth0 ネットマスク", "", VC_NETWORK, 0, NULL, NULL},

  {"x_eth_typ__eth1", "eth1 モード", "", VC_NETWORK, 0, NULL, eth_typ},
  {"x_eth_adr__eth1", "eth1 IPアドレス", "", VC_NETWORK, 0, chk_eth1, NULL},
  {"x_eth_subnet_mask__eth1", "eth1 ネットマスク", "", VC_NETWORK, 0, NULL, NULL},

  {"x_nameserver3", "ネームサーバ3", "", VC_NETWORK, 0, is_ip4, NULL},
  {"x_nameserver2", "ネームサーバ2", "", VC_NETWORK, 0, is_ip4, NULL},
  {"x_nameserver", "ネームサーバ", "", VC_NETWORK, 0, is_ip4, NULL},
  {"x_domain", "ドメイン名", "", VC_NETWORK, 0, is_hostname, NULL},

  {"x_ipv6_enable__eth0", "eth0のIPv6を有効にする", "", VC_IPV6, 0, NULL, NULL},
  {"x_ipv6_enable__eth1", "eth1のIPv6を有効にする", "", VC_IPV6, 0, NULL, NULL},
  {"x_ipv6_prefix__eth0", "eth0のprefix", "", VC_IPV6, 0, NULL, NULL},
  {"x_ipv6_prefix__eth1", "eth1のprefix", "", VC_IPV6, 0, NULL, NULL},
  {"x_ipv6_local__eth0", "eth0のlocal address", "", VC_IPV6, 0, NULL, NULL},
  {"x_ipv6_local__eth1", "eth1のlocal address", "", VC_IPV6, 0, NULL, NULL},
  {"x_ipv6_tunnel", "IPv4 over IPv6トンネルを使用する", "", VC_IPV6, 0, NULL, NULL},
  {"x_ipv6_tunnel_here", "トンネル自分側IPv4アドレス", "", VC_IPV6, VCF_NOTNULL_V6TUN, is_ip4, NULL},
  {"x_ipv6_tunnel_there", "トンネル相手側IPv4アドレス", "", VC_IPV6, VCF_NOTNULL_V6TUN, is_ip4, NULL},

  {"x_hostname", "ホスト名", "", VC_SYSTEM, VCF_NOTNULL, is_hostname, NULL},
  {"x_domainname", "ドメイン名", "", VC_SYSTEM, VCF_NOTNULL, is_hostname, NULL},
  {"x_year", "年", "", VC_SYSTEM, 0, NULL, NULL},
  {"x_mon", "月", "", VC_SYSTEM, 0, NULL, NULL},
  {"x_mday", "日", "", VC_SYSTEM, 0, NULL, NULL},
  {"x_hour", "時", "", VC_SYSTEM, 0, NULL, NULL},
  {"x_min", "分", "", VC_SYSTEM, 0, NULL, NULL},
  {"x_sec", "秒", "", VC_SYSTEM, 0, NULL, NULL},
  {"x_ntp_hostname", "ＮＴＰサーバ", "", VC_SYSTEM , 0, is_ip4, NULL},

  {"x_msq_typ", "IPマスカレード", "", VC_MASQ, VCF_NOTNULL, NULL, msq_typ},

  {"x_portfw_id", NULL, "", VC_FW, VCF_NOTNULL, NULL, NULL},
  {"x_portfw_proto___T", NULL, "", VC_FW, VCF_NOTNULL, NULL, NULL},
  {"x_portfw_interface___T", NULL, "", VC_FW, VCF_NOTNULL, NULL, NULL},
  {"x_portfw_src_port___T", "source port", "", VC_FW, VCF_NOTNULL, is_numeric, NULL},
  {"x_portfw_dst_ip___T", "destination IP", "", VC_FW, VCF_NOTNULL, is_ip4, NULL},
  {"x_portfw_dst_port___T", "destination port", "", VC_FW, VCF_NOTNULL, is_numeric, NULL},

  {"x_fw_id", NULL, "", VC_FW, VCF_NOTNULL, NULL, NULL},
  {"x_fw_proto___T", NULL, "", VC_FW, VCF_NOTNULL, NULL, NULL},
  {"x_fw_src_ip___T", "source IP", "", VC_FW, VCF_NOTNULL, is_ip4_2, NULL},
  {"x_fw_src_subnet_mask___T", NULL, "", VC_FW, VCF_NOTNULL, NULL, NULL},
  {"x_fw_src_port___T", "source port", "", VC_FW, VCF_NOTNULL, is_port, NULL},
  {"x_fw_dst_ip___T", "destination ip", "", VC_FW, VCF_NOTNULL, is_ip4_2, NULL},
  {"x_fw_dst_subnet_mask___T", NULL, "", VC_FW, VCF_NOTNULL, NULL, NULL},
  {"x_fw_dst_port___T", "destination port", "", VC_FW, VCF_NOTNULL, is_port, NULL},
  {"x_fw_action___T", "動作", "", VC_FW, VCF_NOTNULL, NULL, NULL},

  {"x_dhcpd_enable", "dhcpdを使用する", "", VC_DHCPD, VCF_NOTNULL, NULL, NULL},
  {"x_dhcpd_eth0_enable", "eth0側でdhcpdを使用する", "", VC_DHCPD, VCF_NOTNULL, NULL, NULL},
  {"x_dhcpd_eth0_range1", "eth0 範囲", "", VC_DHCPD, VCF_NOTNULL_DHCP0, is_ip4, NULL},
  {"x_dhcpd_eth0_range2", "eth0 範囲", "", VC_DHCPD, VCF_NOTNULL_DHCP0, is_ip4, NULL},
  {"x_dhcpd_eth0_nameserver", "eth0 ネームサーバ", "", VC_DHCPD, 0, is_ip4, NULL},
  {"x_dhcpd_eth0_domainname", "eth0 ドメイン名", "", VC_DHCPD, 0, is_hostname, NULL},
  {"x_dhcpd_eth0_routers", "eth1 ゲートウェイ", "", VC_DHCPD, 0, is_ip4, NULL},
  {"x_dhcpd_eth0_subnet_mask", "eth1 ネットマスク", "", VC_DHCPD, 0, NULL, NULL},
  {"x_dhcpd_eth1_enable", "eth1側でdhcpdを使用する", "", VC_DHCPD, VCF_NOTNULL, NULL, NULL},
  {"x_dhcpd_eth1_range1", "eth1 範囲", "", VC_DHCPD, VCF_NOTNULL_DHCP1, is_ip4, NULL},
  {"x_dhcpd_eth1_range2", "eth1 範囲", "", VC_DHCPD, VCF_NOTNULL_DHCP1, is_ip4, NULL},
  {"x_dhcpd_eth1_nameserver", "eth1 ネームサーバ", "", VC_DHCPD, 0, is_ip4, NULL},
  {"x_dhcpd_eth1_domainname", "eth1 ドメイン名", "", VC_DHCPD, 0, is_hostname, NULL},
  {"x_dhcpd_eth1_routers", "eth1 ゲートウェイ", "", VC_DHCPD, 0, is_ip4, NULL},
  {"x_dhcpd_eth1_subnet_mask", "eth1 ネットマスク", "", VC_DHCPD, 0, NULL, NULL},

  {"x_dhcpd_enable__eth0", "eth0側でdhcpdを使用する", "", VC_DHCPD, VCF_NOTNULL, NULL, NULL},
  {"x_dhcpd_range1__eth0", "eth0 範囲", "", VC_DHCPD, VCF_NOTNULL_DHCP0, is_ip4, NULL},
  {"x_dhcpd_range2__eth0", "eth0 範囲", "", VC_DHCPD, VCF_NOTNULL_DHCP0, is_ip4, NULL},
  {"x_dhcpd_nameserver__eth0", "eth0 ネームサーバ", "", VC_DHCPD, 0, is_ip4, NULL},
  {"x_dhcpd_domainname__eth0", "eth0 ドメイン名", "", VC_DHCPD, 0, is_hostname, NULL},
  {"x_dhcpd_routers__eth0", "eth0 ゲートウェイ", "", VC_DHCPD, 0, is_ip4, NULL},
  {"x_dhcpd_subnet_mask__eth0", "eth0 ネットマスク", "", VC_DHCPD, 0, is_ip4, NULL},
  {"x_dhcpd_enable__eth1", "eth1側でdhcpdを使用する", "", VC_DHCPD, VCF_NOTNULL, NULL, NULL},
  {"x_dhcpd_range1__eth1", "eth1 範囲", "", VC_DHCPD, VCF_NOTNULL_DHCP1, is_ip4, NULL},
  {"x_dhcpd_range2__eth1", "eth1 範囲", "", VC_DHCPD, VCF_NOTNULL_DHCP1, is_ip4, NULL},
  {"x_dhcpd_nameserver__eth1", "eth1 ネームサーバ", "", VC_DHCPD, 0, is_ip4, NULL},
  {"x_dhcpd_domainname__eth1", "eth1 ドメイン名", "", VC_DHCPD, 0, is_hostname, NULL},
  {"x_dhcpd_routers__eth1", "eth1 ゲートウェイ", "", VC_DHCPD, 0, is_ip4, NULL},
  {"x_dhcpd_subnet_mask__eth1", "eth1 ネットマスク", "", VC_DHCPD, 0, NULL, NULL},

  {"x_sendmail_enable", "sendmailを使用する", "", VC_SENDMAIL, VCF_NOTNULL, NULL, NULL},
  {"x_sendmail_my_official_smtp_hostname", "ホスト名(FQDN)", "", VC_SENDMAIL, VCF_NOTNULL, is_hostname, NULL},
  {"x_sendmail_local_domain_name", "ドメイン名", "", VC_SENDMAIL, VCF_NOTNULL, is_hostname, NULL},
  {"x_sendmail_domain_alias1", "別名ドメイン名", "", VC_SENDMAIL, 0, is_hostname, NULL},
  {"x_sendmail_relay_id", NULL, "", VC_SENDMAIL, VCF_NOTNULL, NULL, NULL},
  {"x_sendmail_relay___T", "リレー許可ホスト", "", VC_SENDMAIL, VCF_NOTNULL, is_hostname, NULL},

  {"x_named_enable", "namedを使用する", "", VC_NAMED, VCF_NOTNULL, NULL, NULL},
  {"x_named_zone_id", NULL, "", VC_NAMED, VCF_NOTNULL, NULL, NULL},
  {"x_named_zone_name___T", "ゾーン名", "", VC_NAMED, VCF_NOTNULL, is_hostname, NULL},
  {"x_named_zone_typ___T", NULL, "", VC_NAMED, VCF_NOTNULL, NULL, NULL},

  {"x_named_zone_record_id", NULL, "", VC_NAMED, VCF_NOTNULL, NULL, NULL},
  {"x_named_zone_record_domain___T", "レコード", "", VC_NAMED, 0, is_hostname, NULL},
  {"x_named_zone_record_typ___T", "レコード種別", "", VC_NAMED, VCF_NOTNULL, NULL, NULL},
  {"x_named_zone_record_resource___T", "レコード", "", VC_NAMED, VCF_NOTNULL, NULL, NULL},

  {"x_named_zone_soa_mname__", "ホスト名", "", VC_NAMED, VCF_NOTNULL, is_hostname, NULL},
  {"x_named_zone_soa_rname__", "メール・アドレス", "", VC_NAMED, VCF_NOTNULL, is_hostname, NULL},

  {"x_named_zone_master__", "マスタDNSサーバ", "", VC_NAMED, VCF_NOTNULL, is_ip4, NULL},

  {"x_httpd_enable", "httpdを使用する", "", VC_HTTPD, VCF_NOTNULL, NULL, NULL},
  {"x_httpd_chroot", "Data Diectory に chroot する", "", VC_HTTPD, VCF_NOTNULL, NULL, NULL},
  {"x_httpd_dir", "dir=", "", VC_HTTPD, VCF_NOTNULL, is_unixpath, NULL},
  {"x_httpd_cgipat", "cgipat=", "", VC_HTTPD, VCF_NOTNULL, is_unixpath, NULL},
  {"x_httpd_logfile", "logfile=", "", VC_HTTPD, VCF_NOTNULL, is_unixpath, NULL},

  {"x_samba_enable", "sambaを使用する", "", VC_SAMBA, VCF_NOTNULL, NULL, NULL},
  {"x_samba_workgroup", "ワークグループ名", "", VC_SAMBA, VCF_NOTNULL, is_hostname, NULL},
  {"x_samba_nmbd_enable", "nmbdを使用する", "", VC_SAMBA, VCF_NOTNULL, NULL, NULL},
  {"x_netatalk_enable", "NETATALKを使用する", "", VC_SAMBA, VCF_NOTNULL, NULL, NULL},

  {"x_login", NULL, "", VC_LOGIN, VCF_NOTNULL | VCF_NODISP, NULL},
  {"x_passwd", NULL, "", VC_LOGIN, VCF_NOTNULL | VCF_NODISP, NULL},
  {"x_key", NULL, "", VC_LOGIN, 0, NULL},


  {NULL},
};

static char *
err_chk_sub(const char *key)
{
  char *val;
  char *p;
  char *ret;
  VTab *v;

  v = vtab;

  while(v->key){
    if(!strncmp(v->key, key, strlen(v->key))){
      val = getval(key);
      if ((val == NULL) || (*val == '\0')) {
	switch (v->flag & ~VCF_NODISP) {
	  case VCF_NOTNULL:
	    return R_sprintf("<B>%s:</B>&nbsp;%s", v->desc ? v->desc : v->key, "値を入力してください");
	  case VCF_NOTNULL_DHCP0:
	    p = getval(X_DHCPD_ENABLE__ETH0);
	    if ((p == NULL) || (*p == '\0')) {
	      ret = NULL;
	      break;
	    }
	    if(!strcasecmp(p, "YES"))
	      return R_sprintf("<B>%s:</B>&nbsp;%s", v->desc ? v->desc : v->key, "値を入力してください");
	    ret = NULL;
	    break;
	  case VCF_NOTNULL_DHCP1:
	    p = getval(X_DHCPD_ENABLE__ETH1);
	    if ((p == NULL) || (*p == '\0')) {
	      ret = NULL;
	      break;
	    }
	    if(!strcasecmp(p, "YES"))
	      return R_sprintf("<B>%s:</B>&nbsp;%s", v->desc ? v->desc : v->key, "値を入力してください");
	    ret = NULL;
	    break;
	  case VCF_NOTNULL_V6TUN:
	    p = getval(X_IPV6_TUNNEL);
	    if ((p == NULL) || (*p == '\0')) {
	      ret = NULL;
	      break;
	    }
	    if(!strcasecmp(p, "YES"))
	      return R_sprintf("<B>%s:</B>&nbsp;%s", v->desc ? v->desc : v->key, "値を入力してください");
	    ret = NULL;
	    break;
	  default:
	    ret = NULL;
	}
      } else {
	if(v->chk)
	  ret = v->chk(key, key);
        else
	  ret = NULL;
      }

      if(ret)
	return R_sprintf("<B>%s:</B>&nbsp;%s", v->desc ? v->desc : v->key, ret);
      else
	return NULL;
    }

    ++v;
  }
  return R_sprintf("<B>%s:</B>&nbsp;重大なシステムエラー", key);
}

int
err_chk(char *op, char *arg)
{
  Env *e = envtop.next;
  char *key;
  char *ret;
  int errflg = 0;

  while(e){
    if(e->flag == 3 && e->key[0] == 'i' && e->key[1] == '_'){
      key = my_strdup(e->key);
      key[0] = 'x';
      ret = err_chk_sub(key);
      my_free(key);
      if(ret){
	errflg = 1;
	str_append_charp(HTML_error, R_sprintf("<FONT COLOR=red><B>エラー</B></FONT>&nbsp;%s<BR>\n", ret));
      }
    }
    e = e->next;
  }

  return errflg;
}

void
output_change(char *op)
{
  Env *e = envtop.next;
  VTab *v;
  char *key;

  while(e){
    if(e->key[0] == 'i' && e->key[1] == '_'){
      key = my_strdup(e->key);
      key[0] = 'x';
      v = vtab;
      while(v->key && !(v->flag & VCF_NODISP)){
	if(!strncmp(v->key, key, strlen(key))){
	  if(v->valdesc)
	    printf("<B>%s:</B>&nbsp;%s<BR>\n", v->desc ? v->desc : v->key, v->valdesc[my_atoi(e->val)]);
	  else
	    printf("<B>%s:</B>&nbsp;%s<BR>\n", v->desc ? v->desc : v->key, e->val);
	  break;
	}
	++v;
      }
      my_free(key);
    }
    e = e->next;
  }
  printf("<P><FONT COLOR=red>設定は保存・再起動後、有効となります。</FONT>\n");
}
