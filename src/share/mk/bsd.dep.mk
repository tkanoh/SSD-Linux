#	$ssdlinux: bsd.dep.mk,v 1.1.1.1 2002/05/02 13:37:09 kanoh Exp $
#	$NetBSD: bsd.dep.mk,v 1.30 2000/01/22 19:31:00 mycroft Exp $

.PHONY:		cleandepend
cleandir: cleandepend

MKDEP?=		mkdep

# some of the rules involve .h sources, so remove them from mkdep line
realdepend: beforedepend
.if defined(SRCS)
realdepend: .depend
.NOPATH: .depend
.depend: ${SRCS} ${DPSRCS}
	@rm -f .depend
	@files="${.ALLSRC:M*.s} ${.ALLSRC:M*.S}"; \
	if [ "$$files" != " " ]; then \
	  echo ${MKDEP} -a ${MKDEPFLAGS} \
	    ${AFLAGS:M-[ID]*:Q} ${CPPFLAGS:Q} -traditional-cpp ${AINC:Q} \
	    $$files; \
	  ${MKDEP} -a ${MKDEPFLAGS} \
	    ${AFLAGS:M-[ID]*} ${CPPFLAGS} -traditional-cpp ${AINC} $$files; \
	fi
	@files="${.ALLSRC:M*.c}"; \
	if [ "$$files" != "" ]; then \
	  echo ${MKDEP} -a ${MKDEPFLAGS} \
	    ${CFLAGS:M-[ID]*:Q} ${CPPFLAGS:Q} $$files; \
	  ${MKDEP} -a ${MKDEPFLAGS} \
	    ${CFLAGS:M-[ID]*} ${CPPFLAGS} $$files; \
	fi
	@files="${.ALLSRC:M*.m}"; \
	if [ "$$files" != "" ]; then \
	  echo ${MKDEP} -a ${MKDEPFLAGS} \
	    ${OBJCFLAGS:M-[ID]*:Q} ${CPPFLAGS:Q} $$files; \
	  ${MKDEP} -a ${MKDEPFLAGS} \
	    ${OBJCFLAGS:M-[ID]*} ${CPPFLAGS} $$files; \
	fi
	@files="${.ALLSRC:M*.cc} ${.ALLSRC:M*.C} ${.ALLSRC:M*.cxx}"; \
	if [ "$$files" != "  " ]; then \
	  echo ${MKDEP} -a ${MKDEPFLAGS} \
	    ${CXXFLAGS:M-[ID]*:Q} ${CPPFLAGS:Q} $$files; \
	  ${MKDEP} -a ${MKDEPFLAGS} \
	    ${CXXFLAGS:M-[ID]*} ${CPPFLAGS} $$files; \
	fi
cleandepend:
	rm -f .depend ${.CURDIR}/tags ${CLEANDEPEND}
.else
cleandepend:
.endif
realdepend: afterdepend

beforedepend:
afterdepend:

.if !target(tags)
.if defined(SRCS)
tags: ${SRCS}
	-cd ${.CURDIR}; ctags -f /dev/stdout ${.ALLSRC:N*.h} | \
	    sed "s;\${.CURDIR}/;;" > tags
.else
tags:
.endif
.endif
