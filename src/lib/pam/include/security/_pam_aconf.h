/*	$ssdlinux: _pam_aconf.h,v 1.4 2004/11/24 01:18:47 yamagata Exp $	*/
/* _pam_aconf.h.  Generated automatically by configure.  */
/*
 * Id: _pam_aconf.h.in,v 1.4 2000/12/04 20:56:10 baggins Exp $
 *
 * 
 */

#ifndef PAM_ACONF_H
#define PAM_ACONF_H

/* lots of stuff gets written to /tmp/pam-debug.log */
/* #undef DEBUG */

/* build libraries with different names (suffixed with 'd') */
/* #undef WITH_LIBDEBUG */

/* provide a global locking facility within libpam */
/* #undef PAM_LOCKING */

/* GNU systems as a class, all have the feature.h file */
#define HAVE_FEATURES_H 1
#ifdef HAVE_FEATURES_H
# define _SVID_SOURCE
# define _BSD_SOURCE
# define __USE_BSD
# define __USE_SVID
# define __USE_MISC
# define _GNU_SOURCE
# include <features.h>
#endif /* HAVE_FEATURES_H */

/* we have libcrack available */
/* #undef HAVE_LIBCRACK */

/* we have libcrypt - its not part of libc (do we need both definitions?) */
#define HAVE_LIBCRYPT 1
#define HAVE_CRYPT_H 1

/* we have libndbm and/or libdb */
#define HAVE_DB_H 1
/* #undef HAVE_NDBM_H */

/* have libfl (Flex) */
#define HAVE_LIBFL 1

/* have libnsl - instead of libc support */
#define HAVE_LIBNSL 1

/* have libpwdb - don't expect this to be important for much longer */
/* #undef HAVE_LIBPWDB */

/* ugly hack to partially support old pam_strerror syntax */
/* #undef UGLY_HACK_FOR_PRIOR_BEHAVIOR_SUPPORT */

/* read both confs - read /etc/pam.d and /etc/pam.conf in serial */
/* #undef PAM_READ_BOTH_CONFS */

#define HAVE_PATHS_H 1
#ifdef HAVE_PATHS_H
#include <paths.h>
#endif
/* location of the mail spool directory */
#define PAM_PATH_MAILDIR _PATH_MAILDIR

#endif /* PAM_ACONF_H */
