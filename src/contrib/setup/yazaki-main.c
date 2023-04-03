/*
	$Id: yazaki-main.c,v 1.4 2003/02/19 00:50:52 yamagata Exp $
 */

#include	<sys/types.h>
#include	<sys/file.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	"setup.h"

#ifdef	YAZAKI_LOCAL
Ring *ring;
Str  *HTML_script_op;
Str  *HTML_script_subop;
#endif

int yazaki_main( int argc, char *argv[] )
{
#ifdef	YAZAKI_DEBUG
extern Env envtop;
	Env *envp, *parent;
#endif

#ifdef	YAZAKI_LOCAL
	/*　初期化　*/
	ring = ring_new( 16 );
#endif

	/*  情報読み込み  */
	read_conf();

	/*  dhcpd.conf 出力  */
	rc2dhcpd();

	/*　sendmail.cf 出力　*/
	rc2sendmail();

	/*　named.conf関連ファイル出力　*/
	rc2named();

	/*　resolv.conf出力　*/
	rc2resolv();

	/*　httpd.confを出力　*/
	rc2httpd();

	/* /etc/namedb/127,localhost,loopback.v6 を出力 */
	rc2named_local();

#ifdef CUSTOM0
	/* smb.conf を出力 */
	rc2samba();
#endif

#ifdef	YAZAKI_DEBUG
	/*　デバッグ用ファイル出力　*/
	write_conf();

	/*　キーワード削除　*/
	delval( X_ETH0_TYP );
	delval( "error1" );

	setvalflag( X_ETH1_TYP, 0 );
	setvalflag( "error2", 0 );
	getvalflag( X_ETH1_TYP );
	getvalflag( "error3" );
	putval( X_FOO__2, "AIR DC", RC_bWRITE | RC_bNULL );

	write_conf2( "dummy.conf", 1 );

	envp = &envtop;
	while(1)
	{
		parent = envp;
		envp = parent->next;
		if ( envp == NULL ) { break; }
		fprintf( stdout, "ip %d %d %s=%s\n",
					is_ipcheckval( envp->val ),
					is_ipcheckval_range( envp->val ),
					envp->key, envp->val );
	}
#endif

	return 0;
}
