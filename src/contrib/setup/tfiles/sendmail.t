<?head("sendmail����")?>
<FORM <?def_formarg()?>>
<?input_hidden("typ","sendmail")?>
<?input_hidden("op","$op")?>
<?input_hidden("subop","$subop")?>
<?input_hidden("i_login","$x_login")?>
<?input_hidden("i_key","$x_key")?>
<TABLE>
<TR>
 <TD><?input_checkbox("i_sendmail_enable","$x_sendmail_enable")?></TD>
 <TD COLSPAN=2>sendmail��ư���˵�ư����</TD>
</TR>
<TR>
<TD>&nbsp;</TD>
<TD>�ۥ���̾(FQDN):</TD><TD><?input_text("i_sendmail_my_official_smtp_hostname","$x_sendmail_my_official_smtp_hostname","SIZE=40")?></TD>
</TR>
<TR>
<TD>&nbsp;</TD>
<TD>�ɥᥤ��̾:</TD><TD><?input_text("i_sendmail_local_domain_name","$x_sendmail_local_domain_name","SIZE=40")?>
</TR>
<TR>
<TD>&nbsp;</TD>
<TD>��̾�ɥᥤ��̾:</TD><TD><?input_text("i_sendmail_domain_alias1","$x_sendmail_domain_alias1","SIZE=40")?></TD>
</TR>
</TABLE>
<P>
<INPUT TYPE=SUBMIT NAME=s_ok VALUE="����">
</FORM>
<FORM <?def_formarg()?>>
<?input_hidden("typ","sendmail")?>
<?input_hidden("op","$op")?>
<?input_hidden("subop","$subop")?>
<?input_hidden("i_login","$x_login")?>
<?input_hidden("i_key","$x_key")?>
<?head("��졼���ĥۥ���")?>
<P>
<TABLE BORDER=0 CELLPADDING=6 CELLSPACING=2>
<TR>
 <TD BGCOLOR=#eeeeee>�ۥ���̾.�ɥᥤ��̾</TD>
 <TD></TD>
</TR>
<?trlist("x_sendmail_relay__","x_sendmail_relay__%s")?>
</TABLE>
<?head2("�ɲ�")?>
<TABLE>
<TR>
 <?input_hidden("i_sendmail_relay_id",nextval(eval("x_sendmail_relay__")))?>
 <TD><?input_text("i_sendmail_relay___T","")?></TD>
</TR>
</TABLE>
<INPUT TYPE=SUBMIT NAME=s_ok2 VALUE="�ɲ�">
</FORM>
<!-- $Id: sendmail.t,v 1.2 2003/02/19 07:31:55 yamagata Exp $ -->
