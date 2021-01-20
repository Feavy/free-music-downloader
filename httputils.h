#ifndef HTTPUTILS_H
#define HTTPUTILS_H

#include <QWidget>
#include <QUrl>
#include <QString>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QEventLoop>

QNetworkReply *sendGetRequest(QWidget *parent, QString url);
void sigUrl(QString &url);
QString escapeHtml(QString url);

#endif // HTTPUTILS_H
