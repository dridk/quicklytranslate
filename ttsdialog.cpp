/*!
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *
 *    Author: sacha schutz
 *    E-Mail: istdasklar@gmail.com
 *    Years: 2010-2010
 *    Author: flareguner
 *    E-Mail: flareguner@gmail.com
 *    Years: 2010-2010
 */
#include "ttsdialog.h"
#include "ui_ttsdialog.h"
#include <QTemporaryFile>
#include <Phonon/MediaObject>
#include <QDebug>
#include <QDesktopServices>
#include <QFile>
#include <QTemporaryFile>
#include <QDir>
#include <QMessageBox>
#include <QPalette>
#include <QMenu>
#include <QLocale>
#include <QFileDialog>
#define GOOGLE_TTS "http://translate.google.com/translate_tts"
TTSDialog::TTSDialog( Language* langage,const QString& tts,QWidget *parent) :
        QDialog(parent),
        ui(new Ui::TTSDialog)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    mLangage = langage;
    mNetManager = new QNetworkAccessManager;
    mLangageModel = new LanguageModel;
    mMediaObject= Phonon::createPlayer(Phonon::MusicCategory);
    mMediaObject->setTickInterval(100);


    QMenu * dlMenu = new QMenu(this);
    dlMenu->addAction(tr("open audio file"));
    dlMenu->addAction(tr("download audio file"));
    ui->loadedButton->setMenu(dlMenu);

    ui->comboBox->setModel(mLangageModel);
    ui->comboBox->setCurrentIndex(mLangageModel->findLangageId(mLangage->id));



    connect(dlMenu->actions().at(0),SIGNAL(triggered()),this,SLOT(openSoundFile()));
    connect(dlMenu->actions().at(1),SIGNAL(triggered()),this,SLOT(saveSoundFile()));
    connect(ui->stopButton,SIGNAL(clicked()),mMediaObject,SLOT(stop()));
    connect(ui->pauseButton,SIGNAL(clicked()),mMediaObject,SLOT(pause()));
    connect(mMediaObject,SIGNAL(tick(qint64)),this,SLOT(updateProgress(qint64)));
    connect(ui->slider,SIGNAL(sliderMoved(int)),this,SLOT(updateSlider(int)));
    connect(ui->playButton,SIGNAL(clicked()),mMediaObject,SLOT(play()));


    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(updateLangage()));
    connect(ui->textEdit,SIGNAL(returnPressed()),this,SLOT(downloadFile()));
    setText(tts);

}
void TTSDialog::openSoundFile()
{
    QString ttsPath = QDesktopServices::storageLocation(QDesktopServices::TempLocation)+"/tts.wav";
    QDesktopServices::openUrl(QUrl(ttsPath));
}

void TTSDialog::saveSoundFile()
{
    QString savePath = QFileDialog::getSaveFileName(this,"save audio","","Audio (*.wav)");
    QString ttsPath = QDesktopServices::storageLocation(QDesktopServices::TempLocation)+"/tts.wav";
    QFile::copy(ttsPath,savePath);

}

void TTSDialog::updateLangage()
{
    mLangage =  mLangageModel->language(ui->comboBox->currentIndex());
}
void TTSDialog::downloadProgress(qint64 receive,qint64 total)
{
    float ratio = float(receive) / float ( total) * 100;
    ui->progressBar->setValue(ratio);
}

void TTSDialog::updateProgress(qint64 time)
{
    float ratio = float(time) /float(mMediaObject->totalTime())*100;
    ui->slider->setValue(ratio);
    if ( ratio >= 100)
        mMediaObject->stop();
}
void TTSDialog::updateSlider(int step)
{
    if ( mMediaObject->isValid())
        mMediaObject->seek(step);
}

TTSDialog::~TTSDialog()
{
    delete ui;
    delete mMediaObject;
}
void TTSDialog::downloadFile()
{
    mMediaObject->clear();
    mMediaObject->clearQueue();
    ui->progressBar->setValue(0);
    ui->toolFrame->setEnabled(false);
    QString text = ui->textEdit->toPlainText();
    QNetworkReply * reply = mNetManager->get(QNetworkRequest(QUrl(
            QString(GOOGLE_TTS"?tl=%1&q=%2").arg(mLangage->id).arg(text))));

    connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(downloadProgress(qint64,qint64)));
    connect(reply,SIGNAL(finished()),this,SLOT(downloadDone()));


}

void TTSDialog::downloadDone()
{
    QNetworkReply * reply = qobject_cast<QNetworkReply*>(sender());

    QByteArray data = reply->readAll();
    qDebug()<<"size"<<data.size();


    if ( data.size()<=0)
    {
        QMessageBox::warning(this,tr("langage not supported"),tr("sorry this langage is not yet supported by Google. Please select another langage"));
        return;
    }
    QString dir = QDesktopServices::storageLocation(QDesktopServices::TempLocation);

    QFile file(dir+"/tts.wav");
    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(this,tr("file error"),tr("cannot open tempFile"));
        file.close();
        return;
    }

    file.write(data);
    file.close();

    qDebug()<<"filename"<<file.fileName();
    ui->toolFrame->setEnabled(true);


    playFile(file.fileName());

    reply->deleteLater();


}
void TTSDialog::setText(const QString& _text)
{
    if ( _text.isEmpty())
        return;
    ui->textEdit->setText(_text);
    downloadFile();
}
void TTSDialog::playFile(const QString& filename)
{
    qDebug()<<filename;
    mMediaObject->setCurrentSource(Phonon::MediaSource(filename));
    mMediaObject->play();
}
