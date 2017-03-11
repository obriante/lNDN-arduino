
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

#include "URI.h"
#include "XBeeComm.h"

namespace ndn {
  URI::URI() {
    this->object = String();
    this->path = String();
    this->value = String();
    this->type = CLEAN;
  } URI::URI(const String uri) {
    this->object = String();
    this->path = String();
    this->value = String();
    this->type = CLEAN;

    this->setURI(uri);
  }

  URI::URI(const String object, const String path) {
    this->object = String(object);
    this->path = String(path);
    this->value = String();
    this->type = CLEAN;
  }

  URI::URI(const String object, const String path, const Type type) {
    this->object = String(object);
    this->path = String(path);
    this->value = String();
    this->type = type;
  }


  URI::URI(const String object, const String path, const String value, const Type type) {
    this->object = String(object);
    this->path = String(path);
    this->value = String(value);
    this->type = type;
  }

  URI::~URI() {
    this->object. ~ String();
    this->path. ~ String();
    this->value. ~ String();
  }

  String URI::getObject() const {
    return object;
  } void URI::setObject(const String object) {
    this->object = object;
  }

  String URI::getPath() const {
    return path;
  } void URI::setPath(const String path) {
    this->path = path;
  }

  String URI::getValue() const {
    return value;
  } void URI::setValue(const String value) {
    this->value = value;
  }

  URI::Type URI::getType()const {
    return type;
  } void
    URI::setType(URI::Type type) {
    this->type = type;
  }

  void URI::setURI(const String & uri) {

    this->object = String();
    this->path = String();
    this->value = String();

    this->type = CLEAN;

    if (uri.endsWith(NDN_CLOSE_DELIMITER) &&
        (uri.startsWith(NDN_REQ) || uri.startsWith(NDN_ANS) || uri.startsWith(NDN_PATH_DELIMITER))) {

      String cleanURI = String(uri);

      if (uri.startsWith(NDN_REQ)) {
        this->type = REQUEST;
        cleanURI = cleanURI.substring(cleanURI.indexOf(NDN_REQ) + NDN_REQ_SIZE, cleanURI.indexOf(NDN_CLOSE_DELIMITER));
      } else if (uri.startsWith(NDN_ANS)) {
        this->type = ANSWER;
        cleanURI = cleanURI.substring(cleanURI.indexOf(NDN_ANS) + NDN_ANS_SIZE, cleanURI.indexOf(NDN_CLOSE_DELIMITER));
      }

      cleanURI = cleanURI.substring(NDN_PATH_DELIMITER_SIZE, cleanURI.indexOf(NDN_CLOSE_DELIMITER));

      this->object = cleanURI.substring(0, cleanURI.indexOf(NDN_PATH_DELIMITER));

      if (cleanURI.indexOf(NDN_DELIMITER) >= 0) {
        this->path = cleanURI.substring(cleanURI.indexOf(NDN_PATH_DELIMITER), cleanURI.indexOf(NDN_DELIMITER));
        this->value = cleanURI.substring(cleanURI.indexOf(NDN_DELIMITER) + NDN_DELIMITER_SIZE);
      } else {
        this->path = cleanURI.substring(cleanURI.indexOf(NDN_PATH_DELIMITER));
      }
    }
  }


  String URI::getURI() const {

    String s = String(NDN_PATH_DELIMITER);

    if (object)
      if (object.length() > 0)
          s = s + object;

    if (path)
      if (path.length() > 0)
          s = s + path;

    if (value)
      if (value.length() > 0)
          s = s + NDN_DELIMITER + value;

    if (this->type == REQUEST)
      return NDN_REQ + s + NDN_CLOSE_DELIMITER;
    else if (this->type == ANSWER)
      return NDN_ANS + s + NDN_CLOSE_DELIMITER;

      return s;
  } String URI::toString() const {

    String s = String("URI: { object=" + object + ", path=" + path + ", value=" + value + ", type=");

    if (this->type == REQUEST)
      s = s + "REQUEST";
    else if (this->type == ANSWER)
      s = s + "ANSWER";
    else
        s = s + "CLEAN";

      s = s + "}";

      return s;
  } boolean URI::equals(const URI & uri) {
    if (this->object.equals(uri.getObject()) && this->path.equals(uri.getPath()) && this->value.equals(uri.getValue())
        && this->type == uri.getType())
      return true;

    return false;
  }

  boolean URI::isThisObject(const URI & uri)const {
    if (this->object.equals(uri.object) || uri.getObject().equals(NDN_JOLLY_OBJ))
      return true;

    return false;
  } boolean URI::isThisPath(const URI & uri)const {
    if (this->path.equals(uri.path) || uri.getPath().equals(NDN_JOLLY_PATH))
      return true;

    return false;
  } void
    URI::send() {
    XBeeComm::sendMessage(XBeeAddress64(BDR_MAC_HIGH, BDR_MAC_LOW), ZB_BROADCAST_ADDRESS,
                          MAX_BROADCAST_RADIUS_FWD, ZB_TX_BROADCAST, getURI());
  }

  void
    URI::send(const XBeeAddress64 & addr64) {
    XBeeComm::sendMessage(addr64, ZB_BROADCAST_ADDRESS, MAX_BROADCAST_RADIUS_FWD, ZB_TX_UNICAST, getURI());
  }

  void
    URI::receive(XBeeAddress64 & addr64) {
    String msg = XBeeComm::recvMessage(addr64);
    setURI(msg);
  }

  void
    URI::receive(XBeeAddress64 & addr64, const unsigned long timeout) {
    String msg = XBeeComm::recvMessage(addr64, timeout);
    setURI(msg);
  }

}                               /* namespace ndn */
