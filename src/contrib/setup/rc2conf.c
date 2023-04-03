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
	char	*param;		/*　置き換え用文字列へのポインタ　*/
	char	*kstr;		/*　対応する設定文字列　*/
	char	*key;		/*　キー文字列へのポインタ　*/
} RENSOH;
/*----------------------------------------------------------------------------
valconv();
概要
  ファイル情報に記述されているキーの内容をgetval()で得られる、キーに対応した
  環境情報値に置き換えます。
形式
  void valconv(FILE *out, FILE *in, RENSOH rensoh[], int num);
引数
  out		出力ファイルポインタ
  in		入力ファイルポインタ
  rensoh	キー値、値連想配列
  num		rensohの数
戻り値
  なし
----------------------------------------------------------------------------*/
void valconv(FILE *out, FILE *in, RENSOH rensoh[], int num)
{
	List	*l;
	char	param[1024];
	char	*rparam, *key, *tmp;
	int		flg_mix, flg_w;
	int		i, j;

	/*　Warning 対策　*/
	flg_mix = flg_w = 0,
	rparam = NULL;

	while (fgets(param, sizeof(param), in))
	{
		for (i = 0; i < num; i++)
		{
			flg_mix = flg_w = 0;
			rparam = rensoh[i].param;
			/*　合成を必要とする配列変数かどうか　*/
			if (strncmp(rparam, "ar__", 4) == 0)
			{
				rparam = &(rparam[4]);
				flg_mix++;
			}
			/*　値をダブルクォーテーションでくくって出力するか(合成の場合を除く)　*/
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

			/*　キーワードと一致したらループから抜ける　*/
			if (strncmp(param, rparam, strlen(rparam)) == 0) { break; }
		}
		/*　書き換えのキーワードと一致したかどうか　*/
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
				/*　パラメータ単純出力　*/
				fprintf(out, !flg_w ? "%s\n": (flg_w == 1) ? "\"%s\"\n": "\"%s\">\n", tmp);
			} else
			{
				/*　項目数を取得します　*/
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

	/*　Warning 対策　*/
	tmp = NULL;

	while (fgets(param, sizeof(param), in))
	{
		for (i = 0; i < num; i++)
		{
			if ((tmp = strstr(param, rensoh[i].param)) == NULL) { continue; }
			break;
		}

		/*　書き換えのキーワードと一致したかどうか　*/
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
  rc.conf より読みこんだ情報をもとにネットワークカード一枚に
  対応するdhcpd の設定を出力します。
引数
  out	出力先ストリーム
  no	ネットワークカードID (0 - 3)
	※正しくはrc.conf に設定されたキー項目に対するID
戻り値
  1	情報を出力した
  0	情報を出力しなかった
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

	/*  4個以上のイーサネットカードはまずないだろう  */
	if (no > 3)
	{
//		fprintf(stderr, "over ethernet number => %d\n", no);
		return 0;
	}

	/*  オートコンフィグの有効無効を判定します  */
	sprintf(parastr, tstr, "enable", no);
	if (strcmp(getval3(parastr), "YES") != 0)
	{
//		fprintf(stderr, "disable => eth%d\n", no);
		return 0;
	}

	/*　サブネットを算出します　*/
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
	/*  設定を出力します  */
	fprintf(out, "subnet %d.%d.%d.%d netmask %s {\n",
				ip[0], ip[1], ip[2], ip[3], submask);

//	fprintf(out, "subnet %s netmask %s {\n",
//				getval3(R_sprintf(tstr, no, "subnet")),
//				getval3(R_sprintf(tstr, no, "subnet_mask")));
	fprintf(out, "    range %s %s;\n",
				getval3(R_sprintf(tstr, "range1", no)),
				getval3(R_sprintf(tstr, "range2", no)));

	/*　オプション群を出力します　*/
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

	/*　設定を閉じます　*/
	fprintf(out, "}\n");

	return 1;
}
/*----------------------------------------------------------------------------
rc2dhcpd()
  rc.conf から読み取った情報をもとにdhcp.conf を出力します。
引数
  なし
戻り値
  1	出力終了
  0	出力できなかった（ファイルが開けなかった）
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

	/*　出力ファイルをオープンします　*/
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

	/*　各イーサネットカード毎にDHCP情報を出力します　*/
	rc2dhcpd_sub(out, 0);
	rc2dhcpd_sub(out, 1);
	rc2dhcpd_sub(out, 2);
	rc2dhcpd_sub(out, 3);

	/*　出力ファイルを閉じます　*/
	fclose(out);

	return 1;
}
#ifdef SENDMAIL_V10
/*----------------------------------------------------------------------------
rc2sendmail(); V10版
概要
  sendmail.cf の基本の内容をファイルから読み込み、
  環境情報を反映させて出力します。
形式
  int rc2sendmail(void);
引数
  なし
戻り値
  1	出力完了
  0	出力できなかった
----------------------------------------------------------------------------*/
int rc2sendmail(void)
{

	FILE	*out;
	char	*file,*tmp,*buf,*id,str[32];

	/*　出力ファイルを開きます　*/
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

	/*　ファイルを閉じます　*/
	fclose(out);

	/*　出力ファイルを開きます　*/
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

	/*　ファイルを閉じます　*/
	fclose(out);

	return 1;
}


#else
/*----------------------------------------------------------------------------
rc2sendmail(); V8版
概要
  sendmail.cf の基本の内容をファイルから読み込み、
  環境情報を反映させて出力します。
形式
  int rc2sendmail(void);
引数
  なし
戻り値
  1	出力完了
  0	出力できなかった
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

	/*　基本ファイルを開きます　*/
	file = RC_SENDMAIL_DEFAULT;
	if ((in = fopen(file, "r")) == NULL)
	{
		fprintf(stderr,
			"fatal error: cannot open sendmail default file %s\n", file);
		return 0;
	}

	/*　出力ファイルを開きます　*/
	file = RC_SENDMAIL_CF;
	if ((out = fopen(file, "w")) == NULL)
	{
		fprintf(stderr,
			"fatal error: cannot open sendmail cf file %s\n", file);

		fclose(in);
		return 0;
	}

	/*　変換して出力します　*/
	valconv(out, in, rconv, sizeof(rconv)/sizeof(rconv[0]));

	/*　ファイルを閉じます　*/
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
概要
  ゾーンの個別のデータベース情報を読み取り出力します。
形式
  void rc2named_zonedb(FILE *out, char *no);
引数
  out	出力ファイルポインタ
  no	ゾーンの環境情報管理番号の文字データへのポインタ
戻り値
  なし
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
概要
　指定のゾーンのnamed.conf上の設定を出力します。
　また、そのゾーンのデータベースをファイルに出力します。
形式
  void rc2named_zone(FILE *out, char *no);
引数
  out	出力ファイルポインタ
  no	ゾーンの環境情報管理番号の文字データへのポインタ
戻り値
  1	出力完了
  0 出力ができなかった(ファイルが開けなかった)
----------------------------------------------------------------------------*/
int rc2named_zone(FILE *out, char *no, time_t serial)
{
     char	zone[128];
     List	*l;
     FILE	*zone_db;
     char	*tmp, *tmp2;

     /*　ゾーン変数名を取得　*/
     sprintf(zone, "x_named_zone__%s", no);

     /*　基本パラメータ取得　*/
     tmp = getval3(zone);

     /*　パラメータ分割　*/
     l = list_split(0, tmp);
     if (l->n != 2) { return 0; }

     tmp  = l->item[0];
     tmp2 = l->item[1];
     if (strcmp(tmp, "master") == 0)
     {
	  tmp = R_sprintf("%s/%s", RC_NAMED_DB_OFFPATH,tmp2);
	  fprintf(out, str_named_zone_master, tmp2, tmp);
	  
	  /*　ゾーンデータベース構築　*/
	  tmp = R_sprintf("%s%s/%s",RC_NAMED_DB_PATH,RC_NAMED_DB_OFFPATH, tmp2);
	  
	  /* ディレクトリのないときは作成する */
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
概要
　環境情報を元にネームサーバーの設定ファイルを出力します。
形式
  int rc2named(void);
引数
  なし
戻り値
  1	出力完了
  0	出力が不完全であった
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

	/*　基本ファイルオープン　*/
	file = RC_NAMED_DEFAULT;
	if ((base = fopen(file, "r")) == NULL)
	{
		fprintf(stderr,
			"fatal error: cannot open named conf base file %s\n", file);
		return 0;
	}

	/*　出力ファイルオープン　*/
	file = RC_NAMED_CF;
	if ((out = fopen(file, "w")) == NULL)
	{
		fprintf(stderr,
			"fatal error: cannot open named.conf file %s\n", file);

		fclose(base);
		return 0;
	}

	/*　ヘッダ表示　*/
	fprintf(out, RC2NAMED_HEADER);

	/*　共通部分を基本ファイルから行単位で複写　*/
	while (fgets(line, sizeof(line), base)) { fputs(line, out); }

	/*　アクティブなゾーン番号を取得します　*/
	tmp = getval3("x_named_zone__");
	/*　ゾーン番号を分割　*/
	l = list_split(0, tmp);

	/*　Epoch を取得してシリアル扱いにします　*/
	time(&serial);

	/*　各ゾーン毎に処理　*/
	zmax = l->n;
	for (i = 0; i < zmax; i++)
	{
		if (rc2named_zone(out, l->item[i], serial) != 1)
		{
			return 0;
		}
	}

	/*　ファイルを閉じます　*/
	fclose(out);
	fclose(base);

	return 1;
}
/*----------------------------------------------------------------------------
rc2resolv();
概要
　環境情報を元にresolverの設定を出力します。
形式
  int rc2resolv(void);
引数
  なし
戻り値
  1  出力完了
  0  出力が不完全であった
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

	/*　出力ファイルオープン　*/
	tmp = RC_RESOLVE_CF;
	if ((out = fopen(tmp, "w")) == NULL)
	{
		fprintf(stderr,
			"fatal error: cannot open resolv.conf file %s\n", tmp);
		return 0;
	}

	/*　自ドメインの出力　*/
	tmp = getval3("x_domain");
	if (tmp[0] != 0x00)
	{
		fprintf(out, "domain %s\n", tmp);
	}
	/*　ネームサーバー情報の出力　*/
	for (i = 0; i < sizeof(keytable)/sizeof(keytable[0]); i++)
	{
		tmp = getval3(keytable[i]);
		if (tmp[0] == 0x00) { continue; }
		fprintf(out, "nameserver %s\n", tmp);
	}

	/*　ファイルを閉じます　*/
	fclose(out);

	return 1;
}

/*----------------------------------------------------------------------------
rc2httpd();
概要
　環境情報を元にhttpd.confの内容を生成、出力します。
形式
	int rc2httpd(void);
引数
  out	出力ファイルポインタ
戻り値
  1  出力完了
  0  出力できなかった
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

	/*　基本ファイルを開きます　*/
	file = RC_HTTPD_DEFAULT;
	if ((in = fopen(file, "r")) == NULL)
	{
		fprintf(stderr,
			"fatal error: cannot open httpd default file %s\n", file);
		return 0;
	}

	/*　出力ファイルを開きます　*/
	file = RC_HTTPD_CF;
	if ((out = fopen(file, "w")) == NULL)
	{
		fprintf(stderr,
			"fatal error: cannot open httpd.conf file %s\n", file);
		fclose(in);
		return 0;
	}

	/*　変換して出力します　*/
	valconv2(out, in, rconv, sizeof(rconv)/sizeof(rconv[0]));

	if(strcmp(getval3("x_httpd_chroot"),"YES")==0)
     		fprintf(out,"chroot\n");

	/*　ファイルを閉じます　*/
	fclose(out);
	fclose(in);

	return 1;
}

