
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

#ifndef URI_H_
#define URI_H_

#include "Arduino.h"
#include "XBee.h"

namespace ndn {

#define NDN_DELIMITER ":"
#define NDN_DELIMITER_SIZE 1

#define NDN_PATH_DELIMITER "/"
#define NDN_PATH_DELIMITER_SIZE 1

#define NDN_CLOSE_DELIMITER      "//"
#define NDN_CLOSE_DELIMITER_SIZE  2

#define NDN_JOLLY_PATH "/*"
#define NDN_JOLLY_PATH_SIZE 2

#define NDN_JOLLY_OBJ "*"
#define NDN_JOLLY_OBJ_SIZE 1

#define NDN_REQ      "r:"
#define NDN_REQ_SIZE  2

#define NDN_ANS      "a:"
#define NDN_ANS_SIZE  2

  class URI {

  public:
    enum Type {
      ANSWER = 0,
      REQUEST,
      CLEAN
    };

  protected:
      String object;
    String path;
    String value;
    Type type;

  public:
      URI();
      URI(const String uri);
      URI(const String object, const String path);
      URI(const String object, const String path, const URI::Type type);
      URI(const String object, const String path, const String value, const URI::Type type);

      virtual ~ URI();

    String getObject() const;
    void setObject(const String object);
    String getPath() const;
    void setPath(const String path);
    String getValue() const;
    void setValue(const String value);
      URI::Type getType() const;
    void setType(URI::Type type);
    void setURI(const String & uri);
    String getURI() const;

    String toString() const;
    boolean isThisObject(const URI & uri) const;
    boolean isThisPath(const URI & uri) const;

    boolean equals(const URI & uri);

    void send();
    void send(const XBeeAddress64 & addr64);
    void receive(XBeeAddress64 & addr64);
    void receive(XBeeAddress64 & addr64, const unsigned long timeout);

  };

}                                      /* namespace ndn */
#endif                                 /* URI_H_ */
