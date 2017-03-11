
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

#ifndef LNDN_EXAMPLE_OBJECTTEST_DUMMY_H_
#define LNDN_EXAMPLE_OBJECTTEST_DUMMY_H_

#include "lNDN.h"

namespace ndn {
  class Dummy:public Object {
  public:
    Dummy();
    Dummy(const String uri);

    void action();
    void action(const String & value);


      virtual ~ Dummy();
  };

}                                      /* namespace ndn */
#endif                                 /* LNDN_EXAMPLE_OBJECTTEST_DUMMY_H_ */
