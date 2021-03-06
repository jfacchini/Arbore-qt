#include "sharemodel.h"
#include "share.h"
#include "persist/persist.h"
#include "ipfs/ipfshash.h"

#include <QDebug>

ShareModel::ShareModel(QObject *parent) :
    QAbstractListModel(parent)
{
    foreach (Share *share, Persist::instance()->share.get_all())
    {
        addShare(share);
    }

    // FAKE DATA FOR NOW
    if(shares_.count() > 0 )
        return;

    Share *share = new Share(this);
    share->set_title("WebUI");
    share->add_hash(IpfsHash("QmXX7YRpU7nNBKfw75VG7Y1c3GwpSAGHRev67XVPgZFv9R"), Object::DIRECTORY);
    addShare(share);

    share = new Share(this);
    share->set_title("fake 2 with overly long name, like really long with a lot of letters and phrase and stuff");
    share->add_hash(IpfsHash("QmTkzDwWqPbnAh5YiV5VwcTLnGdwSNsNTn2aDxdXBFca7D"), Object::DIRECTORY);
    addShare(share);

    share = new Share(this);
    share->set_title("Example 3");
    share->add_hash(IpfsHash("QmX6gcmX2vy2gs5dWB45w8aUNynEiqGhLayXySGb7RF2TM"), Object::DIRECTORY);
    addShare(share);
}

ShareModel::~ShareModel()
{
    foreach (Share *share, shares_)
    {
        Persist::instance()->share.persist(share);
    }
}

QHash<int, QByteArray> ShareModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[ProgressRole] = "progress";
    roles[StateRole] = "state";
    roles[SizeTotalRole] = "sizeTotal";
    roles[SizeLocalRole] = "sizeLocal";
    roles[BlockTotalRole] = "blockTotal";
    roles[BlockLocalRole] = "blockLocal";
    roles[FileTotalRole] = "fileTotal";
    roles[FileLocalRole] = "fileLocal";
    return roles;
}

int ShareModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return shares_.size();
}

QVariant ShareModel::data(const QModelIndex &index, int role) const
{
    const Share *share = shares_.value(index.row(), 0);
    switch(role)
    {
    case NameRole:
        return share->title();
    case ProgressRole:
        return share->progress();
    case StateRole:
        return share->state();
    case SizeTotalRole:
        return share->size_total();
    case SizeLocalRole:
        return share->size_local();
    case BlockTotalRole:
        return share->block_total();
    case BlockLocalRole:
        return share->block_local();
    case FileTotalRole:
        return share->file_total();
    case FileLocalRole:
        return share->file_local();
    }
    return QVariant();
}

int ShareModel::count() const
{
    return shares_.size();
}

void ShareModel::addShare(QString hash)
{
    Share *share = new Share();
    share->set_title(hash);
    try
    {
        share->add_hash(IpfsHash(hash));
    }
    catch(...)
    {
        qDebug() << "Invalid hash, doing nothing";
        return;
    }

    addShare(share);
    share->start();
}

Share *ShareModel::getShare(int index)
{
    return shares_.at(index);
}

void ShareModel::removeShare(int index)
{
    Share *share = shares_.takeAt(index);
    share->remove();
}

void ShareModel::addShare(Share *share)
{
    beginInsertRows(QModelIndex(), shares_.size(), shares_.size());
    shares_.append(share);
    endInsertRows();

    connect(share, &Share::dataChanged, [this, share]()
    {
        QModelIndex index = this->index(this->shares_.indexOf(share));
        emit dataChanged(index, index);
    });

    connect(share, &Share::shareChanged, [this, share]()
    {
        QModelIndex index = this->index(this->shares_.indexOf(share));
        emit dataChanged(index, index);
    });
}
