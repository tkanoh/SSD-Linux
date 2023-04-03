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
  Str�ϲ���Ĺʸ����򥨥ߥ�졼�Ȥ���ʰפ����餯�ؿ����Ǥ��롣
  ʸ����Ĺ���ʤꡢ���ݤ����ΰ��Ǽ�ޤ�ʤ����ϼ�ư�Ǻ�
  �������Ȥ���
  
typedef struct _Str{
  int len;	 ʸ�����Ĺ��
  int sz;	 ʸ����Τ���˳��ݤ��Ƥ������Υ�����
  char *str;	 ʸ����
} Str;

  Str *str_new()			������ Str���������
  str_delete(Str *s)			Str���˴�����
  str_trunc(Str *s, int len)		Str��Ĺ���� len�˵ͤ��
  str_append_charp(Str *s, char *p)	Str��ʸ������ɲä���
  str_append_char(Str *s, int c)	Str�˰�ʸ���ɲä���
  str_append_str(Str *s, Str *s)	Str��Str���ɲä���
*/

/*
  constructor
 */

Str *
str_new()
{
  Str *s;
  int sz = 16;

  sz *= 2;	/* ����ä�¿��˳��ݤ򤷤Ƥ��� */

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
