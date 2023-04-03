#	$ssdlinux: Makefile,v 1.5 2003/08/29 02:14:12 todoroki Exp $

.include <bsd.own.mk>

.ifmake clean
SUBDIR=         ide_info ifport ifuser scsi_info dump_cardbus dump_cis
SUBDIR+=        dump_tcic pack_cis ftl_check ftl_format
.else

# cardmgr
SUBDIR=		ide_info ifport ifuser scsi_info 

# debug-tools
SUBDIR+=	dump_cardbus dump_cis
.if ${TARGET_OPENBLOCKS} == "none"
SUBDIR+=	dump_tcic
.endif
SUBDIR+=	pack_cis 

# flash
SUBDIR+=	ftl_check ftl_format 

.endif

.include <bsd.subdir.mk>
