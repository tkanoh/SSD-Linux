#	$ssdlinux: Makefile,v 1.8 2004/12/27 03:02:28 yamagata Exp $

.include <bsd.own.mk>

LIB=		db
INCS=		db.h db_cxx.h
INCSDIR=	/usr/include
MKMAN=		no
MKPIC=		yes
MKPICINSTALL=	no

DIST=		${.CURDIR}/../../dist/db
.PATH:		${DIST}/btree ${DIST}/db ${DIST}/hash ${DIST}/qam ${DIST}/rep \
		${DIST}/clib \
		${DIST}/mutex ${DIST}/common ${DIST}/env ${DIST}/dbm \
		${DIST}/dbreg ${DIST}/fileops ${DIST}/hmac ${DIST}/hsearch \
		${DIST}/lock ${DIST}/log ${DIST}/mp ${DIST}/os \
		${DIST}/sequence ${DIST}/txn \
		${DIST}/xa ${DIST}/crypto ${DIST}/crypto/mersenne \
		${DIST}/crypto/rijndael ${DIST}/rpc_client ${DIST}/rpc_server/c

CPPFLAGS+=	-I${.CURDIR} -I${DIST} -D_GNU_SOURCE -D_REENTRANT
.if ${TARGET_HOSTTYPE} == "i386"
CPPFLAGS+=	-DHAVE_MUTEX_X86_GCC_ASSEMBLY=1
.elif ${TARGET_HOSTTYPE} == "powerpc"
CPPFLAGS+=	-DHAVE_MUTEX_PPC_GCC_ASSEMBLY=1
.endif

# BTREE
SRCS=	bt_compare.c bt_conv.c bt_curadj.c bt_cursor.c bt_delete.c \
	bt_method.c bt_open.c bt_put.c bt_rec.c bt_reclaim.c \
	bt_recno.c bt_rsearch.c bt_search.c bt_split.c bt_stat.c \
	bt_upgrade.c btree_auto.c
# BTREE_VRFY
SRCS+=	db_ovfl_vrfy.c db_vrfy.c db_vrfyutil.c bt_verify.c
# HASH
SRCS+=	hash.c hash_auto.c hash_conv.c hash_dup.c hash_meta.c \
	hash_method.c hash_open.c hash_page.c hash_rec.c \
	hash_reclaim.c hash_stat.c hash_upgrade.c
# HASH_VRFY
SRCS+=	hash_verify.c
# QUEUE
SRCS+=	qam.c qam_auto.c qam_conv.c qam_files.c qam_method.c \
	qam_open.c qam_rec.c qam_stat.c qam_upgrade.c
# QUEUE_VRFY
SRCS+=	qam_verify.c
# REP 
SRCS+=	rep_auto.c rep_backup.c rep_method.c rep_record.c rep_region.c \
	rep_stat.c rep_util.c

# C
SRCS+=	mut_tas.c \
	crdel_auto.c crdel_rec.c db.c db_am.c db_auto.c \
	db_byteorder.c db_cam.c db_conv.c db_dispatch.c db_dup.c \
	db_err.c db_getlong.c db_idspace.c db_iface.c db_join.c \
	db_log2.c db_meta.c db_method.c db_open.c db_overflow.c \
	db_pr.c db_rec.c db_reclaim.c db_rename.c db_remove.c \
	db_ret.c db_salloc.c db_setid.c db_setlsn.c db_shash.c \
	db_stati.c db_truncate.c db_upg.c db_upg_opd.c dbm.c \
	dbreg.c dbreg_auto.c dbreg_rec.c dbreg_stat.c dbreg_util.c \
	env_file.c env_method.c env_open.c env_recover.c \
	env_region.c env_stat.c fileops_auto.c fop_basic.c \
	fop_rec.c fop_util.c hash_func.c hmac.c hsearch.c lock.c \
	lock_deadlock.c lock_id.c lock_list.c lock_method.c \
	lock_region.c lock_stat.c lock_timer.c lock_util.c log.c \
	log_archive.c log_compare.c log_get.c log_method.c \
	log_put.c log_stat.c mp_alloc.c mp_bh.c mp_fget.c \
	mp_fmethod.c mp_fopen.c mp_fput.c mp_fset.c mp_method.c \
	mp_region.c mp_register.c mp_stat.c mp_sync.c mp_trickle.c \
	mutex.c os_abs.c os_alloc.c os_clock.c os_config.c \
	os_dir.c os_errno.c os_fid.c os_fsync.c os_handle.c \
	os_id.c os_map.c os_method.c os_oflags.c os_open.c \
	os_region.c os_rename.c os_root.c os_rpath.c os_rw.c \
	os_seek.c os_sleep.c os_spin.c os_stat.c os_tmpdir.c \
	os_truncate.c os_unlink.c sha1.c seq_stat.c sequence.c \
	snprintf.c txn.c txn_auto.c txn_method.c txn_rec.c \
	txn_recover.c txn_region.c txn_stat.c txn_util.c xa.c \
	xa_db.c xa_map.c

# CRYPTO
SRCS+=	aes_method.c crypto.c mt19937db.c rijndael-alg-fst.c \
        rijndael-api-fst.c

# RPC_CLIENT
SRCS+=	client.c db_server_clnt.c db_server_xdr.c gen_client.c \
	gen_client_ret.c

NOGCCERROR=	yes

.include <bsd.lib.mk>
