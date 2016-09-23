#ifndef AUDIODOWNLOADER_H
#define AUDIODOWNLOADER_H

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class AudioDownloader : public QObject
{
    Q_OBJECT

    enum Method
    {
        getNextTrackId,
        getTrackById
    };

public:
    explicit AudioDownloader(QString deviceID, QObject *parent = 0);

    const QByteArray& getData() const;
    void getNextTrack();

signals:
    void downloaded();

private slots:
    void finished(QNetworkReply* pReply);

private:
    void loadCurrTrack();

    QString m_DeviceID;
    QString m_CurrTrackID;
    QByteArray m_Data;
    QNetworkAccessManager m_NAM;
};

#endif // AUDIODOWNLOADER_H
