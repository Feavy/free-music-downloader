#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "histogram.h"
#include <youtubemp3downloader.h>
#include <QMainWindow>
#include <QGroupBox>
#include <QLineEdit>
#include <QLabel>
#include <QFileDialog>
#include <QIntValidator>
#include <QPushButton>
#include <QDebug>
#include <QProgressBar>
#include <QMessageBox>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();
public slots:
    void showFileChooser();
    void fileChosen(QString filePath);
    void generate();
private:
    Histogram *_histogram;
    QLabel *_titleLabel;
    QGroupBox *_playlistPropertiesBox;
    QGroupBox *_histogramContainer;
    QLineEdit *_durationField;
    QPushButton *_fileSectionButton;
    QFileDialog *_fileChooser;
    QLabel *_label1;
    QLabel *_label2;
    QLabel *_fileNameLabel;
    QPushButton *_generateButton;
    QPushButton *_creditsButton;
    QProgressBar *_progressBar;
    QLabel *_currentStepLabel;
    YoutubeMp3Downloader *_downloader;
};

#endif // MAINWINDOW_H
