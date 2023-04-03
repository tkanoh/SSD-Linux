#	$ssdlinux: Makefile,v 1.1.1.1 2002/05/02 13:37:09 kanoh Exp $

.include <bsd.own.mk>

FILES=  applkey.map   		      azerty-layout.inc
FILES+= backspace.map   	      ctrl.map   
FILES+= euro.map   		      euro1.map   
FILES+= euro2.map   		      keypad.map   
FILES+= linux-keys-bare.inc	      linux-keys-extd.inc
FILES+= linux-with-alt-and-altgr.inc  linux-with-modeshift-altgr.inc
FILES+= linux-with-two-alt-keys.inc   qwerty-layout.inc
FILES+= qwertz-layout.inc	      unicode.map   
FILES+= windowkeys.map   

FILESDIR=	$(BINDIR)/include
.PATH:		${.CURDIR}/../../../../../dist/kbd/data/keymaps/i386/include

.include <bsd.prog.mk>
