#include "locfilesystemmodel.h"

LocFileSystemModel::LocFileSystemModel(void)
{
    codec=nullptr;
    systemcodec=nullptr;
}
/*!
 * \brief LocFileSystemModel::data overrides the default data function to return decoded file names
 * \param index model index
 * \param role role of data
 * \return decoded data
 */
QVariant LocFileSystemModel::data(const QModelIndex &index, int role) const{
    QVariant dat=QFileSystemModel::data(index,role);//get data from base class
    //did I want to add some other check here?
    if(role==Qt::DisplayRole&&codec&&systemcodec){
        QByteArray str=systemcodec->fromUnicode(dat.toString());
        QByteArray cname=systemcodec->name();
        if(cname=="UTF-16"||cname=="UTF-16LE"||cname=="UTF-16BE"){
            str.remove(0,2);//remove byte order mark
        }
        else if(cname=="UTF-32"||cname=="UTF-32LE"||cname=="UTF-32BE"){
            str.remove(0,4);//remove byte order mark
        }
        dat=QVariant(codec->toUnicode(str));
    }
    return dat;
}
/*!
 * \brief LocFileSystemModel::setEncoding sets the actual encoding of filenames
 * \param enc The name of the encoding in a string form
 */
void LocFileSystemModel::setEncoding(QByteArray enc){
    codec=QTextCodec::codecForName(enc);
    QFileSystemModel::layoutChanged();//update display
}
/*!
 * \brief LocFileSystemModel::setSysEncoding sets the encoding that the operating system is interpreting the filenames in
 * \param enc The name of the encoding in a string form
 */
void LocFileSystemModel::setSysEncoding(QByteArray enc){
    systemcodec=QTextCodec::codecForName(enc);
    QFileSystemModel::layoutChanged();//update display
}
