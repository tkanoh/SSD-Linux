#	$ssdlinux: Makefile,v 1.4 2004/11/24 01:16:11 yamagata Exp $

.include <bsd.own.mk>

SUBDIR=		pammodutil .WAIT \
		pam_access pam_debug pam_deny pam_env pam_filter pam_ftp \
		pam_group pam_issue pam_lastlog pam_limits \
		pam_listfile pam_mail pam_mkhomedir pam_motd \
		pam_nologin pam_permit pam_rhosts_auth pam_rootok \
		pam_securetty pam_shells pam_stress pam_tally \
		pam_time pam_unix pam_warn pam_wheel

# These modules will not be compiled on this system
#SUBDIR+=	pam_cracklib pam_pwdb pam_radius pam_userdb

.include <bsd.subdir.mk>
