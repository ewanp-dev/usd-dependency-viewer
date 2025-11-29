#include <QApplication>
#include <QFontDatabase>
#include <QFont>
#include <QString>
#include <QFile>
#include <QDir>
#include <Gui/MainWindow/Application.h>
#include <Gui/MainWindow/Globals.h>
#include <argparse/argparse.hpp>

int main(int argc, char **argv)
{
    QApplication::setDesktopSettingsAware(false);
    QApplication app(argc, argv);
    QApplication::setCursorFlashTime(0);

    argparse::ArgumentParser parser("dependencyViewer");

    parser.add_argument("filePath")
          .help("launch dependency viewer interface")
          .default_value("");

    try 
    {
        parser.parse_args(argc, argv);
    } catch (const std::exception& err) 
    {
        std::cerr << err.what() << std::endl;
        std::cerr << parser;
        return 1;
    }

    auto filePath = parser.get<std::string>("filePath");

    DependencyViewer* viewer = new DependencyViewer(filePath);
    viewer->show();

    return app.exec();
}
