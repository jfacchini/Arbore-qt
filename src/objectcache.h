#ifndef OBJECTCACHE_H
#define OBJECTCACHE_H

#include <QObject>
#include <QHash>
#include "ipfs/ipfshash.h"

class Object;

class ObjectCache : public QObject
{
    // Only an Object can insert himself in the cache
    friend class Object;

    Q_OBJECT
public:
    ObjectCache();
    virtual ~ObjectCache();

    // Singleton
    static ObjectCache* instance();

public:
    bool contains(const IpfsHash &hash) const;
    Object* get(const IpfsHash &hash) const;

private:
    void insert(Object* obj);

private:
    QHash<IpfsHash, Object*> objects_;
};

#endif // OBJECTCACHE_H