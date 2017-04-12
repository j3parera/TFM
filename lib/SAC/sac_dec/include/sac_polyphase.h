/*******************************************************************************
This software module was originally developed by

Agere Systems, Coding Technologies, Fraunhofer IIS, Philips

and edited by

-

in the course of development of ISO/IEC 23003 for reference purposes and its
performance may not have been optimized. This software module is an
implementation of one or more tools as specified by ISO/IEC 23003. ISO/IEC gives
You a royalty-free, worldwide, non-exclusive, copyright license to copy,
distribute, and make derivative works of this software module or modifications
thereof for use in implementations of ISO/IEC 23003 in products that satisfy
conformance criteria (if any). Those intending to use this software module in
products are advised that its use may infringe existing patents. ISO/IEC have no
liability for use of this software module or modifications thereof. Copyright is
not released for products that do not conform to audiovisual and image-coding
related ITU Recommendations and/or ISO/IEC International Standards.

Agere Systems, Coding Technologies, Fraunhofer IIS, Philips retain full right to
modify and use the code for its (their) own purpose, assign or donate the code
to a third party and to inhibit third parties from using the code for products
that do not conform to MPEG-related ITU Recommendations and/or ISO/IEC
International Standards. This copyright notice must be included in all copies or
derivative works.

Copyright (c) ISO/IEC 2009.
*******************************************************************************/




#ifndef __SAC_POLY_H
#define __SAC_POLY_H

typedef struct SAC_POLYPHASE_SYN_FILTERBANK SAC_POLYPHASE_SYN_FILTERBANK;
typedef struct SAC_POLYPHASE_ANA_FILTERBANK SAC_POLYPHASE_ANA_FILTERBANK;

typedef struct _Twiddle
{
  double fi;
  double beta;
} Twiddle;

void
SacDecInitSynFilterbank(const Twiddle *twiddle,
                     int resolution);

void
SacDecOpenSynFilterbank(SAC_POLYPHASE_SYN_FILTERBANK **self);


void
SacDecCloseSynFilterbank(SAC_POLYPHASE_SYN_FILTERBANK *self);

void
SacDecCalculateSynFilterbank(SAC_POLYPHASE_SYN_FILTERBANK *self,
                          float * Sr,
                          float * Si,
                          double * timeSig);

void
SacDecInitAnaFilterbank(const Twiddle *twiddle,
                     int resolution);

void
SacDecOpenAnaFilterbank(SAC_POLYPHASE_ANA_FILTERBANK **self);

void
SacDecCloseAnaFilterbank(SAC_POLYPHASE_ANA_FILTERBANK *self);

void
SacDecCalculateAnaFilterbank(SAC_POLYPHASE_ANA_FILTERBANK *self,
                          float * timeSig,
                          float * Sr,
                          float * Si);

void
SacDecGetFilterbankPrototype(int resolution,
                          float * prototype);

#endif
