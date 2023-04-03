/*
	$Id: eval.c,v 1.2 2003/03/11 03:14:54 kanoh Exp $
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdarg.h>

#include "setup.h"

Env envtop;

static char *search_array( char *key, int bcount );

static unsigned char mask_tbl[][4] = {
  {0,0,0,0},
  {0x80,0,0,0},
  {0xc0,0,0,0},
  {0xe0,0,0,0},
  {0xf0,0,0,0},
  {0xf8,0,0,0},
  {0xfc,0,0,0},
  {0xfe,0,0,0},
  {0xff,0,0,0},
  {0xff,0x80,0,0},
  {0xff,0xc0,0,0},
  {0xff,0xe0,0,0},
  {0xff,0xf0,0,0},
  {0xff,0xf8,0,0},
  {0xff,0xfc,0,0},
  {0xff,0xfe,0,0},
  {0xff,0xff,0,0},
  {0xff,0xff,0x80,0},
  {0xff,0xff,0xc0,0},
  {0xff,0xff,0xe0,0},
  {0xff,0xff,0xf0,0},
  {0xff,0xff,0xf8,0},
  {0xff,0xff,0xfc,0},
  {0xff,0xff,0xfe,0},
  {0xff,0xff,0xff,0},
  {0xff,0xff,0xff,0x80},
  {0xff,0xff,0xff,0xc0},
  {0xff,0xff,0xff,0xe0},
  {0xff,0xff,0xff,0xf0},
  {0xff,0xff,0xff,0xf8},
  {0xff,0xff,0xff,0xfc},
  {0xff,0xff,0xff,0xfe},
  {0xff,0xff,0xff,0xff},
};

char *
mask_to_ip4(int mask)
{
  static char ret[16];

  if(mask >= 0 && mask <= 32){
    sprintf(ret, "%d.%d.%d.%d", mask_tbl[mask][0], mask_tbl[mask][1], mask_tbl[mask][2], mask_tbl[mask][3]);
    return ret;
  }

  return "0.0.0.0";
}

int
ip4_to_mask(char *ip4)
{
  int d[4];
  int n = 0;
  int *dd;

  if(!ip4)
    return 24;
  dd = d;

  if(sscanf(ip4, "%d.%d.%d.%d", d, d+1, d+2, d+3) != 4)
    return 24;

  while(*dd == 0xff && n < 32){
    n += 8;
    ++dd;
  }

  if(*dd == 0)
    n += 0;
  else if(*dd == 0x80)
    n += 1;
  else if(*dd == 0xc0)
    n += 2;
  else if(*dd == 0xe0)
    n += 3;
  else if(*dd == 0xf0)
    n += 4;
  else if(*dd == 0xf8)
    n += 5;
  else if(*dd == 0xfc)
    n += 6;
  else if(*dd == 0xfe)
    n += 7;
  else if(*dd == 0xff)
    n += 8;

  return n;
}

int
is_atom(int c)
{
  return isalnum(c) || c == '_';
}

static char *
numeric(Str *ret, char *in)
{
  char tmp[16];
  int n = 0;

  while(*in && isdigit(*in)){
    n *= 10;
    n += (*in - '0');
    ++in;
  }
  snprintf(tmp, 16, "%d", n);
  str_append_charp(ret, tmp);

  return in;
}

static char *
val(Str *ret, char *in)
{
  char *p = in;
  Str *tmp = str_new();

  if(*p == '{'){
    ++p;
    p = val(tmp, p);
    if(*p == '}'){
      ++p;
      str_append_charp(ret, tmp->str);
      goto End;
    }
  }
  p = in;
  str_trunc(tmp, 0);

  while(*p && is_atom(*p)){
    str_append_char(tmp, *p);
    ++p;
  }
  str_append_charp(ret, getval(tmp->str));

 End:
  str_delete(tmp);

  return p;
}

static char *
qatom(Str *ret, char *in)
{
  Str *tmp;

  tmp = str_new();

  while(*in){
    if(*in == '\\'){
      ++in;
      str_append_char(tmp, *in);
      ++in;
    }
    else if(*in == '$'){
      ++in;
      in = val(tmp, in);
    }
    else if(*in == '"'){
      break;
    }
    else{
      str_append_char(tmp, *in);
      ++in;
    }
  }

  str_append_str(ret, tmp);
  str_delete(tmp);

  return in;
}

static char *
atom(Str *ret, char *in)
{
  Str *tmp = str_new();

  while(isspace(*in))
    ++in;

  while(*in && is_atom(*in)){
    str_append_char(tmp, *in);
    ++in;
  }

  str_append_str(ret, tmp);
  
  str_delete(tmp);

  return in;
}

char *
token(Str *ret, char *in)
{
  char *p = in;
  Str *tmp = str_new();

  while(isspace(*p))
    ++p;

  if(*p == '"'){
    ++p;
    p = qatom(tmp, p);
    if(*p == '"'){
      ++p;
      goto End;
    }
  }
  p = in;
  while(isspace(*p))
    ++p;

  str_trunc(tmp, 0);
  p = atom(tmp, p);
 End:
  str_append_str(ret, tmp);
  
  str_delete(tmp);

  while(isspace(*p))
    ++p;

  return p;
}

char *
func_input_text(Str *ret, char *in)
{
  char *p = in;
  Str *tmp = str_new();
  Str *tmp2 = str_new();
  Str *tmp3 = str_new();

  str_trunc(tmp, 0);
  p = eval(tmp, p);
  if(*p != ','){	/*第2引数が省略された*/
    str_append_charp(tmp2, getval(tmp->str));
    goto Skip;
  }

  ++p;
  str_trunc(tmp2, 0);
  p = eval(tmp2, p);

  if(*p != ',')	/*第3引数が省略された*/
    goto Skip;
  ++p;
  str_trunc(tmp3, 0);
  p = eval(tmp3, p);
 Skip:
  str_append_charp(ret, 
		   R_sprintf("<INPUT TYPE=TEXT NAME=\"%s\" VALUE=\"%s\" %s>",
			     tmp->str, tmp2->str, tmp3->str));

  str_delete(tmp);
  str_delete(tmp2);
  return p;
}

