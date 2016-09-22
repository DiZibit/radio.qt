#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QObject>
#include <QBuffer>
#include <QMediaPlayer>

#include "audiodownloader.h"

class AudioPlayer : public QObject
{
    Q_OBJECT
public:
    explicit AudioPlayer(QString deviceID, QObject *parent = 0);

    void playNext();
    QMediaPlayer& getMediaPlayer() const;

private slots:
    void play();
    void playStatusChanged();

private:
    QBuffer m_Buffer;
    QMediaPlayer *m_Player;
    AudioDownloader *m_Downloader;
};

#endif // AUDIOPLAYER_H
