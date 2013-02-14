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
#ifndef LANGUAGEMODEL_H
#define LANGUAGEMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QIcon>
class Language
{
public:
    Language(const QString& _name, const QString& _id,const QIcon& _icon)
    {
        name = _name;
        id = _id;
        icon=_icon;
    }

    QString name;
    QString id;
    QIcon icon;
};


class LanguageModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit LanguageModel(QObject *parent = 0);
    ~LanguageModel();
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    void load();
    Language *language(int row);
    int findLangageId(const QString id);

signals:

public slots:

private:
    QList <Language*> mLangages;

};

#endif // LANGUAGEMODEL_H
