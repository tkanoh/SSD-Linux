#	$ssdlinux: Makefile,v 1.5 2005/03/10 08:40:02 yamagata Exp $

.include <bsd.own.mk>

LIB=		util
SRCS=		alldig.c argv.c argv_split.c attr_print0.c attr_print64.c \
		attr_scan0.c attr_scan64.c base64_code.c basename.c binhash.c \
		chroot_uid.c clean_env.c close_on_exec.c concatenate.c ctable.c \
		dict.c dict_alloc.c dict_db.c dict_cdb.c dict_dbm.c dict_debug.c dict_env.c \
		dict_cidr.c dict_ht.c dict_ni.c dict_nis.c \
		dict_nisplus.c dict_open.c dict_pcre.c dict_regexp.c \
		dict_static.c dict_tcp.c dict_unix.c dir_forest.c doze.c \
		duplex_pipe.c environ.c events.c exec_command.c fifo_listen.c \
		fifo_trigger.c file_limit.c find_inet.c fsspace.c fullname.c \
		get_domainname.c get_hostname.c hex_quote.c host_port.c htable.c \
		inet_addr_host.c inet_addr_list.c inet_addr_local.c inet_connect.c \
		inet_listen.c inet_trigger.c line_wrap.c \
		lowercase.c lstat_as.c mac_expand.c mac_parse.c make_dirs.c \
		match_list.c match_ops.c msg.c msg_output.c msg_syslog.c \
		msg_vstream.c mvect.c myflock.c mymalloc.c myrand.c mystrtok.c \
		name_mask.c netstring.c non_blocking.c nvtable.c open_as.c \
		open_limit.c open_lock.c peekfd.c percentm.c posix_signals.c \
		printable.c rand_sleep.c read_wait.c readable.c readlline.c \
		ring.c safe_getenv.c safe_open.c sane_accept.c sane_link.c \
		sane_rename.c sane_socketpair.c sane_time.c scan_dir.c \
		set_eugid.c set_ugid.c sigdelay.c skipblanks.c spawn_command.c \
		split_at.c split_nameval.c stat_as.c stream_connect.c \
		stream_listen.c stream_trigger.c sys_compat.c timed_connect.c \
		timed_read.c timed_wait.c timed_write.c translit.c trimblanks.c \
		unescape.c unix_connect.c unix_listen.c unix_trigger.c unsafe.c \
		username.c valid_hostname.c vbuf.c vbuf_print.c vstream.c \
		vstream_popen.c vstring.c vstring_vstream.c watchdog.c writable.c \
		write_buf.c write_wait.c auto_clnt.c attr_clnt.c attr_scan_plain.c \
		attr_print_plain.c sane_connect.c neuter.c name_code.c \
		uppercase.c unix_recv_fd.c stream_recv_fd.c unix_send_fd.c \
		stream_send_fd.c dict_sdbm.c hex_code.c dummy_read.c dummy_write.c \
		myaddrinfo.c sock_addr.c inet_proto.c cidr_match.c mask_addr.c

DIST=		${.CURDIR}/../../../dist/postfix
.PATH:		${DIST}/src/${LIB}

libinstall::

.include <bsd.lib.mk>
