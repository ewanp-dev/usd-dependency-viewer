#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QTableView>
#include <qevent.h>
#include <QSplitter>
#include <qtmetamacros.h>

// NOTE: I put this class with the table widget one, we might want to move it
// to it's own file in the future. It's just a tiny wrapper to promote the resized event.
class TableWidgetHeaderSplitter
: public QSplitter
{
    Q_OBJECT
    public:
        using QSplitter::QSplitter;
    protected:
        void resizeEvent(QResizeEvent* event) override
        {
            QSplitter::resizeEvent(event);
            Q_EMIT resized();
        }
    Q_SIGNALS:
        void resized();
};

class TableWidget
: public QWidget
{
    public:
        TableWidget();
        QTableView* getView() {return view_;}
        void setModel(QAbstractItemModel* model) {view_->setModel(model);}
        // TODO: support replacing existing labels with fewer labels
        void setHorizontalHeaderLabels(const QStringList &labels);
        void onHeaderResized();
    private:
        void initHeader();
        void initBody();

        void onHeaderMoved(int pos, int index);

        TableWidgetHeaderSplitter* headerSplitter_;
        // std::vector<QSplitter*> splitters_;

        QVBoxLayout* mainLayout_;
        QHBoxLayout* columnLayout_;
        QTableView* view_;

        QWidget* body_;
        QWidget* header_;
};
