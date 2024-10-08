#include "yangplayer/AppTestFileWriter.h"

#define ENABLE_TEST_FILE

AppTestFileWriter::AppTestFileWriter(std::string filename)
    :m_pFile(NULL)
{
#ifdef IOS
    std::string path = ProtoMyInfo::instance()->getIOSSandboxPath();
    filename = path.append("/").append(filename);
    FUNLOGI("ios file path = %s", filename.c_str());
#else if ANDROID
    std::string audioPath = "";
    if(!audioPath.empty()){
        filename = audioPath.append("/").append(filename);
    }
#endif
    
#ifdef ENABLE_TEST_FILE
    m_filename = filename;
    fopen_s(&m_pFile, filename.c_str(), "wb+");
    if (m_pFile == NULL){
    }
#endif
}

AppTestFileWriter::~AppTestFileWriter()
{
    closeFile();
}

int AppTestFileWriter::write(const char* data, int len)
{
    if (m_pFile) {
        int ret = fwrite(data, 1, len, m_pFile);
        return ret;
    }
	return 0;
}

void AppTestFileWriter::closeFile()
{
    if (m_pFile){
        fclose(m_pFile);
        m_pFile = NULL;
    }
}

int AppTestFileWriter::removeFile()
{
    if (m_pFile) {
        closeFile();
        return remove(m_filename.c_str());
    }
    return -1;
}

void AppTestFileWriter::setFileName(std::string fileName) {
    m_filename = fileName;
    closeFile();
    fopen_s(&m_pFile, fileName.c_str(), "wb+");
    if (m_pFile == NULL){
    }
}

bool AppTestFileWriter::isHadFile() {
    if(m_pFile){
        return true;
    }
    return false;
}

