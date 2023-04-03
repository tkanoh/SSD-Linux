/*
	$Id: rc2conf.c,v 1.23 2003/02/20 07:25:16 yamagata Exp $
 */

#include	<sys/types.h>
#include	<sys/file.h>
#include	<sys/stat.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<time.h>

#include	"setup.h"

typedef struct {
	char	*param;		/*���֤�������ʸ����ؤΥݥ��󥿡�*/
	char	*kstr;		/*���б���������ʸ����*/
	char	*key;		/*������ʸ����ؤΥݥ��󥿡�*/
} RENSOH;
/*----------------------------------------------------------------------------
valconv();
����
  �ե��������˵��Ҥ���Ƥ��륭�������Ƥ�getval()�������롢�������б�����
  �Ķ������ͤ��֤������ޤ���
����
  void valconv(FILE *out, FILE *in, RENSOH rensoh[], int num);
����
  out		���ϥե�����ݥ���
  in		���ϥե�����ݥ���
  rensoh	�����͡���Ϣ������
  num		rensoh�ο�
�����
  �ʤ�
----------------------------------------------------------------------------*/
void valconv(FILE *out, FILE *in, RENSOH rensoh[], int num)
{
	List	*l;
	char	param[1024];
	char	*rparam, *key, *tmp;
	int		flg_mix, flg_w;
	int		i, j;

	/*��Warning �к���*/
	flg_mix = flg_w = 0,
	rparam = NULL;

	while (fgets(param, sizeof(param), in))
	{
		for (i = 0; i < num; i++)
		{
			flg_mix = flg_w = 0;
			rparam = rensoh[i].param;
			/*��������ɬ�פȤ��������ѿ����ɤ�����*/
			if (strncmp(rparam, "ar__", 4) == 0)
			{
				rparam = &(rparam[4]);
				flg_mix++;
			}
			/*���ͤ���֥륯�����ơ������Ǥ����äƽ��Ϥ��뤫(�����ξ������)��*/
			if (strncmp(rparam, "ww__", 4) == 0)
			{
				rparam = &(rparam[4]);
				flg_w++;
			}
			if (strncmp(rparam, "w>__", 4) == 0)
			{
				rparam = &(rparam[4]);
				flg_w++,
				flg_w++;
			}

			/*��������ɤȰ��פ�����롼�פ���ȴ���롡*/
			if (strncmp(param, rparam, strlen(rparam)) == 0) { break; }
		}
		/*���񤭴����Υ�����ɤȰ��פ������ɤ�����*/
		if (i == num)
		{
			fputs(param, out);
		}
		else
		{
			rparam = rensoh[i].kstr,
			key    = rensoh[i].key;

			tmp = getval3(key);
			fprintf(out, "%s", rparam);
			if (!flg_mix)
			{
				/*���ѥ�᡼��ñ����ϡ�*/
				fprintf(out, !flg_w ? "%s\n": (flg_w == 1) ? "\"%s\"\n": "\"%s\">\n", tmp);
			} else
			{
				/*�����ܿ���������ޤ���*/
				l = list_split(0, tmp);
				i = 0,
				j = l->n;
				for (i = 0; i < j; i++)
				{
					fprintf(out, " %s", getval3(R_sprintf("%s%s", key, l->item[i])));
				}
				fprintf(out, "\n");
			}
		}
	}

	return;
}

/*--------------------------------------------------------------------------*/
void valconv2(FILE *out, FILE *in, RENSOH rensoh[], int num)
{
	char	param[1024];
	char	val[1024];
	char	*tmp;
	int		i;

	/*��Warning �к���*/
	tmp = NULL;

	while (fgets(param, sizeof(param), in))
	{
		for (i = 0; i < num; i++)
		{
			if ((tmp = strstr(param, rensoh[i].param)) == NULL) { continue; }
			break;
		}

		/*���񤭴����Υ�����ɤȰ��פ������ɤ�����*/
		if (i == num)
		{
			fputs(param, out);
		}
		else
		{
			*tmp = 0x00;
			strcpy(val, param);
			strcat(val, getval3(rensoh[i].key));
			strcat(val, &(tmp[ strlen(rensoh[i].param) ]));
			fputs(val, out);
		}
	}

	return;
}

