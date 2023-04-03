/*
  $Id: list.c,v 1.1 2002/07/08 06:57:26 nao Exp $
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdarg.h>
#include "setup.h"

/*
  constructor
 */

List *
list_new(int sz)
{
  List *l;

  sz *= 2;	/* ���Ф��ɤ� */

  l = my_malloc(sizeof(List));
  l->n = 0;
  l->sz = sz;
  l->item = my_malloc(sz * sizeof(char *));

  return l;
}
/*
  destructor
 */
void
list_delete(List *l)
{
  int i;

  if(!l)
    return;

  for(i=0 ; i<l->n ; ++i)
    my_free(l->item[i]);
  my_free(l);
}
/*
  debug
 */
void
list_dump(List *l)
{
  int i;

  fprintf(stderr, "list.n = %d\n", l->n);
  for(i=0 ; i<l->n ; ++i)
    fprintf(stderr, "list.item[%d] = %s\n", i, l->item[i]);
}

/*
  ʸ�����List�ˤ���
  
  ����ʸ���� sep�ǻ��ꤹ�롣0�ξ��϶���ʸ��
 */
List *
list_split(int sep, const char *str)
{
  int i;
  int c;
  char *s, *s0;
  char *p;
  List *l;

  if(!str)
    return list_new(0);
  /*
    sep�ο��������
   */
  p = s0 = my_strdup(str);

  c = 0;
  while(*p){
    if(!sep && isspace(*p))
      ++c;
    else if(*p == sep)
      ++c;
    ++p;
  }

  /*
    list�θĿ��� c+1�ΤϤ��ʤΤǡ�list�򥢥����Ȥ���
   */;
  l = list_new(c + 1);

  i = 0;
  p = s = s0;
  if(!sep){
    while(*p){
      while(*p && !isspace(*p))
	++p;
      
      if(!*p){
	l->item[i] = my_strdup(s);
	++i;
	break;
      }
      
      *p = '\0';
      ++p;
      l->item[i] = my_strdup(s);
      
      while(*p && isspace(*p))
	++p;
      
      ++i;
      s = p;
    }
  }
  else{
    while(*p){
      while(*p && *p != sep)
	++p;
      
      if(!*p){
	l->item[i] = my_strdup(s);
	++i;
	break;
      }
      
      *p = '\0';
      ++p;
      l->item[i] = my_strdup(s);
      /*      
      while(*p && *p == sep)
	++p;
      */
      
      ++i;
      s = p;
    }
  }
  my_free(s0);

  l->n = i;

  return l;
}

/*
  List��ʸ����ˤ��롣
  ʸ����� my_malloc�ǳ����Ƥ���
 */
char *
list_join(List *l)
{
  int i;
  int sz;
  char *ret;
  int n = l->n;

  sz = 1;
  for(i=0 ; i<l->n ; ++i)
    sz += strlen(l->item[i]);

  ret = my_malloc(sz);
  *ret = '\0';
  for(i=0 ; i<n-1 ; ++i){
    strcat(ret, l->item[i]);
    strcat(ret, " ");
  }

  if(n >= 1 && l->item[n-1])
    strcat(ret, l->item[n-1]);

  return ret;
}

/*
  list�κǸ�� item���ɲä��롣�ɲäǤ��ʤ��ä�����
  ����Ƴ�����Ƥ򤷤ƤǤ��ɲä���
 */
void
list_push(List *l, char *item)
{
  int i;
  char **new;

  if(l->n < l->sz){
    l->item[l->n] = my_strdup(item);
    ++l->n;
    return;
  }
  else{
    new = my_malloc(l->sz * sizeof(char *) * 2);
    for(i=0 ; i<l->n ; ++i)
      new[i] = l->item[i];
    new[i] = my_strdup(item);

    my_free(l->item);
    l->item = new;
    ++l->n;
    return;
  }
}

/*
  list�κǸ�����ǤΥݥ��󥿤��֤���
  ���Ǥ��ĸ��餹��
*/

char *
list_pop(List *l)
{
  int n;

  n = l->n;

  if(n > 0){
    --l->n;
    return l->item[n-1];
  }

  return NULL;
}

/*
  List���椫��ʸ���� str�Τ�Τ�õ��������
  �ʤ���� NULL���֤�
 */

char *
list_grep_item(List *l, const char *str)
{
  int i;

  for(i=0 ; i<l->n ; ++i)
    if(!strcmp(l->item[i], str))
      return l->item[i];
  
  return NULL;
}

/*
  List���椫��ʸ���� str�Τ�Τ�1�Ĥ�����������
  �ͤ��
 */

void
list_remove_item(List *l, const char *str)
{
  int i;

  for(i=0 ; i<l->n ; ++i){
    if(!strcmp(l->item[i], str)){
      my_free(l->item[i]);
      --l->n;
      while(i < l->n){
	l->item[i] = l->item[i+1];
	++i;
      }

      return;
    }
  }
}

int
comp_num(const void *aa, const void *bb)
{
  int ret;
  char **a, **b;

  a = (char **)aa;
  b = (char **)bb;

  ret = atoi(*a) - atoi(*b);

  return ret;
}

/*
  List����Ȥ򥽡��Ȥ��롣(������)
 */
void
list_sort_item(List *l)
{
  qsort(l->item, l->n, sizeof(char *), comp_num);
}

#ifdef TEST
main()
{
  List *l;

  l = list_split("5 1 2 3 4");
  list_dump(l);
  list_sort_item(l);
  list_dump(l);
}
#endif
