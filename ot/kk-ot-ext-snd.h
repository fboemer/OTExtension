/*
 * kk-ot-ext-sender.h
 *
 *  Created on: Aug 20, 2015
 *      Author: mzohner
 */

#ifndef KK_OT_EXT_SENDER_H_
#define KK_OT_EXT_SENDER_H_

#include "ot-ext-snd.h"
#include "kk-ot-ext.h"

class KKOTExtSnd : public OTExtSnd, public KKOTExt {

public:
	KKOTExtSnd(crypto* crypt, RcvThread* rcvthread, SndThread* sndthread, uint64_t num_ot_blocks=4096, bool verify_ot=true, bool use_fixed_key_aes_hashing=false)
		: OTExtSnd(num_ot_blocks, verify_ot, use_fixed_key_aes_hashing) {
		uint32_t numbaseots = 2*crypt->get_seclvl().symbits;

		//assert(pad_to_power_of_two(nSndVals) == nSndVals); //TODO right now only supports power of two nSndVals
		assert(numbaseots == 256); //TODO: right now only 256 base OTs work due to the size of the code
		InitSnd(crypt, rcvthread, sndthread, 2*crypt->get_seclvl().symbits);
		//Initialize the code words
		InitAndReadCodeWord(&m_vCodeWords);
	}
	;


	virtual ~KKOTExtSnd() {
	}
	;

	BOOL sender_routine(uint32_t threadid, uint64_t numOTs);
	void ComputeBaseOTs(field_type ftype);

private:
	void KKHashValues(CBitVector& Q, CBitVector* seedbuf, CBitVector* snd_buf, uint64_t OT_ptr, uint64_t OT_len, uint64_t** mat_mul);
	void KKMaskAndSend(CBitVector* snd_buf, uint64_t OT_ptr, uint64_t OT_len, channel* chan);
	//uint64_t** m_vCodeWords;
};



#endif /* KK_OT_EXT_SENDER_H_ */
