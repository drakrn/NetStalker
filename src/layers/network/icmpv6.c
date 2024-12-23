/**
 * @author Flavien Lallemant
 * @file icmpv6.c
 * @brief ICMPv6 layer
 * @ingroup network
 * 
 * This file contains the implementation of the ICMPv6 layer.
 * 
 * @see icmpv6.h
 * @see cast_icmp6
 */

// Global libraries
#include <stdio.h>
#include <stdlib.h>

// Local header files
#include "icmpv6.h"

static const char *destination_unreachable_message_v6[] = {
    "No route to destination",
    "Communication with destination administratively prohibited",
    "Beyond scope of source address",
    "Port unreachable",
    "Source address failed ingress/egress policy",
    "Reject route to destination",
    "Error in source routing header"}; /**< Destination unreachable messages */
static const char *time_exceeded_message_v6[] = {
    "Hop limit exceeded in transit", "Fragment reassembly time exceeded"}; /**< Time exceeded messages */
static const char *bad_ip_header_message_v6[] = {
    "Erroneous header field encountered",
    "Unrecognized Next Header type encountered",
    "Unrecognized IPv6 option encountered"}; /**< Bad IP header messages */
static const char *extended_echo_reply_message_v6[] = {
    "No error", "Malformed query", "No such interface", "No such table entry",
    "Multipe interfaces satisfy query"}; /**< Extended echo reply messages */


/**
 * @brief Handle an ICMPv6 message
 * 
 * This function handles an ICMPv6 message.
 * 
 * @param icmp6 The ICMPv6 header
 * @return int 0 if the message is well handled, -1 otherwise
 */