/*--------------------------------------------------------------------------*/
char *get_ipnum(int *num, char *s)
{
	char	str[4];
	char	c, *p;
	int		i, j;

	*num = 0;
	p = s;
	for (i = 0; i < 4; i++)
	{
		str[i] = c = *p++;
		if (c == '.' || c == 0x00) { break; }
	}
	if (i >= 4 || !i) { return s; }

	str[i] = 0x00;
	j = sscanf(str, "%d", &i);
	if (j != 1)  { return s; }
	if (i > 255) { return s; }

	*num = i;

	return p;
}

/*----------------------------------------------------------------------------
rc2dhcpd_sub()
  rc.conf ����ɤߤ����������Ȥ˥ͥåȥ�������ɰ����
  �б�����dhcpd ���������Ϥ��ޤ���
����
  out	�����襹�ȥ꡼��
  no	�ͥåȥ��������ID (0 - 3)
	����������rc.conf �����ꤵ�줿�������ܤ��Ф���ID
�����
  1	�������Ϥ���
  0	�������Ϥ��ʤ��ä�
----------------------------------------------------------------------------*/
int rc2dhcpd_sub(FILE *out, int no)
{
static const char	*tstr = "x_dhcpd_%s__eth%d";
static const char	*options[] = {
	"routers",		/* 0x00 */
	"nameserver",	/* 0x01 */
	"domainname"	/* 0x02 */
};
static const char	*options_str[] = {
	"    option routers %s;\n",
	"    option domain-name-servers %s;\n",
	"    option domain-name \"%s\";\n"
};

	char	parastr[128], *range1, *submask, *tmp, *tmp2;
	int		ip[4], bc[4];
	int		i, max;
	u_int	j, k;

	/*  4�İʾ�Υ������ͥåȥ����ɤϤޤ��ʤ�����  */
	if (no > 3)
	{
//		fprintf(stderr, "over ethernet number => %d\n", no);
		return 0;
	}

	/*  �����ȥ���ե�����ͭ��̵����Ƚ�ꤷ�ޤ�  */
	sprintf(parastr, tstr, "enable", no);
	if (strcmp(getval3(parastr), "YES") != 0)
	{
//		fprintf(stderr, "disable => eth%d\n", no);
		return 0;
	}

	/*�����֥ͥåȤ򻻽Ф��ޤ���*/
	submask = getval3(R_sprintf(tstr, "subnet_mask", no));
	range1  = getval3(R_sprintf(tstr, "range1", no));
	tmp = range1, tmp2 = submask;
	for (i = 0; i < 4; i++)
	{
		tmp  = get_ipnum(&j, tmp);
		tmp2 = get_ipnum(&k, tmp2);
		ip[i] = j & k;
		bc[i] = ((j & k) | ~k) & 0xff;
	}
	/*  �������Ϥ��ޤ�  */
	fprintf(out, "subnet %d.%d.%d.%d netmask %s {\n",
				ip[0], ip[1], ip[2], ip[3], submask);

//	fprintf(out, "subnet %s netmask %s {\n",
//				getval3(R_sprintf(tstr, no, "subnet")),
//				getval3(R_sprintf(tstr, no, "subnet_mask")));
	fprintf(out, "    range %s %s;\n",
				getval3(R_sprintf(tstr, "range1", no)),
				getval3(R_sprintf(tstr, "range2", no)));

	/*�����ץ���󷲤���Ϥ��ޤ���*/
#if	0
	fprintf(out, "    option broadcast-address %d.%d.%d.%d;\n",
				bc[0], bc[1], bc[2], bc[3]);
#endif
	max = sizeof(options)/sizeof(options[0]);
	for (i = 0; i < max; i++)
	{
		tmp = getval3(R_sprintf(tstr, options[i], no));
		if (strcmp(tmp, "") != 0)
		{
			fprintf(out, options_str[i], tmp);
		}
	}

	/*��������Ĥ��ޤ���*/
	fprintf(out, "}\n");

	return 1;
}
/*----------------------------------------------------------------------------
rc2dhcpd()
  rc.conf �����ɤ߼�ä�������Ȥ�dhcp.conf ����Ϥ��ޤ���
����
  �ʤ�
�����
  1	���Ͻ�λ
  0	���ϤǤ��ʤ��ä��ʥե����뤬�����ʤ��ä���
----------------------------------------------------------------------------*/
int rc2dhcpd(void)
{
#if	0
static char	*lease_str[] = {
	"x_dhcpd_default_lease_time",
	"x_dhcpd_max_lease_time"
};
#endif
	char	*file;
	FILE	*out;

	/*�����ϥե�����򥪡��ץ󤷤ޤ���*/
	file = RC_DHCPD_CF;
	if ((out = fopen(file, "w")) == NULL)
	{
		fprintf(stderr,
			"fatal error: cannot open dhcpd conf file %s\n", file);
		return 0;
	}
	fprintf(out, RC2DHCP_HEADER);
	fprintf(out, "ddns-update-style none;\n");
//	fprintf(out, "default-lease-time %s\n", getval3(lease_str[0]));
//	fprintf(out, "max-lease-time %s\n", getval3(lease_str[1]));

	/*���ƥ������ͥåȥ��������DHCP�������Ϥ��ޤ���*/
	rc2dhcpd_sub(out, 0);
	rc2dhcpd_sub(out, 1);
	rc2dhcpd_sub(out, 2);
	rc2dhcpd_sub(out, 3);

	/*�����ϥե�������Ĥ��ޤ���*/
	fclose(out);

	return 1;
}
#ifdef SENDMAIL_V10
/*----------------------------------------------------------------------------
rc2sendmail(); V10��
����
  sendmail.cf �δ��ܤ����Ƥ�ե����뤫���ɤ߹��ߡ�
  �Ķ������ȿ�Ǥ����ƽ��Ϥ��ޤ���
����
  int rc2sendmail(void);
����
  �ʤ�
�����
  1	���ϴ�λ
  0	���ϤǤ��ʤ��ä�
----------------------------------------------------------------------------*/
int rc2sendmail(void)
{

	FILE	*out;
	char	*file,*tmp,*buf,*id,str[32];

	/*�����ϥե�����򳫤��ޤ���*/
	file = RC_LOCAL_HOST_NAMES;
	if ((out = fopen(file, "w")) == NULL)
	{
		fprintf(stderr,
			"fatal error: cannot open %s\n", file);
		return 0;
	}

	tmp = getval3("x_sendmail_my_official_smtp_hostname");
	if (tmp[0] != 0x00)
	{
		fprintf(out, "%s\n", tmp);
	}
	tmp = getval3("x_sendmail_domain_alias1");
	if (tmp[0] != 0x00)
	{
		fprintf(out, "%s\n", tmp);
	}

	/*���ե�������Ĥ��ޤ���*/
	fclose(out);

	/*�����ϥե�����򳫤��ޤ���*/
	file = RC_RELAY_DOMAINS;
	if ((out = fopen(file, "w")) == NULL)
	{
		fprintf(stderr,
			"fatal error: cannot open %s\n", file);
		return 0;
	}
	tmp = getval3("x_sendmail_client_dom");
	if (tmp[0] != 0x00)
	{
		fprintf(out, "%s\n", tmp);
	}
	buf = getval3("x_sendmail_relay__");
	if (buf[0] != 0x00)
	{
		id=strtok(buf," ");
		do {
			snprintf(str,sizeof(char)*32,"x_sendmail_relay__%s",id);
			tmp = getval3(str);
			if (tmp[0] != 0x00)
			{
				fprintf(out, "%s\n", tmp);
			}
		} while((id=strtok(NULL," ")) != NULL);
	}

	/*���ե�������Ĥ��ޤ���*/
	fclose(out);

	return 1;
}