char *
func_input_passwd(Str *ret, char *in)
{
  char *p = in;
  Str *tmp = str_new();
  Str *tmp2 = str_new();
  Str *tmp3 = str_new();

  str_trunc(tmp, 0);
  p = eval(tmp, p);
  if(*p != ','){	/*第2引数が省略された*/
    str_append_charp(tmp2, getval(tmp->str));
    goto Skip;
  }

  ++p;
  str_trunc(tmp2, 0);
  p = eval(tmp2, p);

  if(*p != ',')	/*第3引数が省略された*/
    goto Skip;
  ++p;
  str_trunc(tmp3, 0);
  p = eval(tmp3, p);
 Skip:
  str_append_charp(ret, 
		   R_sprintf("<INPUT TYPE=PASSWORD NAME=\"%s\" VALUE=\"%s\" %s>",
			     tmp->str, tmp2->str, tmp3->str));

  str_delete(tmp);
  str_delete(tmp2);
  return p;
}

char *
func_input_hidden(Str *ret, char *in)
{
  char *p = in;
  Str *tmp = str_new();
  Str *tmp2 = str_new();

  str_trunc(tmp, 0);
  p = eval(tmp, p);
  if(*p != ','){	/* ERROR */
    p = in;
    goto End;
  }
  ++p;
  str_trunc(tmp2, 0);
  p = eval(tmp2, p);
  str_append_charp(ret, R_sprintf("<INPUT TYPE=HIDDEN NAME=\"%s\" VALUE=\"%s\">", tmp->str, tmp2->str));

 End:
  str_delete(tmp);
  str_delete(tmp2);
  return p;
}

/*
  input_select(NAME,VALUE,OPTION1,OPTION2...)
 */
char *
func_input_select(Str *ret, char *in)
{
  char *p = in;
  Str *tmp = str_new();
  Str *tmp2 = str_new();
  Str *tmp3 = str_new();

  p = eval(tmp, p);
  if(*p != ','){
    p = in;
    goto End;
  }
  ++p;

  p = eval(tmp2, p);
  if(*p != ','){
    p = in;
    goto End;
  }
  ++p;

  str_append_charp(ret, R_sprintf("<SELECT NAME=\"%s\">", tmp->str));
  while(1){
    str_trunc(tmp3, 0);
    p = eval(tmp3, p);
    if(!strcmp(tmp2->str, tmp3->str))
      str_append_charp(ret, R_sprintf("<OPTION SELECTED>%s\n", tmp3->str));
    else
      str_append_charp(ret, R_sprintf("<OPTION>%s\n", tmp3->str));
    if(*p != ',')
      break;
    ++p;
  }
  str_append_charp(ret, R_sprintf("</SELECT>"));
 End:
  str_delete(tmp);
  str_delete(tmp2);
  str_delete(tmp3);
  return p;
}


char *
func_input_checkbox(Str *ret, char *in)
{
  char *p = in;
  Str *tmp = str_new();
  Str *tmp2 = str_new();
  char *val;

  p = eval(tmp, p);
  if(*p != ','){
    val = getval(tmp->str);
    goto Skip;
  }
  ++p;
  p = eval(tmp2, p);
  val = tmp2->str;
 Skip:

  if(*(tmp->str + 1))
    str_append_charp(ret, R_sprintf("<INPUT TYPE=HIDDEN NAME=\"j%s\" VALUE=\"NO\">", tmp->str + 1));
  if(val && (atoi(val) != 0 || !strcasecmp(val, "yes")))
    str_append_charp(ret, R_sprintf("<INPUT TYPE=CHECKBOX NAME=\"%s\" VALUE=\"YES\" CHECKED>", tmp->str));
  else
    str_append_charp(ret, R_sprintf("<INPUT TYPE=CHECKBOX NAME=\"%s\" VALUE=\"YES\">", tmp->str));

  str_delete(tmp);
  str_delete(tmp2);
  return p;
}

