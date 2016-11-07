#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->comboBox_videoformat->addItem("best");
    ui->comboBox_videoformat->addItem("worst");

    this->FolderSelectFlag = 0;
    this->fileNameS = "";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Download_clicked()
{
    QString path = QDir::currentPath();
    qDebug() << path;
    QString cmd = path;

    cmd = doIncludePlaylist(cmd);
    cmd = doIncludeSubtitles(cmd);
    cmd = doIncludeDescription(cmd);
    cmd = outputFolder(cmd);

    qDebug() << cmd;

    runCMD(cmd);

}

QString MainWindow::doIncludePlaylist(QString cmd)
{
    QString cmdx;

    if(ui->checkBox_PlayList->isChecked())
    {
        cmdx = "\"" + cmd + "/youtube-dl\" --yes-playlist " + " -f " + ui->comboBox_videoformat->currentText() +  " " + ui->lineEdit_url->text();
    }else
    {
        cmdx = "\"" + cmd + "/youtube-dl\" --no-playlist " + " -f " + ui->comboBox_videoformat->currentText() +  " "  + ui->lineEdit_url->text();
        //cmd = "/home/bhagy/QtProjects/build-VideoDownloader-Desktop_Qt_5_7_0_GCC_64bit-Debug/youtube-dl  -f best https://www.youtube.com/watch?v=s-qXrj2JkzU";
    }
    return cmdx;
}

QString MainWindow::doIncludeSubtitles(QString cmd)
{
    QString cmdx;

    if(ui->checkBox_Subtitles->isChecked())
    {
        cmdx = cmd + " --write-auto-sub ";
    }else{
        cmdx = cmd;
    }
    return cmdx;
}

QString MainWindow::doIncludeDescription(QString cmd)
{
    QString cmdx;

    if(ui->checkBox_Description->isChecked())
    {
        cmdx = cmd + " --write-description ";
    }else{
        cmdx = cmd;
    }
    return cmdx;
}

QString MainWindow::outputFolder(QString cmd)
{
    QString cmdx;

    if(this->FolderSelectFlag == 1)
    {
        cmdx = cmd + " -o " + fileNameS + "/%(title)s-%(id)s.%(ext)s" ;
    }else{
        cmdx = cmd;
    }
    return cmdx;
}

void MainWindow::runCMD(QString cmd)
{
    QProcess *process = new QProcess;
    process->start(cmd);
    process->waitForFinished();
    QString output = process->readAllStandardOutput();
    ShowOnStatusBar(output);
    qDebug() << output;
}

void MainWindow::ShowOnStatusBar(QString output)
{
    if((output.compare(""))==0){
        ui->statusBar->showMessage("Downloading Unsuccessfull", 3000);
    }
    if(output.contains("100%")){
        ui->statusBar->showMessage("Downloading Successfull", 3000);
    }else{
        ui->statusBar->showMessage("Command Successfully executed", 3000);
    }
}

void MainWindow::on_actionUpdate_triggered()
{
    QString path = QDir::currentPath();
    QString cmd = "/youtube-dl --update";

    qDebug() << cmd;
    runCMD(cmd);
}

void MainWindow::on_actionHelp_triggered()
{
    /*
    QString path = QDir::currentPath();
    QString cmd = "/youtube-dl --update";

    qDebug() << cmd;
    runCMD(cmd);*/
}

void MainWindow::on_pushButton_clicked()
{
    QFileDialog *fd = new QFileDialog;
    fd->setFileMode(QFileDialog::Directory);
    fd->setOption(QFileDialog::ShowDirsOnly);
    QUrl fileName = fd->getExistingDirectoryUrl();
    this->fileNameS = fileName.toLocalFile();
    //qDebug() << fileName;
    ui->lineEdit_outputFolder->setText(fileName.toLocalFile());
    this->FolderSelectFlag =1;
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox msgbox;
    msgbox.setText("<h3> <font color=''blue' >A Graphical user interface for youtube-dl video downloader. </font></h3>");
    msgbox.exec();
}
