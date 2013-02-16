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
#ifndef TTSDIALOG_H
#define TTSDIALOG_H

#include <QDialog>
#include <QtNetwork>
#include <QTemporaryFile>
#include <phonon/MediaObject>
#include <QFile>
#include "languagemodel.h"

namespace Ui {
    class TTSDialog;
}

class TTSDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TTSDialog(Language* langage, const QString& tts="hello world",QWidget *parent = 0);
    ~TTSDialog();
public slots:
    void downloadFile();
    void downloadDone();
    void setText(const QString& _text);

    void playFile(const QString& filename);
    void updateProgress(qint64 time);
    void updateSlider(int step);
    void updateLangage();
    void downloadProgress(qint64,qint64);
    void openSoundFile();
    void saveSoundFile();
private:
    Ui::TTSDialog *ui;
    LanguageModel * mLangageModel;
    Language *mLangage;
    QNetworkAccessManager * mNetManager;
    QFile mTempFile;
    Phonon::MediaObject *mMediaObject;
};

#endif // TTSDIALOG_H
