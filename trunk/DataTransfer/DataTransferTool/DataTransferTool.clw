; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDataTransferToolApp
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DataTransferTool.h"

ClassCount=7
Class1=CDataTransferToolApp
Class2=CDataTransferToolDlg
Class3=CAboutDlg

ResourceCount=6
Resource1=IDR_MAINFRAME
Class4=TargetFileChooseDialog
Resource2=IDD_DIALOG_FIELD_CONFIG
Class5=CTemplateNameDialog
Resource3=IDD_DATATRANSFERTOOL_DIALOG
Class6=CFieldConfigDialog
Resource4=IDD_DIALOG_TEMPLATE_NAME
Resource5=IDD_ABOUTBOX
Class7=CTransferingDialog
Resource6=IDD_DIALOG_TRANSFERING

[CLS:CDataTransferToolApp]
Type=0
HeaderFile=DataTransferTool.h
ImplementationFile=DataTransferTool.cpp
Filter=N
LastObject=CDataTransferToolApp
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CDataTransferToolDlg]
Type=0
HeaderFile=DataTransferToolDlg.h
ImplementationFile=DataTransferToolDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CDataTransferToolDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=DataTransferToolDlg.h
ImplementationFile=DataTransferToolDlg.cpp
Filter=D

[DLG:IDD_DATATRANSFERTOOL_DIALOG]
Type=1
Class=CDataTransferToolDlg
ControlCount=22
Control1=IDC_LIST_TEMPLATES,SysListView32,1350631433
Control2=IDC_STATIC,button,1342178055
Control3=IDC_STATIC,button,1342178055
Control4=IDC_LIST_FIELD_TABLE,SysListView32,1350631433
Control5=IDC_BUTTON_NEW_FIELD,button,1342242816
Control6=IDC_BUTTON_DEL_FIELD,button,1342242816
Control7=IDC_BUTTON_MODIFY_FIELD,button,1342242816
Control8=IDC_BUTTON_NEW_TEMPLATE,button,1342242816
Control9=IDC_BUTTON_DEL_TEMPLATE,button,1342242816
Control10=IDC_BUTTON_APPLY_TEMPLATE,button,1342242816
Control11=IDC_BUTTON_EXIT,button,1342242816
Control12=IDC_STATIC,static,1342308352
Control13=IDC_EDIT_TARGET_FILE,edit,1350631552
Control14=IDC_BUTTON_CHOOSE_TARGET,button,1342242816
Control15=IDC_STATIC,button,1342177287
Control16=IDC_BUTTON_START_TRANSFER,button,1342242816
Control17=IDC_STATIC,static,1342308352
Control18=IDC_EDIT_CURRENT_TEMPLATE,edit,1484849280
Control19=IDC_BUTTON_CHOOSE_DIR,button,1342242816
Control20=IDC_BUTTON_SAVEAS_TEMPLATE,button,1342242816
Control21=IDC_BUTTON_SAVE_TEMPLATE1,button,1342242816
Control22=IDC_BUTTON_ABOUT,button,1342242816

[CLS:TargetFileChooseDialog]
Type=0
HeaderFile=TargetFileChooseDialog.h
ImplementationFile=TargetFileChooseDialog.cpp
BaseClass=CFileDialog
Filter=D

[DLG:IDD_DIALOG_TEMPLATE_NAME]
Type=1
Class=CTemplateNameDialog
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_TEMPLATE_NAME,edit,1350631552

[CLS:CTemplateNameDialog]
Type=0
HeaderFile=TemplateNameDialog.h
ImplementationFile=TemplateNameDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CTemplateNameDialog

[DLG:IDD_DIALOG_FIELD_CONFIG]
Type=1
Class=CFieldConfigDialog
ControlCount=12
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT_START_DATA,edit,1350631552
Control4=IDC_EDIT_END_DATA,edit,1350631552
Control5=IDC_EDIT_TAG,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_COMBO_END_TYPE,combobox,1344340227
Control12=IDC_COMBO_START_TYPE,combobox,1344340227

[CLS:CFieldConfigDialog]
Type=0
HeaderFile=FieldConfigDialog.h
ImplementationFile=FieldConfigDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT_END_DATA
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=?
ControlCount=3
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308876
Control3=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG_TRANSFERING]
Type=1
Class=CTransferingDialog
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[CLS:CTransferingDialog]
Type=0
HeaderFile=TransferingDialog.h
ImplementationFile=TransferingDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CTransferingDialog
VirtualFilter=dWC

