/*
  $Id: misc.c,v 1.2 2003/03/12 01:55:09 yamagata Exp $
 */
#define  _GNU_SOURCE
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdarg.h>
/*
#include <sysexits.h>
*/
#include "setup.h"

/*
  わーたいへんだー
 */
void
panic(char *str)
{
  printf("Content-Type: text/html\n\n");
  printf("Panic: %s\n", str);
  /*
  exit(EX_UNAVAILABLE);
  */
  exit(1);
}

void *
my_malloc(size_t sz)
{
  void *adr;

  adr = malloc(sz);
  if(adr == NULL){
    fprintf(stderr, "Panic: Cannot malloc memory\n");
    panic("malloc");
  }

  return adr;
}

char *
my_strdup(const char *s)
{
  char *str;

  str = strdup(s);
  if(str == NULL){
    fprintf(stderr, "Panic: Cannot malloc memory\n");
    panic("malloc");
  }

  return str;
}

void
my_free(void *adr)
{
  free(adr);
}

/*
  便利な関数
 */

int
my_atoi(const char *s)
{
  if(s == 0)
    return 0;

  return atoi(s);
}

void
chop(char *s)
{
  while(*s)
    ++s;

  if(s[-1] == '\n')
    s[-1] = '\0';
}

/*
  文字列を quoteする。
 */

char *
quote(const char *in)
{
  char *p, *p0, *p1;
  
  p0 = p = R_malloc(strlen(in) * 6 + 1);

  while(*in){
    if(*in == '&'){
      *(p++) = '&';
      *(p++) = 'a';
      *(p++) = 'm';
      *(p++) = 'p';
      *(p++) = ';';
    }
    else if(*in == '"'){
      *(p++) = '&';
      *(p++) = 'q';
      *(p++) = 'u';
      *(p++) = 'o';
      *(p++) = 't';
      *(p++) = ';';
    }
    else if(*in == '<'){
      *(p++) = '&';
      *(p++) = 'l';
      *(p++) = 't';
      *(p++) = ';';
    }
    else if(*in == '>'){
      *(p++) = '&';
      *(p++) = 'g';
      *(p++) = 't';
      *(p++) = ';';
    }
    else
      *(p++) = *in;
    ++in;
  }
  *p = '\0';
  
  p1 = R_strdup(p0);
  R_free(p0);

  return p1;
}

/*
  簡易リングバッファ
 */

/*
  リングバッファに割当てる
 */
void *
ring_malloc(Ring *r, size_t size)
{
  void *ptr;

/*
  ptr = r->adr[r->i % r->n];

  if(ptr != NULL)
    my_free(NULL);

  ptr = r->adr[r->i % r->n] = (void *)my_malloc(size);
  if(ptr == NULL){
    fprintf(stderr, "Fatal: Cannot allocate memory\n");
    panic("malloc");
  }
  ++r->i;
*/
  ptr = (void *)my_malloc(size);

  return ptr;
}

/*
  リングバッファに文字列を割当てる
 */
char *
ring_strdup(Ring *r, const char *str)
{
  char *p;

  p = ring_malloc(r, strlen(str) + 1);
  strcpy(p, str);

  return p;
}

/*
  リングバッファのデータを解放する
 */
void
ring_free(Ring *r, void *ptr)
{
  int i;

  free(ptr);

  for(i=0 ; i < r->n ; ++i)
    if(r->adr[i] == ptr){
      r->adr[i] = NULL;
      return;
    }

  return;
}

/*
  formatした文字列をリングバッファに割当てる
 */
char *
ring_sprintf(Ring *r, const char *fmt, ...)
{
  char *ret, *tmp;
  va_list ap;

  va_start(ap, fmt);
  vasprintf(&tmp, fmt, ap);
  va_end(ap);
  ret = ring_strdup(r, tmp);
  free(tmp);

  return ret;
}

/*
  formatした文字列をリングバッファに割当てる
 */
char *
R_sprintf(const char *fmt, ...)
{
  char *ret, *tmp;
  va_list ap;

  va_start(ap, fmt);
  vasprintf(&tmp, fmt, ap);
  va_end(ap);
  ret = ring_strdup(ring, tmp);
  free(tmp);

  return ret;
}

/*
  INTを文字列にしてリングバッファに割当てる
 */

char *
ring_itoa(Ring *r, int n)
{
  return ring_sprintf(r, "%d", n);
}

/*
  一行読みこむ。長い行は無視する。
 */
char *
ring_readln(Ring *r, FILE *fp)
{
  int len;
  char buf[1024];
  char tmp[1024];
  char *p;

  p = fgets(buf, 1024, fp);
  if(!p)
    return NULL;

  len = strlen(buf);
  while(len == 1023)	/* 長い行対策 */
    fgets(tmp, 1024, fp);

  return ring_strdup(r, buf);
}
/*
  リングバッファを作成する
*/


Ring *
ring_new(size_t sz)
{
  Ring *new;
  int size = sizeof(Ring) + sz * sizeof(void *);
  new = my_malloc(size);
  memset(new, 0, size);

  new->n = sz;
  new->i = 0;
  
  return new;
}

/*
  リングバッファを解放する
 */
void
ring_delete(Ring *r)
{
  int i;

  for(i=0 ; i < r->n ; ++i)
    if(r->adr[i])
      my_free(r->adr[i]);
  my_free(r);
}


/*  エスケープされた文字を戻す  */
char *
ring_htdecode(Ring *r, char *str)
{
  char *p, *ret;
  char b[3];

  ret = p = ring_malloc(r, strlen(str) * 3 + 1);

  while(*str){
    if(*str == '+'){
      *(p++) = ' ';
      ++str;
    }
    else if(*str == '%'){
      b[0] = str[1];
      b[1] = str[2];
      b[2] = '\0';
      *(p++) = strtol(b, NULL, 16);
      str += 3;
    }
    else
      *(p++) = *(str++);
  }
  *p = '\0';

  return ret;
}

