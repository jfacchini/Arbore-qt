#include "ipfsswarm.h"
#include "ipfs/ipfs.h"

#include <QDebug>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonObject>
#include <QJsonArray>

const QString API_URL = "http://127.0.0.1:5001/api/v0/swarm/";

IpfsSwarm::IpfsSwarm(QObject *parent)
    : IpfsCommand(parent)
{
}

void IpfsSwarm::init()
{
    refresh_peers();
}

void IpfsSwarm::refresh_peers()
{
    QUrl url = API_URL + "peers";

    Ipfs::instance().query(url, this);
}

void IpfsSwarm::on_reply(const QJsonObject *json)
{
    peers_.clear();
    foreach (const QJsonValue &value, json->value("Strings").toArray())
    {
        peers_ << IpfsPeer(value.toString());
    }
}

const QList<IpfsPeer> &IpfsSwarm::peers() const
{
    return peers_;
}