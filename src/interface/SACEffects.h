#ifndef SACEFFECTS_H
#define SACEFFECTS_H

// C libraries
#include "iostream"
#include "stdlib.h"
#include "map"
// Qt libraries
#include "QApplication"
#include "QMainWindow"
#include "QTimer"
// Classes and local files
#include "Encoder.h"
#include "ChannelsList.h"
#include "EffectsMonitor.h"
#include "AudioOutput.h"
#include "AudioInfo.h"
#include "Chart2D.h"
#include "../process/ProcessManager.h"
#include "../process/File.h"
#include "../tools/Logger.h"

/**
 * @brief   SAC decoder parameter upmix type
 */
struct UpmixType {
	enum upmixtype {
        normal = 0, /**< normal upmix */
        blind = 1, /**< blind upmix */
        binaural = 2, /**< binaural upmix */
        stereo = 3 /**< stereo upmix */
	};
};
/**
 * @brief   SAC decoder parameter decoding type
 */
struct DecodingType {
	enum decodingtype {
        low = 0, /**< low complexity decoding mode */
        high = 1 /**< high complexity decoding mode */
	};
};
/**
 * @brief   SAC decoder parameter binaural quality
 */
struct BinauralQuality {
	enum binauralquality {
        parametric = 0, /** parametric binaural quality */
        filtering = 1 /**< filtering binaural quality */
	};
};
/**
 * @brief   SAC decoder parameter HRTF model
 */
struct HRTFModel {
	enum hrtfmodel {
        kemar = 0, /**< kemar head related transfer funcion model */
        vast = 1, /**< vast head related transfer funcion model */
        mps_vt = 2 /**< MPS VT head related transfer funcion model */
	};
};

/**
 * @namespace   Ui
 * @brief   Qt user interfaces namespace (see http://doc.qt.io/qt-5/topics-ui.html).
 */
namespace Ui {
class SACEffects;
}

/**
 * @class	SACEffects
 * @author	Andrés González Fornell
 * @brief	SACEffects window interface.
 */
class SACEffects: public QMainWindow {
	Q_OBJECT
public:
	const int fs = 44100; /**< signal sampling frequency [Hz] */
	explicit SACEffects(QWidget *framework = 0);
	~SACEffects();
	void play();
	void pause();
    void reset();
	void updateControls();
    void setEffect(Effect::effectID effect);
	void setSource(std::string filename);
	void setBitstream(std::string filename);
	void setInput(std::string filename);
    void setFormat(int fs, int samplesize);
	void setDuration(QLabel *label, double duration);
	void getDuration(QLabel label);
	void setUpmixType(UpmixType::upmixtype upmixtype);
	void setDecodingType(DecodingType::decodingtype decodingtype);
	void setBinauralQuality(BinauralQuality::binauralquality binauralquality);
	void setHRTFModel(HRTFModel::hrtfmodel hrtfmodel);
private:
	ProcessManager *process; /**< process manager object */
	QTimer *clock; /**< application clock to call effect in proccess periodically*/
	Ui::SACEffects *ui; /**< user interface object */
	QStatusBar *status; /**< user interface status bar object */
	WAVFile *source; /**< encoded source file object */
	File *bitstream; /**< encoded bit stream file object */
	WAVFile *input; /**< decoded input file object */
    Effect *effect; /**< effect object */
	ChannelsList *channels_input; /**< input channels list */
    ChannelsList *channels_output; /**< output channels list */
	EffectsMonitor *effectsmonitor; /**< effects monitor object */
    int chunksize; /**< number of samples in a chunk */
	bool muted; /**< it indicates if output playback is muted (true) or not (false) */
	bool buried; /**< SAC decoder parameter */
	DecodingType::decodingtype decodingtype; /**< SAC decoder parameter */
	UpmixType::upmixtype upmixtype; /**< SAC decoder parameter */
	BinauralQuality::binauralquality binauralquality; /**< SAC decoder parameter */
	HRTFModel::hrtfmodel hrtfmodel; /**< SAC decoder parameter */
    void setTimer();
private slots:
    // Input & output
	void setPlayback(bool state);
	void stop();
	void openInfo();
	void setTimer(QTime time);
	void load();
	void exportOutput();
    void openChannelsCharts();
	void test();
	// SACEffects
	void encode();
	void decode();
	void setBuried(bool state);
	void toggleUpmixType(QAction *item);
	void toggleDecodingType(QAction *item);
	void toggleBinauralQuality(QAction *item);
	void toggleHRTFModel(QAction *item);
	// Effects
	void toggleEffect();
	void applyEffect();
    void sendOutput();
};

#endif // SACEFFECTS_H