/*
  input_radio(NAME, RADIO_VALUE, VALUE);
 */
char *
func_input_radio(Str *ret, char *in)
{
  char *p = in;
  Str *tmp = str_new();
  Str *tmp2 = str_new();
  Str *tmp3 = str_new();

  str_trunc(tmp, 0);
  p = eval(tmp, p);
  if(*p != ',')
    goto End;
  ++p;

  str_trunc(tmp2, 0);
  p = eval(tmp2, p);
  if(*p != ',')
    goto Skip;
  ++p;

 Skip:
  str_trunc(tmp3, 0);
  p = eval(tmp3, p);

  str_append_charp(ret, R_sprintf("<INPUT TYPE=RADIO NAME=\"%s\" VALUE=\"%s\"%s>\n", 
				  tmp->str, tmp2->str,
				  !strcmp(tmp2->str, tmp3->str) ? " CHECKED" : ""));
 End:

  str_delete(tmp);
  return p;
}

/*
  input_netmask(NAME, VALUE)
 */
char *
func_input_netmask(Str *ret, char *in)
{
  char *p = in;
  Str *tmp = str_new();
  Str *tmp2 = str_new();

  str_trunc(tmp, 0);
  p = eval(tmp, p);
  if(*p != ','){	/*第2引数が省略された*/
    str_append_charp(tmp2, getval(tmp->str));
    goto Skip;
  }

  ++p;
  str_trunc(tmp2, 0);
  p = eval(tmp2, p);

 Skip:
  str_append_charp(ret, R_sprintf("<SELECT NAME=\"%s\">", tmp->str));
  {
    int i;
    int n = ip4_to_mask(tmp2->str);

    for(i=2 ; i<=32 ; ++i)
      if(n == i)
	str_append_charp(ret, R_sprintf("<OPTION VALUE=\"%s\" SELECTED>%d\n", mask_to_ip4(i), i));
      else
	str_append_charp(ret, R_sprintf("<OPTION VALUE=\"%s\">%d\n", mask_to_ip4(i), i));
  }
  str_append_charp(ret, R_sprintf("</SELECT>"));

  str_delete(tmp);
  str_delete(tmp2);
  return p;

  

  str_delete(tmp);
  return p;
}

char *
func_eval(Str *ret, char *in)
{
  char *p = in;
  Str *tmp = str_new();

  p = eval(tmp, p);
  str_append_charp(ret, getval(tmp->str));

  str_delete(tmp);
  return p;
}

char *
func_head2(Str *ret, char *in)
{
  char *p = in;
  Str *tmp = str_new();

  p = eval(tmp, p);
  str_append_charp(ret, R_sprintf("<P><B>%s</B><P>\n", tmp->str));

  str_delete(tmp);
  return p;
}
char *
func_head(Str *ret, char *in)
{
  char *p = in;
  Str *tmp = str_new();

  p = eval(tmp, p);
  str_append_charp(ret, R_sprintf("<TABLE WIDTH=\"100%%\" BORDER=0 CELLSPACING=0 CELLPADDING=5><TR><TD BGCOLOR=\"%s\"><B>%s</B></TD></TR></TABLE>", COLOR_C2, tmp->str));

  str_delete(tmp);
  return p;
}

char *
func_trlist(Str *ret, char *in)
{
  char *p = in;
  Str *tmp = str_new();
  Str *tmp2 = str_new();
  int  i, j;
  List *lst = NULL;
  List *lst2 = NULL;
  char *val;

  p = eval(tmp, p);
  if(*p != ','){
    p = in;
    goto End;
  }
  ++p;
  p = eval(tmp2, p);

  lst = list_split(0, getval(tmp->str));
  if(lst == NULL)
    goto End;

  for(i=0 ; i<lst->n ; ++i){
    str_append_charp(ret, "<TR>");
    val = getval(R_sprintf(tmp2->str, lst->item[i]));
    lst2 = list_split(0, val);
    for(j=0 ; j<lst2->n ; ++j){
      str_append_charp(ret, R_sprintf("<TD>%s</TD>", lst2->item[j]));
    }
    list_delete(lst2);
    str_append_charp(ret, R_sprintf("<TD><INPUT TYPE=SUBMIT NAME=\"d__%s\" VALUE=\"削除\"></TD>\n", lst->item[i]));
    str_append_charp(ret, "</TR>");
  }
  list_delete(lst);
 End:
  str_delete(tmp);
  str_delete(tmp2);

  return p;
}

