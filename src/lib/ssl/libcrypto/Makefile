#	$ssdlinux: Makefile,v 1.12 2004/10/28 02:34:13 yamagata Exp $

.include <bsd.own.mk>

LIB=		crypto
SSLVERSION=	0.9.7e
MKPIC=		yes
MKPICINSTALL=	no

.include "${.CURDIR}/../Makefile.cflags"

#NO_IDEA=	yes
#NO_RC2=	yes
#NO_RC4=	yes

INCS=		e_os2.h
INCS+=		md4.h
INCS+=		crypto.h ebcdic.h opensslconf.h opensslv.h ossl_typ.h \
		symhacks.h tmdiff.h
INCS+=		md2.h md5.h sha.h mdc2.h hmac.h ripemd.h des.h des_old.h
.if !defined(NO_RC2)
INCS+=		rc2.h
.endif
.if !defined(NO_RC_4)
INCS+=		rc4.h
.endif
INCS+=		rc5.h
.if !defined(NO_IDEA)
INCS+=		idea.h
.endif
INCS+=		blowfish.h cast.h bn.h ec.h rsa.h dsa.h dh.h dso.h engine.h \
		aes.h buffer.h bio.h stack.h safestack.h lhash.h rand.h err.h \
		objects.h obj_mac.h evp.h asn1.h asn1_mac.h asn1t.h \
		pem.h pem2.h x509.h x509_vfy.h x509v3.h conf.h conf_api.h \
		txt_db.h pkcs7.h pkcs12.h comp.h ocsp.h ui.h ui_compat.h \
		krb5_asn.h

INCSDIR=	/usr/include/openssl

DIST=		${.CURDIR}/../../../dist/openssl
CDIST=		${DIST}/crypto

SDIST=		${CDIST}
SDIST+=		${CDIST}/md2
SDIST+=		${CDIST}/md4
SDIST+=		${CDIST}/md5
SDIST+=		${CDIST}/sha
SDIST+=		${CDIST}/mdc2
SDIST+=		${CDIST}/hmac
SDIST+=		${CDIST}/ripemd
SDIST+=		${CDIST}/des
.if !defined(NO_RC2)
SDIST+=		${CDIST}/rc2
.endif
.if !defined(NO_RC_4)
SDIST+=		${CDIST}/rc4
.endif
SDIST+=		${CDIST}/rc5
.if !defined(NO_IDEA)
SDIST+=		${CDIST}/idea
.endif
SDIST+=		${CDIST}/bf
SDIST+=		${CDIST}/cast
SDIST+=		${CDIST}/bn
SDIST+=		${CDIST}/ec
SDIST+=		${CDIST}/rsa
SDIST+=		${CDIST}/dsa
SDIST+=		${CDIST}/dh
SDIST+=		${CDIST}/dso
SDIST+=		${CDIST}/engine
SDIST+=		${CDIST}/aes
SDIST+=		${CDIST}/buffer
SDIST+=		${CDIST}/bio
SDIST+=		${CDIST}/stack
SDIST+=		${CDIST}/lhash
SDIST+=		${CDIST}/rand
SDIST+=		${CDIST}/err
SDIST+=		${CDIST}/objects
SDIST+=		${CDIST}/evp
SDIST+=		${CDIST}/asn1
SDIST+=		${CDIST}/pem
SDIST+=		${CDIST}/x509
SDIST+=		${CDIST}/x509v3
SDIST+=		${CDIST}/conf
SDIST+=		${CDIST}/txt_db
SDIST+=		${CDIST}/pkcs7
SDIST+=		${CDIST}/pkcs12
SDIST+=		${CDIST}/comp
SDIST+=		${CDIST}/ocsp
SDIST+=		${CDIST}/ui
SDIST+=		${CDIST}/krb5
SDIST+=		${DIST}/include/openssl

.PATH:		${SDIST}

CPPFLAGS+=	-I${.CURDIR} -I${CDIST} -I${DIST} -I${DIST}/include

SRCS=		buildinf.h
SRCS+=		cryptlib.c mem.c mem_clr.c mem_dbg.c cversion.c ex_data.c tmdiff.c cpt_err.c ebcdic.c uid.c o_time.c o_str.c
# md2
SRCS+=		md2_dgst.c md2_one.c
# md4
SRCS+=		md4_dgst.c md4_one.c
# md5
SRCS+=		md5_dgst.c md5_one.c
# sha
SRCS+=		sha_dgst.c sha1dgst.c sha_one.c sha1_one.c
# mdc2
SRCS+=		mdc2dgst.c mdc2_one.c
# hmac
SRCS+=		hmac.c
# ripemd
SRCS+=		rmd_dgst.c rmd_one.c
# des
SRCS+=		cbc_cksm.c cbc_enc.c cfb64enc.c cfb_enc.c \
		ecb3_enc.c ecb_enc.c enc_read.c enc_writ.c \
		fcrypt.c ofb64enc.c ofb_enc.c pcbc_enc.c \
		qud_cksm.c rand_key.c rpc_enc.c set_key.c  \
		des_enc.c fcrypt_b.c \
		xcbc_enc.c \
		str2key.c  cfb64ede.c ofb64ede.c ede_cbcm_enc.c des_old.c des_old2.c \
		read2pwd.c
