#ifndef SAC_DECODER_H
#define SAC_DECODER_H

char *sac_decode(const char *input_filename, const char *output_filename,
		const char *bitstream_filename, double fs, int upmixtype,
		int decodingtype, int binauralquality, int hrtfmodel, int debuggermode);
void myexit(char *s);

#endif // SAC_DECODER_H
