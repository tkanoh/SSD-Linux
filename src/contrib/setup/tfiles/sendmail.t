<?head("sendmail設定")?>
<FORM <?def_formarg()?>>
<?input_hidden("typ","sendmail")?>
<?input_hidden("op","$op")?>
<?input_hidden("subop","$subop")?>
<?input_hidden("i_login","$x_login")?>
<?input_hidden("i_key","$x_key")?>
<TABLE>
<TR>
 <TD><?input_checkbox("i_sendmail_enable","$x_sendmail_enable")?></TD>
 <TD COLSPAN=2>sendmailを起動時に起動する</TD>
</TR>
<TR>
<TD>&nbsp;</TD>
<TD>ホスト名(FQDN):</TD><TD><?input_text("i_sendmail_my_official_smtp_hostname","$x_sendmail_my_official_smtp_hostname","SIZE=40")?></TD>
</TR>
<TR>
<TD>&nbsp;</TD>
<TD>ドメイン名:</TD><TD><?input_text("i_sendmail_local_domain_name","$x_sendmail_local_domain_name","SIZE=40")?>
</TR>
<TR>
<TD>&nbsp;</TD>
<TD>別名ドメイン名:</TD><TD><?input_text("i_sendmail_domain_alias1","$x_sendmail_domain_alias1","SIZE=40")?></TD>
</TR>
</TABLE>
<P>
<INPUT TYPE=SUBMIT NAME=s_ok VALUE="更新">
</FORM>
<FORM <?def_formarg()?>>
<?input_hidden("typ","sendmail")?>
<?input_hidden("op","$op")?>
<?input_hidden("subop","$subop")?>
<?input_hidden("i_login","$x_login")?>
<?input_hidden("i_key","$x_key")?>
<?head("リレー許可ホスト")?>
<P>
<TABLE BORDER=0 CELLPADDING=6 CELLSPACING=2>
<TR>
 <TD BGCOLOR=#eeeeee>ホスト名.ドメイン名</TD>
 <TD></TD>
</TR>
<?trlist("x_sendmail_relay__","x_sendmail_relay__%s")?>
</TABLE>
<?head2("追加")?>
<TABLE>
<TR>
 <?input_hidden("i_sendmail_relay_id",nextval(eval("x_sendmail_relay__")))?>
 <TD><?input_text("i_sendmail_relay___T","")?></TD>
</TR>
</TABLE>
<INPUT TYPE=SUBMIT NAME=s_ok2 VALUE="追加">
</FORM>
<!-- $Id: sendmail.t,v 1.2 2003/02/19 07:31:55 yamagata Exp $ -->