static int message_handler(const struct icmp6_hdr *icmp6)
{
    switch (icmp6->icmp6_type) {
    case ICMP6_DST_UNREACH: // ICMPv6 Destination Unreachable
        if (icmp6->icmp6_code > 7) {
            fprintf(stderr, "Bad ICMP6 code\n");
            return (-1);
        }
        printf("ICMP6 Destination Unreachable: %s\n",
               destination_unreachable_message_v6[icmp6->icmp6_code]);
        break;
    case ICMP6_PACKET_TOO_BIG: // ICMPv6 Packet too big
        if (icmp6->icmp6_code > 0) {
            fprintf(stderr, "Bad ICMP6 code\n");
            return (-1);
        }
        printf("ICMP6 Packet too big\n");
        break;
    case ICMP6_TIME_EXCEEDED: // ICMPv6 Time Exceeded
        if (icmp6->icmp6_code > 0) {
            fprintf(stderr, "Bad ICMP code\n");
            return (-1);
        }
        printf("ICMP6 Time Exceeded: %s\n",
               time_exceeded_message_v6[icmp6->icmp6_code]);
        break;
    case ICMP6_PARAM_PROB: // ICMPv6 Parameter Problem
        if (icmp6->icmp6_code > 0) {
            fprintf(stderr, "Bad ICMP code\n");
            return (-1);
        }
        printf("ICMP6 Bad IP header: %s\n",
               bad_ip_header_message_v6[icmp6->icmp6_code]);
        break;
    case ICMP6_ECHO_REQUEST: // ICMPv6 Echo Request
        if (icmp6->icmp6_code > 0) {
            fprintf(stderr, "Bad ICMP code\n");
            return (-1);
        }
        printf("ICMP6 Echo Request");
        break;
    case ICMP6_ECHO_REPLY: // ICMPv6 Echo Reply
        if (icmp6->icmp6_code > 0) {
            fprintf(stderr, "Bad ICMP code\n");
            return (-1);
        }
        printf("ICMP6 Echo Reply\n");
        break;
    case MLD_LISTENER_QUERY: // MLD Multicast Listener Query
        if (icmp6->icmp6_code > 0) {
            fprintf(stderr, "Bad ICMP code\n");
            return (-1);
        }
        printf("MLD Multicast Listener Query\n");
        break;
    case MLD_LISTENER_REPORT: // MLD Multicast Listener Report
        if (icmp6->icmp6_code > 0) {
            fprintf(stderr, "Bad ICMP code\n");
            return (-1);
        }
        printf("MLD Multicast Listener Report\n");
        break;
    case MLD_LISTENER_REDUCTION: // MLD Multicast Listener Reduction
        if (icmp6->icmp6_code > 0) {
            fprintf(stderr, "Bad ICMP code\n");
            return (-1);
        }
        printf("MLD Multicast Listener Done\n");
        break;
    case ND_ROUTER_SOLICIT: // NDP Router Solicitation
        if (icmp6->icmp6_code > 0) {
            fprintf(stderr, "Bad ICMP code\n");
            return (-1);
        }
        printf("NDP Router Solicitation\n");
        break;
    case ND_ROUTER_ADVERT: // NDP Router Advertisement
        if (icmp6->icmp6_code > 0) {
            fprintf(stderr, "Bad ICMP code\n");
            return (-1);
        }
        printf("NDP Router Advertisement\n");
        break;
    case ND_NEIGHBOR_SOLICIT: // NDP Neighbor Solicitation
        if (icmp6->icmp6_code > 0) {
            fprintf(stderr, "Bad ICMP code\n");
            return (-1);
        }
        printf("NDP Neighbor Solicitation\n");
        break;
    case ND_NEIGHBOR_ADVERT: // NDP Neighbor Advertisement
        if (icmp6->icmp6_code > 0) {
            fprintf(stderr, "Bad ICMP code\n");
            return (-1);
        }
        printf("NDP Neighbor Advertisement\n");
        break;
    case ND_REDIRECT: // NDP Redirect Message
        if (icmp6->icmp6_code > 0) {
            fprintf(stderr, "Bad ICMP code\n");
            return (-1);
        }
        printf("NDP Redirect Message\n");
        break;
    case ICMP6_ROUTER_RENUMBERING: // ICMPv6 Router Renumbering
        if (icmp6->icmp6_code > 1 && icmp6->icmp6_code < 255) {
            fprintf(stderr, "Bad ICMP code\n");
            return (-1);
        }
        printf("ICMP6 Router Renumbering\n");
        break;
    case ICMP6_NODE_INFORMATION_QUERY: // ICMPv6 Node Information Query
        if (icmp6->icmp6_code > 2) {
            fprintf(stderr, "Bad ICMP code\n");
            return (-1);
        }
        printf("ICMP6 Node Information Query\n");
        break;
    case ICMP6_NODE_INFORMATION_RESPONSE: // ICMPv6 Node Information Response
        if (icmp6->icmp6_code > 2) {
            fprintf(stderr, "Bad ICMP code\n");
            return (-1);
        }
        printf("ICMP6 Node Information Response\n");
        break;
    case ICMP6_INVERSE_NEIGHBOR_DISCOVERY_SOLICITATION_MESSAGE: // ICMPv6 Inverse Neighbor Discovery Solicitation
        if (icmp6->icmp6_code > 0) {
            fprintf(stderr, "Bad ICMP code\n");
            return (-1);
        }
        printf("ICMP6 Inverse Neighbor Discovery Solicitation message\n");
        break;
    case ICMP6_INVERSE_NEIGHBOR_DISCOVERY_ADVERTISEMENT_MESSAGE: // ICMPv6 Inverse Neighbor Discovery Advertisement
        if (icmp6->icmp6_code > 0) {
            fprintf(stderr, "Bad ICMP code\n");
            return (-1);
        }
        printf("ICMP6 Inverse Neighbor Discovery Advertisement messsage\n");
        break;
    case ICMP6_MULTICAST_LISTENER_DISCOVERY_REPORTS: // ICMPv6 Multicast Listener Discovery Reports
        if (icmp6->icmp6_code > 0) {
            fprintf(stderr, "Bad ICMP code\n");
            return (-1);
        }
        printf("ICMP6 Multicast Listener Discovery Reports\n");
        break;
    case ICMP6_HOME_AGENT_ADDRESS_DISCOVERY_REQUEST: // ICMPv6 Home Agent Address Discovery Request
        if (icmp6->icmp6_code > 0) {
            fprintf(stderr, "Bad ICMP code\n");
            return (-1);
        }
        printf("ICMP6 Home Agent Address Discovery Request\n");
        break;
    case ICMP6_HOME_AGENT_ADDRESS_DISCOVERY_REPLY: // ICMPv6 Home Agent Address Discovery Reply
        if (icmp6->icmp6_code > 0) {
            fprintf(stderr, "Bad ICMP code\n");
            return (-1);
        }
        printf("ICMP6 Home Agent Address Discovery Reply\n");
        break;
    case ICMP6_MOBILE_PREFIX_SOLICITATION: // ICMPv6 Mobile Prefix Solicitation
        if (icmp6->icmp6_code > 0) {
            fprintf(stderr, "Bad ICMP code\n");
            return (-1);
        }
        printf("ICMP6 Mobile Prefix Solicitation\n");
        break;
    case ICMP6_MOBILE_PREFIX_ADVERTISEMENT: // ICMPv6 Mobile Prefix Advertisement
        if (icmp6->icmp6_code > 0) {
            fprintf(stderr, "Bad ICMP code\n");
            return (-1);
        }
        printf("ICMP6 Mobile Prefix Advertisement\n");
        break;
    case ICMP6_CERTIFICATION_PATH_SOLICITATION: // ICMPv6 Certification Path Solicitation
        if (icmp6->icmp6_code > 0) {
            fprintf(stderr, "Bad ICMP code\n");
            return (-1);
        }
        printf("ICMP6 Certififcation Path Solicitation\n");
        break;
    case ICMP6_CERTIFICATION_PATH_ADVERTISEMENT: // ICMPv6 Certification Path Advertisement
        if (icmp6->icmp6_code > 0) {
            fprintf(stderr, "Bad ICMP code\n");
            return (-1);
        }
        printf("ICMP6 Certification Path Advertisement\n");
        break;
    case ICMP6_MULTICAST_ROUTER_SOLICITATION: // ICMPv6 Multicast Router Solicitation
        if (icmp6->icmp6_code > 0) {
            fprintf(stderr, "Bad ICMP code\n");
            return (-1);
        }
        printf("ICMP6 Multicast Router Solicitation\n");
        break;
    case ICMP6_MULTICAST_ROUTER_ADVERTISEMENT: // ICMPv6 Multicast Router Advertisement
        if (icmp6->icmp6_code > 0) {
            fprintf(stderr, "Bad ICMP code\n");
            return (-1);
        }
        printf("ICMP6 Multicast Router Advertisement\n");
        break;
    case ICMP6_MULTICAST_ROUTER_TERMINATION: // ICMPv6 Multicast Router Termination
        if (icmp6->icmp6_code > 0) {
            fprintf(stderr, "Bad ICMP code\n");
            return (-1);
        }
        printf("ICMP6 Multicast Router Termination\n");
        break;
    case ICMP6_RPL_CONTROL_MESSAGE: // ICMPv6 RPL Control Message
        if (icmp6->icmp6_code > 0) {
            fprintf(stderr, "Bad ICMP code\n");
            return (-1);
        }
        printf("ICMP6 RPL Control Message\n");
        break;
    case ICMPV6_EXT_ECHO_REQUEST: // ICMPv6 Extended Echo Request
        if (icmp6->icmp6_code > 0) {
            fprintf(stderr, "Bad ICMP code\n");
            return (-1);
        }
        printf("ICMP6 Extended Echo Request\n");
        break;
    case ICMPV6_EXT_ECHO_REPLY: // ICMPv6 Extended Echo Reply
        if (icmp6->icmp6_code > 0) {
            fprintf(stderr, "Bad ICMP code\n");
            return (-1);
        }
        printf("ICMP6 Extended Echo Reply: %s\n",
               extended_echo_reply_message_v6[icmp6->icmp6_code]);
        break;
    default:
        fprintf(stderr, "Unknown ICMP type. ICMP TYPE: 0x%x\n",
                icmp6->icmp6_code);
        break;
    }
    return 0;
}


/**
 * @brief Handle an ICMPv6 packet
 * 
 * This function handles an ICMPv6 packet.
 * 
 * @param packet The packet to handle
 * @return int 0 if the packet is well handled
 * @see message_handler
 */
int cast_icmp6(const u_char *packet)
{
    const struct icmp6_hdr *icmp6;
    icmp6 = (struct icmp6_hdr *)(packet);
    message_handler(icmp6);
    return 0;
}
