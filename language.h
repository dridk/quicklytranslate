#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <QObject>
#include <QIcon>
class Language
{
public:
    explicit Language(const QString& _name, const QString& _id,const QIcon& _icon=QIcon());
    QString name;
    QString id;
    QIcon icon;



};

#endif // LANGUAGE_H
