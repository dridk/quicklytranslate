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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QPropertyAnimation>
#include <QClipboard>
#include <QtNetwork>
#include <QList>
#include <QSystemTrayIcon>
#include "languagemodel.h"
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void exit();
    void trayActivated(QSystemTrayIcon::ActivationReason reason);
    void translate();
    void parseResult();
    void swapLangages();
    void showPreferences();
    void textToSpeak();
    void copy();
    void past();
    void cut();
    void showAbout();
    void showAboutQt();
    void showTextTTS();


protected:
    void closeEvent(QCloseEvent *event);
private:
    Ui::MainWindow *ui;
    QPropertyAnimation * mPropertyAnimation;
    QNetworkAccessManager * mNetManager;
    LanguageModel * mLangageModel;
};

#endif // MAINWINDOW_H
