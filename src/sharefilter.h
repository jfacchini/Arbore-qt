#ifndef SHAREFILTER_H
#define SHAREFILTER_H

#include <QSortFilterProxyModel>
#include <QMetaType>
#include <QVariant>

class Share;

class ShareFilter : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_ENUMS(FilterType)

public:
    enum FilterType {
        ShareList,
        Inbox,
        MyShares, //Current user as creator
        ActiveShares, //Status WAITING_FOR_DL and DOWNLOAD
        Starred //Property starred into Share model
    };

public:
    explicit ShareFilter(QObject *parent = 0);
    virtual ~ShareFilter();

    Q_INVOKABLE
    Share* getShare(int);

    Q_INVOKABLE
    void addShare(QString hash);

    Q_INVOKABLE
    int count() const;

    Q_INVOKABLE
    void setFilterType(const QString&);

    bool filterShareList() const;
    bool filterInbox() const;
    bool filterMyShares() const;
    bool filterActiveShares() const;
    bool filterStarred() const;

protected:
    virtual bool filterAcceptsRow(int, const QModelIndex&) const;

private:
    FilterType current_filter_type_;
};

#endif // SHAREFILTER_H
