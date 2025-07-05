//
// Generated file, do not edit! Created by opp_msgtool 6.1 from EDVRPMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "EDVRPMessage_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

Register_Enum(EDVRPMessageType, (EDVRPMessageType::HELLO, EDVRPMessageType::ROUTING_UPDATE));

Register_Class(EDVRPMessage)

EDVRPMessage::EDVRPMessage(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

EDVRPMessage::EDVRPMessage(const EDVRPMessage& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

EDVRPMessage::~EDVRPMessage()
{
}

EDVRPMessage& EDVRPMessage::operator=(const EDVRPMessage& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void EDVRPMessage::copy(const EDVRPMessage& other)
{
    this->messageType = other.messageType;
    this->routerId = other.routerId;
    this->timestamp = other.timestamp;
    this->authToken = other.authToken;
}

void EDVRPMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->messageType);
    doParsimPacking(b,this->routerId);
    doParsimPacking(b,this->timestamp);
    doParsimPacking(b,this->authToken);
}

void EDVRPMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->messageType);
    doParsimUnpacking(b,this->routerId);
    doParsimUnpacking(b,this->timestamp);
    doParsimUnpacking(b,this->authToken);
}

int EDVRPMessage::getMessageType() const
{
    return this->messageType;
}

void EDVRPMessage::setMessageType(int messageType)
{
    this->messageType = messageType;
}

int EDVRPMessage::getRouterId() const
{
    return this->routerId;
}

void EDVRPMessage::setRouterId(int routerId)
{
    this->routerId = routerId;
}

omnetpp::simtime_t EDVRPMessage::getTimestamp() const
{
    return this->timestamp;
}

void EDVRPMessage::setTimestamp(omnetpp::simtime_t timestamp)
{
    this->timestamp = timestamp;
}

const char * EDVRPMessage::getAuthToken() const
{
    return this->authToken.c_str();
}

void EDVRPMessage::setAuthToken(const char * authToken)
{
    this->authToken = authToken;
}

class EDVRPMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_messageType,
        FIELD_routerId,
        FIELD_timestamp,
        FIELD_authToken,
    };
  public:
    EDVRPMessageDescriptor();
    virtual ~EDVRPMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(EDVRPMessageDescriptor)

EDVRPMessageDescriptor::EDVRPMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(EDVRPMessage)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

EDVRPMessageDescriptor::~EDVRPMessageDescriptor()
{
    delete[] propertyNames;
}

bool EDVRPMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<EDVRPMessage *>(obj)!=nullptr;
}

const char **EDVRPMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *EDVRPMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int EDVRPMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int EDVRPMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_messageType
        FD_ISEDITABLE,    // FIELD_routerId
        FD_ISEDITABLE,    // FIELD_timestamp
        FD_ISEDITABLE,    // FIELD_authToken
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *EDVRPMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "messageType",
        "routerId",
        "timestamp",
        "authToken",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int EDVRPMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "messageType") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "routerId") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "timestamp") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "authToken") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *EDVRPMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_messageType
        "int",    // FIELD_routerId
        "omnetpp::simtime_t",    // FIELD_timestamp
        "string",    // FIELD_authToken
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **EDVRPMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_messageType: {
            static const char *names[] = { "enum", "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *EDVRPMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_messageType:
            if (!strcmp(propertyName, "enum")) return "EDVRPMessageType";
            if (!strcmp(propertyName, "enum")) return "EDVRPMessageType";
            return nullptr;
        default: return nullptr;
    }
}

int EDVRPMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    EDVRPMessage *pp = omnetpp::fromAnyPtr<EDVRPMessage>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void EDVRPMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    EDVRPMessage *pp = omnetpp::fromAnyPtr<EDVRPMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'EDVRPMessage'", field);
    }
}

const char *EDVRPMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    EDVRPMessage *pp = omnetpp::fromAnyPtr<EDVRPMessage>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string EDVRPMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    EDVRPMessage *pp = omnetpp::fromAnyPtr<EDVRPMessage>(object); (void)pp;
    switch (field) {
        case FIELD_messageType: return enum2string(pp->getMessageType(), "EDVRPMessageType");
        case FIELD_routerId: return long2string(pp->getRouterId());
        case FIELD_timestamp: return simtime2string(pp->getTimestamp());
        case FIELD_authToken: return oppstring2string(pp->getAuthToken());
        default: return "";
    }
}

void EDVRPMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    EDVRPMessage *pp = omnetpp::fromAnyPtr<EDVRPMessage>(object); (void)pp;
    switch (field) {
        case FIELD_messageType: pp->setMessageType((EDVRPMessageType)string2enum(value, "EDVRPMessageType")); break;
        case FIELD_routerId: pp->setRouterId(string2long(value)); break;
        case FIELD_timestamp: pp->setTimestamp(string2simtime(value)); break;
        case FIELD_authToken: pp->setAuthToken((value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EDVRPMessage'", field);
    }
}

omnetpp::cValue EDVRPMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    EDVRPMessage *pp = omnetpp::fromAnyPtr<EDVRPMessage>(object); (void)pp;
    switch (field) {
        case FIELD_messageType: return pp->getMessageType();
        case FIELD_routerId: return pp->getRouterId();
        case FIELD_timestamp: return pp->getTimestamp().dbl();
        case FIELD_authToken: return pp->getAuthToken();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'EDVRPMessage' as cValue -- field index out of range?", field);
    }
}

void EDVRPMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    EDVRPMessage *pp = omnetpp::fromAnyPtr<EDVRPMessage>(object); (void)pp;
    switch (field) {
        case FIELD_messageType: pp->setMessageType((EDVRPMessageType)value.intValue()); break;
        case FIELD_routerId: pp->setRouterId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_timestamp: pp->setTimestamp(value.doubleValue()); break;
        case FIELD_authToken: pp->setAuthToken(value.stringValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EDVRPMessage'", field);
    }
}

const char *EDVRPMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr EDVRPMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    EDVRPMessage *pp = omnetpp::fromAnyPtr<EDVRPMessage>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void EDVRPMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    EDVRPMessage *pp = omnetpp::fromAnyPtr<EDVRPMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EDVRPMessage'", field);
    }
}

Register_Class(EDVRPHelloMessage)

EDVRPHelloMessage::EDVRPHelloMessage(const char *name, short kind) : ::EDVRPMessage(name, kind)
{
    this->setMessageType(HELLO);
}

EDVRPHelloMessage::EDVRPHelloMessage(const EDVRPHelloMessage& other) : ::EDVRPMessage(other)
{
    copy(other);
}

EDVRPHelloMessage::~EDVRPHelloMessage()
{
}

EDVRPHelloMessage& EDVRPHelloMessage::operator=(const EDVRPHelloMessage& other)
{
    if (this == &other) return *this;
    ::EDVRPMessage::operator=(other);
    copy(other);
    return *this;
}

void EDVRPHelloMessage::copy(const EDVRPHelloMessage& other)
{
}

void EDVRPHelloMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::EDVRPMessage::parsimPack(b);
}

void EDVRPHelloMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::EDVRPMessage::parsimUnpack(b);
}

class EDVRPHelloMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    EDVRPHelloMessageDescriptor();
    virtual ~EDVRPHelloMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(EDVRPHelloMessageDescriptor)

EDVRPHelloMessageDescriptor::EDVRPHelloMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(EDVRPHelloMessage)), "EDVRPMessage")
{
    propertyNames = nullptr;
}

EDVRPHelloMessageDescriptor::~EDVRPHelloMessageDescriptor()
{
    delete[] propertyNames;
}

bool EDVRPHelloMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<EDVRPHelloMessage *>(obj)!=nullptr;
}

const char **EDVRPHelloMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *EDVRPHelloMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int EDVRPHelloMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int EDVRPHelloMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *EDVRPHelloMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int EDVRPHelloMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *EDVRPHelloMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **EDVRPHelloMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *EDVRPHelloMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int EDVRPHelloMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    EDVRPHelloMessage *pp = omnetpp::fromAnyPtr<EDVRPHelloMessage>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void EDVRPHelloMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    EDVRPHelloMessage *pp = omnetpp::fromAnyPtr<EDVRPHelloMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'EDVRPHelloMessage'", field);
    }
}

const char *EDVRPHelloMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    EDVRPHelloMessage *pp = omnetpp::fromAnyPtr<EDVRPHelloMessage>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string EDVRPHelloMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    EDVRPHelloMessage *pp = omnetpp::fromAnyPtr<EDVRPHelloMessage>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void EDVRPHelloMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    EDVRPHelloMessage *pp = omnetpp::fromAnyPtr<EDVRPHelloMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EDVRPHelloMessage'", field);
    }
}

omnetpp::cValue EDVRPHelloMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    EDVRPHelloMessage *pp = omnetpp::fromAnyPtr<EDVRPHelloMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'EDVRPHelloMessage' as cValue -- field index out of range?", field);
    }
}

void EDVRPHelloMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    EDVRPHelloMessage *pp = omnetpp::fromAnyPtr<EDVRPHelloMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EDVRPHelloMessage'", field);
    }
}

const char *EDVRPHelloMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr EDVRPHelloMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    EDVRPHelloMessage *pp = omnetpp::fromAnyPtr<EDVRPHelloMessage>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void EDVRPHelloMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    EDVRPHelloMessage *pp = omnetpp::fromAnyPtr<EDVRPHelloMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EDVRPHelloMessage'", field);
    }
}

RouteEntry::RouteEntry()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const RouteEntry& a)
{
    doParsimPacking(b,a.destinationId);
    doParsimPacking(b,a.cost);
    doParsimPacking(b,a.sequenceNumber);
}

void __doUnpacking(omnetpp::cCommBuffer *b, RouteEntry& a)
{
    doParsimUnpacking(b,a.destinationId);
    doParsimUnpacking(b,a.cost);
    doParsimUnpacking(b,a.sequenceNumber);
}

class RouteEntryDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_destinationId,
        FIELD_cost,
        FIELD_sequenceNumber,
    };
  public:
    RouteEntryDescriptor();
    virtual ~RouteEntryDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(RouteEntryDescriptor)

RouteEntryDescriptor::RouteEntryDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(RouteEntry)), "")
{
    propertyNames = nullptr;
}

RouteEntryDescriptor::~RouteEntryDescriptor()
{
    delete[] propertyNames;
}

bool RouteEntryDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RouteEntry *>(obj)!=nullptr;
}

const char **RouteEntryDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RouteEntryDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RouteEntryDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int RouteEntryDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_destinationId
        FD_ISEDITABLE,    // FIELD_cost
        FD_ISEDITABLE,    // FIELD_sequenceNumber
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *RouteEntryDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "destinationId",
        "cost",
        "sequenceNumber",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int RouteEntryDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "destinationId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "cost") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "sequenceNumber") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *RouteEntryDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_destinationId
        "double",    // FIELD_cost
        "int",    // FIELD_sequenceNumber
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **RouteEntryDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *RouteEntryDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int RouteEntryDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RouteEntry *pp = omnetpp::fromAnyPtr<RouteEntry>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RouteEntryDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RouteEntry *pp = omnetpp::fromAnyPtr<RouteEntry>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RouteEntry'", field);
    }
}

const char *RouteEntryDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RouteEntry *pp = omnetpp::fromAnyPtr<RouteEntry>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RouteEntryDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RouteEntry *pp = omnetpp::fromAnyPtr<RouteEntry>(object); (void)pp;
    switch (field) {
        case FIELD_destinationId: return long2string(pp->destinationId);
        case FIELD_cost: return double2string(pp->cost);
        case FIELD_sequenceNumber: return long2string(pp->sequenceNumber);
        default: return "";
    }
}

void RouteEntryDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RouteEntry *pp = omnetpp::fromAnyPtr<RouteEntry>(object); (void)pp;
    switch (field) {
        case FIELD_destinationId: pp->destinationId = string2long(value); break;
        case FIELD_cost: pp->cost = string2double(value); break;
        case FIELD_sequenceNumber: pp->sequenceNumber = string2long(value); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RouteEntry'", field);
    }
}

omnetpp::cValue RouteEntryDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RouteEntry *pp = omnetpp::fromAnyPtr<RouteEntry>(object); (void)pp;
    switch (field) {
        case FIELD_destinationId: return pp->destinationId;
        case FIELD_cost: return pp->cost;
        case FIELD_sequenceNumber: return pp->sequenceNumber;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RouteEntry' as cValue -- field index out of range?", field);
    }
}

void RouteEntryDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RouteEntry *pp = omnetpp::fromAnyPtr<RouteEntry>(object); (void)pp;
    switch (field) {
        case FIELD_destinationId: pp->destinationId = omnetpp::checked_int_cast<int>(value.intValue()); break;
        case FIELD_cost: pp->cost = value.doubleValue(); break;
        case FIELD_sequenceNumber: pp->sequenceNumber = omnetpp::checked_int_cast<int>(value.intValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RouteEntry'", field);
    }
}

const char *RouteEntryDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr RouteEntryDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RouteEntry *pp = omnetpp::fromAnyPtr<RouteEntry>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RouteEntryDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RouteEntry *pp = omnetpp::fromAnyPtr<RouteEntry>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RouteEntry'", field);
    }
}

