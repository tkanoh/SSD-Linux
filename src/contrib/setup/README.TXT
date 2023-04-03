#
#	$Id: README.TXT,v 1.1 2002/07/08 06:57:25 nao Exp $
#

OpenBlockS設定ファイルドキュメント

動作環境

・OpenBlockS
・ファームウェア(1.09h)

実験環境

ディスクを mkhdrtでフォーマット、マウントし、1.09hをフルコピーし、
さらに ext1.tgzを上書きでインストールしたもので実験

インストール

1) setup.tgzを適当なディレクトリで展開
2) setup.cgiを /etc/httpd/cgi-binにコピー
3) *.tを /etc/httpd/cgi-binにコピー
4) ob_title.gifを /etc/httpd/htmlにコピー
5) root/etc/defaults/* を /etc/defaultsの下にコピー
6) touch /etc/openblocks.conf
7) mkdir /var/named/db


※) /usr/local/apache/conf/srm.conf /usr/local/apache/conf/access.confは消して、
    touchでサイズが0のファイルを作成しておいたほうがよいと思います。

操作等

0)デバッグバージョン
・現在はデバッグを容易にするため全てGETでフォーム内容を送信しているが、将
  来的には POSTにする予定
・/tmp/setup.debugというファイルを作成する。これを実行すると前回のCGIをgdb
  を使って実行をトレースできる。

1)仕様

・ユーザ、時刻を除く全てのパラメータは /etc/openblocks.confに保存される。
・通常の変更はボタンを押しただけでは更新されない。
・ただし、日付・時刻だけは即座に反映される。
・ユーザの追加/削除は「設定保存のデフォルトの設定に戻す」で戻せない。
・eth0側(100BASE)から設定メニューを開けない。これは openblocks.confの
  x_openblocks_access_limitの値を変えることで変更することができる。
・setup.cgiは setuidをする。

2)システム

2-1)ホストネーム

・変更を押すとホストネームを更新する。変更は保存、再起動後有効となる。

対応
openblocks.conf:	x_hostname

2-2) 日付時刻

・変更を押すと即座に更新される。

3)ユーザ管理

削除を選択するとユーザを削除、追加を選択するとユーザを追加する。追加、
削除はuseradd、userdelを内部で呼ぶことにより行なわれる。

・ユーザのgidは 100に設定されている。
・ホームディレクトリは /homeに設定されている。

4)ネットワーク

4-1)ルーティング

・変更を押すと更新する。変更は保存、再起動後有効となる。
openblocks.conf:	x_defaultroute_adr, x_defaultroute_interface

4-2)イーサネット1

・変更を押すと更新する。変更は保存、再起動後有効となる。
openblocks.conf:	x_eth_typ__eth0,x_eth_adr__eth0,x_eth_subnet_mask__eth0
			x_eth_typ_broadcast__eth0

4-3)イーサネット2

・変更を押すと更新する。変更は保存、再起動後有効となる。
openblocks.conf:	x_eth_typ__eth1,x_eth_adr__eth1,x_eth_subnet_mask__eth1
			x_eth_typ_broadcast__eth1

4-4)リゾルバ設定

・変更を押すと更新する。変更は保存、再起動後有効となる。

openblocks.conf:	x_nameserver,x_nameserver2,x_nameserver3,x_domain
/etc/resolv.conf:	

5)アドレス変換

5-1)IPマスカレード
・変更を押すと更新する。二番目を選択すると
ipchains -A forward -i eth1 -j MASQ

三番目を選択すると
ipchains -A forward -i eth0 -j MASQ

が/etc/rc.iptablesに書き込まれる。

openblocks.conf:	x_msq_typ
/etc/rc.iptables

6)簡易ファイヤウォール

6-1)ポートフォワード
・追加を押すと追加される。x_portfw__にリストの引数
  x_portfw__%sに設定値が格納される。

openblocks.conf:	x_portfw__ x_portfw__%s
/etc/rc.iptables

6-2)簡易ファイヤウォール

openblocks.conf:	x_fw__ x_fw__%s
/etc/rc.iptables

・追加を押すと追加される。x_fw__にリストの引数、x_fw__%sに設定値が
  格納される。アドレス、ポートにはANYを記述することができる。

7)その他
7-1) dhcpd
・変更を押すと更新する。雛型は /etc/defaults/dhcpd.conf
・起動する、しないの設定は設定はできるが、まだ機能していない

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

・変更を押すと更新する。雛型は /etc/defaults/sendmail.cf
・起動する、しないの設定は設定はできるが、まだ機能していない
・オフィシャルホスト名は Dj
・ドメイン名は Dm
・別名ドメイン名は Cw
・リレー許可ホストは C{localIP}に格納される

openblocks.conf:	x_sendmail_enable
/etc/sendmail.cf

7-1-3) named
・起動する、しないの設定は設定はできるが、まだ機能していない
・localhost, 127.IN-ADDR.ARPA は自動でマスタとして生成される。
・まず、ゾーンを追加する。ゾーンはマスターとスレーブを選択できる。
  それから、ゾーンの設定を行う。
・マスターではレコードを追加できる (SOA等の設定は固定なので設定できない)
・スレーブではマスタDNSを指定できる

/etc/named.conf
/var/named/*

7-1-4) httpd
・起動する、しないの設定は設定はできるが、まだ機能していない
・変更を押すと更新する。雛型は /etc/defaults/httpd.conf

openblocks.conf:	x_httpd_enable, x_httpd_document_root, x_httpd_script_alias
/usr/local/apache/conf/httpd.conf

OpenBlcokSS メモ

・ /etc/tmp.conf は消す
・ x_keyを保存しない
・ x_openblocks_autoconfig_version -> 埋め込み

・ /var/named/db -> /var/named
・ユーザ作成のときに home ディレクトリを作成するように変更
・削除のときに homeディレクトリを削除するように変更
・x_hostnameと x_domainnameを変更したときに named.localを変更するように変更
・iptablesを使うように変更
・/etc/flashcfgが無い場合、もしくは /etc/flashcfgのサイズが0の場合は flashcfgを実行しないよう変更

・Makefile修正
・malloc修正(mallocしっぱなし)

・番号の若いnamedのレコードを消すと、それ以降が消せなくなる(修正)


・IPマスカレードが追記モードでupsetconfをオープンするため、設定を変えても反映されない
  →直前の IPフィルタを設定するところで upsetconfを必ずオープンしてサイズ0にするよう変更
