/*
This source file is part of KBEngine
For the latest info, see http://www.kbengine.org/

Copyright (c) 2008-2012 KBEngine.

KBEngine is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

KBEngine is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.
 
You should have received a copy of the GNU Lesser General Public License
along with KBEngine.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef __DATA_TYPE_H__
#define __DATA_TYPE_H__

// common include
#include "cstdkbe/cstdkbe.hpp"
#if KBE_PLATFORM == PLATFORM_WIN32
#pragma warning (disable : 4910)
#pragma warning (disable : 4251)
#pragma warning (disable : 4661)
#endif
#include "entitydef/common.hpp"	
#include "cstdkbe/refcountable.hpp"
#include "cstdkbe/memorystream.hpp"
#include "pyscript/scriptobject.hpp"
#include "pyscript/pickler.hpp"
#include "xmlplus/xmlplus.hpp"	
//#define NDEBUG
// windows include	
#if KBE_PLATFORM == PLATFORM_WIN32
#else
// linux include
#endif

namespace KBEngine{

#define OUT_TYPE_ERROR(T)								\
{														\
	char err[] = {"must be set to a " T " type."};		\
	PyErr_SetString(PyExc_TypeError, err);				\
	PyErr_PrintEx(0);									\
}

class RefCountable;


class DataType : public RefCountable
{
public:	
	DataType(DATATYPE_UID did = 0);
	virtual ~DataType();	

	virtual bool isSameType(PyObject* pyValue) = 0;

	virtual void addToStream(MemoryStream* mstream, PyObject* pyValue) = 0;

	virtual PyObject* createFromStream(MemoryStream* mstream) = 0;

	/**	
		当传入的这个pyobj并不是当前类型时则按照当前类型创建出一个obj
		前提是即使这个PyObject不是当前类型， 但必须拥有转换的共性
		既一个python字典转换为一个固定字典， 字典中的key都匹配
	*/
	virtual PyObject* createNewItemFromObj(PyObject* pyobj)
	{
		Py_INCREF(pyobj);
		return pyobj;
	}
	
	virtual PyObject* createNewFromObj(PyObject* pyobj)
	{
		Py_INCREF(pyobj);
		return pyobj;
	}
		
	virtual bool initialize(XmlPlus* xmlplus, TiXmlNode* node);

	virtual PyObject* parseDefaultStr(std::string defaultVal) = 0;

	virtual const char* getName(void)const = 0;

	INLINE DATATYPE_UID id()const;

	INLINE void aliasName(std::string aliasName);
	INLINE const char* aliasName(void)const;

	virtual DATATYPE type()const{ return DATA_TYPE_UNKONWN; }
protected:
	DATATYPE_UID id_;
	std::string aliasName_;
};

template <typename SPECIFY_TYPE>
class IntType : public DataType
{
protected:
public:	
	IntType(DATATYPE_UID did = 0);
	virtual ~IntType();	

	bool isSameType(PyObject* pyValue);
	void addToStream(MemoryStream* mstream, PyObject* pyValue);
	PyObject* createFromStream(MemoryStream* mstream);
	PyObject* parseDefaultStr(std::string defaultVal);
	const char* getName(void)const{ return "INT";}
	virtual DATATYPE type()const{ return DATA_TYPE_DIGIT; }
};

//-------------------------------------------------------------------------------------
template <>
inline const char* IntType<uint8>::getName(void)const
{
        return "UINT8";
}

//-------------------------------------------------------------------------------------
template <>
inline const char* IntType<uint16>::getName(void)const
{
        return "UINT16";
}

//-------------------------------------------------------------------------------------
template <>
inline const char* IntType<uint32>::getName(void)const
{
        return "UINT32";
}

//-------------------------------------------------------------------------------------
template <>
inline const char* IntType<int8>::getName(void)const
{
        return "INT8";
}

//-------------------------------------------------------------------------------------
template <>
inline const char* IntType<int16>::getName(void)const
{
        return "INT16";
}

//-------------------------------------------------------------------------------------
template <>
inline const char* IntType<int32>::getName(void)const
{
        return "INT32";
}

//-------------------------------------------------------------------------------------

class UInt64Type : public DataType
{
protected:
public:	
	UInt64Type(DATATYPE_UID did = 0);
	virtual ~UInt64Type();	

	bool isSameType(PyObject* pyValue);

	void addToStream(MemoryStream* mstream, PyObject* pyValue);

	PyObject* createFromStream(MemoryStream* mstream);

	PyObject* parseDefaultStr(std::string defaultVal);

	const char* getName(void)const{ return "UINT64";}

	virtual DATATYPE type()const{ return DATA_TYPE_DIGIT; }
};

class UInt32Type : public DataType
{
protected:
public:	
	UInt32Type(DATATYPE_UID did = 0);
	virtual ~UInt32Type();	

	bool isSameType(PyObject* pyValue);

	void addToStream(MemoryStream* mstream, PyObject* pyValue);

	PyObject* createFromStream(MemoryStream* mstream);

	PyObject* parseDefaultStr(std::string defaultVal);

	const char* getName(void)const{ return "UINT32";}

