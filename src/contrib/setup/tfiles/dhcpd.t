<?head("�ܺ�����")?>
<FORM <?def_formarg()?>>
<?input_hidden("typ","dhcpd")?>
<?input_hidden("op","$op")?>
<?input_hidden("subop","$subop")?>
<?input_hidden("i_login","$x_login")?>
<?input_hidden("i_key","$x_key")?>
<TABLE BORDER=0>
<TR>
 <TD><?input_checkbox("i_dhcpd_enable__eth0","$x_dhcpd_enable__eth0")?></TD>
 <TD COLSPAN=2>eth0¦��dhcpd����Ѥ���</TD>
</TR>
<TR>
<TR>
 <TD>&nbsp;</TD>
 <TD><B>�ϰ�:</B></TD>
 <TD><?input_text("i_dhcpd_range1__eth0","$x_dhcpd_range1__eth0")?>��<?input_text("i_dhcpd_range2__eth0","$x_dhcpd_range2__eth0")?></TD>
</TR>
<TR>
 <TD>&nbsp;</TD>
 <TD><B>�͡��ॵ����:</B></TD>
 <TD><?input_text("i_dhcpd_nameserver__eth0","$x_dhcpd_nameserver__eth0")?></TD>
</TR>
<TR>
 <TD>&nbsp;</TD>
 <TD><B>�ɥᥤ��̾:</B></TD>
 <TD><?input_text("i_dhcpd_domainname__eth0","$x_dhcpd_domainname__eth0")?></TD>
</TR>
<TR>
 <TD>&nbsp;</TD>
 <TD><B>�����ȥ�����:</B></TD>
 <TD><?input_text("i_dhcpd_routers__eth0","$x_dhcpd_routers__eth0")?></TD>
</TR>
<TR>
 <TD>&nbsp;</TD>
 <TD><B>�ͥåȥޥ���:</B></TD>
 <TD><?input_netmask("i_dhcpd_subnet_mask__eth0","$x_dhcpd_subnet_mask__eth0")?></TD>
</TR>
</TABLE>
<P>
<HR>
<TABLE BORDER=0>
<TR>
 <TD><?input_checkbox("i_dhcpd_enable__eth1","$x_dhcpd_enable__eth1")?></TD>
 <TD COLSPAN=2>eth1¦��dhcpd����Ѥ���</TD>
</TR>
<TR>
<TR>
 <TD>&nbsp;</TD>
 <TD><B>�ϰ�:</B></TD>
 <TD><?input_text("i_dhcpd_range1__eth1","$x_dhcpd_range1__eth1")?>��<?input_text("i_dhcpd_range2__eth1","$x_dhcpd_range2__eth1")?></TD>
</TR>
<TR>
 <TD>&nbsp;</TD>
 <TD><B>�͡��ॵ����:</B></TD>
 <TD><?input_text("i_dhcpd_nameserver__eth1","$x_dhcpd_nameserver__eth1")?></TD>
</TR>
<TR>
 <TD>&nbsp;</TD>
 <TD><B>�ɥᥤ��̾:</B></TD>
 <TD><?input_text("i_dhcpd_domainname__eth1","$x_dhcpd_domainname__eth1")?></TD>
</TR>
<TR>
 <TD>&nbsp;</TD>
 <TD><B>�����ȥ�����:</B></TD>
 <TD><?input_text("i_dhcpd_routers__eth1","$x_dhcpd_routers__eth1")?></TD>
</TR>
<TR>
 <TD>&nbsp;</TD>
 <TD><B>�ͥåȥޥ���:</B></TD>
 <TD><?input_netmask("i_dhcpd_subnet_mask__eth1","$x_dhcpd_subnet_mask__eth1")?></TD>
</TR>
</TABLE>
<P>
<INPUT TYPE=SUBMIT NAME=s_ok VALUE="�ѹ�">
</FORM>
<!-- $Id: dhcpd.t,v 1.3 2003/03/11 07:35:49 yamagata Exp $ -->
