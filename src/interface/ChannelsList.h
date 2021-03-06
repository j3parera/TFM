#ifndef CHANNELSLIST_H
#define CHANNELSLIST_H

// System libraries
#include "stdlib.h"
#include "vector"
#include "cmath"
// Qt libraries
#include "QDialog"
#include "QObject"
#include "QWidget"
#include "QLayout"
#include "QGroupBox"
#include "QLabel"
#include "QLineEdit"
#include "QCheckBox"
// Classes and local files
#include "AudioOutput.h"
#include "Chart2D.h"
#include "../process/AudioSignal.h"
#include "../tools/Logger.h"

namespace Ui {
class ChannelsPlot;
}

/**
 * @class   Channel
 * @author  Andrés González Fornell
 * @brief   Single-object class from channels list.
 */
class Channel {
public:
	int index; /**< channel index */
	std::string name; /**< channel name */
	double volume; /**< current audio volume level */
	bool muted; /**< it indicates if channel is muted */
	bool bypassed; /**< it tells channel to bypass effects or apply them */
	AudioOutput *audiooutput; /**< system audio output devices object */
	/**
	 * @brief   user interface elements
	 * @{
	 */
	QGroupBox *groupbox; /**< channel group box */
	QLineEdit *label; /**< field to change the channel label */
	QSlider *volumeslider; /**< volume level slider */
	QCheckBox *mutecheckbox; /**< muted checkbox object */
	QCheckBox *bypasscheckbox; /**< checkbox object to bypass effect */
	QComboBox *deviceselector; /**< audio output device selector object */
	/** @} */
	Channel(QLayout *framework, std::string prefix, int index, bool isoutput);
	~Channel();
	int getIndex();
	void setIndex(int index);
	void setLabel(std::string label);
    void setVolume(int volume);
	void mute(bool state);
	void bypass(bool state);
private:
	std::string prefix; /**< user interface prefix */
	bool isoutput; /**< true to show audio output device selector (in case of sending channel to speakers or other audio output system device) */
};

/**
 * @class   ChannelsList
 * @author  Andrés González Fornell
 * @brief   Channels list class. It shows information about channels signals.
 */
class ChannelsList: public QObject {
	Q_OBJECT
public:
    static int fs; /**< signal sampling frequency */
    static int samplesize; /**< signal sample size */
    ChannelsList(QWidget *framework, int number, bool showdevices);
	~ChannelsList();
	Channel *getChannel(int index);
	void deleteChannel(int index);
	int getSize();
	void setSize(int size);
	std::vector<std::string> getNames();
private:
	std::vector<Channel *> channels; /**< list of channels */
	std::string prefix; /**< user interface prefix */
	bool showdevices; /**< true to show audio output device selector (in case of sending channels to speakers or other audio output system devices) */
	QWidget *framework; /**< user interface framework of channels list */
	QLayout *layout; /**< user interface layout of channels list */
    int getIndex(QObject *element);
private slots:
	void setLabel(QString label);
    void setLabel(QString label, int index);
	void setVolume(int volume);
	void mute(bool state);
	void bypass(bool state);
    void setDevice(int device);
signals:
    void namechanged(QString, int);
};

namespace Ui {
class ChannelsCharts;
}

class ChannelsCharts : public QDialog {
    Q_OBJECT
public:
    ChannelsCharts(float **input, float **output, ChannelsList *input_channels, ChannelsList *output_channels, int samples, QWidget *parent = 0);
    ~ChannelsCharts();
private:
    Ui::ChannelsCharts *ui; /**< user interface object */
    float **input; /**< input signal pointer */
    float **output; /**< output signal pointer */
    ChannelsList *input_channels; /**< input channels object */
    ChannelsList *output_channels; /**< output channels object */
    int samples; /**< number of samples each channel */
    Chart2D *input_chart; /**< input chart object */
    Chart2D *output_chart; /**< output chart object */
    void updateSelectors();
private slots:
    void setTimeCursor(int sample);
    int getTimeCursor();
    void setScope(int time);
    int getScope();
    void plot();
};

#endif // CHANNELSLIST_H