char *
func_zone_trlist(Str *ret, char *in)
{
  int i, j;
  List *l;
  List *l2;
  
  l = list_split(0, getval(X_NAMED_ZONE__));
  for(j=0 ; j<l->n ; ++j){
    i = atoi(l->item[j]);	/* 修正 2001/11/26 */
    l2 = list_split(0, getval(R_sprintf("x_named_zone__%d", i)));
    str_append_charp(ret, R_sprintf("<TR>\n"));
    str_append_charp(ret, R_sprintf("  <TD>%d</TD>", i));
    str_append_charp(ret, R_sprintf("  <TD><A HREF=\"setup.cgi?i_login=%s&i_key=%s&op=%s&subop=%s&a2=%d&a=%s\">%s</A></TD>",
				    getval(X_LOGIN),
				    getval(X_KEY),
				    HTML_script_op->str, 
				    HTML_script_subop->str,
				    i, l2->item[0], l2->item[1]));
    str_append_charp(ret, R_sprintf("  <TD>%s</TD>", l2->item[0]));
    str_append_charp(ret, R_sprintf("<TD><INPUT TYPE=SUBMIT NAME=\"%s\" VALUE=\"削除\"></TD>\n", R_sprintf("d__%d", i)));
    str_append_charp(ret, R_sprintf("</TR>\n"));
    list_delete(l2);
  }

  list_delete(l);

  return in;
}

char *
func_user_trlist(Str *ret, char *in)
{
  FILE *fp;
  List *l;
  char *passwd;

  fp = fopen(PASSWD, "r");
  while((passwd = ring_readln(ring, fp)) != NULL){
    if(!isalnum(passwd[0]))
      continue;
    /*
      userは1000から60000まで
     */
    l = list_split(':', passwd);
    if(l->n >= 6 && atoi(l->item[2]) >= 32768 && atoi(l->item[2]) <= 60000){
      str_append_charp(ret, R_sprintf("<TR>\n"));
      str_append_charp(ret, R_sprintf("  <TD>%s</TD>", l->item[2]));
      str_append_charp(ret, R_sprintf("  <TD>%s</TD>", l->item[0]));
      str_append_charp(ret, R_sprintf("  <TD>%s</TD>", l->item[4]));
      str_append_charp(ret, R_sprintf("<TD><INPUT TYPE=SUBMIT NAME=\"%s\" VALUE=\"削除\"></TD>\n", R_sprintf("d__%s", l->item[2])));
      str_append_charp(ret, R_sprintf("</TR>\n"));
    }
    list_delete(l);
  }
  fclose(fp);

  return in;
}

char *
func_user_nextid(Str *ret, char *in)
{
  FILE *fp;
  List *l = NULL;
  char *passwd;
  int uid;
  int max = 0;

  fp = fopen(PASSWD, "r");
  while((passwd = ring_readln(ring, fp)) != NULL){
    if(!isalnum(passwd[0]))
      continue;
    l = list_split(':', passwd);
    if(l->n >=6){
      uid = atoi(l->item[2]);
      if(l->n >= 6 && uid >= 500 && uid <= 60000){
	if(uid >= max)
	  max = uid;
      }
    }
  }
  fclose(fp);
  ++max;

  str_append_charp(ret, R_sprintf("<INPUT TYPE=TEXT NAME=\"i_user_id\" VALUE=\"%d\">\n", max));
  if(l)
    list_delete(l);

  return in;
}

char *
func_nextval(Str *ret, char *in)
{
  char *p = in;
  Str *tmp = str_new();
  List *lst = NULL;

  p = eval(tmp, p);
  lst = list_split(0, tmp->str);
  if(lst->n > 0)
    str_append_charp(ret, R_sprintf("%d", my_atoi(lst->item[lst->n - 1]) + 1));
  else
    str_append_charp(ret, "0");

  list_delete(lst);

  str_delete(tmp);

  return p;
}

char *
func_def_formarg(Str *ret, char *in)
{
  str_append_charp(ret, R_sprintf("METHOD=POST ACTION=\"%s\"", HTML_script_name));

  return in;
}

static struct FuncTab{
  char *funcname;
  char *(*func)(Str *, char *);
} functab[] = {
  {"eval", func_eval},
  {"input_text", func_input_text},
  {"input_passwd", func_input_passwd},
  {"input_hidden", func_input_hidden},
  {"input_select", func_input_select},
  {"input_checkbox", func_input_checkbox},
  {"input_radio", func_input_radio},
  {"input_netmask", func_input_netmask},
  {"head", func_head},
  {"head2", func_head2},
  {"trlist", func_trlist},
  {"user_trlist", func_user_trlist},
  {"zone_trlist", func_zone_trlist},
  {"user_nextid", func_user_nextid},
  {"nextval", func_nextval},
  {"def_formarg", func_def_formarg},
  {NULL, NULL},
};

