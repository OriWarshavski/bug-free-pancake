#include <assert.h>
#include <boost/regex.hpp>

#include "gumbo.h"
#include "parser.hpp"
#include "search_word_protocol.hpp"

namespace crawl {

namespace {

std::string cleanText(GumboNode* a_node) 
{
    if(a_node->type == GUMBO_NODE_TEXT) {
        return std::string(a_node->v.text.text);
    } else if (a_node->type == GUMBO_NODE_ELEMENT &&
    a_node->v.element.tag != GUMBO_TAG_SCRIPT &&
    a_node->v.element.tag != GUMBO_TAG_STYLE) {

        std::string contents = "";
        GumboVector* children = &a_node->v.element.children;

        for (unsigned int i = 0; i < children->length; ++i) {
            const std::string text = cleanText((GumboNode*) children->data[i]);
            if (i != 0 && !text.empty()) {
                contents.append(" ");
            }
        contents.append(text);
        }
    return contents;
  } else {
    return "";
  }
}

void findHead(const GumboNode* a_root, GumboNode** a_head) 
{
    const GumboVector* rootChildren = &a_root->v.element.children;
    for (unsigned int i = 0; i < rootChildren->length; ++i) {
        GumboNode* child = static_cast<GumboNode*>(rootChildren->data[i]);
        if (child->type == GUMBO_NODE_ELEMENT &&
            child->v.element.tag == GUMBO_TAG_HEAD) {
            *a_head = child;
            break;
        }
    }
}

std::string findTitle(GumboNode* a_root) 
{
    assert(a_root->type == GUMBO_NODE_ELEMENT);
    assert(a_root->v.element.children.length >= 2);

    GumboNode* head = nullptr;
    findHead(a_root, &head);
    assert(head != nullptr);
    if(head == nullptr) {
        return std::string{""};
    }

    GumboVector* headChildren = &head->v.element.children;
    for (unsigned int i = 0; i < headChildren->length; ++i) {
        GumboNode* child = static_cast<GumboNode*>(headChildren->data[i]);
        if (child->type == GUMBO_NODE_ELEMENT &&
            child->v.element.tag == GUMBO_TAG_TITLE) {
            if (child->v.element.children.length != 1) {
                return std::string{""};
            }

            GumboNode* titleText = static_cast<GumboNode*>(child->v.element.children.data[0]);
            assert(titleText->type == GUMBO_NODE_TEXT || titleText->type == GUMBO_NODE_WHITESPACE);
            return titleText->v.text.text;
        }
    }
    return std::string{""};
}


std::string normalizeUrl(const std::string& a_currentUrl, const std::string& a_otherUrl) {
    if (a_otherUrl.empty()) {
        return a_currentUrl;
    }

    // Check if URL starts with "#"
    if (a_otherUrl[0] == '#') {
        return a_currentUrl;
    }
    
    if(a_otherUrl.size() > 2) {
        if(a_otherUrl[0] == '/' && a_otherUrl[1] == '/') {
            return std::string{"https:"} + a_otherUrl;
        }
    }
   
    // Check if URL is relative
    boost::regex relUrlRegex("^(?!https?://)(.*)$");
    boost::smatch relUrlMatch;
    if (boost::regex_match(a_otherUrl, relUrlMatch, relUrlRegex)) {
        // Get the scheme and host from the current URL
        boost::regex currUrlRegex("^(https?://[^/]+)");
        boost::smatch currUrlMatch;
        if (boost::regex_search(a_currentUrl, currUrlMatch, currUrlRegex)) {
            std::string scheme_and_host = currUrlMatch[1];

            // Construct the normalized URL by appending the relative URL to the scheme and host
            return scheme_and_host + "" + relUrlMatch[1];
        } else {
            return a_otherUrl;
        }
    }
    return a_otherUrl;
}

void searchLinks(std::string const& a_currentUrl, GumboNode* a_node, std::vector<std::string> & a_url, ConditionFunction a_function) 
{
    if (a_node->type != GUMBO_NODE_ELEMENT) {
        return;
    }
    GumboAttribute* href;
    if (a_node->v.element.tag == GUMBO_TAG_A &&
    (href = gumbo_get_attribute(&a_node->v.element.attributes, "href"))) {
        std::string link{href->value};
        link = normalizeUrl(a_currentUrl, link);
        if(a_function(link)) {
            a_url.emplace_back(link);
        }
    }

    GumboVector* children = &a_node->v.element.children;
    for (unsigned int i = 0; i < children->length; ++i) {
        searchLinks(a_currentUrl,static_cast<GumboNode*>(children->data[i]), a_url, a_function);
    }
}

} // namespace




void Parser::links(std::string const& a_currentUrl, std::ostringstream const & a_content, std::vector<std::string>& a_urls, ConditionFunction a_function) const
{
    std::string contents{a_content.str()};
    GumboOutput* output = gumbo_parse(contents.c_str());

    searchLinks(a_currentUrl, output->root, a_urls, a_function);
    gumbo_destroy_output(&kGumboDefaultOptions, output);
}

void Parser::words(std::ostringstream const & a_content, Container& a_words) const
{   
    std::string contents{a_content.str()};
    GumboOutput* output = gumbo_parse(contents.c_str());

    std::string allWords = cleanText(output->root);

    std::istringstream issWords(allWords);
    std::string word;
    
    while (issWords >> word) {
        std::string cWord = words::normalizeWord(word);
        if(cWord.length() > 0) {
            a_words.emplace_back(cWord);
        } 
    }
    gumbo_destroy_output(&kGumboDefaultOptions, output);
}

std::string Parser::title(std::ostringstream const &a_content) const
{
    std::string contents{a_content.str()};
    GumboOutput* output = gumbo_parse(contents.c_str());
    std::string title = findTitle(output->root);
    gumbo_destroy_output(&kGumboDefaultOptions, output);
    return title;
}

std::string Parser::extractSite(std::string const& a_url)
{   
    std::string site;
    boost::regex re("(https?://)?(www\\.)?([a-zA-Z0-9\\-]+\\.[a-zA-Z]{2,63})");
    boost::smatch match;
    if (boost::regex_search(a_url, match, re)) {
        site = match[3];
    }
    return site;
}

} // namespace crawl
