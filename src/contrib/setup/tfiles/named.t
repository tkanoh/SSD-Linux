<FORM <?def_formarg()?>>
<?input_hidden("typ","named")?>
<?input_hidden("op","$op")?>
<?input_hidden("subop","$subop")?>
<?input_hidden("i_login","$x_login")?>
<?input_hidden("i_key","$x_key")?>
<?head("������")?>
<P>
<TABLE>
<TR>
 <TD><?input_checkbox("i_named_enable","$x_named_enable")?></TD>
 <TD>named��ư���˵�ư����</TD>
</TR>
</TABLE>
<P>
<INPUT TYPE=SUBMIT NAME=s_ok VALUE="�ѹ�">
<HR>
</FORM>
<FORM <?def_formarg()?>>
<?input_hidden("typ","named")?>
<?input_hidden("op","$op")?>
<?input_hidden("subop","$subop")?>
<?input_hidden("i_login","$x_login")?>
<?input_hidden("i_key","$x_key")?>
<TABLE BORDER=0 CELLPADDING=6 CELLSPACING=2>
<TR>
  <TD BGCOLOR="#eeeeee">#</TD>
  <TD BGCOLOR="#eeeeee">������̾</TD>
  <TD BGCOLOR="#eeeeee">������</TD>
</TR>
<?zone_trlist()?>
</TABLE>
<P>
<?head2("��������ɲ�")?>
<P>
<TABLE BORDER=0 CELLPADDING=6 CELLSPACING=2>
<TR>
  <TD BGCOLOR="#eeeeee">������̾</TD>
  <TD BGCOLOR="#eeeeee">������</TD>
</TR>
<TR>
  <?input_hidden("i_named_zone_id",nextval(eval("x_named_zone__")))?>
  <TD><?input_text("i_named_zone_name___T","")?></TD>
  <TD><?input_select("i_named_zone_typ___T","","master","slave")?></TD>
</TR>
</TABLE>
<INPUT TYPE=SUBMIT NAME=s_ok2 VALUE="�ɲ�">
</FORM>
<!-- $Id: named.t,v 1.1 2003/01/10 17:03:27 kanoh Exp $ -->
