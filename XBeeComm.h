
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

#ifndef XBEECOMM_H_
#define XBEECOMM_H_

#include "Arduino.h"

#include "XBee.h"

namespace ndn {

#define MAX_PAYLOAD_SIZE		72
#define	DEFAULT_DELAY			1000

#define BDR_MAC_HIGH			0x00000000
#define BDR_MAC_LOW			0x0000FFFF

#define MAX_BROADCAST_RADIUS_FWD	1

  class XBeeComm {
  public:
    static String recvMessage(XBeeAddress64 & addr64);

    static String recvMessage(XBeeAddress64 & addr64, const unsigned long timeout);

    static void

     
      sendMessage(XBeeAddress64 addr64, uint16_t addr16, const uint8_t broadcast_radius, const uint8_t option,
                  const String & message);
  };
}                                      /* namespace ndn */
#endif                                 /* XBEECOMM_H_ */
