#ifndef LOCFILESYSTEMMODEL_H
#define LOCFILESYSTEMMODEL_H

#include <QFileSystemModel>
#include <QTextCodec>
#include <string>
/*!
 * \brief The LocFileSystemModel class overrides some of the default functions in QFileSystemModel to provide encoding conversion functionalities
 */
class LocFileSystemModel : public QFileSystemModel
{
public:
    LocFileSystemModel(void);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    void setEncoding(QByteArray enc);
    void setSysEncoding(QByteArray enc);
    QString utfFileName(const QModelIndex & Index)const;
private:
    QTextCodec *codec;
    QTextCodec *systemcodec;
};

#endif // LOCFILESYSTEMMODEL_H