char *
eval_func(Str *ret, char *in)
{
  struct FuncTab *ftab;
  char *p = in;
  Str *tmp = str_new();

  str_trunc(tmp, 0);
  p = atom(tmp, p);

  ftab = functab;
  while(ftab->funcname){
    if(!strcmp(ftab->funcname, tmp->str)){
      str_trunc(tmp, 0);
      if(*p == '('){
	++p;
	p = ftab->func(tmp, p);
	if(*p == ')'){
	  ++p;
	  str_append_str(ret, tmp);
	  goto End;
	}
      }
    }
    ++ftab;
  }
  /* this is not builtin function*/
  p = in;
 End:
  str_delete(tmp);
  return p;
}

char *
eval_sub(Str *ret, char *in)
{
  char *p = in;
  Str *tmp = str_new();
  Str *tmp2 = str_new();

  if(*in == '\0')
    goto End;

  str_trunc(tmp, 0);
  p = eval_func(tmp, p);
  if(p != in){
    str_append_str(ret, tmp);
    goto End;
  }

  p = in;
  str_trunc(tmp, 0);

  p = token(tmp, p);
  str_append_str(ret, tmp);

 End:
  str_delete(tmp);
  str_delete(tmp2);

  return p;
}

char *
eval(Str *ret, char *in)
{
  char *p = in;
  Str *tmp = str_new();
  Str *tmp2 = str_new();

  /*  fprintf(stderr, "DEBUG: eval=%s\n", in);*/
  p = in;
  str_trunc(tmp, 0);

  p = eval_sub(tmp, p);
  if(*p == '['){
    ++p;
    p = numeric(tmp2, p);
    if(*p == ']'){
      int n;
      List *lst;

      n = atoi(tmp2->str);
      lst = list_split(0, tmp->str);

      if(n < lst->n)
	str_append_charp(ret, lst->item[n]);

      list_delete(lst);
      ++p;
      goto End;
    }
  }

  str_append_str(ret, tmp);

 End:
  str_delete(tmp);
  str_delete(tmp2);

  return p;
}

/*
  古いバージョンと互換のある token
 */
int
t_token(char **in, char **out, int *sz)
{
  int len;
  Str *tmp;

  tmp = str_new();
  *in = token(tmp, *in);

  len = strlen(tmp->str);
  if(len >= *sz){
    len = *sz - 1;
  }

  strncpy(*out, tmp->str, len);
  (*out)[len] = '\0';
  *sz -= len;

  return len;
}

void
freeval( Env *envp )
{
  char	*s;

  /*　環境系メモリ開放　*/
  if ( ( s = envp->key  ) != NULL ) { my_free( s ); }
  if ( ( s = envp->val  ) != NULL ) { my_free( s ); }
  /*
  if ( ( s = envp->desc ) != NULL ) { my_free( s ); }
  */
  return;
}
/*----------------------------------------------------------------------------
putval()
  キー情報設定
形式
  void putval( char *key, char *val, int sw );
  void putval_withdesc( char *key, char *val, char *desc, int sw );
引数
  key	キー文字列へのポインタ
  val	値の文字列へのポインタ
  desc	説明文へのポインタ
  sw	書き込みするときの条件
		0	更新情報はクリアされる
		1	設定フラグを立て、内容が更新されていたときは更新フラグを立てる
		3	強制的に更新フラグを立てる
----------------------------------------------------------------------------*/
void
putval_withdesc(const char *key, char *val, char *desc, int sw)
{
  Env *envp, *parent;
  int sw2;

  sw2 = 0;
  /*
  fprintf(stderr, "k=%s val=%s\n", key, val);
  */
  /*  キー情報がないときは保存しない  */
  if ( !key[0] )
    { return; }

  /*  情報バッファを検索します  */
  envp = &envtop;
  while(1)
  {
    parent = envp;
    envp = parent->next;

    /*　最終バッファに到達していたか　*/
    if ( envp == NULL )
    {
       /*　メモリ確保　*/
       envp = my_malloc( sizeof(Env) );
       memset( envp, 0, sizeof(Env) );
       sw2 = RC_bUPDATE;
       break;
    }

    /*  既に設定されているキーかどうか  */
    if ( strcmp( key, envp->key ) != 0 )
      { continue; }

    /*  設定されている情報と一致しないときは更新情報を書き込みます  */
    if ( strcmp( val, envp->val ) != 0 )
      { sw2 = RC_bUPDATE; }

    /*  以前確保されていたメモリを解放しておきます  */
    freeval( envp );
    break;
  }

  /*　更新情報の調整　*/
  if ( sw & RC_bWRITE ) { sw |= sw2; }

  /*  パラメータを書き込みます  */
  envp->key = my_strdup( key );
  envp->val = my_strdup( val );
  /*
  envp->desc = my_strdup( desc ? desc : "" );
  */
  envp->flag = sw;

  setenv(key, val, 1);

  /*　親に登録　*/
  parent->next = envp;

  return;
}

