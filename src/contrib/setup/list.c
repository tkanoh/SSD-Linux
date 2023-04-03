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

  sz *= 2;	/* サバを読む */

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
  文字列をListにする
  
  区切文字は sepで指定する。0の場合は空白文字
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
    sepの数を数える
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
    listの個数は c+1のはずなので、listをアロケートする
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
  Listを文字列にする。
  文字列は my_mallocで割当てられる
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
  listの最後に itemを追加する。追加できなかった場合は
  メモリ再割り当てをしてでも追加する
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
  listの最後の要素のポインタを返し、
  要素を一つ減らす。
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
  Listの中から文字列 strのものを探しだす。
  なければ NULLを返す
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
  Listの中から文字列 strのものを1つだけ除外し、
  詰める
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
  Listの中身をソートする。(数字で)
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
