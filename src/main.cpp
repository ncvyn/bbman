#include "eoutln.h"
#include <cstdlib>
#include <httplib.h>
#include <iostream>

int main() {
    const char* ID = std::getenv("ID");
    if (!ID) {
        return eoutln("please set ID variable for KTN xml feed");
    }

    httplib::Client cli("https://kill-the-newsletter.com");
    auto res = cli.Get("/feeds/" + std::string(ID) + ".xml");
    if (!res) {
        return eoutln(httplib::to_string(res.error()));
    }
    if (res->status != 200) {
        return eoutln("error! status code " + std::to_string(res->status));
    }

    std::cout << res->body << std::endl;

    return 0;
}
