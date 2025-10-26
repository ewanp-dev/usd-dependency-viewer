#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QTableView>
#include <qevent.h>
#include <QSplitter>

class TableWidget
: public QWidget
{
    public:
        TableWidget();
    private:
        void initHeader();
        void initBody();

        void onHeaderResize(int pos, int index);

        QSplitter* headerSplitter_;
        // std::vector<QSplitter*> splitters_;

        QVBoxLayout* mainLayout_;
        QHBoxLayout* columnLayout_;
        QTableView* view_;

        QWidget* body_;
        QWidget* header_;
};
