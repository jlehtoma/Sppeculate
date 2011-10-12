#ifndef TRAININGSET_H
#define TRAININGSET_H

#include <QDir>
#include <QMap>

class TrainingSet
{
public:
    TrainingSet();
    TrainingSet(const QString &path);
    ~TrainingSet();

    int count();
    QString getFilePath(int index);
    QString getFileName(int index);
    QString getRootPath();
    void readData(const QString &path);

private:
    QDir rootPath;
    QFileInfoList imageInfos;
};

#endif // TRAININGSET_H
