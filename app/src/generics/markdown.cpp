/**
This code is taken from Wikipp, need to ask for the actual licence
**/


#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <stdexcept>
#include <cppcms/xss.h>
#include "markdown.h"

extern "C" {
	#include <mkdio.h>
}

/**
 *
 */
cppcms::xss::rules const &xss_filter() {
    static cppcms::xss::rules r;
    static bool initialized = false;
    if(initialized) {
        return r;
    }
    using namespace cppcms::xss;

    r.html(rules::xhtml_input);
    r.add_tag("ol",rules::opening_and_closing);
    r.add_tag("ul",rules::opening_and_closing);
    r.add_tag("li",rules::opening_and_closing);
    r.add_tag("p",rules::opening_and_closing);
    r.add_property("p","style",booster::regex("\\s*text-align\\s*:\\s*(center|left|right)\\s*;?"));
    r.add_tag("b",rules::opening_and_closing);
    r.add_tag("i",rules::opening_and_closing);
    r.add_tag("tt",rules::opening_and_closing);
    r.add_tag("sub",rules::opening_and_closing);
    r.add_tag("sup",rules::opening_and_closing);
    r.add_tag("blockquote",rules::opening_and_closing);
    r.add_tag("strong",rules::opening_and_closing);
    r.add_tag("em",rules::opening_and_closing);
    r.add_tag("h1",rules::opening_and_closing);
    r.add_tag("h2",rules::opening_and_closing);
    r.add_tag("h3",rules::opening_and_closing);
    r.add_tag("h4",rules::opening_and_closing);
    r.add_tag("h5",rules::opening_and_closing);
    r.add_tag("h6",rules::opening_and_closing);
    booster::regex cl_id(".*");
    r.add_property("h1","id",cl_id);
    r.add_property("h2","id",cl_id);
    r.add_property("h3","id",cl_id);
    r.add_property("h4","id",cl_id);
    r.add_property("h5","id",cl_id);
    r.add_property("h6","id",cl_id);
    r.add_tag("span",rules::opening_and_closing);
    r.add_property("span","id",cl_id);
    r.add_tag("code",rules::opening_and_closing);
    r.add_tag("pre",rules::opening_and_closing);
    r.add_property("pre","name",booster::regex("\\w+"));
    r.add_property("pre","class",booster::regex("\\w+"));
    
    // rules for a tag
    r.add_tag("a",rules::opening_and_closing);
    r.add_uri_property(
        "a",
        "href",
        "(http|https|irc|xmpp)"
    );
    r.add_property("a","name",cl_id);
    r.add_property("a","title",cl_id);

    r.add_tag("hr",rules::stand_alone);
    r.add_tag("br",rules::stand_alone);
    
    // rules for the img tag
    r.add_tag("img",rules::stand_alone);
    r.add_uri_property("img","src");
    r.add_property("img","title",cl_id);
    r.add_integer_property("img","width");
    r.add_integer_property("img","height");
    r.add_integer_property("img","border");
    r.add_property("img","alt",booster::regex(".*"));
    
    r.add_tag("table",rules::opening_and_closing);
    r.add_tag("tr",rules::opening_and_closing);
    r.add_tag("th",rules::opening_and_closing);
    r.add_tag("td",rules::opening_and_closing);
    r.add_integer_property("table","cellpadding");
    r.add_integer_property("table","cellspacing");
    r.add_integer_property("table","border");
    r.add_tag("center",rules::opening_and_closing);
    r.add_entity("nbsp");
    r.encoding("UTF-8");
    r.comments_allowed(true);

    initialized = true;
    return r;
}

/**
 *
 */
struct init_it {
    init_it() {
        xss_filter();
    }
} instance;

/**
 *
 */
std::string markdown_to_html(char const *str,int len,int flags)
{
	/// It is safe to const cast as mkd_string does not 
	/// alter original string
	MMIOT *doc = mkd_string(const_cast<char *>(str),len,flags);
	if(!doc) {
		throw std::runtime_error("Failed to read document");
	}

	mkd_compile(doc,flags);
	
	std::string result;
	result.reserve(len);
	char *content_ptr = 0;
	int content_size = 0;
	char *toc_ptr = 0;

	content_size = mkd_document(doc,&content_ptr);
	if(flags & mkd::toc) {
		int toc_size = mkd_toc(doc,&toc_ptr);
		result.assign(toc_ptr,toc_size);
	}
	result.append(content_ptr,content_size);
	free(toc_ptr);
	mkd_cleanup(doc);

	return result;
}


//TODO move it somewhere else
// HACK!

std::string mymarkdown(std::string const &s)
{
    int flags = mkd::no_pants;
    if(s.compare(0,10,"<!--toc-->")==0) {
        flags |= mkd::toc;
    }

    std::string html = markdown_to_html(
        s.c_str(),
        s.size(),flags
    );
    
	return cppcms::xss::filter(
        html,
        xss_filter(),
        cppcms::xss::escape_invalid
    );
};



