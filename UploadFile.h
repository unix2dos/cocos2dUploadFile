//
//  UploadFile.h
//  ReadingFriends
//
//  Created by liuwei on 16/7/6.
//
//

#ifndef UploadFile_h
#define UploadFile_h


struct stuUpload
{
    //data
    std::string m_strUrl;
    std::string m_strFileName;
    std::string m_strFileCopyName;
    std::string m_strFileContentType;
    std::map<std::string,std::string> m_mapHeadValue;
    std::map<std::string,std::string> m_mapPostValue;
    std::map<std::string,std::string> m_mapGetValue;
    
    
    stuUpload(std::string url,
              std::string fileName,
              std::string fileCopy,
              std::string fileType,
              std::map<std::string,std::string> head = {},
              std::map<std::string,std::string> post = {},
              std::map<std::string,std::string> get = {}
              )
    :m_strUrl(url),
    m_strFileName(fileName),
    m_strFileCopyName(fileCopy),
    m_strFileContentType(fileType)
    {
        m_mapHeadValue = head;
        m_mapPostValue = post;
        m_mapGetValue  = get;
    }
    
    
    //callback
    std::function<void(double)>  m_callBackProgress;
    std::function<void()>        m_callBackFinsih;
    std::vector<char>            m_vecResponseData;
    std::vector<char>            m_vecHeadData;
};




typedef std::function<void(std::string)> uploadFinishCallback;
typedef std::function<void(std::string, std::string)> uploadResponse;
class UploadFile : public cocos2d::Ref
{
public:
    UploadFile();
    ~UploadFile();
public:
    
    /* 上传文件  */
    CC_DEPRECATED_ATTRIBUTE void uploadFile(std::string url, std::string fileName,
                    std::string fileCopyName, std::string fileContentType,
                    uploadFinishCallback callBack,
                    const std::map<std::string,std::string>& mapHeadValue,
                    const std::map<std::string,std::string>& mapPostValue,
                    const std::map<std::string,std::string>& mapGetValue
                    );
    
    
    /* 上传文件 */
    void uploadFile(uploadResponse callBack, const stuUpload& upload);
    
    
    /* 设置上传进度 */
    void    setUploadProgress(double dProgress);
    
    /* 获取上传进度 */
    double  getUploadProgress();
    
    
private:
    /* 线程上传函数 */
    void _threadUpload(stuUpload* pUploadData);
    
private:
    std::mutex m_mutexProgress;
    double m_dProgress;
};

#endif /* UploadFile_h */
