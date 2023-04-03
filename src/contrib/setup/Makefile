#
#	$Id: Makefile,v 1.47 2004/10/08 03:48:32 yamagata Exp $
#
.include <bsd.own.mk>

SENDMAIL_VER=	v10
HTTPD_PORT=	880

CFLAGS= -g -Wall -O -DBUILD_DATE="\"`date`\""
.if ${SENDMAIL_VER} == "v10"
CFLAGS+=	-DSENDMAIL_V10=1 -DHTTPD_PORT=880
.endif
.if ${TARGET_OPENBLOCKS} == obs200
CFLAGS+=	-DOBS200
.endif
.if ${IPV6} == yes
CFLAGS+=        -DIPV6
.endif

#DEBUGS=	-DDEBUG
DEBUGS=

SRCS=		misc.c list.c setup.c eval.c ok.c valtab.c str.c io.c yazaki-main.c rc2conf.c sym.c
COMMON_OBJS=	misc.o list.o eval.o ok.o valtab.o str.o io.o rc2conf.o sym.o
OBJS=		$(COMMON_OBJS) yazaki-main.o setup.o
OBJS_CUSTOM0=	$(COMMON_OBJS) yazaki-main_custom0.o setup_custom0.o

OBJS_ALL=	$(COMMON_OBJS) yazaki-main.o yazaki-main_custom0.o setup.o setup_custom0.o

TARGET  = setup.cgi setup_custom0.cgi
_CONTRIBDIR= $(DESTDIR)$(CONTRIBDIR)

INSTALLDIR = $(_CONTRIBDIR)/etc/setup

STRIP?=	strip

.MAIN: all
all: $(TARGET)

clean::
	rm -f $(OBJS_ALL) $(TARGET) sym.c sym.h
	rm -f etc/setup_thttpd.conf

cleandir: clean

install-cgi: $(TARGET)
	if [ ! -d "$(INSTALLDIR)" ]; then mkdir -p $(INSTALLDIR) ; fi
	cp $(TARGET) $(INSTALLDIR)
	chown root $(INSTALLDIR)/$(TARGET)
	chmod u+s $(INSTALLDIR)/$(TARGET)
	$(STRIP) $(INSTALLDIR)/$(TARGET)
	cp tfiles/*.t $(INSTALLDIR)
	cp tfiles/ob_title.gif $(INSTALLDIR)
	cp index.html $(INSTALLDIR)

install: install-cgi
	if [ ! -d "$(_CONTRIBDIR)/etc/defaults" ]; then mkdir -p $(_CONTRIBDIR)/etc/defaults ; fi
	cp etc/openblocks.conf $(_CONTRIBDIR)/etc/
	cp etc/openblocks.conf $(_CONTRIBDIR)/etc/defaults/
	cp etc/smb.conf $(_CONTRIBDIR)/etc/defaults/
	cp etc/thttpd.conf $(_CONTRIBDIR)/etc/
	cp etc/thttpd.conf $(_CONTRIBDIR)/etc/defaults/
	cp etc/setup_thttpd.conf $(_CONTRIBDIR)/etc/setup_thttpd.conf
	cp ../../etc/common/dhcpd.conf.sample $(_CONTRIBDIR)/etc/defaults/dhcpd.conf
	cp ../../etc/common/namedb/named.conf $(_CONTRIBDIR)/etc/defaults/
.if ${SENDMAIL_VER} == "v8"
	cp etc/sendmail.cf $(_CONTRIBDIR)/etc/defaults/
.endif
	cp etc/rc.local $(_CONTRIBDIR)/etc/
	chmod 555 $(_CONTRIBDIR)/etc/rc.local
	cp etc/netstart.local $(_CONTRIBDIR)/etc/

setup.cgi: $(OBJS)
	$(CC) $(CFLAGS) $(DEBUGS) $(OBJS) -o setup.cgi -lcrypt
	sed -e 's/%HTTPD_PORT%/${HTTPD_PORT}/' etc/setup_thttpd.conf.in > etc/setup_thttpd.conf

setup_custom0.cgi: $(OBJS_CUSTOM0)
	$(CC) $(CFLAGS) $(DEBUGS) $(OBJS_CUSTOM0) -o setup_custom0.cgi -lcrypt

setup_custom0.o: setup.c
	$(CC) $(CFLAGS) $(DEBUGS) -g -c -DCUSTOM0=1 setup.c -o ${.TARGET}

yazaki-main_custom0.o: yazaki-main.c
	$(CC) $(CFLAGS) $(DEBUGS) -g -c -DCUSTOM0=1 yazaki-main.c -o ${.TARGET}

misc.o: misc.c setup.h sym.h
list.o: list.c setup.h sym.h
setup.o: setup.c setup.h sym.h
setup_custom0.o: setup.c setup.h sym.h
eval.o: eval.c setup.h sym.h
ok.o: ok.c setup.h sym.h
valtab.o: valtab.c setup.h sym.h
str.o: str.c setup.h sym.h
io.o: io.c setup.h sym.h
yazaki-main.o: setup.h sym.h
yazaki-main_custom0.o: setup.h sym.h
rc2conf.o: setup.h sym.h
sym.o: sym.c
sym.c: symtab

sym.h: symtab gensym
	perl ./gensym < symtab
