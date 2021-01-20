#ifndef YOUTUBEMP3DOWNLOADER_H
#define YOUTUBEMP3DOWNLOADER_H

#include <QProgressBar>
#include <QString>
#include <QString>
#include <QFile>
#include <ctime>
#include <QMessageBox>
#include <QLabel>

class YoutubeMp3Downloader
{
public:
    YoutubeMp3Downloader(QWidget *parent, QStringList *channelIds, int channelAmount, QProgressBar *progressBar, QLabel *informationLabel);
    void download(QString filePath, int playlistDuration, int musicDuration[]);
 private:
    int addLinks(QStringList &list, QString channelId, int duration);
    bool isVideoAvailable(QString const &videoId) const;
    QByteArray downloadVideo(QString videoId);
    QWidget *_parent;
    QLabel *_informationLabel;
    QProgressBar *_progressBar;
    QStringList *_channelIds;
    int _length;
    int _playListDuration;
    QStringList _videosLink;
};

#endif // YOUTUBEMP3DOWNLOADER_H
