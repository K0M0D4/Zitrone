#include "App.hpp"

int main(int argc, char** argv) {
    cmt::App app;
    return app.start();

    /*NFD_Init();

    nfdchar_t* savePath{};

    nfdfilteritem_t filterItem[1] {{"Project files", "ztp"}};

    nfdresult_t result{NFD_SaveDialog(&savePath, filterItem, 1, NULL, "project.ztp")};
    if(result == NFD_OKAY) {
        std::cout << "okay\n";
        NFD_FreePath(savePath);
    } else if(result == NFD_CANCEL) {
        std::cout << "cancel\n";
    } else {
        std::cout << "Error: " << NFD_GetError() << '\n';
    }

    NFD_Quit();*/
}