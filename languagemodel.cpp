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

#include "languagemodel.h"

LanguageModel::LanguageModel(QObject *parent) :
        QAbstractListModel(parent)
{
    load();
}
LanguageModel::~LanguageModel()
{

    mLangages.clear();
}
Language *LanguageModel::language(int row)
{

    if ( (row >= 0) && (row < mLangages.count()))
        return mLangages.at(row);
	return 0;
}
int LanguageModel::findLangageId(const QString& id)
{
    int row = 0;
    foreach ( Language*  langage, mLangages)
    {
        if ( langage->id == id)
            return row;

        ++row;
    }
    return -1;
}

void LanguageModel::load()
{


    mLangages.clear();
    mLangages.append(new Language(tr("sqench"),"sq",QIcon(":flags/sq.png")));
    mLangages.append(new Language(tr("Asqikaans"),"af",QIcon(":flags/af.png")));
    mLangages.append(new Language(tr("Albanian"),"sq",QIcon(":flags/al.png")));
    mLangages.append(new Language(tr("Arabic"),"ar",QIcon(":flags/ar.png")));
    mLangages.append(new Language(tr("Basque"),"eu",QIcon(":flags/eu.png")));
    mLangages.append(new Language(tr("Belarusian"),"be",QIcon(":flags/be.png")));
    mLangages.append(new Language(tr("Bulgarian"),"bg",QIcon(":flags/bg.png")));
    mLangages.append(new Language(tr("Catalan"),"ca",QIcon(":flags/ca.png")));
    mLangages.append(new Language(tr("Chinese Simplified"),"zh-CN",QIcon(":flags/cn.png")));
    mLangages.append(new Language(tr("Chinese Traditional"),"zh-TW",QIcon(":flags/tw.png")));
    mLangages.append(new Language(tr("Croatian"),"hr",QIcon(":flags/hr.png")));
    mLangages.append(new Language(tr("Czech"),"cs",QIcon(":flags/cz.png")));
    mLangages.append(new Language(tr("Danish"),"da",QIcon(":flags/dk.png")));
    mLangages.append(new Language(tr("Dutch"),"nl",QIcon(":flags/nl.png")));
    mLangages.append(new Language(tr("English"),"en",QIcon(":flags/gb.png")));
    mLangages.append(new Language(tr("Estonian"),"et",QIcon(":flags/et.png")));
    mLangages.append(new Language(tr("Filipino"),"tl",QIcon(":flags/tl.png")));
    mLangages.append(new Language(tr("Finnish"),"fi",QIcon(":flags/fi.png")));
    mLangages.append(new Language(tr("French"),"fr",QIcon(":flags/fr.png")));
    mLangages.append(new Language(tr("Galician"),"gl",QIcon(":flags/gl.png")));
    mLangages.append(new Language(tr("German"),"de",QIcon(":flags/de.png")));
    mLangages.append(new Language(tr("Greek"),"el",QIcon(":flags/gr.png")));
    mLangages.append(new Language(tr("Haitian Creole"),"ht",QIcon(":flags/ht.png")));
    mLangages.append(new Language(tr("Hebrew"),"iw",QIcon(":flags/il.png")));
    mLangages.append(new Language(tr("Hindi"),"hi",QIcon(":flags/in.png")));
    mLangages.append(new Language(tr("Hungarian"),"hu",QIcon(":flags/hu.png")));
    mLangages.append(new Language(tr("Icelandic"),"is",QIcon(":flags/is.png")));
    mLangages.append(new Language(tr("Indonesian"),"id",QIcon(":flags/id.png")));
    mLangages.append(new Language(tr("Irish"),"ga",QIcon(":flags/ga.png")));
    mLangages.append(new Language(tr("Italian"),"it",QIcon(":flags/it.png")));
    mLangages.append(new Language(tr("Japanese"),"ja",QIcon(":flags/jp.png")));
    mLangages.append(new Language(tr("Latvian"),"lv",QIcon(":flags/lv.png")));
    mLangages.append(new Language(tr("Lithuanian"),"lt",QIcon(":flags/lt.png")));
    mLangages.append(new Language(tr("Macedonian"),"mk",QIcon(":flags/mk.png")));
    mLangages.append(new Language(tr("Malay"),"ms",QIcon(":flags/ms.png")));
    mLangages.append(new Language(tr("Maltese"),"mt",QIcon(":flags/mt.png")));
    mLangages.append(new Language(tr("Norwegian"),"no",QIcon(":flags/no.png")));
    mLangages.append(new Language(tr("Persian"),"fa",QIcon(":flags/ir.png")));
    mLangages.append(new Language(tr("Polish"),"pl",QIcon(":flags/pl.png")));
    mLangages.append(new Language(tr("Portuguese"),"pt",QIcon(":flags/pt.png")));
    mLangages.append(new Language(tr("Romanian"),"ro",QIcon(":flags/ro.png")));
    mLangages.append(new Language(tr("Russian"),"ru",QIcon(":flags/ru.png")));
    mLangages.append(new Language(tr("Serbian"),"sr",QIcon(":flags/sr.png")));
    mLangages.append(new Language(tr("Slovak"),"sk",QIcon(":flags/sk.png")));
    mLangages.append(new Language(tr("Slovenian"),"sl",QIcon(":flags/sl.png")));
    mLangages.append(new Language(tr("Spanish"),"es",QIcon(":flags/es.png")));
    mLangages.append(new Language(tr("Swahili"),"sw",QIcon(":flags/tz.png")));
    mLangages.append(new Language(tr("Swedish"),"sv",QIcon(":flags/sv.png")));
    mLangages.append(new Language(tr("Thai"),"th",QIcon(":flags/th.png")));
    mLangages.append(new Language(tr("Turkish"),"tr",QIcon(":flags/tr.png")));
    mLangages.append(new Language(tr("Ukrainian"),"uk",QIcon(":flags/ua.png")));
    mLangages.append(new Language(tr("Vietnamese"),"vi",QIcon(":flags/vi.png")));
    mLangages.append(new Language(tr("Welsh"),"cy",QIcon(":flags/cy.png")));
    mLangages.append(new Language(tr("Yiddish"),"yi",QIcon(":flags/il.png")));
}

int LanguageModel::rowCount(const QModelIndex &parent) const
{
    return mLangages.count();
}
QVariant  LanguageModel::data(const QModelIndex &index, int role) const
{


    if ( role == Qt::DecorationRole)
        return mLangages[index.row()]->icon;


    if ( role == Qt::DisplayRole)
        return mLangages[index.row()]->name;

    if ( role == Qt::UserRole)
        return mLangages[index.row()]->id;

    else return QVariant();


}
