<FORM <?def_formarg()?>>
<?input_hidden("typ","user")?>
<?input_hidden("op","$op")?>
<?input_hidden("subop","$subop")?>
<?input_hidden("i_login","$x_login")?>
<?input_hidden("i_key","$x_key")?>
<?head("登録ユーザ一覧")?>
<P>
<TABLE BORDER=0 CELLPADDING=6 CELLSPACING=2>
<TR>
 <TD BGCOLOR="#eeeeee">UID</TD>
 <TD BGCOLOR="#eeeeee">ログイン名</TD>
 <TD BGCOLOR="#eeeeee">ユーザ名</TD>
 <TD></TD>
</TR>
<?user_trlist()?>
</TABLE>
<P>
<?head("ユーザ追加")?>
<P>
<TABLE>
<TR>
 <TD><B>UID:</B></TD><TD><?user_nextid()?></TD>
</TR>
<TR>
 <TD><B>ログイン名:</B></TD><TD><?input_text("i_user_login___T","")?></TD>
</TR>
<TR>
 <TD><B>ユーザ名:</B></TD><TD><?input_text("i_user_name___T","")?></TD>
</TR>
<TR>
 <TD><B>パスワード:</B></TD><TD><?input_passwd("i_user_passwd___T","")?></TD>
</TR>
<TR>
 <TD><B>再入力:</B></TD><TD><?input_passwd("i_user_passwd2___T","")?></TD>
</TR>
<TR>
</TABLE>
<P>
<INPUT TYPE=SUBMIT NAME=s_ok VALUE="追加">
</FORM>
<!-- $Id: user.t,v 1.4 2003/02/19 07:05:19 yamagata Exp $ -->
