#pragma once 

#include <QWidget>
#include <QHBoxLayout>

#include <Gui/Widgets/AbstractButton.h>
#include <Gui/Widgets/DropdownWidgets/Properties.h>
#include <Gui/Widgets/DropdownWidgets/Results.h>
#include <Gui/Widgets/DropdownWidgets/Sort.h>

class NavigationHeader : public QWidget
{
    public:
        NavigationHeader(QWidget* parent = nullptr);

    private:
        void showDropdown_(AbstractButton* button, QWidget* dropdown, int shift = 0); 
        QHBoxLayout* mainLayout_;
        AbstractButton* resultsList_;
        AbstractButton* sort_;
        AbstractButton* properties_;
        ResultsDropdownWidget* resultsDropdown_;
        SortDropdownWidget* sortDropdown_;
        PropertiesDropdownWidget* propertiesDropdown_;
};
