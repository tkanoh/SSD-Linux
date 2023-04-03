<?head(eval("x_named_zone__${a2}")[1])?>
<FORM <?def_formarg()?>>
<?input_hidden("typ","named_master_soa")?>
<?input_hidden("op","$op")?>
<?input_hidden("subop","$subop")?>
<?input_hidden("i_login","$x_login")?>
<?input_hidden("i_key","$x_key")?>
<?input_hidden("a","$a")?>
<?input_hidden("a2","$a2")?>
<?head2("SOA")?>
<P>
<TABLE BORDER=0 CELLPADDING=6 CELLSPACING=2>
<TR>
  <TD>ホスト名:</TD>
  <TD><?input_text("i_named_zone_soa_mname__${a2}",eval("x_named_zone_soa_mname__${a2}"))?></TD>
</TR>
<TR>
  <TD>メール・アドレス:</TD>
  <TD><?input_text("i_named_zone_soa_rname__${a2}",eval("x_named_zone_soa_rname__${a2}"))?></TD>
</TR>
</TABLE>
<P>
<INPUT TYPE=SUBMIT NAME=s_ok VALUE="更新">
<P>
<HR>
</FORM>
<P>
<FORM <?def_formarg()?>>
<?input_hidden("typ","named_master")?>
<?input_hidden("op","$op")?>
<?input_hidden("subop","$subop")?>
<?input_hidden("i_login","$x_login")?>
<?input_hidden("i_key","$x_key")?>
<?input_hidden("a","$a")?>
<?input_hidden("a2","$a2")?>
<?head2("レコード")?>
<P>
<TABLE BORDER=0 CELLPADDING=6 CELLSPACING=2>
<TR>
  <TD BGCOLOR="#eeeeee">name</TD>
  <TD BGCOLOR="#eeeeee">type</TD>
  <TD BGCOLOR="#eeeeee">resource</TD>
</TR>
<?trlist("x_named_zone_record__${a2}__","x_named_zone_record__${a2}__%s")?>
</TABLE>
<P>
<P>
<TABLE BORDER=0 CELLPADDING=6 CELLSPACING=2>
<TR>
  <?input_hidden("i_named_zone_record_id",nextval(eval("x_named_zone_record__${a2}__")))?>
  <TD><?input_text("i_named_zone_record_domain___T","")?></TD>
  <TD><?input_select("i_named_zone_record_typ___T","","A","AAAA","PTR","NS","CNAME","MX")?></TD>
  <TD><?input_text("i_named_zone_record_resource___T","")?></TD>
</TR>
</TABLE>
<INPUT TYPE=SUBMIT NAME=s_ok2 VALUE="追加">

</FORM>
<!-- $Id: named-master.t,v 1.2 2003/02/20 03:37:04 yamagata Exp $ -->
