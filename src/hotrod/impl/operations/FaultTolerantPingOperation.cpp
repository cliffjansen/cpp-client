

#include "hotrod/sys/types.h"
#include "hotrod/impl/operations/FaultTolerantPingOperation.h"
#include "hotrod/impl/operations/PingOperation.h"

namespace infinispan {
namespace hotrod {
namespace operations {

using namespace infinispan::hotrod::protocol;
using namespace infinispan::hotrod::transport;

FaultTolerantPingOperation::FaultTolerantPingOperation(
    const Codec&      codec_,
    transport::TransportFactory* transportFactory_,
    const hrbytes&    cacheName_,
    uint32_t          topologyId_,
    uint32_t    flags_)
    : RetryOnFailureOperation<PingResult>(
        codec_, transportFactory_, cacheName_, topologyId_, flags_)
{}

Transport& FaultTolerantPingOperation::getTransport(int /*retryCount*/)
{
        return RetryOnFailureOperation<PingResult>::transportFactory->getTransport();
}

PingResult FaultTolerantPingOperation::executeOperation(transport::Transport& transport)
{

    return (new PingOperation(codec, topologyId, transport, cacheName))->execute();
}

}}} /// namespace infinispan::hotrod::operations
