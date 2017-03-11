
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

#include "Object.h"

namespace ndn {

  Object::Object():URI() {
    this->type = ANSWER;
  } Object::Object(const String uri):URI(uri) {
    this->type = ANSWER;
  }

  Object::~Object() {
    this->~URI();
  }

  void Object::setURI(const String & uri) {
    this->URI::setURI(uri);
    this->type = ANSWER;
  }


  String Object::toString() const {
    return "Object: {" + this->URI::toString() + "}";
}}                                     /* namespace ndn */
