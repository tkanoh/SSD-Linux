<FORM <?def_formarg()?>>
<?input_hidden("typ","system")?>
<?input_hidden("op","$op")?>
<?input_hidden("i_login","$x_login")?>
<?input_hidden("i_key","$x_key")?>
<?head("�ۥ��Ⱦ���")?>
<P>
<TABLE>
<TR>
 <TD>&nbsp;</TD>
 <TD><B>�ۥ���̾:</B></TD>
 <TD><?input_text("i_hostname","$x_hostname","SIZE=40")?></TD>
</TR>
<TR>
 <TD>&nbsp;</TD>
 <TD><B>�ɥᥤ��̾:</B></TD>
 <TD><?input_text("i_domainname","$x_domainname","SIZE=40")?></TD>
</TR>
</TABLE>
<P>
<INPUT TYPE=SUBMIT NAME=s_ok VALUE="�ѹ�">
<P>
</FORM>

<FORM NAME="i_timer" <?def_formarg()?>>
<?input_hidden("typ","system")?>
<?input_hidden("op","$op")?>
<?input_hidden("i_login","$x_login")?>
<?input_hidden("i_key","$x_key")?>
<?head("���ա�����")?>
<P>
<TABLE>
<TR>
 <TD>&nbsp;</TD>
 <TD>
    <?input_text("i_year","$x_year","SIZE=4")?>ǯ
    <?input_text("i_mon","$x_mon","SIZE=2")?>��
    <?input_text("i_mday","$x_mday","SIZE=2")?>��
 </TD>
</TR>
<TR>
 <TD>&nbsp;</TD>
 <TD>
    <?input_text("i_hour","$x_hour","SIZE=2")?>��
    <?input_text("i_min","$x_min","SIZE=2")?>ʬ
    <?input_hidden("00","$x_sec")?>
 </TD>
</TR>
</TABLE>
<P>
<INPUT TYPE=SUBMIT NAME=s_ok2 VALUE="�ѹ�">
<P>
</FORM>

<FORM NAME="i_timer" <?def_formarg()?>>
<?input_hidden("typ","system")?>
<?input_hidden("op","$op")?>
<?input_hidden("i_login","$x_login")?>
<?input_hidden("i_key","$x_key")?>
<?head("����Ʊ��")?>
<P>
<TABLE>
<TR>
 <TD>&nbsp;</TD>
 <TD><B>�ΣԣХ�����:</B></TD>
 <TD><?input_text("i_ntp_hostname","$x_ntp_hostname")?></TD>
</TR>
</TABLE>
<P>
<INPUT TYPE=SUBMIT NAME=s_ok3 VALUE="�ѹ�">
<P>
</FORM>
<!-- $Id: system.t,v 1.10 2004/11/26 09:57:24 todoroki Exp $ -->
