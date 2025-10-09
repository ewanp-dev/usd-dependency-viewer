#include "Home.h"
#include <QVBoxLayout>

HomePage::HomePage(QWidget *parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    homeLabel_ = new QLabel(R"(
██╗   ██╗███████╗██████╗         ██████╗ ███████╗██████╗ ███████╗███╗   ██╗██████╗ 
██║   ██║██╔════╝██╔══██╗        ██╔══██╗██╔════╝██╔══██╗██╔════╝████╗  ██║██╔══██╗
██║   ██║███████╗██║  ██║        ██║  ██║█████╗  ██████╔╝█████╗  ██╔██╗ ██║██║  ██║
██║   ██║╚════██║██║  ██║        ██║  ██║██╔══╝  ██╔═══╝ ██╔══╝  ██║╚██╗██║██║  ██║
╚██████╔╝███████║██████╔╝███████╗██████╔╝███████╗██║     ███████╗██║ ╚████║██████╔╝
 ╚═════╝ ╚══════╝╚═════╝ ╚══════╝╚═════╝ ╚══════╝╚═╝     ╚══════╝╚═╝  ╚═══╝╚═════╝ 
    )");
    search_ = new QLineEdit();
    search_->setPlaceholderText("Search for dependency...");
    search_->setFixedWidth(800);

    layout->addStretch();
    layout->addWidget(homeLabel_, 0, Qt::AlignmentFlag::AlignHCenter);
    layout->addWidget(search_, 0, Qt::AlignmentFlag::AlignHCenter);
    layout->addStretch();
}
