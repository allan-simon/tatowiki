/**
This code is taken from Wikipp, need to ask for the actual licence
**/


#ifndef WIKIPP_MARKDOWN_H
#define WIKIPP_MARKDOWN_H

#include <string>

namespace mkd {
	static const int no_links     = 0x0001;  // don't do link processing, block <a> tags  
	static const int no_image     = 0x0002;  // don't do image processing, block <img> 
	static const int no_pants     = 0x0004;  // don't run smartypants() 
	static const int no_html      = 0x0008;  // don't allow raw html through at all 
	static const int strict       = 0x0010;  // disable superscript, relaxed_emphasis 
	static const int tagtext      = 0x0020;  // process text inside an html tag; no
	                                         // <em>, no <bold>, no html or [] expansion 
	static const int no_ext       = 0x0040;  // don't allow pseudo-protocols 
	static const int cdata        = 0x0080;  // generate code for xml ![cdata[...]] 
	static const int no_tables    = 0x0400;  // disallow tables 
	static const int toc          = 0x1000;  // do table-of-contents processing 
	static const int compat       = 0x2000;  // compatability with markdowntest_1.0 
	static const int autolink     = 0x4000;  // make http://foo.com link even without <>s 
	static const int safelink     = 0x8000;  // paranoid check for link protocol 
	static const int embed        = no_links|no_image|tagtext;

					  
	static const int no_header    = 0x0100;  // don't process header blocks 
	static const int tabstop      = 0x0200;  // expand tabs to 4 spaces 
};

std::string markdown_to_html(char const *str,int len,int flags);
std::string markdown_format_for_highlighting(std::string const &,std::string const &html_class);

std::string mymarkdown(std::string const &s);

#endif


