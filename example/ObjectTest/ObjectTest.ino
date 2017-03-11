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

#include "XBee.h"
#include "lNDN.h"
#include "Dummy.h"

using namespace ndn;

void setup(){

  Serial.begin(9600);

  Dummy dummy=Dummy();
  Serial.println(dummy.getURI());
  Serial.println(dummy.toString());
  
  dummy.setURI("/Temperature/Kitchen//");
  Serial.println(dummy.getURI());
  Serial.println(dummy.toString());

  dummy.action("");
  Serial.println(dummy.getURI());
  Serial.println(dummy.toString());
  


URI uri=URI("r:/Temperature/Kitchen//");

  if(dummy.isThisPath (uri))
    Serial.println("Is this path.");
  else
    Serial.println("Is not this path.");

  if(dummy.isThisObject(uri))
    Serial.println("Is this Object.");
  else
    Serial.println("Is not this Object.");


  dummy.~Dummy();
  uri.~URI();
}

void loop(){
}
