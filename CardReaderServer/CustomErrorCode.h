#ifndef _CUSTOM_ERROR_CODE_H_
#define _CUSTOM_ERROR_CODE_H_

#define COMMAND_NOT_FOUND (-100) // 命令未找到
#define INIT_FAILED (-101) // 与卡片读写器的通信初始化失败
#define CLOSE_FAILED (-102) // 关闭通信失败

#define READER_ALREADY_USED (-103) // 读卡器已经被使用了
#define IN_WAIT_LIST (-104) //加入到等待队列, 等待中

#endif