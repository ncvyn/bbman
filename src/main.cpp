#include <cstdlib>
#include <httplib.h>
#include <iostream>

int main() {
    const char* ID = std::getenv("ID");
    if (!ID) {
        std::cerr << "error! please set ID variable for KTN xml feed"
                  << std::endl;
        return 1;
    }

    httplib::Client cli("https://kill-the-newsletter.com");
    auto res = cli.Get("/feeds/" + std::string(ID) + ".xml");
    if (!res) {
        std::cerr << "error! " << httplib::to_string(res.error()) << std::endl;
        return 1;
    }
    if (res->status != 200) {
        std::cerr << "error! status code " << res->status << std::endl;
        return 1;
    }

    std::cout << res->body << std::endl;

    return 0;
}
