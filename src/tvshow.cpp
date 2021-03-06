#include "tvshow.h"

#include "quickinfo.h"
#include "utils.h"

#include <QDebug>
#include <QRegExp>
#include <QDate>
#include <QStringList>

// Constructor
TvShow::TvShow(QString name, int seas, int ep)
    : title(name), season(seas), episode(ep), info(new QuickInfo(this)), newEpisodeAvailable(false)
{
    // Create Connection to API
    info->createConnection(title);
    QObject::connect(info, SIGNAL(apiErrorOccured()), this, SIGNAL(apiError()));
    QObject::connect(info, SIGNAL(htmlErrorOccured()), this, SIGNAL(htmlErrorOccured()));
}

// Constructor for loading from database
TvShow::TvShow(QString name, int seas, int ep, QString genre, QString started, QString status, QString airtime,
               QString network, QString latestEp, QString nextEp, QString imageUrl)
    : title(name), season(seas), episode(ep), genre(genre), started(started), status(status), airtime(airtime), network(network),
      latestEpisode(latestEp), nextEpisode(nextEp), imageUrl(imageUrl) ,info(new QuickInfo(this)), newEpisodeAvailable(false)
{
    QObject::connect(info, SIGNAL(apiErrorOccured()), this, SIGNAL(apiError()));
    QObject::connect(info, SIGNAL(htmlErrorOccured()), this, SIGNAL(htmlErrorOccured()));
}

TvShow::~TvShow()
{
    delete info;
}


// when API-information is loaded, values are extracted
void TvShow::onShowInfoFilled()
{
    setTitle(info->showInfo->value("Show Name"));
    setStarted(info->showInfo->value("Started"));
    setStatus(info->showInfo->value("Status"));
    setAirtime(info->showInfo->value("Airtime"));
    setNetwork(info->showInfo->value("Network"));
    setGenre(info->showInfo->value("Genres"));
    setLatestEpisode(info->showInfo->value("Latest Episode"));
    setNextEpisode(info->showInfo->value("Next Episode"));
    setImageUrl(info->showInfo->value("Image Url"));

    // All data is loaded, now show can be added to QList
    emit allDataLoaded(this);
}

void TvShow::debugString(TvShow *show)
{
    qDebug() << show->toString();
}


// Returns Debug-String
QString TvShow::toString() const
{
    return title + " " + QString::number(season) + " " +
            QString::number(episode)+ " " + started + " " + status + " " + airtime + " " + network
            + " " + latestEpisode + " " + nextEpisode;
}

// Extracts Date Information String from NextEpisode-Member
QString TvShow::getNextEpisodeDateString() const
{
    // NextEpisode-Format: 3Letters/2digits/4digits$  [$ marks end of string]
    QRegExp rex("([A-Z|a-z]{3,3}/[0-9]{1,2}/[0-9]{4,4})$");
    int index = rex.indexIn(nextEpisode);

    if(index == -1) // Error occured try parsing: 3Letters/4digits [no Day specified]
    {
        rex = QRegExp("([A-Z|a-z]{3,3}/[0-9]{4,4})$");
        index = rex.indexIn(nextEpisode);
    }

    return rex.cap(1);
}


// Returns QDate of the next Episode of Show
QDate TvShow::getNextEpisodeDate() const
{
    QStringList dates = getNextEpisodeDateString().split('/');

    int month, day, year;

    month =  Utils::monthToInt(dates.at(0));

    if (dates.size() == 2) // Day is not specified
    {
        day   = 1;
        year  = dates.at(1).toInt();
    }
    else if (dates.size() == 3) // Day is specified
    {
        day  = dates.at(1).toInt();
        year = dates.at(2).toInt();
    }
    else
    {
        return QDate();
    }

    return QDate(year,month,day);
}


void TvShow::editShow(const QString &newName)
{
    QObject::connect(info, SIGNAL(showEdited(bool,const QString&)), this, SIGNAL(showEdited(bool,const QString&)));
    this->info->createConnection(newName);
}

void TvShow::getExtraInformation()
{
    info->createConnection(title);
}


// check if there are new episodes availabe
void TvShow::checkForNewEpisodes()
{
    // check if latestEpisode is empty
    if(latestEpisode.isEmpty())
    {
        qDebug() << "Error when checking for new Episodes: String is empty\n"
                    "Show was: "+title;
        return;
    }

    // extract Ints from latestEpisode-String
    int _season  = latestEpisode.left(2).toInt();
    int _episode = latestEpisode.mid(3,2).toInt();

    if(_season == 0 || _episode == 0) // toInt returns 0 if conversion failed
    {
        qDebug() << "Error when checking for new Episodes: String could not be converted to Int";
        return;
    }

    // Check if there are new Episodes:
    if(_season > season)
    {
        newEpisodeAvailable = true;
        return;
    }

    else {

        if(_season == season)
        {
            newEpisodeAvailable = (_episode > episode);
            return;
        }
        else
        {
            newEpisodeAvailable = false;
            return;
        }
    }
}