#else
/*----------------------------------------------------------------------------
rc2sendmail(); V8��
����
  sendmail.cf �δ��ܤ����Ƥ�ե����뤫���ɤ߹��ߡ�
  �Ķ������ȿ�Ǥ����ƽ��Ϥ��ޤ���
����
  int rc2sendmail(void);
����
  �ʤ�
�����
  1	���ϴ�λ
  0	���ϤǤ��ʤ��ä�
----------------------------------------------------------------------------*/
int rc2sendmail(void)
{
static RENSOH rconv[] = {
 { "Cw",             "Cw localhost local ",  "x_sendmail_domain_alias1" },
 { "Dm",             "Dm",                   "x_sendmail_local_domain_name" },
 { "Dj",             "Dj",                   "x_sendmail_my_official_smtp_hostname" },
 { "ar__C{LocalIP}", "C{LocalIP} 127.0.0.1", "x_sendmail_relay__" },
 { "C{LocalDom} ",   "C{localDom} ",         "x_sendmail_client_dom" }
};

	FILE	*in, *out;
	char	*file;

	/*�����ܥե�����򳫤��ޤ���*/
	file = RC_SENDMAIL_DEFAULT;
	if ((in = fopen(file, "r")) == NULL)
	{
		fprintf(stderr,
			"fatal error: cannot open sendmail default file %s\n", file);
		return 0;
	}

	/*�����ϥե�����򳫤��ޤ���*/
	file = RC_SENDMAIL_CF;
	if ((out = fopen(file, "w")) == NULL)
	{
		fprintf(stderr,
			"fatal error: cannot open sendmail cf file %s\n", file);

		fclose(in);
		return 0;
	}

	/*���Ѵ����ƽ��Ϥ��ޤ���*/
	valconv(out, in, rconv, sizeof(rconv)/sizeof(rconv[0]));

	/*���ե�������Ĥ��ޤ���*/
	fclose(out);
	fclose(in);

	return 1;
}
#endif
/*--------------------------------------------------------------------------*/
static char *str_named_zone_master =
"zone \"%s\" {\n"
"   type master;\n"
"   file \"%s\";\n"
"};\n"
;
/*--------------------------------------------------------------------------*/
static char *str_named_zone_slave =
"zone \"%s\" {\n"
"   type slave;\n"
"   file \"%s/%s\";\n"
"   masters {\n"
"       %s;\n"
"   };\n"
"};\n"
;
/*--------------------------------------------------------------------------*/
static char *str_named_zone_db_head = 
"; zone '%s'\n"
"$TTL 3600\n"
"@	IN	SOA	%s. %s.  (\n"
"				%d	; Serial\n"
"				3600		; Refresh\n"
"				300		; Retry\n"
"				3600000		; Expire\n"
"				3600)		; Minimum\n"
;

