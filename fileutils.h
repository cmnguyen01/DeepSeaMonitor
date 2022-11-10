#ifndef FILEUTILS_H
#define FILEUTILS_H
#include <string>
#include "settings.h"
#include <QJsonObject>
#include <QJsonDocument>

using std::string;

class FileUtils
{
public:
    FileUtils();
    ~FileUtils();

    static void loadSettings(Settings * settings, string filepath);
    static void saveSettings(string filepath);
    static Settings * readJson(QString filePath);
    static void writeJson(QJsonObject &jsonObject, QString filepath);
    static int verifyCredentials(string username, string password);
    static void writeToBinaryFile(QString data, QString filepath);
    static QJsonObject readDevicesFile();
};

#endif // FILEUTILS_H