void
putval(const char *key, char *val, int sw)
{
  putval_withdesc(key, val, NULL, sw);
}

/*
  削除する
 */
void
delval( const char *key )
{
  Env	*envp, *parent;

  envp = &envtop;
  while(1)
  {
    parent = envp;
    envp = parent->next;

    /*　データ末端だったら終了　*/
    if ( envp == NULL ) { break; }

    /*　キーが一致しなければ次のデータを検索する　*/
    if ( strcmp( key, envp->key ) != 0 ) { continue; }

    /*　指定された項目をリストから削除します　*/
    parent->next = envp->next;
    freeval( envp );
    my_free( envp );
    break;
  }

  return;
}

/*----------------------------------------------------------------------------
read_conf_sub()
制限
  １行は半角1024文字まで。キーと値の文字列は半角 256文字まで。
----------------------------------------------------------------------------*/
static void
read_conf_sub( FILE *fp, int sw, int check_desc )
{
  char buf[1024];
  char key[256];
  char val[256];
  char *in, *out, *desc;
  char *check;
  int chk;
  int len;

  while( fgets( buf, sizeof(buf), fp ) ){
    if(*buf == '#')
      continue;

    chk = 0;
    in = buf;
    out = key;
    len = 256;

    t_token(&in, &out, &len);
    if(*in != '='){
      val[0] = 0;
      continue;
    }

    ++in;
    out = val;
    len = 256;
    t_token(&in, &out, &len);

    desc = NULL;
    if(check_desc){
      while(*in){
        if(*in == '#'){
          chk = atoi(in + 1);
          desc = index(in + 1, '#');
          if(desc)
            ++desc;

          break;
        }
        ++in;
      }
    }

    /*　特殊変数は記述が存在しても出力しない　*/
    if ( ( check = search_array( key, 3 ) ) != NULL )
    {
      if ( strcmp( check, "___a" ) != 0 )
        { continue; }
    }
    if(desc)
      putval_withdesc( key, val, desc, sw );
    else
      putval( key, val, sw );
  }

  return;
}

Env *getvalp( const char *key )
{
  Env *envp, *parent;

  envp = &envtop;
  while(1)
  {
    parent = envp;
    envp = parent->next;

    /*　末端まで検索してもなかったら終了　*/
    if ( envp == NULL ) { break; }
    if ( strcmp( envp->key, key ) == 0 ) { break; }
  }

  return envp;
}

char *
getval2( const char *key, int *flag )
{
  Env *e;
  time_t t;
  struct tm *tm;

  t = time(NULL);
  tm = localtime(&t);

  if ( flag != NULL )
    { *flag = 0x00; }

  if(!strcmp(key, X_YEAR))
    return ring_sprintf(ring, "%4d", tm->tm_year + 1900);
  else if(!strcmp(key, X_MON))
    return ring_sprintf(ring, "%02d", tm->tm_mon + 1);
  else if(!strcmp(key, X_MDAY))
    return ring_sprintf(ring, "%02d", tm->tm_mday);
  else if(!strcmp(key, X_HOUR))
    return ring_sprintf(ring, "%02d", tm->tm_hour);
  else if(!strcmp(key, X_MIN))
    return ring_sprintf(ring, "%02d", tm->tm_min);
  else if(!strcmp(key, X_SEC))
    return ring_sprintf(ring, "%02d", tm->tm_sec);

  /*　キーを元に検索します　*/
  if ( ( e = getvalp( key ) ) == NULL )
    { return NULL; }

  /*　フラグ格納用のポインタが設定されているときは複写します　*/
  if ( flag != NULL )
    { *flag = e->flag; }

  return e->val;
}

char *
getval( const char *key )
{
  return getval2( key, 0 );
}
/*----------------------------------------------------------------------------
getval3()
  キーが存在しなかったときに空文字列を返すようにしたgetval()関数
型式
  char *getval3( char *key );
引数
  key	キー文字列へのポインタ
戻り値
  値の文字列へのポインタ
----------------------------------------------------------------------------*/
char *getval3( char *key )
{
	char	*val;

	val = getval( key );
	return val == NULL ? "": val;
}

int
getval_int( const char *key )
{
  char *v;

  v = getval(key);
  if(v)
    return atoi(v);
  
  return 0;
}

char *
getval_printf( const char *fmt, char *key )
{
  char *val;
  val = getval3(key);
  printf( fmt, val );
  return val;
}

int
setvalflag( const char *key, int flag )
{
  Env *env;

  if ( ( env = getvalp( key ) ) == NULL ) { return 0; }

  env->flag |= flag;
  return 1;
}

