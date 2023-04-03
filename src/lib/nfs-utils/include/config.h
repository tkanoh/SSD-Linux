/*	$ssdlinux: config.h,v 1.2 2004/12/20 05:00:53 yamagata Exp $	*/
/*
 *	./configure --with-statedir=/var/db/nfs --disable-nfsv4 --disable-gss
 */
/* support/include/config.h.  Generated automatically by configure.  */
/* Define this if you have standard C headers
 */
#define  STDC_HEADERS 1

/* Define this if you have string.h */
/* #undef  HAVE_STRING_H */

/* Define this if you have netgroup support
 */
#define  HAVE_INNETGR 1

/* Define this if you want NFSv3 support compiled in
 */
#define  NFS3_SUPPORTED 1

/* This defines the location of the NFS state files
 * Warning: these must match definitions in config.mk!
 */
#define NFS_STATEDIR		"/var/db/nfs"

/* Define this if you want to enable various security
 * checks in statd. These checks basically keep anyone
 * but lockd from using this service.
 */
/* #undef RESTRICTED_STATD */

/* Define this if you want support for rpcsec_gss with
 * the MIT krb5 mechanism compiled in */
/* #undef HAVE_KRB5 */

/* Define this if you want support for rpcsec_gss with
 * the Heimdal krb5 mechanism compiled in */
/* #undef HAVE_HEIMDAL */

/* Define this if the Kerberos gssapi library has function
 * gss_krb5_export_lucid_sec_context */
/* #undef HAVE_LUCID_CONTEXT_SUPPORT */

/* Define this if the Kerberos gssapi library has function
 * gss_krb5_set_allowable_enctypes */
/* #undef HAVE_SET_ALLOWABLE_ENCTYPES */

/* Define this if the Kerberos gssapi library has function
 * gss_krb5_cache_name */
/* #undef HAVE_GSS_KRB5_CCACHE_NAME */
