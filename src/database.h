#ifndef DATABASE_H
#define DATABASE_H
#include <QObject>
#include "tvshow.h"
#include "tvshowdata.h"
#include <QtSql>

class Database : public QObject
{
    Q_OBJECT

public:
    explicit Database(QObject *parent = 0);
    void addShow(QString name);
    void removeShow(QString name);
    void alterSeason(QString name,int delta);
    void alterEpisode(QString name,int delta);
    void load();
    TvShowData* data;
};

#endif // DATABASE_H