int
unsetvalflag( const char *key, int flag )
{
  Env *env;

  if ( ( env = getvalp( key ) ) == NULL ) { return 0; }

  env->flag &= ~flag;
  return 1;
}

int
getvalflag( const char *key )
{
  Env *env;

  if ( ( env = getvalp( key ) ) == NULL ) { return 0; }

  return env->flag;
}

/*----------------------------------------------------------------------------
search_array()
  配列変数候補になるか判定します
----------------------------------------------------------------------------*/
static
char *
search_array( char *key, int bcount )
{
#if 1
  return NULL;
#else
  int	max;
  int	i;

  max = 256;
  for ( i = 0; i < max; i++, key++ )
  {
    if ( *key == 0x00 ) { key = NULL; break; }
    if ( strncmp( key, "___", bcount ) == 0 ) { break; }
  }
  if ( i == max ) { key = NULL; }

  return key;
#endif
}

void
put_array_param( Env *envp, int sw )
{
#if 1
  return;
#else
  char	key[256], key2[256], val2[16];
  char	*val, *lastp;
  int	num, last, flg;
  int	i;

  /*　定義されているパラメータをカウント。最後の文字列へのポインタを取得　*/
  strcpy( key, envp->key );
  val = envp->val;
  num = last = flg = 0, lastp = NULL;

  /*　値が設定されているときはカウントを開始する　*/
  if ( val != NULL )
  {
    for ( i = 0; i < 256; i++, val++ )
    {
      /*　終端判定　*/
      if ( *val == 0x00 ) { break; }

      /*　個数を数え、最後の文字列へのポインタを保存する　*/
      if ( flg )
      {
        if ( *val == ' ' ) { flg = 0; num++; }
      }
      else
      {
        if ( *val != ' ' ) { flg = 1; lastp = val; }
      }
    }
  }

  /*　文字列で完結したときのカウンタ補正　*/
  if ( flg ) { num++; }

  /*　文字列から数値へ変換　*/
  last = ( lastp != NULL ) ? atoi( lastp ): 0;

  /*　パラメータを出力用に書き換える　*/
  val = search_array( key, 2 );
  *val = 0x00;

  /*　三項目書き足す　*/
  strcat( key, "___\%s" );
  sprintf( key2, key, "n" );
  sprintf( val2, "%d", num );
  putval( key2, val2, sw );

  sprintf( key2, key, "m" );
  sprintf( val2, "%d", last - 1 );
  putval( key2, val2, sw );

  sprintf( key2, key, "p" );
  sprintf( val2, "%d", last + 1 );
  putval( key2, val2, sw );
#endif

  return;
}

void
put_array( int sw )
{
  Env	*envp, *parent;
  char	*key;

  /*　キー項目数分ループ　*/
  envp = &envtop;
  while(1)
  {
    parent = envp;
    envp = parent->next;

    /*　終了判定　*/
    if ( envp == NULL ) { break; }

    key = envp->key;
    if ( ( key = search_array( key, 2 ) ) == NULL ) { continue; }
    if ( strncmp( key, "___a", 4 ) != 0 ) { continue; }

    /*　配列情報を出力します　*/
    put_array_param( envp, sw );
  }

  return;
}

void
read_conf()
{
  FILE	*fp;
  char	*file;

  /*  環境情報ゼロクリア  */
  memset( &envtop, 0, sizeof(envtop) );

  /*  デフォルト値読み込み  */
  file = RC_CONF_DEFAULT;
  if ( ( fp = fopen( file, "r" ) ) == NULL )
  {
    fprintf( stderr, "fatal error: cannot open default file %s\n", file );
    panic(file);
  }
  read_conf_sub( fp, 0, 1 );
  put_array( 0 );
  fclose( fp );

  /*  設定ファイルの値を読み込み  */
  file = RC_CONF;
  if ( ( fp = fopen( file, "r" ) ) == NULL )
  {
    fprintf( stderr, "fatal error: cannot open file %s\n", file );
    panic(file);
  }
  read_conf_sub( fp, 0, 0 );
  put_array( 0 );
  fclose( fp );

  /*  一時ファイルの値読み込み  */
  file = RC_CONF_TMP;
  if ( ( fp = fopen( file, "r" ) ) != NULL )
  {
    read_conf_sub( fp, RC_bWRITE, 0 );
    put_array( RC_bWRITE );
    fclose( fp );
  }

  return;
}