static char *str_named_local_head = 
"$TTL 86400\n"
"@	IN	SOA	%s.%s. %s.%s.  (\n"
"				%d	; Serial\n"
"				10800		; Refresh\n"
"				3600		; Retry\n"
"				604800		; Expire\n"
"				86400)		; Minimum\n"
;

static char *str_named_localhost =
"		IN	NS	localhost.\n"
"localhost.	IN	A	127.0.0.1\n"
"		IN	AAAA	::1\n"
;

static char *str_named_127 =
"		IN	NS	localhost.\n"
"1.0.0		IN	PTR	localhost.\n"
;

static char *str_named_loopback_v6 =
"		IN	NS	localhost.\n"
"1		IN	PTR	localhost.\n"
;

/*----------------------------------------------------------------------------
rc2named_zonedb();
����
  ������θ��̤Υǡ����١���������ɤ߼����Ϥ��ޤ���
����
  void rc2named_zonedb(FILE *out, char *no);
����
  out	���ϥե�����ݥ���
  no	������δĶ���������ֹ��ʸ���ǡ����ؤΥݥ���
�����
  �ʤ�
----------------------------------------------------------------------------*/
void rc2named_zonedb(FILE *out, char *no)
{
	List	*l, *l2;
	char	key[256];
	char	*tmp;
	int		i, max;

	sprintf(key, "x_named_zone_record__%s__", no);
	tmp = getval3(key);
	l = list_split(0, tmp);

	max = l->n;
	for (i = 0; i < max; i++)
	{
		tmp = R_sprintf("%s%s", key, l->item[i]);

		tmp = getval3(tmp);
		l2 = list_split(0, tmp);
		if (l2->n == 3) {
			if (
				!strcmp(l2->item[1], "A") ||
				!strcmp(l2->item[1], "AAAA") ||
				!strcmp(l2->item[1], "PTR") ||
				!strcmp(l2->item[1], "NS") ||
				!strcmp(l2->item[1], "CNAME")
			)
				fprintf(out, "%s\tIN\t%s\t%s\n",
					l2->item[0], l2->item[1], l2->item[2]);
		} if (l2->n == 4) { 
			if (!strcmp(l2->item[1], "MX"))
				fprintf(out, "%s\tIN\t%s\t%s\t%s\n",
					l2->item[0], l2->item[1], l2->item[2], l2->item[3]);
		}
	}

	return;
}
/*----------------------------------------------------------------------------
rc2named_zone();
����
������Υ������named.conf����������Ϥ��ޤ���
���ޤ������Υ�����Υǡ����١�����ե�����˽��Ϥ��ޤ���
����
  void rc2named_zone(FILE *out, char *no);
����
  out	���ϥե�����ݥ���
  no	������δĶ���������ֹ��ʸ���ǡ����ؤΥݥ���
�����
  1	���ϴ�λ
  0 ���Ϥ��Ǥ��ʤ��ä�(�ե����뤬�����ʤ��ä�)
----------------------------------------------------------------------------*/
int rc2named_zone(FILE *out, char *no, time_t serial)
{
     char	zone[128];
     List	*l;
     FILE	*zone_db;
     char	*tmp, *tmp2;

     /*���������ѿ�̾�������*/
     sprintf(zone, "x_named_zone__%s", no);

     /*�����ܥѥ�᡼��������*/
     tmp = getval3(zone);

     /*���ѥ�᡼��ʬ�䡡*/
     l = list_split(0, tmp);
     if (l->n != 2) { return 0; }

     tmp  = l->item[0];
     tmp2 = l->item[1];
     if (strcmp(tmp, "master") == 0)
     {
	  tmp = R_sprintf("%s/%s", RC_NAMED_DB_OFFPATH,tmp2);
	  fprintf(out, str_named_zone_master, tmp2, tmp);
	  
	  /*��������ǡ����١������ۡ�*/
	  tmp = R_sprintf("%s%s/%s",RC_NAMED_DB_PATH,RC_NAMED_DB_OFFPATH, tmp2);
	  
	  /* �ǥ��쥯�ȥ�Τʤ��Ȥ��Ϻ������� */
	  mkdir(RC_NAMED_DB_PATH, 0777);
	  
	  if ((zone_db = fopen(tmp, "w")) == NULL)
	  {
	       fprintf(stderr,
		       "fatal error: cannot open named zone db file %s\n", tmp);
	       return 0;
	  }
	  
	  tmp = getval3("x_hostname");
	  {
	       char *mname, *rname;
	       
	       mname = R_sprintf("x_named_zone_soa_mname__%s", no);
	       rname = R_sprintf("x_named_zone_soa_rname__%s", no);
	       fprintf(zone_db, str_named_zone_db_head, tmp2, getval(mname), getval(rname), serial);
	  }
	  rc2named_zonedb(zone_db, no);
	  fclose(zone_db);
     } else if (strcmp(tmp, "slave") == 0)
     {
	  sprintf(zone, "x_named_zone_master__%s", no);
	  tmp = getval3(zone);
	  fprintf(out, str_named_zone_slave, tmp2, RC_NAMED_SLAVE_DB_OFFPATH, tmp2, tmp);
     }
     
     return 1;
}
/*----------------------------------------------------------------------------
rc2named();
����
���Ķ�����򸵤˥͡��ॵ���С�������ե��������Ϥ��ޤ���
����
  int rc2named(void);
����
  �ʤ�
�����
  1	���ϴ�λ
  0	���Ϥ��Դ����Ǥ��ä�
----------------------------------------------------------------------------*/
int rc2named(void)
{
	char	line[512];

	time_t	serial;
	FILE	*base, *out;
	List	*l;
	char	*file;
	char	*tmp;
	int		zmax;
	int		i;

	/*�����ܥե����륪���ץ�*/
	file = RC_NAMED_DEFAULT;
	if ((base = fopen(file, "r")) == NULL)
	{
		fprintf(stderr,
			"fatal error: cannot open named conf base file %s\n", file);
		return 0;
	}

	/*�����ϥե����륪���ץ�*/
	file = RC_NAMED_CF;
	if ((out = fopen(file, "w")) == NULL)
	{
		fprintf(stderr,
			"fatal error: cannot open named.conf file %s\n", file);

		fclose(base);
		return 0;
	}

	/*���إå�ɽ����*/
	fprintf(out, RC2NAMED_HEADER);

	/*��������ʬ����ܥե����뤫���ñ�̤�ʣ�̡�*/
	while (fgets(line, sizeof(line), base)) { fputs(line, out); }

	/*�������ƥ��֤ʥ������ֹ��������ޤ���*/
	tmp = getval3("x_named_zone__");
	/*���������ֹ��ʬ�䡡*/
	l = list_split(0, tmp);

	/*��Epoch ��������ƥ��ꥢ�밷���ˤ��ޤ���*/
	time(&serial);

	/*���ƥ�������˽�����*/
	zmax = l->n;
	for (i = 0; i < zmax; i++)
	{
		if (rc2named_zone(out, l->item[i], serial) != 1)
		{
			return 0;
		}
	}

	/*���ե�������Ĥ��ޤ���*/
	fclose(out);
	fclose(base);

	return 1;
}
/*----------------------------------------------------------------------------
rc2resolv();
����
���Ķ�����򸵤�resolver���������Ϥ��ޤ���
����
  int rc2resolv(void);
����
  �ʤ�
�����
  1  ���ϴ�λ
  0  ���Ϥ��Դ����Ǥ��ä�
----------------------------------------------------------------------------*/
int rc2resolv(void)
{
static char	*keytable[] = {
	"x_nameserver",
	"x_nameserver2",
	"x_nameserver3",
	"x_nameserver4"
};
	FILE	*out;
	char	*tmp;
	int		i;

	/*�����ϥե����륪���ץ�*/
	tmp = RC_RESOLVE_CF;
	if ((out = fopen(tmp, "w")) == NULL)
	{
		fprintf(stderr,
			"fatal error: cannot open resolv.conf file %s\n", tmp);
		return 0;
	}

	/*�����ɥᥤ��ν��ϡ�*/
	tmp = getval3("x_domain");
	if (tmp[0] != 0x00)
	{
		fprintf(out, "domain %s\n", tmp);
	}
	/*���͡��ॵ���С�����ν��ϡ�*/
	for (i = 0; i < sizeof(keytable)/sizeof(keytable[0]); i++)
	{
		tmp = getval3(keytable[i]);
		if (tmp[0] == 0x00) { continue; }
		fprintf(out, "nameserver %s\n", tmp);
	}

	/*���ե�������Ĥ��ޤ���*/
	fclose(out);

	return 1;
}

