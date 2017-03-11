
/*
 *
 * The arduino XBeeAPI library facilitate the management, of XBee Devices configured in API Mode
 * Copyright (C) 2015  Orazio Briante orazio.briante@unirc.it
 * Laboratory A.R.T.S. - University Mediterranea of Reggio Calabria - Faculty of Engineering
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "XBeeComm.h"

extern XBee xbee;

namespace ndn {

  String XBeeComm::recvMessage(XBeeAddress64 & addr64) {

    uint8_t i = 0;
    ZBRxResponse response;
    String ccn_response = String();

    while (true) {
      xbee.readPacket();
      if (xbee.getResponse().isAvailable()) {

        if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
          response = ZBRxResponse();
          addr64 = response.getRemoteAddress64();
          xbee.getResponse().getZBRxResponse(response);

          uint8_t *rxData = response.getData();
          uint8_t rxLength = response.getDataLength();

          for (i = 0; i < rxLength; i++)
              ccn_response += String((char)rxData[i]);

            return ccn_response;
        }
      }
    } return ccn_response;
  }

  String XBeeComm::recvMessage(XBeeAddress64 & addr64, const unsigned long timeout) {

    unsigned long previousMillis = millis();
    unsigned long currentMillis = 0;

    int _timeout = timeout;
    uint8_t i = 0;
    ZBRxResponse response;
    String ccn_response = String();

    while (_timeout > 0) {
      if (xbee.readPacket(_timeout)) {
        if (xbee.getResponse().isAvailable()) {
          if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
            response = ZBRxResponse();
            xbee.getResponse().getZBRxResponse(response);

            uint8_t *rxData = response.getData();
            uint8_t rxLength = response.getDataLength();

            for (i = 0; i < rxLength; i++)
              ccn_response += String((char)rxData[i]);

            return ccn_response;
          }
        }

      }

      currentMillis = millis();
      _timeout = _timeout - ((int)(currentMillis - previousMillis));
    }
    return ccn_response;
  }

  void
   
    XBeeComm::sendMessage(XBeeAddress64 addr64, uint16_t addr16, const uint8_t broadcast_radius,
                          const uint8_t option, const String & message) {

    unsigned int number_of_fragments;

    unsigned int last_fragment_length = message.length() % MAX_PAYLOAD_SIZE;
    if (last_fragment_length)
      number_of_fragments = ((message.length() - last_fragment_length)
                             / MAX_PAYLOAD_SIZE) + 1;
    else
      number_of_fragments = message.length() / MAX_PAYLOAD_SIZE;

    for (int i = 0; i < number_of_fragments; i++) {

      if (i < number_of_fragments - 1) {

        uint8_t payload[MAX_PAYLOAD_SIZE];

        for (int k = 0; k < MAX_PAYLOAD_SIZE; k++) {
          payload[k] = message[i * 72 + k];
        }

        ZBTxRequest zbTXRequest = ZBTxRequest(addr64, addr16,
                                              broadcast_radius, option,
                                              payload, sizeof(payload),
                                              i + 1);

        xbee.send(zbTXRequest);
      } else {

        uint8_t payload[last_fragment_length];

        for (int k = 0; k < last_fragment_length; k++) {
          payload[k] = message[i * 72 + k];
        }

/*	  ZBTxRequest zbTXRequest = ZBTxRequest (addr64, addr16,
						 broadcast_radius, option,
						 payload, last_fragment_length,
						 i + 1);*/

        ZBTxRequest zbTXRequest = ZBTxRequest(addr64, payload, last_fragment_length);

        xbee.send(zbTXRequest);

      }
      //delay (DEFAULT_DELAY);
    }
  }

}                               /* namespace ndn */
