#pragma once
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <RTC3231.h>

class LogFile {

public:

    LogFile(FS *fileStorage, String serviceName);
    LogFile(FS *fileStorage, String serviceName, String FilePath);
    LogFile(FS *fileStorage, String serviceName, String FilePath, int maxFileSizeBytes);
    LogFile(FS *fileStorage, String serviceName, String FilePath, int maxFileSizeBytes, int maxRecordsInFile);
    LogFile(FS *fileStorage, String serviceName, String FilePath, int maxFileSizeBytes, int maxRecordsInFile, String archivePath);
    ~LogFile();
    void init(RTC3231 *rtc);
    void createFile();
    // void copyFile();
    // void moveFile(String destFolder);
    void openFile();
    void closeFile();
    void deleteFile();
    void archiveFile();
    void rotateFile();
    void writeString(String logString);
    void logString(String logString);

private:
    fs::FS *fileStorage;
    String filePath = "/";
    String fileFullPath = "";
    String archivePath = "/archive";
    String serviceName;
    String currFileName;
    fs::File file;

    int recordsCounter = 0;
    int maxRecordsInFile = 10000;
    int maxFileSizeBytes = 209715200; // 200 Mb
    RTC3231 *rtc;
};
