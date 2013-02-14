#ifndef TEXTTOSPEAKDIALOG_H
#define TEXTTOSPEAKDIALOG_H

#include <QDialog>

namespace Ui {
    class TextToSpeakDialog;
}

class TextToSpeakDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TextToSpeakDialog(QWidget *parent = 0);
    ~TextToSpeakDialog();

private:
    Ui::TextToSpeakDialog *ui;
};

#endif // TEXTTOSPEAKDIALOG_H
