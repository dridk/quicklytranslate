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
#include <QSettings>
#include "preferencedialog.h"
#include "ui_preferencedialog.h"
PreferenceDialog::PreferenceDialog(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::PreferenceDialog)
{
    ui->setupUi(this);

    mLangageModel = new LanguageModel;

    ui->sourceComboBox->setModel(mLangageModel);
    ui->targetComboBox->setModel(mLangageModel);

    connect(ui->saveButton,SIGNAL(clicked()),this,SLOT(save()));

    load();
}

PreferenceDialog::~PreferenceDialog()
{
    delete ui;
    delete mLangageModel;
}
void PreferenceDialog::save()
{

    Language *source = mLangageModel->language(ui->sourceComboBox->currentIndex());
    Language *target = mLangageModel->language(ui->targetComboBox->currentIndex());

    QSettings settings;
    settings.setValue("source", source->id);
    settings.setValue("target", target->id);
    settings.setValue("autopast", ui->autoPastCheckBox->isChecked());
    settings.setValue("autotranslate", ui->autoTranslateCheckBox->isChecked());

    emit accept();


}

void PreferenceDialog::load()
{
    QSettings settings;
    QString sourceId = settings.value("source").toString();
    QString targetId = settings.value("target").toString();

    ui->sourceComboBox->setCurrentIndex(mLangageModel->findLangageId(sourceId));
    ui->targetComboBox->setCurrentIndex(mLangageModel->findLangageId(targetId));

    ui->autoPastCheckBox->setChecked(settings.value("autopast").toBool());
    ui->autoTranslateCheckBox->setChecked(settings.value("autotranslate").toBool());

}
