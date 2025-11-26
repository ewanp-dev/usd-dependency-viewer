#pragma once

#include <QWidget>
#include <vector>
#include <QLineEdit>
#include <QListWidget>
#include <QKeyEvent>
#include <Gui/Widgets/AbstractButton.h>

class SearchWidget : public QWidget
{
    public:
        SearchWidget(std::vector<std::string> dependencies, QWidget* parent = nullptr);

    private:
        void keyPressEvent(QKeyEvent *event) override;
        void populateDefaultList();

        QLineEdit*                 searchBar_;
        QListWidget*               results_;
        dvWidgets::AbstractButton* exitButton_;
        std::vector<std::string>   dependencies_;
};
