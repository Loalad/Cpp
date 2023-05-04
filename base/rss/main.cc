#include <iostream>
#include "tinyxml2.h"
#include <regex>
#include <vector>
#include <fstream>

using std::ofstream;
using std::vector;
using std::cout;
using std::endl;
using std::string;
using namespace tinyxml2;

struct RssItem {
    string title;
    string link;
    string description;
    string content;
};

class RssReader{
public:
    RssReader(){};
    void parseRss();//解析
    void dump(const string & filename);//输出
private:
    vector<RssItem> _rss;
};  

void RssReader::parseRss () {
    XMLDocument doc;
    doc.LoadFile("coolshell.xml");

    XMLElement *root = doc.FirstChildElement("rss");
    XMLElement *itemElement = root->FirstChildElement("channel")->FirstChildElement("item");

    do {
        struct RssItem item;

        XMLElement *titleElement = itemElement->FirstChildElement("title");
        item.title = titleElement->GetText();

        XMLElement *linkElement = itemElement->FirstChildElement("link");
        item.link = linkElement->GetText();
        
        XMLElement *descriptionElment = itemElement->FirstChildElement("description");
        item.description = descriptionElment->GetText();

        XMLElement *contentElement = itemElement->FirstChildElement("content:encoded");
        item.content = contentElement->GetText();
        std::regex re("<.*?>");
	    std::string origin(item.content);
        item.content = std::regex_replace(item.content, re, string(""));

        _rss.push_back(item);
        
    } while (itemElement = itemElement->NextSiblingElement("item"));

}

void RssReader::dump (const string &filename) {
    ofstream ofs(filename, std::ios::app);
    if (!ofs) {
        cout << "open file failed" << endl;
        return;
    }
    for(int i = 0; i < _rss.size(); ++i){
        ofs << "<doc>" << endl;
        ofs << "   <docid>" << i + 1 << "</docid>";
        ofs << "\n   <title>";
        ofs << _rss[i].title << "</title>";
        ofs << "\n   <link>";
        ofs << _rss[i].link << "</link>";
        ofs << "\n   <description>";
        ofs << _rss[i].description << "</description>";
        ofs << "\n   <content>";
        ofs << _rss[i].content << "</content>";
        ofs << "\n</doc>" << endl;
    }
    ofs.close();
}

int main () {
    RssReader rss;
    rss.parseRss();
    rss.dump("pagelib.txt");
    return 0;
}

void test () {
    XMLDocument doc;
    doc.LoadFile("coolshell.xml");

    XMLElement *root = doc.FirstChildElement("rss");
    XMLElement *itemElement = root->FirstChildElement("channel")->FirstChildElement("item");

    XMLElement *titleElement = itemElement->FirstChildElement("title");
    const char *title = titleElement->GetText();
    cout << "title:" << title << endl;

    XMLElement *linkElement = itemElement->FirstChildElement("link");
    const char *link = linkElement->GetText();
    cout << "link:" << link << endl;

    XMLElement *descriptionElement = itemElement->FirstChildElement("description");
    const char *description = descriptionElement->GetText();
    //cout << "description:" << description << endl;

    XMLElement *contentElement = itemElement->FirstChildElement("content:encoded");
    const char *content = contentElement->GetText();
    //cout << "content:" << content << endl << endl;

    std::regex re("<.*?>");
	std::string origin(content);
	cout << "content:" << std::regex_replace(origin, re, string(""));
}

