#
#	$Id: README.TXT,v 1.1 2002/07/08 06:57:25 nao Exp $
#

OpenBlockS����ե�����ɥ������

ư��Ķ�

��OpenBlockS
���ե����०����(1.09h)

�¸��Ķ�

�ǥ������� mkhdrt�ǥե����ޥåȡ��ޥ���Ȥ���1.09h��ե륳�ԡ�����
����� ext1.tgz���񤭤ǥ��󥹥ȡ��뤷����ΤǼ¸�

���󥹥ȡ���

1) setup.tgz��Ŭ���ʥǥ��쥯�ȥ��Ÿ��
2) setup.cgi�� /etc/httpd/cgi-bin�˥��ԡ�
3) *.t�� /etc/httpd/cgi-bin�˥��ԡ�
4) ob_title.gif�� /etc/httpd/html�˥��ԡ�
5) root/etc/defaults/* �� /etc/defaults�β��˥��ԡ�
6) touch /etc/openblocks.conf
7) mkdir /var/named/db


��) /usr/local/apache/conf/srm.conf /usr/local/apache/conf/access.conf�Ͼä��ơ�
    touch�ǥ�������0�Υե������������Ƥ������ۤ����褤�Ȼפ��ޤ���

�����

0)�ǥХå��С������
�����ߤϥǥХå����ưפˤ��뤿������GET�ǥե��������Ƥ��������Ƥ��뤬����
  ��Ū�ˤ� POST�ˤ���ͽ��
��/tmp/setup.debug�Ȥ����ե������������롣�����¹Ԥ���������CGI��gdb
  ��ȤäƼ¹Ԥ�ȥ졼���Ǥ��롣

1)����

���桼���������������ƤΥѥ�᡼���� /etc/openblocks.conf����¸����롣
���̾���ѹ��ϥܥ���򲡤��������ǤϹ�������ʤ���
�������������ա����������¨�¤�ȿ�Ǥ���롣
���桼�����ɲ�/����ϡ�������¸�Υǥե���Ȥ�������᤹�פ��᤻�ʤ���
��eth0¦(100BASE)���������˥塼�򳫤��ʤ�������� openblocks.conf��
  x_openblocks_access_limit���ͤ��Ѥ��뤳�Ȥ��ѹ����뤳�Ȥ��Ǥ��롣
��setup.cgi�� setuid�򤹤롣

2)�����ƥ�

2-1)�ۥ��ȥ͡���

���ѹ��򲡤��ȥۥ��ȥ͡���򹹿����롣�ѹ�����¸���Ƶ�ư��ͭ���Ȥʤ롣

�б�
openblocks.conf:	x_hostname

2-2) ���ջ���

���ѹ��򲡤���¨�¤˹�������롣

3)�桼������

��������򤹤�ȥ桼���������ɲä����򤹤�ȥ桼�����ɲä��롣�ɲá�
�����useradd��userdel�������ǸƤ֤��Ȥˤ��Ԥʤ��롣

���桼����gid�� 100�����ꤵ��Ƥ��롣
���ۡ���ǥ��쥯�ȥ�� /home�����ꤵ��Ƥ��롣

4)�ͥåȥ��

4-1)�롼�ƥ���

���ѹ��򲡤��ȹ������롣�ѹ�����¸���Ƶ�ư��ͭ���Ȥʤ롣
openblocks.conf:	x_defaultroute_adr, x_defaultroute_interface

4-2)�������ͥå�1

���ѹ��򲡤��ȹ������롣�ѹ�����¸���Ƶ�ư��ͭ���Ȥʤ롣
openblocks.conf:	x_eth_typ__eth0,x_eth_adr__eth0,x_eth_subnet_mask__eth0
			x_eth_typ_broadcast__eth0

4-3)�������ͥå�2

���ѹ��򲡤��ȹ������롣�ѹ�����¸���Ƶ�ư��ͭ���Ȥʤ롣
openblocks.conf:	x_eth_typ__eth1,x_eth_adr__eth1,x_eth_subnet_mask__eth1
			x_eth_typ_broadcast__eth1

4-4)�꥾�������

���ѹ��򲡤��ȹ������롣�ѹ�����¸���Ƶ�ư��ͭ���Ȥʤ롣

openblocks.conf:	x_nameserver,x_nameserver2,x_nameserver3,x_domain
/etc/resolv.conf:	

5)���ɥ쥹�Ѵ�

5-1)IP�ޥ����졼��
���ѹ��򲡤��ȹ������롣�����ܤ����򤹤��
ipchains -A forward -i eth1 -j MASQ

�����ܤ����򤹤��
ipchains -A forward -i eth0 -j MASQ

��/etc/rc.iptables�˽񤭹��ޤ�롣

openblocks.conf:	x_msq_typ
/etc/rc.iptables

6)�ʰץե����䥦������

6-1)�ݡ��ȥե����
���ɲä򲡤����ɲä���롣x_portfw__�˥ꥹ�Ȥΰ���
  x_portfw__%s�������ͤ���Ǽ����롣

openblocks.conf:	x_portfw__ x_portfw__%s
/etc/rc.iptables

6-2)�ʰץե����䥦������

openblocks.conf:	x_fw__ x_fw__%s
/etc/rc.iptables

���ɲä򲡤����ɲä���롣x_fw__�˥ꥹ�Ȥΰ�����x_fw__%s�������ͤ�
  ��Ǽ����롣���ɥ쥹���ݡ��Ȥˤ�ANY�򵭽Ҥ��뤳�Ȥ��Ǥ��롣

7)����¾
7-1) dhcpd
���ѹ��򲡤��ȹ������롣������ /etc/defaults/dhcpd.conf
����ư���롢���ʤ������������ϤǤ��뤬���ޤ���ǽ���Ƥ��ʤ�

openblocks.conf:	x_dhcpd_enable__eth0
			x_dhcpd_range1__eth0
			x_dhcpd_range2__eth0
			x_dhcpd_nameserver__eth0
			x_dhcpd_domainname__eth0
			x_dhcpd_routers__eth0
			x_dhcpd_subnet_mask__eth0
			x_dhcpd_range1__eth1
			x_dhcpd_range2__eth1
			x_dhcpd_nameserver__eth1
			x_dhcpd_domainname__eth1
			x_dhcpd_routers__eth1
			x_dhcpd_subnet_mask__eth1

/etc/dhcpd.conf

7-1-2) sendmail

���ѹ��򲡤��ȹ������롣������ /etc/defaults/sendmail.cf
����ư���롢���ʤ������������ϤǤ��뤬���ޤ���ǽ���Ƥ��ʤ�
�����ե������ۥ���̾�� Dj
���ɥᥤ��̾�� Dm
����̾�ɥᥤ��̾�� Cw
����졼���ĥۥ��Ȥ� C{localIP}�˳�Ǽ�����

openblocks.conf:	x_sendmail_enable
/etc/sendmail.cf

7-1-3) named
����ư���롢���ʤ������������ϤǤ��뤬���ޤ���ǽ���Ƥ��ʤ�
��localhost, 127.IN-ADDR.ARPA �ϼ�ư�ǥޥ����Ȥ�����������롣
���ޤ�����������ɲä��롣������ϥޥ������ȥ��졼�֤�����Ǥ��롣
  ���줫�顢������������Ԥ���
���ޥ������Ǥϥ쥳���ɤ��ɲäǤ��� (SOA��������ϸ���ʤΤ�����Ǥ��ʤ�)
�����졼�֤Ǥϥޥ���DNS�����Ǥ���

/etc/named.conf
/var/named/*

7-1-4) httpd
����ư���롢���ʤ������������ϤǤ��뤬���ޤ���ǽ���Ƥ��ʤ�
���ѹ��򲡤��ȹ������롣������ /etc/defaults/httpd.conf

openblocks.conf:	x_httpd_enable, x_httpd_document_root, x_httpd_script_alias
/usr/local/apache/conf/httpd.conf

OpenBlcokSS ���

�� /etc/tmp.conf �Ͼä�
�� x_key����¸���ʤ�
�� x_openblocks_autoconfig_version -> ������

�� /var/named/db -> /var/named
���桼�������ΤȤ��� home �ǥ��쥯�ȥ���������褦���ѹ�
������ΤȤ��� home�ǥ��쥯�ȥ��������褦���ѹ�
��x_hostname�� x_domainname���ѹ������Ȥ��� named.local���ѹ�����褦���ѹ�
��iptables��Ȥ��褦���ѹ�
��/etc/flashcfg��̵����硢�⤷���� /etc/flashcfg�Υ�������0�ξ��� flashcfg��¹Ԥ��ʤ��褦�ѹ�

��Makefile����
��malloc����(malloc���äѤʤ�)

���ֹ�μ㤤named�Υ쥳���ɤ�ä��ȡ�����ʹߤ��ä��ʤ��ʤ�(����)


��IP�ޥ����졼�ɤ��ɵ��⡼�ɤ�upsetconf�򥪡��ץ󤹤뤿�ᡢ������Ѥ��Ƥ�ȿ�Ǥ���ʤ�
  ��ľ���� IP�ե��륿�����ꤹ��Ȥ����� upsetconf��ɬ�������ץ󤷤ƥ�����0�ˤ���褦�ѹ