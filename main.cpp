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

#include <QApplication>
#include <QTranslator>
#include "mainwindow.h"


int main(int argc, char **argv)
{

    QApplication app(argc,argv);
    QCoreApplication::setOrganizationName("omedsoft");
    QCoreApplication::setOrganizationDomain("omedsoft.blogspot.com");
    QCoreApplication::setApplicationName("quicktranslate");
    QCoreApplication::setApplicationVersion("0.5alpha");

    QString locale = QLocale::system().name().section('_', 0, 0);

    QTranslator translator;
    qDebug()<<locale;
    translator.load(QString("../quicklytranslate/quicklytranslate_") + locale);
    app.installTranslator(&translator);


    MainWindow * window = new MainWindow;

    window->show();
    return app.exec();

}
