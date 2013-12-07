#ifndef RESOURCECACHE_H
#define RESOURCECACHE_H

#include "common.h"

template <class ResourceType>
class ResourceCache
{
public:
    void remove(string name) 
    {
        m_resourceMap.erase(name);
    }

    void purge() 
    {
        m_resourceMap.clear();
    }
    
protected:
    ResourceCache() {}
    virtual ~ResourceCache() {}
    ResourceCache(const ResourceCache&) {}
    ResourceCache& operator=(const ResourceCache&) {}
    
    ResourceType* getResource(string name) {
        auto it = m_resourceMap.find(name);
        if (it != end(m_resourceMap)) {
            return it->second.get();
        }
        else {
            return NULL;
        }
    }
    
    void addResource(string name, ResourceType* p) {
        m_resourceMap[name] = move(unique_ptr<ResourceType>(p));
    }
    
    std::map<string, unique_ptr<ResourceType>> m_resourceMap;
};

#endif // RESOURCECACHE_H