	virtual DATATYPE type()const{ return DATA_TYPE_DIGIT; }
};

class Int64Type : public DataType
{
protected:
public:	
	Int64Type(DATATYPE_UID did = 0);
	virtual ~Int64Type();	

	bool isSameType(PyObject* pyValue);

	void addToStream(MemoryStream* mstream, PyObject* pyValue);

	PyObject* createFromStream(MemoryStream* mstream);

	PyObject* parseDefaultStr(std::string defaultVal);

	const char* getName(void)const{ return "INT64";}

	virtual DATATYPE type()const{ return DATA_TYPE_DIGIT; }
};

class FloatType : public DataType
{
protected:
public:	
	FloatType(DATATYPE_UID did = 0);
	virtual ~FloatType();	

	bool isSameType(PyObject* pyValue);

	void addToStream(MemoryStream* mstream, PyObject* pyValue);

	PyObject* createFromStream(MemoryStream* mstream);

	PyObject* parseDefaultStr(std::string defaultVal);

	const char* getName(void)const{ return "FLOAT";}

	virtual DATATYPE type()const{ return DATA_TYPE_DIGIT; }
};

class DoubleType : public DataType
{
protected:
public:	
	DoubleType(DATATYPE_UID did = 0);
	virtual ~DoubleType();	

	bool isSameType(PyObject* pyValue);

	void addToStream(MemoryStream* mstream, PyObject* pyValue);

	PyObject* createFromStream(MemoryStream* mstream);

	PyObject* parseDefaultStr(std::string defaultVal);

	const char* getName(void)const{ return "DOUBLE";}

	virtual DATATYPE type()const{ return DATA_TYPE_DIGIT; }
};

class VectorType : public DataType
{
public:	
	VectorType(uint32 elemCount, DATATYPE_UID did = 0);
	virtual ~VectorType();	

	bool isSameType(PyObject* pyValue);

	void addToStream(MemoryStream* mstream, PyObject* pyValue);

	PyObject* createFromStream(MemoryStream* mstream);

	PyObject* parseDefaultStr(std::string defaultVal);

	const char* getName(void)const{ return name_.c_str();}

	virtual DATATYPE type()const{ return DATA_TYPE_VECTOR; }
protected:
	std::string name_;
	uint32 elemCount_;
};

class StringType : public DataType
{
protected:
public:	
	StringType(DATATYPE_UID did = 0);
	virtual ~StringType();	

	bool isSameType(PyObject* pyValue);

	void addToStream(MemoryStream* mstream, PyObject* pyValue);

	PyObject* createFromStream(MemoryStream* mstream);

	PyObject* parseDefaultStr(std::string defaultVal);

	const char* getName(void)const{ return "STRING";}

	virtual DATATYPE type()const{ return DATA_TYPE_STRING; }
};

class UnicodeType : public DataType
{
protected:
public:	
	UnicodeType(DATATYPE_UID did = 0);
	virtual ~UnicodeType();	

	bool isSameType(PyObject* pyValue);

	void addToStream(MemoryStream* mstream, PyObject* pyValue);

	PyObject* createFromStream(MemoryStream* mstream);

	PyObject* parseDefaultStr(std::string defaultVal);

	const char* getName(void)const{ return "UNICODE";}

	virtual DATATYPE type()const{ return DATA_TYPE_UNICODE; }
};

class PythonType : public DataType
{
protected:
public:	
	PythonType(DATATYPE_UID did = 0);
	virtual ~PythonType();	

	virtual bool isSameType(PyObject* pyValue);
	virtual void addToStream(MemoryStream* mstream, PyObject* pyValue);

	virtual PyObject* createFromStream(MemoryStream* mstream);

	virtual PyObject* parseDefaultStr(std::string defaultVal);

	const char* getName(void)const{ return "PYTHON";}

	virtual DATATYPE type()const{ return DATA_TYPE_PYTHON; }
};

class PyDictType : public PythonType
{
protected:
public:	
	PyDictType(DATATYPE_UID did = 0);
	virtual ~PyDictType();	

	bool isSameType(PyObject* pyValue);

	PyObject* parseDefaultStr(std::string defaultVal);

	const char* getName(void)const{ return "PY_DICT";}

	virtual DATATYPE type()const{ return DATA_TYPE_PYDICT; }
};

class PyTupleType : public PythonType
{
protected:
public:	
	PyTupleType(DATATYPE_UID did = 0);
	virtual ~PyTupleType();	

	bool isSameType(PyObject* pyValue);

	PyObject* parseDefaultStr(std::string defaultVal);

	const char* getName(void)const{ return "PY_TUPLE";}

	virtual DATATYPE type()const{ return DATA_TYPE_PYTUPLE; }
};

class PyListType : public PythonType
{
protected:
public:	
	PyListType(DATATYPE_UID did = 0);
	virtual ~PyListType();	

	bool isSameType(PyObject* pyValue);

	PyObject* parseDefaultStr(std::string defaultVal);

	const char* getName(void)const{ return "PY_LIST";}

	virtual DATATYPE type()const{ return DATA_TYPE_PYLIST; }
};

