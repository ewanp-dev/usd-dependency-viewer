#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QTableView>
#include <qevent.h>
#include <QSplitter>
#include <qtmetamacros.h>

class TableWidgetHeaderSplitter
: public QSplitter
{
    Q_OBJECT
    public:
        using QSplitter::QSplitter;
    protected:
        void resizeEvent(QResizeEvent *) override;
    Q_SIGNALS:
        void resized();
};

class TableWidget
: public QWidget
{
    public:
        TableWidget();
    private:
        void initHeader();
        void initBody();

        void onHeaderMoved(int pos, int index);
        void onHeaderResized();

        TableWidgetHeaderSplitter* headerSplitter_;
        // std::vector<QSplitter*> splitters_;

        QVBoxLayout* mainLayout_;
        QHBoxLayout* columnLayout_;
        QTableView* view_;

        QWidget* body_;
        QWidget* header_;
};
