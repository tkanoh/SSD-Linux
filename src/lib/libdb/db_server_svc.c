/*	$ssdlinux: db_server_svc.c,v 1.1 2004/12/27 03:02:29 yamagata Exp $	*/
/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "db_config.h"
#include "db_server.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif

static void
db_rpc_serverprog_4003(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		__env_get_cachesize_msg __db_env_get_cachesize_4003_arg;
		__env_cachesize_msg __db_env_cachesize_4003_arg;
		__env_close_msg __db_env_close_4003_arg;
		__env_create_msg __db_env_create_4003_arg;
		__env_dbremove_msg __db_env_dbremove_4003_arg;
		__env_dbrename_msg __db_env_dbrename_4003_arg;
		__env_get_encrypt_flags_msg __db_env_get_encrypt_flags_4003_arg;
		__env_encrypt_msg __db_env_encrypt_4003_arg;
		__env_get_flags_msg __db_env_get_flags_4003_arg;
		__env_flags_msg __db_env_flags_4003_arg;
		__env_get_home_msg __db_env_get_home_4003_arg;
		__env_get_open_flags_msg __db_env_get_open_flags_4003_arg;
		__env_open_msg __db_env_open_4003_arg;
		__env_remove_msg __db_env_remove_4003_arg;
		__txn_abort_msg __db_txn_abort_4003_arg;
		__txn_begin_msg __db_txn_begin_4003_arg;
		__txn_commit_msg __db_txn_commit_4003_arg;
		__txn_discard_msg __db_txn_discard_4003_arg;
		__txn_prepare_msg __db_txn_prepare_4003_arg;
		__txn_recover_msg __db_txn_recover_4003_arg;
		__db_associate_msg __db_db_associate_4003_arg;
		__db_bt_maxkey_msg __db_db_bt_maxkey_4003_arg;
		__db_get_bt_minkey_msg __db_db_get_bt_minkey_4003_arg;
		__db_bt_minkey_msg __db_db_bt_minkey_4003_arg;
		__db_close_msg __db_db_close_4003_arg;
		__db_create_msg __db_db_create_4003_arg;
		__db_del_msg __db_db_del_4003_arg;
		__db_get_encrypt_flags_msg __db_db_get_encrypt_flags_4003_arg;
		__db_encrypt_msg __db_db_encrypt_4003_arg;
		__db_get_extentsize_msg __db_db_get_extentsize_4003_arg;
		__db_extentsize_msg __db_db_extentsize_4003_arg;
		__db_get_flags_msg __db_db_get_flags_4003_arg;
		__db_flags_msg __db_db_flags_4003_arg;
		__db_get_msg __db_db_get_4003_arg;
		__db_get_name_msg __db_db_get_name_4003_arg;
		__db_get_open_flags_msg __db_db_get_open_flags_4003_arg;
		__db_get_h_ffactor_msg __db_db_get_h_ffactor_4003_arg;
		__db_h_ffactor_msg __db_db_h_ffactor_4003_arg;
		__db_get_h_nelem_msg __db_db_get_h_nelem_4003_arg;
		__db_h_nelem_msg __db_db_h_nelem_4003_arg;
		__db_key_range_msg __db_db_key_range_4003_arg;
		__db_get_lorder_msg __db_db_get_lorder_4003_arg;
		__db_lorder_msg __db_db_lorder_4003_arg;
		__db_open_msg __db_db_open_4003_arg;
		__db_get_pagesize_msg __db_db_get_pagesize_4003_arg;
		__db_pagesize_msg __db_db_pagesize_4003_arg;
		__db_pget_msg __db_db_pget_4003_arg;
		__db_put_msg __db_db_put_4003_arg;
		__db_get_re_delim_msg __db_db_get_re_delim_4003_arg;
		__db_re_delim_msg __db_db_re_delim_4003_arg;
		__db_get_re_len_msg __db_db_get_re_len_4003_arg;
		__db_re_len_msg __db_db_re_len_4003_arg;
		__db_re_pad_msg __db_db_re_pad_4003_arg;
		__db_get_re_pad_msg __db_db_get_re_pad_4003_arg;
		__db_remove_msg __db_db_remove_4003_arg;
		__db_rename_msg __db_db_rename_4003_arg;
		__db_stat_msg __db_db_stat_4003_arg;
		__db_sync_msg __db_db_sync_4003_arg;
		__db_truncate_msg __db_db_truncate_4003_arg;
		__db_cursor_msg __db_db_cursor_4003_arg;
		__db_join_msg __db_db_join_4003_arg;
		__dbc_close_msg __db_dbc_close_4003_arg;
		__dbc_count_msg __db_dbc_count_4003_arg;
		__dbc_del_msg __db_dbc_del_4003_arg;
		__dbc_dup_msg __db_dbc_dup_4003_arg;
		__dbc_get_msg __db_dbc_get_4003_arg;
		__dbc_pget_msg __db_dbc_pget_4003_arg;
		__dbc_put_msg __db_dbc_put_4003_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		

	case __DB_env_get_cachesize:
		_xdr_argument = (xdrproc_t) xdr___env_get_cachesize_msg;
		_xdr_result = (xdrproc_t) xdr___env_get_cachesize_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_env_get_cachesize_4003_svc;
		break;

	case __DB_env_cachesize:
		_xdr_argument = (xdrproc_t) xdr___env_cachesize_msg;
		_xdr_result = (xdrproc_t) xdr___env_cachesize_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_env_cachesize_4003_svc;
		break;

	case __DB_env_close:
		_xdr_argument = (xdrproc_t) xdr___env_close_msg;
		_xdr_result = (xdrproc_t) xdr___env_close_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_env_close_4003_svc;
		break;

	case __DB_env_create:
		_xdr_argument = (xdrproc_t) xdr___env_create_msg;
		_xdr_result = (xdrproc_t) xdr___env_create_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_env_create_4003_svc;
		break;

	case __DB_env_dbremove:
		_xdr_argument = (xdrproc_t) xdr___env_dbremove_msg;
		_xdr_result = (xdrproc_t) xdr___env_dbremove_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_env_dbremove_4003_svc;
		break;

	case __DB_env_dbrename:
		_xdr_argument = (xdrproc_t) xdr___env_dbrename_msg;
		_xdr_result = (xdrproc_t) xdr___env_dbrename_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_env_dbrename_4003_svc;
		break;

	case __DB_env_get_encrypt_flags:
		_xdr_argument = (xdrproc_t) xdr___env_get_encrypt_flags_msg;
		_xdr_result = (xdrproc_t) xdr___env_get_encrypt_flags_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_env_get_encrypt_flags_4003_svc;
		break;

	case __DB_env_encrypt:
		_xdr_argument = (xdrproc_t) xdr___env_encrypt_msg;
		_xdr_result = (xdrproc_t) xdr___env_encrypt_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_env_encrypt_4003_svc;
		break;

	case __DB_env_get_flags:
		_xdr_argument = (xdrproc_t) xdr___env_get_flags_msg;
		_xdr_result = (xdrproc_t) xdr___env_get_flags_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_env_get_flags_4003_svc;
		break;

	case __DB_env_flags:
		_xdr_argument = (xdrproc_t) xdr___env_flags_msg;
		_xdr_result = (xdrproc_t) xdr___env_flags_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_env_flags_4003_svc;
		break;

	case __DB_env_get_home:
		_xdr_argument = (xdrproc_t) xdr___env_get_home_msg;
		_xdr_result = (xdrproc_t) xdr___env_get_home_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_env_get_home_4003_svc;
		break;

	case __DB_env_get_open_flags:
		_xdr_argument = (xdrproc_t) xdr___env_get_open_flags_msg;
		_xdr_result = (xdrproc_t) xdr___env_get_open_flags_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_env_get_open_flags_4003_svc;
		break;

	case __DB_env_open:
		_xdr_argument = (xdrproc_t) xdr___env_open_msg;
		_xdr_result = (xdrproc_t) xdr___env_open_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_env_open_4003_svc;
		break;

	case __DB_env_remove:
		_xdr_argument = (xdrproc_t) xdr___env_remove_msg;
		_xdr_result = (xdrproc_t) xdr___env_remove_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_env_remove_4003_svc;
		break;

	case __DB_txn_abort:
		_xdr_argument = (xdrproc_t) xdr___txn_abort_msg;
		_xdr_result = (xdrproc_t) xdr___txn_abort_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_txn_abort_4003_svc;
		break;

	case __DB_txn_begin:
		_xdr_argument = (xdrproc_t) xdr___txn_begin_msg;
		_xdr_result = (xdrproc_t) xdr___txn_begin_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_txn_begin_4003_svc;
		break;

	case __DB_txn_commit:
		_xdr_argument = (xdrproc_t) xdr___txn_commit_msg;
		_xdr_result = (xdrproc_t) xdr___txn_commit_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_txn_commit_4003_svc;
		break;

	case __DB_txn_discard:
		_xdr_argument = (xdrproc_t) xdr___txn_discard_msg;
		_xdr_result = (xdrproc_t) xdr___txn_discard_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_txn_discard_4003_svc;
		break;

	case __DB_txn_prepare:
		_xdr_argument = (xdrproc_t) xdr___txn_prepare_msg;
		_xdr_result = (xdrproc_t) xdr___txn_prepare_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_txn_prepare_4003_svc;
		break;

	case __DB_txn_recover:
		_xdr_argument = (xdrproc_t) xdr___txn_recover_msg;
		_xdr_result = (xdrproc_t) xdr___txn_recover_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_txn_recover_4003_svc;
		break;

	case __DB_db_associate:
		_xdr_argument = (xdrproc_t) xdr___db_associate_msg;
		_xdr_result = (xdrproc_t) xdr___db_associate_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_db_associate_4003_svc;
		break;

	case __DB_db_bt_maxkey:
		_xdr_argument = (xdrproc_t) xdr___db_bt_maxkey_msg;
		_xdr_result = (xdrproc_t) xdr___db_bt_maxkey_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_db_bt_maxkey_4003_svc;
		break;

	case __DB_db_get_bt_minkey:
		_xdr_argument = (xdrproc_t) xdr___db_get_bt_minkey_msg;
		_xdr_result = (xdrproc_t) xdr___db_get_bt_minkey_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_db_get_bt_minkey_4003_svc;
		break;

	case __DB_db_bt_minkey:
		_xdr_argument = (xdrproc_t) xdr___db_bt_minkey_msg;
		_xdr_result = (xdrproc_t) xdr___db_bt_minkey_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_db_bt_minkey_4003_svc;
		break;

	case __DB_db_close:
		_xdr_argument = (xdrproc_t) xdr___db_close_msg;
		_xdr_result = (xdrproc_t) xdr___db_close_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_db_close_4003_svc;
		break;

	case __DB_db_create:
		_xdr_argument = (xdrproc_t) xdr___db_create_msg;
		_xdr_result = (xdrproc_t) xdr___db_create_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_db_create_4003_svc;
		break;

	case __DB_db_del:
		_xdr_argument = (xdrproc_t) xdr___db_del_msg;
		_xdr_result = (xdrproc_t) xdr___db_del_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_db_del_4003_svc;
		break;

	case __DB_db_get_encrypt_flags:
		_xdr_argument = (xdrproc_t) xdr___db_get_encrypt_flags_msg;
		_xdr_result = (xdrproc_t) xdr___db_get_encrypt_flags_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_db_get_encrypt_flags_4003_svc;
		break;

	case __DB_db_encrypt:
		_xdr_argument = (xdrproc_t) xdr___db_encrypt_msg;
		_xdr_result = (xdrproc_t) xdr___db_encrypt_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_db_encrypt_4003_svc;
		break;

	case __DB_db_get_extentsize:
		_xdr_argument = (xdrproc_t) xdr___db_get_extentsize_msg;
		_xdr_result = (xdrproc_t) xdr___db_get_extentsize_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_db_get_extentsize_4003_svc;
		break;

	case __DB_db_extentsize:
		_xdr_argument = (xdrproc_t) xdr___db_extentsize_msg;
		_xdr_result = (xdrproc_t) xdr___db_extentsize_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_db_extentsize_4003_svc;
		break;

	case __DB_db_get_flags:
		_xdr_argument = (xdrproc_t) xdr___db_get_flags_msg;
		_xdr_result = (xdrproc_t) xdr___db_get_flags_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_db_get_flags_4003_svc;
		break;

	case __DB_db_flags:
		_xdr_argument = (xdrproc_t) xdr___db_flags_msg;
		_xdr_result = (xdrproc_t) xdr___db_flags_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_db_flags_4003_svc;
		break;

	case __DB_db_get:
		_xdr_argument = (xdrproc_t) xdr___db_get_msg;
		_xdr_result = (xdrproc_t) xdr___db_get_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_db_get_4003_svc;
		break;

	case __DB_db_get_name:
		_xdr_argument = (xdrproc_t) xdr___db_get_name_msg;
		_xdr_result = (xdrproc_t) xdr___db_get_name_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_db_get_name_4003_svc;
		break;

	case __DB_db_get_open_flags:
		_xdr_argument = (xdrproc_t) xdr___db_get_open_flags_msg;
		_xdr_result = (xdrproc_t) xdr___db_get_open_flags_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_db_get_open_flags_4003_svc;
		break;

	case __DB_db_get_h_ffactor:
		_xdr_argument = (xdrproc_t) xdr___db_get_h_ffactor_msg;
		_xdr_result = (xdrproc_t) xdr___db_get_h_ffactor_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_db_get_h_ffactor_4003_svc;
		break;

	case __DB_db_h_ffactor:
		_xdr_argument = (xdrproc_t) xdr___db_h_ffactor_msg;
		_xdr_result = (xdrproc_t) xdr___db_h_ffactor_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_db_h_ffactor_4003_svc;
		break;

	case __DB_db_get_h_nelem:
		_xdr_argument = (xdrproc_t) xdr___db_get_h_nelem_msg;
		_xdr_result = (xdrproc_t) xdr___db_get_h_nelem_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_db_get_h_nelem_4003_svc;
		break;

	case __DB_db_h_nelem:
		_xdr_argument = (xdrproc_t) xdr___db_h_nelem_msg;
		_xdr_result = (xdrproc_t) xdr___db_h_nelem_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_db_h_nelem_4003_svc;
		break;

	case __DB_db_key_range:
		_xdr_argument = (xdrproc_t) xdr___db_key_range_msg;
		_xdr_result = (xdrproc_t) xdr___db_key_range_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_db_key_range_4003_svc;
		break;

	case __DB_db_get_lorder:
		_xdr_argument = (xdrproc_t) xdr___db_get_lorder_msg;
		_xdr_result = (xdrproc_t) xdr___db_get_lorder_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_db_get_lorder_4003_svc;
		break;

	case __DB_db_lorder:
		_xdr_argument = (xdrproc_t) xdr___db_lorder_msg;
		_xdr_result = (xdrproc_t) xdr___db_lorder_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_db_lorder_4003_svc;
		break;

	case __DB_db_open:
		_xdr_argument = (xdrproc_t) xdr___db_open_msg;
		_xdr_result = (xdrproc_t) xdr___db_open_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_db_open_4003_svc;
		break;

	case __DB_db_get_pagesize:
		_xdr_argument = (xdrproc_t) xdr___db_get_pagesize_msg;
		_xdr_result = (xdrproc_t) xdr___db_get_pagesize_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_db_get_pagesize_4003_svc;
		break;

	case __DB_db_pagesize:
		_xdr_argument = (xdrproc_t) xdr___db_pagesize_msg;
		_xdr_result = (xdrproc_t) xdr___db_pagesize_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_db_pagesize_4003_svc;
		break;

	case __DB_db_pget:
		_xdr_argument = (xdrproc_t) xdr___db_pget_msg;
		_xdr_result = (xdrproc_t) xdr___db_pget_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_db_pget_4003_svc;
		break;

	case __DB_db_put:
		_xdr_argument = (xdrproc_t) xdr___db_put_msg;
		_xdr_result = (xdrproc_t) xdr___db_put_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_db_put_4003_svc;
		break;

	case __DB_db_get_re_delim:
		_xdr_argument = (xdrproc_t) xdr___db_get_re_delim_msg;
		_xdr_result = (xdrproc_t) xdr___db_get_re_delim_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_db_get_re_delim_4003_svc;
		break;

	case __DB_db_re_delim:
		_xdr_argument = (xdrproc_t) xdr___db_re_delim_msg;
		_xdr_result = (xdrproc_t) xdr___db_re_delim_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_db_re_delim_4003_svc;
		break;

	case __DB_db_get_re_len:
		_xdr_argument = (xdrproc_t) xdr___db_get_re_len_msg;
		_xdr_result = (xdrproc_t) xdr___db_get_re_len_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_db_get_re_len_4003_svc;
		break;

	case __DB_db_re_len:
		_xdr_argument = (xdrproc_t) xdr___db_re_len_msg;
		_xdr_result = (xdrproc_t) xdr___db_re_len_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_db_re_len_4003_svc;
		break;

	case __DB_db_re_pad:
		_xdr_argument = (xdrproc_t) xdr___db_re_pad_msg;
		_xdr_result = (xdrproc_t) xdr___db_re_pad_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_db_re_pad_4003_svc;
		break;

	case __DB_db_get_re_pad:
		_xdr_argument = (xdrproc_t) xdr___db_get_re_pad_msg;
		_xdr_result = (xdrproc_t) xdr___db_get_re_pad_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_db_get_re_pad_4003_svc;
		break;

	case __DB_db_remove:
		_xdr_argument = (xdrproc_t) xdr___db_remove_msg;
		_xdr_result = (xdrproc_t) xdr___db_remove_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_db_remove_4003_svc;
		break;

	case __DB_db_rename:
		_xdr_argument = (xdrproc_t) xdr___db_rename_msg;
		_xdr_result = (xdrproc_t) xdr___db_rename_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_db_rename_4003_svc;
		break;

	case __DB_db_stat:
		_xdr_argument = (xdrproc_t) xdr___db_stat_msg;
		_xdr_result = (xdrproc_t) xdr___db_stat_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_db_stat_4003_svc;
		break;

	case __DB_db_sync:
		_xdr_argument = (xdrproc_t) xdr___db_sync_msg;
		_xdr_result = (xdrproc_t) xdr___db_sync_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_db_sync_4003_svc;
		break;

	case __DB_db_truncate:
		_xdr_argument = (xdrproc_t) xdr___db_truncate_msg;
		_xdr_result = (xdrproc_t) xdr___db_truncate_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_db_truncate_4003_svc;
		break;

	case __DB_db_cursor:
		_xdr_argument = (xdrproc_t) xdr___db_cursor_msg;
		_xdr_result = (xdrproc_t) xdr___db_cursor_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_db_cursor_4003_svc;
		break;

	case __DB_db_join:
		_xdr_argument = (xdrproc_t) xdr___db_join_msg;
		_xdr_result = (xdrproc_t) xdr___db_join_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_db_join_4003_svc;
		break;

	case __DB_dbc_close:
		_xdr_argument = (xdrproc_t) xdr___dbc_close_msg;
		_xdr_result = (xdrproc_t) xdr___dbc_close_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_dbc_close_4003_svc;
		break;

	case __DB_dbc_count:
		_xdr_argument = (xdrproc_t) xdr___dbc_count_msg;
		_xdr_result = (xdrproc_t) xdr___dbc_count_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_dbc_count_4003_svc;
		break;

	case __DB_dbc_del:
		_xdr_argument = (xdrproc_t) xdr___dbc_del_msg;
		_xdr_result = (xdrproc_t) xdr___dbc_del_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_dbc_del_4003_svc;
		break;

	case __DB_dbc_dup:
		_xdr_argument = (xdrproc_t) xdr___dbc_dup_msg;
		_xdr_result = (xdrproc_t) xdr___dbc_dup_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_dbc_dup_4003_svc;
		break;

	case __DB_dbc_get:
		_xdr_argument = (xdrproc_t) xdr___dbc_get_msg;
		_xdr_result = (xdrproc_t) xdr___dbc_get_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_dbc_get_4003_svc;
		break;

	case __DB_dbc_pget:
		_xdr_argument = (xdrproc_t) xdr___dbc_pget_msg;
		_xdr_result = (xdrproc_t) xdr___dbc_pget_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_dbc_pget_4003_svc;
		break;

	case __DB_dbc_put:
		_xdr_argument = (xdrproc_t) xdr___dbc_put_msg;
		_xdr_result = (xdrproc_t) xdr___dbc_put_reply;
		local = (char *(*)(char *, struct svc_req *)) __db_dbc_put_4003_svc;
		break;

	default:
		svcerr_noproc (transp);
		
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	
__dbsrv_timeout(0);}

int
__dbsrv_main(int argc, char *argv)
{
	register SVCXPRT *transp;

	pmap_unset (DB_RPC_SERVERPROG, DB_RPC_SERVERVERS);

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, DB_RPC_SERVERPROG, DB_RPC_SERVERVERS, db_rpc_serverprog_4003, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (DB_RPC_SERVERPROG, DB_RPC_SERVERVERS, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}
