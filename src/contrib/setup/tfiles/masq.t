<FORM <?def_formarg()?>>
<?input_hidden("typ","masq")?>
<?input_hidden("op","$op")?>
<?input_hidden("subop","$subop")?>
<?input_hidden("i_login","$x_login")?>
<?input_hidden("i_key","$x_key")?>
<?head("IP�ޥ����졼��")?>
<P>
<TABLE>
<TR>
 <TD><?input_radio("i_msq_typ","1","$x_msq_typ")?></TD>
  <TD COLSPAN=2>IP�ޥ����졼�ɤ����Ѥ��ʤ�</TD>
</TR>
<TR>
 <TD><?input_radio("i_msq_typ","2","$x_msq_typ")?></TD>
 <TD COLSPAN=2><A HREF="<?eval("script")?>&op=network">eth0</A> (<?eval("x_eth_adr__eth0")?>) �� eth1 (<?eval("x_eth_adr__eth1")?>)</TD>
</TR>
<TR>
 <TD><?input_radio("i_msq_typ","3","$x_msq_typ")?></TD>
 <TD COLSPAN=2><A HREF="<?eval("script")?>&op=network">eth1</A> (<?eval("x_eth_adr__eth1")?>) �� eth0 (<?eval("x_eth_adr__eth0")?>)</TD>
</TR>
</TABLE>
<P>
<INPUT TYPE=SUBMIT NAME=s_ok VALUE="�ѹ�">
</FORM>
<!-- $Id: masq.t,v 1.2 2003/02/19 03:56:47 yamagata Exp $ -->
