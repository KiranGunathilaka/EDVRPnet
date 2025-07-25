//
// Generated file, do not edit! Created by opp_msgtool 6.1 from EDVRPMessage.msg.
//

#ifndef __EDVRPMESSAGE_M_H
#define __EDVRPMESSAGE_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// opp_msgtool version check
#define MSGC_VERSION 0x0601
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgtool: 'make clean' should help.
#endif

class EDVRPMessage;
class EDVRPHelloMessage;
struct RouteEntry;
class EDVRPRoutingUpdateMessage;
/**
 * Enum generated from <tt>EDVRPMessage.msg:3</tt> by opp_msgtool.
 * <pre>
 * enum EDVRPMessageType
 * {
 *     HELLO = 1;
 *     ROUTING_UPDATE = 2;
 * }
 * </pre>
 */
enum EDVRPMessageType {
    HELLO = 1,
    ROUTING_UPDATE = 2
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const EDVRPMessageType& e) { b->pack(static_cast<int>(e)); }
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, EDVRPMessageType& e) { int n; b->unpack(n); e = static_cast<EDVRPMessageType>(n); }

/**
 * Class generated from <tt>EDVRPMessage.msg:12</tt> by opp_msgtool.
 * <pre>
 * //
 * // Base message for EDVRP protocol
 * //
 * packet EDVRPMessage
 * {
 *     int messageType \@enum(EDVRPMessageType);
 *     int routerId;
 *     simtime_t timestamp;
 *     string authToken = "";
 * }
 * </pre>
 */
class EDVRPMessage : public ::omnetpp::cPacket
{
  protected:
    int messageType = 0;
    int routerId = 0;
    omnetpp::simtime_t timestamp = SIMTIME_ZERO;
    omnetpp::opp_string authToken = "";

  private:
    void copy(const EDVRPMessage& other);

  protected:
    bool operator==(const EDVRPMessage&) = delete;

  public:
    EDVRPMessage(const char *name=nullptr, short kind=0);
    EDVRPMessage(const EDVRPMessage& other);
    virtual ~EDVRPMessage();
    EDVRPMessage& operator=(const EDVRPMessage& other);
    virtual EDVRPMessage *dup() const override {return new EDVRPMessage(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual int getMessageType() const;
    virtual void setMessageType(int messageType);

    virtual int getRouterId() const;
    virtual void setRouterId(int routerId);

    virtual omnetpp::simtime_t getTimestamp() const;
    virtual void setTimestamp(omnetpp::simtime_t timestamp);

    virtual const char * getAuthToken() const;
    virtual void setAuthToken(const char * authToken);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const EDVRPMessage& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, EDVRPMessage& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>EDVRPMessage.msg:23</tt> by opp_msgtool.
 * <pre>
 * //
 * // Hello message for neighbor discovery
 * //
 * packet EDVRPHelloMessage extends EDVRPMessage
 * {
 *     messageType = HELLO;
 * }
 * </pre>
 */
class EDVRPHelloMessage : public ::EDVRPMessage
{
  protected:

  private:
    void copy(const EDVRPHelloMessage& other);

  protected:
    bool operator==(const EDVRPHelloMessage&) = delete;

  public:
    EDVRPHelloMessage(const char *name=nullptr, short kind=0);
    EDVRPHelloMessage(const EDVRPHelloMessage& other);
    virtual ~EDVRPHelloMessage();
    EDVRPHelloMessage& operator=(const EDVRPHelloMessage& other);
    virtual EDVRPHelloMessage *dup() const override {return new EDVRPHelloMessage(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const EDVRPHelloMessage& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, EDVRPHelloMessage& obj) {obj.parsimUnpack(b);}

/**
 * Struct generated from EDVRPMessage.msg:31 by opp_msgtool.
 */
struct RouteEntry
{
    RouteEntry();
    int destinationId = 0;
    double cost = 0;
    int sequenceNumber = 0;
};

// helpers for local use
void __doPacking(omnetpp::cCommBuffer *b, const RouteEntry& a);
void __doUnpacking(omnetpp::cCommBuffer *b, RouteEntry& a);

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RouteEntry& obj) { __doPacking(b, obj); }
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RouteEntry& obj) { __doUnpacking(b, obj); }

/**
 * Class generated from <tt>EDVRPMessage.msg:41</tt> by opp_msgtool.
 * <pre>
 * //
 * // Routing update message
 * //
 * packet EDVRPRoutingUpdateMessage extends EDVRPMessage
 * {
 *     messageType = ROUTING_UPDATE;
 *     int destinationCount;
 *     RouteEntry routes[];
 * }
 * </pre>
 */
class EDVRPRoutingUpdateMessage : public ::EDVRPMessage
{
  protected:
    int destinationCount = 0;
    RouteEntry *routes = nullptr;
    size_t routes_arraysize = 0;

  private:
    void copy(const EDVRPRoutingUpdateMessage& other);

  protected:
    bool operator==(const EDVRPRoutingUpdateMessage&) = delete;

  public:
    EDVRPRoutingUpdateMessage(const char *name=nullptr, short kind=0);
    EDVRPRoutingUpdateMessage(const EDVRPRoutingUpdateMessage& other);
    virtual ~EDVRPRoutingUpdateMessage();
    EDVRPRoutingUpdateMessage& operator=(const EDVRPRoutingUpdateMessage& other);
    virtual EDVRPRoutingUpdateMessage *dup() const override {return new EDVRPRoutingUpdateMessage(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual int getDestinationCount() const;
    virtual void setDestinationCount(int destinationCount);

    virtual void setRoutesArraySize(size_t size);
    virtual size_t getRoutesArraySize() const;
    virtual const RouteEntry& getRoutes(size_t k) const;
    virtual RouteEntry& getRoutesForUpdate(size_t k) { return const_cast<RouteEntry&>(const_cast<EDVRPRoutingUpdateMessage*>(this)->getRoutes(k));}
    virtual void setRoutes(size_t k, const RouteEntry& routes);
    virtual void insertRoutes(size_t k, const RouteEntry& routes);
    [[deprecated]] void insertRoutes(const RouteEntry& routes) {appendRoutes(routes);}
    virtual void appendRoutes(const RouteEntry& routes);
    virtual void eraseRoutes(size_t k);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const EDVRPRoutingUpdateMessage& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, EDVRPRoutingUpdateMessage& obj) {obj.parsimUnpack(b);}


namespace omnetpp {

template<> inline EDVRPMessage *fromAnyPtr(any_ptr ptr) { return check_and_cast<EDVRPMessage*>(ptr.get<cObject>()); }
template<> inline EDVRPHelloMessage *fromAnyPtr(any_ptr ptr) { return check_and_cast<EDVRPHelloMessage*>(ptr.get<cObject>()); }
inline any_ptr toAnyPtr(const RouteEntry *p) {return any_ptr(p);}
template<> inline RouteEntry *fromAnyPtr(any_ptr ptr) { return ptr.get<RouteEntry>(); }
template<> inline EDVRPRoutingUpdateMessage *fromAnyPtr(any_ptr ptr) { return check_and_cast<EDVRPRoutingUpdateMessage*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __EDVRPMESSAGE_M_H

