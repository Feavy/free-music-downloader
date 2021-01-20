#include "httputils.h"

QNetworkReply *sendGetRequest(QWidget *parent, QString url){
    QNetworkAccessManager *networkManager = new QNetworkAccessManager(parent);

    QNetworkReply *reply = networkManager->get(QNetworkRequest(QUrl(url)));

    QEventLoop loop;
    parent->connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    return reply;
}

QString characters[] = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","_","&","-","/","="};
int numbers[] = {870,906,167,119,130,899,248,123,627,706,694,421,214,561,819,925,857,539,898,866,433,299,137,285,613,635,638,639,880,687,721};

QString charNbs[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

int isNumeric(QString c);
int getIndex(QString tbl[], QString c, int length);

void sigUrl(QString &url){
    double F = 1.51214;

    double N = 3219;

    for (int Y = 0; Y < url.length(); Y++) {

        QString Q = url.mid(Y, 1).toLower();

        if (isNumeric(Q) > -1) {
            N += (Q.toInt() * 121 * F);
        } else {
            int index = getIndex(characters, Q, 31);
            if (index >= 0) {
                N += (numbers[index] * F);
            }
        }

        N *= 0.1;
    }
    N = round(N*1000);

    url += "&s="+QString::number(N);
}

QString escapeHtml(QString url) {
    return url.replace("&", "&amp;").replace("<", "&lt;").replace(">", "&gt;").replace('"', "&quot;").replace("'", "&#039;");
}

int getIndex(QString tbl[], QString c, int length){
    for(int i = 0; i < length; i++){
        if(tbl[i] == c)
            return i;
    }
    return -1;
}

int isNumeric(QString c) {
    for (int i = 0; i < 10; i++) {
        if (charNbs[i] == c)
            return i;
    }
    return -1;
}
