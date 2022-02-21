# NOTES

## Makefile

 CC : compilateur utilisée
 CFLAGS : options de compilation
 $@ : nom de la cible
 $< : nom de la premiere dependance
 $ˆ : liste des dependances
 $? : liste des dependances plus recentes que la cible
 $* : nom d un fichier sans son suffixe

## DNS protocol

The DNS message structure contains header information (an unique id,
flags and number of answer, authority and additionnal resource records),
a query type, a domain name, and a list of resource record.

A resource record is a struture which store all information send by a
server to resolve a domain name: an owner domain name, a query type,
a Time To Live, the length of the response and the response.
According to the situation, the list in the message can store answer,
authority and/or additional resource records.

The DNS message structure respect as much as possible the RFC 1035, but
differs in some aspects. Each message contains only one question
(the domain name to be resolved and its type), then it is not necessary
to store the number of question. The query class is also never stored
because it is always assumed to be Internet class.

## Send/Recv message

/* At the end of a packet, indicate that the next packet must start
   a new DNS message. */
#define CHAR_START_NEW_DNS_MESSAGE  ';'

/* At the end of a packet, indicate that there is no more packet to be send. */
#define CHAR_NO_MORE_PACKET         '!'

  const bool one_more_msg
{
  /* Finally, we indicate if it is or not the end of the transmission. */
  msg[la - 1] = (one_more_msg) ? CHAR_NO_MORE_PACKET : CHAR_START_NEW_DNS_MESSAGE;
}




