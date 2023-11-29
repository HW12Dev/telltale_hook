#pragma once

#include <string>

namespace telltale_types {

class Symbol {
    unsigned __int64 mCrc64;
};

class String : public std::string {};

template<typename T>
class Ptr {
    T* mpData;
};

class ResourceAddress {
    int mScheme;
    Symbol mResOrLoc;
    Ptr<ResourceAddress> mpParent;
};

class FunctionBase {
    FunctionBase *mpNext;
};


class CallbacksBase {
    FunctionBase *mpLast;
};

template<typename T>
class Callbacks : CallbacksBase {};

class __declspec(align(8)) ContainerInterface {
    Callbacks<Ptr<ContainerInterface>> mContainerChangedCallbacks;
    bool mbScriptLocked;
};

template<typename T>
class ContainerDataAttach {};

template<typename T>
class DCArray : ContainerInterface, ContainerDataAttach<T> {
    int mSize;
    int mCapacity;
    T* mpStorage;
};

class __declspec(align(8)) WeakPointerSlot {
    const void *mpObject;
    int mRefCount;
};

class WeakPointerID {
    WeakPointerSlot *mpSlot;
};

template<typename T>
class Atomic {
    T mValue;
};

class RefCountObj_DebugPtr {
    Atomic<int> mRefCount;
};

class DataStream : WeakPointerID {
    RefCountObj_DebugPtr __mRefCountObj;
    ResourceAddress mResourceAddress;
};

class TTArchive2__ResourceEntry {
    unsigned __int64 mNameCRC;
    unsigned __int64 mOffset;
    unsigned int mSize;
    unsigned __int16 mNamePageIndex;
    unsigned __int16 mNamePageOffset;
};

// Struct is incorrect for MCSMS1
class __declspec(align(8)) TTArchive2 {
    public:
    ResourceAddress mArchiveResourceAddress;
    ResourceAddress mResourceAddress;
    ResourceAddress mContainingLocationResourceAddress;
    Ptr<DataStream> mpResourceStream;
    Ptr<DataStream> mpNameStream;
    DCArray<TTArchive2__ResourceEntry> mResources;
    char *mpNamePageCache;
    int mVersion;
    unsigned int mNamePageCacheIndex;
    unsigned int mNamePageCount;
};

}