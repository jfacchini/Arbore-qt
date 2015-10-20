#include <QDebug>

#include "sharefilter.h"
#include "sharemodel.h"
#include "share.h"

ShareFilter::ShareFilter(QObject *parent) :
    QSortFilterProxyModel(parent),
    current_filter_type_(ShareList)
{
}

ShareFilter::~ShareFilter()
{
}

bool ShareFilter::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const
{
    QModelIndex childIndex = sourceModel()->index(sourceRow, 0, sourceParent);
    const QAbstractItemModel* model = childIndex.model();


    QString shareName = model->data(childIndex, ShareModel::NameRole).value<QString>();
    Share::ShareState state = model->data(childIndex, ShareModel::StateRole).value<Share::ShareState>();

    bool isDisplayed = true;
    switch (this->current_filter_type_) {
        case ShareList:
            isDisplayed = filterShareList();
            break;
        case Inbox:
            isDisplayed = filterInbox();
            break;
        case MyShares:
            isDisplayed = filterMyShares();
            break;
        case ActiveShares:
            isDisplayed = filterActiveShares();
            break;
        case Starred:
            isDisplayed = filterStarred();
            break;
        default:
            isDisplayed = true;
    }

    QRegExp regExp = filterRegExp();
    regExp.setCaseSensitivity(Qt::CaseInsensitive);

    return shareName.contains(regExp) && (state != Share::ShareState::CREATING) && isDisplayed;
}

void ShareFilter::setFilterType(const QString& filterType)
{
    if (filterType == "FilterType.ShareList") {
        this->current_filter_type_ = ShareList;
    } else if (filterType == "FilterType.Inbox") {
        this->current_filter_type_ = Inbox;
    } else if (filterType == "FilterType.MyShares") {
        this->current_filter_type_ = MyShares;
    } else if (filterType == "FilterType.ActiveShares") {
        this->current_filter_type_ = ActiveShares;
    } else if (filterType == "FilterType.Starred") {
        this->current_filter_type_ = Starred;
    } else {
        //throw new Exception();
    }
}

bool ShareFilter::filterShareList() const
{
    return true;
}

bool ShareFilter::filterInbox() const
{
    return true;
}

bool ShareFilter::filterMyShares() const
{
    return true;
}

bool ShareFilter::filterActiveShares() const
{
    return true;
}

bool ShareFilter::filterStarred() const
{
    return true;
}

Share *ShareFilter::getShare(int index)
{
    ShareModel* model = (ShareModel*)sourceModel();
    return model->getShare(index);
}

void ShareFilter::addShare(QString hash)
{
    ShareModel* model = (ShareModel*)sourceModel();
    return model->addShare(hash);
}

int ShareFilter::count() const
{
    ShareModel* model = (ShareModel*)sourceModel();
    return model->count();
}
