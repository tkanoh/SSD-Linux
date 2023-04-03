<FORM <?def_formarg()?>>
<?input_hidden("typ","login")?>
<?input_hidden("op","$op")?>
<P>
<TABLE ALIGN=CENTER BGCOLOR="#eeeeee" BORDER=0 CELLPADDING=6 CELLSPACING=2>
<TR>
 <TD COLSPAN="2"><?head("OpenBlockS")?></TD>
</TR>
<TR>
 <TD COLSPAN="2">ログイン名またはパスワードが間違っています</TD>
</TR>
<TR>
 <TD><B>ログイン名:</B></TD><TD><?input_text("i_login","")?></TD>
</TR>
<TR>
 <TD><B>パスワード:</B></TD><TD><?input_passwd("i_passwd","")?></TD>
</TR>
<TR>
 <TD ALIGN=center COLSPAN=2><INPUT TYPE=SUBMIT NAME="login_ok" VALUE="ログイン"></TD>
</TR>
</TABLE>
</FORM>
<!-- $Id: badpasswd.t,v 1.2 2003/02/19 06:49:45 yamagata Exp $ -->
