
#include "qury_cache.hpp"


namespace search{

void QuryCache::insert(std::string const& a_terms, UrlsContainer const& a_urlsStr)
{
    std::unique_lock<std::mutex> lock(m_mtx);
    try{
        m_urls[a_terms] = a_urlsStr;
    } catch(std::bad_alloc const& x){
        //nothing will happen /just cant insert new search to cache
    }
}


bool QuryCache::urls(std::string const& a_terms, UrlsContainer& a_constainer)
{
    std::unique_lock<std::mutex> lock(m_mtx);
    auto it = m_urls.find(a_terms);
    if(it == m_urls.end()){
        return false;
    }else {
        a_constainer = (*it).second;
    }
    return true;
}

}//search