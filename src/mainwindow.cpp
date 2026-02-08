// SPDX-License-Identifier: GPL-3.0-only

#include "mainwindow.h"
#include "ui_mainwindow.h"

// Build a checkable item
QStandardItem* newItem(const QString& str) {
    auto item = new QStandardItem(str);
    item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    item->setData(Qt::Unchecked, Qt::CheckStateRole);
    return item;
}

// Populate a ComboBox with checkable items using text from a list
// The optional title is set at the top of the list, and is visible when the combo is closed
QStandardItemModel* MainWindow::setComboCheckBox(QComboBox* combo, const QStringList& strList, const QString& title) {
    auto model = new QStandardItemModel;
    if (not title.isNull()) {
        model->appendRow(new QStandardItem(title));
    }
    foreach (auto str, strList) {
        model->appendRow(newItem(str));
    }
    combo->setModel(model);
    return model;
}

// Populate a ComboBox with checkable items using text from form
// if withTitle is true the fisrt item is interpreted as a title
QStandardItemModel* MainWindow::setComboCheckBox(QComboBox* combo, bool withTitle) {
    int       row   = 0;
    auto      model = new QStandardItemModel;
    const int count = combo->count();
    if (withTitle and count > 0) {
        model->appendRow(new QStandardItem(combo->itemText(row++)));
    }
    while (row < combo->count()) {
        model->appendRow(newItem(combo->itemText(row++)));
    }
    combo->setModel(model);
    return model;
}

#if TRACK_CHANGES

// counts the number of checkable items that are checked
int countSelected(QStandardItemModel* model) {
    int count = 0;
    for (int row = 0; row < model->rowCount(); row++) {
        const auto item = model->item(row, 0);
        if (item->isCheckable() and item->checkState() == Qt::Checked) {
            count++;
        }
    }
    return count;
}

// Invoked by the lambda function acting as a slot when the status of a checkable item changes.
// The title is update accordingly.
void updateTitle(QStandardItemModel* model, const QModelIndex& idx, const QString& title) {
    auto item0 = model->itemFromIndex(idx.sibling(0, 0));
    if (not item0->isCheckable()) {
        const QString fullTitle = QString("%1 (%2/%3)").arg(title).arg(countSelected(model)).arg(model->rowCount()-1);
        item0->setText(fullTitle);
    }
}

#endif

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Populate the comboBox_A with checkable items defined by a QStringList
    const QStringList strList_A = {"Rome", "Lima", "Oslo", "Kiev"};
    const auto        model_A   = setComboCheckBox(ui->comboBox_A, strList_A, "Select cities ...");
    // qDebug() << "Setup of Model_A with" << model_A->rowCount() << "rows";

    // Populate the comboBox_B with checkable items defined in the form (mainwindows.ui)
    const auto model_B = setComboCheckBox(ui->comboBox_B, true);
    // qDebug() << "Setup of Model_B with" << model_B->rowCount() << "rows";

#if TRACK_CHANGES
    connect(
        model_A, &QStandardItemModel::dataChanged, this,
        [model_A](const QModelIndex& idx, const QModelIndex&) { updateTitle(model_A, idx, "Cities selected"); });

    connect(
        model_B, &QStandardItemModel::dataChanged, this,
        [model_B](const QModelIndex& idx, const QModelIndex&) { updateTitle(model_B, idx, "Names selected"); });
#endif

}

// Prints the title (if any) and the status of each checkable item
void getComboStates(const QComboBox* combo) {
    const auto model = qobject_cast<QStandardItemModel*>(combo->model()); // didn't found better :-(
    for (int row = 0; row < model->rowCount(); row++) {
        const auto item = model->item(row, 0);
        if (item->isCheckable()) {
            qDebug() << row << item->text() << "\tis" << item->checkState();
        } else {
            qDebug() << "Title:" << item->text();
        }
    }
}

// For each ComboBox, print each item and its status
void MainWindow::on_pushButton_clicked() {
    qDebug() << "\n**** Status of items in ComboBox A ****";
    getComboStates(ui->comboBox_A);
    qDebug() << "\n**** Status of items in ComboBox B ****";
    getComboStates(ui->comboBox_B);
}
