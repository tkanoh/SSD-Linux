<FORM <?def_formarg()?>>
<?input_hidden("typ","sendmail")?>
<?input_hidden("op","$op")?>
<?input_hidden("subop","$subop")?>
<?input_hidden("i_login","$x_login")?>
<?input_hidden("i_key","$x_key")?>
<?head("����")?>
<P>
<TABLE>
<TR>
  <TD><?input_radio("x_save_mode","1","1")?></TD>
  <TD>��¸</TD>
</TR>
<TR>
  <TD><?input_radio("x_save_mode","2")?></TD>
  <TD>��¸���ƺƵ�ư</TD>
</TR>
<TR>
  <TD><?input_radio("x_save_mode","3")?></TD>
  <TD>��¸�������</TD>
</TR>
<TR>
  <TD><?input_radio("x_save_mode","4")?></TD>
  <TD>��¸���ʤ������</TD>
</TR>
<TR>
  <TD><?input_radio("x_save_mode","5")?></TD>
  <TD>�ǥե���Ȥ��᤹</TD>
</TR>
</TABLE>
<P>
<INPUT TYPE=SUBMIT NAME=s_ok VALUE="�¹�">
<P>
</FORM>
<!-- $Id: save.t,v 1.1 2003/01/10 17:03:27 kanoh Exp $ -->
