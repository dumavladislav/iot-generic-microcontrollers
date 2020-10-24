#include <LogFile.h>

LogFile::LogFile(FS *fileStorage, String serviceName) {
  this->fileStorage = fileStorage;
  this->serviceName = serviceName;
}

LogFile::LogFile(FS *fileStorage, String serviceName, String filePath) {
  this->fileStorage = fileStorage;
  this->serviceName = serviceName;
  this->filePath = filePath;
}

LogFile::LogFile(FS *fileStorage, String serviceName, String filePath, int maxFileSizeBytes) {
  this->fileStorage = fileStorage;
  this->serviceName = serviceName;
  this->filePath = filePath;
  this->maxFileSizeBytes = maxFileSizeBytes;
}

LogFile::LogFile(FS *fileStorage, String serviceName, String filePath, int maxFileSizeBytes, int maxRecordsInFile) {
  this->fileStorage = fileStorage;
  this->serviceName = serviceName;
  this->filePath = filePath;
  this->maxFileSizeBytes = maxFileSizeBytes;
  this->maxRecordsInFile = maxRecordsInFile; 
}

LogFile::LogFile(FS *fileStorage, String serviceName, String filePath, int maxFileSizeBytes, int maxRecordsInFile, String archivePath) {
  this->fileStorage = fileStorage;
  this->serviceName = serviceName;
  this->filePath = filePath;
  this->maxFileSizeBytes = maxFileSizeBytes;
  this->maxRecordsInFile = maxRecordsInFile; 
  this->archivePath = archivePath; 
}

LogFile::~LogFile() {
  closeFile();
}

void LogFile::init(RTC3231 *rtc) {
  this->rtc = rtc;
  fileFullPath = String(filePath + "/" + serviceName);

  if(fileStorage->exists(fileFullPath)) {
    archiveFile();
  }

  createFile();

  /*
  if (SD.exists("/fcntr.txt")) {
    Serial.println("Reading fileCounter");
    File fileCounterFile = SD.open("/fcntr.txt");

    // if the file is available, write to it:
    if (fileCounterFile) {
      int i = 0;
      byte fileContent[20];
      while (fileCounterFile.available()) {
        fileContent[i] = fileCounterFile.read();
        i++;
        //Serial.write(dataFile.read());
      }
      fileCounterFile.close();
      if(i > 0) filesCounter = atoi((char*)fileContent);
      Serial.println("Files Counter:");
      Serial.println(filesCounter);
    }
    // if the file isn't open, pop up an error:
    else {
      Serial.println("error opening fcntr.txt");
    }
  }
  else { 
    Serial.println("Creating fcntr");
    filesCounter = 0;
    fileCounterFile = SD.open("/fcntr.txt", FILE_WRITE);
    fileCounterFile.println(filesCounter);
    fileCounterFile.close();
    if (SD.exists("/fcntr.txt")) Serial.println("fcntr.txt created");
  }
  */
}

void LogFile::createFile() {
  Serial.print("CREATING FILE: ");
  
  // currFileName = String(fileName + "_" + rtc->getTimeStamp());
  

  Serial.println(fileFullPath);

  if(!fileStorage->exists(filePath)) {
    Serial.print("CREATING FOLDER: ");
    Serial.println(filePath);
    fileStorage->mkdir(filePath);
  }

  if(!fileStorage->exists(archivePath)) {
    Serial.print("CREATING FOLDER: ");
    Serial.println(archivePath);
    fileStorage->mkdir(archivePath);
  }

  // openFile();

}

void LogFile::openFile() {
  // Serial.print("OPENING FILE... ");
  recordsCounter = 0;
  if(!fileStorage->exists(fileFullPath))
    file = fileStorage->open(fileFullPath, FILE_WRITE);
  else
    file = fileStorage->open(fileFullPath, FILE_APPEND);
    
  // Serial.print("FILE OPENED!"); 
}

void LogFile::deleteFile() {
  fileStorage->remove(fileFullPath);
}

void LogFile::archiveFile() {
  Serial.println("Archiving File...");
  closeFile();
  Serial.print("Copying file: ");
  Serial.print(fileFullPath);
  Serial.print(" INTO: ");
  Serial.println(archivePath + "/" + serviceName + "_" + rtc->getTimeStamp());
  fileStorage->rename(fileFullPath, archivePath + "/" + serviceName + "_" + rtc->getTimeStamp());
}

void LogFile::rotateFile() {
  archiveFile();
  createFile();
}

void LogFile::closeFile() {
  // Serial.println("Closing File...");
  file.close();
  // Serial.println("File closed...");
}


void LogFile::writeString(String logString) {

    recordsCounter++;

    if(recordsCounter > maxRecordsInFile) {
        rotateFile();

        // SD.remove("/fcntr.txt");
        // fileCounterFile = SD.open("/fcntr.txt", FILE_WRITE);
        // if (fileCounterFile) {
        //   fileCounterFile.print(filesCounter);
        //   fileCounterFile.close();
        //   Serial.println("Files COUNTER updated!!!");
        // }
        // // if the file isn't open, pop up an error:
        // else {
        //   Serial.println("error opening fcntr.txt");
        // }
        // recordsInFileCounter = 1;
      }

      openFile();
      
      // File dataFile = SD.open(String("/") + (String(deviceId)+String("_")+String(filesCounter) + String(".txt")).c_str(), FILE_WRITE);
      // file = fileStorage->open(fileFullPath, FILE_APPEND);

      // if the file is available, write to it:
      if (file) {
        // if(recordsInFileCounter == 1) 
        // { 
        //   Serial.println(generateFileHeader());
        //   dataFile.println(generateFileHeader());
        // }

        file.println(logString);
        // file.flush();
        // file.close();
        // print to the serial port too:
        // Serial.print("Saving String: ");
        // Serial.println(logString);
      }
      // if the file isn't open, pop up an error:
      else {
        Serial.println("error opening file");
      }
      closeFile();
}

void LogFile::logString(String logString) {

  writeString(String(rtc->getDateTime() + " | " + logString));

}