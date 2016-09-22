#include "audioplayer.h"

AudioPlayer::AudioPlayer(QString deviceID, QObject *parent) : QObject(parent)
{
    m_Downloader = new AudioDownloader(deviceID, this);
    m_Player = new QMediaPlayer(this, QMediaPlayer::StreamPlayback);

    connect(m_Downloader, SIGNAL(downloaded()), SLOT(play()));
    connect(m_Player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), SLOT(playStatusChanged()));
}

void AudioPlayer::playNext()
{
    m_Downloader->getNextTrack();
}

QMediaPlayer& AudioPlayer::getMediaPlayer() const
{
    return *m_Player;
}

void AudioPlayer::play()
{
    QByteArray data(m_Downloader->getData());
    if (data.size() > 0)
    {
        if (m_Buffer.isOpen())
            m_Buffer.close();

        m_Buffer.setData(m_Downloader->getData());
        m_Buffer.open(QBuffer::ReadOnly);
        m_Player->setMedia(QMediaContent(), &m_Buffer);
        m_Player->setVolume(100);
        m_Player->play();
    }
}

void AudioPlayer::playStatusChanged()
{
    if (m_Player->mediaStatus() == QMediaPlayer::EndOfMedia)
        playNext();
}
