#include "texttospeakdialog.h"
#include "ui_texttospeakdialog.h"

TextToSpeakDialog::TextToSpeakDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TextToSpeakDialog)
{
    ui->setupUi(this);
}

TextToSpeakDialog::~TextToSpeakDialog()
{
    delete ui;
}
