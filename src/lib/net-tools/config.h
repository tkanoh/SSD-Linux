/*	$ssdlinux: config.h,v 1.1.1.1 2002/05/02 13:37:07 kanoh Exp $
*
* config.h	Automatically generated configuration includefile
*
* NET-TOOLS	A collection of programs that form the base set of the
*		NET-3 Networking Distribution for the LINUX operating
*		system.
*
*		DO  NOT  EDIT  DIRECTLY
*
*/

/* For Installer */
#ifdef NET_TOOL_LIB_INSTALLER
#define I18N 0
#define HAVE_AFUNIX 1
#define HAVE_AFINET 1
#define HAVE_AFINET6 0
#define HAVE_AFIPX 0
#define HAVE_AFATALK 0
#define HAVE_AFAX25 0
#define HAVE_AFNETROM 0
#define HAVE_AFROSE 0
#define HAVE_AFX25 0
#define HAVE_AFECONET 0
#define HAVE_AFDECnet 0
#define HAVE_AFASH 0
#define HAVE_HWETHER 1
#define HAVE_HWARC 0
#define HAVE_HWSLIP 0
#define HAVE_HWPPP 0
#define HAVE_HWTUNNEL 0
#define HAVE_HWSTRIP 0
#define HAVE_HWTR 0
#define HAVE_HWAX25 0
#define HAVE_HWROSE 0
#define HAVE_HWNETROM 0
#define HAVE_HWX25 0
#define HAVE_HWFR 0
#define HAVE_HWSIT 0
#define HAVE_HWFDDI 0
#define HAVE_HWHIPPI 0
#define HAVE_HWASH 0
#define HAVE_HWHDLCLAPB 0
#define HAVE_HWIRDA 0
#define HAVE_HWEC 0
#define HAVE_FW_MASQUERADE 0
#define HAVE_IP_TOOLS 0
#define HAVE_MII 0
#endif

/* 
 * 
 * Internationalization
 * 
 * The net-tools package has currently been translated to French,
 * German and Brazilian Portugese.  Other translations are, of
 * course, welcome.  Answer `n' here if you have no support for
 * internationalization on your system.
 * 
 */

#ifndef I18N
#define I18N 0
#endif

/* 
 * 
 * Protocol Families.
 * 
 */
#ifndef HAVE_AFUNIX
#define HAVE_AFUNIX 1
#endif
#ifndef HAVE_AFINET
#define HAVE_AFINET 1
#endif
#ifndef HAVE_AFINET6
#define HAVE_AFINET6 1
#endif
#ifndef HAVE_AFIPX
#define HAVE_AFIPX 1
#endif
#ifndef HAVE_AFATALK
#define HAVE_AFATALK 1
#endif
#ifndef HAVE_AFAX25
#define HAVE_AFAX25 1
#endif
#ifndef HAVE_AFNETROM
#define HAVE_AFNETROM 1
#endif
#ifndef HAVE_AFROSE
#define HAVE_AFROSE 0
#endif
#ifndef HAVE_AFX25
#define HAVE_AFX25 1
#endif
#ifndef HAVE_AFECONET
#define HAVE_AFECONET 0
#endif
#ifndef HAVE_AFDECnet
#define HAVE_AFDECnet 0
#endif
#ifndef HAVE_AFASH
#define HAVE_AFASH 0
#endif

/* 
 * 
 * Device Hardware types.
 * 
 */
#ifndef HAVE_HWETHER
#define HAVE_HWETHER 1
#endif
#ifndef HAVE_HWARC
#define HAVE_HWARC 1
#endif
#ifndef HAVE_HWSLIP
#define HAVE_HWSLIP 1
#endif
#ifndef HAVE_HWPPP
#define HAVE_HWPPP 1
#endif
#ifndef HAVE_HWTUNNEL
#define HAVE_HWTUNNEL 1
#endif
#ifndef HAVE_HWSTRIP 
#define HAVE_HWSTRIP 1
#endif
#ifndef HAVE_HWTR
#define HAVE_HWTR 1
#endif
#ifndef HAVE_HWAX25
#define HAVE_HWAX25 1
#endif
#ifndef HAVE_HWROSE
#define HAVE_HWROSE 0
#endif
#ifndef HAVE_HWNETROM
#define HAVE_HWNETROM 1
#endif
#ifndef HAVE_HWX25
#define HAVE_HWX25 1
#endif
#ifndef HAVE_HWFR
#define HAVE_HWFR 1
#endif
#ifndef HAVE_HWSIT
#define HAVE_HWSIT 1
#endif
#ifndef HAVE_HWFDDI
#define HAVE_HWFDDI 0
#endif
#ifndef HAVE_HWHIPPI
#define HAVE_HWHIPPI 0
#endif
#ifndef HAVE_HWASH
#define HAVE_HWASH 0
#endif
#ifndef HAVE_HWHDLCLAPB
#define HAVE_HWHDLCLAPB 0
#endif
#ifndef HAVE_HWIRDA
#define HAVE_HWIRDA 1
#endif
#ifndef HAVE_HWEC
#define HAVE_HWEC 0
#endif

/* 
 * 
 * Other Features.
 * 
 */
#ifndef HAVE_FW_MASQUERADE
#define HAVE_FW_MASQUERADE 1
#endif
#ifndef HAVE_IP_TOOLS
#define HAVE_IP_TOOLS 1
#endif
#ifndef HAVE_MII 
#define HAVE_MII 1
#endif
