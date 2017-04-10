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



#ifndef SAC_HRTF_H
#define SAC_HRTF_H

#include "sac_dec.h"

extern const HRTF_DATA SpatialDecKemarHRTF;
extern const HRTF_DATA SpatialDecVastHRTF;
extern const HRTF_DATA SpatialDecMPSVTHRTF;
extern const HRTF_DATA SpatialDecTestHRTF;

void SpatialDecOpenHrtfFilterbank(HRTF_FILTERBANK **selfPtr,
                                  HRTF_DATA const *hrtfModel,
                                  float surroundGain,
                                  int qmfBands);

void SpatialDecCloseHrtfFilterbank(HRTF_FILTERBANK *self);

#ifdef HRTF_DYNAMIC_UPDATE
void SpatialDecReloadHrtfFilterbank(HRTF_FILTERBANK *self,
                                    SPATIAL_HRTF_DATA *hrtfData);
#endif 

void SpatialDecUpdateHrtfFilterbank(HRTF_FILTERBANK *self,
                                    float mReal[MAX_PARAMETER_BANDS][3][5],
                                    float mImag[MAX_PARAMETER_BANDS][3][5],
                                    float lf[MAX_PARAMETER_BANDS],
                                    float ls[MAX_PARAMETER_BANDS],
                                    float rf[MAX_PARAMETER_BANDS],
                                    float rs[MAX_PARAMETER_BANDS],
                                    float c1[MAX_PARAMETER_BANDS],
                                    float c2[MAX_PARAMETER_BANDS],
                                    float icc_c[MAX_PARAMETER_BANDS],
                                    int   aPredictionMode[MAX_PARAMETER_BANDS],
                                    int parametersSlot);


void SpatialDecApplyHrtfFilterbank(HRTF_FILTERBANK *self,
                                   float hybInputReal[][MAX_TIME_SLOTS][MAX_HYBRID_BANDS],
                                   float hybInputImag[][MAX_TIME_SLOTS][MAX_HYBRID_BANDS],
                                   float hybOutputReal[][MAX_TIME_SLOTS][MAX_HYBRID_BANDS],
                                   float hybOutputImag[][MAX_TIME_SLOTS][MAX_HYBRID_BANDS],
                                   int arbDmxResEnabled);

#endif 