Register_Class(EDVRPRoutingUpdateMessage)

EDVRPRoutingUpdateMessage::EDVRPRoutingUpdateMessage(const char *name, short kind) : ::EDVRPMessage(name, kind)
{
    this->setMessageType(ROUTING_UPDATE);

}

EDVRPRoutingUpdateMessage::EDVRPRoutingUpdateMessage(const EDVRPRoutingUpdateMessage& other) : ::EDVRPMessage(other)
{
    copy(other);
}

EDVRPRoutingUpdateMessage::~EDVRPRoutingUpdateMessage()
{
    delete [] this->routes;
}

EDVRPRoutingUpdateMessage& EDVRPRoutingUpdateMessage::operator=(const EDVRPRoutingUpdateMessage& other)
{
    if (this == &other) return *this;
    ::EDVRPMessage::operator=(other);
    copy(other);
    return *this;
}

void EDVRPRoutingUpdateMessage::copy(const EDVRPRoutingUpdateMessage& other)
{
    this->destinationCount = other.destinationCount;
    delete [] this->routes;
    this->routes = (other.routes_arraysize==0) ? nullptr : new RouteEntry[other.routes_arraysize];
    routes_arraysize = other.routes_arraysize;
    for (size_t i = 0; i < routes_arraysize; i++) {
        this->routes[i] = other.routes[i];
    }
}

void EDVRPRoutingUpdateMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::EDVRPMessage::parsimPack(b);
    doParsimPacking(b,this->destinationCount);
    b->pack(routes_arraysize);
    doParsimArrayPacking(b,this->routes,routes_arraysize);
}

void EDVRPRoutingUpdateMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::EDVRPMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->destinationCount);
    delete [] this->routes;
    b->unpack(routes_arraysize);
    if (routes_arraysize == 0) {
        this->routes = nullptr;
    } else {
        this->routes = new RouteEntry[routes_arraysize];
        doParsimArrayUnpacking(b,this->routes,routes_arraysize);
    }
}

int EDVRPRoutingUpdateMessage::getDestinationCount() const
{
    return this->destinationCount;
}

void EDVRPRoutingUpdateMessage::setDestinationCount(int destinationCount)
{
    this->destinationCount = destinationCount;
}

size_t EDVRPRoutingUpdateMessage::getRoutesArraySize() const
{
    return routes_arraysize;
}

const RouteEntry& EDVRPRoutingUpdateMessage::getRoutes(size_t k) const
{
    if (k >= routes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)routes_arraysize, (unsigned long)k);
    return this->routes[k];
}

void EDVRPRoutingUpdateMessage::setRoutesArraySize(size_t newSize)
{
    RouteEntry *routes2 = (newSize==0) ? nullptr : new RouteEntry[newSize];
    size_t minSize = routes_arraysize < newSize ? routes_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        routes2[i] = this->routes[i];
    delete [] this->routes;
    this->routes = routes2;
    routes_arraysize = newSize;
}

void EDVRPRoutingUpdateMessage::setRoutes(size_t k, const RouteEntry& routes)
{
    if (k >= routes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)routes_arraysize, (unsigned long)k);
    this->routes[k] = routes;
}

void EDVRPRoutingUpdateMessage::insertRoutes(size_t k, const RouteEntry& routes)
{
    if (k > routes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)routes_arraysize, (unsigned long)k);
    size_t newSize = routes_arraysize + 1;
    RouteEntry *routes2 = new RouteEntry[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        routes2[i] = this->routes[i];
    routes2[k] = routes;
    for (i = k + 1; i < newSize; i++)
        routes2[i] = this->routes[i-1];
    delete [] this->routes;
    this->routes = routes2;
    routes_arraysize = newSize;
}

void EDVRPRoutingUpdateMessage::appendRoutes(const RouteEntry& routes)
{
    insertRoutes(routes_arraysize, routes);
}

void EDVRPRoutingUpdateMessage::eraseRoutes(size_t k)
{
    if (k >= routes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)routes_arraysize, (unsigned long)k);
    size_t newSize = routes_arraysize - 1;
    RouteEntry *routes2 = (newSize == 0) ? nullptr : new RouteEntry[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        routes2[i] = this->routes[i];
    for (i = k; i < newSize; i++)
        routes2[i] = this->routes[i+1];
    delete [] this->routes;
    this->routes = routes2;
    routes_arraysize = newSize;
}

class EDVRPRoutingUpdateMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_destinationCount,
        FIELD_routes,
    };
  public:
    EDVRPRoutingUpdateMessageDescriptor();
    virtual ~EDVRPRoutingUpdateMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(EDVRPRoutingUpdateMessageDescriptor)

EDVRPRoutingUpdateMessageDescriptor::EDVRPRoutingUpdateMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(EDVRPRoutingUpdateMessage)), "EDVRPMessage")
{
    propertyNames = nullptr;
}

EDVRPRoutingUpdateMessageDescriptor::~EDVRPRoutingUpdateMessageDescriptor()
{
    delete[] propertyNames;
}

bool EDVRPRoutingUpdateMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<EDVRPRoutingUpdateMessage *>(obj)!=nullptr;
}

const char **EDVRPRoutingUpdateMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *EDVRPRoutingUpdateMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int EDVRPRoutingUpdateMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int EDVRPRoutingUpdateMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_destinationCount
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISRESIZABLE,    // FIELD_routes
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *EDVRPRoutingUpdateMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "destinationCount",
        "routes",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int EDVRPRoutingUpdateMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "destinationCount") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "routes") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *EDVRPRoutingUpdateMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_destinationCount
        "RouteEntry",    // FIELD_routes
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **EDVRPRoutingUpdateMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *EDVRPRoutingUpdateMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int EDVRPRoutingUpdateMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    EDVRPRoutingUpdateMessage *pp = omnetpp::fromAnyPtr<EDVRPRoutingUpdateMessage>(object); (void)pp;
    switch (field) {
        case FIELD_routes: return pp->getRoutesArraySize();
        default: return 0;
    }
}

void EDVRPRoutingUpdateMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    EDVRPRoutingUpdateMessage *pp = omnetpp::fromAnyPtr<EDVRPRoutingUpdateMessage>(object); (void)pp;
    switch (field) {
        case FIELD_routes: pp->setRoutesArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'EDVRPRoutingUpdateMessage'", field);
    }
}

const char *EDVRPRoutingUpdateMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    EDVRPRoutingUpdateMessage *pp = omnetpp::fromAnyPtr<EDVRPRoutingUpdateMessage>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string EDVRPRoutingUpdateMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    EDVRPRoutingUpdateMessage *pp = omnetpp::fromAnyPtr<EDVRPRoutingUpdateMessage>(object); (void)pp;
    switch (field) {
        case FIELD_destinationCount: return long2string(pp->getDestinationCount());
        case FIELD_routes: return "";
        default: return "";
    }
}

void EDVRPRoutingUpdateMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    EDVRPRoutingUpdateMessage *pp = omnetpp::fromAnyPtr<EDVRPRoutingUpdateMessage>(object); (void)pp;
    switch (field) {
        case FIELD_destinationCount: pp->setDestinationCount(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EDVRPRoutingUpdateMessage'", field);
    }
}

omnetpp::cValue EDVRPRoutingUpdateMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    EDVRPRoutingUpdateMessage *pp = omnetpp::fromAnyPtr<EDVRPRoutingUpdateMessage>(object); (void)pp;
    switch (field) {
        case FIELD_destinationCount: return pp->getDestinationCount();
        case FIELD_routes: return omnetpp::toAnyPtr(&pp->getRoutes(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'EDVRPRoutingUpdateMessage' as cValue -- field index out of range?", field);
    }
}

void EDVRPRoutingUpdateMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    EDVRPRoutingUpdateMessage *pp = omnetpp::fromAnyPtr<EDVRPRoutingUpdateMessage>(object); (void)pp;
    switch (field) {
        case FIELD_destinationCount: pp->setDestinationCount(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EDVRPRoutingUpdateMessage'", field);
    }
}

const char *EDVRPRoutingUpdateMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_routes: return omnetpp::opp_typename(typeid(RouteEntry));
        default: return nullptr;
    };
}

omnetpp::any_ptr EDVRPRoutingUpdateMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    EDVRPRoutingUpdateMessage *pp = omnetpp::fromAnyPtr<EDVRPRoutingUpdateMessage>(object); (void)pp;
    switch (field) {
        case FIELD_routes: return omnetpp::toAnyPtr(&pp->getRoutes(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void EDVRPRoutingUpdateMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    EDVRPRoutingUpdateMessage *pp = omnetpp::fromAnyPtr<EDVRPRoutingUpdateMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EDVRPRoutingUpdateMessage'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

