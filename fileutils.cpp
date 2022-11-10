#include "fileutils.h"
#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QDataStream>

using std::string;
using namespace std;

FileUtils::FileUtils()
{

}

FileUtils::~FileUtils()
{

}

void FileUtils::loadSettings(Settings * settings, string filepath)
{
    ifstream myFile;
    string line;

    myFile.open(filepath);


    if(myFile.is_open())
    {
        cout << "Opened successfully" << endl;

        getline(myFile, line);
        settings->upperBound = atof(line.c_str());

        getline(myFile, line);
        settings->lowerBound = atof(line.c_str());

        getline(myFile, line);
        settings->lowerThreshold = atof(line.c_str());

        getline(myFile, line);
        settings->upperThreshold = atof(line.c_str());
    }
    else
    {
        cout << "Didn't open" << endl;
    }


    myFile.close();
}

void FileUtils::saveSettings(string filepath)
{
    ofstream myfile;
    myfile.open(filepath);
    myfile << "Writing this to a file.\n";
    myfile.close();
}

// Function that checks the user.txt file and verifies if a username exists,
// and if the password for that username is correct.
// Returns 1 if it successfully verifies the user
// returns 0 otherwise
int FileUtils::verifyCredentials(string username, string password)
{
    string filepath = "/Users/vitaliytrach/HardwareMonitor/users.txt";

    ifstream myFile;
    string line;

    myFile.open(filepath);

    if(myFile.is_open())
    {
        while(!myFile.eof())
        {
            getline(myFile, line);

            if(line.compare(username) == 0)
            {
                string pass;
                getline(myFile, pass);

                if(pass.compare(password) == 0)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
        }
    }
    else
    {
        cout << "Didn't open" << endl;
    }

    myFile.close();
    return 0;
}

Settings * FileUtils::readJson(QString filePath)
{
    Settings * settings = new Settings();
    QString fileData;
    QFile file(filePath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    fileData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(fileData.toUtf8());
    QJsonObject obj = doc.object();

    settings->lowerBound = obj["Lower Bound"].toString().toDouble();
    settings->upperBound = obj["Upper Bound"].toString().toDouble();
    settings->lowerThreshold = obj["Lower Threshold"].toString().toDouble();
    settings->upperThreshold = obj["Upper Threshold"].toString().toDouble();

    return settings;
}

void FileUtils::writeJson(QJsonObject &jsonObject, QString filepath)
{
    QFile saveFile(filepath);
    saveFile.open(QFile::WriteOnly);
    QJsonDocument saveDoc(jsonObject);
    saveFile.write(saveDoc.toJson());
}

void FileUtils::writeToBinaryFile(QString data, QString filepath)
{
    filepath = "/Users/vitaliytrach/Desktop/School/Capstone2/capstone/outputs/test.dat";
    QFile file(filepath);
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QDataStream out(&file);
    out << data;
    file.close();
}

QJsonObject FileUtils::readDevicesFile()
{
    QString filepath = "/Users/vitaliytrach/Desktop/School/Capstone2/capstone/config/config.json";
    QString fileData;
    QFile file(filepath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    fileData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(fileData.toUtf8());
    return doc.object();
}

