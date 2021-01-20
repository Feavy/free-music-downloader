#include "youtubemp3downloader.h"
#include "httputils.h"

YoutubeMp3Downloader::YoutubeMp3Downloader(QWidget *parent, QStringList *channelIds, int channelAmount, QProgressBar *progressBar, QLabel *informationLabel) :
    _channelIds(channelIds),
    _length(channelAmount),
    _progressBar(progressBar),
    _videosLink(QStringList()),
    _parent(parent),
    _playListDuration(0),
    _informationLabel(informationLabel)
{
    srand(time(0));
}

void YoutubeMp3Downloader::download(QString filePath, int playlistDuration, int musicDuration[]){

    _progressBar->setRange(0, 4);
    _progressBar->setValue(0);

    _informationLabel->setText("Obtention des musiques...");

    _playListDuration = playlistDuration;
    int d;

    for(int i = 0; i < _length; i++){
        d = addLinks(_videosLink, _channelIds->at(i), (_playListDuration < musicDuration[i])?_playListDuration:musicDuration[i]);
        _playListDuration -= d;
        qDebug() << _playListDuration;
        if(i < _length-1){
            musicDuration[i+1] = musicDuration[i+1]-(d-musicDuration[i]);
        }
        qDebug() << "Durée : " << _channelIds->at(i) << " : " << QString::number(d) << " secondes";
        if(_playListDuration <= 60)
            break;
        _progressBar->setValue(i+1);
    }

    _progressBar->setValue(1);
    _progressBar->setRange(1, _videosLink.size());

    QStringList videosLink = _videosLink;
    _videosLink.clear();
    int s = videosLink.size();
    int r;

    for(int i = 0; i < s; i++){
        r = rand() % videosLink.size();
        _videosLink.push_back(videosLink.at(r));
        videosLink.removeAt(r);
    }

    qDebug() << "VideoIds obtenus !";
    _informationLabel->setText("Téléchargement des musiques...");

    std::vector<QByteArray> audios;

    for(int i = 0; i < _videosLink.size(); i++){
        audios.push_back(downloadVideo(_videosLink.at(i)));
        _informationLabel->setText("Musique téléchargée : "+_videosLink.at(i));
        _progressBar->setValue(i+1);
    }

    _informationLabel->setText("Création du fichier...");

    QFile file(filePath);

    file.resize(0);

    if(file.open(QIODevice::WriteOnly)){
        QDataStream output(&file);
        for(QByteArray audio : audios){
           output.writeBytes(audio, audio.length());
        }
        file.close();
    }

    _informationLabel->setText("Fichier créé !");

    QMessageBox::information(_parent, "Succès", "Les musiques ont été correctement téléchargées !", QMessageBox::Ok);
    _progressBar->setValue(1);

    _informationLabel->setText("...");

}

QByteArray YoutubeMp3Downloader::downloadVideo(QString videoId){

    QString url = "http://www.youtube-mp3.org/a/itemInfo/?video_id="+videoId+"&ac=www&t=grp&r="+QString::number(QDateTime::currentDateTime().toMSecsSinceEpoch());
    sigUrl(url);

    QNetworkReply *reply = sendGetRequest(_parent, url);

    QString dataString = QString(reply->readAll()).replace("\\", "").replace("\"", "");

    QString ts_create(dataString.split("ts_create:")[1].split(",")[0]),
            r(dataString.split("r:")[1].split(",")[0]),
            h2(dataString.split("h2:")[1].split("}")[0]);

    url = "http://www.youtube-mp3.org/get?video_id="+videoId+"&ts_create="+ts_create+"&r="+r+"&h2="+h2;
    sigUrl(url);

    reply = sendGetRequest(_parent, url);

    url = reply->header(QNetworkRequest::KnownHeaders::LocationHeader).toString();

    reply = sendGetRequest(_parent, url);

    return reply->readAll();

}

bool YoutubeMp3Downloader::isVideoAvailable(QString const &videoId) const{
    QString url = "http://www.youtube-mp3.org/a/itemInfo/?video_id="+videoId+"&ac=www&t=grp&r="+QString::number(QDateTime::currentDateTime().toMSecsSinceEpoch());
    sigUrl(url);

    QNetworkReply *reply = sendGetRequest(_parent, url);

    if(QString(reply->readAll()).contains(R"("status":"progress")")){
        return false;
    }

    return true;

}

int YoutubeMp3Downloader::addLinks(QStringList &list, QString channelId, int duration){

    QString url = "https://www.youtube.com/channel/"+channelId+"/videos";
    QNetworkReply *reply(0);
    QStringList dataLines;
    QString nextKey("");
    QString timeString;
    bool print = true;

    int durationDownloaded = 0;

    while(duration-60 > durationDownloaded){

        dataLines.clear();
        reply = sendGetRequest(_parent, url);
        if(!reply->canReadLine()){
            reply->deleteLater();
            QString data = QString(reply->readAll()).toUtf8();
            data = data.replace("\\u003c", "<").replace("\\u003e", ">");
            dataLines = QString(data).split("\\n");
        }else{
            while(reply->canReadLine())
                dataLines.push_back(reply->readLine());
        }

        for(QString line : dataLines){
            line = line.replace("\\", "");
            if(line.contains("watch?") && line.contains("yt-uix-sessionlink")){
                if(print)
                    list.push_back(line.split("?v=")[1].split("\"")[0]);
                print = !print;
            } else if(line.contains("video-time")){
                timeString = line.split("\">")[2].split("<")[0];
                int s = timeString.split(":")[0].toInt()*60+timeString.split(":")[1].toInt();
                if(s < 420)
                    if(isVideoAvailable(list.at(list.size()-1)))
                        durationDownloaded += s;
                    else
                        list.pop_back();
                else
                    list.pop_back();

            }else if(line.contains("/browse_ajax?action_continuation"))
                nextKey = line.split(";continuation=")[1].split("\"")[0];

            if(durationDownloaded > duration)
                break;
        }

        url = "https://www.youtube.com/browse_ajax?action_continuation=1&continuation="+nextKey;

    }

    return durationDownloaded;

}