# rc2
.if !defined(NO_RC2)
SRCS+=		rc2_ecb.c rc2_skey.c rc2_cbc.c rc2cfb64.c rc2ofb64.c
.endif
# rc4
.if !defined(NO_RC4)
SRCS+=		rc4_skey.c rc4_enc.c
.endif
# rc5
SRCS+=		rc5_skey.c rc5_ecb.c rc5_enc.c rc5cfb64.c rc5ofb64.c
# idea
.if !defined(NO_IDEA)
SRCS+=		i_cbc.c i_cfb64.c i_ofb64.c i_ecb.c i_skey.c
.endif
# bf
SRCS+=		bf_skey.c bf_ecb.c bf_enc.c bf_cfb64.c bf_ofb64.c
# cast
SRCS+=		c_skey.c c_ecb.c c_enc.c c_cfb64.c c_ofb64.c
# bn
SRCS+=		bn_add.c bn_div.c bn_exp.c bn_lib.c bn_ctx.c bn_mul.c bn_mod.c \
		bn_print.c bn_rand.c bn_shift.c bn_word.c bn_blind.c \
		bn_kron.c bn_sqrt.c bn_gcd.c bn_prime.c bn_err.c bn_sqr.c bn_asm.c \
		bn_recp.c bn_mont.c bn_mpi.c bn_exp2.c
# ec
SRCS+=		ec_lib.c ecp_smpl.c ecp_mont.c ecp_recp.c ecp_nist.c ec_cvt.c ec_mult.c \
		ec_err.c
# rsa
SRCS+=		rsa_eay.c rsa_gen.c rsa_lib.c rsa_sign.c rsa_saos.c rsa_err.c \
		rsa_pk1.c rsa_ssl.c rsa_none.c rsa_oaep.c rsa_chk.c rsa_null.c \
		rsa_asn1.c
# dsa
SRCS+=		dsa_gen.c dsa_key.c dsa_lib.c dsa_asn1.c dsa_vrf.c dsa_sign.c \
		dsa_err.c dsa_ossl.c
# dh
SRCS+=		dh_asn1.c dh_gen.c dh_key.c dh_lib.c dh_check.c dh_err.c
# dso
SRCS+=		dso_dl.c dso_dlfcn.c dso_err.c dso_lib.c dso_null.c \
		dso_openssl.c dso_win32.c dso_vms.c
# engine
SRCS+=		eng_err.c eng_lib.c eng_list.c eng_init.c eng_ctrl.c \
		eng_table.c eng_pkey.c eng_fat.c eng_all.c \
		tb_rsa.c tb_dsa.c tb_dh.c tb_rand.c tb_cipher.c tb_digest.c \
		eng_openssl.c eng_dyn.c eng_cnf.c \
		hw_atalla.c hw_cswift.c hw_ncipher.c hw_nuron.c hw_ubsec.c \
		hw_cryptodev.c hw_aep.c hw_sureware.c hw_4758_cca.c
# aes
SRCS+=		aes_core.c aes_misc.c aes_ecb.c aes_cbc.c aes_cfb.c aes_ofb.c aes_ctr.c
# buffer
SRCS+=		buffer.c buf_err.c
# bio
SRCS+=		bio_lib.c bio_cb.c bio_err.c \
		bss_mem.c bss_null.c bss_fd.c \
		bss_file.c bss_sock.c bss_conn.c \
		bf_null.c bf_buff.c b_print.c b_dump.c \
		b_sock.c bss_acpt.c bf_nbio.c bss_log.c bss_bio.c
# stack
SRCS+=		stack.c
# lhash
SRCS+=		lhash.c	lh_stats.c
# rand
SRCS+=		md_rand.c randfile.c rand_lib.c rand_err.c rand_egd.c \
		rand_win.c rand_unix.c rand_os2.c
# err
SRCS+=		err.c err_all.c err_prn.c
# objects
SRCS+=		o_names.c obj_dat.c obj_lib.c obj_err.c
# evp
SRCS+=		encode.c digest.c evp_enc.c evp_key.c evp_acnf.c \
		e_des.c e_bf.c e_idea.c e_des3.c \
		e_rc4.c e_aes.c names.c \
		e_xcbc_d.c e_rc2.c e_cast.c e_rc5.c \
		m_null.c m_md2.c m_md4.c m_md5.c m_sha.c m_sha1.c \
		m_dss.c m_dss1.c m_mdc2.c m_ripemd.c \
		p_open.c p_seal.c p_sign.c p_verify.c p_lib.c p_enc.c p_dec.c \
		bio_md.c bio_b64.c bio_enc.c evp_err.c e_null.c \
		c_all.c c_allc.c c_alld.c evp_lib.c bio_ok.c \
		evp_pkey.c evp_pbe.c p5_crpt.c p5_crpt2.c
