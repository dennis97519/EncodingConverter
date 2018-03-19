#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFileSystemModel>
#include <QMessageBox>
#include "locfilesystemmodel.h"
#include <iterator>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    LocFileSystemModel *treeModel;
    QList<QByteArray> codecs;
    void rename(QDir idx);
private slots:
    void on_btnBrowse_clicked();

    void on_cmboSysEnc_currentIndexChanged(int index);

    void on_cmboEnc_currentIndexChanged(int index);

    void slot_treeModel_directoryLoaded(const QString & path);

    void on_btnApply_clicked();
};

#endif // MAINWINDOW_H
