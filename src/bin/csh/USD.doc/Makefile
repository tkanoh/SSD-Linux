#	$ssdlinux: Makefile,v 1.1.1.1 2002/05/02 13:37:04 kanoh Exp $

SRCS=	tabs csh.1 csh.2 csh.3 csh.4 csh.a csh.g

all:	csh.ps csh.txt

csh.ps:
	groff -etpR -ms -Tps $(SRCS) >$@

csh.txt:
	groff -etpR -ms -Tlatin1 $(SRCS) >$@

clean:
	$(RM) *.ps *.txt core
