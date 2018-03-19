#include "locfilesystemmodel.h"

LocFileSystemModel::LocFileSystemModel(void)
{
    codec=nullptr;
    systemcodec=nullptr;
}

QVariant LocFileSystemModel::data(const QModelIndex &index, int role) const{
    QVariant dat=QFileSystemModel::data(index,role);

    if(role==Qt::DisplayRole&&codec&&systemcodec)
    {
        QByteArray str=systemcodec->fromUnicode(dat.toString());
        dat=QVariant(codec->toUnicode(str));
    }
    return dat;
}

void LocFileSystemModel::setEncoding(QByteArray enc){
    codec=QTextCodec::codecForName(enc);
    QFileSystemModel::layoutChanged();
}
void LocFileSystemModel::setSysEncoding(QByteArray enc){
    systemcodec=QTextCodec::codecForName(enc);
    QFileSystemModel::layoutChanged();
}
QString LocFileSystemModel::utfFileName(const QModelIndex & Index)const{
    QString name=QFileSystemModel::fileName(Index);
    QByteArray str=systemcodec->fromUnicode(name);
    QString utfName=codec->toUnicode(str);
    return utfName;
}
