<FORM <?def_formarg()?>>
<?input_hidden("typ","user")?>
<?input_hidden("op","$op")?>
<?input_hidden("subop","$subop")?>
<?input_hidden("i_login","$x_login")?>
<?input_hidden("i_key","$x_key")?>
<?head("��Ͽ�桼������")?>
<P>
<TABLE BORDER=0 CELLPADDING=6 CELLSPACING=2>
<TR>
 <TD BGCOLOR="#eeeeee">UID</TD>
 <TD BGCOLOR="#eeeeee">������̾</TD>
 <TD BGCOLOR="#eeeeee">�桼��̾</TD>
 <TD></TD>
</TR>
<?user_trlist()?>
</TABLE>
<P>
<?head("�桼���ɲ�")?>
<P>
<TABLE>
<TR>
 <TD><B>UID:</B></TD><TD><?user_nextid()?></TD>
</TR>
<TR>
 <TD><B>������̾:</B></TD><TD><?input_text("i_user_login___T","")?></TD>
</TR>
<TR>
 <TD><B>�桼��̾:</B></TD><TD><?input_text("i_user_name___T","")?></TD>
</TR>
<TR>
 <TD><B>�ѥ����:</B></TD><TD><?input_passwd("i_user_passwd___T","")?></TD>
</TR>
<TR>
 <TD><B>������:</B></TD><TD><?input_passwd("i_user_passwd2___T","")?></TD>
</TR>
<TR>
</TABLE>
<P>
<INPUT TYPE=SUBMIT NAME=s_ok VALUE="�ɲ�">
</FORM>
<!-- $Id: user.t,v 1.4 2003/02/19 07:05:19 yamagata Exp $ -->
