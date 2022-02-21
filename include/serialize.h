/**
 * @file serialize.h
 * 
 * @brief Serialization and deserialization.
 * 
 * @see https://isocpp.org/wiki/faq/serialization#serialize-text-format
 * @see http://erights.org/data/serial/jhu-paper/intro.html
 */
#ifndef SERIALIZE__H
#define SERIALIZE__H

#include "dns_proto.h"
#include "parameters.h"
#include "alloc.h"
#include "compress.h"
#include <stdint.h>

/**
 * @brief Serialize the input DNS request into a packet.
 * 
 * @return A buffer/packet which contains serialized data.
 */
uint8_t *serialize(dns_msg_t *msg, const size_t align);

/**
 * @brief Deserialize the input packet into a DNS request structure.
 * 
 * @return A DNS request struture which contains transfered data.
 */
dns_msg_t *deserialize(const uint16_t xid, uint8_t *pck);

#endif  //SERIALIZE__H
