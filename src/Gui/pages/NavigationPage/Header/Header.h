#pragma once 

#include <QWidget>
#include <QHBoxLayout>

#include "Gui/interface/AbstractButton.h"
#include "Gui/interface/widgets/dropdown/Results.h"
#include "Gui/interface/widgets/dropdown/Sort.h"
#include "Gui/interface/widgets/dropdown/Properties.h"

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
