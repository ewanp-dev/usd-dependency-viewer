#include "Nodegraph.h"
#include <QVBoxLayout>
#include <QLabel>

NodegraphPage::NodegraphPage(QWidget *parent) {
    // NOTE: Just temporary stuff here
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *label = new QLabel("Nodegraph Page");

    layout->addWidget(label);
}