class BlobType : public DataType
{
protected:
public:	
	BlobType(DATATYPE_UID did = 0);
	virtual ~BlobType();	

	bool isSameType(PyObject* pyValue);

	void addToStream(MemoryStream* mstream, PyObject* pyValue);

	PyObject* createFromStream(MemoryStream* mstream);

	PyObject* parseDefaultStr(std::string defaultVal);

	const char* getName(void)const{ return "BLOB";}

	virtual DATATYPE type()const{ return DATA_TYPE_BLOB; }
};

class MailboxType : public DataType
{
protected:
public:	
	MailboxType(DATATYPE_UID did = 0);
	virtual ~MailboxType();	

	bool isSameType(PyObject* pyValue);

	void addToStream(MemoryStream* mstream, PyObject* pyValue);

	PyObject* createFromStream(MemoryStream* mstream);

	PyObject* parseDefaultStr(std::string defaultVal);

	const char* getName(void)const{ return "MAILBOX";}

	virtual DATATYPE type()const{ return DATA_TYPE_MAILBOX; }
};

class FixedArrayType : public DataType
{
public:	
	FixedArrayType(DATATYPE_UID did = 0);
	virtual ~FixedArrayType();	
	
	DataType* getDataType(){ return dataType_; }

	bool isSameType(PyObject* pyValue);
	bool isSameItemType(PyObject* pyValue);

	void addToStream(MemoryStream* mstream, PyObject* pyValue);

	PyObject* createFromStream(MemoryStream* mstream);

	PyObject* parseDefaultStr(std::string defaultVal);

	bool initialize(XmlPlus* xmlplus, TiXmlNode* node);

	const char* getName(void)const{ return "ARRAY";}

	/**	
		当传入的这个pyobj并不是当前类型时则按照当前类型创建出一个obj
		前提是即使这个PyObject不是当前类型， 但必须拥有转换的共性
		既一个python字典转换为一个固定字典， 字典中的key都匹配
	*/
	virtual PyObject* createNewItemFromObj(PyObject* pyobj);
	virtual PyObject* createNewFromObj(PyObject* pyobj);

	virtual DATATYPE type()const{ return DATA_TYPE_FIXEDARRAY; }
protected:
	DataType*			dataType_;		// 这个数组所处理的类别
};

class FixedDictType : public DataType
{
public:
	struct DictItemDataType
	{
		DataType* dataType;

		// 作为一个数据类别在alias中可对dict中的某个项指定是否持久化
		bool persistent;
	};

	typedef std::vector< std::pair< std::string, KBEShared_ptr< DictItemDataType > > > FIXEDDICT_KEYTYPE_MAP;
public:	
	FixedDictType(DATATYPE_UID did = 0);
	virtual ~FixedDictType();
	
	/** 
		获得这个固定字典的key类别 
	*/	
	FIXEDDICT_KEYTYPE_MAP& getKeyTypes(void){ return keyTypes_; }

	const char* getName(void)const{ return "FIXED_DICT";}

	bool isSameType(PyObject* pyValue);
	DataType* isSameItemType(const char* keyName, PyObject* pyValue);

	void addToStream(MemoryStream* mstream, PyObject* pyValue);
	void addToStreamEx(MemoryStream* mstream, PyObject* pyValue, bool onlyPersistents);

	PyObject* createFromStream(MemoryStream* mstream);

	PyObject* parseDefaultStr(std::string defaultVal);
	bool initialize(XmlPlus* xmlplus, TiXmlNode* node);
	
	/**	
		当传入的这个pyobj并不是当前类型时则按照当前类型创建出一个obj
		前提是即使这个PyObject不是当前类型， 但必须拥有转换的共性
		既一个python字典转换为一个固定字典， 字典中的key都匹配
	*/
	virtual PyObject* createNewItemFromObj(const char* keyName, PyObject* pyobj);
	virtual PyObject* createNewFromObj(PyObject* pyobj);

	/** 
		获得固定字典所有的key名称 
	*/
	std::string getKeyNames(void);

	/** 
		获得debug信息，返回固定字典所有的key名称和类型
	*/
	std::string debugInfos(void);

	/** 
		加载impl模块
	*/
	bool loadImplModule(std::string moduleName);

	/** 
		impl相关实现
	*/
	PyObject* impl_createObjFromDict(PyObject* dictData);
	PyObject* impl_getDictFromObj(PyObject* pyobj);
	bool impl_isSameType(PyObject* pyobj);

	bool hasImpl()const { return implObj_ != NULL; }

	virtual DATATYPE type()const{ return DATA_TYPE_FIXEDDICT; }
protected:
	// 这个固定字典里的各个key的类型
	FIXEDDICT_KEYTYPE_MAP			keyTypes_;				

	// 实现脚本模块
	PyObject*						implObj_;				

	PyObject*						pycreateObjFromDict_;
	PyObject*						pygetDictFromObj_;

	PyObject*						pyisSameType_;

	std::string						moduleName_;		
};


template class IntType<uint8>;
template class IntType<uint16>;
template class IntType<int8>;
template class IntType<int16>;
template class IntType<int32>;


}

#ifdef CODE_INLINE
#include "datatype.ipp"
#endif
#endif
