#ifndef RESOURCECACHE_H
#define RESOURCECACHE_H

#include "common.h"

template <class ResourceType>
class ResourceCache
{
public:
    ResourceType* acquire(string name) 
    {
        auto it = m_resourceMap.find(name);
        if (it != end(m_resourceMap)) {
            return it->second.get();
        }
        else {
            m_resourceMap[name] = move(loadResource(name));
            return m_resourceMap[name].get();
        }
    }
    
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
    
    virtual unique_ptr<ResourceType> loadResource(string name) = 0;
    std::map<string, unique_ptr<ResourceType>> m_resourceMap;
};

#endif // RESOURCECACHE_H
