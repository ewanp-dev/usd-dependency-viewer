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
        void showDropdown_(dvWidgets::AbstractButton* button, QWidget* dropdown, int shift = 0); 
        QHBoxLayout* mainLayout_;
        dvWidgets::AbstractButton* resultsList_;
        dvWidgets::AbstractButton* sort_;
        dvWidgets::AbstractButton* properties_;
        ResultsDropdownWidget* resultsDropdown_;
        SortDropdownWidget* sortDropdown_;
        PropertiesDropdownWidget* propertiesDropdown_;
};
