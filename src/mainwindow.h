// SPDX-License-Identifier: GPL-3.0-only

#ifndef MainWindow_H
#define MainWindow_H

#include <QComboBox>
#include <QMainWindow>
#include <QStandardItemModel>

#define TRACK_CHANGES 1

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget* parent = 0);

  protected:
    QStandardItemModel* setComboCheckBox(QComboBox* combo, const QStringList& strList, const QString& title = QString() );
    QStandardItemModel* setComboCheckBox(QComboBox* combo, bool withTitle = false);

  private slots:
    void on_pushButton_clicked();

  private:
    Ui::MainWindow* ui;
};

#endif
