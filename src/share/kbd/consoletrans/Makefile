#	$ssdlinux: Makefile,v 1.2 2002/11/08 07:06:40 yamagata Exp $

.include <bsd.own.mk>

FILES=  8859-10_to_uni.trans  8859-13_to_uni.trans     8859-14_to_uni.trans
FILES+= 8859-15_to_uni.trans  8859-1_to_uni.trans      8859-2_to_uni.trans
FILES+= 8859-3_to_uni.trans   8859-4_to_uni.trans      8859-5_to_uni.trans
FILES+= 8859-6_to_uni.trans   8859-7_to_uni.trans      8859-8_to_uni.trans
FILES+= 8859-9_to_uni.trans   baltic.trans	       cp1250_to_uni.trans
FILES+=	cp1251_to_uni.trans
FILES+= cp437_to_iso01.trans  cp437_to_uni.trans       cp737_to_uni.trans
FILES+= cp775_to_uni.trans    cp850_to_iso01.trans     cp850_to_uni.trans
FILES+= cp852_to_uni.trans    cp853_to_uni.trans       cp855_to_uni.trans
FILES+= cp857_to_uni.trans    cp860_to_uni.trans       cp861_to_uni.trans
FILES+= cp862_to_uni.trans    cp863_to_uni.trans       cp864_to_uni.trans
FILES+= cp865_to_uni.trans    cp866_to_uni.trans       cp869_to_uni.trans
FILES+= cp874_to_uni.trans    iso02_to_cp1250.trans    koi2alt
FILES+= koi8-r_to_uni.trans   koi8-u_to_uni.trans
FILES+= koi8u2ruscii	      latin2u.trans	       null
FILES+= space		      trivial		       utflist
FILES+= vga2iso		      viscii1.0_to_tcvn.trans  viscii1.0_to_viscii1.1.trans
FILES+= zero

FILESDIR=	${BINDIR}/consoletrans
.PATH:		${.CURDIR}/../../../dist/kbd/data/consoletrans

.include <bsd.prog.mk>
