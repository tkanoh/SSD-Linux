<FORM <?def_formarg()?>>
<?input_hidden("typ","sendmail")?>
<?input_hidden("op","$op")?>
<?input_hidden("subop","$subop")?>
<?input_hidden("i_login","$x_login")?>
<?input_hidden("i_key","$x_key")?>
<?head("設定")?>
<P>
<TABLE>
<TR>
  <TD><?input_radio("x_save_mode","1","1")?></TD>
  <TD>保存</TD>
</TR>
<TR>
  <TD><?input_radio("x_save_mode","2")?></TD>
  <TD>保存して再起動</TD>
</TR>
<TR>
  <TD><?input_radio("x_save_mode","3")?></TD>
  <TD>保存して停止</TD>
</TR>
<TR>
  <TD><?input_radio("x_save_mode","4")?></TD>
  <TD>保存しないで停止</TD>
</TR>
<TR>
  <TD><?input_radio("x_save_mode","5")?></TD>
  <TD>デフォルトに戻す</TD>
</TR>
</TABLE>
<P>
<INPUT TYPE=SUBMIT NAME=s_ok VALUE="実行">
<P>
</FORM>
<!-- $Id: save.t,v 1.1 2003/01/10 17:03:27 kanoh Exp $ -->
