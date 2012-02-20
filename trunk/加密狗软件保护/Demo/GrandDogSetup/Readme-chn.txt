                -----------------------------------------------------------------------------------------------------------------
                    宏狗套装 Windows 2K (32 位)/Windows XP (32/x64 位)/Windows Server 2003 (32/x64 位)/Windows Vista (32/x64 位)
                    /Windows 7 (32/x64 位)/Windows Server 2008 (32/x64 位)/Windows 2008 R2 (x64 位)驱动安装卸载程序使用说明
                -----------------------------------------------------------------------------------------------------------------
                                            版权所有 (C)  2010  赛孚耐（北京）信息技术有限公司

 
  加密后的 Windows 应用程序在 Windows 2K (32 位)/Windows XP (32/x64 位)/Windows Server 2003 (32/x64 位)
  /Windows Vista (32/x64 位)/Windows 7 (32/x64 位)/Windows Server 2008 (32/x64 位)/Windows 2008 R2 (x64 位)
  下运行时，需要安装硬件狗的设备驱动程序。

  我们提供了宏狗驱动安装动态库GrandDogSetup.dll，该动态库提供了驱动安装、卸载以及检测驱动版本的接口。
  在卸载狗驱动时，如果您已经插上了硬件狗，请拔掉狗后再卸载狗驱动。
 	
==========
文件清单
==========

  readme-chn.txt     			本文档
  DogInst.exe				驱动安装执行程序
  GrandDogSetup.dll	 		驱动安装动态库
  Delphi<dir> 				调用驱动安装动态库的Delphi例子程序
  VB<dir> 				调用驱动安装动态库的VB例子程序
  VC<dir> 				调用驱动安装动态库的VC例子程序
==================
GrandDogSetup.dll 简介
==================

GrandDogSetup.dll是WIN32下动态连接库,开发商可用在其加密的软件安装程序中使用如下接口函数。
  
  (1)驱动安装的函数接口Install，定义如下:
  unsigned long PASCAL Install(int iFlag)；
  参数：
  	iFlag = 1 只安装USB狗驱动
	iFlag = 2 只安装并口狗驱动(本版本不支持)
	iFlag = 3 安装并口狗驱动和USB狗驱动
  返回值：
  如果运行成功则返回0,否则返回错误值。

  (2)驱动卸载的函数接口Uninstall，定义如下:
  unsigned long PASCAL Uninstall(int iFlag)；
  参数：
  	iFlag = 1 只卸载USB狗驱动
	iFlag = 2 只卸载并口狗驱动（本版本不支持）
	iFlag = 3 卸载并口狗驱动和USB狗驱动
  返回值：
  如果运行成功则返回0,否则返回错误值。
  (3)检测驱动版本的接口CheckVersion，定义如下:
  unsigned long PASCAL CheckVersion(BOOL bShowMessageBox,
					int* piUsbVerStatus,
					int* piParVerStatus)
  参数：
	bShowMessageBox = TRUE 	显示获取版本的弹出窗口
	bShowMessageBox = FALSE 不显示获取版本的弹出窗口
	piUsbVerStatus	存储USB狗驱动状态的指针
	piParVerStatus	存储并口狗驱动状态的指针（为后续版本保留）

  返回值：
  如果运行成功则返回0,否则返回错误值。
  如果运行成功，*piUsbVerStatus=0 代表本机没有安装usb狗驱动
		*piUsbVerStatus=1 代表本机安装的驱动版本与待安装的驱动版本一致
 		*piUsbVerStatus=2 代表本机安装的驱动版本比待安装的驱动版本旧
		*piUsbVerStatus=3 代表本机安装的驱动版本比待安装的驱动版本新

		
  详情请参见例子程序的源代码。

=========
 错误码
=========

E_RC_MAPPING_SYSTEM_LIBRARY_FUNCTION (0xA8162001)	映射系统库函数错误
E_RC_LOAD_SYSTEM_LIBRARY	     (0xA8162002)	加载系统库错误
E_RC_FIND_USB_DOG_DEVICE	     (0xA8162003)	没有发现USB狗设备
E_RC_UPDATE_USB_DOG		     (0xA8162004)	更新usb狗驱动失败
E_RC_OPERATING_SYSTEM		     (0xA8162005)	不支持的操作系统
E_RC_NO_PARALLEL_PORT_OR_DISABLED    (0xA8162006)	没有并口或并口被禁用
E_RC_REMOVE_FILE_FAILED    	     (0xA8162007)	删除文件失败
E_RC_OPEN_DRIVER_SERVICE_FAILED	     (0xA8162008)	打开服务失败
E_RC_START_DRIVER_SERVICE_FAILED     (0xA8162009)	启动服务失败
E_RC_COPY_FILE_FAILED		     (0xA816200A)	拷贝文件失败
E_RC_OPERATE_REGISTRY_FAILED         (0xA816200B)	访问注册表失败
E_RC_NOT_ADMINISTRATOR               (0xA816200C)	不是管理员身份


========
注意事项
========
 1. 在安装和卸载宏狗驱动前，请关闭使用宏狗的应用程序。


---------------------------------------------------------------------------------------------------
“狗”是北京金天地软件发展有限公司的注册商标，已授权赛孚耐（北京）信息技术有限公司。
----------------------------------------------------------------------------------------------------