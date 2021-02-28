#include <nanogui/screen.h>
#include <nanogui/glutil.h>
#include <nanogui/label.h>
#include <nanogui/window.h>
#include <nanogui/layout.h>
#include <nanogui/entypo.h>
#include <nanogui/combobox.h>
#include <nanogui/slider.h>
#include <nanogui/textbox.h>
#include <nanogui/checkbox.h>
#include <nanogui/messagedialog.h>
#include <filesystem/resolver.h>
#include "pugixml.hpp"
#include <iostream>

using namespace std;

int main(int argc, char **argv){

    std::cout<<"wan jianzhou"<<std::endl;

    std::string sceneName = "";
    filesystem::path path(argv[1]);
    try {
        if (path.extension() == "xml") {
            sceneName = argv[1];
            cout << sceneName << endl;
        } else {
            cerr << "Fatal error: unknown file \"" << argv[1]
                 << "\", expected an extension of type .xml" << endl;
        }
    } catch (const std::exception &e) {
        cerr << "Fatal error: " << e.what() << endl;
        return -1;
    }

    return 0;
}