/*----------------------------------------------------------------------------
write_conf()
  情報ファイル出力
----------------------------------------------------------------------------*/
void
write_conf2( char *file, int sw )
{
  FILE *fp;
  Env  *envp, *parent;
/*
  char *check;
*/

  int i, j;

  /*　ファイルオープン　*/
  if ( ( fp = fopen( file, "w" ) ) == NULL )
  {
    fprintf( stderr, "fatal error: cannot open file %s\n", file );
    panic(file);
  }

  /*　コメント出力　*/
  fprintf( fp, "# OpenBlockS Auto config\n" );

  envp = &envtop;
  for ( i = j = 0; ; i++ )
  {
    parent = envp;
    envp = parent->next;

    /*　環境領域終末判定　*/
    if ( envp == NULL )
      { break; }

    /*　出力すべき内容でなければループ　*/
    if ( strncmp( envp->key, "x_", 2 ) != 0 )
      { continue; }

    /*　完全表示要求があったら非表示判定をスキップする　*/
    if ( !sw )
    {
      /*　書き出し禁止フラグが設定されていれば出力しない　*/
      if ( envp->flag & RC_bNULL )
        { continue; }
#if 0
      /*　配列変数の情報は出力しない　*/
      if ( ( check = search_array( envp->key, 3 ) ) != NULL )
      {
        if ( strcmp( check, "___a" ) != 0 )
          { continue; }
      }
#endif
      /* ___ が含まれる情報は出力しない */
      if(strstr(envp->key, "___T")){
	   continue;
      }
    }

    /*　情報出力　*/
    fprintf( fp, "%s=\"%s\"\n", envp->key, envp->val );

    j++;
  }

  /*　キー項目数を出力　*/
  fprintf( fp, "# Key number = %d (%d)\n", j, i );

  if ( sw )
  {
    fprintf( fp, "# update val = %d\n", is_updateval() );
  }

  /*　ファイルを閉じる　*/
  fclose( fp );

  return;
}

void
write_conf( int sw )
{
  /*　デバッグモードなしで出力　*/
  write_conf2( RC_CONF_TMP, 0 );
  return;
}

/*----------------------------------------------------------------------------
is_updateval();
  ファイル全体の更新情報を取得します。
戻り値
  0		更新なし
  1		書き換え要求があった	RC_bWRITE
  3		内容が更新された	RC_bWRITE + RC_bUPDATE
----------------------------------------------------------------------------*/
int
is_updateval( void )
{
  Env *envp, *parent;
  int ret, flag, mask;

  mask = RC_bWRITE | RC_bUPDATE;
  ret = 0;
  envp = &envtop;
  while(1)
  {
    parent = envp;
    envp = parent->next;

    /*　終端判定　*/
    if ( envp == NULL )
      { break; }
    flag = envp->flag;
    if ( strncmp( envp->key, "x_", 2 ) != 0
           || flag & RC_bNULL ) { continue; }

    ret |= flag & mask;
    if ( ret == mask ) { break; }
  }

  return ret;
}

char *
is_ipnum( char *s )
{
  char	num[4];
  char	*p, c;
  int	i, j;

  p = s;
  for ( i = 0; i < 4; i++ )
  {
    num[i] = c = *p++;
    if ( c == '.' || c == 0x00 || c == '-' ) { break; }
  }
  if ( i >= 4 || !i ) { return 0; }

  num[i] = 0x00;
  j = sscanf( num, "%d", &i );
  if ( j != 1 ) { return 0; }
  if ( i > 255 ) { return 0; }

  return --p;
}
/*----------------------------------------------------------------------------
is_ipcheckval();
is_ipcheckval_range();
概要
　文字配列がIPアドレスの書式で書かれているか判定します。
※is_ipcheckval_range() は範囲指定の書式でかかれているか判定します。
形式
	int is_ipcheckval( char *val );
	int is_ipcheckval_range( char *val );
引数
  val	文字配列へのポインタ
戻り値
  1	IPアドレスの書式の範囲に収まっている
  0	IPアドレスの書式の範囲に収まっていない
----------------------------------------------------------------------------*/
static
int
is_ipcheckval_zero( char *val, int sw )
{
  char	c;
  int	i, j;

  /*　範囲をしている場合にも対応するために二回処理　*/
  for ( j = 0; j < 2; j++ )
  {
    /*　IPアドレスなのだから４個なくてはいけない　*/
    for ( i = 0; i < 4; i++ )
    {
      /*　文字列がIPアドレスを構成する値の範囲に収まっているか判定　*/
      if ( ( val = is_ipnum( val ) ) == 0 )
        { return 0; }

      c = *val++;
      if ( i != 3 )
      {
        if ( c != '.' )
          { return 0; }
      }
      else
      {
        if ( sw && !j )
        {
          if ( c != '-' )
            { return 0; }

          continue;
        }
        return ( c == 0 ) ? 1: 0;
      }
    }
  }

  return 1;
}

int
is_ipcheckval( char *val )
{
  return is_ipcheckval_zero( val, 0 );
}

int
is_ipcheckval_range( char *val )
{
  return is_ipcheckval_zero( val, 1 );
}
