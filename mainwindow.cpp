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
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSystemTrayIcon>
#include <QMenu>
#include <QGraphicsEffect>
#include <QDesktopWidget>
#include <QDebug>
#include <QNetworkRequest>
#include <QApplication>
#include <QClipboard>
#include <QMessageBox>
#include <QScriptEngine>
#include <QScriptValueIterator>
#include <QDesktopServices>
#include <QLocale>
#include <QTextDocumentFragment>
#include "preferencedialog.h"
#include "aboutdialog.h"
#include "ttsdialog.h"
#include "qxtjson/qxtjson.h"
#define GOOGLE_URL "http://www.google.com/translate_a/t"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":icons/icon.png"));
    setWindowTitle("quickly translate");
    QSystemTrayIcon * trayIcon = new QSystemTrayIcon(this);
    mNetManager = new QNetworkAccessManager(this);
    mLangageModel = new LanguageModel;

    trayIcon->setIcon(QIcon(":icons/icon.png"));

    trayIcon->setContextMenu(ui->menuFile);
    trayIcon->show();

    ui->dockWidget->hide();
    ui->sourceComboBox->setModel(mLangageModel);
    ui->targetComboBox->setModel(mLangageModel);

    QDesktopWidget * desktop = new QDesktopWidget;

    QPoint startPos = QPoint(desktop->geometry().bottomRight() );
    QPoint finalPos = desktop->geometry().center() - QPoint(width()/2,height()/2);

    move(finalPos);
    connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(trayActivated(QSystemTrayIcon::ActivationReason)));
    connect(ui->actionExit,SIGNAL(triggered()),this,SLOT(exit()));
    connect(ui->translateButton,SIGNAL(clicked()),this,SLOT(translate()));
    connect(ui->sourceTextEdit,SIGNAL(returnPressed()),this,SLOT(translate()));
    connect(ui->swapButton,SIGNAL(clicked()),this,SLOT(swapLangages()));

    connect(ui->actionCopy,SIGNAL(triggered()),this,SLOT(copy()));
    connect(ui->actionCut,SIGNAL(triggered()),this,SLOT(cut()));
    connect(ui->actionPast,SIGNAL(triggered()),this,SLOT(past()));
    connect(ui->actionPreferences,SIGNAL(triggered()),this,SLOT(showPreferences()));
    connect(ui->actionAboutQt,SIGNAL(triggered()),this,SLOT(showAboutQt()));
    connect(ui->actionAbout,SIGNAL(triggered()),this,SLOT(showAbout()));
    connect(ui->actionTTS,SIGNAL(triggered()),this,SLOT(showTextTTS()));


    connect(ui->sourceSoundButton,SIGNAL(clicked()),this,SLOT(textToSpeak()));
    connect(ui->targetSoundButton,SIGNAL(clicked()),this,SLOT(textToSpeak()));


    //    mPropertyAnimation  = new QPropertyAnimation(this, "pos");
    //    mPropertyAnimation->setDuration(800);
    //    mPropertyAnimation->setStartValue(startPos);
    //    mPropertyAnimation->setEndValue(finalPos);


    //load default langage

    QSettings settings;
    QString sourceId = settings.value("source").toString();
    QString targetId = settings.value("target").toString();
    ui->sourceComboBox->setCurrentIndex(mLangageModel->findLangageId(sourceId));
    ui->targetComboBox->setCurrentIndex(mLangageModel->findLangageId(targetId));

}
void MainWindow::trayActivated(QSystemTrayIcon::ActivationReason reason)
{

    if ( reason != QSystemTrayIcon::Trigger)
        return;
    if (isHidden())
    {
        show();
        QSettings settings;
        if (settings.value("autopast").toBool())
            past();
        if (settings.value("autotranslate").toBool())
            translate();
    }
    else
        hide();

}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::exit()
{
    QApplication::exit();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox msgBox;
    msgBox.setText(tr("Would you like to definitly close application?"));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Discard);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();

    if ( ret == QMessageBox::Yes)
        exit();

    else
    {
        event->ignore();
        hide();
    }
}
void MainWindow::translate()
{
    Language *srcLn = mLangageModel->language(ui->sourceComboBox->currentIndex());
    Language *targetLn = mLangageModel->language(ui->targetComboBox->currentIndex());

    QByteArray postData;
    QString source = srcLn->id.toUtf8().toPercentEncoding();
    QString dest = targetLn->id.toUtf8().toPercentEncoding();
    QString texte=ui->sourceTextEdit->toPlainText().toUtf8().toPercentEncoding();
    QString st = "text="+texte+"&client=t&sl=" + source + "&tl=" + dest;

    postData = st.toUtf8();

    QNetworkRequest request(QString(GOOGLE_URL));

    request.setRawHeader("Content-Type","application/x-www-form-urlencoded");
    request.setRawHeader("Host","www.google.com");
    request.setRawHeader("User-Agent","Mozilla/5.0");
    request.setRawHeader("Accept-Encoding","deflate");
    request.setRawHeader("Connection","Close");


    QNetworkReply * reply = mNetManager->post(QNetworkRequest(request),postData);
    qDebug()<<reply->url();
    connect(reply,SIGNAL(finished()),this,SLOT(parseResult()));
}