/*----------------------------------------------------------------------------
rc2httpd();
����
���Ķ�����򸵤�httpd.conf�����Ƥ����������Ϥ��ޤ���
����
	int rc2httpd(void);
����
  out	���ϥե�����ݥ���
�����
  1  ���ϴ�λ
  0  ���ϤǤ��ʤ��ä�
----------------------------------------------------------------------------*/
int rc2httpd(void)
{
static RENSOH rconv[] = {
 { "_$_DIR_$_",     "", "x_httpd_dir" },
 { "_$_CGIPAT_$_", "", "x_httpd_cgipat" },
 { "_$_LOGFILE_$_",  "", "x_httpd_logfile" }
};

	FILE	*in, *out;
	char	*file;

	/*�����ܥե�����򳫤��ޤ���*/
	file = RC_HTTPD_DEFAULT;
	if ((in = fopen(file, "r")) == NULL)
	{
		fprintf(stderr,
			"fatal error: cannot open httpd default file %s\n", file);
		return 0;
	}

	/*�����ϥե�����򳫤��ޤ���*/
	file = RC_HTTPD_CF;
	if ((out = fopen(file, "w")) == NULL)
	{
		fprintf(stderr,
			"fatal error: cannot open httpd.conf file %s\n", file);
		fclose(in);
		return 0;
	}

	/*���Ѵ����ƽ��Ϥ��ޤ���*/
	valconv2(out, in, rconv, sizeof(rconv)/sizeof(rconv[0]));

	if(strcmp(getval3("x_httpd_chroot"),"YES")==0)
     		fprintf(out,"chroot\n");

	/*���ե�������Ĥ��ޤ���*/
	fclose(out);
	fclose(in);

	return 1;
}

