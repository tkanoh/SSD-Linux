/*
	$Id: setup.h,v 1.18 2004/11/26 09:57:24 todoroki Exp $
 */

#ifndef SETUP_H
#define SETUP_H

#define SETUP_CGI_VERSION "3.00"
#define	RC_ENV_MAX	1024

#define PREFIX		"/usr/contrib"


#define RC_CONF		PREFIX "/etc/openblocks.conf"
#define RC_CONF_DEFAULT	PREFIX "/etc/defaults/openblocks.conf"
#define RC_CONF_TMP	PREFIX "/etc/tmp.conf"

#define UPSETCONF	"/etc/rc.iptables"
#define	RADVDCONF	"/etc/radvd.conf"

#define USER_HOME	"/home"
#define USER_GROUP	100
#define PASSWD		"/etc/passwd"

#define ETC_FLASHCFG	"/etc/flashcfg"
#ifdef OBS200
#define SBIN_FLASHCFG_SAVE	"/usr/sbin/flashcfg s"
#else
#define SBIN_FLASHCFG_SAVE	"/usr/sbin/flashcfg -s"
#endif

#define	RC_DHCPD_CF		"/etc/dhcpd.conf"
#define	RC2DHCP_HEADER		"# setup.cgi (dhcpd) \n"

#define	RC_SENDMAIL_DEFAULT	PREFIX "/etc/defaults/sendmail.cf"
#define	RC_SENDMAIL_CF		"/etc/mail/sendmail.cf"
#ifdef SENDMAIL_V10
#define	RC_LOCAL_HOST_NAMES	"/etc/mail/local-host-names"
#define RC_RELAY_DOMAINS	"/etc/mail/relay-domains"
#endif

#define	RC_NAMED_DB_OFFPATH	"db"
#define	RC_NAMED_SLAVE_DB_OFFPATH	"2nd"
#define	RC_NAMED_DB_PATH	"/etc/namedb/"
#define	RC_NAMED_DEFAULT	PREFIX "/etc/defaults/named.conf"
#define	RC_NAMED_CF		"/etc/namedb/named.conf"
#define RC_NAMED_127		"/etc/namedb/127"
#define RC_NAMED_LOCALHOST	"/etc/namedb/localhost"
#define RC_NAMED_LOOPBACK_V6	"/etc/namedb/loopback.v6"

#define	RC2NAMED_HEADER		"# setup.cgi (named)\n"

#define	RC_RESOLVE_CF		"/etc/resolv.conf"
#define	RC_HTTPD_DEFAULT	PREFIX "/etc/defaults/thttpd.conf"
#define	RC_HTTPD_CF		PREFIX "/etc/thttpd.conf"
#ifndef HTTPD_PORT
#define HTTPD_PORT		880
#endif

#define RC_SAMBA_CF			"/usr/contrib/samba/lib/smb.conf"
#define RC_SAMBA_CF_DEFAULT	PREFIX "/etc/defaults/smb.conf"

typedef struct _Env {
  char *key;
  char *val;
  int  flag;	/* bit0:更新
                 * bit1:内容の更新
                 * bit2:出力するか否か
                 */
  struct _Env *next;
} Env;

#define	RC_bWRITE	(1<<0)
#define	RC_bUPDATE	(1<<1)
#define	RC_bNOOUTPUT	(1<<2)

#define RC_bNULL RC_bNOOUTPUT

typedef struct _ZTab {
  char *key;
  void (*z_hook)(char *);
} ZTab;

typedef struct _STab {
  char *key;
  void (*s_hook)(char *);
} STab;

#define	VC_SAVE		1
#define VC_SYSTEM	2
#define VC_USER		3
#define VC_NETWORK	4
#define VC_MASQ		5
#define VC_FW		6
#define VC_MISC		7
#define VC_HELP		8
#define VC_DHCPD	9
#define VC_SENDMAIL	10
#define VC_NAMED	11
#define VC_HTTPD	12
#define VC_LOGIN	13
#define VC_IPV6		14
#define VC_SAMBA	15

#define VCF_NOTNULL		1	/* 空白は許されない */
#define VCF_NOTNULL_DHCP0	2	/* Eth0 で DHCPD オンのとき 空白は許されない */
#define VCF_NOTNULL_DHCP1	3	/* Eth1 で DHCPD オンのとき 空白は許されない */
#define VCF_NOTNULL_V6TUN	4	/* IPv6 over IPv4 トンネル オンのとき 空白は許されない */
#define VCF_NODISP		(1<<8)	/* 設定画面で設定したということを表示しない */

