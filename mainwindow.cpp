#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    treeModel = new LocFileSystemModel();
    QObject::connect(treeModel,SIGNAL(directoryLoaded(const QString&)),
                     this,SLOT(slot_treeModel_directoryLoaded(const QString&)));

    ui->treePreview->setSortingEnabled(true);
    ui->treePreview->setExpandsOnDoubleClick(true);


    codecs=QTextCodec::availableCodecs();
    QStringList codeclist;

    int systemindex=-1;
    int latin1index=-1;//mac doesn't have the system codec option
    int sjisindex=-1;
    for(int i=0;i<codecs.length();i++){
        QByteArray currcodec=codecs.at(i);
        codeclist.push_back(currcodec);
        if(currcodec=="System")systemindex=i;
        if(currcodec=="latin1")latin1index=i;
        if(currcodec=="Shift_JIS")sjisindex=i;
    }
    ui->cmboEnc->addItems(codeclist);
    ui->cmboSysEnc->addItems(codeclist);
    //set system codec index
    if(systemindex!=-1)ui->cmboSysEnc->setCurrentIndex(systemindex);
    else if(latin1index!=-1)ui->cmboSysEnc->setCurrentIndex(latin1index);
    //set target index
    if(sjisindex!=-1)ui->cmboEnc->setCurrentIndex(sjisindex);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete treeModel;
}

void MainWindow::rename(QDir root)
{
    QStringList files = root.entryList(QDir::Files);
    QStringList dirs = root.entryList(QDir::Dirs|QDir::NoDotAndDotDot);
    for(auto it=dirs.begin();it<dirs.end();it++){
        QString path=root.absoluteFilePath(*it);
        rename(QDir(path));
        root.rename(*it,treeModel->fileName(treeModel->index(path)));
        //qDebug()<<"Renaming "<<*it<<" to "<<treeModel->fileName(treeModel->index(path))<<", path "<<path;
    }
    for(auto it=files.begin();it<files.end();it++){
        QString path=root.absoluteFilePath(*it);
        root.rename(*it,treeModel->fileName(treeModel->index(path)));
        //qDebug()<<"Renaming "<<*it<<" to "<<treeModel->fileName(treeModel->index(path))<<", path "<<path;
    }
}

void MainWindow::on_btnBrowse_clicked()
{
    QString dir=QFileDialog::getExistingDirectory(this, "Select Folder", ui->txtFolder->text());
    if(dir!=""){
        ui->txtFolder->setText(dir);
        QModelIndex rootidx=treeModel->setRootPath(dir);
        ui->treePreview->setModel(treeModel);
        ui->treePreview->setColumnWidth(0,500);
        ui->treePreview->setRootIndex(rootidx);

        //ui->treePreview->expandToDepth(3);
        //ui->treePreview->rootIndex().row();

    }
}

void MainWindow::on_cmboSysEnc_currentIndexChanged(int index)
{
    treeModel->setSysEncoding(codecs.at(index));
}

void MainWindow::on_cmboEnc_currentIndexChanged(int index)
{
    treeModel->setEncoding(codecs.at(index));
}
void MainWindow::slot_treeModel_directoryLoaded(const QString & path){
    ui->treePreview->expandToDepth(4);
}

void MainWindow::on_btnApply_clicked()
{
    QMessageBox::StandardButton reply;
    reply=QMessageBox::question(this,"Confirmation","Are you sure you want to rename files and folders as shown in the preview?\n"
                                                     "Make sure that you have a backup in case something goes wrong! \n"
                                                     "Please confirm the path is correct before clicking Yes: \n"+ui->txtFolder->text(),
                                                        QMessageBox::Yes|QMessageBox::No);
    if(reply==QMessageBox::Yes){
        //QModelIndex idx=treeModel->index(ui->txtFolder->text());
        QDir traverseRoot=QDir(ui->txtFolder->text());
        rename(traverseRoot);
    }
}
