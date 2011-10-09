#include "trainingset.h"

TrainingSet::TrainingSet(const QString &path)
{
    QDir rootPath(path);
    if (rootPath.exists())
    {
        QStringList imageFilters;

        imageFilters << "*.jpg" << "*.png" << "*.tif";
        imageInfos = rootPath.entryInfoList(imageFilters);
    }
}

TrainingSet::~TrainingSet()
{

}

int TrainingSet::count()
{
    return imageInfos.count();
}

QString TrainingSet::fileName(int index)
{
    if (index >= 0 && index < imageInfos.count()) {
        QFileInfo itemInfo = imageInfos.value(index);
        return itemInfo.fileName();
    }
    else {
        return QString("");
    }
}

QString TrainingSet::filePath(int index)
{
    if (index >= 0 && index < imageInfos.count()) {
        QFileInfo itemInfo = imageInfos.value(index);
        return itemInfo.filePath();
    }
    else {
        return QString("");
    }
}
