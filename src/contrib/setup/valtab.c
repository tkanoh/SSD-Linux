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
  static char *err_msg = "�ѥ��ε��Ҥ��ְ�äƤ��ޤ�";
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
  static char *err_msg = "�ۥ���̾�ε��Ҥ��ְ�äƤ��ޤ�";

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
  static char *err_msg = "IP���ɥ쥹�ε��Ҥ��ְ�äƤ��ޤ� (%s)";
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
      return R_sprintf("�ͤε��Ҥ��ְ�äƤ��ޤ� (%s)", val0);
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
    return "UID��32768����60000�δ֤ο�������ꤷ�Ƥ�������";
  if(getpwuid(v))
    return "����UID�Ϥ��Ǥ˻Ȥ��Ƥ��ޤ�";

  return NULL;
}

char *
is_login(const char *key, const char *desc)
{
  char *p;
  char *val;

  val = getval(key);

  if(strlen(val) > 8)
    return "Ĺ�������¤�ۤ��Ƥ��ޤ�";

  p = val;
  if(!isalpha(*p))
    return "�ѻ��ǻϤޤäƤ��ޤ���";

  while(*p){
    if(!isalnum(*p) && *p != '_')
      return "���ѤǤ��ʤ�ʸ�����ޤޤ�Ƥ��ޤ�";
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
      return R_sprintf("%s�˻Ȥ��ʤ�ʸ�����ޤޤ�Ƥ��ޤ�", desc);
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
  "IP�ޥ����졼�ɤ���Ѥ��ʤ�",
  "eth0->eth1",
  "eth1->eth0"
};

static char *eth_typ[] = {
  "",
  "DHCP�����Ѥ���",
  "��ư�ǻ��ꤹ��"
};

static VTab vtab[] = {
  {"x_user_id", "UID", "", VC_USER, VCF_NOTNULL, is_uid, NULL},
  {"x_user_login___T", "������̾", "", VC_USER, VCF_NOTNULL, is_login, NULL},
  {"x_user_name___T", "�桼��̾", "", VC_USER, VCF_NOTNULL, is_print, NULL},
  {"x_user_passwd___T", "�ѥ����", "", VC_USER, VCF_NOTNULL, is_print, NULL},
  {"x_user_passwd2___T", "�ѥ����2", "", VC_USER, VCF_NOTNULL, is_print, NULL},

  {"x_defaultroute_adr", "�ǥե���ȥ롼��", "", VC_NETWORK, VCF_NOTNULL, is_ip4, NULL},
  {"x_defaultroute_interface", "�ǥե���ȥ롼�����󥿥ե�����", "", VC_NETWORK, 0, NULL, NULL},

  {"x_eth_typ__eth0", "eth0 �⡼��", "", VC_NETWORK, 0, NULL, eth_typ},
  {"x_eth_adr__eth0", "eth0 IP���ɥ쥹", "", VC_NETWORK, 0, chk_eth0, NULL},
  
  
  {"x_eth_subnet_mask__eth0", "eth0 �ͥåȥޥ���", "", VC_NETWORK, 0, NULL, NULL},

  {"x_eth_typ__eth1", "eth1 �⡼��", "", VC_NETWORK, 0, NULL, eth_typ},
  {"x_eth_adr__eth1", "eth1 IP���ɥ쥹", "", VC_NETWORK, 0, chk_eth1, NULL},
  {"x_eth_subnet_mask__eth1", "eth1 �ͥåȥޥ���", "", VC_NETWORK, 0, NULL, NULL},

  {"x_nameserver3", "�͡��ॵ����3", "", VC_NETWORK, 0, is_ip4, NULL},
  {"x_nameserver2", "�͡��ॵ����2", "", VC_NETWORK, 0, is_ip4, NULL},
  {"x_nameserver", "�͡��ॵ����", "", VC_NETWORK, 0, is_ip4, NULL},
  {"x_domain", "�ɥᥤ��̾", "", VC_NETWORK, 0, is_hostname, NULL},

  {"x_ipv6_enable__eth0", "eth0��IPv6��ͭ���ˤ���", "", VC_IPV6, 0, NULL, NULL},
  {"x_ipv6_enable__eth1", "eth1��IPv6��ͭ���ˤ���", "", VC_IPV6, 0, NULL, NULL},
  {"x_ipv6_prefix__eth0", "eth0��prefix", "", VC_IPV6, 0, NULL, NULL},
  {"x_ipv6_prefix__eth1", "eth1��prefix", "", VC_IPV6, 0, NULL, NULL},
  {"x_ipv6_local__eth0", "eth0��local address", "", VC_IPV6, 0, NULL, NULL},
  {"x_ipv6_local__eth1", "eth1��local address", "", VC_IPV6, 0, NULL, NULL},
  {"x_ipv6_tunnel", "IPv4 over IPv6�ȥ�ͥ����Ѥ���", "", VC_IPV6, 0, NULL, NULL},
  {"x_ipv6_tunnel_here", "�ȥ�ͥ뼫ʬ¦IPv4���ɥ쥹", "", VC_IPV6, VCF_NOTNULL_V6TUN, is_ip4, NULL},
  {"x_ipv6_tunnel_there", "�ȥ�ͥ����¦IPv4���ɥ쥹", "", VC_IPV6, VCF_NOTNULL_V6TUN, is_ip4, NULL},

  {"x_hostname", "�ۥ���̾", "", VC_SYSTEM, VCF_NOTNULL, is_hostname, NULL},
  {"x_domainname", "�ɥᥤ��̾", "", VC_SYSTEM, VCF_NOTNULL, is_hostname, NULL},
  {"x_year", "ǯ", "", VC_SYSTEM, 0, NULL, NULL},
  {"x_mon", "��", "", VC_SYSTEM, 0, NULL, NULL},
  {"x_mday", "��", "", VC_SYSTEM, 0, NULL, NULL},
  {"x_hour", "��", "", VC_SYSTEM, 0, NULL, NULL},
  {"x_min", "ʬ", "", VC_SYSTEM, 0, NULL, NULL},
  {"x_sec", "��", "", VC_SYSTEM, 0, NULL, NULL},
  {"x_ntp_hostname", "�ΣԣХ�����", "", VC_SYSTEM , 0, is_ip4, NULL},

  {"x_msq_typ", "IP�ޥ����졼��", "", VC_MASQ, VCF_NOTNULL, NULL, msq_typ},

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
  {"x_fw_action___T", "ư��", "", VC_FW, VCF_NOTNULL, NULL, NULL},

  {"x_dhcpd_enable", "dhcpd����Ѥ���", "", VC_DHCPD, VCF_NOTNULL, NULL, NULL},
  {"x_dhcpd_eth0_enable", "eth0¦��dhcpd����Ѥ���", "", VC_DHCPD, VCF_NOTNULL, NULL, NULL},
  {"x_dhcpd_eth0_range1", "eth0 �ϰ�", "", VC_DHCPD, VCF_NOTNULL_DHCP0, is_ip4, NULL},
  {"x_dhcpd_eth0_range2", "eth0 �ϰ�", "", VC_DHCPD, VCF_NOTNULL_DHCP0, is_ip4, NULL},
  {"x_dhcpd_eth0_nameserver", "eth0 �͡��ॵ����", "", VC_DHCPD, 0, is_ip4, NULL},
  {"x_dhcpd_eth0_domainname", "eth0 �ɥᥤ��̾", "", VC_DHCPD, 0, is_hostname, NULL},
  {"x_dhcpd_eth0_routers", "eth1 �����ȥ�����", "", VC_DHCPD, 0, is_ip4, NULL},
  {"x_dhcpd_eth0_subnet_mask", "eth1 �ͥåȥޥ���", "", VC_DHCPD, 0, NULL, NULL},
  {"x_dhcpd_eth1_enable", "eth1¦��dhcpd����Ѥ���", "", VC_DHCPD, VCF_NOTNULL, NULL, NULL},
  {"x_dhcpd_eth1_range1", "eth1 �ϰ�", "", VC_DHCPD, VCF_NOTNULL_DHCP1, is_ip4, NULL},
  {"x_dhcpd_eth1_range2", "eth1 �ϰ�", "", VC_DHCPD, VCF_NOTNULL_DHCP1, is_ip4, NULL},
  {"x_dhcpd_eth1_nameserver", "eth1 �͡��ॵ����", "", VC_DHCPD, 0, is_ip4, NULL},
  {"x_dhcpd_eth1_domainname", "eth1 �ɥᥤ��̾", "", VC_DHCPD, 0, is_hostname, NULL},
  {"x_dhcpd_eth1_routers", "eth1 �����ȥ�����", "", VC_DHCPD, 0, is_ip4, NULL},
  {"x_dhcpd_eth1_subnet_mask", "eth1 �ͥåȥޥ���", "", VC_DHCPD, 0, NULL, NULL},

  {"x_dhcpd_enable__eth0", "eth0¦��dhcpd����Ѥ���", "", VC_DHCPD, VCF_NOTNULL, NULL, NULL},
  {"x_dhcpd_range1__eth0", "eth0 �ϰ�", "", VC_DHCPD, VCF_NOTNULL_DHCP0, is_ip4, NULL},
  {"x_dhcpd_range2__eth0", "eth0 �ϰ�", "", VC_DHCPD, VCF_NOTNULL_DHCP0, is_ip4, NULL},
  {"x_dhcpd_nameserver__eth0", "eth0 �͡��ॵ����", "", VC_DHCPD, 0, is_ip4, NULL},
  {"x_dhcpd_domainname__eth0", "eth0 �ɥᥤ��̾", "", VC_DHCPD, 0, is_hostname, NULL},
  {"x_dhcpd_routers__eth0", "eth0 �����ȥ�����", "", VC_DHCPD, 0, is_ip4, NULL},
  {"x_dhcpd_subnet_mask__eth0", "eth0 �ͥåȥޥ���", "", VC_DHCPD, 0, is_ip4, NULL},
  {"x_dhcpd_enable__eth1", "eth1¦��dhcpd����Ѥ���", "", VC_DHCPD, VCF_NOTNULL, NULL, NULL},
  {"x_dhcpd_range1__eth1", "eth1 �ϰ�", "", VC_DHCPD, VCF_NOTNULL_DHCP1, is_ip4, NULL},
  {"x_dhcpd_range2__eth1", "eth1 �ϰ�", "", VC_DHCPD, VCF_NOTNULL_DHCP1, is_ip4, NULL},
  {"x_dhcpd_nameserver__eth1", "eth1 �͡��ॵ����", "", VC_DHCPD, 0, is_ip4, NULL},
  {"x_dhcpd_domainname__eth1", "eth1 �ɥᥤ��̾", "", VC_DHCPD, 0, is_hostname, NULL},
  {"x_dhcpd_routers__eth1", "eth1 �����ȥ�����", "", VC_DHCPD, 0, is_ip4, NULL},
  {"x_dhcpd_subnet_mask__eth1", "eth1 �ͥåȥޥ���", "", VC_DHCPD, 0, NULL, NULL},

  {"x_sendmail_enable", "sendmail����Ѥ���", "", VC_SENDMAIL, VCF_NOTNULL, NULL, NULL},
  {"x_sendmail_my_official_smtp_hostname", "�ۥ���̾(FQDN)", "", VC_SENDMAIL, VCF_NOTNULL, is_hostname, NULL},
  {"x_sendmail_local_domain_name", "�ɥᥤ��̾", "", VC_SENDMAIL, VCF_NOTNULL, is_hostname, NULL},
  {"x_sendmail_domain_alias1", "��̾�ɥᥤ��̾", "", VC_SENDMAIL, 0, is_hostname, NULL},
  {"x_sendmail_relay_id", NULL, "", VC_SENDMAIL, VCF_NOTNULL, NULL, NULL},
  {"x_sendmail_relay___T", "��졼���ĥۥ���", "", VC_SENDMAIL, VCF_NOTNULL, is_hostname, NULL},

  {"x_named_enable", "named����Ѥ���", "", VC_NAMED, VCF_NOTNULL, NULL, NULL},
  {"x_named_zone_id", NULL, "", VC_NAMED, VCF_NOTNULL, NULL, NULL},
  {"x_named_zone_name___T", "������̾", "", VC_NAMED, VCF_NOTNULL, is_hostname, NULL},
  {"x_named_zone_typ___T", NULL, "", VC_NAMED, VCF_NOTNULL, NULL, NULL},

  {"x_named_zone_record_id", NULL, "", VC_NAMED, VCF_NOTNULL, NULL, NULL},
  {"x_named_zone_record_domain___T", "�쥳����", "", VC_NAMED, 0, is_hostname, NULL},
  {"x_named_zone_record_typ___T", "�쥳���ɼ���", "", VC_NAMED, VCF_NOTNULL, NULL, NULL},
  {"x_named_zone_record_resource___T", "�쥳����", "", VC_NAMED, VCF_NOTNULL, NULL, NULL},

  {"x_named_zone_soa_mname__", "�ۥ���̾", "", VC_NAMED, VCF_NOTNULL, is_hostname, NULL},
  {"x_named_zone_soa_rname__", "�᡼�롦���ɥ쥹", "", VC_NAMED, VCF_NOTNULL, is_hostname, NULL},

  {"x_named_zone_master__", "�ޥ���DNS������", "", VC_NAMED, VCF_NOTNULL, is_ip4, NULL},

  {"x_httpd_enable", "httpd����Ѥ���", "", VC_HTTPD, VCF_NOTNULL, NULL, NULL},
  {"x_httpd_chroot", "Data Diectory �� chroot ����", "", VC_HTTPD, VCF_NOTNULL, NULL, NULL},
  {"x_httpd_dir", "dir=", "", VC_HTTPD, VCF_NOTNULL, is_unixpath, NULL},
  {"x_httpd_cgipat", "cgipat=", "", VC_HTTPD, VCF_NOTNULL, is_unixpath, NULL},
  {"x_httpd_logfile", "logfile=", "", VC_HTTPD, VCF_NOTNULL, is_unixpath, NULL},

  {"x_samba_enable", "samba����Ѥ���", "", VC_SAMBA, VCF_NOTNULL, NULL, NULL},
  {"x_samba_workgroup", "������롼��̾", "", VC_SAMBA, VCF_NOTNULL, is_hostname, NULL},
  {"x_samba_nmbd_enable", "nmbd����Ѥ���", "", VC_SAMBA, VCF_NOTNULL, NULL, NULL},
  {"x_netatalk_enable", "NETATALK����Ѥ���", "", VC_SAMBA, VCF_NOTNULL, NULL, NULL},

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
	    return R_sprintf("<B>%s:</B>&nbsp;%s", v->desc ? v->desc : v->key, "�ͤ����Ϥ��Ƥ�������");
	  case VCF_NOTNULL_DHCP0:
	    p = getval(X_DHCPD_ENABLE__ETH0);
	    if ((p == NULL) || (*p == '\0')) {
	      ret = NULL;
	      break;
	    }
	    if(!strcasecmp(p, "YES"))
	      return R_sprintf("<B>%s:</B>&nbsp;%s", v->desc ? v->desc : v->key, "�ͤ����Ϥ��Ƥ�������");
	    ret = NULL;
	    break;
	  case VCF_NOTNULL_DHCP1:
	    p = getval(X_DHCPD_ENABLE__ETH1);
	    if ((p == NULL) || (*p == '\0')) {
	      ret = NULL;
	      break;
	    }
	    if(!strcasecmp(p, "YES"))
	      return R_sprintf("<B>%s:</B>&nbsp;%s", v->desc ? v->desc : v->key, "�ͤ����Ϥ��Ƥ�������");
	    ret = NULL;
	    break;
	  case VCF_NOTNULL_V6TUN:
	    p = getval(X_IPV6_TUNNEL);
	    if ((p == NULL) || (*p == '\0')) {
	      ret = NULL;
	      break;
	    }
	    if(!strcasecmp(p, "YES"))
	      return R_sprintf("<B>%s:</B>&nbsp;%s", v->desc ? v->desc : v->key, "�ͤ����Ϥ��Ƥ�������");
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
  return R_sprintf("<B>%s:</B>&nbsp;����ʥ����ƥ२�顼", key);
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
	str_append_charp(HTML_error, R_sprintf("<FONT COLOR=red><B>���顼</B></FONT>&nbsp;%s<BR>\n", ret));
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
  printf("<P><FONT COLOR=red>�������¸���Ƶ�ư�塢ͭ���Ȥʤ�ޤ���</FONT>\n");
}
