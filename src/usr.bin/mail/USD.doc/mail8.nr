.\"	$ssdlinux: mail8.nr,v 1.1.1.1 2002/05/02 13:37:11 kanoh Exp $
.\"	$NetBSD: mail8.nr,v 1.4 1998/01/09 08:06:00 perry Exp $
.\"
.\" Copyright (c) 1980, 1993
.\"	The Regents of the University of California.  All rights reserved.
.\"
.\" Redistribution and use in source and binary forms, with or without
.\" modification, are permitted provided that the following conditions
.\" are met:
.\" 1. Redistributions of source code must retain the above copyright
.\"    notice, this list of conditions and the following disclaimer.
.\" 2. Redistributions in binary form must reproduce the above copyright
.\"    notice, this list of conditions and the following disclaimer in the
.\"    documentation and/or other materials provided with the distribution.
.\" 3. All advertising materials mentioning features or use of this software
.\"    must display the following acknowledgement:
.\"	This product includes software developed by the University of
.\"	California, Berkeley and its contributors.
.\" 4. Neither the name of the University nor the names of its contributors
.\"    may be used to endorse or promote products derived from this software
.\"    without specific prior written permission.
.\"
.\" THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
.\" ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
.\" IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
.\" ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
.\" FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
.\" DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
.\" OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
.\" HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
.\" LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
.\" OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
.\" SUCH DAMAGE.
.\"
.\"	@(#)mail8.nr	8.2 (Berkeley) 5/16/94
.\"
.sh 1 "Glossary"
.pp
This section contains the definitions of a few phrases
peculiar to
.i Mail .
.ip "\fIalias\fP"
An alternative name for a person or list of people.
.ip "\fIflag\fP"
An option, given on the command line of
.i Mail ,
prefaced with a \-.  For example,
.b \-f
is a flag.
.ip "\fIheader field\fP"
At the beginning of a message, a line which contains information
that is part of the structure of the message.  Popular header fields
include
.i to ,
.i cc ,
and
.i subject .
.ip "\fImail\ \ \fP"
A collection of messages.  Often used in the phrase,
.q "Have you read your mail?"
.ip "\fImailbox\fP"
The place where your mail is stored, typically in the directory
/var/mail.
.ip "\fImessage\fP"
A single letter from someone, initially stored in your
.i mailbox .
.ip "\fImessage list\fP"
A string used in
.i Mail
command mode to describe a sequence of messages.
.ip "\fIoption\fP"
A piece of special purpose information used to tailor
.i Mail
to your taste.
Options are specified with the
.b set
command.
