#	$ssdlinux: Makefile,v 1.11 2005/03/02 05:59:14 yamagata Exp $

.include <bsd.own.mk>

LIB=		ext2fs
# DEBUGFS_LIB_SRCS
SRCS=		bb_compat.c cmp_bitmaps.c fileio.c \
		inode_io.c namei.c write_bb_file.c
# RESIZE_LIB_SRCS
SRCS+=		rs_bitmap.c dupfs.c test_io.c
# E2IMAGE_LIB_SRCS
SRCS+=		imager.c
#
SRCS+=		ext2_err.c alloc.c alloc_sb.c alloc_stats.c alloc_tables.c \
		badblocks.c bb_inode.c bitmaps.c bitops.c block.c bmap.c \
		check_desc.c closefs.c \
		dblist.c dblist_dir.c dirblock.c dirhash.c dir_iterate.c \
		expanddir.c ext_attr.c finddev.c flushb.c freefs.c \
		gen_bitmap.c get_pathname.c getsize.c getsectsize.c \
		icount.c ind_block.c initialize.c inline.c inode.c io_manager.c ismounted.c \
		link.c llseek.c lookup.c mkdir.c mkjournal.c native.c newdir.c \
		openfs.c read_bb.c read_bb_file.c res_gdt.c rw_bitmaps.c \
		swapfs.c \
		unix_io.c unlink.c valid_blk.c version.c		
MKPIC=		yes
MKPICINSTALL=	no
MKMAN=		no

FILES=		bitops.h ext2fs.h ext2_io.h ext2_fs.h ext2_ext_attr.h
FILES+=		../include/${LIB}/ext2_err.h
FILES+=		../include/ext2fs/ext2_types.h
FILESMODE=	444
FILESDIR=	/usr/include/${LIB}

DIST=		${.CURDIR}/../../../dist/e2fsprogs
.PATH:		${DIST}/lib/${LIB}

.include "${.CURDIR}/../Makefile.cflags"

CLEANFILES=	ext2_err.c ext2_err.et ../include/${LIB}/ext2_err.h

ext2_err.et:
	../util/subst -f ../util/subst.conf ${DIST}/lib/${LIB}/ext2_err.et.in ${.TARGET}

ext2_err.c: ext2_err.et
	../libcom_err/compile_et ext2_err.et
	mv ext2_err.h ../include/${LIB}

.include <bsd.lib.mk>
