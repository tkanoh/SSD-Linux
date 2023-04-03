/*
	$Id: env.c,v 1.1 2002/07/08 06:57:25 nao Exp $
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdarg.h>
#include "setup.h"

Env *env_root;

#define OVAL	1
#define	TVAL	2
#define NVAL	4

/*
  キーから対応する Envエントリを探す。
  あればそのポインタを返す。
*/
static Env *
search(Env *e, const char *key)
{
  int sign;

  if(e == NULL)
    return e;

  while(e){
    sign = strcmp(e->key, key);
    if(sign == 0)
      return e;
    e = e->next;
  }

  /* dummy */
  return NULL;
}

void
put_env(const char *key, const char *val)
{
  Env *e;

  e = search(env_root, key);
  if(e){
    if(e->val)
      free(e->val);
    e->val = strdup(val);
  }
  else{
    e = malloc(sizeof(Env));
    e->key = strdup(key);
    e->val = strdup(val);

    e->next = env_root;
    env_root = e;
  }
}

char *
get_env(const char *key)
{
  Env *e;

  e = search(env_root, key);
  if(e)
    return e->val;

  return NULL;
}

void
del_env(const char *key)
{
  Env *e, *en;

  e = env_root;
  if(!strcmp(e->key, key)){
    free(e->key);
    free(e->val);
    free(e);
    env_root = NULL;
  }

  while(e->next){
    if(!strcmp(e->next->key, key)){
      en = e->next;
      e->next = en->next;
      free(en->key);
      free(en->val);
      free(en);
      return;
    }
  }
  return;
}
