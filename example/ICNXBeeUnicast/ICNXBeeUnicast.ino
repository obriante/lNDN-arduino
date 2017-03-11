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

#include "Arduino.h"
#include "XBee.h"
#include "lNDN.h"
#include "Dummy.h"

using namespace ndn;


#define DEFAULT_TIMEOUT 10000

XBee xbee=XBee();
Dummy dummy=Dummy("/Temperature/Kitchen//");

URI uri=URI();

void setup(){

  Serial.begin(9600);
  Serial1.begin(9600);
  xbee.begin(Serial);

  Serial1.println(dummy.toString());

  Serial1.println("Waiting request..");
}

void loop(){
  XBeeAddress64 addr64=XBeeAddress64();

  uri.receive(addr64);
  Serial1.print("From: ");
  Serial1.print("[");
  Serial1.print(addr64.getMsb());
  Serial1.print(",");
  Serial1.print(addr64.getLsb());
  Serial1.println("]");
  Serial1.println("["+uri.getURI()+"]\n");

  if(uri.getType()==URI::REQUEST)
    if(dummy.isThisObject(uri) && dummy.isThisPath(uri)){
    dummy.action();
	dummy.send();
	Serial1.print("Answer: [");
	Serial1.print(dummy.getURI());
	Serial1.println("]\n");
    }
}
