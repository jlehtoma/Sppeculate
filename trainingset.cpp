#include "trainingset.h"

TrainingSet::TrainingSet()
{
    rootPath = QDir("");
}

TrainingSet::TrainingSet(const QString &path)
{
    readData(path);
}

TrainingSet::~TrainingSet()
{

}

int TrainingSet::count()
{
    return imageInfos.count();
}

QString TrainingSet::getFileName(int index)
{
    if (index >= 0 && index < imageInfos.count()) {
        QFileInfo itemInfo = imageInfos.value(index);
        return itemInfo.fileName();
    }
    else {
        return QString("");
    }
}

QString TrainingSet::getFilePath(int index)
{
    if (index >= 0 && index < imageInfos.count()) {
        QFileInfo itemInfo = imageInfos.value(index);
        return itemInfo.filePath();
    }
    else {
        return QString("");
    }
}

QString TrainingSet::getRootPath()
{
    return rootPath.absolutePath();
}

void TrainingSet::readData(const QString &path)
{
    QDir tempRootPath(path);
    if (tempRootPath.exists())
    {
        rootPath = tempRootPath;
        QStringList imageFilters;

        imageFilters << "*.jpg" << "*.png" << "*.tif";
        imageInfos = rootPath.entryInfoList(imageFilters);
    }
}
