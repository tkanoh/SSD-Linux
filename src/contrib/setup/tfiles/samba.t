<?head("samba����")?>
<FORM <?def_formarg()?>>
<?input_hidden("typ","samba")?>
<?input_hidden("op","$op")?>
<?input_hidden("subop","$subop")?>
<?input_hidden("i_login","$x_login")?>
<?input_hidden("i_key","$x_key")?>
<TABLE>
<TR>
 <TD><?input_checkbox("i_samba_enable","$x_samba_enable")?></TD>
 <TD COLSPAN=2>samba��ư���˵�ư����</TD>
</TR>
<TR>
<TD>&nbsp;</TD>
<TD>������롼��̾:</TD><TD><?input_text("i_samba_workgroup","$x_samba_workgroup","SIZE=40")?></TD>
</TR>
<TR>
 <TD><?input_checkbox("i_samba_nmbd_enable","$x_samba_nmbd_enable")?></TD>
 <TD COLSPAN=2>nmbd��ư���˵�ư����</TD>
</TR>
<TR>
 <TD><?input_checkbox("i_netatalk_enable","$x_netatalk_enable")?></TD>
 <TD COLSPAN=2>netatalk��ư���˵�ư����</TD>
</TR>
</TABLE>
<P>
<INPUT TYPE=SUBMIT NAME=s_ok VALUE="����">
</FORM>
<!-- $Id: samba.t,v 1.2 2003/03/11 07:55:08 yamagata Exp $ -->