void MainWindow::parseResult()
{
    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    const QByteArray rawdata = reply->readAll();
	QString result;
	/*
		google returns :
		[[["Je mange. ","I eat.","",""],["vous n'avez pas.","you don't.","",""]],,"en",, ...]
		or
		[[["bonjour","hello","",""]],,"interjection",, ...]
		
		QxtJson return a shitty list:
		QList("Je mange. ", "I eat.", "", "", "vous n'avez pas.","you don't.","","", "en", ...)
		or
		QList("bonjour", "hello", "", "", "interjection", ...)
		
		// forget it for now.
		QStringList list = QxtJSON::parse(QString::fromUtf8(rawdata)).toStringList();
	*/
	int index = 0;
	index = rawdata.indexOf('[', index);
	index = rawdata.indexOf('[', index);
	
	// check what is next, a next array or the end of the group.
	int indexOpen = rawdata.indexOf('[', index);
	int indexClose = rawdata.indexOf(']', index);
	
	// if open < close, there are still things to read
	while(indexOpen < indexClose)
	{
		QByteArray extract = rawdata.mid(indexOpen, indexClose - indexOpen + 1);
		
		// the translated string is the first quoted-string.
		int translationStarts = extract.indexOf('"') + 1;
		int translationEnds = extract.indexOf('"', translationStarts);
		while(extract[ translationEnds-1 ] == '\\') // skip escaped quotes
			translationEnds = extract.indexOf('"', translationEnds + 1);
		
		result += QString::fromUtf8(extract.mid(translationStarts, translationEnds - translationStarts));
		
		index = indexClose + 1;
		indexOpen = rawdata.indexOf('[', index);
		indexClose = rawdata.indexOf(']', index);
	}
	
	ui->targetTextEdit->setText(QTextDocumentFragment::fromHtml(result).toPlainText());

    /*
    QVariantMap map = parser.parse(QString::fromUtf8(rawdata.data())).toMap();
    qDebug()<<map;
    ui
    QVariantMap map2 = map["responseData"].toMap();
    const QString result = map2["translatedText"].toString();

    ui->targetTextEdit->setText(QTextDocumentFragment::fromHtml(result).toPlainText());

    */
    reply->deleteLater();
}
void MainWindow::swapLangages()
{

    int idSource = ui->sourceComboBox->currentIndex();
    int idTarget = ui->targetComboBox->currentIndex();

    ui->sourceComboBox->setCurrentIndex(idTarget);
    ui->targetComboBox->setCurrentIndex(idSource);


}
void MainWindow::textToSpeak()
{

    /*  Language *srcLn = mLangageModel->language(ui->sourceComboBox->currentIndex());
    Language *targetLn = mLangageModel->language(ui->targetComboBox->currentIndex());

    QToolButton * button = qobject_cast<QToolButton*>(sender());

    qDebug()<<button->text();
    TTSDialog * dialog = 0 ;
    if ( button->text() == "source")
    {
        dialog = new TTSDialog(srcLn,ui->sourceTextEdit->toPlainText());

    }
    if ( button->text() == "target")
    {
        dialog = new TTSDialog(targetLn,ui->targetTextEdit->toPlainText());
    }
    if ( !dialog)
        return;

    dialog->exec();
*/
}

void MainWindow::showTextTTS()
{
    /*
    TTSDialog * dialog = new TTSDialog(mLangageModel->language(mLangageModel->findLangageId("en")),"welcome");
    dialog->exec();

    */
}

void MainWindow::showPreferences()
{
    PreferenceDialog * dialog = new PreferenceDialog;
    dialog->exec();
}
void MainWindow::copy()
{
    if ( ui->sourceTextEdit->hasFocus())
        QApplication::clipboard()->setText(ui->sourceTextEdit->toPlainText());
    else
        QApplication::clipboard()->setText(ui->targetTextEdit->toPlainText());
}
void MainWindow::past()
{
    qDebug()<<"past";
    ui->sourceTextEdit->setText(QApplication::clipboard()->text(QClipboard::Clipboard));
}
void MainWindow::cut()
{
    if ( ui->sourceTextEdit->hasFocus())
    {
        QApplication::clipboard()->setText(ui->sourceTextEdit->toPlainText());
        ui->sourceTextEdit->clear();
    }
    else
        QApplication::clipboard()->setText(ui->targetTextEdit->toPlainText());
}
void MainWindow::showAbout()
{
    AboutDialog * dialog = new AboutDialog;
    dialog->exec();
}
void MainWindow::showAboutQt()
{
    QMessageBox::aboutQt (this, tr("about qt"));
}
