#include "eoutln.h"
#include <cstdlib>
#include <httplib.h>
#include <iostream>

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

    std::cout << res->body << std::endl;

    return 0;
}