/*----------------------------------------------------------------------------
rc2named_local();
����
���Ķ�����򸵤� /etc/namedb/127,localhost,loopback.v6�����Ƥ����������Ϥ��ޤ���
����
	int rc2named_local(void);
����
  out	���ϥե�����ݥ���
�����
  1  ���ϴ�λ
  0  ���ϤǤ��ʤ��ä�
----------------------------------------------------------------------------*/
int
rc2named_local(void)
{
     char *file;
     FILE *out;
     time_t serial;
     
     time(&serial);

     file=RC_NAMED_LOCALHOST;
     if((out = fopen(file, "w")) == NULL){
	  fprintf(stderr, "fatal error: cannot open %s\n", file);
	  return 0;
     }
     fprintf(out, str_named_local_head,
	     getval("x_hostname"), 
	     getval("x_domainname"), 
	     "root",
	     getval("x_domainname"),
	     serial);
     fprintf(out, str_named_localhost);
     fclose(out);

     file=RC_NAMED_127;
     if((out = fopen(file, "w")) == NULL){
	  fprintf(stderr, "fatal error: cannot open %s\n", file);
	  return 0;
     }
     fprintf(out, str_named_local_head,
	     getval("x_hostname"), 
	     getval("x_domainname"), 
	     "root",
	     getval("x_domainname"),
	     serial);
     fprintf(out, str_named_127);
     fclose(out);

     file=RC_NAMED_LOOPBACK_V6;
     if((out = fopen(file, "w")) == NULL){
	  fprintf(stderr, "fatal error: cannot open %s\n", file);
	  return 0;
     }
     fprintf(out, str_named_local_head,
	     getval("x_hostname"), 
	     getval("x_domainname"), 
	     "root",
	     getval("x_domainname"),
	     serial);
     fprintf(out, str_named_loopback_v6);
     fclose(out);

     return 1;
}

