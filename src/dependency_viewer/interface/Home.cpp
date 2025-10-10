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
    search_->setPlaceholderText("> Search for dependency...");
    search_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    search_->setMaximumWidth(QWIDGETSIZE_MAX);
    search_->setMinimumWidth(650);
    search_->setFixedHeight(40);
    search_->setCursor(Qt::CursorShape::IBeamCursor);

    layout->addStretch();
    layout->addWidget(homeLabel_, 0, Qt::AlignmentFlag::AlignHCenter);
    layout->addWidget(search_, 0, Qt::AlignmentFlag::AlignHCenter);
    layout->addStretch();

    homeLabel_->setStyleSheet(R"(
        QLabel {
            color: rgb(210, 210, 210);
        }
    )");

    search_->setStyleSheet(R"(
        QLineEdit {
            background-color: rgb(40, 40, 40);
            color: rgb(210, 210, 210);
            padding-left: 6px;
            padding-right: 6px;
            border-radius: 0px;
        }
    )");
}
