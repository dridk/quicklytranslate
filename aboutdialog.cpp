#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include <QDesktopServices>
#include <QUrl>
#include <QApplication>
AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    connect(ui->paypalButton,SIGNAL(clicked()),this,SLOT(openPayPal()));
    ui->versionLabel->setText("version "+QApplication::applicationVersion());
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
void AboutDialog::openPayPal()
{


    QDesktopServices::openUrl(QUrl("http://flattr.com/thing/86615/omed-Le-blog-du-developpeur-sous-Qt-4"));

}