/*----------------------------------------------------------------------------
rc2samba();
����
���Ķ�����򸵤�smb.conf�����Ƥ����������Ϥ��ޤ���
����
	int rc2samba(void);
����
  out	���ϥե�����ݥ���
�����
  1  ���ϴ�λ
  0  ���ϤǤ��ʤ��ä�
----------------------------------------------------------------------------*/
int rc2samba(void)
{
static RENSOH rconv[] = {
 { "MYGROUP",     "", "x_samba_workgroup"},
 { "LinuxServer", "", "x_hostname" }
};

	FILE	*in, *out;
	char	*file;

	/*�����ܥե�����򳫤��ޤ���*/
	file = RC_SAMBA_CF_DEFAULT;
	if ((in = fopen(file, "r")) == NULL)
	{
/*
		fprintf(stderr,
			"fatal error: cannot open samba default file %s\n", file);
*/
		return 0;
	}

	/*�����ϥե�����򳫤��ޤ���*/
	file = RC_SAMBA_CF;
	if ((out = fopen(file, "w")) == NULL)
	{
		fprintf(stderr,
			"fatal error: cannot open smb.conf file %s\n", file);
		fclose(in);
		return 0;
	}

	/*���Ѵ����ƽ��Ϥ��ޤ���*/
	valconv2(out, in, rconv, sizeof(rconv)/sizeof(rconv[0]));

	/*���ե�������Ĥ��ޤ���*/
	fclose(out);
	fclose(in);

	return 1;
}
