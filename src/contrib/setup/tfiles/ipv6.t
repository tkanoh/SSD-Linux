<FORM <?def_formarg()?>>
<?input_hidden("typ","ipv6")?>
<?input_hidden("op","$op")?>
<?input_hidden("subop","$subop")?>
<?input_hidden("i_login","$x_login")?>
<?input_hidden("i_key","$x_key")?>
<?head("eth0")?>
<P>
<TABLE>
<TR>
 <TD><?input_checkbox("i_ipv6_enable__eth0","$x_ipv6_enable__eth0")?></TD>
 <TD><B>IPv6����Ѥ���</B></TD>
</TR>
<TR>
 <TD>&nbsp;</TD>
 <TD ALIGN="RIGHT">�ץ�ե�����:</TD>
 <TD><?input_text("i_ipv6_prefix__eth0","$x_ipv6_prefix__eth0","SIZE=25")?></TD>
 <TD>/64</TD>
</TR>
</TABLE>
<P>
<?head("eth1")?>
<P>
<TABLE>
<TR>
 <TD><?input_checkbox("i_ipv6_enable__eth1","$x_ipv6_enable__eth1")?></TD>
 <TD><B>IPv6����Ѥ���</B></TD>
</TR>
<TR>
 <TD>&nbsp;</TD>
 <TD ALIGN="RIGHT">�ץ�ե�����:</TD>
 <TD><?input_text("i_ipv6_prefix__eth1","$x_ipv6_prefix__eth1","SIZE=25")?></TD>
 <TD>/64</TD>
</TR>
</TABLE>
<P>
<?head("IPv6 over IPv4�ȥ�ͥ�����")?>
<P>
<TABLE>
<TR>
 <TD><?input_checkbox("i_ipv6_tunnel","$x_ipv6_enable__eth0")?></TD>
 <TD><B>�ȥ�ͥ����Ѥ���</B></TD>
</TR>
<TR>
 <TD>&nbsp;</TD>
 <TD ALIGN="RIGHT"><B>��ʬ¦v4���ɥ쥹:</B></TD>
 <TD><?input_text("i_ipv6_tunnel_here", "$x_ipv6_tunnel_here")?></TD>
</TR>
<TR>
 <TD>&nbsp;</TD>
 <TD ALIGN="RIGHT"><B>���¦v4���ɥ쥹:</B></TD>
 <TD><?input_text("i_ipv6_tunnel_there", "$x_ipv6_tunnel_there")?></TD>
</TR>
</TABLE>
<P>
<INPUT TYPE=SUBMIT NAME=s_ok VALUE="�ѹ�">
<P>
</FORM>