/*----------------------------------------------------------------------------
rc2named_local();
概要
　環境情報を元に /etc/namedb/127,localhost,loopback.v6の内容を生成、出力します。
形式
	int rc2named_local(void);
引数
  out	出力ファイルポインタ
戻り値
  1  出力完了
  0  出力できなかった
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
概要
　環境情報を元にsmb.confの内容を生成、出力します。
形式
	int rc2samba(void);
引数
  out	出力ファイルポインタ
戻り値
  1  出力完了
  0  出力できなかった
----------------------------------------------------------------------------*/
int rc2samba(void)
{
static RENSOH rconv[] = {
 { "MYGROUP",     "", "x_samba_workgroup"},
 { "LinuxServer", "", "x_hostname" }
};

	FILE	*in, *out;
	char	*file;

	/*　基本ファイルを開きます　*/
	file = RC_SAMBA_CF_DEFAULT;
	if ((in = fopen(file, "r")) == NULL)
	{
/*
		fprintf(stderr,
			"fatal error: cannot open samba default file %s\n", file);
*/
		return 0;
	}

	/*　出力ファイルを開きます　*/
	file = RC_SAMBA_CF;
	if ((out = fopen(file, "w")) == NULL)
	{
		fprintf(stderr,
			"fatal error: cannot open smb.conf file %s\n", file);
		fclose(in);
		return 0;
	}

	/*　変換して出力します　*/
	valconv2(out, in, rconv, sizeof(rconv)/sizeof(rconv[0]));

	/*　ファイルを閉じます　*/
	fclose(out);
	fclose(in);

	return 1;
}
