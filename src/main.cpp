#include "eoutln.h"
#include <cstdlib>
#include <httplib.h>
#include <iostream>
#include <tinyxml2.h>

int main() {
    // The feed identifier, obtained from https://kill-the-newsletter.com.
    const char* KTN_FEED_ID = std::getenv("KTN_FEED_ID");
    if (!KTN_FEED_ID) {
        return eoutln("KTN_FEED_ID not set");
    }

    httplib::Client cli("https://kill-the-newsletter.com");
    auto res = cli.Get("/feeds/" + std::string(KTN_FEED_ID) + ".xml");
    if (!res) {
        return eoutln(httplib::to_string(res.error()));
    }
    if (res->status != 200) {
        return eoutln("status code " + std::to_string(res->status));
    }

    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError xmlError = doc.Parse(res->body.c_str());
    if (xmlError != tinyxml2::XML_SUCCESS) {
        return eoutln(tinyxml2::XMLDocument::ErrorIDToName(xmlError));
    }

    tinyxml2::XMLElement* entry =
        doc.FirstChildElement("feed")->FirstChildElement("entry");
    if (!entry) {
        return eoutln("no entries found");
    }

    while (entry) {
        const tinyxml2::XMLText* titleElement =
            entry->FirstChildElement("title")->FirstChild()->ToText();
        if (!titleElement) {
            return eoutln("weirdly enough, no title in entry");
        }

        const std::string title = std::string(titleElement->Value());
        if (title.find("due soon") == std::string::npos ||
            title.find("New Assignment") == std::string::npos) {
            continue;
        }

        const tinyxml2::XMLText* html =
            entry->FirstChildElement("content")->FirstChild()->ToText();
        if (!html) {
            return eoutln("weirdly enough, no content in entry");
        }
        std::cout << html->Value() << std::endl;
        entry = entry->NextSiblingElement("entry");
    }

    return 0;
}
