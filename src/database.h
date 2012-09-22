#ifndef DATABASE_H
#define DATABASE_H
#include <QObject>
#include "tvshow.h"
#include "tvshowdata.h"

class Database : public QObject
{
    Q_OBJECT

public:
     explicit Database(QObject *parent = 0);
    void addShow(QString name);
    void removeShow(QString name);
    void alterSeason(QString name,int season);
    void alterEpisode(QString name,int episode);
    void alterGenre(QString name,QString genre);
    void load();
    TvShowData* data;
};

#endif // DATABASE_H
