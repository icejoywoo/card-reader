#include "StdAfx.h"
#include "DataTransfer.h"

//////////////////////////////////////////////////////////////////////////
// TransferRule
//////////////////////////////////////////////////////////////////////////
TransferRule::TransferRule()
{
	this->length = -1;
}

TransferRule::TransferRule(const TransferRule& rule)
	: length(rule.length), 
	startType(rule.startType),
	startPosition(rule.startPosition),
	startTag(rule.startTag),
	endType(rule.endType),
	endPosition(rule.endPosition),
	endTag(rule.endTag),
	tag(rule.tag),
	prefix(rule.prefix),
	suffix(rule.suffix)
{
}

TransferRule& TransferRule::operator=(const TransferRule &rgt)
{
	this->length = rgt.length;
	this->startType = rgt.startType;
	this->startPosition = rgt.startPosition;
	this->startTag = rgt.startTag;
	this->endType = rgt.endType;
	this->endPosition = rgt.endPosition;
	this->endTag = rgt.endTag;
	this->tag = rgt.tag;
	this->prefix = rgt.prefix;
	this->suffix = rgt.suffix;
	
	return *this;
}

TransferRule::~TransferRule()
{
}

void TransferRule::SetTarget(CString target)
{
	this->target = target;
}

void TransferRule::SetStart(int startPosition)
{
	this->startType = POSITION_TYPE;
	this->startPosition = startPosition;
}

void TransferRule::SetStart(char* startTag)
{
	this->startType = TAG_TYPE;
	this->startTag = startTag;
}

void TransferRule::SetEnd(int endPosition)
{
	this->endType = POSITION_TYPE;
	this->endPosition = endPosition;
}

void TransferRule::SetEnd(char* endTag)
{
	this->endType = TAG_TYPE;
	this->endTag = endTag;
}

void TransferRule::SetPrefix(char* prefix)
{
	this->prefix = prefix;
}

void TransferRule::SetSuffix(char* suffix)
{
	this->suffix = suffix;
}

void TransferRule::SetLength(int length)
{
	this->length = length;
}

void TransferRule::SetTag(char* tag)
{
	this->tag = tag;
}

int TransferRule::GetStart()
{
	if (this->startType == POSITION_TYPE)
	{
		return this->startPosition;
	} 
	else if (this->startType == TAG_TYPE)
	{
		int start = this->target.Find(this->startTag);
		return start + strlen(this->startTag);
	} else {
		throw bad_exception("获取开始位置出错!");
	}
}

int TransferRule::GetLength()
{
	if (this->length != -1)
	{
		return this->length;
	}
	else
	{
		int start = this->GetStart();
		if (this->endType == POSITION_TYPE)
		{
			return this->endPosition - start;
		} 
		else if (this->endType == TAG_TYPE)
		{
			int end = this->target.Find(this->endTag);
			return end - start;
		}
		else
		{
			throw bad_exception("获取长度出错!");
		}
	}
}

CString TransferRule::Handle(CString target)
{
	this->SetTarget(target);
	CString result;
	result.Format("<%s>%s%s%s</%s>", this->tag, this->prefix, target.Mid(this->GetStart(), this->GetLength()), this->suffix, this->tag);
	return result;
}



//////////////////////////////////////////////////////////////////////////
// DataTransfer
//////////////////////////////////////////////////////////////////////////

DataTransfer::DataTransfer()
{
}

DataTransfer::~DataTransfer()
{
	rules.clear();
}

void DataTransfer::AddRule(TransferRule& rule)
{
	TransferRule _rule(rule);
	this->rules.push_back(_rule);
}

void DataTransfer::HandleFile(const char* filename)
{
	try
	{
		CStdioFile file(filename, CFile::modeRead);

		char outFilename[128];
		sprintf(outFilename, "%s_HDP5000", filename);

		CStdioFile outFile(outFilename, CFile::modeCreate | CFile::modeWrite);
		CString line;
		int lineNo = 0; // 行号
		while (file.ReadString(line))
		{
			++lineNo;
			CString result;
			CString temp;

			for (vector<TransferRule>::iterator iter = rules.begin();
				iter != rules.end(); ++iter)
			{
				temp += iter->Handle(line);
			}

			result.Format("%06d [ROW]%s", lineNo, temp);
			outFile.WriteString(result + "\n");
		}
		file.Close();
		outFile.Close();
	}
	catch (CFileException* e)
	{
		AfxMessageBox(_T("文件打开错误, 文件不存在!"));
	}
}
