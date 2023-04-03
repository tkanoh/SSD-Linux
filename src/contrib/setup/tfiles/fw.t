<FORM <?def_formarg()?>>
<?input_hidden("typ","portfw")?>
<?input_hidden("op","$op")?>
<?input_hidden("subop","$subop")?>
<?input_hidden("i_login","$x_login")?>
<?input_hidden("i_key","$x_key")?>
<?head("ポートフォワーディング")?>
<P>
<TABLE BORDER=0 CELLPADDING=6 CELLSPACING=2>
<TR>
 <TD BGCOLOR="#eeeeee" COLSPAN=3>src</TD>
 <TD BGCOLOR="#eeeeee" COLSPAN=2>dst</TD>
 <TD>&nbsp;</TD>
</TR>
<TR>
 <TD BGCOLOR="#dddddd">proto</TD>
 <TD BGCOLOR="#dddddd">interface</TD>
 <TD BGCOLOR="#dddddd">port</TD>
 <TD BGCOLOR="#dddddd">IP</TD>
 <TD BGCOLOR="#dddddd">port</TD>
 <TD>&nbsp;</TD>
</TR>
<?trlist("x_portfw__","x_portfw__%s")?>
</TABLE>
<?head2("追加")?>
<TABLE>
<TR>
 <TD BGCOLOR="#eeeeee" COLSPAN=3>src</TD>
 <TD BGCOLOR="#eeeeee" COLSPAN=2>dst</TD>
 <TD>&nbsp;</TD>
</TR>
<TR>
 <TD BGCOLOR="#dddddd">proto</TD>
 <TD BGCOLOR="#dddddd">interface</TD>
 <TD BGCOLOR="#dddddd">port</TD>
 <TD BGCOLOR="#dddddd">IP</TD>
 <TD BGCOLOR="#dddddd">port</TD>
 <TD>&nbsp;</TD>
</TR>
<TR>
 <?input_hidden("i_portfw_id",nextval(eval("x_portfw__")))?>
 <TD><?input_select("i_portfw_proto___T","tcp","tcp","udp")?></TD>
 <TD><?input_select("i_portfw_interface___T","eth0","eth0","eth1")?></TD>
 <TD><?input_text("i_portfw_src_port___T","","SIZE=5")?></TD>
 <TD><?input_text("i_portfw_dst_ip___T","")?></TD>
 <TD><?input_text("i_portfw_dst_port___T","","SIZE=5")?></TD>
 <TD><INPUT TYPE=SUBMIT NAME=s_ok VALUE="追加"></TD>
</TR>
</TABLE>
</FORM>

<FORM <?def_formarg()?>>
<?input_hidden("typ","fw")?>
<?input_hidden("op","$op")?>
<?input_hidden("subop","$subop")?>
<?input_hidden("i_login","$x_login")?>
<?input_hidden("i_key","$x_key")?>

<P>
<?head("簡易ファイヤウォール")?>
<P>
<TABLE BORDER=0 CELLPADDING=6 CELLSPACING=2>
<TR>
 <TD>&nbsp;</TD>
 <TD>&nbsp;</TD>
 <TD BGCOLOR="#eeeeee" COLSPAN=3>src</TD>
 <TD BGCOLOR="#eeeeee" COLSPAN=3>dst</TD>
 <TD>&nbsp;</TD>
</TR>
<TR>
 <TD BGCOLOR="#dddddd">#</TD>
 <TD BGCOLOR="#dddddd">proto</TD>
 <TD BGCOLOR="#dddddd">IP</TD>
 <TD BGCOLOR="#dddddd">mask</TD>
 <TD BGCOLOR="#dddddd">port</TD>
 <TD BGCOLOR="#dddddd">IP</TD>
 <TD BGCOLOR="#dddddd">mask</TD>
 <TD BGCOLOR="#dddddd">port</TD>
 <TD BGCOLOR="#dddddd">&nbsp;</TD>
 <TD>&nbsp;</TD>
</TR>
<?trlist("x_fw__","x_fw__%s")?>
</TABLE>
<?head2("追加")?>
<TABLE>
<TR>
 <TD>&nbsp;</TD>
 <TD>&nbsp;</TD>
 <TD BGCOLOR="#eeeeee" COLSPAN=3>src</TD>
 <TD BGCOLOR="#eeeeee" COLSPAN=3>dst</TD>
 <TD>&nbsp;</TD>
</TR>
<TR>
 <TD BGCOLOR="#dddddd">#</TD>
 <TD BGCOLOR="#dddddd">proto</TD>
 <TD BGCOLOR="#dddddd">IP</TD>
 <TD BGCOLOR="#dddddd">mask</TD>
 <TD BGCOLOR="#dddddd">port</TD>
 <TD BGCOLOR="#dddddd">IP</TD>
 <TD BGCOLOR="#dddddd">mask</TD>
 <TD BGCOLOR="#dddddd">port</TD>
 <TD BGCOLOR="#dddddd">&nbsp;</TD>
 <TD>&nbsp;</TD>
</TR>
<TR>

 <TD><?input_text("i_fw_id",nextval(eval("x_fw__")),"SIZE=3")?></TD>
 <TD><?input_select("i_fw_proto___T","tcp","all","tcp","udp")?></TD>
 <TD><?input_text("i_fw_src_ip___T","ANY")?></TD>
 <TD><?input_netmask("i_fw_src_subnet_mask___T","255.255.255.0")?></TD>
 <TD><?input_text("i_fw_src_port___T","ANY","SIZE=5")?></TD>
 <TD><?input_text("i_fw_dst_ip___T","ANY")?></TD>
 <TD><?input_netmask("i_fw_dst_subnet_mask___T","255.255.255.0")?></TD>
 <TD><?input_text("i_fw_dst_port___T","ANY","SIZE=5")?></TD>
 <TD><?input_select("i_fw_action___T","ANY","ACCEPT","DROP")?></TD>
 <TD><INPUT TYPE=SUBMIT NAME=s_ok2 VALUE="追加"></TD>
</TR>
</TABLE>
<P>
</FORM>
<!-- $Id: fw.t,v 1.2 2003/04/25 07:40:19 kanoh Exp $ -->
