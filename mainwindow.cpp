#include "mainwindow.h"

MainWindow::MainWindow() : _titleLabel(new QLabel(this)),
    _creditsButton(new QPushButton("Credits", this)),
    _playlistPropertiesBox(new QGroupBox("Propriétés de la playlist", this)),
    _histogramContainer(new QGroupBox("Origine des musiques", this)),
    _durationField(new QLineEdit(this)),
    _label1(new QLabel("Durée (minutes) :", this)),
    _label2(new QLabel("Fichier de sortie :", this)),
    _fileNameLabel(new QLabel("Aucun fichier sélectionné", this)),
    _fileSectionButton(new QPushButton("...", this)),
    _fileChooser(new QFileDialog(this)),
    _generateButton(new QPushButton("Télécharger", this)),
    _progressBar(new QProgressBar(this)),
    _currentStepLabel(new QLabel("...", this))
{
    setFixedSize(500,540);

    _progressBar->setTextVisible(false);

    QStringList *channels = new QStringList();
    channels->push_back("UC_aEa8K-EOJ3D6gOs7HcyNg");
    channels->push_back("UCXvSeBDvzmPO05k-0RyB34w");
    channels->push_back("UC5nc_ZtjKW1htCVZVRxlQAQ");
    channels->push_back("UCJ6td3C9QlPO9O_J5dF4ZzA");

    _downloader = new YoutubeMp3Downloader(this, channels, 4, _progressBar, _currentStepLabel);

    _fileChooser->setDirectory(QDir::home());
    _fileChooser->setNameFilter(".mp3");
    connect(_fileChooser, SIGNAL(fileSelected(QString)), this, SLOT(fileChosen(QString)));

    _titleLabel->setFont(QFont("sans-serif", 15, 15));
    _titleLabel->setText("Free Music Downloader");
    _titleLabel->setGeometry(0,10,500,30);
    _titleLabel->setAlignment(Qt::AlignCenter);

    _creditsButton->setGeometry(width()-50, 0, 50, 30);

    _playlistPropertiesBox->setGeometry(10, 50, 480, 120);

    _label1->setGeometry(23, 75, 83, 20);
    _durationField->setAlignment(Qt::AlignCenter);
    _durationField->setText("3");
    _durationField->setGeometry(120, 75, 40, 20);
    _durationField->setValidator(new QIntValidator(this));

    _label2->setGeometry(23, 125, 83, 20);
    _fileSectionButton->setGeometry(120, 125, 40, 22);
    connect(_fileSectionButton, SIGNAL(pressed()), this, SLOT(showFileChooser()));
    _fileNameLabel->setGeometry(170, 125, 200, 20);

    _histogramContainer->setGeometry(10, 175, 480, 265);

    _histogram = new Histogram(this);
    _histogram->setGeometry(25, 205, width()-50, 220);

    connect(_generateButton, SIGNAL(pressed()), this, SLOT(generate()));
    _generateButton->setGeometry(width()/2-50, 450, 100, 40);
    _progressBar->setGeometry(10, 500, width()-20, 20);
    _currentStepLabel->setGeometry(10, 520, width()-20, 20);
    _currentStepLabel->setAlignment(Qt::AlignCenter);

}

MainWindow::~MainWindow()
{
    delete _downloader;
    delete _currentStepLabel;
    delete _progressBar;
    delete _generateButton;
    delete _label1;
    delete _label2;
    delete _fileNameLabel;
    delete _fileChooser;
    delete _fileSectionButton;
    delete _durationField;
    delete _histogram;
    delete _titleLabel;
    delete _playlistPropertiesBox;
    delete _histogramContainer;
}

void MainWindow::fileChosen(QString filePath){
    if(!filePath.endsWith(".mp3"))
        filePath += ".mp3";
    _fileNameLabel->setText(filePath);
}

void MainWindow::showFileChooser(){
    _fileChooser->show();
}

void MainWindow::generate(){
    if(_durationField->text().toInt() >= 3){
        if(_fileNameLabel->text() == "Aucun fichier sélectionné"){
            QMessageBox::information(this, "Erreur", "Vous devez sélectionner le fichier où sauvegarder les musiques.", QMessageBox::Ok);
            return;
        }
        int total =  _durationField->text().toInt()*60;
        int durations[4];
        durations[0] = total*_histogram->getRectangleValue(0)/100;
        durations[1] = total*_histogram->getRectangleValue(1)/100;
        durations[2] = total*_histogram->getRectangleValue(2)/100;
        durations[3] = total*_histogram->getRectangleValue(3)/100;
        _generateButton->setEnabled(false);
        _downloader->download(_fileNameLabel->text(), total, durations);
        _generateButton->setEnabled(true);
    }else
        QMessageBox::information(this, "Erreur", "Le temps indiqué doit être supérieur à 3 minutes.", QMessageBox::Ok);
}
