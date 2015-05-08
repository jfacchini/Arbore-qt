#include "ipfsswarm.h"
#include "ipfs/ipfs.h"

#include <QDebug>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonObject>
#include <QJsonArray>

const QString API_COMMAND = "swarm";

IpfsSwarm::IpfsSwarm(QObject *parent)
    : QObject(parent),
      valid_data_(false),
      refreshTimer_(this)
{
    connect(&refreshTimer_, SIGNAL(timeout()),
            this, SLOT(refresh_peers()));

    refreshTimer_.start(10 * 1000); // 10s
}

void IpfsSwarm::init()
{
    refresh_peers();
}

void IpfsSwarm::refresh_peers()
{
    Ipfs::instance().query(API_COMMAND + "/peers", this);

    qDebug() << "refreshing peers";
}

void IpfsSwarm::on_reply(const QJsonObject *json)
{
    peers_.clear();
    foreach (const QJsonValue &value, json->value("Strings").toArray())
    {
        peers_ << IpfsPeer(value.toString());
    }
    valid_data_ = true;
}

bool IpfsSwarm::valid_data() const
{
    return valid_data_;
}

const QList<IpfsPeer> &IpfsSwarm::peers() const
{
    return peers_;
}
