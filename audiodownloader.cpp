#include "audiodownloader.h"
#include <QNetworkRequest>

AudioDownloader::AudioDownloader(QString deviceID, QObject *parent)
    : QObject(parent),
      m_DeviceID(deviceID)
{
    connect(&m_NAM, SIGNAL(finished(QNetworkReply*)), SLOT(finished(QNetworkReply*)));
}

const QByteArray& AudioDownloader::getData() const
{
    return m_Data;
}

void AudioDownloader::getNextTrack()
{
    m_CurrTrackID = "";
    QString url("http://ownradio.ru/api/track/GetNextTrackID/");
    url.append(m_DeviceID);
    QNetworkRequest request(url);
    request.setAttribute(QNetworkRequest::User, Method::getNextTrackId);
    m_NAM.get(request);
}

void AudioDownloader::loadCurrTrack()
{
    if (!m_CurrTrackID.isEmpty())
    {
        QString url("http://ownradio.ru/api/track/GetTrackByID/");
        url.append(m_CurrTrackID);
        QNetworkRequest request(url);
        request.setAttribute(QNetworkRequest::User, Method::getTrackById);
        m_NAM.get(request);
    }
}

void AudioDownloader::finished(QNetworkReply *pReply)
{
    switch (pReply->request().attribute(QNetworkRequest::User).toInt())
    {
    case Method::getNextTrackId:
        m_CurrTrackID = pReply->readAll();
        m_CurrTrackID.replace("\"","");
        pReply->deleteLater();
        loadCurrTrack();
        break;
    case Method::getTrackById:
        m_Data = pReply->readAll();
        pReply->deleteLater();
        emit downloaded();
        break;
    }
}


