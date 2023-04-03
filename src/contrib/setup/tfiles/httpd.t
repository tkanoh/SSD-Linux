<?head("httpd設定")?>
<FORM <?def_formarg()?>>
<?input_hidden("typ","httpd")?>
<?input_hidden("op","$op")?>
<?input_hidden("subop","$subop")?>
<?input_hidden("i_login","$x_login")?>
<?input_hidden("i_key","$x_key")?>
<TABLE>
<TR>
 <TD><?input_checkbox("i_httpd_enable","$x_httpd_enable")?></TD>
 <TD COLSPAN=2>httpdを使用する</TD>
</TR>
<TR>
 <TD>&nbsp;</TD>
 <TD COLSPAN=2><?input_checkbox("i_httpd_chroot","$x_httpd_chroot")?>Data Directoryにchrootする</TD>
</TR>
<TR>
 <TD>&nbsp;</TD>
 <TD>Data Directory (dir):</TD><TD><?input_text("i_httpd_dir","$x_httpd_dir","SIZE=40")?></TD>
</TR>
<TR>
 <TD>&nbsp;</TD>
 <TD>CGI pattern (cgipat):</TD><TD><?input_text("i_httpd_cgipat","$x_httpd_cgipat","SIZE=40")?></TD>
</TR>
<TR>
 <TD>&nbsp;</TD>
 <TD>Log file (logfile):</TD><TD><?input_text("i_httpd_logfile","$x_httpd_logfile","SIZE=40")?></TD>
</TR>
</TABLE>
<P>
<INPUT TYPE=SUBMIT NAME=s_ok VALUE="更新">
</FORM>
<!-- $Id: httpd.t,v 1.6 2003/03/13 02:52:44 yamagata Exp $ -->
