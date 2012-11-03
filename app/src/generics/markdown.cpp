/**
This code is taken from Wikipp, need to ask for the actual licence
**/


#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <stdexcept>
#include "markdown.h"

extern "C" {
	#include <mkdio.h>
}

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


std::string markdown_format_for_highlighting(std::string const &input,std::string const &html_class)
{
	enum { part_a , part_b } state = part_a;
	std::string repla = "<pre name=\"code\" class=\"" + html_class + "\">";
	std::string replb = "</pre>";
	std::string origa="<pre><code>";
	std::string origb="</code></pre>";
	std::string result;
	result.reserve(input.size());
	size_t pos = 0;
	while(pos < input.size()) {
		std::string const &orig = state == part_a ? origa : origb;
		std::string const &repl = state == part_a ? repla : replb;
		size_t next = input.find(orig,pos);
		if(next == std::string::npos)
			next = input.size();
		result.append(input.data() + pos, next - pos);
		if(next < input.size()) {
			result.append(repl);
			pos = next + orig.size();
			if(state == part_a)
				state = part_b;
			else
				state = part_a;
		}
		else {
			pos = next;
		}
	}
	return result;
}
