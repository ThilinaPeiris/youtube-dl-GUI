#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_Download_clicked();
    void on_actionUpdate_triggered();
    void runCMD(QString);
    QString doIncludePlaylist(QString);
    QString doIncludeSubtitles(QString);
    QString doIncludeDescription(QString);
    QString outputFolder(QString);
    void on_actionHelp_triggered();
    void ShowOnStatusBar(QString);
    void on_pushButton_clicked();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    int FolderSelectFlag;
    QString fileNameS;
};

#endif // MAINWINDOW_H
