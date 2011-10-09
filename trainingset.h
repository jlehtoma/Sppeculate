#ifndef TRAININGSET_H
#define TRAININGSET_H

#include <QDir>
#include <QMap>

class TrainingSet
{
public:
    TrainingSet(const QString &path);
    ~TrainingSet();

    int count();
    QString filePath(int index);
    QString fileName(int index);

private:
    QDir rootPath;
    QFileInfoList imageInfos;
};

#endif // TRAININGSET_H
