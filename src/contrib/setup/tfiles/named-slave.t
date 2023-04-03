<FORM <?def_formarg()?>>
<?input_hidden("typ","named_slave")?>
<?input_hidden("op","$op")?>
<?input_hidden("subop","$subop")?>
<?input_hidden("a","$a")?>
<?input_hidden("a2","$a2")?>
<?input_hidden("i_login","$x_login")?>
<?input_hidden("i_key","$x_key")?>
<?head(eval("x_named_zone__${a2}")[1])?>
<P>
<TABLE>
<TR>
<TD>マスタDNSサーバ:</TD><TD><?input_text("i_named_zone_master__${a2}",eval("x_named_zone_master__${a2}"),"SIZE=40")?></TD>
</TR>
</TR>
</TABLE>
<INPUT TYPE=SUBMIT NAME=s_ok VALUE="更新">
</FORM>
<!-- $Id: named-slave.t,v 1.2 2003/02/20 03:37:46 yamagata Exp $ -->
