#include "interface/Application.h"
#include "interface/Globals.h"
#include <QApplication>
#include <QFontDatabase>
#include <QFont>
#include <QString>
#include <QFile>
#include <QDir>
#include <argparse/argparse.hpp>

int main (int argc, char **argv) {
    QApplication app (argc, argv);
    QApplication::setCursorFlashTime(0);

    // Argument parsing
    argparse::ArgumentParser parser("dependencyViewer");

    parser.add_argument("filePath")
        .help("launch dependency viewer interface")
        .default_value("");

    try {
        parser.parse_args(argc, argv);
    }
    catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << parser;
        return 1;
    }

    auto filePath = parser.get<std::string>("filePath");

    // interface
    DependencyViewer* viewer = new DependencyViewer(nullptr, filePath);
    viewer->show();

    return app.exec();
}
