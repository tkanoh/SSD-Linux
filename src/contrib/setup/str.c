/*
  $Id: str.c,v 1.1 2002/07/08 06:57:26 nao Exp $
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdarg.h>
#include "setup.h"

/*
  Strは可変長文字列をエミュレートする簡易おきらく関数群である。
  文字列が長くなり、確保した領域に納まらない場合は自動で再
  アロケートする
  
typedef struct _Str{
  int len;	 文字列の長さ
  int sz;	 文字列のために確保してあるメモリのサイズ
  char *str;	 文字列
} Str;

  Str *str_new()			新しい Strを作成する
  str_delete(Str *s)			Strを破棄する
  str_trunc(Str *s, int len)		Strの長さを lenに詰める
  str_append_charp(Str *s, char *p)	Strに文字列を追加する
  str_append_char(Str *s, int c)	Strに一文字追加する
  str_append_str(Str *s, Str *s)	StrにStrを追加する
*/

/*
  constructor
 */

Str *
str_new()
{
  Str *s;
  int sz = 16;

  sz *= 2;	/* ちょっと多めに確保をしておく */

  s = my_malloc(sizeof(Str));
  s->len = 0;
  s->sz = sz;
  s->str = my_malloc(sz);
  s->str[0] = '\0';
  
  return s;
}
/*
  destructor
 */
void
str_delete(Str *s)
{
  my_free(s->str);
  my_free(s);
}

static void
str_resize(Str *s, int sz)
{
  char *old;

  if(sz < s->sz){
    s->str[sz] = '\0';
    s->len = sz;
    s->sz = sz;
    return;
  }

  old = s->str;
  s->sz = sz;
  s->str = my_malloc(sz);
  strcpy(s->str, old);

  my_free(old);

  return;
}

void
str_trunc(Str *s, int len)
{
  if(len < s->sz){
    s->len = len;
    s->str[len] = 0;
  }
}

void
str_append_charp(Str *s, char *p)
{
  int len;

  if(!p)
    return;

  len = strlen(p);
  while(len + s->len >= s->sz - 1){
    str_resize(s, s->sz * 2 + len + 1);
  }

  if(len + s->len < s->sz - 1){
    strcat(s->str, p);
    s->len += len;
    return;
  }

  strcat(s->str, p);
}

void
str_append_char(Str *s, int c)
{
  char b[2];

  b[0] = c;
  b[1] = '\0';
  str_append_charp(s, b);
}

void
str_append_str(Str *s, Str *s2)
{
  str_append_charp(s, s2->str);
}