# asn1
SRCS+=		a_object.c a_bitstr.c a_utctm.c a_gentm.c a_time.c a_int.c a_octet.c \
		a_print.c a_type.c a_set.c a_dup.c a_d2i_fp.c a_i2d_fp.c \
		a_enum.c a_utf8.c a_sign.c a_digest.c a_verify.c a_mbstr.c a_strex.c \
		x_algor.c x_val.c x_pubkey.c x_sig.c x_req.c x_attrib.c x_bignum.c \
		x_long.c x_name.c x_x509.c x_x509a.c x_crl.c x_info.c x_spki.c nsseq.c \
		d2i_pu.c d2i_pr.c i2d_pu.c i2d_pr.c \
		t_req.c t_x509.c t_x509a.c t_crl.c t_pkey.c t_spki.c t_bitst.c \
		tasn_new.c tasn_fre.c tasn_enc.c tasn_dec.c tasn_utl.c tasn_typ.c \
		f_int.c f_string.c n_pkey.c \
		f_enum.c a_hdr.c x_pkey.c a_bool.c x_exten.c \
		asn1_par.c asn1_lib.c asn1_err.c a_meth.c a_bytes.c a_strnid.c \
		evp_asn1.c asn_pack.c p5_pbe.c p5_pbev2.c p8_pkey.c asn_moid.c
# pem
SRCS+=		pem_sign.c pem_seal.c pem_info.c pem_lib.c pem_all.c pem_err.c \
		pem_x509.c pem_xaux.c pem_oth.c pem_pk8.c pem_pkey.c
# x509
SRCS+=		x509_def.c x509_d2.c x509_r2x.c x509_cmp.c \
		x509_obj.c x509_req.c x509spki.c x509_vfy.c \
		x509_set.c x509cset.c x509rset.c x509_err.c \
		x509name.c x509_v3.c x509_ext.c x509_att.c \
		x509type.c x509_lu.c x_all.c x509_txt.c \
		x509_trs.c by_file.c by_dir.c
# x509v3
SRCS+=		v3_bcons.c v3_bitst.c v3_conf.c v3_extku.c v3_ia5.c v3_lib.c \
		v3_prn.c v3_utl.c v3err.c v3_genn.c v3_alt.c v3_skey.c v3_akey.c v3_pku.c \
		v3_int.c v3_enum.c v3_sxnet.c v3_cpols.c v3_crld.c v3_purp.c v3_info.c \
		v3_ocsp.c v3_akeya.c
# conf
SRCS+=		conf_err.c conf_lib.c conf_api.c conf_def.c  conf_mod.c \
		conf_mall.c conf_sap.c
# txt_db
SRCS+=		txt_db.c
# pkcs7
SRCS+=		pk7_asn1.c pk7_lib.c pkcs7err.c pk7_doit.c pk7_smime.c pk7_attr.c \
		pk7_mime.c
# pkcs12
SRCS+=		p12_add.c p12_asn.c p12_attr.c p12_crpt.c p12_crt.c p12_decr.c \
		p12_init.c p12_key.c p12_kiss.c p12_mutl.c \
		p12_utl.c p12_npas.c pk12err.c p12_p8d.c p12_p8e.c
# comp
SRCS+=		comp_lib.c comp_err.c \
		c_rle.c c_zlib.c
# ocsp
SRCS+=		ocsp_asn.c ocsp_ext.c ocsp_ht.c ocsp_lib.c ocsp_cl.c \
		ocsp_srv.c ocsp_prn.c ocsp_vfy.c ocsp_err.c
# ui
SRCS+=		ui_err.c ui_lib.c ui_openssl.c ui_util.c ui_compat.c
# krb5
SRCS+=		krb5_asn.c

CLEANFILES=	buildinf.h

buildinf.h:
	(echo "#ifndef MK1MF_BUILD"; \
	 echo "  /* auto-generated by crypto/Makefile.ssl for crypto/cversion.c */"; \
	 echo "  #define CFLAGS \"cc -O\""; \
	 echo "  #define PLATFORM \"dist\""; \
	 echo "  #define DATE \"`date`\""; \
	 echo "#endif") >${.TARGET}

maninstall:
	@for i in ${DIST}/doc/crypto/*.pod; do \
		fn=`basename $$i .pod`; \
		if [ "$$fn" = "des_modes" ]; then sec=7; else sec=3; fi; \
		echo "installing man$$sec/`basename $$i .pod`.$$sec"; \
		(cd `dirname $$i`; \
		 perl ${DIST}/util/pod2man.pl --section=$$sec --center=OpenSSL \
			--release=${SSLVERSION} `basename $$i`) \
		 > ${DESTDIR}${MANDIR}/man$$sec/`basename $$i .pod`.$$sec; \
	done

.include <bsd.lib.mk>