typedef struct _VTab {
  char *key;
  char *desc;		/* 説明 */
  char *err_help;
  int category;		/* カテゴリ */
  int flag;		/* フラグ */
  char * (*chk)(const char *, const char *);
  char **valdesc;
} VTab;

typedef struct _List{
  int n;	/* リストの数 */
  int sz;	/* 最大数(mallocした itemの数) */
  char **item;
} List;

typedef struct _Ring{
  int n;	/* リングバッファの数 */
  int i;	/* 割当て index */
  void *adr[0];	/* 割当てる領域 */
} Ring;

typedef struct _Str{
  int len;	/* 文字列の長さ */
  int sz;	/* 文字列のサイズ */
  char *str;	/* 文字列 */
} Str;

extern Env envtop;
extern ZTab ztab[];

void	stab_hook(char *, char *);
int	err_chk(char *, char *);

void	output_change(char *);


extern void read_conf();
extern void write_conf();
extern void write_conf2( char *file, int debug );
extern char *getval( const char *key );
extern char *getval2( const char *key, int *flag );
extern char *getval3( char *key );
extern char *getval_printf( const char *fmt, char *key );
extern int getval_int( const char *key);
extern void delval( const char *key );
extern int is_updateval( void );
extern Env *getvalp( const char *key );
extern int setvalflag( const char *key, int flag );
extern int getvalflag( const char *key );
extern int is_ipcheckval( char *val );
extern int is_ipcheckval_range( char *val );

extern void putval(const char *key, char *val, int sw);
extern int t_token(char **in, char **out, int *sz);
extern char *eval(Str *, char *);
extern char *token(Str *, char *);
extern int ip4_to_mask(char *ip4);

extern Ring *ring_new(size_t);
extern void ring_delete(Ring *);

extern void *ring_malloc(Ring *, size_t);
extern char *ring_strdup(Ring *, const char *);
extern void ring_free(Ring *, void *);
extern char *ring_sprintf(Ring *, const char *fmt, ...);
extern char *ring_itoa(Ring *, int);
extern char *ring_htdecode(Ring *r, char *str);
extern char *ring_readln(Ring *r, FILE *fp);

extern char *get_interface_adr(char *interface);

extern Ring *ring;	/* 汎用 ring */
#define R_malloc(x)	ring_malloc(ring, (x))
#define R_strdup(x)	ring_strdup(ring, (x))
#define R_free(x)	ring_free(ring, (x))
#define R_itoa(x)	ring_itoa(ring, (x))
extern char *		R_sprintf(const char *fmt, ...);

extern void chop(char *);
extern void panic(char *);
extern char *quote(const char *);
extern void *  my_malloc(size_t sz);
extern char *  my_strdup(const char *s);
extern void    my_free(void *adr);

List *  list_new(int sz);
void    list_delete(List *l);
List *  list_split(int sep, const char *str);
char *  list_join(List *l);
void	list_dump(List *l);
void	list_push(List *l, char *item);
char *	list_pop(List *l);
void	list_remove_item(List *l, const char *str);
char *	list_grep_item(List *l, const char *str);
void	list_sort_item(List *l);

Str *   str_new(void);
void    str_delete(Str *s);
void	str_trunc(Str *s, int len);
void    str_append_charp(Str *s, char *p);
void    str_append_char(Str *s, int c);
void	str_append_str(Str *s, Str *s2);

void *  my_malloc(size_t sz);
void	my_free(void *);
int	my_atoi(const char *);

char	    *HTML_script_name;
extern Str  *HTML_script_op;
extern Str  *HTML_script_subop;
extern Str  *HTML_script_arg1;
extern Str  *HTML_script_arg2;
extern Str  *HTML_location;
extern Str  *HTML_error;

#define NG		0
#define OK		1
#define OK_SAVE		2
#define OK_NOSAVE	3
#define CONT		4

#ifndef BUILD_DATE
#define BUILD_DATE	"unknown"
#endif	

#define COLOR_WHITE	"#ffffff"
#define COLOR_GRAY0	"#eeeeee"
#define COLOR_C0	"#eeeeee"
#define COLOR_C1	"#0cb0e0"
#define COLOR_C2	"#ee86b8"
#define COLOR_C3	"#ffff00"

extern int yazaki_main();

int rc2dhcpd	__P((void));
int rc2sendmail	__P((void));
int rc2named	__P((void));
int rc2resolv	__P((void));
int rc2httpd	__P((void));
int rc2named_local __P((void));
int rc2samba	__P((void));

#include "sym.h"

#endif	/*SETUP_H*/
