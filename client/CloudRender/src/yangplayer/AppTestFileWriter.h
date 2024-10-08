#ifndef APPFILEWRITEHELPER_H
#define APPFILEWRITEHELPER_H

#include <stdio.h>
#include <string>

//NOTE:this class is not thread-safe
class  __declspec(dllexport) AppTestFileWriter
{
public:
    AppTestFileWriter(std::string filename);
    ~AppTestFileWriter();

    int write(const char* data, int len);
    void closeFile();
    int removeFile();
    void setFileName(std::string fileName);
    bool isHadFile();

private:
    FILE* m_pFile;
    std::string m_filename;
};

#endif // APPFILEWRITEHELPER_H
