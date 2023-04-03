<FORM <?def_formarg()?>>
<?input_hidden("typ","system")?>
<?input_hidden("op","$op")?>
<?input_hidden("i_login","$x_login")?>
<?input_hidden("i_key","$x_key")?>
<?head("ホスト情報")?>
<P>
<TABLE>
<TR>
 <TD>&nbsp;</TD>
 <TD><B>ホスト名:</B></TD>
 <TD><?input_text("i_hostname","$x_hostname","SIZE=40")?></TD>
</TR>
<TR>
 <TD>&nbsp;</TD>
 <TD><B>ドメイン名:</B></TD>
 <TD><?input_text("i_domainname","$x_domainname","SIZE=40")?></TD>
</TR>
</TABLE>
<P>
<INPUT TYPE=SUBMIT NAME=s_ok VALUE="変更">
<P>
</FORM>

<FORM NAME="i_timer" <?def_formarg()?>>
<?input_hidden("typ","system")?>
<?input_hidden("op","$op")?>
<?input_hidden("i_login","$x_login")?>
<?input_hidden("i_key","$x_key")?>
<?head("日付・時刻")?>
<P>
<TABLE>
<TR>
 <TD>&nbsp;</TD>
 <TD>
    <?input_text("i_year","$x_year","SIZE=4")?>年
    <?input_text("i_mon","$x_mon","SIZE=2")?>月
    <?input_text("i_mday","$x_mday","SIZE=2")?>日
 </TD>
</TR>
<TR>
 <TD>&nbsp;</TD>
 <TD>
    <?input_text("i_hour","$x_hour","SIZE=2")?>時
    <?input_text("i_min","$x_min","SIZE=2")?>分
    <?input_hidden("00","$x_sec")?>
 </TD>
</TR>
</TABLE>
<P>
<INPUT TYPE=SUBMIT NAME=s_ok2 VALUE="変更">
<P>
</FORM>

<FORM NAME="i_timer" <?def_formarg()?>>
<?input_hidden("typ","system")?>
<?input_hidden("op","$op")?>
<?input_hidden("i_login","$x_login")?>
<?input_hidden("i_key","$x_key")?>
<?head("時刻同期")?>
<P>
<TABLE>
<TR>
 <TD>&nbsp;</TD>
 <TD><B>ＮＴＰサーバ:</B></TD>
 <TD><?input_text("i_ntp_hostname","$x_ntp_hostname")?></TD>
</TR>
</TABLE>
<P>
<INPUT TYPE=SUBMIT NAME=s_ok3 VALUE="変更">
<P>
</FORM>
<!-- $Id: system.t,v 1.10 2004/11/26 09:57:24 todoroki Exp $ -->
