#ifndef GDATADEF_H
#define GDATADEF_H

#include <QString>

typedef struct FileRecord{
    bool bChecked;          //是否选中
    QString strFilePath;    //文件路径
    QString strFileSize;    //文件大小
    QString strSpeed;       //传输速度
} fileRecord;

#define COLUMN_COUNT                    4
#define CHECK_BOX_COLUMN                0
#define File_PATH_COLUMN                1
#define File_SIZE_COLUMN                2
#define File_SPEED_COLUMN               3


#endif // GDATADEF_H
