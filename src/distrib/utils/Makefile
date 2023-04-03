#	$ssdlinux: Makefile,v 1.19 2004/06/14 04:47:54 todoroki Exp $

.include <bsd.own.mk>

.ifmake clean
SUBDIR+=        libhack libnet-tools libshadow-misc
SUBDIR+=        sysinst
SUBDIR+=        x_basename x_bind x_login x_su x_sulogin x_passwd x_vtund
SUBDIR+=        x_cat x_chgrp x_chmod x_chown x_chroot x_cmp x_cp
SUBDIR+=        x_date x_df x_dhclient x_dump x_expr x_ftp x_grep x_grub
SUBDIR+=        x_gzip x_ifconfig x_insmod x_ln
SUBDIR+=        x_login x_login_no_shadow x_ls
SUBDIR+=        x_mkdir x_mount x_mount_no_nfs x_mv x_portmap
SUBDIR+=        x_passwd
SUBDIR+=        x_rm x_sed x_sleep x_sort x_sshd x_su x_sulogin
SUBDIR+=        x_tar x_touch x_umount x_umount_no_nfs x_uniq
SUBDIR+=        sysinst
.else

SUBDIR+=	libhack libnet-tools libshadow-misc
.if ${TARGET_SSDHOSTTYPE} == "powerpc-obs50" || ${TARGET_SSDHOSTTYPEX} == "powerpc-obs2xx"
SUBDIR+=	sysinst
SUBDIR+=	x_bind x_login x_su x_sulogin x_passwd x_vtund
SUBDIR+=	x_sshd
.endif

.endif

.include <bsd.subdir.mk>
