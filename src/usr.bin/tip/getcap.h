#ifndef _GETCAP_H_
#define _GETCAP_H_
char	*cgetcap __P((char *, const char *, int));
int	cgetclose __P((void));
int	cgetmatch __P((const char *, const char *));
int	cgetnum __P((char *, const char *, long *));
int	cgetset __P((const char *));
int	cgetstr __P((char *, const char *, char **));
int	cgetustr __P((char *, const char *, char **));
#ifdef __AUDIT__
int	cgetent __P((char **, char **, const char *));
int	cgetfirst __P((char **, char **));
int	cgetnext __P((char **, char **));
#else
int	cgetent __P((char **, const char * const *, const char *));
int	cgetfirst __P((char **, const char * const *));
int	cgetnext __P((char **, const char * const *));
#endif
#endif
